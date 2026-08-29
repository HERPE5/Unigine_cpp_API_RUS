// Демонстрирует создание WidgetCheckBox и обработку событий. Изменения состояния вызывают
// callback EventChanged, который отображает текущее состояние отметки в
// оверлее консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт переключаемый виджет чекбокса с текстом метки.
class CheckBox : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CheckBox, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(450, 50));
	// Текст метки, отображаемой рядом с чекбоксом
	PROP_PARAM(String, text, "Check Me");
	// Размер шрифта для текста метки
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета чекбокса
	Unigine::WidgetCheckBoxPtr widget_checkbox;
};
