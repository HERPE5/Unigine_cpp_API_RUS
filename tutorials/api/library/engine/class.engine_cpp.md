# Unigine::Engine Class (CPP)

**Header:** #include <UnigineEngine.h>


The Engine class is required for the engine [initialization](../../../code/fundamentals/execution_sequence/init.md) and executing the [main loop](../../../code/fundamentals/execution_sequence/main_loop.md) of the program. Also, you can get the engine [startup options](../../../code/command_line.md) through this class.


The **InitParameters** structure provides the way to set the following parameters to initialize a new Engine instance:.


| Parameter | Description |
|---|---|
| **window_title** | Title of the window. |
| **window_icon_path** | Path to the window icon. |
| **app_path** | Path to a directory where binary executable file is stored. |
| **home_path** | Path to the user's home directory. |
| **project** | Project name. |
| **password** | Password for the filesystem archives. |
| **system_proxy** | Instance of the [CustomSystemProxy](../../../api/library/engine/class.customsystemproxy_cpp.md) class. |


## Engine Class

### Перечисления

## BUILD_CONFIG

Engine build configuration.
| Name | Description |
|---|---|
| **BUILD_CONFIG_DEBUG** = 0 | Debug build configuration. |
| **BUILD_CONFIG_DEVELOPMENT** = 1 | Development build configuration. |
| **BUILD_CONFIG_RELEASE** = 2 | Release build configuration. |

## BACKGROUND_UPDATE

Engine background update mode.
| Name | Description |
|---|---|
| **BACKGROUND_UPDATE_DISABLED** = 0 | Background update is disabled. |
| **BACKGROUND_UPDATE_RENDER_NON_MINIMIZED** = 1 | Background update is enabled (rendering is performed when the window is out of focus, but stops if the window is minimized). |
| **BACKGROUND_UPDATE_RENDER_ALWAYS** = 2 | Background update is always enabled (rendering is performed all the time, regardless of the window state. |

## PRECISION

engine precision type.
| Name | Description |
|---|---|
| **PRECISION_PRECISION_FLOAT** = 0 | Float precision type. |
| **PRECISION_PRECISION_DOUBLE** = 1 | Double precision type. |

### Методы класса

## static bool isInitialized () const

Returns the current value indicating whether the engine is initialized.
### Возвращаемое значение

**true** if the Engine is initialized; otherwise **false**.
## static const char * getAppPath () const

Returns the current path to a directory where binary executable file is stored.
### Возвращаемое значение

Current path to a directory where binary executable file is stored.
## static const char * getDataPath () const

Returns the current path to the data directory.
### Возвращаемое значение

Current path to the data directory.
## static const char * getHomePath () const

Returns the current path to the user's home directory.
### Возвращаемое значение

Current path to the user's home directory.
## static const char * getSavePath () const

Returns the current path to a directory with the default configuration file, saved files, etc.
### Возвращаемое значение

Current path to a directory with the default configuration file, saved files, etc.
## static const char * getCachePath () const

Returns the current path to the directory with cached files.
### Возвращаемое значение

Current path to the directory with cached files.
## static int getNumPluginPaths () const

Returns the current number of directory paths to plugins that were set using the [-plugin_path](../../../code/command_line.md#plugin_path) startup command-line option.
### Возвращаемое значение

Current number of directory paths to plugins that were set using the [-plugin_path](../../../code/command_line.md#plugin_path) startup command-line option.
## static const char * getSystemScript () const

Returns the current path to the system script.
### Возвращаемое значение

Current path to the system script.
## static const char * getSystemCache () const

Returns the current path to the system script cache.
### Возвращаемое значение

Current path to the system script cache.
## static const char * getEditorCache () const

Returns the current path to the editor script cache.
### Возвращаемое значение

Current path to the editor script cache.
## static const char * getVideoApp () const

Returns the current graphics API used for rendering.
### Возвращаемое значение

Current graphics API used for rendering.
## static const char * getSoundApp () const

Returns the current sound API used.
### Возвращаемое значение

Current sound API used.
## static const char * getExternDefine () const

Returns the current list of [external definitions](../../../code/command_line.md#extern_define) specified on the application start-up.
### Возвращаемое значение

Current list of external definitions.
## static const char * getFeatures () const

Returns the current list of features like Direct3D, Microprofile, Geodetic, etc.
### Возвращаемое значение

Current list of features like Direct3D, Microprofile, Geodetic, etc.
## static const char * getVersion () const

Returns the current engine version info.
### Возвращаемое значение

Current engine version info.
## static void setBackgroundUpdate ( Engine.BACKGROUND_UPDATE update )

Sets a new value indicating whether the application window is updated when the window is hidden or out of focus (rendering frames in background). By default your UNIGINE application stops rendering frames and updating its main window, when it window goes out of focus (e.g. user switches to another window). Setting the background update mode enables constant rendering regardless of whether the application window is focused or in the background.
### Аргументы

- *[Engine.BACKGROUND_UPDATE](../../../api/library/engine/class.engine_cpp.md#BACKGROUND_UPDATE)* **update** - The value indicating whether the application window is updated when the window is hidden or out of focus (rendering frames in background).

## static Engine.BACKGROUND_UPDATE getBackgroundUpdate () const

Returns the current value indicating whether the application window is updated when the window is hidden or out of focus (rendering frames in background). By default your UNIGINE application stops rendering frames and updating its main window, when it window goes out of focus (e.g. user switches to another window). Setting the background update mode enables constant rendering regardless of whether the application window is focused or in the background.
### Возвращаемое значение

Current value indicating whether the application window is updated when the window is hidden or out of focus (rendering frames in background).
## static bool isActive () const

Returns the current **active** state of the Engine.
### Возвращаемое значение

**true** if the engine is active; otherwise **false**.
## static bool isFocus () const

Returns the current value showing if any of the Engine windows is in focus.
### Возвращаемое значение

**true** if the Engine window is focused; otherwise **false**.
## static bool isQuit () const

Returns the current **quitting** flag on engine quit.
### Возвращаемое значение

**true** if the engine is quitting; otherwise **false**.
## static float getTotalTime () const

Returns the current total time (in milliseconds) that both rendering and calculating of the frame took (the duration of the [main loop](../../../code/fundamentals/execution_sequence/main_loop.md) in the application [execution sequence](../../../code/fundamentals/execution_sequence/index.md)). Includes *update, render, swap and wait GPU*.
### Возвращаемое значение

Current total time value, in milliseconds.
## static float getTotalCPUTime () const

Returns the current total CPU time (in milliseconds) taken to perform calculations for the frame (the duration of the [main loop](../../../code/fundamentals/execution_sequence/main_loop.md) in the application [execution sequence](../../../code/fundamentals/execution_sequence/index.md)). Includes *update, render and swap*.
### Возвращаемое значение

Current total CPU time value, in milliseconds.
## static float getUpdateTime () const

Returns the current duration (in milliseconds) of the [update phase](../../../code/fundamentals/execution_sequence/main_loop.md#update), during which the objects are prepared for their collision response to be calculated.
### Возвращаемое значение

Current update phase duration value, in milliseconds.
## static float getRenderTime () const

Returns the current time (in milliseconds) required to prepare all data to be rendered in the current frame and feed rendering commands from the CPU to the GPU. See the [Profiler](../../../tools/profiling/profiler/index.md#render_cpu) article for details.
### Возвращаемое значение

Current rendering time value, in milliseconds.
## static float getPresentTime () const

Returns the current total time (in milliseconds) spent on waiting for the GPU after all calculations on the CPU are completed. See the [Profiler](../../../tools/profiling/profiler/index.md#present) article for details.
### Возвращаемое значение

Current time value, in milliseconds.
## static float getInterfaceTime () const

Returns the current total accumulative time (in milliseconds) spent on rendering GUI widgets.
### Возвращаемое значение

Current time value, in milliseconds.
## static int64_t getFrame () const

Returns the current number of the current engine frame.
### Возвращаемое значение

Current engine frame number.
## static float getFps () const

Returns the current value of the Engine FPS counter.
### Возвращаемое значение

Current value of the Engine FPS counter.
## static float getIFps () const

Returns the current inverse value of the Engine FPS counter (1/FPS).
### Возвращаемое значение

Current inverse value of the Engine FPS counter (1/FPS).
## static float getStatisticsFpsMin () const

Returns the current minimum FPS counter value for the last 600 frames.
### Возвращаемое значение

Current minimum FPS counter value for the last 600 frames.
## static float getStatisticsFpsAvg () const

Returns the current average FPS counter value for the last 600 frames.
### Возвращаемое значение

Current average FPS counter value for the last 600 frames.
## static float getStatisticsFpsMax () const

Returns the current maximum FPS counter value for the last 600 frames.
### Возвращаемое значение

Current maximum FPS counter value for the last 600 frames.
## static bool isMainThread () const

Returns the current value indicating if the current thread is main.
### Возвращаемое значение

**true** if the current thread is main; otherwise **false**.
## static Ptr < Player > getMainPlayer () const

Returns the current main player.
### Возвращаемое значение

Current main player.
## static bool isEvaluation () const

Returns the current value indicating if the running version of the Engine is for evaluation only.
### Возвращаемое значение

**true** if the evaluation version of the Engine is used; otherwise **false**.
## static int getNumEditorLogics () const

Returns the current number of [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instances.
### Возвращаемое значение

Current number of [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instances.
## static int getNumWorldLogics () const

Returns the current number of [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instances.
### Возвращаемое значение

Current number of [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instances.
## static int getNumSystemLogics () const

Returns the current number of [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instances.
### Возвращаемое значение

Current number of [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instances.
## static int getNumArgs () const

Returns the current number of command line arguments.
### Возвращаемое значение

Current number of command line arguments.
## static int getNumPlugins () const

Returns the current number of loaded plugins.
### Возвращаемое значение

Current number of loaded plugins.
## static Engine::PRECISION getPrecision () const

Returns the current precision type.
### Возвращаемое значение

Current precision type.
## static Event getEventBeginUpdate () const

event triggered before the update stage is started. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginUpdate
void beginupdate_event_handler()
{
	Log::message("\Обработка события BeginUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginUpdate().connect(beginupdate_event_connections, beginupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginUpdate().connect(beginupdate_event_connections, []() {
		Log::message("\Обработка события BeginUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginupdate_event_connection;

// подписываемся на событие BeginUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginUpdate().connect(beginupdate_event_connection, beginupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginUpdate через соединение
beginupdate_event_connection.disconnect();

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

	// Обработчик события BeginUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginupdate_handler_id;

// подписываемся на событие BeginUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginupdate_handler_id = Engine::getEventBeginUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginUpdate().disconnect(beginupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPropertiesUpdate () const

event triggered before the properties update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPropertiesUpdate
void beginpropertiesupdate_event_handler()
{
	Log::message("\Обработка события BeginPropertiesUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpropertiesupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPropertiesUpdate().connect(beginpropertiesupdate_event_connections, beginpropertiesupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPropertiesUpdate().connect(beginpropertiesupdate_event_connections, []() {
		Log::message("\Обработка события BeginPropertiesUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpropertiesupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpropertiesupdate_event_connection;

// подписываемся на событие BeginPropertiesUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPropertiesUpdate().connect(beginpropertiesupdate_event_connection, beginpropertiesupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpropertiesupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpropertiesupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPropertiesUpdate через соединение
beginpropertiesupdate_event_connection.disconnect();

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

	// Обработчик события BeginPropertiesUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPropertiesUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPropertiesUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpropertiesupdate_handler_id;

// подписываемся на событие BeginPropertiesUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginpropertiesupdate_handler_id = Engine::getEventBeginPropertiesUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginPropertiesUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPropertiesUpdate().disconnect(beginpropertiesupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPropertiesUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPropertiesUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPropertiesUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPropertiesUpdate () const

event triggered after the properties update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPropertiesUpdate
void endpropertiesupdate_event_handler()
{
	Log::message("\Обработка события EndPropertiesUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpropertiesupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPropertiesUpdate().connect(endpropertiesupdate_event_connections, endpropertiesupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPropertiesUpdate().connect(endpropertiesupdate_event_connections, []() {
		Log::message("\Обработка события EndPropertiesUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpropertiesupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpropertiesupdate_event_connection;

// подписываемся на событие EndPropertiesUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPropertiesUpdate().connect(endpropertiesupdate_event_connection, endpropertiesupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpropertiesupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpropertiesupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPropertiesUpdate через соединение
endpropertiesupdate_event_connection.disconnect();

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

	// Обработчик события EndPropertiesUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPropertiesUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPropertiesUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpropertiesupdate_handler_id;

// подписываемся на событие EndPropertiesUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endpropertiesupdate_handler_id = Engine::getEventEndPropertiesUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndPropertiesUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPropertiesUpdate().disconnect(endpropertiesupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPropertiesUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPropertiesUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPropertiesUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginInputUpdate () const

event triggered before the input update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginInputUpdate
void begininputupdate_event_handler()
{
	Log::message("\Обработка события BeginInputUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begininputupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginInputUpdate().connect(begininputupdate_event_connections, begininputupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginInputUpdate().connect(begininputupdate_event_connections, []() {
		Log::message("\Обработка события BeginInputUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begininputupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begininputupdate_event_connection;

// подписываемся на событие BeginInputUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginInputUpdate().connect(begininputupdate_event_connection, begininputupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begininputupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begininputupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginInputUpdate через соединение
begininputupdate_event_connection.disconnect();

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

	// Обработчик события BeginInputUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginInputUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginInputUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begininputupdate_handler_id;

// подписываемся на событие BeginInputUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
begininputupdate_handler_id = Engine::getEventBeginInputUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginInputUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginInputUpdate().disconnect(begininputupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginInputUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginInputUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginInputUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndInputUpdate () const

event triggered after the input update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndInputUpdate
void endinputupdate_event_handler()
{
	Log::message("\Обработка события EndInputUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endinputupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndInputUpdate().connect(endinputupdate_event_connections, endinputupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndInputUpdate().connect(endinputupdate_event_connections, []() {
		Log::message("\Обработка события EndInputUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endinputupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endinputupdate_event_connection;

// подписываемся на событие EndInputUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndInputUpdate().connect(endinputupdate_event_connection, endinputupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endinputupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endinputupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndInputUpdate через соединение
endinputupdate_event_connection.disconnect();

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

	// Обработчик события EndInputUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndInputUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndInputUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endinputupdate_handler_id;

// подписываемся на событие EndInputUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endinputupdate_handler_id = Engine::getEventEndInputUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndInputUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndInputUpdate().disconnect(endinputupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndInputUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndInputUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndInputUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginControlsUpdate () const

event triggered before the controls update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginControlsUpdate
void begincontrolsupdate_event_handler()
{
	Log::message("\Обработка события BeginControlsUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begincontrolsupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginControlsUpdate().connect(begincontrolsupdate_event_connections, begincontrolsupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginControlsUpdate().connect(begincontrolsupdate_event_connections, []() {
		Log::message("\Обработка события BeginControlsUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begincontrolsupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begincontrolsupdate_event_connection;

// подписываемся на событие BeginControlsUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginControlsUpdate().connect(begincontrolsupdate_event_connection, begincontrolsupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begincontrolsupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begincontrolsupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginControlsUpdate через соединение
begincontrolsupdate_event_connection.disconnect();

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

	// Обработчик события BeginControlsUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginControlsUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginControlsUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begincontrolsupdate_handler_id;

// подписываемся на событие BeginControlsUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
begincontrolsupdate_handler_id = Engine::getEventBeginControlsUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginControlsUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginControlsUpdate().disconnect(begincontrolsupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginControlsUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginControlsUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginControlsUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndControlsUpdate () const

event triggered after the controls update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndControlsUpdate
void endcontrolsupdate_event_handler()
{
	Log::message("\Обработка события EndControlsUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endcontrolsupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndControlsUpdate().connect(endcontrolsupdate_event_connections, endcontrolsupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndControlsUpdate().connect(endcontrolsupdate_event_connections, []() {
		Log::message("\Обработка события EndControlsUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endcontrolsupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endcontrolsupdate_event_connection;

// подписываемся на событие EndControlsUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndControlsUpdate().connect(endcontrolsupdate_event_connection, endcontrolsupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endcontrolsupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endcontrolsupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndControlsUpdate через соединение
endcontrolsupdate_event_connection.disconnect();

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

	// Обработчик события EndControlsUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndControlsUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndControlsUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endcontrolsupdate_handler_id;

// подписываемся на событие EndControlsUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endcontrolsupdate_handler_id = Engine::getEventEndControlsUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndControlsUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndControlsUpdate().disconnect(endcontrolsupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndControlsUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndControlsUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndControlsUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginWorldManagerUpdate () const

event triggered before the world manager update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWorldManagerUpdate
void beginworldmanagerupdate_event_handler()
{
	Log::message("\Обработка события BeginWorldManagerUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginworldmanagerupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginWorldManagerUpdate().connect(beginworldmanagerupdate_event_connections, beginworldmanagerupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginWorldManagerUpdate().connect(beginworldmanagerupdate_event_connections, []() {
		Log::message("\Обработка события BeginWorldManagerUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginworldmanagerupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginworldmanagerupdate_event_connection;

// подписываемся на событие BeginWorldManagerUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginWorldManagerUpdate().connect(beginworldmanagerupdate_event_connection, beginworldmanagerupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginworldmanagerupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginworldmanagerupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWorldManagerUpdate через соединение
beginworldmanagerupdate_event_connection.disconnect();

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

	// Обработчик события BeginWorldManagerUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWorldManagerUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginWorldManagerUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginworldmanagerupdate_handler_id;

// подписываемся на событие BeginWorldManagerUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginworldmanagerupdate_handler_id = Engine::getEventBeginWorldManagerUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginWorldManagerUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginWorldManagerUpdate().disconnect(beginworldmanagerupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWorldManagerUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginWorldManagerUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginWorldManagerUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndWorldManagerUpdate () const

event triggered after the world manager update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWorldManagerUpdate
void endworldmanagerupdate_event_handler()
{
	Log::message("\Обработка события EndWorldManagerUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endworldmanagerupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndWorldManagerUpdate().connect(endworldmanagerupdate_event_connections, endworldmanagerupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndWorldManagerUpdate().connect(endworldmanagerupdate_event_connections, []() {
		Log::message("\Обработка события EndWorldManagerUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endworldmanagerupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endworldmanagerupdate_event_connection;

// подписываемся на событие EndWorldManagerUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndWorldManagerUpdate().connect(endworldmanagerupdate_event_connection, endworldmanagerupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endworldmanagerupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endworldmanagerupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWorldManagerUpdate через соединение
endworldmanagerupdate_event_connection.disconnect();

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

	// Обработчик события EndWorldManagerUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWorldManagerUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndWorldManagerUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endworldmanagerupdate_handler_id;

// подписываемся на событие EndWorldManagerUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endworldmanagerupdate_handler_id = Engine::getEventEndWorldManagerUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndWorldManagerUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndWorldManagerUpdate().disconnect(endworldmanagerupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWorldManagerUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndWorldManagerUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndWorldManagerUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSoundManagerUpdate () const

event triggered before the sound manager update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSoundManagerUpdate
void beginsoundmanagerupdate_event_handler()
{
	Log::message("\Обработка события BeginSoundManagerUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsoundmanagerupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSoundManagerUpdate().connect(beginsoundmanagerupdate_event_connections, beginsoundmanagerupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSoundManagerUpdate().connect(beginsoundmanagerupdate_event_connections, []() {
		Log::message("\Обработка события BeginSoundManagerUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsoundmanagerupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsoundmanagerupdate_event_connection;

// подписываемся на событие BeginSoundManagerUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSoundManagerUpdate().connect(beginsoundmanagerupdate_event_connection, beginsoundmanagerupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsoundmanagerupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsoundmanagerupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSoundManagerUpdate через соединение
beginsoundmanagerupdate_event_connection.disconnect();

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

	// Обработчик события BeginSoundManagerUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSoundManagerUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSoundManagerUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginsoundmanagerupdate_handler_id;

// подписываемся на событие BeginSoundManagerUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginsoundmanagerupdate_handler_id = Engine::getEventBeginSoundManagerUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginSoundManagerUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSoundManagerUpdate().disconnect(beginsoundmanagerupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSoundManagerUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSoundManagerUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSoundManagerUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSoundManagerUpdate () const

event triggered after the sound manager update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSoundManagerUpdate
void endsoundmanagerupdate_event_handler()
{
	Log::message("\Обработка события EndSoundManagerUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsoundmanagerupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSoundManagerUpdate().connect(endsoundmanagerupdate_event_connections, endsoundmanagerupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSoundManagerUpdate().connect(endsoundmanagerupdate_event_connections, []() {
		Log::message("\Обработка события EndSoundManagerUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsoundmanagerupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsoundmanagerupdate_event_connection;

// подписываемся на событие EndSoundManagerUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSoundManagerUpdate().connect(endsoundmanagerupdate_event_connection, endsoundmanagerupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsoundmanagerupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsoundmanagerupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSoundManagerUpdate через соединение
endsoundmanagerupdate_event_connection.disconnect();

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

	// Обработчик события EndSoundManagerUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSoundManagerUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSoundManagerUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endsoundmanagerupdate_handler_id;

// подписываемся на событие EndSoundManagerUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endsoundmanagerupdate_handler_id = Engine::getEventEndSoundManagerUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndSoundManagerUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSoundManagerUpdate().disconnect(endsoundmanagerupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSoundManagerUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSoundManagerUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSoundManagerUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginGameUpdate () const

event triggered before the game logic update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginGameUpdate
void begingameupdate_event_handler()
{
	Log::message("\Обработка события BeginGameUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begingameupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginGameUpdate().connect(begingameupdate_event_connections, begingameupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginGameUpdate().connect(begingameupdate_event_connections, []() {
		Log::message("\Обработка события BeginGameUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begingameupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begingameupdate_event_connection;

// подписываемся на событие BeginGameUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginGameUpdate().connect(begingameupdate_event_connection, begingameupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begingameupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begingameupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginGameUpdate через соединение
begingameupdate_event_connection.disconnect();

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

	// Обработчик события BeginGameUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginGameUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginGameUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begingameupdate_handler_id;

// подписываемся на событие BeginGameUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
begingameupdate_handler_id = Engine::getEventBeginGameUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginGameUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginGameUpdate().disconnect(begingameupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginGameUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginGameUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginGameUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndGameUpdate () const

event triggered after the game logic update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndGameUpdate
void endgameupdate_event_handler()
{
	Log::message("\Обработка события EndGameUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endgameupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndGameUpdate().connect(endgameupdate_event_connections, endgameupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndGameUpdate().connect(endgameupdate_event_connections, []() {
		Log::message("\Обработка события EndGameUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endgameupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endgameupdate_event_connection;

// подписываемся на событие EndGameUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndGameUpdate().connect(endgameupdate_event_connection, endgameupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endgameupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endgameupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndGameUpdate через соединение
endgameupdate_event_connection.disconnect();

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

	// Обработчик события EndGameUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndGameUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndGameUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endgameupdate_handler_id;

// подписываемся на событие EndGameUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endgameupdate_handler_id = Engine::getEventEndGameUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndGameUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndGameUpdate().disconnect(endgameupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndGameUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndGameUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndGameUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginRenderUpdate () const

event triggered before the render functions update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginRenderUpdate
void beginrenderupdate_event_handler()
{
	Log::message("\Обработка события BeginRenderUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginrenderupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginRenderUpdate().connect(beginrenderupdate_event_connections, beginrenderupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginRenderUpdate().connect(beginrenderupdate_event_connections, []() {
		Log::message("\Обработка события BeginRenderUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginrenderupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginrenderupdate_event_connection;

// подписываемся на событие BeginRenderUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginRenderUpdate().connect(beginrenderupdate_event_connection, beginrenderupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginrenderupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginrenderupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginRenderUpdate через соединение
beginrenderupdate_event_connection.disconnect();

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

	// Обработчик события BeginRenderUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginRenderUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginRenderUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginrenderupdate_handler_id;

// подписываемся на событие BeginRenderUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginrenderupdate_handler_id = Engine::getEventBeginRenderUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginRenderUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginRenderUpdate().disconnect(beginrenderupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginRenderUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginRenderUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginRenderUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndRenderUpdate () const

event triggered after the render functions update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndRenderUpdate
void endrenderupdate_event_handler()
{
	Log::message("\Обработка события EndRenderUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endrenderupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndRenderUpdate().connect(endrenderupdate_event_connections, endrenderupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndRenderUpdate().connect(endrenderupdate_event_connections, []() {
		Log::message("\Обработка события EndRenderUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endrenderupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endrenderupdate_event_connection;

// подписываемся на событие EndRenderUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndRenderUpdate().connect(endrenderupdate_event_connection, endrenderupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endrenderupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endrenderupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndRenderUpdate через соединение
endrenderupdate_event_connection.disconnect();

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

	// Обработчик события EndRenderUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndRenderUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndRenderUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endrenderupdate_handler_id;

// подписываемся на событие EndRenderUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endrenderupdate_handler_id = Engine::getEventEndRenderUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndRenderUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndRenderUpdate().disconnect(endrenderupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndRenderUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndRenderUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndRenderUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginExpressionUpdate () const

event triggered before the expressions update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginExpressionUpdate
void beginexpressionupdate_event_handler()
{
	Log::message("\Обработка события BeginExpressionUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginexpressionupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginExpressionUpdate().connect(beginexpressionupdate_event_connections, beginexpressionupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginExpressionUpdate().connect(beginexpressionupdate_event_connections, []() {
		Log::message("\Обработка события BeginExpressionUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginexpressionupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginexpressionupdate_event_connection;

// подписываемся на событие BeginExpressionUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginExpressionUpdate().connect(beginexpressionupdate_event_connection, beginexpressionupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginexpressionupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginexpressionupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginExpressionUpdate через соединение
beginexpressionupdate_event_connection.disconnect();

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

	// Обработчик события BeginExpressionUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginExpressionUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginExpressionUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginexpressionupdate_handler_id;

// подписываемся на событие BeginExpressionUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginexpressionupdate_handler_id = Engine::getEventBeginExpressionUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginExpressionUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginExpressionUpdate().disconnect(beginexpressionupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginExpressionUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginExpressionUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginExpressionUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndExpressionUpdate () const

event triggered after the expressions update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndExpressionUpdate
void endexpressionupdate_event_handler()
{
	Log::message("\Обработка события EndExpressionUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endexpressionupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndExpressionUpdate().connect(endexpressionupdate_event_connections, endexpressionupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndExpressionUpdate().connect(endexpressionupdate_event_connections, []() {
		Log::message("\Обработка события EndExpressionUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endexpressionupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endexpressionupdate_event_connection;

// подписываемся на событие EndExpressionUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndExpressionUpdate().connect(endexpressionupdate_event_connection, endexpressionupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endexpressionupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endexpressionupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndExpressionUpdate через соединение
endexpressionupdate_event_connection.disconnect();

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

	// Обработчик события EndExpressionUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndExpressionUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndExpressionUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endexpressionupdate_handler_id;

// подписываемся на событие EndExpressionUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endexpressionupdate_handler_id = Engine::getEventEndExpressionUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndExpressionUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndExpressionUpdate().disconnect(endexpressionupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndExpressionUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndExpressionUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndExpressionUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSoundsUpdate () const

event triggered before the sounds update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSoundsUpdate
void beginsoundsupdate_event_handler()
{
	Log::message("\Обработка события BeginSoundsUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsoundsupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSoundsUpdate().connect(beginsoundsupdate_event_connections, beginsoundsupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSoundsUpdate().connect(beginsoundsupdate_event_connections, []() {
		Log::message("\Обработка события BeginSoundsUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsoundsupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsoundsupdate_event_connection;

// подписываемся на событие BeginSoundsUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSoundsUpdate().connect(beginsoundsupdate_event_connection, beginsoundsupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsoundsupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsoundsupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSoundsUpdate через соединение
beginsoundsupdate_event_connection.disconnect();

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

	// Обработчик события BeginSoundsUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSoundsUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSoundsUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginsoundsupdate_handler_id;

// подписываемся на событие BeginSoundsUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginsoundsupdate_handler_id = Engine::getEventBeginSoundsUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginSoundsUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSoundsUpdate().disconnect(beginsoundsupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSoundsUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSoundsUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSoundsUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSoundsUpdate () const

event triggered after the sounds update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSoundsUpdate
void endsoundsupdate_event_handler()
{
	Log::message("\Обработка события EndSoundsUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsoundsupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSoundsUpdate().connect(endsoundsupdate_event_connections, endsoundsupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSoundsUpdate().connect(endsoundsupdate_event_connections, []() {
		Log::message("\Обработка события EndSoundsUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsoundsupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsoundsupdate_event_connection;

// подписываемся на событие EndSoundsUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSoundsUpdate().connect(endsoundsupdate_event_connection, endsoundsupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsoundsupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsoundsupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSoundsUpdate через соединение
endsoundsupdate_event_connection.disconnect();

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

	// Обработчик события EndSoundsUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSoundsUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSoundsUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endsoundsupdate_handler_id;

// подписываемся на событие EndSoundsUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endsoundsupdate_handler_id = Engine::getEventEndSoundsUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndSoundsUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSoundsUpdate().disconnect(endsoundsupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSoundsUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSoundsUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSoundsUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPluginsUpdate () const

event triggered before the plugins update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPluginsUpdate
void beginpluginsupdate_event_handler()
{
	Log::message("\Обработка события BeginPluginsUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpluginsupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPluginsUpdate().connect(beginpluginsupdate_event_connections, beginpluginsupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPluginsUpdate().connect(beginpluginsupdate_event_connections, []() {
		Log::message("\Обработка события BeginPluginsUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpluginsupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpluginsupdate_event_connection;

// подписываемся на событие BeginPluginsUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPluginsUpdate().connect(beginpluginsupdate_event_connection, beginpluginsupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpluginsupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpluginsupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPluginsUpdate через соединение
beginpluginsupdate_event_connection.disconnect();

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

	// Обработчик события BeginPluginsUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPluginsUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPluginsUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpluginsupdate_handler_id;

// подписываемся на событие BeginPluginsUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginpluginsupdate_handler_id = Engine::getEventBeginPluginsUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginPluginsUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPluginsUpdate().disconnect(beginpluginsupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPluginsUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPluginsUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPluginsUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPluginsUpdate () const

event triggered after the plugins update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPluginsUpdate
void endpluginsupdate_event_handler()
{
	Log::message("\Обработка события EndPluginsUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpluginsupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPluginsUpdate().connect(endpluginsupdate_event_connections, endpluginsupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPluginsUpdate().connect(endpluginsupdate_event_connections, []() {
		Log::message("\Обработка события EndPluginsUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpluginsupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpluginsupdate_event_connection;

// подписываемся на событие EndPluginsUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPluginsUpdate().connect(endpluginsupdate_event_connection, endpluginsupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpluginsupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpluginsupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPluginsUpdate через соединение
endpluginsupdate_event_connection.disconnect();

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

	// Обработчик события EndPluginsUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPluginsUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPluginsUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpluginsupdate_handler_id;

// подписываемся на событие EndPluginsUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endpluginsupdate_handler_id = Engine::getEventEndPluginsUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndPluginsUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPluginsUpdate().disconnect(endpluginsupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPluginsUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPluginsUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPluginsUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginVRUpdate () const

event triggered before the VR update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginVRUpdate
void beginvrupdate_event_handler()
{
	Log::message("\Обработка события BeginVRUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginvrupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginVRUpdate().connect(beginvrupdate_event_connections, beginvrupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginVRUpdate().connect(beginvrupdate_event_connections, []() {
		Log::message("\Обработка события BeginVRUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginvrupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginvrupdate_event_connection;

// подписываемся на событие BeginVRUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginVRUpdate().connect(beginvrupdate_event_connection, beginvrupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginvrupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginvrupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginVRUpdate через соединение
beginvrupdate_event_connection.disconnect();

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

	// Обработчик события BeginVRUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginVRUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginVRUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginvrupdate_handler_id;

// подписываемся на событие BeginVRUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginvrupdate_handler_id = Engine::getEventBeginVRUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginVRUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginVRUpdate().disconnect(beginvrupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginVRUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginVRUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginVRUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndVRUpdate () const

event triggered after the VR update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndVRUpdate
void endvrupdate_event_handler()
{
	Log::message("\Обработка события EndVRUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endvrupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndVRUpdate().connect(endvrupdate_event_connections, endvrupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndVRUpdate().connect(endvrupdate_event_connections, []() {
		Log::message("\Обработка события EndVRUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endvrupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endvrupdate_event_connection;

// подписываемся на событие EndVRUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndVRUpdate().connect(endvrupdate_event_connection, endvrupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endvrupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endvrupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndVRUpdate через соединение
endvrupdate_event_connection.disconnect();

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

	// Обработчик события EndVRUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndVRUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndVRUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endvrupdate_handler_id;

// подписываемся на событие EndVRUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endvrupdate_handler_id = Engine::getEventEndVRUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndVRUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndVRUpdate().disconnect(endvrupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndVRUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndVRUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndVRUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginEditorUpdate () const

event triggered before the editor update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginEditorUpdate
void begineditorupdate_event_handler()
{
	Log::message("\Обработка события BeginEditorUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begineditorupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginEditorUpdate().connect(begineditorupdate_event_connections, begineditorupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginEditorUpdate().connect(begineditorupdate_event_connections, []() {
		Log::message("\Обработка события BeginEditorUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begineditorupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begineditorupdate_event_connection;

// подписываемся на событие BeginEditorUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginEditorUpdate().connect(begineditorupdate_event_connection, begineditorupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begineditorupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begineditorupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginEditorUpdate через соединение
begineditorupdate_event_connection.disconnect();

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

	// Обработчик события BeginEditorUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginEditorUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginEditorUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begineditorupdate_handler_id;

// подписываемся на событие BeginEditorUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
begineditorupdate_handler_id = Engine::getEventBeginEditorUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginEditorUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginEditorUpdate().disconnect(begineditorupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginEditorUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginEditorUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginEditorUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndEditorUpdate () const

event triggered after the editor update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndEditorUpdate
void endeditorupdate_event_handler()
{
	Log::message("\Обработка события EndEditorUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endeditorupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndEditorUpdate().connect(endeditorupdate_event_connections, endeditorupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndEditorUpdate().connect(endeditorupdate_event_connections, []() {
		Log::message("\Обработка события EndEditorUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endeditorupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endeditorupdate_event_connection;

// подписываемся на событие EndEditorUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndEditorUpdate().connect(endeditorupdate_event_connection, endeditorupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endeditorupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endeditorupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndEditorUpdate через соединение
endeditorupdate_event_connection.disconnect();

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

	// Обработчик события EndEditorUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndEditorUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndEditorUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endeditorupdate_handler_id;

// подписываемся на событие EndEditorUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endeditorupdate_handler_id = Engine::getEventEndEditorUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndEditorUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndEditorUpdate().disconnect(endeditorupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndEditorUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndEditorUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndEditorUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSystemScriptUpdate () const

event triggered before the system script update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSystemScriptUpdate
void beginsystemscriptupdate_event_handler()
{
	Log::message("\Обработка события BeginSystemScriptUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsystemscriptupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSystemScriptUpdate().connect(beginsystemscriptupdate_event_connections, beginsystemscriptupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSystemScriptUpdate().connect(beginsystemscriptupdate_event_connections, []() {
		Log::message("\Обработка события BeginSystemScriptUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsystemscriptupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsystemscriptupdate_event_connection;

// подписываемся на событие BeginSystemScriptUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSystemScriptUpdate().connect(beginsystemscriptupdate_event_connection, beginsystemscriptupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsystemscriptupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsystemscriptupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSystemScriptUpdate через соединение
beginsystemscriptupdate_event_connection.disconnect();

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

	// Обработчик события BeginSystemScriptUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSystemScriptUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSystemScriptUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginsystemscriptupdate_handler_id;

// подписываемся на событие BeginSystemScriptUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginsystemscriptupdate_handler_id = Engine::getEventBeginSystemScriptUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginSystemScriptUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSystemScriptUpdate().disconnect(beginsystemscriptupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSystemScriptUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSystemScriptUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSystemScriptUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSystemScriptUpdate () const

event triggered after the system script update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSystemScriptUpdate
void endsystemscriptupdate_event_handler()
{
	Log::message("\Обработка события EndSystemScriptUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsystemscriptupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSystemScriptUpdate().connect(endsystemscriptupdate_event_connections, endsystemscriptupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSystemScriptUpdate().connect(endsystemscriptupdate_event_connections, []() {
		Log::message("\Обработка события EndSystemScriptUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsystemscriptupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsystemscriptupdate_event_connection;

// подписываемся на событие EndSystemScriptUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSystemScriptUpdate().connect(endsystemscriptupdate_event_connection, endsystemscriptupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsystemscriptupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsystemscriptupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSystemScriptUpdate через соединение
endsystemscriptupdate_event_connection.disconnect();

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

	// Обработчик события EndSystemScriptUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSystemScriptUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSystemScriptUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endsystemscriptupdate_handler_id;

// подписываемся на событие EndSystemScriptUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endsystemscriptupdate_handler_id = Engine::getEventEndSystemScriptUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndSystemScriptUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSystemScriptUpdate().disconnect(endsystemscriptupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSystemScriptUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSystemScriptUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSystemScriptUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSystemLogicUpdate () const

event triggered before the system logic update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSystemLogicUpdate
void beginsystemlogicupdate_event_handler()
{
	Log::message("\Обработка события BeginSystemLogicUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsystemlogicupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSystemLogicUpdate().connect(beginsystemlogicupdate_event_connections, beginsystemlogicupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSystemLogicUpdate().connect(beginsystemlogicupdate_event_connections, []() {
		Log::message("\Обработка события BeginSystemLogicUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsystemlogicupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsystemlogicupdate_event_connection;

// подписываемся на событие BeginSystemLogicUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSystemLogicUpdate().connect(beginsystemlogicupdate_event_connection, beginsystemlogicupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsystemlogicupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsystemlogicupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSystemLogicUpdate через соединение
beginsystemlogicupdate_event_connection.disconnect();

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

	// Обработчик события BeginSystemLogicUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSystemLogicUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSystemLogicUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginsystemlogicupdate_handler_id;

// подписываемся на событие BeginSystemLogicUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginsystemlogicupdate_handler_id = Engine::getEventBeginSystemLogicUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginSystemLogicUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSystemLogicUpdate().disconnect(beginsystemlogicupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSystemLogicUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSystemLogicUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSystemLogicUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSystemLogicUpdate () const

event triggered after the system logic update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSystemLogicUpdate
void endsystemlogicupdate_event_handler()
{
	Log::message("\Обработка события EndSystemLogicUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsystemlogicupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSystemLogicUpdate().connect(endsystemlogicupdate_event_connections, endsystemlogicupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSystemLogicUpdate().connect(endsystemlogicupdate_event_connections, []() {
		Log::message("\Обработка события EndSystemLogicUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsystemlogicupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsystemlogicupdate_event_connection;

// подписываемся на событие EndSystemLogicUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSystemLogicUpdate().connect(endsystemlogicupdate_event_connection, endsystemlogicupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsystemlogicupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsystemlogicupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSystemLogicUpdate через соединение
endsystemlogicupdate_event_connection.disconnect();

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

	// Обработчик события EndSystemLogicUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSystemLogicUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSystemLogicUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endsystemlogicupdate_handler_id;

// подписываемся на событие EndSystemLogicUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endsystemlogicupdate_handler_id = Engine::getEventEndSystemLogicUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndSystemLogicUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSystemLogicUpdate().disconnect(endsystemlogicupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSystemLogicUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSystemLogicUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSystemLogicUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginWorldUpdate () const

event triggered before the world logic update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWorldUpdate
void beginworldupdate_event_handler()
{
	Log::message("\Обработка события BeginWorldUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginworldupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginWorldUpdate().connect(beginworldupdate_event_connections, beginworldupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginWorldUpdate().connect(beginworldupdate_event_connections, []() {
		Log::message("\Обработка события BeginWorldUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginworldupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginworldupdate_event_connection;

// подписываемся на событие BeginWorldUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginWorldUpdate().connect(beginworldupdate_event_connection, beginworldupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginworldupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginworldupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWorldUpdate через соединение
beginworldupdate_event_connection.disconnect();

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

	// Обработчик события BeginWorldUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWorldUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginWorldUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginworldupdate_handler_id;

// подписываемся на событие BeginWorldUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginworldupdate_handler_id = Engine::getEventBeginWorldUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginWorldUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginWorldUpdate().disconnect(beginworldupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWorldUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginWorldUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginWorldUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndWorldUpdate () const

event triggered after the world logic update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWorldUpdate
void endworldupdate_event_handler()
{
	Log::message("\Обработка события EndWorldUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endworldupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndWorldUpdate().connect(endworldupdate_event_connections, endworldupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndWorldUpdate().connect(endworldupdate_event_connections, []() {
		Log::message("\Обработка события EndWorldUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endworldupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endworldupdate_event_connection;

// подписываемся на событие EndWorldUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndWorldUpdate().connect(endworldupdate_event_connection, endworldupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endworldupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endworldupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWorldUpdate через соединение
endworldupdate_event_connection.disconnect();

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

	// Обработчик события EndWorldUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWorldUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndWorldUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endworldupdate_handler_id;

// подписываемся на событие EndWorldUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endworldupdate_handler_id = Engine::getEventEndWorldUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndWorldUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndWorldUpdate().disconnect(endworldupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWorldUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndWorldUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndWorldUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginAnimationManagerUpdate () const

event triggered before the animation manager update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginAnimationManagerUpdate
void beginanimationmanagerupdate_event_handler()
{
	Log::message("\Обработка события BeginAnimationManagerUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginanimationmanagerupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginAnimationManagerUpdate().connect(beginanimationmanagerupdate_event_connections, beginanimationmanagerupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginAnimationManagerUpdate().connect(beginanimationmanagerupdate_event_connections, []() {
		Log::message("\Обработка события BeginAnimationManagerUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginanimationmanagerupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginanimationmanagerupdate_event_connection;

// подписываемся на событие BeginAnimationManagerUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginAnimationManagerUpdate().connect(beginanimationmanagerupdate_event_connection, beginanimationmanagerupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginanimationmanagerupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginanimationmanagerupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginAnimationManagerUpdate через соединение
beginanimationmanagerupdate_event_connection.disconnect();

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

	// Обработчик события BeginAnimationManagerUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginAnimationManagerUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginAnimationManagerUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginanimationmanagerupdate_handler_id;

// подписываемся на событие BeginAnimationManagerUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginanimationmanagerupdate_handler_id = Engine::getEventBeginAnimationManagerUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginAnimationManagerUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginAnimationManagerUpdate().disconnect(beginanimationmanagerupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginAnimationManagerUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginAnimationManagerUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginAnimationManagerUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndAnimationManagerUpdate () const

event triggered after the animation manager update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndAnimationManagerUpdate
void endanimationmanagerupdate_event_handler()
{
	Log::message("\Обработка события EndAnimationManagerUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endanimationmanagerupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndAnimationManagerUpdate().connect(endanimationmanagerupdate_event_connections, endanimationmanagerupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndAnimationManagerUpdate().connect(endanimationmanagerupdate_event_connections, []() {
		Log::message("\Обработка события EndAnimationManagerUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endanimationmanagerupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endanimationmanagerupdate_event_connection;

// подписываемся на событие EndAnimationManagerUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndAnimationManagerUpdate().connect(endanimationmanagerupdate_event_connection, endanimationmanagerupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endanimationmanagerupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endanimationmanagerupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndAnimationManagerUpdate через соединение
endanimationmanagerupdate_event_connection.disconnect();

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

	// Обработчик события EndAnimationManagerUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndAnimationManagerUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndAnimationManagerUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endanimationmanagerupdate_handler_id;

// подписываемся на событие EndAnimationManagerUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endanimationmanagerupdate_handler_id = Engine::getEventEndAnimationManagerUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndAnimationManagerUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndAnimationManagerUpdate().disconnect(endanimationmanagerupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndAnimationManagerUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndAnimationManagerUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndAnimationManagerUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginWorldPostUpdate () const

event triggered before the world logic postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWorldPostUpdate
void beginworldpostupdate_event_handler()
{
	Log::message("\Обработка события BeginWorldPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginworldpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginWorldPostUpdate().connect(beginworldpostupdate_event_connections, beginworldpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginWorldPostUpdate().connect(beginworldpostupdate_event_connections, []() {
		Log::message("\Обработка события BeginWorldPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginworldpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginworldpostupdate_event_connection;

// подписываемся на событие BeginWorldPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginWorldPostUpdate().connect(beginworldpostupdate_event_connection, beginworldpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginworldpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginworldpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWorldPostUpdate через соединение
beginworldpostupdate_event_connection.disconnect();

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

	// Обработчик события BeginWorldPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWorldPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginWorldPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginworldpostupdate_handler_id;

// подписываемся на событие BeginWorldPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginworldpostupdate_handler_id = Engine::getEventBeginWorldPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginWorldPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginWorldPostUpdate().disconnect(beginworldpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWorldPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginWorldPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginWorldPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndWorldPostUpdate () const

event triggered after the world logic postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWorldPostUpdate
void endworldpostupdate_event_handler()
{
	Log::message("\Обработка события EndWorldPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endworldpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndWorldPostUpdate().connect(endworldpostupdate_event_connections, endworldpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndWorldPostUpdate().connect(endworldpostupdate_event_connections, []() {
		Log::message("\Обработка события EndWorldPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endworldpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endworldpostupdate_event_connection;

// подписываемся на событие EndWorldPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndWorldPostUpdate().connect(endworldpostupdate_event_connection, endworldpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endworldpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endworldpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWorldPostUpdate через соединение
endworldpostupdate_event_connection.disconnect();

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

	// Обработчик события EndWorldPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWorldPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndWorldPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endworldpostupdate_handler_id;

// подписываемся на событие EndWorldPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endworldpostupdate_handler_id = Engine::getEventEndWorldPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndWorldPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndWorldPostUpdate().disconnect(endworldpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWorldPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndWorldPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndWorldPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSystemScriptPostUpdate () const

event triggered before the system script postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSystemScriptPostUpdate
void beginsystemscriptpostupdate_event_handler()
{
	Log::message("\Обработка события BeginSystemScriptPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsystemscriptpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSystemScriptPostUpdate().connect(beginsystemscriptpostupdate_event_connections, beginsystemscriptpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSystemScriptPostUpdate().connect(beginsystemscriptpostupdate_event_connections, []() {
		Log::message("\Обработка события BeginSystemScriptPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsystemscriptpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsystemscriptpostupdate_event_connection;

// подписываемся на событие BeginSystemScriptPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSystemScriptPostUpdate().connect(beginsystemscriptpostupdate_event_connection, beginsystemscriptpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsystemscriptpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsystemscriptpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSystemScriptPostUpdate через соединение
beginsystemscriptpostupdate_event_connection.disconnect();

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

	// Обработчик события BeginSystemScriptPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSystemScriptPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSystemScriptPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginsystemscriptpostupdate_handler_id;

// подписываемся на событие BeginSystemScriptPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginsystemscriptpostupdate_handler_id = Engine::getEventBeginSystemScriptPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginSystemScriptPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSystemScriptPostUpdate().disconnect(beginsystemscriptpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSystemScriptPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSystemScriptPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSystemScriptPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSystemScriptPostUpdate () const

event triggered after the system script postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSystemScriptPostUpdate
void endsystemscriptpostupdate_event_handler()
{
	Log::message("\Обработка события EndSystemScriptPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsystemscriptpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSystemScriptPostUpdate().connect(endsystemscriptpostupdate_event_connections, endsystemscriptpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSystemScriptPostUpdate().connect(endsystemscriptpostupdate_event_connections, []() {
		Log::message("\Обработка события EndSystemScriptPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsystemscriptpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsystemscriptpostupdate_event_connection;

// подписываемся на событие EndSystemScriptPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSystemScriptPostUpdate().connect(endsystemscriptpostupdate_event_connection, endsystemscriptpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsystemscriptpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsystemscriptpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSystemScriptPostUpdate через соединение
endsystemscriptpostupdate_event_connection.disconnect();

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

	// Обработчик события EndSystemScriptPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSystemScriptPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSystemScriptPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endsystemscriptpostupdate_handler_id;

// подписываемся на событие EndSystemScriptPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endsystemscriptpostupdate_handler_id = Engine::getEventEndSystemScriptPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndSystemScriptPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSystemScriptPostUpdate().disconnect(endsystemscriptpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSystemScriptPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSystemScriptPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSystemScriptPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSystemLogicPostUpdate () const

event triggered before the system logic postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSystemLogicPostUpdate
void beginsystemlogicpostupdate_event_handler()
{
	Log::message("\Обработка события BeginSystemLogicPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginsystemlogicpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSystemLogicPostUpdate().connect(beginsystemlogicpostupdate_event_connections, beginsystemlogicpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSystemLogicPostUpdate().connect(beginsystemlogicpostupdate_event_connections, []() {
		Log::message("\Обработка события BeginSystemLogicPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginsystemlogicpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginsystemlogicpostupdate_event_connection;

// подписываемся на событие BeginSystemLogicPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSystemLogicPostUpdate().connect(beginsystemlogicpostupdate_event_connection, beginsystemlogicpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginsystemlogicpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginsystemlogicpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSystemLogicPostUpdate через соединение
beginsystemlogicpostupdate_event_connection.disconnect();

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

	// Обработчик события BeginSystemLogicPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSystemLogicPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSystemLogicPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginsystemlogicpostupdate_handler_id;

// подписываемся на событие BeginSystemLogicPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginsystemlogicpostupdate_handler_id = Engine::getEventBeginSystemLogicPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginSystemLogicPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSystemLogicPostUpdate().disconnect(beginsystemlogicpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSystemLogicPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSystemLogicPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSystemLogicPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSystemLogicPostUpdate () const

event triggered after the system logic postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSystemLogicPostUpdate
void endsystemlogicpostupdate_event_handler()
{
	Log::message("\Обработка события EndSystemLogicPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endsystemlogicpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSystemLogicPostUpdate().connect(endsystemlogicpostupdate_event_connections, endsystemlogicpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSystemLogicPostUpdate().connect(endsystemlogicpostupdate_event_connections, []() {
		Log::message("\Обработка события EndSystemLogicPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endsystemlogicpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endsystemlogicpostupdate_event_connection;

// подписываемся на событие EndSystemLogicPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSystemLogicPostUpdate().connect(endsystemlogicpostupdate_event_connection, endsystemlogicpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endsystemlogicpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endsystemlogicpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSystemLogicPostUpdate через соединение
endsystemlogicpostupdate_event_connection.disconnect();

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

	// Обработчик события EndSystemLogicPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSystemLogicPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSystemLogicPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endsystemlogicpostupdate_handler_id;

// подписываемся на событие EndSystemLogicPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endsystemlogicpostupdate_handler_id = Engine::getEventEndSystemLogicPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndSystemLogicPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSystemLogicPostUpdate().disconnect(endsystemlogicpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSystemLogicPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSystemLogicPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSystemLogicPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginEditorPostUpdate () const

event triggered before the editor logic postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginEditorPostUpdate
void begineditorpostupdate_event_handler()
{
	Log::message("\Обработка события BeginEditorPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begineditorpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginEditorPostUpdate().connect(begineditorpostupdate_event_connections, begineditorpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginEditorPostUpdate().connect(begineditorpostupdate_event_connections, []() {
		Log::message("\Обработка события BeginEditorPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begineditorpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begineditorpostupdate_event_connection;

// подписываемся на событие BeginEditorPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginEditorPostUpdate().connect(begineditorpostupdate_event_connection, begineditorpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begineditorpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begineditorpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginEditorPostUpdate через соединение
begineditorpostupdate_event_connection.disconnect();

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

	// Обработчик события BeginEditorPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginEditorPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginEditorPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begineditorpostupdate_handler_id;

// подписываемся на событие BeginEditorPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
begineditorpostupdate_handler_id = Engine::getEventBeginEditorPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginEditorPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginEditorPostUpdate().disconnect(begineditorpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginEditorPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginEditorPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginEditorPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndEditorPostUpdate () const

event triggered after the editor logic postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndEditorPostUpdate
void endeditorpostupdate_event_handler()
{
	Log::message("\Обработка события EndEditorPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endeditorpostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndEditorPostUpdate().connect(endeditorpostupdate_event_connections, endeditorpostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndEditorPostUpdate().connect(endeditorpostupdate_event_connections, []() {
		Log::message("\Обработка события EndEditorPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endeditorpostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endeditorpostupdate_event_connection;

// подписываемся на событие EndEditorPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndEditorPostUpdate().connect(endeditorpostupdate_event_connection, endeditorpostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endeditorpostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endeditorpostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndEditorPostUpdate через соединение
endeditorpostupdate_event_connection.disconnect();

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

	// Обработчик события EndEditorPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndEditorPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndEditorPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endeditorpostupdate_handler_id;

// подписываемся на событие EndEditorPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endeditorpostupdate_handler_id = Engine::getEventEndEditorPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndEditorPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndEditorPostUpdate().disconnect(endeditorpostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndEditorPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndEditorPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndEditorPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPluginsPostUpdate () const

event triggered before the plugins postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPluginsPostUpdate
void beginpluginspostupdate_event_handler()
{
	Log::message("\Обработка события BeginPluginsPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpluginspostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPluginsPostUpdate().connect(beginpluginspostupdate_event_connections, beginpluginspostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPluginsPostUpdate().connect(beginpluginspostupdate_event_connections, []() {
		Log::message("\Обработка события BeginPluginsPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpluginspostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpluginspostupdate_event_connection;

// подписываемся на событие BeginPluginsPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPluginsPostUpdate().connect(beginpluginspostupdate_event_connection, beginpluginspostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpluginspostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpluginspostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPluginsPostUpdate через соединение
beginpluginspostupdate_event_connection.disconnect();

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

	// Обработчик события BeginPluginsPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPluginsPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPluginsPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpluginspostupdate_handler_id;

// подписываемся на событие BeginPluginsPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginpluginspostupdate_handler_id = Engine::getEventBeginPluginsPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginPluginsPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPluginsPostUpdate().disconnect(beginpluginspostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPluginsPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPluginsPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPluginsPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPluginsPostUpdate () const

event triggered after the plugins postupdate stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPluginsPostUpdate
void endpluginspostupdate_event_handler()
{
	Log::message("\Обработка события EndPluginsPostUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpluginspostupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPluginsPostUpdate().connect(endpluginspostupdate_event_connections, endpluginspostupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPluginsPostUpdate().connect(endpluginspostupdate_event_connections, []() {
		Log::message("\Обработка события EndPluginsPostUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpluginspostupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpluginspostupdate_event_connection;

// подписываемся на событие EndPluginsPostUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPluginsPostUpdate().connect(endpluginspostupdate_event_connection, endpluginspostupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpluginspostupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpluginspostupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPluginsPostUpdate через соединение
endpluginspostupdate_event_connection.disconnect();

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

	// Обработчик события EndPluginsPostUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPluginsPostUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPluginsPostUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpluginspostupdate_handler_id;

// подписываемся на событие EndPluginsPostUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endpluginspostupdate_handler_id = Engine::getEventEndPluginsPostUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndPluginsPostUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPluginsPostUpdate().disconnect(endpluginspostupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPluginsPostUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPluginsPostUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPluginsPostUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSpatialUpdate () const

event triggered before the spatial tree update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSpatialUpdate
void beginspatialupdate_event_handler()
{
	Log::message("\Обработка события BeginSpatialUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginspatialupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSpatialUpdate().connect(beginspatialupdate_event_connections, beginspatialupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSpatialUpdate().connect(beginspatialupdate_event_connections, []() {
		Log::message("\Обработка события BeginSpatialUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginspatialupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginspatialupdate_event_connection;

// подписываемся на событие BeginSpatialUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSpatialUpdate().connect(beginspatialupdate_event_connection, beginspatialupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginspatialupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginspatialupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSpatialUpdate через соединение
beginspatialupdate_event_connection.disconnect();

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

	// Обработчик события BeginSpatialUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSpatialUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSpatialUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginspatialupdate_handler_id;

// подписываемся на событие BeginSpatialUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginspatialupdate_handler_id = Engine::getEventBeginSpatialUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginSpatialUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSpatialUpdate().disconnect(beginspatialupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSpatialUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSpatialUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSpatialUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSpatialUpdate () const

event triggered after the spatial tree update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSpatialUpdate
void endspatialupdate_event_handler()
{
	Log::message("\Обработка события EndSpatialUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endspatialupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSpatialUpdate().connect(endspatialupdate_event_connections, endspatialupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSpatialUpdate().connect(endspatialupdate_event_connections, []() {
		Log::message("\Обработка события EndSpatialUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endspatialupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endspatialupdate_event_connection;

// подписываемся на событие EndSpatialUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSpatialUpdate().connect(endspatialupdate_event_connection, endspatialupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endspatialupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endspatialupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSpatialUpdate через соединение
endspatialupdate_event_connection.disconnect();

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

	// Обработчик события EndSpatialUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSpatialUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSpatialUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endspatialupdate_handler_id;

// подписываемся на событие EndSpatialUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endspatialupdate_handler_id = Engine::getEventEndSpatialUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndSpatialUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSpatialUpdate().disconnect(endspatialupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSpatialUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSpatialUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSpatialUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginFilesystemUpdate () const

event triggered before the filesystem update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginFilesystemUpdate
void beginfilesystemupdate_event_handler()
{
	Log::message("\Обработка события BeginFilesystemUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginfilesystemupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginFilesystemUpdate().connect(beginfilesystemupdate_event_connections, beginfilesystemupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginFilesystemUpdate().connect(beginfilesystemupdate_event_connections, []() {
		Log::message("\Обработка события BeginFilesystemUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginfilesystemupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginfilesystemupdate_event_connection;

// подписываемся на событие BeginFilesystemUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginFilesystemUpdate().connect(beginfilesystemupdate_event_connection, beginfilesystemupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginfilesystemupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginfilesystemupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginFilesystemUpdate через соединение
beginfilesystemupdate_event_connection.disconnect();

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

	// Обработчик события BeginFilesystemUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginFilesystemUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginFilesystemUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginfilesystemupdate_handler_id;

// подписываемся на событие BeginFilesystemUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
beginfilesystemupdate_handler_id = Engine::getEventBeginFilesystemUpdate().connect(e_connections, []() {
		Log::message("\Обработка события BeginFilesystemUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginFilesystemUpdate().disconnect(beginfilesystemupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginFilesystemUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginFilesystemUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginFilesystemUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndFilesystemUpdate () const

event triggered after the filesystem update stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndFilesystemUpdate
void endfilesystemupdate_event_handler()
{
	Log::message("\Обработка события EndFilesystemUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endfilesystemupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndFilesystemUpdate().connect(endfilesystemupdate_event_connections, endfilesystemupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndFilesystemUpdate().connect(endfilesystemupdate_event_connections, []() {
		Log::message("\Обработка события EndFilesystemUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endfilesystemupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endfilesystemupdate_event_connection;

// подписываемся на событие EndFilesystemUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndFilesystemUpdate().connect(endfilesystemupdate_event_connection, endfilesystemupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endfilesystemupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endfilesystemupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndFilesystemUpdate через соединение
endfilesystemupdate_event_connection.disconnect();

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

	// Обработчик события EndFilesystemUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndFilesystemUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndFilesystemUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endfilesystemupdate_handler_id;

// подписываемся на событие EndFilesystemUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endfilesystemupdate_handler_id = Engine::getEventEndFilesystemUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndFilesystemUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndFilesystemUpdate().disconnect(endfilesystemupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndFilesystemUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndFilesystemUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndFilesystemUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPathfinding () const

event triggered before the pathfinding module is updated. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPathfinding
void beginpathfinding_event_handler()
{
	Log::message("\Обработка события BeginPathfinding\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpathfinding_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPathfinding().connect(beginpathfinding_event_connections, beginpathfinding_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPathfinding().connect(beginpathfinding_event_connections, []() {
		Log::message("\Обработка события BeginPathfinding (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpathfinding_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpathfinding_event_connection;

// подписываемся на событие BeginPathfinding с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPathfinding().connect(beginpathfinding_event_connection, beginpathfinding_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpathfinding_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpathfinding_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPathfinding через соединение
beginpathfinding_event_connection.disconnect();

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

	// Обработчик события BeginPathfinding, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPathfinding\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPathfinding().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpathfinding_handler_id;

// подписываемся на событие BeginPathfinding с лямбда-обработчиком, сохраняя идентификатор соединения
beginpathfinding_handler_id = Engine::getEventBeginPathfinding().connect(e_connections, []() {
		Log::message("\Обработка события BeginPathfinding (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPathfinding().disconnect(beginpathfinding_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPathfinding при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPathfinding().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPathfinding().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndUpdate () const

event triggered after the update stage is finished. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndUpdate
void endupdate_event_handler()
{
	Log::message("\Обработка события EndUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndUpdate().connect(endupdate_event_connections, endupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndUpdate().connect(endupdate_event_connections, []() {
		Log::message("\Обработка события EndUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endupdate_event_connection;

// подписываемся на событие EndUpdate с функцией-обработчиком, сохраняя соединение
Engine::getEventEndUpdate().connect(endupdate_event_connection, endupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndUpdate через соединение
endupdate_event_connection.disconnect();

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

	// Обработчик события EndUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endupdate_handler_id;

// подписываемся на событие EndUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
endupdate_handler_id = Engine::getEventEndUpdate().connect(e_connections, []() {
		Log::message("\Обработка события EndUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndUpdate().disconnect(endupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventSyncBeginFramePhysics () const

event triggered before the physics frame in the main thread. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события SyncBeginFramePhysics
void syncbeginframephysics_event_handler()
{
	Log::message("\Обработка события SyncBeginFramePhysics\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections syncbeginframephysics_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventSyncBeginFramePhysics().connect(syncbeginframephysics_event_connections, syncbeginframephysics_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventSyncBeginFramePhysics().connect(syncbeginframephysics_event_connections, []() {
		Log::message("\Обработка события SyncBeginFramePhysics (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
syncbeginframephysics_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection syncbeginframephysics_event_connection;

// подписываемся на событие SyncBeginFramePhysics с функцией-обработчиком, сохраняя соединение
Engine::getEventSyncBeginFramePhysics().connect(syncbeginframephysics_event_connection, syncbeginframephysics_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
syncbeginframephysics_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
syncbeginframephysics_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие SyncBeginFramePhysics через соединение
syncbeginframephysics_event_connection.disconnect();

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

	// Обработчик события SyncBeginFramePhysics, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события SyncBeginFramePhysics\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventSyncBeginFramePhysics().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId syncbeginframephysics_handler_id;

// подписываемся на событие SyncBeginFramePhysics с лямбда-обработчиком, сохраняя идентификатор соединения
syncbeginframephysics_handler_id = Engine::getEventSyncBeginFramePhysics().connect(e_connections, []() {
		Log::message("\Обработка события SyncBeginFramePhysics (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventSyncBeginFramePhysics().disconnect(syncbeginframephysics_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий SyncBeginFramePhysics при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventSyncBeginFramePhysics().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventSyncBeginFramePhysics().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventSyncEndFramePhysics () const

event triggered after the physics frame in the main thread. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события SyncEndFramePhysics
void syncendframephysics_event_handler()
{
	Log::message("\Обработка события SyncEndFramePhysics\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections syncendframephysics_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventSyncEndFramePhysics().connect(syncendframephysics_event_connections, syncendframephysics_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventSyncEndFramePhysics().connect(syncendframephysics_event_connections, []() {
		Log::message("\Обработка события SyncEndFramePhysics (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
syncendframephysics_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection syncendframephysics_event_connection;

// подписываемся на событие SyncEndFramePhysics с функцией-обработчиком, сохраняя соединение
Engine::getEventSyncEndFramePhysics().connect(syncendframephysics_event_connection, syncendframephysics_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
syncendframephysics_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
syncendframephysics_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие SyncEndFramePhysics через соединение
syncendframephysics_event_connection.disconnect();

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

	// Обработчик события SyncEndFramePhysics, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события SyncEndFramePhysics\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventSyncEndFramePhysics().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId syncendframephysics_handler_id;

// подписываемся на событие SyncEndFramePhysics с лямбда-обработчиком, сохраняя идентификатор соединения
syncendframephysics_handler_id = Engine::getEventSyncEndFramePhysics().connect(e_connections, []() {
		Log::message("\Обработка события SyncEndFramePhysics (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventSyncEndFramePhysics().disconnect(syncendframephysics_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий SyncEndFramePhysics при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventSyncEndFramePhysics().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventSyncEndFramePhysics().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventAsyncBeginFramePhysics () const

event triggered before the physics frame in the physics thread. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события AsyncBeginFramePhysics
void asyncbeginframephysics_event_handler()
{
	Log::message("\Обработка события AsyncBeginFramePhysics\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections asyncbeginframephysics_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventAsyncBeginFramePhysics().connect(asyncbeginframephysics_event_connections, asyncbeginframephysics_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventAsyncBeginFramePhysics().connect(asyncbeginframephysics_event_connections, []() {
		Log::message("\Обработка события AsyncBeginFramePhysics (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
asyncbeginframephysics_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection asyncbeginframephysics_event_connection;

// подписываемся на событие AsyncBeginFramePhysics с функцией-обработчиком, сохраняя соединение
Engine::getEventAsyncBeginFramePhysics().connect(asyncbeginframephysics_event_connection, asyncbeginframephysics_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
asyncbeginframephysics_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
asyncbeginframephysics_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие AsyncBeginFramePhysics через соединение
asyncbeginframephysics_event_connection.disconnect();

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

	// Обработчик события AsyncBeginFramePhysics, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события AsyncBeginFramePhysics\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventAsyncBeginFramePhysics().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId asyncbeginframephysics_handler_id;

// подписываемся на событие AsyncBeginFramePhysics с лямбда-обработчиком, сохраняя идентификатор соединения
asyncbeginframephysics_handler_id = Engine::getEventAsyncBeginFramePhysics().connect(e_connections, []() {
		Log::message("\Обработка события AsyncBeginFramePhysics (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventAsyncBeginFramePhysics().disconnect(asyncbeginframephysics_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий AsyncBeginFramePhysics при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventAsyncBeginFramePhysics().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventAsyncBeginFramePhysics().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventAsyncEndFramePhysics () const

event triggered after the physics frame in the physics thread. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события AsyncEndFramePhysics
void asyncendframephysics_event_handler()
{
	Log::message("\Обработка события AsyncEndFramePhysics\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections asyncendframephysics_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventAsyncEndFramePhysics().connect(asyncendframephysics_event_connections, asyncendframephysics_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventAsyncEndFramePhysics().connect(asyncendframephysics_event_connections, []() {
		Log::message("\Обработка события AsyncEndFramePhysics (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
asyncendframephysics_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection asyncendframephysics_event_connection;

// подписываемся на событие AsyncEndFramePhysics с функцией-обработчиком, сохраняя соединение
Engine::getEventAsyncEndFramePhysics().connect(asyncendframephysics_event_connection, asyncendframephysics_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
asyncendframephysics_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
asyncendframephysics_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие AsyncEndFramePhysics через соединение
asyncendframephysics_event_connection.disconnect();

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

	// Обработчик события AsyncEndFramePhysics, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события AsyncEndFramePhysics\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventAsyncEndFramePhysics().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId asyncendframephysics_handler_id;

// подписываемся на событие AsyncEndFramePhysics с лямбда-обработчиком, сохраняя идентификатор соединения
asyncendframephysics_handler_id = Engine::getEventAsyncEndFramePhysics().connect(e_connections, []() {
		Log::message("\Обработка события AsyncEndFramePhysics (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventAsyncEndFramePhysics().disconnect(asyncendframephysics_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий AsyncEndFramePhysics при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventAsyncEndFramePhysics().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventAsyncEndFramePhysics().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginVRRender () const

event triggered before the VR rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginVRRender
void beginvrrender_event_handler()
{
	Log::message("\Обработка события BeginVRRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginvrrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginVRRender().connect(beginvrrender_event_connections, beginvrrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginVRRender().connect(beginvrrender_event_connections, []() {
		Log::message("\Обработка события BeginVRRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginvrrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginvrrender_event_connection;

// подписываемся на событие BeginVRRender с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginVRRender().connect(beginvrrender_event_connection, beginvrrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginvrrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginvrrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginVRRender через соединение
beginvrrender_event_connection.disconnect();

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

	// Обработчик события BeginVRRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginVRRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginVRRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginvrrender_handler_id;

// подписываемся на событие BeginVRRender с лямбда-обработчиком, сохраняя идентификатор соединения
beginvrrender_handler_id = Engine::getEventBeginVRRender().connect(e_connections, []() {
		Log::message("\Обработка события BeginVRRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginVRRender().disconnect(beginvrrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginVRRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginVRRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginVRRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndVRRender () const

event triggered after the VR rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndVRRender
void endvrrender_event_handler()
{
	Log::message("\Обработка события EndVRRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endvrrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndVRRender().connect(endvrrender_event_connections, endvrrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndVRRender().connect(endvrrender_event_connections, []() {
		Log::message("\Обработка события EndVRRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endvrrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endvrrender_event_connection;

// подписываемся на событие EndVRRender с функцией-обработчиком, сохраняя соединение
Engine::getEventEndVRRender().connect(endvrrender_event_connection, endvrrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endvrrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endvrrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndVRRender через соединение
endvrrender_event_connection.disconnect();

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

	// Обработчик события EndVRRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndVRRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndVRRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endvrrender_handler_id;

// подписываемся на событие EndVRRender с лямбда-обработчиком, сохраняя идентификатор соединения
endvrrender_handler_id = Engine::getEventEndVRRender().connect(e_connections, []() {
		Log::message("\Обработка события EndVRRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndVRRender().disconnect(endvrrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndVRRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndVRRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndVRRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginRender () const

event triggered before the rendering stage is started. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginRender
void beginrender_event_handler()
{
	Log::message("\Обработка события BeginRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginRender().connect(beginrender_event_connections, beginrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginRender().connect(beginrender_event_connections, []() {
		Log::message("\Обработка события BeginRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginrender_event_connection;

// подписываемся на событие BeginRender с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginRender().connect(beginrender_event_connection, beginrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginRender через соединение
beginrender_event_connection.disconnect();

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

	// Обработчик события BeginRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginrender_handler_id;

// подписываемся на событие BeginRender с лямбда-обработчиком, сохраняя идентификатор соединения
beginrender_handler_id = Engine::getEventBeginRender().connect(e_connections, []() {
		Log::message("\Обработка события BeginRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginRender().disconnect(beginrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginEditorRender () const

event triggered before the editor rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginEditorRender
void begineditorrender_event_handler()
{
	Log::message("\Обработка события BeginEditorRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begineditorrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginEditorRender().connect(begineditorrender_event_connections, begineditorrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginEditorRender().connect(begineditorrender_event_connections, []() {
		Log::message("\Обработка события BeginEditorRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begineditorrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begineditorrender_event_connection;

// подписываемся на событие BeginEditorRender с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginEditorRender().connect(begineditorrender_event_connection, begineditorrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begineditorrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begineditorrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginEditorRender через соединение
begineditorrender_event_connection.disconnect();

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

	// Обработчик события BeginEditorRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginEditorRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginEditorRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begineditorrender_handler_id;

// подписываемся на событие BeginEditorRender с лямбда-обработчиком, сохраняя идентификатор соединения
begineditorrender_handler_id = Engine::getEventBeginEditorRender().connect(e_connections, []() {
		Log::message("\Обработка события BeginEditorRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginEditorRender().disconnect(begineditorrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginEditorRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginEditorRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginEditorRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndEditorRender () const

event triggered after the editor rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndEditorRender
void endeditorrender_event_handler()
{
	Log::message("\Обработка события EndEditorRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endeditorrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndEditorRender().connect(endeditorrender_event_connections, endeditorrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndEditorRender().connect(endeditorrender_event_connections, []() {
		Log::message("\Обработка события EndEditorRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endeditorrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endeditorrender_event_connection;

// подписываемся на событие EndEditorRender с функцией-обработчиком, сохраняя соединение
Engine::getEventEndEditorRender().connect(endeditorrender_event_connection, endeditorrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endeditorrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endeditorrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndEditorRender через соединение
endeditorrender_event_connection.disconnect();

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

	// Обработчик события EndEditorRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndEditorRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndEditorRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endeditorrender_handler_id;

// подписываемся на событие EndEditorRender с лямбда-обработчиком, сохраняя идентификатор соединения
endeditorrender_handler_id = Engine::getEventEndEditorRender().connect(e_connections, []() {
		Log::message("\Обработка события EndEditorRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndEditorRender().disconnect(endeditorrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndEditorRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndEditorRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndEditorRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPluginsRender () const

event triggered before the plugins rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPluginsRender
void beginpluginsrender_event_handler()
{
	Log::message("\Обработка события BeginPluginsRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpluginsrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPluginsRender().connect(beginpluginsrender_event_connections, beginpluginsrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPluginsRender().connect(beginpluginsrender_event_connections, []() {
		Log::message("\Обработка события BeginPluginsRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpluginsrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpluginsrender_event_connection;

// подписываемся на событие BeginPluginsRender с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPluginsRender().connect(beginpluginsrender_event_connection, beginpluginsrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpluginsrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpluginsrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPluginsRender через соединение
beginpluginsrender_event_connection.disconnect();

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

	// Обработчик события BeginPluginsRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPluginsRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPluginsRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpluginsrender_handler_id;

// подписываемся на событие BeginPluginsRender с лямбда-обработчиком, сохраняя идентификатор соединения
beginpluginsrender_handler_id = Engine::getEventBeginPluginsRender().connect(e_connections, []() {
		Log::message("\Обработка события BeginPluginsRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPluginsRender().disconnect(beginpluginsrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPluginsRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPluginsRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPluginsRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPluginsRender () const

event triggered after the plugins rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPluginsRender
void endpluginsrender_event_handler()
{
	Log::message("\Обработка события EndPluginsRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpluginsrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPluginsRender().connect(endpluginsrender_event_connections, endpluginsrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPluginsRender().connect(endpluginsrender_event_connections, []() {
		Log::message("\Обработка события EndPluginsRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpluginsrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpluginsrender_event_connection;

// подписываемся на событие EndPluginsRender с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPluginsRender().connect(endpluginsrender_event_connection, endpluginsrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpluginsrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpluginsrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPluginsRender через соединение
endpluginsrender_event_connection.disconnect();

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

	// Обработчик события EndPluginsRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPluginsRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPluginsRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpluginsrender_handler_id;

// подписываемся на событие EndPluginsRender с лямбда-обработчиком, сохраняя идентификатор соединения
endpluginsrender_handler_id = Engine::getEventEndPluginsRender().connect(e_connections, []() {
		Log::message("\Обработка события EndPluginsRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPluginsRender().disconnect(endpluginsrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPluginsRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPluginsRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPluginsRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginRenderWorld () const

event triggered before the world rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginRenderWorld
void beginrenderworld_event_handler()
{
	Log::message("\Обработка события BeginRenderWorld\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginrenderworld_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginRenderWorld().connect(beginrenderworld_event_connections, beginrenderworld_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginRenderWorld().connect(beginrenderworld_event_connections, []() {
		Log::message("\Обработка события BeginRenderWorld (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginrenderworld_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginrenderworld_event_connection;

// подписываемся на событие BeginRenderWorld с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginRenderWorld().connect(beginrenderworld_event_connection, beginrenderworld_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginrenderworld_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginrenderworld_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginRenderWorld через соединение
beginrenderworld_event_connection.disconnect();

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

	// Обработчик события BeginRenderWorld, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginRenderWorld\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginRenderWorld().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginrenderworld_handler_id;

// подписываемся на событие BeginRenderWorld с лямбда-обработчиком, сохраняя идентификатор соединения
beginrenderworld_handler_id = Engine::getEventBeginRenderWorld().connect(e_connections, []() {
		Log::message("\Обработка события BeginRenderWorld (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginRenderWorld().disconnect(beginrenderworld_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginRenderWorld при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginRenderWorld().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginRenderWorld().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndRenderWorld () const

event triggered after the world rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndRenderWorld
void endrenderworld_event_handler()
{
	Log::message("\Обработка события EndRenderWorld\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endrenderworld_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndRenderWorld().connect(endrenderworld_event_connections, endrenderworld_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndRenderWorld().connect(endrenderworld_event_connections, []() {
		Log::message("\Обработка события EndRenderWorld (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endrenderworld_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endrenderworld_event_connection;

// подписываемся на событие EndRenderWorld с функцией-обработчиком, сохраняя соединение
Engine::getEventEndRenderWorld().connect(endrenderworld_event_connection, endrenderworld_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endrenderworld_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endrenderworld_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndRenderWorld через соединение
endrenderworld_event_connection.disconnect();

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

	// Обработчик события EndRenderWorld, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndRenderWorld\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndRenderWorld().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endrenderworld_handler_id;

// подписываемся на событие EndRenderWorld с лямбда-обработчиком, сохраняя идентификатор соединения
endrenderworld_handler_id = Engine::getEventEndRenderWorld().connect(e_connections, []() {
		Log::message("\Обработка события EndRenderWorld (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndRenderWorld().disconnect(endrenderworld_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndRenderWorld при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndRenderWorld().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndRenderWorld().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPluginsGui () const

event triggered before the gui() function of plugins is called. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPluginsGui
void beginpluginsgui_event_handler()
{
	Log::message("\Обработка события BeginPluginsGui\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpluginsgui_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPluginsGui().connect(beginpluginsgui_event_connections, beginpluginsgui_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPluginsGui().connect(beginpluginsgui_event_connections, []() {
		Log::message("\Обработка события BeginPluginsGui (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpluginsgui_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpluginsgui_event_connection;

// подписываемся на событие BeginPluginsGui с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPluginsGui().connect(beginpluginsgui_event_connection, beginpluginsgui_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpluginsgui_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpluginsgui_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPluginsGui через соединение
beginpluginsgui_event_connection.disconnect();

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

	// Обработчик события BeginPluginsGui, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPluginsGui\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPluginsGui().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpluginsgui_handler_id;

// подписываемся на событие BeginPluginsGui с лямбда-обработчиком, сохраняя идентификатор соединения
beginpluginsgui_handler_id = Engine::getEventBeginPluginsGui().connect(e_connections, []() {
		Log::message("\Обработка события BeginPluginsGui (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPluginsGui().disconnect(beginpluginsgui_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPluginsGui при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPluginsGui().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPluginsGui().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPluginsGui () const

event triggered after the gui() function of plugins is called. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPluginsGui
void endpluginsgui_event_handler()
{
	Log::message("\Обработка события EndPluginsGui\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpluginsgui_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPluginsGui().connect(endpluginsgui_event_connections, endpluginsgui_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPluginsGui().connect(endpluginsgui_event_connections, []() {
		Log::message("\Обработка события EndPluginsGui (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpluginsgui_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpluginsgui_event_connection;

// подписываемся на событие EndPluginsGui с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPluginsGui().connect(endpluginsgui_event_connection, endpluginsgui_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpluginsgui_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpluginsgui_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPluginsGui через соединение
endpluginsgui_event_connection.disconnect();

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

	// Обработчик события EndPluginsGui, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPluginsGui\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPluginsGui().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpluginsgui_handler_id;

// подписываемся на событие EndPluginsGui с лямбда-обработчиком, сохраняя идентификатор соединения
endpluginsgui_handler_id = Engine::getEventEndPluginsGui().connect(e_connections, []() {
		Log::message("\Обработка события EndPluginsGui (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPluginsGui().disconnect(endpluginsgui_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPluginsGui при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPluginsGui().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPluginsGui().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPostRender () const

event triggered before the post-rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPostRender
void beginpostrender_event_handler()
{
	Log::message("\Обработка события BeginPostRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpostrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPostRender().connect(beginpostrender_event_connections, beginpostrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPostRender().connect(beginpostrender_event_connections, []() {
		Log::message("\Обработка события BeginPostRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpostrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpostrender_event_connection;

// подписываемся на событие BeginPostRender с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPostRender().connect(beginpostrender_event_connection, beginpostrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpostrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpostrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPostRender через соединение
beginpostrender_event_connection.disconnect();

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

	// Обработчик события BeginPostRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPostRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPostRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpostrender_handler_id;

// подписываемся на событие BeginPostRender с лямбда-обработчиком, сохраняя идентификатор соединения
beginpostrender_handler_id = Engine::getEventBeginPostRender().connect(e_connections, []() {
		Log::message("\Обработка события BeginPostRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPostRender().disconnect(beginpostrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPostRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPostRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPostRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPostRender () const

event triggered after the post-rendering stage. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPostRender
void endpostrender_event_handler()
{
	Log::message("\Обработка события EndPostRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpostrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPostRender().connect(endpostrender_event_connections, endpostrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPostRender().connect(endpostrender_event_connections, []() {
		Log::message("\Обработка события EndPostRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpostrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpostrender_event_connection;

// подписываемся на событие EndPostRender с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPostRender().connect(endpostrender_event_connection, endpostrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpostrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpostrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPostRender через соединение
endpostrender_event_connection.disconnect();

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

	// Обработчик события EndPostRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPostRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPostRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpostrender_handler_id;

// подписываемся на событие EndPostRender с лямбда-обработчиком, сохраняя идентификатор соединения
endpostrender_handler_id = Engine::getEventEndPostRender().connect(e_connections, []() {
		Log::message("\Обработка события EndPostRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPostRender().disconnect(endpostrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPostRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPostRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPostRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndRender () const

event triggered after the rendering stage is finished. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndRender
void endrender_event_handler()
{
	Log::message("\Обработка события EndRender\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endrender_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndRender().connect(endrender_event_connections, endrender_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndRender().connect(endrender_event_connections, []() {
		Log::message("\Обработка события EndRender (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endrender_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endrender_event_connection;

// подписываемся на событие EndRender с функцией-обработчиком, сохраняя соединение
Engine::getEventEndRender().connect(endrender_event_connection, endrender_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endrender_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endrender_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndRender через соединение
endrender_event_connection.disconnect();

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

	// Обработчик события EndRender, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndRender\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndRender().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endrender_handler_id;

// подписываемся на событие EndRender с лямбда-обработчиком, сохраняя идентификатор соединения
endrender_handler_id = Engine::getEventEndRender().connect(e_connections, []() {
		Log::message("\Обработка события EndRender (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndRender().disconnect(endrender_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndRender при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndRender().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndRender().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginSwap () const

event triggered before the swap stage is started. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginSwap
void beginswap_event_handler()
{
	Log::message("\Обработка события BeginSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginswap_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginSwap().connect(beginswap_event_connections, beginswap_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginSwap().connect(beginswap_event_connections, []() {
		Log::message("\Обработка события BeginSwap (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginswap_event_connection;

// подписываемся на событие BeginSwap с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginSwap().connect(beginswap_event_connection, beginswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginswap_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginSwap через соединение
beginswap_event_connection.disconnect();

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

	// Обработчик события BeginSwap, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginswap_handler_id;

// подписываемся на событие BeginSwap с лямбда-обработчиком, сохраняя идентификатор соединения
beginswap_handler_id = Engine::getEventBeginSwap().connect(e_connections, []() {
		Log::message("\Обработка события BeginSwap (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginSwap().disconnect(beginswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPathfinding () const

event triggered after the pathfinding is updated. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPathfinding
void endpathfinding_event_handler()
{
	Log::message("\Обработка события EndPathfinding\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpathfinding_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPathfinding().connect(endpathfinding_event_connections, endpathfinding_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPathfinding().connect(endpathfinding_event_connections, []() {
		Log::message("\Обработка события EndPathfinding (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpathfinding_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpathfinding_event_connection;

// подписываемся на событие EndPathfinding с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPathfinding().connect(endpathfinding_event_connection, endpathfinding_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpathfinding_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpathfinding_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPathfinding через соединение
endpathfinding_event_connection.disconnect();

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

	// Обработчик события EndPathfinding, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPathfinding\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPathfinding().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpathfinding_handler_id;

// подписываемся на событие EndPathfinding с лямбда-обработчиком, сохраняя идентификатор соединения
endpathfinding_handler_id = Engine::getEventEndPathfinding().connect(e_connections, []() {
		Log::message("\Обработка события EndPathfinding (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPathfinding().disconnect(endpathfinding_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPathfinding при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPathfinding().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPathfinding().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginWorldSwap () const

event triggered before the world logic swap() function is executed. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginWorldSwap
void beginworldswap_event_handler()
{
	Log::message("\Обработка события BeginWorldSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginworldswap_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginWorldSwap().connect(beginworldswap_event_connections, beginworldswap_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginWorldSwap().connect(beginworldswap_event_connections, []() {
		Log::message("\Обработка события BeginWorldSwap (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginworldswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginworldswap_event_connection;

// подписываемся на событие BeginWorldSwap с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginWorldSwap().connect(beginworldswap_event_connection, beginworldswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginworldswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginworldswap_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginWorldSwap через соединение
beginworldswap_event_connection.disconnect();

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

	// Обработчик события BeginWorldSwap, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginWorldSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginWorldSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginworldswap_handler_id;

// подписываемся на событие BeginWorldSwap с лямбда-обработчиком, сохраняя идентификатор соединения
beginworldswap_handler_id = Engine::getEventBeginWorldSwap().connect(e_connections, []() {
		Log::message("\Обработка события BeginWorldSwap (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginWorldSwap().disconnect(beginworldswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginWorldSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginWorldSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginWorldSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndWorldSwap () const

event triggered after the world logic swap() function is executed. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndWorldSwap
void endworldswap_event_handler()
{
	Log::message("\Обработка события EndWorldSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endworldswap_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndWorldSwap().connect(endworldswap_event_connections, endworldswap_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndWorldSwap().connect(endworldswap_event_connections, []() {
		Log::message("\Обработка события EndWorldSwap (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endworldswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endworldswap_event_connection;

// подписываемся на событие EndWorldSwap с функцией-обработчиком, сохраняя соединение
Engine::getEventEndWorldSwap().connect(endworldswap_event_connection, endworldswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endworldswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endworldswap_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndWorldSwap через соединение
endworldswap_event_connection.disconnect();

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

	// Обработчик события EndWorldSwap, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndWorldSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndWorldSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endworldswap_handler_id;

// подписываемся на событие EndWorldSwap с лямбда-обработчиком, сохраняя идентификатор соединения
endworldswap_handler_id = Engine::getEventEndWorldSwap().connect(e_connections, []() {
		Log::message("\Обработка события EndWorldSwap (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndWorldSwap().disconnect(endworldswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndWorldSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndWorldSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndWorldSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginPluginsSwap () const

event triggered before the plugin swap() function is called, if it exists. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginPluginsSwap
void beginpluginsswap_event_handler()
{
	Log::message("\Обработка события BeginPluginsSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginpluginsswap_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginPluginsSwap().connect(beginpluginsswap_event_connections, beginpluginsswap_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginPluginsSwap().connect(beginpluginsswap_event_connections, []() {
		Log::message("\Обработка события BeginPluginsSwap (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginpluginsswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginpluginsswap_event_connection;

// подписываемся на событие BeginPluginsSwap с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginPluginsSwap().connect(beginpluginsswap_event_connection, beginpluginsswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginpluginsswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginpluginsswap_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginPluginsSwap через соединение
beginpluginsswap_event_connection.disconnect();

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

	// Обработчик события BeginPluginsSwap, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginPluginsSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginPluginsSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginpluginsswap_handler_id;

// подписываемся на событие BeginPluginsSwap с лямбда-обработчиком, сохраняя идентификатор соединения
beginpluginsswap_handler_id = Engine::getEventBeginPluginsSwap().connect(e_connections, []() {
		Log::message("\Обработка события BeginPluginsSwap (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginPluginsSwap().disconnect(beginpluginsswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginPluginsSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginPluginsSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginPluginsSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndPluginsSwap () const

event triggered after the plugin swap() function is called, if it exists. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndPluginsSwap
void endpluginsswap_event_handler()
{
	Log::message("\Обработка события EndPluginsSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endpluginsswap_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndPluginsSwap().connect(endpluginsswap_event_connections, endpluginsswap_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndPluginsSwap().connect(endpluginsswap_event_connections, []() {
		Log::message("\Обработка события EndPluginsSwap (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endpluginsswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endpluginsswap_event_connection;

// подписываемся на событие EndPluginsSwap с функцией-обработчиком, сохраняя соединение
Engine::getEventEndPluginsSwap().connect(endpluginsswap_event_connection, endpluginsswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endpluginsswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endpluginsswap_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndPluginsSwap через соединение
endpluginsswap_event_connection.disconnect();

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

	// Обработчик события EndPluginsSwap, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndPluginsSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndPluginsSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endpluginsswap_handler_id;

// подписываемся на событие EndPluginsSwap с лямбда-обработчиком, сохраняя идентификатор соединения
endpluginsswap_handler_id = Engine::getEventEndPluginsSwap().connect(e_connections, []() {
		Log::message("\Обработка события EndPluginsSwap (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndPluginsSwap().disconnect(endpluginsswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndPluginsSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndPluginsSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndPluginsSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventBeginDeleteObjects () const

event triggered before the objects are deleted. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginDeleteObjects
void begindeleteobjects_event_handler()
{
	Log::message("\Обработка события BeginDeleteObjects\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begindeleteobjects_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventBeginDeleteObjects().connect(begindeleteobjects_event_connections, begindeleteobjects_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventBeginDeleteObjects().connect(begindeleteobjects_event_connections, []() {
		Log::message("\Обработка события BeginDeleteObjects (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begindeleteobjects_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begindeleteobjects_event_connection;

// подписываемся на событие BeginDeleteObjects с функцией-обработчиком, сохраняя соединение
Engine::getEventBeginDeleteObjects().connect(begindeleteobjects_event_connection, begindeleteobjects_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begindeleteobjects_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begindeleteobjects_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginDeleteObjects через соединение
begindeleteobjects_event_connection.disconnect();

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

	// Обработчик события BeginDeleteObjects, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginDeleteObjects\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventBeginDeleteObjects().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begindeleteobjects_handler_id;

// подписываемся на событие BeginDeleteObjects с лямбда-обработчиком, сохраняя идентификатор соединения
begindeleteobjects_handler_id = Engine::getEventBeginDeleteObjects().connect(e_connections, []() {
		Log::message("\Обработка события BeginDeleteObjects (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventBeginDeleteObjects().disconnect(begindeleteobjects_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginDeleteObjects при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventBeginDeleteObjects().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventBeginDeleteObjects().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndDeleteObjects () const

event triggered after the objects are deleted. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndDeleteObjects
void enddeleteobjects_event_handler()
{
	Log::message("\Обработка события EndDeleteObjects\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections enddeleteobjects_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndDeleteObjects().connect(enddeleteobjects_event_connections, enddeleteobjects_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndDeleteObjects().connect(enddeleteobjects_event_connections, []() {
		Log::message("\Обработка события EndDeleteObjects (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
enddeleteobjects_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection enddeleteobjects_event_connection;

// подписываемся на событие EndDeleteObjects с функцией-обработчиком, сохраняя соединение
Engine::getEventEndDeleteObjects().connect(enddeleteobjects_event_connection, enddeleteobjects_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
enddeleteobjects_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
enddeleteobjects_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndDeleteObjects через соединение
enddeleteobjects_event_connection.disconnect();

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

	// Обработчик события EndDeleteObjects, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndDeleteObjects\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndDeleteObjects().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId enddeleteobjects_handler_id;

// подписываемся на событие EndDeleteObjects с лямбда-обработчиком, сохраняя идентификатор соединения
enddeleteobjects_handler_id = Engine::getEventEndDeleteObjects().connect(e_connections, []() {
		Log::message("\Обработка события EndDeleteObjects (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndDeleteObjects().disconnect(enddeleteobjects_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndDeleteObjects при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndDeleteObjects().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndDeleteObjects().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventEndSwap () const

event triggered after the swap stage is finished. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndSwap
void endswap_event_handler()
{
	Log::message("\Обработка события EndSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endswap_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventEndSwap().connect(endswap_event_connections, endswap_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventEndSwap().connect(endswap_event_connections, []() {
		Log::message("\Обработка события EndSwap (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endswap_event_connection;

// подписываемся на событие EndSwap с функцией-обработчиком, сохраняя соединение
Engine::getEventEndSwap().connect(endswap_event_connection, endswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endswap_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndSwap через соединение
endswap_event_connection.disconnect();

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

	// Обработчик события EndSwap, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventEndSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endswap_handler_id;

// подписываемся на событие EndSwap с лямбда-обработчиком, сохраняя идентификатор соединения
endswap_handler_id = Engine::getEventEndSwap().connect(e_connections, []() {
		Log::message("\Обработка события EndSwap (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventEndSwap().disconnect(endswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventEndSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventEndSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventFocusGained () const

event triggered when any of the engine windows gained the focus. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FocusGained
void focusgained_event_handler()
{
	Log::message("\Обработка события FocusGained\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections focusgained_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventFocusGained().connect(focusgained_event_connections, focusgained_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventFocusGained().connect(focusgained_event_connections, []() {
		Log::message("\Обработка события FocusGained (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
focusgained_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection focusgained_event_connection;

// подписываемся на событие FocusGained с функцией-обработчиком, сохраняя соединение
Engine::getEventFocusGained().connect(focusgained_event_connection, focusgained_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
focusgained_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
focusgained_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FocusGained через соединение
focusgained_event_connection.disconnect();

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

	// Обработчик события FocusGained, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события FocusGained\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventFocusGained().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId focusgained_handler_id;

// подписываемся на событие FocusGained с лямбда-обработчиком, сохраняя идентификатор соединения
focusgained_handler_id = Engine::getEventFocusGained().connect(e_connections, []() {
		Log::message("\Обработка события FocusGained (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventFocusGained().disconnect(focusgained_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FocusGained при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventFocusGained().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventFocusGained().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event getEventFocusLost () const

event triggered when all engine windows lost the focus. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FocusLost
void focuslost_event_handler()
{
	Log::message("\Обработка события FocusLost\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections focuslost_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventFocusLost().connect(focuslost_event_connections, focuslost_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventFocusLost().connect(focuslost_event_connections, []() {
		Log::message("\Обработка события FocusLost (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
focuslost_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection focuslost_event_connection;

// подписываемся на событие FocusLost с функцией-обработчиком, сохраняя соединение
Engine::getEventFocusLost().connect(focuslost_event_connection, focuslost_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
focuslost_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
focuslost_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FocusLost через соединение
focuslost_event_connection.disconnect();

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

	// Обработчик события FocusLost, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события FocusLost\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventFocusLost().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId focuslost_handler_id;

// подписываемся на событие FocusLost с лямбда-обработчиком, сохраняя идентификатор соединения
focuslost_handler_id = Engine::getEventFocusLost().connect(e_connections, []() {
		Log::message("\Обработка события FocusLost (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventFocusLost().disconnect(focuslost_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FocusLost при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventFocusLost().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventFocusLost().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char*> getEventPluginAdded () const

event triggered before the update stage is started. You can subscribe to events via *connect()*  and unsubscribe via *disconnect()*. You can also use *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* and *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)*  classes for convenience (see examples below).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char ***plugin_name**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PluginAdded
void pluginadded_event_handler(const char *plugin_name)
{
	Log::message("\Обработка события PluginAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections pluginadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventPluginAdded().connect(pluginadded_event_connections, pluginadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventPluginAdded().connect(pluginadded_event_connections, [](const char *plugin_name) {
		Log::message("\Обработка события PluginAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
pluginadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection pluginadded_event_connection;

// подписываемся на событие PluginAdded с функцией-обработчиком, сохраняя соединение
Engine::getEventPluginAdded().connect(pluginadded_event_connection, pluginadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
pluginadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
pluginadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PluginAdded через соединение
pluginadded_event_connection.disconnect();

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

	// Обработчик события PluginAdded, реализованный как член класса
	void event_handler(const char *plugin_name)
	{
		Log::message("\Обработка события PluginAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventPluginAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId pluginadded_handler_id;

// подписываемся на событие PluginAdded с лямбда-обработчиком, сохраняя идентификатор соединения
pluginadded_handler_id = Engine::getEventPluginAdded().connect(e_connections, [](const char *plugin_name) {
		Log::message("\Обработка события PluginAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventPluginAdded().disconnect(pluginadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PluginAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventPluginAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventPluginAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char*> getEventPluginRemoved () const

event triggered before the update stage is started. You can subscribe to events via *connect()*  and unsubscribe via *disconnect()*. You can also use *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* and *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)*  classes for convenience (see examples below).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char ***plugin_name**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PluginRemoved
void pluginremoved_event_handler(const char *plugin_name)
{
	Log::message("\Обработка события PluginRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections pluginremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Engine::getEventPluginRemoved().connect(pluginremoved_event_connections, pluginremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Engine::getEventPluginRemoved().connect(pluginremoved_event_connections, [](const char *plugin_name) {
		Log::message("\Обработка события PluginRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
pluginremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection pluginremoved_event_connection;

// подписываемся на событие PluginRemoved с функцией-обработчиком, сохраняя соединение
Engine::getEventPluginRemoved().connect(pluginremoved_event_connection, pluginremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
pluginremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
pluginremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PluginRemoved через соединение
pluginremoved_event_connection.disconnect();

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

	// Обработчик события PluginRemoved, реализованный как член класса
	void event_handler(const char *plugin_name)
	{
		Log::message("\Обработка события PluginRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Engine::getEventPluginRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId pluginremoved_handler_id;

// подписываемся на событие PluginRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
pluginremoved_handler_id = Engine::getEventPluginRemoved().connect(e_connections, [](const char *plugin_name) {
		Log::message("\Обработка события PluginRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Engine::getEventPluginRemoved().disconnect(pluginremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PluginRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Engine::getEventPluginRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Engine::getEventPluginRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static Engine * get ( )

Returns a pointer to the existing engine instance.
### Возвращаемое значение

Pointer to the existing engine.
## virtual const char * getArg ( int num ) const

Returns a [command line](../../../code/command_line.md) argument by its index.
### Аргументы

- *int* **num** - Index of the command line argument.

### Возвращаемое значение

Command line argument.
## virtual float getArgf ( int num ) const =0

Returns a [command line](../../../code/command_line.md) argument by its index converted to a floating point value.
### Аргументы

- *int* **num** - Index of the command line argument.

### Возвращаемое значение

Command line argument.
## virtual int getArgi ( int num ) const =0

Returns a [command line](../../../code/command_line.md) argument by its index converted to an integer value.
### Аргументы

- *int* **num** - Index of the command line argument.

### Возвращаемое значение

Command line argument.
## static Engine::BUILD_CONFIG getBuildConfiguration ( )

Returns the current Engine build configuration.
### Возвращаемое значение

Current build configuration. One of the [BUILD_CONFIG_](#BUILD_CONFIG) values.
## static const char * getLibraryModulePath ( )

Returns a path to the Engine's dynamic library file.
### Возвращаемое значение

Path to the Engine's dynamic library file.
## virtual int getEditorFunction ( const char * name , int num_args ) const

Returns the editor function identifier.
### Аргументы

- *const char ** **name** - Name of the editor script function.
- *int* **num_args** - Number of editor script function arguments.

### Возвращаемое значение

The editor script function identifier.
## virtual bool isEditorFunction ( const char * name , int num_args ) const

Returns a value indicating if the editor script function exists.
### Аргументы

- *const char ** **name** - Name of the editor script function.
- *int* **num_args** - Number of editor script function arguments.

### Возвращаемое значение

**true** if the editor script function exists; otherwise, **false**.
## virtual void * getEditorInterpreter ( ) const =0

Returns a pointer to the editor interpreter.
### Возвращаемое значение

Pointer to the editor interpreter.
## virtual bool isEditorInterpreter ( ) const =0

Returns a value indicating if the function is called from the editor script.
### Возвращаемое значение

**true** if the function is called from the editor script; otherwise, **false**.
## virtual bool isEditorLoaded ( ) const =0

Returns a value indicating if the editor script is loaded.
### Возвращаемое значение

**true** if the editor script is loaded; otherwise, **false**.
## virtual EditorLogic * getEditorLogic ( int num ) const =0

Returns the registered [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instance by its number.
### Аргументы

- *int* **num** - Number of the EditorLogic instance.

### Возвращаемое значение

[EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instance.
## virtual void setEditorVariable ( const char * name , const Variable & v ) =0

Sets the editor script variable by its name.
### Аргументы

- *const char ** **name** - Name of the editor script variable.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Value of the editor script variable.

## virtual const Variable & getEditorVariable ( const char * name ) const =0

Returns the editor script variable by its name.
### Аргументы

- *const char ** **name** - Name of the world script variable.

### Возвращаемое значение

Value of the editor script variable.
## virtual bool isEditorVariable ( const char * name ) const =0

Returns a value indicating if the editor script variable exists.
### Аргументы

- *const char ** **name** - Name of the editor script variable.

### Возвращаемое значение

**true** if the editor script variable exists; otherwise, **false**.
## virtual const char * getArg ( int num ) =0

Returns the command-line argument by its index.
### Аргументы

- *int* **num** - Index of the argument.

### Возвращаемое значение

Command-line argument
## template < SingletonClass class >

## SingletonClass * getPlugin ( const char * name )

Returns the loaded plugin interface.
### Аргументы

- *const char ** **name** - Name of the loaded plugin.

### Возвращаемое значение

Interface of the loaded plugin, if it exists; otherwise, **nullptr**.
## virtual void * getPluginData ( int num ) const =0

Returns the data of the specified loaded plugin by calling its [get_data()](../../../api/library/common/class.plugin_cpp.md#get_data_void_ptr) method.
### Аргументы

- *int* **num** - Index of the loaded plugin.

### Возвращаемое значение

Data of the loaded plugin, if it exists; otherwise, **0**.
## virtual Plugin * getPluginInterface ( int num ) const =0

Returns the loaded plugin interface.
### Аргументы

- *int* **num** - Index of the loaded plugin.

### Возвращаемое значение

Interface of the loaded plugin, if it exists; otherwise, **0**.
## const char * getPluginName ( int num ) const

Returns the name of the specified loaded plugin by calling its *[get_name()](../../../api/library/common/class.plugin_cpp.md#get_name_const_char_ptr)* method.
### Аргументы

- *int* **num** - Index of the loaded plugin.

### Возвращаемое значение

Loaded plugin name.
## int getPluginOrder ( int num ) const

Returns the execution order of the specified loaded plugin by calling its *[get_order()](../../../api/library/common/class.plugin_cpp.md#get_order_int)* method.
### Аргументы

- *int* **num** - Index of the loaded plugin.

### Возвращаемое значение

Loaded plugin execution order.
## const char * getPluginPath ( int num ) const

Returns a path to a plugin directory specified via [-plugin_path](../../../code/command_line.md#plugin_path).
### Аргументы

- *int* **num** - Plugin path number in the row of the specified plugin paths.

### Возвращаемое значение

Path to a plugin directory.
## const char * getPluginAbsolutePath ( int num ) const

Returns an absolute path to a plugin directory.
### Аргументы

- *int* **num** - Plugin path number in the row of the specified plugin paths.

### Возвращаемое значение

Absolute path to a plugin directory.
## int getSystemFunction ( const char * name , int num_args ) const

Returns the system function identifier.
### Аргументы

- *const char ** **name** - Name of the system script function.
- *int* **num_args** - Number of system script function arguments.

### Возвращаемое значение

System script function identifier.
## bool isSystemFunction ( const char * name , int num_args ) const

Checks whether the system script function exists.
### Аргументы

- *const char ** **name** - Name of the system script function.
- *int* **num_args** - Number of system script function arguments.

### Возвращаемое значение

**true** if the system script function exists; otherwise, **false**.
## virtual void * getSystemInterpreter ( ) const =0

Returns a pointer to the system interpreter.
### Возвращаемое значение

Pointer to the system interpreter.
## virtual bool isSystemInterpreter ( ) const =0

Checks if the function is called from the system script.
### Возвращаемое значение

**true** when the function is called from the system script; otherwise, **false**.
## virtual SystemLogic * getSystemLogic ( int num ) const =0

Returns the registered [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instance by the given number.
### Аргументы

- *int* **num** - Number of the SystemLogic instance.

### Возвращаемое значение

[SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instance.
## void setSystemVariable ( const char * name , const Variable & v )

Sets a system script variable by a name.
### Аргументы

- *const char ** **name** - Name of the system script variable.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Value of the system script variable.

## const Variable & getSystemVariable ( const char * name ) const

Returns the system script variable by its name.
### Аргументы

- *const char ** **name** - Name of the system script variable.

### Возвращаемое значение

System script variable.
## bool isSystemVariable ( const char * name ) const

Checks whether a system script variable exists.
### Аргументы

- *const char ** **name** - Name of the system script variable.

### Возвращаемое значение

**true** if the system script variable exists; otherwise, **false**.
## int getWorldFunction ( const char * name , int num_args ) const

Returns the world script function identifier.
### Аргументы

- *const char ** **name** - Name of the world script function.
- *int* **num_args** - Number of world script function arguments.

### Возвращаемое значение

World script function identifier.
## bool isWorldFunction ( const char * name , int num_args ) const

Returns value indicating if the world script function exists.
### Аргументы

- *const char ** **name** - Name of the world script function.
- *int* **num_args** - Number of world script function arguments.

### Возвращаемое значение

**true** if the world script function exists; otherwise, **false**.
## virtual void * getWorldInterpreter ( ) const =0

Returns a pointer to the world interpreter.
### Возвращаемое значение

Pointer to the world interpreter.
## virtual bool isWorldInterpreter ( ) const =0

Returns a value indicating if the function is called from the world script.
### Возвращаемое значение

**true** if the function is called from the world script; otherwise, **false**.
## virtual bool isWorldLoaded ( ) const =0

Returns a value indicating if the world script is loaded.
### Возвращаемое значение

**true** if the world script is loaded; otherwise, **false**.
## virtual WorldLogic * getWorldLogic ( int num ) const =0

Returns the registered [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instance by its number.
### Аргументы

- *int* **num** - Number of the WorldLogic instance.

### Возвращаемое значение

[WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instance.
## void setWorldVariable ( const char * name , const Variable & v )

Sets a world script variable by its name.
### Аргументы

- *const char ** **name** - Name of the world script variable.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Value of the world script variable.

## const Variable & getWorldVariable ( const char * name ) const

Returns a world script variable by its name.
### Аргументы

- *const char ** **name** - Name of the world script variable.

### Возвращаемое значение

World script variable.
## bool isWorldVariable ( const char * name ) const

Returns a value indicating if the world script variable exists.
### Аргументы

- *const char ** **name** - Name of the world script variable.

### Возвращаемое значение

**true** if the world script variable exists; otherwise, **false**.
## bool addEditorLogic ( EditorLogic * logic )

Adds an [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instance to the engine runtime.
### Аргументы

- *[EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) ** **logic** - [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instance.

### Возвращаемое значение

**true** if the EditorLogic instance has been added successfully; otherwise, **false**.
## virtual bool addPlugin ( Plugin * plugin ) =0

Adds a plugin to engine runtime by using a pointer to this plugin.
### Аргументы

- *[Plugin](../../../api/library/common/class.plugin_cpp.md) ** **plugin** - Plugin pointer.

### Возвращаемое значение

**true** if the plugin ha been added successfully; otherwise, **false**.
## bool addPlugin ( const char * name )

Adds a plugin to engine runtime by its name.
### Аргументы

- *const char ** **name** - Plugin name.

### Возвращаемое значение

**true** if the plugin has been added successfully; otherwise, **false**.
## bool addSystemLogic ( SystemLogic * logic )

Adds a [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instance to Engine runtime.
### Аргументы

- *[SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) ** **logic** - [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instance.

### Возвращаемое значение

**true** if the SystemLogic instance has been added successfully; otherwise, **false**.
## bool addWorldLogic ( WorldLogic * logic )

Adds a [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instance to the engine runtime.
> **Notice:** Instances of the *WorldLogic* class **should not be added while the world is loaded** and the world script is being executed (as you can't change a world script while the world is loaded). In such a case the ***init()*** method shall not be called if the WorldLogic is added before opening the world.


### Аргументы

- *[WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) ** **logic** - [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instance.

### Возвращаемое значение

**true** if the WorldLogic instance has been added successfully; otherwise, **false**.
## int findPlugin ( const char * name ) const

Searches the index of the loaded plugin by its name.
### Аргументы

- *const char ** **name** - Name of the plugin.

### Возвращаемое значение

Index of the plugin if it is found, or -1 otherwise.
## void main ( SystemLogic * system , WorldLogic * world , EditorLogic * editor )

Engine main loop. Replaces the following commands:
```cpp
while (!Engine::get()->isQuit()) {
	Engine::get()->update();
	Engine::get()->render();
	Engine::get()->swap();
}

```


```csharp
while (!Engine.IsQuit) {
	Engine.Update();
	Engine.Render();
	Engine.Swap();
}

```


### Аргументы

- *[SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) ** **system** - A [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instance.
- *[WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) ** **world** - A [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instance.
- *[EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) ** **editor** - An [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instance.

## bool removeEditorLogic ( EditorLogic * logic )

Removes an [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instance from engine runtime.
### Аргументы

- *[EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) ** **logic** - An [EditorLogic](../../../api/library/common/logic/class.editorlogic_cpp.md) instance.

### Возвращаемое значение

**true** if the instance has been removed successfully; otherwise, **false**.
## virtual bool destroyPlugin ( Plugin * plugin ) =0

Removes the specified plugin.
### Аргументы

- *[Plugin](../../../api/library/common/class.plugin_cpp.md) ** **plugin** - Plugin pointer to remove.

### Возвращаемое значение

**true** if the plugin has been removed successfully; otherwise, **false**.
## bool removeSystemLogic ( SystemLogic * logic )

Removes a [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instance from engine runtime.
### Аргументы

- *[SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) ** **logic** - A [SystemLogic](../../../api/library/common/logic/class.systemlogic_cpp.md) instance.

### Возвращаемое значение

**true** if the instance has been removed successfully; otherwise, **false**.
## bool removeWorldLogic ( WorldLogic * logic )

Removes a [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instance from engine runtime.
> **Notice:** Instances of the *WorldLogic* class **should not be removed while the world is loaded** and the world script is being executed (as you can't change a world script while the world is loaded). In such a case the ***shutdown()*** method shall not be called if the WorldLogic is removed before closing the world.


### Аргументы

- *[WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) ** **logic** - A [WorldLogic](../../../api/library/common/logic/class.worldlogic_cpp.md) instance.

### Возвращаемое значение

**true** if the instance has been removed successfully; otherwise, **false**.
## virtual const Variable & runEditorFunction ( const Variable & name ) =0

Runs the editor script function by its name. The target function can receive up to 8 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 )

Runs the editor script function by its name. The target function must receive 1 argument.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 , const Variable & a1 )

Runs the editor script function by its name. The target function must receive 2 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 )

Runs the editor script function by its name. The target function must receive 3 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 )

Runs the editor script function by its name. The target function must receive 4 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 )

Runs the editor script function by its name. The target function must receive 5 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 )

Runs the editor script function by its name. The target function must receive 6 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 )

Runs the editor script function by its name. The target function must receive 7 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 , const Variable & a7 )

Runs the editor script function by its name. The target function must receive 8 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a7** - Eighth argument.

### Возвращаемое значение

Editor script function return value.
## virtual const Variable & runEditorFunction ( const Variable & name , const Variable * args , int num_args ) =0

Runs the editor script function by its name.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args** - Pointer to editor script function arguments.
- *int* **num_args** - Number of editor script function arguments.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id )

Runs the editor script function by its id. The target function can receive up to 8 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable * args , int num_args )

Runs the editor script function by its id.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args** - Pointer to editor script function arguments.
- *int* **num_args** - Number of editor script function arguments.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 )

Runs the editor script function by its name. The target function must receive 1 argument.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 , const Variable & a1 )

Runs the editor script function by its name. The target function must receive 2 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 )

Runs the editor script function by its name. The target function must receive 3 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 )

Runs the editor script function by its name. The target function must receive 4 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 )

Runs the editor script function by its name. The target function must receive 5 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 )

Runs the editor script function by its name. The target function must receive 6 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 )

Runs the editor script function by its name. The target function must receive 7 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.

### Возвращаемое значение

Editor script function return value.
## const Variable & runEditorFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 , const Variable & a7 )

Runs the editor script function by its name. The target function must receive 8 arguments.
### Аргументы

- *int* **id** - ID of the editor script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a7** - Eighth argument.

### Возвращаемое значение

Editor script function return value.
## virtual const Variable & runSystemFunction ( const Variable & name ) =0

Runs the system script function by its name. The target function can receive up to 8 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 )

Runs the system script function by its name. The target function must receive 1 argument.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 , const Variable & a1 )

Runs the system script function by its name. The target function must receive 2 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 )

Runs the system script function by its name. The target function must receive 3 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 )

Runs the system script function by its name. The target function must receive 4 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 )

Runs the system script function by its name. The target function must receive 4 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 )

Runs the system script function by its name. The target function must receive 6 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 )

Runs the system script function by its name. The target function must receive 7 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 , const Variable & a7 )

Runs the system script function by its name. The target function must receive 8 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a7** - Eighth argument.

### Возвращаемое значение

System script function return value.
## virtual const Variable & runSystemFunction ( const Variable & name , const Variable * args , int num_args ) =0

Runs system script function by its name.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args** - Pointer to system script function arguments.
- *int* **num_args** - Number of system script function arguments.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id )

Runs the system script function by its id. The target function can receive up to 8 arguments.
### Аргументы

- *int* **id** - ID of the system script function.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable * args , int num_args )

Runs system script function by its id.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args** - Pointer to system script function arguments.
- *int* **num_args** - Number of system script function arguments.

## const Variable & runSystemFunction ( int id , const Variable & a0 )

Runs the system script function by its id. The target function must receive 1 argument.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable & a0 , const Variable & a1 )

Runs the system script function by its id. The target function must receive 2 arguments.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 )

Runs the system script function by its id. The target function must receive 3 arguments.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 )

Runs the system script function by its id. The target function must receive 4 arguments.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 )

Runs the system script function by its id. The target function must receive 5 arguments.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 )

Runs the system script function by its id. The target function must receive 6 arguments.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 )

Runs the system script function by its id. The target function must receive 7 arguments.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.

### Возвращаемое значение

System script function return value.
## const Variable & runSystemFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 , const Variable & a7 )

Runs the system script function by its id. The target function must receive 8 arguments.
### Аргументы

- *int* **id** - ID of the system script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a7** - Eighth argument.

### Возвращаемое значение

System script function return value.
## virtual const Variable & runWorldFunction ( const Variable & name ) =0

Runs the world script function by its name. The target function can receive up to 8 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 )

Runs the world script function by its name. The target function must receive 1 argument.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable & a0 )

Runs the world script function by its identifier. The target function must receive one argument.
### Аргументы

- *int* **id** - Identifier of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - Argument

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 , const Variable & a1 )

Runs the world script function by its name. The target function must receive 2 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 )

Runs the world script function by its name. The target function must receive 3 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 )

Runs the world script function by its name. The target function must receive 4 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 )

Runs the world script function by its name. The target function must receive 5 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 )

Runs the world script function by its name. The target function must receive 6 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 )

Runs the world script function by its name. The target function must receive 8 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( const Variable & name , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 , const Variable & a7 )

Runs the world script function by its name. The target function must receive 8 arguments.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a7** - Eighth argument.

### Возвращаемое значение

World script function return value.
## virtual const Variable & runWorldFunction ( const Variable & name , const Variable * args , int num_args ) =0

Runs the world script function by its name.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **name** - Name of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args** - Pointer to world script function arguments.
- *int* **num_args** - Number of world script function arguments.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id )

Runs the world script function by its id.
### Аргументы

- *int* **id** - ID of the world script function.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable * args , int num_args )

Runs the world script function by its id.
### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args** - Pointer to world script function arguments.
- *int* **num_args** - Number of world script function arguments.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable & a0 , const Variable & a1 )

Runs the world script function by its id. The target function must receive 2 arguments.
### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 )

Runs the world script function by its id. The target function must receive 3 arguments.
### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 )

### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.

### Возвращаемое значение

World script function return value.Runs the world script function by its id. The target function must receive 4 arguments.
## const Variable & runWorldFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 )

Runs the world script function by its id. The target function must receive 5 arguments.
### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 )

Runs the world script function by its id. The target function must receive 6 arguments.
### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 )

Runs the world script function by its id. The target function must receive 7 arguments.
### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.

### Возвращаемое значение

World script function return value.
## const Variable & runWorldFunction ( int id , const Variable & a0 , const Variable & a1 , const Variable & a2 , const Variable & a3 , const Variable & a4 , const Variable & a5 , const Variable & a6 , const Variable & a7 )

Runs the world script function by its id. The target function must receive 8 arguments.
### Аргументы

- *int* **id** - ID of the world script function.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a0** - First argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a1** - Second argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a2** - Third argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a3** - Fourth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a4** - Fifth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a5** - Sixth argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a6** - Seventh argument.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a7** - Eighth argument.

### Возвращаемое значение

World script function return value.
## void shutdown ( )

Deletes the pointer to the existing engine instance.
## virtual void iterate ( ) =0

Engine iterate function (update, render, swap). This function must be called every frame.
## void beginOutsideLoopRender ( )

Starts a block of code where you can call *[Render](../../../api/library/rendering/class.render_cpp.md)* class methods from outside the Engine's Loop. The end of this block should be marked with a call to the **[endOutsideLoopRender()](../../...md#endOutsideLoopRender_void)** method.
## void endOutsideLoopRender ( )

Closes a block of code where you can call *[Render](../../../api/library/rendering/class.render_cpp.md)* class methods from outside the Engine's Loop started with a call to the **[beginOutsideLoopRender()](../../...md#beginOutsideLoopRender_void)** method.
## void startFps ( )

Starts the FPS counter if it was stopped. All function calls are placed into a stack, so the number of calls to this function should correspond to the number of calls to the *[stopFps()](#stopFps_void)* function.
## void stopFps ( )

Stops the FPS counter. This function should be called if application window is hidden or some heavy non-rendering tasks are processing. All function calls are placed into a stack, so the number of calls to this function should correspond to the number of calls to the *[startFps()](#startFps_void)* function.
## int getVideoContextFlags ( )

Returns the current video context flags.
### Возвращаемое значение

A set of current video context flags as an integer value.
## static Engine * init ( int argc , char** argv )

Initializes a new engine instance to be used with an external graphics application.
### Аргументы

- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *char*** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

### Возвращаемое значение

Pointer to the new engine instance.
## static Engine * init ( int argc , wchar_t** argv )

Initializes a new engine instance to be used with an external graphics application.
### Аргументы

- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *wchar_t*** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

### Возвращаемое значение

Pointer to the new engine instance.
## static Engine * init ( const InitParameters& init_parameters , int argc , char** argv )

Initializes a new engine instance to be used with an external graphics application.
### Аргументы

- *const InitParameters&* **init_parameters** - Structure of [initializing parameters](#init_parameters).
- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *char*** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

### Возвращаемое значение

Pointer to the new engine instance.
## static Engine * init ( const InitParameters& init_parameters , int argc , wchar_t** argv )

Initializes a new engine instance to be used with an external graphics application.
### Аргументы

- *const InitParameters&* **init_parameters** - Structure of [initializing parameters](#init_parameters).
- *int* **argc** - Number of [command line arguments](../../../code/command_line.md).
- *wchar_t*** **argv** - Array of [command line arguments](../../../code/command_line.md) values.

### Возвращаемое значение

Pointer to the new engine instance.
## void quit ( )

The Engine requests to exit the application.
