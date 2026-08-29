// Элемент управления "вентиль", вращающийся вокруг своей оси Z на основе движения захвата игрока.
// Точка захвата отслеживает направление взгляда игрока, спроецированное на плоскость вентиля.
// Угол поворота вычисляется из угловой разницы между последовательными позициями захвата.

#include "InteractableValveComponent.h"

#include "UnigineVisualizer.h"
REGISTER_COMPONENT(InteractableValveComponent);

using namespace Unigine;
using namespace Math;

// Порог для остановки интерполяции, когда целевой угол почти достигнут
const float angle_eps = 0.05f;

// Оси плоскости вентиля захватываются из ориентации узла трансформации.
void InteractableValveComponent::init()
{
	// По умолчанию используем узел компонента, если явная цель трансформации не задана
	if (!transformation_node)
	{
		transformation_node = node;
	}

	// Строим ортонормированный базис для плоскости вращения вентиля
	valve_plane_x = (vec3)transformation_node->getWorldDirection(AXIS_X).normalize();
	valve_plane_y = (vec3)transformation_node->getWorldDirection(AXIS_Y).normalize();
	valve_plane_normal = (vec3)transformation_node->getWorldDirection(AXIS_Z).normalize();

	// Инициализируем взглядом и захватом по умолчанию в центре вентиля
	player_view_direction = valve_plane_y;
	grab_point = (vec3)transformation_node->getWorldPosition();
}

// Точка захвата захватывается и проецируется на плоскость вентиля для начального кадра.
void InteractableValveComponent::use(Unigine::PlayerPtr player,
	Unigine::Math::vec3 intersection_point)
{
	used_current_frame = true;
	player_view_direction = player->getViewDirection();
	player_position = (vec3)player->getWorldPosition();

	grab_point = intersection_point;
	// На первом кадре захвата фиксируем исходное направление захвата на плоскости вентиля
	if (!used_last_frame)
	{
		vec3 grab_vec = (grab_point - (vec3)transformation_node->getWorldPosition());
		grab_vec_old = valve_plane_x * dot(valve_plane_x, grab_vec)
			+ valve_plane_y * dot(valve_plane_y, grab_vec);
	}
}

// Угловая дельта между позициями захвата приводит вращение к целевому углу.
void InteractableValveComponent::update()
{
	// Пересчитываем базис плоскости вентиля каждый кадр для подвижных вентилей
	if (is_movable)
	{
		valve_plane_x = (vec3)transformation_node->getWorldDirection(AXIS_X).normalize();
		valve_plane_y = (vec3)transformation_node->getWorldDirection(AXIS_Y).normalize();
		valve_plane_normal = (vec3)transformation_node->getWorldDirection(AXIS_Z).normalize();
	}
	// Проецируем текущую позицию захвата на плоскость вентиля
	if (used_current_frame)
	{
		vec3 valve_position = (vec3)transformation_node->getWorldPosition();
		// Продлеваем луч взгляда игрока до расстояния вентиля
		grab_vec = (player_position
					   + player_view_direction * (player_position - valve_position).length())
			- valve_position;

		// Проецируем на плоскость вентиля, чтобы получить направление вращения
		rotation_vec = valve_plane_x * dot(valve_plane_x, grab_vec)
			+ valve_plane_y * dot(valve_plane_y, grab_vec);
		rotation_vec.normalize();
	}
	// Плавно интерполируем к цели во время взаимодействия или установки
	if (Math::abs(rotation_angle - rotation_angle_target) > angle_eps || used_current_frame)
	{
		// Накапливаем угловую дельту между последовательными направлениями захвата
		rotation_angle_target += getAngle(vec3(grab_vec_old), vec3(rotation_vec),
			vec3(valve_plane_normal));
		rotation_angle_target = clamp(rotation_angle_target, 0.0f, rotation_angle_range);
		rotation_angle = lerp(rotation_angle, rotation_angle_target, 0.1f);

		transformation_node->setRotation(
			quat(vec3(transformation_node->getDirection(AXIS_Z)), rotation_angle));
	}
	// Сохраняем текущий захват для вычисления дельты в следующем кадре
	grab_vec_old = rotation_vec;
	used_last_frame = used_current_frame;
	used_current_frame = false;
}

// Возвращается нормализованное положение вентиля (0 = начало, 1 = полный диапазон).
float InteractableValveComponent::getValue()
{
	return rotation_angle / rotation_angle_range;
}
