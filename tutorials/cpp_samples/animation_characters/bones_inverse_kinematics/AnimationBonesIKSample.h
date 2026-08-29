#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует базовую обратную кинематику (IK) с вектором полюса.
// Предоставлены два манипулятора: один для IK-цели (куда должен дотянуться конечный эффектор)
// и один для вектора полюса (управляет направлением сгибания суставов).
class AnimationBonesIKSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesIKSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел ObjectMeshSkinned, содержащий скелетный меш
	PROP_PARAM(Node, mesh_skinned_node);
	// Список имён костей, образующих IK-цепочку (порядок важен: от корня к концу)
	PROP_ARRAY(String, bones);

private:
	void init();
	void update();
	void shutdown();

private:
	// Манипулятор, управляющий тем, куда должен дотянуться конец IK-цепочки
	Unigine::WidgetManipulatorTranslatorPtr target_translator;
	// Манипулятор, управляющий вектором полюса (задаёт плоскость сгибания суставов)
	Unigine::WidgetManipulatorTranslatorPtr pole_translator;

	Unigine::ObjectMeshSkinnedLegacyPtr skinned;
	// ID созданной IK-цепочки (-1 означает, что цепочка не инициализирована)
	int chain_id{-1};
};
