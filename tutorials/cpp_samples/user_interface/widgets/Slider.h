// Демонстрирует WidgetSlider для выбора значения через перетаскиваемый ползунок. Размеры
// слайдера и ширина кнопки настраиваются через свойства компонента, изменения значения
// отображаются в оверлее консоли через callback EventChanged.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт перетаскиваемый виджет слайдера для выбора значения.
class Slider : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Slider, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(600, 150));
	// Размеры виджета в пикселях
	PROP_PARAM(Vec2, size, Unigine::Math::vec2(100, 50));
	// Ширина кнопки-ползунка слайдера
	PROP_PARAM(Int, button_width, 30)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета слайдера
	Unigine::WidgetSliderPtr widget_slider;
};
