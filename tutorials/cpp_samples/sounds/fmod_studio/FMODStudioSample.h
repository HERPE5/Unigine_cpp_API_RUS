// Пример интеграции FMOD Studio API, демонстрирующий аудио на основе событий.
// Показывает управление параметрами (окружение, обороты двигателя), группы громкости VCA и эффект Доплера.
// Движущаяся сфера демонстрирует сдвиг высоты тона на основе скорости для реалистичного звука движения.

#pragma once

#include <UnigineComponentSystem.h>
#include <plugins/Unigine/FMOD/UnigineFMOD.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Демонстрирует события FMOD Studio, параметры, VCA и симуляцию эффекта Доплера.
class FMODStudioSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(FMODStudioSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();

	void init_description_window();

	void env_vca_slider_changed();
	void engine_slider_changed();
	void wind_forest_slider_changed();
	void rain_forest_slider_changed();
	void cover_forest_slider_changed();
	void doppler_rpm_slider_changed();
	void doppler_velocity_slider_changed();

	// Отслеживает, успешно ли загрузился плагин FMOD
	bool plugin_initialized = false;

	// Таймер сброса позиции объекта Доплера
	float timer = 0.0f;

	// Неподвижная сфера, представляющая позицию звука машины
	Unigine::ObjectMeshDynamicPtr car_sphere;
	// Движущаяся сфера для демонстрации эффекта Доплера
	Unigine::ObjectMeshDynamicPtr doppler_sphere;

	// Экземпляры событий FMOD Studio для разных звуков
	Unigine::Plugins::FMOD::EventInstance *engine_event = nullptr;
	Unigine::Plugins::FMOD::EventInstance *doppler_engine_event = nullptr;
	Unigine::Plugins::FMOD::EventInstance *forest_event = nullptr;
	// VCA для управления громкостью группы звуков окружения
	Unigine::Plugins::FMOD::VCA *env_vca = nullptr;

	// Текущая скорость сферы Доплера для вычисления высоты тона
	Unigine::Math::Vec3 velocity;
	// Начальная позиция для сброса сферы Доплера
	Unigine::Math::Vec3 start_point = Unigine::Math::Vec3(-5, 80, 0);

	SampleDescriptionWindow sample_description_window;
	// Элементы управления UI для различных аудиопараметров
	Unigine::WidgetSliderPtr engine_slider;
	Unigine::WidgetSliderPtr wind_forest_slider;
	Unigine::WidgetSliderPtr rain_forest_slider;
	Unigine::WidgetSliderPtr cover_forest_slider;
	Unigine::WidgetSliderPtr env_vca_slider;
	Unigine::WidgetSliderPtr doppler_rpm_slider;
	Unigine::WidgetSliderPtr doppler_velocity_slider;
	Unigine::WidgetCheckBoxPtr show_doppler_box_check_box;
};