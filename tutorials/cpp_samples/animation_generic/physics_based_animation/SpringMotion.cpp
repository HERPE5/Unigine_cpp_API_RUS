// Реализует движение на основе пружины с симуляцией физики фиксированным шагом времени.
// Использует паттерн аккумулятора для физики, независимой от частоты кадров, и интерполирует
// между шагами физики для плавного рендеринга. Пружина следует закону Гука.

#include "SpringMotion.h"

#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

// Инициализируются базовый класс и настройки пружины, затем компонент включается.
void SpringMotion::init()
{
	MotionMode::init();
	physics_ifps = 1.0f / physicsFPS;
	refresh_spring_settings();
	on_enable();
}

// Позиция преследователя обновляется с использованием физики пружины, применяется анимация.
void SpringMotion::update()
{
	Vec3 cur_pos = persecutor->getPosition();
	Vec3 prev_pos = cur_pos;
	Vec3 target_pos = targetNode.get()->getWorldPosition();
	// Выравниваем цель по плоскости преследователя
	target_pos.z = cur_pos.z;

	// Вычисляем новую позицию и направление преследователя
	finished = false;
	Vec3 target_dir;
	cur_pos = update_physics(cur_pos, target_pos, finished, target_dir);

	// Применяем вычисления к преследователю
	if (!finished)
		persecutor->setRotation(target_dir);

	persecutor->setPosition(cur_pos);

	float real_speed = (float)length(cur_pos - prev_pos) / Game::getIFps();
	persecutor->setAnimation(real_speed, finished);
}

// Вызывается при активации компонента. Состояние пружины сбрасывается к текущей позиции.
void SpringMotion::on_enable()
{
	// Обновляем позицию преследователя, чтобы продолжить движение с последней точки
	cur_out_p = persecutor->getPosition();
	prev_out_p = cur_out_p;
	position = cur_out_p;
	velocity = Vec3_zero;
}

// Симулируется физика пружины с фиксированным шагом времени с использованием паттерна аккумулятора.
Vec3 SpringMotion::update_physics(const Vec3 &src, const Vec3 &dst, bool &out_finished,
	Vec3 &out_dir)
{
	Vec3 offset = dst - src;
	float dist = (float)length(offset);
	if (dist > 0)
		out_dir = offset / dist;

	out_finished = dist < distance_epsilon;

	float ifps = Game::getIFps();
	// Ограничиваем delta time, чтобы избежать "спирали смерти" при всплесках частоты кадров
	ifps = min(ifps, 0.25f);

	// Паттерн аккумулятора с фиксированным шагом времени для детерминированной физики
	accumulator += ifps;
	if (accumulator >= physics_ifps)
	{
		// Сохраняем предыдущую и текущую цель для интерполяции ввода
		prev_in = cur_in;
		cur_in = dst;

		// Выполняем несколько шагов физики при необходимости (навёрстывание)
		int steps = ftoi(Math::floor(accumulator / physics_ifps));
		for (int i = 0; i < steps; i++)
		{
			// Интерполируем целевую позицию для субкадровой точности
			float alpha_in = itof(i + 1) / steps;

			prev_out_p = cur_out_p;
			integrate_spring(lerp(prev_in, cur_in, alpha_in), physics_ifps);
			cur_out_p = position;
		}
		accumulator -= steps * physics_ifps;
	}

	// Интерполируем между кадрами физики для плавного рендеринга
	float alpha_out = accumulator / physics_ifps;
	lerped_position = lerp(prev_out_p, cur_out_p, alpha_out);

	return lerped_position;
}

// Интегрируется один шаг физики пружины с использованием закона Гука и демпфирования.
void SpringMotion::integrate_spring(const Unigine::Math::Vec3 &target_position, float ifps)
{
	// Закон Гука: F_spring = -k * x (смещение от цели)
	Vec3 force_spring = (target_position - position) * stiffness;
	// Сила демпфирования: F_damping = -c * v (противодействует скорости)
	Vec3 force_damping = -velocity * damping;
	// Второй закон Ньютона: a = F/m
	Vec3 acceleration = (force_spring + force_damping) / mass;

	// Полунеявное интегрирование Эйлера (симплектическое): более стабильно, чем явный метод Эйлера
	velocity += acceleration * ifps;
	position += velocity * ifps;
}
