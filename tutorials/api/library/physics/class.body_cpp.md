# Unigine::Body Class (CPP)

**Header:** #include <UniginePhysics.h>


Этот класс используется для симуляции [physical bodies](../../../principles/physics/bodies/index.md), которые позволяют объекту участвовать в физических взаимодействиях. Телу может быть назначена одна или несколько коллизионных [shapes](../../../api/library/physics/class.shape_cpp.md), а также тела могут быть соединены между собой с помощью [joints](../../../api/library/physics/class.joint_cpp.md).


> **Notice:** Максимальное количество коллизионных форм для одного тела ограничено 32768.


Для трансформации тела можно использовать один из следующих методов:

- **[setTransform()](../../...md#setTransform_Mat4_void)**
- **[setPreserveTransform()](../../...md#setPreserveTransform_Mat4_void)**
- **[setVelocityTransform()](../../...md#setVelocityTransform_Mat4_void)**

Все эти функции вступают в силу после завершения физических расчётов и выполнения **[updatePhysics()](../../../code/fundamentals/execution_sequence/main_loop.md#physics)**. Только после этого трансформации тела применяются к отрисовываемому узлу. Если узел нужно трансформировать сразу вслед за его физическим телом, следует вызвать **[flushTransform()](../../...md#flushTransform_void)**.
Симуляцию тела можно [frozen](../../../principles/physics/bodies/index.md#freezing) (если установлен флаг *[Frozen](#setFrozen_int_void)*).


Тела взаимодействуют друг с другом через joints или контакты. Контакт может обрабатываться любым из участвующих в нём тел. То, какому телу назначается контакт, определяется случайным образом. Если контакт назначен телу и обрабатывается им, он называется **внутренним** (internal), в противном случае — **внешним** (external, обрабатывается другим телом). Общее количество контактов тела включает как внутренние, так и внешние. Перебор внутренних контактов выполняется значительно быстрее, чем внешних, поэтому может быть полезно, чтобы определённое тело обрабатывало большую часть контактов, в которых оно участвует. Для твёрдого тела (rigid body) это можно сделать, повысив его приоритет через **[BodyRigid::setHighPriorityContacts()](../../../api/library/physics/class.bodyrigid_cpp.md#setHighPriorityContacts_int_void)**.


Внутри тела контакты обозначаются своими **номерами** в диапазоне от 0 до [total number of contacts](#getNumContacts_int). Также глобально каждый контакт имеет ID, по которому на него можно ссылаться.


Вы можете подписаться на определённые события тела для их обработки:


- *[Frozen](#getEventFrozen_Event)* - для выполнения определённых действий при [freezes/unfreezes](../../../principles/physics/bodies/index.md#freezing) тела.
- *[Position](#getEventPosition_Event)* - для выполнения определённых действий при изменении позиции тела.
- *[ContactEnter](#getEventContactEnter_Event)* - для выполнения определённых действий при возникновении контакта (тело начинает касаться другого тела или коллизионной поверхности).
- *[ContactLeave](#getEventContactLeave_Event)* - для выполнения определённых действий при завершении контакта (тело перестаёт касаться другого тела или коллизионной поверхности).
- *[Contacts](#getEventContacts_Event)* - для получения **всех контактов** тела, включая новые (enter) и завершающиеся (leave). Контакты leave удаляются после этапа выполнения колбэка, так что это единственный момент, когда их ещё можно получить.


### См. также


- Пример использования [Creating and Attaching a Cloth](../../../code/usage/cloth_particle_joint/index_cpp.md), демонстрирующий создание объектов, назначение тел и добавление форм к ним
- C++ sample

  -
  -
  -
- Пример использования [Handling Contacts on Collision](../../../code/usage/handling_contacts_on_collision/index_cpp.md)


## Body Class

### Перечисления

## TYPE

Type of the body defining its physical properties.
| Name | Description |
|---|---|
| **BODY_DUMMY** = 0 | This body is used to create an immovable collider for an object. |
| **BODY_RIGID** = 1 | This is a basic type of body describing a rigid object. |
| **BODY_RAGDOLL** = 2 | This body contains joints connecting parts of the body (represented with [rigid bodies](#BODY_RIGID)). |
| **BODY_FRACTURE** = 3 | This body simulates breakable objects. |
| **BODY_ROPE** = 4 | This body simulates ropes. |
| **BODY_CLOTH** = 5 | This body simulates cloth. |
| **BODY_WATER** = 6 | This body simulates water and other fluids. |
| **BODY_PATH** = 7 | This body simulates a path along which rigid bodies are moving, for example, like a train along the railtrack. |
| **NUM_BODIES** = 8 | The number of bodies. |

### Методы класса

## int getNumContacts () const

Returns the current total number of contacts in which the body participates. It includes internal (handled by the body) and external [contacts](#contacts) (handled by other bodies).
### Возвращаемое значение

Current number of [contacts](#contacts).
## int getNumJoints () const

Returns the current number of joints in the body.
### Возвращаемое значение

Current number of joints in the body.
## int getNumShapes () const

Returns the current number of shapes comprising the body.
### Возвращаемое значение

Current number of shapes.
## int getNumChildren () const

Returns the current number of child bodies.
### Возвращаемое значение

Current number of children.
## void setRotation ( const Math:: quat & rotation )

Sets a new rotation in the world coordinates.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md)&* **rotation** - The rotation in the world coordinates.

## Math:: quat getRotation () const

Returns the current rotation in the world coordinates.
### Возвращаемое значение

Current rotation in the world coordinates.
## void setPosition ( const Math:: Vec3 & position )

Sets a new body position (in world coordinates). When setting the value, body's linear and angular velocities will be reset to **0**.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md)&* **position** - The position in the world coordinates.

## Math:: Vec3 getPosition () const

Returns the current body position (in world coordinates). When setting the value, body's linear and angular velocities will be reset to **0**.
### Возвращаемое значение

Current position in the world coordinates.
## void setTransform ( const Math:: Mat4 & transform )

Sets a new transformation matrix of the body (in world coordinates). This matrix describes position and orientation of the body. When setting the value, the body's linear and angular velocities are reset to defaults, forces and torques are set to zeros, counted down frozen frames are nullified. Setting the value is required, for example, when the node is dragged to a new position in the editor.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)&* **transform** - The transformation matrix. This matrix describes position, orientation and scale of the body.

## Math:: Mat4 getTransform () const

Returns the current transformation matrix of the body (in world coordinates). This matrix describes position and orientation of the body. When setting the value, the body's linear and angular velocities are reset to defaults, forces and torques are set to zeros, counted down frozen frames are nullified. Setting the value is required, for example, when the node is dragged to a new position in the editor.
### Возвращаемое значение

Current transformation matrix. This matrix describes position, orientation and scale of the body.
## void setPhysicalMask ( int mask )

Sets a new bit mask for interactions with [physicals](../../../api/library/physics/class.physical_cpp.md). Two objects interact, if they both have matching masks.
### Аргументы

- *int* **mask** - The integer, each bit of which is a mask.

## int getPhysicalMask () const

Returns the current bit mask for interactions with [physicals](../../../api/library/physics/class.physical_cpp.md). Two objects interact, if they both have matching masks.
### Возвращаемое значение

Current integer, each bit of which is a mask.
## void setName ( const char * name )

Sets a new name of the body.
### Аргументы

- *const char ** **name** - The name of the body.

## const char * getName () const

Returns the current name of the body.
### Возвращаемое значение

Current name of the body.
## void setGravity ( bool gravity )

Sets a new value indicating if [gravity](../../../api/library/physics/class.physics_cpp.md#setGravity_vec3_void) is affecting the body.
### Аргументы

- *bool* **gravity** - Set **true** to enable the body is affected by gravity; **false** - to disable it.

## bool isGravity () const

Returns the current value indicating if [gravity](../../../api/library/physics/class.physics_cpp.md#setGravity_vec3_void) is affecting the body.
### Возвращаемое значение

**true** if the body is affected by gravity; otherwise **false**.
## void setImmovable ( bool immovable )

Sets a new value indicating if the body is immovable (static).
### Аргументы

- *bool* **immovable** - Set **true** to enable the body is immovable (static); **false** - to disable it.

## bool isImmovable () const

Returns the current value indicating if the body is immovable (static).
### Возвращаемое значение

**true** if the body is immovable (static); otherwise **false**.
## void setFrozen ( bool frozen )

Sets a new value indicating if the body is [frozen](../../../principles/physics/bodies/index.md#frozen_velocities). When a body is frozen, it is not simulated (though its contacts are still calculated), until a collision with a frozen body occurs or some force is applied.
### Аргументы

- *bool* **frozen** - Set **true** to enable the body frozen status; **false** - to disable it.

## bool isFrozen () const

Returns the current value indicating if the body is [frozen](../../../principles/physics/bodies/index.md#frozen_velocities). When a body is frozen, it is not simulated (though its contacts are still calculated), until a collision with a frozen body occurs or some force is applied.
### Возвращаемое значение

**true** if the body frozen status is enabled; otherwise **false**.
## bool isEnabledSelf () const

Returns the current value indicating if the body is enabled.
### Возвращаемое значение

**true** if the body is enabled; otherwise **false**.
## void setEnabled ( bool enabled )

Sets a new value indicating if physical interactions with the body are enabled.
### Аргументы

- *bool* **enabled** - Set **true** to enable physical interactions with the body; **false** - to disable it.

## bool isEnabled () const

Returns the current value indicating if physical interactions with the body are enabled.
### Возвращаемое значение

**true** if physical interactions with the body is enabled; otherwise **false**.
## const char * getTypeName () const

Returns the current name of the body type.
### Возвращаемое значение

Current name of the body type.
## Body::TYPE getType () const

Returns the current type of the body.
### Возвращаемое значение

Current type of the body, one of the *[BODY_*](#BODY_RIGID)* pre-defined variables.
## void setID ( int id )

Sets a new unique ID of the body.
### Аргументы

- *int* **id** - The unique ID of the body.

## int getID () const

Returns the current unique ID of the body.
### Возвращаемое значение

Current unique ID of the body.
## void setObject ( const Ptr < Object >& object )

Sets a new object whose physical properties and behavior are defined by this body.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)>&* **object** - The object whose physical properties and behavior are defined by this body.

## Ptr < Object > getObject () const

Returns the current object whose physical properties and behavior are defined by this body.
### Возвращаемое значение

Current object whose physical properties and behavior are defined by this body.
## Ptr < Body > getParent () const

Returns the current parent of the body.
### Возвращаемое значение

Current parent of the body.
## Math:: vec3 getDirection () const

Returns the current normalized direction vector of the body (in world coordinates). By default, a direction vector points along **-Z** axis. It always has an unit length.
### Возвращаемое значение

Current normalized direction vector in the world coordinates.
## Event<const Ptr < Body > &> getEventContacts () const

Событие, срабатывающее после добавления новых контактов и перед удалением тех, что перестают существовать. Это событие можно использовать для получения **всех контактов** тела, включая новые (*enter*) и завершающиеся (*leave*). Контакты *Leave* удаляются после срабатывания события, так что это единственный момент, когда их ещё можно получить. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** События, основанные на физике, выполняются в главном потоке, так как они в основном используются для создания, уничтожения или изменения других объектов.


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Body> & **body**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Contacts
void contacts_event_handler(const Ptr<Body> & body)
{
	Log::message("\Обработка события Contacts\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections contacts_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventContacts().connect(contacts_event_connections, contacts_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventContacts().connect(contacts_event_connections, [](const Ptr<Body> & body) {
		Log::message("\Обработка события Contacts (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
contacts_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection contacts_event_connection;

// подписываемся на событие Contacts с функцией-обработчиком, сохраняя соединение
publisher->getEventContacts().connect(contacts_event_connection, contacts_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
contacts_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
contacts_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Contacts через соединение
contacts_event_connection.disconnect();

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

	// Обработчик события Contacts, реализованный как член класса
	void event_handler(const Ptr<Body> & body)
	{
		Log::message("\Обработка события Contacts\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventContacts().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId contacts_handler_id;

// подписываемся на событие Contacts с лямбда-обработчиком, сохраняя идентификатор соединения
contacts_handler_id = publisher->getEventContacts().connect(e_connections, [](const Ptr<Body> & body) {
		Log::message("\Обработка события Contacts (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventContacts().disconnect(contacts_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Contacts при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventContacts().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventContacts().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Body > &, int> getEventContactLeave () const

Событие, срабатывающее при завершении контакта с телом (тело перестаёт касаться другого тела). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** События, основанные на физике, выполняются в главном потоке, так как они в основном используются для создания, уничтожения или изменения других объектов.


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Body> & **body**, int **contact_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ContactLeave
void contactleave_event_handler(const Ptr<Body> & body,  int contact_id)
{
	Log::message("\Обработка события ContactLeave\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections contactleave_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventContactLeave().connect(contactleave_event_connections, contactleave_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventContactLeave().connect(contactleave_event_connections, [](const Ptr<Body> & body,  int contact_id) {
		Log::message("\Обработка события ContactLeave (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
contactleave_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection contactleave_event_connection;

// подписываемся на событие ContactLeave с функцией-обработчиком, сохраняя соединение
publisher->getEventContactLeave().connect(contactleave_event_connection, contactleave_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
contactleave_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
contactleave_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ContactLeave через соединение
contactleave_event_connection.disconnect();

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

	// Обработчик события ContactLeave, реализованный как член класса
	void event_handler(const Ptr<Body> & body,  int contact_id)
	{
		Log::message("\Обработка события ContactLeave\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventContactLeave().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId contactleave_handler_id;

// подписываемся на событие ContactLeave с лямбда-обработчиком, сохраняя идентификатор соединения
contactleave_handler_id = publisher->getEventContactLeave().connect(e_connections, [](const Ptr<Body> & body,  int contact_id) {
		Log::message("\Обработка события ContactLeave (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventContactLeave().disconnect(contactleave_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ContactLeave при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventContactLeave().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventContactLeave().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Body > &, int> getEventContactEnter () const

Событие, срабатывающее при возникновении контакта с телом (тело начинает касаться другого тела). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** События, основанные на физике, выполняются в главном потоке, так как они в основном используются для создания, уничтожения или изменения других объектов.


<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события ContactEnter
void contactenter_event_handler(const Ptr<Body> & body,  int contact_id)
{
	Log::message("\Обработка события ContactEnter\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections contactenter_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
body->getEventContactEnter().connect(contactenter_event_connections, contactenter_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
body->getEventContactEnter().connect(contactenter_event_connections, [](const Ptr<Body> & body,  int contact_id) {
		Log::message("\Обработка события ContactEnter (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
contactenter_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection contactenter_event_connection;

// подписываемся на событие ContactEnter с функцией-обработчиком, сохраняя соединение
body->getEventContactEnter().connect(contactenter_event_connection, contactenter_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
contactenter_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
contactenter_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ContactEnter через соединение
contactenter_event_connection.disconnect();

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

	// Обработчик события ContactEnter, реализованный как член класса
	void event_handler(const Ptr<Body> & body,  int contact_id)
	{
		Log::message("\Обработка события ContactEnter\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
body->getEventContactEnter().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. Можно подписываться и отписываться напрямую через функцию-обработчик
//////////////////////////////////////////////////////////////////////////////

// подписываемся на событие ContactEnter с функцией-обработчиком
body->getEventContactEnter().connect(contactenter_event_handler);

// удаляем подписку на событие ContactEnter позже через функцию-обработчик
body->getEventContactEnter().disconnect(contactenter_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Подписка на событие с сохранением идентификатора и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId contactenter_handler_id;

// подписываемся на событие ContactEnter с лямбда-обработчиком, сохраняя идентификатор соединения
contactenter_handler_id = body->getEventContactEnter().connect([](const Ptr<Body> & body,  int contact_id) {
		Log::message("\Обработка события ContactEnter (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
body->getEventContactEnter().disconnect(contactenter_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Игнорирование всех событий ContactEnter при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
body->getEventContactEnter().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
body->getEventContactEnter().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Body> & **body**, int **contact_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ContactEnter
void contactenter_event_handler(const Ptr<Body> & body,  int contact_id)
{
	Log::message("\Обработка события ContactEnter\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections contactenter_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventContactEnter().connect(contactenter_event_connections, contactenter_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventContactEnter().connect(contactenter_event_connections, [](const Ptr<Body> & body,  int contact_id) {
		Log::message("\Обработка события ContactEnter (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
contactenter_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection contactenter_event_connection;

// подписываемся на событие ContactEnter с функцией-обработчиком, сохраняя соединение
publisher->getEventContactEnter().connect(contactenter_event_connection, contactenter_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
contactenter_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
contactenter_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ContactEnter через соединение
contactenter_event_connection.disconnect();

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

	// Обработчик события ContactEnter, реализованный как член класса
	void event_handler(const Ptr<Body> & body,  int contact_id)
	{
		Log::message("\Обработка события ContactEnter\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventContactEnter().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId contactenter_handler_id;

// подписываемся на событие ContactEnter с лямбда-обработчиком, сохраняя идентификатор соединения
contactenter_handler_id = publisher->getEventContactEnter().connect(e_connections, [](const Ptr<Body> & body,  int contact_id) {
		Log::message("\Обработка события ContactEnter (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventContactEnter().disconnect(contactenter_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ContactEnter при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventContactEnter().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventContactEnter().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Body > &> getEventPosition () const

Событие, срабатывающее, когда заданное тело перемещается на определённое расстояние (поворот не учитывается). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** События, основанные на физике, выполняются в главном потоке, так как они в основном используются для создания, уничтожения или изменения других объектов.


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Body> & **body**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Position
void position_event_handler(const Ptr<Body> & body)
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
publisher->getEventPosition().connect(position_event_connections, [](const Ptr<Body> & body) {
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
	void event_handler(const Ptr<Body> & body)
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
position_handler_id = publisher->getEventPosition().connect(e_connections, [](const Ptr<Body> & body) {
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
## Event<const Ptr < Body > &> getEventFrozen () const

Событие, срабатывающее, когда заданное тело [freezes/unfreezes](#isFrozen_int) (т.е. изменяется его состояние *Frozen*). Используйте **[isFrozen()](../../...md#isFrozen_int)**, чтобы определить, заморожено ли тело в данный момент. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** События, основанные на физике, выполняются в главном потоке, так как они в основном используются для создания, уничтожения или изменения других объектов.


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Body> & **body**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Frozen
void frozen_event_handler(const Ptr<Body> & body)
{
	Log::message("\Обработка события Frozen\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections frozen_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventFrozen().connect(frozen_event_connections, frozen_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventFrozen().connect(frozen_event_connections, [](const Ptr<Body> & body) {
		Log::message("\Обработка события Frozen (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
frozen_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection frozen_event_connection;

// подписываемся на событие Frozen с функцией-обработчиком, сохраняя соединение
publisher->getEventFrozen().connect(frozen_event_connection, frozen_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
frozen_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
frozen_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Frozen через соединение
frozen_event_connection.disconnect();

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

	// Обработчик события Frozen, реализованный как член класса
	void event_handler(const Ptr<Body> & body)
	{
		Log::message("\Обработка события Frozen\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventFrozen().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId frozen_handler_id;

// подписываемся на событие Frozen с лямбда-обработчиком, сохраняя идентификатор соединения
frozen_handler_id = publisher->getEventFrozen().connect(e_connections, [](const Ptr<Body> & body) {
		Log::message("\Обработка события Frozen (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventFrozen().disconnect(frozen_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Frozen при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventFrozen().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventFrozen().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## Ptr < Body > createBody ( int type )

Создаёт новое тело указанного типа.
### Аргументы

- *int* **type** - Тип тела. Одно из значений [BODY_*](#BODY_CLOTH).

### Возвращаемое значение

Умный указатель на новое созданное тело.
## Ptr < Body > createBody ( const char * type_name )

Создаёт новое тело указанного типа.
### Аргументы

- *const char ** **type_name** - Имя типа тела.

### Возвращаемое значение

Умный указатель на новое созданное тело.
## const char * getTypeName ( int type )

Возвращает имя типа тела с указанным ID.
### Аргументы

- *int* **type** - ID типа тела. Одно из значений [BODY_*](#BODY_CLOTH).

### Возвращаемое значение

Имя типа тела.
## bool setObject ( const Ptr < Object > & object , bool update )

Задаёт объект, который аппроксимирует тело.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Аппроксимируемый объект.
- *bool* **update** - Флаг обновления: true, чтобы обновить объект после назначения тела (по умолчанию), false — не обновлять сразу после назначения тела.

### Возвращаемое значение

true, если тело успешно назначено указанному объекту; иначе false.
## void setPreserveTransform ( const Math:: Mat4 & transform )

Задаёт матрицу трансформации тела (в мировых координатах). Этот метод безопасно сохраняет линейную и угловую скорости тела. Он изменяет только координаты тела — все остальные параметры тела остаются прежними.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации. Эта матрица описывает позицию, ориентацию и масштаб тела.

## void setVelocityTransform ( const Math:: Mat4 & transform )

Задаёт матрицу трансформации (в мировых координатах) и вычисляет линейную и угловую скорости тела в зависимости от его траектории от текущей позиции до указанной. Время, используемое в расчётах, соответствует [physics ticks](../../../api/library/physics/class.physics_cpp.md#setIFps_float_void). Обнуляет силы и моменты сил и обнуляет отсчитанные замороженные кадры.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации. Эта матрица описывает позицию, ориентацию и масштаб тела.

## void flushTransform ( ) const

Принудительно устанавливает трансформации тела для узла.
## void setDirection ( const Math:: vec3 & dir , const Math:: vec3 & up )

Обновляет вектор направления тела (в мировых координатах). По умолчанию вектор направления указывает вдоль оси **-Z**. Эта функция изменяет его направление и переориентирует тело.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **dir** - Новый вектор направления в мировых координатах. Вектор направления всегда имеет единичную длину.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **up** - Новый вектор "вверх" в мировых координатах.

## int isChild ( const Ptr < Body > & body ) const

Проверяет, является ли указанное тело дочерним для данного тела.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Проверяемое тело.

### Возвращаемое значение

**1**, если указанное тело является дочерним; иначе **0**.
## int findChild ( const char * name ) const

Ищет дочернее тело с указанным именем.
### Аргументы

- *const char ** **name** - Имя дочернего тела.

### Возвращаемое значение

Номер дочернего тела в списке дочерних тел, если оно найдено; иначе **-1**.
## Ptr < Body > getChild ( int num ) const

Возвращает указанное дочернее тело.
### Аргументы

- *int* **num** - Номер дочернего тела.

### Возвращаемое значение

Соответствующее тело.
## void addShape ( const Ptr < Shape > & shape , const Math:: mat4 & transform )

Добавляет форму (shape) в список форм, составляющих тело.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Новая добавляемая форма.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации формы (в системе координат тела).

## void addShape ( const Ptr < Shape > & shape )

Добавляет форму (shape) в список форм, составляющих тело.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Новая добавляемая форма.

## void removeShape ( const Ptr < Shape > & shape , bool destroy = false )

Удаляет указанную форму из тела.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Удаляемая форма.
- *bool* **destroy** - Флаг, указывающий, следует ли уничтожить форму после удаления: используйте true, чтобы уничтожить форму после удаления, или false, если планируете использовать форму позже. Значение по умолчанию: false.

## void removeShape ( int num , bool destroy = false )

Удаляет форму с указанным номером из тела.
### Аргументы

- *int* **num** - Номер формы.
- *bool* **destroy** - Флаг, указывающий, следует ли уничтожить форму после удаления: используйте true, чтобы уничтожить форму после удаления, или false, если планируете использовать форму позже. Значение по умолчанию: false.

## void clearShapes ( int destroy = 0 )

Очищает все формы тела.
### Аргументы

- *int* **destroy** - Флаг, указывающий, следует ли уничтожить формы после удаления: используйте 1, чтобы уничтожить формы после удаления, или 0, если планируете использовать их позже. Значение по умолчанию: 0.

## int isShape ( const Ptr < Shape > & shape ) const

Проверяет, принадлежит ли указанная форма телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Проверяемая форма.

### Возвращаемое значение

**1**, если форма принадлежит телу; иначе **0**.
## bool insertShape ( int pos , const Ptr < Shape > & shape )

Вставляет указанную форму в заданную позицию в списке форм тела.
### Аргументы

- *int* **pos** - Позиция в списке, в которую вставляется форма, в диапазоне от 0 до [number of shapes](#getNumShapes_int).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Вставляемая [shape](../../../api/library/physics/class.shape_cpp.md).

### Возвращаемое значение

true, если форма успешно вставлена; иначе false.
## bool insertShape ( int pos , const Ptr < Shape > & shape , const Math:: mat4 & transform )

Вставляет указанную форму в заданную позицию в списке форм тела и задаёт для неё указанную трансформацию.
### Аргументы

- *int* **pos** - Позиция в списке, в которую вставляется форма, в диапазоне от 0 до [number of shapes](#getNumShapes_int).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shape](../../../api/library/physics/class.shape_cpp.md)> &* **shape** - Вставляемая [shape](../../../api/library/physics/class.shape_cpp.md).
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Трансформация формы (в системе координат тела).

### Возвращаемое значение

true, если форма успешно вставлена; иначе false.
## int findShape ( const char * name ) const

Ищет форму с указанным именем.
### Аргументы

- *const char ** **name** - Имя формы.

### Возвращаемое значение

Номер формы в списке форм, если она найдена; иначе **-1**.
## Ptr < Shape > getShape ( int num ) const

Возвращает указанную форму.
### Аргументы

- *int* **num** - Номер формы.

### Возвращаемое значение

Соответствующий объект формы.
## void setShapeTransform ( int num , const Math:: mat4 & transform )

Задаёт матрицу трансформации указанной формы (в локальных координатах). Эта матрица описывает позицию и ориентацию формы.
### Аргументы

- *int* **num** - Номер формы.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации (в системе координат тела).

## Math:: mat4 getShapeTransform ( int num ) const

Возвращает матрицу трансформации указанной формы (в локальных координатах). Эта матрица описывает позицию и ориентацию формы.
### Аргументы

- *int* **num** - Номер формы.

### Возвращаемое значение

Матрица трансформации.
## void updateShapes ( )

Обновляет все [shapes](#addShape_Shape_void) тела.
## void addJoint ( const Ptr < Joint > & joint )

Добавляет joint к телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Joint](../../../api/library/physics/class.joint_cpp.md)> &* **joint** - Новый добавляемый joint.

## void removeJoint ( const Ptr < Joint > & joint )

Удаляет указанный joint из тела.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Joint](../../../api/library/physics/class.joint_cpp.md)> &* **joint** - Удаляемый joint.

## void removeJoint ( int num )

Удаляет joint с указанным номером из тела.
### Аргументы

- *int* **num** - Номер joint.

## void insertJoint ( const Ptr < Joint > & joint , int num )

Вставляет указанный joint в заданную позицию в списке joints тела.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Joint](../../../api/library/physics/class.joint_cpp.md)> &* **joint** - Вставляемый [joint](../../../api/library/physics/class.joint_cpp.md).
- *int* **num** - Позиция в списке, в которую вставляется joint, в диапазоне от 0 до [number of joints](#getNumJoints_int).

## int isJoint ( const Ptr < Joint > & joint ) const

Проверяет, принадлежит ли указанный joint телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Joint](../../../api/library/physics/class.joint_cpp.md)> &* **joint** - Проверяемый joint.

### Возвращаемое значение

**1**, если joint принадлежит телу; иначе **0**.
## int findJoint ( const char * name ) const

Ищет joint с указанным именем.
### Аргументы

- *const char ** **name** - Имя joint.

### Возвращаемое значение

Номер joint в списке joints, если он найден; иначе **-1**.
## Ptr < Joint > getJoint ( int num ) const

Возвращает указанный joint.
### Аргументы

- *int* **num** - Номер joint.

### Возвращаемое значение

Соответствующий joint.
## Ptr < Shape > getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 , int mask , Math:: Vec3 * OUT_ret_point , Math:: vec3 * OUT_ret_normal )


Выполняет трассировку от точки p0 до точки p1 для поиска формы тела, пересекаемой этой линией. Пересечение находится только для объектов с совпадающей маской пересечений. В случае успеха *ret_point* и *ret_normal* будут содержать информацию о пересечении.


> **Notice:** Для этой функции используются координаты мирового пространства.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии (в мировых координатах).
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии (в мировых координатах).
- *int* **mask** - Маска пересечений.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_point** - Контейнер, в который будут помещены координаты точки [contact](#contacts) (если есть), в мировой системе координат. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **OUT_ret_normal** - Контейнер, в который будут помещены координаты нормали точки [contact](#contacts) (если есть), в мировой системе координат. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

### Возвращаемое значение

Первая пересечённая форма, если найдена; иначе 0.
## unsigned long long getContactID ( int num ) const

Возвращает ID контакта по номеру [contact](#contacts).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

ID контакта.
## int findContactByID ( unsigned long long id ) const

Возвращает номер [contact](#contacts) по его ID.
### Аргументы

- *unsigned long long* **id** - ID контакта.

### Возвращаемое значение

Номер [contact](#contacts) с указанным ID, если он существует; иначе -1.
## bool isContactInternal ( int num ) const

Возвращает значение, указывающее, является ли [contact](#contacts) с указанным номером внутренним (обрабатывается телом) или нет (обрабатывается другим телом). Контакт может обрабатываться любым из участвующих в нём тел. То, какому телу назначается контакт, определяется случайным образом. Если контакт назначен телу и обрабатывается им, он называется *внутренним*, в противном случае — *внешним* (обрабатывается другим телом). Общее количество контактов тела включает как внутренние, так и внешние. Перебор внутренних контактов выполняется значительно быстрее, чем внешних, поэтому может быть полезно, чтобы определённое тело обрабатывало большую часть контактов, в которых оно участвует. Для твёрдого тела это можно сделать, повысив его приоритет через **[BodyRigid::setHighPriorityContacts()](../../../api/library/physics/class.bodyrigid_cpp.md#setHighPriorityContacts_int_void)**.
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

true, если контакт с указанным номером является внутренним; иначе false.
## bool isContactEnter ( int num ) const

Возвращает значение, указывающее, начало ли тело касаться другого тела в точке [contact](#contacts) с указанным номером (контакт только что возник).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

true, если тело начало касаться другого тела в точке контакта с указанным номером (контакт только что возник); иначе false.
## bool isContactLeave ( int num ) const

Возвращает значение, указывающее, перестало ли тело касаться другого тела в точке [contact](#contacts) с указанным номером.
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

true, если тело перестало касаться другого тела в точке контакта с указанным номером; иначе false.
## bool isContactStay ( int num ) const

Возвращает значение, указывающее, продолжает ли тело касаться другого тела в точке [contact](#contacts) с указанным номером (контакт продолжается).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

true, если тело продолжает касаться другого тела в точке контакта с указанным номером (контакт продолжается); иначе false.
## Math:: Vec3 getContactPoint ( int num ) const

Возвращает мировые координаты точки [contact](#contacts).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Точка контакта (в мировых координатах).
## Math:: vec3 getContactNormal ( int num ) const

Возвращает нормаль точки [contact](#contacts), в мировых координатах.
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Нормаль контакта (в мировых координатах).
## Math:: vec3 getContactVelocity ( int num ) const

Возвращает относительную скорость в указанной точке [contact](#contacts).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Вектор скорости.
## float getContactImpulse ( int num ) const

Возвращает относительный импульс в указанной точке [contact](#contacts).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Значение импульса.
## float getContactTime ( int num ) const

Возвращает время наступления указанного [contact](#contacts). При использовании CCD (для сфер или капсул) возвращается время от текущего тика физической симуляции до момента, когда должен произойти рассчитанный контакт. При непрерывном (non-continuous) обнаружении столкновений всегда возвращается **0**.
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Время наступления рассчитанного контакта, в секундах.
## float getContactDepth ( int num ) const

Возвращает глубину, на которую тело проникло в препятствие в результате указанного [contact](#contacts). Это расстояние измеряется вдоль нормали контакта.
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Глубина проникновения, в единицах.
## float getContactFriction ( int num ) const

Возвращает относительное трение в указанной точке [contact](#contacts).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Значение трения.
## float getContactRestitution ( int num ) const

Возвращает относительную упругость (restitution) в указанной точке [contact](#contacts).
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Упругость.
## Ptr < Body > getContactBody0 ( int num ) const

Возвращает первое тело, участвующее в указанном [contact](#contacts). Это необязательно текущее тело.
### Аргументы

- *int* **num** - Номер [contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Первое тело.
## Ptr < Body > getContactBody1 ( int num ) const

Возвращает второе тело, участвующее в указанном [contact](#contacts). Это необязательно текущее тело.
### Аргументы

- *int* **num** - [Contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Второе тело.
## Ptr < Shape > getContactShape0 ( int num ) const

Возвращает первую форму, участвующую в указанном [contact](#contacts). Эта форма необязательно принадлежит текущему телу.
### Аргументы

- *int* **num** - [Contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Первая форма.
## Ptr < Shape > getContactShape1 ( int num ) const

Возвращает вторую форму, участвующую в указанном [contact](#contacts). Эта форма необязательно принадлежит текущему телу.
### Аргументы

- *int* **num** - [Contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Вторая форма.
## Ptr < Object > getContactObject ( int num ) const

Возвращает объект, участвующий в [contact](#contacts) (используется для столкновений с непроцессуальным объектом без физики).
### Аргументы

- *int* **num** - [Contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Объект в контакте.
## int getContactSurface ( int num ) const

Возвращает поверхность текущего объекта, находящуюся в [contact](#contacts) (используется для столкновений с объектом без физики).
### Аргументы

- *int* **num** - [Contact](#contacts) в диапазоне от 0 до [total number of contacts](#getNumContacts_int).

### Возвращаемое значение

Номер поверхности.
## void renderContacts ( )

Отрисовывает все точки [contacts](#contacts) тела, включая внутренние и внешние (обрабатываемые другими телами).
> **Notice:** Необходимо включить визуализатор движка консольной командой `show_visualizer 1`.


## void renderExternalContacts ( )

Отрисовывает все внешние [contacts](#contacts) тела (обрабатываемые другими телами).
> **Notice:** Необходимо включить визуализатор движка консольной командой `show_visualizer 1`.


## void renderInternalContacts ( )

Отрисовывает все внутренние [contacts](#contacts) тела (обрабатываемые им самим).
> **Notice:** Необходимо включить визуализатор движка консольной командой `show_visualizer 1`.


## void renderJoints ( )

Отрисовывает joints, к которым подключено тело.
> **Notice:** Необходимо включить визуализатор движка консольной командой `show_visualizer 1`.


## void renderShapes ( )

Отрисовывает формы, составляющие тело.
> **Notice:** Необходимо включить визуализатор движка консольной командой `show_visualizer 1`.


## void renderVisualizer ( )

Отрисовывает формы, joints и точки [contacts](#contacts) тела.
> **Notice:** Необходимо включить визуализатор движка консольной командой `show_visualizer 1`.


## Ptr < Body > clone ( const Ptr < Object > & object ) const

Клонирует тело и назначает копию указанному объекту.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, которому будет назначена копия.

### Возвращаемое значение

Копия тела.
## void swap ( const Ptr < Body > & body ) const

Меняет местами тела, сохраняя указатели.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Тело для обмена.

## int saveState ( const Ptr < Stream > & stream ) const

Сохраняет состояние указанного тела в двоичный поток.
**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_int):


```cpp
// задаём состояние тела
body->setPosition(vec3(1, 1, 0));

// сохраняем состояние
BlobPtr blob_state = Blob::create();
body->saveState(blob_state);

// изменяем состояние
body->setPosition(vec3(0, 0, 0));

// восстанавливаем состояние
blob_state->seekSet(0);       // возвращаем каретку в начало blob'а
body->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток для сохранения данных состояния тела.

### Возвращаемое значение

true, если состояние тела успешно сохранено; иначе false.
## int restoreState ( const Ptr < Stream > & stream )

Восстанавливает состояние указанного тела из двоичного потока.
**Пример** использования методов *[saveState()](#saveState_Stream_int)* и *restoreState()*:


```cpp
// задаём состояние тела
body->setPosition(vec3(1, 1, 0));

// сохраняем состояние
BlobPtr blob_state = Blob::create();
body->saveState(blob_state);

// изменяем состояние
body->setPosition(vec3(0, 0, 0));

// восстанавливаем состояние
blob_state->seekSet(0);       // возвращаем каретку в начало blob'а
body->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток с сохранёнными данными состояния тела.

### Возвращаемое значение

true, если состояние тела успешно восстановлено; иначе false.
