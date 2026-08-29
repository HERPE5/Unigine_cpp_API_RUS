// Демонстрирует WidgetScroll как самостоятельный элемент управления полосой прокрутки. Ориентация
// полосы прокрутки устанавливается горизонтальной, а изменения значения вызывают callback
// EventChanged, который показывает текущую позицию прокрутки в оверлее консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт виджет горизонтальной полосы прокрутки с отслеживанием изменения значения.
class Scroll : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Scroll, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(500, 150));

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета полосы прокрутки
	Unigine::WidgetScrollPtr widget_scroll;
};
