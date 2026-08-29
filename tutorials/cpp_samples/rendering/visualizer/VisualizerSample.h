#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include "VisualizerUsage.h"

#include <UnigineComponentSystem.h>

class VisualizerSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(VisualizerSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component provides a UI to control the Visualizer: enable/disable it, toggle depth testing, "
							"and switch individual 2D debug primitives via the linked VisualizerUsage component.")

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	// Ссылка на узел компонента VisualizerUsage (задаётся в редакторе)
	PROP_PARAM(Node, visualizer_usage_node, "Visualizer usage node");

	void init();
	void shutdown();

	VisualizerUsage* visualizer_usage = nullptr;

	// UI примера с описанием и элементами управления
	SampleDescriptionWindow window;
};
