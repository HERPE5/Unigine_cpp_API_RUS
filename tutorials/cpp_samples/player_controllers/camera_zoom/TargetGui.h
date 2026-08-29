// Отображает внутримировую GUI-панель, привязанную к целевому объекту, показывающую
// расстояние от камеры и размер метки. Обновляет расстояние каждый кадр.

#pragma once
#include "UnigineComponentSystem.h"

// Внутримировой GUI, показывающий информацию о цели (имя, расстояние, размер).
class TargetGui : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TargetGui, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	void update();

private:
	Unigine::ObjectGuiPtr object_gui;		// ObjectGui, к которому привязан этот компонент
	Unigine::GuiPtr gui;					// Контекст GUI для создания виджетов
	Unigine::WidgetLabelPtr distance_label;	// Обновляется каждый кадр текущим расстоянием

	void init();
};