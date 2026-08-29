#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует обратную кинематику (IK) с ограничениями вращения костей.
// Цель можно перетаскивать в 3D-пространстве, и цепочка костей автоматически адаптируется,
// соблюдая заданные ограничения углов по осям yaw/pitch/roll.
class AnimationBonesConstraintsSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesConstraintsSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел ObjectMeshSkinned, содержащий скелетный меш
	PROP_PARAM(Node, mesh_skinned_node);
	// Список имён костей, образующих IK-цепочку (порядок важен: от корня к концу)
	PROP_ARRAY(String, ik_chain_bones);

	// Структура, определяющая ограничения вращения для отдельной кости
	struct Constraint: Unigine::ComponentStruct
	{
		// Имя кости, к которой применяются ограничения
		PROP_PARAM(String, name);

		// Локальные оси вращения кости (заданы в локальной системе координат кости)
		PROP_PARAM(Vec3, yaw_axis, Unigine::Math::vec3_forward);
		PROP_PARAM(Vec3, pitch_axis, -Unigine::Math::vec3_right);
		PROP_PARAM(Vec3, roll_axis, Unigine::Math::vec3_up);

		// Допустимый диапазон углов для каждой оси (в градусах)
		PROP_PARAM(Float, yaw_min_angle, -180.0f);
		PROP_PARAM(Float, yaw_max_angle, 180.0f);

		PROP_PARAM(Float, pitch_min_angle, -90.0f);
		PROP_PARAM(Float, pitch_max_angle, 90.0f);

		// Roll по умолчанию заблокирован (min == max == 0)
		PROP_PARAM(Float, roll_min_angle, -0.0f);
		PROP_PARAM(Float, roll_max_angle, 0.0f);
	};

	PROP_ARRAY_STRUCT(Constraint, constraints);

private:
	void init();
	void update();
	void shutdown();

private:
	// Виджет-манипулятор для интерактивного перетаскивания IK-цели в 3D-пространстве
	Unigine::WidgetManipulatorTranslatorPtr target_translator;

	Unigine::ObjectMeshSkinnedLegacyPtr skinned;
	// ID созданной IK-цепочки (-1 означает, что цепочка не инициализирована)
	int chain_id{-1};
};
