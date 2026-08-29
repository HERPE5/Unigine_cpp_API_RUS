// Демонстрирует зону SoundReverb для эффектов звука окружения.
// Создаёт объём реверберации, влияющий на источники звука в своих границах.
// Параметры реверберации управляются одним ползунком мощности для простой настройки.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Создаёт и управляет зоной реверберации, влияющей на ближайшие источники звука.
class SoundReverbController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SoundReverbController, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел источника звука для визуализации
	PROP_PARAM(Node, sound_node, "Sound Source");

private:
	void init();
	void update();
	void shutdown();

	void update_reverb_settings();

private:
	// Источник звука для визуализации
	Unigine::SoundSourcePtr sound_source;

	// Зона реверберации, влияющая на звуки в своих границах
	Unigine::SoundReverbPtr sound_reverb;
	// Главное управляющее значение для всех параметров реверберации (0-1)
	float reverb_power = 0.5f;

	SampleDescriptionWindow sample_description_window;
};
