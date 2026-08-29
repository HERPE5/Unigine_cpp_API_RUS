#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

// Управляет движением твёрдого тела с помощью физических сил и крутящих моментов.
// Поддерживает ввод с клавиатуры для управления, торможения и прыжков.
class PhysicsMover: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(PhysicsMover, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_UPDATE_PHYSICS(update_physics);

	PROP_PARAM(Float, force, 10.0f);              // Ускорение вперёд/назад
	PROP_PARAM(Float, torque, 1.0f);              // Сила поворота
	PROP_PARAM(Float, jump_impulse, 3.0f);        // Вертикальный импульс при прыжке
	PROP_PARAM(Float, max_speed, 30.0f);          // Ограничение линейной скорости
	PROP_PARAM(Float, max_rotation_speed, 10.0f); // Ограничение угловой скорости
	PROP_PARAM(Float, brakes_strength, 5.0f);     // Затухание при торможении

private:
	void init();           // Кэширует ссылку на твёрдое тело
	void update();         // Считывает ввод с клавиатуры
	void update_physics(); // Применяет силы и крутящие моменты

private:
	Unigine::BodyRigidPtr body; // Управляемое твёрдое тело

	Unigine::Math::vec2 input_direction; // Состояние ввода WASD
	bool brake = false;                  // Состояние клавиши Shift
	bool jump = false;                   // Состояние клавиши Space
};
