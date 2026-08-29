// Демонстрирует WidgetListBox для отображения прокручиваемого списка выбираемых элементов.
// Элементы добавляются программно, а изменения выбора вызывают callback EventChanged,
// который показывает текст выбранного элемента в оверлее консоли.

#include "ListBox.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(ListBox);

using namespace Unigine;
using namespace Math;

// Виджет списка создаётся с примерными элементами, подключается callback выбора.
void ListBox::init()
{
	gui = WindowManager::getMainWindow()->getGui();

	widget_listbox = WidgetListBox::create(gui);

	gui->addChild(widget_listbox, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	widget_listbox->setPosition(position.get().x, position.get().y);
	widget_listbox->setFontSize(font_size.get());
	widget_listbox->setFontOutline(1);
	// Заполняем список примерными элементами
	widget_listbox->addItem("item 0");
	widget_listbox->addItem("item 1");
	widget_listbox->addItem("item 2");

	// Callback-лямбда отображает текст выбранного элемента
	widget_listbox->getEventChanged().connect(*this, [this]() {
		String msg = String("ListBox: ") + widget_listbox->getCurrentItemText();
		Console::onscreenMessageLine(msg.get());
		});

	Console::setOnscreen(true);
}

// Виджет удаляется из GUI, ресурсы освобождаются.
void ListBox::shutdown()
{
	if (gui)
	{
		gui->removeChild(widget_listbox);

		widget_listbox.deleteLater();
	}

	Console::setOnscreen(false);
}
