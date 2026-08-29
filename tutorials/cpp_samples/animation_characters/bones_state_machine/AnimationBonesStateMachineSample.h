#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует конечные автоматы анимации для анимации персонажей.
// Показаны три различные конфигурации конечных автоматов:
// 1. Машина ходьбы: анимация ходьбы на основе скорости с возможностью разворота
// 2. Машина поворота в ожидании: состояние ожидания с поворотом на основе направления ввода
// 3. Машина ходьбы/бега: 2D-пространство смешивания для локомоции (вперёд/назад + страйф)
// Каждый конечный автомат использует root motion для управления движением персонажа.
class AnimationBonesStateMachineSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesStateMachineSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Машина ходьбы: переходы между ожиданием и ходьбой на основе переменной скорости
	PROP_PARAM(Node, skeleton_pose_node_walk);

	// Машина поворота в ожидании: 1D-смешивание между поворотом влево, ожиданием и поворотом вправо
	PROP_PARAM(Node, skeleton_pose_node_idle_turn);

	// Машина ходьбы/бега: 2D-пространство смешивания для направленной локомоции
	PROP_PARAM(Node, skeleton_pose_node_walk_run);

private:
	void init();
	void update();

private:
	Unigine::NodeSkeletonPosePtr pose_walk;
	Unigine::AnimScriptPtr walk_script;

	Unigine::NodeSkeletonPosePtr pose_idle_turn;
	Unigine::AnimScriptPtr idle_turn_script;

	Unigine::NodeSkeletonPosePtr pose_walk_run;
	Unigine::AnimScriptPtr walk_run_script;
};
