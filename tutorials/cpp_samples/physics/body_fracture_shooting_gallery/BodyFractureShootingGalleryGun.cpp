// Создаёт снаряды по клику мыши, способные разбивать разрушаемые объекты.
// Каждый снаряд загружается из файла узла, позиционируется перед оружием
// и получает начальный импульс в направлении выстрела.

#include "BodyFractureShootingGalleryGun.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(BodyFractureShootingGalleryGun);

using namespace Unigine;

void BodyFractureShootingGalleryGun::update()
{
	if (Console::isActive())
		return;

	if (Input::isMouseButtonDown(Input::MOUSE_BUTTON_LEFT))
	{
		// Загружаем снаряд из файла узла
		auto projectileNode = World::loadNode(projectile, true);
		if (!projectileNode)
			return;

		// Создаём снаряд на одну единицу впереди вдоль отрицательной оси Z оружия (вперёд)
		projectileNode->setWorldPosition(node->getWorldPosition() + Math::Vec3(node->getWorldDirection(Math::AXIS_NZ)));
		auto body = projectileNode->getObjectBodyRigid();
		if (!body)
			return;

		// Применяем мгновенную скорость в направлении выстрела
		body->addLinearImpulse(node->getWorldDirection(Math::AXIS_NZ) * force);
	}
}
