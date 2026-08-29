// Демонстрирует вызов функций UnigineScript из C++ с помощью Engine::runWorldFunction.
// Показывает двустороннее взаимодействие: C++ вызывает функции скрипта по имени через класс Variable.
// Регистрирует функцию-обёртку, предоставляющую возможность вызова обратно в UnigineScript.

#pragma once

#include <UnigineComponentSystem.h>

// Вызывает функции UnigineScript каждый кадр и отображает результаты на экране.
class ScriptCallbacks : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptCallbacks, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();
};
