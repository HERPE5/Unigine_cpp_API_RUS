// Демонстрирует доступ к стеку Interpreter для вариативных функций в UnigineScript.
// Показывает, как извлекать аргументы Variable из стека скрипта с помощью getStack/popStack.
// Реализует форматирование в стиле printf со спецификаторами %d, %f, %s.

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время демонстрации стека.
class ScriptStack : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptStack, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
