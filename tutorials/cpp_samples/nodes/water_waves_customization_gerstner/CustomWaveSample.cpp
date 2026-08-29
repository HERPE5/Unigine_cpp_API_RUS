// Демонстрирует ручную генерацию волн для ObjectWaterGlobal. В ручном режиме
// отдельные волны определяются пользовательскими параметрами (длина, амплитуда, крутизна,
// направление, фаза) вместо использования автоматического спектра волн на основе Beaufort.

#include "CustomWaveSample.h"

REGISTER_COMPONENT(CustomWaveSample);

using namespace Unigine;
using namespace Math;

void CustomWaveSample::init()
{
	// Переключаемся на пользовательский пресет геометрии воды (индекс 4)
	// Он обеспечивает точный контроль над тесселяцией и настройками LOD
	Render::setWaterGeometryPreset(4);
	// Маленький размер полигона = более высокая тесселяция для детализированных форм волн
	Render::setWaterGeometryPolygonSize(0.01f);
	// Линейная прогрессия (1) для равномерной тесселяции по дистанции
	Render::setWaterGeometryProgression(1);
	// Subpixel reduction управляет агрессивностью LOD для мелких полигонов
	Render::setWaterGeometrySubpixelReduction(6);

	water = ObjectWaterGlobal::create();
	// Ручной режим отключает автоматическую генерацию волн на основе Beaufort
	// Волны должны добавляться явно через addWave()
	water->setWavesMode(ObjectWaterGlobal::WAVES_MODE_MANUAL);


	init_gui();
	refresh_wave_param();
}

void CustomWaveSample::shutdown()
{
	// deleteLater() обеспечивает безопасное удаление в конце кадра
	water.deleteLater();
	sample_description_window.shutdown();
}

void CustomWaveSample::init_gui()
{
	sample_description_window.createWindow();

	// Октавы представляют полосы частот (каждая октава удваивает длину волны)
	sample_description_window.addIntParameter("Number of Octaves", "", num_octaves, 1, 5, [this](int v)
	{
		num_octaves = v;
		refresh_wave_param();
	});

	// Больше волн на октаву создаёт более богатую, сложную поверхность воды
	sample_description_window.addIntParameter("Number of Waves Per Octave", "", num_waves_per_octave, 1, 10, [this](int v)
	{
		num_waves_per_octave = v;
		refresh_wave_param();
	});

	// Крутизна влияет на остроту волн (параметр волны Герстнера)
	sample_description_window.addFloatParameter("Stepness Scale", "", steepness_scale, 0.01f, 1.0f, [this](float v)
	{
		steepness_scale = v;
		refresh_wave_param();
	});

	// Length mean: центральное значение для рандомизации длины волны
	sample_description_window.addFloatParameter("Length Mean", "", len_mean, 0.0f, 2.0f, [this](float v)
	{
		len_mean = v;
		refresh_wave_param();
	});

	// Length spread: диапазон вариации вокруг среднего (+/- это значение)
	sample_description_window.addFloatParameter("Length Spread", "", len_spread, 0.0f, 2.0f, [this](float v)
	{
		len_spread = v;
		refresh_wave_param();
	});

	sample_description_window.addFloatParameter("Amplitude Mean", "", amp_mean, 0.0f, 25.0f, [this](float v)
	{
		amp_mean = v;
		refresh_wave_param();
	});

	sample_description_window.addFloatParameter("Amplitude Spread", "", amp_spread, 0.0f, 25.0f, [this](float v)
	{
		amp_spread = v;
		refresh_wave_param();
	});

	// Смещение фазы сдвигает позицию волны вдоль её направления
	sample_description_window.addFloatParameter("Phase Offset Mean", "", phase_mean, 0.0f, Consts::PI2, [this](float v)
	{
		phase_mean = v;
		refresh_wave_param();
	});

	sample_description_window.addFloatParameter("Phase Offset Spread", "", phase_spread, 0.0f, Consts::PI2, [this](float v)
	{
		phase_spread = v;
		refresh_wave_param();
	});
}

void CustomWaveSample::refresh_wave_param()
{
	// Вычисляем диапазоны min/max из среднего +/- разброс, ограниченные допустимыми пределами
	const float len_min = Unigine::Math::clamp(len_mean - len_spread, 0.0f, 100.0f);
	const float len_max = Unigine::Math::clamp(len_mean + len_spread, 0.0f, 100.0f);
	const float amplitude_min = Unigine::Math::clamp(amp_mean - amp_spread, 0.0f, 100.0f);
	const float amplitude_max = Unigine::Math::clamp(amp_mean + amp_spread, 0.0f, 100.0f);
	// Фаза может быть отрицательной для обратного смещения
	const float phase_min = Unigine::Math::clamp(phase_mean - phase_spread, -Consts::PI2, Consts::PI2);
	const float phase_max = Unigine::Math::clamp(phase_mean + phase_spread, -Consts::PI2, Consts::PI2);

	// Удаляем все существующие волны перед регенерацией
	// Удаление выполняется с конца, чтобы избежать проблем со сдвигом индексов
	while (water->getNumWaves())
		water->removeWave(water->getNumWaves() - 1);

	// Направление ветра - основной угол распространения для всех волн
	water->setWindDirectionAngle(wind_direction_angle);

	float num_waves = (float)(num_octaves * num_waves_per_octave);
	// Обратная величина для нормализации амплитуды по количеству волн
	float inv_num_waves = rcp(num_waves);
	for (int i = 0; i < num_octaves; i++)
	{
		for (int j = 0; j < num_waves_per_octave; j++)
		{
			// Устанавливаем детерминированное зерно на основе индекса волны для воспроизводимых результатов
			// Одинаковые параметры всегда дают идентичные спектры волн
			random.setSeed(num_waves_per_octave * i + j);

			// Длина волны удваивается с каждой октавой (масштабирование степенями 2)
			// Более высокие октавы = более длинные, медленные волны
			float wave_length = powf(2.0f, float(i - 1) + random.getFloat(len_min, len_max));

			// Амплитуда нормализуется по количеству волн, чтобы предотвратить чрезмерную высоту
			// 0.25f - максимальная относительная высота на волну
			float amplitude = (float(i) + random.getFloat(amplitude_min, amplitude_max)) * inv_num_waves * 0.25f;

			// Направление меняется в пределах +/- 70 градусов от направления ветра
			// Создаёт реалистичный паттерн распространения волн
			float direction_angle = random.getFloat(-1.0f, 1.0f) * 140.0f + wind_direction_angle;

			float phase_offset = random.getFloat(phase_min, phase_max);

			// Формула крутизны предотвращает самозацикливание волн
			// Основана на физике волн Герстнера: steepness = Q / (amplitude * k * n)
			// где k = 2*PI/wavelength, n = количество волн
			float steepness = steepness_scale / max(amplitude * (Consts::PI / wave_length) * num_waves, Consts::EPS);

			// Добавляем настроенную волну на поверхность воды
			water->addWave(wave_length, amplitude, steepness, direction_angle, phase_offset);
		}
	}
}
