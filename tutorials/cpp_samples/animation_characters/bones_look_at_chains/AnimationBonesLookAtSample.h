#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует LookAt-цепочки для наведения костей на цель.
// Несколько костей (например, позвоночник и голова) могут участвовать в цепочке с разными весами,
// распределяя вращение по цепочке для естественного взгляда.
class AnimationBonesLookAtSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesLookAtSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел ObjectMeshSkinned, содержащий скелетный меш
	PROP_PARAM(Node, mesh_skinned_node);

	// Настройка для каждой кости, участвующей в LookAt-цепочке
	struct Bone: Unigine::ComponentStruct
	{
		// Имя кости для включения в LookAt-цепочку
		PROP_PARAM(String, name);
		// Ось "вперёд" кости (направление, которое должно указывать на цель)
		PROP_PARAM(Vec3, axis, Unigine::Math::vec3_forward);
		// Ось "вверх" кости (используется для ориентации кручения/крена)
		PROP_PARAM(Vec3, up, Unigine::Math::vec3_up);
		// Вес вклада: чем выше значение, тем сильнее кость вращается к цели
		PROP_PARAM(Float, weight, 1.0f);
	};

	PROP_ARRAY_STRUCT(Bone, bones);

private:
	void init();
	void update();
	void shutdown();

private:
	// Манипулятор для позиции цели наведения
	Unigine::WidgetManipulatorTranslatorPtr target_translator;
	// Манипулятор для вектора полюса (управляет ориентацией "вверх" цепочки)
	Unigine::WidgetManipulatorTranslatorPtr pole_translator;

	Unigine::ObjectMeshSkinnedLegacyPtr skinned;
	// ID созданной LookAt-цепочки (-1 означает, что цепочка не инициализирована)
	int chain_id{-1};
};
