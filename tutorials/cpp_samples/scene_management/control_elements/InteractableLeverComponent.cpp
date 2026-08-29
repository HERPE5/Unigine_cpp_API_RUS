// Элемент управления "рычаг", вращающийся вокруг настраиваемой оси.
// Направление взгляда игрока проецируется на плоскость вращения для вычисления целевого угла.
// Плавная интерполяция применяется каждый кадр, пока рычаг не достигнет целевого положения.

#include "InteractableLeverComponent.h"
#include "UnigineVisualizer.h"
REGISTER_COMPONENT(InteractableLeverComponent);

using namespace Unigine;
using namespace Math;

// Порог, ниже которого разница углов считается незначительной
const float angle_eps = 0.05f;

// Оси плоскости вращения вычисляются из ориентации узла трансформации.
void InteractableLeverComponent::init()
{
	// По умолчанию используем узел компонента, если явная цель трансформации не задана
	if (!transformation_node)
		transformation_node = node;

	// Убеждаемся, что ось вращения имеет единичную длину
	rotation_axis = normalize(rotation_axis.get());
	// Строим ортонормированный базис для плоскости вращения
	valve_plane_x = (vec3)transformation_node->getWorldDirection(AXIS_Z).normalize();
	valve_plane_normal = (transformation_node->getWorldRotation() * rotation_axis).normalize();
	valve_plane_y = cross(valve_plane_normal, valve_plane_x).normalize();
	// Сохраняем исходную ориентацию для применения относительного поворота
	initial_rotation = transformation_node->getWorldRotation();
}

// Направление взгляда игрока и позиция захватываются для расчёта проекции.
void InteractableLeverComponent::use(Unigine::PlayerPtr player, Unigine::Math::vec3 intersection_point)
{
	used_current_frame = true;
	player_view_direction = player->getViewDirection();
	player_position = (vec3)player->getWorldPosition();
}

// Плоскость вращения обновляется, рычаг интерполируется к целевому углу.
void InteractableLeverComponent::update()
{
	// Пересчитываем базис плоскости вращения каждый кадр для подвижных рычагов
	if (is_movable)
	{
		valve_plane_normal = (transformation_node->getWorldRotation() * rotation_axis).normalize();
		valve_plane_x = (quat(valve_plane_normal, -rotation_angle) * (vec3)transformation_node->getWorldDirection(AXIS_Z)).normalize();
		valve_plane_y = cross(valve_plane_normal, valve_plane_x).normalize();
	}

	// Проецируем взгляд игрока на плоскость вращения, когда взаимодействие активно
	if (used_current_frame)
	{
		lever_position = (vec3)transformation_node->getWorldPosition();
		// Продлеваем луч взгляда игрока до расстояния рычага и вычисляем направление
		player_vec = (player_position + player_view_direction * (player_position - lever_position).length()) - lever_position;

		// Проецируем на плоскость вращения, чтобы получить целевое направление
		rotation_vec = valve_plane_x * dot(valve_plane_x, player_vec) + valve_plane_y * dot(valve_plane_y, player_vec);
		rotation_vec.normalize();
	}

	// Плавно интерполируем к целевому углу во время взаимодействия или установки
	if (Math::abs(rotation_angle - rotation_angle_target) > angle_eps || used_current_frame)
	{
		// Вычисляем угол между осью X плоскости и вектором вращения
		rotation_angle_target = getAngle(valve_plane_x, rotation_vec, vec3(valve_plane_normal));
		rotation_angle_target = clamp(rotation_angle_target, 0.0f, rotation_angle_range);
		// Линейная интерполяция обеспечивает плавное движение
		rotation_angle = lerp(rotation_angle, rotation_angle_target, 0.2f);
		transformation_node->setRotation(initial_rotation * quat(rotation_axis, rotation_angle));
	}

	// Сбрасываем флаги кадра после обработки
	if (used_current_frame)
	{
		rotation_vec_old = rotation_vec;
		used_last_frame = used_current_frame;
		used_current_frame = false;
	}
}

// Возвращается нормализованное положение рычага (0 = начало, 1 = полный диапазон).
float InteractableLeverComponent::getValue()
{
	return rotation_angle / rotation_angle_range;
}