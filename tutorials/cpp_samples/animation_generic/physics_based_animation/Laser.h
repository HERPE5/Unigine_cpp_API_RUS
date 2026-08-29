#pragma once

#include <UnigineComponentSystem.h>

// Лазерная указка, следующая за позицией курсора мыши.
// Отправляет луч от камеры через позицию мыши
// и размещает узел в точке пересечения с миром.
class Laser : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Laser, Unigine::ComponentBase);
	COMPONENT_UPDATE(update, -1);

private:
	Unigine::WorldIntersectionPtr intersection = Unigine::WorldIntersection::create();

private:
	void update();
};