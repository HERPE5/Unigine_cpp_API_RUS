// Демонстрирует рендеринг FFP (Fixed-Function Pipeline) с тестированием глубины.
// Рендерит 3D-линии, правильно взаимодействующие с глубиной сцены, в отличие от
// стандартного FFP, который рендерится поверх всего.

#pragma once

#include <UnigineComponentSystem.h>

// Рендерит линии FFP с тестированием глубины через callback end-visualizer.
class FFPDepth : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(FFPDepth, ComponentBase)
	COMPONENT_INIT(init)

private:
	void init();
	void render_lines_callback();		// Отрисовывает линии с включённым тестированием глубины
};
