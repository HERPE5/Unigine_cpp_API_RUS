// Расширяет SpringMotion поведением отскока при пересечении цели. Когда
// преследователь пересекает воображаемую "стену" рядом с целью (в пределах bounceRadius), его
// скорость реверсируется для создания эффекта упругого отскока.

#include "EaseOutBounceMotion.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(EaseOutBounceMotion);

using namespace Unigine;
using namespace Math;

// Выполняется физика пружины с определением отскока. Скорость реверсируется при пересечении плоскости стены.
Vec3 EaseOutBounceMotion::update_physics(const Vec3 &src, const Vec3 &dst, bool &out_finished,
	Vec3 &out_dir)
{
	// Находим расстояние и направление до цели
	Vec3 offset = dst - src;
	float dist = (float)length(offset);
	if (dist > 0)
		out_dir = offset / dist;

	out_finished = dist < distance_epsilon;

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

		// Цель переместилась
		if (prev_in != cur_in)
		{
			// Вычисляем нормаль цели
			wall_normal = normalize(prev_in - cur_in);
			if (dot(normalize(position - cur_in), wall_normal) < 0)
				wall_normal = -wall_normal;
		}

		// Обновляем физику
		int steps = ftoi(Math::floor(accumulator / physics_ifps));
		for (int i = 0; i < steps; i++)
		{
			// Интерполируем ввод для каждого физического кадра: (0, 1]
			float alpha_in = itof(i + 1) / steps;
			Vec3 target_position = lerp(prev_in, cur_in, alpha_in);

			prev_out_p = cur_out_p;
			integrate_spring(target_position, physics_ifps);

			// Определение отскока: когда преследователь пересекает "стену" рядом с целью
			Vec3 dir_to_cat_from_target = normalize(position - target_position);
			if (dot(dir_to_cat_from_target, wall_normal) < 0.0
				&& length2(position - target_position) < bounceRadius * bounceRadius)
				velocity = -velocity;	// реверсируем скорость для создания эффекта отскока

			// Пересчитываем позицию после применения эффекта отскока
			new_position += velocity * physics_ifps;
			position = new_position;

			cur_out_p = position;
		}
		// Сбрасываем счётчик
		accumulator -= steps * physics_ifps;
	}

	// Интерполируем выходную позицию
	float alpha_out = accumulator / physics_ifps;
	lerped_position = lerp(prev_out_p, cur_out_p, alpha_out);

	return lerped_position;
}

// Вызывается при активации компонента. Родительское состояние пружины и позиция отскока сбрасываются.
void EaseOutBounceMotion::on_enable()
{
	SpringMotion::on_enable();
	new_position = position;
}
