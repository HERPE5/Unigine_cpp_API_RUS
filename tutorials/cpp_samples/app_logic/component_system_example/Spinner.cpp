// Вращающаяся турель, создающая снаряды через случайные интервалы. Демонстрирует три
// способа изменения параметров компонента: прямой доступ из C++, поиск свойства узла
// и ссылку на свойство компонента. Сложность увеличивается со временем через частоту спавна.

#include "Spinner.h"

#include "Projectile.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(Spinner);

using namespace Unigine;
using namespace Math;

// Материал кешируется, случайные параметры спавна/цвета инициализируются.
void Spinner::init()
{
	// Получаем текущий материал (с первой поверхности)
	ObjectPtr obj = checked_ptr_cast<Object>(node);
	if (obj && obj->getNumSurfaces() > 0)
		material = obj->getMaterialInherit(0);

	// Инициализируем случайные значения
	time_to_spawn = Game::getRandomFloat(min_spawn_delay, max_spawn_delay);
	color_offset = Game::getRandomFloat(0, 360.0f);
	start_turn_speed = turn_speed;
}

// Применяется вращение, циклически меняется цвет, через интервалы создаются снаряды.
void Spinner::update()
{
	// Вращаем волчок
	float ifps = Game::getIFps();
	turn_speed = turn_speed + acceleration * ifps;
	node->setRotation(node->getRotation() * quat(0, 0, turn_speed * ifps));

	// Меняем цвет
	int id = material->findParameter("albedo_color");
	if (id != -1)
	{
		float hue = Math::mod(Game::getTime() * 60.0f + color_offset, 360.0f);
		material->setParameterFloat4(id, vec4(hsv2rgb(hue, 1, 1), 1.0f));
	}

	// Создаём снаряды
	time_to_spawn -= ifps;
	if (time_to_spawn < 0 && spawn_node.get())
	{
		// Сбрасываем таймер и увеличиваем сложность
		time_to_spawn = Game::getRandomFloat(min_spawn_delay, max_spawn_delay)
			/ (turn_speed / start_turn_speed);

		// Создаём узел
		NodePtr spawned = spawn_node.get()->clone();
		spawned->setEnabled(1);
		spawned->setWorldTransform(node->getWorldTransform());

		// Создаём компонент
		Projectile *proj_component = addComponent<Projectile>(spawned);

		// Три паттерна изменения параметров компонента:
		// 1) Прямой доступ из C++ (самый быстрый, типобезопасный)
		proj_component->speed = Game::getRandomFloat(proj_component->speed * 0.5f,
			proj_component->speed * 1.5f);

		// 2) Через список свойств узла (медленнее, для динамического поиска по имени)
		for (int i = 0; i < spawned->getNumProperties(); i++)
		{
			PropertyPtr prop = spawned->getProperty(i);
			if (prop && (!strcmp(prop->getName(), "Projectile") || prop->isParent("Projectile")))
				prop->getParameterPtr("damage")->setValueInt(Game::getRandomInt(75, 100));
		}

		// 3) Через ссылку на свойство компонента (чище, чем #2)
		PropertyPtr proj_property = proj_component->getProperty();
		proj_property->getParameterPtr("lifetime")
			->setValueFloat(Game::getRandomFloat(5.0f, 10.0f));

		// Вызываем публичный метод другого компонента
		proj_component->setMaterial(material);
	}
}

// Цвет HSV преобразуется в RGB. H: [0, 360), S,V: [0, 1].
vec3 Spinner::hsv2rgb(float h, float s, float v)
{
	float p, q, t, fract;

	h /= 60.0f;
	fract = h - Math::floor(h);

	p = v * (1.0f - s);
	q = v * (1.0f - s * fract);
	t = v * (1.0f - s * (1.0f - fract));

	if (0.0f <= h && h < 1.0f) return vec3(v, t, p);
	else if (1.0f <= h && h < 2.0f) return vec3(q, v, p);
	else if (2.0f <= h && h < 3.0f) return vec3(p, v, t);
	else if (3.0f <= h && h < 4.0f) return vec3(p, q, v);
	else if (4.0f <= h && h < 5.0f) return vec3(t, p, v);
	else if (5.0f <= h && h < 6.0f) return vec3(v, p, q);
	else return vec3(0, 0, 0);
}
