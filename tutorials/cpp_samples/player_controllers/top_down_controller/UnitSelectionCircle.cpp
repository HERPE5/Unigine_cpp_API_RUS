// Визуальный индикатор для выбранных юнитов. Загружает узел круга выбора
// и делает его дочерним по отношению к юниту, переключая видимость в зависимости от состояния выбора.

#include "UnitSelectionCircle.h"
#include <UniginePrimitives.h>
REGISTER_COMPONENT(UnitSelectionCircle);

using namespace Unigine;
using namespace Math;

// Задаёт состояние выбора и соответственно показывает/скрывает круг выбора.
void UnitSelectionCircle::setSelected(bool value)
{
	if (!selection_circle)
		return;

	selected = value;
	selection_circle->setEnabled(selected);
}

// Загружает узел круга выбора, делает его дочерним по отношению к этому юниту и изначально скрывает его.
void UnitSelectionCircle::init()
{
	selection_circle = World::loadNode(selectionCircle.get());
	if (!selection_circle)
	{
		Log::error("UnitSelectionCircle::init(): cannot load node '%s'\n", selectionCircle.get());
		return;
	}

	selection_circle->setParent(node);
	selection_circle->setPosition(Vec3(offset.get()));
	selection_circle->setEnabled(false);
}
