# Unigine::Plugins::SpiderVision::DisplaysConfig Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Экземпляр этого класса описывает текущую конфигурацию, хранит информацию обо всех viewport и группах текущей конфигурации и предоставляет интерфейс для взаимодействия с ними.


## DisplaysConfig Class

### Методы класса

## String getPath () const

Возвращает текущий путь к файлу конфигурации дисплеев.
### Возвращаемое значение

Текущий путь к файлу конфигурации дисплеев.
## unsigned int getNumViewports () const

Возвращает текущее общее количество viewport в конфигурации.
### Возвращаемое значение

Текущее общее количество viewport в конфигурации.
## unsigned int getNumGroups () const

Возвращает текущее общее количество проекционных групп в конфигурации.
### Возвращаемое значение

Текущее общее количество проекционных групп в конфигурации.
## void setShowHotkey ( Input::KEY hotkey )

Задаёт новую горячую клавишу, открывающую окно конфигурации дисплеев.
### Аргументы

- *[Input::KEY](../../../../api/library/controls/class.input_cpp.md#KEY)* **hotkey** - Горячая клавиша, открывающая окно конфигурации дисплеев.

## Input::KEY getShowHotkey () const

Возвращает текущую горячую клавишу, открывающую окно конфигурации дисплеев.
### Возвращаемое значение

Текущая горячая клавиша, открывающая окно конфигурации дисплеев.
## static Event<ViewportData*> getEventViewportCreated () const

событие, вызываемое при создании viewport. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ViewportCreated
void viewportcreated_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события ViewportCreated\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections viewportcreated_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
DisplaysConfig::getEventViewportCreated().connect(viewportcreated_event_connections, viewportcreated_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
DisplaysConfig::getEventViewportCreated().connect(viewportcreated_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события ViewportCreated (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
viewportcreated_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection viewportcreated_event_connection;

// подписываемся на событие ViewportCreated с функцией-обработчиком, сохраняя соединение
DisplaysConfig::getEventViewportCreated().connect(viewportcreated_event_connection, viewportcreated_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
viewportcreated_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
viewportcreated_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ViewportCreated через соединение
viewportcreated_event_connection.disconnect();

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

	// Обработчик события ViewportCreated, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события ViewportCreated\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
DisplaysConfig::getEventViewportCreated().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId viewportcreated_handler_id;

// подписываемся на событие ViewportCreated с лямбда-обработчиком, сохраняя идентификатор соединения
viewportcreated_handler_id = DisplaysConfig::getEventViewportCreated().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события ViewportCreated (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
DisplaysConfig::getEventViewportCreated().disconnect(viewportcreated_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ViewportCreated при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
DisplaysConfig::getEventViewportCreated().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
DisplaysConfig::getEventViewportCreated().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventViewportRemoved () const

событие, вызываемое при удалении viewport. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ViewportRemoved
void viewportremoved_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события ViewportRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections viewportremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
DisplaysConfig::getEventViewportRemoved().connect(viewportremoved_event_connections, viewportremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
DisplaysConfig::getEventViewportRemoved().connect(viewportremoved_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события ViewportRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
viewportremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection viewportremoved_event_connection;

// подписываемся на событие ViewportRemoved с функцией-обработчиком, сохраняя соединение
DisplaysConfig::getEventViewportRemoved().connect(viewportremoved_event_connection, viewportremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
viewportremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
viewportremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ViewportRemoved через соединение
viewportremoved_event_connection.disconnect();

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

	// Обработчик события ViewportRemoved, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события ViewportRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
DisplaysConfig::getEventViewportRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId viewportremoved_handler_id;

// подписываемся на событие ViewportRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
viewportremoved_handler_id = DisplaysConfig::getEventViewportRemoved().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события ViewportRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
DisplaysConfig::getEventViewportRemoved().disconnect(viewportremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ViewportRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
DisplaysConfig::getEventViewportRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
DisplaysConfig::getEventViewportRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventLoad () const

событие, вызываемое при загрузке конфигурации дисплеев из файла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Load
void load_event_handler()
{
	Log::message("\Обработка события Load\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections load_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
DisplaysConfig::getEventLoad().connect(load_event_connections, load_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
DisplaysConfig::getEventLoad().connect(load_event_connections, []() {
		Log::message("\Обработка события Load (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
load_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection load_event_connection;

// подписываемся на событие Load с функцией-обработчиком, сохраняя соединение
DisplaysConfig::getEventLoad().connect(load_event_connection, load_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
load_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
load_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Load через соединение
load_event_connection.disconnect();

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

	// Обработчик события Load, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события Load\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
DisplaysConfig::getEventLoad().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId load_handler_id;

// подписываемся на событие Load с лямбда-обработчиком, сохраняя идентификатор соединения
load_handler_id = DisplaysConfig::getEventLoad().connect(e_connections, []() {
		Log::message("\Обработка события Load (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
DisplaysConfig::getEventLoad().disconnect(load_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Load при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
DisplaysConfig::getEventLoad().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
DisplaysConfig::getEventLoad().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventClear () const

событие, вызываемое при очистке конфигурации дисплеев. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Clear
void clear_event_handler()
{
	Log::message("\Обработка события Clear\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections clear_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
DisplaysConfig::getEventClear().connect(clear_event_connections, clear_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
DisplaysConfig::getEventClear().connect(clear_event_connections, []() {
		Log::message("\Обработка события Clear (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
clear_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection clear_event_connection;

// подписываемся на событие Clear с функцией-обработчиком, сохраняя соединение
DisplaysConfig::getEventClear().connect(clear_event_connection, clear_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
clear_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
clear_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Clear через соединение
clear_event_connection.disconnect();

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

	// Обработчик события Clear, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события Clear\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
DisplaysConfig::getEventClear().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId clear_handler_id;

// подписываемся на событие Clear с лямбда-обработчиком, сохраняя идентификатор соединения
clear_handler_id = DisplaysConfig::getEventClear().connect(e_connections, []() {
		Log::message("\Обработка события Clear (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
DisplaysConfig::getEventClear().disconnect(clear_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Clear при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
DisplaysConfig::getEventClear().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
DisplaysConfig::getEventClear().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<CalibrationGridData*> getEventCalibrationGridChanged () const

событие, вызываемое при изменении калибровочной сетки. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(CalibrationGridData ***calibration_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CalibrationGridChanged
void calibrationgridchanged_event_handler(CalibrationGridData *calibration_data)
{
	Log::message("\Обработка события CalibrationGridChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections calibrationgridchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
DisplaysConfig::getEventCalibrationGridChanged().connect(calibrationgridchanged_event_connections, calibrationgridchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
DisplaysConfig::getEventCalibrationGridChanged().connect(calibrationgridchanged_event_connections, [](CalibrationGridData *calibration_data) {
		Log::message("\Обработка события CalibrationGridChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
calibrationgridchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection calibrationgridchanged_event_connection;

// подписываемся на событие CalibrationGridChanged с функцией-обработчиком, сохраняя соединение
DisplaysConfig::getEventCalibrationGridChanged().connect(calibrationgridchanged_event_connection, calibrationgridchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
calibrationgridchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
calibrationgridchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CalibrationGridChanged через соединение
calibrationgridchanged_event_connection.disconnect();

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

	// Обработчик события CalibrationGridChanged, реализованный как член класса
	void event_handler(CalibrationGridData *calibration_data)
	{
		Log::message("\Обработка события CalibrationGridChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
DisplaysConfig::getEventCalibrationGridChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId calibrationgridchanged_handler_id;

// подписываемся на событие CalibrationGridChanged с лямбда-обработчиком, сохраняя идентификатор соединения
calibrationgridchanged_handler_id = DisplaysConfig::getEventCalibrationGridChanged().connect(e_connections, [](CalibrationGridData *calibration_data) {
		Log::message("\Обработка события CalibrationGridChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
DisplaysConfig::getEventCalibrationGridChanged().disconnect(calibrationgridchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CalibrationGridChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
DisplaysConfig::getEventCalibrationGridChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
DisplaysConfig::getEventCalibrationGridChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## ViewportData * getViewportByIndex ( int index ) const

Возвращает данные указанного viewport по индексу (значение от 0 до [total number of viewports](#getNumViewports_uint)). Индекс временно соответствует ID viewport и может измениться при изменении количества viewport. Обращение к viewport по индексу подразумевает, что индекс ссылается на ID viewport, который, в свою очередь, ссылается на соответствующий этому ID экземпляр ViewportData.
Этот метод может использоваться следующим образом:


```cpp
for(int i = 0; i < config->getNumViewports(); ++i)
{
	auto viewport = config->getViewportByIndex(i);
	// ... required actions with viewport
}

```


### Аргументы

- *int* **index** - Индекс viewport, значение от 0 до [total number of viewports](#getNumViewports_uint). Индекс временно соответствует ID viewport и может измениться при изменении количества viewport. Обращение к viewport по индексу подразумевает, что индекс ссылается на ID viewport, который, в свою очередь, ссылается на соответствующий этому ID экземпляр ViewportData.

### Возвращаемое значение

[ViewportData class](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md) instance that stores the viewport data.
## ViewportData * getViewport ( int id ) const

Возвращает viewport по указанному ID.
### Аргументы

- *int* **id** - ID viewport.

### Возвращаемое значение

[ViewportData class](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md) instance that stores the viewport data.
## ViewportData * createViewport ( int group_id = -1 )

Создаёт viewport для указанной группы viewport. Если группа не задана, создаётся отдельный viewport.
### Аргументы

- *int* **group_id** - ID группы. Значение по умолчанию -1 означает, что viewport не относится ни к одной группе.

### Возвращаемое значение

[ViewportData class](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md) instance that stores the viewport data.
## void removeViewport ( int id )

Удаляет указанный viewport.
### Аргументы

- *int* **id** - ID viewport.

## GroupData * getGroupByIndex ( int index ) const

Возвращает группу с указанным индексом.
### Аргументы

- *int* **index** - Индекс группы, значение от 0 до [total number of viewport groups](#getNumGroups_uint).

### Возвращаемое значение

[GroupData class](../../../../api/library/plugins/spidervision/class.groupdata_cpp.md) instance that stores the group data.
## GroupData * getGroup ( int id ) const

Возвращает группу viewport по указанному ID.
### Аргументы

- *int* **id** - ID группы.

### Возвращаемое значение

Экземпляр [GroupData class](../../../../api/library/plugins/spidervision/class.groupdata_cpp.md), хранящий данные группы.
## GroupData * createGroup ( GroupData::GROUP_TYPE type )

Создаёт группу указанного типа.
### Аргументы

- *[GroupData::GROUP_TYPE](../../../../api/library/plugins/spidervision/class.groupdata_cpp.md#GROUP_TYPE)* **type** - Тип группы.

### Возвращаемое значение

[GroupData class](../../../../api/library/plugins/spidervision/class.groupdata_cpp.md) instance that stores the group data.
## void removeGroup ( int id )

Удаляет группу с указанным ID.
### Аргументы

- *int* **id** - ID группы.

## CalibrationGridData * getCalibrationGrid ( )

Возвращает калибровочную сетку для конфигурации.
### Возвращаемое значение

Экземпляр [CalibrationGridData class](../../../../api/library/plugins/spidervision/class.calibrationgriddata_cpp.md), хранящий данные калибровочной сетки.
## bool hasUnsavedChanges ( ) const

Возвращает значение, указывающее, есть ли у конфигурации дисплеев несохранённые изменения.
### Возвращаемое значение

true, если у конфигурации дисплеев есть несохранённые изменения; иначе false.
## bool loadConfig ( const char * filepath )

Загружает конфигурацию из указанного источника.
### Аргументы

- *const char ** **filepath** - Путь к файлу конфигурации дисплеев.

### Возвращаемое значение

true, если файл конфигурации успешно загружен; иначе false.
## void loadConfig ( const Ptr < Stream > & stream )

Загружает данные конфигурации из указанного источника.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Указатель на исходный поток.

## bool saveConfig ( const char * filepath )

Сохраняет конфигурацию в указанный файл конфигурации дисплеев.
### Аргументы

- *const char ** **filepath** - Путь к файлу конфигурации дисплеев.

### Возвращаемое значение

true, если файл конфигурации успешно сохранён; иначе false.
## void clear ( )

Очищает конфигурацию дисплеев.
## void saveXml ( const Ptr < Xml > & xml )

Сохраняет данные конфигурации дисплеев в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные.

## bool restoreXml ( const Ptr < Xml > & xml )

Загружает данные конфигурации дисплеев из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.

### Возвращаемое значение

true, если данные успешно загружены; иначе false.
## void save ( const Ptr < Stream > & stream )

Сохраняет данные конфигурации дисплеев в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restore ( const Ptr < Stream > & stream )

Загружает данные конфигурации дисплеев из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.

## void loadConfig ( const Ptr < Xml > & stream )

Загружает конфигурацию из XML-файла.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **stream** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.
