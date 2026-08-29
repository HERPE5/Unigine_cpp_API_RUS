// Демонстрирует пользовательскую маршализацию типов между C++ и UnigineScript.
// Показывает специализации шаблонов TypeToVariable/VariableToType для автоматического
// преобразования между пользовательским MyVector3 и встроенным типом vec3.

#pragma once

#include <UnigineComponentSystem.h>

// Настраивает консоль для вывода на экран во время демонстрации преобразования типов.
class ScriptTypes : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptTypes, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
