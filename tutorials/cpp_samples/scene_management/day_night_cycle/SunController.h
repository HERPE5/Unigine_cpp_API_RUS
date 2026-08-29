#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineLights.h>
#include <UnigineGame.h>
#include <UnigineConsole.h>

// Управляет вращением направленного света (солнца) в зависимости от времени суток.
// Поддерживает ручную установку времени и непрерывное вращение с настраиваемым масштабом времени.
// Вызывает time_changed_event при обновлении времени, позволяя другим системам реагировать.
class SunController : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(SunController, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component controls sun based on it's own game time and various adjustable parameters");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
public:
	Unigine::Event<float>& getEventOnTimeChanged() { return time_changed_event; };

	void setTime(int t);
	int getTime() { return int(current_time); } // Возвращает время в минутах
	bool isContinuous() { return is_continuous.get() > 0; }
	void setContinuousEnabled(bool value);
	void setTimescale(float timescale);
	float getTimescale() { return timescale.get(); }
	void refreshSunPosition();

private:
	PROP_PARAM(Toggle, is_continuous, true, "", "Is sun moving continuously");
	PROP_PARAM(Float, timescale, 20000.0f, "", "Scale of countinuous time rotation");

	Unigine::EventInvoker<float> time_changed_event;
	Unigine::Math::quat sun_init_tilt = Unigine::Math::quat_identity;


	float current_time = 720 * 60; // В секундах (720 мин = 12:00)
	float max_time_sec = 60 * 60 * 24; // Секунд в сутках (86400)
	void init();
	void update();
};