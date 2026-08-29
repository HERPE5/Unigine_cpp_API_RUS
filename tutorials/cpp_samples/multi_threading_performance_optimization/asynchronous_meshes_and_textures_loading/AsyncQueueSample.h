#pragma once

#include <UnigineComponentSystem.h>

// Демонстрирует фоновую загрузку ресурсов с помощью AsyncQueue.
// Меши и текстуры загружаются в отдельных потоках, пока основной поток
// остаётся отзывчивым. Завершённые ресурсы размещаются на сцене или отображаются как спрайты.
class AsyncQueueSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(AsyncQueueSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates asynchronous resource loading using AsyncQueue. "
			"It queues meshes and textures for background loading, creates scene objects when meshes are ready, "
			"and displays loaded textures as GUI sprites.")

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	// списки ресурсов для загрузки (задаются в редакторе)
	PROP_ARRAY(File, meshes)
	PROP_ARRAY(File, textures)

private:
	void init();     // ставит ресурсы в очередь для асинхронной загрузки
	void update();   // проверяет завершённые меши и создаёт объекты
	void shutdown(); // удаляет спрайты и скрывает консоль

	// коллбэк для завершения загрузки текстуры
	void image_loaded_callback(const char *name, int id);

	// структура для отслеживания запросов загрузки меша
	struct AsyncLoadRequest
	{
		Unigine::String name;
		int id{-1};
	};
	Unigine::Vector<AsyncLoadRequest> mesh_load_requests;

	// счётчик, используемый для размещения мешей на сцене
	int objects_placed{0};

	// GUI-спрайты, созданные из загруженных текстур
	Unigine::Vector<Unigine::WidgetSpritePtr> sprites;
};
