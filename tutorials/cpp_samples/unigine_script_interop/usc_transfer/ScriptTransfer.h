// Демонстрирует передачу объектов UNIGINE между C++ и UnigineScript.
// Сравнивает три подхода: прямой Ptr, Variable с setImage/getImage
// и шаблоны TypeToVariable/VariableToType для автоматического преобразования.

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время демонстрации передачи объектов.
class ScriptTransfer : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptTransfer, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
