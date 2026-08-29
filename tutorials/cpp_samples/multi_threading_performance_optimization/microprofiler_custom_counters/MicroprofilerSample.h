#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"
#include <UnigineComponentSystem.h>

// Демонстрирует интеграцию с Microprofiler для детального анализа производительности.
// Отображает URL микропрофилировщика для профилирования в браузере, когда он доступен.
class MicroprofilerSample
	: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(MicroprofilerSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();     // отображает URL микропрофилировщика и включает фоновые обновления
	void shutdown(); // восстанавливает настройки фоновых обновлений

private:
	// UI примера с описанием и элементами управления
	SampleDescriptionWindow sample_description_window;
	Unigine::Engine::BACKGROUND_UPDATE previous_bg_update;
};
