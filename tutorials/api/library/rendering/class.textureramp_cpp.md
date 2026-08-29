# Unigine.TextureRamp Class (CPP)

**Header:** #include <UnigineTextures.h>


Интерфейс для работы с текстурами-рампами (ramp textures). Этот класс позволяет пользователю хранить 2D-кривые в форме текстуры (преобразовывать векторы в растровые данные).


Текстуры-рампы можно использовать для вариации цвета в материале [particles_base](../../../content/materials/library/particles_base/index.md) систем частиц или в других пользовательских материалах.


![](texturecurve_editor.png)


Для текстуры-рампы можно задать до 4 каналов.


## TextureRamp Class

### Методы класса

## Ptr < Texture > getTexture () const

Возвращает текущую новую текстуру и обновляет хэши кривых, если требуется. Возвращает указатель на текстуру или null, если текстура не была создана.
### Возвращаемое значение

Текущая новая текстура.
## void setNumChannels ( int channels )

Задаёт новое количество каналов для текстуры.
### Аргументы

- *int* **channels** - Количество каналов текстуры.

## int getNumChannels () const

Возвращает текущее количество каналов текстуры.
### Возвращаемое значение

Текущее количество каналов текстуры.
## void setResolution ( int resolution )

Задаёт новое разрешение по ширине для текстуры.
### Аргументы

- *int* **resolution** - Разрешение текстуры по ширине.

## int getResolution () const

Возвращает текущее разрешение по ширине для текстуры.
### Возвращаемое значение

Текущее разрешение текстуры по ширине.
## void setFlags ( int flags )

Задаёт новые флаги текстуры.
### Аргументы

- *int* **flags** - Флаги текстуры.

## int getFlags () const

Возвращает текущие флаги текстуры.
### Возвращаемое значение

Текущие флаги текстуры.
## bool isDefaultAll () const

Возвращает текущее значение, указывающее, являются ли значения всех каналов кривых значениями по умолчанию, ранее заданными через [setDefaultCurve](#setDefaultCurve_int_Curve2d_void).
### Возвращаемое значение

**true**, если значения всех каналов кривых являются значениями по умолчанию, ранее заданными через [setDefaultCurve](#setDefaultCurve_int_Curve2d_void); иначе **false**.
## Event<> getEventChanged () const

событие, генерируемое при изменении текстуры-рампы. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Changed
void changed_event_handler()
{
	Log::message("\Обработка события Changed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections changed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventChanged().connect(changed_event_connections, changed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventChanged().connect(changed_event_connections, []() {
		Log::message("\Обработка события Changed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
changed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection changed_event_connection;

// подписываемся на событие Changed с функцией-обработчиком, сохраняя соединение
publisher->getEventChanged().connect(changed_event_connection, changed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
changed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
changed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Changed через соединение
changed_event_connection.disconnect();

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

	// Обработчик события Changed, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события Changed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId changed_handler_id;

// подписываемся на событие Changed с лямбда-обработчиком, сохраняя идентификатор соединения
changed_handler_id = publisher->getEventChanged().connect(e_connections, []() {
		Log::message("\Обработка события Changed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventChanged().disconnect(changed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Changed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## static TextureRampPtr create ( int num_channels , int resolution , int flags )

Задаёт разрешение, количество каналов и флаги текстуры для этого экземпляра TextureRamp. Указатель на текстуру-рампу устанавливается в null, а кривые помечаются для обновления.
### Аргументы

- *int* **num_channels** - Количество каналов текстуры.
- *int* **resolution** - Разрешение текстуры-рампы по ширине.
- *int* **flags** - Флаги текстуры.

## static TextureRampPtr create ( const Ptr < TextureRamp > & texture_ramp )

Конструктор текстуры-рампы. Создаёт новую текстуру-рампу путём копирования заданной исходной текстуры-рампы.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[TextureRamp](../../../api/library/rendering/class.textureramp_cpp.md)> &* **texture_ramp** - Указатель на новую текстуру-рампу.

## TextureRamp ( )

## void releaseTexture ( )

Удаляет текстуру и её указатель.
## void copy ( const Ptr < TextureRamp > & src_texture_ramp )

Копирует данные исходной текстуры-рампы в текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[TextureRamp](../../../api/library/rendering/class.textureramp_cpp.md)> &* **src_texture_ramp** - Исходная текстура-рампа.

## Ptr < TextureRamp > clone ( ) const

Дублирует текстуру-рампу и возвращает указатель на копию.
## Ptr < Curve2d > getCurve ( int channel ) const

Возвращает указатель на [Curve2d](../../../api/library/common/class.curve2d_cpp.md) для указанного канала.
### Аргументы

- *int* **channel** - Требуемый канал.

### Возвращаемое значение

Указатель на объект Curve2d.
## void setDefaultCurve ( const Ptr < Curve2d > & default_curve )

Сбрасывает кривую на значение по умолчанию.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Curve2d](../../../api/library/common/class.curve2d_cpp.md)> &* **default_curve** - Кривая, используемая в качестве значения по умолчанию.

## void setDefaultCurve ( int channel , const Ptr < Curve2d > & default_curve )

Сбрасывает кривую для заданного канала на значение по умолчанию.
### Аргументы

- *int* **channel** - Канал R, G, B или A, заданный соответствующим значением от 0 до 3.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Curve2d](../../../api/library/common/class.curve2d_cpp.md)> &* **default_curve** - Кривая, используемая в качестве значения по умолчанию.

## bool isDefault ( int channel ) const

Возвращает значение, указывающее, является ли значение заданного канала кривой значением по умолчанию, ранее заданным через [setDefaultCurve](#setDefaultCurve_int_Curve2d_void).
### Аргументы

- *int* **channel** - Канал R, G, B или A, заданный соответствующим значением от 0 до 3.

### Возвращаемое значение

true, если значение кривой является значением по умолчанию, заданным через [setDefaultCurve](#setDefaultCurve_int_Curve2d_void), иначе false.
## void save ( const Ptr < Xml > & xml )

Сохраняет данные текстуры-рампы в заданный узел [Xml](../../../api/library/common/class.xml_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Целевой узел Xml.

## void save ( const Ptr < Json > & json ) const

Сохраняет данные текстуры-рампы в заданный экземпляр класса [Json](../../../api/library/common/class.json_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Json](../../../api/library/common/class.json_cpp.md)> &* **json** - Целевой экземпляр класса Json.

## void load ( const Ptr < Xml > & xml )

Загружает данные текстуры-рампы из заданного узла [Xml](../../../api/library/common/class.xml_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Исходный узел Xml, содержащий данные текстуры-рампы.

## void load ( const Ptr < Json > & json )

Загружает данные текстуры-рампы из заданного экземпляра класса [Json](../../../api/library/common/class.json_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Json](../../../api/library/common/class.json_cpp.md)> &* **json** - Исходный экземпляр класса Json, содержащий данные текстуры-рампы.

## void saveState ( const Ptr < Stream > & stream ) const

Сохраняет состояние текстуры-рампы в бинарный поток.
**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_void):


```cpp
// инициализируем узел и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
ramp->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
ramp->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток для сохранения данных состояния текстуры-рампы.

## void restoreState ( const Ptr < Stream > & stream ) const

Восстанавливает состояние текстуры-рампы из бинарного потока.
**Пример** использования методов [saveState()](#saveState_Stream_void) и restoreState():


```cpp
// инициализируем узел и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
ramp->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
ramp->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, хранящий данные состояния текстуры-рампы.
