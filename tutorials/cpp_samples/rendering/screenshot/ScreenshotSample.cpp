// UI примера для запуска захвата скриншота по клику кнопки.
// Скриншот сохраняется в data/screenshot.dds.

#include "ScreenshotSample.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ScreenshotSample);

// Вспомогательный объект скриншота привязывается к главному окну; кнопка UI запускает захват.
void ScreenshotSample::init()
{
	// Подключаем вспомогательный объект скриншота к главному окну приложения
	screenshot.setWindow(WindowManager::getMainWindow());

	// Строим UI примера с информационной меткой и кнопкой захвата
	sample_description_window.createWindow();
	WidgetGroupBoxPtr parameters = sample_description_window.getParameterGroupBox();
	auto info_label = WidgetLabel::create("Screenshot will be saved in <b>data/screenshot.dds</b>");
	info_label->setFontRich(1);
	parameters->addChild(info_label, Gui::ALIGN_EXPAND);

	// Клик кнопки устанавливает флаг grab; фактический захват происходит в конце следующего кадра
	auto screenshot_button = WidgetButton::create("Take Screenshot");
	parameters->addChild(screenshot_button, Gui::ALIGN_EXPAND);
	screenshot_button->getEventClicked().connect(*this, [this]() { screenshot.grab(); });
}

// Окно UI очищается при уничтожении компонента.
void ScreenshotSample::shutdown()
{
	sample_description_window.shutdown();
}
