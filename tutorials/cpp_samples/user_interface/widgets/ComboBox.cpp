// Демонстрирует WidgetComboBox как выпадающий виджет выбора. Элементы добавляются
// программно, а изменения выбора вызывают callback EventChanged, который
// показывает текст выбранного элемента в оверлее консоли.

#include "ComboBox.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(ComboBox);

using namespace Unigine;
using namespace Math;

// Виджет выпадающего списка создаётся с примерными элементами, подключается callback выбора.
void ComboBox::init()
{
	gui = WindowManager::getMainWindow()->getGui();

	widget_combobox = WidgetComboBox::create(gui);

	gui->addChild(widget_combobox, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	widget_combobox->setPosition(position.get().x, position.get().y);
	widget_combobox->setFontSize(font_size.get());

	// Заполняем выпадающий список примерными элементами
	widget_combobox->addItem("item 0");
	widget_combobox->addItem("item 1");
	widget_combobox->addItem("item 2");

	// Callback-лямбда отображает текст выбранного элемента
	widget_combobox->getEventChanged().connect(*this, [this]() {
		String msg = String("ComboBox: ") + widget_combobox->getCurrentItemText();
		Console::onscreenMessageLine(msg.get());
		});

	Console::setOnscreen(true);
}

// Виджет удаляется из GUI, ресурсы освобождаются.
void ComboBox::shutdown()
{
	if (gui)
	{
		gui->removeChild(widget_combobox);

		widget_combobox.deleteLater();
	}

	Console::setOnscreen(false);
}
