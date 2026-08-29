#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineConsole.h>

// Демонстрирует интеграцию с консолью: пользовательские переменные, команды и коллбэки.
// Типы ConsoleVariable (Int, Float, String) предоставляются во внутриигровую консоль.
// Пользовательские команды регистрируются с коллбэками, получающими аргументы argc/argv.
class ConsoleSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(ConsoleSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates console integration by registering custom "
			"variables and commands, executing callbacks, and allowing control of a scene node via console arguments.")

	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown)

	// Узел, которым можно управлять через консольную команду (задаётся в редакторе)
	PROP_PARAM(Node, controllable_node)

private:
	void init();
	void shutdown();

	// Коллбэки для консольных команд
	void command_callback(int argc, char **argv);
	void move_node_callback(int argc, char **argv);
};
