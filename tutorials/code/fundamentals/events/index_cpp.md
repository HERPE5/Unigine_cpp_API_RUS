# Event Handling (CPP)


При написании логики приложения одна из самых больших сложностей, с которой вы, скорее всего, столкнётесь — это связывание различных изменяющихся элементов таким образом, чтобы всё работало. Например, заставить персонажа двигаться, прыгать или подсчитывать очки может быть относительно легко само по себе. Но связать все события, происходящие в вашей игре или приложении, не запутавшись при этом, может быть очень сложно.


***Event System*** позволяет создавать логику приложения, которая выполняется при срабатывании **event** во время работы приложения. Она позволяет объектам подписывать одну или несколько своих функций на событие субъекта. Затем, когда субъект вызывает событие, в ответ вызываются функции объектов. Такие функции также известны как **обработчики событий**.


Система событий обладает следующими особенностями:


- *Строгая проверка типов для сигнатур*: вы можете видеть, сколько именно и каких аргументов требует функция-обработчик события.
- *Проверка на этапе компиляции*: обеспечивает соответствие типов аргументов типам события, предотвращая ошибки времени выполнения.
- *Простая подписка/отписка от событий с [lambda functions](#lambda_functions)* без необходимости выполнять внутренние преобразования типов.
- *Автоматическая отписка от события*.
- *Временная деактивация события*: определённые события можно временно отключить для выполнения конкретных действий без их срабатывания.
- *Пакетное управление*: вы можете отписаться от нескольких подписок за один вызов функции.


## События


**Event** представлено абстрактным классом *Event*. Он служит интерфейсом для взаимодействия с событием. Обычно вы получаете этот интерфейс через ссылку как **Event<args...>**, где *args* представляет список аргументов, которые событие передаст функции-обработчику.


Например, **[Body::getEventPosition()](../../../api/library/physics/class.body_cpp.md#getEventPosition_Event)** возвращает событие со следующей сигнатурой:


```cpp
Event<const Ptr<Body>&>

```


Это означает, что при подключении к событию функция-обработчик должна принимать аргумент того же типа.


### Эмуляция событий


Иногда необходимо эмулировать события. Для пользовательских событий вы можете использовать функцию ***EventInvoker::run()***, которая принимает те же аргументы, что и событие, и вызывает его функции-обработчики.


Следующий пример показывает, как создать своё событие, а затем запустить его при необходимости:


```cpp
class MyEventClass
{
public:

	Event<int> &getEvent() { return event; }

	void runEvent()
	{
		num_runs++;
		event.run(num_runs);
	}

private:

	int num_runs = 0;
	EventInvoker<int> event;
};

int main()
{
	MyEventClass my_class;
	EventConnections e_conn;

	my_class.getEvent().connect(
		e_conn,
		[](int n)
		{
			printf("n = %d\n", n);
		}
	);

	my_class.runEvent();
	my_class.runEvent();

	return 0;
}

```


Существующие события, реализованные для встроенных объектов и доступные через API, можно эмулировать с помощью соответствующих методов ***runEvent*()*** (без необходимости использовать ***EventInvoker::run()***). Например, чтобы эмулировать событие *Show* для [widget](../../../api/library/gui/class.widget_cpp.md), вызовите **[Widget::runEventShow()](../../../api/library/gui/class.widget_cpp.md#runEventShow_void)**.


```cpp
widget->runEventShow();

```


## Обработчики событий


Функции-обработчики событий могут принимать **не более 5** аргументов.


Кроме того, система событий выполняет строгую проверку типов для сигнатур функций-обработчиков: вы можете подписаться на событие только если типы аргументов функции совпадают с типами события. Например, в случае события с одним аргументом типа *int* вы можете связать его только с обработчиком, который также принимает один целочисленный аргумент. Даже если типы могут быть неявно преобразованы (как в примере), подписка не разрешена.


```cpp
Event<int> event;	// сигнатура события
void on_event(int a);	// типы совпадают, подписка разрешена
void on_event(long a);	// несовпадение типов, подписка невозможна

```


Это ограничение также распространяется на модификаторы *&, const* и *const&*. Например, когда типом события является пользовательский класс без модификаторов:


```cpp
Event<MyClass> event;
void on_event(MyClass a);			// типы совпадают, подписка разрешена
void on_event(MyClass a&);		// несовпадение типов
void on_event(const MyClass a&);// несовпадение типов

```


### Отбрасывание аргументов


В большинстве случаев не все аргументы, передаваемые событием функции-обработчику, необходимы. Поэтому события позволяют **отбрасывать ненужные аргументы** при подписке функций на них. Вы можете отбрасывать только один аргумент за раз, начиная с последнего. Например, следующие функции-обработчики могут подписаться на событие:


```cpp
// событие
Event<int, float, const char *, vec3, const MyClass &> event;

// обработчики события с отброшенными аргументами
on_event(int a, float b, const char *s, vec3 v, const MyClass &c);
on_event(int a, float b, const char *s, vec3 v);
on_event(int a, float b, const char *s);
on_event(int a, float b);
on_event(int a);
on_event();

```


### Получение дополнительных аргументов


Чтобы получить дополнительный пользовательский аргумент в функции-обработчике, необходимо добавить требуемый аргумент в конец списка аргументов обработчика и передать его значение в функцию **connect()**.


> **Примечание:** Есть ограничение: использование ссылок в качестве дополнительных аргументов не допускается. Это ограничение связано с тем, что копия аргумента создаётся в классе [*CallbackBase*](../../../api/library/common/callbacks/class.callbackbase_cpp.md).


```cpp
class UserClass
{
	{ /* ... */ }
};

Event<int, float> event;
EventConnections e_conn;

void on_event_0(int a, float b, int my_var) { /* ... */ }

void on_event_1(int a, float b, UserClass c) { /* ... */ }

void on_event_2(int a, float b, UserClass *c_ptr) { /* ... */ }

void on_event(float f, const char *str) { /* ... */ }

UserClass user_class;

int main()
{
	// передаём значение дополнительного аргумента "my_var" функции-обработчику
	event.connect(e_conn, on_event_0, 33);
	// передаём значение дополнительного аргумента "c" функции-обработчику
	event.connect(e_conn, on_event_1, user_class);
	// передаём значение дополнительного аргумента "c_ptr" функции-обработчику
	event.connect(e_conn, on_event_2, &user_class);
	// отбрасываем аргументы обработчика int и float, добавляем пользовательские float и const char* и передаём их в connect()
	event.connect(e_conn, on_event, 33.3f, "test");

	return 0;
}

```


## Подписка на события


Для удобства система событий предоставляет классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)*, которые позволяют легко подписываться и отписываться от событий. Рассмотрим их подробно.


### Одиночная подписка с EventConnection


Класс *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* хранит связь между событием и его обработчиком. Например, связь между событием и *свободной функцией-обработчиком* можно установить следующим образом:


```cpp
EventConnection connection;

// функция-обработчик
void on_event()
{
	Log::message("\Handling the event\n");
}

void init()
{
	//подключаем функцию-обработчик к событию с помощью EventConnection
	getSomeEvent().connect(connection, this, on_event);

}

```


Вы можете временно **отключить событие**, чтобы выполнить определённые действия без его срабатывания.


```cpp
// отключаем событие
getSomeEvent().setEnabled(false);

/* выполняем некоторые действия */

// и снова включаем его
getSomeEvent().setEnabled(true);

```


Более того, вы можете **включать и выключать отдельные подключения** (экземпляры *EventConnection*), что обеспечивает гибкость при работе с событиями.


```cpp
EventConnection connection;
/* ... */

// отключаем подключение
connection.setEnabled(false);

/* выполняем некоторые действия */

// и снова включаем его при необходимости
connection.setEnabled(true);

```


Позже вы можете отписаться от события через *EventConnection* следующим образом:


> **Примечание:** Вы не можете отписаться, используя указатель на функцию-обработчик, если подключение было создано через *EventConnection*.


```cpp
void shutdown()
{
	// разрываем связь с помощью EventConnection
	connection.disconnect();
}

```


Если *класс обрабатывает событие*, вы можете объявить экземпляр *EventConnection* как член класса и использовать его для подписки на события. В этом случае все связанные подписки будут автоматически удалены при вызове деструктора класса. Например:


<details>
<summary>Handler Class | Close</summary>

```cpp
// класс, обрабатывающий событие
class SomeClass
{
public:

	// экземпляр класса EventConnection как член класса
	EventConnection connection;

	// обработчик события, реализованный как член класса
	void on_event()
	{
		Log::message("\Handling the event\n");
	}
};

// создаём экземпляр класса
SomeClass *obj = new SomeClass();

// подключаем функцию-обработчик к событию с помощью EventConnection;
// указываем экземпляр класса, поскольку обработчик события принадлежит классу
getSomeEvent().connect(obj->connection, obj, &SomeClass::on_event);

/* ... */

// экземпляр класса-обработчика удаляется вместе со всеми его подписками;
// подписки удаляются автоматически в деструкторе
delete obj;

```

</details>


### Множественные подписки с EventConnections


Класс *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* — это контейнер для экземпляров *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)*. Несколько подписок на одно событие или **разные события** можно связать с одним экземпляром *EventConnections*.


Например, вы можете создать несколько подписок на одно событие следующим образом:


```cpp
EventConnections connections;

// обработчики события
static void on_some_event_0() { Log::message("\Handling the 1st event\n"); }
static void on_some_event_1() { Log::message("\Handling the 2nd event\n"); }

static void Main(string[] args)
{
	// добавляем два обработчика для события
	// и связываем его с экземпляром EventConnections, чтобы позже удалить пакет подписок
	getSomeEvent().connect(connections, this, on_some_event_0);
	getSomeEvent().connect(connections, this, on_some_event_1);

}

```


Также вы можете создать несколько подписок на разные события:


```cpp
EventConnections connections;

// обработчики события
static void on_some_event_0() { Log::message("\Handling the 1st event\n"); }
static void on_some_event_1() { Log::message("\Handling the 2nd event\n"); }
static void on_some_event_2() { Log::message("\Handling the 3rd event\n"); }

static void Main(string[] args)
{
	// подписываемся на разные события с обработчиками, которые будут выполнены при их срабатывании;
	// здесь несколько подписок связаны с одним экземпляром класса EventConnections
	getSomeEvent0().connect(connections, this, on_some_event_0);
	getSomeEvent1().connect(connections, this, on_some_event_1);
	getSomeEvent2().connect(connections, this, on_some_event_2);
}

```


Позже вы можете отписаться от событий через *EventConnections* следующим образом:


> **Примечание:** Вы не можете отписаться, используя указатель на функцию-обработчик, если подключение было создано через *EventConnections*.


```cpp
// разрываем связь с помощью EventConnections
// все экземпляры EventConnection будут удалены из контейнера EventConnections
connections.disconnectAll();

```


Если *класс обрабатывает событие*, вы можете объявить экземпляр *EventConnections* как член класса и использовать его для подписки на события. В этом случае все связанные подписки будут автоматически удалены при вызове деструктора класса. См. пример, приведённый [above](#handler_class) — то же самое применимо и к *EventConnections*.


#### Наследование от EventConnections


Существует другой способ автоматически отписаться от события, обрабатываемого классом: можно унаследовать его от *EventConnections*. В этом случае событие будет взаимодействовать с пользовательским классом так же, как с *EventConnections*. Все связанные подписки будут автоматически удалены в деструкторе пользовательского класса.


```cpp
class UserClass : public EnventConnections
{
public:

	void init(Event<int, float> &event)
	{
		event.connect(this, &UserClass::on_event);
	}

	void on_event(int a, float b)
	{
		Log::message("\Handling the event\n");
	}
};

int main()
{
	UserClass *user_class = new UserClass();
	user_class->init(getSomeEvent());
	delete user_class; // my_class автоматически отпишется от всех событий в деструкторе

	return 0;
}

```


### Использование лямбда-функций


Вы можете передать лямбда-функцию в качестве аргумента функции **connect()** для обработки события: нет необходимости выполнять внутренние преобразования типов. Все возможности, доступные для функций-обработчиков, также применимы к лямбда-функциям, за исключением дополнительных аргументов.


```cpp
int main()
{
	// экземпляр класса EventConnections для управления подписками на события
	EventConnections connections;

	auto l = [](int a, float b) {};

	event.connect(connections, l);

	event.connect(connections, [](int a, float b) {});

	event.connect(connections, [](int a {}));

	return 0;
}

```


### Дескрипторы подключения


При подписке на событие возвращается дескриптор подключения *EventConnectionId*. Вы можете сохранить его и использовать позже для отписки.


> **Примечание:** Мы не рекомендуем этот подход. Он приведён только в информационных целях.


```cpp
// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

// подписываемся на событие Contacts с лямбда-функцией-обработчиком, сохраняя ID подключения
EventConnectionId contacts_handler_id = body->getEventContacts().connect(econnections, [](const Ptr<Body> & body) {
		Log::message("\Handling Contacts event (lambda).\n");
	}
);

// удаляем подписку позже, используя ID
body->getEventContacts().disconnect(contacts_handler_id);

```


В некоторых случаях использование дескриптора подключения приводит к сбою:


- Если вы подписаны на событие через *EventConnection*, оно станет недействительным при отписке с использованием дескриптора подключения.
- Если у вас есть несколько подписок, связанных с *EventConnections*, отписка от одного события с использованием дескриптора подключения не удалит экземпляр *EventConnection* из контейнера.


## Прямая небезопасная подписка


Вы можете подписываться на события напрямую через функцию *connectUnsafe()*, без указания экземпляра класса *EventConnection/EventConnections*, и отписываться через *disconnect()*:


- Функция *connectUnsafe()* используется для подключения события и обработчика события. Количество аргументов функции может варьироваться.
- Функция *disconnect()* используется для разрыва связи между событием и его обработчиком. Она принимает в качестве аргумента указатель на функцию-обработчик или дескриптор подключения.


```cpp
// функция-обработчик
void on_event(int a, float b)
{
	Log::message("\Handling the event\n");
}

void init()
{
	// подключаем функцию-обработчик к событию напрямую
	getSomeEvent().connectUnsafe(on_event);

	// отключаем функцию-обработчик от события, используя указатель на эту функцию
	getSomeEvent().disconnect(on_event);

	// ...

	// прямое подключение с использованием лямбда-выражения
	// и сохранением дескриптора подключения для последующего удаления подписки
	EventConnectionId connection_id = event.connectUnsafe([](int a, float b) {});

	// отключаем функцию-обработчик от события, используя дескриптор подключения
	getSomeEvent().disconnect(connection_id);

	return 0;
}

```


Если *класс обрабатывает событие*, вам следует передать экземпляр класса в качестве аргумента функциям *connect()* и *disconnect()*. Например:


<details>
<summary>Handler Class | Close</summary>

```cpp
// класс, обрабатывающий событие
class SomeClass
{
public:

	// обработчик события, реализованный как член класса
	void on_event()
	{
		Log::message("\Handling the event\n");
	}
};

// создаём экземпляр класса
SomeClass *obj = new SomeClass();

// подключаем функцию-обработчик к событию;
// указываем экземпляр класса, поскольку обработчик события принадлежит классу
getSomeEvent().connectUnsafe(obj, &SomeClass::on_event);

/* ... */

// удаляем подписку
getSomeEvent().disconnect(obj, &SomeClass::on_event);

```

</details>


## Использование предопределённых событий


Некоторые члены API Unigine имеют несколько предопределённых событий, которые можно обрабатывать в специфических случаях. В следующих разделах показано практическое применение описанных выше концепций.


### Триггеры


Триггеры используются для обнаружения изменений позиции или состояния узлов. Unigine предлагает три типа встроенных триггеров:


- *[**NodeTrigger**](../../../api/library/nodes/class.nodetrigger_cpp.md)* вызывает события, когда узел триггера [enabled](../../../api/library/nodes/class.nodetrigger_cpp.md#getEventEnabled_Event) или изменяется его [position](../../../api/library/nodes/class.nodetrigger_cpp.md#getEventPosition_Event).
- *[**WorldTrigger**](../../../api/library/worlds/class.worldtrigger_cpp.md)* вызывает события, когда любой узел (коллайдер или нет) [inside](../../../api/library/worlds/class.worldtrigger_cpp.md#getEventEnter_Event) него или [outside](../../../api/library/worlds/class.worldtrigger_cpp.md#getEventLeave_Event) него. > **Примечание:** **World Triggers** обнаруживают только узлы с включённым *Triggers Interaction* — либо в редакторе, либо через API с помощью *[setTriggerInteractionEnabled()](../../../api/library/nodes/class.node_cpp.md#setTriggerInteractionEnabled_int_void)*.
- *[**PhysicalTrigger**](../../../api/library/physics/class.physicaltrigger_cpp.md)* вызывает события, когда физические объекты [inside](../../../api/library/physics/class.physicaltrigger_cpp.md#getEventEnter_Event) него или [outside](../../../api/library/physics/class.physicaltrigger_cpp.md#getEventLeave_Event) него.


Вот простой пример использования *NodeTrigger*. Обработчики событий задаются через указатели, указанные при подписке на следующие события: *[EventEnabled](../../../api/library/nodes/class.nodetrigger_cpp.md#getEventEnabled_Event)* и *[EventPosition](../../../api/library/nodes/class.nodetrigger_cpp.md#getEventPosition_Event)*.


<details>
<summary>AppWorldLogic.h | Close</summary>

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
		Log::message("Object position has been changed. New position is: (%f %f %f)\n", trigger->getWorldPosition().x, trigger->getWorldPosition().y, trigger->getWorldPosition().z);
	}

	void enabled_event_handler(const NodeTriggerPtr &trigger)
	{
		Log::message("The enabled flag is %d\n", trigger->isEnabled());
	}
};

```

</details>


<details>
<summary>AppWorldLogic.cpp | Close</summary>

```cpp
#include "AppWorldLogic.h"

using namespace Math;

int AppWorldLogic::init() {

	// создаём меш
	object = ObjectMeshStatic::create("core/meshes/box.mesh");
	// изменяем цвет альбедо материала
	object->setMaterialParameterFloat4("albedo_color", vec4(1.0f, 0.0f, 0.0f, 1.0f), 0);

	// создаём узел триггера
	trigger = NodeTrigger::create();

	// добавляем узел триггера к статическому мешу как дочерний узел
	object->addWorldChild(trigger);

	// подписываемся на события Enabled и Position
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

</details>


А вот пример *WorldTrigger*, демонстрирующий, как подписаться на события *Enter* и *Leave* с соответствующим обработчиком и сохранить это подключение для последующей отписки.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

```cpp
WorldTriggerPtr trigger;
EventConnections event_connections;

// реализуем обработчик события Enter
void AppWorldLogic::enter_event_handler(const NodePtr &node)
{
	Log::message("\nA node named %s has entered the trigger\n", node->getName());
}

// реализуем обработчик события Leave
void AppWorldLogic::leave_event_handler1(const NodePtr &node)
{
	Log::message("\nA node named %s has left the trigger\n", node->getName());
}

// реализуем дополнительный обработчик события Leave
void AppWorldLogic::leave_event_handler2(const NodePtr &node)
{
	Log::message("\nAdditional Leave event handler.\n");
}

int AppWorldLogic::init()
{

	// создаём узел мирового триггера
	trigger = WorldTrigger::create(Math::vec3(3.0f));

	// добавляем обработчик события Enter, который будет выполнен, когда узел входит в мировой триггер,
	// и привязываем его к экземпляру EventConnections, чтобы позже удалить пакет подписок
	trigger->getEventEnter().connect(event_connections, this, &AppWorldLogic::enter_event_handler);
	// добавляем два обработчика события Leave, которые будут выполнены, когда узел покидает мировой триггер,
	// и привязываем их к тому же экземпляру EventConnections
	trigger->getEventLeave().connect(event_connections, this, &AppWorldLogic::leave_event_handler1);
	trigger->getEventLeave().connect(event_connections, this, &AppWorldLogic::leave_event_handler2);

	return 1;
}

```

</details>


Чтобы удалить подписки на события, используйте следующий код:


```cpp
// удаляем все подписки на события Leave и Enter
event_connections.disconnectAll();


```


### Виджеты


Базовый класс виджетов *[**Widget**](../../../api/library/gui/class.widget_cpp.md)* позволяет подписываться на события.


Пример ниже демонстрирует, как подписаться на событие *Clicked* виджета.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

`AppWorldLogic.cpp`


```cpp
// функция-обработчик события
int AppWorldLogic::onButtonClicked()
{
	Log::message("\nThe widget button has been clicked\n");

	return 1;
}

// экземпляр класса EventConnections для управления подписками на события
EventConnections e_conn;

int AppWorldLogic::init()
{

	// получаем указатель на системный GUI
	GuiPtr gui = Gui::getCurrent();
	// создаём виджет кнопки и задаём её подпись
	WidgetButtonPtr widget_button = WidgetButton::create(gui, "Press me");
	// задаём всплывающую подсказку
	widget_button->setToolTip("Click this button");
	// пересчитываем размер кнопки
	widget_button->arrange();
	// задаём позицию кнопки
	widget_button->setPosition(10, 10);
	// назначаем функцию onButtonClicked для обработки события CLICKED
	widget_button->getEventClicked().connect(e_conn, this, &AppWorldLogic::onButtonClicked);
	// добавляем созданный виджет кнопки в системный GUI
	gui->addChild(widget_button, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

	return 1;
}

```

</details>


### Физика


Вы можете отслеживать определённые события, связанные с физикой, у [Bodies](../../../api/library/physics/class.body_cpp.md) и [Joints](../../../api/library/physics/class.joint_cpp.md):


- ****[Body::getEventFrozen()](../../../api/library/physics/class.body_cpp.md#getEventFrozen_Event)**** для отслеживания события заморозки тела.
- ****[Body::getEventPosition()](../../../api/library/physics/class.body_cpp.md#getEventPosition_Event)**** для отслеживания события изменения позиции тела.
- ****[Body::getEventContactEnter()](../../../api/library/physics/class.body_cpp.md#getEventContactEnter_Event)**** для отслеживания события возникновения контакта (тело начинает касаться другого тела или сталкиваемой поверхности).
- ****[Body::getEventContactLeave()](../../../api/library/physics/class.body_cpp.md#getEventContactLeave_Event)**** для отслеживания события окончания контакта (тело перестаёт касаться другого тела или сталкиваемой поверхности).
- ****[Body::getEventContacts()](../../../api/library/physics/class.body_cpp.md#getEventContacts_Event)**** для получения **всех контактов** тела, включая новые (*enter*) и завершающиеся (*leave*). Завершающиеся контакты удаляются после этапа выполнения callback, поэтому это единственный момент, когда их ещё можно получить.
- ****[Joint::getEventBroken()](../../../api/library/physics/class.joint_cpp.md#getEventBroken_Event)**** для отслеживания события разрыва сочленения.


Следующий пример кода показывает, как подписаться на события Body.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

`AppWorldLogic.cpp`


```cpp
// устанавливаем красный цвет альбедо узла при событии заморозки
int AppWorldLogic::frozen_event_handler(const BodyPtr &body)
{
	body->getObject()->setMaterialParameterFloat4("albedo_color", Math::vec4(1.0f, 0.0f, 0.0f, 1.0f), 0);

	return 1;
}

// устанавливаем синий цвет альбедо узла при событии изменения позиции
int AppWorldLogic::position_event_handler(const BodyPtr &body)
{
	body->getObject()->setMaterialParameterFloat4("albedo_color", Math::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0);

	return 1;
}

// устанавливаем жёлтый цвет альбедо узла при каждом контакте
int AppWorldLogic::contact_enter_event_handler(const BodyPtr &body, int num)
{
	body->getObject()->setMaterialParameterFloat4("albedo_color", Math::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0);

	return 1;
}

// экземпляр класса EventConnections для управления подписками на события
EventConnections e_conn;

int AppWorldLogic::init()
{

	// создаём бокс
	ObjectMeshStaticPtr meshStatic = ObjectMeshStatic::create("core/meshes/box.mesh");
	meshStatic->setPosition(Math::Vec3(0, 0, 5.0f));
	// добавляем твёрдое тело к боксу
	BodyRigidPtr body = BodyRigid::create(meshStatic);
	// подписываемся на события тела
	body->getEventFrozen().connect(e_conn, this, &AppWorldLogic::frozen_event_handler);
	body->getEventPosition().connect(e_conn, this, &AppWorldLogic::position_event_handler);
	body->getEventContactEnter().connect(e_conn, this, &AppWorldLogic::contact_enter_event_handler);
	// добавляем форму к телу
	ShapeBoxPtr shape = ShapeBox::create(body, Math::vec3(1.0f));

	return 1;
}

```

</details>


> **Примечание:** События, связанные с физикой, выполняются в главном потоке, так как в основном используются для создания, уничтожения или модификации других объектов.


### Свойства


События можно использовать для определения действий, выполняемых при добавлении или удалении свойств узла и поверхности, а также при замене свойств узла. Вот пример, демонстрирующий, как отслеживать добавление свойства узла через события.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

`AppWorldLogic.cpp`


```cpp
void AppWorldLogic::node_property_added(const NodePtr &node, const PropertyPtr &property)
{
	Log::message("Property \"%s\" was added to the node named \"%s\".\n", property->getName(), node->getName());
}

void AppWorldLogic::parameter_changed(const PropertyPtr &property, int num)
{
	Log::message("Parameter \"%s\" of the property \"%s\" has changed its value.\n", property->getParameterPtr(num)->getName(), property->getName());
}

void AppWorldLogic::property_removed(const PropertyPtr &property)
{
	Log::message("Property \"%s\" was removed.\n", property->getName());
}

// экземпляр класса EventConnections для управления подписками на события
EventConnections e_conn;

int AppWorldLogic::init()
{

	NodeDummyPtr node = NodeDummy::create();

	// ищем свойство с именем "new_property_0"
	PropertyPtr property = Properties::findProperty("new_property_0");

	// подписываемся на событие PropertyNodeAdd (добавление свойства узла)
	node->getEventPropertyNodeAdd().connect(e_conn, this, &AppWorldLogic::node_property_added);

	// добавляем свойство с именем "new_property_0" к узлу
	node->addProperty("new_property_0");

	// подписываемся на событие ParameterChanged (изменение параметра свойства)
	property->getEventParameterChanged().connect(e_conn, this, &AppWorldLogic::parameter_changed);

	// изменяем значение параметра "my_int_param"
	property->getParameterPtr("my_int_param")->setValueInt(3);

	// наследуем новое свойство с именем "new_property_1" от базового свойства "surface_base"
	Properties::findManualProperty("surface_base")->inherit("new_property_1");

	// подписываемся на удаление свойства
	Properties::getEventRemoved().connect(e_conn, this, &AppWorldLogic::property_removed);

	// удаляем свойство с именем "new_property_1"
	Properties::removeProperty(Properties::findProperty("new_property_1")->getGUID());

	return 1;
}

```

</details>
