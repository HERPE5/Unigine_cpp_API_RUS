#include "AnimationBonesConstraintsSample.h"

#include <UnigineGui.h>
#include <UnigineVisualizer.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(AnimationBonesConstraintsSample);

using namespace Unigine;
using namespace Math;

void AnimationBonesConstraintsSample::init()
{
	// Визуализация костей работает только в сборках Debug/Development
#ifndef DEBUG
	if (Engine::get()->getBuildConfiguration() == Engine::BUILD_CONFIG_RELEASE)
		Log::warning("Current build configuration is Release. Visualization of ObjectMeshSkinned "
					 "Bones is not available with this build configuration\n");
#endif

	skinned = checked_ptr_cast<ObjectMeshSkinnedLegacy>(mesh_skinned_node.get());
	if (skinned.isValid() == false)
	{
		Log::error("AnimationBonesConstraintsSample::init(): skinned is null\n");
		return;
	}

	// Создаём IK-цепочку и добавляем в неё кости.
	// CHAIN_CONSTRAINT_BONE_ROTATIONS включает ограничения вращения для каждой кости при решении IK.
	chain_id = skinned->addIKChain();
	skinned->setIKChainConstraint(ObjectMeshSkinnedLegacy::CHAIN_CONSTRAINT_BONE_ROTATIONS, chain_id);
	for (int i = 0; i < ik_chain_bones.size(); i++)
		skinned->addIKChainBone(ik_chain_bones[i], chain_id);

	// Создаём виджет 3D-манипулятора для интерактивного позиционирования IK-цели
	target_translator = WidgetManipulatorTranslator::create();
	target_translator->setTransform(translate(Vec3(2.0f, 2.0f, 0.5f)));
	target_translator->setLifetime(Widget::LIFETIME_WORLD);
	WindowManager::getMainWindow()->addChild(target_translator);

	skinned->setIKChainTargetWorldPosition(target_translator->getTransform().getTranslate(), chain_id);

	// Применяем ограничения вращения к каждой кости, указанной в массиве constraints.
	// Ограничения задают, насколько далеко кость может вращаться по своим локальным осям.
	for (int i = 0; i < constraints.size(); i++)
	{
		const Constraint &c = constraints[i];
		int index = skinned->addBoneConstraint(c.name);
		if (index == -1)
			continue;

		// Задаём локальные оси для вращений yaw/pitch/roll
		skinned->setBoneConstraintYawAxis(c.yaw_axis, index);
		skinned->setBoneConstraintPitchAxis(c.pitch_axis, index);
		skinned->setBoneConstraintRollAxis(c.roll_axis, index);

		// Задаём мин/макс ограничения углов для каждой оси вращения
		skinned->setBoneConstraintYawAngles(c.yaw_min_angle, c.yaw_max_angle, index);
		skinned->setBoneConstraintPitchAngles(c.pitch_min_angle, c.pitch_max_angle, index);
		skinned->setBoneConstraintRollAngles(c.roll_min_angle, c.roll_max_angle, index);

		// Включаем отладочную визуализацию для этого ограничения (показывает допустимый конус вращения)
		skinned->addVisualizeConstraint(index);
	}

	// Включаем отладочную визуализацию для IK-цепочки (показывает кости и суставы)
	skinned->addVisualizeIKChain(chain_id);
	Visualizer::setEnabled(true);
	// Отключаем проверку глубины, чтобы визуализация всегда была видна (даже сквозь геометрию)
	Visualizer::setMode(Visualizer::MODE_ENABLED_DEPTH_TEST_DISABLED);
}

void AnimationBonesConstraintsSample::update()
{
	if (chain_id == -1)
		return;

	PlayerPtr player = Game::getPlayer();
	if (player.isValid() == false)
		return;

	// Синхронизируем виджет-манипулятор с текущей камерой, чтобы он корректно рендерился
	target_translator->setModelview(player->getCamera()->getModelview());
	target_translator->setProjection(player->getCamera()->getProjection());

	// Обновляем позицию IK-цели на основе текущей позиции манипулятора
	Vec3 pos = target_translator->getTransform().getTranslate();
	skinned->setIKChainTargetWorldPosition(pos, chain_id);
	Visualizer::renderMessage3D(pos + Vec3(0.f,0.f,-0.1f), vec3_zero, "Drag Me", vec4_white, 1, 30);
}

void AnimationBonesConstraintsSample::shutdown()
{
	// Восстанавливаем настройки визуализатора по умолчанию
	Visualizer::setEnabled(false);
	Visualizer::setMode(Visualizer::MODE_ENABLED_DEPTH_TEST_ENABLED);
}
