// Демонстрирует ручную генерацию волн для ObjectWaterGlobal. В ручном режиме
// отдельные волны определяются пользовательскими параметрами (длина, амплитуда, крутизна,
// направление, фаза) вместо использования автоматического спектра волн на основе Beaufort.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>
#include "../../menu_ui/SampleDescriptionWindow.h"

class CustomWaveSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CustomWaveSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Направление ветра влияет на угол распространения волн
	PROP_PARAM(Float, wind_direction_angle, 90.0f);
	// Октавы создают волны на разных частотных масштабах (как в аудио-октавах)
	PROP_PARAM(Int, num_octaves, 5);
	// Несколько волн на октаву добавляют вариативность в каждой полосе частот
	PROP_PARAM(Int, num_waves_per_octave, 4);
	// Крутизна управляет резкостью волн (выше = более острые волны)
	PROP_PARAM(Float, steepness_scale, 1.0f);

private:
	void init();
	void shutdown();

	void refresh_wave_param();

	void init_gui();
	SampleDescriptionWindow sample_description_window;
	// Генератор случайных чисел с зерном для воспроизводимых спектров волн
	Unigine::Math::Random random;
	Unigine::ObjectWaterGlobalPtr water;

	// Среднее значение и разброс определяют диапазоны параметров для рандомизации
	float len_mean = 0.5f;
	float len_spread = 0.5f;
	float amp_mean = 0.5f;
	float amp_spread = 0.5f;
	// Смещение фазы в радианах (диапазон от 0 до 2*PI)
	float phase_mean = 0.0f;
	float phase_spread = Unigine::Math::Consts::PI;
};
