// Обновляет множество экземпляров ObjectMeshCluster параллельно с помощью CPUShader.
// Каждый кластер имеет видимую и асинхронную копии; они меняются местами каждый кадр для бесшовных обновлений.

#include "CPUShaderSample.h"

#include <UnigineGame.h>
#include <UnigineProfiler.h>

REGISTER_COMPONENT(CPUShaderSample)

using namespace Unigine;
using namespace Math;


constexpr int SIZE{30};
constexpr float MIN_SPACING{15.0f};  // минимальный зазор между кластерами
// Фактический интервал
constexpr float SPACING = static_cast<float>(SIZE * 2 + 1) + MIN_SPACING;

void CPUShaderSample::AsyncCluster::update(const ObjectMeshClusterPtr &cluster_)
{
	UNIGINE_PROFILER_FUNCTION;

	// Генерируем трансформации на основе таймера и случайных значений
	random.setSeed(seed);
	int num = 0;

	for (int y = -SIZE; y <= SIZE; y++)
	{
		for (int x = -SIZE; x <= SIZE; x++)
		{
			const Scalar rand_timer = timer + random.getFloat(0, 100.0);
			auto pos = Vec3(static_cast<Scalar>(x), static_cast<Scalar>(y),
						   Math::cos(rand_timer) * 50.f)
				+ offset;
			transforms[num] = translate(pos) * rotateZ(rand_timer * 360.f)
				* scale(static_cast<Scalar>(5.0f));
			num++;
		}
	}

	// Перестраиваем геометрию кластера из трансформаций
	cluster_->createMeshes(transforms);
}

void CPUShaderSample::AsyncCluster::swap()
{
	// Меняем местами асинхронный и рендерящийся кластеры в конце кадра
	UNIGINE_PROFILER_FUNCTION;

	timer += Game::getIFps();

	// Прогреваем несколько кадров, чтобы стриминг устоялся
	is_need_update = cluster->isVisibleCamera() || cluster->isVisibleShadow() || frames < 60;
	if (frames < 60)
	{
		frames++;
	}

	if (!is_need_update)
	{
		return;
	}

	// Меняем местами активный и асинхронный кластеры
	cluster->swap(cluster_async);
	cluster->setEnabled(true);
	cluster_async->setEnabled(false);
}

void CPUShaderSample::AsyncCluster::update()
{
	// Обновляем кластер асинхронно при необходимости
	UNIGINE_PROFILER_FUNCTION;
	if (is_need_update)
	{
		update(cluster_async);
	}
}

void CPUShaderSample::UpdateClusterCPUShader::process(int thread_num, int threads_count)
{
	UNIGINE_PROFILER_FUNCTION;

	while (true)
	{
		const int num = counter.fetch_add(1);
		if (num >= clusters.size())
		{
			break;
		}
		clusters[num].update();
	}
}


// Мы вызываем этот метод сами
//	runAsync - неблокирующий. Работа планируется в пуле потоков движка.
//		Кадр позже приостановится на Engine::swap() до завершения всех задач.
//	runSync - блокирующий. Выполнение ждёт здесь до завершения.
void CPUShaderSample::UpdateClusterCPUShader::run()
{
	UNIGINE_PROFILER_FUNCTION;

	for (auto &c : clusters)
	{
		c.swap();
	}

	counter = 0;
	runAsync();
}

void CPUShaderSample::init()
{
	// Создаём объект CPUShader
	shader = std::make_unique<UpdateClusterCPUShader>();
	Vector<AsyncCluster> &clusters = shader->clusters;
	clusters.resize(64);

	// Количество трансформаций на кластер
	const int num_objects = pow2(static_cast<int>(SIZE * 2 + 1));

	// Инициализируем кластеры
	for (int i = 0; i < shader->clusters.size(); i++)
	{
		AsyncCluster &c = clusters[i];

		// Создаём основную и асинхронную копии кластера
		const String mesh_path = mesh.get();
		c.cluster = ObjectMeshCluster::create(mesh_path);
		c.cluster->setMaterialParameterFloat4("albedo_color", Game::getRandomColor(), 0);
		c.cluster_async = static_ptr_cast<ObjectMeshCluster>(c.cluster->clone());

		// Включаем только основной кластер
		c.cluster->setEnabled(true);
		c.cluster_async->setEnabled(false);

		c.is_need_update = true;

		// Распределяем кластеры по сетке
		const float x = SPACING * getBit(i, 0) + SPACING * 2.0f * getBit(i, 2)
			+ SPACING * 4.0f * getBit(i, 4);
		const float y = SPACING * getBit(i, 1) + SPACING * 2.0f * getBit(i, 3)
			+ SPACING * 4.0f * getBit(i, 5);

		c.offset = Vec3(x, y, 0);
		c.seed = i;

		// Выделяем буфер трансформаций
		c.transforms.resize(num_objects);

		// Строим начальные меши
		c.update(c.cluster);

		clusters[i] = c;
	};
	Log::message("Num objects %d", num_objects * shader->clusters.size());
}

// Кластеры меняются местами, асинхронное обновление планируется на следующий кадр.
void CPUShaderSample::swap() const
{
	// запускаем работу CPUShader
	// примечание: runAsync планирует выполнение; если не завершено к Engine::swap(),
	//       swap() заблокируется до завершения
	shader->run();
}
