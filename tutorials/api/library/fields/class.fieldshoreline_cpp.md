# Класс FieldShoreline (CPP)

**Заголовочный файл:** #include <UnigineFields.h>

**Наследуется от:** Field


Этот класс используется для создания и изменения [field shoreline](../../../objects/effects/fields/field_shoreline/index.md). Поле применяется к [global water](../../../api/library/objects/class.objectwaterglobal_cpp.md) и помогает создавать накаты волн у берегов, а также применяет эффект намокания к объектам вблизи береговой линии.

> **Notice:** Объект field shoreline будет влиять на воду только в том случае, если опция *FieldShoreline interaction* включена на вкладке *States* материала [water_global_base](../../../content/materials/library/water_global_base/index.md).


### Создание поля береговой линии


> **Notice:** При создании объекта FieldShoreline следует указать для него текстуру береговой линии, так как у этого объекта нет текстуры по умолчанию.


```cpp
// создаём новый экземпляр класса FieldShoreline и задаём его трансформацию
FieldShorelinePtr shoreline = FieldShoreline::create();
shoreline->setTransform(Mat4(1));
// задаём размер поля
shoreline->setSize(vec3(4096.0f, 4096.0f, 512.0f));
// задаём путь к текстуре береговой линии
shoreline->setTexturePath("unigine_project/textures/shorelines/shoreline_0.texture");

```


## Класс FieldShoreline

### Методы класса

## void setTexture ( const Ptr < Texture >& texture )

Устанавливает новую текстуру береговой линии, используемую GPU для FieldShoreline.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)>&* **texture** - Экземпляр текстуры береговой линии.

## Ptr < Texture > getTexture () const

Возвращает текущую текстуру береговой линии, используемую GPU для FieldShoreline.
### Возвращаемое значение

Текущий экземпляр текстуры береговой линии.
## void setTexturePath ( const char * path )

Устанавливает новый путь к текстуре FieldShoreline.
### Аргументы

- *const char ** **path** - Путь к текстуре FieldShoreline.

## const char * getTexturePath () const

Возвращает текущий путь к текстуре FieldShoreline.
### Возвращаемое значение

Текущий путь к текстуре FieldShoreline.
## void setSize ( const Math:: vec3 & size )

Устанавливает новый вектор размера vec3 для FieldShoreline.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **size** - Вектор размера vec3 для FieldShoreline. Значение по умолчанию — (**512.0f**, **512.0f**, **512.0f**).

## Math:: vec3 getSize () const

Возвращает текущий вектор размера vec3 для FieldShoreline.
### Возвращаемое значение

Текущий вектор размера vec3 для FieldShoreline.
Значение по умолчанию — (**512.0f**, **512.0f**, **512.0f**).


## Event<> getEventProgress () const

Событие, срабатывающее при запекании береговой линии (при вызове [bakeWaterLevel()](#bakeWaterLevel_Image_int)). Это событие вызывается для каждой итерации запекания, и в событие передаётся значение от 0 до 1 (где 1 соответствует 100%). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Progress
void progress_event_handler()
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
publisher->getEventProgress().connect(progress_event_connections, []() {
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
	void event_handler()
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
progress_handler_id = publisher->getEventProgress().connect(e_connections, []() {
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
---

## static FieldShorelinePtr create ( )

Конструктор по умолчанию. Создаёт экземпляр FieldShoreline с размером по умолчанию vec3(**512.0f, 512.0f, 512.0f**).
> **Notice:** По умолчанию текстура береговой линии пуста. Укажите её после создания FieldShoreline с помощью соответствующей функции.


## int bakeWaterLevel ( const Ptr < Image > & image )

Запекает береговую линию для текущего уровня воды объекта глобальной воды и помещает результат в указанное изображение. Этот метод генерирует текстуру береговой линии, находя пересечения объекта [Global Water](../../../objects/objects/water/water_object.md) с террейнами ([Landscape Terrain](../../../objects/objects/terrain/landscape_terrain/index.md) и [Terrain Global](../../../objects/objects/terrain/terrain_global/index.md))
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Экземпляр изображения, в которое будет запечена береговая линия для текущего уровня воды.

### Возвращаемое значение

**1**, если береговая линия успешно запечена; иначе **0**.
## int setTextureImage ( const Ptr < Image > & image )

Устанавливает заданное изображение в качестве текстуры береговой линии FieldShoreline.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Экземпляр изображения с текстурой береговой линии для FieldShoreline.

## int getTextureImage ( const Ptr < Image > & image ) const

Захватывает текстуру для FieldShoreline (уже загруженную на GPU) и сохраняет её в заданный экземпляр Image.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Экземпляр изображения, в который будет сохранена текстура.

### Возвращаемое значение

**1**, если текстура успешно захвачена; иначе **0**.
## int createShorelineDistanceField ( const Ptr < Texture > & texture , int shoreline_radius , int blur_radius , int downsample_resolution )

Создаёт поле расстояний береговой линии с указанными параметрами и помещает его в указанное изображение.
```text
float shoreline_radius = 64;
int blur_radius = 8;
int downsample_resolution = 128;
Texture distance_field = new Texture();
field.createShorelineDistanceField(distance_field,shoreline_radius,blur_radius,downsample_resolution);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Текстура, в которую будет помещено поле расстояний береговой линии.
- *int* **shoreline_radius** - Радиус береговой линии.
- *int* **blur_radius** - Радиус области размытия.
- *int* **downsample_resolution** - Разрешение береговой линии.

### Возвращаемое значение

**1**, если поле было успешно создано; иначе **0**.
## static int type ( )

Возвращает тип объекта.
### Возвращаемое значение

Идентификатор типа [FieldShoreline](../../../api/library/nodes/class.node_cpp.md#FIELD_SHORELINE).
