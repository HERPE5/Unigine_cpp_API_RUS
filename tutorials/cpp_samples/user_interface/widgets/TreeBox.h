// Демонстрирует WidgetTreeBox для иерархического отображения элементов. Отношения
// родитель-потомок устанавливаются через addItemChild, создавая раскрываемые узлы
// дерева. Изменения выбора вызывают callback EventChanged для вывода в консоль.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт виджет древовидного списка с раскрываемыми иерархическими узлами.
class TreeBox : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TreeBox, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(775, 300));
	// Размер шрифта для меток элементов дерева
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета древовидного списка
	Unigine::WidgetTreeBoxPtr widget_treebox;
};
