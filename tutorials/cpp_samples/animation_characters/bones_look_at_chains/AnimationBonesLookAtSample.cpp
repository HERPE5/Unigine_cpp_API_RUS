#include "AnimationBonesLookAtSample.h"

#include <UnigineGui.h>
#include <UnigineVisualizer.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(AnimationBonesLookAtSample);

using namespace Unigine;
using namespace Math;

void AnimationBonesLookAtSample::init()
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
		Log::error("AnimationBonesLookAtSample::init(): skinned is null\n");
		return;
	}

	// Создаём LookAt-цепочку и настраиваем каждую участвующую кость
	chain_id = skinned->addLookAtChain();
	for (int i = 0; i < bones.size(); i++)
	{
		const Bone &b = bones[i];
		int index = skinned->addLookAtChainBone(b.name, chain_id);
		if (index == -1)
			continue;

		// Оси axis и up должны быть заданы в локальной системе координат кости
		skinned->setLookAtChainBoneAxis(Vec3(b.axis), index, chain_id);
		skinned->setLookAtChainBoneUp(Vec3(b.up), index, chain_id);

		// Вес определяет, насколько сильно эта кость участвует в общем вращении наведения
		skinned->setLookAtChainBoneWeight(b.weight, index, chain_id);
	}

	// Создаём манипулятор для цели наведения
	target_translator = WidgetManipulatorTranslator::create();
	target_translator->setTransform(translate(Vec3(1.5f, 1.5f, 1.6f)));
	target_translator->setLifetime(Widget::LIFETIME_WORLD);
	WindowManager::getMainWindow()->addChild(target_translator);

	// Создаём манипулятор для вектора полюса (задаёт ориентир "вверх" для ориентации)
	pole_translator = WidgetManipulatorTranslator::create();
	pole_translator->setTransform(translate(Vec3(0.0f, 0.0f, 3.0f)));
	pole_translator->setLifetime(Widget::LIFETIME_WORLD);
	WindowManager::getMainWindow()->addChild(pole_translator);

	// Задаём начальные позиции цели и полюса
	skinned->setLookAtChainTargetWorldPosition(target_translator->getTransform().getTranslate(), chain_id);
	skinned->setLookAtChainPoleWorldPosition(pole_translator->getTransform().getTranslate(), chain_id);

	// Включаем отладочную визуализацию для LookAt-цепочки
	skinned->addVisualizeLookAtChain(chain_id);
	Visualizer::setEnabled(true);
	Visualizer::setMode(Visualizer::MODE_ENABLED_DEPTH_TEST_DISABLED);
}

void AnimationBonesLookAtSample::update()
{
	if (chain_id == -1)
		return;

	PlayerPtr player = Game::getPlayer();
	if (player.isValid() == false)
		return;

	// Синхронизируем манипуляторы с текущей камерой
	target_translator->setModelview(player->getCamera()->getModelview());
	target_translator->setProjection(player->getCamera()->getProjection());

	pole_translator->setModelview(player->getCamera()->getModelview());
	pole_translator->setProjection(player->getCamera()->getProjection());

	Vec3 target_pos = target_translator->getTransform().getTranslate();
	Vec3 pole_pos = pole_translator->getTransform().getTranslate();

	// Обновляем LookAt-цепочку текущими позициями манипуляторов
	skinned->setLookAtChainTargetWorldPosition(target_translator->getTransform().getTranslate(), chain_id);
	skinned->setLookAtChainPoleWorldPosition(pole_translator->getTransform().getTranslate(), chain_id);

	Visualizer::renderMessage3D(target_pos + Vec3(0.f, 0.f, -0.1f), vec3_zero, "Drag Me",
		vec4_white, 1, 30);
	Visualizer::renderMessage3D(pole_pos + Vec3(0.f, 0.f, -0.1f), vec3_zero, "Drag Me", vec4_white,
		1, 30);
}

void AnimationBonesLookAtSample::shutdown()
{
	// Восстанавливаем настройки визуализатора по умолчанию
	Visualizer::setEnabled(false);
	Visualizer::setMode(Visualizer::MODE_ENABLED_DEPTH_TEST_ENABLED);
}
