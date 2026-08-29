#include "AnimationBonesStateMachineSample.h"

#include <UnigineGui.h>
#include <UnigineVisualizer.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(AnimationBonesStateMachineSample);

using namespace Unigine;
using namespace Math;

void AnimationBonesStateMachineSample::init()
{
	// Машина ходьбы
	pose_walk = checked_ptr_cast<NodeSkeletonPose>(skeleton_pose_node_walk.get());
	if (pose_walk.isValid() == false)
	{
		Log::error("AnimationBonesStateMachineSample::init(): pose walk is null\n");
		return;
	}

	walk_script = pose_walk->getAnimScript();
	if (walk_script.isValid() == false)
	{
		Log::error("AnimationBonesStateMachineSample::init(): walk script is null\n");
		return;
	}

	// Машина поворота в ожидании
	pose_idle_turn = checked_ptr_cast<NodeSkeletonPose>(skeleton_pose_node_idle_turn.get());
	if (pose_idle_turn.isValid() == false)
	{
		Log::error("AnimationBonesStateMachineSample::init(): pose_idle_turn is null\n");
		return;
	}

	idle_turn_script = pose_idle_turn->getAnimScript();
	if (idle_turn_script.isValid() == false)
	{
		Log::error("AnimationBonesStateMachineSample::init(): idle turn script is null\n");
		return;
	}

	// Машина ходьбы/бега
	pose_walk_run = checked_ptr_cast<NodeSkeletonPose>(skeleton_pose_node_walk_run.get());
	if (pose_walk_run.isValid() == false)
	{
		Log::error("AnimationBonesStateMachineSample::init(): pose walk run is null\n");
		return;
	}

	walk_run_script = pose_walk_run->getAnimScript();
	if (walk_run_script.isValid() == false)
	{
		Log::error("AnimationBonesStateMachineSample::init(): walk run script is null\n");
		return;
	}
}

void AnimationBonesStateMachineSample::update()
{
	// Машина ходьбы: демонстрирует переходы состояний на основе скорости
	// Переменная "speed" управляет переходами ожидание<->ходьба
	// Флаг "turn" запускает анимацию разворота на 180 градусов
	{
		if (Input::isKeyDown(Input::KEY_T))
			walk_script->setParamFloat("speed", 1.0f);

		if (Input::isKeyDown(Input::KEY_G))
			walk_script->setParamFloat("speed", 0.0f);

		walk_script->setParamBool("turn", false);
		if (Input::isKeyPressed(Input::KEY_Y))
			walk_script->setParamBool("turn", true);

		// Применяем root motion: движение корневой кости анимации извлекается
		// и применяется к мировой трансформации персонажа для реалистичной локомоции
		if (walk_script->isActiveRootMotion())
		{
			Transform delta = walk_script->getRootMotionDelta();
			pose_walk->setWorldTransform(pose_walk->getWorldTransform() * Mat4(delta.getMat()));
		}
	}

	// Машина поворота в ожидании: демонстрирует 1D-пространство смешивания
	// Переменная "turn" (от -1 до 1) смешивает анимации turn_left, idle и turn_right
	// Это создаёт плавный направленный поворот на месте
	{
		float turn = idle_turn_script->getParamFloat("turn");
		if (Input::isKeyPressed(Input::KEY_V))
			turn += Game::getIFps();
		if (Input::isKeyPressed(Input::KEY_C))
			turn -= Game::getIFps();
		turn = clamp(turn, -1.0f, 1.0f);
		idle_turn_script->setParamFloat("turn", turn);

		if (idle_turn_script->isActiveRootMotion())
		{
			Transform delta = idle_turn_script->getRootMotionDelta();
			pose_idle_turn->setWorldTransform(pose_idle_turn->getWorldTransform() * Mat4(delta.getMat()));
		}
	}

	// Машина ходьбы/бега: демонстрирует 2D-пространство смешивания
	// Две переменные управляют смешиванием: "y" (0-1) для скорости вперёд/назад,
	// "x" (от -1 до 1) для направления страйфа. Это создаёт движение в 8 направлениях
	// путём смешивания анимаций walk_forward, walk_backward, strafe_left, strafe_right и т.д.
	{
		float y = walk_run_script->getParamFloat("y");
		if (Input::isKeyPressed(Input::KEY_I))
			y += Game::getIFps();
		if (Input::isKeyPressed(Input::KEY_K))
			y -= Game::getIFps();
		y = saturate(y);
		walk_run_script->setParamFloat("y", y);

		float x = walk_run_script->getParamFloat("x");
		if (Input::isKeyPressed(Input::KEY_L))
			x += Game::getIFps();
		if (Input::isKeyPressed(Input::KEY_J))
			x -= Game::getIFps();
		x = clamp(x, -1.0f, 1.0f);
		walk_run_script->setParamFloat("x", x);

		if (walk_run_script->isActiveRootMotion())
		{
			Transform delta = walk_run_script->getRootMotionDelta();
			pose_walk_run->setWorldTransform(pose_walk_run->getWorldTransform() * Mat4(delta.getMat()));
		}
	}
}
