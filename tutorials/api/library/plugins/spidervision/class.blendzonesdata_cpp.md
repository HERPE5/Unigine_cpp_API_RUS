# Unigine::Plugins::SpiderVision::BlendZonesData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Этот класс хранит данные обо всех [blend zones](../../../../principles/render/output/multi_monitor/spidervision_plugin/projection_setup.md#blend), созданных для viewport, и предоставляет интерфейс для настройки каждой зоны смешивания.


Зона смешивания — это произвольная форма, образованная тремя вертикальными линиями, так что она состоит из двух частей — одна часть является маской (от синей до зелёной линии), а другая (от зелёной до красной линии) является градиентной зоной.


![](../../../../principles/render/output/multi_monitor/spidervision_plugin/blend_zone.jpg)


Данные зоны смешивания хранятся в [configuration file](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#config_file).


Для настройки параметров конкретной зоны смешивания viewport используются методы этого класса. Однако экземпляр класса *BlendZonesData* не хранит информацию о том, к какому viewport он привязан — эта информация хранится в экземпляре класса *[ViewportData](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#getBlendZones_BlendZonesData)*.


## BlendZonesData Class

### Перечисления

## BLEND_POINT_ROLE

| Name | Description |
|---|---|
| **BLEND_POINT_ROLE_TRANSPARENT** = 0 | Точка на стороне зоны смешивания, затухающая до прозрачности. |
| **BLEND_POINT_ROLE_CENTER** = 1 | Точка в центре зоны смешивания. |
| **BLEND_POINT_ROLE_MASK** = 2 | Точка на стороне зоны смешивания, которая маскируется. |
| **BLEND_POINT_ROLE_NUM** = 3 | Общее количество типов точек смешивания. |

### Методы класса

## void setEnabled ( bool enabled )

Задаёт новое значение, указывающее, включена ли отрисовка зон смешивания.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отрисовку зон смешивания; **false** - чтобы отключить её.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включена ли отрисовка зон смешивания.
### Возвращаемое значение

**true**, если отрисовка зон смешивания включена; иначе **false**.
## int getNumZones () const

Возвращает текущее общее количество зон смешивания.
### Возвращаемое значение

Текущее общее количество зон смешивания.
## static Event<> getEventChanged () const

событие, вызываемое при изменении данных зон смешивания. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

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
BlendZonesData::getEventChanged().connect(changed_event_connections, changed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
BlendZonesData::getEventChanged().connect(changed_event_connections, []() {
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
BlendZonesData::getEventChanged().connect(changed_event_connection, changed_event_handler);

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
BlendZonesData::getEventChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
changed_handler_id = BlendZonesData::getEventChanged().connect(e_connections, []() {
		Log::message("\Обработка события Changed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
BlendZonesData::getEventChanged().disconnect(changed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Changed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
BlendZonesData::getEventChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
BlendZonesData::getEventChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## int addZone ( )

Добавляет новую зону смешивания для viewport.
### Возвращаемое значение

Индекс добавленной зоны смешивания.
## void removeZone ( int index )

Удаляет указанную зону смешивания.
### Аргументы

- *int* **index** - Индекс зоны смешивания.

## void clear ( )

Очищает все зоны смешивания.
## void changeZoneResolution ( int zone , int count )

Определяет количество линий между начальной и конечной точками, помогающих настроить контур. Этот метод соответствует параметру *Resolution* в настройках зоны смешивания в UI.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **count** - Количество линий в области от начальной до конечной точки зоны смешивания.

## void setZoneEnabled ( int zone , bool in_enabled )

Включает или отключает указанную зону смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *bool* **in_enabled** - true, чтобы включить указанную зону смешивания, false, чтобы отключить её.

## bool isZoneEnabled ( int zone ) const

Возвращает значение, указывающее, включена ли указанная зона смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

true, если указанная зона смешивания включена, иначе false.
## void setZoneAlpha ( int zone , float in_alpha )

Задаёт значение alpha для указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *float* **in_alpha** - Значение alpha.

## float getZoneAlpha ( int zone ) const

Возвращает значение alpha для указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Значение alpha.
## void setZoneContrast ( int zone , float in_contrast )

Задаёт значение контрастности для указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *float* **in_contrast** - Значение контрастности.

## float getZoneContrast ( int zone ) const

Возвращает значение контрастности для указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Значение контрастности.
## void setZoneGamma ( int zone , float in_gamma )

Задаёт значение гаммы для указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *float* **in_gamma** - Значение гаммы.

## float getZoneGamma ( int zone ) const

Возвращает значение гаммы для указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Значение гаммы.
## void setZoneLinked ( int zone , bool linked )

Задаёт значение, указывающее, включена ли связь зоны. При включении позволяет одновременно настраивать Alpha, Contrast и Gamma для двух зон смешивания для лучшего сопряжения двух viewport.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *bool* **linked** - true, чтобы включить связь зоны, false, чтобы отключить её.

## bool isZoneLinked ( int zone ) const

Возвращает значение, указывающее, включена ли связь зоны. При включении позволяет одновременно настраивать Alpha, Contrast и Gamma для двух зон смешивания для лучшего сопряжения двух viewport.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

true, если связь зоны включена, иначе false.
## void setZoneLink ( int zone , const Math:: ivec2 & link )

Связывает две зоны смешивания для синхронной настройки их параметров.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *const  Math::[ivec2](../../../../api/library/math/class.ivec2_cpp.md) &* **link** - Вектор, содержащий два значения:

  1. Индекс viewport, зона смешивания которого должна быть связана
  2. Индекс зоны смешивания в списке зон смешивания этого viewport

## Math:: ivec2 getZoneLink ( int zone ) const

Возвращает информацию о зоне смешивания, связанной с данной зоной смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Вектор, содержащий два значения:
1. Индекс viewport, зона смешивания которого должна быть связана
2. Индекс зоны смешивания в списке зон смешивания этого viewport


## int addLine ( int zone )

Добавляет линию к указанной зоне смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Индекс линии.
## void removeLine ( int zone , int index )

Удаляет указанную линию из указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **index** - Индекс линии.

## int getNumLines ( int zone ) const

Возвращает общее количество линий для указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Общее количество линий.
## void setLinePoint ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type , const Math:: vec2 & point )

Задаёт точку с указанными координатами и типом на указанной линии указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **point** - Координаты точки.

## Math:: vec2 getLinePoint ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type ) const

Возвращает координаты точки указанного типа на указанной линии указанной зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.

### Возвращаемое значение

Координаты точки.
## void setLinePointHandleLeft ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type , const Math:: vec2 & handle_left )

Задаёт координаты левого управляющего маркера для указанной точки.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **handle_left** - Координаты маркера.

## Math:: vec2 getLinePointHandleLeft ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type ) const

Возвращает координаты левого управляющего маркера для указанной точки.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.

### Возвращаемое значение

Координаты маркера.
## void setLinePointHandleRight ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type , const Math:: vec2 & handle_right )

Задаёт координаты правого управляющего маркера для указанной точки.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.
- *const  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) &* **handle_right** - Координаты маркера.

## Math:: vec2 getLinePointHandleRight ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type ) const

Возвращает координаты правого управляющего маркера для указанной точки.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.

### Возвращаемое значение

Координаты маркера.
## void setLinePointSmoothType ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type , ViewportData::POINT_SMOOTH_TYPE smooth_type )

Задаёт поведение изгиба линии для точки.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.
- *[ViewportData::POINT_SMOOTH_TYPE](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#POINT_SMOOTH_TYPE)* **smooth_type** - Тип поведения изгиба линии в точке.

## ViewportData::POINT_SMOOTH_TYPE getLinePointSmoothType ( int zone , int line , BlendZonesData::BLEND_POINT_ROLE type ) const

Возвращает поведение изгиба линии для точки.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **line** - Индекс линии.
- *[BlendZonesData::BLEND_POINT_ROLE](../../../../api/library/plugins/spidervision/class.blendzonesdata_cpp.md#BLEND_POINT_ROLE)* **type** - Тип точки.

### Возвращаемое значение

Тип поведения изгиба линии в точке.
## void setZoneName ( int zone , const char * name )

Задаёт имя зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *const char ** **name** - Имя зоны смешивания.

## String getZoneName ( int zone ) const

Возвращает имя зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Имя зоны смешивания.
## void setZoneSmooth ( int zone , int value )

Задаёт значение сглаживания, определяющее округлость краёв зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.
- *int* **value** - Значение сглаживания — количество дополнительных точек, создающих сплайн Безье между двумя точками зоны смешивания.

## int getZoneSmooth ( int zone ) const

Возвращает значение сглаживания, определяющее округлость краёв зоны смешивания.
### Аргументы

- *int* **zone** - Индекс зоны смешивания.

### Возвращаемое значение

Значение сглаживания.
## void saveXml ( const Ptr < Xml > & xml )

Сохраняет данные зон смешивания в указанный экземпляр класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), в который будут сохранены данные.

## bool restoreXml ( const Ptr < Xml > & xml )

Загружает данные зон смешивания из указанного экземпляра класса Xml.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - Экземпляр [Xml class](../../../../api/library/common/class.xml_cpp.md), из которого загружаются данные.

### Возвращаемое значение

true, если данные успешно загружены, иначе false.
## void save ( const Ptr < Stream > & stream )

Сохраняет данные зон смешивания в указанный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные.

## void restore ( const Ptr < Stream > & stream )

Загружает данные зон смешивания из указанного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружаются данные.
