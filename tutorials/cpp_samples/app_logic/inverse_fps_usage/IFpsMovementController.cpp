// Сравнивает движение, зависящее и независящее от частоты кадров. Когда use_ifps равно true,
// движение масштабируется через Game::getIFps() для постоянной скорости независимо от FPS.
// Без масштабирования IFps скорость движения меняется вместе с частотой кадров.

#include "IFpsMovementController.h"

#include <Unigine.h>
#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(IFpsMovementController);

// Узел перемещается вдоль оси X; направление меняется на границах.
void IFpsMovementController::update()
{
	// С IFps: расстояние = скорость * deltaTime (постоянно независимо от FPS)
	// Без: расстояние = скорость за кадр (быстрее при более высоком FPS)
	if (use_ifps)
	{
		node->translate(current_dir * movement_speed * Game::getIFps());
	}
	else {
		node->translate(current_dir * movement_speed);
	}

	// Направление меняется на противоположное, когда узел достигает граничных пределов
	if (node->getWorldPosition().x > 5)
		current_dir = Vec3_left;
	if (node->getWorldPosition().x < -5)
		current_dir = Vec3_right;
}