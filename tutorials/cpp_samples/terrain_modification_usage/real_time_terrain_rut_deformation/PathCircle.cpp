// Перемещает узел по круговому пути, комбинируя движение вперёд и вращение.
// Speed управляет линейной скоростью; angular_speed управляет скоростью поворота.
// Используется для симуляции транспортных средств, оставляющих следы на terrain.

#include "PathCircle.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(PathCircle);

using namespace Unigine;
using namespace Math;

// Позиция и поворот обновляются каждый кадр на основе параметров скорости.
void PathCircle::update()
{
	// Поворот увеличивается вокруг оси Z на основе угловой скорости
	quat new_rotation = node->getRotation() * quat(0.0f, 0.0f, angular_speed.get() * Game::getIFps());

	// Позиция перемещается вперёд вдоль оси Y на основе линейной скорости
	Vec3 new_position = node->getPosition() + Vec3(node->getDirection(AXIS::AXIS_Y)) * speed.get() * Game::getIFps();

	// Трансформация составляется и применяется к узлу
	Mat4 new_transform;
	composeTransform(new_transform, new_position, new_rotation, vec3_one);
	node->setTransform(new_transform);
}
