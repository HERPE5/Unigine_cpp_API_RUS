#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

class Laser;
class SpringRegular;

// Интерактивный игровой режим, в котором игрок управляет лазерной указкой.
// Кот использует физику пружины для погони за лазером с нарастающей
// сложностью со временем (жёсткость и демпфирование увеличиваются).
// Игра заканчивается, когда кот ловит лазер.
class CatGame : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CatGame, Unigine::ComponentBase);

	COMPONENT_INIT(init, -1);
	// обновляем CatGame после обновления лазера и компонентов движения кота
	COMPONENT_UPDATE(update, 1);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, laserNode);
	PROP_PARAM(Node, catMode);

	// Добавляет связанные с игрой элементы GUI в окно примера
	void initGUI(const Unigine::WidgetWindowPtr &window);

private:
	float timer = 0.f;
	bool catched = false;

	SpringRegular *cat_mode = nullptr;
	Laser *laser_component = nullptr;

	Unigine::WidgetGroupBoxPtr game_box;
	Unigine::WidgetLabelPtr game_label;
	Unigine::WorldIntersectionPtr intersection = Unigine::WorldIntersection::create();

private:
	void init();
	void on_enable() override;
	void on_disable() override;
	void update();
	void update_game();
	void update_gameover();
	void shutdown();
	void shutdown_gui();
};
