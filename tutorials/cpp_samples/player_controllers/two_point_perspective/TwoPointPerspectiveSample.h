#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

class CameraShiftController;

class TwoPointPerspectiveSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TwoPointPerspectiveSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component provides a UI to toggle two-point perspective mode "
						"by enabling or disabling camera shift in the CameraShiftController.")

	COMPONENT_INIT(init)
	COMPONENT_SHUTDOWN(shutdown);

	// Узел игрока, владеющий управляемой камерой (задаётся в редакторе)
	PROP_PARAM(Node, controlledPlayer);

private:
	void init();
	void shutdown();

	void init_gui();
	void shutdown_gui();

	void on_checkbox_changed();

private:
	// Контроллер камеры, поддерживающий двухточечную перспективу
	CameraShiftController *camera_controller = nullptr;

	// UI примера с описанием и элементами управления
	Unigine::WidgetCheckBoxPtr checkbox;
	SampleDescriptionWindow sample_description_window;
};
