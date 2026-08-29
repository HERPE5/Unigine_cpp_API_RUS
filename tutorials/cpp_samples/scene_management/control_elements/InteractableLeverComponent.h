// Элемент управления "рычаг", вращающийся вокруг настраиваемой оси.
// Направление взгляда игрока проецируется на плоскость вращения для вычисления угла.
// Поддерживает плавную интерполяцию к целевому углу.

#pragma once
#include "Interactable.h"
#include <UnigineComponentSystem.h>

// Вращает узел на основе направления взгляда игрока, спроецированного на плоскость вращения.
class InteractableLeverComponent
	: public Interactable
	, public Unigine::ComponentBase
{
public:
	COMPONENT(InteractableLeverComponent, ComponentBase);
	PROP_NAME("InteractableLeverComponent");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update, Interactable::interactable_update_priority);

	// Локальная ось, вокруг которой вращается рычаг
	PROP_PARAM(Vec3, rotation_axis, Unigine::Math::vec3(1, 0, 0));
	// Максимальный угол поворота от центрального положения в градусах
	PROP_PARAM(Float, rotation_angle_range, 90.0f);
	// Узел, получающий трансформацию поворота (может отличаться от узла компонента)
	PROP_PARAM(Node, transformation_node);
	// Может ли игрок в данный момент манипулировать рычагом
	PROP_PARAM(Toggle, is_movable, true);

	void use(Unigine::PlayerPtr player, Unigine::Math::vec3 intersection_point) override;
	float getValue() override;

private:
	void init();
	void update();

	// Мировая позиция точки опоры рычага
	Unigine::Math::vec3 lever_position;
	// Точка, в которой игрок захватил рычаг
	Unigine::Math::vec3 grab_point;
	// Направление от рычага к позиции игрока
	Unigine::Math::vec3 player_vec;

	// Текущий вектор направления вращения на плоскости вращения
	Unigine::Math::vec3 rotation_vec;
	// Целевое направление вращения на основе взгляда игрока
	Unigine::Math::vec3 rotation_target_vec;
	// Вектор вращения предыдущего кадра для интерполяции
	Unigine::Math::vec3 rotation_vec_old;
	// Ось X плоскости вращения (перпендикулярна оси вращения)
	Unigine::Math::vec3 valve_plane_x;
	// Ось Y плоскости вращения (перпендикулярна оси вращения)
	Unigine::Math::vec3 valve_plane_y;
	// Нормаль плоскости вращения (совпадает с направлением оси вращения)
	Unigine::Math::vec3 valve_plane_normal;

	// Направление взгляда игрока в мировом пространстве
	Unigine::Math::vec3 player_view_direction;
	// Позиция камеры игрока в мировом пространстве
	Unigine::Math::vec3 player_position;

	// Исходное направление рычага, когда он не захвачен
	Unigine::Math::vec3 lever_direction_off;
	// Исходный поворот, сохранённый для вычисления дельты
	Unigine::Math::quat initial_rotation;

	// Текущий угол поворота рычага в градусах
	float rotation_angle = 0.0f;
	// Целевой угол, вычисленный из проекции взгляда игрока
	float rotation_angle_target = 0.0f;
	// Целевой угол предыдущего кадра для сглаживания
	float rotation_angle_target_old = 0.0f;

	// Отслеживает, использовался ли рычаг в предыдущем кадре
	bool used_last_frame = false;
	// Отслеживает, используется ли рычаг в текущем кадре
	bool used_current_frame = false;
};
