#pragma once
#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Демонстрирует движение, независимое от частоты кадров, с использованием Game::getIFps().
// Показывает разницу между движением с фиксированным шагом и движением, масштабированным по времени,
// для обеспечения постоянного поведения независимо от частоты кадров.
class IFpsMovementSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(IFpsMovementSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component displays information about the Game::getIfps and demonstrates"
		"how it affects nodes behaviour.");

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);


private:
	void init();
	void shutdown();

	SampleDescriptionWindow window_sample;
};
