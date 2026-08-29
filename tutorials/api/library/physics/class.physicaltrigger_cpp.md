# Unigine.PhysicalTrigger Class (CPP)

**Header:** #include <UniginePhysicals.h>

**Inherits from:** Physical


***Physical Trigger*** запускает события, когда физический объект попадает внутрь него или покидает его. Чтобы быть обнаруженным триггером, физические объекты должны одновременно иметь и то, и другое:


1. [Bodies](../../../api/library/physics/class.body_cpp.md) (с совпадающей [Physical Mask](../../../api/library/physics/class.body_cpp.md#setPhysicalMask_int_void)) > **Notice:** Чтобы [BodyDummy](../../../api/library/physics/class.bodydummy_cpp.md) мог активировать PhysicalTrigger, сначала нужно вызвать [updateContacts()](#updateContacts_void).
2. [Shapes](../../../api/library/physics/class.shape_cpp.md) (с совпадающей [Collision mask](../../../api/library/physics/class.shape_cpp.md#setCollisionMask_int_void))


Для принудительного обновления physical trigger можно вызвать [updateContacts()](#updateContacts_void). После этого можно получить доступ ко всем обновлённым данным о контактах в том же кадре. Однако функции-обработчики всё равно будут выполнены только при вызове следующей функции движка: то есть перед *[updatePhysics()](../../../code/fundamentals/execution_sequence/main_loop.md#physics)* (в текущем кадре) или перед *[update()](../../../code/fundamentals/execution_sequence/main_loop.md#update)* (в следующем кадре) — в зависимости от того, что наступит раньше.


> **Notice:** Если вы переместили некоторые узлы и хотите выполнить обработчики событий на основе изменённых позиций в том же кадре, сначала нужно вызвать [updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void).


### См. также


- Видеоурок [How To Use Physical Triggers to Catch Physical Objects](../../../videotutorials/how_to/how_to_cs/physical_trigger.md)
- Статья [Event Handling](../../../code/fundamentals/events/index_cpp.md)

  -
  -
  -


### Пример использования


В этом примере создаются physical trigger и два бокса, каждый со своим телом и формой. Когда бокс с совпадающей физической маской входит в physical trigger, вызывается функция **trigger_enter()**, а когда он покидает триггер — функция **trigger_leave()**.


Добавим следующий код в файл **AppWorldLogic.h**:


```cpp
#include <UniginePhysics.h>
#include <UniginePhysicals.h>
#include <UnigineConsole.h>
#include <UnigineGame.h>

class AppWorldLogic : public Unigine::WorldLogic
{

public:

private:

	// указатель на physical trigger
	Unigine::PhysicalTriggerPtr trigger;

	// буфер для хранения подписок на события триггера
	Unigine::EventConnections connections;

	// указатели на физические объекты
	Unigine::ObjectMeshDynamicPtr box1;
	Unigine::ObjectMeshDynamicPtr box2;
};


```


Добавим следующий код в файл **AppWorldLogic.cpp**:


```cpp
#include "AppWorldLogic.h"

using namespace Unigine;
using namespace Math;

// функция-обработчик, выполняемая при входе физического объекта в триггер
void trigger_enter(const BodyPtr &body)
{
	// пытаемся получить объект из тела
	ObjectPtr obj = body->getObject();
	if (!obj)
		return;

	// включаем излучение материала для всех поверхностей объекта
	for (int i = 0; i < obj->getNumSurfaces(); i++)
		obj->setMaterialState("emission", 1, i);

	// выводим имя объекта, входящего в область триггера
	Log::message("\n %s has entered the trigger area!", body->getObject()->getName());
}

// функция-обработчик, выполняемая при выходе физического объекта из триггера
void trigger_leave(const BodyPtr &body)
{
	// пытаемся получить объект из тела
	ObjectPtr obj = body->getObject();
	if (!obj)
		return;

	// отключаем излучение материала для всех поверхностей объекта
	for (int i = 0; i < obj->getNumSurfaces(); i++)
		obj->setMaterialState("emission", 0, i);

	// выводим имя объекта, покидающего область триггера
	Log::message("\n %s has left the trigger area!", body->getObject()->getName());
}

/// функция, создающая именованный бокс заданного размера, цвета и трансформации с телом и формой
ObjectMeshDynamicPtr createBodyBox(const char* name, vec3 size, float mass, vec4 color, Mat4 transform, int physical_mask)
{
	// создаём геометрию и задаём её параметры (имя, материал и трансформацию)
	ObjectMeshDynamicPtr OMD = Primitives::createBox(size);
	OMD->setWorldTransform(transform);
	OMD->setMaterialParameterFloat4("albedo_color", color, 0);
	OMD->setName(name);

	// добавляем физику, т.е. rigid body и форму бокса с указанной массой
	BodyRigidPtr body = BodyRigid::create(OMD);
	body->addShape(ShapeBox::create(size), translate(vec3(0.0f)));
	OMD->getBody()->getShape(0)->setMass(mass);
	// задаём физическую маску тела
	body->setPhysicalMask(physical_mask);

	return OMD;
}

int AppWorldLogic::init()
{
	//включаем визуализатор для отрисовки границ physical trigger
	Console::run("show_visualizer 1");

	// создаём physical trigger
	trigger = PhysicalTrigger::create(Shape::SHAPE_BOX, vec3(2.0f, 2.0f, 1.0f));

	// задаём позицию триггера
	trigger->setPosition(Vec3(0.0f, 0.0f, 1.0f));

	// задаём физическую маску триггера равной 1
	trigger->setPhysicalMask(1);

	// получаем размер триггера
	vec3 size = trigger->getSize();

	// выводим размер триггера и тип формы
	Log::message("\n Trigger parameters size(%f, %f ,%f) type: %d", size.x, size.y, size.z, trigger->getShapeType());

	// подписываемся на событие входа в триггер
	trigger->getEventEnter().connect(connections, trigger_enter);

	// подписываемся на событие выхода из триггера
	trigger->getEventLeave().connect(connections, trigger_leave);

	// создаём бокс с телом и значением физической маски 2, чтобы триггер его игнорировал
	box1 = createBodyBox("Box1", vec3(0.2f), 5.0f, vec4(1.0f, 0.0f, 0.0f, 1.0f), translate(Vec3(0.0f, 0.0f, 2.22f)), 2);

	// создаём бокс с телом и значением физической маски 1, чтобы он воздействовал на триггер
	box2 = createBodyBox("Box2", vec3(0.2f), 0.0f, vec4(1.0f, 1.0f, 0.0f, 1.0f), translate(Vec3(3.5f, 0.0f, 1.2f)), 1);

	// выводим физические маски обоих боксов и триггера
	Log::message("\n Box1 Physical mask: %d", box1->getBody()->getPhysicalMask());
	Log::message("\n Box2 Physical mask: %d", box2->getBody()->getPhysicalMask());
	Log::message("\n Trigger Physical mask: %d", trigger->getPhysicalMask());

	return 1;
}

int AppWorldLogic::update()
{
	// отображаем границы physical trigger
	trigger->renderVisualizer();

	// изменяем позицию второго бокса
	box2->setWorldPosition(box2->getWorldPosition() - Vec3(0.5f * Game::getIFps(), 0.0f, 0.0f));

	return 1;
}

int AppWorldLogic::updatePhysics()
{
	// обновляем информацию о контактах триггера
	trigger->updateContacts();

	return 1;
}

int AppWorldLogic::shutdown()
{
	// удаляем подписки на все события триггера
	connections.disconnectAll();

	return 1;
}


```


## PhysicalTrigger Class

### Методы класса

## void setSize ( )

Задаёт новый размер physical trigger.
### Аргументы

- **size** - Размер physical trigger:

  - Радиус, в случае сферы (передайте радиус в первом элементе вектора).
  - Радиус и высота, в случае капсулы или цилиндра (передайте радиус как первый элемент вектора, а высоту — как второй).
  - Размеры по осям X, Y и Z, в случае бокса.

## getSize () const

Возвращает текущий размер physical trigger.
### Возвращаемое значение

Текущий размер physical trigger:
- Радиус, в случае сферы (передайте радиус в первом элементе вектора).
- Радиус и высота, в случае капсулы или цилиндра (передайте радиус как первый элемент вектора, а высоту — как второй).
- Размеры по осям X, Y и Z, в случае бокса.


## void setShapeType ( int type )

Задаёт новый тип формы physical trigger.
### Аргументы

- *int* **type** - Тип формы physical trigger:

  - 0 - Sphere
  - 1 - Capsule
  - 2 - Cylinder
  - 3 - Box

## int getShapeType () const

Возвращает текущий тип формы physical trigger.
### Возвращаемое значение

Текущий тип формы physical trigger:
- 0 - Sphere
- 1 - Capsule
- 2 - Cylinder
- 3 - Box


## int getNumContacts () const

Возвращает текущее общее количество контактов с телами, формами и сталкивающимися поверхностями, в которых участвовал physical trigger.
### Возвращаемое значение

Текущее количество контактов.
## int getNumBodies () const

Возвращает текущее общее количество тел, пересекающихся с physical trigger.
### Возвращаемое значение

Текущее количество тел.
## void setLeaveCallbackName ( const char * name )

Задаёт новое имя функции обратного вызова, срабатывающей при выходе из physical trigger. Эта функция обратного вызова задаётся через [setLeaveCallbackName()](#setLeaveCallbackName_cstr_void).
### Аргументы

- *const char ** **name** - Имя функции обратного вызова.

## const char * getLeaveCallbackName () const

Возвращает текущее имя функции обратного вызова, срабатывающей при выходе из physical trigger. Эта функция обратного вызова задаётся через [setLeaveCallbackName()](#setLeaveCallbackName_cstr_void).
### Возвращаемое значение

Текущее имя функции обратного вызова.
## void setExclusionMask ( int mask )

Задаёт новую битовую маску, предотвращающую обнаружение столкновений с формами и телами. Эта маска не зависит от маски столкновений. Чтобы physical trigger не обнаруживал столкновения для тел и форм с совпадающими масками столкновений, должен совпадать хотя бы один бит масок исключения.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getExclusionMask () const

Возвращает текущую битовую маску, предотвращающую обнаружение столкновений с формами и телами. Эта маска не зависит от маски столкновений. Чтобы physical trigger не обнаруживал столкновения для тел и форм с совпадающими масками столкновений, должен совпадать хотя бы один бит масок исключения.
### Возвращаемое значение

Текущее целое число, каждый бит которого является маской.
## void setEnterCallbackName ( const char * name )

Задаёт новое имя функции обратного вызова, срабатывающей при входе в physical trigger.
### Аргументы

- *const char ** **name** - Имя функции обратного вызова.

## const char * getEnterCallbackName () const

Возвращает текущее имя функции обратного вызова, срабатывающей при входе в physical trigger.
### Возвращаемое значение

Текущее имя функции обратного вызова.
## void setCollisionMask ( int mask )

Задаёт новую битовую маску столкновений для триггера:
- триггер будет активирован, если вошедшее тело будет иметь совпадающую [physical mask](../../../api/library/physics/class.body_cpp.md#setPhysicalMask_int_void) и одновременно его форма будет иметь совпадающую [collision mask](../../../api/library/physics/class.shape_cpp.md#setCollisionMask_int_void).


### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getCollisionMask () const

Возвращает текущую битовую маску столкновений для триггера:
- триггер будет активирован, если вошедшее тело будет иметь совпадающую [physical mask](../../../api/library/physics/class.body_cpp.md#setPhysicalMask_int_void) и одновременно его форма будет иметь совпадающую [collision mask](../../../api/library/physics/class.shape_cpp.md#setCollisionMask_int_void).


### Возвращаемое значение

Текущее целое число, каждый бит которого является маской.
## Event<const Ptr < Body > &> getEventLeave () const

Событие, срабатывающее при выходе тела из physical trigger. Обработчик события должен получать [*Body*](../../../api/library/physics/class.body_cpp.md) в качестве первого аргумента. Кроме того, он также может принимать **2** аргумента любого типа. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Body> & **body**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Leave
void leave_event_handler(const Ptr<Body> & body)
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
publisher->getEventLeave().connect(leave_event_connections, [](const Ptr<Body> & body) {
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
	void event_handler(const Ptr<Body> & body)
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
leave_handler_id = publisher->getEventLeave().connect(e_connections, [](const Ptr<Body> & body) {
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
## Event<const Ptr < Body > &> getEventEnter () const

Событие, срабатывающее при входе тела в physical trigger. Функция обратного вызова должна получать [*Body*](../../../api/library/physics/class.body_cpp.md) в качестве первого аргумента. Кроме того, она также может принимать 2 аргумента любого типа. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Body> & **body**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Enter
void enter_event_handler(const Ptr<Body> & body)
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
publisher->getEventEnter().connect(enter_event_connections, [](const Ptr<Body> & body) {
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
	void event_handler(const Ptr<Body> & body)
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
enter_handler_id = publisher->getEventEnter().connect(e_connections, [](const Ptr<Body> & body) {
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

## static PhysicalTriggerPtr create ( Shape::TYPE type , const Math:: vec3 & size )

Конструктор. Создаёт physical trigger указанной формы и размера.
### Аргументы

- *[Shape::TYPE](../../../api/library/physics/class.shape_cpp.md#TYPE)* **type** - Форма physical trigger:

  - 0 = *Sphere*
  - 1 = *Capsule*
  - 2 = *Cylinder*
  - 3 = *Box*
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размер physical trigger:

  - *Radius*, в случае сферы
  - *Radius* и *height*, в случае капсулы или цилиндра
  - *Dimensions*, в случае бокса

## Ptr < Body > getBody ( int num )

Возвращает указанное тело, пересекающееся с physical trigger.
### Аргументы

- *int* **num** - Номер тела.

### Возвращаемое значение

Пересечённое тело.
## float getContactDepth ( int contact ) const

Возвращает глубину проникновения для указанного контакта.
### Аргументы

- *int* **contact** - Номер контакта.

### Возвращаемое значение

Глубина проникновения.
## Math:: vec3 getContactNormal ( int contact ) const

Возвращает нормаль точки контакта, в мировых координатах.
### Аргументы

- *int* **contact** - Номер контакта.

### Возвращаемое значение

Нормаль точки контакта.
## Ptr < Object > getContactObject ( int contact ) const

Возвращает объект, участвующий в контакте с physical trigger.
### Аргументы

- *int* **contact** - Номер контакта.

### Возвращаемое значение

Объект в контакте.
## Math:: Vec3 getContactPoint ( int contact ) const

Возвращает мировые координаты точки контакта.
### Аргументы

- *int* **contact** - Номер контакта.

### Возвращаемое значение

Точка контакта.
## Ptr < Shape > getContactShape ( int contact ) const

Возвращает форму, столкнувшуюся с physical trigger.
### Аргументы

- *int* **contact** - Номер контакта.

### Возвращаемое значение

Форма в контакте.
## int getContactSurface ( int contact ) const

Возвращает поверхность текущего объекта, находящуюся в контакте.
### Аргументы

- *int* **contact** - Номер контакта.

### Возвращаемое значение

Номер поверхности.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Physical trigger](../../../api/library/nodes/class.node_cpp.md#PHYSICAL_TRIGGER).
## void updateContacts ( )

Принудительно обновляет physical trigger, т.е. пересчитывает его пересечения с физическими объектами и коллайдерами. После этого можно получить доступ ко всем обновлённым данным; однако сами функции-обработчики событий будут выполнены только по завершении сброса физики (physics flush).
