// Демонстрирует WidgetMenuBar с вложенными выпадающими меню WidgetMenuBox. Каждый пункт
// панели меню открывает всплывающее меню с выбираемыми элементами, а события выбора
// обрабатываются через callback EventClicked, которые отображают выбранный пункт в консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт панель меню с выпадающими всплывающими меню.
class Menu : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Menu, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(450, 300));
	// Размер шрифта для элементов меню
	PROP_PARAM(Int, font_size, 16)
	// Цвет подсветки для элементов меню под курсором
	PROP_PARAM(Color, selection_color, Unigine::Math::vec4(0.3f, 0.3f, 0.3f, 1.0f));

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета панели меню
	Unigine::WidgetMenuBarPtr widget_menubar;
};
