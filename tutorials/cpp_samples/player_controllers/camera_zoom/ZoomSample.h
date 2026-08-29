// UI примера, демонстрирующий масштабирование камеры с отображением в реальном времени изменений FOV,
// чувствительности мыши и масштаба дистанции рендеринга.
// Предоставляет кнопки целей для быстрой ориентации камеры на объекты.

#pragma once

#include "ZoomController.h"
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Панель GUI, управляющая уровнем масштабирования и отображающая параметры камеры.
class ZoomSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ZoomSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component displays information about the zoom sample and demonstrates "
		"how to use a simple zoom and how it affects player camera.");

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, zoom_node, "", "Zoom controller node");		// Игрок с прикреплённым ZoomController
	PROP_PARAM(Node, target_one_node, "", "Target one node");	// Первая цель фокусировки
	PROP_PARAM(Node, target_two_node, "", "Target two node");	// Вторая цель фокусировки
	PROP_PARAM(Node, target_three_node, "", "Target three node");	// Третья цель фокусировки

private:
	Unigine::Input::MOUSE_HANDLE mouse_grab = Unigine::Input::MOUSE_HANDLE_USER;

	void init();
	void shutdown();
	void init_components();

	SampleDescriptionWindow window_sample;

	Unigine::WidgetLabelPtr fov_label;				// Показывает текущий FOV в градусах
	Unigine::WidgetLabelPtr mouse_sensivity_label;	// Показывает скорректированную чувствительность мыши
	Unigine::WidgetLabelPtr render_scale_label;		// Показывает множитель дистанции LOD

	ZoomController* zoom = nullptr;
	Unigine::PlayerPtr player;
};
