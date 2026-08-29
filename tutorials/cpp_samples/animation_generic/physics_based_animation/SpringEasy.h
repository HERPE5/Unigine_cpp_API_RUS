#pragma once

#include "SpringMotion.h"

#include <UnigineComponentSystem.h>

// Упрощённая настройка пружины с использованием интуитивных параметров.
// Вместо сырых значений жёсткости/демпфирования используются:
// - duration: время затухания пружины
// - damping_ratio: величина колебаний (0.01-1, чем ниже, тем более "пружинисто")
// Жёсткость и демпфирование вычисляются автоматически из этих значений.
class SpringEasy : public SpringMotion

{
public:
	COMPONENT_DEFINE(SpringEasy, SpringMotion);

	PROP_PARAM(Float, duration, 6.0f);
	// коэффициент демпфирования [0.01, 1]
	PROP_PARAM(Float, damping_ratio, 0.6f);
	// Пружина никогда не достигает нулевой амплитуды, она становится бесконечно меньше.
	// Эта доля представляет собой воспринимаемую нулевую точку.
	PROP_PARAM(Float, fraction_of_amplitude, 1500.0f);

private:
	void refresh_spring_settings() override;
};
