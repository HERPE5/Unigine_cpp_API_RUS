// Демонстрация рендеринга Fixed Function Pipeline (FFP). Показывает, как использовать
// рендеринг треугольников в непосредственном режиме для простых 2D-наложений без шейдеров.

#pragma once

#include <UnigineComponentSystem.h>

// Рендерит вращающийся цветной веер с помощью отрисовки FFP в непосредственном режиме.
// Подключается к событию рендеринга после GUI, чтобы рисовать после завершения UI.
class FFPSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(FFPSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates using the Fixed-Function Pipeline (FFP) to render "
							"dynamic geometry with per-vertex colors after GUI rendering.")

	COMPONENT_INIT(init)

private:
	void init();

	// Пользовательский callback рендеринга FFP, выполняемый после завершения рендеринга GUI движком
	static void render();
};
