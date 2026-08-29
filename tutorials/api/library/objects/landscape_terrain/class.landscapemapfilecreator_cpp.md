# Unigine.LandscapeMapFileCreator Class (CPP)

**Header:** #include <UnigineObjects.h>


Этот класс используется для генерации файла карты landscape (`.lmap`), используемого для создания [landscape layer map](../../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md).


### Пример использования


```cpp
using namespace Math;
// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

// методы, выполняемые в процессе создания файла карты landscape
void create(const LandscapeMapFileCreatorPtr& creator)
{
	Log::message("Создание LMAP\n");
}
void progress(const LandscapeMapFileCreatorPtr& creator)
{
	Log::message("%d %f\n", int(creator->getProgress()), creator->getTimeSeconds());
}
void begin(const LandscapeMapFileCreatorPtr& creator)
{
	Log::message("%f\n", creator->getProgress());
}
void end(const LandscapeMapFileCreatorPtr& creator)
{
	Log::message("%f\n", creator->getTimeSeconds());
}

	// ...

	// задаём размер сетки (2х2 тайла) и разрешение
	ivec2 grid = ivec2(2, 2);
	ivec2 resolution = ivec2(2048) * grid;

	// создаём генератор файла карты landscape и задаём размер сетки, разрешение и путь
	LandscapeMapFileCreatorPtr creator = LandscapeMapFileCreator::create();
	creator->setGrid(grid);
	creator->setResolution(resolution);
	creator->setPath("test.lmap");

	// подписываемся на необходимые события с нашими обработчиками
	creator->getEventCreate().connect(econnections, create);
	creator->getEventProgress().connect(econnections, progress);
	creator->getEventBegin().connect(econnections, begin);
	creator->getEventEnd().connect(econnections, end);

	// запускаем генератор для создания нового файла "test.lmap"
	creator->run();

	// ...

	// создаём новую карту слоя landscape на основе созданного файла "test.lmap"
	LandscapeLayerMapPtr landscape_map = LandscapeLayerMap::create();
	landscape_map->setPath("test.lmap");

	// ...

	// удаляем все подписки на события где-нибудь при завершении работы
	econnections.disconnectAll();


```


### См. также


- C++ sample


## LandscapeMapFileCreator Class

### Методы класса

## void setResolution ( const Math:: ivec2 & resolution )

Задаёт новое разрешение карты landscape.
### Arguments

- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md)&* **resolution** - Двухкомпонентный вектор (X, Y), представляющий разрешение карты landscape по осям X и Y, в пикселях.

## Math:: ivec2 getResolution () const

Возвращает текущее разрешение карты landscape.
### Возвращаемое значение

Текущий двухкомпонентный вектор (X, Y), представляющий разрешение карты landscape по осям X и Y, в пикселях.
## void setGrid ( const Math:: ivec2 & grid )

Задаёт новый размер сетки карты landscape.
### Arguments

- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md)&* **grid** - Двухкомпонентный вектор (X, Y), представляющий количество тайлов карты landscape по осям X и Y.

## Math:: ivec2 getGrid () const

Возвращает текущий размер сетки карты landscape.
### Возвращаемое значение

Текущий двухкомпонентный вектор (X, Y), представляющий количество тайлов карты landscape по осям X и Y.
## float getProgress () const

Возвращает текущий прогресс создания файла карты landscape.
### Возвращаемое значение

Текущий прогресс создания файла карты landscape (в процентах).
## double getTimeSeconds () const

Возвращает текущее время создания файла карты landscape. Этот метод можно использовать для получения общего времени генерации файла при обработке колбэка End.
### Возвращаемое значение

Текущее время создания файла карты landscape, в секундах.
## void setPath ( const char * path )

Задаёт новый путь к генерируемому файлу `*.lmap`.
### Arguments

- *const char ** **path** - Путь к генерируемому файлу `*.lmap`.

## const char * getPath () const

Возвращает текущий путь к генерируемому файлу `*.lmap`.
### Возвращаемое значение

Текущий путь к генерируемому файлу `*.lmap`.
## Event<const Ptr < LandscapeMapFileCreator > &> getEventEnd () const

Событие, срабатывающее по завершении создания файла карты landscape. Сигнатура функции обратного вызова должна быть следующей:
```cpp
void end_event_handler(const Ptr<LandscapeMapFileCreator> & creator)

```

 Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<LandscapeMapFileCreator> & **creator**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// implement the End event handler
void end_event_handler(const Ptr<LandscapeMapFileCreator> & creator)
{
	Log::message("\Handling End event\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Multiple subscriptions can be linked to an instance of the EventConnections
//  class that you can use later to remove all these subscriptions at once
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnections class
EventConnections end_event_connections;

// link to this instance when subscribing to an event (subscription to various events can be linked)
publisher->getEventEnd().connect(end_event_connections, end_event_handler);

// other subscriptions are also linked to this EventConnections instance
// (e.g. you can subscribe using lambdas)
publisher->getEventEnd().connect(end_event_connections, [](const Ptr<LandscapeMapFileCreator> & creator) {
		Log::message("\Handling End event (lambda).\n");
	}
);

// ...

// later all of these linked subscriptions can be removed with a single line
end_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. You can subscribe and unsubscribe via an instance of the EventConnection
//  class. And toggle this particular connection off and on, when necessary.
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnection class
EventConnection end_event_connection;

// subscribe to the End event with a handler function keeping the connection
publisher->getEventEnd().connect(end_event_connection, end_event_handler);

// ...

// you can temporarily disable a particular event connection to perform certain actions
end_event_connection.setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
end_event_connection.setEnabled(true);

// ...

// remove subscription to the End event via the connection
end_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. You can add EventConnection/EventConnections instance as a member of the
//  class that handles the event. In this case all linked subscriptions will be
//  automatically removed when class destructor is called
//////////////////////////////////////////////////////////////////////////////

// Class handling the event
class SomeClass
{
public:
	// instance of the EventConnections class as a class member
	EventConnections e_connections;

	// A End event handler implemented as a class member
	void event_handler(const Ptr<LandscapeMapFileCreator> & creator)
	{
		Log::message("\Handling End event\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// specify a class instance in case a handler method belongs to some class
publisher->getEventEnd().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// handler class instance is deleted with all its subscriptions removed automatically
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Subscribe to an event saving a particular connection ID
//   and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////
// instance of the EventConnections class to manage event connections
EventConnections e_connections;

// define a particular connection ID to be used to unsubscribe later
EventConnectionId end_handler_id;

// subscribe to the End event with a lambda handler function and keeping connection ID
end_handler_id = publisher->getEventEnd().connect(e_connections, [](const Ptr<LandscapeMapFileCreator> & creator) {
		Log::message("\Handling End event (lambda).\n");
	}
);

// remove the subscription later using the ID
publisher->getEventEnd().disconnect(end_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Ignoring all End events when necessary
//////////////////////////////////////////////////////////////////////////////

// you can temporarily disable the event to perform certain actions without triggering it
publisher->getEventEnd().setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
publisher->getEventEnd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < LandscapeMapFileCreator > &> getEventBegin () const

Событие, срабатывающее в начале создания файла карты landscape. Сигнатура функции обратного вызова должна быть следующей:
```cpp
void begin_event_handler(const Ptr<LandscapeMapFileCreator> & creator)

```

 Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<LandscapeMapFileCreator> & **creator**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// implement the Begin event handler
void begin_event_handler(const Ptr<LandscapeMapFileCreator> & creator)
{
	Log::message("\Handling Begin event\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Multiple subscriptions can be linked to an instance of the EventConnections
//  class that you can use later to remove all these subscriptions at once
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnections class
EventConnections begin_event_connections;

// link to this instance when subscribing to an event (subscription to various events can be linked)
publisher->getEventBegin().connect(begin_event_connections, begin_event_handler);

// other subscriptions are also linked to this EventConnections instance
// (e.g. you can subscribe using lambdas)
publisher->getEventBegin().connect(begin_event_connections, [](const Ptr<LandscapeMapFileCreator> & creator) {
		Log::message("\Handling Begin event (lambda).\n");
	}
);

// ...

// later all of these linked subscriptions can be removed with a single line
begin_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. You can subscribe and unsubscribe via an instance of the EventConnection
//  class. And toggle this particular connection off and on, when necessary.
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnection class
EventConnection begin_event_connection;

// subscribe to the Begin event with a handler function keeping the connection
publisher->getEventBegin().connect(begin_event_connection, begin_event_handler);

// ...

// you can temporarily disable a particular event connection to perform certain actions
begin_event_connection.setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
begin_event_connection.setEnabled(true);

// ...

// remove subscription to the Begin event via the connection
begin_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. You can add EventConnection/EventConnections instance as a member of the
//  class that handles the event. In this case all linked subscriptions will be
//  automatically removed when class destructor is called
//////////////////////////////////////////////////////////////////////////////

// Class handling the event
class SomeClass
{
public:
	// instance of the EventConnections class as a class member
	EventConnections e_connections;

	// A Begin event handler implemented as a class member
	void event_handler(const Ptr<LandscapeMapFileCreator> & creator)
	{
		Log::message("\Handling Begin event\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// specify a class instance in case a handler method belongs to some class
publisher->getEventBegin().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// handler class instance is deleted with all its subscriptions removed automatically
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Subscribe to an event saving a particular connection ID
//   and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////
// instance of the EventConnections class to manage event connections
EventConnections e_connections;

// define a particular connection ID to be used to unsubscribe later
EventConnectionId begin_handler_id;

// subscribe to the Begin event with a lambda handler function and keeping connection ID
begin_handler_id = publisher->getEventBegin().connect(e_connections, [](const Ptr<LandscapeMapFileCreator> & creator) {
		Log::message("\Handling Begin event (lambda).\n");
	}
);

// remove the subscription later using the ID
publisher->getEventBegin().disconnect(begin_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Ignoring all Begin events when necessary
//////////////////////////////////////////////////////////////////////////////

// you can temporarily disable the event to perform certain actions without triggering it
publisher->getEventBegin().setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
publisher->getEventBegin().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < LandscapeMapFileCreator > &> getEventProgress () const

Событие, срабатывающее при изменении прогресса создания файла карты landscape. Сигнатура функции обратного вызова должна быть следующей:
```cpp
void progress_event_handler(const Ptr<LandscapeMapFileCreator> & creator)

```

 Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<LandscapeMapFileCreator> & **creator**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// implement the Progress event handler
void progress_event_handler(const Ptr<LandscapeMapFileCreator> & creator)
{
	Log::message("\Handling Progress event\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Multiple subscriptions can be linked to an instance of the EventConnections
//  class that you can use later to remove all these subscriptions at once
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnections class
EventConnections progress_event_connections;

// link to this instance when subscribing to an event (subscription to various events can be linked)
publisher->getEventProgress().connect(progress_event_connections, progress_event_handler);

// other subscriptions are also linked to this EventConnections instance
// (e.g. you can subscribe using lambdas)
publisher->getEventProgress().connect(progress_event_connections, [](const Ptr<LandscapeMapFileCreator> & creator) {
		Log::message("\Handling Progress event (lambda).\n");
	}
);

// ...

// later all of these linked subscriptions can be removed with a single line
progress_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. You can subscribe and unsubscribe via an instance of the EventConnection
//  class. And toggle this particular connection off and on, when necessary.
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnection class
EventConnection progress_event_connection;

// subscribe to the Progress event with a handler function keeping the connection
publisher->getEventProgress().connect(progress_event_connection, progress_event_handler);

// ...

// you can temporarily disable a particular event connection to perform certain actions
progress_event_connection.setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
progress_event_connection.setEnabled(true);

// ...

// remove subscription to the Progress event via the connection
progress_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. You can add EventConnection/EventConnections instance as a member of the
//  class that handles the event. In this case all linked subscriptions will be
//  automatically removed when class destructor is called
//////////////////////////////////////////////////////////////////////////////

// Class handling the event
class SomeClass
{
public:
	// instance of the EventConnections class as a class member
	EventConnections e_connections;

	// A Progress event handler implemented as a class member
	void event_handler(const Ptr<LandscapeMapFileCreator> & creator)
	{
		Log::message("\Handling Progress event\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// specify a class instance in case a handler method belongs to some class
publisher->getEventProgress().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// handler class instance is deleted with all its subscriptions removed automatically
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Subscribe to an event saving a particular connection ID
//   and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////
// instance of the EventConnections class to manage event connections
EventConnections e_connections;

// define a particular connection ID to be used to unsubscribe later
EventConnectionId progress_handler_id;

// subscribe to the Progress event with a lambda handler function and keeping connection ID
progress_handler_id = publisher->getEventProgress().connect(e_connections, [](const Ptr<LandscapeMapFileCreator> & creator) {
		Log::message("\Handling Progress event (lambda).\n");
	}
);

// remove the subscription later using the ID
publisher->getEventProgress().disconnect(progress_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Ignoring all Progress events when necessary
//////////////////////////////////////////////////////////////////////////////

// you can temporarily disable the event to perform certain actions without triggering it
publisher->getEventProgress().setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
publisher->getEventProgress().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < LandscapeMapFileCreator > &, const Ptr < LandscapeImages > &, int, int> getEventCreate () const

Событие, срабатывающее при создании файла карты слоя landscape. Сигнатура функции обратного вызова должна быть следующей:
```cpp
void create_event_handler(const Ptr<LandscapeMapFileCreator> & creator,  const Ptr<LandscapeImages> & images,  int x,  int y)

```

 Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<LandscapeMapFileCreator> & **creator**, const Ptr<LandscapeImages> & **images**, int **x**, int **y**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// implement the Create event handler
void create_event_handler(const Ptr<LandscapeMapFileCreator> & creator,  const Ptr<LandscapeImages> & images,  int x,  int y)
{
	Log::message("\Handling Create event\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Multiple subscriptions can be linked to an instance of the EventConnections
//  class that you can use later to remove all these subscriptions at once
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnections class
EventConnections create_event_connections;

// link to this instance when subscribing to an event (subscription to various events can be linked)
publisher->getEventCreate().connect(create_event_connections, create_event_handler);

// other subscriptions are also linked to this EventConnections instance
// (e.g. you can subscribe using lambdas)
publisher->getEventCreate().connect(create_event_connections, [](const Ptr<LandscapeMapFileCreator> & creator,  const Ptr<LandscapeImages> & images,  int x,  int y) {
		Log::message("\Handling Create event (lambda).\n");
	}
);

// ...

// later all of these linked subscriptions can be removed with a single line
create_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. You can subscribe and unsubscribe via an instance of the EventConnection
//  class. And toggle this particular connection off and on, when necessary.
//////////////////////////////////////////////////////////////////////////////

// create an instance of the EventConnection class
EventConnection create_event_connection;

// subscribe to the Create event with a handler function keeping the connection
publisher->getEventCreate().connect(create_event_connection, create_event_handler);

// ...

// you can temporarily disable a particular event connection to perform certain actions
create_event_connection.setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
create_event_connection.setEnabled(true);

// ...

// remove subscription to the Create event via the connection
create_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. You can add EventConnection/EventConnections instance as a member of the
//  class that handles the event. In this case all linked subscriptions will be
//  automatically removed when class destructor is called
//////////////////////////////////////////////////////////////////////////////

// Class handling the event
class SomeClass
{
public:
	// instance of the EventConnections class as a class member
	EventConnections e_connections;

	// A Create event handler implemented as a class member
	void event_handler(const Ptr<LandscapeMapFileCreator> & creator,  const Ptr<LandscapeImages> & images,  int x,  int y)
	{
		Log::message("\Handling Create event\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// specify a class instance in case a handler method belongs to some class
publisher->getEventCreate().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// handler class instance is deleted with all its subscriptions removed automatically
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Subscribe to an event saving a particular connection ID
//   and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////
// instance of the EventConnections class to manage event connections
EventConnections e_connections;

// define a particular connection ID to be used to unsubscribe later
EventConnectionId create_handler_id;

// subscribe to the Create event with a lambda handler function and keeping connection ID
create_handler_id = publisher->getEventCreate().connect(e_connections, [](const Ptr<LandscapeMapFileCreator> & creator,  const Ptr<LandscapeImages> & images,  int x,  int y) {
		Log::message("\Handling Create event (lambda).\n");
	}
);

// remove the subscription later using the ID
publisher->getEventCreate().disconnect(create_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Ignoring all Create events when necessary
//////////////////////////////////////////////////////////////////////////////

// you can temporarily disable the event to perform certain actions without triggering it
publisher->getEventCreate().setEnabled(false);

// ... actions to be performed

// and enable it back when necessary
publisher->getEventCreate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static LandscapeMapFileCreatorPtr create ( )

Конструктор LandscapeMapFileCreator.
## void setDownscaleFilter ( Landscape::TYPE_FILE_DATA file_data_type , Image::FILTER filter )

Задаёт новый тип фильтрации, используемый для уменьшения масштаба изображения, выполняемого для LOD указанного типа данных файла.
### Arguments

- *[Landscape::TYPE_FILE_DATA](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#TYPE_FILE_DATA)* **file_data_type** - Тип данных файла.
- *[Image::FILTER](../../../../api/library/common/class.image_cpp.md#FILTER)* **filter** - Тип фильтра, используемый для уменьшения масштаба. См. [Unigine::Image Enumerations with FILTER_* prefixes](../../../../api/library/common/class.image_cpp.md#FILTER_LINEAR).

## Image::FILTER getDownscaleFilter ( Landscape::TYPE_FILE_DATA file_data_type ) const

Возвращает текущий тип фильтрации, используемый для уменьшения масштаба изображения, выполняемого для LOD указанного типа данных файла.
### Arguments

- *[Landscape::TYPE_FILE_DATA](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#TYPE_FILE_DATA)* **file_data_type** - Тип данных файла.

### Возвращаемое значение

Тип фильтра, используемый для уменьшения масштаба изображения. См. [Unigine::Image Enumerations with FILTER_* prefixes](../../../../api/library/common/class.image_cpp.md#FILTER_LINEAR).
## bool run ( bool is_empty = false , bool is_safe = true )

Запускает процесс создания файла карты landscape. Вы можете [set callbacks](#example), срабатывающие в начале, по завершении и во время процесса для отслеживания прогресса и отображения статистики. Создаёт путь к файлу карты landscape, если он ещё не существует (включая подкаталоги).
### Arguments

- *bool* **is_empty** - true, чтобы создать пустой файл `.lmap` (например, при создании карты слоя, которая будет вручную создаваться с нуля с помощью [brushes](../../../../editor2/brush_editor/index.md)), false — чтобы получить необходимые данные из источников и поместить их в генерируемый файл `.lmap`.
- *bool* **is_safe** - true, чтобы движок автоматически вызывал методы *filesClose()/fileOpen()* при выполнении операций (перед изменением файла `.lmap` движок должен освободить файлы через *filesClose()*, а после изменения должен быть вызван *fileOpen()*), false — чтобы вызывать методы *filesClose()/fileOpen()* вручную. Класс Landscape имеет две перегрузки метода *filesClose()*: > **Notice:** При **is_safe = true** движок всегда будет вызывать *filesClose(reload_files)* с полной перезагрузкой данных.

  - [*filesClose()*](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#filesClose_void) — следует вызывать при перемещении файла `.lmap` (перезагрузка данных не выполняется, так как сам файл не изменялся — экономит время на перезагрузку данных)
  - [*filesClose(reload_files)*](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#filesClose_VECUGUID_void) — следует вызывать при удалении или изменении файла `.lmap`.

### Возвращаемое значение

true, если операция выполнена успешно; иначе false.
