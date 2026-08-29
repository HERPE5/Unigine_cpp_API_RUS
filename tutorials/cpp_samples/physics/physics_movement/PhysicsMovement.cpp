// Применяет физическое движение с помощью сил и импульсов. Ввод считывается
// в update() и применяется в update_physics() для согласованного физического поведения.

#include "PhysicsMovement.h"
#include <UnigineConsole.h>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(PhysicsMover);

using namespace Unigine;
using namespace Math;

// Твёрдое тело кэшируется из узла.
void PhysicsMover::init()
{
	body = node->getObjectBodyRigid();
}

// Ввод с клавиатуры захватывается для движения и действий.
void PhysicsMover::update()
{
	body->setMaxLinearVelocity(max_speed);
	body->setMaxAngularVelocity(max_rotation_speed);

	if (!Console::isActive())
	{
		input_direction.y = Input::isKeyPressed(Input::KEY_W) - Input::isKeyPressed(Input::KEY_S);
		input_direction.x = Input::isKeyPressed(Input::KEY_A) - Input::isKeyPressed(Input::KEY_D);
		brake |= Input::isKeyPressed(Input::KEY_ANY_SHIFT);
		jump |= Input::isKeyDown(Input::KEY_SPACE);
	}
}

// Силы, крутящие моменты и импульсы применяются на основе состояния ввода.
void PhysicsMover::update_physics()
{
	vec3 forward = node->getWorldDirection(AXIS_Y);
	vec3 up = node->getWorldDirection(AXIS_Z);

	bool onGround = body->getNumContacts() != 0;

	body->addForce(forward * input_direction.y * force);
	body->addTorque(up * input_direction.x * sign(input_direction.y) * torque);

	body->setLinearDamping(brake && onGround ? brakes_strength : 0.0f);
	body->setAngularDamping(brake ? brakes_strength : 0.0f);

	if (jump && onGround)
	{
		body->addLinearImpulse(up * jump_impulse);
	}

	brake = false;
	jump = false;
}
