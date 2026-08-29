# Unigine::Animations Class (CPP)

**Header:** #include <UnigineAnimation.h>

> **Notice:** Этот класс является синглтоном.


Этот класс является центральным менеджером системы анимации. Он предоставляет функциональность для двух подсистем анимации:


- **Timeline Animation** — управление [animation tracks](../../../principles/animations/index.md#animation_track) (`.utrack`) и [animation playbacks](../../../principles/animations/index.md#animation_playback) (`.uplay`), запрос анимируемых классов и их параметров, а также конвертация устаревших форматов анимации.
- **Animation Scripts** — работа с [animation scripts](../../../api/library/animations/skeletal/class.animscript_cpp.md) (скомпилированными графами анимации, с которыми можно взаимодействовать через код), запрос типов графов и отслеживание процесса сборки.


## Animations Class

### Перечисления

## RESULT

| Имя | Описание |
|---|---|
| **RESULT_TRACK_ERROR** = 0 | Произошла ошибка, связанная с треком. |
| **RESULT_NEW_TRACK_LOADED** = 1 | Загружен новый [animation track](../../../principles/animations/index.md#animation_track). |
| **RESULT_TRACK_IS_ALREADY_LOADED** = 2 | [Animation track](../../../principles/animations/index.md#animation_track) уже загружен. |
| **RESULT_TRACK_RELOADED** = 3 | [Animation track](../../../principles/animations/index.md#animation_track) перезагружен. |
| **RESULT_TRACK_SAVED** = 4 | [Animation track](../../../principles/animations/index.md#animation_track) сохранён. |
| **RESULT_TRACK_UNLOADED** = 5 | [Animation track](../../../principles/animations/index.md#animation_track) выгружен. |
| **RESULT_PLAYBACK_ERROR** = 6 | Произошла ошибка, связанная с проигрыванием. |
| **RESULT_NEW_PLAYBACK_LOADED** = 7 | Загружено новое [animation playback](../../../principles/animations/index.md#animation_playback). |
| **RESULT_PLAYBACK_IS_ALREADY_LOADED** = 8 | [Animation playback](../../../principles/animations/index.md#animation_playback) уже загружено. |
| **RESULT_PLAYBACK_SAVED** = 9 | [Animation playback](../../../principles/animations/index.md#animation_playback) сохранено. |

### Методы класса

## getNumObjects () const

Возвращает текущее общее количество анимированных объектов.
### Возвращаемое значение

Текущее количество [animated objects](../../../principles/animations/index.md#animation_object).
## getNumTracks () const

Возвращает текущее общее количество [animation tracks](../../../principles/animations/index.md#animation_track).
### Возвращаемое значение

Текущее количество треков анимации.
## getNumPlaybacks () const

Возвращает текущее общее количество [animation playbacks](../../../principles/animations/index.md#animation_playback).
### Возвращаемое значение

Текущее количество проигрываний анимации.
## static Event<const Ptr < AnimationTrack > &> getEventTrackRemoved () const

Событие, срабатывающее при удалении [animation track](../../../principles/animations/index.md#animation_track). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<AnimationTrack> & **anim_track**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TrackRemoved
void trackremoved_event_handler(const Ptr<AnimationTrack> & anim_track)
{
	Log::message("\Обработка события TrackRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections trackremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Animations::getEventTrackRemoved().connect(trackremoved_event_connections, trackremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Animations::getEventTrackRemoved().connect(trackremoved_event_connections, [](const Ptr<AnimationTrack> & anim_track) {
		Log::message("\Обработка события TrackRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
trackremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection trackremoved_event_connection;

// подписываемся на событие TrackRemoved с функцией-обработчиком, сохраняя соединение
Animations::getEventTrackRemoved().connect(trackremoved_event_connection, trackremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
trackremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
trackremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TrackRemoved через соединение
trackremoved_event_connection.disconnect();

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

	// Обработчик события TrackRemoved, реализованный как член класса
	void event_handler(const Ptr<AnimationTrack> & anim_track)
	{
		Log::message("\Обработка события TrackRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Animations::getEventTrackRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId trackremoved_handler_id;

// подписываемся на событие TrackRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
trackremoved_handler_id = Animations::getEventTrackRemoved().connect(e_connections, [](const Ptr<AnimationTrack> & anim_track) {
		Log::message("\Обработка события TrackRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Animations::getEventTrackRemoved().disconnect(trackremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TrackRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Animations::getEventTrackRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Animations::getEventTrackRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < AnimationTrack > &> getEventTrackAdded () const

Событие, срабатывающее при добавлении нового [animation track](../../../principles/animations/index.md#animation_track). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<AnimationTrack> & **anim_track**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TrackAdded
void trackadded_event_handler(const Ptr<AnimationTrack> & anim_track)
{
	Log::message("\Обработка события TrackAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections trackadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Animations::getEventTrackAdded().connect(trackadded_event_connections, trackadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Animations::getEventTrackAdded().connect(trackadded_event_connections, [](const Ptr<AnimationTrack> & anim_track) {
		Log::message("\Обработка события TrackAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
trackadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection trackadded_event_connection;

// подписываемся на событие TrackAdded с функцией-обработчиком, сохраняя соединение
Animations::getEventTrackAdded().connect(trackadded_event_connection, trackadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
trackadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
trackadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TrackAdded через соединение
trackadded_event_connection.disconnect();

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

	// Обработчик события TrackAdded, реализованный как член класса
	void event_handler(const Ptr<AnimationTrack> & anim_track)
	{
		Log::message("\Обработка события TrackAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Animations::getEventTrackAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId trackadded_handler_id;

// подписываемся на событие TrackAdded с лямбда-обработчиком, сохраняя идентификатор соединения
trackadded_handler_id = Animations::getEventTrackAdded().connect(e_connections, [](const Ptr<AnimationTrack> & anim_track) {
		Log::message("\Обработка события TrackAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Animations::getEventTrackAdded().disconnect(trackadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TrackAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Animations::getEventTrackAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Animations::getEventTrackAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < AnimationObject > &> getEventObjectRemoved () const

Событие, срабатывающее при удалении [animation object](../../../principles/animations/index.md#animation_object). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<AnimationObject> & **anim_object**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ObjectRemoved
void objectremoved_event_handler(const Ptr<AnimationObject> & anim_object)
{
	Log::message("\Обработка события ObjectRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections objectremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Animations::getEventObjectRemoved().connect(objectremoved_event_connections, objectremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Animations::getEventObjectRemoved().connect(objectremoved_event_connections, [](const Ptr<AnimationObject> & anim_object) {
		Log::message("\Обработка события ObjectRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
objectremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection objectremoved_event_connection;

// подписываемся на событие ObjectRemoved с функцией-обработчиком, сохраняя соединение
Animations::getEventObjectRemoved().connect(objectremoved_event_connection, objectremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
objectremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ObjectRemoved через соединение
objectremoved_event_connection.disconnect();

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

	// Обработчик события ObjectRemoved, реализованный как член класса
	void event_handler(const Ptr<AnimationObject> & anim_object)
	{
		Log::message("\Обработка события ObjectRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Animations::getEventObjectRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId objectremoved_handler_id;

// подписываемся на событие ObjectRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
objectremoved_handler_id = Animations::getEventObjectRemoved().connect(e_connections, [](const Ptr<AnimationObject> & anim_object) {
		Log::message("\Обработка события ObjectRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Animations::getEventObjectRemoved().disconnect(objectremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ObjectRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Animations::getEventObjectRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Animations::getEventObjectRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < AnimationObject > &> getEventObjectAdded () const

Событие, срабатывающее при добавлении нового [animation object](../../../principles/animations/index.md#animation_object). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<AnimationObject> & **anim_object**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ObjectAdded
void objectadded_event_handler(const Ptr<AnimationObject> & anim_object)
{
	Log::message("\Обработка события ObjectAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections objectadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Animations::getEventObjectAdded().connect(objectadded_event_connections, objectadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Animations::getEventObjectAdded().connect(objectadded_event_connections, [](const Ptr<AnimationObject> & anim_object) {
		Log::message("\Обработка события ObjectAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
objectadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection objectadded_event_connection;

// подписываемся на событие ObjectAdded с функцией-обработчиком, сохраняя соединение
Animations::getEventObjectAdded().connect(objectadded_event_connection, objectadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
objectadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ObjectAdded через соединение
objectadded_event_connection.disconnect();

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

	// Обработчик события ObjectAdded, реализованный как член класса
	void event_handler(const Ptr<AnimationObject> & anim_object)
	{
		Log::message("\Обработка события ObjectAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Animations::getEventObjectAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId objectadded_handler_id;

// подписываемся на событие ObjectAdded с лямбда-обработчиком, сохраняя идентификатор соединения
objectadded_handler_id = Animations::getEventObjectAdded().connect(e_connections, [](const Ptr<AnimationObject> & anim_object) {
		Log::message("\Обработка события ObjectAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Animations::getEventObjectAdded().disconnect(objectadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ObjectAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Animations::getEventObjectAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Animations::getEventObjectAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<string, string, string> getEventCustomLibBuild () const

Событие, срабатывающее при сборке пользовательской библиотеки скриптов анимации. Обработчик получает пути к сгенерированному исходному файлу C++, скомпилированной библиотеке и журналу сборки. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **cpp_path**, const char * **lib_path**, const char * **log_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CustomLibBuild
void customlibbuild_event_handler(const char * cpp_path,  const char * lib_path,  const char * log_path)
{
	Log::message("\Обработка события CustomLibBuild\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections customlibbuild_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventCustomLibBuild().connect(customlibbuild_event_connections, customlibbuild_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventCustomLibBuild().connect(customlibbuild_event_connections, [](const char * cpp_path,  const char * lib_path,  const char * log_path) {
		Log::message("\Обработка события CustomLibBuild (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
customlibbuild_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection customlibbuild_event_connection;

// подписываемся на событие CustomLibBuild с функцией-обработчиком, сохраняя соединение
publisher->getEventCustomLibBuild().connect(customlibbuild_event_connection, customlibbuild_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
customlibbuild_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
customlibbuild_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CustomLibBuild через соединение
customlibbuild_event_connection.disconnect();

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

	// Обработчик события CustomLibBuild, реализованный как член класса
	void event_handler(const char * cpp_path,  const char * lib_path,  const char * log_path)
	{
		Log::message("\Обработка события CustomLibBuild\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventCustomLibBuild().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId customlibbuild_handler_id;

// подписываемся на событие CustomLibBuild с лямбда-обработчиком, сохраняя идентификатор соединения
customlibbuild_handler_id = publisher->getEventCustomLibBuild().connect(e_connections, [](const char * cpp_path,  const char * lib_path,  const char * log_path) {
		Log::message("\Обработка события CustomLibBuild (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventCustomLibBuild().disconnect(customlibbuild_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CustomLibBuild при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventCustomLibBuild().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventCustomLibBuild().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## int getNumAnimScriptTypes () const

Возвращает текущее общее количество зарегистрированных типов [animation script](../../../api/library/animations/skeletal/class.animscript_cpp.md).
### Возвращаемое значение

Текущее количество зарегистрированных типов скриптов анимации.
## bool isAnimScriptsSuccessBuild () const

Возвращает значение, указывающее, была ли последняя сборка [animation script](../../../api/library/animations/skeletal/class.animscript_cpp.md) успешной.
### Возвращаемое значение

**true**, если последняя сборка скрипта анимации завершилась успешно; иначе **false**.
## bool isAnimScriptsRebuilding () const

Возвращает значение, указывающее, выполняется ли в данный момент пересборка [animation scripts](../../../api/library/animations/skeletal/class.animscript_cpp.md).
### Возвращаемое значение

**true**, если скрипты анимации в данный момент пересобираются; иначе **false**.
## bool isAnimScriptsLoaded () const

Возвращает значение, указывающее, загружены ли [animation scripts](../../../api/library/animations/skeletal/class.animscript_cpp.md).
### Возвращаемое значение

**true**, если скрипты анимации загружены; иначе **false**.
---

## Ptr < AnimationObject > getObjectByIndex ( int index ) const

Возвращает [animation object](../../../principles/animations/index.md#animation_object) по его индексу в общем списке объектов анимации.
### Аргументы

- *int* **index** - Индекс объекта анимации.

### Возвращаемое значение

Объект анимации с указанным индексом
## Ptr < AnimationObject > getObjectByID ( int id ) const

Возвращает [animation object](../../../principles/animations/index.md#animation_object) по его ID.
### Аргументы

- *int* **id** - ID объекта анимации.

### Возвращаемое значение

Объект анимации с указанным ID.
## bool containsObject ( int id ) const

Возвращает значение, указывающее, существует ли [animation object](../../../principles/animations/index.md#animation_object) с указанным ID.
### Аргументы

- *int* **id** - ID объекта анимации.

### Возвращаемое значение

true, если объект анимации с указанным ID существует; иначе false.
## int getObjectIndex ( const Ptr < AnimationObject > & obj ) const

Возвращает индекс указанного [animation object](../../../principles/animations/index.md#animation_object) в общем списке.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AnimationObject](../../../api/library/animations/timeline/class.animationobject_cpp.md)> &* **obj** - Объект анимации, для которого требуется найти индекс.

### Возвращаемое значение

Индекс объекта анимации в общем списке объектов анимации, если он найден; иначе -1.
## void loadTracks ( )

Загружает все [animation tracks](../../../principles/animations/index.md#animation_track).
## void unloadTracks ( )

Выгружает все [animation tracks](../../../principles/animations/index.md#animation_track).
## void reloadTracks ( )

Перезагружает все [animation tracks](../../../principles/animations/index.md#animation_track).
## Animations::RESULT loadTrack ( const char * path )

Загружает [animation track](../../../principles/animations/index.md#animation_track) из указанного пути к файлу.
### Аргументы

- *const char ** **path** - Путь к исходному файлу трека (`.utrack`).

### Возвращаемое значение

Результат операции загрузки.
## Animations::RESULT reloadTrack ( const char * path )

Перезагружает [animation track](../../../principles/animations/index.md#animation_track) из указанного пути к файлу.
### Аргументы

- *const char ** **path** - Путь к исходному файлу трека (`.utrack`).

### Возвращаемое значение

Результат операции перезагрузки.
## Animations::RESULT saveTrack ( const Ptr < AnimationTrack > & track , const char * path )

Сохраняет указанный [animation track](../../../principles/animations/index.md#animation_track) по указанному пути к файлу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Трек анимации, который требуется сохранить.
- *const char ** **path** - Путь, по которому требуется сохранить указанный трек анимации.

### Возвращаемое значение

Результат операции сохранения.
## Animations::RESULT saveTrackPrecomputed ( const Ptr < AnimationTrack > & track , int num_frames , bool is_looped_frames , const char * path )

Сохраняет предварительно вычисленную версию указанного [animation track](../../../principles/animations/index.md#animation_track) по указанному пути к файлу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Трек анимации, который требуется сохранить.
- *int* **num_frames** - Количество кадров, которые требуется сохранить.
- *bool* **is_looped_frames** - Установите true, если трек анимации должен быть зациклен; иначе false.
- *const char ** **path** - Путь, по которому требуется сохранить указанный трек анимации.

### Возвращаемое значение

Результат операции сохранения.
## Ptr < AnimationTrack > getTrackByIndex ( int index )

Возвращает [animation track](../../../principles/animations/index.md#animation_track) по его индексу в общем списке треков.
### Аргументы

- *int* **index** - Индекс трека анимации в общем списке треков.

### Возвращаемое значение

Трек анимации с указанным индексом.
## Ptr < AnimationTrack > getTrackByGUID ( const UGUID & guid )

Возвращает [animation track](../../../principles/animations/index.md#animation_track) по его GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID трека анимации.

### Возвращаемое значение

Трек анимации с указанным GUID.
## Ptr < AnimationTrack > getTrackByFileGUID ( const UGUID & guid )

Возвращает [animation track](../../../principles/animations/index.md#animation_track) по GUID файла трека анимации (`.utrack`).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID файла трека анимации (`.utrack`).

### Возвращаемое значение

Трек анимации с указанным GUID файла.
## Ptr < AnimationTrack > getTrackByPath ( const char * path )

Возвращает [animation track](../../../principles/animations/index.md#animation_track) по пути к файлу трека анимации (`.utrack`).
### Аргументы

- *const char ** **path** - Путь к файлу трека анимации (`.utrack`).

### Возвращаемое значение

Трек анимации с указанным GUID файла.
## bool containsTrack ( const UGUID & guid )

Возвращает значение, указывающее, существует ли [animation track](../../../principles/animations/index.md#animation_track) с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID трека анимации.

### Возвращаемое значение

true, если трек анимации с указанным GUID существует; иначе false.
## int getTrackIndex ( const Ptr < AnimationTrack > & track )

Возвращает индекс указанного [animation track](../../../principles/animations/index.md#animation_track) в общем списке.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AnimationTrack](../../../api/library/animations/timeline/class.animationtrack_cpp.md)> &* **track** - Трек анимации, для которого требуется найти индекс.

### Возвращаемое значение

Индекс трека анимации в общем списке треков анимации, если он найден; иначе -1.
## void loadPlaybacks ( )

Загружает все [animation playbacks](../../../principles/animations/index.md#animation_playback).
## Animations::RESULT loadPlayback ( const char * path )

Загружает [animation playback](../../../principles/animations/index.md#animation_playback) из указанного пути к файлу.
### Аргументы

- *const char ** **path** - Путь к исходному файлу проигрывания анимации (`.uplay`).

### Возвращаемое значение

Результат операции загрузки.
## Animations::RESULT savePlayback ( const Ptr < AnimationPlayback > & playback , const char * path )

Сохраняет указанное [animation playback](../../../principles/animations/index.md#animation_playback) по указанному пути к файлу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Проигрывание анимации, которое требуется сохранить.
- *const char ** **path** - Путь, по которому требуется сохранить указанное проигрывание анимации.

### Возвращаемое значение

Результат операции сохранения.
## Ptr < AnimationPlayback > getPlaybackByIndex ( int index ) const

Возвращает [animation playback](../../../principles/animations/index.md#animation_playback) по его индексу в общем списке треков.
### Аргументы

- *int* **index** - Индекс проигрывания анимации в общем списке проигрываний.

### Возвращаемое значение

Проигрывание анимации с указанным индексом.
## Ptr < AnimationPlayback > getPlaybackByGUID ( const UGUID & guid ) const

Возвращает [animation playback](../../../principles/animations/index.md#animation_playback) по его GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID проигрывания анимации.

### Возвращаемое значение

Проигрывание анимации с указанным GUID.
## Ptr < AnimationPlayback > getPlaybackByFileGUID ( const UGUID & guid ) const

Возвращает [animation playback](../../../principles/animations/index.md#animation_playback) по GUID файла трека анимации (`.uplay`).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID файла проигрывания анимации (`.uplay`).

### Возвращаемое значение

Трек анимации с указанным GUID файла.
## Ptr < AnimationPlayback > getPlaybackByPath ( const char * path ) const

Возвращает [animation playback](../../../principles/animations/index.md#animation_playback) по пути к файлу трека анимации (`.uplay`).
### Аргументы

- *const char ** **path** - Путь к файлу проигрывания анимации (`.uplay`).

### Возвращаемое значение

Проигрывание анимации с указанным путём.
## bool containsPlayback ( const UGUID & guid ) const

Возвращает значение, указывающее, существует ли [animation playback](../../../principles/animations/index.md#animation_playback) с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID проигрывания анимации.

### Возвращаемое значение

true, если проигрывание анимации с указанным GUID существует; иначе false.
## int getPlaybackIndex ( const Ptr < AnimationPlayback > & playback ) const

Возвращает индекс указанного [animation playbacks](../../../principles/animations/index.md#animation_playback) в общем списке.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AnimationPlayback](../../../api/library/animations/timeline/class.animationplayback_cpp.md)> &* **playback** - Проигрывание анимации, для которого требуется найти индекс.

### Возвращаемое значение

Индекс трека анимации в общем списке треков анимации, если он найден; иначе -1.
## int getClasses ( Vector < String > & OUT_out_classes )

Получает список имён всех доступных классов, которые могут быть анимированы, и помещает его в указанный выходной буфер.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_out_classes** - Выходной буфер для списка классов Движка, которые могут быть анимированы. > **Notice:** Этот выходной буфер заполняется Движком в результате выполнения метода.

### Возвращаемое значение

Количество классов Движка, которые могут быть анимированы.
## int getSingletonClasses ( Vector < String > & OUT_out_classes )

Получает список имён всех классов-синглтонов Движка и помещает его в указанный выходной буфер.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_out_classes** - Выходной буфер для списка классов-синглтонов Движка. > **Notice:** Этот выходной буфер заполняется Движком в результате выполнения метода.

### Возвращаемое значение

Количество классов-синглтонов Движка.
## const char * getParentClass ( const char * class_name ) const

Возвращает имя родительского класса для указанного класса.
### Аргументы

- *const char ** **class_name** - Имя класса, для которого требуется найти родительский класс.

### Возвращаемое значение

Имя родительского класса.
## int getDerivedClasses ( const char * class_name , Vector < String > & OUT_out_classes ) const

Получает список всех классов, производных от указанного, и помещает его в указанный выходной буфер.
### Аргументы

- *const char ** **class_name** - Имя класса, для которого требуется найти производные классы.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_out_classes** - Выходной буфер для списка классов, производных от указанного класса. > **Notice:** Этот выходной буфер заполняется Движком в результате выполнения метода.

### Возвращаемое значение

Количество производных классов.
## int getClassParameters ( const char * class_name , Vector <int> & OUT_out_parameters ) const

Получает список всех [animation parameters](../../../principles/animations/index.md#animation_parameters) для указанного класса и помещает его в указанный выходной буфер.
### Аргументы

- *const char ** **class_name** - Имя класса, для которого требуется найти список параметров анимации.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_out_parameters** - Выходной буфер для списка параметров указанного класса. > **Notice:** Этот выходной буфер заполняется Движком в результате выполнения метода.

### Возвращаемое значение

Количество параметров анимации для указанного класса.
## const char * getParameterName ( AnimParams::PARAM param ) const

Возвращает имя указанного [animation parameter](../../../principles/animations/index.md#animation_parameters).
### Аргументы

- *AnimParams::PARAM* **param** - Параметр анимации.

### Возвращаемое значение

Имя параметра анимации.
## AnimationModifier::TYPE getParameterModifierType ( AnimParams::PARAM param ) const

Возвращает тип модификатора, используемого для указанного [animation parameter](../../../principles/animations/index.md#animation_parameters).
### Аргументы

- *AnimParams::PARAM* **param** - Параметр анимации.

### Возвращаемое значение

Тип модификатора для указанного параметра.
## AnimParams::PARAM getParameterByName ( const char * param_name ) const

Возвращает [animation parameter](../../../principles/animations/index.md#animation_parameters) по его имени.
### Аргументы

- *const char ** **param_name** - Имя параметра анимации.

### Возвращаемое значение

Параметр анимации с указанным именем.
## void convertToUanims ( const char * folder_path , const Vector < String > & playbacks )

Конвертирует все файлы треков в старом формате *Tracker* (`.track`) из указанной папки в новые форматы анимации (`.utrack` / `.uplay`).
### Аргументы

- *const char ** **folder_path** - Путь к папке, содержащей файлы треков в старом формате *Tracker* (`.track`), которые требуется конвертировать в новый формат трека (`.utrack`).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **playbacks** - Список треков анимации *Tracker* в старом формате (`.track`), которые требуется конвертировать в новый формат проигрывания (`.uplay`).

## void convertToUanims ( const Vector < String > & tracks , const Vector < String > & playbacks )

Конвертирует указанные списки треков в старом формате *Tracker* (`.track`) в новые форматы анимации (`.utrack` / `.uplay`).
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **tracks** - Список треков анимации *Tracker* в старом формате (`.track`), которые требуется конвертировать в новый формат трека (`.utrack`).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **playbacks** - Список треков анимации *Tracker* в старом формате (`.track`), которые требуется конвертировать в новый формат проигрывания (`.uplay`).

## void checkUtrackTypes ( )

Проверяет все старые типы параметров анимации (используемые в инструменте *Tracker*) на соответствие их эквивалентам в новой системе анимации и выводит их в консоль. В случае обнаружения неизвестных типов параметров выводится соответствующее сообщение.
## bool animToBonesModifier ( const char * anim_path , const Ptr < AnimationModifierBones > & out_modifier , float duration ) const

Конвертирует указанный файл анимации меша (`.anim`) в [modifier](../../../principles/animations/index.md#animation_modifier) для костей [ObjectMeshSkinnedLegacy](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md) (*AnimationModifierBones*) и помещает его в указанный экземпляр *AnimationModifierBones*.
### Аргументы

- *const char ** **anim_path** - Путь к файлу анимации меша (`.anim`), который требуется конвертировать.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AnimationModifierBones](../../../api/library/animations/timeline/class.animationmodifierbones_cpp.md)> &* **out_modifier** - Результирующий модификатор анимации.
- *float* **duration** - Целевая продолжительность анимации, в секундах.

### Возвращаемое значение

true, если указанный файл анимации меша был успешно конвертирован; иначе false.
## void rebuildAnimScripts ( )

Запускает пересборку всех [animation scripts](../../../api/library/animations/skeletal/class.animscript_cpp.md). Это перекомпилирует исходные файлы графа анимации в библиотеку времени выполнения. Используйте соответствующий метод, чтобы проверить, продолжается ли процесс пересборки, и другой метод, чтобы проверить, завершился ли он успешно.
## const char * getAnimScriptTypeName ( int type_index ) const

Возвращает имя типа [animation script](../../../api/library/animations/skeletal/class.animscript_cpp.md) по его индексу.
### Аргументы

- *int* **type_index** - Индекс типа скрипта анимации в диапазоне от 0 до количества типов.

### Возвращаемое значение

Имя типа скрипта анимации.
## static void waitAnimScriptsRebuilding ( )

Блокирует выполнение до тех пор, пока текущая пересборка скриптов анимации не завершится. Если пересборка выполняется, этот метод ожидает завершения фоновой задачи сборки, а затем загружает обновлённую библиотеку. Если пересборка не выполняется, метод возвращает управление немедленно.
