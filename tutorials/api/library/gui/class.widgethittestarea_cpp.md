# Unigine::WidgetHitTestArea Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот класс используется для определения области виджета в окнах движкового стиля и безрамочных системных окнах, пересекаемой курсором, управляемым пользователем. Если тип области hit test — "resize", система автоматически изменяет форму курсора; если область hit test перетаскиваемая, окно можно перетаскивать, кликая и перетаскивая эту область.


В следующем примере системные границы главного окна отключены, и добавлены 2 пользовательские области перетаскивания. Первая область расположена в верхней части окна, вторая — в его центре. Для демонстрации фон включён для обеих областей.


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineWindowManager.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

int AppSystemLogic::init()
{

	// безрамочное главное окно
	EngineWindowViewportPtr main_window = WindowManager::getMainWindow();
	if (main_window)
	{
		// отключаем системные границы
		main_window->setBordersEnabled(false);

		GuiPtr gui = main_window->getSelfGui();

		// добавляем область перетаскивания, похожую на панель заголовка
		WidgetVBoxPtr top_drag_container = WidgetVBox::create(gui);
		main_window->addChild(top_drag_container);

		WidgetHitTestAreaPtr top_drag_area = WidgetHitTestArea::create(gui, EngineWindow::HITTEST_DRAGGABLE);
		top_drag_area->setHeight(25);
		top_drag_container->addChild(top_drag_area, Gui::ALIGN_EXPAND);

		top_drag_area->setBackground(1);
		top_drag_area->setBackgroundColor(Math::vec4_red);

		// добавляем дополнительную область перетаскивания
		WidgetHitTestAreaPtr drag_area = WidgetHitTestArea::create(gui, EngineWindow::HITTEST_DRAGGABLE);
		drag_area->setWidth(512);
		drag_area->setHeight(256);
		main_window->addChild(drag_area, Gui::ALIGN_CENTER);

		drag_area->setBackground(1);
		drag_area->setBackgroundColor(Math::vec4_blue);
	}

	return 1;
}

int AppSystemLogic::shutdown()
{
	// удаляем все подписки на события
	econnections.disconnectAll();

	return 1;
}


```

</details>


## WidgetHitTestArea Class

### Методы класса

## int getHitTestResult () const

Возвращает текущий тип области hit test, одно из значений **[EngineWindow::HITTEST_*](../../../api/library/gui/class.enginewindow_cpp.md#HITTEST_INVALID)**.
### Возвращаемое значение

Текущий тип области hit test.
## void setBackgroundColor ( const Math:: vec4 & color )

Устанавливает новый цвет фона области перетаскивания, используемый для отладки.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет фона.

## Math:: vec4 getBackgroundColor () const

Возвращает текущий цвет фона области перетаскивания, используемый для отладки.
### Возвращаемое значение

Текущий цвет фона.
## void setBackground ( int background )

Устанавливает новый флаг, указывающий, включена ли отрисовка фона для области перетаскивания в целях отладки.
### Аргументы

- *int* **background** - Флаг, указывающий статус отрисовки фона: 1 — включено, 0 — отключено.

## int getBackground () const

Возвращает текущий флаг, указывающий, включена ли отрисовка фона для области перетаскивания в целях отладки.
### Возвращаемое значение

Текущий флаг, указывающий статус отрисовки фона: 1 — включено, 0 — отключено.
---

## WidgetHitTestArea ( const Ptr < Gui > & gui , int hit_test )

Конструктор. Создаёт виджет области hit test и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому принадлежит виджет области hit test.
- *int* **hit_test** - Тип области hit test, одно из значений **[EngineWindow::HITTEST_*](../../../api/library/gui/class.enginewindow_cpp.md#HITTEST_INVALID)**.

## WidgetHitTestArea ( int hit_test )

Конструктор. Создаёт виджет области hit test указанного типа.
### Аргументы

- *int* **hit_test** - Тип области hit test, одно из значений **[EngineWindow::HITTEST_*](../../../api/library/gui/class.enginewindow_cpp.md#HITTEST_INVALID)**.
