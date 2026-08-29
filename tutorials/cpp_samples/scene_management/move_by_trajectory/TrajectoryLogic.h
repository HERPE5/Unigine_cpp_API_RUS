// UI примера для демонстрации движения по траектории с тремя самолётами.
// Каждый самолёт использует свой подход к движению (линейный, сплайновый, файл пути).
// Предоставляет управление скоростью, переключение камер и переключатель визуализации пути.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"
#include "UnigineComponentSystem.h"
#include "UniginePlayers.h"

// Управляет UI примера и переключением камер между самолётами.
class TrajectoryLogic : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TrajectoryLogic, ComponentBase);
	COMPONENT_DESCRIPTION("This component displays information about the sample and demonstrates "
						  "how to use a trajectory movement.");
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Самолёт, использующий линейную интерполяцию
	PROP_PARAM(Node, airplane_1);
	// Самолёт, использующий сплайновую интерполяцию
	PROP_PARAM(Node, airplane_2);
	// Самолёт, использующий сохранённый файл пути
	PROP_PARAM(Node, airplane_3);

private:
	void init();
	void update();
	void shutdown();
	void init_gui();
	// Обновляет скорость во всех компонентах движения
	void update_velocity_callback();
	// Переключает активную камеру между основным видом и видами, прикреплёнными к самолётам
	void switch_trajectory_callback();
	// Переключает отладочную визуализацию пути на всех самолётах
	void enable_visualize_callback();

	Unigine::WidgetWindowPtr window;

	Unigine::WidgetSliderPtr velocity_widget;
	Unigine::WidgetLabelPtr velocity_value_label;
	Unigine::WidgetButtonPtr switch_camera;
	Unigine::WidgetCheckBoxPtr enable_visualize_path;

	// Индексы камер для переключения между видами
	enum Players
	{
		MAIN,
		ONE,
		TWO,
		THREE,
		TOTAL_PLAYERS
	};

	// Все доступные камеры (основная плюс прикреплённые к самолётам)
	Unigine::Vector<Unigine::PlayerPtr> main_players;
	Players current_player = MAIN;

	SampleDescriptionWindow sample_description_window;
};
