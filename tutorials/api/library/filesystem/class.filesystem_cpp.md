# Unigine::FileSystem Class (CPP)

**Header:** #include <UnigineFileSystem.h>

> **Notice:** This class is a singleton.


При инициализации [Engine file system](../../../principles/filesystem/index_cpp.md) все файлы и пакеты, хранящиеся в папке `data`, автоматически добавляются в виртуальную файловую систему. При этом содержимое пакетов ZIP и UNG загружается в RAM как есть (поэтому не рекомендуется хранить тяжёлый контент (например, террейны) в пакетах).


Файлы и пакеты, хранящиеся вне каталога `data`, также добавляются в виртуальную файловую систему, если они [mounted](../../../principles/filesystem/index_cpp.md#mount_points) (т.е. на них ссылается точка монтирования).

> **Notice:** Если вы добавляете новые файлы во время выполнения, движок ничего не будет знать о таких файлах. Чтобы добавить файлы в виртуальную файловую систему, используйте *[addVirtualFile()](#addVirtualFile_cstr_UGUID_bool_bool)*.


Функции файловой системы:

- Обеспечивают контроль над [asynchronous loading](../../../api/library/filesystem/class.asyncqueue_cpp.md) файлов/мешей/изображений/узлов по требованию внутри каталога `data`, включая файлы в пакетах ZIP и UNG. Такие пакеты [automatically handled](../../../principles/filesystem/index_cpp.md#file_packages) движком, и все их файлы автоматически добавляются в файловую систему.
- Позволяют добавлять каталоги (даже с пакетами ZIP и UNG), находящиеся [outside](../../../principles/filesystem/index_cpp.md#mount_points) каталога `data`, и обеспечивают [control over loading](../../../api/library/filesystem/class.asyncqueue_cpp.md) таких файлов.
- Позволяют добавлять пакеты ZIP и UNG, находящиеся [outside the `data`](../../../principles/filesystem/index_cpp.md#mount_points). После этого доступ к файлам в таких пакетах осуществляется обычным способом, указывая путь к файлу только внутри пакета.
- Позволяют [caching](#addCacheFile_cstr_bool) файлы в памяти и [adding files to blobs](#addBlobFile_cstr_bool), если к ним обращаются или их изменяют многократно во время выполнения.


Также методы класса FileSystem можно использовать при реализации собственного импортёра из внешнего формата в нативные форматы UNIGINE. Например, можно хранить на диске только оригинальный файл, а файлы в нативных форматах UNIGINE хранить только в виртуальной файловой системе.


> **Notice:** This class is in the **Unigine** namespace.


### Получение имени файла ассета


Используя [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета или путь к исходному файлу на диске, можно получить доступ к имени файла следующим образом:


```cpp
String input = "guid://857e03518c10647cb16975abc15f0f0e66a04b15"; // ассет должен быть указан по GUID

// для текстуры может быть возвращено одно из двух возможных имён файлов
//String input = ".runtimes/de/857e03518c10647cb16975abc15f0f0e66a04b15.texture"; // текстура может иметь runtime-версию
//String input = "test/test.png"; // или исходная версия может использоваться как runtime

// получаем виртуальный путь
const UGUID &guid = FileSystem::getGUID(input); // GUID для указанного файла
const UGUID &asset_guid = FileSystemAssets::resolveAsset(guid); // соответствующий GUID ассета
const String &asset_virtual_filepath = FileSystem::getVirtualPath(asset_guid); // виртуальный путь для указанного GUID файла

// получаем и выводим имя файла
Log::message("Filepath: %s\n", asset_virtual_filepath.get()); // виртуальный путь
Log::message("Filename: %s\n", asset_virtual_filepath.filename().get()); // имя файла без расширения
Log::message("Basename: %s\n", asset_virtual_filepath.basename().get()); // имя файла с расширением

```


### См. также


- [AsyncQueue Class](../../../api/library/filesystem/class.asyncqueue_cpp.md) для управления загрузкой ресурсов (файлов, изображений, мешей и узлов) по требованию.


## FileSystem Class

### Методы класса

## int getNumModifiers () const

Возвращает текущее общее количество модификаторов файлов, зарегистрированных в файловой системе.
### Возвращаемое значение

Текущее общее количество модификаторов файлов, зарегистрированных в файловой системе.
## static Event<const UGUID &, const char *> getEventFileChanged () const

Событие, срабатывающее при изменении файла через FileSystem API. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const UGUID & **guid**, const char * **path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FileChanged
void filechanged_event_handler(const UGUID & guid,  const char * path)
{
	Log::message("\Обработка события FileChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections filechanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
FileSystem::getEventFileChanged().connect(filechanged_event_connections, filechanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
FileSystem::getEventFileChanged().connect(filechanged_event_connections, [](const UGUID & guid,  const char * path) {
		Log::message("\Обработка события FileChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
filechanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection filechanged_event_connection;

// подписываемся на событие FileChanged с функцией-обработчиком, сохраняя соединение
FileSystem::getEventFileChanged().connect(filechanged_event_connection, filechanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
filechanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
filechanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FileChanged через соединение
filechanged_event_connection.disconnect();

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

	// Обработчик события FileChanged, реализованный как член класса
	void event_handler(const UGUID & guid,  const char * path)
	{
		Log::message("\Обработка события FileChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
FileSystem::getEventFileChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId filechanged_handler_id;

// подписываемся на событие FileChanged с лямбда-обработчиком, сохраняя идентификатор соединения
filechanged_handler_id = FileSystem::getEventFileChanged().connect(e_connections, [](const UGUID & guid,  const char * path) {
		Log::message("\Обработка события FileChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
FileSystem::getEventFileChanged().disconnect(filechanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FileChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
FileSystem::getEventFileChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
FileSystem::getEventFileChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const UGUID &, const char *> getEventFileRemoved () const

Событие, срабатывающее при удалении файла через FileSystem API. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const UGUID & **guid**, const char * **path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FileRemoved
void fileremoved_event_handler(const UGUID & guid,  const char * path)
{
	Log::message("\Обработка события FileRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections fileremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
FileSystem::getEventFileRemoved().connect(fileremoved_event_connections, fileremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
FileSystem::getEventFileRemoved().connect(fileremoved_event_connections, [](const UGUID & guid,  const char * path) {
		Log::message("\Обработка события FileRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
fileremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection fileremoved_event_connection;

// подписываемся на событие FileRemoved с функцией-обработчиком, сохраняя соединение
FileSystem::getEventFileRemoved().connect(fileremoved_event_connection, fileremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
fileremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
fileremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FileRemoved через соединение
fileremoved_event_connection.disconnect();

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

	// Обработчик события FileRemoved, реализованный как член класса
	void event_handler(const UGUID & guid,  const char * path)
	{
		Log::message("\Обработка события FileRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
FileSystem::getEventFileRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId fileremoved_handler_id;

// подписываемся на событие FileRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
fileremoved_handler_id = FileSystem::getEventFileRemoved().connect(e_connections, [](const UGUID & guid,  const char * path) {
		Log::message("\Обработка события FileRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
FileSystem::getEventFileRemoved().disconnect(fileremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FileRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
FileSystem::getEventFileRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
FileSystem::getEventFileRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const UGUID &, const char *> getEventFileAdded () const

Событие, срабатывающее при добавлении файла через FileSystem API. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const UGUID & **guid**, const char * **path**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FileAdded
void fileadded_event_handler(const UGUID & guid,  const char * path)
{
	Log::message("\Обработка события FileAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections fileadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
FileSystem::getEventFileAdded().connect(fileadded_event_connections, fileadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
FileSystem::getEventFileAdded().connect(fileadded_event_connections, [](const UGUID & guid,  const char * path) {
		Log::message("\Обработка события FileAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
fileadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection fileadded_event_connection;

// подписываемся на событие FileAdded с функцией-обработчиком, сохраняя соединение
FileSystem::getEventFileAdded().connect(fileadded_event_connection, fileadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
fileadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
fileadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FileAdded через соединение
fileadded_event_connection.disconnect();

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

	// Обработчик события FileAdded, реализованный как член класса
	void event_handler(const UGUID & guid,  const char * path)
	{
		Log::message("\Обработка события FileAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
FileSystem::getEventFileAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId fileadded_handler_id;

// подписываемся на событие FileAdded с лямбда-обработчиком, сохраняя идентификатор соединения
fileadded_handler_id = FileSystem::getEventFileAdded().connect(e_connections, [](const UGUID & guid,  const char * path) {
		Log::message("\Обработка события FileAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
FileSystem::getEventFileAdded().disconnect(fileadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FileAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
FileSystem::getEventFileAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
FileSystem::getEventFileAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Vector <FilePath> &> getEventFilesChanged () const

Событие, срабатывающее в конце *Engine::update()*, содержащее файлы, изменённые в течение кадра. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Vector<FilePath> & **paths**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FilesChanged
void fileschanged_event_handler(const Vector<FilePath> & paths)
{
	Log::message("\Обработка события FilesChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections fileschanged_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
FileSystem::getEventFilesChanged().connect(fileschanged_event_connections, fileschanged_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
FileSystem::getEventFilesChanged().connect(fileschanged_event_connections, [](const Vector<FilePath> & paths) {
		Log::message("\Обработка события FilesChanged (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
fileschanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection fileschanged_event_connection;

// подписываемся на событие FilesChanged с функцией-обработчиком, сохраняя соединение
FileSystem::getEventFilesChanged().connect(fileschanged_event_connection, fileschanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
fileschanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
fileschanged_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FilesChanged через соединение
fileschanged_event_connection.disconnect();

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

	// Обработчик события FilesChanged, реализованный как член класса
	void event_handler(const Vector<FilePath> & paths)
	{
		Log::message("\Обработка события FilesChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
FileSystem::getEventFilesChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId fileschanged_handler_id;

// подписываемся на событие FilesChanged с лямбда-обработчиком, сохраняя идентификатор соединения
fileschanged_handler_id = FileSystem::getEventFilesChanged().connect(e_connections, [](const Vector<FilePath> & paths) {
		Log::message("\Обработка события FilesChanged (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
FileSystem::getEventFilesChanged().disconnect(fileschanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FilesChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
FileSystem::getEventFilesChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
FileSystem::getEventFilesChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Vector <FilePath> &> getEventFilesRemoved () const

Событие, срабатывающее в конце *Engine::update()*, содержащее файлы, удалённые в течение кадра. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Vector<FilePath> & **paths**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FilesRemoved
void filesremoved_event_handler(const Vector<FilePath> & paths)
{
	Log::message("\Обработка события FilesRemoved\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections filesremoved_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
FileSystem::getEventFilesRemoved().connect(filesremoved_event_connections, filesremoved_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
FileSystem::getEventFilesRemoved().connect(filesremoved_event_connections, [](const Vector<FilePath> & paths) {
		Log::message("\Обработка события FilesRemoved (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
filesremoved_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection filesremoved_event_connection;

// подписываемся на событие FilesRemoved с функцией-обработчиком, сохраняя соединение
FileSystem::getEventFilesRemoved().connect(filesremoved_event_connection, filesremoved_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
filesremoved_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
filesremoved_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FilesRemoved через соединение
filesremoved_event_connection.disconnect();

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

	// Обработчик события FilesRemoved, реализованный как член класса
	void event_handler(const Vector<FilePath> & paths)
	{
		Log::message("\Обработка события FilesRemoved\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
FileSystem::getEventFilesRemoved().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId filesremoved_handler_id;

// подписываемся на событие FilesRemoved с лямбда-обработчиком, сохраняя идентификатор соединения
filesremoved_handler_id = FileSystem::getEventFilesRemoved().connect(e_connections, [](const Vector<FilePath> & paths) {
		Log::message("\Обработка события FilesRemoved (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
FileSystem::getEventFilesRemoved().disconnect(filesremoved_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FilesRemoved при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
FileSystem::getEventFilesRemoved().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
FileSystem::getEventFilesRemoved().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Vector <FilePath> &> getEventFilesAdded () const

Событие, срабатывающее в конце *Engine::update()*, содержащее файлы, добавленные в течение кадра. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Vector<FilePath> & **paths**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FilesAdded
void filesadded_event_handler(const Vector<FilePath> & paths)
{
	Log::message("\Обработка события FilesAdded\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections filesadded_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
FileSystem::getEventFilesAdded().connect(filesadded_event_connections, filesadded_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
FileSystem::getEventFilesAdded().connect(filesadded_event_connections, [](const Vector<FilePath> & paths) {
		Log::message("\Обработка события FilesAdded (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
filesadded_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection filesadded_event_connection;

// подписываемся на событие FilesAdded с функцией-обработчиком, сохраняя соединение
FileSystem::getEventFilesAdded().connect(filesadded_event_connection, filesadded_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
filesadded_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
filesadded_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FilesAdded через соединение
filesadded_event_connection.disconnect();

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

	// Обработчик события FilesAdded, реализованный как член класса
	void event_handler(const Vector<FilePath> & paths)
	{
		Log::message("\Обработка события FilesAdded\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
FileSystem::getEventFilesAdded().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId filesadded_handler_id;

// подписываемся на событие FilesAdded с лямбда-обработчиком, сохраняя идентификатор соединения
filesadded_handler_id = FileSystem::getEventFilesAdded().connect(e_connections, [](const Vector<FilePath> & paths) {
		Log::message("\Обработка события FilesAdded (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
FileSystem::getEventFilesAdded().disconnect(filesadded_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FilesAdded при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
FileSystem::getEventFilesAdded().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
FileSystem::getEventFilesAdded().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## Ptr < FileSystemMount > getMount ( const char * path ) const

Возвращает [mount point](../../../principles/filesystem/index_cpp.md#mount_points) для указанного пути.
> **Notice:** Этот метод вернёт [root mount](#getRootMount_FileSystemMount) для всех файлов, находящихся непосредственно в папке `data` или её подпапках.


### Аргументы

- *const char ** **path** - Путь к файлу, для которого нужно найти точку монтирования. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

Умный указатель класса [FileSystemMount](../../../api/library/filesystem/class.filesystemmount_cpp.md) при успехе; иначе **nullptr**.
## Ptr < FileSystemMount > getMount ( const UGUID & guid ) const

Возвращает [mount point](../../../principles/filesystem/index_cpp.md#mount_points) для указанного [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
> **Notice:** Этот метод вернёт [root mount](#getRootMount_FileSystemMount) для всех файлов, находящихся непосредственно в папке `data` или её подпапках.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла, для которого нужно найти точку монтирования.

### Возвращаемое значение

Умный указатель класса [FileSystemMount](../../../api/library/filesystem/class.filesystemmount_cpp.md) при успехе; иначе **nullptr**.
## void getMounts ( Vector < Ptr < FileSystemMount >> & OUT_container ) const

Возвращает список всех [mount points](../../../principles/filesystem/index_cpp.md#mount_points), используемых файловой системой в данный момент, и помещает их в указанный выходной буфер.
> **Notice:** Этот список не будет включать [root mount](#getRootMount_FileSystemMount).


### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[FileSystemMount](../../../api/library/filesystem/class.filesystemmount_cpp.md)>> &* **OUT_container** - Выходной буфер для хранения списка всех используемых в данный момент [mount points](../../../api/library/filesystem/class.filesystemmount_cpp.md). > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Ptr < FileSystemMount > getRootMount ( ) const

Возвращает корневую точку монтирования файловой системы. Она монтирует папку `data` в корень виртуальной файловой системы. Корневая точка монтирования не может быть размонтирована.
### Возвращаемое значение

Умный указатель класса [FileSystemMount](../../../api/library/filesystem/class.filesystemmount_cpp.md) для корневой точки монтирования виртуальной файловой системы.
## Ptr < FileSystemMount > createMount ( const char * absolute_path , const char * virtual_path , int access , const Vector < String > & exclusive_filters = {} , const Vector < String > & ignore_filters = {} , const Vector < String > & guidsdb_ignore_filters = {} , bool save_file = true )

Добавляет новую [mount point](../../../principles/filesystem/index_cpp.md#mount_points) для указанной внешней папки/пакета, виртуального пути и режима доступа. Все смонтированные файлы автоматически добавляются как известные в виртуальную файловую систему.
### Аргументы

- *const char ** **absolute_path** - Абсолютный путь к монтируемой папке/пакету.
- *const char ** **virtual_path** - [Virtual path](../../../principles/filesystem/index_cpp.md#virtual_paths) к папке, в которую монтируется содержимое внешней папки/пакета.
- *int* **access** - Режим доступа точки монтирования, одно из значений *[FileSystemMount::ACCESS_*](../../../api/library/filesystem/class.filesystemmount_cpp.md#ACCESS_READONLY)*.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **exclusive_filters** - Список масок (например, *"*.jpg", "some_folder_*/", "dir*/*1*.world", "editor_[1-9]*.log"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)), используемых для фильтрации файлов в монтируемой папке/пакете.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **ignore_filters** - Список масок (например, *"*.tmp", "cache_*/", "dir*/*1*.world", "editor_[1-9]*.log"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)), используемых для исключения игнорируемых файлов в монтируемой папке/пакете.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **guidsdb_ignore_filters** - Список масок (например, *"*.tmp", "cache_*/", "dir*/*1*.world", "editor_[1-9]*.log"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)), используемых для исключения файлов или каталогов из базы данных GUID.
- *bool* **save_file** - Флаг, указывающий, следует ли записывать файл `.umount` на диск.

### Возвращаемое значение

Умный указатель класса [FileSystemMount](../../../api/library/filesystem/class.filesystemmount_cpp.md), если он был успешно создан; иначе **nullptr**.
## Ptr < FileSystemMount > addMount ( const char * umount_path )

 Добавляет новую [mount point](../../../principles/filesystem/index_cpp.md#mount_points), используя данные из указанного файла `*.umount`. Все смонтированные файлы автоматически добавляются как известные в виртуальную файловую систему.
### Аргументы

- *const char ** **umount_path** - Абсолютный путь к файлу `*.umount`.

### Возвращаемое значение

Умный указатель класса [FileSystemMount](../../../api/library/filesystem/class.filesystemmount_cpp.md), если он был успешно создан; иначе **nullptr**.
## bool saveMountFile ( const char * umount_path ) const

Сохраняет указанный файл `*.umount`.
### Аргументы

- *const char ** **umount_path** - Путь к файлу [mount point](../../../principles/filesystem/index_cpp.md#mount_points).

### Возвращаемое значение

true, если указанный файл `*.umount` успешно сохранён; иначе false.
## bool removeMount ( const char * path )

 Размонтирует [mount point](../../../principles/filesystem/index_cpp.md#mount_points) с заданным путём.
> **Notice:** [root mount](#getRootMount_FileSystemMount) не может быть удалена.


### Аргументы

- *const char ** **path** - Абсолютный путь к монтируемой папке/пакету.

### Возвращаемое значение

true, если точка монтирования с заданным путём успешно размонтирована; иначе false.
## void clearMounts ( )

 Размонтирует все [mount point](../../../principles/filesystem/index_cpp.md#mount_points).
> **Notice:** Этот метод не удаляет [root mount](#getRootMount_FileSystemMount).


## bool loadPackage ( const char * path )

 Загружает пакет UNG или ZIP в файловую систему. Обратите внимание, что пакет должен быть [mounted](../../../principles/filesystem/index_cpp.md#mount_points), иначе он не будет загружен.
> **Notice:** Пакеты UNG без защиты паролем могут быть загружены, даже если в движке встроен пароль для пакетов файловой системы. Например, можно загрузить как пакет `core.ung` без пароля, так и пакет `my_assets.ung`, защищённый паролем.


### Аргументы

- *const char ** **path** - Путь к пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

**true**, если пакет загружен; иначе **false**.
## bool loadPackage ( const char * path , const char * extension )

 Загружает пакет с указанным расширением (ung, zip или pak) в файловую систему. Обратите внимание, что пакет должен быть [mounted](../../../principles/filesystem/index_cpp.md#mount_points), иначе он не будет загружен.
> **Notice:** Пакеты UNG без защиты паролем могут быть загружены, даже если в движке встроен пароль для пакетов файловой системы. Например, можно загрузить как пакет `core.ung` без пароля, так и пакет `my_assets.ung`, защищённый паролем.


### Аргументы

- *const char ** **path** - Путь к пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).
- *const char ** **extension** - Расширение пользовательского пакета, одно из следующих значений:

  - ung
  - zip
  - pak

### Возвращаемое значение

**true**, если пакет загружен; иначе **false**.
## bool removePackage ( const char * path )

Выгружает пакет UNG или ZIP из файловой системы.
### Аргументы

- *const char ** **path** - Путь к пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

true, если пакет удалён; иначе false.
## void getSupportedPackagesExtensions ( Vector < String > & OUT_extensions ) const

Возвращает список зарегистрированных расширений, которые можно загрузить как пакет.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_extensions** - Массив для хранения зарегистрированных расширений. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void getPackageVirtualFiles ( const char * path , Vector < String > & OUT_files ) const

Сохраняет список имён всех виртуальных файлов, хранящихся в указанном пакете, в указанный строковый буфер.
### Аргументы

- *const char ** **path** - Путь к пользовательскому пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_files** - Строковый буфер для хранения списка имён всех виртуальных файлов, хранящихся в указанном пакете. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void getPackageVirtualFiles ( const char * path , const char * extension , Vector < String > & OUT_files ) const

Сохраняет список имён всех виртуальных файлов, хранящихся в пакете с указанным именем и расширением, в указанный строковый буфер.
### Аргументы

- *const char ** **path** - Путь к пользовательскому пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).
- *const char ** **extension** - Расширение пользовательского пакета, одно из следующих значений:

  - ung
  - zip
  - pak
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_files** - Строковый буфер для хранения списка имён всех виртуальных файлов, хранящихся в указанном пакете. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void preloadExternPackage ( Package * package )

Загружает пользовательский пакет до инициализации файловой системы. Метод должен быть вызван до инициализации движка.
```cpp
// предзагружаем пакет
FileSystem::preloadExternPackage(new MyPackage());
// инициализируем движок
EnginePtr engine(argc, argv);

```


### Аргументы

- *[Package](../../../api/library/filesystem/class.package_cpp.md) ** **package** - Экземпляр пользовательского пакета.

## void preloadExternPackage ( const char * virtual_path , Package * package )

Загружает пользовательский пакет до инициализации файловой системы и задаёт для него виртуальный путь. Метод должен быть вызван до инициализации движка.
### Аргументы

- *const char ** **virtual_path** - Виртуальный путь к пользовательскому пакету.
- *[Package](../../../api/library/filesystem/class.package_cpp.md) ** **package** - Экземпляр пользовательского пакета.

## void clearPreloadedExternPackages ( )

Очищает все [preloaded](#preloadExternPackage_Package_void) пользовательские пакеты (пакеты, загруженные до инициализации файловой системы).
## bool addExternPackage ( Package * package )

Добавляет пользовательский пакет в виртуальную файловую систему.
### Аргументы

- *[Package](../../../api/library/filesystem/class.package_cpp.md) ** **package** - Экземпляр пользовательского пакета.

### Возвращаемое значение

true, если пакет успешно добавлен; иначе false.
## bool addExternPackage ( const char * path , Package * package )

Добавляет пользовательский пакет в виртуальную файловую систему и назначает ему виртуальный путь. Виртуальный путь получается из указанного пути.
### Аргументы

- *const char ** **path** - Путь к пользовательскому пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).
- *[Package](../../../api/library/filesystem/class.package_cpp.md) ** **package** - Экземпляр пользовательского пакета.

### Возвращаемое значение

true, если пакет успешно добавлен; иначе false.
## void getVirtualFiles ( Vector < String > & OUT_files ) const

Сохраняет список имён всех известных файлов, зарегистрированных в файловой системе, в указанный строковый буфер.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_files** - Строковый буфер для хранения списка имён всех известных виртуальных файлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void getVirtualFiles ( Vector < UGUID > & OUT_files ) const

Сохраняет список [GUID](../../../api/library/filesystem/class.uguid_cpp.md) всех известных файлов, зарегистрированных в файловой системе, в указанный строковый буфер.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[UGUID](../../../api/library/filesystem/class.uguid_cpp.md)> &* **OUT_files** - Строковый буфер для хранения списка GUID всех известных виртуальных файлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## bool isVirtualFile ( const char * path ) const

Проверяет, известен ли указанный файл виртуальной файловой системе.
### Аргументы

- *const char ** **path** - Путь к файлу. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

true, если файл известен виртуальной файловой системе; иначе false.
## bool isVirtualFile ( const UGUID & guid ) const

Проверяет, известен ли файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) виртуальной файловой системе и зарегистрирован ли для него виртуальный путь.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл известен виртуальной файловой системе; иначе false.
## bool addVirtualFile ( const char * path , const UGUID & guid , bool must_exist = false )

Регистрирует обычное имя файла как известный виртуальный файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) и добавляет его в карту, используемую для быстрого поиска. Этот метод следует использовать, когда нужно добавить, например, новый контент в проект.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.
- *bool* **must_exist** - Флаг, указывающий, должен ли указанный файл [exist](#isFileExist_cstr_bool).

### Возвращаемое значение

true, если имя файла успешно добавлено; иначе false.
## UGUID addVirtualFile ( const char * path , bool must_exist = false )

Регистрирует обычное имя файла как известный виртуальный файл и добавляет его в карту, используемую для быстрого поиска. Этот метод следует использовать, когда нужно добавить, например, новый контент в проект.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.
- *bool* **must_exist** - Флаг, указывающий, должен ли указанный файл [exist](#isFileExist_cstr_bool).

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла, если он успешно зарегистрирован, иначе пустой GUID.
## bool renameVirtualFile ( const char * path , const char * new_path )

Переименовывает указанный известный виртуальный файл.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.
- *const char ** **new_path** - Новый путь для файла.

### Возвращаемое значение

true, если файл успешно переименован; иначе false.
## bool renameVirtualFile ( const char * path , const char * new_path , const UGUID & new_guid )

Переименовывает указанный известный файл и присваивает ему указанный новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.
- *const char ** **new_path** - Новый путь для файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_guid** - Новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для файла.

### Возвращаемое значение

true, если файл успешно переименован; иначе false.
## bool renameVirtualFile ( const UGUID & guid , const char * new_path )

Переименовывает известный виртуальный файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.
- *const char ** **new_path** - Новый путь для файла.

### Возвращаемое значение

true, если файл успешно переименован; иначе false.
## bool renameVirtualFile ( const UGUID & guid , const char * new_path , const UGUID & new_guid )

Переименовывает известный виртуальный файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) и присваивает ему указанный новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.
- *const char ** **new_path** - Новый путь для файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_guid** - Новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для файла.

### Возвращаемое значение

true, если файл успешно переименован; иначе false.
## bool removeVirtualFile ( const char * path )

Удаляет виртуальный файл с указанным именем.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл успешно удалён; иначе false.
## bool removeVirtualFile ( const UGUID & guid )

Удаляет виртуальный файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) удаляемого известного виртуального файла.

### Возвращаемое значение

true, если файл успешно удалён; иначе false.
## bool changeVirtualFile ( const char * path )

Помечает виртуальный файл с указанным именем как изменённый. При этом отправляется соответствующий сигнал *CALLBACK_FILE_CHANGED*. Этот метод используется для уведомления движка о том, что ресурс был изменён и требует обновления.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл успешно помечен как изменённый; иначе false.
## bool changeVirtualFile ( const UGUID & guid )

Помечает виртуальный файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) как изменённый. При этом отправляется соответствующий сигнал *CALLBACK_FILE_CHANGED*. Этот метод используется для уведомления движка о том, что ресурс был изменён и требует обновления.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) удаляемого известного виртуального файла.

### Возвращаемое значение

true, если файл успешно помечен как изменённый; иначе false.
## void removeNonExistingVirtualFiles ( )

Удаляет все несуществующие виртуальные файлы из файловой системы. Эти файлы физически не существуют на диске, однако добавлены в виртуальную файловую систему. Например, это может быть blob или файл кэша.
## bool isBlobFile ( const char * path ) const

Проверяет, [loaded](#addBlobFile_cstr_bool) ли указанный файл в blob.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл успешно загружен в blob; иначе false.
## bool isBlobFile ( const UGUID & guid ) const

Проверяет, [loaded](#addBlobFile_UGUID_bool) ли файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) в blob.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл успешно загружен в blob; иначе false.
## bool addBlobFile ( const char * path )

Добавляет файл в blob. Может использоваться для файлов, часто изменяемых во время выполнения (например, изображений). После загрузки такого файла с диска и записи в blob в памяти его изменения можно быстро сохранять в этот blob.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл успешно добавлен в blob; иначе false.
## bool addBlobFile ( const UGUID & guid )

Добавляет файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) в blob. Может использоваться для файлов, часто изменяемых во время выполнения (например, изображений). После загрузки такого файла с диска и записи в blob в памяти его изменения можно быстро сохранять в этот blob.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл успешно добавлен в blob; иначе false.
## bool removeBlobFile ( const char * path )

Удаляет файл из blob. Blob-хранение может использоваться для файлов, часто изменяемых во время выполнения (например, изображений). После загрузки такого файла с диска и записи в blob в памяти его изменения можно быстро сохранять в этот blob.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл успешно удалён; иначе false.
## bool removeBlobFile ( const UGUID & guid )

Удаляет файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) из blob. Blob-хранение может использоваться для файлов, часто изменяемых во время выполнения (например, изображений). После загрузки такого файла с диска и записи в blob в памяти его изменения можно быстро сохранять в этот blob.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл успешно удалён; иначе false.
## bool isCacheFile ( const char * path ) const

Проверяет, загружен ли указанный файл в кэш.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл добавлен в кэш; иначе false.
## bool isCacheFile ( const UGUID & guid ) const

Проверяет, загружен ли файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) в кэш.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл добавлен в кэш; иначе false.
## bool addCacheFile ( const char * path )

Кэширует файл в памяти. Может использоваться для файлов, к которым обращаются многократно во время выполнения (например, текстуры читаются подряд два раза). Такие файлы загружаются в память для более быстрого чтения.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл успешно добавлен в кэш; иначе false.
## bool addCacheFile ( const UGUID & guid )

Кэширует файл в памяти с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md). Может использоваться для файлов, к которым обращаются многократно во время выполнения (например, текстуры читаются подряд два раза). Такие файлы загружаются в память для более быстрого чтения.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл успешно добавлен в кэш; иначе false.
## bool removeCacheFile ( const char * path )

Удаляет кэшированный файл из памяти. Кэширование может использоваться для файлов, к которым обращаются многократно во время выполнения (например, текстуры читаются подряд два раза). Такие файлы загружаются в память для более быстрого чтения.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл успешно удалён из кэша; иначе false.
## bool removeCacheFile ( const UGUID & guid )

Удаляет кэшированный файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) из памяти. Кэширование может использоваться для файлов, к которым обращаются многократно во время выполнения (например, текстуры читаются подряд два раза). Такие файлы загружаются в память для более быстрого чтения.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл успешно удалён из кэша; иначе false.
## bool isDiskFile ( const char * path ) const

Возвращает значение, указывающее, является ли указанный путь к файлу путём к файлу на диске (т.е. не пакет, не blob и не файл кэша).
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если указанный путь к файлу является путём к файлу на диске; иначе false.
## bool isDiskFile ( const UGUID & guid ) const

Возвращает значение, указывающее, является ли файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файлом на диске.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл с указанным GUID является файлом на диске; иначе false.
## bool isPackageFile ( const char * path ) const

Возвращает значение, указывающее, является ли указанный путь к файлу путём к файлу внутри пакета ZIP или UNG.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

true, если указанный путь к файлу является путём к файлу внутри пакета ZIP или UNG; иначе false.
## bool isPackageFile ( const UGUID & guid ) const

Возвращает значение, указывающее, является ли файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файлом внутри пакета ZIP или UNG.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл с указанным GUID является файлом внутри пакета ZIP или UNG; иначе false.
## String resolvePartialVirtualPath ( const char * path ) const

Преобразует указанный [partial path](../../../principles/filesystem/index_cpp.md#partial) в полный виртуальный путь.
> **Notice:** Если файл не добавлен в виртуальную файловую систему, полный виртуальный путь не будет возвращён.

 Например, если у вас есть `data/project/image_1.tga` и вы хотите использовать частичный виртуальный путь `image_1.tga`, сначала нужно получить полный виртуальный путь:
```cpp
// преобразуем частичный виртуальный путь в полный виртуальный путь
String full_virtual_path = FileSystem::resolvePartialVirtualPath("image_1.tga"); // возвращается project/image_1.tga
// используем преобразованный путь
Image::create(full_virtual_path);

```


### Аргументы

- *const char ** **path** - Частичный путь для разрешения.

### Возвращаемое значение

Полный виртуальный путь.
## String getVirtualPath ( const char * path ) const

Разрешает виртуальный путь для указанного пути к файлу. Следующие примеры показывают частные случаи использования метода:
- Если указанный путь известен виртуальной файловой системе, может быть возвращено следующее: ```cpp String s1, s2, s3, s4; // абсолютный путь к папке s1 = FileSystem::getVirtualPath("D:/Unigine/data");			// пустая строка s2 = FileSystem::getVirtualPath("D:/Unigine/data/");		// пустая строка // путь к ассетам в папке s3 = FileSystem::getVirtualPath("asset://D:/Unigine/data");	// пустая строка s4 = FileSystem::getVirtualPath("asset://D:/Unigine/data/");// пустая строка ``` Во всех случаях возвращается пустая строка: виртуальный путь всегда возвращается относительно каталога data, а в примере указан сам каталог data. Если указать известный файл внутри него, будет возвращён соответствующий виртуальный путь: ```cpp String s = FileSystem::getVirtualPath("D:/Unigine/data/1.tga");		// "1.tga" ```
- Если указанный путь неизвестен виртуальной файловой системе, может быть возвращено следующее: ```cpp // абсолютный путь к папке s1 = FileSystem::getVirtualPath("C:/temp");			// "C:/temp" s2 = FileSystem::getVirtualPath("C:/temp/");		// "C:/temp" // путь к ассетам в папке s3 = FileSystem::getVirtualPath("asset://C:/temp");	// "C:/temp" s4 = FileSystem::getVirtualPath("asset://C:/temp/");// "C:/temp" ``` Во всех случаях возвращается нормализованный путь к папке, так как указанная папка неизвестна виртуальной файловой системе, и, следовательно, виртуальный путь вернуть невозможно. То же самое для файлов, например: ```cpp s = FileSystem::getVirtualPath("C:/temp/1.tga");			// "C:/temp/1.tga" ```
- Если указанный путь — это путь к [mounted](../../../principles/filesystem/index_cpp.md#mount_points) файлу. Здесь `mount_1` — это точка монтирования `mount_1.umount`. Обратите внимание, что в примере ниже ассет `1.tga` не имеет runtime-файлов. Если у ассета есть runtime-файл, будет возвращён виртуальный путь к этому runtime-файлу (хранящемуся в папке `.runtimes` точки монтирования). ```cpp // virtual path to the file specified as an absolute one s1 = FileSystem::getVirtualPath("D:/Unigine/data/mounts/mount_1/1.tga");// "mounts/mount_1/1.tga" // absolute path to the file s2 = FileSystem::getVirtualPath("D:/extern_content/1.tga");				// "mounts/mount_1/1.tga" // full virtual path to the file s3 = FileSystem::getVirtualPath("mounts/mount_1/1.tga");				// "mounts/mount_1/1.tga" ```
- Если указанный путь — это путь к [mounted](../../../principles/filesystem/index_cpp.md#mount_points) файлу, хранящемуся во вложенных точках монтирования. Здесь `mount_1` и `mount_2` — это точки монтирования `mount_1.umount` и `mount_2.umount` соответственно. Обратите внимание, что в примере ниже ассет `1.tga` не имеет runtime-файлов. Если у ассета есть runtime-файл, будет возвращён виртуальный путь к этому runtime-файлу (хранящемуся в папке `.runtimes` точки монтирования). ```cpp // virtual path to the file specified as an absolute one s1 = FileSystem::getVirtualPath("D:/Unigine/data/mounts/mount_1/mount_2/1.tga");	// "mounts/mount_1/mount_2/1.tga" // absolute path to the file s2 = FileSystem::getVirtualPath("D:/extern_content_2/1.tga");						// "mounts/mount_1/mount_2/1.tga" // full virtual path to the file s3 = FileSystem::getVirtualPath("mounts/mount_1/mount_2/1.tga");					// "mounts/mount_1/mount_2/1.tga" ```


### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths), including a path to a folder. > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

Виртуальный путь к файлу относительно папки `data`.
## String getVirtualPath ( const UGUID & guid ) const

Разрешает виртуальный путь для указанного [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

Виртуальный путь к файлу относительно папки `data`.
## String getAbsolutePath ( const char * path ) const

Разрешает абсолютный путь для указанного пути к файлу. Следующие примеры показывают частные случаи использования метода:
- Если указанный путь известен виртуальной файловой системе, может быть возвращено следующее: ```cpp String s1, s2, s3, s4; // абсолютный путь к папке s1 = FileSystem::getAbsolutePath("D:/Unigine/data");			// "D:/Unigine/data" s2 = FileSystem::getAbsolutePath("D:/Unigine/data/");			// "D:/Unigine/data" // абсолютный путь к ассетам в папке s3 = FileSystem::getAbsolutePath("asset://D:/Unigine/data");	// "D:/Unigine/data" s4 = FileSystem::getAbsolutePath("asset://D:/Unigine/data/");	// "D:/Unigine/data" ```
- Если указанный путь неизвестен виртуальной файловой системе, может быть возвращено следующее: ```cpp // абсолютный путь к папке s1 = FileSystem::getAbsolutePath("C:/temp");				// "C:/temp" s2 = FileSystem::getAbsolutePath("C:/temp/");				// "C:/temp" // абсолютный путь к ассетам в папке s3 = FileSystem::getAbsolutePath("asset://C:/temp");		// "C:/temp" s4 = FileSystem::getAbsolutePath("asset://C:/temp/");		// "C:/temp" ```
- Если указанный путь — это путь к [mounted](../../../principles/filesystem/index_cpp.md#mount_points) файлу. Здесь `mount_1` — это точка монтирования `mount_1.umount`. Обратите внимание, что в примере ниже ассет `1.tga` не имеет runtime-файлов. Если у ассета есть runtime-файл, будет возвращён абсолютный путь к этому runtime-файлу (хранящемуся в папке `.runtimes` точки монтирования). ```cpp // virtual path specified as an absolute one s1 = FileSystem::getAbsolutePath("D:/Unigine/data/mounts/mount_1/1.tga");		// "D:/extern_content/1.tga" // absolute path s2 = FileSystem::getAbsolutePath("D:/extern_content/1.tga");					// "D:/extern_content/1.tga" // virtual path s3 = FileSystem::getAbsolutePath("mounts/mount_1/1.tga");						// "D:/extern_content/1.tga" ```
- Если указанный путь — это путь к [mounted](../../../principles/filesystem/index_cpp.md#mount_points) файлу, хранящемуся во вложенных точках монтирования. Здесь `mount_1` и `mount_2` — это точки монтирования `mount_1.umount` и `mount_2.umount` соответственно. Обратите внимание, что в примере ниже ассет `1.tga` не имеет runtime-файлов. Если у ассета есть runtime-файл, будет возвращён абсолютный путь к этому runtime-файлу (хранящемуся в папке `.runtimes` точки монтирования). ```cpp // virtual path specified as an absolute one s1 = FileSystem::getAbsolutePath("D:/UnigineGIT/data/mounts/mount_1/mount_2/1.tga");// "D:/extern_content_2/1.tga" // absolute path s2 = FileSystem::getAbsolutePath("D:/extern_content_2/1.tga");						// "D:/extern_content_2/1.tga" // virtual path s3 = FileSystem::getAbsolutePath("mounts/mount_1/mount_2/1.tga");					// "D:/extern_content_2/1.tga" ```
- Если указанный путь — это сетевой путь: ```cpp s1 = FileSystem::getAbsolutePath("//studio/work/shared_content/images.zip");			// "//studio/work/shared_content/images.zip" s2 = FileSystem::getAbsolutePath("\\\\studio\\work\\shared_content\\images.zip");		// "//studio/work/shared_content/images.zip" ```


### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths), including a path to a folder. > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

Абсолютный путь к файлу.
## String getAbsolutePath ( const UGUID & guid ) const


Разрешает абсолютный путь для указанного [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

Абсолютный путь к файлу.
## String getPackageVirtualPath ( const char * path ) const

Разрешает виртуальный путь для указанного пути к пакету.
### Аргументы

- *const char ** **path** - Путь к пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

Виртуальный путь к пакету.
## String getPackageVirtualPath ( const UGUID & guid ) const

Разрешает виртуальный путь для указанного [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) пакета.

### Возвращаемое значение

Виртуальный путь к пакету.
## String getPackageAbsolutePath ( const char * path ) const

Разрешает абсолютный путь для указанного пути к пакету.
### Аргументы

- *const char ** **path** - Путь к пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

Абсолютный путь к пакету.
## String getPackageAbsolutePath ( const UGUID & guid ) const


Разрешает абсолютный путь для указанного [GUID](../../../api/library/filesystem/class.uguid_cpp.md) пакета.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) пакета.

### Возвращаемое значение

Абсолютный путь к пакету.
## String getExtension ( const char * path ) const

Возвращает расширение для указанного файла.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

Расширение файла в нижнем регистре, если оно есть; иначе пустая строка.
## String getExtension ( const UGUID & guid ) const

Возвращает расширение для файла с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID файла, для которого нужно вернуть расширение.

### Возвращаемое значение

Расширение файла в нижнем регистре, если оно есть; иначе пустая строка.
## bool isFileExist ( const char * path ) const

Проверяет, существует ли указанный файл фактически на диске.
> **Notice:** Вызов этого метода каждый кадр в главном потоке, особенно для нескольких файлов, может привести к снижению производительности. Лучше оптимизировать такие проверки и перенести их в отдельный поток.


### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

true, если файл существует; иначе false.
## bool isFileExist ( const UGUID & guid ) const

Проверяет, существует ли фактически файл с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
> **Notice:** Вызов этого метода каждый кадр в главном потоке, особенно для нескольких файлов, может привести к снижению производительности. Лучше оптимизировать такие проверки и перенести их в отдельный поток.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл существует; иначе false.
## bool isGUIDPath ( const char * path ) const

Возвращает значение, указывающее, имеет ли указанный путь корректный формат GUID-пути (например, "guid://e231e15beff2309b8f87c30b2c105cc4d2399973)".
### Аргументы

- *const char ** **path** - Путь для проверки.

### Возвращаемое значение

true, если указанный путь имеет корректный формат GUID-пути; иначе false.
## bool isAssetPath ( const char * path ) const

Возвращает значение, указывающее, имеет ли указанный путь корректный [asset path format](../../../principles/filesystem/index_cpp.md#access_path) (например, `asset://1.tga`).
### Аргументы

- *const char ** **path** - Путь для проверки.

### Возвращаемое значение

true, если указанный путь имеет корректный формат пути ассета; иначе false.
## long long getMTime ( const char * path ) const

Возвращает время последнего изменения указанного файла.
> **Notice:** Вызов этого метода каждый кадр в главном потоке, особенно для нескольких файлов, может привести к снижению производительности. Лучше оптимизировать такие проверки и перенести их в отдельный поток.


### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

Время последнего изменения файла. Если такого файла нет, будет возвращено **-1**.
## long long getMTime ( const UGUID & guid ) const

Возвращает время последнего изменения файла с указанным GUID.
> **Notice:** Вызов этого метода каждый кадр в главном потоке, особенно для нескольких файлов, может привести к снижению производительности. Лучше оптимизировать такие проверки и перенести их в отдельный поток.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

Время последнего изменения файла. Если такого файла нет, будет возвращено **-1**.
## bool loadGUIDs ( const char * path )

Загружает [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файловой системы из указанного файла.
### Аргументы

- *const char ** **path** - Путь к файлу, в котором хранятся GUID файловой системы.

### Возвращаемое значение

true, если GUID файловой системы успешно загружены; иначе false.
## bool saveGUIDs ( const char * path , bool binary = false ) const

Сохраняет все [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файловой системы в указанный файл в указанном формате (json или binary).
### Аргументы

- *const char ** **path** - Путь к файлу, в который будут сохранены GUID файловой системы.
- *bool* **binary** - Флаг бинарного формата файла. Если флаг установлен в true, файловая система сохранит GUID в бинарный файл; иначе — в JSON-файл.

### Возвращаемое значение

true, если все GUID файловой системы успешно сохранены; иначе false.
## UGUID generateGUID ( ) const

Генерирует новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Возвращаемое значение

Новый GUID файловой системы, если он был успешно сгенерирован; иначе пустой GUID.
## bool setGUID ( const char * path , const UGUID & guid )

Устанавливает указанный [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для указанного файла.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), который нужно установить для файла.

### Возвращаемое значение

true, если [GUID](../../../api/library/filesystem/class.uguid_cpp.md) успешно установлен; иначе false.
## UGUID getGUID ( const char * path ) const

Возвращает [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для указанного пути, если этот путь зарегистрирован в файловой системе.
> **Notice:** Если вы передаёте строку guid *(guid://)*, этот метод вернёт указанный вами guid (**без проверки, зарегистрирован ли он в файловой системе**).

### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла, под которым указанный путь зарегистрирован в файловой системе; иначе [empty GUID](../../../api/library/filesystem/class.uguid_cpp.md#empty).
## long long getFileSize ( const char * path ) const

Возвращает размер указанного файла.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (asset://). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

Размер файла в байтах.
## long long getFileSize ( const UGUID & guid ) const

Возвращает размер файла с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла

### Возвращаемое значение

Размер файла в байтах.
## String getModifier ( int num ) const

Возвращает имя указанного модификатора.
### Аргументы

- *int* **num** - ID-номер модификатора.

### Возвращаемое значение

Имя модификатора.
## void addModifier ( const char * name )

Регистрирует новый модификатор в файловой системе.
### Аргументы

- *const char ** **name** - Имя модификатора.

## void removeModifier ( const char * name )

Отменяет регистрацию указанного модификатора в файловой системе.
### Аргументы

- *const char ** **name** - Имя модификатора.

## void clearModifiers ( )

Отменяет регистрацию всех модификаторов в файловой системе.
## String guidToPath ( const UGUID & guid ) const

Возвращает путь к файлу с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла

### Возвращаемое значение

Путь к файлу. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).
## UGUID pathToGuid ( const char * path )

Возвращает GUID файла, для которого указан путь.
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths). > **Notice:** Если вы хотите указать путь к ассету, используйте формат пути ассета (`asset://`). Иначе, если вы укажете обычный путь к ассету, он будет рассматриваться как путь к его runtime-файлу (если есть) из папки `.runtimes`.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.
## bool isExternalFile ( const char * path ) const

Проверяет, ссылается ли указанный путь к файлу на внешний файл (расположенный вне `data`).
### Аргументы

- *const char ** **path** - File path. It can be a relative, absolute, network, or virtual [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

true, если файл является внешним; иначе false.
## bool isExternalFile ( const UGUID & guid ) const

Проверяет, ссылается ли указанный GUID пути к файлу на внешний файл (расположенный вне `data`).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла

### Возвращаемое значение

true, если файл является внешним; иначе false.
## bool isPackageLoaded ( const char * path )

Возвращает значение, указывающее, загружен ли указанный пакет в файловую систему.
### Аргументы

- *const char ** **path** - Путь к пакету. Это может быть относительный, абсолютный, сетевой или виртуальный [path](../../../principles/filesystem/index_cpp.md#paths).

### Возвращаемое значение

true, если пакет загружен; иначе false.
## void getPackagesVirtualPaths ( Vector < String > & OUT_packages_virtual_paths ) const

Возвращает виртуальные пути всех пакетов, загруженных в данный момент в файловую систему.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_packages_virtual_paths** - Массив для хранения виртуальных путей всех загруженных пакетов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
