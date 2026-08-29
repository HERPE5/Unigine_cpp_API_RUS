#pragma once
#include <UnigineComponentSystem.h>

// Переключаемый контроллер, сравнивающий движение с масштабированием IFps и без него.
// Когда use_ifps равно false, скорость движения зависит от частоты кадров.
// Когда use_ifps равно true, движение не зависит от частоты кадров (постоянная скорость).
class IFpsMovementController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(IFpsMovementController, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component controls node movement, optionally using Game::getIfps() for it"
		"depending on the parameter value");

	COMPONENT_UPDATE(update);

private:
	// Параметры
	PROP_PARAM(Toggle, use_ifps, false, "Use IFps");       // включает движение, не зависящее от частоты кадров
	PROP_PARAM(Float, movement_speed, 1.0f, "Movement Speed"); // базовая скорость движения

	Unigine::Math::Vec3 current_dir = Unigine::Math::Vec3_right; // текущее направление движения

	void update();
};
