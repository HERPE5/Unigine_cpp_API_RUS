// Управляет состоянием ввода мыши для примера контроллера от первого лица.
// Сохраняет и восстанавливает режимы захвата/обработки мыши между сессиями.

#include "FirstPersonControllerSample.h"

REGISTER_COMPONENT(FirstPersonControllerSample);

using namespace Unigine;

// Настраивает мышь для управления от первого лица. Сохраняет текущее состояние, чтобы
// его можно было восстановить по завершении примера, затем включает режим захвата для управления камерой.
void FirstPersonControllerSample::init()
{
	// Сохраняем текущие настройки мыши для последующей очистки
	mouse_grab_state_at_init = Input::isMouseGrab();
	mouse_handle_at_init = Input::getMouseHandle();
	// Начинаем с отключённого захвата (пользователь кликает, чтобы захватить мышь)
	Input::setMouseGrab(false);
	// MOUSE_HANDLE_GRAB центрирует курсор каждый кадр - необходимо для камеры FPS
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
}

// Восстанавливает мышь в состояние до запуска примера. Гарантирует, что редактор или другие
// приложения восстановят корректное управление мышью после выхода из примера.
void FirstPersonControllerSample::shutdown()
{
	Input::setMouseGrab(mouse_grab_state_at_init);
	Input::setMouseHandle(mouse_handle_at_init);
}
