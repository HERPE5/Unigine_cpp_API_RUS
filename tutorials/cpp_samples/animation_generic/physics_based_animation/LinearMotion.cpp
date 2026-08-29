// Реализует линейное движение к цели с постоянной скоростью. Простейший тип
// движения: перемещается с фиксированной скоростью независимо от расстояния, прилипая к цели,
// когда расстояние до неё не превышает одного шага.

#include "LinearMotion.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(LinearMotion);

using namespace Unigine;
using namespace Math;

// Позиция преследователя обновляется с использованием линейной интерполяции с постоянной скоростью.
void LinearMotion::update()
{
	Vec3 cur_pos = persecutor->getPosition();
	Vec3 target_pos = targetNode.get()->getWorldPosition();
	// Выравниваем цель по плоскости преследователя
	target_pos.z = cur_pos.z;

	bool finished = true;
	Vec3 target_dir;
	float step = speed * Game::getIFps();
	cur_pos = move_towards(cur_pos, target_pos, step, finished, target_dir);

	// Применяем вычисления к преследователю
	if (!finished)
		persecutor->setRotation(target_dir);

	persecutor->setPosition(cur_pos);
	persecutor->setAnimation(speed, finished);
}

// Новая позиция вычисляется путём перемещения к цели с постоянной скоростью.
Vec3 LinearMotion::move_towards(const Vec3 &src, const Vec3 &dst, float step, bool &out_finished,
	Vec3 &out_dir)
{
	// Линейная интерполяция: движение к цели с постоянной скоростью
	Vec3 offset = dst - src;
	float dist = (float)length(offset);

	// Прилипаем к цели, если расстояние не превышает одного шага
	if (dist <= step)
	{
		out_finished = true;
		if (dist > 0)
			out_dir = offset / dist;
		return dst;
	}

	// Перемещаемся ровно на 'step' единиц к цели
	out_finished = false;
	out_dir = offset / dist;
	return src + out_dir * step;
}