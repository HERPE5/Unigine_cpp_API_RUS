# Класс Unigine::Properties (CPP)

**Заголовочный файл:** #include <UnigineProperties.h>

> **Notice:** Этот класс является одиночкой (singleton).


Приведённые ниже функции используются для управления загрузкой свойств и их обслуживанием в рамках проекта: вы можете [get](#getProperty_int_Property), [clone](#cloneProperty_UGUID_cstr_cstr_Property), [inherit](#inheritProperty_UGUID_cstr_cstr_Property) или [remove](#removeProperty_UGUID_int_int_int) любое свойство в проекте. [Reparenting](#reparentProperty_UGUID_UGUID_int_int) поддерживается для всех [non-manual](../../../api/library/common/class.property_cpp.md#isManual_int) и [editable](../../../api/library/common/class.property_cpp.md#isEditable_int) свойств.


Вы также можете [subscribe for such events](#callbacks), чтобы обрабатывать их.


> **Notice:** Чтобы изменить одно свойство, используйте функции класса [Property](../../../api/library/common/class.property_cpp.md).


### Обработка событий


Вы можете подписываться на события, чтобы отслеживать любые изменения, вносимые в любое свойство, и выполнять определённые действия. Сигнатура функции-обработчика должна быть следующей:


```cpp
void handler_function_name(const PropertyPtr &property);
```


Ниже приведён пример отслеживания удаления свойства через события:


```cpp
void AppWorldLogic::property_removed(const PropertyPtr &property)
{
	Log::message("Property \"%s\" was removed.\n", property->getName());
}

// где-то в коде

// наследуем новое свойство с именем "new_property_1" от базового свойства "surface_base"
Properties::findManualProperty("surface_base")->inherit("new_property_1");

// подписываемся на удаление свойства
Properties::getEventRemoved().connect(this, &AppWorldLogic::property_removed);

// удаляем свойство с именем "new_property_1"
Properties::removeProperty(Properties::findProperty("new_property_1")->getGUID());

```


## Класс Properties

### Методы класса

## int getNumProperties () const

Возвращает текущее общее количество свойств, загруженных для проекта.
### Возвращаемое значение

Текущее общее количество свойств, загруженных для проекта.
## static Event<const Ptr < Property > &> getEventRemoved () const

Событие, срабатывающее при удалении свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Removed
void removed_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Removed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections removed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Properties::getEventRemoved().connect(removed_event_connections, removed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Properties::getEventRemoved().connect(removed_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Removed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
removed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection removed_event_connection;

// подписываемся на событие Removed с функцией-обработчиком, сохраняя соединение
Properties::getEventRemoved().connect(removed_event_connection, removed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
removed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
removed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Removed через соединение
removed_event_connection.disconnect();

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

	// Обработчик события Removed, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Removed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Properties::getEventRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId removed_handler_id;

// подписываемся на событие Removed с лямбда-обработчиком, сохраняя идентификатор соединения
removed_handler_id = Properties::getEventRemoved().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Removed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Properties::getEventRemoved().disconnect(removed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Removed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Properties::getEventRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Properties::getEventRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Property > &> getEventReparented () const

Событие, срабатывающее при изменении родителя свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Reparented
void reparented_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Reparented\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections reparented_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Properties::getEventReparented().connect(reparented_event_connections, reparented_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Properties::getEventReparented().connect(reparented_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Reparented (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
reparented_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection reparented_event_connection;

// подписываемся на событие Reparented с функцией-обработчиком, сохраняя соединение
Properties::getEventReparented().connect(reparented_event_connection, reparented_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
reparented_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
reparented_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Reparented через соединение
reparented_event_connection.disconnect();

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

	// Обработчик события Reparented, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Reparented\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Properties::getEventReparented().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId reparented_handler_id;

// подписываемся на событие Reparented с лямбда-обработчиком, сохраняя идентификатор соединения
reparented_handler_id = Properties::getEventReparented().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Reparented (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Properties::getEventReparented().disconnect(reparented_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Reparented при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Properties::getEventReparented().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Properties::getEventReparented().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Property > &> getEventRenamed () const

Событие, срабатывающее при изменении [name](../../../api/library/common/class.property_cpp.md#name_path) свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Renamed
void renamed_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Renamed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections renamed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Properties::getEventRenamed().connect(renamed_event_connections, renamed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Properties::getEventRenamed().connect(renamed_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Renamed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
renamed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection renamed_event_connection;

// подписываемся на событие Renamed с функцией-обработчиком, сохраняя соединение
Properties::getEventRenamed().connect(renamed_event_connection, renamed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
renamed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
renamed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Renamed через соединение
renamed_event_connection.disconnect();

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

	// Обработчик события Renamed, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Renamed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Properties::getEventRenamed().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId renamed_handler_id;

// подписываемся на событие Renamed с лямбда-обработчиком, сохраняя идентификатор соединения
renamed_handler_id = Properties::getEventRenamed().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Renamed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Properties::getEventRenamed().disconnect(renamed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Renamed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Properties::getEventRenamed().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Properties::getEventRenamed().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Property > &> getEventMoved () const

Событие, срабатывающее при изменении [path](../../../api/library/common/class.property_cpp.md#name_path) свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Moved
void moved_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Moved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections moved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Properties::getEventMoved().connect(moved_event_connections, moved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Properties::getEventMoved().connect(moved_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Moved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
moved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection moved_event_connection;

// подписываемся на событие Moved с функцией-обработчиком, сохраняя соединение
Properties::getEventMoved().connect(moved_event_connection, moved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
moved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
moved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Moved через соединение
moved_event_connection.disconnect();

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

	// Обработчик события Moved, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Moved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Properties::getEventMoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId moved_handler_id;

// подписываемся на событие Moved с лямбда-обработчиком, сохраняя идентификатор соединения
moved_handler_id = Properties::getEventMoved().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Moved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Properties::getEventMoved().disconnect(moved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Moved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Properties::getEventMoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Properties::getEventMoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Property > &> getEventCreated () const

Событие, срабатывающее при создании нового свойства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Property> & **property**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Created
void created_event_handler(const Ptr<Property> & property)
{
	Log::message("\Обработка события Created\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections created_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Properties::getEventCreated().connect(created_event_connections, created_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Properties::getEventCreated().connect(created_event_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Created (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
created_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection created_event_connection;

// подписываемся на событие Created с функцией-обработчиком, сохраняя соединение
Properties::getEventCreated().connect(created_event_connection, created_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
created_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
created_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Created через соединение
created_event_connection.disconnect();

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

	// Обработчик события Created, реализованный как член класса
	void event_handler(const Ptr<Property> & property)
	{
		Log::message("\Обработка события Created\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Properties::getEventCreated().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId created_handler_id;

// подписываемся на событие Created с лямбда-обработчиком, сохраняя идентификатор соединения
created_handler_id = Properties::getEventCreated().connect(e_connections, [](const Ptr<Property> & property) {
		Log::message("\Обработка события Created (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Properties::getEventCreated().disconnect(created_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Created при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Properties::getEventCreated().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Properties::getEventCreated().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## void setValidationEnabled ( bool enabled )

Устанавливает новое значение, указывающее, включена ли валидация свойств. Может использоваться для временного отключения валидации свойств во избежание различных проблем (например, во время генерации свойств).
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить валидацию свойств; **false** - чтобы отключить её.

## bool isValidationEnabled () const

Возвращает текущее значение, указывающее, включена ли валидация свойств. Может использоваться для временного отключения валидации свойств во избежание различных проблем (например, во время генерации свойств).
### Возвращаемое значение

**true**, если валидация свойств включена; иначе **false**.
---

## Ptr < Property > getProperty ( int num ) const

Возвращает свойство по его номеру. Возвращённое свойство можно изменять с помощью методов класса [Property](../../../api/library/common/class.property_cpp.md).
```cpp
Vector<PropertyPtr> my_properties;
for (int i = 0; i < Properties::getNumProperties(); i++) {
	my_properties.append(Properties::getProperty(i));
}

```


### Аргументы

- *int* **num** - Номер свойства в диапазоне от 0 до [total number of properties](#getNumProperties_int).

### Возвращаемое значение

Умный указатель на [Property](../../../api/library/common/class.property_cpp.md), если он существует, или NULL.
## bool isProperty ( const char * name ) const

Проверяет, существует ли свойство с заданным именем.
### Аргументы

- *const char ** **name** - Имя свойства.

### Возвращаемое значение

true, если свойство с заданным именем существует; иначе false.
## bool isProperty ( const UGUID & guid ) const

Проверяет, существует ли свойство с заданным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства.

### Возвращаемое значение

true, если свойство с заданным GUID существует; иначе false.
## bool isManualProperty ( const char * name ) const

Проверяет, существует ли свойство с заданным именем.
### Аргументы

- *const char ** **name** - Имя ручного свойства.

### Возвращаемое значение

true, если ручное свойство с заданным именем существует; иначе false.
## const char * getPropertyName ( int num ) const

Возвращает имя свойства по его номеру.
### Аргументы

- *int* **num** - Номер свойства в диапазоне от 0 до [total number of properties](#getNumProperties_int).

### Возвращаемое значение

Имя свойства.
> **Notice:** Если свойство с указанным номером является внутренним и имеет родителя, будет возвращено имя родителя.


## Ptr < Property > cloneProperty ( const UGUID & guid , const char * name = 0 , const char * path = 0 )

Клонирует свойство и присваивает клону указанные имя и путь.
> **Notice:** Без имени клонированное свойство не будет отображаться в иерархии свойств, без пути оно не будет сохранено при вызове *[saveProperties()](#saveProperties_int)*.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства, которое нужно клонировать.
- *const char ** **name** - Имя клонированного свойства.
- *const char ** **path** - Путь для сохранения клонированного свойства.

### Возвращаемое значение

Умный указатель на [Property](../../../api/library/common/class.property_cpp.md), если свойство с указанным GUID существует, или nullptr.
## Ptr < Property > findProperty ( const char * name ) const

Ищет свойство с заданным именем. Возвращённым свойством можно управлять с помощью методов класса [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const char ** **name** - Имя свойства.

### Возвращаемое значение

Свойство, если оно найдено (экземпляр класса [Property](../../../api/library/common/class.property_cpp.md)); иначе nullptr.
## Ptr < Property > findManualProperty ( const char * name ) const

Ищет ручное свойство с заданным именем. Возвращённым свойством можно управлять с помощью методов класса [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const char ** **name** - Имя ручного свойства.

### Возвращаемое значение

Ручное свойство, если оно найдено (экземпляр класса [Property](../../../api/library/common/class.property_cpp.md)); иначе nullptr.
## Ptr < Property > findPropertyByGUID ( const UGUID & guid ) const

Ищет свойство с заданным GUID. Возвращённым свойством можно управлять с помощью методов класса [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства.

### Возвращаемое значение

Свойство, если оно найдено (экземпляр класса [Property](../../../api/library/common/class.property_cpp.md)); иначе nullptr.
## Ptr < Property > findPropertyByPath ( const char * path ) const

Ищет свойство с заданным путём. Возвращённым свойством можно управлять с помощью методов класса [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const char ** **path** - [Path](../../../api/library/common/class.property_cpp.md#name_path) свойства.

### Возвращаемое значение

Свойство, если оно найдено (экземпляр класса [Property](../../../api/library/common/class.property_cpp.md)); иначе nullptr.
## Ptr < Property > findPropertyByFileGUID ( const UGUID & guid ) const

Ищет свойство с заданным GUID файла `*.prop`. Возвращённым свойством можно управлять с помощью методов класса [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла свойства.

### Возвращаемое значение

Свойство, если оно найдено (экземпляр класса [Property](../../../api/library/common/class.property_cpp.md)); иначе nullptr.
## Ptr < Property > loadProperty ( const char * path )

Загружает свойство из указанного файла `*.prop`. Возвращённым свойством можно управлять с помощью методов класса [Property](../../../api/library/common/class.property_cpp.md).
### Аргументы

- *const char ** **path** - Путь к файлу `*.prop`, из которого загружается свойство.

### Возвращаемое значение

Свойство, если оно успешно загружено (экземпляр класса [Property](../../../api/library/common/class.property_cpp.md)); иначе nullptr.
## Ptr < Property > inheritProperty ( const UGUID & guid , const char * name = 0 , const char * path = 0 )

Наследует свойство от заданного свойства и присваивает новому свойству указанные имя и путь.
> **Notice:** Без имени унаследованное свойство не будет отображаться в иерархии свойств, без пути оно не будет сохранено при вызове *[saveProperties()](#saveProperties_int)*.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства, от которого выполняется наследование.
- *const char ** **name** - Имя унаследованного свойства.
- *const char ** **path** - Путь для сохранения унаследованного свойства.

### Возвращаемое значение

Умный указатель на [Property](../../../api/library/common/class.property_cpp.md), если свойство с указанным GUID существует, или nullptr.
## bool removeProperty ( const UGUID & guid , bool remove_file = 0 , bool remove_children = 1 )

Удаляет свойство с указанным GUID.
> **Notice:** Корневое свойство (свойство без родителя) или [non-editable](../../../api/library/common/class.property_cpp.md#isEditable_int) свойство нельзя удалить с помощью этой функции.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) удаляемого свойства.
- *bool* **remove_file** - Флаг, указывающий, будет ли удалён соответствующий файл `*.prop`. Установите 1, чтобы удалить файл, или 0, чтобы оставить его.
- *bool* **remove_children** - Флаг, указывающий, будут ли удалены все дочерние элементы свойства. Установите 1, чтобы удалить все дочерние элементы свойства, или 0, чтобы связать все дочерние элементы с родителем.

### Возвращаемое значение

true, если свойство успешно удалено; иначе false.
## bool renameProperty ( const UGUID & guid , const char * new_name )

Изменяет [name](../../../api/library/common/class.property_cpp.md#name_path) свойства с указанным GUID.
> **Notice:** - Имя файла `*.prop` при этом не меняется.
> - Этот метод недоступен для [manual](../../../api/library/common/class.property_cpp.md#isManual_int) и [non-editable](../../../api/library/common/class.property_cpp.md#isEditable_int) свойств.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) переименовываемого свойства.
- *const char ** **new_name** - Новое имя, которое будет присвоено свойству.

### Возвращаемое значение

true, если свойство успешно переименовано; иначе false.
## bool replaceProperty ( const Ptr < Property > & property , const Ptr < Property > & new_property )

 Заменяет указанное свойство новым для всех узлов и поверхностей. Новое свойство, заменяющее указанное, должно существовать. Например, если у вас есть 3 узла с одним и тем же свойством, вызов этого метода изменит это свойство на указанное для всех этих узлов.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Заменяемое свойство.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **new_property** - Новое свойство.

### Возвращаемое значение

true, если свойство успешно заменено; иначе false.
## bool reparentProperty ( const UGUID & guid , const UGUID & new_parent , bool save_all_values = 0 )

Устанавливает нового родителя для указанного свойства. Оба свойства с заданными GUID должны существовать.
> **Notice:** Метод недоступен для [manual](../../../api/library/common/class.property_cpp.md#isManual_int) и [non-editable](../../../api/library/common/class.property_cpp.md#isEditable_int) свойств.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства, родителя которого нужно изменить.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_parent** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) свойства, которое будет назначено новым родителем.
- *bool* **save_all_values** - Флаг, указывающий, будут ли сохранены значения параметров указанного свойства после смены родителя.

### Возвращаемое значение

true, если родитель свойства успешно изменён; иначе false.
## void reloadProperties ( )

Перезагружает все файлы `*.prop` из всех папок данных.
> **Notice:** Если найдены новые файлы `*.prop`, они будут загружены автоматически. При необходимости иерархия будет перестроена с сохранением всех переопределённых значений параметров.


## int saveProperties ( ) const

Сохраняет все свойства, которые можно сохранить, в соответствующие файлы `*.prop`.
> **Notice:** Этот метод сохранит только те свойства, которые:
> - не являются [manual](../../../api/library/common/class.property_cpp.md#isManual_int)
> - являются [editable](../../../api/library/common/class.property_cpp.md#isEditable_int)
> - имеют имя (не являются [internal](../../../api/library/common/class.property_cpp.md#isInternal_int))
> - имеют [path](../../../api/library/common/class.property_cpp.md#name_path)


### Возвращаемое значение

1, если все свойства успешно сохранены; иначе 0.
