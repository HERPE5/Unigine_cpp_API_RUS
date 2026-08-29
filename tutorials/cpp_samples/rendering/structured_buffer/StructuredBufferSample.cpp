// Сжатие текстуры в формат DXT1 на GPU с использованием compute-шейдеров и
// структурированных буферов. Демонстрирует создание UAV-структурированного буфера,
// запуск compute-шейдера и асинхронную передачу GPU->CPU для сохранения сжатого изображения.

#include "StructuredBufferSample.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(StructuredBufferSample)

// Загружает текстуру, запускает compute-шейдер для сжатия DXT и сохраняет результат в файл.
void StructuredBufferSample::init()
{
	// Compute-материал
	MaterialPtr compute_material = Materials::findManualMaterial("gpu_dxt_compute");

	// Загружаем исходную текстуру
	TexturePtr source_texture = Texture::create();
	source_texture->load(source_texture_param.get());

	Log::message("Source texture size %ix%i: %i kb\n", source_texture->getWidth(),
		source_texture->getHeight(),
		(source_texture->getWidth() * source_texture->getHeight() * 3) / 1024);

	// Выходная структура
	struct DXT1Block
	{
		unsigned int colors;
		unsigned int indices;
	};

	// Вычисляем размер DXT
	const int dxt_size_x = source_texture->getWidth() / 4;
	const int dxt_size_y = source_texture->getHeight() / 4;

	// Определено шейдером
	const int threads_in_group_x = 8;
	const int threads_in_group_y = 8;

	// Создаём выходной структурированный буфер (gpu_read-readwrite)
	StructuredBufferPtr dxt_buffer = StructuredBuffer::create();
	dxt_buffer->create(StructuredBuffer::USAGE_RENDER, NULL, sizeof(DXT1Block),
		dxt_size_x * dxt_size_y);

	Unigine::Log::message("Structure buffer (compressed DXT) size in video memory: %s\n",
		Unigine::String::memory(sizeof(DXT1Block) * dxt_size_x * dxt_size_y).get());

	// Создаём compute render
	RenderTargetPtr render_target = RenderTarget::create();

	// Привязываем исходную текстуру
	RenderState::setTexture(RenderState::BIND_ALL, 0, source_texture);

	// Настраиваем буфер неупорядоченного доступа (чтение-запись)
	render_target->bindStructuredBuffer(0, dxt_buffer);
	render_target->enableCompute();

	// Вычисляем группы для запуска compute-шейдера
	int groups_x = (dxt_size_x) / threads_in_group_x;
	int groups_y = (dxt_size_y) / threads_in_group_y;

	if ((dxt_size_x) % threads_in_group_x > 0)
	{
		groups_x++;
	}

	if ((dxt_size_y) % threads_in_group_y > 0)
	{
		groups_y++;
	}

	long begin_time = clock();

	// Вычисляем время разогрева (компиляция шейдера)
	compute_material->renderCompute(Render::PASS_POST, 1, 1);
	render_target->flush();

	float time_warmup = float(clock() - begin_time) / CLOCKS_PER_SEC * 1000;
	begin_time = clock();

	// Запускаем groups_x * groups_y групп потоков, по 256 потоков в каждой
	compute_material->renderCompute(Render::PASS_POST, groups_x, groups_y);
	render_target->flush();

	float time_execution = float(clock() - begin_time) / CLOCKS_PER_SEC * 1000;

	Unigine::Log::message("Shader setup and compilation time: %f ms\n", time_warmup);
	Unigine::Log::message(
		"Dispatched %ix%i group threads (%ix%i threads each), execution time: %f ms\n", groups_x,
		groups_y, threads_in_group_x, threads_in_group_y, time_execution);

	render_target->disable();
	render_target->unbindStructuredBuffers();

	// Создаём изображение
	ImagePtr dxt_image = Image::create();
	dxt_image->create2D(source_texture->getWidth(), source_texture->getHeight(), Image::FORMAT_DXT1,
		1, 0, 1);

	begin_time = clock();

	// Передаём данные из GPU в изображение CPU
	Render::asyncTransferStructuredBuffer(nullptr,
		MakeCallback([begin_time, dxt_image, dxt_buffer](void *data) {
			Unigine::Log::message("Transfer GPU -> CPU time: %f ms\n",
				float(clock() - begin_time) / CLOCKS_PER_SEC * 1000);
			memcpy(dxt_image->getPixels(), data, sizeof(DXT1Block) * dxt_buffer->getNumElements());

			// Сохраняем изображение
			String path = String::format("%s%s", Engine::get()->getSavePath(),
				"compressed_image.dds");
			dxt_image->save(path.get());
			Unigine::Log::message("Compressed texture saved: %s\n", path.get());
		}),
		dxt_buffer);

	dxt_buffer.clear();
}
