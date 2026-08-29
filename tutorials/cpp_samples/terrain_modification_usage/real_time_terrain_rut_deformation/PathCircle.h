// Перемещает узел по круговому пути, комбинируя движение вперёд и вращение.
// Speed управляет линейной скоростью; angular_speed управляет скоростью поворота.
// Используется для симуляции транспортных средств, оставляющих следы на terrain.

#pragma once

#include <UnigineComponentSystem.h>

// Анимирует движение узла по круговому паттерну.
class PathCircle : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(PathCircle, Unigine::ComponentBase);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, speed, 1.0f, "Speed");				// Линейная скорость в единицах в секунду
	PROP_PARAM(Float, angular_speed, 45.0f, "Angular Speed");	// Скорость поворота в градусах в секунду

private:
	void update();
};