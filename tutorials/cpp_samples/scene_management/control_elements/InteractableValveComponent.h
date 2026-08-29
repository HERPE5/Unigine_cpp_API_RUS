// Элемент управления "вентиль", вращающийся вокруг своей оси Z на основе движения захвата игрока.
// Вращение управляется отслеживанием углового движения взгляда игрока на плоскости вентиля.
// Поддерживает плавную интерполяцию и настраиваемый диапазон вращения.

#pragma once
#include "Interactable.h"

#include <UnigineComponentSystem.h>

// Вращается на основе движения захвата игрока, спроецированного на плоскость вентиля.
class InteractableValveComponent
	: public Interactable
	, public Unigine::ComponentBase
{
public:
	COMPONENT(InteractableValveComponent, ComponentBase);
	PROP_NAME("InteractableValveComponent");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update, Interactable::interactable_update_priority);

	// Максимальный угол поворота от начального положения в градусах
	PROP_PARAM(Float, rotation_angle_range, 90.0f);
	// Узел, получающий трансформацию поворота
	PROP_PARAM(Node, transformation_node);
	// Может ли игрок в данный момент манипулировать вентилем
	PROP_PARAM(Toggle, is_movable, true);


	void use(Unigine::PlayerPtr player, Unigine::Math::vec3 intersection_point) override;
	float getValue() override;

private:
	void init();
	void update();

	// Ось X плоскости вращения вентиля
	Unigine::Math::vec3 valve_plane_x;
	// Ось Y плоскости вращения вентиля
	Unigine::Math::vec3 valve_plane_y;
	// Нормаль плоскости вентиля (ось Z, ось вращения)
	Unigine::Math::vec3 valve_plane_normal;

	// Направление взгляда игрока в мировом пространстве
	Unigine::Math::vec3 player_view_direction;
	// Позиция камеры игрока в мировом пространстве
	Unigine::Math::vec3 player_position;
	// Текущее направление захвата, спроецированное на плоскость вентиля
	Unigine::Math::vec3 rotation_vec;

	// Направление от центра вентиля к текущей позиции захвата
	Unigine::Math::vec3 grab_vec;
	// Мировая позиция, где игрок захватил вентиль
	Unigine::Math::vec3 grab_point;
	// Направление захвата предыдущего кадра для вычисления дельты
	Unigine::Math::vec3 grab_vec_old;
	// Текущий угол поворота вентиля в градусах
	float rotation_angle = 0.0f;
	// Целевой угол, вычисленный из движения захвата
	float rotation_angle_target = 0.0f;

	// Отслеживает, использовался ли вентиль в предыдущем кадре
	bool used_last_frame = false;
	// Отслеживает, используется ли вентиль в текущем кадре
	bool used_current_frame = false;
};
