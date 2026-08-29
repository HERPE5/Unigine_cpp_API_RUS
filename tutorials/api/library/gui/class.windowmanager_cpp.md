# Unigine::WindowManager Class (CPP)

**Header:** #include <UnigineWindowManager.h>

> **Notice:** This class is a singleton.


Класс для управления окнами, позволяющий получать доступ к любому окну приложения, группировать или объединять окна в стек, создавать различные диалоги и т.д.


### Доступ к окнам


Доступ к окну приложения можно получить с помощью функции *[getWindow()](#getWindow_int_EngineWindow)*. Также есть функции (например, *[getMainWindow()](#getMainWindow_EngineWindowViewport)*), позволяющие обращаться к конкретным окнам (окно в фокусе, полноэкранное окно, главное окно приложения и т.д.). Так вы получаете экземпляр класса *[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)* (или его потомка), который можно использовать для задания размера/разрешения экрана, позиции на экране, оформления и т.д.


```cpp
// получение главного окна
EngineWindowPtr main_window = WindowManager::getMainWindow();
// изменение позиции и размера (разрешения) главного окна
if (main_window)
{
	main_window->setPosition(Math::ivec2(1020, 60));
	main_window->setSize(Math::ivec2(305, 670));
}


```


### Группировка окон


Окна движка, созданные с помощью класса *[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)*, можно группировать. Существует три типа **групп окон**:


- Вертикальная
- Горизонтальная
- Группа вкладок


Количество окон в группе не ограничено.


Класс WindowManager предоставляет две основные функции для группировки окон:


- *[stack()](#stack_EngineWindow_EngineWindow_int_int_int_EngineWindowGroup)* создаёт группу из двух окон.
- *[stackGroups()](#stackGroups_EngineWindowGroup_EngineWindowGroup_int_EngineWindowGroup)* создаёт группу из двух групп окон.


```cpp
// создание отдельных окон
EngineWindowViewportPtr horizontal_1 = EngineWindowViewport::create("Horizontal 1", 512, 256);
EngineWindowViewportPtr horizontal_2 = EngineWindowViewport::create("Horizontal 2", 512, 256);
EngineWindowViewportPtr horizontal_3 = EngineWindowViewport::create("Horizontal 3", 512, 256);
EngineWindowViewportPtr horizontal_4 = EngineWindowViewport::create("Horizontal 4", 512, 256);

// создание 2 горизонтальных групп окон
EngineWindowGroupPtr horizontal_group_1 = WindowManager::stack(horizontal_1, horizontal_2, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);
EngineWindowGroupPtr horizontal_group_2 = WindowManager::stack(horizontal_3, horizontal_4, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);
// создание вертикальной группы из 2 горизонтальных групп
EngineWindowGroupPtr vertical_group = WindowManager::stackGroups(horizontal_group_1, horizontal_group_2, EngineWindowGroup::GROUP_TYPE_VERTICAL);
// задание позиции, размера, заголовка вертикальной группы окон
vertical_group->setPosition(Math::ivec2(50, 60));
vertical_group->setSize(Math::ivec2(565, 310));
vertical_group->setTitle("Vertical Group");
// отображение группы окон
vertical_group->show();


```


У каждого окна или группы окон есть [state](../../../api/library/gui/class.enginewindow_cpp.md#TYPE), которое изменяется после объединения в стек.


![](window_manager_stacking.png)


Также есть функции, основанные на функции *stack()*, которые следует использовать в конкретных случаях, чтобы избежать дополнительной проверки аргументов:


- *[stackToParentGroup()](#stackToParentGroup_EngineWindow_EngineWindow_int_int_EngineWindowGroup)* добавляет второе окно в родительскую группу первого окна. В результате оба окна, переданные в качестве аргументов, окажутся на одном уровне иерархии группы.
- *[stackWindows()](#stackWindows_EngineWindowViewport_EngineWindowViewport_int_EngineWindowGroup)* создаёт группу из отдельных/вложенных окон. Окна объединяются в стек в порядке по умолчанию.
- *[stack()](#stack_EngineWindow_EngineWindow_int_int_int_EngineWindowGroup)* добавляет окно к другому окну. Если первый аргумент - отдельное окно, возвращается новая группа окон. Если первый аргумент - вложенное окно, окно добавляется в его группу.
- *[stackToGroup()](#stackToGroup_EngineWindowGroup_EngineWindow_int_int_EngineWindowGroup)* добавляет окно или группу окон в другую группу окон.


Перейдите по ссылкам, чтобы увидеть примеры кода.


Для разгруппировки используется функция *[unstack()](#unstack_EngineWindow_void)*: она удаляет окно или группу окон из родительской группы.


### Создание диалоговых окон


Чтобы создать диалоговое окно, используйте соответствующие функции класса. Например:


```cpp
// функция-обработчик события
int AppSystemLogic::onButtonClicked(const WidgetPtr &sender_widget, int buttons)
{
	// показ диалога с сообщением
	WindowManager::dialogMessage("Message", "The button has been pressed.");

	return 1;

}

int AppSystemLogic::init()
{

	// создание окна с виджетами в клиентской области
	auto create_window = [](const char *name)
	{
		EngineWindowViewportPtr window = EngineWindowViewport::create(name, 512, 256);

		window->addChild(WidgetLabel::create(window->getSelfGui(), String::format("This is a %s.", name)), Gui::ALIGN_TOP);
		window->addChild(WidgetButton::create(window->getSelfGui(), name), Gui::ALIGN_CENTER);

		return window;

	};

	{
		// создание окна
		EngineWindowViewportPtr window = create_window("Window");
		// получение дочернего виджета окна
		WidgetPtr button = window->getChild(1);
		// подписка на событие Clicked
		button->getEventClicked().connect(this, &AppSystemLogic::onButtonClicked);
		// отображение окна
		window->setPosition(Math::ivec2(50, 60));
		window->show();
	}

	return 1;
}


```


### См. также


- Набор примеров SDK (`source/window_manager/`), демонстрирующих различные аспекты использования.


## WindowManager Class

### Перечисления

## DPI_AWARENESS

| Имя | Описание |
|---|---|
| **DPI_AWARENESS_CUSTOM** = -1 | Уровень осведомлённости о DPI задаётся не на стороне движка. Например, когда приложение интегрируется через CustomSystemProxy, пользователь задаёт требуемый режим. |
| **DPI_AWARENESS_UNAWARE** = CUSTOM + 1 | Масштабирование не учитывается. Окна отображаются со стандартным уровнем DPI 96 (100%). Операционная система растянет растровую часть окна, и оно будет выглядеть размытым. |
| **DPI_AWARENESS_SYSTEM_AWARE** = UNAWARE + 1 | Получается уровень DPI главного системного дисплея. Только при этом уровне DPI изображение отображается чётко. Дисплеи с другим уровнем DPI или изменение значения DPI на главном системном дисплее во время работы приложения приведёт к размытию изображения. |
| **DPI_AWARENESS_PER_MONITOR_AWARE** = SYSTEM_AWARE + 1 | Окна получают уровень DPI от каждого дисплея индивидуально. > **Notice:** Недоступно на Linux. |

### Методы класса

## Ptr < EngineWindowViewport > getMainWindow () const

Возвращает текущий viewport окна, заданный как главное окно по умолчанию.
> **Notice:** Может быть несколько окон, заданных как главные, или ни одного главного окна.


### Возвращаемое значение

Текущий viewport окна движка.
## int getNumWindows () const

Возвращает текущее количество окон.
### Возвращаемое значение

Текущее количество окон.
## bool isFullscreenMode () const

Возвращает текущее значение, указывающее, находится ли окно в полноэкранном состоянии или в оконном режиме.
### Возвращаемое значение

**true**, если окно находится в полноэкранном состоянии; иначе **false**.
## bool isMultipleWindowsSupported () const

Возвращает текущее значение, указывающее, может ли движок создавать более одного окна.
### Возвращаемое значение

**true**, если поддерживается несколько окон; иначе **false**.
## Ptr < EngineWindow > getFocusedWindow () const

Возвращает текущий viewport окна, которое в данный момент находится в фокусе.
### Возвращаемое значение

Текущий viewport окна, которое в данный момент находится в фокусе.
## Ptr < EngineWindow > getUnderCursorWindow () const

Возвращает текущий viewport окна, которое в данный момент находится под курсором.
### Возвращаемое значение

Текущий viewport окна, которое в данный момент находится под курсором.
## Ptr < EngineWindowViewport > getSystemFocusedWindow () const

Возвращает текущий viewport окна движка, у которого включён флаг [isSystemFocused()](../../../api/library/gui/class.enginewindow_cpp.md#isSystemFocused_int) - либо у самого окна, либо у его родительской группы с включённым системным фокусом. Если такого окна не найдено, возвращается nullptr.
### Возвращаемое значение

Текущий viewport окна движка, у которого включён флаг [isSystemFocused()](../../../api/library/gui/class.enginewindow_cpp.md#isSystemFocused_int), или nullptr, если такого окна нет.
## bool isAutoDpiScaling () const

Возвращает текущее значение, определяющее, применяется ли автоматическое масштабирование DPI к окну. Если автоматическое масштабирование DPI отключено, все элементы GUI имеют размер 100%, масштабируется только размер системного окна.
> **Notice:** Это значение хранится в файле загрузочной конфигурации и может быть изменено только при запуске приложения. Оно не может быть изменено во время выполнения, поэтому при попытке изменить значение в консоли будет показано соответствующее предупреждение.


### Возвращаемое значение

**true**, если масштабирование всех элементов GUI окна включено; иначе **false**.
## WindowManager::DPI_AWARENESS getDpiAwareness () const

Возвращает текущий режим осведомлённости о DPI - значение, указывающее, как приложение обрабатывает масштабирование DPI. По умолчанию значение установлено в [PER_MONITOR_AWARE](#DPI_AWARENESS_PER_MONITOR_AWARE). В Windows, если указанный режим не может быть установлен, будет выполнено переключение на более низкое возможное значение с соответствующим предупреждением. В Linux [PER_MONITOR_AWARE](#DPI_AWARENESS_PER_MONITOR_AWARE) в настоящее время не поддерживается, установка этого значения переключит режим на [SYSTEM_AWARE](#DPI_AWARENESS_SYSTEM_AWARE) с соответствующим предупреждением в консоли.
> **Notice:** Это значение хранится в файле загрузочной конфигурации и может быть изменено только при запуске приложения. Оно не может быть изменено во время выполнения, поэтому при попытке изменить значение в консоли будет показано соответствующее предупреждение.


### Возвращаемое значение

Текущий режим осведомлённости о DPI, значение, указывающее, как приложение обрабатывает масштабирование DPI.
## WindowManager::DPI_AWARENESS getCurrentDpiAwareness () const

Возвращает текущий фактический режим осведомлённости о DPI, значение, указывающее, как приложение обрабатывает масштабирование DPI. По умолчанию значение установлено в [PER_MONITOR_AWARE](#DPI_AWARENESS_PER_MONITOR_AWARE). В Windows, если указанный режим не может быть установлен, будет выполнено переключение на более низкое возможное значение с соответствующим предупреждением. В Linux [PER_MONITOR_AWARE](#DPI_AWARENESS_PER_MONITOR_AWARE) в настоящее время не поддерживается, установка этого значения переключит режим на [SYSTEM_AWARE](#DPI_AWARENESS_SYSTEM_AWARE) с соответствующим предупреждением в консоли.
> **Notice:** Это фактическое значение, оно может отличаться от режима, хранящегося в файле загрузочной конфигурации (если система не может установить указанный режим, она попытается использовать подходящий вместо него).


### Возвращаемое значение

Текущий фактический режим осведомлённости о DPI, значение, указывающее, как приложение обрабатывает масштабирование DPI.
## static Event<const Ptr < WindowEvent > &> getEventImmediateWindowEvent () const

событие, срабатывающее сразу же, как только событие от окна получено от прокси, до его обработки движком. Это событие может срабатывать в разных потоках в зависимости от реализации прокси. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WindowEvent> & **event**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ImmediateWindowEvent
void immediatewindowevent_event_handler(const Ptr<WindowEvent> & event)
{
	Log::message("\Обработка события ImmediateWindowEvent\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections immediatewindowevent_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
WindowManager::getEventImmediateWindowEvent().connect(immediatewindowevent_event_connections, immediatewindowevent_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
WindowManager::getEventImmediateWindowEvent().connect(immediatewindowevent_event_connections, [](const Ptr<WindowEvent> & event) {
		Log::message("\Обработка события ImmediateWindowEvent (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
immediatewindowevent_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection immediatewindowevent_event_connection;

// подписываемся на событие ImmediateWindowEvent с функцией-обработчиком, сохраняя соединение
WindowManager::getEventImmediateWindowEvent().connect(immediatewindowevent_event_connection, immediatewindowevent_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
immediatewindowevent_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
immediatewindowevent_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ImmediateWindowEvent через соединение
immediatewindowevent_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события ImmediateWindowEvent, реализованный как член класса
	void event_handler(const Ptr<WindowEvent> & event)
	{
		Log::message("\Обработка события ImmediateWindowEvent\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
WindowManager::getEventImmediateWindowEvent().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId immediatewindowevent_handler_id;

// подписываемся на событие ImmediateWindowEvent с лямбда-обработчиком, сохраняя идентификатор соединения
immediatewindowevent_handler_id = WindowManager::getEventImmediateWindowEvent().connect(e_connections, [](const Ptr<WindowEvent> & event) {
		Log::message("\Обработка события ImmediateWindowEvent (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
WindowManager::getEventImmediateWindowEvent().disconnect(immediatewindowevent_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ImmediateWindowEvent при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
WindowManager::getEventImmediateWindowEvent().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
WindowManager::getEventImmediateWindowEvent().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < EngineWindow > &> getEventWindowUnstacked () const

событие, срабатывающее после того, как окно было удалено из стека. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<EngineWindow> & **window**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события WindowUnstacked
void windowunstacked_event_handler(const Ptr<EngineWindow> & window)
{
	Log::message("\Обработка события WindowUnstacked\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections windowunstacked_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
WindowManager::getEventWindowUnstacked().connect(windowunstacked_event_connections, windowunstacked_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
WindowManager::getEventWindowUnstacked().connect(windowunstacked_event_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowUnstacked (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
windowunstacked_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection windowunstacked_event_connection;

// подписываемся на событие WindowUnstacked с функцией-обработчиком, сохраняя соединение
WindowManager::getEventWindowUnstacked().connect(windowunstacked_event_connection, windowunstacked_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
windowunstacked_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
windowunstacked_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие WindowUnstacked через соединение
windowunstacked_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события WindowUnstacked, реализованный как член класса
	void event_handler(const Ptr<EngineWindow> & window)
	{
		Log::message("\Обработка события WindowUnstacked\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
WindowManager::getEventWindowUnstacked().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId windowunstacked_handler_id;

// подписываемся на событие WindowUnstacked с лямбда-обработчиком, сохраняя идентификатор соединения
windowunstacked_handler_id = WindowManager::getEventWindowUnstacked().connect(e_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowUnstacked (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
WindowManager::getEventWindowUnstacked().disconnect(windowunstacked_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий WindowUnstacked при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
WindowManager::getEventWindowUnstacked().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
WindowManager::getEventWindowUnstacked().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < EngineWindow > &> getEventWindowStacked () const

событие, срабатывающее после того, как окно было добавлено в стек. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<EngineWindow> & **window**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события WindowStacked
void windowstacked_event_handler(const Ptr<EngineWindow> & window)
{
	Log::message("\Обработка события WindowStacked\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections windowstacked_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
WindowManager::getEventWindowStacked().connect(windowstacked_event_connections, windowstacked_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
WindowManager::getEventWindowStacked().connect(windowstacked_event_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowStacked (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
windowstacked_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection windowstacked_event_connection;

// подписываемся на событие WindowStacked с функцией-обработчиком, сохраняя соединение
WindowManager::getEventWindowStacked().connect(windowstacked_event_connection, windowstacked_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
windowstacked_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
windowstacked_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие WindowStacked через соединение
windowstacked_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события WindowStacked, реализованный как член класса
	void event_handler(const Ptr<EngineWindow> & window)
	{
		Log::message("\Обработка события WindowStacked\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
WindowManager::getEventWindowStacked().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId windowstacked_handler_id;

// подписываемся на событие WindowStacked с лямбда-обработчиком, сохраняя идентификатор соединения
windowstacked_handler_id = WindowManager::getEventWindowStacked().connect(e_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowStacked (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
WindowManager::getEventWindowStacked().disconnect(windowstacked_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий WindowStacked при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
WindowManager::getEventWindowStacked().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
WindowManager::getEventWindowStacked().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < EngineWindow > &> getEventWindowRemoved () const

событие, срабатывающее после того, как окно было удалено. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<EngineWindow> & **window**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события WindowRemoved
void windowremoved_event_handler(const Ptr<EngineWindow> & window)
{
	Log::message("\Обработка события WindowRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections windowremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
WindowManager::getEventWindowRemoved().connect(windowremoved_event_connections, windowremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
WindowManager::getEventWindowRemoved().connect(windowremoved_event_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
windowremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection windowremoved_event_connection;

// подписываемся на событие WindowRemoved с функцией-обработчиком, сохраняя соединение
WindowManager::getEventWindowRemoved().connect(windowremoved_event_connection, windowremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
windowremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
windowremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие WindowRemoved через соединение
windowremoved_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события WindowRemoved, реализованный как член класса
	void event_handler(const Ptr<EngineWindow> & window)
	{
		Log::message("\Обработка события WindowRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
WindowManager::getEventWindowRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId windowremoved_handler_id;

// подписываемся на событие WindowRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
windowremoved_handler_id = WindowManager::getEventWindowRemoved().connect(e_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
WindowManager::getEventWindowRemoved().disconnect(windowremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий WindowRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
WindowManager::getEventWindowRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
WindowManager::getEventWindowRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < EngineWindow > &> getEventWindowCreated () const

событие, срабатывающее после того, как окно было создано. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<EngineWindow> & **window**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события WindowCreated
void windowcreated_event_handler(const Ptr<EngineWindow> & window)
{
	Log::message("\Обработка события WindowCreated\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections windowcreated_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
WindowManager::getEventWindowCreated().connect(windowcreated_event_connections, windowcreated_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
WindowManager::getEventWindowCreated().connect(windowcreated_event_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowCreated (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
windowcreated_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection windowcreated_event_connection;

// подписываемся на событие WindowCreated с функцией-обработчиком, сохраняя соединение
WindowManager::getEventWindowCreated().connect(windowcreated_event_connection, windowcreated_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
windowcreated_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
windowcreated_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие WindowCreated через соединение
windowcreated_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события WindowCreated, реализованный как член класса
	void event_handler(const Ptr<EngineWindow> & window)
	{
		Log::message("\Обработка события WindowCreated\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
WindowManager::getEventWindowCreated().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId windowcreated_handler_id;

// подписываемся на событие WindowCreated с лямбда-обработчиком, сохраняя идентификатор соединения
windowcreated_handler_id = WindowManager::getEventWindowCreated().connect(e_connections, [](const Ptr<EngineWindow> & window) {
		Log::message("\Обработка события WindowCreated (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
WindowManager::getEventWindowCreated().disconnect(windowcreated_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий WindowCreated при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
WindowManager::getEventWindowCreated().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
WindowManager::getEventWindowCreated().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Ptr < EngineWindowViewport > getFullscreenWindow () const

Возвращает текущий первый viewport окна движка, находящийся в полноэкранном состоянии.
### Возвращаемое значение

Текущий viewport в полноэкранном состоянии, или nullptr, если окно не найдено.
---

## Ptr < EngineWindow > getWindow ( int index )

Возвращает окно по его индексу.
### Аргументы

- *int* **index** - Индекс окна.

### Возвращаемое значение

Окно движка.
## int getWindowIndex ( const Ptr < EngineWindow > & window ) const

Возвращает индекс указанного окна.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Окно движка.

### Возвращаемое значение

Индекс окна.
## Ptr < EngineWindowGroup > stack ( const Ptr < EngineWindow > & first_window , const Ptr < EngineWindow > & second_window , EngineWindowGroup::GROUP_TYPE group_type , int index = -1 , bool decompose_second = false )

Добавляет окно к другому окну. Если первый аргумент - отдельное окно, возвращается новая группа окон. Если первый аргумент - вложенное окно, окно добавляется в его группу.
```cpp
EngineWindowPtr window_1 = EngineWindowViewport::create("Window 1", 512, 256);
EngineWindowPtr window_2 = EngineWindowViewport::create("Window 2", 512, 256);
EngineWindowPtr window_3 = EngineWindowViewport::create("Window 3", 512, 256);

// создание группы из 2 окон
EngineWindowGroupPtr group_1 = WindowManager::stack(window_1, window_2, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);
// добавление отдельного окна к окну из группы окон
WindowManager::stack(window_1, window_3, EngineWindowGroup::GROUP_TYPE_VERTICAL);


```

 В результате *group_1* будет состоять из 3 окон: *window_1* и *window_3*, объединённых вертикально, и *window_2*, объединённого горизонтально.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **first_window** - Родительское окно, к которому добавляется другое окно.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **second_window** - Добавляемое окно.
- *[EngineWindowGroup::GROUP_TYPE](../../../api/library/gui/class.enginewindowgroup_cpp.md#GROUP_TYPE)* **group_type** - Тип создаваемой группы.
- *int* **index**
- *bool* **decompose_second** - Флаг разложения второго аргумента объединения, если это группа, и объединения с первой группой.

### Возвращаемое значение

Группа объединённых окон.
## Ptr < EngineWindowGroup > stackToParentGroup ( const Ptr < EngineWindow > & window_in_group , const Ptr < EngineWindow > & window , int index = -1 , bool decompose_second = false )

Добавляет второе окно в родительскую группу первого окна. В результате оба окна, переданные в качестве аргументов, окажутся на одном уровне иерархии группы. Если у первого окна нет родительской группы, функция вернёт его как есть.
```cpp
EngineWindowPtr window_1 = EngineWindowViewport::create("Window 1", 512, 256);
EngineWindowPtr window_2 = EngineWindowViewport::create("Window 2", 512, 256);
EngineWindowPtr window_3 = EngineWindowViewport::create("Window 3", 512, 256);

// объединение 2 отдельных окон
EngineWindowGroupPtr group_0 = WindowManager::stack(window_1, window_2, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);
// добавление отдельного окна в родительскую группу "window_1"
WindowManager::stackToParentGroup(window_1, window_3);


```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window_in_group** - Окно, в родительскую группу которого добавляется другое окно.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Добавляемое окно.
- *int* **index** - Место, где окно или группа должны быть размещены в группе.
- *bool* **decompose_second** - Флаг разложения второго аргумента объединения, если это группа, и объединения с первым окном или группой.

### Возвращаемое значение

Группа окон.
## Ptr < EngineWindowGroup > stackWindows ( const Ptr < EngineWindowViewport > & first_viewport , const Ptr < EngineWindowViewport > & second_viewport , EngineWindowGroup::GROUP_TYPE group_type = Enum.EngineWindowGroup.GROUP_TYPE.TAB )

Возвращает вновь созданную группу отдельных и/или вложенных окон. Нельзя добавить группу окон к отдельному окну, однако можно добавить окно, вложенное в группу окон: в этом случае окно будет удалено из родительской группы и добавлено в новую. Окна объединяются в стек в порядке по умолчанию. Например:
```cpp
EngineWindowViewportPtr window_1 = EngineWindowViewport::create("Window 1", 512, 256);
EngineWindowViewportPtr window_2 = EngineWindowViewport::create("Window 2", 512, 256);
EngineWindowViewportPtr window_3 = EngineWindowViewport::create("Window 3", 512, 256);

// объединение 2 отдельных окон
EngineWindowGroupPtr group_0 = WindowManager::stack(window_1, window_2, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);

// добавление окна из группы окон к отдельному окну
EngineWindowGroupPtr group_1 = WindowManager::stackWindows(window_3, window_1, EngineWindowGroup::GROUP_TYPE_VERTICAL);


```

 В результате *group_1* будет вертикальной группой из *window_3* и *window_1*.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowViewport](../../../api/library/gui/class.enginewindowviewport_cpp.md)> &* **first_viewport** - Добавляемое окно.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowViewport](../../../api/library/gui/class.enginewindowviewport_cpp.md)> &* **second_viewport** - Добавляемое окно.
- *[EngineWindowGroup::GROUP_TYPE](../../../api/library/gui/class.enginewindowgroup_cpp.md#GROUP_TYPE)* **group_type** - Тип создаваемой группы.

### Возвращаемое значение

Группа окон.
## Ptr < EngineWindowGroup > stackWithWindow ( const Ptr < EngineWindowViewport > & window_viewport , const Ptr < EngineWindow > & window , EngineWindowGroup::GROUP_TYPE group_type , bool decompose_second = false )

Возвращает вновь созданную группу из viewport окна движка и любого другого окна движка - другого viewport или группы окон.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowViewport](../../../api/library/gui/class.enginewindowviewport_cpp.md)> &* **window_viewport** - Добавляемый viewport окна.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Добавляемое окно.
- *[EngineWindowGroup::GROUP_TYPE](../../../api/library/gui/class.enginewindowgroup_cpp.md#GROUP_TYPE)* **group_type** - Тип создаваемой группы окон.
- *bool* **decompose_second** - Флаг разложения второго аргумента объединения, если это группа, и объединения с первой группой.

### Возвращаемое значение

Группа окон.
## Ptr < EngineWindowGroup > stackGroups ( const Ptr < EngineWindowGroup > & first_group , const Ptr < EngineWindowGroup > & second_group , EngineWindowGroup::GROUP_TYPE group_type )

Возвращает группу групп окон. Вторая группа добавляется в первую группу. Чтобы объединить два окна или группу и окно, используйте метод *[stack()](#stack_EngineWindow_EngineWindow_int_int_int_EngineWindowGroup)*.
```cpp
EngineWindowPtr window_1 = EngineWindowViewport::create("Window 1", 512, 256);
EngineWindowPtr window_2 = EngineWindowViewport::create("Window 2", 512, 256);
EngineWindowPtr window_3 = EngineWindowViewport::create("Window 3", 512, 256);
EngineWindowPtr window_4 = EngineWindowViewport::create("Window 4", 512, 256);

// создание 2 горизонтальных групп окон
EngineWindowGroupPtr group_1 = WindowManager::stack(window_1, window_2, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);
EngineWindowGroupPtr group_2 = WindowManager::stack(window_3, window_4, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);
// объединение одной группы с другой для создания новой вертикальной группы
EngineWindowGroupPtr group_3 = WindowManager::stackGroups(group_1, group_2, EngineWindowGroup::GROUP_TYPE_VERTICAL);


```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowGroup](../../../api/library/gui/class.enginewindowgroup_cpp.md)> &* **first_group** - Первая группа окон для объединения.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowGroup](../../../api/library/gui/class.enginewindowgroup_cpp.md)> &* **second_group** - Вторая группа окон для объединения.
- *[EngineWindowGroup::GROUP_TYPE](../../../api/library/gui/class.enginewindowgroup_cpp.md#GROUP_TYPE)* **group_type** - Тип создаваемой группы.

### Возвращаемое значение

Группа окон.
## Ptr < EngineWindowGroup > stackToGroup ( const Ptr < EngineWindowGroup > & destination_group , const Ptr < EngineWindow > & group , int index = -1 , bool decompose_second = false )

Добавляет окно или группу окон в другую группу окон. Возвращается обновлённая группа окон.
```cpp
EngineWindowPtr window_1 = EngineWindowViewport::create("Window 1", 512, 256);
EngineWindowPtr window_2 = EngineWindowViewport::create("Window 2", 512, 256);
EngineWindowPtr window_3 = EngineWindowViewport::create("Window 3", 512, 256);
EngineWindowPtr window_4 = EngineWindowViewport::create("Window 4", 512, 256);

// создание 2 горизонтальных групп окон
EngineWindowGroupPtr group_1 = WindowManager::stack(window_1, window_2, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);
EngineWindowGroupPtr group_2 = WindowManager::stack(window_3, window_4, EngineWindowGroup::GROUP_TYPE_HORIZONTAL);

// объединение одной группы с другой
WindowManager::stackToGroup(group_1, group_2);


```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindowGroup](../../../api/library/gui/class.enginewindowgroup_cpp.md)> &* **destination_group** - Родительская группа, к которой добавляется другая группа.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **group** - Добавляемое окно или группа окон.
- *int* **index** - Место, где окно или группа должны быть размещены в группе.
- *bool* **decompose_second** - Флаг разложения второго аргумента объединения и объединения с первой группой.

### Возвращаемое значение

Группа объединённых окон.
## void unstack ( const Ptr < EngineWindow > & unstacked )

Удаляет окно или группу из родительской группы. Если остаётся только одно окно, группа автоматически удаляется после удаления из неё окна.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **unstacked** - Окно или группа, удаляемые из родительской группы.

## bool isFullscreenWindow ( const Ptr < EngineWindow > & window )

Возвращает значение, указывающее, находится ли указанное окно в полноэкранном состоянии.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Проверяемое окно.

### Возвращаемое значение

true, если окно движка находится в полноэкранном состоянии, false, если оно в оконном режиме.
## Ptr < EngineWindowViewport > getFullscreenWindow ( ) const

Возвращает первый viewport окна движка, находящийся в полноэкранном состоянии.
### Возвращаемое значение

Viewport в полноэкранном состоянии, или nullptr, если окно не найдено.
## Ptr < EngineWindow > getWindowByID ( unsigned long long win_id ) const

Возвращает окно по его ID.
### Аргументы

- *unsigned long long* **win_id** - ID окна.

### Возвращаемое значение

Окно с указанным ID, или nullptr, если окно не найдено.
## bool dialogMessage ( const char * title , const char * message )

Отображает диалог сообщения с указанным заголовком и текстом.
### Аргументы

- *const char ** **title** - Заголовок отображаемого диалога сообщения.
- *const char ** **message** - Отображаемый текст сообщения.

### Возвращаемое значение

true, если сообщение отображено успешно; иначе false.
## bool dialogWarning ( const char * title , const char * warning )

Отображает диалог предупреждения с указанным заголовком и текстом.
### Аргументы

- *const char ** **title** - Заголовок отображаемого диалога предупреждения.
- *const char ** **warning** - Отображаемый текст предупреждения.

### Возвращаемое значение

true, если сообщение отображено успешно; иначе false.
## bool dialogError ( const char * title , const char * error )

Отображает диалог ошибки с указанным заголовком и текстом.
### Аргументы

- *const char ** **title** - Заголовок отображаемого диалога ошибки.
- *const char ** **error** - Отображаемый текст ошибки.

### Возвращаемое значение

**true**, если сообщение отображено успешно; иначе **false**.
## int showSystemDialog ( const Ptr < SystemDialog > & dialog )

Отображает пользовательский [system dialog](../../../api/library/engine/class.systemdialog_cpp.md) с произвольным набором кнопок.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SystemDialog](../../../api/library/engine/class.systemdialog_cpp.md)> &* **dialog** - Экземпляр класса [*SystemDialog*](../../../api/library/engine/class.systemdialog_cpp.md), представляющий отображаемый пользовательский системный диалог.

### Возвращаемое значение

Номер кнопки диалога, по которой щёлкнул пользователь; или **-1**, если произошла ошибка.
## const char * dialogOpenFolder ( const char * path )

Открывает стандартный диалог, позволяющий пользователю указать папку для открытия. При открытии диалога должен быть установлен указанный путь по умолчанию, отображающий соответствующие элементы.
### Аргументы

- *const char ** **path** - Путь, устанавливаемый по умолчанию при открытии диалога.

### Возвращаемое значение

Имя результирующей папки, указанное пользователем.
## const char * dialogOpenFolder ( )

Открывает стандартный диалог, позволяющий пользователю указать папку для открытия.
### Возвращаемое значение

Имя результирующей папки, указанное пользователем.
## Vector < String > dialogOpenFiles ( const char * path , const char * filter )

Открывает стандартный диалог, позволяющий пользователю указать список имён файлов для открытия нескольких файлов. При открытии диалога должны быть установлены указанные путь по умолчанию и фильтр файлов, отображающие соответствующие элементы.
### Аргументы

- *const char ** **path** - Путь, устанавливаемый по умолчанию при открытии диалога.
- *const char ** **filter** - Строка фильтра имён файлов, устанавливаемая по умолчанию при открытии диалога. Эта строка фильтра определяет выбор типов файлов, отображаемых в поле *Files of type*.

### Возвращаемое значение

Результирующий список имён файлов, указанный пользователем.
## Vector < String > dialogOpenFiles ( const char * path )

Открывает стандартный диалог, позволяющий пользователю указать список имён файлов для открытия нескольких файлов. При открытии диалога должен быть установлен указанный путь по умолчанию, отображающий соответствующие элементы.
### Аргументы

- *const char ** **path** - Путь, устанавливаемый по умолчанию при открытии диалога.

### Возвращаемое значение

Результирующий список имён файлов, указанный пользователем.
## Vector < String > dialogOpenFiles ( )

Открывает стандартный диалог, позволяющий пользователю указать список имён файлов для открытия нескольких файлов.
### Возвращаемое значение

Результирующий список имён файлов, указанный пользователем.
## const char * dialogOpenFile ( const char * path , const char * filter )

Открывает стандартный диалог, позволяющий пользователю указать имя файла для открытия файла. При открытии диалога должны быть установлены указанные путь по умолчанию и фильтр файлов, отображающие соответствующие элементы.
### Аргументы

- *const char ** **path** - Путь, устанавливаемый по умолчанию при открытии диалога.
- *const char ** **filter** - Строка фильтра имён файлов, устанавливаемая по умолчанию при открытии диалога. Эта строка фильтра определяет выбор типов файлов, отображаемых в поле *Files of type*.

### Возвращаемое значение

Результирующее имя файла, указанное пользователем.
## const char * dialogOpenFile ( const char * path )

Открывает стандартный диалог, позволяющий пользователю указать имя файла для открытия файла. При открытии диалога должен быть установлен указанный путь по умолчанию, отображающий соответствующие элементы.
### Аргументы

- *const char ** **path** - Путь, устанавливаемый по умолчанию при открытии диалога.

### Возвращаемое значение

Результирующее имя файла, указанное пользователем.
## const char * dialogOpenFile ( )

Открывает стандартный диалог, позволяющий пользователю указать имя файла для открытия файла.
### Возвращаемое значение

Результирующее имя файла, указанное пользователем.
## const char * dialogSaveFile ( const char * path , const char * filter )

Открывает стандартный диалог, позволяющий пользователю указать имя файла для сохранения. При открытии диалога должны быть установлены указанные путь по умолчанию и фильтр файлов, отображающие соответствующие элементы.
### Аргументы

- *const char ** **path** - Путь, устанавливаемый по умолчанию при открытии диалога.
- *const char ** **filter** - Строка фильтра имён файлов, устанавливаемая по умолчанию при открытии диалога. Эта строка фильтра определяет выбор типов файлов, отображаемых в поле *Save as file type* или *Files of type*.

### Возвращаемое значение

Результирующее имя файла, указанное пользователем.
## const char * dialogSaveFile ( const char * path )

Открывает стандартный диалог, позволяющий пользователю указать имя файла для сохранения. При открытии диалога должен быть установлен указанный путь по умолчанию, отображающий соответствующие элементы.
### Аргументы

- *const char ** **path** - Путь, устанавливаемый по умолчанию при открытии диалога.

### Возвращаемое значение

Результирующее имя файла, указанное пользователем.
## const char * dialogSaveFile ( )

Открывает стандартный диалог, позволяющий пользователю указать имя файла для сохранения.
### Возвращаемое значение

Результирующее имя файла, указанное пользователем.
## Ptr < EngineWindow > getIntersection ( const Math:: ivec2 & global_pos , const Vector < Ptr < EngineWindow >> & excludes ) const

Возвращает окно, пересечение с которым обнаружено.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **global_pos** - Позиция точки пересечения в глобальных координатах.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)>> &* **excludes** - Окна, исключаемые из обнаружения пересечений.

### Возвращаемое значение

Окно, пересечение с которым обнаружено.
## Ptr < EngineWindow > getIntersection ( const Math:: ivec2 & global_pos ) const

Возвращает окно, пересечение с которым обнаружено.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **global_pos** - Позиция точки пересечения в глобальных координатах.

### Возвращаемое значение

Окно, пересечение с которым обнаружено.
## void forceUpdateWindowOrders ( )

Обновляет Z-порядок всех окон.
> **Notice:** Рекомендуется использовать этот метод только при необходимости, так как он очень медленный.


## void setEventsFilter ( int (*)(const Ptr < InputEvent > &) func )

Задаёт функцию обратного вызова, выполняемую при получении входных событий. Этот фильтр входных событий позволяет отклонять определённые входные события для движка и получать необходимую информацию обо всех входных событиях.
### Аргументы

- *int (*)(const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEvent](../../../api/library/controls/class.inputevent_cpp.md)> &)* **func** - Колбэк входного события.
