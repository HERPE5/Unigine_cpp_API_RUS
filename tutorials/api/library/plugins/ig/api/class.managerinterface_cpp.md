# Unigine::Plugins::IG::Manager Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>

> **Notice:** Этот класс является синглтоном.


Этот класс представляет интерфейс Manager IG.

> **Notice:** Плагин IG должен быть загружен.


## Manager Class

### Перечисления

## DEBUG_MODE

| Name | Description |
|---|---|
| **DEBUG_MODE_REQUEST_DEBUG** = 0 | Режим отладки, визуализирующий, куда отправляются запросы LOS/HAT/HOT. |
| **DEBUG_MODE_ENTITY_PATH_TRACE** = 1 | Режим отладки с трассировкой пути сущности — позиции между кадрами и данные, отправленные по сети. Синие точки отмечают данные с сервера; розовые стрелки — движение между кадрами. |
| **DEBUG_MODE_ENTITY_PATH_TRACE_TIME** = 2 | Режим отладки, визуализирующий время трассировки пути сущности. |
| **DEBUG_MODE_ENTITY_COLLISION_SEGMENT** = 3 | Режим отладки, визуализирующий сегменты столкновений для каждой сущности. |
| **DEBUG_MODE_ENTITY_COLLISION_VOLUME** = 4 | Режим отладки, визуализирующий объёмы столкновений для каждой сущности. |
| **DEBUG_MODE_ENTITY_INFO** = 5 | Режим отладки, визуализирующий основу для каждой сущности CIGI и DIS с указанием ID, типа и имени типа (информация берётся из файла [IG configuration](../../../../../ig/config.md)). |
| **DEBUG_MODE_METEO** = 6 | Режим отладки, визуализирующий метеорологическую информацию. |
| **DEBUG_MODE_INTERPOLATION_INFO** = 7 | Режим отладки, визуализирующий на экране параметры и состояния таймера интерполяции. Отображение этих данных также можно включить консольной командой ig_debug_interpolation. |

### Методы класса

## void setDebugScale ( float scale )

Задаёт новый множитель масштаба для элементов визуализатора [Debug](../../../../../ig/debug/index.md).
### Аргументы

- *float* **scale** - Множитель масштаба для элементов визуализатора [Debug](../../../../../ig/debug/index.md).

## float getDebugScale () const

Возвращает текущий множитель масштаба для элементов визуализатора [Debug](../../../../../ig/debug/index.md).
### Возвращаемое значение

Текущий множитель масштаба для элементов визуализатора [Debug](../../../../../ig/debug/index.md).
## void setDebugDepth ( bool depth )

Задаёт новое значение, указывающее, включена ли проверка глубины для элементов визуализатора [Debug](../../../../../ig/debug/index.md) (должны ли элементы перекрываться теми, что ближе к камере).
### Аргументы

- *bool* **depth** - Установите **true**, чтобы включить проверку глубины для элементов визуализатора [Debug](../../../../../ig/debug/index.md); **false** - чтобы отключить.

## bool isDebugDepth () const

Возвращает текущее значение, указывающее, включена ли проверка глубины для элементов визуализатора [Debug](../../../../../ig/debug/index.md) (должны ли элементы перекрываться теми, что ближе к камере).
### Возвращаемое значение

**true**, если проверка глубины для элементов визуализатора [Debug](../../../../../ig/debug/index.md) включена; иначе **false**.
## void setDebugScreenspace ( bool screenspace )

Задаёт новое значение, указывающее тип пространства, используемый при отрисовке элементов визуализатора [Debug](../../../../../ig/debug/index.md): экранное пространство или мировое пространство.
### Аргументы

- *bool* **screenspace** - Установите **true**, чтобы включить визуализацию Debug в экранном пространстве; **false** - чтобы отключить.

## bool isDebugScreenspace () const

Возвращает текущее значение, указывающее тип пространства, используемый при отрисовке элементов визуализатора [Debug](../../../../../ig/debug/index.md): экранное пространство или мировое пространство.
### Возвращаемое значение

**true**, если визуализация Debug в экранном пространстве включена; иначе **false**.
## void setDebugDuration ( float duration )

Задаёт новый период времени, в течение которого отображаются элементы визуализатора [Debug](../../../../../ig/debug/index.md).
### Аргументы

- *float* **duration** - Интервал времени, в течение которого отображаются элементы визуализатора [Debug](../../../../../ig/debug/index.md), в секундах.

## float getDebugDuration () const

Возвращает текущий период времени, в течение которого отображаются элементы визуализатора [Debug](../../../../../ig/debug/index.md).
### Возвращаемое значение

Текущий интервал времени, в течение которого отображаются элементы визуализатора [Debug](../../../../../ig/debug/index.md), в секундах.
## void setDebugEnabled ( bool enabled )

Задаёт новое значение, указывающее, включён ли [Debug mode](../../../../../ig/debug/index.md). Этот режим позволяет инспектировать приложение IG во время выполнения.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить [Debug mode](../../../../../ig/debug/index.md); **false** - чтобы отключить.

## bool isDebugEnabled () const

Возвращает текущее значение, указывающее, включён ли [Debug mode](../../../../../ig/debug/index.md). Этот режим позволяет инспектировать приложение IG во время выполнения.
### Возвращаемое значение

**true**, если [Debug mode](../../../../../ig/debug/index.md) включён; иначе **false**.
## void setCollisionVolumeMask ( int mask )

Задаёт новую маску объёма столкновений для сущностей.
### Аргументы

- *int* **mask** - Маска объёма столкновений для сущностей.

## int getCollisionVolumeMask () const

Возвращает текущую маску объёма столкновений для сущностей.
### Возвращаемое значение

Текущая маска объёма столкновений для сущностей.
## void setTerrainIntersectionMask ( int mask )

Задаёт новую [intersection mask](../../../../../principles/bit_masking/index.md#intersection_mask), используемую для определения земли/посадочной поверхности.
### Аргументы

- *int* **mask** - Маска пересечений.

## int getTerrainIntersectionMask () const

Возвращает текущую [intersection mask](../../../../../principles/bit_masking/index.md#intersection_mask), используемую для определения земли/посадочной поверхности.
### Возвращаемое значение

Текущая маска пересечений.
## bool isTerrainCurved () const

Возвращает текущее значение, указывающее, изогнут ли ландшафт.
### Возвращаемое значение

**true**, если ландшафт изогнут; иначе **false**.
## Math:: dvec3 getGeodeticOrigin () const

Возвращает текущие координаты геодезического начала координат.
### Возвращаемое значение

Текущие координаты геодезического начала координат.
## Ptr < GeodeticPivot > getGeodeticPivot () const

Возвращает текущий геодезический pivot, используемый для изгиба ландшафта.
### Возвращаемое значение

Текущий геодезический pivot, используемый для изгиба ландшафта.
## Ptr < ObjectTerrainGlobal > getTerrain () const

Возвращает текущий объект Global Terrain.
### Возвращаемое значение

Текущий используемый объект Global Terrain.
## void setInterpolation ( bool interpolation )

Задаёт новое значение, указывающее, включены ли [interpolation and extrapolation](../../../../../ig/index.md#interpolation) для IG.
### Аргументы

- *bool* **interpolation** - Установите **true**, чтобы включить [interpolation and extrapolation](../../../../../ig/index.md#interpolation) для IG; **false** - чтобы отключить.

## bool isInterpolation () const

Возвращает текущее значение, указывающее, включены ли [interpolation and extrapolation](../../../../../ig/index.md#interpolation) для IG.
### Возвращаемое значение

**true**, если [interpolation and extrapolation](../../../../../ig/index.md#interpolation) для IG включены; иначе **false**.
## void setInterpolationLerpFactor ( double factor )

Задаёт новое значение коэффициента lerp интерполяции для IG. Чем *ниже* значение, тем плавнее будет движение, но будет ощущение, что объекты движутся под водой или в желе; *более высокие* значения дают более высокую точность позиционирования (положения объектов будут ближе к фактическим для текущего кадра), но объекты будут двигаться с заметным дрожанием.
> **Notice:** Режим [Frame-to-frame interpolation](#setInterpolationLerp_int_void) должен быть включён.


### Аргументы

- *double* **factor** - Значение коэффициента lerp интерполяции.

## double getInterpolationLerpFactor () const

Возвращает текущее значение коэффициента lerp интерполяции для IG. Чем *ниже* значение, тем плавнее будет движение, но будет ощущение, что объекты движутся под водой или в желе; *более высокие* значения дают более высокую точность позиционирования (положения объектов будут ближе к фактическим для текущего кадра), но объекты будут двигаться с заметным дрожанием.
> **Notice:** Режим [Frame-to-frame interpolation](#setInterpolationLerp_int_void) должен быть включён.


### Возвращаемое значение

Текущее значение коэффициента lerp интерполяции.
## void setExtrapolationPeriod ( double period = 0.2 )

Задаёт новое значение периода экстраполяции для IG.
### Аргументы

- *double* **period** - Значение периода экстраполяции, в секундах.

## double getExtrapolationPeriod () const

Возвращает текущее значение периода экстраполяции для IG.
### Возвращаемое значение

Текущее значение периода экстраполяции, в секундах.
## void setInterpolationPeriod ( double period = 0.04 )

Задаёт новое значение периода интерполяции для IG.
### Аргументы

- *double* **period** - Значение периода интерполяции, в секундах.

## double getInterpolationPeriod () const

Возвращает текущее значение периода интерполяции для IG.
### Возвращаемое значение

Текущее значение периода интерполяции, в секундах.
## void setInterpolationTime ( double time )

Задаёт новое значение времени интерполяции для IG.
### Аргументы

- *double* **time** - Значение времени интерполяции, в секундах.

## double getInterpolationTime () const

Возвращает текущее значение времени интерполяции для IG.
### Возвращаемое значение

Текущее значение времени интерполяции, в секундах.
## void setInterpolationLerp ( bool lerp )

Задаёт новое значение, указывающее, включена ли интерполяция между текущим и предыдущим кадрами для IG.
### Аргументы

- *bool* **lerp** - Установите **true**, чтобы включить интерполяцию между текущим и предыдущим кадрами для IG; **false** - чтобы отключить.

## bool isInterpolationLerp () const

Возвращает текущее значение, указывающее, включена ли интерполяция между текущим и предыдущим кадрами для IG.
### Возвращаемое значение

**true**, если интерполяция между текущим и предыдущим кадрами для IG включена; иначе **false**.
## void setInterpolationBufferSize ( int size )

Задаёт новый размер буфера [interpolation](../../../../../ig/index.md#interpolation). Рекомендуется устанавливать размер буфера равным количеству сообщений, полученных за два [interpolation periods](#setInterpolationPeriod_double_void).
### Аргументы

- *int* **size** - Размер буфера интерполяции (количество сообщений).

## int getInterpolationBufferSize () const

Возвращает текущий размер буфера [interpolation](../../../../../ig/index.md#interpolation). Рекомендуется устанавливать размер буфера равным количеству сообщений, полученных за два [interpolation periods](#setInterpolationPeriod_double_void).
### Возвращаемое значение

Текущий размер буфера интерполяции (количество сообщений).
## void setCurrentView ( int view )

Задаёт новый view по его ID. Если view с указанным ID не существует, он будет создан автоматически.
### Аргументы

- *int* **view** - ID отрисовываемого view.

## int getCurrentView () const

Возвращает текущий view по его ID. Если view с указанным ID не существует, он будет создан автоматически.
### Возвращаемое значение

Текущий ID отрисовываемого view.
## Unigine::Plugins::Geodetics::Converter * getConverter () const

Возвращает текущий интерфейс *[converter](../../../../../api/library/geodetics/geodetics_plugin/class.transformer_cpp.md)*.
### Возвращаемое значение

Текущий интерфейс конвертера.
## NEDConverter * getNEDConverter () const

Возвращает текущий интерфейс *[NEDConverter](../../../../../api/library/plugins/ig/api/class.nedconverter_cpp.md)*.
### Возвращаемое значение

Текущий интерфейс NEDConverter.
## LightController * getLightController () const

Возвращает текущий интерфейс контроллера света.
### Возвращаемое значение

Текущий интерфейс контроллера света.
## Meteo * getMeteo () const

Возвращает текущий интерфейс Meteo.
### Возвращаемое значение

Текущий интерфейс Meteo.
## SkyMap * getSkyMap () const

Возвращает текущий интерфейс SkyMap.
### Возвращаемое значение

Текущий интерфейс SkyMap.
## IGConfig * getConfig () const

Возвращает текущую конфигурацию IG как экземпляр класса [IGConfig](../../../../../api/library/plugins/ig/api/class.igconfig_cpp.md).
### Возвращаемое значение

Текущий интерфейс конфигурации IG.
## bool isDatabaseLoaded () const

Возвращает текущее значение, указывающее, загружена ли в данный момент какая-либо база данных.
### Возвращаемое значение

**true**, если в данный момент загружена какая-либо база данных; иначе **false**.
## int getCurrentDatabaseID () const

Возвращает текущий идентификатор загруженной в данный момент базы данных мира, хранящийся в файле конфигурации IG (`ig_config.xml`).
### Возвращаемое значение

Текущий идентификатор базы данных мира, или 0, если мир не загружен.
## float getIFps () const

Возвращает текущее значение обратного FPS (время в секундах, затраченное на завершение последнего кадра). Этот метод аналогичен [*Game::getIFps()*](../../../../../api/library/engine/class.game_cpp.md#getIFps_float), но более предпочтителен для многоканальных систем, так как реализует более точное вычисление времени кадра (включая периоды всплесков).
### Возвращаемое значение

Текущее значение обратного FPS (1/FPS) - время в секундах, затраченное на завершение последнего кадра.
## void setFreeze ( bool freeze )

Задаёт новое значение, указывающее, приостановлено ли временно (на паузе) или возобновлено выполнение логики IG.
### Аргументы

- *bool* **freeze** - Установите **true**, чтобы включить паузу выполнения логики IG; **false** - чтобы отключить.

## bool isFreeze () const

Возвращает текущее значение, указывающее, приостановлено ли временно (на паузе) или возобновлено выполнение логики IG.
### Возвращаемое значение

**true**, если пауза выполнения логики IG включена; иначе **false**.
## bool isReady () const

Возвращает текущее значение, указывающее, подключились ли все Slave, ожидаемые IG.
### Возвращаемое значение

**true**, если все Slave, ожидаемые IG, подключились; иначе **false**.
## bool isMaster () const

Возвращает текущее значение, указывающее, является ли приложение IG Syncker-Master, либо работает в одиночном режиме без [Syncker](../../../../../code/plugins/syncker/index.md) вообще, либо является Syncker-Slave.
### Возвращаемое значение

true, если приложение IG является Syncker-Master либо работает в одиночном режиме без [Syncker](../../../../../code/plugins/syncker/index.md) вообще; false, если приложение IG является Syncker-Slave.
---

## void reloadConfig ( )

Перезагружает [IG Configuration file](../../../../../ig/config.md) (`ig_config.xml`).
## void reloadGeodetics ( )

Принудительно выполняет обновление данных геопривязки во время выполнения, что полезно для изменения проекции на лету.
## bool loadDatabase ( int database_id )

Загружает базу данных с указанным ID и устанавливает её для использования.
### Аргументы

- *int* **database_id** - ID используемой базы данных.

### Возвращаемое значение

true означает, что база данных с указанным ID успешно загружена; иначе false.
## void reloadDatabase ( )

***Console*:**`database_reload`Перезагружает текущую базу данных.
## void unloadDatabase ( )

Выгружает текущую базу данных.
## int getDatabaseID ( const char * world_name ) const

Возвращает идентификатор базы данных мира с указанным именем, хранящийся в файле конфигурации IG (`ig_config.xml`).
### Аргументы

- *const char ** **world_name** - Имя базы данных мира.

### Возвращаемое значение

Идентификатор указанной базы данных мира, или 0, если мир не загружен.
## const char * getDatabaseName ( int id ) const

Возвращает имя базы данных мира, хранящееся в файле конфигурации IG (`ig_config.xml`).
### Аргументы

- *int* **id** - Идентификатор базы данных мира.

### Возвращаемое значение

Имя базы данных мира.
## SymbolsController * getSymbolsController ( ) const

Возвращает интерфейс контроллера символов.
### Возвращаемое значение

Интерфейс контроллера символов.
## View * getView ( int view_id , bool auto_create )

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.view_cpp.md) указанного view.
### Аргументы

- *int* **view_id** - ID view.
- *bool* **auto_create** - true, чтобы автоматически создать view с указанным ID, если он ещё не существует; false - чтобы вернуть nullptr, если view не существует.

### Возвращаемое значение

Указатель на интерфейс view, если он существует; иначе - nullptr.
## void getViews ( Unigine:: Vector < View *> & views_ret ) const

Возвращает список всех существующих view (если они есть).
### Аргументы

- *Unigine::[Vector](../../../../../api/library/containers/vector/class.vector_cpp.md) < [View](../../../../../api/library/plugins/ig/api/class.view_cpp.md) *> &* **views_ret** - Вектор, содержащий все существующие view (если они есть).

## bool removeView ( int view_id )

Удаляет view с указанным ID.
### Аргументы

- *int* **view_id** - ID удаляемого view.

### Возвращаемое значение

true, если view с указанным ID успешно удалён; иначе - false.
## bool isViewExist ( int view_id ) const

Возвращает значение, указывающее, существует ли view с указанным ID.
### Аргументы

- *int* **view_id** - ID view.

### Возвращаемое значение

true, если view с указанным ID существует; иначе - false.
## ViewGroup * getViewGroup ( int group_id , bool auto_create )

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md) указанной группы view.
### Аргументы

- *int* **group_id** - ID группы view.
- *bool* **auto_create** - true, чтобы автоматически создать группу view с указанным ID, если она ещё не существует; false - чтобы вернуть nullptr, если группа view не существует.

### Возвращаемое значение

Указатель на интерфейс группы view, если он существует; иначе - nullptr.
## bool removeViewGroup ( int group_view_id )

Удаляет группу view с указанным ID.
### Аргументы

- *int* **group_view_id** - ID удаляемой группы view.

### Возвращаемое значение

true, если группа view с указанным ID успешно удалена; иначе - false.
## bool isViewGroupExist ( int group_view_id ) const

Возвращает значение, указывающее, существует ли группа view с указанным ID.
### Аргументы

- *int* **group_view_id** - ID группы view.

### Возвращаемое значение

true, если группа view с указанным ID существует; иначе - false.
## Entity * getEntity ( long long entity_id , bool auto_create = true )

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.entity_cpp.md) указанной сущности.
### Аргументы

- *long long* **entity_id** - ID сущности. > **Notice:** Значение должно быть [entity ID](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#getID_llong), а **не** [type ID](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#getType_llong).
- *bool* **auto_create** - true, чтобы автоматически создать сущность с указанным ID, если она ещё не существует; false - чтобы вернуть nullptr, если сущность не существует.

### Возвращаемое значение

Указатель на интерфейс сущности.
## bool removeEntity ( long long entity_id )

Удаляет сущность с указанным ID.
### Аргументы

- *long long* **entity_id** - ID удаляемой сущности. > **Notice:** Значение должно быть [entity ID](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#getID_llong), а **не** [type ID](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#getType_llong).

### Возвращаемое значение

true, если сущность с указанным ID успешно удалена; иначе - false.
## bool isEntityExist ( long long entity_id ) const

Возвращает значение, указывающее, существует ли сущность с указанным ID.
### Аргументы

- *long long* **entity_id** - ID сущности. > **Notice:** Значение должно быть [entity ID](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#getID_llong), а **не** [type ID](../../../../../api/library/plugins/ig/api/class.entity_cpp.md#getType_llong).

### Возвращаемое значение

true, если сущность с указанным ID существует; иначе - false.
## void getEntities ( Unigine:: Vector < Entity *> & entities_ret ) const

Заполняет список сущностей всеми существующими сущностями.
### Аргументы

- *Unigine::[Vector](../../../../../api/library/containers/vector/class.vector_cpp.md)<[Entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md) *> &* **entities_ret** - Список сущностей.

## Entity * findEntity ( const Ptr < Node > & node ) const

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.entity_cpp.md) сущности, представленной указанным узлом.
### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, для которого требуется найти сущность.

### Возвращаемое значение

Указатель на интерфейс сущности, если он существует; иначе - nullptr.
## long long findEntityType ( const char * type_name ) const

Возвращает ID типа сущности по его имени. ID и имя типа сущности определяют тип сущности, используемый для конкретного экземпляра, и задаются в [entity definition section](../../../../../ig/config.md#config_entities) конфигурационного файла IG следующим образом:
```xml
<entity_types>
	<entity id="111" name="b52">
	</entity>
</entity_types>

```


### Аргументы

- *const char ** **type_name** - Имя типа сущности.

### Возвращаемое значение

ID типа сущности.
## int findComponentID ( long long entity_type , const char * name ) const

Возвращает ID компонента с указанным именем, принадлежащего указанному типу сущности.
### Аргументы

- *long long* **entity_type** - ID типа сущности. > **Notice:** ID типа сущности определяется в [entity definition section](../../../../../ig/config.md#config_entities) конфигурационного файла IG.
- *const char ** **name** - Имя компонента.

### Возвращаемое значение

ID компонента.
## int findArticulatedPartID ( long long entity_type , const char * name ) const

Возвращает идентификатор сочленённой части по её имени и типу сущности, которой она принадлежит, хранящийся в файле конфигурации IG (`ig_config.xml`).
### Аргументы

- *long long* **entity_type** - [type identifier](../../../../../ig/config.md#typeid) сущности, указанный в файле конфигурации IG (`ig_config.xml`).
- *const char ** **name** - Имя сочленённой части, указанное в файле конфигурации IG (`ig_config.xml`).

### Возвращаемое значение

Идентификатор сочленённой части.
## bool getHatHot ( const Vec3 & geo_position , double & ret_hat , double & ret_hot , IGIntersection & ret_intersection ) const

Проверяет, есть ли что-либо в указанной геодезической позиции, и возвращает в указанные выходные переменные HAT/HOT, а также нормаль поверхности, точный объект, над которым выполнен запрос, пересечённую поверхность, мировые координаты точки пересечения и т.д.
### Аргументы

- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **geo_position** - Геодезическая позиция.
- *double &* **ret_hat** - Адрес для возвращаемого значения HAT.
- *double &* **ret_hot** - Адрес для возвращаемого значения HOT.
- *IGIntersection &* **ret_intersection** - [Information on intersection](../../../../../api/library/plugins/ig/api/class.igintersection_cpp.md) в указанной геодезической позиции, такая как точный объект, над которым выполнен запрос, пересечённая поверхность, мировые координаты точки пересечения и т.д.

### Возвращаемое значение

true, если в указанной геодезической позиции что-либо есть, иначе false.
## bool getIntersection ( const Vec3 & p0 , const Vec3 & p1 , int mask , Unigine:: Vector <IGIntersection> & ret ) const

Проверяет, пересекает ли луч с заданными точками что-либо.
### Аргументы

- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начало луча.
- *const [Vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **p1** - Точка вдоль луча.
- *int* **mask** - Маска пересечений.
- *Unigine::[Vector](../../../../../api/library/containers/vector/class.vector_cpp.md)<IGIntersection> &* **ret** - Вектор, содержащий [information on intersections](../../../../../api/library/plugins/ig/api/class.igintersection_cpp.md).

### Возвращаемое значение

true, если луч пересекает что-либо, иначе false.
## Water * getWater ( ) const

Возвращает интерфейс управления водой.
### Возвращаемое значение

Интерфейс управления водой.
## Unigine::Plugins::Syncker::Syncker * getSyncker ( ) const

Возвращает [Syncker Interface](../../../../../api/library/plugins/syncker/class.syncker_syncker_cpp.md).
### Возвращаемое значение

Указатель на интерфейс Syncker::Syncker.
## Unigine::Plugins::Syncker::Master * getSynckerMaster ( ) const

Возвращает [Syncker Master Interface](../../../../../api/library/plugins/syncker/class.syncker_master_cpp.md).
### Возвращаемое значение

Указатель на интерфейс Syncker::Master.
## Unigine::Plugins::Syncker::Slave * getSynckerSlave ( ) const

Возвращает [Syncker Slave Interface](../../../../../api/library/plugins/syncker/class.syncker_slave_cpp.md).
### Возвращаемое значение

Указатель на интерфейс Syncker::Slave.
## Ptr < Node > loadNode ( const char * file_path )

Загружает узел из указанного файла в мир на Master и всех Slave. Это сетевой аналог метода [loadNode()](../../../../../api/library/engine/class.world_cpp.md#loadNode_cstr_int_Node) класса *World*.
> **Notice:** Это безопасный аналог метода [Syncker](../../../../../api/library/plugins/syncker/index.md) [loadNode()](../../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#loadNode_cstr_uchar_Mat4_Node), который имеет внутреннюю проверку того, выполняется ли этот метод на master и запущен ли Syncker.


### Аргументы

- *const char ** **file_path** - Путь к файлу `*.node`.

### Возвращаемое значение

Загруженный узел или nullptr, если произошла ошибка.
## void syncNode ( const Ptr < Node > & node , unsigned char mask = 255 )

Включает синхронизацию параметров указанного узла по протоколу UDP. Узлы сцены по умолчанию не синхронизируются, этот метод используется для добавления конкретного узла в очередь синхронизации.
> **Notice:** Это безопасный аналог метода [Syncker](../../../../../api/library/plugins/syncker/index.md) [addSyncNode()](../../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#addSyncNode_Node_uchar_void), который имеет внутреннюю проверку того, выполняется ли этот метод на master и запущен ли Syncker. Если этот метод вызван на slave, он ничего не делает.


### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Синхронизируемый узел.
- *unsigned char* **mask** - Маска синхронизации.

## void synckerCreate ( const Ptr < Node > & node , unsigned char mask = 255 )

Синхронизирует создание указанного узла на всех Slave. Этот метод **следует вызывать после создания узла на Master**. Рекомендуется по возможности использовать метод [*loadNode()*](#loadNode_cstr_Node), так как этот подход **позволяет добавлять узлы всех типов**, в отличие от метода [*synckerCreate()*](#synckerCreate_Node_uchar_void), который поддерживает лишь ограниченное их количество.
> **Notice:** Это безопасный аналог метода [Syncker](../../../../../api/library/plugins/syncker/index.md) [createNode()](../../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#createNode_Node_uchar_bool), который имеет внутреннюю проверку того, выполняется ли этот метод на master и запущен ли Syncker. Если этот метод вызван на slave, он ничего не делает.


### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../../api/library/nodes/class.node_cpp.md)> &* **node** - Создаваемый узел.
- *unsigned char* **mask** - Маска синхронизации.

## void synckerDestroy ( const Ptr < Node > & in_node )

Синхронизирует удаление указанного узла (со всеми его дочерними узлами) на Master и всех Slave.
> **Notice:** Это безопасный аналог метода [Syncker](../../../../../api/library/plugins/syncker/index.md) [deleteNode()](../../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#deleteNode_Node_void), который имеет внутреннюю проверку того, выполняется ли этот метод на master и запущен ли Syncker. Если этот метод вызван на slave, он ничего не делает.


### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../../api/library/nodes/class.node_cpp.md)> &* **in_node** - Удаляемый узел.

## bool isSyncNode ( const Ptr < Node > & in_node ) const

Возвращает значение, указывающее, включена ли синхронизация указанного узла. С помощью этого метода можно быстро проверить, отслеживается ли узел Syncker (состояния узла передаются Slave по сети).
> **Notice:** Это безопасный аналог метода [Syncker](../../../../../api/library/plugins/syncker/index.md) [isSyncNode()](../../../../../api/library/plugins/syncker/class.syncker_master_cpp.md#isSyncNode_Node_bool), который имеет внутреннюю проверку того, выполняется ли этот метод на master и запущен ли Syncker. Если этот метод вызван на slave, он ничего не делает.


### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../../api/library/nodes/class.node_cpp.md)> &* **in_node** - Проверяемый узел.

### Возвращаемое значение

true, если синхронизация указанного узла включена; иначе false.
## bool checkEntityType ( long long entity_type ) const

Проверяет, поддерживается ли указанный тип сущности в IG.
### Аргументы

- *long long* **entity_type** - [type identifier](../../../../../ig/config.md#typeid) сущности

### Возвращаемое значение

true, если указанный тип сущности поддерживается, иначе false.
## void sendUserMessage ( unsigned char packet_code , const Ptr < Blob > & send_message )

Отправляет пользовательское сообщение с master на slave.
### Аргументы

- *unsigned char* **packet_code** - ID пакета.
- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Blob](../../../../../api/library/common/class.blob_cpp.md)> &* **send_message** - Пользовательское сообщение

## void * addOnUserMessageReceivedCallback ( uint8_t packet_code , Unigine:: CallbackBase1 < Unigine:: Blob Ptr >* callback )

Выполняет функцию колбэка при получении [user message](#sendUserMessage_uchar_Blob_void) от master.
### Аргументы

- *uint8_t* **packet_code** - ID пакета.
- *Unigine::[CallbackBase1](../../../../../api/library/common/callbacks/class.callbackbase1_cpp.md) <  Unigine::[Blob](../../../../../api/library/common/class.blob_cpp.md)Ptr >** **callback** - Указатель на колбэк. Функция колбэка должна иметь следующую сигнатуру: void (*Unigine::BlobPtr* ***blob**)

### Возвращаемое значение

ID подписчика колбэка. Этот ID можно использовать для [remove](#removeOnUserMessageReceivedCallback_void_ptr_bool) этого колбэка при необходимости.
## void removeOnUserMessageReceivedCallback ( void * subscriber )

Удаляет колбэк получения пользовательского сообщения для указанного подписчика.
### Аргументы

- *void ** **subscriber** - ID подписчика колбэка, указанный при его [adding](#addOnUserMessageReceivedCallback_uchar_CallbackBase1_ptr_void).

## void clearOnUserMessageReceivedCallbacks ( )

Очищает все [added](#addOnUserMessageReceivedCallback_uchar_CallbackBase1_ptr_void) колбэки получения пользовательского сообщения.
## Manager * get ( )

Возвращает [Manager](../../../../../api/library/plugins/ig/api/class.managerinterface_cpp.md).
### Возвращаемое значение

Указатель на [manager interface](../../../../../api/library/plugins/ig/api/class.managerinterface_cpp.md).
## void setDistanceScale ( float d )

Задаёт глобальный масштаб расстояния для всех параметров расстояния отрисовки: расстояние теней, расстояние источников света, расстояния LOD и т.д. (см. консольную команду [render_distance_scale](../../../../../code/console/index.md#render_distance_scale)) и для компонента IG Simplifier. Компонент Simplifier может помочь оптимизировать отрисовку ваших сущностей. При назначении сущности он позволяет определить, какие части её модели можно пренебречь начиная с определённых уровней расстояния (например, скрыть закрылки, элероны и рули на 1 км, двигатели на 5 км и т.д.) и какие заменители можно использовать для представления сущности на большом расстоянии (например, мигающий строб-маяк, когда самолёт представляет собой всего лишь точку на экране).
> **Notice:** Этот метод вызывает [*setDistanceScale()*](../../../../../api/library/rendering/class.render_cpp.md#setDistanceScale_float_void) класса *Render*.


### Аргументы

- *float* **d** - Глобальный масштаб расстояния отрисовки и компонента Simplifier (менеджер LOD IG).

## void setAdaptiveQualitySystemMode ( int mode )

Задаёт новый режим системы Adaptive Quality. Эта система обеспечивает автоматическую корректировку уровней детализации в реальном времени в зависимости от текущей производительности ([render_distance_scale](../../../../../code/console/index.md#render_distance_scale) и simplifier_distance_scale).
### Аргументы

- *int* **mode** - Задаваемый режим системы Adaptive Quality. Одно из следующих значений:

  - 0 - корректировка качества в реальном времени отключена
  - 1 - только режим деградации (качество изображения снижается, если производительность падает)
  - 2 - автоматическая корректировка в реальном времени (качество изображения снижается при низкой производительности и повышается при её увеличении)

## void destroyObjects ( )

Уничтожает все [entities](../../../../../api/library/plugins/ig/api/class.entity_cpp.md), [view](../../../../../api/library/plugins/ig/api/class.view_cpp.md) и [view groups](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md).
## void setSlaveViewByName ( const char * slave_name , int view_id )

Задаёт view с указанным ID для использования указанным Slave (доступно только для Master IG).
### Аргументы

- *const char ** **slave_name** - Имя Slave (-computer_name "").
- *int* **view_id** - ID view, задаваемого как текущий для указанного Slave.

## void setSlaveView ( int index , int view_id )

Задаёт view с указанным ID для использования определённым Slave по его индексу (доступно только для Master IG).
### Аргументы

- *int* **index** - Индекс Slave в диапазоне от 0 до [total numer of Slaves](#getNumSlaves_int).
- *int* **view_id** - ID view, задаваемого как текущий для указанного Slave.

## int getSlaveViewByName ( const char * slave_name ) const

Возвращает текущий ID view, используемого определённым Slave, по его имени.
### Аргументы

- *const char ** **slave_name** - Имя Slave.

### Возвращаемое значение

ID view, используемого Slave с указанным именем.
## int getSlaveView ( int slave_index ) const

Возвращает текущий ID view, используемого определённым Slave, по его индексу (доступно только для Master IG).
### Аргументы

- *int* **slave_index** - Индекс Slave в диапазоне от 0 до [total numer of Slaves](#getNumSlaves_int).

### Возвращаемое значение

ID view, используемого Slave с указанным индексом.
## void clearInterpolationData ( )

Очищает все данные интерполяции для всех сущностей.
## Plugins::Geodetics::Transformer * getGeodeticsTransformer ( ) const

Возвращает указатель на экземпляр класса [Geodetics::Transformer](../../../../../api/library/geodetics/geodetics_plugin/class.transformer_cpp.md), если загружен плагин [Geodetics](../../../../../code/plugins/geodetics/index.md). Этот класс используется для преобразования геодезических координат (широта, долгота и высота) в 3D-позицию мира и обратно.
## int getNumSlaves ( ) const

Возвращает общее количество Slave (доступно только для Master IG).
### Возвращаемое значение

Общее количество Slave IG.
## const char * getSlaveName ( int index ) const

Возвращает имя Slave по его индексу (доступно только для Master IG).
### Аргументы

- *int* **index** - Индекс Slave.

### Возвращаемое значение

Имя Slave с указанным индексом.
## const char * getSynckerName ( ) const

Возвращает текущее имя хоста IG.
### Возвращаемое значение

Текущее имя хоста IG.
## void setDebugMode ( IG::Manager::DEBUG_MODE mode , bool enabled )

Задаёт значение, указывающее, включён ли указанный [Debug mode](../../../../../ig/debug/index.md). Этот режим позволяет инспектировать приложение IG во время выполнения
### Аргументы

- *IG::Manager::DEBUG_MODE* **mode** - Тип режима Debug. Одно из значений [DEBUG_MODE_*](#DEBUG_MODE).
- *bool* **enabled** - true - чтобы включить указанный [Debug mode](../../../../../ig/debug/index.md); false - чтобы отключить.

## bool isDebugMode ( IG::Manager::DEBUG_MODE mode ) const

Возвращает значение, указывающее, включён ли указанный [Debug mode](../../../../../ig/debug/index.md). Этот режим позволяет инспектировать приложение IG во время выполнения
### Аргументы

- *IG::Manager::DEBUG_MODE* **mode** - Тип режима Debug. Одно из значений [DEBUG_MODE_*](#DEBUG_MODE).

### Возвращаемое значение

true, если указанный режим Debug IG включён; иначе false.
## float calcDebugScale ( float v ) const

Возвращает фактический масштаб элементов визуализатора [Debug](../../../../../ig/debug/index.md), вычисленный для указанного значения на основе текущего [type of dimensions](#setDebugScreenspace_int_void) (мир/экран) и текущего значения [debug scale](#setDebugScale_float_void).
### Аргументы

- *float* **v** - Начальное значение масштаба.

### Возвращаемое значение

Фактический масштаб элементов визуализатора [Debug](../../../../../ig/debug/index.md), вычисленный для указанного значения. Масштаб вычисляется на основе текущего значения [debug scale](#setDebugScale_float_void).
## void * addOnCreateViewCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую при создании нового [view](../../../../../api/library/plugins/ig/api/class.view_cpp.md). Сигнатура функции колбэка следующая:
```text
void(View *)
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Может использоваться для удаления добавленного колбэка через метод *[removeOnCreateViewCallback()](#removeOnCreateViewCallback_void_ptr_void)*.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

### Возвращаемое значение

ID последнего добавленного колбэка Create View, если колбэк был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnCreateViewCallback_void_ptr_void) этого колбэка при необходимости.
## void removeOnCreateViewCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых при создании нового [view](../../../../../api/library/plugins/ig/api/class.view_cpp.md).
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnCreateViewCallbacks ( )

Очищает все [added](#addOnCreateViewCallback_void_ptr_CallbackBase_ptr_void) колбэки Create View.
## void * addOnCreateViewGroupCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую при создании нового [view](../../../../../api/library/plugins/ig/api/class.view_cpp.md). Сигнатура функции колбэка следующая:
```text
void(ViewGroup *)
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Can be used to remove the added callback via the *[removeOnCreateViewGroupCallback()](#removeOnCreateViewGroupCallback_void_ptr_void)* method.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

## void removeOnCreateViewGroupCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых при создании новой [view groups](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md).
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnCreateViewGroupCallbacks ( )

Очищает все [added](#addOnCreateViewGroupCallback_void_ptr_CallbackBase_ptr_void) колбэки Create ViewGroup.
## void addOnCreateEntityCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую при создании новой [entities](../../../../../api/library/plugins/ig/api/class.entity_cpp.md). Сигнатура функции колбэка следующая:
```text
void(IG::ICollisionVolume *volume, Unigine::ContactPtr contact, int contacted_entity, int contacted_volume)
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Can be used to remove the added callback via the *[removeOnCreateEntityCallback()](#removeOnCreateEntityCallback_void_ptr_void)* method.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

## void removeOnCreateEntityCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых при создании новой [entities](../../../../../api/library/plugins/ig/api/class.entity_cpp.md).
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnCreateEntityCallbacks ( )

Очищает все [added](#addOnCreateEntityCallback_void_ptr_CallbackBase_ptr_void) колбэки Create Entity.
## void addOnCollisionVolumeDetectedCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую при обнаружении пересечения с [collision volume](../../../../../api/library/plugins/ig/api/class.collisionvolume_cpp.md). Сигнатура функции колбэка следующая:
```text
void(IG::ICollisionVolume *volume, Unigine::ContactPtr contact, int contacted_entity, int contacted_volume)
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Can be used to remove the added callback via the *[removeOnCollisionVolumeDetectedCallback()](#removeOnCollisionVolumeDetectedCallback_void_ptr_void)* method.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

## void removeOnCollisionVolumeDetectedCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых при обнаружении пересечения с [collision volume](../../../../../api/library/plugins/ig/api/class.collisionvolume_cpp.md).
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnCollisionVolumeDetectedCallbacks ( )

Очищает все [added](#addOnCollisionVolumeDetectedCallback_void_ptr_CallbackBase_ptr_void) колбэки CollisionVolume Detected.
## void addOnCollisionSegmentDetectedCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую при обнаружении пересечения с [collision segment](../../../../../api/library/plugins/ig/api/class.collisionsegment_cpp.md). Сигнатура функции колбэка следующая:
```text
void(IG::ICollisionSegment *segment, Unigine::ObjectPtr object, Unigine::WorldIntersectionPtr intersection)
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Can be used to remove the added callback via the *[removeOnCollisionSegmentDetectedCallback()](#removeOnCollisionSegmentDetectedCallback_void_ptr_void)* method.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

## void removeOnCollisionSegmentDetectedCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых при обнаружении пересечения с [collision segment](../../../../../api/library/plugins/ig/api/class.collisionsegment_cpp.md).
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnCollisionSegmentDetectedCallbacks ( )

Очищает все [added](#addOnCollisionSegmentDetectedCallback_void_ptr_CallbackBase_ptr_void) колбэки CollisionSegment Detected.
## void addOnIGReadyCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую, когда все Slave, ожидаемые IG, подключены. Сигнатура функции колбэка следующая:
```text
void()
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Can be used to remove the added callback via the *[removeOnIGReadyCallback()](#removeOnIGReadyCallback_void_ptr_void)* method.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

## void removeOnIGReadyCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых, когда все Slave, ожидаемые IG, подключены.
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnIGReadyCallbacks ( )

Очищает все [added](#addOnIGReadyCallback_void_ptr_CallbackBase_ptr_void) колбэки IG Ready.
## void addOnSlaveConnectedCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую при подключении нового Slave. Сигнатура функции колбэка следующая:
```text
void(int slave_index, const char * slave_name)
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Can be used to remove the added callback via the *[removeOnSlaveConnectedCallback()](#removeOnSlaveConnectedCallback_void_ptr_void)* method.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

## void removeOnSlaveConnectedCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых при подключении нового Slave.
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnSlaveConnectedCallbacks ( )

Очищает все [added](#addOnSlaveConnectedCallback_void_ptr_CallbackBase_ptr_void) колбэки Slave Connected.
## void addOnSlaveDisconnectedCallback ( void * subscriber , CallbackBase * callback )

Добавляет функцию колбэка, выполняемую при отключении Slave. Сигнатура функции колбэка следующая:
```text
void(int slave_index)
```


### Аргументы

- *void ** **subscriber** - Подписчик колбэка. Can be used to remove the added callback via the *[removeOnSlaveDisconnectedCallback()](#removeOnSlaveDisconnectedCallback_void_ptr_void)* method.
- *[CallbackBase](../../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Выполняемая функция колбэка.

## void removeOnSlaveDisconnectedCallback ( void * subscriber )

Удаляет функцию колбэка для указанного подписчика из списка колбэков, выполняемых при отключении Slave.
### Аргументы

- *void ** **subscriber** - Подписчик колбэка.

## void clearOnSlaveDisconnectedCallbacks ( )

Очищает все [added](#addOnSlaveDisconnectedCallback_void_ptr_CallbackBase_ptr_void) колбэки Slave Disconnected.
## void setPropertyWarningEnabled ( bool v )

Задаёт значение, указывающее, следует ли отображать в консоли предупреждения, связанные со свойствами. Это удобный метод, который может быть полезен при работе с компонентами C#.
### Аргументы

- *bool* **v** - true, чтобы отображать предупреждения, связанные со свойствами; false, чтобы отключить их.
