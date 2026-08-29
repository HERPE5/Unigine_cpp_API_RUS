// Управляет состоянием ввода мыши для примера контроллера от первого лица.
// Сохраняет и восстанавливает режимы захвата/обработки мыши между сессиями.

#pragma once

#include <UnigineComponentSystem.h>

// Обрабатывает настройку и отмену захвата мыши для управления от первого лица.
class FirstPersonControllerSample final : public Unigine::ComponentBase {
	COMPONENT_DEFINE(FirstPersonControllerSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

private:
	Unigine::Input::MOUSE_HANDLE mouse_handle_at_init;	// Исходный режим обработки мыши
	bool current_mouse_grab_state{false};				// Текущее состояние захвата (не используется)
	bool mouse_grab_state_at_init{false};				// Исходное состояние захвата для восстановления
};
