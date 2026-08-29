#pragma once

#include "MotionMode.h"

#include <UnigineComponentSystem.h>

// Линейное движение: движение к цели с постоянной скоростью.
// Простейшая функция сглаживания - без ускорения или замедления.
// Движение резко останавливается по достижении цели.
class LinearMotion : public MotionMode
{
public:
	COMPONENT_DEFINE(LinearMotion, MotionMode);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, speed, 2.0f);	// единиц в секунду

private:
	void update();

	// Вычисляет новую позицию и направление преследователя
	Unigine::Math::Vec3 move_towards(const Unigine::Math::Vec3 &src, // исходная точка
		const Unigine::Math::Vec3 &dst,                              // целевая точка
		float step,                                                  // максимальное смещение
		bool &out_finished,                                          // движение остановлено
		Unigine::Math::Vec3 &out_dir); // направление от исходной точки к целевой
};