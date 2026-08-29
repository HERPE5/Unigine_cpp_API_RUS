// Система взаимодействия игрока с использованием трассировки лучей. Нажатие F инициирует взаимодействие с
// объектами, у которых есть компонент Interactable и подходящая маска пересечения. Удержание
// F продолжает взаимодействие, позволяя непрерывно манипулировать рычагами и вентилями.

#include "InteractorComponent.h"

#include "UnigineVisualizer.h"

REGISTER_COMPONENT(InteractorComponent);

using namespace Unigine;
using namespace Math;

// Максимальная дистанция трассировки луча для обнаружения интерактивных объектов
const float interaction_distance = 10;

// Захватывается мышь и проверяется ссылка на игрока.
void InteractorComponent::init()
{
	mouse_handle = Input::getMouseHandle();
	Visualizer::setEnabled(true);

	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);

	player = checked_ptr_cast<Player>(node);
	if (!player)
	{
		Log::error("InteractorComponent::init: this component should be placed only on Player "
				   "node. '%s'%d\n",
			node->getName(), node->getID());
		return;
	}
}

// Трассировка луча выполняется по клавише F; взаимодействие продолжается, пока клавиша удерживается.
void InteractorComponent::update()
{
	// Блокируемся на объекте при первом нажатии F
	if (Input::isKeyDown(Input::KEY_F))
	{
		ivec2 mouse = Input::getMousePosition();
		Vec3 p0 = player->getWorldPosition();
		Vec3 p1 = p0
			+ Vec3(player->getDirectionFromMainWindow(mouse.x, mouse.y)) * interaction_distance;

		obj = World::getIntersection(p0, p1, interactable_intersection_mask.get(), intersection);
	}
	// Продолжаем взаимодействие, пока F удерживается
	if (Input::isKeyPressed(Input::KEY_F))
	{
		if (obj)
		{
			// Трассировка со всеми масками для получения точной точки пересечения
			ivec2 mouse = Input::getMousePosition();
			Vec3 p0 = player->getWorldPosition();
			Vec3 p1 = p0
				+ Vec3(player->getDirectionFromMainWindow(mouse.x, mouse.y)) * interaction_distance;

			World::getIntersection(p0, p1, ~0, intersection);
			comp_interactable = ComponentSystem::get()->getComponent<Interactable>(obj);
			if (comp_interactable)
			{
				comp_interactable->use(player, (vec3)intersection->getPoint());
			}
		}
	}
	// Отпускаем объект при отпускании F
	if (Input::isKeyUp(Input::KEY_F))
	{
		obj = nullptr;
	}
}

// Вектор направления взгляда визуализируется для отладки.
void InteractorComponent::post_update()
{
	Visualizer::renderVector(player->getWorldPosition(),
		player->getWorldPosition() + (Vec3)player->getViewDirection(), vec4_white, 0.015f, false,
		0.0f, false);
}

// Визуализатор отключается, режим мыши восстанавливается.
void InteractorComponent::shutdown()
{
	Visualizer::setEnabled(false);
	Input::setMouseHandle(mouse_handle);
}
