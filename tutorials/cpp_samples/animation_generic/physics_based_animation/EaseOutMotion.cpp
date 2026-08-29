// Реализует экспоненциальное движение ease-out, при котором объект замедляется по мере
// приближения к цели. Использует exp(-speed * dt) для асимптотического приближения, которое
// быстро покрывает большую часть расстояния, а затем плавно замедляется рядом с целью.

#include "EaseOutMotion.h"

#include <UnigineGame.h>
#include <UnigineObjects.h>

REGISTER_COMPONENT(EaseOutMotion);

using namespace Unigine;
using namespace Math;

// Позиция преследователя обновляется с использованием экспоненциальной интерполяции ease-out.
void EaseOutMotion::update()
{
	Vec3 cur_pos = persecutor->getPosition();
	Vec3 prev_pos = cur_pos;
	Vec3 target_pos = targetNode.get()->getWorldPosition();
	// Выравниваем цель по плоскости преследователя
	target_pos.z = cur_pos.z;

	// Вычисляем новую позицию и направление преследователя
	bool finished = true;
	Vec3 target_dir;
	cur_pos = move_towards(cur_pos, target_pos, speed, finished, target_dir);

	// Применяем вычисления к преследователю
	if (!finished)
		persecutor->setRotation(target_dir);

	persecutor->setPosition(cur_pos);

	float real_speed = (float)length(cur_pos - prev_pos) / Game::getIFps();
	persecutor->setAnimation(real_speed, finished);
}

// Вычисляется экспоненциальная интерполяция к цели. Расстояние уменьшается асимптотически.
Vec3 EaseOutMotion::move_towards(const Vec3 &src, const Vec3 &dst, float speed, bool &out_finished,
	Vec3 &out_dir)
{
	Vec3 offset = dst - src;
	float dist = (float)length(offset);
	if (dist > 0)
		out_dir = offset / dist;

	out_finished = dist < distance_epsilon;

	// Экспоненциальный ease-out: быстро покрывает большую часть расстояния, затем замедляется.
	// Член exp(-speed * dt) создаёт асимптотическое приближение к цели.
	return lerp(src, dst, 1.0f - Math::exp(-speed * Game::getIFps()));
}
