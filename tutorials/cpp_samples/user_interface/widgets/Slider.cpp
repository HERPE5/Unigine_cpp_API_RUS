// Демонстрирует WidgetSlider для выбора значения через перетаскиваемый ползунок. Размеры
// слайдера и ширина кнопки настраиваются через свойства компонента, изменения значения
// отображаются в оверлее консоли через callback EventChanged.

#include "Slider.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(Slider);

using namespace Unigine;
using namespace Math;

// Виджет слайдера создаётся с настроенными размерами и callback изменения значения.
void Slider::init()
{
	gui = WindowManager::getMainWindow()->getGui();

	widget_slider = WidgetSlider::create(gui);

	gui->addChild(widget_slider, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	widget_slider->setPosition(position.get().x, position.get().y);
	widget_slider->setWidth(size.get().x);
	widget_slider->setHeight(size.get().y);
	widget_slider->setButtonWidth(button_width.get());

	// Callback-лямбда отображает текущее значение слайдера при изменении
	widget_slider->getEventChanged().connect(*this, [this]() {
		String msg = String("Slider: ") + String::itoa(widget_slider->getValue());
		Console::onscreenMessageLine(msg.get());
		});

	Console::setOnscreen(true);
}

// Виджет удаляется из GUI, ресурсы освобождаются.
void Slider::shutdown()
{
	if (gui)
	{
		gui->removeChild(widget_slider);

		widget_slider.deleteLater();
	}

	Console::setOnscreen(false);
}
