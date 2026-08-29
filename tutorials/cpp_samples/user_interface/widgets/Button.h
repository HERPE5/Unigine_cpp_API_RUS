// Демонстрирует создание WidgetButton с настраиваемым размером, позицией и шрифтом.
// События клика обрабатываются через callback EventClicked, который отображает
// сообщение в оверлее консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт кликабельный виджет кнопки с настраиваемым внешним видом.
class Button : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Button, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(250, 50));
	// Размеры кнопки в пикселях
	PROP_PARAM(Vec2, size, Unigine::Math::vec2(100, 50));
	// Текст метки, отображаемой на кнопке
	PROP_PARAM(String, text, "Press Me");
	// Размер шрифта для текста кнопки
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета кнопки
	Unigine::WidgetButtonPtr widget_button;
};
