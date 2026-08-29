// Пример интеграции FMOD Core API. Демонстрирует загрузку и воспроизведение 2D/3D звуков,
// применение DSP-эффектов (искажение), управление таймлайном и регулировку громкости.
// 3D-звук привязан к видимой сфере для демонстрации пространственного аудио.

#include "FMODCoreSample.h"

#include <UnigineVisualizer.h>
#include <UniginePrimitives.h>

REGISTER_COMPONENT(FMODCoreSample);

using namespace Unigine;
using namespace Math;
using namespace Unigine::Plugins::FMOD;

// Загружается плагин FMOD, создаются звуки, настраивается UI.
void FMODCoreSample::init()
{
	sample_description_window.createWindow(Gui::ALIGN_LEFT, 500);

	// Загружаем плагин FMOD
	if(Engine::get()->findPlugin("UnigineFMOD") == -1)
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

	// Инициализируем FMOD Core с 1024 каналами в режиме NORMAL
	FMODCore *core = FMOD::get()->getCore();
	core->initCore(1024, FMODEnums::NORMAL);

	// Загружаем саундтрек как 2D-звук (без пространственного позиционирования)
	music_sound = core->createSound(
		FileSystem::getAbsolutePath(FileSystem::resolvePartialVirtualPath("fmod_core/sounds/soundtrack.oga")),
		FMODEnums::_2D);

	// Загружаем тот же файл как 3D-звук (позиционируется в зависимости от позиции слушателя)
	music_sound_3D = core->createSound(
		FileSystem::getAbsolutePath(FileSystem::resolvePartialVirtualPath("fmod_core/sounds/soundtrack.oga")),
		FMODEnums::_3D);

	// Создаём красную сферу для визуализации позиции 3D-источника звука
	car_sphere = Primitives::createSphere(1.0f);
	car_sphere->setMaterialParameterFloat4("albedo_color", vec4(0.4f, 0.0f, 0.0f, 1.0f), 0);

	Visualizer::setEnabled(true);
	init_description_window();
}

// Обновляется ползунок прогресса, рендерится 3D-подпись.
void FMODCoreSample::update()
{
	if (!plugin_initialized)
		return;

	// Отображаем подпись "Music 3D" над сферой в 3D-мире
	auto len = music_sound->getLength(FMODEnums::TIME_UNIT::MS);
	Visualizer::renderMessage3D(car_sphere->getWorldPosition(), vec3_zero, "Music 3D", vec4_white, 0, 25);

	// Обновляем ползунок прогресса; сбрасываем и останавливаем по завершении трека
	unsigned int pos;
	if (music_channel)
	{
		music_channel->getPositionTimeLine(pos, FMODEnums::TIME_UNIT::MS);
		int progress = ftoi(pos / itof(len) * 100);
		if (progress >= 100)
		{
			music_channel->setPositionTimeLine(0, FMODEnums::TIME_UNIT::MS);
			stop_music();
			progress = 0;
		}
		music_position_slider->setValue(progress);
	}
}

// Все ресурсы FMOD освобождаются, плагин выгружается.
void FMODCoreSample::shutdown()
{
	// Освобождаем все звуки и каналы FMOD
	if (music_sound)
	{
		music_sound->release();
		music_sound = nullptr;
	}

	if (music_sound_3D)
	{
		music_sound_3D->release();
		music_sound_3D = nullptr;
	}

	if (music_channel)
	{
		music_channel->release();
		music_channel = nullptr;
	}

	if (music_channel_3D)
	{
		music_channel_3D->release();
		music_channel_3D = nullptr;
	}

	// Выгружаем плагин FMOD
	int idx = Engine::get()->findPlugin("UnigineFMOD");
	if (idx != -1)
	{
		Plugin *plugin = Engine::get()->getPluginInterface(idx);
		Engine::get()->destroyPlugin(plugin);
	}
	plugin_initialized = false;

	car_sphere.deleteLater();
	Visualizer::setEnabled(false);
	sample_description_window.shutdown();
}

// Создаётся UI с вкладками для управления 2D- и 3D-музыкой.
void FMODCoreSample::init_description_window()
{
	// Создаём вкладки и элементы управления GUI
	WidgetGroupBoxPtr parameters_groupbox = sample_description_window.getParameterGroupBox();
	WidgetTabBoxPtr tab = WidgetTabBox::create(4, 4);
	parameters_groupbox->addChild(tab, Gui::ALIGN_EXPAND);

	// Вкладка 2D Music - элементы управления воспроизведением, таймлайн, искажение и громкость
	{
		tab->addTab("Music");

		// Создаём кнопки управления воспроизведением
		auto play_button = WidgetButton::create("Play");
		auto stop_button = WidgetButton::create("Stop");
		auto pause_button = WidgetButton::create("Pause/Resume");
		auto plus_button = WidgetButton::create("+ 10 sec");
		auto minus_button = WidgetButton::create("- 10 sec");

		auto hbox = WidgetHBox::create();
		play_button->getEventClicked().connect(this, &FMODCoreSample::play_music);
		stop_button->getEventClicked().connect(this, &FMODCoreSample::stop_music);
		pause_button->getEventClicked().connect(this, &FMODCoreSample::toggle_pause_music);

		minus_button->getEventClicked().connect(this, &FMODCoreSample::minus_ms);
		plus_button->getEventClicked().connect(this, &FMODCoreSample::plus_ms);

		music_position_slider = WidgetSlider::create();

		distortion_slider = WidgetSlider::create();
		distortion_slider->getEventChanged().connect(this, &FMODCoreSample::distortion_changed);

		volume_slider = WidgetSlider::create();
		volume_slider->getEventChanged().connect(this, &FMODCoreSample::volume_changed);
		volume_slider->setValue(100);
		hbox->addChild(minus_button);
		hbox->addChild(plus_button);

		tab->addChild(WidgetLabel::create("Time Line"), Gui::ALIGN_EXPAND);
		tab->addChild(music_position_slider, Gui::ALIGN_EXPAND);


		tab->addChild(hbox, Gui::ALIGN_EXPAND);
		tab->addChild(play_button, Gui::ALIGN_EXPAND);
		tab->addChild(stop_button, Gui::ALIGN_EXPAND);
		tab->addChild(pause_button, Gui::ALIGN_EXPAND);

		tab->addChild(WidgetLabel::create("Distortion Mix"), Gui::ALIGN_EXPAND);
		tab->addChild(distortion_slider, Gui::ALIGN_EXPAND);

		tab->addChild(WidgetLabel::create("Volume"), Gui::ALIGN_EXPAND);
		tab->addChild(volume_slider, Gui::ALIGN_EXPAND);
	}

	// Вкладка 3D Music - элементы управления пространственным аудио
	{
		tab->addTab("Music 3D");
		auto play_button = WidgetButton::create("Play");
		auto stop_button = WidgetButton::create("Stop");
		auto pause_button = WidgetButton::create("Pause/Resume");

		auto hbox = WidgetHBox::create();
		play_button->getEventClicked().connect(this, &FMODCoreSample::play_music_3D);
		stop_button->getEventClicked().connect(this, &FMODCoreSample::stop_music_3D);
		pause_button->getEventClicked().connect(this, &FMODCoreSample::toggle_pause_music_3D);

		tab->addChild(play_button, Gui::ALIGN_EXPAND);
		tab->addChild(stop_button, Gui::ALIGN_EXPAND);
		tab->addChild(pause_button, Gui::ALIGN_EXPAND);
	}

	parameters_groupbox->arrange();
}

// Уровень микса DSP-искажения обновляется по значению ползунка.
void FMODCoreSample::distortion_changed()
{
	if (!music_channel)
	{
		return;
	}

	// Настраиваем эффект искажения на музыкальном канале
	music_channel->getDSP(0)->setParameterFloat(0, distortion_slider->getValue() * 0.01f);
}

// Громкость канала обновляется по значению ползунка.
void FMODCoreSample::volume_changed()
{
	if (!music_channel)
	{
		return;
	}

	// Настраиваем громкость на музыкальном канале
	music_channel->setVolume(volume_slider->getValue() * 0.01f);
}

// Позиция воспроизведения продвигается на 10 секунд вперёд.
void FMODCoreSample::plus_ms()
{
	if (!music_channel)
	{
		return;
	}

	// Перепрыгиваем на 10 секунд вперёд по таймлайну
	unsigned int curr_time_line;
	unsigned int len = music_sound->getLength(FMODEnums::TIME_UNIT::MS);
	music_channel->getPositionTimeLine(curr_time_line, FMODEnums::TIME_UNIT::MS);
	if (curr_time_line + 10000 >= len)
	{
		music_channel->setPositionTimeLine(0, FMODEnums::TIME_UNIT::MS);
	} else
	{
		music_channel->setPositionTimeLine(curr_time_line + 10000, FMODEnums::TIME_UNIT::MS);
	}
}

// Позиция воспроизведения перематывается на 10 секунд назад.
void FMODCoreSample::minus_ms()
{
	if (!music_channel)
	{
		return;
	}

	// Перепрыгиваем на 10 секунд назад по таймлайну
	unsigned int curr_time_line;
	music_channel->getPositionTimeLine(curr_time_line, FMODEnums::TIME_UNIT::MS);
	if (curr_time_line < 10000)
	{
		music_channel->setPositionTimeLine(0, FMODEnums::TIME_UNIT::MS);
	} else
	{
		music_channel->setPositionTimeLine(curr_time_line - 10000, FMODEnums::TIME_UNIT::MS);
	}
}

// 2D-звук воспроизводится с DSP-искажением, если 3D неактивен.
void FMODCoreSample::play_music()
{
	// Запускаем 2D-воспроизведение музыки, если 3D-музыка не играет
	// Добавляем эффект искажения DSP и устанавливаем громкость
	if (!music_channel_3D || !music_channel_3D->isPlaying())
	{
		stop_music();

		music_channel = music_sound->play();
		if (!music_channel)
			return;

		music_channel->addDSP(0, DSPType::DISTORTION)->setParameterFloat(0, distortion_slider->getValue() * 0.01f);
		music_channel->setVolume(volume_slider->getValue() * 0.01f);
	}
}

// 2D-музыкальный канал останавливается и освобождается.
void FMODCoreSample::stop_music()
{
	if (!music_channel)
	{
		return;
	}

	music_channel->stop();
	music_channel = nullptr;
}

// Переключается состояние паузы 2D-музыки.
void FMODCoreSample::toggle_pause_music()
{
	if (!music_channel)
	{
		return;
	}

	music_channel->setPaused(!music_channel->isPaused());
}

// 3D-звук воспроизводится в позиции сферы, если 2D неактивен.
void FMODCoreSample::play_music_3D()
{
	// Запускаем 3D-воспроизведение музыки в позиции car_sphere
	if (!music_channel || !music_channel->isPlaying())
	{
		stop_music_3D();

		music_channel_3D = music_sound_3D->play();
		if (!music_channel_3D)
			return;
		music_channel_3D->setPosition(car_sphere->getWorldPosition());
	}
}

// 3D-музыкальный канал останавливается и освобождается.
void FMODCoreSample::stop_music_3D()
{
	if (!music_channel_3D)
	{
		return;
	}

	music_channel_3D->stop();
	music_channel_3D = nullptr;
}

// Переключается состояние паузы 3D-музыки.
void FMODCoreSample::toggle_pause_music_3D()
{
	if (!music_channel_3D)
	{
		return;
	}

	music_channel_3D->setPaused(!music_channel_3D->isPaused());
}
