// Демонстрирует создание WidgetButton с настраиваемым размером, позицией и шрифтом.
// Callback EventClicked отображает сообщение в оверлее консоли при
// нажатии кнопки.

#include "Button.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(Button);

using namespace Unigine;
using namespace Math;

// Виджет кнопки создаётся с текстовой меткой, подключается callback клика.
void Button::init()
{
	gui = WindowManager::getMainWindow()->getGui();

	widget_button = WidgetButton::create(gui, text.get());

	// Добавляем в GUI с выравниванием overlap для абсолютного позиционирования
	gui->addChild(widget_button, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	widget_button->setPosition(position.get().x, position.get().y);
	widget_button->setWidth(size.get().x);
	widget_button->setHeight(size.get().y);
	widget_button->setFontSize(font_size.get());

	// Callback-лямбда отображает сообщение в консоли при клике
	widget_button->getEventClicked().connect(*this, []() {
		Console::onscreenMessageLine("Button Clicked!");
		});

	Console::setOnscreen(true);
}

// Виджет удаляется из GUI, ресурсы освобождаются.
void Button::shutdown()
{
	if (gui)
	{
		gui->removeChild(widget_button);

		widget_button.deleteLater();
	}

	Console::setOnscreen(false);
}
