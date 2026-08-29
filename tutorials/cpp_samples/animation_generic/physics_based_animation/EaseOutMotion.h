#pragma once

#include "MotionMode.h"

#include <UnigineComponentSystem.h>

// Движение ease-out: постепенное замедление к цели.
// Начинается быстро и замедляется по мере приближения к цели.
// Использует экспоненциальную интерполяцию (lerp с экспоненциальным затуханием) для плавной остановки.
class EaseOutMotion : public MotionMode
{
public:
	COMPONENT_DEFINE(EaseOutMotion, MotionMode);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, speed, 2.0f);

private:
	float idle_anim_weight = 0;
	float run_anim_time = 0;

	// максимальное расстояние до цели для её поимки
	const float distance_epsilon = 0.5f;

private:
	void update();
	Unigine::Math::Vec3 move_towards(const Unigine::Math::Vec3 &src, // исходная точка
		const Unigine::Math::Vec3 &dst,                              // целевая точка
		float speed,                                                 // скорость движения
		bool &out_finished,                                          // движение остановлено
		Unigine::Math::Vec3 &out_dir); // направление от исходной точки к целевой
};