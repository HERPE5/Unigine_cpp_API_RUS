#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

class CatDemo;
class CatGame;

// Основной компонент примера, демонстрирующий физически обоснованную анимацию с функциями сглаживания.
// Показывает кота, гоняющегося за лазерной указкой с использованием разных методов интерполяции движения:
// Linear, EaseIn, EaseOut, EaseOutBounce и движение на основе пружины.
// Доступны два режима: Demo (автоматическая демонстрация) и Game (интерактивное управление лазером).
class CatSample: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CatSample, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, demoNode);	// корневой узел для режима demo
	PROP_PARAM(Node, gameNode);	// корневой узел для режима game

private:
	CatDemo *demo_manager;
	CatGame *game_manager;

	SampleDescriptionWindow sample_description_window;
	Unigine::WidgetLabelPtr title_label;
	Unigine::WidgetButtonPtr demo_button;
	Unigine::WidgetButtonPtr game_button;

	Unigine::Input::MOUSE_HANDLE mouse_handle;

private:
	void init();
	void init_gui();
	void switch_to_game();
	void switch_to_demo();
	void shutdown();
	void shutdown_gui();
};



