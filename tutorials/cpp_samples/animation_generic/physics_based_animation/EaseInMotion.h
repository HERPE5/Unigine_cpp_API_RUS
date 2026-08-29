#pragma once

#include "MotionMode.h"

#include <UnigineComponentSystem.h>

// Движение ease-in: постепенное ускорение из состояния покоя.
// Начинается медленно и ускоряется по мере приближения к цели.
// Использует симуляцию физики с фиксированным шагом времени и интерполяцию рендера
// для поведения, независимого от частоты кадров.
class EaseInMotion : public MotionMode

{
public:
	COMPONENT_DEFINE(EaseInMotion, MotionMode);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, physicsFPS, 60.0f);	// фиксированный шаг физики
	PROP_PARAM(Float, acceleration, 3.0f);	// скорость ускорения

private:
	float physics_ifps = 1.0f / 60.0f;
	// динамические переменные
	float velocity = 0;
	// начальный дрейф
	float drift_vel = 4.0f;
	// преследователь достиг цели
	bool finished = false;

	// счётчик до следующего физического кадра
	float accumulator = 0;

	// целевая позиция
	Unigine::Math::Vec3 prev_in, cur_in;
	// позиции пружины в физическом кадре
	Unigine::Math::Vec3 prev_pos, cur_pos;

private:
	void init();
	void update();
	void on_enable() override;
	virtual Unigine::Math::Vec3 update_physics(const Unigine::Math::Vec3 &src, // исходная точка
		const Unigine::Math::Vec3 &dst,                                        // целевая точка
		Unigine::Math::Vec3 &out_dir); // направление от исходной точки к целевой

	Unigine::Math::Vec3 move_towards(const Unigine::Math::Vec3 &src, const Unigine::Math::Vec3 &dst,
		float ifps);
};