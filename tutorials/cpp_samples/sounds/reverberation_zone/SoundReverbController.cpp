// Демонстрирует зону SoundReverb для эффектов звука окружения. Создаёт объём
// реверберации, влияющий на источники звука в своих границах. Параметры реверберации (плотность,
// диффузия, время затухания, усиление отражений) настраиваются одним ползунком мощности.

#include "SoundReverbController.h"

#include <UnigineVisualizer.h>

REGISTER_COMPONENT(SoundReverbController)

using namespace Unigine;
using namespace Math;


// Создаётся зона реверберации, настраивается ползунок UI.
void SoundReverbController::init()
{
	sound_source = checked_ptr_cast<SoundSource>(sound_node.get());
	if (!sound_source)
		Log::error("SoundReverbController::init(): Sound Source node must be SoundeSource type\n");

	// Создаём зону реверберации с внешними и внутренними (пороговыми) границами
	sound_reverb = SoundReverb::create(vec3(20.0f, 20.0f, 20.0f));
	sound_reverb->setWorldTransform(Mat4_identity);
	sound_reverb->setThreshold(vec3(10.0f, 10.0f, 10.0f));

	update_reverb_settings();

	// Создаём UI настроек с ползунком мощности
	sample_description_window.createWindow();

	sample_description_window.addFloatParameter("Gain:", "Gain", reverb_power, 0.0f, 1.0f,
		[this](float val) {
			reverb_power = val;
			update_reverb_settings();
		});

	Visualizer::setEnabled(true);
}

// Визуализируются зона реверберации и границы источника звука.
void SoundReverbController::update()
{
	if (!sound_reverb || !sound_source)
		return;

	sound_reverb->renderVisualizer();
	sound_source->renderVisualizer();
}

// Визуализатор отключается, UI очищается.
void SoundReverbController::shutdown()
{
	Visualizer::setEnabled(false);
	sample_description_window.shutdown();
}

// Все параметры реверберации выводятся из единого значения мощности.
void SoundReverbController::update_reverb_settings()
{
	// Чем выше мощность, тем меньше плотность/диффузия, дольше затухание, сильнее отражения
	sound_reverb->setDensity(clamp(1.0f - reverb_power, 0.0f, 1.0f));
	sound_reverb->setDiffusion(clamp(1.0f - reverb_power, 0.0f, 1.0f));
	sound_reverb->setDecayTime(clamp(0.1f + 19.9f * reverb_power, 0.1f, 20.0f));
	sound_reverb->setReflectionGain(clamp(3.16f * reverb_power, 0.0f, 2.16f));
	sound_reverb->setLateReverbGain(clamp(10.0f * reverb_power, 0.0f, 10.0f));
}
