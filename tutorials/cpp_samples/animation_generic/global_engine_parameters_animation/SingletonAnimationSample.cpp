#include <UnigineGame.h>
#include <UnigineEngine.h>
#include <UnigineLogic.h>
#include <UnigineWorld.h>
#include <UnigineAnimation.h>
#include <UniginePrimitives.h>
#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/Utils.h"

using namespace Unigine;
using namespace Math;

// Этот компонент демонстрирует модификаторы анимации синглтонов для глобальных параметров движка.
// В отличие от модификаторов объектов, нацеленных на конкретные узлы/материалы, модификаторы синглтонов
// анимируют глобальные системы, такие как Physics (гравитация) и Render (цвет фона).
// Важно: объекты анимации имеют "время жизни движка" - они сохраняются при смене миров.
// Активные воспроизведения необходимо останавливать при переключении миров, чтобы избежать нежелательных эффектов.
class SingletonAnimationSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(SingletonAnimationSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init()
	{
		// Создаём треки и воспроизведения
		create_animations();

		playback->play();

		gui.init();
	}

	void update()
	{
		gui.update();
	}

	void shutdown()
	{
		gui.shutdown();

		// Треки анимации, воспроизведения и объекты имеют "время жизни движка" - они существуют
		// с момента создания до завершения работы движка и сохраняются между разными мирами.
		// Активные воспроизведения необходимо останавливать при переключении миров, чтобы предотвратить их продолжение.
		playback->stop();

		// Цвет затухания рендера восстанавливается до прозрачного чёрного
		Render::setBackgroundColor(vec4(0.f, 0.f, 0.f, 0.f));
	}

	// Создаём трек анимации с модификаторами синглтонов для глобальных параметров движка
	void create_animations()
	{
		// Создаём новый трек
		AnimationTrackPtr track = AnimationTrack::create();

		// Модификатор для компонента Z Physics::gravity (глобальный параметр движка)
		// addValue(time_sec, value) добавляет ключевой кадр: время в секундах и значение в этот момент
		auto gravity_modifier = AnimationModifierFloat::create("physics.gravity_z");
		gravity_modifier->addValue(0.0f, -9.8f);	// нормальная гравитация
		gravity_modifier->addValue(3.0f, 2.5f);		// обратная (объекты всплывают)
		gravity_modifier->addValue(4.0f, -1.0f);
		gravity_modifier->addValue(5.0f, -4.5f);
		gravity_modifier->addValue(6.0f, -9.8f);	// нормальная гравитация
		// addSingletonModifier() нацелен на глобальное состояние движка, привязка объекта не нужна
		track->addSingletonModifier(gravity_modifier);

		// Модификатор для альфа-компонента Render::backgroundColor (глобальный параметр движка)
		// Альфа, стремящаяся к 1, создаёт эффект затухания к белому
		auto color_modifier = AnimationModifierFloat::create("render.background_color_w");
		color_modifier->addValue(0.0f, 0.0f);
		color_modifier->addValue(3.0f, 1.0f);	// полное затухание к белому
		color_modifier->addValue(4.0f, 1.0f);
		color_modifier->addValue(5.0f, 0.5f);
		color_modifier->addValue(6.0f, 0.0f);
		track->addSingletonModifier(color_modifier);

		playback = AnimationPlayback::create();
		playback->setTrack(track);
		playback->setLoop(true);

		// Треки и воспроизведения можно сериализовать на диск для повторного использования
		Dir::mkdir(FileSystem::getAbsolutePath(joinPaths(getWorldRootPath(), "tracks")));
		Animations::saveTrack(track, joinPaths(getWorldRootPath(), "tracks", "singletons.utrack"));
		Animations::savePlayback(playback, joinPaths(getWorldRootPath(), "tracks", "singletons.uplay"));

		// Загружаем сохранённое воспроизведение обратно с диска (демонстрирует цикл сериализации)
		Animations::RESULT result = Animations::loadPlayback(joinPaths(getWorldRootPath(), "tracks", "singletons.uplay"));
		if (result != Animations::RESULT_PLAYBACK_ERROR)
		{
			// Доступ к загруженным анимациям по пути, GUID или индексу
			playback = Animations::getPlaybackByPath(joinPaths(getWorldRootPath(), "tracks", "singletons.uplay"));
		}
	}

	// ========================================================================================

	struct SampleGui
	{
		void init()
		{
			sample_description_window.createWindow();

			auto w = sample_description_window.getWindow();
			auto state_gbox = WidgetGroupBox::create("State", 9, 3);
			w->addChild(state_gbox);

			auto gridbox = WidgetGridBox::create(2);
			state_gbox->addChild(gridbox, Gui::ALIGN_LEFT);

			auto add_parameter = [](const WidgetGridBoxPtr &gridbox, const char *name) {
				auto hbox = WidgetHBox::create();

				hbox->addChild(WidgetLabel::create(name));
				hbox->addChild(WidgetHBox::create(6));

				gridbox->addChild(hbox, Gui::ALIGN_LEFT);

				auto bg_color = WidgetEditLine::create();
				bg_color->setEditable(false);
				bg_color->setFontVOffset(-2);
				bg_color->setFontColor(vec4(vec3(.9f), 1.f));
				bg_color->setWidth(50);

				gridbox->addChild(bg_color, Gui::ALIGN_LEFT);
				return bg_color;
			};

			bg_color = add_parameter(gridbox, "render.background_color.a");
			gravity = add_parameter(gridbox, "physics.gravity.z");
		}

		void update()
		{
			bg_color->setText(String::format("%.2f", Render::getBackgroundColor().w));
			gravity->setText(String::format("%.1f", Physics::getGravity().z));
		}

		void shutdown() { sample_description_window.shutdown(); }

		SampleDescriptionWindow sample_description_window;
		WidgetEditLinePtr bg_color;
		WidgetEditLinePtr gravity;
	};

	AnimationPlaybackPtr playback;
	SampleGui gui;
};

REGISTER_COMPONENT(SingletonAnimationSample);
