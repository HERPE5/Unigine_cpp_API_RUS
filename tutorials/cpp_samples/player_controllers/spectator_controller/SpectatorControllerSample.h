// UI примера для настройки параметров камеры spectator во время выполнения.
// Предоставляет слайдеры для чувствительности мыши, скорости поворота, скорости и скорости спринта,
// а также чекбоксы для переключения управления вводом и определения столкновений.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include "SpectatorController.h"

// Создаёт GUI настройки параметров для SpectatorController: слайдеры для настроек
// движения и чекбоксы для переключения ввода/столкновений.
class SpectatorControllerSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(SpectatorControllerSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

	SampleDescriptionWindow description_window;			// Окно GUI для элементов управления параметрами
	Unigine::Input::MOUSE_HANDLE mouse_handle_at_init;	// Исходный режим мыши для восстановления

	SpectatorController* spectator {nullptr};	// Управляемый компонент spectator

	bool is_controlled = false;		// Включено ли управление вводом
	bool is_collided = false;		// Включено ли определение столкновений

	// Диапазон и текущее значение слайдера чувствительности мыши
	float min_mouse_sensetivity = 0.1f;		// Примечание: опечатка в оригинале - "sensetivity"
	float max_mouse_sensetivity = 1.0f;
	float current_mouse_sensetivity = 0.0f;

	// Диапазон и текущее значение слайдера скорости поворота
	float min_turning = 15.0f;
	float max_turning = 120.0f;
	float current_turning = 0.0f;

	// Диапазон и текущее значение слайдера базовой скорости
	float min_velocity = 1.0f;
	float max_velocity = 4.0f;
	float current_velocity = 0.0f;

	// Диапазон и текущее значение слайдера скорости спринта
	float min_sprint_velocity = 5.0f;
	float max_sprint_velocity = 10.0f;
	float current_sprint_velocity = 0.0f;
};