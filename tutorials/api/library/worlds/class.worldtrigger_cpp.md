# Unigine::WorldTrigger Class (CPP)

**Header:** #include <UnigineWorlds.h>

**Inherits from:** Node


***World Trigger*** генерирует события, когда любые узлы (коллайдеры или нет) попадают внутрь или наружу него. Триггер может обнаруживать узел любого типа по его ограничивающему боксу.


> **Notice:** **[World Triggers](../../../objects/worlds/world_trigger/index.md)** обнаруживают только узлы с включённым *Triggers Interaction* - либо в редакторе, либо через API с помощью *[setTriggerInteractionEnabled()](../../../api/library/nodes/class.node_cpp.md#setTriggerInteractionEnabled_int_void)*.


Можно либо [specify a list of nodes](#setTargetNodes_SETNode_void), для которых будут выполняться обработчики событий, либо позволить триггеру реагировать на все узлы (поведение по умолчанию). В последнем случае список целевых узлов должен быть пустым. Также можно указать [list of nodes](#setExcludeNodes_SETNode_void), которые пропускаются триггером и проходят незамеченными.


Функция-обработчик *World Trigger* фактически выполняется только при вызове следующей функции движка: то есть перед *[updatePhysics()](../../../code/fundamentals/execution_sequence/main_loop.md#physics_updatePhysics)* (в текущем кадре) или перед *[update()](../../../code/fundamentals/execution_sequence/main_loop.md#world_update)* (в следующем кадре) - смотря что наступит раньше.


> **Notice:** Если вы переместили какие-то узлы и хотите выполнить обработчики событий на основе изменённых позиций в том же кадре, сначала нужно вызвать [World::updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void).


### Пример


Следующий пример позволяет создать ряд коробок, перемещающихся внутрь и наружу области World Trigger, генерируя события. Попадание внутрь World Trigger включает эмиссию для коробок, а выход из неё отключает эмиссию.


```cpp
// AppWorldLogic.cpp
/* .. */
#include "AppWorldLogic.h"
#include <UnigineObjects.h>
#include <UnigineGame.h>
#include <UnigineVisualizer.h>

using namespace Unigine;

using namespace Math;

WorldTriggerPtr trigger;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

const int MAX_OBJECTS = 10;
Vector<ObjectMeshStaticPtr> objects;

static void set_state(const NodePtr& node, const char* name, int value)
{
	ObjectPtr object = checked_ptr_cast<Object>(node);
	if (object.get() == NULL)
		return;

	for (int i = 0; i < object->getNumSurfaces(); i++)
	{
		MaterialPtr material = object->getMaterialInherit(i);
		if (material.get() == NULL)
			continue;
		int id = material->findState(name);
		if (id != -1)
			material->setState(id, value);
	}
}

static void trigger_enter(const NodePtr &node)
{
	set_state(node, "emission", 1);
}

static void trigger_leave(const NodePtr &node)
{
	set_state(node, "emission", 0);
}

int AppWorldLogic::init()
{

	// создаём триггер
	trigger = WorldTrigger::create(vec3(3.0f));

	trigger->getEventEnter().connect(econnections, &trigger_enter);
	trigger->getEventLeave().connect(econnections, &trigger_leave);

	// создаём объекты
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		ObjectMeshStaticPtr mesh = ObjectMeshStatic::create("cbox.mesh");
		mesh->setTriggerInteractionEnabled(true);
		mesh->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 0.0f, 0.0f, 1.0f), 0);
		objects.append(mesh);
	}

	// включаем визуализатор
	Visualizer::setEnabled(true);

	return 1;
}

int AppWorldLogic::update()
{

	trigger->renderVisualizer();
	float time = Game::getTime();

	float hsize = objects.size() / 2.0f;

	for (int i = 0; i < objects.size(); i++)
	{
		float x = Math::sin(time) * hsize - hsize + i;
		objects[i]->setWorldTransform(translate(Vec3(x, -x, 0.0f)));
	}

	return 1;
}

int AppWorldLogic::shutdown()
{

	objects.clear();

	// удаляем все подписки на события при завершении работы
	econnections.disconnectAll();

	return 1;
}


```


### See Also


- Видеоурок [How To Use World Triggers to Detect Nodes by Their Bounds](../../../videotutorials/how_to/how_to_cs/world_trigger.md)
- Статья [Event Handling](../../../code/fundamentals/events/index_cpp.md#triggers)
- Пример на C++
- Примеры на UnigineScript:

  -
  -
  -


## WorldTrigger Class

### Методы класса

## void setLeaveCallbackName ( const char * name )

Задаёт новое имя функции-обработчика, выполняемой при выходе из world trigger. Эта функция-обработчик задаётся через [getEventLeave()](#getEventLeave_Event).
### Аргументы

- *const char ** **name** - Имя функции-обработчика, выполняемой при выходе из world trigger.

## const char * getLeaveCallbackName () const

Возвращает текущее имя функции-обработчика, выполняемой при выходе из world trigger. Эта функция-обработчик задаётся через [getEventLeave()](#getEventLeave_Event).
### Возвращаемое значение

Текущее имя функции-обработчика, выполняемой при выходе из world trigger.
## void setEnterCallbackName ( const char * name )

Задаёт новое имя функции-обработчика, выполняемой при входе в world trigger. Эта функция-обработчик задаётся через [getEventEnter()](#getEventEnter_Event).
### Аргументы

- *const char ** **name** - Имя функции скрипта мира.

## const char * getEnterCallbackName () const

Возвращает текущее имя функции-обработчика, выполняемой при входе в world trigger. Эта функция-обработчик задаётся через [getEventEnter()](#getEventEnter_Event).
### Возвращаемое значение

Текущее имя функции скрипта мира.
## int getNumNodes () const

Возвращает текущее количество узлов, содержащихся в world trigger.
### Возвращаемое значение

Текущее количество узлов, содержащихся в world trigger.
## void setSize ( const Math:: vec3 & size )

Задаёт новые текущие размеры world trigger.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **size** - Текущие размеры world trigger.

## Math:: vec3 getSize () const

Возвращает текущие размеры world trigger.
### Возвращаемое значение

Текущие размеры world trigger.
## void setTouch ( bool touch )

Задаёт новое значение, указывающее, включён ли режим касания для триггера. При включённом режиме триггер будет реагировать на узел по частичному контакту. При отключённом - триггер реагирует, только если вся ограничивающая сфера/бокс попадает внутрь или наружу него.
### Аргументы

- *bool* **touch** - **true**, чтобы включить режим касания для триггера; **false** - чтобы отключить его.

## bool isTouch () const

Возвращает текущее значение, указывающее, включён ли режим касания для триггера. При включённом режиме триггер будет реагировать на узел по частичному контакту. При отключённом - триггер реагирует, только если вся ограничивающая сфера/бокс попадает внутрь или наружу него.
### Возвращаемое значение

**true**, если режим касания для триггера включён; иначе **false**.
## Event<const Ptr < Node > &> getEventLeave () const

Событие, генерируемое при выходе узла из world trigger. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Leave
void leave_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события Leave\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections leave_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventLeave().connect(leave_event_connections, leave_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventLeave().connect(leave_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события Leave (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
leave_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection leave_event_connection;

// подписываемся на событие Leave с функцией-обработчиком, сохраняя соединение
publisher->getEventLeave().connect(leave_event_connection, leave_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
leave_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
leave_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Leave через соединение
leave_event_connection.disconnect();

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

	// Обработчик события Leave, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события Leave\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventLeave().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId leave_handler_id;

// подписываемся на событие Leave с лямбда-обработчиком, сохраняя идентификатор соединения
leave_handler_id = publisher->getEventLeave().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события Leave (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventLeave().disconnect(leave_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Leave при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventLeave().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventLeave().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Node > &> getEventEnter () const

Событие, генерируемое при входе узла в world trigger. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Enter
void enter_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события Enter\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections enter_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEnter().connect(enter_event_connections, enter_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEnter().connect(enter_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события Enter (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
enter_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection enter_event_connection;

// подписываемся на событие Enter с функцией-обработчиком, сохраняя соединение
publisher->getEventEnter().connect(enter_event_connection, enter_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
enter_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
enter_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Enter через соединение
enter_event_connection.disconnect();

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

	// Обработчик события Enter, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события Enter\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEnter().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId enter_handler_id;

// подписываемся на событие Enter с лямбда-обработчиком, сохраняя идентификатор соединения
enter_handler_id = publisher->getEventEnter().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события Enter (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEnter().disconnect(enter_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Enter при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEnter().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEnter().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static WorldTriggerPtr create ( const Math:: vec3 & size )

Конструктор. Создаёт новый world trigger с заданными размерами.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размеры нового world trigger. Если переданы отрицательные значения, вместо них будет использовано **0**.

## void setExcludeNodes ( const Set < Ptr < Node >> & nodes )

Задаёт список исключённых узлов, на которые world trigger не будет реагировать.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Вектор исключённых узлов.

## Set < Ptr < Node >> getExcludeNodes ( ) const

Возвращает текущий список исключённых узлов, на которые world trigger не реагирует.
### Аргументы

## void setExcludeTypes ( const Set <int> & types )

Задаёт список исключённых типов узлов, на которые world trigger не будет реагировать.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<int> &* **types** - Вектор исключённых типов узлов.

## Set <int> getExcludeTypes ( ) const

Возвращает текущий список исключённых типов узлов, на которые world trigger не реагирует.
### Аргументы

## Ptr < Node > getNode ( int num ) const

Возвращает указанный узел, содержащийся в world trigger.
```cpp
#include <UnigineWorlds.h>

#include <UnigineInput.h>

using namespace Unigine;

WorldTriggerPtr trigger;

int AppWorldLogic::init()
{

	// создаём узел world trigger
	trigger = WorldTrigger::create(Math::vec3(3.0f));

	return 1;
}

int AppWorldLogic::update()
{
	// нажмите клавишу i, чтобы получить информацию об узлах внутри триггера
	if (trigger && Input::isKeyDown(Input::KEY_I))
	{
		// получаем количество узлов внутри триггера
		int numNodes = trigger->getNumNodes();
		Log::message("The number of nodes inside the trigger is %i \n", numNodes);

		// перебираем все узлы, чтобы вывести их имена и типы
		for (int i = 0; i < numNodes; i++)
		{
			NodePtr node = trigger->getNode(i);
			Log::message("The type of the %f node is %f \n", node->getName(), node->getType());
		}
	}
	return 1;
}


```


### Аргументы

- *int* **num** - Номер узла в диапазоне от 0 до общего количества узлов.

### Возвращаемое значение

Указатель на узел.
## Vector < Ptr < Node >> getNodes ( ) const

Получает узлы, содержащиеся в триггере.
### Аргументы

## void setTargetNodes ( const Set < Ptr < Node >> & nodes )

Задаёт список целевых узлов, которые будут вызывать колбэки. Если этот список пуст, колбэки вызывают все узлы.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **nodes** - Вектор целевых узлов.

## Set < Ptr < Node >> getTargetNodes ( ) const

Возвращает текущий список целевых узлов, вызывающих колбэки. Если этот список пуст, колбэки вызывают все узлы.
### Аргументы

## void setTargetTypes ( const Set <int> & types )

Задаёт список целевых типов узлов, которые будут вызывать колбэки. Если этот список пуст, колбэки вызывают все узлы.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<int> &* **types** - Вектор целевых типов узлов.

## Set <int> getTargetTypes ( ) const

Возвращает текущий список целевых типов узлов, вызывающих колбэки. Если этот список пуст, колбэки вызывают все узлы.
### Аргументы

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [World](../../../api/library/engine/class.world_cpp.md).
