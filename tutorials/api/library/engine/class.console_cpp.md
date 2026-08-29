# Класс Unigine::Console (CPP)

**Заголовочный файл:** #include <UnigineConsole.h>

> **Примечание:** Этот класс является одиночкой (singleton).


Управляет параметрами, связанными с [console](../../../code/console/index.md).


### Экранное наложение консоли


По умолчанию наложение консоли отключено. Чтобы оно выводило сообщения консоли на экран приложения, его нужно [enabled](#isOnscreen_int). Вы можете настроить поведение и внешний вид наложения, а также указать сообщения, которые будут выводиться исключительно в экранное наложение и не будут записываться в консоль.
 ![](overlay.png)

*Экранное наложение с пользовательскими параметрами и цветным текстом*


Вы можете настроить шрифт консоли с помощью методов [setFontSize()](#setFontSize_int_void), [setMessageColor()](#setMessageColor_vec4_void), [setWarningColor()](#setWarningColor_vec4_void) и [setErrorColor()](#setErrorColor_vec4_void). См. следующий пример:


```cpp
#include "AppWorldLogic.h"
#include <UnigineConsole.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	// включаем экранное наложение
	Console::setOnscreen(true);
	// увеличиваем размер шрифта консоли
	Console::setFontSize(20);

	// меняем цвет для разных типов сообщений
	Console::setMessageColor(Unigine::Math::vec4_green);
	Console::setWarningColor(Unigine::Math::vec4_red);
	Console::setErrorColor(Unigine::Math::vec4_blue);

	// отправляем сообщения в консоль
	Log::message("Message!\n");
	Log::warning("Warning!\n");
	Log::error("Error!\n");

	return 1;
}


```


### Добавление консольной команды с несколькими аргументами


Класс Console можно использовать для создания пользовательских консольных команд с разным количеством аргументов. В этом разделе приведён пример создания пользовательской консольной команды с несколькими аргументами.

  Предварительные знанияПредполагается, что вы уже [created an empty C++ project](../../../code/cpp/application.md#empty_application) с помощью UNIGINE SDK Browser.
В примере ниже мы выполняем следующие действия:


- Определяем и реализуем методы экземпляра [*AppWorldLogic*](../../../code/fundamentals/execution_sequence/app_logic_system.md) для консольных команд.
- Получаем экземпляр консоли (реализованный как одиночка) и добавляем новую команду.


##### 1. Добавление методов экземпляра


В этом примере мы определяем три метода в заголовочном файле `AppWorldLogic.h` — один как обратный вызов для консольной команды и ещё два метода для действий в зависимости от количества аргументов:


```cpp
/* ... */

class AppWorldLogic : public Unigine::WorldLogic
{

public:
	AppWorldLogic();

	/* ... */

private:
	// выбирает метод для выполнения при вызове консольной команды
	void choose_command(int argc, char** argv);
	// выполняет действие, если аргументов нет
	void action_no_args();
	// выполняет другое действие, если был передан аргумент
	void action_one_arg(const char* s);

};


```


- *choose_command()* выбирает подходящий метод.
- *action_no_args()* вызывается, если аргументы консоли отсутствуют.
- *action_one_arg()* вызывается, если был передан аргумент.


В файле `AppWorldLogic.cpp` реализуем недавно определённые методы:


```cpp
// проверяем количество аргументов и вызываем соответствующий метод
void AppWorldLogic::choose_command(int argc, char** argv) {
	for (int i = 0; i < argc; i++) {
		Log::message("arg[%d]: %s\n", i, argv[i]);
	}
	// примечание: первый элемент argv — это имя консольной команды
	if (argc == 1) {
		action_no_args();
	}
	else if (argc == 2) {
		action_one_arg(argv[1]);
	}
	// для большего числа аргументов:
	//else if (...) {
	//	// и т.д.
	//}
}
// записываем сообщение в консоль, если аргументов нет
void AppWorldLogic::action_no_args() {
	Log::message("first action! no arguments!\n");
}
// записываем сообщение в консоль, если был передан аргумент
void AppWorldLogic::action_one_arg(const char* s) {
	Log::message("second action! the argument is:%s \n", s);
}


```


Аргументы ***argc*** и ***argv*** используются для получения *количества аргументов* и *вектора аргументов*.


> **Примечание:** Первый элемент `argv` всегда содержит имя консольной команды. Таким образом, `argc` всегда >= **1**. Чтобы получить первый переданный аргумент, следует использовать *argv[1]*.


##### 2. Добавление пользовательской консольной команды


Добавьте пользовательскую команду в файл `AppWorldLogic.cpp` с помощью функции *[addCommand()](#addCommand_cstr_cstr_CommandCallback_int)*. Добавив этот код в функцию *AppWorldLogic::init()*, движок добавит новую консольную команду при инициализации экземпляра класса AppWorldLogic.


```cpp
#include "AppWorldLogic.h"
#include <UnigineConsole.h>

#include <UnigineCallback.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	// получаем существующий экземпляр-одиночку Console и добавляем команду
	Console::addCommand(
		"console_action",
		"Performs custom console action",
		MakeCallback(this, &AppWorldLogic::choose_command)
	);

	return 1;
}


```


##### 3. Запуск примера


После сборки проекта запустите его и откройте консоль. Введите недавно созданную команду, чтобы увидеть результат:


```text
#if you write "console_action"
arg[0]: console_action
first action! no arguments!

#if you write "console_action arg"
arg[0]: console action
arg[1]: arg
second action! the argument is:arg

```


Чтобы удалить добавленную консольную команду, используйте метод *[removeCommand()](#removeCommand_cstr_int)*.


### См. также


- Пример на C++
- Видео HowTo о [Printing User Messages to Console with C#](../../../videotutorials/how_to/how_to_cs/logging.md)


## Класс Console

### Перечисления

## LEVEL

| Имя | Описание |
|---|---|
| **LEVEL_NORMAL** = 0 | Обычное сообщение. |
| **LEVEL_WARNING** = 1 | Предупреждение. |
| **LEVEL_ERROR** = 2 | Сообщение об ошибке. |

### Методы класса

## void setLock ( int lock )

Устанавливает новое значение, показывающее, отключена ли консоль.
### Аргументы

- *int* **lock** - Значение **1** (или любое положительное значение) означает, что консоль отключена; значение **0** соответствует включённой (разблокированной) консоли.

## int getLock () const

Возвращает текущее значение, показывающее, отключена ли консоль.
### Возвращаемое значение

Текущее значение **1** (или любое положительное значение) означает, что консоль отключена; значение **0** соответствует включённой (разблокированной) консоли.
## int getNumCommands () const

Возвращает текущее количество всех доступных консольных команд, включая пользовательские.
### Возвращаемое значение

Текущее количество доступных консольных [commands](../../../code/console/index.md#command).
## int getNumVariables () const

Возвращает текущее количество всех доступных переменных консоли.
### Возвращаемое значение

Текущее количество доступных [variables](../../../code/console/index.md#variable) консоли.
## void setActive ( bool active )

Устанавливает новое значение, указывающее, открыта или закрыта консоль.
### Аргументы

- *bool* **active** - **true** — включить активное (открытое) состояние консоли; **false** — отключить.

## bool isActive () const

Возвращает текущее значение, указывающее, открыта или закрыта консоль.
### Возвращаемое значение

**true**, если активное (открытое) состояние консоли включено; иначе **false**.
## const char * getLastError () const

Возвращает текущее последнее сообщение об ошибке, выведенное в консоль.
### Возвращаемое значение

Текущее последнее сообщение об ошибке, выведенное в консоль.
## const char * getLastWarning () const

Возвращает текущее последнее предупреждение, выведенное в консоль.
### Возвращаемое значение

Текущее последнее предупреждение, выведенное в консоль.
## const char * getLastMessage () const

Возвращает текущее последнее сообщение, выведенное в консоль.
### Возвращаемое значение

Текущее последнее сообщение, выведенное в консоль.
## void setOnscreenTime ( float time )

Устанавливает новое время, в течение которого текст отображается на экране.
### Аргументы

- *float* **time** - Время, в течение которого текст отображается на экране, в секундах.

## float getOnscreenTime () const

Возвращает текущее время, в течение которого текст отображается на экране.
### Возвращаемое значение

Текущее время, в течение которого текст отображается на экране, в секундах.
## void setOnscreenHeight ( int height )

Устанавливает новую высоту экранного наложения.
### Аргументы

- *int* **height** - Высота экранного наложения в процентах от высоты окна.

## int getOnscreenHeight () const

Возвращает текущую высоту экранного наложения.
### Возвращаемое значение

Текущая высота экранного наложения в процентах от высоты окна.
## void setOnscreenFontSize ( int size )

Устанавливает новый размер шрифта экранного наложения.
### Аргументы

- *int* **size** - Размер шрифта экранного наложения.

## int getOnscreenFontSize () const

Возвращает текущий размер шрифта экранного наложения.
### Возвращаемое значение

Текущий размер шрифта экранного наложения.
## void setOnscreen ( bool onscreen )

Устанавливает новое значение, указывающее, отображается или скрыто экранное наложение.
### Аргументы

- *bool* **onscreen** - **true** — включить отображение экранного наложения; **false** — отключить.

## bool isOnscreen () const

Возвращает текущее значение, указывающее, отображается или скрыто экранное наложение.
### Возвращаемое значение

**true**, если отображение экранного наложения включено; иначе **false**.
## void setFontSize ( int size )

Устанавливает новый текущий размер шрифта, используемый для сообщений консоли.
### Аргументы

- *int* **size** - Текущий размер шрифта, используемый для сообщений консоли.

## int getFontSize () const

Возвращает текущий размер шрифта, используемый для сообщений консоли.
### Возвращаемое значение

Текущий размер шрифта, используемый для сообщений консоли.
## void setWrapping ( bool wrapping )

Устанавливает новое значение, указывающее, включён ли перенос текста для консоли.
### Аргументы

- *bool* **wrapping** - **true** — включить перенос текста для консоли; **false** — отключить.

## bool isWrapping () const

Возвращает текущее значение, указывающее, включён ли перенос текста для консоли.
### Возвращаемое значение

**true**, если перенос текста для консоли включён; иначе **false**.
## void setHeight ( int height )

Устанавливает новую высоту консоли в процентах от высоты окна.
### Аргументы

- *int* **height** - Высота консоли в процентах от высоты окна.

## int getHeight () const

Возвращает текущую высоту консоли в процентах от высоты окна.
### Возвращаемое значение

Текущая высота консоли в процентах от высоты окна.
## void setLimit ( int limit )

Устанавливает новое максимальное количество сообщений, которое может выводить консоль. Значение по умолчанию — **16384**.
### Аргументы

- *int* **limit** - Максимальное количество сообщений, которое может выводить консоль. Значение по умолчанию — **16384**.

## int getLimit () const

Возвращает текущее максимальное количество сообщений, которое может выводить консоль. Значение по умолчанию — **16384**.
### Возвращаемое значение

Текущее максимальное количество сообщений, которое может выводить консоль. Значение по умолчанию — **16384**.
## void setPrompt ( const char * prompt )

Устанавливает новое приглашение консоли.
### Аргументы

- *const char ** **prompt** - Текст приглашения консоли.

## const char * getPrompt () const

Возвращает текущее приглашение консоли.
### Возвращаемое значение

Текущий текст приглашения консоли.
## void setTextColor ( const Math:: vec4 & color )

Устанавливает новый общий цвет шрифта для консоли.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getTextColor () const

Возвращает текущий общий цвет шрифта для консоли.
### Возвращаемое значение

Текущий четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setErrorColor ( const Math:: vec4 & color )

Устанавливает новый цвет для сообщений об ошибках в консоли.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getErrorColor () const

Возвращает текущий цвет для сообщений об ошибках в консоли.
### Возвращаемое значение

Текущий четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setWarningColor ( const Math:: vec4 & color )

Устанавливает новый цвет для предупреждений в консоли.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getWarningColor () const

Возвращает текущий цвет для предупреждений в консоли.
### Возвращаемое значение

Текущий четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setMessageColor ( const Math:: vec4 & color )

Устанавливает новый цвет для обычных сообщений в консоли.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getMessageColor () const

Возвращает текущий цвет для обычных сообщений в консоли.
### Возвращаемое значение

Текущий четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## void setBackgroundColor ( const Math:: vec4 & color )

Устанавливает новый цвет фона для консоли.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getBackgroundColor () const

Возвращает текущий цвет фона для консоли.
### Возвращаемое значение

Текущий четырёхкомпонентный вектор, задающий цвет в формате RGBA.
## Event<const char *, Console::LEVEL > getEventOutput () const

Событие, срабатывающее при выводе текста в консоль. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события Output
void output_event_handler(const char * text,  Console::LEVEL level)
{
	switch (level) {
	case Console::LEVEL_NORMAL:
		// логика для обычных сообщений
	case Console::LEVEL_WARNING:
		// логика для предупреждений
	case Console::LEVEL_ERROR:
		// логика для сообщений об ошибках
	}
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections output_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Console::getEventOutput().connect(output_event_connections, output_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Console::getEventOutput().connect(output_event_connections, [](const char * text,  Console::LEVEL level) {
		Log::message("\Обработка события Output (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
output_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection output_event_connection;

// подписываемся на событие Output с функцией-обработчиком, сохраняя соединение
Console::getEventOutput().connect(output_event_connection, output_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
output_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
output_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Output через соединение
output_event_connection.disconnect();

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

	// Обработчик события Output, реализованный как член класса
	void event_handler(const char * text,  Console::LEVEL level)
	{
		Log::message("\Обработка события Output\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Console::getEventOutput().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. Можно подписываться и отписываться напрямую через функцию-обработчик
//////////////////////////////////////////////////////////////////////////////

// подписываемся на событие Output с функцией-обработчиком
Console::getEventOutput().connect(output_event_handler);

// удаляем подписку на событие Output позже через функцию-обработчик
Console::getEventOutput().disconnect(output_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Подписка на событие с сохранением идентификатора и последующей отпиской по нему
//////////////////////////////////////////////////////////////////////////////

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId output_handler_id;

// подписываемся на событие Output с лямбда-обработчиком, сохраняя идентификатор соединения
output_handler_id = Console::getEventOutput().connect([](const char * text,  Console::LEVEL level) {
		Log::message("\Обработка события Output (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Console::getEventOutput().disconnect(output_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Игнорирование всех событий Output при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Console::getEventOutput().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Console::getEventOutput().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const char * **text**, Console::LEVEL **level**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Output
void output_event_handler(const char * text,  Console::LEVEL level)
{
	Log::message("\Обработка события Output\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections output_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventOutput().connect(output_event_connections, output_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventOutput().connect(output_event_connections, [](const char * text,  Console::LEVEL level) {
		Log::message("\Обработка события Output (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
output_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection output_event_connection;

// подписываемся на событие Output с функцией-обработчиком, сохраняя соединение
publisher->getEventOutput().connect(output_event_connection, output_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
output_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
output_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Output через соединение
output_event_connection.disconnect();

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

	// Обработчик события Output, реализованный как член класса
	void event_handler(const char * text,  Console::LEVEL level)
	{
		Log::message("\Обработка события Output\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventOutput().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId output_handler_id;

// подписываемся на событие Output с лямбда-обработчиком, сохраняя идентификатор соединения
output_handler_id = publisher->getEventOutput().connect(e_connections, [](const char * text,  Console::LEVEL level) {
		Log::message("\Обработка события Output (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventOutput().disconnect(output_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Output при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventOutput().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventOutput().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## bool isCommand ( const char * name ) const

Возвращает значение, указывающее, существует ли команда с заданным именем.
### Аргументы

- *const char ** **name** - Имя команды.

### Возвращаемое значение

**true**, если команда с заданным именем существует; иначе **false**.
## const char * getCommandDescription ( const char * name ) const

Возвращает описание консольной команды по её имени. Если имя не указано, будет возвращена пустая строка.
### Аргументы

- *const char ** **name** - Имя команды.

### Возвращаемое значение

Описание команды, если оно существует; иначе пустая строка.
## const char * getCommandName ( int num ) const

Возвращает имя консольной команды по её номеру в массиве существующих команд.
### Аргументы

- *int* **num** - Номер команды.

### Возвращаемое значение

Имя команды, если она найдена в массиве существующих команд; иначе пустая строка.
## void setFloat ( const char * name , float value )

Устанавливает значение с плавающей точкой для заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *float* **value** - Значение переменной с плавающей точкой.

## float getFloat ( const char * name ) const

Возвращает значение с плавающей точкой заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Значение переменной с плавающей точкой.
## float getFloatMax ( const char * name ) const

Возвращает максимальное значение с плавающей точкой для заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Максимальное значение переменной с плавающей точкой.
## float getFloatMin ( const char * name ) const

Возвращает минимальное значение с плавающей точкой для заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Минимальное значение переменной с плавающей точкой.
## bool isFloat ( const char * name ) const

Проверяет, имеет ли значение, установленное для заданной переменной консоли, тип с плавающей точкой.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

True, если значение переменной с плавающей точкой; иначе false.
## void setInt ( const char * name , int value )

Устанавливает целочисленное значение для заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *int* **value** - Целочисленное значение переменной.

## int getInt ( const char * name ) const

Возвращает целочисленное значение заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Целочисленное значение переменной.
## int getIntMax ( const char * name ) const

Возвращает максимальное целочисленное значение для заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Максимальное целочисленное значение переменной.
## int getIntMin ( const char * name ) const

Возвращает минимальное целочисленное значение для заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Минимальное целочисленное значение переменной.
## bool isInt ( const char * name ) const

Проверяет, имеет ли значение заданной переменной консоли целочисленный тип.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

True, если значение переменной целочисленное; иначе false.
## bool isPalette ( const char * name ) const

Проверяет наличие [palette](../../../api/library/common/class.palette_cpp.md) с указанным именем.
### Аргументы

- *const char ** **name** - Имя палитры.

## void setPalette ( const char * name , const Palette& value )

Устанавливает цветовую [palette](../../../api/library/common/class.palette_cpp.md) по её имени.
### Аргументы

- *const char ** **name** - Имя палитры.
- *const Palette&* **value** - Устанавливаемая палитра.

## void setPalette ( const char * name , int index , float value )

Устанавливает значение для указанного цвета [palette](../../../api/library/common/class.palette_cpp.md) по его индексу.
### Аргументы

- *const char ** **name** - Имя палитры.
- *int* **index** - Индекс цвета палитры.
- *float* **value** - Значение, устанавливаемое для цвета с указанным индексом.

## void setPalette ( const char * name , const char * color , float value )

Устанавливает значение для указанного цвета [palette](../../../api/library/common/class.palette_cpp.md) по имени цвета.
### Аргументы

- *const char ** **name** - Имя палитры.
- *const char ** **color** - Имя цвета палитры.
- *float* **value** - Значение, устанавливаемое для цвета с указанным именем.

## Palette getPalette ( const char * name ) const

Возвращает цветовую [palette](../../../api/library/common/class.palette_cpp.md) по её имени.
### Аргументы

- *const char ** **name** - Имя палитры.

### Возвращаемое значение

Палитра с указанным именем, если она существует; иначе nullptr.
## void setString ( const char * name , const char * value )

Устанавливает строковое значение для заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const char ** **value** - Строковое значение переменной.

## const char * getString ( const char * name ) const

Возвращает строковое значение заданной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Строковое значение переменной.
## bool isString ( const char * name ) const

Проверяет, имеет ли значение заданной переменной консоли строковый тип.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

True, если значение переменной строковое; иначе false.
## bool isVariable ( const char * name ) const

Возвращает значение, указывающее, существует ли переменная с заданным именем.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

True, если переменная существует; иначе false.
## const char * getVariableDescription ( const char * name ) const

Возвращает описание переменной консоли по её имени. Если имя не указано, будет возвращена пустая строка.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Описание переменной, если оно существует; иначе пустая строка.
## const char * getVariableName ( int num ) const

Возвращает имя переменной консоли по её номеру в массиве существующих переменных.
### Аргументы

- *int* **num** - Номер переменной.

### Возвращаемое значение

Имя переменной, если она найдена в массиве существующих переменных; иначе пустая строка.
## void setVec2 ( const char * name , const Math:: vec2 & value )

Устанавливает двухкомпонентный вектор для переменной консоли.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Значение переменной.

## Math:: vec2 getVec2 ( const char * name ) const

Возвращает двухкомпонентный вектор переменной консоли.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Значение переменной.
## bool isVec2 ( const char * name ) const

Возвращает значение, указывающее, является ли переменная консоли двухкомпонентным вектором.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

True, если переменная является двухкомпонентным вектором; иначе false.
## void setVec3 ( const char * name , const Math:: vec3 & value )

Устанавливает трёхкомпонентный вектор для переменной консоли.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Значение переменной.

## Math:: vec3 getVec3 ( const char * name ) const

Возвращает трёхкомпонентный вектор переменной консоли.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Значение переменной.
## bool isVec3 ( const char * name ) const

Возвращает значение, указывающее, является ли переменная консоли трёхкомпонентным вектором.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

**True**, если переменная является трёхкомпонентным вектором; иначе **false**.
## void setVec4 ( const char * name , const Math:: vec4 & value )

Устанавливает четырёхкомпонентный вектор для переменной консоли.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Значение переменной.

## Math:: vec4 getVec4 ( const char * name ) const

Возвращает четырёхкомпонентный вектор переменной консоли.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Значение переменной.
## bool isVec4 ( const char * name ) const

Возвращает значение, указывающее, является ли переменная консоли четырёхкомпонентным вектором.
### Аргументы

- *const char ** **name**

### Возвращаемое значение

**True**, если переменная является трёхкомпонентным вектором; иначе **false**.
## int addCommand ( const char * name , const char * desc , CallbackBase * callback )

Добавляет [custom console command](#adding_command), привязанную к заданной функции обратного вызова.
### Аргументы

- *const char ** **name** - Имя новой консольной команды.
- *const char ** **desc** - Краткое описание, отображаемое в консоли.
- *[CallbackBase](../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Указатель на обратный вызов. Аргументы обратного вызова должны быть (*int* **argc**, *char*** **argv**,...).

### Возвращаемое значение

1, если пользовательская команда успешно добавлена; иначе 0.
## void flush ( )

Принудительно выполняет все команды консоли из очереди.
## bool removeCommand ( const char * name )

Удаляет пользовательскую консольную команду.
### Аргументы

- *const char ** **name** - Имя пользовательской консольной команды.

### Возвращаемое значение

true, если пользовательская команда успешно удалена; иначе 0.
## void run ( const char * command )

Выполняет указанную консольную команду.
### Аргументы

- *const char ** **command** - Консольная команда с аргументами.

## void write ( const char * text )

Записывает указанный текст в консоль и отображает его на экране (экранное наложение).
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **text** - Текст для вывода в консоль.

## void write ( const Math:: vec4 & color , const char * text )

Записывает указанный текст в консоль и отображает его на экране (экранное наложение).
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **text** - Текст для вывода в консоль.

## void write ( Console::LEVEL level , const char * text )

Записывает указанный текст в консоль и отображает его на экране (экранное наложение).
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *[Console::LEVEL](../../../api/library/engine/class.console_cpp.md#LEVEL)* **level** - Тип сообщения.
- *const char ** **text** - Текст для вывода в консоль.

## static void getMessages ( Vector < String > & messages , int limit )

Получает сообщения, записанные в консоль и экранное наложение.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md) < [String](../../../api/library/common/class.string_cpp.md) > &* **messages** - Вектор для заполнения сообщениями.
- *int* **limit** - Максимальное количество сообщений для получения.

## void getMessages ( Vector < String > & OUT_messages , Vector < int > & OUT_levels , int limit ) const

### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **OUT_messages** - Вектор для заполнения сообщениями. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **OUT_levels** - Типы сообщений для получения. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *int* **limit** - Максимальное количество сообщений для получения.

## static void getWarnings ( Vector < String > & messages , int limit )

Получает предупреждения, записанные в консоль и экранное наложение.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md) < [String](../../../api/library/common/class.string_cpp.md) > &* **messages** - Вектор для заполнения сообщениями.
- *int* **limit** - Максимальное количество сообщений для получения.

## void getErrors ( Vector < String > & messages , int limit )

Получает сообщения об ошибках, записанные в консоль и экранное наложение.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md) < [String](../../../api/library/common/class.string_cpp.md) > &* **messages** - Вектор для заполнения сообщениями.
- *int* **limit** - Максимальное количество сообщений для получения.

## static void writeLine ( const char * text )

Записывает текст с последующим символом конца строки в консоль и экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **text** - Текст для вывода в консоль.

## static void writeLine ( const Math:: vec4 & color , const char * text )

Записывает текст с последующим символом конца строки в консоль и экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **text** - Текст для вывода в консоль.

## static void writeLine ( Console::LEVEL level , const char * text )

Записывает текст с последующим символом конца строки в консоль и экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *[Console::LEVEL](../../../api/library/engine/class.console_cpp.md#LEVEL)* **level** - Тип сообщения.
- *const char ** **text** - Текст для вывода в консоль.

## static void onscreenWrite ( const char * text )

Записывает текст только в экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **text** - Текст для вывода в консоль.

## static void onscreenWrite ( const Math:: vec4 color , const char * text )

Записывает текст только в экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **text** - Текст для вывода в консоль.

## static void onscreenWrite ( Console::LEVEL level , const char * text )

Записывает текст только в экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *[Console::LEVEL](../../../api/library/engine/class.console_cpp.md#LEVEL)* **level** - Тип сообщения.
- *const char ** **text** - Текст для вывода в консоль.

## static void onscreenWriteLine ( const char * text )

Записывает текст только в экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **text** - Текст для вывода в консоль.

## static void onscreenWriteLine ( Math:: vec4 & color , const char * text )

Записывает текст только в экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **text** - Текст для вывода в консоль.

## static void onscreenWriteLine ( Console::LEVEL level , const char * text )

Записывает текст только в экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *[Console::LEVEL](../../../api/library/engine/class.console_cpp.md#LEVEL)* **level** - Тип сообщения.
- *const char ** **text** - Текст для вывода в консоль.

## static void message ( const Unigine:: Math:: vec4 & color , const char * format , ... )

Записывает обычное сообщение в консоль и экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const  Unigine:: Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void message ( const char * format , ... )

Записывает обычное сообщение в консоль и экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void warning ( const char * format , ... )

Записывает предупреждение в консоль и экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void error ( const char * format , ... )

Записывает сообщение об ошибке в консоль и экранное наложение.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void messageLine ( const Unigine:: Math:: vec4 & color , const char * format , ... )

Записывает обычное сообщение в консоль и экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const  Unigine:: Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void messageLine ( const char * format , ... )

Записывает обычное сообщение в консоль и экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void warningLine ( const char * format , ... )

Записывает предупреждение в консоль и экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void errorLine ( const char * format , ... )

Записывает сообщение об ошибке в консоль и экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста [onscreen overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenMessage ( const Unigine:: Math:: vec4 & color , const char * format , ... )

Записывает обычное сообщение только в экранное наложение.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const  Unigine:: Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenMessage ( const char * format , ... )

Записывает обычное сообщение только в экранное наложение.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenWarning ( const char * format , ... )

Записывает предупреждение только в экранное наложение.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenError ( const char * format , ... )

Записывает сообщение об ошибке только в экранное наложение.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenMessageLine ( const Unigine:: Math:: vec4 & color , const char * format , ... )

Записывает обычное сообщение только в экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const  Unigine:: Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет текста в формате RGBA.
- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenMessageLine ( const char * format , ... )

Записывает обычное сообщение только в экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenWarningLine ( const char * format , ... )

Записывает предупреждение только в экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.

## static void onscreenErrorLine ( const char * format , ... )

Записывает сообщение об ошибке только в экранное наложение с последующим символом конца строки.
> **Notice:** Для отображения текста на экране [console overlay](#onscreen_console_overlay) должно быть [enabled](#isOnscreen_int).


### Аргументы

- *const char ** **format** - Форматированный текст.
- *...*  - Аргументы, допускается несколько.
