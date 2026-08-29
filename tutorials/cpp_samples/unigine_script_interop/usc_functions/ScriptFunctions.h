// Демонстрирует экспорт функций C++ в UnigineScript через Interpreter.
// Показывает автономные функции с полиморфизмом Variable и функции-члены класса,
// экспортированные как библиотека (паттерн синглтона).

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время демонстрации взаимодействия функций.
class ScriptFunctions : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptFunctions, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
