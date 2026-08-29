// Демонстрирует порождение следов terrain с настраиваемыми параметрами.
// Предоставляет элементы управления GUI для настройки интервала следов и размера пула.
// Управляет несколькими компонентами TrackSpawner в иерархии дочерних узлов.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include "TrackSpawner.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Контроллер для примера порождения следов с GUI параметров.
class TracksSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TracksSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

	Unigine::Vector<TrackSpawner *> track_spawners;		// Все компоненты-спавнеры среди дочерних узлов

	// Инициализация и очистка GUI
	void init_gui();
	void shutdown_gui();

	void min_distance_edit_line_callback();		// Обрабатывает изменение параметра расстояния
	void max_number_edit_line_callback();		// Обрабатывает изменение параметра размера пула

	Unigine::WidgetEditLinePtr min_distance_edit_line;	// Виджет ввода расстояния
	Unigine::WidgetEditLinePtr max_number_edit_line;	// Виджет ввода размера пула

	SampleDescriptionWindow sample_description_window;	// Переиспользуемый компонент окна
};