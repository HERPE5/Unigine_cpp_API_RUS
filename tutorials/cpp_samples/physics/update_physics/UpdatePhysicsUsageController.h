// Сравнивает приложение физической силы в update() и update_physics().
// update() выполняется с частотой кадров рендеринга (переменная), update_physics() выполняется с
// фиксированным шагом времени физики для согласованного поведения независимо от частоты кадров.

#pragma once
#include <UnigineComponentSystem.h>

class UpdatePhysicsUsageController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(UpdatePhysicsUsageController, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component controlls node physics movement and uses update and update_physics for it"
	"depending on parameter value");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	// Обновление с фиксированным шагом времени, синхронизированное с физической симуляцией
	COMPONENT_UPDATE_PHYSICS(update_physics);
	COMPONENT_SHUTDOWN(shutdown);

private:
	// Если true, силы применяются в update() (переменная частота)
	// Если false, силы применяются в update_physics() (фиксированная частота)
	PROP_PARAM(Toggle, use_update, false, "Use update function");
	// Величина горизонтальной силы, применяемой к телу
	PROP_PARAM(Float, linear_force, 5.0f, "Linear force applied to body");
	Unigine::BodyRigidPtr rigid_body;
	// Текущее направление силы (меняется на границах)
	float current_force = 0.0f;

	void init();
	void update_physics();
	void update();
	// Общая логика движения, вызываемая из любого метода обновления
	void movement();
	void shutdown();

private:
	// Исходное состояние визуализатора для восстановления
	bool visualizer_enabled;
};
