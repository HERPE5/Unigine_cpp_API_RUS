// Пример интеграции FMOD Studio API. Демонстрирует аудио на основе событий с управлением
// параметрами (окружение, обороты двигателя), группами громкости VCA и симуляцией эффекта Доплера.
// Движущаяся сфера демонстрирует сдвиг высоты тона на основе скорости для реалистичного звука движения.

#include "FMODStudioSample.h"

#include <UnigineVisualizer.h>
#include <UniginePrimitives.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(FMODStudioSample);

using namespace Unigine;
using namespace Math;
using namespace Unigine::Plugins::FMOD;

// Инициализируется FMOD Studio, загружаются банки, запускаются события.
void FMODStudioSample::init()
{
	sample_description_window.createWindow(Gui::ALIGN_LEFT, 500);

	// Загружаем плагин FMOD
	if (Engine::get()->findPlugin("UnigineFMOD") == -1)
		Engine::get()->addPlugin("UnigineFMOD");
	if (!FMOD::checkPlugin())
	{
		WidgetGroupBoxPtr parameters_groupbox = sample_description_window.getParameterGroupBox();

		auto info_label = WidgetLabel::create();
		info_label->setFontWrap(1);
		info_label->setText("Cannot find FMOD plugin. Please check UnigineFMOD and fmod.dll, fmodL.dll, fmodstudio.dll, fmodstudioL.dll (You can download these files from official site) in bin directory.");

		parameters_groupbox->addChild(info_label);

		return;
	}

	plugin_initialized = true;

	// Создаём две сферы: красную неподвижную (машина) и зелёную движущуюся (демонстрация Доплера)
	car_sphere = Primitives::createSphere(2.0f);
	car_sphere->setMaterialParameterFloat4("albedo_color", vec4(0.4f, 0.0f, 0.0f, 1.0f), 0);

	doppler_sphere = Primitives::createSphere(1.0f);
	doppler_sphere->setMaterialParameterFloat4("albedo_color", vec4(0.0f, 4.0f, 0.0f, 1.0f), 0);
	doppler_sphere->setWorldPosition(start_point);

	// Инициализируем FMOD Studio с поддержкой живого обновления и загружаем звуковые банки
	FMODStudio* studio = FMOD::get()->getStudio();
	studio->useStudioLiveUpdateFlag();
	studio->initStudio();
	studio->loadBank(FileSystem::getAbsolutePath(FileSystem::resolvePartialVirtualPath("fmod_studio/fmod_banks/Master.bank")));
	studio->loadBank(FileSystem::getAbsolutePath(FileSystem::resolvePartialVirtualPath("fmod_studio/fmod_banks/Master.strings.bank")));
	studio->loadBank(FileSystem::getAbsolutePath(FileSystem::resolvePartialVirtualPath("fmod_studio/fmod_banks/Vehicles.bank")));
	studio->loadBank(FileSystem::getAbsolutePath(FileSystem::resolvePartialVirtualPath("fmod_studio/fmod_banks/SFX.bank")));

	// Запускаем зацикленное окружение леса и событие звука двигателя
	forest_event = studio->getEvent("event:/Ambience/Forest");
	if (forest_event)
		forest_event->play();

	engine_event = studio->getEvent("event:/Vehicles/Car Engine");
	if (engine_event)
		engine_event->play();

	// Настраиваем демонстрацию Доплера: двигатель привязан к движущейся сфере
	doppler_engine_event = studio->getEvent("event:/Vehicles/Car Engine");
	if (doppler_engine_event)
	{
		doppler_engine_event->setParent(doppler_sphere);
		doppler_engine_event->setParameter("RPM", 4000);
	}

	// Задаём начальное направление движения для объекта Доплера
	velocity = -Vec3_forward;

	// Загружаем VCA для управления мастер-громкостью окружения
	env_vca = studio->getVCA("vca:/Environment");

	Visualizer::setEnabled(true);
	init_description_window();
}

// Объект Доплера перемещается, скорость звука обновляется.
void FMODStudioSample::update()
{
	if (!plugin_initialized)
		return;

	float dt = Game::getIFps();

	// Симуляция Доплера: движущийся источник звука демонстрирует сдвиг высоты тона
	if (show_doppler_box_check_box->isChecked())
	{
		doppler_sphere->setEnabled(true);

		// Сбрасываем позицию через 2.5 секунды для зацикливания демонстрации
		if (timer >= 2.5f)
		{
			doppler_sphere->setWorldPosition(start_point);
			timer = 0.0f;
		}
		timer += dt;

		// Перезапускаем звук Доплера, если остановлен
		if (doppler_engine_event && !doppler_engine_event->isPlaying() && !doppler_engine_event->isStarting())
		{
			doppler_engine_event->play();
		}

		// Перемещаем сферу и обновляем скорость звука для вычисления высоты тона Доплера
		doppler_sphere->setWorldPosition(doppler_sphere->getWorldPosition() + velocity);
		if (doppler_engine_event)
			doppler_engine_event->setVelocity(velocity);
		Visualizer::renderMessage3D(doppler_sphere->getWorldPosition(), vec3_zero, "Doppler", vec4_white, 0, 20);
	}
	else
	{
		if (doppler_engine_event)
			doppler_engine_event->stop();
		doppler_sphere->setEnabled(false);
	}

	// Отображаем подпись над неподвижной сферой машины
	Visualizer::renderMessage3D(car_sphere->getWorldPosition(), vec3_zero, "Car", vec4_white, 0, 20);
}

// Все события и VCA FMOD освобождаются, плагин выгружается.
void FMODStudioSample::shutdown()
{
	// Освобождаем все события FMOD
	if (engine_event)
	{
		engine_event->release();
		engine_event = nullptr;
	}

	if (doppler_engine_event)
	{
		doppler_engine_event->release();
		doppler_engine_event = nullptr;
	}

	if (forest_event)
	{
		forest_event->release();
		forest_event = nullptr;
	}

	if (env_vca)
	{
		env_vca->release();
		env_vca = nullptr;
	}

	// Выгружаем плагин FMOD
	int idx = Engine::get()->findPlugin("UnigineFMOD");
	if (idx != -1)
	{
		Plugin* plugin = Engine::get()->getPluginInterface(idx);
		Engine::get()->destroyPlugin(plugin);
	}
	plugin_initialized = false;

	car_sphere.deleteLater();
	doppler_sphere.deleteLater();
	Visualizer::setEnabled(false);
	sample_description_window.shutdown();
}

// Создаётся UI с вкладками для управления окружением, двигателем, Доплером и VCA.
void FMODStudioSample::init_description_window()
{
	// Создаём вкладки и элементы управления GUI
	WidgetGroupBoxPtr parameters_groupbox = sample_description_window.getParameterGroupBox();
	WidgetTabBoxPtr tab = WidgetTabBox::create(4, 4);
	parameters_groupbox->addChild(tab, Gui::ALIGN_EXPAND);

	// Вкладка Ambience - параметры ветра, дождя и покрова для события леса
	{
		tab->addTab("Ambience");
		wind_forest_slider = WidgetSlider::create();
		auto wind_label = WidgetLabel::create("Wind");
		tab->addChild(wind_label, Gui::ALIGN_EXPAND);
		tab->addChild(wind_forest_slider, Gui::ALIGN_EXPAND);
		wind_forest_slider->getEventChanged().connect(this, &FMODStudioSample::wind_forest_slider_changed);

		rain_forest_slider = WidgetSlider::create();
		auto forest_label = WidgetLabel::create("Rain");
		tab->addChild(forest_label, Gui::ALIGN_EXPAND);
		tab->addChild(rain_forest_slider, Gui::ALIGN_EXPAND);
		rain_forest_slider->getEventChanged().connect(this, &FMODStudioSample::rain_forest_slider_changed);

		cover_forest_slider = WidgetSlider::create();
		auto cover_label = WidgetLabel::create("Cover");
		tab->addChild(cover_label, Gui::ALIGN_EXPAND);
		tab->addChild(cover_forest_slider, Gui::ALIGN_EXPAND);
		cover_forest_slider->getEventChanged().connect(this, &FMODStudioSample::cover_forest_slider_changed);
	}

	// Вкладка Engine - управление параметром RPM для события двигателя машины
	{
		tab->addTab("Engine");
		engine_slider = WidgetSlider::create();
		engine_slider->setMinValue(0);
		engine_slider->setMaxValue(8000);
		auto label = WidgetLabel::create("RPM");
		tab->addChild(label, Gui::ALIGN_EXPAND);
		tab->addChild(engine_slider, Gui::ALIGN_EXPAND);
		engine_slider->getEventChanged().connect(this, &FMODStudioSample::engine_slider_changed);
	}

	// Вкладка Doppler - движущийся источник звука со сдвигом высоты тона на основе скорости
	{
		tab->addTab("Doppler");
		show_doppler_box_check_box = WidgetCheckBox::create();
		show_doppler_box_check_box->setChecked(false);
		auto label = WidgetLabel::create("Show Doppler Effect");
		tab->addChild(label, Gui::ALIGN_EXPAND);
		tab->addChild(show_doppler_box_check_box, Gui::ALIGN_EXPAND);
		doppler_rpm_slider = WidgetSlider::create();
		doppler_velocity_slider = WidgetSlider::create();
		doppler_rpm_slider->setMaxValue(8000);
		doppler_rpm_slider->setValue(4000);
		tab->addChild(WidgetLabel::create("RPM"), Gui::ALIGN_EXPAND);
		tab->addChild(doppler_rpm_slider, Gui::ALIGN_EXPAND);

		tab->addChild(WidgetLabel::create("Velocity"), Gui::ALIGN_EXPAND);
		tab->addChild(doppler_velocity_slider, Gui::ALIGN_EXPAND);

		doppler_rpm_slider->getEventChanged().connect(this, &FMODStudioSample::doppler_rpm_slider_changed);
		doppler_velocity_slider->getEventChanged().connect(this, &FMODStudioSample::doppler_velocity_slider_changed);
		doppler_velocity_slider->setValue(5);
	}

	// Вкладка VCA - управление мастер-громкостью звуков окружения
	{
		tab->addTab("VCA");
		env_vca_slider = WidgetSlider::create();
		env_vca_slider->setValue(100);
		auto label = WidgetLabel::create("Sounds Volume");
		tab->addChild(label, Gui::ALIGN_EXPAND);
		tab->addChild(env_vca_slider, Gui::ALIGN_EXPAND);
		env_vca_slider->getEventChanged().connect(this, &FMODStudioSample::env_vca_slider_changed);
	}

	parameters_groupbox->arrange();
}

// Громкость VCA устанавливается по значению ползунка.
void FMODStudioSample::env_vca_slider_changed()
{
	// Настраиваем громкость окружения
	if (env_vca)
		env_vca->setVolume(env_vca_slider->getValue() * 0.01f);
}

// Параметр RPM события двигателя обновляется по ползунку.
void FMODStudioSample::engine_slider_changed()
{
	// Устанавливаем RPM для события двигателя
	if (engine_event)
		engine_event->setParameter("RPM", itof(engine_slider->getValue()));
}

// Обновляется параметр ветра окружения леса.
void FMODStudioSample::wind_forest_slider_changed()
{
	// Устанавливаем интенсивность ветра в окружении леса
	if (forest_event)
		forest_event->setParameter("Wind", wind_forest_slider->getValue() * 0.01f);
}

// Обновляется параметр дождя окружения леса.
void FMODStudioSample::rain_forest_slider_changed()
{
	// Устанавливаем интенсивность дождя в окружении леса
	if (forest_event)
		forest_event->setParameter("Rain", rain_forest_slider->getValue() * 0.01f);
}

// Обновляется параметр покрова окружения леса.
void FMODStudioSample::cover_forest_slider_changed()
{
	// Устанавливаем параметр покрова в окружении леса
	if (forest_event)
		forest_event->setParameter("Cover", cover_forest_slider->getValue() * 0.01f);
}

// Обновляется параметр RPM двигателя Доплера.
void FMODStudioSample::doppler_rpm_slider_changed()
{
	// Устанавливаем RPM для события двигателя Доплера
	if (doppler_engine_event)
		doppler_engine_event->setParameter("RPM", itof(doppler_rpm_slider->getValue()));
}

// Обновляется скорость сферы Доплера для сдвига высоты тона.
void FMODStudioSample::doppler_velocity_slider_changed()
{
	// Настраиваем скорость объекта Доплера
	velocity.y = -doppler_velocity_slider->getValue() * 0.1f;
}
