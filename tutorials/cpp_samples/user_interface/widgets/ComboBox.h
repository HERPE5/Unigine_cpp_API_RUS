// Демонстрирует WidgetComboBox как выпадающий виджет выбора. Элементы добавляются
// программно, а изменения выбора вызывают callback EventChanged, который
// показывает текст выбранного элемента в оверлее консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт виджет выпадающего списка для выбора элемента.
class ComboBox : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ComboBox, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(600, 50));
	// Размер шрифта для элементов выпадающего списка
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета выпадающего списка
	Unigine::WidgetComboBoxPtr widget_combobox;
};
