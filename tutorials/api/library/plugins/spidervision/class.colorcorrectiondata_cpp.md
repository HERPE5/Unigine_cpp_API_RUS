# Unigine::Plugins::SpiderVision::ColorCorrectionData Class (CPP)

**Header:** #include <plugins/Unigine/SpiderVision/UnigineSpiderVision.h>


Экземпляр этого класса хранит данные цветокоррекции viewport. Цветокоррекция может потребоваться для компенсации разницы в цветопередаче различных проекторов.


Также можно настроить яркость изображения, чтобы части изображения, находящиеся дальше от наблюдателя, были светлее, и наоборот, чтобы яркость итогового изображения была равномерной.


Данные цветокоррекции хранятся в [configuration file](../../../../principles/render/output/multi_monitor/spidervision_plugin/displays_setup.md#config_file).


Этот объект доступен через соответствующий метод класса [ViewportData](../../../../api/library/plugins/spidervision/class.viewportdata_cpp.md#getColorCorrection_ColorCorrectionData).


## ColorCorrectionData Class

### Методы класса

## void setEnabled ( bool enabled )

Задаёт новое значение, указывающее, применяется ли цветокоррекция.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить цветокоррекцию; **false** - чтобы отключить её.

## bool isEnabled () const

Возвращает текущее значение, указывающее, применяется ли цветокоррекция.
### Возвращаемое значение

**true**, если цветокоррекция включена; иначе **false**.
## void setColorScale ( const Math:: vec4 & scale )

Задаёт новый множитель цвета для отрисовываемого изображения.
### Аргументы

- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md)&* **scale** - Множитель цвета

## Math:: vec4 getColorScale () const

Возвращает текущий множитель цвета для отрисовываемого изображения.
### Возвращаемое значение

Текущий множитель цвета
## void setColorBias ( const Math:: vec4 & bias )

Задаёт новое смещение цвета для отрисовываемого изображения.
### Аргументы

- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md)&* **bias** - Смещение цвета по каждому каналу.

## Math:: vec4 getColorBias () const

Возвращает текущее смещение цвета для отрисовываемого изображения.
### Возвращаемое значение

Текущее смещение цвета по каждому каналу.
## void setCornerBrightness ( const Math:: vec4 & brightness )

Задаёт новые значения коррекции яркости для углов отрисовываемого изображения.
### Аргументы

- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md)&* **brightness** - Четырёхкомпонентный вектор, содержащий значения яркости в диапазоне **[0.0f, 1.0f]** для углов отрисовываемого изображения (верхний левый, верхний правый, нижний левый, нижний правый).

## Math:: vec4 getCornerBrightness () const

Возвращает текущие значения коррекции яркости для углов отрисовываемого изображения.
### Возвращаемое значение

Текущий четырёхкомпонентный вектор, содержащий значения яркости в диапазоне **[0.0f, 1.0f]** для углов отрисовываемого изображения (верхний левый, верхний правый, нижний левый, нижний правый).
## static Event<> getEventChanged () const

событие, вызываемое при изменении данных цветокоррекции. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Для удобства также можно использовать классы *[EventConnection](../../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

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
ColorCorrectionData::getEventChanged().connect(changed_event_connections, changed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
ColorCorrectionData::getEventChanged().connect(changed_event_connections, []() {
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
ColorCorrectionData::getEventChanged().connect(changed_event_connection, changed_event_handler);

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
ColorCorrectionData::getEventChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
changed_handler_id = ColorCorrectionData::getEventChanged().connect(e_connections, []() {
		Log::message("\Обработка события Changed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
ColorCorrectionData::getEventChanged().disconnect(changed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Changed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
ColorCorrectionData::getEventChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
ColorCorrectionData::getEventChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## void saveXml ( const Ptr < Xml > & xml )

Saves the color correction data to the given instance of the Xml class.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - [Xml class](../../../../api/library/common/class.xml_cpp.md) instance into which the data will be saved.

## bool restoreXml ( const Ptr < Xml > & xml )

Loads the color correction data from the specified instance of the Xml class.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../../api/library/common/class.xml_cpp.md)> &* **xml** - [Xml class](../../../../api/library/common/class.xml_cpp.md) instance the data from which is to be loaded.

### Возвращаемое значение

true if the data has been loaded successfully, otherwise false.
## void save ( const Ptr < Stream > & stream )

Saves the color correction data to the specified stream.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Stream to which the data is to be written.

## void restore ( const Ptr < Stream > & stream )

Loads the color correction data from the specified stream.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **stream** - Stream the data from which is to be loaded.
