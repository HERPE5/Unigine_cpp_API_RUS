// Демонстрирует WidgetTreeBox для иерархического отображения элементов. Отношения
// родитель-потомок устанавливаются через addItemChild, создавая раскрываемые узлы
// дерева. Изменения выбора вызывают callback EventChanged для вывода в консоль.

#include "TreeBox.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(TreeBox);

using namespace Unigine;
using namespace Math;

// Виджет древовидного списка создаётся с иерархическими элементами родитель-потомок и callback выбора.
void TreeBox::init()
{
	gui = WindowManager::getMainWindow()->getGui();

	widget_treebox = WidgetTreeBox::create(gui);

	gui->addChild(widget_treebox, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	widget_treebox->setPosition(position.get().x, position.get().y);
	widget_treebox->setFontSize(font_size.get());
	widget_treebox->setFontOutline(1);

	// Добавляем первый родительский узел и его дочерние элементы
	widget_treebox->addItem("parent 0");
	widget_treebox->addItem("child 0");
	widget_treebox->addItem("child 1");
	widget_treebox->addItem("child 2");
	// Устанавливаем отношения родитель-потомок по индексу
	widget_treebox->addItemChild(0, 1);
	widget_treebox->addItemChild(0, 2);
	widget_treebox->addItemChild(0, 3);

	// Добавляем второй родительский узел и его дочерние элементы
	widget_treebox->addItem("parent 1");
	widget_treebox->addItem("child 0");
	widget_treebox->addItem("child 1");
	widget_treebox->addItem("child 2");
	widget_treebox->addItemChild(4, 5);
	widget_treebox->addItemChild(4, 6);
	widget_treebox->addItemChild(4, 7);

	// Callback-лямбда отображает текст выбранного элемента при изменении
	widget_treebox->getEventChanged().connect(*this, [this]() {
		String msg = String("TreeBox: ") + widget_treebox->getCurrentItemText();
		Console::onscreenMessageLine(msg.get());
		});

	Console::setOnscreen(true);
}

// Виджет удаляется из GUI, ресурсы освобождаются.
void TreeBox::shutdown()
{
	if (gui)
	{
		gui->removeChild(widget_treebox);

		widget_treebox.deleteLater();
	}

	Console::setOnscreen(false);
}
