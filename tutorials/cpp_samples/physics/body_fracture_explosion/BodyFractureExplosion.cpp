// Симулирует расширяющийся сферический взрыв, прикладывающий направленные наружу силы к
// близлежащим твёрдым телам и запускающий разрушение разрушаемых объектов.
// Взрыв расширяется со временем, сила уменьшается по мере роста
// радиуса (обратное затухание от центра).

#include "BodyFractureExplosion.h"
#include "../../utils/BodyFractureUnit.h"
#include "UnigineMathLibVec4.h"
#include <UniginePhysics.h>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(BodyFractureExplosion);

using namespace Unigine;

void BodyFractureExplosion::explode()
{
	isExploding = true;
}

void BodyFractureExplosion::init()
{
	radius = 0;
	isExploding = false;

	visualizer_enabled = Visualizer::isEnabled();
	Visualizer::setEnabled(true);
}

void BodyFractureExplosion::updatePhysics()
{
	if (!isExploding)
		return;

	// Создаём сферическую область запроса на текущем радиусе взрыва
	Math::BoundSphere bound(Math::vec3(node->getWorldPosition()), radius);

	if (debug)
		Visualizer::renderBoundSphere(bound, Math::Mat4_identity, Math::vec4_red, 0.1f);

	// Сила линейно уменьшается по мере расширения взрыва (сильнее ближе к центру)
	auto actualPower = power * (1 - radius / max_radius);

	// Запрашиваем все объекты, пересекающие сферу взрыва
	Vector<ObjectPtr> objects;
	if (World::getIntersection(bound, objects))
	{
		for (auto object : objects)
		{
			auto body = object->getBody();
			if (!body)
				continue;

			// Вычисляем направление наружу от центра взрыва к объекту
			auto dir = Math::vec3(object->getWorldPosition() - node->getWorldPosition());
			dir.normalizeValid();

			if (debug)
				Visualizer::renderDirection(object->getWorldPosition(), dir, Math::vec4_blue, 0.25f, true, 0.8f, false);

			// Запускаем разрушение разрушаемых объектов (направление удара внутрь)
			if (auto fractureUnit = getComponent<BodyFractureUnit>(object))
			{
				fractureUnit->crack(actualPower, object->getWorldPosition(), -dir);
			}

			// Отталкиваем твёрдые тела наружу от центра взрыва
			if (auto rigidBody = checked_ptr_cast<BodyRigid>(body))
			{
				rigidBody->addForce(dir * actualPower);
			}
		}
	}

	// Расширяем радиус взрыва со временем, масштабированный шагом физики
	radius = Math::min(radius + speed * Physics::getIFps(), max_radius);
	if (radius >= max_radius)
	{
		radius = 0;
		isExploding = false;
	}
}

void BodyFractureExplosion::shutdown()
{
	Visualizer::setEnabled(visualizer_enabled);
}
