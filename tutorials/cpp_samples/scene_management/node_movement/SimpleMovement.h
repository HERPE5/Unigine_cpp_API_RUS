// Демонстрирует три эквивалентных подхода к перемещению узла:
// translate/rotate, setPosition/setRotation и setTransform.
// Все варианты используют WASD для перемещения; результаты идентичны.

#pragma once
#include "UnigineComponentSystem.h"

// Вариант 1: использует методы Node::translate() и Node::rotate().
class SimpleMovement : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SimpleMovement, ComponentBase);
	COMPONENT_UPDATE(update);

	// Скорость движения в единицах в секунду
	PROP_PARAM(Float, velocity, 5.0f, "", "Linear velocity in units");
	// Скорость поворота в градусах в секунду
	PROP_PARAM(Float, angular_velocity, 50.0f, "","Angular velocity in degrees");

private:
	void update();

	void move(const Unigine::Math::Vec3& dir);
	void turn(const Unigine::Math::vec3& angles);
};

// Вариант 2: использует методы Node::setPosition() и Node::setRotation().
class SimpleMovement2 : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SimpleMovement2, ComponentBase);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, velocity, 5.0f, "", "Linear velocity in units");
	PROP_PARAM(Float, angular_velocity, 50.0f, "", "Angular velocity in degrees");

private:
	void update();

	void move(const Unigine::Math::Vec3& dir);
	void turn(const Unigine::Math::vec3& angles);
};

// Вариант 3: использует Node::setTransform() с перемножением матриц.
class SimpleMovement3 : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SimpleMovement3, ComponentBase);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Float, velocity, 5.0f, "", "Linear velocity in units");
	PROP_PARAM(Float, angular_velocity, 50.0f, "", "Angular velocity in degrees");

private:
	void update();

	void move(const Unigine::Math::Vec3& dir);
	void turn(const Unigine::Math::vec3& angles);
};
