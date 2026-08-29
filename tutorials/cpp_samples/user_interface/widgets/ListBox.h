// Демонстрирует WidgetListBox для отображения прокручиваемого списка выбираемых
// элементов. Элементы добавляются программно, а изменения выбора вызывают
// callback EventChanged, который показывает текст выбранного элемента в консоли.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт прокручиваемый виджет списка для выбора элемента.
class ListBox : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ListBox, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(300, 300));
	// Размер шрифта для элементов списка
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета списка
	Unigine::WidgetListBoxPtr widget_listbox;
};
