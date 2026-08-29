// Демонстрирует экспорт иерархий классов C++ в UnigineScript.
// Показывает цепочку наследования (MyBaseClass -> MyNodeClass -> MyObjectClass) с
// полиморфными вызовами методов и связью базового класса через addBaseClass.

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время демонстрации наследования.
class ScriptInheritance : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptInheritance, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
