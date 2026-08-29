# Unigine.LandscapeMapFileCompression Class (CPP)

**Header:** #include <UnigineObjects.h>


Класс Landscape Map File Compression используется для сжатия и распаковки данных файла `.lmap` с помощью Zlib, LZ4 или собственного алгоритма сжатия Unigine. Последний обеспечивает лучшие результаты сжатия для 2D- и 3D-текстур по сравнению с LZ4 и Zlib без потери качества.


## LandscapeMapFileCompression Class

### Методы класса

## bool isCompressing () const

Возвращает текущее значение, указывающее, выполняется ли сжатие.
### Возвращаемое значение

**true**, если сжатие выполняется; иначе **false**.
## bool isDecompressing () const

Возвращает текущее значение, указывающее, выполняется ли распаковка.
### Возвращаемое значение

**true**, если распаковка выполняется; иначе **false**.
## int getProgress () const

Возвращает текущий прогресс сжатия файла карты landscape.
### Возвращаемое значение

Текущий прогресс сжатия файла карты landscape (в процентах).
## void setHeightCompressor ( Landscape::COMPRESSOR_TYPE compressor )

Задаёт новый тип компрессора, используемый для сжатия данных высот.
### Аргументы

- *[Landscape::COMPRESSOR_TYPE](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#COMPRESSOR_TYPE)* **compressor** - Метод сжатия, используемый для карты слоя.

## Landscape::COMPRESSOR_TYPE getHeightCompressor () const

Возвращает текущий тип компрессора, используемого для сжатия данных высот.
### Возвращаемое значение

Текущий метод сжатия, используемый для карты слоя.
## void setAlbedoCompressor ( Landscape::COMPRESSOR_TYPE compressor )

Задаёт новый тип компрессора, используемый для сжатия данных альбедо.
### Аргументы

- *[Landscape::COMPRESSOR_TYPE](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#COMPRESSOR_TYPE)* **compressor** - Метод сжатия, используемый для карты слоя.

## Landscape::COMPRESSOR_TYPE getAlbedoCompressor () const

Возвращает текущий тип компрессора, используемого для сжатия данных альбедо.
### Возвращаемое значение

Текущий метод сжатия, используемый для карты слоя.
## void setOpacityHeightCompressor ( Landscape::COMPRESSOR_TYPE compressor )

Задаёт новый тип компрессора, используемый для сжатия данных непрозрачности высот.
### Аргументы

- *[Landscape::COMPRESSOR_TYPE](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#COMPRESSOR_TYPE)* **compressor** - Метод сжатия, используемый для карты слоя.

## Landscape::COMPRESSOR_TYPE getOpacityHeightCompressor () const

Возвращает текущий тип компрессора, используемого для сжатия данных непрозрачности высот.
### Возвращаемое значение

Текущий метод сжатия, используемый для карты слоя.
## void setEnabledAlbedoTextureCompression ( bool compression )

Задаёт новое значение, указывающее, включено ли сжатие текстуры альбедо.
### Аргументы

- *bool* **compression** - Установите **true**, чтобы включить сжатие текстуры альбедо; **false** — чтобы отключить.

## bool isEnabledAlbedoTextureCompression () const

Возвращает текущее значение, указывающее, включено ли сжатие текстуры альбедо.
### Возвращаемое значение

**true**, если сжатие текстуры альбедо включено; иначе **false**.
## void setEnabledHeightTextureCompression ( bool compression )

Задаёт новое значение, указывающее, включено ли сжатие текстуры высот.
### Аргументы

- *bool* **compression** - Установите **true**, чтобы включить сжатие текстуры высот; **false** — чтобы отключить.

## bool isEnabledHeightTextureCompression () const

Возвращает текущее значение, указывающее, включено ли сжатие текстуры высот.
### Возвращаемое значение

**true**, если сжатие текстуры высот включено; иначе **false**.
## void setEnabledOpacityHeightTextureCompression ( bool compression )

Задаёт новое значение, указывающее, включено ли сжатие текстуры непрозрачности высот.
### Аргументы

- *bool* **compression** - Установите **true**, чтобы включить сжатие текстуры непрозрачности высот; **false** — чтобы отключить.

## bool isEnabledOpacityHeightTextureCompression () const

Возвращает текущее значение, указывающее, включено ли сжатие текстуры непрозрачности высот.
### Возвращаемое значение

**true**, если сжатие текстуры непрозрачности высот включено; иначе **false**.
## UGUID getGUID () const

Возвращает текущий [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла `.lmap`, содержащего данные карты landscape.
### Возвращаемое значение

Текущий [GUID](../../../../api/library/filesystem/class.uguid_cpp.md) файла `.lmap`, содержащего данные карты landscape.
## void setCacheDirectory ( const char * directory )

Задаёт новый путь к каталогу, используемому для хранения кэша. По умолчанию кэш находится там же, где и кэш UnigineEditor (его можно найти на вкладке *Settings* UnigineEditor). Если памяти недостаточно, можно использовать другой диск. Полная копия текущего террейна будет временно храниться в каталоге кэша, поэтому это следует учитывать при оценке размера кэша. Для быстрого копирования данных рекомендуется SSD.
### Аргументы

- *const char ** **directory** - Путь к каталогу, хранящему кэш.

## const char * getCacheDirectory () const

Возвращает текущий путь к каталогу, используемому для хранения кэша. По умолчанию кэш находится там же, где и кэш UnigineEditor (его можно найти на вкладке *Settings* UnigineEditor). Если памяти недостаточно, можно использовать другой диск. Полная копия текущего террейна будет временно храниться в каталоге кэша, поэтому это следует учитывать при оценке размера кэша. Для быстрого копирования данных рекомендуется SSD.
### Возвращаемое значение

Текущий путь к каталогу, хранящему кэш.
## Event<const Ptr < LandscapeMapFileCompression > &> getEventEnd () const

Событие, срабатывающее по завершении операции сжатия/распаковки файла карты landscape. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<LandscapeMapFileCompression> & **compression**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события End
void end_event_handler(const Ptr<LandscapeMapFileCompression> & compression)
{
	Log::message("\Обработка события End\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections end_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEnd().connect(end_event_connections, end_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEnd().connect(end_event_connections, [](const Ptr<LandscapeMapFileCompression> & compression) {
		Log::message("\Обработка события End (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
end_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection end_event_connection;

// подписываемся на событие End с функцией-обработчиком, сохраняя соединение
publisher->getEventEnd().connect(end_event_connection, end_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
end_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
end_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие End через соединение
end_event_connection.disconnect();

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

	// Обработчик события End, реализованный как член класса
	void event_handler(const Ptr<LandscapeMapFileCompression> & compression)
	{
		Log::message("\Обработка события End\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEnd().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId end_handler_id;

// подписываемся на событие End с лямбда-обработчиком, сохраняя идентификатор соединения
end_handler_id = publisher->getEventEnd().connect(e_connections, [](const Ptr<LandscapeMapFileCompression> & compression) {
		Log::message("\Обработка события End (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEnd().disconnect(end_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий End при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEnd().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEnd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < LandscapeMapFileCompression > &> getEventProgress () const

Событие, срабатывающее в процессе выполнения операции сжатия/распаковки файла карты landscape (сигнализирует об изменении прогресса). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<LandscapeMapFileCompression> & **compression**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Progress
void progress_event_handler(const Ptr<LandscapeMapFileCompression> & compression)
{
	Log::message("\Обработка события Progress\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections progress_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventProgress().connect(progress_event_connections, progress_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventProgress().connect(progress_event_connections, [](const Ptr<LandscapeMapFileCompression> & compression) {
		Log::message("\Обработка события Progress (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
progress_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection progress_event_connection;

// подписываемся на событие Progress с функцией-обработчиком, сохраняя соединение
publisher->getEventProgress().connect(progress_event_connection, progress_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
progress_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
progress_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Progress через соединение
progress_event_connection.disconnect();

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

	// Обработчик события Progress, реализованный как член класса
	void event_handler(const Ptr<LandscapeMapFileCompression> & compression)
	{
		Log::message("\Обработка события Progress\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventProgress().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId progress_handler_id;

// подписываемся на событие Progress с лямбда-обработчиком, сохраняя идентификатор соединения
progress_handler_id = publisher->getEventProgress().connect(e_connections, [](const Ptr<LandscapeMapFileCompression> & compression) {
		Log::message("\Обработка события Progress (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventProgress().disconnect(progress_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Progress при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventProgress().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventProgress().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < LandscapeMapFileCompression > &> getEventBegin () const

Событие, срабатывающее в начале операции сжатия/распаковки файла карты landscape. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<LandscapeMapFileCompression> & **compression**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Begin
void begin_event_handler(const Ptr<LandscapeMapFileCompression> & compression)
{
	Log::message("\Обработка события Begin\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections begin_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBegin().connect(begin_event_connections, begin_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBegin().connect(begin_event_connections, [](const Ptr<LandscapeMapFileCompression> & compression) {
		Log::message("\Обработка события Begin (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
begin_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection begin_event_connection;

// подписываемся на событие Begin с функцией-обработчиком, сохраняя соединение
publisher->getEventBegin().connect(begin_event_connection, begin_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
begin_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
begin_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Begin через соединение
begin_event_connection.disconnect();

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

	// Обработчик события Begin, реализованный как член класса
	void event_handler(const Ptr<LandscapeMapFileCompression> & compression)
	{
		Log::message("\Обработка события Begin\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBegin().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId begin_handler_id;

// подписываемся на событие Begin с лямбда-обработчиком, сохраняя идентификатор соединения
begin_handler_id = publisher->getEventBegin().connect(e_connections, [](const Ptr<LandscapeMapFileCompression> & compression) {
		Log::message("\Обработка события Begin (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBegin().disconnect(begin_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Begin при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBegin().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBegin().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## LandscapeMapFileCompression ( )

Конструктор.
## bool compress ( bool is_safe )

Запускает процесс сжатия файла карты landscape.
### Аргументы

- *bool* **is_safe** - true, чтобы движок автоматически вызывал методы *filesClose()/fileOpen()* при выполнении операций (перед изменением файла `.lmap` движок должен освободить файлы через *filesClose()*, а после изменения должен быть вызван *fileOpen()*), false — чтобы вызывать методы *filesClose()/fileOpen()* вручную. Класс Landscape имеет две перегрузки метода *filesClose()*: > **Notice:** При **is_safe = true** движок всегда будет вызывать *filesClose(reload_files)* с полной перезагрузкой данных.

  - [*filesClose()*](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#filesClose_void) — следует вызывать при перемещении файла `.lmap` (перезагрузка данных не выполняется, так как сам файл не изменялся — экономит время на перезагрузку данных)
  - [*filesClose(reload_files)*](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#filesClose_VECUGUID_void) — следует вызывать при удалении или изменении файла `.lmap`.

### Возвращаемое значение

true, если операция сжатия выполнена успешно; иначе false.
## bool decompress ( bool is_safe )

Запускает процесс распаковки файла карты landscape.
### Аргументы

- *bool* **is_safe** - true, чтобы движок автоматически вызывал методы *filesClose()/fileOpen()* при выполнении операций (перед изменением файла `.lmap` движок должен освободить файлы через *filesClose()*, а после изменения должен быть вызван *fileOpen()*), false — чтобы вызывать методы *filesClose()/fileOpen()* вручную. Класс Landscape имеет две перегрузки метода *filesClose()*: > **Notice:** При **is_safe = true** движок всегда будет вызывать *filesClose(reload_files)* с полной перезагрузкой данных.

  - [*filesClose()*](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#filesClose_void) — следует вызывать при перемещении файла `.lmap` (перезагрузка данных не выполняется, так как сам файл не изменялся — экономит время на перезагрузку данных)
  - [*filesClose(reload_files)*](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#filesClose_VECUGUID_void) — следует вызывать при удалении или изменении файла `.lmap`.

### Возвращаемое значение

true, если операция распаковки выполнена успешно; иначе false.
## void stop ( )

Останавливает процесс сжатия/распаковки файла карты landscape.
## void setMaskCompressor ( int mask , Landscape::COMPRESSOR_TYPE compressor_type )

Задаёт тип компрессора, используемого для указанной маски.
### Аргументы

- *int* **mask** - Номер маски.
- *[Landscape::COMPRESSOR_TYPE](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#COMPRESSOR_TYPE)* **compressor_type** - Тип компрессора:

  - 0 – None
  - 1 – Our Method
  - 2 – LZ4
  - 3 – Zlib

## void setMaskOpacityCompressor ( int mask , Landscape::COMPRESSOR_TYPE compressor_type )

Задаёт тип компрессора, используемого для данных непрозрачности указанной маски.
### Аргументы

- *int* **mask** - Номер маски.
- *[Landscape::COMPRESSOR_TYPE](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#COMPRESSOR_TYPE)* **compressor_type** - Тип компрессора:

  - 0 – None
  - 1 – Our Method
  - 2 – LZ4
  - 3 – Zlib

## void setCompressorAll ( Landscape::COMPRESSOR_TYPE compressor_type )

Задаёт тип компрессора, используемого для сжатия всех данных.
### Аргументы

- *[Landscape::COMPRESSOR_TYPE](../../../../api/library/objects/landscape_terrain/class.landscape_cpp.md#COMPRESSOR_TYPE)* **compressor_type** - Тип компрессора:

  - 0 – None
  - 1 – Our Method
  - 2 – LZ4
  - 3 – Zlib

## int getMaskCompressor ( int mask )

Возвращает текущий тип компрессора, используемого для указанной маски.
### Аргументы

- *int* **mask** - Номер маски.

### Возвращаемое значение

Тип компрессора:
- 0 – None
- 1 – Our Method
- 2 – LZ4
- 3 – Zlib


## int getMaskOpacityCompressor ( int mask )

Возвращает текущий тип компрессора, используемого для данных непрозрачности указанной маски.
### Аргументы

- *int* **mask** - Номер маски.

### Возвращаемое значение

Тип компрессора:
- 0 – None
- 1 – Our Method
- 2 – LZ4
- 3 – Zlib


## void setEnabledMaskTextureCompression ( int mask , bool enable )

Включает или отключает сжатие текстуры указанной маски.
### Аргументы

- *int* **mask** - Номер маски.
- *bool* **enable** - true, чтобы включить сжатие текстуры маски; иначе false.

## void setEnabledMaskOpacityTextureCompression ( int mask , bool enable )

Включает или отключает сжатие текстуры непрозрачности указанной маски.
### Аргументы

- *int* **mask** - Номер маски.
- *bool* **enable** - true, чтобы включить сжатие текстуры непрозрачности маски; иначе false.

## bool isEnabledMaskTextureCompression ( int mask )

Возвращает значение, указывающее, включено ли сжатие текстуры маски.
### Аргументы

- *int* **mask** - Номер маски.

### Возвращаемое значение

true, если сжатие текстуры маски включено; иначе false.
## bool isEnabledMaskOpacityTextureCompression ( int mask )

Возвращает значение, указывающее, включено ли сжатие текстуры непрозрачности маски.
### Аргументы

- *int* **mask** - Номер маски.

### Возвращаемое значение

true, если сжатие текстуры непрозрачности маски включено; иначе false.
