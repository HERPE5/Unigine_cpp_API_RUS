# Класс Unigine::Profiler (CPP)

**Заголовочный файл:** #include <UnigineProfiler.h>

> **Примечание:** Этот класс является одиночкой (singleton).


Класс Profiler используется для создания счётчиков для [Performance Profiler](../../../tools/profiling/profiler/index.md) движка. Позволяет использовать счётчики в вашем коде следующим образом:


```cpp
Profiler::begin("my_counter");
// ...code to profile...
Profiler::end();

```


> **Примечание:** Счётчики можно вкладывать друг в друга.


### Пример использования


Следующий пример содержит различные подходы к созданию счётчиков:


- Два счётчика добавляются через функцию *setValue()*: один показывает количество вершин динамического мэша, другой — время обновления. Этот подход следует использовать, когда нужно показать, например, значение настройки, количество объектов и т.п.
- Ещё два счётчика добавляются с помощью конструкции *begin()/end()*. Они показывают время, потраченное на изменение сетки мэша, и время, потраченное на вычисление векторов нормалей, касательных и ограничивающего бокса мэша. Этот подход следует использовать, когда нужно показать время, затраченное на выполнение части кода.


Файл `AppWorldLogic.h` содержит объявление необходимых переменных.


```cpp
#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UnigineObjects.h>

class AppWorldLogic: public Unigine::WorldLogic
{

public:
	AppWorldLogic();
	virtual ~AppWorldLogic();

	int init() override;

	int update() override;
	int postUpdate() override;
	int updatePhysics() override;

	int shutdown() override;

	int save(const Unigine::StreamPtr &stream) override;
	int restore(const Unigine::StreamPtr &stream) override;

private:
	// объявляем переменные
	int size = 128;
	Unigine::ObjectMeshDynamicPtr mesh;
};

```


В `AppWorldLogic.cpp` создаётся динамический мэш, который затем изменяется при обновлении движка. Все счётчики также создаются в *update()*.


```cpp
#include "AppWorldLogic.h"
#include <UnigineProfiler.h>
#include <UnigineEditor.h>
#include <UnigineGame.h>

using namespace Unigine;

int AppWorldLogic::init()
{
	// создаём динамический мэш
	mesh = ObjectMeshDynamic::create(ObjectMeshDynamic::USAGE_DYNAMIC_VERTEX | ObjectMeshDynamic::USAGE_IMMUTABLE_INDICES);
	// задаём настройки мэша
	mesh->setWorldTransform(Math::translate(Math::Vec3(0.0f, 0.0f, 2.0f)));

	// создаём вершины динамического мэша
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++)
		{
			mesh->addVertex(Math::vec3(0.0f));
			mesh->addTexCoord(Math::vec4((float)x / size, (float)y / size, 0.0f, 0.0f));
		}
	}

	// создаём индексы динамического мэша
	for (int y = 0; y < size - 1; y++) {
		int offset = size * y;
		for (int x = 0; x < size - 1; x++) {
			mesh->addIndex(offset);
			mesh->addIndex(offset + 1);
			mesh->addIndex(offset + size);
			mesh->addIndex(offset + size);
			mesh->addIndex(offset + 1);
			mesh->addIndex(offset + size + 1);
			offset++;
		}
	}

	return 1;
}

int AppWorldLogic::update()
{
	// добавляем счётчик, показывающий продолжительность фазы обновления движка
	Profiler::setValue("Update time", "ms", Engine::get()->getUpdateTime(), 50.0f, Math::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	float time = Game::getTime();
	float isize = 30.0f / size;
	// запускаем счётчик, показывающий время, потраченное на изменение сетки динамического мэша
	Profiler::begin("Grid", Math::vec4(1.0f));
	for (int y = 0; y < size; y++)
	{
		for (int i = 0; i < size; i++)
		{
			float Y = y * isize - 15.0f;
			float Z = Math::cos(Y + time);
			for (int x = 0; x < size; x++)
			{
				float X = x * isize - 15.0f;
				mesh->setVertex(i++, Math::vec3(X, Y, Z * Math::sin(X + time)));
			}
		}
	}
	// останавливаем счётчик
	Profiler::end();
	// запускаем счётчик, показывающий время, потраченное на
	// вычисление векторов нормалей, касательных и ограничивающего бокса динамического мэша
	Profiler::begin("mesh");
	mesh->updateBounds();
	mesh->updateTangents();
	mesh->flushVertex();
	// останавливаем счётчик
	Profiler::end();

	// добавляем счётчик, показывающий количество вершин динамического мэша
	Profiler::setValue("Num vertices", "", mesh->getNumVertex(), 32768, NULL);

	return 1;
}


```


> **Примечание:** Чтобы создать **[nested counters](../../../tools/profiling/microprofile/index_cpp.md#nested_cpp)**, необходимо использовать функции *[beginMicro()](#beginMicro_cstr_int_int)* и *[endMicro()](#endMicro_int_void)*.


#### См. также


- Пример [profiling the application logic](../../../tools/profiling/microprofile/index_cpp.md#app_logic_cpp).


## Класс Profiler

### Методы класса

## void setGui ( const Ptr < Gui >& gui )

Устанавливает новый [GUI](../../../api/library/gui/class.gui_cpp.md) для [Performance Profiler](../../../tools/profiling/profiler/index.md) движка.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)>&* **gui** - Указатель на GUI.

## Ptr < Gui > getGui () const

Возвращает текущий [GUI](../../../api/library/gui/class.gui_cpp.md) для [Performance Profiler](../../../tools/profiling/profiler/index.md) движка.
### Возвращаемое значение

Текущий указатель на GUI.
## void setEnabled ( bool enabled )

Устанавливает новое значение, указывающее, включён ли профайлер.
### Аргументы

- *bool* **enabled** - **true** — включить профайлер; **false** — отключить.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включён ли профайлер.
### Возвращаемое значение

**true**, если профайлер включён; иначе **false**.
## const char * getMicroprofileUrl () const

Возвращает текущий URL веб-сервера microprofile.
### Возвращаемое значение

Текущий URL веб-сервера microprofile, представленный следующим образом:
http://localhost:p/, где p — локальный порт.


## int getNumCounters () const

Возвращает текущее общее количество счётчиков профайлера.
### Возвращаемое значение

Текущее общее количество счётчиков профайлера
## static Event<> getEventProfileDumpStart () const

Событие, срабатывающее при начале записи дампа профайлера. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Примечание:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ProfileDumpStart
void profiledumpstart_event_handler()
{
	Log::message("\Обработка события ProfileDumpStart\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections profiledumpstart_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Profiler::getEventProfileDumpStart().connect(profiledumpstart_event_connections, profiledumpstart_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Profiler::getEventProfileDumpStart().connect(profiledumpstart_event_connections, []() {
		Log::message("\Обработка события ProfileDumpStart (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
profiledumpstart_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection profiledumpstart_event_connection;

// подписываемся на событие ProfileDumpStart с функцией-обработчиком, сохраняя соединение
Profiler::getEventProfileDumpStart().connect(profiledumpstart_event_connection, profiledumpstart_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
profiledumpstart_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
profiledumpstart_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ProfileDumpStart через соединение
profiledumpstart_event_connection.disconnect();

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

	// Обработчик события ProfileDumpStart, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события ProfileDumpStart\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Profiler::getEventProfileDumpStart().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId profiledumpstart_handler_id;

// подписываемся на событие ProfileDumpStart с лямбда-обработчиком, сохраняя идентификатор соединения
profiledumpstart_handler_id = Profiler::getEventProfileDumpStart().connect(e_connections, []() {
		Log::message("\Обработка события ProfileDumpStart (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Profiler::getEventProfileDumpStart().disconnect(profiledumpstart_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ProfileDumpStart при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Profiler::getEventProfileDumpStart().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Profiler::getEventProfileDumpStart().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventProfileDumpEnd () const

Событие, срабатывающее при завершении записи дампа профайлера. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Примечание:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ProfileDumpEnd
void profiledumpend_event_handler()
{
	Log::message("\Обработка события ProfileDumpEnd\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections profiledumpend_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Profiler::getEventProfileDumpEnd().connect(profiledumpend_event_connections, profiledumpend_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Profiler::getEventProfileDumpEnd().connect(profiledumpend_event_connections, []() {
		Log::message("\Обработка события ProfileDumpEnd (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
profiledumpend_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection profiledumpend_event_connection;

// подписываемся на событие ProfileDumpEnd с функцией-обработчиком, сохраняя соединение
Profiler::getEventProfileDumpEnd().connect(profiledumpend_event_connection, profiledumpend_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
profiledumpend_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
profiledumpend_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ProfileDumpEnd через соединение
profiledumpend_event_connection.disconnect();

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

	// Обработчик события ProfileDumpEnd, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события ProfileDumpEnd\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Profiler::getEventProfileDumpEnd().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId profiledumpend_handler_id;

// подписываемся на событие ProfileDumpEnd с лямбда-обработчиком, сохраняя идентификатор соединения
profiledumpend_handler_id = Profiler::getEventProfileDumpEnd().connect(e_connections, []() {
		Log::message("\Обработка события ProfileDumpEnd (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Profiler::getEventProfileDumpEnd().disconnect(profiledumpend_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ProfileDumpEnd при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Profiler::getEventProfileDumpEnd().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Profiler::getEventProfileDumpEnd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## void setValue ( const char * name , const char * units , int value , int max_value , float * OUT_arg5 )

Обновляет настройки целочисленного счётчика.
```cpp
// добавляем счётчик без графика
Profiler::setValue("Random value 1", "", rand() % 5, 4, NULL);
// добавляем счётчик с цветным графиком
Profiler::setValue("Random value 2", "", rand() % 10, 9, Math::vec4(1.0f));

```


### Аргументы

- *const char ** **name** - Имя счётчика.
- *const char ** **units** - Единицы измерения счётчика.
- *int* **value** - Значение счётчика.
- *int* **max_value** - Максимальное значение счётчика.
- *float ** **OUT_arg5** - Цвет графика. Передайте NULL, если график не требуется. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void setValue ( const char * name , const char * units , float value , float max_value , float * OUT_arg5 )

Обновляет настройки счётчика с плавающей точкой.
```cpp
float rvalue1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float rvalue2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
// добавляем счётчик без графика
Profiler::setValue("Random value 1", "", rvalue1, 1.0f, NULL);
// добавляем счётчик с цветным графиком
Profiler::setValue("Random value 2", "", 1 + rvalue2, 10.0f, Math::vec4(1.0f));

```


### Аргументы

- *const char ** **name** - Имя счётчика.
- *const char ** **units** - Единицы измерения счётчика.
- *float* **value** - Значение счётчика.
- *float* **max_value** - Максимальное значение счётчика.
- *float ** **OUT_arg5** - Цвет графика. Передайте NULL, если график не требуется. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## float getValue ( const char * name ) const

Возвращает значение указанного счётчика.
### Аргументы

- *const char ** **name** - Имя счётчика.

### Возвращаемое значение

Значение счётчика в миллисекундах.
## void begin ( const char * name , const Math:: vec4 & color ) const

Запускает счётчик с заданным именем и показывает цветной график (если установлена консольная переменная `show_profiler 1`). Счётчик показывает пользователю, сколько миллисекунд было потрачено на операцию, выполненную между функциями *begin()* и *[end()](#end_float)*.
```cpp
int size = 128;

Unigine::ObjectMeshDynamicPtr mesh;

	float time = Game::getTime();
	float isize = 30.0f / size;
	// запускаем счётчик, показывающий время, потраченное на изменение сетки динамического мэша
	Profiler::begin("Grid", Math::vec4(1.0f));
	for (int y = 0; y < size; y++)
	{
		for (int i = 0; i < size; i++)
		{
			float Y = y * isize - 15.0f;
			float Z = Math::cos(Y + time);
			for (int x = 0; x < size; x++)
			{
				float X = x * isize - 15.0f;
				mesh->setVertex(i++, Math::vec3(X, Y, Z * Math::sin(X + time)));
			}
		}
	}
	// останавливаем счётчик
	Profiler::end();

```


### Аргументы

- *const char ** **name** - Имя счётчика.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет графика.

## void begin ( const char * name ) const

Запускает счётчик с заданным именем. Счётчик показывает пользователю, сколько миллисекунд было потрачено на операцию, выполненную между функциями *begin()* и *[end()](#end_float)*.
```cpp
Unigine::ObjectMeshDynamicPtr mesh;

	// запускаем счётчик, показывающий время, потраченное на
	// вычисление векторов нормалей, касательных и ограничивающего бокса динамического мэша
	Profiler::begin("mesh");
	mesh->updateBounds();
	mesh->updateTangents();
	mesh->flushVertex();
	// останавливаем счётчик
	Profiler::end();

```


### Аргументы

- *const char ** **name** - Имя счётчика.

## float end ( ) const

Останавливает последний [activated](#begin_cstr_vec4_void) счётчик и возвращает его значение.
### Возвращаемое значение

Значение счётчика в миллисекундах.
## int beginMicro ( const char * name , bool gpu = 0 ) const

Запускает счётчик с заданным именем только в [Microprofile](../../../tools/profiling/microprofile/index_cpp.md), без перегрузки макета [Performance Profiler](../../../tools/profiling/profiler/index.md). Счётчик показывает пользователю, сколько миллисекунд было потрачено на операцию, выполненную между функциями *beginMicro()* и *[endMicro()](#endMicro_int_void)*.
> **Примечание:** У каждого счётчика есть ID. Таким образом, можно создавать несколько вложенных блоков *beginMicro() / endMicro()*, что невозможно в [Performance Profiler](../../../tools/profiling/profiler/index.md).


```cpp
Unigine::ObjectMeshDynamicPtr mesh;

	// запускаем счётчик, показывающий время, потраченное на вычисление векторов нормалей,
	// касательных и ограничивающего бокса динамического мэша, с вложенным счётчиком только для касательных векторов
	int c_id = Profiler::beginMicro("mesh");
	mesh->updateBounds();
	int c_nested_id = Profiler::beginMicro("mesh_tangents");
	mesh->updateTangents();
	Profiler::endMicro(c_nested_id);
	mesh->flushVertex();
	// останавливаем счётчик
	Profiler::endMicro(c_id);

```


### Аргументы

- *const char ** **name** - Имя счётчика.
- *bool* **gpu** - true для счётчика GPU; false — для счётчика CPU. Значение по умолчанию — false.

### Возвращаемое значение

ID добавленного счётчика.
## void endMicro ( int id ) const

Останавливает ранее [activated](#beginMicro_cstr_int_int) счётчик Microprofile с указанным ID.
### Аргументы

- *int* **id** - ID счётчика Microprofile.

## void initThread ( const char * name , int priority = 0 )

Инициирует пользовательский поток для вычислений Microprofile, чтобы избежать всплесков, которые иначе регистрируются Microprofile при регистрации нового потока. Этот метод следует вызывать в начале потока и перед [*beginMicro()*](#beginMicro_cstr_int_int), а затем вызывать [*shutdownThread()*](#shutdownThread_void), когда поток больше не нужен.
```cpp
void thread_function()
{
	// инициируем поток для профилирования
	Profiler::initThread("thread1");

	while (true) //цикл потока
	{
		// запускаем счётчик
		int c_id = Profiler::beginMicro("mesh");

		//...код для профилирования.../

		// останавливаем счётчик
		Profiler::endMicro(c_id);
	}

	// завершаем работу потока для профилирования
	Profiler::shutdownThread();
}

```


### Аргументы

- *const char ** **name** - Имя потока, отображаемое в Microprofile.
- *int* **priority** - Порядок (порядковый номер) потока, отображаемый в Microprofile.

## void shutdownThread ( )

Останавливает ранее [activated](#initThread_cstr_int_void) счётчик потока Microprofile. Этот метод следует вызывать после [*endMicro()*](#endMicro_int_void) и перед завершением потока.
## int findCounter ( const char * name ) const

Возвращает номер счётчика по его имени.
### Аргументы

- *const char ** **name** - Имя счётчика.

### Возвращаемое значение

Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).
## const char * getCounterName ( int num ) const

Возвращает имя счётчика по его номеру.
### Аргументы

- *int* **num** - Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).

### Возвращаемое значение

Имя счётчика.
## const char * getCounterText ( int num ) const

Возвращает текст указанного счётчика.
### Аргументы

- *int* **num** - Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).

### Возвращаемое значение

Текст счётчика.
## Math:: vec4 getCounterColor ( int num ) const

Возвращает цвет указанного счётчика.
### Аргументы

- *int* **num** - Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).

### Возвращаемое значение

Цвет счётчика.
## float getCounterValue ( int num ) const

Возвращает значение указанного счётчика.
### Аргументы

- *int* **num** - Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).

### Возвращаемое значение

Значение счётчика.
## long long getCounterFrame ( int num ) const

Возвращает кадр указанного счётчика.
### Аргументы

- *int* **num** - Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).

### Возвращаемое значение

Кадр счётчика.
## bool isCounterActive ( int num ) const

Возвращает значение, указывающее, активен ли указанный счётчик.
### Аргументы

- *int* **num** - Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).

### Возвращаемое значение

true, если счётчик активен; иначе false.
## bool isCounterSeparator ( int num ) const

Возвращает значение, указывающее, размещён ли разделитель после указанного счётчика.
### Аргументы

- *int* **num** - Номер счётчика в диапазоне от 0 до [total number of counters](#NumCounters).

### Возвращаемое значение

true, если разделитель размещён; иначе false.
## static void startProfilerDump ( const char * path = nullptr )

***Console*:**`profiling_start`Начинает сбор дампа профайлера по указанному пути к файлу. Дамп профайлера содержит данные о производительности во время выполнения по кадрам, которые впоследствии можно проанализировать с помощью класса *[ProfilerDump](../../../api/library/engine/class.profilerdump_cpp.md)*. Запись продолжается до тех пор, пока не будет вызван метод *[*stopProfilerDump()*](../../../api/library/engine/class.profiler_cpp.md#stopProfilerDump_void)* или команда [profiling_stop](../../../code/console/index.md#profiling_stop).
### Аргументы

- *const char ** **path** - Путь к файлу, в который будет записан дамп профайлера. Вы можете указать абсолютный путь или путь относительно *[profiling_dump_dir](../../../code/console/index.md#profiling_dump_dir)*. Если путь не указан, дамп профайлера будет сохранён по адресу: `profiling_dump_dir/profiling_dump_{currentdatetime}`

## static void startProfilerDump ( int frames , const char * path = nullptr )

***Console*:**`profiling_start_frames`Начинает сбор дампа профайлера для указанного количества кадров и записывает его по заданному пути к файлу. Дамп профайлера содержит данные о производительности во время выполнения по кадрам, которые впоследствии можно проанализировать с помощью класса *[ProfilerDump](../../../api/library/engine/class.profilerdump_cpp.md)*. Запись автоматически останавливается после указанного количества кадров или раньше, если вызван метод *[*stopProfilerDump()*](../../../api/library/engine/class.profiler_cpp.md#stopProfilerDump_void)* или команда [profiling_stop](../../../code/console/index.md#profiling_stop).
### Аргументы

- *int* **frames** - Количество кадров для записи данных. Профайлер автоматически остановит запись по истечении этого периода.
- *const char ** **path** - Путь к файлу, в который будет записан дамп профайлера. Вы можете указать абсолютный путь или путь относительно *[profiling_dump_dir](../../../code/console/index.md#profiling_dump_dir)*. Если путь не указан, дамп профайлера будет сохранён по адресу: `profiling_dump_dir/profiling_dump_{currentdatetime}`

## static void startProfilerDump ( float seconds , const char * path = nullptr )

***Console*:**`profiling_start_seconds`Начинает сбор дампа профайлера в течение указанной продолжительности (в секундах) и записывает его по заданному пути к файлу. Дамп профайлера содержит данные о производительности во время выполнения по кадрам, которые впоследствии можно проанализировать с помощью класса *[ProfilerDump](../../../api/library/engine/class.profilerdump_cpp.md)*. Запись автоматически останавливается после указанного количества секунд или раньше, если вызван метод *[*stopProfilerDump()*](../../../api/library/engine/class.profiler_cpp.md#stopProfilerDump_void)* или команда [profiling_stop](../../../code/console/index.md#profiling_stop).
### Аргументы

- *float* **seconds** - Продолжительность в секундах, в течение которой профайлер должен собирать данные. Профайлер автоматически остановит запись по истечении этого периода.
- *const char ** **path** - Путь к файлу, в который будет записан дамп профайлера. Вы можете указать абсолютный путь или путь относительно *[profiling_dump_dir](../../../code/console/index.md#profiling_dump_dir)*. Если путь не указан, дамп профайлера будет сохранён по адресу: `profiling_dump_dir/profiling_dump_{currentdatetime}`

## static bool isProfilerDumpEnabled ( )

Проверяет, ведётся ли в данный момент запись дампа профайлера.
### Возвращаемое значение

true, если дамп профайлера в данный момент записывается; иначе false.
## static void stopProfilerDump ( )

***Console*:**`profiling_stop`Останавливает текущую активную запись дампа профайлера. Если запись дампа профайлера выполняется, вызов этого метода завершает дамп и закрывает выходной файл.
