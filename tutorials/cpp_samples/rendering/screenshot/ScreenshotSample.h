// UI примера для функциональности захвата скриншота.
// Предоставляет кнопку для запуска захвата скриншота через
// вспомогательный класс Screenshot.

#pragma once

#include "Screenshot.h"

#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Предоставляет кнопку UI для запуска захвата скриншота и сохранения в файл.
class ScreenshotSample final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(ScreenshotSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

private:
	// Вспомогательный объект, обрабатывающий фактический захват скриншота
	Screenshot screenshot;

	SampleDescriptionWindow sample_description_window;
};
