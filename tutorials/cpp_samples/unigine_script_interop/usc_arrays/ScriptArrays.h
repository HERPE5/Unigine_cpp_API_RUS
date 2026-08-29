// Демонстрирует взаимодействие C++ с массивами UnigineScript (ArrayVector, ArrayMap).
// Экспортирует функции для манипуляции индексированными и ключ-значение контейнерами из скрипта.
// Показывает паттерны итерации с прямыми/обратными итераторами для карт.

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время операций с массивами.
class ScriptArrays : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptArrays, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
