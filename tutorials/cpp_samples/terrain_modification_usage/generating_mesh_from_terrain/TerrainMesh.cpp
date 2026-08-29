// Генерирует динамический меш из данных высоты terrain с помощью асинхронного LandscapeFetch.
// Сетка позиций сэмплов запрашивается асинхронно с настраиваемым уровнем параллелизма.
// Полученные вершины меша содержат высоту terrain и цвет albedo из landscape.

#include "TerrainMesh.h"

#include <UnigineVisualizer.h>
#include <UnigineMeshDynamic.h>
#include <UnigineMaterials.h>

REGISTER_COMPONENT(TerrainMesh);

using namespace Unigine;
using namespace Math;

// Генерируется сетка позиций сэмплов; инициализируются и запускаются асинхронные запросы.
void TerrainMesh::run()
{
	// Операция запускается, только если ещё не выполняется запрос
	if (state != State::IDLE)
		return;

	// Углы сетки вычисляются из трансформации узла
	Mat4 transform = node->getWorldTransform();
	Vec3 bottom_left = transform * Vec3(-0.5f, -0.5f, 0.0f);

	// Перенос убирается, чтобы получить только векторы направления
	transform.setColumn3(3, Vec3(0.0f, 0.0f, 0.0f));
	Vec3 delta_x = transform * Vec3(1.0f / resolution.x, 0.0f, 0.0f);
	Vec3 delta_y = transform * Vec3(0.0f, 1.0f / resolution.y, 0.0f);

	// Позиции сэмплов генерируются как равномерная сетка
	fetch_positions.clear();
	for (int i = 0; i <= resolution.y; ++i)
	{
		for (int j = 0; j <= resolution.x; ++j)
		{
			Vec3 sample_point = bottom_left + delta_y * static_cast<Scalar>(i) + delta_x * static_cast<Scalar>(j);
			fetch_positions.push_back(sample_point.xy);
		}
	}

	fetch_data.resize(fetch_positions.size());

	// Пул запросов изменяется в размере в соответствии с лимитом параллелизма
	while (fetchers.size() < min(max_fetchers, fetch_positions.size()))
	{
		Fetcher &f = fetchers.emplace_back();
		f.landscape_fetch = LandscapeFetch::create();
		f.landscape_fetch->setUsesHeight(true);
		f.landscape_fetch->setUsesAlbedo(true);
	}

	// Избыточные запросы удаляются, если пул слишком велик
	while (fetchers.size() > min(max_fetchers, fetch_positions.size()))
		fetchers.removeLast();

	// Запускается начальная партия асинхронных запросов
	next_fetch_index = 0;
	fishined_fetch_count = 0;
	for (int i = 0; i < fetchers.size(); ++i)
	{
		fetchers[i].landscape_fetch->fetchAsync(fetch_positions[next_fetch_index]);
		fetchers[i].out_data_index = next_fetch_index;

		next_fetch_index += 1;
	}

	state = State::FETCHING;
}

// Визуализации рендерятся; завершённые запросы обрабатываются, новые ставятся в очередь.
void TerrainMesh::update()
{
	// Ограничивающий бокс визуализируется, если включено
	if (draw_bounding_box)
		Visualizer::renderBox(vec3{1.0f, 1.0f, 800.0f}, node->getTransform(), vec4_white);

	// Каркас визуализируется, если меш существует и флаг установлен
	if (draw_wireframe && mesh_dynamic)
	{
		Visualizer::renderObject(mesh_dynamic, vec4_white);
	}

	// Результаты запросов обрабатываются, пока операция в процессе
	if (state == State::FETCHING)
	{
		for (int i = 0; i < fetchers.size(); ++i)
		{
			// У завершённых запросов сохраняются результаты
			if (fetchers[i].landscape_fetch->isAsyncCompleted())
			{
				fishined_fetch_count += 1;

				// Высота и albedo сохраняются в массиве результатов
				fetch_data[fetchers[i].out_data_index].height = fetchers[i].landscape_fetch->getHeight();
				fetch_data[fetchers[i].out_data_index].albedo = fetchers[i].landscape_fetch->getAlbedo();

				// Запрос переиспользуется для следующей позиции, если остались
				if (next_fetch_index < fetch_positions.size())
				{
					fetchers[i].landscape_fetch->fetchAsync(fetch_positions[next_fetch_index]);
					fetchers[i].out_data_index = next_fetch_index;

					next_fetch_index += 1;
				}
			}
		}

		// Меш генерируется, когда все запросы завершены
		if (fishined_fetch_count == fetch_positions.size())
		{
			generate_mesh();
			state = State::IDLE;
		}
	}
}

// Динамический меш строится из запрошенных данных высоты и цвета.
void TerrainMesh::generate_mesh()
{
	// Объект меша создаётся при первой генерации
	if (!mesh_dynamic)
	{
		mesh_dynamic = ObjectMeshDynamic::create();
		mesh_dynamic->setMaterial(material_prop.get(), "*");
		mesh_dynamic->translate(Vec3(0.0f, 0.0f, 200.f));
	}

	// Предыдущие данные меша очищаются; буферы предварительно выделяются
	mesh_dynamic->clearVertex();
	mesh_dynamic->clearIndices();
	mesh_dynamic->allocateVertex((resolution.x + 1) * (resolution.y + 1));
	mesh_dynamic->allocateIndices(resolution.x * resolution.y * 6);

	// Вершины добавляются с позицией из координат запроса и высоты
	for (int i = 0; i <= resolution.y; ++i)
	{
		for (int j = 0; j <= resolution.x; ++j)
		{
			FetchData &data = fetch_data[(resolution.x + 1) * i + j];
			const auto &position = vec3(vec2(fetch_positions[(resolution.x + 1) * i + j]), data.height);

			mesh_dynamic->addVertex(position);
			mesh_dynamic->addColor(data.albedo);
		}
	}

	// Индексы треугольников генерируются для сетки; недопустимые высоты пропускаются
	for (int i = 0; i < resolution.y; ++i)
	{
		auto pitch = resolution.x + 1;
		auto offset = pitch * i;

		for (int j = 0; j < resolution.x; ++j)
		{
			// Вычисляются углы квада
			const int a = offset + j + 1;
			const int b = offset + pitch + j;
			const int c = offset + j;
			const int d = b + 1;

			// Первый треугольник пропускается, если у любой вершины недопустимая высота
			if (mesh_dynamic->getVertex(a).z == INVALID_FETCH_HEIGHT || mesh_dynamic->getVertex(b).z == INVALID_FETCH_HEIGHT ||
				mesh_dynamic->getVertex(c).z == INVALID_FETCH_HEIGHT)
			{
				continue;
			}

			mesh_dynamic->addIndex(a);
			mesh_dynamic->addIndex(b);
			mesh_dynamic->addIndex(c);

			// Второй треугольник пропускается, если у четвёртой вершины недопустимая высота
			if (mesh_dynamic->getVertex(d).z == INVALID_FETCH_HEIGHT)
			{
				continue;
			}

			mesh_dynamic->addIndex(a);
			mesh_dynamic->addIndex(d);
			mesh_dynamic->addIndex(b);
		}
	}

	// Тангенты и границы пересчитываются; данные загружаются на GPU
	mesh_dynamic->updateTangents();
	mesh_dynamic->updateBounds();
	mesh_dynamic->flushVertex();
	mesh_dynamic->flushIndices();

	// Трансформация применяется повторно для обновления внутренних матриц
	mesh_dynamic->setTransform(mesh_dynamic->getTransform());
}
