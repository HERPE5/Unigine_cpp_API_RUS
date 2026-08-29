#pragma once

#include "MotionMode.h"

#include <UnigineComponentSystem.h>

// Движение на основе пружины с использованием физики демпфированного гармонического осциллятора.
// Создаёт естественное, органичное движение с перелётом и затуханием.
// Базовый класс для вариантов SpringEasy (простой) и SpringRegular (настраиваемый).
// Использует закон Гука: F = -kx - cv (силы жёсткости и демпфирования).
class SpringMotion : public MotionMode

{
public:
	COMPONENT_DEFINE(SpringMotion, MotionMode);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, physicsFPS, 60.0f);	// фиксированный шаг физики для стабильности
	PROP_PARAM(Float, mass, 0.75f);			// влияет на частоту колебаний

protected:
	float physics_ifps = 1.0f / 60.0f;

	float idle_anim_weight = 0;
	float run_anim_time = 0;

	bool finished = false;

	// Параметры пружины: коэффициенты жёсткости (k) и демпфирования (c)
	float stiffness = 1.0f;	// выше = быстрее прилипание к цели
	float damping = 1.0f;	// выше = меньше колебаний

	// Аккумулятор фиксированного шага времени для симуляции физики
	float accumulator = 0;

	// Переменные состояния пружины
	Unigine::Math::Vec3 position;
	Unigine::Math::Vec3 velocity;

	// Интерполяция целевой позиции (для плавного движения цели)
	Unigine::Math::Vec3 prev_in, cur_in;
	// Интерполяция выходной позиции (для плавного рендеринга между шагами физики)
	Unigine::Math::Vec3 prev_out_p, cur_out_p;
	Unigine::Math::Vec3 lerped_position;

	const float distance_epsilon = 0.5f;	// порог для определения "поимки"

protected:
	void init();
	void update();
	void on_enable() override;

	virtual Unigine::Math::Vec3 update_physics(const Unigine::Math::Vec3 &src,
		const Unigine::Math::Vec3 &dst,
		bool &out_finished,
		Unigine::Math::Vec3 &out_dir);

	// Интегрирует физику пружины: применяет закон Гука с демпфированием
	void integrate_spring(const Unigine::Math::Vec3 &target_position, float ifps);

	// Производные классы должны реализовать для задания значений жёсткости/демпфирования
	virtual void refresh_spring_settings() = 0;
};