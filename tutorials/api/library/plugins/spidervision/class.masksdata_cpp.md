# Unigine::Plugins::SpiderVision::MasksData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Этот класс хранит данные обо всех [masks](../../../../principles/render/output/multi_monitor/spidervision_plugin/projection_setup.md#masks), созданных для viewport, и предоставляет интерфейс для настройки каждой маски.


Маска — это произвольная форма, заполненная выбранным цветом, которая позволяет вырезать выбранные области на изображении, отрисовываемом в viewport.


Этот объект доступен через соответствующий метод класса [ViewportData](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#getMasks_MasksData).


Данные масок хранятся в [configuration file](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#config_file).


## MasksData Class

### Методы класса

## void setEnabled ( bool enabled )

Задаёт новое значение, указывающее, включена ли отрисовка масок.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отрисовку масок; **false** - чтобы отключить её.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включена ли отрисовка масок.
### Возвращаемое значение

**true**, если отрисовка масок включена; иначе **false**.
## int getNumMasks () const

Возвращает текущее общее количество масок в конфигурации.
### Возвращаемое значение

Текущее общее количество масок в конфигурации.
## static Event<> getEventChanged () const

событие, вызываемое при изменении данных масок. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../../code/fundamentals/events/index_cpp.md).

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
MasksData::getEventChanged().connect(changed_event_connections, changed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
MasksData::getEventChanged().connect(changed_event_connections, []() {
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
MasksData::getEventChanged().connect(changed_event_connection, changed_event_handler);

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
MasksData::getEventChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
changed_handler_id = MasksData::getEventChanged().connect(e_connections, []() {
		Log::message("\Обработка события Changed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
MasksData::getEventChanged().disconnect(changed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Changed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
MasksData::getEventChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
MasksData::getEventChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## void clear ( )

Очищает все маски.
## int addMask ( )

Добавляет новую маску.
### Возвращаемое значение

Индекс маски.
## void removeMask ( int index )

Удаляет маску с указанным индексом.
### Аргументы

- *int* **index** - Индекс маски.

## void setMaskName ( int mask , const char * name )

Задаёт имя для указанной маски.
### Аргументы

- *int* **mask** - Индекс маски.
- *const char ** **name** - Имя маски.

## String getMaskName ( int mask ) const

Возвращает имя указанной маски.
### Аргументы

- *int* **mask** - Индекс маски.

### Возвращаемое значение

Имя маски.
## void setMaskEnabled ( int mask , bool enabled )

Задаёт значение, указывающее, включена ли отрисовка указанной маски.
### Аргументы

- *int* **mask** - Индекс маски.
- *bool* **enabled** - true, чтобы включить отрисовку маски, false - чтобы отключить её.

## bool isMaskEnabled ( int mask ) const

Возвращает значение, указывающее, включена ли отрисовка указанной маски.
### Аргументы

- *int* **mask** - Индекс маски.

### Возвращаемое значение

true, если отрисовка маски включена, иначе false.
## void setMaskSmoothStep ( int mask , int smooth_step )

Задаёт сглаживание краёв для указанной маски.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **smooth_step** - Значение сглаживания, количество дополнительных точек, вставляемых между контрольными точками маски.

## int getMaskSmoothStep ( int mask ) const

Возвращает значение сглаживания для указанной маски.
### Аргументы

- *int* **mask** - Индекс маски.

### Возвращаемое значение

Значение сглаживания, количество дополнительных точек, вставленных между контрольными точками маски.
## int addPoint ( int mask )

Добавляет точку в маску как последнюю точку в списке точек.
### Аргументы

- *int* **mask** - Индекс маски.

### Возвращаемое значение

Индекс добавленной точки.
## int addPoint ( int mask , int insert_index )

Добавляет точку в маску.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **insert_index** - Индекс точки.

### Возвращаемое значение

Общее количество точек в маске.
## void removePoint ( int mask , int index )

Удаляет точку из маски.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.

## int getNumPoints ( int mask ) const

Возвращает общее количество точек в маске.
### Аргументы

- *int* **mask** - Индекс маски.

### Возвращаемое значение

Общее количество точек.
## void setPoint ( int mask , int index , const Math:: vec2 & point )

Задаёт координаты указанной точки в маске.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Координаты точки.

## Math:: vec2 getPoint ( int mask , int index ) const

Возвращает координаты указанной точки в маске.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.

### Возвращаемое значение

Координаты точки.
## void setPointHandleLeft ( int mask , int index , const Math:: vec2 & point )

Задаёт левую контрольную точку-указатель для указанной точки в маске.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Координаты левой контрольной точки-указателя.

## Math:: vec2 getHandleLeft ( int mask , int index ) const

Возвращает левую контрольную точку-указатель для указанной точки в маске.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.

### Возвращаемое значение

Координаты левой контрольной точки-указателя.
## void setPointHandleRight ( int mask , int index , const Math:: vec2 & point )

Задаёт правую контрольную точку-указатель для указанной точки в маске.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Координаты правой контрольной точки-указателя.

## Math:: vec2 getHandleRight ( int mask , int index ) const

Возвращает правую контрольную точку-указатель для указанной точки в маске.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.

### Возвращаемое значение

Координаты правой контрольной точки-указателя.
## void setPointSmoothType ( int mask , int index , ViewportData::POINT_SMOOTH_TYPE type )

Задаёт поведение изгиба линии для точки.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.
- *[ViewportData::POINT_SMOOTH_TYPE](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#POINT_SMOOTH_TYPE)* **type** - Тип поведения изгиба линии в точке.

## ViewportData::POINT_SMOOTH_TYPE getPointSmoothType ( int mask , int index ) const

Возвращает поведение изгиба линии для точки.
### Аргументы

- *int* **mask** - Индекс маски.
- *int* **index** - Индекс точки.

### Возвращаемое значение

Тип поведения изгиба линии в точке.
## void saveXml ( const Ptr < Xml > & xml )

Сохраняет данные масок в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные.

## bool restoreXml ( const Ptr < Xml > & xml )

Загружает данные масок из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.

### Возвращаемое значение

true, если данные успешно загружены; иначе false.
## void save ( const Ptr < Stream > & stream )

Сохраняет данные масок в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restore ( const Ptr < Stream > & stream )

Загружает данные масок из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.
