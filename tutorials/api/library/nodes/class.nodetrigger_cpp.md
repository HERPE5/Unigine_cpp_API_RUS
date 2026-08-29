# Unigine::NodeTrigger Class (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Node


*[Trigger](../../../objects/nodes/trigger/index.md)* — это узел нулевого размера, не имеющий визуального представления и вызывающий события при:


- Включении/отключении (срабатывает событие *Enabled*).
- Изменении трансформации (срабатывает событие *Position*).


Узел *Trigger* обычно добавляется как дочерний узел к другому узлу, чтобы функции-обработчики выполнялись при включении/отключении или трансформации родительского узла.


Например, чтобы определить, был ли включён какой-либо узел (например, узел world clutter, отображающий узлы только вокруг камеры, которая его включила), узел *Trigger* добавляется как дочерний к этому узлу и выполняет соответствующую функцию.


### Создание узла-триггера


Чтобы создать узел *Trigger*, просто вызовите [constructor](#NodeTrigger) NodeTrigger, а затем добавьте узел как дочерний к другому узлу, для которого должны выполняться обработчики.


```cpp
#include <UnigineLogic.h>

using namespace Unigine;

class AppWorldLogic : public Unigine::WorldLogic {

public:

	virtual int init();
	virtual int update();

	/*...*/

private:

	ObjectMeshStaticPtr object;
	NodeTriggerPtr trigger;

	// экземпляр класса EventConnections для управления подписками на события
	EventConnections econnections;
};

```


```cpp
#include "AppWorldLogic.h"

using namespace Math;

int AppWorldLogic::init() {

	// создание меша
	object = ObjectMeshStatic::create("core/meshes/box.mesh");
	// изменение цвета albedo материала
	object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 0.0f, 0.0f, 1.0f), 0);

	// создание узла-триггера
	trigger = NodeTrigger::create();

	// добавление узла-триггера к статичному мешу как дочернего узла
	object->addWorldChild(trigger);

	return 1;
}


```


### Редактирование узла-триггера


Редактирование узла-триггера включает реализацию и указание обработчиков событий *Enabled* и *Position*, которые выполняются при включении или изменении позиции узла *Trigger* соответственно.


Обработчик события должен принимать как минимум **1** аргумент типа *NodeTrigger*. Кроме того, он также может принимать ещё 2 аргумента любого типа.


Обработчики событий задаются через указатели, указанные при подписке на следующие события: *[EventEnabled](#getEventEnabled_Event)* и *[EventPosition](#getEventPosition_Event)*.


```cpp
#include <UnigineLogic.h>
#include <UnigineGame.h>

using namespace Unigine;

class AppWorldLogic : public Unigine::WorldLogic {

public:

	virtual int init();
	virtual int update();

	/*...*/

private:

	ObjectMeshStaticPtr object;
	NodeTriggerPtr trigger;

	// экземпляр класса EventConnections для управления подписками на события
	EventConnections econnections;

	void position_event_handler(const NodeTriggerPtr &trigger)
	{
		Log::message("Позиция объекта изменена. Новая позиция: (%f %f %f)\n", trigger->getWorldPosition().x, trigger->getWorldPosition().y, trigger->getWorldPosition().z);
	}

	void enabled_event_handler(const NodeTriggerPtr &trigger)
	{
		Log::message("Флаг enabled: %d\n", trigger->isEnabled());
	}
};

```


```cpp
#include "AppWorldLogic.h"

using namespace Math;

int AppWorldLogic::init() {

	// создание меша
	object = ObjectMeshStatic::create("core/meshes/box.mesh");
	// изменение цвета albedo материала
	object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 0.0f, 0.0f, 1.0f), 0);

	// создание узла-триггера
	trigger = NodeTrigger::create();

	// добавление узла-триггера к статичному мешу как дочернего узла
	object->addWorldChild(trigger);

	// подписка на события Enabled и Position
	trigger->getEventEnabled().connect(econnections, this, &AppWorldLogic::enabled_event_handler);
	trigger->getEventPosition().connect(econnections, this, &AppWorldLogic::position_event_handler);

	return 1;
}

int AppWorldLogic::update()
{

	float time = Game::getTime();
	Vec3 pos = Vec3(Math::sin(time) * 2.0f, Math::cos(time) * 2.0f, 0.0f);
	object->setEnabled(pos.x > 0.0f || pos.y > 0.0f);
	object->setWorldPosition(pos);

	return 1;
}


```


### См. также


- Видеоурок [How To Use Node Triggers to Detect Changes in Node States](../../../videotutorials/how_to/how_to_cs/node_trigger.md)
- Статья [Event Handling](../../../code/fundamentals/events/index_cpp.md#triggers)
- Пример на C++


## Класс NodeTrigger

### Методы класса

## Event<const Ptr < NodeTrigger > &> getEventPosition () const

Событие, срабатывающее при изменении позиции узла-триггера. Обработчик события должен принимать *NodeTrigger* в качестве первого аргумента. Кроме того, он также может принимать **2** аргумента любого типа. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<NodeTrigger> & **trigger**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Position
void position_event_handler(const Ptr<NodeTrigger> & trigger)
{
	Log::message("\Обработка события Position\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections position_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventPosition().connect(position_event_connections, position_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventPosition().connect(position_event_connections, [](const Ptr<NodeTrigger> & trigger) {
		Log::message("\Обработка события Position (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
position_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection position_event_connection;

// подписываемся на событие Position с функцией-обработчиком, сохраняя соединение
publisher->getEventPosition().connect(position_event_connection, position_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
position_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
position_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Position через соединение
position_event_connection.disconnect();

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

	// Обработчик события Position, реализованный как член класса
	void event_handler(const Ptr<NodeTrigger> & trigger)
	{
		Log::message("\Обработка события Position\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventPosition().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId position_handler_id;

// подписываемся на событие Position с лямбда-обработчиком, сохраняя идентификатор соединения
position_handler_id = publisher->getEventPosition().connect(e_connections, [](const Ptr<NodeTrigger> & trigger) {
		Log::message("\Обработка события Position (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventPosition().disconnect(position_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Position при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventPosition().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventPosition().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < NodeTrigger > &> getEventEnabled () const

Событие, срабатывающее при включении или отключении узла-триггера. Обработчик события должен принимать *NodeTrigger* в качестве первого аргумента. Кроме того, он также может принимать **2** аргумента любого типа. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<NodeTrigger> & **trigger**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Enabled
void enabled_event_handler(const Ptr<NodeTrigger> & trigger)
{
	Log::message("\Обработка события Enabled\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections enabled_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEnabled().connect(enabled_event_connections, enabled_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEnabled().connect(enabled_event_connections, [](const Ptr<NodeTrigger> & trigger) {
		Log::message("\Обработка события Enabled (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
enabled_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection enabled_event_connection;

// подписываемся на событие Enabled с функцией-обработчиком, сохраняя соединение
publisher->getEventEnabled().connect(enabled_event_connection, enabled_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
enabled_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
enabled_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Enabled через соединение
enabled_event_connection.disconnect();

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

	// Обработчик события Enabled, реализованный как член класса
	void event_handler(const Ptr<NodeTrigger> & trigger)
	{
		Log::message("\Обработка события Enabled\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEnabled().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId enabled_handler_id;

// подписываемся на событие Enabled с лямбда-обработчиком, сохраняя идентификатор соединения
enabled_handler_id = publisher->getEventEnabled().connect(e_connections, [](const Ptr<NodeTrigger> & trigger) {
		Log::message("\Обработка события Enabled (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEnabled().disconnect(enabled_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Enabled при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEnabled().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEnabled().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static NodeTriggerPtr create ( )

Конструктор. Создаёт новый узел-триггер.
## void setEnabledCallbackName ( const char * name )

Задаёт функцию обратного вызова, срабатывающую при включении узла-триггера. Функция обратного вызова должна быть реализована в скрипте мира (на стороне UnigineScript). Функция обратного вызова может не принимать аргументов, принимать *[Node](../../../api/library/nodes/class.node_cpp.md)* или *NodeTrigger*.
> **Notice:** Метод позволяет задавать callback только с **0** или **1** аргументом.

На стороне UnigineScript:
```cpp
// реализация callback'а enabled
void enabled_callback(Node node) {
	log.message("Флаг enabled: %d\n", node.isEnabled());
}

```

 На стороне C++:
```cpp
int AppWorldLogic::init() {

	// создание узла-триггера
	trigger = NodeTrigger::create();

	// задание функции-обработчика события enabled, выполняемой при включении/отключении узла

	trigger->setEnabledCallbackName("enabled_event_handler");

	return 1;
}


```


### Аргументы

- *const char ** **name** - Имя функции обратного вызова, реализованной в скрипте мира (сторона UnigineScript).

## const char * getEnabledCallbackName ( ) const

Возвращает имя функции обратного вызова, срабатывающей при включении узла-триггера. Эта функция обратного вызова задаётся через *[setEnabledCallbackName()](#setEnabledCallbackName_cstr_void)*.
### Возвращаемое значение

Имя функции обратного вызова, реализованной в скрипте мира (сторона UnigineScript).
## void setPositionCallbackName ( const char * name )

Задаёт функцию обратного вызова, срабатывающую при изменении позиции узла-триггера. Функция обратного вызова должна быть реализована в скрипте мира (на стороне UnigineScript). Функция обратного вызова может не принимать аргументов, принимать *[Node](../../../api/library/nodes/class.node_cpp.md)* или *NodeTrigger*.
> **Notice:** Метод позволяет задавать callback только с **0** или **1** аргументом.

На стороне UnigineScript:
```cpp
// реализация callback'а position
void position_changed(NodeTriggerPtr trigger) {
	log.message("Новая позиция узла: %s\n", typeinfo(node.getWorldPosition()));
}

```

 На стороне C++:
```cpp
int AppWorldLogic::init() {

	// создание узла-триггера
	trigger = NodeTrigger::create();

	// задание функции-обработчика события position, выполняемой при изменении позиции узла

	trigger->setPositionCallbackName("position_event_handler");

	return 1;
}


```


### Аргументы

- *const char ** **name** - Имя функции обратного вызова, реализованной в скрипте мира (сторона UnigineScript).

## const char * getPositionCallbackName ( ) const

Возвращает имя функции обратного вызова, срабатывающей при изменении позиции узла-триггера. Эта функция задаётся с помощью функции *[setPositionCallbackName()](#setPositionCallbackName_cstr_void)*.
### Возвращаемое значение

Имя функции обратного вызова, реализованной в скрипте мира (сторона UnigineScript).
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа *[NodeTrigger](../../../api/library/nodes/class.node_cpp.md#NODE_TRIGGER)*.
