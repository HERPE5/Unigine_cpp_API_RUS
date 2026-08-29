// Простой контроллер машины для демонстрации гонки с разделённым экраном.
// Обрабатывает ввод с клавиатуры (WASD или стрелки) для перемещения и поворота
// машины с настраиваемой скоростью и ускорением.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineInput.h>

class CarControl: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CarControl, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Параметры движения
	PROP_PARAM(Float, max_speed, 10.f);
	PROP_PARAM(Float, max_rotation, 50.f);
	PROP_PARAM(Float, acceleration_factor, 0.5f);
	// Если true, используются клавиши стрелок вместо WASD
	PROP_PARAM(Toggle, use_arrows, false);

private:
	void init();
	void update();
	void shutdown();

	// Возвращает -1, 0 или 1 в зависимости от ввода вперёд/назад
	int get_movement_command() const;
	// Возвращает -1, 0 или 1 в зависимости от ввода влево/вправо
	int get_rotate_command() const;
	// Привязывает клавиши в зависимости от настройки use_arrows
	void init_input_keys();

	// Текущее состояние движения
	Unigine::Math::Scalar forward = 0.f;
	float rotation = 0.f;
	// Настроенные клавиши ввода
	Unigine::Input::KEY key_forward;
	Unigine::Input::KEY key_back;
	Unigine::Input::KEY key_left;
	Unigine::Input::KEY key_right;
};
