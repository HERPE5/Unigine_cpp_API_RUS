// Демонстрирует события с несколькими аргументами. Клавиши запускают события с
// разным числом аргументов: T/Y/U для вращения по одной оси (1 аргумент), I для комбинированного
// вращения по XYZ (4 аргумента, включая указатель отправителя для контекста коллбэка).

#include "EventsAdvancedSample.h"
#include <UnigineConsole.h>
#include <UnigineInput.h>

REGISTER_COMPONENT(EventsAdvancedSample);

using namespace Unigine;

// Консоль включается для вывода на экран.
void EventsAdvancedSample::init()
{
	Console::setOnscreen(true);
}

// Проверяется клавиатурный ввод, вызываются соответствующие события вращения.
void EventsAdvancedSample::update()
{
	// Пропускаем обработку ввода, если консоль активна
	if (Console::isActive())
		return;

	// Вызываем событие rotate X с одним аргументом при нажатии T
	if (Input::isKeyPressed(Input::KEY_T))
	{
		Log::message("Run rotate X with 1 arg\n");
		rotate_x_event.run(rotation_speed.get().x);
	}

	// Вызываем событие rotate Y с одним аргументом при нажатии Y
	if (Input::isKeyPressed(Input::KEY_Y))
	{
		Log::message("Run rotate Y with 1 arg\n");
		rotate_y_event.run(rotation_speed.get().y);
	}

	// Вызываем событие rotate Z с одним аргументом при нажатии U
	if (Input::isKeyPressed(Input::KEY_U))
	{
		Log::message("Run rotate Z with 1 arg\n");
		rotate_z_event.run(rotation_speed.get().z);
	}

	// Вызываем событие rotate XYZ с 4 аргументами при нажатии I
	if (Input::isKeyPressed(Input::KEY_I))
	{
		Log::message("Run rotate XYZ with 4 args\n");
		rotate_event.run(rotation_speed.get().x, rotation_speed.get().y, rotation_speed.get().z, this);
	}
}

// Консоль отключается при завершении работы.
void EventsAdvancedSample::shutdown()
{
	Console::setOnscreen(false);
}
