// Загружает меши и текстуры асинхронно через AsyncQueue. Меши опрашиваются
// каждый кадр; текстуры используют коллбэки событий. Создаёт объекты сцены и GUI-спрайты.

#include "AsyncQueueSample.h"

#include <UnigineAsyncQueue.h>
#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(AsyncQueueSample)

// Ресурсы ставятся в очередь для фоновой загрузки; подписываемся на событие текстур.
void AsyncQueueSample::init()
{
	// Ставим меши в очередь для асинхронной загрузки и сохраняем ID запросов
	for (int i = 0; i < meshes.size(); ++i)
	{
		const char *name = meshes[i];
		AsyncLoadRequest request;
		request.name = name;
		request.id = AsyncQueue::loadMesh(name);
		mesh_load_requests.push_back(request);
	}

	// Ставим текстуры в очередь для асинхронной загрузки (обрабатывается коллбэком)
	for (int i = 0; i < textures.size(); ++i)
	{
		AsyncQueue::loadImage(textures[i]);
	}

	// Подписываемся на события загрузки текстур
	AsyncQueue::getEventImageLoaded().connect(this, &AsyncQueueSample::image_loaded_callback);

	Console::setOnscreen(true);
}

// Обрабатываются завершённые запросы мешей, создаются объекты сцены.
void AsyncQueueSample::update()
{
	// Проверяем статус всех запросов загрузки мешей
	for (int i = 0; i < mesh_load_requests.size(); ++i)
	{
		const AsyncLoadRequest &request = mesh_load_requests[i];
		if (!AsyncQueue::checkMesh(request.id))
		{
			continue;
		}

		// Забираем меш из AsyncQueue, как только он готов
		MeshPtr mesh = AsyncQueue::takeMesh(request.id);

		if (mesh != nullptr)
		{
			// Создаём объект ObjectMeshDynamic из загруженного меша
			const ObjectMeshDynamicPtr object_mesh_dynamic = ObjectMeshDynamic::create(mesh);

			// Размещаем объекты последовательно вдоль оси X
			constexpr Scalar initial_pos = -5.;
			constexpr Scalar step = 5.;
			object_mesh_dynamic->setPosition(
				Vec3(initial_pos + static_cast<float>(objects_placed) * step, 0., 0.));
			objects_placed++;

			// Удаляем запрос из AsyncQueue и локального отслеживания
			AsyncQueue::removeMesh(request.id);
			Log::message("Loaded mesh \"%s\"\n", request.name.get());
			mesh_load_requests.remove(i--);
		}
	}
}

// GUI-спрайты удаляются, консоль скрывается.
void AsyncQueueSample::shutdown()
{
	// Удаляем все GUI-спрайты и скрываем консоль
	for (auto &sprite : sprites)
	{
		sprite.deleteLater();
	}

	Console::setOnscreen(false);
}

// Вызывается по завершении загрузки текстуры
void AsyncQueueSample::image_loaded_callback(const char *name, int id)
{
	auto loaded_image = AsyncQueue::takeImage(id);
	if (!loaded_image)
	{
		return;
	}

	AsyncQueue::removeImage(id);
	Log::message("Image \"%s\" loaded\n", name);

	// Создаём GUI-спрайт для отображения загруженного изображения
	auto main_window = WindowManager::getMainWindow();
	auto gui = main_window->getGui();

	auto sprite = WidgetSprite::create(gui);
	sprites.push_back(sprite);
	gui->addChild(sprite, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);
	sprite->setImage(loaded_image);
	sprite->setWidth(100);
	sprite->setHeight(100);

	ivec2 initial_sprite_position = ivec2(0, main_window->getSize().y - 200);

	// Размещаем спрайты последовательно по окну
	auto new_pos = ivec2(initial_sprite_position.x + sprites.size() * 100,
		initial_sprite_position.y);
	sprite->setPosition(new_pos.x, new_pos.y);
}
