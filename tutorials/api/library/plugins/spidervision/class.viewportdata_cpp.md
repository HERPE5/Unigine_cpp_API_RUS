# Unigine::Plugins::SpiderVision::ViewportData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Экземпляр этого класса хранит все данные viewport: трансформации, настройки типа viewport, физический размер дисплея, VFOV, аспект, вертикальное и горизонтальное смещение, детали эффекта искажения и т.д.


Этот объект доступен через соответствующие методы класса [DisplaysConfig](../../../../api/library/plugins/spidervision/class.displaysconfig_cpp.md#getViewportByIndex_int_ViewportData).


Данные масок хранятся в [configuration file](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#config_file).


## ViewportData Class

### Перечисления

## WINDOW_MODE

| Name | Description |
|---|---|
| **WINDOW_MODE_WINDOWED** = 0 | Оконный режим. |
| **WINDOW_MODE_BORDERLESS_WINDOWED** = 1 | Окно ОС без рамки с настраиваемым размером. |
| **WINDOW_MODE_EXCLUSIVE_FULLSCREEN** = 2 | Полноэкранное окно, занимающее весь дисплей, при этом все остальные окна движка сворачиваются. Взаимодействие с другими окнами движка невозможно. Если фокус переключается на окно другого приложения, полноэкранное окно автоматически сворачивается ОС. |

## POINT_SMOOTH_TYPE

| Name | Description |
|---|---|
| **POINT_SMOOTH_TYPE_LINEAR** = 0 | Для изгиба линии с обеих сторон точки применяется линейная интерполяция. |
| **POINT_SMOOTH_TYPE_SMOOTH** = 1 | Симметричные контрольные точки-указатели для плавных кривых с обеих сторон точки. |
| **POINT_SMOOTH_TYPE_BREAK** = 2 | Асимметричные контрольные точки-указатели для независимого управления каждым указателем. |
| **POINT_SMOOTH_TYPE_AUTO** = 3 | Автоматический плавный изгиб линии, контрольные точки-указатели недоступны. |
| **POINT_SMOOTH_TYPE_NUM** = 4 | Общее количество режимов изгиба линии. |

## DISPLAY_TRANSFORM_TYPE

| Name | Description |
|---|---|
| **DISPLAY_TRANSFORM_TYPE_DISPLAY** = 0 | Viewport дисплея. |
| **DISPLAY_TRANSFORM_TYPE_PROJECTOR** = 1 | Viewport проектора. |

### Методы класса

## int getID () const

Возвращает текущий ID viewport.
### Возвращаемое значение

Текущий ID viewport.
## void setName ( const char * name )

Задаёт новое [viewport name](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#viewport_name).
### Аргументы

- *const char ** **name** - Имя viewport.

## String getName () const

Возвращает текущее [viewport name](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#viewport_name).
### Возвращаемое значение

Текущее имя viewport.
## void setComputerName ( const char * name )

Задаёт новое [name of the computer](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#computer_name), на котором должен отрисовываться этот viewport.
### Аргументы

- *const char ** **name** - Имя компьютера, на котором должен отрисовываться этот viewport. Если не задано, viewport отрисовывается на любом ПК.

## String getComputerName () const

Возвращает текущее [name of the computer](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#computer_name), на котором должен отрисовываться этот viewport.
### Возвращаемое значение

Текущее имя компьютера, на котором должен отрисовываться этот viewport. Если не задано, viewport отрисовывается на любом ПК.
## void setDisplayIndex ( int index )

Задаёт новый [display index](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#display_index).
### Аргументы

- *int* **index** - Индекс дисплея.

## int getDisplayIndex () const

Возвращает текущий [display index](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#display_index).
### Возвращаемое значение

Текущий индекс дисплея.
## void setWindowSize ( const Math:: ivec2 & size )

Задаёт новый [size of the window](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#window_size), если оно в [Window mode](#WINDOW_MODE_WINDOWED).
### Аргументы

- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md)&* **size** - Размер окна.

## Math:: ivec2 getWindowSize () const

Возвращает текущий [size of the window](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#window_size), если оно в [Window mode](#WINDOW_MODE_WINDOWED).
### Возвращаемое значение

Текущий размер окна.
## void setWindowPosition ( const Math:: ivec2 & position )

Задаёт новую [window position](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#window_position) на экране.
### Аргументы

- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md)&* **position** - Координаты верхнего левого угла окна на экране.

## Math:: ivec2 getWindowPosition () const

Возвращает текущую [window position](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#window_position) на экране.
### Возвращаемое значение

Текущие координаты верхнего левого угла окна на экране.
## void setWindowMode ( ViewportData::WINDOW_MODE mode )

Задаёт новый [window mode](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#window_mode) для отрисовываемого viewport: имитация полноэкранного режима (окно без рамки, адаптированное под всю область окна) или оконный режим.
### Аргументы

- *[ViewportData::WINDOW_MODE](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#WINDOW_MODE)* **mode** - Режим окна для отрисовываемого viewport.

## ViewportData::WINDOW_MODE getWindowMode () const

Возвращает текущий [window mode](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#window_mode) для отрисовываемого viewport: имитация полноэкранного режима (окно без рамки, адаптированное под всю область окна) или оконный режим.
### Возвращаемое значение

Текущий режим окна для отрисовываемого viewport.
## void setProjectionEnabled ( bool enabled )

Задаёт новое значение, указывающее, включена ли [projection rendering](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#projection_enabled) в viewport.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отрисовку проекции; **false** - чтобы отключить её.

## bool isProjectionEnabled () const

Возвращает текущее значение, указывающее, включена ли [projection rendering](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#projection_enabled) в viewport.
### Возвращаемое значение

**true**, если отрисовка проекции включена; иначе **false**.
## void setPosition ( const Math:: vec3 & position )

Задаёт новую [viewport position](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#transform_position) относительно точки обзора в настройке.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md)&* **position** - Позиция viewport относительно точки обзора в настройке.

## Math:: vec3 getPosition () const

Возвращает текущую [viewport position](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#transform_position) относительно точки обзора в настройке.
### Возвращаемое значение

Текущая позиция viewport относительно точки обзора в настройке.
## void setRotation ( const Math:: vec3 & rotation )

Задаёт новый [viewport rotation](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#transform_rotation) относительно его собственного центра в настройке.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md)&* **rotation** - Поворот viewport относительно его собственного центра в настройке.

## Math:: vec3 getRotation () const

Возвращает текущий [viewport rotation](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#transform_rotation) относительно его собственного центра в настройке.
### Возвращаемое значение

Текущий поворот viewport относительно его собственного центра в настройке.
## void setOffset ( const Math:: vec2 & offset )

Задаёт новое смещение FOV.
### Аргументы

- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md)&* **offset** - Смещение FOV.

## Math:: vec2 getOffset () const

Возвращает текущее смещение FOV.
### Возвращаемое значение

Текущее смещение FOV.
## void setType ( ViewportData::DISPLAY_TRANSFORM_TYPE type )

Задаёт новый тип искажения проекционной матрицы, применяемого к viewport: дисплей или проектор.
### Аргументы

- *[ViewportData::DISPLAY_TRANSFORM_TYPE](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#DISPLAY_TRANSFORM_TYPE)* **type** - Тип искажения проекционной матрицы, применяемого к viewport.

## ViewportData::DISPLAY_TRANSFORM_TYPE getType () const

Возвращает текущий тип искажения проекционной матрицы, применяемого к viewport: дисплей или проектор.
### Возвращаемое значение

Текущий тип искажения проекционной матрицы, применяемого к viewport.
## void setSize ( const Math:: vec2 & size )

Задаёт новый физический размер дисплея.
### Аргументы

- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md)&* **size** - Физический размер дисплея.

## Math:: vec2 getSize () const

Возвращает текущий физический размер дисплея.
### Возвращаемое значение

Текущий физический размер дисплея.
## void setAspect ( float aspect )

Задаёт новое соотношение сторон для проектора.
### Аргументы

- *float* **aspect** - Соотношение сторон для проектора.

## float getAspect () const

Возвращает текущее соотношение сторон для проектора.
### Возвращаемое значение

Текущее соотношение сторон для проектора.
## void setVFov ( float vfov )

Задаёт новый вертикальный угол обзора для проектора.
### Аргументы

- *float* **vfov** - Вертикальный угол обзора для проектора, в градусах.

## float getVFov () const

Возвращает текущий вертикальный угол обзора для проектора.
### Возвращаемое значение

Текущий вертикальный угол обзора для проектора, в градусах.
## void setGroupID ( int id )

Задаёт новый ID группы viewport.
### Аргументы

- *int* **id** - ID группы viewport.

## int getGroupID () const

Возвращает текущий ID группы viewport.
### Возвращаемое значение

Текущий ID группы viewport.
## static Event<ViewportData*> getEventBaseChanged () const

событие, вызываемое при изменении базовых параметров viewport (ширина, высота, позиция, поворот и т.д.). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BaseChanged
void basechanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события BaseChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections basechanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventBaseChanged().connect(basechanged_event_connections, basechanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventBaseChanged().connect(basechanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события BaseChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
basechanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection basechanged_event_connection;

// подписываемся на событие BaseChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventBaseChanged().connect(basechanged_event_connection, basechanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
basechanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
basechanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BaseChanged через соединение
basechanged_event_connection.disconnect();

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

	// Обработчик события BaseChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события BaseChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventBaseChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId basechanged_handler_id;

// подписываемся на событие BaseChanged с лямбда-обработчиком, сохраняя идентификатор соединения
basechanged_handler_id = ViewportData::getEventBaseChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события BaseChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventBaseChanged().disconnect(basechanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BaseChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventBaseChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventBaseChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventWarpChanged () const

событие, вызываемое при изменении искажения (коррекции геометрии). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события WarpChanged
void warpchanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события WarpChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections warpchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventWarpChanged().connect(warpchanged_event_connections, warpchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventWarpChanged().connect(warpchanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события WarpChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
warpchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection warpchanged_event_connection;

// подписываемся на событие WarpChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventWarpChanged().connect(warpchanged_event_connection, warpchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
warpchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
warpchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие WarpChanged через соединение
warpchanged_event_connection.disconnect();

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

	// Обработчик события WarpChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события WarpChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventWarpChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId warpchanged_handler_id;

// подписываемся на событие WarpChanged с лямбда-обработчиком, сохраняя идентификатор соединения
warpchanged_handler_id = ViewportData::getEventWarpChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события WarpChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventWarpChanged().disconnect(warpchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий WarpChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventWarpChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventWarpChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventEasyblendChanged () const

событие, вызываемое при загрузке или выгрузке файла конфигурации многопроекторной настройки `.ol` (созданного через *Scalable Display Manager*). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EasyblendChanged
void easyblendchanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события EasyblendChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections easyblendchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventEasyblendChanged().connect(easyblendchanged_event_connections, easyblendchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventEasyblendChanged().connect(easyblendchanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события EasyblendChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
easyblendchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection easyblendchanged_event_connection;

// подписываемся на событие EasyblendChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventEasyblendChanged().connect(easyblendchanged_event_connection, easyblendchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
easyblendchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
easyblendchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EasyblendChanged через соединение
easyblendchanged_event_connection.disconnect();

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

	// Обработчик события EasyblendChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события EasyblendChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventEasyblendChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId easyblendchanged_handler_id;

// подписываемся на событие EasyblendChanged с лямбда-обработчиком, сохраняя идентификатор соединения
easyblendchanged_handler_id = ViewportData::getEventEasyblendChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события EasyblendChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventEasyblendChanged().disconnect(easyblendchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EasyblendChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventEasyblendChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventEasyblendChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventBlendChanged () const

событие, вызываемое при изменении настроек экранного или краевого смешивания (альфа, контраст, гамма и т.д.). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BlendChanged
void blendchanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события BlendChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections blendchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventBlendChanged().connect(blendchanged_event_connections, blendchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventBlendChanged().connect(blendchanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события BlendChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
blendchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection blendchanged_event_connection;

// подписываемся на событие BlendChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventBlendChanged().connect(blendchanged_event_connection, blendchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
blendchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
blendchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BlendChanged через соединение
blendchanged_event_connection.disconnect();

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

	// Обработчик события BlendChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события BlendChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventBlendChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId blendchanged_handler_id;

// подписываемся на событие BlendChanged с лямбда-обработчиком, сохраняя идентификатор соединения
blendchanged_handler_id = ViewportData::getEventBlendChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события BlendChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventBlendChanged().disconnect(blendchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BlendChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventBlendChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventBlendChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventMaskChanged () const

событие, вызываемое при изменении (добавлении, удалении или модификации) масок. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события MaskChanged
void maskchanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события MaskChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections maskchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventMaskChanged().connect(maskchanged_event_connections, maskchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventMaskChanged().connect(maskchanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события MaskChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
maskchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection maskchanged_event_connection;

// подписываемся на событие MaskChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventMaskChanged().connect(maskchanged_event_connection, maskchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
maskchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
maskchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие MaskChanged через соединение
maskchanged_event_connection.disconnect();

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

	// Обработчик события MaskChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события MaskChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventMaskChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId maskchanged_handler_id;

// подписываемся на событие MaskChanged с лямбда-обработчиком, сохраняя идентификатор соединения
maskchanged_handler_id = ViewportData::getEventMaskChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события MaskChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventMaskChanged().disconnect(maskchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий MaskChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventMaskChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventMaskChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventColorChanged () const

событие, вызываемое при изменении настроек яркости и цветокоррекции. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ColorChanged
void colorchanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события ColorChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections colorchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventColorChanged().connect(colorchanged_event_connections, colorchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventColorChanged().connect(colorchanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события ColorChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
colorchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection colorchanged_event_connection;

// подписываемся на событие ColorChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventColorChanged().connect(colorchanged_event_connection, colorchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
colorchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
colorchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ColorChanged через соединение
colorchanged_event_connection.disconnect();

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

	// Обработчик события ColorChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события ColorChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventColorChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId colorchanged_handler_id;

// подписываемся на событие ColorChanged с лямбда-обработчиком, сохраняя идентификатор соединения
colorchanged_handler_id = ViewportData::getEventColorChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события ColorChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventColorChanged().disconnect(colorchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ColorChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventColorChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventColorChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventDebugChanged () const

событие, вызываемое при изменении вспомогательных настроек отладки. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события DebugChanged
void debugchanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события DebugChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections debugchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventDebugChanged().connect(debugchanged_event_connections, debugchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventDebugChanged().connect(debugchanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события DebugChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
debugchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection debugchanged_event_connection;

// подписываемся на событие DebugChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventDebugChanged().connect(debugchanged_event_connection, debugchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
debugchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
debugchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие DebugChanged через соединение
debugchanged_event_connection.disconnect();

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

	// Обработчик события DebugChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события DebugChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventDebugChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId debugchanged_handler_id;

// подписываемся на событие DebugChanged с лямбда-обработчиком, сохраняя идентификатор соединения
debugchanged_handler_id = ViewportData::getEventDebugChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события DebugChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventDebugChanged().disconnect(debugchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий DebugChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventDebugChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventDebugChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<ViewportData*> getEventSomethingChanged () const

событие, вызываемое при ЛЮБЫХ изменениях данных конфигурации viewport (искажение, смешивание, цветокоррекция, отладка и т.д.).
> **Notice:** Это событие вызывается вместе со всеми остальными событиями этого класса.

  Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(ViewportData ***viewport_data**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события SomethingChanged
void somethingchanged_event_handler(ViewportData *viewport_data)
{
	Log::message("\Обработка события SomethingChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections somethingchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
ViewportData::getEventSomethingChanged().connect(somethingchanged_event_connections, somethingchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ViewportData::getEventSomethingChanged().connect(somethingchanged_event_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события SomethingChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
somethingchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection somethingchanged_event_connection;

// подписываемся на событие SomethingChanged с функцией-обработчиком, сохраняя соединение
ViewportData::getEventSomethingChanged().connect(somethingchanged_event_connection, somethingchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
somethingchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
somethingchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие SomethingChanged через соединение
somethingchanged_event_connection.disconnect();

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

	// Обработчик события SomethingChanged, реализованный как член класса
	void event_handler(ViewportData *viewport_data)
	{
		Log::message("\Обработка события SomethingChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
ViewportData::getEventSomethingChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId somethingchanged_handler_id;

// подписываемся на событие SomethingChanged с лямбда-обработчиком, сохраняя идентификатор соединения
somethingchanged_handler_id = ViewportData::getEventSomethingChanged().connect(e_connections, [](ViewportData *viewport_data) {
		Log::message("\Обработка события SomethingChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ViewportData::getEventSomethingChanged().disconnect(somethingchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий SomethingChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ViewportData::getEventSomethingChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ViewportData::getEventSomethingChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## void setViewportRendering ( bool rendering )

Задаёт новое значение, указывающее, включена ли отрисовка viewport.
### Аргументы

- *bool* **rendering** - Установите **true**, чтобы включить отрисовку viewport; **false** - чтобы отключить её.

## bool isViewportRendering () const

Возвращает текущее значение, указывающее, включена ли отрисовка viewport.
### Возвращаемое значение

**true**, если отрисовка viewport включена; иначе **false**.
---

## void update ( )

Обновляет данные, отображаемые в viewport.
## void grabWindowParameters ( )

Обновляет данные viewport в соответствии с [current window parameters](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#grab): индексом дисплея, размером и позицией окна.
## bool isGrouped ( ) const

Возвращает значение, указывающее, входит ли viewport в группу.
### Возвращаемое значение

true, если viewport является частью группы; иначе false.
## void loadEasyBlendSettings ( const char * filepath )

Загружает настройки из файла настроек EasyBlend.
### Аргументы

- *const char ** **filepath** - Путь к файлу настроек EasyBlend.

## void removeEasyblendSetup ( )

Удаляет настройки EasyBlend.
## WarpGridData * getWarpGrid ( )

Возвращает данные warp grid.
### Возвращаемое значение

Экземпляр [WarpGridData class](../../../../api/library/plugins/spidervision/class.warpgriddata_cpp.md), хранящий данные warp grid.
## BlendZonesData * getBlendZones ( )

Возвращает данные зон смешивания.
### Возвращаемое значение

Экземпляр [BlendZonesData class](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md), хранящий данные зон смешивания.
## MasksData * getMasks ( )

Возвращает данные масок.
### Возвращаемое значение

Экземпляр [MasksData class](../../../../api/library/plugins/spidervision/class.masksdata_cpp.md), хранящий данные масок.
## ColorCorrectionData * getColorCorrection ( )

Возвращает данные цветокоррекции.
### Возвращаемое значение

Экземпляр [ColorCorrectionData class](../../../../api/library/plugins/spidervision/class.colorcorrectiondata_cpp.md), хранящий данные цветокоррекции.
## DebugData * getDebug ( )

Возвращает отладочные данные.
### Возвращаемое значение

Экземпляр [DebugData class](../../../../api/library/plugins/spidervision/class.debugdata_cpp.md), хранящий отладочные данные.
## EasyBlendData * getEasyblendData ( )

Возвращает данные EasyBlend.
### Возвращаемое значение

Экземпляр [EasyBlendData class](../../../../api/library/plugins/spidervision/class.easyblenddata_cpp.md), хранящий данные EasyBlend.
## void saveXml ( const Ptr < Xml > & xml )

Сохраняет данные viewport в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные.

## bool restoreXml ( const Ptr < Xml > & xml )

Загружает данные viewport из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.

### Возвращаемое значение

true, если данные успешно загружены; иначе false.
## void save ( const Ptr < Stream > & stream )

Сохраняет данные viewport в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restore ( const Ptr < Stream > & stream )

Загружает данные viewport из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.

## void saveBase ( const Ptr < Stream > & stream )

Сохраняет данные viewport в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restoreBase ( const Ptr < Stream > & stream )

Загружает данные viewport из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.

## void copy ( const ViewportData & data )

Копирует текущие данные viewport в указанный экземпляр класса ViewportData.
### Аргументы

- *const [ViewportData](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md) &* **data** - Данные viewport.
