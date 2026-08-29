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

// Этот компонент демонстрирует анимацию параметров свойств с помощью системы Animation.
// AnimationObjectPropertyParameter позволяет анимировать любой параметр свойства, прикреплённый к узлу.
// Здесь анимируется параметр свойства "speed", который затем управляет вращением объекта в update().
// Этот паттерн полезен для анимаций, управляемых данными, где логика считывает анимированные значения.
class PropertyAnimationSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(PropertyAnimationSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init()
	{
		// Создаются треки анимации и воспроизведение
		create_animations();

		// Создаём примитив box как цель анимации
		box = Primitives::createBox(vec3(1.0f, 1.0f, 1.0f));
		box->setID(123);
		box->setName("box");
		box->setWorldPosition(Vec3(0.f, 0.f, 1.15f));

		PropertyPtr prop = Properties::findPropertyByPath(joinPaths(getWorldRootPath(), "properties", "speed_prop.prop"));
		box->addProperty(prop);

		playback->play();

		// GUI инициализируется вручную, так как SampleGui - простая структура
		gui.init(this);
	}

	void update()
	{
		// Анимированное значение параметра считывается и используется для управления вращением.
		// Система анимации обновляет параметр; игровая логика считывает и применяет его.
		PropertyPtr prop = box->getProperty();
		float speed = prop->getParameterPtr("speed")->getValueFloat();

		box->worldRotate(0.f, 0.f, speed * Game::getIFps());

		// Состояние GUI обновляется вручную каждый кадр
		gui.update();
	}

	void shutdown()
	{
		// Ресурсы GUI освобождаются вручную перед уничтожением компонента
		gui.shutdown();
		playback->stop();
	}

	// Создаётся анимация, изменяющая значение параметра свойства во времени
	void create_animations()
	{
		AnimationTrackPtr track = AnimationTrack::create();

		// AnimationObjectPropertyParameter нацелен на конкретный параметр внутри свойства
		AnimationObjectPropertyParameterPtr anim_obj = AnimationObjectPropertyParameter::create("param");
		track->addObject(anim_obj);

		// Настраиваем привязку: ACCESS_FROM_NODE находит свойство на конкретном узле
		AnimationBindPropertyParameterPtr bind = anim_obj->getBind();
		bind->setAccess(AnimationBindPropertyParameter::ACCESS_FROM_NODE);
		bind->setNodePropertyDescription("speed_prop", 0);	// имя и индекс свойства
		bind->setNodeDescription(123, "box");				// целевой узел
		bind->setParameterPath("speed");					// имя параметра внутри свойства
		anim_obj->setBind(bind);

		// "property_parameter.value_float" - путь модификатора для float-параметров свойств
		AnimationModifierFloatPtr param_modifier = AnimationModifierFloat::create("property_parameter.value_float");
		param_modifier->addValue(0.0f, 0.0f);		// начинаем с 0
		param_modifier->addValue(3.0f, 120.0f);		// ускоряемся до 120
		param_modifier->addValue(9.0f, -120.0f);	// реверсируем до -120
		param_modifier->addValue(12.0f, 0.0f);		// возвращаемся к 0
		track->addObjectModifier(anim_obj, param_modifier);

		playback = AnimationPlayback::create();
		playback->setTrack(track);
		playback->setLoop(true);
	}

	// ========================================================================================

	struct SampleGui
	{
		void init(PropertyAnimationSample *sample)
		{
			this->sample = sample;

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

			speed = add_parameter(gridbox, "speed_prop.speed");
		}

		void update()
		{
			PropertyPtr prop = sample->box->getProperty();
			float prop_speed = prop->getParameterPtr("speed")->getValueFloat();

			speed->setText(String::format("%.2f", prop_speed));
		}

		void shutdown() { sample_description_window.shutdown(); }

		PropertyAnimationSample *sample = nullptr;
		SampleDescriptionWindow sample_description_window;
		WidgetEditLinePtr speed;
	};

	NodePtr box;
	AnimationPlaybackPtr playback;
	SampleGui gui;
};

REGISTER_COMPONENT(PropertyAnimationSample);
