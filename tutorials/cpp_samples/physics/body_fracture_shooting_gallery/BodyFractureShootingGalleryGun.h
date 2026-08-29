// Создаёт снаряды по клику мыши, способные разбивать разрушаемые объекты.
// Каждый снаряд загружается из файла узла, позиционируется в месте нахождения оружия
// и получает начальный импульс в направлении выстрела.

#pragma once
#include <UnigineComponentSystem.h>

class BodyFractureShootingGalleryGun
	: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(BodyFractureShootingGalleryGun, Unigine::ComponentBase);
	COMPONENT_UPDATE(update);

	// Файл узла (.node), содержащий префаб снаряда
	PROP_PARAM(File, projectile);
	// Величина импульса, применяемая к снаряду при создании
	PROP_PARAM(Float, force, 10.0f);

private:
	void update();
};
