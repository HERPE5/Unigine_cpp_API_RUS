// Обёртка UI примера для демонстрации камеры преследования от третьего лица.
// Создаёт элементы управления для фиксированного режима, столкновений, ограничений дистанции, углов и точки привязки.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Настраивает захват мыши и создаёт GUI для настройки параметров PlayerPersecutorComponent.
class PlayerPersecutorSample final : public Unigine::ComponentBase {
	COMPONENT_DEFINE(PlayerPersecutorSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Node, rotator, "");								// Целевой узел для слежения
	PROP_PARAM(Node, persecutor, "", "", "", "filter=PlayerDummy");	// Камера с компонентом

private:
	void init();
	void shutdown();

private:
	SampleDescriptionWindow description_window;		// Окно GUI для элементов управления параметрами
	Unigine::Input::MOUSE_HANDLE mouse_handle_at_init;	// Исходный режим мыши для восстановления
	bool current_mouse_grab_state{false};			// Не используется
	bool mouse_grab_state_at_init{false};			// Исходное состояние захвата для восстановления

	Unigine::WidgetSliderPtr min_distance_slider;
	Unigine::WidgetSliderPtr max_distance_slider;
	Unigine::WidgetSliderPtr min_theta_slider;
	Unigine::WidgetSliderPtr max_theta_slider;
};
