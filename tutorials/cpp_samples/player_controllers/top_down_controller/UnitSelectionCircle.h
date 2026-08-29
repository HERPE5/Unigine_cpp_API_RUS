// Визуальный индикатор выбора для юнитов RTS. Загружает узел круга выбора и делает его
// дочерним по отношению к юниту, переключая видимость в зависимости от состояния выбора.

#pragma once

#include <UnigineComponentSystem.h>

// Компонент-маркер для выбираемых юнитов. Загружает визуальный индикатор (круг выбора),
// появляющийся под юнитом при его выборе.
class UnitSelectionCircle : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(UnitSelectionCircle, Unigine::ComponentBase);

	COMPONENT_INIT(init);

	PROP_PARAM(File, selectionCircle, nullptr, "NodeRefence of selection circle");
	PROP_PARAM(Vec3, offset, Unigine::Math::vec3(0, 0, 0.01), nullptr, "Offset of selection circle from the center of the unit");

	void setSelected(bool value);			// Задаёт состояние выбора и переключает видимость круга
	bool isSelected() { return selected; }	// Возвращает текущее состояние выбора

protected:
	void init();
	Unigine::NodePtr selection_circle;	// Загруженный узел визуального индикатора

private:
	bool selected = false;	// Текущее состояние выбора
};