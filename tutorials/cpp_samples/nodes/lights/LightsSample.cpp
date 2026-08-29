// Демонстрирует три основных типа источников света: World, Omni и Projected.
// World light имитирует солнце с атмосферным рассеиванием.
// Omni light излучает во всех направлениях из точки с опциональными профилями IES.
// Projected light отбрасывает конус света с настраиваемыми FOV и полутенью.

#include <UnigineComponentSystem.h>
#include <UnigineVisualizer.h>
#include <UnigineLights.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

using namespace Unigine;
using namespace Math;

class LightSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(LightSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init()
	{
		// Создаём по одному экземпляру каждого типа источника света
		create_world_light();
		create_omni_light();
		create_projected_light();

		// Включаем визуализатор для отображения форм и радиусов источников света
		visualizer_enabled = Visualizer::isEnabled();
		Visualizer::setEnabled(true);

		gui.init(this);
	}

	void update()
	{
		// Отрисовываем визуализацию объёмов источников света (у world light нет локального объёма)
		omni_light->renderVisualizer();
		proj_light->renderVisualizer();
	}

	void shutdown()
	{
		gui.shutdown();
		Visualizer::setEnabled(visualizer_enabled);
	}

	void create_world_light()
	{
		// LightWorld: направленный источник света, имитирующий солнце/луну с бесконечной дальностью
		world_light = LightWorld::create(vec4_white);

		// Режим температуры вычисляет цвет из значения в Кельвинах (6500K = дневной свет)
		world_light->setColorMode(Light::COLOR_MODE_TEMPERATURE);
		world_light->setColorTemperature(6500.f);
		world_light->setIntensity(1.f);

		// Включаем атмосферное рассеивание для реалистичного рендеринга неба
		world_light->setScattering(LightWorld::SCATTERING_SUN);

		// Вращение управляет направлением света (угол солнца в небе)
		world_light->setWorldRotation(quat(273.f, 330.f, 120.f));
	}

	void create_omni_light()
	{
		// LightOmni: точечный источник света, излучающий равномерно во всех направлениях
		// Параметры: цвет, дистанция затухания, имя
		omni_light = LightOmni::create(vec4_white, 20.f, "omni");

		// Сферическая форма создаёт мягкие тени area light (более реалистично)
		omni_light->setShapeType(Light::SHAPE_SPHERE);
		omni_light->setShapeRadius(0.17f);

		// Расстояние, на котором интенсивность света достигает нуля
		omni_light->setAttenuationDistance(20.f);

		// Режим IES использует фотометрические профили для реалистичного распределения света
		omni_light->setShadowColorTextureMode(Light::SHADOW_COLOR_MODE_IES);

		// Текстуру можно загрузить по пути или назначить напрямую
		omni_light->setTextureFilePath(FileSystem::resolvePartialVirtualPath("white.texture"));

		// Тёплая цветовая температура (3165K = лампа накаливания)
		omni_light->setColorMode(Light::COLOR_MODE_TEMPERATURE);
		omni_light->setColorTemperature(3165.f);
		omni_light->setIntensity(1.3f);

		omni_light->setWorldPosition(Vec3(1.1f, -1.3f, 2.2f));
	}

	void create_projected_light()
	{
		// LightProj: прожектор, отбрасывающий конус света
		// Параметры: цвет, дистанция затухания, угол FOV, имя
		proj_light = LightProj::create(vec4_white, 20.f, 70.f, "proj");

		// Тёпло-нейтральная цветовая температура (4000K = люминесцентная лампа)
		proj_light->setColorMode(Light::COLOR_MODE_TEMPERATURE);
		proj_light->setColorTemperature(4000.f);
		proj_light->setIntensity(1.3f);

		// Точечная форма создаёт резкие тени (идеально для прожекторов)
		proj_light->setShapeType(Light::SHAPE_POINT);

		// Угол конуса от центра до края
		proj_light->setFov(70.f);

		proj_light->setAttenuationDistance(20.f);
		// Полутень: плавный переход от освещённой области к теневой (0-1)
		proj_light->setPenumbra(0.15f);

		// Устанавливаем режим текстуры цвета тени в SHADOW_COLOR_MODE_SIMPLE, чтобы можно было использовать любую 2D-текстуру
		proj_light->setShadowColorTextureMode(Light::SHADOW_COLOR_MODE_SIMPLE);

		proj_light->setTextureFilePath(FileSystem::resolvePartialVirtualPath("white.texture"));

		proj_light->setWorldPosition(Vec3(-0.8f, -1.1f, 2.3f));
		// Вращение определяет направление света
		proj_light->setWorldRotation(quat(30.f, 343.f, 331.f));
	}

	// ========================================================================================

	struct SampleGui
	{
		void init(LightSample *sample)
		{
			this->sample = sample;

			sample_description_window.createWindow();

			// Вращение world light (имитирует движение солнца)
			sample_description_window.addFloatParameter(
				"world light angle",
				"Change the rotation of the LightWorld.",
				273.f,
				273.f,
				360.f,
				[sample](float value) {
					sample->world_light->setWorldRotation(quat(value, 330.f, 120.f));
				}
			);

			sample_description_window.addParameterSpacer();

			// Управление яркостью omni light
			sample_description_window.addFloatParameter(
				"omni light intensity",
				"Change the light intensity of the LightOmni.",
				1.3f,
				0.f,
				2.f,
				[sample](float value) {
					sample->omni_light->setIntensity(value);
				}
			);

			// Теплота/холодность цвета omni light
			sample_description_window.addFloatParameter(
				"omni light color temperature",
				"Change the color temperature of the LightOmni.",
				3165.f,
				1000.f,
				10'000.f,
				[sample](float value) {
					sample->omni_light->setColorTemperature(value);
				}
			);

			sample_description_window.addParameterSpacer();

			// Мягкость краёв projected light
			sample_description_window.addFloatParameter(
				"projected light penumbra",
				"Change the penumbra parameter of the LightProj.",
				.15f,
				0.f,
				1.f,
				[sample](float value) {
					sample->proj_light->setPenumbra(value);
				}
			);

			// Угол конуса projected light
			sample_description_window.addFloatParameter(
				"projected light fov",
				"Change the FOV of the LightProj.",
				75.f,
				0.f,
				120.f,
				[sample](float value) {
					sample->proj_light->setFov(value);
				}
			);
		}

		void shutdown() { sample_description_window.shutdown(); }

		SampleDescriptionWindow sample_description_window;
		LightSample *sample = nullptr;
	};

	// ========================================================================================

	// Глобальный направленный источник света (солнце/луна)
	LightWorldPtr world_light;
	// Точечный источник света, излучающий во всех направлениях
	LightOmniPtr omni_light;
	// Прожектор с конусообразным освещением
	LightProjPtr proj_light;

	// Сохранённое состояние визуализатора для восстановления
	bool visualizer_enabled = false;

	SampleGui gui;
};

REGISTER_COMPONENT(LightSample);
