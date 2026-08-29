// Демонстрирует WidgetSpinBox, присоединённый к WidgetEditLine для числового ввода с
// кнопками увеличения/уменьшения. Spinbox размещается поверх строки ввода с помощью
// порядка отрисовки виджетов, изменения значения отображаются в оверлее консоли.

#include "SpinBox.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(SpinBox);

using namespace Unigine;
using namespace Math;

// Spinbox создаётся и присоединяется к строке ввода с callback изменения значения.
void SpinBox::init()
{
	gui = WindowManager::getMainWindow()->getGui();

	// Создаём строку ввода для отображения числового значения
	widget_editline = WidgetEditLine::create(gui, "0");
	widget_editline->setPosition(position.get().x, position.get().y);
	widget_editline->setFontOutline(1);

	gui->addChild(widget_editline, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	// Создаём spinbox и размещаем его поверх строки ввода
	widget_spinbox = WidgetSpinBox::create(gui);
	widget_spinbox->setOrder(widget_editline->getOrder() + 1);
	// Присоединяем spinbox к строке ввода для согласованного позиционирования
	widget_editline->addAttach(widget_spinbox);

	gui->addChild(widget_spinbox, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	// Callback-лямбда отображает текущее значение spinbox при изменении
	widget_spinbox->getEventChanged().connect(*this, [this]() {
		String msg = String("SpinBox: ") + String::itoa(widget_spinbox->getValue());
		Console::onscreenMessageLine(msg.get());
		});

	Console::setOnscreen(true);
}

// Виджеты удаляются из GUI, ресурсы освобождаются.
void SpinBox::shutdown()
{
	if (gui)
	{
		gui->removeChild(widget_editline);
		gui->removeChild(widget_spinbox);

		widget_editline.deleteLater();
		widget_spinbox.deleteLater();
	}

	Console::setOnscreen(false);
}
