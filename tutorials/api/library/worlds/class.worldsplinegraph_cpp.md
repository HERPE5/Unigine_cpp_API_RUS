# Unigine.WorldSplineGraph Class (CPP)

**Header:** #include <UnigineWorlds.h>

**Inherits from:** Node


> **Warning:** Эта возможность является экспериментальной и не рекомендуется для использования в продакшене.


Этот класс используется для генерации указанных узлов (называемых **исходными узлами**) вдоль [spline graph](../../../objects/worlds/world_spline_graph/index.md).


Система 3D-сплайнов UNIGINE имеет широкий спектр применений, в частности процедурную генерацию контента (реки, дороги, трубопроводы и т.д.).


![](../../../code/formats/spline.png)


Граф сплайна определяется набором [points](../../../api/library/worlds/class.splinepoint_cpp.md) **p0, p 1, ... p n** и набором сегментов (кубических сплайнов Безье), соединяющих некоторые или все эти точки.


Каждый [**segment**](../../../api/library/worlds/class.splinesegment_cpp.md) определяется индексами начальной (**pSTART**) и конечной (**pEND**) точек и координатами касательных векторов в этих точках, которые определяют форму сегмента (**tSTART** и **tEND** соответственно).


Дополнительно для каждой точки сегмента хранятся координаты **вектора "up"**. Этот вектор можно указать для определения ориентации геометрии или объектов, которые могут быть [stretched or tiled along the segments](#intro) графа сплайна. По умолчанию этот вектор параллелен оси **Z**. Вектор "up" не влияет на форму сегмента сплайна.


Можно получить интерполированное значение для любой точки, принадлежащей сегменту, это можно использовать для различных целей (например, для изменения профиля дороги). Интерполированный вектор "up" можно вычислить следующим образом (псевдокод):

```cpp
vec3 lerpUpVector(vec3 start_up, vec3 end_up, float t) const
{
	float angle = acos(dot(start_up, end_up)) * RAD2DEG;
	vec3 rotation_axis = cross(start_up, end_up);

	return rotateAxisAngle(rotation_axis, angle * t) * start_up;
}

```


Граф сплайна мира состоит из сегментов и имеет список исходных узлов (в настоящее время [ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md), [ObjectMeshSkinnedLegacy](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md) и [DecalProj](../../../api/library/decals/class.decalproj_cpp.md)), которые могут быть размещены в точках и вдоль сегментов графа сплайна. Каждая точка и сегмент могут иметь один или несколько назначенных исходных узлов. В сцену можно добавить произвольное количество узлов WorldSplineGraph.


WorldSplineGraph обладает следующими возможностями:

- Точки графа сплайна управляются через класс [SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md).
- Сегменты графа сплайна управляются через класс [SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md).
- Поддерживаются 3 режима:

  - **растяжение (stretching)**: исходные узлы растягиваются вдоль сегмента сплайна.
  - **тайлинг (tiling)**: исходные узлы дублируются вдоль сегмента сплайна.
  - **адаптивный (adaptive)** - представляет собой комбинацию первых двух: исходные узлы дублируются вдоль сегмента сплайна, но длина каждого узла (растяжение) определяется кривизной соответствующей части сегмента. Таким образом, длинные узлы размещаются вдоль прямых частей сегментов, а короткие - вдоль изогнутых, обеспечивая разумный баланс между правдоподобным видом и производительностью.
- Выбор оси направления для растяжения/тайлинга исходных узлов.


### См. также


- Статья про объект [World Spline Graph](../../../objects/worlds/world_spline_graph/index.md)
- Пример на C++
- Примеры на UnigineScript:

  -
  -


## WorldSplineGraph Class

### Методы класса

## int getNumSplineSegments () const

Возвращает текущее общее количество [spline segments](../../../api/library/worlds/class.splinesegment_cpp.md) в графе сплайна мира.
### Возвращаемое значение

Текущее количество сегментов в графе сплайна мира.
## int getNumSplinePoints () const

Возвращает текущее общее количество [spline points](../../../api/library/worlds/class.splinepoint_cpp.md) в графе сплайна мира.
### Возвращаемое значение

Текущее количество точек сплайна.
## bool isCurved () const

Возвращает текущее значение, указывающее, является ли граф сплайна мира изогнутым.
### Возвращаемое значение

**true**, если граф сплайна мира изогнутый; иначе **false**.
## Event<const Ptr < WorldSplineGraph > &> getEventRebuildingFinished () const

Событие, генерируемое после перестроения графа сплайна мира. Граф сплайна мира использует отложенное перестроение. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WorldSplineGraph> & **spline_graph**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события RebuildingFinished
void rebuildingfinished_event_handler(const Ptr<WorldSplineGraph> & spline_graph)
{
	Log::message("\Обработка события RebuildingFinished\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections rebuildingfinished_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventRebuildingFinished().connect(rebuildingfinished_event_connections, rebuildingfinished_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventRebuildingFinished().connect(rebuildingfinished_event_connections, [](const Ptr<WorldSplineGraph> & spline_graph) {
		Log::message("\Обработка события RebuildingFinished (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
rebuildingfinished_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection rebuildingfinished_event_connection;

// подписываемся на событие RebuildingFinished с функцией-обработчиком, сохраняя соединение
publisher->getEventRebuildingFinished().connect(rebuildingfinished_event_connection, rebuildingfinished_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
rebuildingfinished_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
rebuildingfinished_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие RebuildingFinished через соединение
rebuildingfinished_event_connection.disconnect();

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

	// Обработчик события RebuildingFinished, реализованный как член класса
	void event_handler(const Ptr<WorldSplineGraph> & spline_graph)
	{
		Log::message("\Обработка события RebuildingFinished\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventRebuildingFinished().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId rebuildingfinished_handler_id;

// подписываемся на событие RebuildingFinished с лямбда-обработчиком, сохраняя идентификатор соединения
rebuildingfinished_handler_id = publisher->getEventRebuildingFinished().connect(e_connections, [](const Ptr<WorldSplineGraph> & spline_graph) {
		Log::message("\Обработка события RebuildingFinished (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventRebuildingFinished().disconnect(rebuildingfinished_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий RebuildingFinished при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventRebuildingFinished().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventRebuildingFinished().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < WorldSplineGraph > &, const Ptr < SplineSegment > &> getEventSegmentRemoved () const

event triggered when a segment of the world spline graph is removed. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WorldSplineGraph> & **spline_graph**, const Ptr<SplineSegment> & **segment**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события SegmentRemoved
void segmentremoved_event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment)
{
	Log::message("\Обработка события SegmentRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections segmentremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventSegmentRemoved().connect(segmentremoved_event_connections, segmentremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventSegmentRemoved().connect(segmentremoved_event_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment) {
		Log::message("\Обработка события SegmentRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
segmentremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection segmentremoved_event_connection;

// подписываемся на событие SegmentRemoved с функцией-обработчиком, сохраняя соединение
publisher->getEventSegmentRemoved().connect(segmentremoved_event_connection, segmentremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
segmentremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
segmentremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие SegmentRemoved через соединение
segmentremoved_event_connection.disconnect();

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

	// Обработчик события SegmentRemoved, реализованный как член класса
	void event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment)
	{
		Log::message("\Обработка события SegmentRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventSegmentRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId segmentremoved_handler_id;

// подписываемся на событие SegmentRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
segmentremoved_handler_id = publisher->getEventSegmentRemoved().connect(e_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment) {
		Log::message("\Обработка события SegmentRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventSegmentRemoved().disconnect(segmentremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий SegmentRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventSegmentRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventSegmentRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < WorldSplineGraph > &, const Ptr < SplineSegment > &> getEventSegmentChanged () const

event triggered when a segment of the world spline graph is modified. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WorldSplineGraph> & **spline_graph**, const Ptr<SplineSegment> & **segment**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события SegmentChanged
void segmentchanged_event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment)
{
	Log::message("\Обработка события SegmentChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections segmentchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventSegmentChanged().connect(segmentchanged_event_connections, segmentchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventSegmentChanged().connect(segmentchanged_event_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment) {
		Log::message("\Обработка события SegmentChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
segmentchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection segmentchanged_event_connection;

// подписываемся на событие SegmentChanged с функцией-обработчиком, сохраняя соединение
publisher->getEventSegmentChanged().connect(segmentchanged_event_connection, segmentchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
segmentchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
segmentchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие SegmentChanged через соединение
segmentchanged_event_connection.disconnect();

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

	// Обработчик события SegmentChanged, реализованный как член класса
	void event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment)
	{
		Log::message("\Обработка события SegmentChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventSegmentChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId segmentchanged_handler_id;

// подписываемся на событие SegmentChanged с лямбда-обработчиком, сохраняя идентификатор соединения
segmentchanged_handler_id = publisher->getEventSegmentChanged().connect(e_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment) {
		Log::message("\Обработка события SegmentChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventSegmentChanged().disconnect(segmentchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий SegmentChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventSegmentChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventSegmentChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < WorldSplineGraph > &, const Ptr < SplineSegment > &> getEventSegmentAdded () const

event triggered when a segment is added to the world spline graph. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WorldSplineGraph> & **spline_graph**, const Ptr<SplineSegment> & **segment**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события SegmentAdded
void segmentadded_event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment)
{
	Log::message("\Обработка события SegmentAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections segmentadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventSegmentAdded().connect(segmentadded_event_connections, segmentadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventSegmentAdded().connect(segmentadded_event_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment) {
		Log::message("\Обработка события SegmentAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
segmentadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection segmentadded_event_connection;

// подписываемся на событие SegmentAdded с функцией-обработчиком, сохраняя соединение
publisher->getEventSegmentAdded().connect(segmentadded_event_connection, segmentadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
segmentadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
segmentadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие SegmentAdded через соединение
segmentadded_event_connection.disconnect();

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

	// Обработчик события SegmentAdded, реализованный как член класса
	void event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment)
	{
		Log::message("\Обработка события SegmentAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventSegmentAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId segmentadded_handler_id;

// подписываемся на событие SegmentAdded с лямбда-обработчиком, сохраняя идентификатор соединения
segmentadded_handler_id = publisher->getEventSegmentAdded().connect(e_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplineSegment> & segment) {
		Log::message("\Обработка события SegmentAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventSegmentAdded().disconnect(segmentadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий SegmentAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventSegmentAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventSegmentAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < WorldSplineGraph > &, const Ptr < SplinePoint > &> getEventPointRemoved () const

event triggered when a point of the world spline graph is removed. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WorldSplineGraph> & **spline_graph**, const Ptr<SplinePoint> & **point**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PointRemoved
void pointremoved_event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point)
{
	Log::message("\Обработка события PointRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections pointremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventPointRemoved().connect(pointremoved_event_connections, pointremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventPointRemoved().connect(pointremoved_event_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point) {
		Log::message("\Обработка события PointRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
pointremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection pointremoved_event_connection;

// подписываемся на событие PointRemoved с функцией-обработчиком, сохраняя соединение
publisher->getEventPointRemoved().connect(pointremoved_event_connection, pointremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
pointremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
pointremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PointRemoved через соединение
pointremoved_event_connection.disconnect();

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

	// Обработчик события PointRemoved, реализованный как член класса
	void event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point)
	{
		Log::message("\Обработка события PointRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventPointRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId pointremoved_handler_id;

// подписываемся на событие PointRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
pointremoved_handler_id = publisher->getEventPointRemoved().connect(e_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point) {
		Log::message("\Обработка события PointRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventPointRemoved().disconnect(pointremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PointRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventPointRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventPointRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < WorldSplineGraph > &, const Ptr < SplinePoint > &> getEventPointChanged () const

event triggered when a point of the world spline graph is modified. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WorldSplineGraph> & **spline_graph**, const Ptr<SplinePoint> & **point**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PointChanged
void pointchanged_event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point)
{
	Log::message("\Обработка события PointChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections pointchanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventPointChanged().connect(pointchanged_event_connections, pointchanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventPointChanged().connect(pointchanged_event_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point) {
		Log::message("\Обработка события PointChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
pointchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection pointchanged_event_connection;

// подписываемся на событие PointChanged с функцией-обработчиком, сохраняя соединение
publisher->getEventPointChanged().connect(pointchanged_event_connection, pointchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
pointchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
pointchanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PointChanged через соединение
pointchanged_event_connection.disconnect();

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

	// Обработчик события PointChanged, реализованный как член класса
	void event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point)
	{
		Log::message("\Обработка события PointChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventPointChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId pointchanged_handler_id;

// подписываемся на событие PointChanged с лямбда-обработчиком, сохраняя идентификатор соединения
pointchanged_handler_id = publisher->getEventPointChanged().connect(e_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point) {
		Log::message("\Обработка события PointChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventPointChanged().disconnect(pointchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PointChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventPointChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventPointChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < WorldSplineGraph > &, const Ptr < SplinePoint > &> getEventPointAdded () const

event triggered when a point is added to the world spline graph. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<WorldSplineGraph> & **spline_graph**, const Ptr<SplinePoint> & **point**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PointAdded
void pointadded_event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point)
{
	Log::message("\Обработка события PointAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections pointadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventPointAdded().connect(pointadded_event_connections, pointadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventPointAdded().connect(pointadded_event_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point) {
		Log::message("\Обработка события PointAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
pointadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection pointadded_event_connection;

// подписываемся на событие PointAdded с функцией-обработчиком, сохраняя соединение
publisher->getEventPointAdded().connect(pointadded_event_connection, pointadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
pointadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
pointadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PointAdded через соединение
pointadded_event_connection.disconnect();

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

	// Обработчик события PointAdded, реализованный как член класса
	void event_handler(const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point)
	{
		Log::message("\Обработка события PointAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventPointAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId pointadded_handler_id;

// подписываемся на событие PointAdded с лямбда-обработчиком, сохраняя идентификатор соединения
pointadded_handler_id = publisher->getEventPointAdded().connect(e_connections, [](const Ptr<WorldSplineGraph> & spline_graph,  const Ptr<SplinePoint> & point) {
		Log::message("\Обработка события PointAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventPointAdded().disconnect(pointadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PointAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventPointAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventPointAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static WorldSplineGraphPtr create ( )

Конструктор по умолчанию. Создаёт пустой граф сплайна мира.
## static WorldSplineGraphPtr create ( const char * name )

Конструктор. Создаёт пустой граф сплайна мира с заданным именем.
### Аргументы

- *const char ** **name** - Имя графа сплайна мира.

## void setSplineGraphName ( const char * name , bool force_load = 0 )

Задаёт имя графа сплайна мира.
### Аргументы

- *const char ** **name** - Имя графа сплайна мира.
- *bool* **force_load** - true, чтобы немедленно загрузить граф сплайна мира из файла, false, чтобы обновить только имя графа сплайна мира.

## const char * getSplineGraphName ( ) const

Возвращает имя графа сплайна мира.
### Возвращаемое значение

Имя графа сплайна мира.
## void loadSegmentNodes ( int segment_index = -1 )

Немедленно загружает исходные узлы, назначенные указанному сегменту сплайна.
### Аргументы

- *int* **segment_index** - Индекс сегмента. Если индекс сегмента не указан, метод загружает исходные узлы, назначенные всем сегментам.

## void clear ( )

Очищает граф сплайна мира.
## void makeCurved ( )

Изгибает граф сплайна мира с использованием его геодезической опорной точки. Файл сплайна сохраняется по завершении операции изгибания.
> **Notice:** Граф сплайна мира должен быть дочерним узлом [Geodetic Pivot](../../../api/library/geodetics/class.geodeticpivot_cpp.md).


## void makeFlat ( )

Выравнивает граф сплайна мира с использованием его геодезической опорной точки. Файл сплайна сохраняется по завершении операции выравнивания.
> **Notice:** Граф сплайна мира должен быть дочерним узлом [Geodetic Pivot](../../../api/library/geodetics/class.geodeticpivot_cpp.md).


## bool load ( const char * name )

Загружает граф сплайна из указанного XML-файла.
### Аргументы

- *const char ** **name** - Имя XML-файла, из которого загружается граф сплайна.

### Возвращаемое значение

true, если граф сплайна успешно загружен; иначе false.
## bool save ( const char * name )

Сохраняет граф сплайна в указанный XML-файл.
### Аргументы

- *const char ** **name** - Имя XML-файла, в который сохраняется граф сплайна.

### Возвращаемое значение

true, если граф сплайна успешно сохранён; иначе false.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [WorldSplineGraph](../../../api/library/nodes/class.node_cpp.md#WORLD_SPLINE_GRAPH).
## void getSegmentNodeMesh ( const Ptr < Mesh > & mesh , const Ptr < SplineSegment > & segment , int node_index , bool bake_transform = 0 )

Получает меш, используемый узлом с указанным индексом, размещённым вдоль указанного [spline segment](../../../api/library/worlds/class.splinesegment_cpp.md), и помещает его в указанный целевой экземпляр [Mesh](../../../api/library/rendering/class.mesh_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Целевой экземпляр меша, в который помещается полученный меш.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md)> &* **segment** - [Spline segment](../../../api/library/worlds/class.splinesegment_cpp.md), для которого нужно вернуть меш.
- *int* **node_index** - Номер экземпляра узла, размещённого вдоль сегмента сплайна.
- *bool* **bake_transform** - true, чтобы использовать запечённую трансформацию меша, false - чтобы использовать значение по умолчанию (меш будет размещён в начале координат). Значение по умолчанию - false.

## void getPointNodeMesh ( const Ptr < Mesh > & mesh , const Ptr < SplinePoint > & point , int node_index , bool bake_transform = false )

Экспортирует меш с указанным индексом, размещённый в указанной [spline point](../../../api/library/worlds/class.splinepoint_cpp.md), в указанный целевой меш.
> **Notice:** Из-за особенностей меша будут визуальные артефакты, связанные с точностью float, если экспортируемый узел находится очень далеко от начала координат (примерно от 10 000 м и далее). В этом случае рекомендуется экспортировать его без запекания трансформации.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Целевой меш для хранения нужного меша, размещённого в указанной точке сплайна.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **point** - Точка сплайна, для которой нужно получить меш.
- *int* **node_index** - Номер нужного узла в ряду узлов, размещённых в указанной точке, в диапазоне от 0 до [total number of nodes placed at the point](../../../api/library/worlds/class.splinepoint_cpp.md#getNumNodes_int). > **Notice:** Узел должен быть [ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md) или [ObjectMeshSkinnedLegacy](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md), иначе возникнет ошибка.
- *bool* **bake_transform** - Флаг *Bake Transform*: true - экспортировать меш с сохранением текущих координат (может быть полезно при разделении больших объектов *WorldSplineGraph* для сохранения относительных позиций мешей); или false - сбросить позицию экспортируемого меша в начало координат (0,0,0) с нулевым поворотом.

## Ptr < SplinePoint > createSplinePoint ( const Math:: Vec3 & position )

Создаёт новую [spline point](../../../api/library/worlds/class.splinepoint_cpp.md) с указанными параметрами и присоединяет её к графу сплайна мира.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Координаты позиции новой точки сплайна.

### Возвращаемое значение

Новая [Spline point](../../../api/library/worlds/class.splinepoint_cpp.md).
## void removeSplinePoint ( const Ptr < SplinePoint > & point , bool merge = 0 )

Удаляет указанную точку сплайна из графа сплайна мира. Можно задать флаг *merge* для объединения [spline segments](../../../api/library/worlds/class.splinesegment_cpp.md), использующих эту точку в качестве начальной и конечной.
> **Notice:** Объединение сегментов доступно только тогда, когда удаляемая точка используется двумя сегментами, иначе флаг *merge* игнорируется, и все сегменты, использующие эту точку, также удаляются.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **point** - [Spline point](../../../api/library/worlds/class.splinepoint_cpp.md) для удаления.
- *bool* **merge** - true, чтобы объединить сегменты сплайна, использующие эту точку в качестве начальной и конечной, false, чтобы удалить все сегменты, использующие эту точку. Значение по умолчанию - false.

## void getSplinePoints ( Vector < Ptr < SplinePoint >> & OUT_points ) const

Возвращает список всех точек графа сплайна мира и помещает их в указанный вектор элементов [SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md).
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)>> &* **OUT_points** - Вектор для хранения списка всех точек графа сплайна мира. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Ptr < SplineSegment > createSplineSegment ( const Ptr < SplinePoint > & start_point , const Math:: vec3 & start_tangent , const Math:: vec3 & start_up , const Ptr < SplinePoint > & end_point , const Math:: vec3 & end_tangent , const Math:: vec3 & end_up )

Создаёт новый [spline segment](../../../api/library/worlds/class.splinesegment_cpp.md) с указанными параметрами и присоединяет его к графу сплайна мира.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **start_point** - Начальная [point](../../../api/library/worlds/class.splinepoint_cpp.md) сегмента сплайна.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **start_tangent** - Координаты касательной для начальной точки сегмента сплайна.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **start_up** - Координаты ["up" vector](#up) для начальной точки сегмента сплайна.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **end_point** - Конечная [point](../../../api/library/worlds/class.splinepoint_cpp.md) сегмента.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **end_tangent** - Координаты касательной для конечной точки сегмента сплайна.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **end_up** - Координаты ["up" vector](#up) для конечной точки сегмента сплайна.

### Возвращаемое значение

Новый [spline segment](../../../api/library/worlds/class.splinesegment_cpp.md), соединяющий две указанные точки.
## void removeSplineSegment ( const Ptr < SplineSegment > & segment , bool with_points = 0 )

Удаляет указанный сегмент сплайна из графа сплайна мира. Можно задать флаг *with_points* для удаления сегмента вместе с его начальной и конечной точками.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md)> &* **segment** - [Spline segment](../../../api/library/worlds/class.splinesegment_cpp.md) для удаления.
- *bool* **with_points** - true, чтобы удалить сегмент вместе с его начальной и конечной точками, false, чтобы сохранить точки. Значение по умолчанию - false.

## void getSplineSegments ( Vector < Ptr < SplineSegment >> & OUT_segments ) const

Возвращает список всех сегментов графа сплайна мира и помещает их в указанный вектор элементов [SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md).
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md)>> &* **OUT_segments** - Вектор для хранения списка всех сегментов графа сплайна мира. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void rebuild ( int try_force = 0 )

Перестраивает граф сплайна мира. Этот метод следует вызывать после внесения любых изменений в сегменты сплайна (режим и т.д.), позиции точек, касательные или векторы "up", а также после изменения назначений [source node](#source_node) и/или других параметров (тайлинг UV, зазор и т.д.)
### Аргументы

- *int* **try_force** - Флаг принудительного перестроения: установите 1, чтобы попытаться принудительно перестроить граф сплайна мира.

## int isRebuilding ( ) const

Возвращает значение, указывающее, перестраивается ли граф сплайна мира в данный момент. Граф сплайна мира использует отложенное перестроение.
### Возвращаемое значение

1, если граф сплайна мира в данный момент перестраивается; иначе 0.
## void splitSplineSegment ( const Ptr < SplineSegment > & segment , float new_point_t )

Разделяет указанный [spline segment](../../../api/library/worlds/class.splinesegment_cpp.md) на две части, вставляя новую точку, размещённую в параметрически заданной позиции на оси T (оси времени) в диапазоне **[0.0f, 1.0f]** от начальной точки сегмента.
![](../math/cubic_bezier.gif)


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md)> &* **segment** - Сегмент сплайна для разделения.
- *float* **new_point_t** - Координата точки разделения сегмента вдоль горизонтальной оси *T* (времени) в диапазоне **[0.0f, 1.0f]**.

## void breakSplinePoint ( const Ptr < SplinePoint > & point )

Разбивает указанную [spline point](../../../api/library/worlds/class.splinepoint_cpp.md), общую для нескольких [spline segments](../../../api/library/worlds/class.splinesegment_cpp.md), на набор отдельных точек, так что каждый сегмент получает собственную точку.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **point** - Точка сплайна для разбиения. > **Notice:** Точка должна быть общей как минимум для 2 сегментов.

## void weldSplinePoints ( Vector < Ptr < SplinePoint >> & OUT_points )

Объединяет все [spline points](../../../api/library/worlds/class.splinepoint_cpp.md), указанные в списке, в одну, так что эта точка становится общей для всех сегментов сплайна, имеющих указанные точки в качестве начальных или конечных.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)>> &* **OUT_points** - Список точек сплайна для объединения в одну. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## bool isLinked ( const Ptr < SplinePoint > & point ) const

Возвращает значение, указывающее, связана ли указанная [Spline point](../../../api/library/worlds/class.splinepoint_cpp.md) с каким-либо [spline segment](../../../api/library/worlds/class.splinesegment_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **point** - Точка сплайна для проверки.

### Возвращаемое значение

true, если указанная точка сплайна связана с каким-либо сегментом сплайна; иначе false.
