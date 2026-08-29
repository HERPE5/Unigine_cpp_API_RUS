// Демонстрирует порождение следов terrain с настраиваемыми параметрами.
// Предоставляет элементы управления GUI для настройки интервала следов и размера пула.
// Управляет несколькими компонентами TrackSpawner в иерархии дочерних узлов.

#include "TracksSample.h"

REGISTER_COMPONENT(TracksSample);

using namespace Unigine;
using namespace Math;

// Компоненты-спавнеры следов собираются, инициализируется GUI.
void TracksSample::init()
{
	// Собираются все компоненты TrackSpawner среди дочерних узлов
	getComponentsInChildren<TrackSpawner>(getNode(), track_spawners);

	// Создаётся панель управления
	init_gui();
}

// Ресурсы GUI освобождаются.
void TracksSample::shutdown()
{
	shutdown_gui();
}

// Создаются элементы управления параметрами для настройки порождения следов.
void TracksSample::init_gui()
{
	// Окно примера создаётся из переиспользуемого компонента
	sample_description_window.createWindow();

	auto parameters = sample_description_window.getParameterGroupBox();

	// Создаётся строка параметра минимального расстояния
	auto hbox = WidgetHBox::create(4);
	parameters->addChild(hbox, Gui::ALIGN_LEFT);

	auto label = WidgetLabel::create("Min distance between track maps");
	label->setWidth(200);
	hbox->addChild(label, Gui::ALIGN_LEFT);

	// Создаётся поле ввода float для минимального расстояния
	min_distance_edit_line = WidgetEditLine::create("0.1");
	min_distance_edit_line->setValidator(Gui::VALIDATOR_FLOAT);
	min_distance_edit_line->getEventChanged().connect(this, &TracksSample::min_distance_edit_line_callback);
	hbox->addChild(min_distance_edit_line, Gui::ALIGN_LEFT);

	// Создаётся строка параметра максимального количества
	hbox = WidgetHBox::create(4);
	parameters->addChild(hbox, Gui::ALIGN_LEFT);

	label = WidgetLabel::create("Max number of track maps");
	label->setWidth(200);
	hbox->addChild(label, Gui::ALIGN_LEFT);

	// Создаётся поле ввода целого числа для размера пула
	max_number_edit_line = WidgetEditLine::create("100");
	max_number_edit_line->setValidator(Gui::VALIDATOR_UINT);
	max_number_edit_line->getEventChanged().connect(this, &TracksSample::max_number_edit_line_callback);
	hbox->addChild(max_number_edit_line, Gui::ALIGN_LEFT);
}

// Окно примера освобождается.
void TracksSample::shutdown_gui()
{
	sample_description_window.shutdown();
}

// Параметр расстояния применяется ко всем спавнерам.
void TracksSample::min_distance_edit_line_callback()
{
	// Текст ввода разбирается как float
	float value = String::atof(min_distance_edit_line->getText());

	// Значение применяется ко всем компонентам-спавнерам
	for (auto track_spawner : track_spawners)
	{
		track_spawner->setMinDistanceBetweenTracks(value);
	}
}

// Параметр размера пула применяется ко всем спавнерам.
void TracksSample::max_number_edit_line_callback()
{
	// Текст ввода разбирается как целое число
	int value = String::atoi(max_number_edit_line->getText());

	// Значение применяется ко всем компонентам-спавнерам
	for (auto track_spawner : track_spawners)
	{
		track_spawner->setMaxNumberOfTracks(value);
	}
}
