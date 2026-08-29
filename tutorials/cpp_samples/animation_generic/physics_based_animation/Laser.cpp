// Перемещает узел лазерной указки, чтобы следовать за позицией курсора мыши в мировом пространстве.
// Отправляет луч от камеры через позицию мыши, находит пересечение с миром и
// размещает лазер в этой точке (ограничено плоскостью XY).

#include "Laser.h"

#include <UnigineGame.h>
#include <UnigineObjects.h>

REGISTER_COMPONENT(Laser);

using namespace Unigine;
using namespace Math;

// Позиция лазера обновляется, чтобы следовать за курсором мыши в мировом пространстве.
void Laser::update()
{
	// Преобразуем экранные координаты мыши в 3D-направление от камеры
	PlayerPtr player = Game::getPlayer();
	ivec2 mouse_coord = Input::getMousePosition();
	Vec3 mouse_dir = Vec3(player->getDirectionFromMainWindow(mouse_coord.x, mouse_coord.y));

	// Отправляем луч от камеры через позицию мыши для поиска пересечения с миром
	Vec3 cam_pos = player->getWorldPosition();
	if (World::getIntersection(cam_pos, cam_pos + mouse_dir * player->getZFar(), ~0, intersection))
	{
		Vec3 point = intersection->getPoint();
		// Удерживаем лазер в той же горизонтальной плоскости (движение только в плоскости XY)
		point.z = node->getWorldPosition().z;
		node->setWorldPosition(point);
	}
}
