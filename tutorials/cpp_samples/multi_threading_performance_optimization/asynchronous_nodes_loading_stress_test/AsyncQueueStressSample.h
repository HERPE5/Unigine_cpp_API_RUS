#pragma once

#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Стресс-тестирует AsyncQueue, создавая множество узлов в фоновом потоке.
// Узлы создаются и позиционируются вне главного потока, затем активируются в главном.
class AsyncQueueStressSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AsyncQueueStressSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates stress testing of asynchronous node loading. "
		"It uses AsyncQueue to spawn multiple nodes in a background thread, assigns them random positions, "
		"and activates them on the main thread while displaying progress in the UI.")

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// узел, который будет многократно создаваться на сцене (задаётся в редакторе)
	PROP_PARAM(File, node_to_spawn);

private:
	void init();     // создаёт элементы управления UI и включает профилировщик
	void update();   // обновляет отображение количества загруженных узлов
	void shutdown(); // отключает профилировщик и закрывает UI

	// асинхронно загружает заданное количество узлов
	void load_nodes(int num);

	// счётчик успешно загруженных узлов
	Unigine::AtomicInt64 num_nodes_loaded;

	// UI примера с описанием и элементами управления
	Unigine::WidgetLabelPtr num_nodes_loaded_label;
	SampleDescriptionWindow sample_description_window;
};