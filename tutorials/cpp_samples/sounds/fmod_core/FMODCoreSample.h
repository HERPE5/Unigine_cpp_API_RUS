// Пример интеграции FMOD Core API, демонстрирующий низкоуровневое управление аудио.
// Показывает загрузку 2D/3D звука, DSP-эффекты (искажение), управление таймлайном и громкостью.
// Видимая сфера представляет позицию 3D-источника звука в сцене.

#pragma once

#include <UnigineComponentSystem.h>
#include <plugins/Unigine/FMOD/UnigineFMOD.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Демонстрирует FMOD Core API для прямого управления звуком и каналами.
class FMODCoreSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(FMODCoreSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();

	void init_description_window();

	void distortion_changed();
	void volume_changed();
	void plus_ms();
	void minus_ms();
	void play_music();
	void stop_music();
	void toggle_pause_music();
	void play_music_3D();
	void stop_music_3D();
	void toggle_pause_music_3D();

	// Отслеживает, успешно ли загрузился плагин FMOD
	bool plugin_initialized = false;

	// Визуальное представление позиции 3D-звука
	Unigine::ObjectMeshDynamicPtr car_sphere;

	// Объекты звука FMOD для 2D- и 3D-воспроизведения
	Unigine::Plugins::FMOD::Sound *music_sound = nullptr;
	Unigine::Plugins::FMOD::Sound *music_sound_3D = nullptr;
	// Активные каналы воспроизведения для 2D- и 3D-звуков
	Unigine::Plugins::FMOD::Channel *music_channel = nullptr;
	Unigine::Plugins::FMOD::Channel *music_channel_3D = nullptr;

	SampleDescriptionWindow sample_description_window;
	// Элементы управления UI для позиции воспроизведения, эффекта искажения и громкости
	Unigine::WidgetSliderPtr music_position_slider;
	Unigine::WidgetSliderPtr distortion_slider;
	Unigine::WidgetSliderPtr volume_slider;
};