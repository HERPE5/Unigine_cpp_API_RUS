#pragma once

#include <UnigineComponentSystem.h>

// Источник событий, транслирующий события вращения на основе клавиатурного ввода.
// Демонстрирует EventInvoker для создания пользовательских событий с типизированными параметрами.
// Подписчики могут слушать события отдельных осей или комбинированное событие вращения.
class EventsAdvancedSample
	: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(EventsAdvancedSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates generating rotation events "
							"on key press for subscription by other components.");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// скорость вращения по осям X, Y, Z
	PROP_PARAM(Vec3, rotation_speed, {3.0f, 3.0f, 3.0f});

	// акцессоры для событий вращения
	Unigine::Event<float> &getEventRotateX() { return rotate_x_event; }
	Unigine::Event<float> &getEventRotateY() { return rotate_y_event; }
	Unigine::Event<float> &getEventRotateZ() { return rotate_z_event; }
	Unigine::Event<float, float, float, EventsAdvancedSample *> &getEventRotate() { return rotate_event; }

protected:
	void init();
	void update();
	void shutdown();

private:
	// события, вызываемые клавишами ввода
	Unigine::EventInvoker<float> rotate_x_event;
	Unigine::EventInvoker<float> rotate_y_event;
	Unigine::EventInvoker<float> rotate_z_event;
	Unigine::EventInvoker<float, float, float, EventsAdvancedSample *> rotate_event;
};
