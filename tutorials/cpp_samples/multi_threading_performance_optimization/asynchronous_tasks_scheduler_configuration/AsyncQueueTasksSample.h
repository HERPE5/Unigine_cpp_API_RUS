#pragma once

#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Демонстрирует выполнение задач через AsyncQueue на разных типах потоков.
// Показывает одиночные асинхронные задачи, многопоточные задачи и режимы sync/async выполнения.
class AsyncQueueTasksSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AsyncQueueTasksSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates running single and multithreaded tasks "
		"using AsyncQueue, with options for thread type and async or sync execution.")

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();     // создаёт UI с элементами управления выполнением задач
	void shutdown(); // скрывает консоль и закрывает UI

	// одиночная асинхронная задача
	void async_task();

	// коллбэк многопоточной задачи. Получает текущий индекс потока и общее количество потоков
	void multithread_task(int current_thread, int total_threads);

	// UI примера с описанием и элементами управления
	SampleDescriptionWindow sample_description_window;
};
