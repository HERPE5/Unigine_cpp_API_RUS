#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует технику root motion.
// Root motion извлекает движение из корневой кости анимации и применяет его
// к мировой позиции объекта, обеспечивая локомоцию, управляемую анимацией.
// Это гарантирует, что движение персонажа точно соответствует анимации.
class AnimationBonesRootMotion : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesRootMotion, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_POST_UPDATE(post_update);
	COMPONENT_SHUTDOWN(shutdown);

	// Эталонная модель для сравнения (воспроизводит анимацию без root motion)
	PROP_PARAM(Node, skeleton_pose_node);
	// Модель, использующая root motion (объект перемещается на основе анимации)
	PROP_PARAM(Node, skeleton_pose_root_motion_node);

private:
	void init();
	void update();
	void post_update();
	void shutdown();

private:
	Unigine::NodeSkeletonPosePtr pose;

	Unigine::NodeSkeletonPosePtr pose_root_motion;
	Unigine::AnimScriptPtr anim_script;
};
