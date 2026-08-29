# Unigine::UserInterface Class (CPP)

**Header:** #include <UnigineUserInterface.h>


Этот класс используется для работы с виджетами, которые создаются загрузкой UI-файла.


### Примеры использования


Примеры ниже показывают:

- Загрузку UserInterface из файла `*.ui` и доступ к хранящимся в нём виджетам.
- Добавление обратных вызовов к этим виджетам.
- Управление жизненным циклом UserInterface.


#### Управление жизненным циклом с помощью сцены


UserInterface создаётся при загрузке сцены. При перезагрузке или выходе из сцены, либо при закрытии окна движка, UserInterface удаляется.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

`AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"
#include <UnigineWidgets.h>

#include <UnigineUserInterface.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econn;

void on_group_remove(const WidgetPtr &group)
{
	Log::message("world group removed\n");
}

int AppWorldLogic::init()
{

	// world user interface
	UserInterfacePtr ui = UserInterface::create(Gui::getCurrent(), "user_interface.ui");
	ui->setLifetime(Widget::LIFETIME_WORLD);

	auto main_group = checked_ptr_cast<WidgetGroupBox>(ui->getWidget(ui->findWidget("main_group")));
	main_group->setText("World User Interface");
	main_group->getEventRemove().connect(econn, on_group_remove);
	WindowManager::getMainWindow()->addChild(main_group, Gui::ALIGN_EXPAND);

	return 1;
}

int AppWorldLogic::shutdown()
{
	// удаляем все подписки на события
	econn.disconnectAll();

	return 1;
}


```

</details>


#### Управление жизненным циклом с помощью окна


UserInterface создаётся в отдельном окне. При закрытии окна UserInterface удаляется, так как его жизненным циклом управляет это окно. Консоль показывает, удалены ли окно и UserInterface, сработало ли событие удаления, и сообщение из обработчика события удаления (если оно есть).


После закрытия окно можно пересоздать, нажав **T**.


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineWidgets.h>

#include <UnigineUserInterface.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

EngineWindowViewportPtr window;

UserInterfacePtr ui;
WidgetGroupBoxPtr main_group;

bool group_remove_handler = false;

void on_window_group_remove()
{
	Log::message("window group removed\n");
	group_remove_handler = true;
}

void create_window()
{

	window = EngineWindowViewport::create("Test", 512, 256, EngineWindow::FLAGS_SHOWN);

	// window user interface
	ui = UserInterface::create(window->getGui(), "user_interface.ui");
	ui->setLifetime(Widget::LIFETIME_WINDOW);

	main_group = checked_ptr_cast<WidgetGroupBox>(ui->getWidget(engine_ui->findWidget("main_group")));
	main_group->setText("Window User Interface");
	main_group->getEventRemove().connect(econnections, on_window_group_remove);
	window->addChild(main_group, Gui::ALIGN_EXPAND);

}

int AppSystemLogic::init()
{

	create_window();

	return 1;
}

int AppSystemLogic::update()
{

	if (Input::isKeyDown(Input::KEY_T) && window.isDeleted())
		create_window();

	Log::message("window deleted: %d, group deleted: %d, ui deleted: %d, group remove handler %d\n",
		window.isDeleted(), main_group.isDeleted(), ui.isDeleted(), group_remove_handler);


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


#### Управление жизненным циклом с помощью движка


Жизненным циклом UserInterface управляет движок, поэтому он удаляется при завершении работы движка. Экземпляр [Gui](../../../api/library/gui/class.gui_cpp.md) устанавливается вручную через метод *[setGui()](#setGui_Gui_void)*.


The console shows whether the window and UserInterface are deleted or not, whether the remove event is fired, and the message from the remove event handler (if it is). После закрытия окно можно пересоздать, нажав **T**.


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineWidgets.h>

#include <UnigineUserInterface.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

EngineWindowViewportPtr engine_window;

UserInterfacePtr engine_ui;
WidgetGroupBoxPtr engine_main_group;

bool engine_group_remove_handler = false;

void on_engine_group_remove(const WidgetPtr &group)
{
	Log::message("engine group removed\n");
	engine_group_remove_handler = true;
}

void create_engine_window()
{

	engine_window = EngineWindowViewport::create("Test", 512, 256, EngineWindow::FLAGS_SHOWN);

	engine_ui->setGui(engine_window->getGui());
	engine_window->addChild(engine_main_group, Gui::ALIGN_EXPAND);

}

int AppSystemLogic::init()
{

	// engine user interface
	engine_ui = UserInterface::create(Gui::getCurrent(), "user_interface.ui");
	engine_ui->setLifetime(Widget::LIFETIME_ENGINE);

	engine_main_group = checked_ptr_cast<WidgetGroupBox>(engine_ui->getWidget(ui->findWidget("main_group")));
	engine_main_group->setText("Engine User Interface");
	engine_main_group->getEventRemove().connect(econnections, on_engine_group_remove);

	create_engine_window();

	return 1;
}

int AppSystemLogic::update()
{

	if (Input::isKeyDown(Input::KEY_T) && engine_window.isDeleted())
		create_engine_window();

	Log::message("engine window deleted: %d,engine group deleted: %d, engine ui deleted: %d, engine group remove handler %d\n",
		engine_window.isDeleted(), engine_main_group.isDeleted(), engine_ui.isDeleted(), engine_group_remove_handler);

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


### См. также


- Пример C++


## UserInterface Class

### Перечисления

## EVENT_TYPE

| Name | Description |
|---|---|
| **EVENT_SHOW** = 0 |  |
| **EVENT_HIDE** = 1 |  |
| **EVENT_FOCUS_IN** = 2 |  |
| **EVENT_FOCUS_OUT** = 3 |  |
| **EVENT_CHANGED** = 4 |  |
| **EVENT_CLICKED** = 5 |  |
| **EVENT_DOUBLE_CLICKED** = 6 |  |
| **EVENT_PRESSED** = 7 |  |
| **EVENT_RELEASED** = 8 |  |
| **EVENT_KEY_PRESSED** = 9 |  |
| **EVENT_TEXT_PRESSED** = 10 |  |
| **EVENT_ENTER** = 11 |  |
| **EVENT_LEAVE** = 12 |  |
| **EVENT_DRAG_MOVE** = 13 |  |
| **EVENT_DRAG_DROP** = 14 |  |
| **EVENT_REMOVE** = 15 |  |
| **NUM_EVENTS** = 16 |  |

### Методы класса

---

## static UserInterfacePtr create ( const Ptr < Gui > & gui , const char * name , const char * prefix = 0 )

Конструктор UserInterface.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - Умный указатель на GUI.
- *const char ** **name** - Имя пользовательского интерфейса.
- *const char ** **prefix** - Префикс имён.

## int getCallback ( int num , int callback ) const

Возвращает номер указанной функции обратного вызова.
### Аргументы

- *int* **num** - Номер виджета.
- *int* **callback** - Номер типа обратного вызова. Один из обратных вызовов, определённых в [Gui class](../../../api/library/gui/class.gui_cpp.md) (например, CLICK, SHOW, HIDE и т.д.).

### Возвращаемое значение

Номер обратного вызова.
## const char * getCallbackInstanceData ( int num , Gui::CALLBACK_INDEX callback ) const

Возвращает данные экземпляра обратного вызова.
### Аргументы

- *int* **num** - Номер виджета.
- *[Gui::CALLBACK_INDEX](../../../api/library/gui/class.gui_cpp.md#CALLBACK_INDEX)* **callback** - Номер типа обратного вызова. Один из обратных вызовов, определённых в [Gui class](../../../api/library/gui/class.gui_cpp.md) (например, CLICK, SHOW, HIDE и т.д.).

### Возвращаемое значение

Данные экземпляра обратного вызова.
## const char * getCallbackName ( int num , Gui::CALLBACK_INDEX callback ) const

Возвращает имя указанной функции обратного вызова.
### Аргументы

- *int* **num** - Номер виджета.
- *[Gui::CALLBACK_INDEX](../../../api/library/gui/class.gui_cpp.md#CALLBACK_INDEX)* **callback** - Номер типа обратного вызова. Один из обратных вызовов, определённых в [Gui class](../../../api/library/gui/class.gui_cpp.md) (например, CLICK, SHOW, HIDE и т.д.).

### Возвращаемое значение

Имя функции обратного вызова.
## const char * getCallbackStringData ( int num , Gui::CALLBACK_INDEX callback ) const

Возвращает строковые данные обратного вызова.
### Аргументы

- *int* **num** - Номер виджета.
- *[Gui::CALLBACK_INDEX](../../../api/library/gui/class.gui_cpp.md#CALLBACK_INDEX)* **callback** - Номер типа обратного вызова. Один из обратных вызовов, определённых в [Gui class](../../../api/library/gui/class.gui_cpp.md) (например, CLICK, SHOW, HIDE и т.д.).

### Возвращаемое значение

Строковые данные обратного вызова.
## const char * getCallbackVariableData ( int num , Gui::CALLBACK_INDEX callback ) const

Возвращает данные переменной обратного вызова.
### Аргументы

- *int* **num** - Номер виджета.
- *[Gui::CALLBACK_INDEX](../../../api/library/gui/class.gui_cpp.md#CALLBACK_INDEX)* **callback** - Номер типа обратного вызова. Один из обратных вызовов, определённых в [Gui class](../../../api/library/gui/class.gui_cpp.md) (например, CLICK, SHOW, HIDE и т.д.).

### Возвращаемое значение

Данные переменной обратного вызова.
## Ptr < Widget > getCallbackWidgetData ( int num , Gui::CALLBACK_INDEX callback ) const

Возвращает данные виджета обратного вызова.
### Аргументы

- *int* **num** - Номер виджета.
- *[Gui::CALLBACK_INDEX](../../../api/library/gui/class.gui_cpp.md#CALLBACK_INDEX)* **callback** - Номер типа обратного вызова. Один из обратных вызовов, определённых в [Gui class](../../../api/library/gui/class.gui_cpp.md) (например, CLICK, SHOW, HIDE и т.д.).

### Возвращаемое значение

Данные виджета.
## int getNumCallbacks ( int num ) const

Возвращает общее количество обратных вызовов для указанного виджета.
### Аргументы

- *int* **num** - Номер виджета.

### Возвращаемое значение

Количество обратных вызовов.
## int getNumWidgets ( ) const

Возвращает количество связанных виджетов.
### Возвращаемое значение

Количество связанных виджетов.
## Ptr < Widget > getWidget ( int num ) const

Возвращает виджет с указанным ID.
### Аргументы

- *int* **num** - Номер виджета.

### Возвращаемое значение

Указатель на виджет с указанным номером.
## Ptr < Widget > getWidgetByName ( const char * name ) const

Возвращает виджет с указанным именем.
### Аргументы

- *const char ** **name** - Имя виджета.

### Возвращаемое значение

Виджет с указанным ID.
## int getWidgetExport ( int num ) const

Возвращает значение, указывающее, экспортирован ли указанный виджет в скрипт.
### Аргументы

- *int* **num** - Номер виджета.

### Возвращаемое значение

Возвращает 1, если виджет экспортирован; иначе 0.
## const char * getWidgetName ( int num ) const

Возвращает имя виджета по его номеру.
### Аргументы

- *int* **num** - Номер виджета.

### Возвращаемое значение

Имя виджета.
## const char * getWidgetNext ( int num ) const

Возвращает имя виджета, который получит фокус следующим.
### Аргументы

- *int* **num** - Номер текущего виджета.

### Возвращаемое значение

Next Имя виджета.
## int findWidget ( const char * name ) const

Ищет виджет по его имени.
### Аргументы

- *const char ** **name** - Имя виджета.

### Возвращаемое значение

Возвращает номер виджета, если он существует; иначе -1.
## void updateWidgets ( ) const

Обновляет все виджеты, принадлежащие пользовательскому интерфейсу. Эту функцию следует вызывать, например, после смены языка интерфейса.
## void setGui ( const Ptr < Gui > & gui )

Устанавливает новый экземпляр *[Gui](../../../api/library/gui/class.gui_cpp.md)*, используемый для UserInterface.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - Экземпляр *[Gui](../../../api/library/gui/class.gui_cpp.md)*, используемый для UserInterface.

## Ptr < Gui > getGui ( ) const

Возвращает экземпляр *[Gui](../../../api/library/gui/class.gui_cpp.md)* для UserInterface.
### Возвращаемое значение

Экземпляр *[Gui](../../../api/library/gui/class.gui_cpp.md)*, используемый в данный момент для UserInterface.
## void setLifetime ( Widget::LIFETIME lifetime )

Устанавливает тип управления жизненным циклом для UserInterface. По умолчанию используется тип [LIFETIME_ENGINE](../../../api/library/gui/class.widget_cpp.md#LIFETIME).
### Аргументы

- *[Widget::LIFETIME](../../../api/library/gui/class.widget_cpp.md#LIFETIME)* **lifetime**

## Widget::LIFETIME getLifetime ( ) const

Возвращает тип управления жизненным циклом для корня UserInterface, либо для самого UserInterface (если он не является дочерним для другого UserInterface).
> **Notice:** Жизненный цикл каждого UserInterface в иерархии определяется его корнем. Таким образом, тип управления жизненным циклом, установленный для дочернего UserInterface и отличающийся от установленного для корня, игнорируется.
