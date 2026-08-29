// Демонстрирует 3D-позиционный звук с помощью узла SoundSource.
// Звук пространственно позиционируется в зависимости от расстояния до слушателя с настраиваемым затуханием.
// Поддерживает потоковый режим, зацикливание, управление громкостью, высотой тона и отладочную визуализацию.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Создаёт и управляет 3D-позиционным источником звука в сцене.
class SoundSourceController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SoundSourceController, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Путь к аудиофайлу для воспроизведения
	PROP_PARAM(File, sound_file);

private:
	void init();
	void update();
	void shutdown();

private:
	// Узел 3D-позиционного источника звука
	Unigine::SoundSourcePtr sound_source;

	SampleDescriptionWindow sample_description_window;
};
