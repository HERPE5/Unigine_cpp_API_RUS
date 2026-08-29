// Демонстрирует WidgetSpinBox, присоединённый к WidgetEditLine для числового ввода с
// кнопками увеличения/уменьшения. Spinbox размещается поверх строки ввода с помощью
// порядка отрисовки виджетов, изменения значения отображаются в оверлее консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт элемент управления spinbox, присоединённый к строке ввода для числового ввода.
class SpinBox : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SpinBox, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(625, 300));

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Виджет spinbox с кнопками увеличения/уменьшения
	Unigine::WidgetSpinBoxPtr widget_spinbox;
	// Виджет строки ввода для отображения числового значения
	Unigine::WidgetEditLinePtr widget_editline;
};
