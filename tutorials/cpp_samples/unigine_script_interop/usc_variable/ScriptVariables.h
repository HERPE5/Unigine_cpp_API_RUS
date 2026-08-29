// Демонстрирует систему типов класса Variable для взаимодействия C++/UnigineScript.
// Показывает оборачивание примитивов (int, long, float, double) и векторов (vec3, vec4,
// dvec3, dvec4, ivec3, ivec4) в объекты Variable для вызовов функций скрипта.

#pragma once

#include <UnigineComponentSystem.h>

// Проверяет обработку типов Variable, передавая различные типы в скрипт и обратно.
class ScriptVariables : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ScriptVariables, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};
