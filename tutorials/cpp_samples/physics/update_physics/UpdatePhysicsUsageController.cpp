// Сравнивает приложение физической силы в update() и update_physics().
// update() выполняется с частотой кадров рендеринга (переменная), update_physics() выполняется с
// фиксированным шагом времени физики. Использование update_physics() гарантирует согласованное поведение
// независимо от производительности рендеринга.

#pragma once
#include "UpdatePhysicsUsageController.h"

#include <Unigine.h>
#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(UpdatePhysicsUsageController);

void UpdatePhysicsUsageController::init()
{
	rigid_body = node->getObjectBodyRigid();

	if (!rigid_body)
	{
		Log::error("PhysicsIFpsController::init can't find rigid body on the node!\n");
	}
	current_force = linear_force;

	visualizer_enabled = Visualizer::isEnabled();
	Visualizer::setEnabled(true);
}

void UpdatePhysicsUsageController::update()
{
	// Визуализируем текущую линейную скорость
	Visualizer::renderVector(rigid_body->getPosition(), rigid_body->getPosition() + Vec3(rigid_body->getLinearVelocity()), vec4_red,0.5f);

	// ОБРАТИТЕ ВНИМАНИЕ, что методы update и udpate_physics регистрируются в разных макросах компонента, и код одинаков для обоих примеров использования
	// использование update() для перемещения узла с физикой
	if (use_update) 
	{
		movement();
	}
}

void UpdatePhysicsUsageController::movement()
{
	// Применяем горизонтальную силу для движения тела вперёд-назад
	rigid_body->addForce(vec3_right * current_force);

	// Меняем направление при достижении граничных позиций
	if (node->getWorldPosition().x > 5)
		current_force = -linear_force;
	if (node->getWorldPosition().x < -5)
		current_force = linear_force;
}

void UpdatePhysicsUsageController::shutdown()
{
	Visualizer::setEnabled(visualizer_enabled);
}

void UpdatePhysicsUsageController::update_physics()
{
	// ОБРАТИТЕ ВНИМАНИЕ, что методы update и udpate_physics регистрируются в разных макросах компонента, и код одинаков для обоих примеров использования
	// использование update() для перемещения узла с физикой
	if (!use_update)
	{
		movement();
	}
}
