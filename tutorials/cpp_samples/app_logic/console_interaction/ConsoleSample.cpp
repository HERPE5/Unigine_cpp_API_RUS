// Демонстрирует систему консоли: ConsoleVariable для настраиваемых во время выполнения параметров,
// Console::addCommand для пользовательских команд с разбором аргументов и Console::run
// для программного выполнения команд.

#include "ConsoleSample.h"

REGISTER_COMPONENT(ConsoleSample)

using namespace Unigine;
using namespace Math;

// Макросы ConsoleVariable* создают переменные, доступные из консоли.
// Параметры: name, description, flags, default_value, min_value, max_value
// Они сохраняются глобально и могут изменяться во время выполнения через консоль.
ConsoleVariableInt my_console_variable_int{"my_console_variable_int", "my_console_variable_int", 1,
	0, 0, 1000};
ConsoleVariableFloat my_console_variable_float{"my_console_variable_float",
	"my_console_variable_float", 1, 0.0f, 0.0f, 1.0f};
ConsoleVariableString my_console_variable_string{"my_console_variable_string",
	"my_console_variable_string", 1, nullptr};


void ConsoleSample::init()
{
	// Задаём начальные значения консольных переменных
	my_console_variable_float = 1.f;
	my_console_variable_int = 1;
	my_console_variable_string = "String";

	// Добавляем простую консольную команду с коллбэком
	Console::addCommand("my_console_command", "my_console_command decription",
		MakeCallback(this, &ConsoleSample::command_callback));

	// Выполняем команду напрямую из кода
	Console::run("my_console_command \"Hello from C++\"");
	Console::setActive(true);

	// Добавляем команду для перемещения узла на сцене
	Console::addCommand("control_node",
		"With this command you can control node, pass desired position through the arguments",
		MakeCallback(this, &ConsoleSample::move_node_callback));

	if (!controllable_node)
	{
		Log::message("ConsoleSample::init(): No node was provided!\n");
	}

	Log::message("To move the node, you can use control_node command and 3 arguments to specify "
				 "node position");
}


void ConsoleSample::shutdown()
{
	// Удаляем команды и деактивируем консоль
	Console::removeCommand("my_console_command");
	Console::removeCommand("control_node");
	Console::setActive(false);
}


// Коллбэк для логирования вызова команды и её аргументов
void ConsoleSample::command_callback(int argc, char **argv)
{
	Log::message("my_console_command(): called\n");
	for (int i = 0; i < argc; i++)
	{
		Log::message("%d: %s\n", i, argv[i]);
	}
}

// Коллбэк для перемещения узла в координаты, переданные через консоль
void ConsoleSample::move_node_callback(int argc, char **argv)
{
	if (!controllable_node)
		return;

	Vec3 node_position{};
	if (argc != 4)
	{
		Log::warning("control_node was called incorrectly, you need to pass 3 coordinates to move "
					 "the node\n");
		return;
	}

	const auto parse_arg = [this, &argv](int index) -> float {
		const char *a_value = argv[index];
		return Scalar(atof(a_value));
	};

	node_position.x = parse_arg(1);
	node_position.y = parse_arg(2);
	node_position.z = parse_arg(3);

	controllable_node->setWorldPosition(node_position);
}
