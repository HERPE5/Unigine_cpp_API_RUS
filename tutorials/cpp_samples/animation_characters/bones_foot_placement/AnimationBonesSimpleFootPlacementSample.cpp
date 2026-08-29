#include "AnimationBonesSimpleFootPlacementSample.h"

#include <UnigineGui.h>
#include <UnigineVisualizer.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(AnimationBonesSimpleFootPlacementSample);

using namespace Unigine;
using namespace Math;

void AnimationBonesSimpleFootPlacementSample::init()
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
		Log::error("AnimationBonesSimpleFootPlacementSample::init(): skinned is null\n");
		return;
	}

	// Создаём IK-цепочку для левой ноги
	chain_ids[FOOT_LEFT] = skinned->addIKChain();
	for (int i = 0; i < left_leg_bones.size(); i++)
	{
		int bone = skinned->findBone(left_leg_bones[i]);
		if (bone == -1)
			continue;

		skinned->addIKChainBone(bone, chain_ids[FOOT_LEFT]);
		effector_bones[FOOT_LEFT] = bone; // последняя добавленная кость становится эффектором
	}
	skinned->setIKChainPoleWorldPosition(Vec3(0.5, 1.0f, 1.5), chain_ids[FOOT_LEFT]);

	// Создаём IK-цепочку для правой ноги
	chain_ids[FOOT_RIGHT] = skinned->addIKChain();
	for (int i = 0; i < right_leg_bones.size(); i++)
	{
		int bone = skinned->findBone(right_leg_bones[i]);
		if (bone == -1)
			continue;

		skinned->addIKChainBone(bone, chain_ids[FOOT_RIGHT]);
		effector_bones[FOOT_RIGHT] = bone;
	}
	skinned->setIKChainPoleWorldPosition(Vec3(1.0, 0.5f, 1.5), chain_ids[FOOT_RIGHT]);

	// Инициализируем IK-цели на текущих позициях стоп и включаем вращение эффектора
	// (чтобы стопы выравнивались по нормали поверхности, а не только по позиции)
	for (int i = FOOT_LEFT; i < FOOT_NUM; i++)
	{
		if (effector_bones[i] == -1)
			continue;

		Mat4 t = skinned->getBoneWorldTransform(effector_bones[i]);
		skinned->setIKChainTargetWorldPosition(t.getTranslate(), chain_ids[i]);

		skinned->setIKChainUseEffectorRotation(true, chain_ids[i]);
		skinned->setIKChainEffectorWorldRotation(t.getRotate(), chain_ids[i]);

		skinned->addVisualizeIKChain(chain_ids[i]);
	}

	// Создаём манипуляторы для перемещения/вращения платформы-препятствия
	if (obstacle.get().isValid())
	{
		translator = WidgetManipulatorTranslator::create();
		translator->setLifetime(Widget::LIFETIME_WORLD);
		translator->setTransform(obstacle->getWorldTransform());
		WindowManager::getMainWindow()->addChild(translator);

		rotator = WidgetManipulatorRotator::create();
		rotator->setLifetime(Widget::LIFETIME_WORLD);
		rotator->setTransform(obstacle->getWorldTransform());
		rotator->setHidden(true);
		WindowManager::getMainWindow()->addChild(rotator);
	}

	// Подписываемся на событие, вызываемое непосредственно перед решением IK.
	// Именно здесь позиции стоп обновляются на основе трассировки лучей.
	skinned->getEventBeginIKSolvers().connect(this, &AnimationBonesSimpleFootPlacementSample::on_begin_ik_solvers);

	Visualizer::setEnabled(true);
	Visualizer::setMode(Visualizer::MODE_ENABLED_DEPTH_TEST_DISABLED);
}

void AnimationBonesSimpleFootPlacementSample::update()
{
	PlayerPtr player = Game::getPlayer();
	if (obstacle.get().isValid() && player.isValid())
	{
		// Переключение между манипуляторами перемещения (T) и вращения (R)
		if (Input::isKeyDown(Input::KEY_T))
		{
			translator->setHidden(false);
			rotator->setHidden(true);
			translator->setTransform(obstacle->getWorldTransform());
		}

		if (Input::isKeyDown(Input::KEY_R))
		{
			rotator->setHidden(false);
			translator->setHidden(true);
			rotator->setTransform(obstacle->getWorldTransform());
		}

		// Применяем изменения манипулятора к препятствию
		if (translator->isHidden() == false)
		{
			translator->setModelview(player->getCamera()->getModelview());
			translator->setProjection(player->getCamera()->getProjection());
			obstacle->setWorldTransform(translator->getTransform());
		}

		if (rotator->isHidden() == false)
		{
			rotator->setModelview(player->getCamera()->getModelview());
			rotator->setProjection(player->getCamera()->getProjection());
			obstacle->setWorldTransform(rotator->getTransform());
		}

		Visualizer::renderMessage3D(translator->getTransform().getTranslate()
				+ Vec3(0.f, 0.f, -0.1f),
			vec3_zero, "Drag Me", vec4_white, 1, 30);
	}
}

void AnimationBonesSimpleFootPlacementSample::shutdown()
{
	Visualizer::setEnabled(false);
	Visualizer::setMode(Visualizer::MODE_ENABLED_DEPTH_TEST_ENABLED);
}

// Этот коллбэк вызывается непосредственно перед запуском решателей IK.
// Он выполняет трассировку лучей для поиска земли под каждой стопой и обновляет цели IK.
void AnimationBonesSimpleFootPlacementSample::on_begin_ik_solvers()
{
	for (int i = FOOT_LEFT; i < FOOT_NUM; i++)
	{
		if (effector_bones[i] == -1)
			continue;

		// Получаем текущую позицию и вращение стопы из анимации
		Mat4 t = skinned->getBoneWorldTransform(effector_bones[i]);
		Vec3 foot_pos(t.getTranslate());
		quat foot_rot(t.getRotate());

		// Визуализируем линию трассировки луча
		Visualizer::renderVector(foot_pos + Vec3_up * 0.5f, foot_pos + Vec3_down * foot_height, vec4_blue);

		// Отправляем луч вниз от стопы для поиска контакта с землёй
		PhysicsIntersectionNormalPtr intersection = PhysicsIntersectionNormal::create();
		ObjectPtr obj = Physics::getIntersection(foot_pos + Vec3_up * 0.5f, foot_pos + Vec3_down * foot_height, 1, intersection);
		if (obj != nullptr)
		{
			// Визуализируем нормаль поверхности в точке контакта
			Visualizer::renderVector(intersection->getPoint(), intersection->getPoint() + Vec3(intersection->getNormal()), vec4_blue);

			// Корректируем позицию стопы в соответствии с высотой земли (плюс смещение foot_height)
			foot_pos = intersection->getPoint() + Vec3_up * foot_height;
			// Вращаем стопу для выравнивания по нормали поверхности
			foot_rot = rotationFromTo(vec3_up, intersection->getNormal()) * foot_rot;
		}

		// Обновляем цель IK с скорректированной позицией и вращением
		skinned->setIKChainTargetWorldPosition(foot_pos, chain_ids[i]);
		skinned->setIKChainEffectorWorldRotation(foot_rot, chain_ids[i]);
	}
}
