# Класс Unigine::World (CPP)

**Заголовочный файл:** #include <UnigineWorld.h>

> **Notice:** Этот класс является одиночкой (singleton).


Этот класс предоставляет функциональность для [world script](../../../code/fundamentals/execution_sequence/app_logic_system.md#world_logic). Он содержит методы, необходимые для загрузки мира со всеми его узлами, управления пространственным деревом и обработки коллизий и пересечений узлов.


Загрузка узлов по требованию управляется через [AsyncQueue Class](../../../api/library/filesystem/class.asyncqueue_cpp.md).


> **Notice:** Методы C++, выполняющие функции скрипта редактора, описаны в справочнике по [Engine class](../../../api/library/engine/class.engine_cpp.md).


### См. также


- [AsyncQueue Class](../../../api/library/filesystem/class.asyncqueue_cpp.md) для управления загрузкой узлов и других ресурсов по требованию.
- Статья [Intersections](../../../code/usage/intersections/index_cpp.md), демонстрирующая, как использовать функции, связанные с пересечениями.


## Класс World

### Перечисления

## MOVING_IMMOVABLE_NODES_MODE

| Имя | Описание |
|---|---|
| **MOVING_IMMOVABLE_NODES_MODE_BAN** = 0 | Перемещение узлов с флагом Immovable запрещено. |
| **MOVING_IMMOVABLE_NODES_MODE_WARNING** = 1 | Перемещение узлов с флагом Immovable сопровождается предупреждением в консоли. |
| **MOVING_IMMOVABLE_NODES_MODE_ALLOW** = 2 | Перемещение узлов с флагом Immovable разрешено. |

### Методы класса

## void setUnpackNodeReferences ( bool references )

Устанавливает новое значение, указывающее, включена ли автоматическая распаковка [node references](../../../api/library/nodes/class.nodereference_cpp.md) во время выполнения. Эта опция может использоваться для упрощения управления иерархией: когда она включена, все узлы, содержащиеся в ссылках на узлы, присутствуют в иерархии мира. Когда она отключена, вам приходится проверять иерархию каждой ссылки на узел индивидуально (например, чтобы найти количество дочерних элементов или управлять некоторыми из них). Содержимое узлов *NodeReference* распаковывается только во время выполнения и не влияет на ваши файлы `*.world` и `*.node`. Таким образом, вы можете использовать все преимущества ссылок на узлы при построении миров в UnigineEditor и управлять чёткой и понятной иерархией во время выполнения.
> **Notice:** Эта опция доступна только через код, может быть включена в [System Script](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) и работает для всех миров, используемых в вашем проекте.


> **Notice:** **Автораспаковка включена** в проектах на C# по умолчанию.


### Аргументы

- *bool* **references** - Установите **true**, чтобы включить автоматическую распаковку ссылок на узлы во время выполнения; **false** - чтобы отключить её.

## bool isUnpackNodeReferences () const

Возвращает текущее значение, указывающее, включена ли автоматическая распаковка [node references](../../../api/library/nodes/class.nodereference_cpp.md) во время выполнения. Эта опция может использоваться для упрощения управления иерархией: когда она включена, все узлы, содержащиеся в ссылках на узлы, присутствуют в иерархии мира. Когда она отключена, вам приходится проверять иерархию каждой ссылки на узел индивидуально (например, чтобы найти количество дочерних элементов или управлять некоторыми из них). Содержимое узлов *NodeReference* распаковывается только во время выполнения и не влияет на ваши файлы `*.world` и `*.node`. Таким образом, вы можете использовать все преимущества ссылок на узлы при построении миров в UnigineEditor и управлять чёткой и понятной иерархией во время выполнения.
> **Notice:** Эта опция доступна только через код, может быть включена в [System Script](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) и работает для всех миров, используемых в вашем проекте.


> **Notice:** **Автораспаковка включена** в проектах на C# по умолчанию.


### Возвращаемое значение

**true**, если автоматическая распаковка ссылок на узлы во время выполнения включена; иначе **false**.
## void setAutoReloadNodeReferences ( bool references )

Устанавливает новое значение, указывающее, включена ли автоматическая перезагрузка ссылок на узлы. Если включено, все узлы [NodeReference](../../../api/library/nodes/class.nodereference_cpp.md) будут перезагружать свои файлы `*.node` при вызове метода [saveNode()](#saveNode_cstr_Node_int_int).
> **Notice:** Эту опцию можно использовать, если вы изменяете и сохраняете ссылочные узлы во время выполнения. В противном случае вам придётся вручную обновлять указатели для всех [NodeReferences](../../../api/library/nodes/class.nodereference_cpp.md), ссылающихся на изменённый узел.


### Аргументы

- *bool* **references** - Установите **true**, чтобы включить автоматическую перезагрузку ссылок на узлы; **false** - чтобы отключить её.

## bool isAutoReloadNodeReferences () const

Возвращает текущее значение, указывающее, включена ли автоматическая перезагрузка ссылок на узлы. Если включено, все узлы [NodeReference](../../../api/library/nodes/class.nodereference_cpp.md) будут перезагружать свои файлы `*.node` при вызове метода [saveNode()](#saveNode_cstr_Node_int_int).
> **Notice:** Эту опцию можно использовать, если вы изменяете и сохраняете ссылочные узлы во время выполнения. В противном случае вам придётся вручную обновлять указатели для всех [NodeReferences](../../../api/library/nodes/class.nodereference_cpp.md), ссылающихся на изменённый узел.


### Возвращаемое значение

**true**, если автоматическая перезагрузка ссылок на узлы включена; иначе **false**.
## void setUpdateGridSize ( float size )

Устанавливает новый размер сетки, используемой для обновления пространственного дерева. Значение по умолчанию является средним и может быть скорректировано при необходимости в зависимости от сцены.
### Аргументы

- *float* **size** - Размер сетки, в единицах. Значение по умолчанию — 1000 единиц.

## float getUpdateGridSize () const

Возвращает текущий размер сетки, используемой для обновления пространственного дерева. Значение по умолчанию является средним и может быть скорректировано при необходимости в зависимости от сцены.
### Возвращаемое значение

Текущий размер сетки, в единицах. Значение по умолчанию — 1000 единиц.
## void setDistance ( float distance )

Устанавливает новое расстояние, на котором (и далее) ничего не будет отображаться или симулироваться.
### Аргументы

- *float* **distance** - Расстояние, на котором (и далее) ничего не будет отображаться или симулироваться, в единицах.

## float getDistance () const

Возвращает текущее расстояние, на котором (и далее) ничего не будет отображаться или симулироваться.
### Возвращаемое значение

Текущее расстояние, на котором (и далее) ничего не будет отображаться или симулироваться, в единицах.
## void setBudget ( float budget )

Устанавливает новое значение бюджета генерации мира для травы и объектов подлеска. Новые объекты не создаются, когда время превышает бюджет.
### Аргументы

- *float* **budget** - Значение бюджета в секундах. Значение по умолчанию — 1/60.

## float getBudget () const

Возвращает текущее значение бюджета генерации мира для травы и объектов подлеска. Новые объекты не создаются, когда время превышает бюджет.
### Возвращаемое значение

Текущее значение бюджета в секундах. Значение по умолчанию — 1/60.
## bool isLoaded () const

Возвращает текущее значение, указывающее, полностью ли загружен текущий мир.
### Возвращаемое значение

**true**, если мир полностью загружен; иначе **false**.
## void setScriptName ( const char * name )

Устанавливает новое имя файла [world script](../../../principles/world_structure/index.md) `*.usc`.
### Аргументы

- *const char ** **name** - Имя файла [world script](../../../principles/world_structure/index.md) `*.usc`.

## const char * getScriptName () const

Возвращает текущее имя файла [world script](../../../principles/world_structure/index.md) `*.usc`.
### Возвращаемое значение

Текущее имя файла [world script](../../../principles/world_structure/index.md) `*.usc`.
## void setPath ( const char * path )

Устанавливает новый путь к [`*.world`-file](../../../principles/world_structure/index.md), в котором хранится мир.
### Аргументы

- *const char ** **path** - Путь к [`*.world`-file](../../../principles/world_structure/index.md), в котором хранится мир.

## const char * getPath () const

Возвращает текущий путь к [`*.world`-file](../../../principles/world_structure/index.md), в котором хранится мир.
### Возвращаемое значение

Текущий путь к [`*.world`-file](../../../principles/world_structure/index.md), в котором хранится мир.
## void setScriptExecute ( bool execute )

Устанавливает новое значение, указывающее, должен ли выполняться скрипт мира (файл `*.usc`), связанный с миром.
### Аргументы

- *bool* **execute** - Установите **true**, чтобы включить загрузку скрипта логики, связанного с миром, вместе с ним; **false** - чтобы отключить это.

## bool isScriptExecute () const

Возвращает текущее значение, указывающее, должен ли выполняться скрипт мира (файл `*.usc`), связанный с миром.
### Возвращаемое значение

**true**, если скрипт логики, связанный с миром, должен загружаться вместе с ним; иначе **false**.
## void setPhysicsSettings ( const char * settings )

Устанавливает новое имя файла `*.physics`, содержащего [physics settings](../../../editor2/settings/physics_global/index.md) по умолчанию, используемые миром.
### Аргументы

- *const char ** **settings** - Имя файла `*.physics`, содержащего [physics settings](../../../editor2/settings/physics_global/index.md) по умолчанию, используемые миром.

## const char * getPhysicsSettings () const

Возвращает текущее имя файла `*.physics`, содержащего [physics settings](../../../editor2/settings/physics_global/index.md) по умолчанию, используемые миром.
### Возвращаемое значение

Текущее имя файла `*.physics`, содержащего [physics settings](../../../editor2/settings/physics_global/index.md) по умолчанию, используемые миром.
## void setSoundSettings ( const char * settings )

Устанавливает новое имя файла `*.sound`, содержащего [sound settings](../../../editor2/settings/sound_global/index.md) по умолчанию, используемые миром.
### Аргументы

- *const char ** **settings** - Имя файла `*.sound`, содержащего [sound settings](../../../editor2/settings/sound_global/index.md) по умолчанию, используемые миром.

## const char * getSoundSettings () const

Возвращает текущее имя файла `*.sound`, содержащего [sound settings](../../../editor2/settings/sound_global/index.md) по умолчанию, используемые миром.
### Возвращаемое значение

Текущее имя файла `*.sound`, содержащего [sound settings](../../../editor2/settings/sound_global/index.md) по умолчанию, используемые миром.
## void setRenderSettings ( const char * settings )

Устанавливает новое имя файла `*.render`, содержащего [render settings](../../../editor2/settings/render_settings/index.md) по умолчанию, используемые миром.
### Аргументы

- *const char ** **settings** - Имя файла `*.render`, содержащего [render settings](../../../editor2/settings/render_settings/index.md) по умолчанию, используемые миром.

## const char * getRenderSettings () const

Возвращает текущее имя файла `*.render`, содержащего [render settings](../../../editor2/settings/render_settings/index.md) по умолчанию, используемые миром.
### Возвращаемое значение

Текущее имя файла `*.render`, содержащего [render settings](../../../editor2/settings/render_settings/index.md) по умолчанию, используемые миром.
## const char * getLoadWorldRequestPath () const

Возвращает текущий путь к миру, который будет загружен.
### Возвращаемое значение

Текущий путь к миру, который будет загружен.
## bool isLoadWorldRequested () const

Возвращает текущее значение, указывающее, будет ли загружен другой мир в следующем кадре.
### Возвращаемое значение

**true**, если другой мир будет загружен в следующем кадре; иначе **false**.
## void setMovingImmovableNodeMode ( World::MOVING_IMMOVABLE_NODES_MODE mode )

***Консольная команда*:**`world_moving_immovable_node_mode`Устанавливает новый режим обработки попыток переместить узлы с включённым флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)*.
> **Notice:** Обратите внимание, что есть два случая, когда вы можете отключить предупреждения и разрешить перемещение узлов *Immovable*:
> - Во время выполнения для процедурной генерации уровней. Это может вызвать некоторые задержки, но не сильно повлияет на производительность. По завершении процесса генерации вам следует снова включить предупреждения.
> - При инициализации мира — это изменит время загрузки мира, но не повлияет на общую производительность.


### Аргументы

- *[World::MOVING_IMMOVABLE_NODES_MODE](../../../api/library/engine/class.world_cpp.md#MOVING_IMMOVABLE_NODES_MODE)* **mode** - Режим обработки попыток переместить узлы с включённым флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)*. Одно из следующих значений:

  - **0** - перемещение узлов с флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)* запрещено.
  - **1** - перемещение узлов с флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)* сопровождается предупреждением в консоли. (по умолчанию)
  - **2** - перемещение узлов с флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)* разрешено (предупреждения не отображаются).

## World::MOVING_IMMOVABLE_NODES_MODE getMovingImmovableNodeMode () const

***Консольная команда*:**`world_moving_immovable_node_mode`Возвращает текущий режим обработки попыток переместить узлы с включённым флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)*.
> **Notice:** Обратите внимание, что есть два случая, когда вы можете отключить предупреждения и разрешить перемещение узлов *Immovable*:
> - Во время выполнения для процедурной генерации уровней. Это может вызвать некоторые задержки, но не сильно повлияет на производительность. По завершении процесса генерации вам следует снова включить предупреждения.
> - При инициализации мира — это изменит время загрузки мира, но не повлияет на общую производительность.


### Возвращаемое значение

Текущий режим обработки попыток переместить узлы с включённым флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)*. Одно из следующих значений:
- **0** - перемещение узлов с флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)* запрещено.
- **1** - перемещение узлов с флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)* сопровождается предупреждением в консоли. (по умолчанию)
- **2** - перемещение узлов с флагом *[Immovable](../../../editor2/node_parameters/transformation_common/index.md#clutter)* разрешено (предупреждения не отображаются).

## void setAsyncLoadNodeReferences ( bool references )

Устанавливает новое значение, указывающее, включена ли асинхронная загрузка ссылок на узлы.
### Аргументы

- *bool* **references** - Установите **true**, чтобы включить асинхронную загрузку ссылок на узлы; **false** - чтобы отключить её.

## bool isAsyncLoadNodeReferences () const

Возвращает текущее значение, указывающее, включена ли асинхронная загрузка ссылок на узлы.
### Возвращаемое значение

**true**, если асинхронная загрузка ссылок на узлы включена; иначе **false**.
## static Event<const Ptr < Node > &> getEventNodeRemoved () const

Событие, срабатывающее при удалении узла из мира. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события NodeRemoved
void noderemoved_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события NodeRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections noderemoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventNodeRemoved().connect(noderemoved_event_connections, noderemoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventNodeRemoved().connect(noderemoved_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
noderemoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection noderemoved_event_connection;

// подписываемся на событие NodeRemoved с функцией-обработчиком, сохраняя соединение
World::getEventNodeRemoved().connect(noderemoved_event_connection, noderemoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
noderemoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
noderemoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие NodeRemoved через соединение
noderemoved_event_connection.disconnect();

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

	// Обработчик события NodeRemoved, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события NodeRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventNodeRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId noderemoved_handler_id;

// подписываемся на событие NodeRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
noderemoved_handler_id = World::getEventNodeRemoved().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventNodeRemoved().disconnect(noderemoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий NodeRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventNodeRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventNodeRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &> getEventNodeAdded () const

event triggered when a node is added into the world, including creation of a node from code. The event is also triggered when a the world is loaded from the xml file. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события NodeAdded
void nodeadded_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события NodeAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections nodeadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventNodeAdded().connect(nodeadded_event_connections, nodeadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventNodeAdded().connect(nodeadded_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
nodeadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection nodeadded_event_connection;

// подписываемся на событие NodeAdded с функцией-обработчиком, сохраняя соединение
World::getEventNodeAdded().connect(nodeadded_event_connection, nodeadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
nodeadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
nodeadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие NodeAdded через соединение
nodeadded_event_connection.disconnect();

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

	// Обработчик события NodeAdded, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события NodeAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventNodeAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId nodeadded_handler_id;

// подписываемся на событие NodeAdded с лямбда-обработчиком, сохраняя идентификатор соединения
nodeadded_handler_id = World::getEventNodeAdded().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventNodeAdded().disconnect(nodeadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий NodeAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventNodeAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventNodeAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventPostWorldShutdown () const

event triggered after calling all WorldLogic::shutdown() methods. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PostWorldShutdown
void postworldshutdown_event_handler()
{
	Log::message("\Обработка события PostWorldShutdown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections postworldshutdown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPostWorldShutdown().connect(postworldshutdown_event_connections, postworldshutdown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPostWorldShutdown().connect(postworldshutdown_event_connections, []() {
		Log::message("\Обработка события PostWorldShutdown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
postworldshutdown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection postworldshutdown_event_connection;

// подписываемся на событие PostWorldShutdown с функцией-обработчиком, сохраняя соединение
World::getEventPostWorldShutdown().connect(postworldshutdown_event_connection, postworldshutdown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
postworldshutdown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
postworldshutdown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PostWorldShutdown через соединение
postworldshutdown_event_connection.disconnect();

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

	// Обработчик события PostWorldShutdown, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события PostWorldShutdown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPostWorldShutdown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId postworldshutdown_handler_id;

// подписываемся на событие PostWorldShutdown с лямбда-обработчиком, сохраняя идентификатор соединения
postworldshutdown_handler_id = World::getEventPostWorldShutdown().connect(e_connections, []() {
		Log::message("\Обработка события PostWorldShutdown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPostWorldShutdown().disconnect(postworldshutdown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PostWorldShutdown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPostWorldShutdown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPostWorldShutdown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventPreWorldShutdown () const

event triggered before calling all WorldLogic::shutdown() methods. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PreWorldShutdown
void preworldshutdown_event_handler()
{
	Log::message("\Обработка события PreWorldShutdown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections preworldshutdown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPreWorldShutdown().connect(preworldshutdown_event_connections, preworldshutdown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPreWorldShutdown().connect(preworldshutdown_event_connections, []() {
		Log::message("\Обработка события PreWorldShutdown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
preworldshutdown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection preworldshutdown_event_connection;

// подписываемся на событие PreWorldShutdown с функцией-обработчиком, сохраняя соединение
World::getEventPreWorldShutdown().connect(preworldshutdown_event_connection, preworldshutdown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
preworldshutdown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
preworldshutdown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PreWorldShutdown через соединение
preworldshutdown_event_connection.disconnect();

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

	// Обработчик события PreWorldShutdown, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события PreWorldShutdown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPreWorldShutdown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId preworldshutdown_handler_id;

// подписываемся на событие PreWorldShutdown с лямбда-обработчиком, сохраняя идентификатор соединения
preworldshutdown_handler_id = World::getEventPreWorldShutdown().connect(e_connections, []() {
		Log::message("\Обработка события PreWorldShutdown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPreWorldShutdown().disconnect(preworldshutdown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PreWorldShutdown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPreWorldShutdown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPreWorldShutdown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventPostWorldInit () const

event triggered after calling all WorldLogic::init() methods. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Forced closing of the Engine should be disabled with the [`-auto_quit 0`](../../../code/command_line.md#auto_quit) command-line option.


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PostWorldInit
void postworldinit_event_handler()
{
	Log::message("\Обработка события PostWorldInit\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections postworldinit_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPostWorldInit().connect(postworldinit_event_connections, postworldinit_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPostWorldInit().connect(postworldinit_event_connections, []() {
		Log::message("\Обработка события PostWorldInit (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
postworldinit_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection postworldinit_event_connection;

// подписываемся на событие PostWorldInit с функцией-обработчиком, сохраняя соединение
World::getEventPostWorldInit().connect(postworldinit_event_connection, postworldinit_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
postworldinit_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
postworldinit_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PostWorldInit через соединение
postworldinit_event_connection.disconnect();

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

	// Обработчик события PostWorldInit, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события PostWorldInit\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPostWorldInit().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId postworldinit_handler_id;

// подписываемся на событие PostWorldInit с лямбда-обработчиком, сохраняя идентификатор соединения
postworldinit_handler_id = World::getEventPostWorldInit().connect(e_connections, []() {
		Log::message("\Обработка события PostWorldInit (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPostWorldInit().disconnect(postworldinit_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PostWorldInit при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPostWorldInit().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPostWorldInit().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventPreWorldInit () const

event triggered before calling all WorldLogic::init() methods. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PreWorldInit
void preworldinit_event_handler()
{
	Log::message("\Обработка события PreWorldInit\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections preworldinit_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPreWorldInit().connect(preworldinit_event_connections, preworldinit_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPreWorldInit().connect(preworldinit_event_connections, []() {
		Log::message("\Обработка события PreWorldInit (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
preworldinit_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection preworldinit_event_connection;

// подписываемся на событие PreWorldInit с функцией-обработчиком, сохраняя соединение
World::getEventPreWorldInit().connect(preworldinit_event_connection, preworldinit_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
preworldinit_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
preworldinit_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PreWorldInit через соединение
preworldinit_event_connection.disconnect();

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

	// Обработчик события PreWorldInit, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события PreWorldInit\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPreWorldInit().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId preworldinit_handler_id;

// подписываемся на событие PreWorldInit с лямбда-обработчиком, сохраняя идентификатор соединения
preworldinit_handler_id = World::getEventPreWorldInit().connect(e_connections, []() {
		Log::message("\Обработка события PreWorldInit (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPreWorldInit().disconnect(preworldinit_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PreWorldInit при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPreWorldInit().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPreWorldInit().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *, const Ptr < Node > &> getEventPostNodeSave () const

event triggered after calling the World::saveNode() method. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**, const Ptr<Node> & **node**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PostNodeSave
void postnodesave_event_handler(const char * world_file_path,  const Ptr<Node> & node)
{
	Log::message("\Обработка события PostNodeSave\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections postnodesave_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPostNodeSave().connect(postnodesave_event_connections, postnodesave_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPostNodeSave().connect(postnodesave_event_connections, [](const char * world_file_path,  const Ptr<Node> & node) {
		Log::message("\Обработка события PostNodeSave (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
postnodesave_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection postnodesave_event_connection;

// подписываемся на событие PostNodeSave с функцией-обработчиком, сохраняя соединение
World::getEventPostNodeSave().connect(postnodesave_event_connection, postnodesave_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
postnodesave_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
postnodesave_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PostNodeSave через соединение
postnodesave_event_connection.disconnect();

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

	// Обработчик события PostNodeSave, реализованный как член класса
	void event_handler(const char * world_file_path,  const Ptr<Node> & node)
	{
		Log::message("\Обработка события PostNodeSave\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPostNodeSave().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId postnodesave_handler_id;

// подписываемся на событие PostNodeSave с лямбда-обработчиком, сохраняя идентификатор соединения
postnodesave_handler_id = World::getEventPostNodeSave().connect(e_connections, [](const char * world_file_path,  const Ptr<Node> & node) {
		Log::message("\Обработка события PostNodeSave (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPostNodeSave().disconnect(postnodesave_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PostNodeSave при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPostNodeSave().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPostNodeSave().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *, const Ptr < Node > &> getEventPreNodeSave () const

event triggered before calling the World::saveNode() method. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**, const Ptr<Node> & **node**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PreNodeSave
void prenodesave_event_handler(const char * world_file_path,  const Ptr<Node> & node)
{
	Log::message("\Обработка события PreNodeSave\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections prenodesave_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPreNodeSave().connect(prenodesave_event_connections, prenodesave_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPreNodeSave().connect(prenodesave_event_connections, [](const char * world_file_path,  const Ptr<Node> & node) {
		Log::message("\Обработка события PreNodeSave (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
prenodesave_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection prenodesave_event_connection;

// подписываемся на событие PreNodeSave с функцией-обработчиком, сохраняя соединение
World::getEventPreNodeSave().connect(prenodesave_event_connection, prenodesave_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
prenodesave_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
prenodesave_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PreNodeSave через соединение
prenodesave_event_connection.disconnect();

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

	// Обработчик события PreNodeSave, реализованный как член класса
	void event_handler(const char * world_file_path,  const Ptr<Node> & node)
	{
		Log::message("\Обработка события PreNodeSave\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPreNodeSave().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId prenodesave_handler_id;

// подписываемся на событие PreNodeSave с лямбда-обработчиком, сохраняя идентификатор соединения
prenodesave_handler_id = World::getEventPreNodeSave().connect(e_connections, [](const char * world_file_path,  const Ptr<Node> & node) {
		Log::message("\Обработка события PreNodeSave (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPreNodeSave().disconnect(prenodesave_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PreNodeSave при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPreNodeSave().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPreNodeSave().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *> getEventPostWorldClear () const

event triggered after clearing the World. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PostWorldClear
void postworldclear_event_handler(const char * world_file_path)
{
	Log::message("\Обработка события PostWorldClear\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections postworldclear_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPostWorldClear().connect(postworldclear_event_connections, postworldclear_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPostWorldClear().connect(postworldclear_event_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PostWorldClear (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
postworldclear_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection postworldclear_event_connection;

// подписываемся на событие PostWorldClear с функцией-обработчиком, сохраняя соединение
World::getEventPostWorldClear().connect(postworldclear_event_connection, postworldclear_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
postworldclear_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
postworldclear_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PostWorldClear через соединение
postworldclear_event_connection.disconnect();

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

	// Обработчик события PostWorldClear, реализованный как член класса
	void event_handler(const char * world_file_path)
	{
		Log::message("\Обработка события PostWorldClear\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPostWorldClear().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId postworldclear_handler_id;

// подписываемся на событие PostWorldClear с лямбда-обработчиком, сохраняя идентификатор соединения
postworldclear_handler_id = World::getEventPostWorldClear().connect(e_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PostWorldClear (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPostWorldClear().disconnect(postworldclear_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PostWorldClear при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPostWorldClear().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPostWorldClear().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *> getEventPreWorldClear () const

event triggered before clearing the world — either closing the current world or preparing to load the next World. This event always takes place in Engine::swap(), i.e. in the end of the frame. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PreWorldClear
void preworldclear_event_handler(const char * world_file_path)
{
	Log::message("\Обработка события PreWorldClear\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections preworldclear_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPreWorldClear().connect(preworldclear_event_connections, preworldclear_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPreWorldClear().connect(preworldclear_event_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PreWorldClear (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
preworldclear_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection preworldclear_event_connection;

// подписываемся на событие PreWorldClear с функцией-обработчиком, сохраняя соединение
World::getEventPreWorldClear().connect(preworldclear_event_connection, preworldclear_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
preworldclear_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
preworldclear_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PreWorldClear через соединение
preworldclear_event_connection.disconnect();

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

	// Обработчик события PreWorldClear, реализованный как член класса
	void event_handler(const char * world_file_path)
	{
		Log::message("\Обработка события PreWorldClear\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPreWorldClear().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId preworldclear_handler_id;

// подписываемся на событие PreWorldClear с лямбда-обработчиком, сохраняя идентификатор соединения
preworldclear_handler_id = World::getEventPreWorldClear().connect(e_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PreWorldClear (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPreWorldClear().disconnect(preworldclear_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PreWorldClear при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPreWorldClear().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPreWorldClear().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *> getEventPostWorldSave () const

event triggered after saving the World. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PostWorldSave
void postworldsave_event_handler(const char * world_file_path)
{
	Log::message("\Обработка события PostWorldSave\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections postworldsave_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPostWorldSave().connect(postworldsave_event_connections, postworldsave_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPostWorldSave().connect(postworldsave_event_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PostWorldSave (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
postworldsave_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection postworldsave_event_connection;

// подписываемся на событие PostWorldSave с функцией-обработчиком, сохраняя соединение
World::getEventPostWorldSave().connect(postworldsave_event_connection, postworldsave_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
postworldsave_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
postworldsave_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PostWorldSave через соединение
postworldsave_event_connection.disconnect();

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

	// Обработчик события PostWorldSave, реализованный как член класса
	void event_handler(const char * world_file_path)
	{
		Log::message("\Обработка события PostWorldSave\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPostWorldSave().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId postworldsave_handler_id;

// подписываемся на событие PostWorldSave с лямбда-обработчиком, сохраняя идентификатор соединения
postworldsave_handler_id = World::getEventPostWorldSave().connect(e_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PostWorldSave (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPostWorldSave().disconnect(postworldsave_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PostWorldSave при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPostWorldSave().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPostWorldSave().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *> getEventPreWorldSave () const

event triggered before saving the World. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PreWorldSave
void preworldsave_event_handler(const char * world_file_path)
{
	Log::message("\Обработка события PreWorldSave\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections preworldsave_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPreWorldSave().connect(preworldsave_event_connections, preworldsave_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPreWorldSave().connect(preworldsave_event_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PreWorldSave (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
preworldsave_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection preworldsave_event_connection;

// подписываемся на событие PreWorldSave с функцией-обработчиком, сохраняя соединение
World::getEventPreWorldSave().connect(preworldsave_event_connection, preworldsave_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
preworldsave_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
preworldsave_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PreWorldSave через соединение
preworldsave_event_connection.disconnect();

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

	// Обработчик события PreWorldSave, реализованный как член класса
	void event_handler(const char * world_file_path)
	{
		Log::message("\Обработка события PreWorldSave\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPreWorldSave().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId preworldsave_handler_id;

// подписываемся на событие PreWorldSave с лямбда-обработчиком, сохраняя идентификатор соединения
preworldsave_handler_id = World::getEventPreWorldSave().connect(e_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PreWorldSave (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPreWorldSave().disconnect(preworldsave_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PreWorldSave при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPreWorldSave().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPreWorldSave().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *> getEventPostWorldLoad () const

event triggered after loading the World. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PostWorldLoad
void postworldload_event_handler(const char * world_file_path)
{
	Log::message("\Обработка события PostWorldLoad\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections postworldload_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPostWorldLoad().connect(postworldload_event_connections, postworldload_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPostWorldLoad().connect(postworldload_event_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PostWorldLoad (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
postworldload_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection postworldload_event_connection;

// подписываемся на событие PostWorldLoad с функцией-обработчиком, сохраняя соединение
World::getEventPostWorldLoad().connect(postworldload_event_connection, postworldload_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
postworldload_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
postworldload_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PostWorldLoad через соединение
postworldload_event_connection.disconnect();

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

	// Обработчик события PostWorldLoad, реализованный как член класса
	void event_handler(const char * world_file_path)
	{
		Log::message("\Обработка события PostWorldLoad\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPostWorldLoad().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId postworldload_handler_id;

// подписываемся на событие PostWorldLoad с лямбда-обработчиком, сохраняя идентификатор соединения
postworldload_handler_id = World::getEventPostWorldLoad().connect(e_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PostWorldLoad (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPostWorldLoad().disconnect(postworldload_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PostWorldLoad при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPostWorldLoad().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPostWorldLoad().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const char *> getEventPreWorldLoad () const

event triggered before loading the World. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **world_file_path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PreWorldLoad
void preworldload_event_handler(const char * world_file_path)
{
	Log::message("\Обработка события PreWorldLoad\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections preworldload_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
World::getEventPreWorldLoad().connect(preworldload_event_connections, preworldload_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
World::getEventPreWorldLoad().connect(preworldload_event_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PreWorldLoad (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
preworldload_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection preworldload_event_connection;

// подписываемся на событие PreWorldLoad с функцией-обработчиком, сохраняя соединение
World::getEventPreWorldLoad().connect(preworldload_event_connection, preworldload_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
preworldload_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
preworldload_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие PreWorldLoad через соединение
preworldload_event_connection.disconnect();

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

	// Обработчик события PreWorldLoad, реализованный как член класса
	void event_handler(const char * world_file_path)
	{
		Log::message("\Обработка события PreWorldLoad\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
World::getEventPreWorldLoad().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId preworldload_handler_id;

// подписываемся на событие PreWorldLoad с лямбда-обработчиком, сохраняя идентификатор соединения
preworldload_handler_id = World::getEventPreWorldLoad().connect(e_connections, [](const char * world_file_path) {
		Log::message("\Обработка события PreWorldLoad (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
World::getEventPreWorldLoad().disconnect(preworldload_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PreWorldLoad при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
World::getEventPreWorldLoad().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
World::getEventPreWorldLoad().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## bool getCollision ( const Math:: WorldBoundBox & bb , Vector < Ptr < Object >> & OUT_objects )

Ищет все [collider objects](../../../principles/physics/collision/index.md#collider) в пределах заданного ограничивающего бокса.
> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий бокс.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей объектов-коллайдеров. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если объекты-коллайдеры найдены; иначе false.
## bool getCollision ( const Math:: WorldBoundSphere & bs , Vector < Ptr < Object >> & OUT_objects )

Ищет все [collider objects](../../../principles/physics/collision/index.md#collider) в пределах заданной ограничивающей сферы.
> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей объектов-коллайдеров. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если объекты-коллайдеры найдены; иначе false.
## bool getCollision ( const Math:: WorldBoundFrustum & bf , Vector < Ptr < Object >> & OUT_objects )

Ищет все [collider objects](../../../principles/physics/collision/index.md#collider) в пределах заданного ограничивающего фрустума.
> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundFrustum](../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий фрустум.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей объектов-коллайдеров. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если объекты-коллайдеры найдены; иначе false.
## bool getCollision ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , Vector < Ptr < Object >> & OUT_objects )


Выполняет трассировку от точки p0 до точки p1, чтобы найти все [collider objects](../../../principles/physics/collision/index.md#collider), пересекаемые линией. Эта функция обнаруживает пересечение с поверхностями (полигонами) объектов мешей и террейна.


Коллизии с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Collision](../../../api/library/objects/class.object_cpp.md#setCollision_int_int_void) для поверхности включён.
3. Поверхности назначен материал.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей объектов-коллайдеров. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если объекты-коллайдеры найдены; иначе false.
## void setData ( const char * name , const char * data )

Устанавливает пользовательские данные, связанные с миром, с указанным ключом. В файле `*.world` данные задаются в теге data с указанным ключом.
### Аргументы

- *const char ** **name** - Строка, содержащая ключ, идентифицирующий пользовательские данные, которые нужно сохранить в файле `*.world`. > **Notice:** Ключ "editor_data" зарезервирован для UnigineEditor.
- *const char ** **data** - Новые пользовательские данные.

## const char * getData ( const char * name )

Возвращает пользовательские строковые данные, связанные с миром, по указанному ключу. Эта строка записывается непосредственно в тег data файла `*.world` с указанным ключом.
### Аргументы

- *const char ** **name** - Строка, содержащая ключ, идентифицирующий пользовательские данные, хранящиеся в файле `*.world`. > **Notice:** Ключ "editor_data" зарезервирован для UnigineEditor.

### Возвращаемое значение

Пользовательские строковые данные.
## bool hasData ( const char * name ) const

Проверяет, хранятся ли пользовательские строковые данные, связанные с миром, по указанному ключу в теге data файла `*.world`.
### Аргументы

- *const char ** **name** - Строка, содержащая ключ, идентифицирующий пользовательские данные, хранящиеся в файле `*.world`. > **Notice:** Ключ "editor_data" зарезервирован для UnigineEditor.

### Возвращаемое значение

true, если пользовательские строковые данные, связанные с миром, по указанному ключу хранятся в теге data файла `*.world`; иначе false.
## void removeData ( const char * name )

Удаляет пользовательские строковые данные, связанные с миром, по указанному ключу. Эта строка хранится в теге data файла `*.world` с указанным ключом.
### Аргументы

- *const char ** **name** - Строка, содержащая ключ, идентифицирующий пользовательские данные, хранящиеся в файле `*.world`. > **Notice:** Ключ "editor_data" зарезервирован для UnigineEditor.

## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекаемый линией**. Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если у объекта есть соответствующая маска пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.

### Возвращаемое значение

Указатель на первый пересечённый объект.
## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Vector < Ptr < Node >> & exclude )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекаемый линией** (за исключением тех, что переданы в списке **exclude**). Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если у объекта есть соответствующая маска пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **exclude** - Список узлов, которые следует игнорировать при поиске пересечения по трассируемой линии.

### Возвращаемое значение

Первый пересечённый объект, найденный на линии (за исключением тех, что переданы в списке **exclude**); иначе указатель NULL.
## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Ptr < WorldIntersection > & intersection )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекающий линию**. Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если объект соответствует маске пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersection](../../../api/library/worlds/class.worldintersection_cpp.md)> &* **intersection** - Указатель на объект WorldIntersection, который будет заполнен.

### Возвращаемое значение

Указатель на первый пересечённый объект.
## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Ptr < WorldIntersectionNormal > & intersection )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекающий линию**. Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если объект соответствует маске пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionNormal](../../../api/library/worlds/class.worldintersectionnormal_cpp.md)> &* **intersection** - Указатель на объект WorldIntersectionNormal, который будет заполнен.

### Возвращаемое значение

Указатель на первый пересечённый объект.
## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Ptr < WorldIntersectionTexCoord > & intersection )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекающий линию**. Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если объект соответствует маске пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionTexCoord](../../../api/library/worlds/class.worldintersectiontexcoord_cpp.md)> &* **intersection** - Указатель на объект WorldIntersectionTexCoord, который будет заполнен.

### Возвращаемое значение

Указатель на первый пересечённый объект.
## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Vector < Ptr < Node >> & exclude , const Ptr < WorldIntersection > & intersection )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекающий линию**. Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если объект соответствует маске пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **exclude** - Список исключаемых узлов.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersection](../../../api/library/worlds/class.worldintersection_cpp.md)> &* **intersection** - Указатель на объект WorldIntersection, который будет заполнен.

### Возвращаемое значение

Указатель на первый пересечённый объект.
## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Vector < Ptr < Node >> & exclude , const Ptr < WorldIntersectionNormal > & intersection )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекающий линию**. Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если объект соответствует маске пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **exclude** - Список исключаемых узлов.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionNormal](../../../api/library/worlds/class.worldintersectionnormal_cpp.md)> &* **intersection** - Указатель на объект WorldIntersectionNormal, который будет заполнен.

### Возвращаемое значение

Указатель на первый пересечённый объект.
## Ptr < Object > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , const Vector < Ptr < Node >> & exclude , const Ptr < WorldIntersectionTexCoord > & intersection )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **первый объект, пересекаемый линией**. Эта функция обнаруживает пересечение с поверхностями (полигонами) мешей. Пересечение может быть найдено, только если объект соответствует маске пересечения.


Пересечения с поверхностью могут быть найдены только при выполнении следующих условий:


1. Поверхность включена.
2. Флаг [Intersection](../../../api/library/objects/class.object_cpp.md#setIntersection_int_int_void) для поверхности включён.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *int* **mask** - Маска пересечения. Если передан 0, функция вернёт NULL.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **exclude** - Список исключаемых узлов.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WorldIntersectionTexCoord](../../../api/library/worlds/class.worldintersectiontexcoord_cpp.md)> &* **intersection** - Указатель на объект WorldIntersectionTexCoord, который будет заполнен.

### Возвращаемое значение

Указатель на первый пересечённый объект.
## bool getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , Vector < Ptr < Object >> & OUT_objects , bool check_surface_flags = true )


Выполняет трассировку от точки p0 до точки p1, чтобы найти **объекты, пересекаемые линией**. Эта функция обнаруживает пересечение с ограничивающими объёмами объектов.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Координаты начальной точки линии.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Координаты конечной точки линии.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей пересечённых объектов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *bool* **check_surface_flags** - true, если [surface*Intersection* flags](../../../api/library/objects/class.object_cpp.md#getIntersection_int_int) должны учитываться при проверке пересечений с объектами; иначе false. Если установлено true, объекты с отключёнными флагами *Intersection* поверхности (настройка по умолчанию) будут игнорироваться как непересекаемые.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundBox & bb , Vector < Ptr < Object >> & OUT_objects )


Ищет пересечения **с объектами**, находящимися в заданном ограничивающем боксе.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий бокс, в котором будет выполнен поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей пересечённых объектов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundBox & bb , Vector < Ptr < Node >> & OUT_nodes )


Ищет пересечения **с узлами**, находящимися в заданном ограничивающем боксе.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий бокс, в котором будет выполнен поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей пересечённых узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundBox & bb , Node::TYPE type , Vector < Ptr < Node >> & OUT_nodes )


Ищет пересечения **с узлами указанного типа**, находящимися в заданном ограничивающем боксе.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundBox](../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий бокс, в котором будет выполнен поиск пересечений.
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **type** - Фильтр по типу узла. Будут проверены только узлы указанного типа.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей пересечённых узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundSphere & bs , Vector < Ptr < Object >> & OUT_objects )


Ищет пересечения **с объектами**, находящимися в заданной ограничивающей сфере.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера, в которой будет выполнен поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей пересечённых объектов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundSphere & bs , Vector < Ptr < Node >> & OUT_nodes )


Ищет пересечения **с узлами**, находящимися в заданной ограничивающей сфере.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера, в которой будет выполнен поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей пересечённых узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundSphere & bs , Node::TYPE type , Vector < Ptr < Node >> & OUT_nodes )


Ищет пересечения **с узлами указанного типа**, находящимися в заданной ограничивающей сфере.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundSphere](../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера, в которой будет выполнен поиск пересечений.
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **type** - Фильтр по типу узла. Будут проверены только узлы указанного типа.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей пересечённых узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundFrustum & bf , Vector < Ptr < Object >> & OUT_objects )


Ищет пересечения **с объектами**, находящимися в заданном ограничивающем фрустуме. Этот метод обнаруживает все объекты независимо от их видимости (т.е. если объект отключён, любой из его LOD-уровней отключён, или он находится за пределами диапазона [visibility distance](../../../editor2/settings/render_settings/visibility_distances/index.md), но расположен внутри ограничивающего фрустума, пересечение будет обнаружено). Чтобы проверять пересечения с учётом аспекта видимости, используйте *[getVisibleIntersection()](#getVisibleIntersection_Vec3_WorldBoundFrustum_VECObject_float_int)*. Ознакомьтесь с [usage example](../../../code/usage/intersections/index_cpp.md#frustrum_search), применяющим этот метод.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundFrustum](../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий фрустум, в котором будет выполнен поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив умных указателей пересечённых объектов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundFrustum & bf , Node::TYPE type , Vector < Ptr < Node >> & OUT_nodes )


Ищет пересечения **с узлами указанного типа**, находящимися в заданном ограничивающем фрустуме. Этот метод обнаруживает все узлы указанного типа независимо от их видимости (т.е. если объект отключён, любой из его LOD-уровней отключён, или он находится за пределами диапазона [visibility distance](../../../editor2/settings/render_settings/visibility_distances/index.md), но расположен внутри ограничивающего фрустума, пересечение будет обнаружено). Чтобы проверять пересечения с учётом аспекта видимости, используйте *[getVisibleIntersection()](#getVisibleIntersection_Vec3_WorldBoundFrustum_int_VECNode_float_int)*.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundFrustum](../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий фрустум, в котором будет выполнен поиск пересечений.
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **type** - Фильтр по типу узла. Будут проверены только узлы указанного типа.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей пересечённых узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getIntersection ( const Math:: WorldBoundFrustum & bf , Vector < Ptr < Node >> & OUT_nodes )


Ищет пересечения **с узлами указанного типа**, находящимися в заданном ограничивающем фрустуме. Этот метод обнаруживает все узлы независимо от их видимости (т.е. если объект отключён, любой из его LOD-уровней отключён, или он находится за пределами диапазона [visibility distance](../../../editor2/settings/render_settings/visibility_distances/index.md), но расположен внутри ограничивающего фрустума, пересечение будет обнаружено). Чтобы проверять пересечения с учётом аспекта видимости, используйте *[getVisibleIntersection()](#getVisibleIntersection_Vec3_WorldBoundFrustum_int_VECNode_float_int)*.


> **Notice:** Так как новый узел становится частью BSP-дерева только после вызова метода *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* (движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира), все подсистемы движка могут обработать этот узел только в следующем кадре. Если вам нужно получить узел в самом первом кадре, вызовите метод *[updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


### Аргументы

- *const  Math::[WorldBoundFrustum](../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий фрустум, в котором будет выполнен поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей пересечённых узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если пересечения найдены; иначе false.
## bool getVisibleIntersection ( const Math:: Vec3 & camera , const Math:: WorldBoundFrustum & bf , Vector < Ptr < Object >> & OUT_objects , float max_distance )

Ищет пересечения с объектами внутри заданного ограничивающего фрустума, видимыми с указанной позиции камеры, т.е. когда [either of its LODs](../../../api/library/objects/class.object_cpp.md#setMinVisibleDistance_float_int_void) находится в пределах [visibility distance](../../../editor2/settings/render_settings/visibility_distances/index.md). В отличие от метода *[getIntersection()](#getIntersection_WorldBoundFrustum_VECObject_int)*, этот метод учитывает концепцию "видимости" (скрытые объекты или те, что находятся слишком далеко, не будут найдены). Подробнее см. этот [usage example](../../../code/usage/intersections/index_cpp.md#frustrum_search).
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **camera** - Позиция камеры, от которой проверяется дистанция видимости до объектов.
- *const  Math::[WorldBoundFrustum](../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий фрустум, внутри которого выполняется поиск пересечений.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>> &* **OUT_objects** - Массив пересечённых объектов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *float* **max_distance** - Максимальная дистанция видимости для объектов, в единицах. Если расстояние от указанной позиции камеры до объекта превышает этот предел, пересечение не регистрируется, даже если узел находится внутри указанного ограничивающего фрустума.

### Возвращаемое значение

true, если найдено хотя бы одно пересечение; иначе false.
## bool getVisibleIntersection ( const Math:: Vec3 & camera , const Math:: WorldBoundFrustum & bf , Node::TYPE type , Vector < Ptr < Node >> & OUT_nodes , float max_distance )


Ищет пересечения с узлами внутри заданного ограничивающего фрустума, видимыми с указанной позиции камеры, т.е. когда [either of its LODs](../../../api/library/objects/class.object_cpp.md#setMinVisibleDistance_float_int_void) находится в пределах [visibility distance](../../../editor2/settings/render_settings/visibility_distances/index.md). В отличие от метода *[getIntersection()](#getIntersection_WorldBoundFrustum_int_VECNode_int)*, этот метод учитывает концепцию "видимости" (скрытые узлы или те, что находятся слишком далеко, не будут найдены). Подробнее см. этот [usage example](../../../code/usage/intersections/index_cpp.md#frustrum_search).


> **Notice:** Этот метод можно использовать только для узлов, унаследованных от класса [Object](../../../api/library/objects/class.object_cpp.md), т.е. имеющих поверхности, хранящие данные о LOD и [visibility distance](../../../editor2/settings/render_settings/visibility_distances/index.md).


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **camera** - Позиция камеры, от которой проверяется дистанция видимости до узлов.
- *const  Math::[WorldBoundFrustum](../../../api/library/math/bounds/class.worldboundfrustum_cpp.md) &* **bf** - Ограничивающий фрустум, внутри которого выполняется поиск пересечений.
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **type** - Тип узла (одна из переменных [NODE_*](../../../api/library/nodes/class.node_cpp.md#DECAL_BEGIN)); установите -1, если этот фильтр не используется.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив пересечённых узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *float* **max_distance** - Максимальная дистанция видимости для узлов, в единицах. Если расстояние от указанной позиции камеры до узла превышает этот предел, пересечение не регистрируется, даже если узел находится внутри указанного ограничивающего фрустума.

### Возвращаемое значение

true, если найдено хотя бы одно пересечение; иначе false.
## bool loadWorld ( const char * path )

Загружает мир из указанного пути к файлу и заменяет им текущий мир. Мир загружается не сразу — загрузка начинается в [beginning](../../../code/fundamentals/execution_sequence/main_loop.md#update) следующего кадра, тогда как текущий мир выгружается в [end](../../../code/fundamentals/execution_sequence/main_loop.md#swap) текущего кадра.
### Аргументы

- *const char ** **path** - Путь к [file describing the world](../../../principles/world_structure/index.md).

### Возвращаемое значение

true, если мир успешно загружен; иначе false.
## bool loadWorld ( const char * path , bool partial_path )

Загружает мир из указанного пути к файлу и заменяет им текущий мир. Мир загружается не сразу — загрузка начинается в [beginning](../../../code/fundamentals/execution_sequence/main_loop.md#update) следующего кадра, тогда как текущий мир выгружается в [end](../../../code/fundamentals/execution_sequence/main_loop.md#swap) текущего кадра.
### Аргументы

- *const char ** **path** - Путь к [file describing the world](../../../principles/world_structure/index.md).
- *bool* **partial_path** - true, если путь к файлу мира является частичным; или false, если это полный путь.

### Возвращаемое значение

true, если мир успешно загружен; иначе false.
## bool loadWorldForce ( const char * path )

Загружает мир из указанного пути к файлу и заменяет им текущий мир. Мир загружается немедленно, прерывая последовательность выполнения, поэтому должен использоваться либо до [Engine::update()](../../../code/fundamentals/execution_sequence/main_loop.md#update), либо после [Engine::swap()](../../../code/fundamentals/execution_sequence/main_loop.md#swap). Если вызывается в Engine::update(), последовательность выполнения будет следующей: update() до вызова loadWorldForce(), loadWorldForce(), shutdown(), продолжение update() с места прерывания, postUpdate(), swap(), init() и т.д. Эта функция рекомендуется для использования, связанного с редактором.
### Аргументы

- *const char ** **path** - Путь к [file describing the world](../../../principles/world_structure/index.md).

### Возвращаемое значение

true, если мир успешно загружен; иначе false.
## bool loadWorldForce ( const char * path , bool partial_path )

Загружает мир из указанного пути к файлу и заменяет им текущий мир. Мир загружается немедленно, прерывая последовательность выполнения, поэтому должен использоваться либо до [Engine::update()](../../../code/fundamentals/execution_sequence/main_loop.md#update), либо после [Engine::swap()](../../../code/fundamentals/execution_sequence/main_loop.md#swap). Если вызывается в Engine::update(), последовательность выполнения будет следующей: update() до вызова loadWorldForce(), loadWorldForce(), shutdown(), продолжение update() с места прерывания, postUpdate(), swap(), init() и т.д. Эта функция рекомендуется для использования, связанного с редактором.
### Аргументы

- *const char ** **path** - Путь к [file describing the world](../../../principles/world_structure/index.md).
- *bool* **partial_path** - true, если путь к файлу мира является частичным; или false, если это полный путь.

### Возвращаемое значение

true, если мир успешно загружен; иначе false.
## bool saveWorld ( )

Сохраняет мир.
### Возвращаемое значение

true, если мир успешно сохранён; иначе false.
## bool saveWorld ( const char * path )

Сохраняет мир в указанное место.
### Аргументы

- *const char ** **path** - Путь, по которому будет сохранён мир.

### Возвращаемое значение

true, если мир успешно сохранён; иначе false.
## bool reloadWorld ( )

Перезагружает мир.
### Возвращаемое значение

true, если мир успешно перезагружен; иначе false.
## bool quitWorld ( )

Закрывает мир.
### Возвращаемое значение

true, если мир успешно закрыт; иначе false.
## bool addWorld ( const char * name )

Загружает мир из файла и добавляет его к текущему миру.
### Аргументы

- *const char ** **name** - Имя [file describing the world](../../../principles/world_structure/index.md).

### Возвращаемое значение

true, если мир успешно загружен и добавлен; иначе false.
## bool isNode ( int id ) const

Проверяет, существует ли в мире узел с заданным ID.
### Аргументы

- *int* **id** - ID узла.

### Возвращаемое значение

true, если узел с заданным ID существует; иначе false.
## void getNodes ( Vector < Ptr < Node >> & OUT_nodes , bool expand_node_reference = true , bool expand_world_clutter = true ) const

 Собирает все экземпляры всех узлов (загруженных из файла `*.world` или созданных динамически во время выполнения), включая [cache](../../../principles/world_management/index.md#node_cache), [Node Reference internals](../../../api/library/nodes/class.nodereference_cpp.md#unpacking), содержимое World Clutter (если установлены соответствующие флаги), и помещает их в указанный выходной список.
> **Notice:** Если вам нужно получить только корневые узлы, используйте вместо этого [getRootNodes()](#getRootNodes_VECNode_void).


### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *bool* **expand_node_reference** - true, чтобы получить узлы, содержащиеся в *NodeReferences*; иначе false.
- *bool* **expand_world_clutter** - true, чтобы получить узлы, содержащиеся в *WorldClutters*; иначе false.

## Ptr < Node > loadNode ( const char * file_path , bool cache = true )

Загружает узел (или иерархию узлов) из файла `.node / .fbx`. Если узел успешно загружен, им управляет текущий мир (его *[Lifetime](../../../api/library/nodes/class.node_cpp.md#getLifetime_int)* — *[World](../../../api/library/nodes/class.node_cpp.md#LIFETIME)*).
[Cached nodes](../../../principles/world_management/index.md#node_cache) остаются в памяти. Если вы не собираетесь загружать больше ссылок на узлы из определённого ассета `*.node`, установите аргумент **cache** в 0, либо вы можете впоследствии удалить кэшированные узлы из списка узлов мира с помощью метода *[destroyCacheNode()](#destroyCacheNode_cstr_int)*.


### Аргументы

- *const char ** **file_path** - Путь к загружаемому файлу `*.node`.
- *bool* **cache** - true для использования кэширования узлов, false — для отказа от него.

### Возвращаемое значение

Загруженный узел; NULL, если узел не может быть загружен.
## Ptr < Node > loadNode ( const UGUID & file_guid , bool cache = true )

Загружает узел (или иерархию узлов) из файла `.node / .fbx` с указанным GUID файла. Если узел успешно загружен, им управляет текущий мир (его *[Lifetime](../../../api/library/nodes/class.node_cpp.md#getLifetime_int)* — *[World](../../../api/library/nodes/class.node_cpp.md#LIFETIME)*).
[Cached nodes](../../../principles/world_management/index.md#node_cache) остаются в памяти. Если вы не собираетесь загружать больше ссылок на узлы из определённого ассета `*.node`, установите аргумент **cache** в 0, либо вы можете впоследствии удалить кэшированные узлы из списка узлов мира с помощью метода *[destroyCacheNode()](#destroyCacheNode_cstr_int)*.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - GUID загружаемого файла `*.node`.
- *bool* **cache** - true для использования кэширования узлов, false — для отказа от него.

### Возвращаемое значение

Загруженный узел; NULL, если узел не может быть загружен.
## bool loadNodes ( const char * file_path , Vector < Ptr < Node >> & OUT_nodes ) const

Загружает узлы из файла.
### Аргументы

- *const char ** **file_path** - Путь к файлу `*.node`.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Массив умных указателей узлов, к которому добавляются загруженные узлы. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

true, если узлы успешно загружены; иначе false.
## bool saveNode ( const char * file_path , const Ptr < Node > & node , bool binary = 0 )

Сохраняет указанный узел в файл с учётом его [local transformation](../../../api/library/nodes/class.node_cpp.md#getTransform_Mat4).
### Аргументы

- *const char ** **file_path** - Путь к файлу `*.node`.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Указатель на сохраняемый узел.
- *bool* **binary** - Если установлено true, узел сохраняется в бинарный `*.xml`. Этот файл нельзя прочитать, но его использование ускоряет сохранение узла и требует меньше места на диске.

### Возвращаемое значение

true, если узел успешно сохранён; иначе false.
## bool saveNodes ( const char * file_path , const Vector < Ptr < Node >> & nodes , bool binary = 0 ) const

Сохраняет узлы в файл.
### Аргументы

- *const char ** **file_path** - Путь к файлу `*.node`.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Массив умных указателей узлов для сохранения.
- *bool* **binary** - Если установлено true, узел сохраняется в бинарный `*.xml`. Этот файл нельзя прочитать, но его использование ускоряет сохранение узла и требует меньше места на диске.

### Возвращаемое значение

true, если узлы успешно сохранены; иначе false.
## void updateSpatial ( )


Обновляет [BSP-дерево (binary space partitioning) узлов](../../../principles/world_management/index.md#outdoor).


Движок вызывает этот метод автоматически каждый кадр после выполнения кода *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)* скрипта мира. Так как новый узел становится частью BSP-дерева только после вызова этого метода, все подсистемы движка (рендерер, физика, звук, поиск пути, коллизии, пересечения и т.д.) могут обработать этот узел только в следующем кадре. Если вам нужно, чтобы подсистема обработала узел в самом первом кадре, вы можете вызвать метод *updateSpatial()* вручную. В любом случае движок вызовет этот метод автоматически после выполнения кода *update()*.


## Ptr < Node > getNodeByID ( int node_id ) const

Возвращает узел по его идентификатору, если он существует.
### Аргументы

- *int* **node_id** - ID узла.

### Возвращаемое значение

Узел, если он существует в мире; иначе **nullptr**.
## Ptr < Node > getNodeByName ( const char * name ) const

Возвращает узел по его имени, если он существует. Если мир содержит несколько узлов с одинаковым именем, будет возвращён только первый найденный. Чтобы получить все узлы с одинаковым именем, используйте метод [*getNodesByName()*](#getNodesByName_cstr_VECNode_void).
> **Notice:** Метод отфильтровывает изолированные иерархии узлов и кэшированные узлы, поэтому не возвращает узлы, имеющие владельца (*NodeReference / Clutter / Cluster*) среди своих предков, или узлы из кэша.


### Аргументы

- *const char ** **name** - Имя узла.

### Возвращаемое значение

Node, if it exists in the world; otherwise, **nullptr**.
## void getNodesByName ( const char * name , Vector < Ptr < Node >> & OUT_nodes ) const

Формирует список узлов в мире с заданным именем и помещает его в **nodes**.
### Аргументы

- *const char ** **name** - Имя узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Список узлов с заданным именем (если есть); иначе **nullptr**. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Ptr < Node > getNodeByType ( int type ) const

Возвращает первый узел указанного типа в мире. Скрытые и системные узлы игнорируются.
### Аргументы

- *int* **type** - Идентификатор типа узла, одно из значений [NODE_*](../../../api/library/nodes/class.node_cpp.md#NODE_BEGIN).

### Возвращаемое значение

Первый узел указанного типа, если он существует в мире; иначе **nullptr**.
## void getNodesByType ( int type , Vector < Ptr < Node >> & OUT_nodes ) const

Формирует список узлов указанного типа в мире и помещает его в **nodes**. Скрытые и системные узлы игнорируются.
### Аргументы

- *int* **type** - Идентификатор типа узла, одно из значений [NODE_*](../../../api/library/nodes/class.node_cpp.md#NODE_BEGIN).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Список узлов заданного типа (если есть); иначе **nullptr**. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## bool isNode ( const char * name ) const

Проверяет, существует ли в мире узел с заданным именем.
### Аргументы

- *const char ** **name** - Имя узла.

### Возвращаемое значение

true, если узел с указанным именем существует в мире; иначе false.
## void clearBindings ( )

Очищает внутренние буферы с указателями и экземплярами. Эта функция используется для корректного клонирования объектов с иерархиями, например, тел и шарниров. Должна вызываться перед клонированием.
## void getRootNodes ( Vector < Ptr < Node >> & OUT_nodes )

Получает все корневые узлы в иерархии мира и помещает их в nodes. Не включает [cached](../../../principles/world_management/index.md#node_cache) узлы.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Вектор, в который будут помещены все корневые узлы иерархии мира. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## int getRootNodeIndex ( const Ptr < Node > & node ) const

Возвращает индекс указанного корневого узла, принадлежащего иерархии мира.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Корневой узел, для которого нужно получить индекс.

### Возвращаемое значение

Индекс указанного корневого узла, если он существует; иначе -1.
## void setRootNodeIndex ( const Ptr < Node > & node , int index )

Устанавливает новый индекс для указанного корневого узла, принадлежащего иерархии мира.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Корневой узел, для которого нужно установить новый индекс.
- *int* **index** - Новый индекс, устанавливаемый для указанного корневого узла.

## void setNodeIdSeed ( unsigned int seed )

Устанавливает значение зерна (seed) для случайной генерации ID узла. Этот метод используется для детерминированной генерации.
### Аргументы

- *unsigned int* **seed** - Значение зерна.

## void setNodeIdRange ( int from , int to )

Устанавливает диапазон для случайной генерации ID узла. Этот метод можно использовать, например, для генерации ID для узлов, разделённых на несколько групп: внутри группы ID будут генерироваться в отдельном диапазоне.
### Аргументы

- *int* **from** - Начало диапазона.
- *int* **to** - Конец диапазона.

## void findNodes ( CallbackBase2 < Ptr < Node >, bool *> * find_node_callback ) const

### Аргументы

- *[CallbackBase2](../../../api/library/common/callbacks/class.callbackbase2_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>, bool *> ** **find_node_callback**

## bool removeNodeFile ( const char * file_path )

Очищает [cached](../../../principles/world_management/index.md#node_cache) узлы для заданного файла `*.node` и удаляет все связанные с ним *Node References* из сцены.
При попытке доступа к кэшированным узлам учитывайте следующее:

- если узел был загружен по имени — узел сохраняется в кэше по своему **имени**;
- если узел был загружен из родительского *Node Reference* — узел сохраняется в кэше по своему **GUID**.

 Ниже приведён пример того, как очистить кэшированные узлы и перезагрузить их в обоих случаях:
<details>
<summary>Example | Close</summary>

```cpp
NodePtr node = World::loadNode(file_name);
// change something in the node...
World::saveNode(file_name, node);

// clear cache by the name and remove all node references associated with this source from the scene
World::removeNodeFile(file_name);
// clear cache by the GUID (if this node is inside another Node Reference) and remove all node references associated with this source from the scene
World::removeNodeFile(FileSystem::guidToPath(FileSystem::getGUID(file_name)));

```

</details>


### Аргументы

- *const char ** **file_path** - Path to the `*.node` file.

### Возвращаемое значение

true if nodes for the given `*.node` file were successfully removed from cache with related *Node References* removed from the scene; otherwise, false.
## bool removeNodeFile ( const UGUID & file_guid )

Очищает [cached](../../../principles/world_management/index.md#node_cache) узлы для заданного файла `*.node` и удаляет все связанные с ним *Node References* из сцены.
При попытке доступа к кэшированным узлам учитывайте следующее:

- если узел был загружен по имени — узел сохраняется в кэше по своему **имени**;
- если узел был загружен из родительского *Node Reference* — узел сохраняется в кэше по своему **GUID**.

 Ниже приведён пример того, как очистить кэшированные узлы и перезагрузить их в обоих случаях:
<details>
<summary>Пример | Закрыть</summary>

```cpp
NodePtr node = World::loadNode(file_name);
// изменяем что-то в узле...
World::saveNode(file_name, node);

// очищаем кэш по имени и удаляем все ссылки на узлы, связанные с этим источником, из сцены
World::removeNodeFile(file_name);
// очищаем кэш по GUID (если этот узел находится внутри другого Node Reference) и удаляем все ссылки на узлы, связанные с этим источником, из сцены
World::removeNodeFile(FileSystem::guidToPath(FileSystem::getGUID(file_name)));

```

</details>


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - GUID файла `*.node`.

### Возвращаемое значение

true, если узлы для заданного файла `*.node` были успешно удалены из кэша, а связанные с ними *Node References* удалены из сцены; иначе false.
## bool reloadNodeFile ( const char * file_path )

Очищает [cached](../../../principles/world_management/index.md#node_cache) узлы для заданного файла `*.node` и перезагружает все связанные с ним *Node References* в сцене.
При попытке доступа к кэшированным узлам учитывайте следующее:

- если узел был загружен по имени — узел сохраняется в кэше по своему **имени**;
- если узел был загружен из родительского *Node Reference* — узел сохраняется в кэше по своему **GUID**.

 Ниже приведён пример того, как очистить кэшированные узлы и перезагрузить их в обоих случаях:
<details>
<summary>Пример | Закрыть</summary>

```cpp
NodePtr node = World::loadNode(file_name);
// изменяем что-то в узле...
World::saveNode(file_name, node);

// очищаем кэш по имени и перезагружаем все ссылки на узлы, связанные с этим источником
World::reloadNodeFile(file_name);
// очищаем кэш по GUID (если этот узел находится внутри другого Node Reference) и перезагружаем все ссылки на узлы, связанные с этим источником
World::reloadNodeFile(FileSystem::guidToPath(FileSystem::getGUID(file_name)));

```

</details>


### Аргументы

- *const char ** **file_path** - Путь к файлу `*.node`.

### Возвращаемое значение

true, если узлы для заданного файла `*.node` были успешно удалены из кэша и перезагружены из исходного файла; иначе false.
## bool reloadNodeFile ( const UGUID & file_guid )

Очищает [cached](../../../principles/world_management/index.md#node_cache) узлы для заданного файла `*.node` и перезагружает все связанные с ним *Node References* в сцене.
При попытке доступа к кэшированным узлам учитывайте следующее:

- если узел был загружен по имени — узел сохраняется в кэше по своему **имени**;
- если узел был загружен из родительского *Node Reference* — узел сохраняется в кэше по своему **GUID**.

 Ниже приведён пример того, как очистить кэшированные узлы и перезагрузить их в обоих случаях:
<details>
<summary>Пример | Закрыть</summary>

```cpp
NodePtr node = World::loadNode(file_name);
// изменяем что-то в узле...
World::saveNode(file_name, node);

// очищаем кэш по имени и перезагружаем все ссылки на узлы, связанные с этим источником
World::reloadNodeFile(file_name);
// очищаем кэш по GUID (если этот узел находится внутри другого Node Reference) и перезагружаем все ссылки на узлы, связанные с этим источником
World::reloadNodeFile(FileSystem::guidToPath(FileSystem::getGUID(file_name)));

```

</details>


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - GUID файла `*.node`.

### Возвращаемое значение

true, если узлы для заданного файла `*.node` были успешно удалены из кэша и перезагружены из исходного файла; иначе false.
## bool destroyCacheNode ( const char * file_path )

Очищает [cached](../../../principles/world_management/index.md#node_cache) узлы для заданного файла `*.node`.
При попытке доступа к кэшированным узлам учитывайте следующее:

- если узел был загружен по имени — узел сохраняется в кэше по своему **имени**;
- если узел был загружен из родительского *Node Reference* — узел сохраняется в кэше по своему **GUID**.

 Ниже приведён пример того, как очистить кэшированные узлы в обоих случаях:
<details>
<summary>Пример | Закрыть</summary>

```cpp
NodePtr node = World::loadNode(file_name);
// изменяем что-то в узле...
World::saveNode(file_name, node);

// очищаем кэш по имени
World::destroyCacheNode(file_name);
// очищаем кэш по GUID (если этот узел находится внутри другого Node Reference)
World::destroyCacheNode(FileSystem::guidToPath(FileSystem::getGUID(file_name)));

// перезагружаем узел
node.deleteForce();
node = World::loadNode(file_name);

```

</details>


### Аргументы

- *const char ** **file_path** - Путь к файлу `*.node`.

### Возвращаемое значение

true, если узлы для заданного файла `*.node` были успешно удалены из кэша; иначе false.
## bool destroyCacheNode ( const UGUID & file_guid )

Очищает [cached](../../../principles/world_management/index.md#node_cache) узлы для заданного файла `*.node`.
При попытке доступа к кэшированным узлам учитывайте следующее:

- если узел был загружен по имени — узел сохраняется в кэше по своему **имени**;
- если узел был загружен из родительского *Node Reference* — узел сохраняется в кэше по своему **GUID**.

 Ниже приведён пример того, как очистить кэшированные узлы в обоих случаях:
<details>
<summary>Пример | Закрыть</summary>

```cpp
NodePtr node = World::loadNode(file_name);
// изменяем что-то в узле...
World::saveNode(file_name, node);

// очищаем кэш по имени
World::destroyCacheNode(file_name);
// очищаем кэш по GUID (если этот узел находится внутри другого Node Reference)
World::destroyCacheNode(FileSystem::guidToPath(FileSystem::getGUID(file_name)));

// перезагружаем узел
node.deleteForce();
node = World::loadNode(file_name);

```

</details>


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **file_guid** - GUID файла `*.node`.

### Возвращаемое значение

true, если узлы для файла `*.node` с заданным GUID были успешно удалены из кэша; иначе false.
