// Демонстрирует экспорт структур C++ в UnigineScript через ExternClass.
// Показывает автоматически сгенерированные аксессоры свойств с помощью addSetFunction/addGetFunction
// с указателями на переменные-члены вместо явных методов получения/установки.

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время демонстрации структур.
class ScriptStructure : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptStructure, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};

