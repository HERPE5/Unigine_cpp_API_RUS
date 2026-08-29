# Unigine.Materials Class (CPP)

**Header:** #include <UnigineMaterials.h>

> **Notice:** Этот класс является одиночкой (singleton).


Интерфейс для управления загруженными [materials](../../../principles/world_structure/index.md#materials) через код.


Все материалы, существующие в проекте, предзагружаются при инициализации движка в зависимости от режима предзагрузки материалов, заданного консольной командой [`materials_preload`](../../../code/console/index.md#materials_preload) (включена по умолчанию), и сохраняются при сохранении мира или при вызове консольной команды *[materials_save](../../../code/console/index.md#materials_save)*.


### См. также


- Пример C++ API находится в папке **<UnigineSDK>/source/samples/Api/Systems/Materials**


## Materials Class

### Методы класса

## void setPrecompileAllShaders ( bool shaders )

Задаёт новое значение, указывающее, включена ли предварительная компиляция шейдеров.
### Аргументы

- *bool* **shaders** - Установите **true**, чтобы включить предварительную компиляцию шейдеров; **false** - чтобы отключить её.

## bool isPrecompileAllShaders () const

Возвращает текущее значение, указывающее, включена ли предварительная компиляция шейдеров.
### Возвращаемое значение

**true**, если предварительная компиляция шейдеров включена; иначе **false**.
## int getNumMaterials () const

Возвращает текущее количество материалов, загруженных для текущего проекта.
### Возвращаемое значение

Текущее количество материалов.
## static Event<> getEventEndReload () const

Событие, вызываемое после того, как все материалы перезагружены (т.е. выполнение [reloadMaterials()](#reloadMaterials_void) завершено), если включена консольная переменная `materials_reload_event`. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndReload
void endreload_event_handler()
{
	Log::message("\Обработка события EndReload\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endreload_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Materials::getEventEndReload().connect(endreload_event_connections, endreload_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Materials::getEventEndReload().connect(endreload_event_connections, []() {
		Log::message("\Обработка события EndReload (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endreload_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endreload_event_connection;

// подписываемся на событие EndReload с функцией-обработчиком, сохраняя соединение
Materials::getEventEndReload().connect(endreload_event_connection, endreload_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endreload_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endreload_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndReload через соединение
endreload_event_connection.disconnect();

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

	// Обработчик события EndReload, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события EndReload\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Materials::getEventEndReload().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId endreload_handler_id;

// подписываемся на событие EndReload с лямбда-обработчиком, сохраняя идентификатор соединения
endreload_handler_id = Materials::getEventEndReload().connect(e_connections, []() {
		Log::message("\Обработка события EndReload (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Materials::getEventEndReload().disconnect(endreload_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndReload при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Materials::getEventEndReload().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Materials::getEventEndReload().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventBeginReload () const

Событие, вызываемое перед перезагрузкой всех загруженных материалов (т.е. при вызове [reloadMaterials()](#reloadMaterials_void)), если включена консольная переменная `materials_reload_event`. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginReload
void beginreload_event_handler()
{
	Log::message("\Обработка события BeginReload\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginreload_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Materials::getEventBeginReload().connect(beginreload_event_connections, beginreload_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Materials::getEventBeginReload().connect(beginreload_event_connections, []() {
		Log::message("\Обработка события BeginReload (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginreload_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginreload_event_connection;

// подписываемся на событие BeginReload с функцией-обработчиком, сохраняя соединение
Materials::getEventBeginReload().connect(beginreload_event_connection, beginreload_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginreload_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginreload_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginReload через соединение
beginreload_event_connection.disconnect();

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

	// Обработчик события BeginReload, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события BeginReload\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Materials::getEventBeginReload().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId beginreload_handler_id;

// подписываемся на событие BeginReload с лямбда-обработчиком, сохраняя идентификатор соединения
beginreload_handler_id = Materials::getEventBeginReload().connect(e_connections, []() {
		Log::message("\Обработка события BeginReload (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Materials::getEventBeginReload().disconnect(beginreload_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginReload при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Materials::getEventBeginReload().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Materials::getEventBeginReload().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## bool isShadersCompiling () const

Возвращает текущее значение, указывающее, выполняется ли асинхронная компиляция.
### Возвращаемое значение

**true**, если асинхронная компиляция выполняется; иначе **false**.
---

## Ptr < Material > loadMaterial ( const char * path )

Загружает материал, хранящийся по заданному пути. Функция может использоваться для загрузки материалов, созданных во время работы приложения, или хранящихся вне директории `data`.
### Аргументы

- *const char ** **path** - Путь к материалу (включая его имя).

### Возвращаемое значение

Загруженный материал.
## bool isMaterialGUID ( const UGUID & guid ) const

Возвращает значение, указывающее, существует ли материал с заданным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала.

### Возвращаемое значение

true, если материал с заданным GUID существует; иначе false.
## Ptr < Material > getMaterial ( int num ) const

Возвращает материал по его номеру.
### Аргументы

- *int* **num** - Номер материала.

### Возвращаемое значение

Материал.
## Ptr < Material > findManualMaterial ( const char * name ) const

Ищет ручной (manual) материал по заданному имени.
### Аргументы

- *const char ** **name** - Имя ручного материала.

### Возвращаемое значение

Умный указатель на ручной материал.
## Ptr < Material > findMaterialByGUID ( const UGUID & guid ) const

Ищет материал с заданным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала.

### Возвращаемое значение

Умный указатель на материал.
## Ptr < Material > findMaterialByFileGUID ( const UGUID & guid ) const

Ищет материал по заданному GUID файла материала.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла материала.

### Возвращаемое значение

Умный указатель на материал.
## Ptr < Material > findMaterialByPath ( const char * path ) const

Ищет материал, хранящийся по заданному пути.
### Аргументы

- *const char ** **path** - Путь загрузки материала (включая имя материала).

### Возвращаемое значение

Умный указатель на материал.
## void setCachedMaterial ( const Ptr < Material > & mat )

 Задаёт материал, который будет изменяться во время выполнения. Этот метод используется вместе с [setCachedState](#setCachedState_cstr_int_void) и [getCachedMaterial()](#getCachedMaterial_Material) для изменения состояния материала во время выполнения без необходимости пересчитывать материалы каждый кадр и перекомпилировать шейдеры. Использование этих методов настоятельно рекомендуется, если состояния материала меняются почти каждый кадр или несколько раз за кадр.
Рассмотрим пример использования, в котором эти методы могут пригодиться. Предположим, у вас есть ресурсоёмкий материал, и вы хотите снизить его качество при рендеринге в отражениях. Следующий псевдокод демонстрирует подход к использованию этих методов:


```text
MaterialPtr get_effect_material(bool quality)
	{
		Materials::setCachedMaterial(my_effect);

		Materials::setCachedState("quality", quality);

		return Material::getCachedMaterial();
	}

// переключаем качество материала в зависимости от того, где он рендерится
void event()
	{
		bool quality = true;
		if (Renderer::isReflection())
			quality = false;

		MaterialPtr mat = get_effect_material(quality);
	}

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **mat** - Материал, который будет изменяться во время выполнения.

## Ptr < Material > getCachedMaterial ( )

 Возвращает материал, изменённый во время выполнения. Этот метод используется вместе с [setCachedMaterial()](#setCachedMaterial_Material_void) и [setCachedState](#setCachedState_cstr_int_void) для изменения состояния материала во время выполнения без необходимости пересчитывать материалы каждый кадр и перекомпилировать шейдеры. Использование этих методов настоятельно рекомендуется, если состояния материала меняются почти каждый кадр или несколько раз за кадр.
Рассмотрим пример использования, в котором эти методы могут пригодиться. Предположим, у вас есть ресурсоёмкий материал, и вы хотите снизить его качество при рендеринге в отражениях. Следующий псевдокод демонстрирует подход к использованию этих методов:


```text
MaterialPtr get_effect_material(bool quality)
	{
		Materials::setCachedMaterial(my_effect);

		Materials::setCachedState("quality", quality);

		return Material::getCachedMaterial();
	}

// переключаем качество материала в зависимости от того, где он рендерится
void event()
	{
		bool quality = true;
		if (Renderer::isReflection())
			quality = false;

		MaterialPtr mat = get_effect_material(quality);
	}

```


### Возвращаемое значение

Материал, изменённый во время выполнения.
## void setCachedState ( const char * name , int value )

 Задаёт целевое состояние материала для его изменения во время выполнения. Этот метод используется вместе с [setCachedMaterial()](#setCachedMaterial_Material_void) и [getCachedMaterial()](#getCachedMaterial_Material) для изменения состояния материала во время выполнения без необходимости пересчитывать материалы каждый кадр и перекомпилировать шейдеры. Использование этих методов настоятельно рекомендуется, если состояния материала меняются почти каждый кадр или несколько раз за кадр.
Рассмотрим пример использования, в котором эти методы могут пригодиться. Предположим, у вас есть ресурсоёмкий материал, и вы хотите снизить его качество при рендеринге в отражениях. Следующий псевдокод демонстрирует подход к использованию этих методов:


```text
MaterialPtr get_effect_material(bool quality)
	{
		Materials::setCachedMaterial(my_effect);

		Materials::setCachedState("quality", quality);

		return Material::getCachedMaterial();
	}

// переключаем качество материала в зависимости от того, где он рендерится
void event()
	{
		bool quality = true;
		if (Renderer::isReflection())
			quality = false;

		MaterialPtr mat = get_effect_material(quality);
	}

```


### Аргументы

- *const char ** **name** - Имя изменяемого состояния.
- *int* **value** - Целевое значение состояния.

## bool removeMaterial ( const UGUID & guid , bool remove_file = 0 , bool remove_children = 1 )

Удаляет материал. Если включён флаг *remove_file*, файл материала также будет удалён. Если флаг отключён, удалённый материал будет снова загружен при следующем запуске приложения. Если включён флаг *remove_children*, все дочерние материалы также будут удалены.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID удаляемого материала.
- *bool* **remove_file** - Флаг, указывающий, будет ли удалён файл материала.
- *bool* **remove_children** - Флаг, указывающий, будут ли также удалены все дочерние материалы.

### Возвращаемое значение

true, если материал успешно удалён; иначе false.
## bool replaceMaterial ( const Ptr < Material > & material , const Ptr < Material > & new_material )

Заменяет материал заданным.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Заменяемый материал.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **new_material** - Материал для замены.

### Возвращаемое значение

true, если материал успешно заменён; иначе false.
## bool saveMaterials ( ) const

Сохраняет изменения, внесённые во все загруженные материалы.
### Возвращаемое значение

true, если материалы успешно сохранены; иначе false.
## void reloadMaterials ( )

Перезагружает все загруженные материалы.
## void destroyShaders ( )

Удаляет все шейдеры, используемые загруженными материалами.
## void destroyTextures ( )

Удаляет все текстуры, используемые загруженными материалами.
## void createShaders ( )

Создаёт все шейдеры для всех загруженных материалов.
## void createRenderMaterials ( )

Создаёт материалы рендеринга (внутренние материалы, необходимые для рендеринга). Например, вы можете создать все необходимые материалы рендеринга во время инициализации, чтобы избежать просадок производительности, которые могут возникнуть позже.
## void createShaderCache ( )

Создаёт кэш шейдеров для всех загруженных материалов.
## void createShadersFromCache ( )

Компилирует шейдеры, доступные в кэше шейдеров.
## void flushShadersCompiling ( )

Принудительно компилирует все шейдеры, находящиеся в очереди на асинхронную компиляцию.
