// Демонстрирует воспроизведение окружающего (непозиционного) звука с помощью AmbientSource.
// Поддерживает воспроизведение/остановку, зацикливание, управление громкостью, высотой тона и переключение
// режима потока/буфера. Идеально подходит для фоновой музыки и звуков UI, не требующих 3D-позиционирования.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Воспроизводит непозиционное аудио с переключением режима потока во время выполнения.
class SoundAmbient : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SoundAmbient, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Путь к аудиофайлу для воспроизведения
	PROP_PARAM(File, sound_file);

private:
	void init();
	void shutdown();

	void change_souce_type();

private:
	// Источник аудио для непозиционного воспроизведения
	Unigine::AmbientSourcePtr ambient_source;
	// Текущий режим воспроизведения (true = потоковый, false = буферизованный)
	bool is_stream = false;

	SampleDescriptionWindow sample_description_window;
};
