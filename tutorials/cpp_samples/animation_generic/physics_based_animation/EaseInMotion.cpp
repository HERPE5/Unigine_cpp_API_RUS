// Реализует движение ease-in с постоянным ускорением. Объект начинает медленно и
// постепенно ускоряется по мере движения к цели. Использует физику с фиксированным шагом
// времени и паттерн аккумулятора для движения, независимого от частоты кадров.

#include "EaseInMotion.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(EaseInMotion);

using namespace Unigine;
using namespace Math;

// Базовый класс инициализируется, настраивается шаг физики.
void EaseInMotion::init()
{
	MotionMode::init();
	on_enable();
	physics_ifps = 1.0f / physicsFPS;
}

// Позиция преследователя обновляется с использованием физики ease-in, применяется анимация.
void EaseInMotion::update()
{
	Vec3 cur_pos = persecutor->getPosition();
	Vec3 target_pos = targetNode.get()->getWorldPosition();
	// Выравниваем цель по плоскости преследователя
	target_pos.z = cur_pos.z;

	// Вычисляем новую позицию и направление преследователя
	Vec3 target_dir;
	cur_pos = update_physics(cur_pos, target_pos, target_dir);

	// Применяем вычисления к преследователю
	if (!finished)
		persecutor->setRotation(target_dir);

	persecutor->setPosition(cur_pos);

	float speed = Math::max(drift_vel, velocity);
	persecutor->setAnimation(speed, finished);
}

// Вызывается при активации компонента. Позиция и скорость сбрасываются.
void EaseInMotion::on_enable()
{
	cur_pos = persecutor->getPosition();
	velocity = 0;
	prev_pos = cur_pos;
}

// Выполняется симуляция физики с фиксированным шагом времени с использованием паттерна аккумулятора.
Vec3 EaseInMotion::update_physics(const Vec3 &src, const Vec3 &dst, Vec3 &out_dir)
{
	// Находим расстояние и направление до целевой точки
	Vec3 offset = dst - src;
	float dist = (float)length(offset);
	if (dist > 0)
		out_dir = offset / dist;


	float ifps = Game::getIFps();
	// Избегаем "спирали смерти"
	ifps = min(ifps, 0.25f);

	accumulator += ifps;
	// Проверяем, достигли ли мы следующего физического кадра
	if (accumulator >= physics_ifps)
	{
		// Обновляем ввод
		prev_in = cur_in;
		cur_in = dst;

		// Обновляем физику
		int steps = ftoi(Math::floor(accumulator / physics_ifps));
		for (int i = 0; i < steps; i++)
		{
			// Интерполируем ввод для каждого физического кадра: (0, 1]
			float alpha_in = itof(i + 1) / steps;

			prev_pos = cur_pos;
			cur_pos = move_towards(cur_pos, lerp(prev_in, cur_in, alpha_in), physics_ifps);
		}
		// Сбрасываем счётчик
		accumulator -= steps * physics_ifps;
	}

	// Возвращаем линейно интерполированную позицию для плавного рендеринга
	return lerp(prev_pos, cur_pos, accumulator / physics_ifps);
}

// Выполняется один шаг физики с постоянным ускорением.
Vec3 EaseInMotion::move_towards(const Vec3 &src, const Vec3 &dst, float ifps)
{
	Vec3 target_dir;

	// Постоянное ускорение: скорость линейно возрастает со временем
	velocity += acceleration * ifps;
	float step = velocity * ifps;

	Vec3 offset = dst - src;
	float dist = (float)length(offset);

	// Прилипаем к цели, если достаточно близко
	if (dist <= step)
	{
		finished = true;
		if (dist > 0)
			target_dir = offset / dist;
		velocity = 0;
		return dst;
	}

	finished = false;
	target_dir = offset / dist;
	return src + target_dir * step;
}