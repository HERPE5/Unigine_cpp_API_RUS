// Демонстрирует поведение переключателя (radio button) с использованием WidgetCheckBox и addAttach.
// Присоединение чекбоксов создаёт взаимное исключение, так что можно выбрать только один
// одновременно. Изменения выбора отображаются в оверлее консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт взаимоисключающие переключатели с использованием присоединённых чекбоксов.
class RadioButtons : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(RadioButtons, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, widget_position, Unigine::Math::vec2(600, 450));
	// Размер шрифта для меток переключателей
	PROP_PARAM(Int, font_size, 16);
	// Горизонтальный отступ внутри контейнера компоновки
	PROP_PARAM(Int, horizontal_layout_space, 4);
	// Вертикальный интервал между переключателями
	PROP_PARAM(Int, vertical_layout_space, 4);
	// Текст метки для первого переключателя
	PROP_PARAM(String, first_rbutton_text, "Check Me");
	// Текст метки для второго переключателя
	PROP_PARAM(String, second_rbutton_text, "Or Me");

private:
	void init();
	void shutdown();

	// Вертикальный контейнер компоновки для размещения переключателей
	Unigine::WidgetVBoxPtr p_vertical_layout;

	// Виджет чекбокса первого переключателя
	Unigine::WidgetCheckBoxPtr p_first_rbutton = nullptr;
	// Виджет чекбокса второго переключателя
	Unigine::WidgetCheckBoxPtr p_second_rbutton = nullptr;
};
