# Unigine.ObjectTerrainGlobal Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для создания объекта [global terrain](../../../objects/objects/terrain/terrain_global/index.md), представляющего определённый фрагмент поверхности Земли на основе доступных ГИС-данных (высоты и изображения). Глобальный террейн отрисовывается с использованием предварительно сгенерированных [tilesets](../../../objects/objects/terrain/terrain_global/index.md#tiling), представляющих LOD-ы для различных [data layers](../../../objects/objects/terrain/terrain_global/index.md#terrain_structure) (высот, альбедо, нормалей и масок). Управление tileset-ами осуществляется через класс [TileSet](../../../api/library/objects/class.tileset_cpp.md). Данные tileset-ов хранятся в файлах tileset на диске, управление этими файлами осуществляется через класс [TileSetFile](../../../api/library/objects/class.tilesetfile_cpp.md)


### See Also


- Класс *[TerrainGlobalDetail](../../../api/library/objects/class.terrainglobaldetail_cpp.md)* для управления глобальным террейном через C++, C# или UnigineScript API
- Класс *[TerrainGlobalLod](../../../api/library/objects/class.terraingloballod_cpp.md)* для управления LOD-ом глобального террейна через C++, C# или UnigineScript API
- Класс *[TerrainGlobalLodHeight](../../../api/library/objects/class.terraingloballodheight_cpp.md)* для управления LOD-ом высот глобального террейна через C++, C# или UnigineScript API
- Класс *[TerrainGlobalLods](../../../api/library/objects/class.terraingloballods_cpp.md)* для управления группой LOD-ов глобального террейна через C++, C# или UnigineScript API
- Класс *[Tileset](../../../api/library/objects/class.tileset_cpp.md)* для управления данными tileset ObjectTerrainGlobal через C++, C# или UnigineScript API
- Класс *[TilesetFile](../../../api/library/objects/class.tilesetfile_cpp.md)* для управления файлами tileset ObjectTerrainGlobal через C++, C# или UnigineScript API
- Пример на UnigineScript


## ObjectTerrainGlobal Class

### Методы класса

---

## static ObjectTerrainGlobalPtr create ( )

Конструктор. Создаёт новый пустой объект глобального террейна со свойствами по умолчанию.
## void clear ( )

Очищает все данные террейна (LOD-ы, текстуры, детали, маски и т.д.).
## static int type ( )

Возвращает тип объекта.
### Возвращаемое значение

Идентификатор типа [ObjectTerrainGlobal](../../../api/library/nodes/class.node_cpp.md#OBJECT_TERRAIN_GLOBAL).
## Ptr < TerrainGlobalLods > getAlbedoLods ( )

Возвращает [group](../../../api/library/objects/class.terraingloballods_cpp.md) LOD-ов альбедо террейна.
### Возвращаемое значение

Группа LOD-ов альбедо террейна.
## Ptr < Texture > getAlbedoTextureArray ( ) const

Возвращает массив текстур альбедо.
### Возвращаемое значение

Массив текстур альбедо.
## void setAlbedoTextureArrayName ( const char * name )

Задаёт имя массива текстур альбедо.
### Аргументы

- *const char ** **name** - Имя массива текстур альбедо.

## const char * getAlbedoTextureArrayName ( ) const

Возвращает имя массива текстур альбедо.
### Возвращаемое значение

Имя массива текстур альбедо.
## int addDetail ( const char * name )

Добавляет новую деталь в вектор деталей террейна.
### Аргументы

- *const char ** **name** - Имя детали.

### Возвращаемое значение

Номер новой детали.
## int cloneDetail ( int num )

Клонирует деталь с указанным номером.
### Аргументы

- *int* **num** - Номер детали.

### Возвращаемое значение

Номер новой клонированной детали террейна.
## Ptr < TerrainGlobalDetail > getDetail ( int num )

Возвращает деталь террейна с указанным номером.
### Аргументы

- *int* **num** - Номер детали.

### Возвращаемое значение

[detail](../../../api/library/objects/class.terrainglobaldetail_cpp.md) террейна.
## void removeDetail ( int num )

Удаляет деталь с указанным номером.
### Аргументы

- *int* **num** - Номер детали.

## void swapDetail ( int num_0 , int num_1 )

Меняет местами две детали террейна.
### Аргументы

- *int* **num_0** - Номер первой детали.
- *int* **num_1** - Номер второй детали.

## void resizeDetails ( int size )

Изменяет размер вектора деталей террейна.
### Аргументы

- *int* **size** - Новый размер.

## int getNumDetails ( ) const

Возвращает общее количество деталей.
### Возвращаемое значение

Количество деталей.
## void setForceIntersection ( bool intersection )


Включает или отключает принудительную загрузку необходимых тайлов террейна для обеспечения корректного определения пересечений.


> **Notice:** - При включении этой опции производительность может значительно снизиться. Поэтому рекомендуется включать её, выполнять проверку пересечения, а затем снова отключать.
> - Рекомендуется делать два или более запросов пересечения, чтобы гарантированно получить нужный результат, так как в редких случаях принудительная загрузка тайлов может не дать 100% гарантии.


### Аргументы

- *bool* **intersection** - true для загрузки необходимых тайлов террейна для определения пересечений; иначе false. Значение по умолчанию: false.

## bool isForceIntersection ( ) const

Возвращает значение, указывающее, включена ли принудительная загрузка тайлов террейна для определения пересечений.
> **Notice:** Эта опция используется для включения принудительной загрузки тайлов террейна для обеспечения корректного определения пересечений.


### Возвращаемое значение

true, если принудительная загрузка тайлов террейна для определения пересечений включена; иначе false.
## int addMask ( const char * name )

Добавляет новую маску в вектор масок.
### Аргументы

- *const char ** **name** - Имя маски.

### Возвращаемое значение

Номер новой маски, если маска успешно добавлена; иначе -1.
## int cloneMask ( int num )

Клонирует маску с указанным номером.
### Аргументы

- *int* **num** - Номер маски.

### Возвращаемое значение

Номер новой клонированной маски.
## void removeMask ( int num )

Удаляет маску с указанным номером из вектора масок.
### Аргументы

- *int* **num** - Номер маски.

## void swapMask ( int num_0 , int num_1 )

Меняет местами две маски.
### Аргументы

- *int* **num_0** - Номер первой маски.
- *int* **num_1** - Номер второй маски.

## void replaceMasks ( const Vector < String > & names )

Заменяет список масок на указанный.
> **Notice:** Если маска, используемая какой-либо деталью, отсутствует в новом списке, такая деталь будет считаться не имеющей назначенной маски, в противном случае она сохранит свою маску.


### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **names** - Новый список масок.

## void resizeMasks ( int size )

Изменяет размер вектора масок.
### Аргументы

- *int* **size** - Новый размер.

## int getNumMasks ( ) const

Возвращает общее количество масок.
### Возвращаемое значение

Количество масок.
## Ptr < TerrainGlobalLods > getMaskLods ( )

Возвращает [group](../../../api/library/objects/class.terraingloballods_cpp.md) LOD-ов масок террейна.
### Возвращаемое значение

Группа LOD-ов масок террейна.
## void setMaskName ( int num , const char * name )

Задаёт имя маски с указанным номером.
### Аргументы

- *int* **num** - Номер маски.
- *const char ** **name** - Новое имя маски.

## const char * getMaskName ( int num ) const

Возвращает имя маски с указанным номером.
### Аргументы

- *int* **num** - Номер маски.

### Возвращаемое значение

Имя маски.
## Ptr < TerrainGlobalLods > getHeightLods ( )

Возвращает [group](../../../api/library/objects/class.terraingloballods_cpp.md) LOD-ов высот террейна.
### Возвращаемое значение

Группа LOD-ов высот террейна.
## Ptr < Texture > getHeightTextureArray ( ) const

Возвращает массив текстур высот.
### Возвращаемое значение

Массив текстур высот.
## void setHeightTextureArrayName ( const char * name )

Задаёт имя массива текстур высот.
### Аргументы

- *const char ** **name** - Имя массива текстур высот.

## const char * getHeightTextureArrayName ( ) const

Возвращает имя массива текстур высот.
### Возвращаемое значение

Имя массива текстур высот.
## Ptr < TerrainGlobalLods > getNormalLods ( )

Возвращает [group](../../../api/library/objects/class.terraingloballods_cpp.md) LOD-ов нормалей террейна.
### Возвращаемое значение

Группа LOD-ов нормалей террейна.
## Ptr < Texture > getNormalTextureArray ( ) const

Возвращает массив текстур нормалей.
### Возвращаемое значение

Массив текстур нормалей.
## void setNormalTextureArrayName ( const char * name )

Задаёт имя массива текстур нормалей.
### Аргументы

- *const char ** **name** - Имя массива текстур нормалей.

## const char * getNormalTextureArrayName ( ) const

Возвращает имя массива текстур нормалей.
### Возвращаемое значение

Имя массива текстур нормалей.
## int fetchTopologyData ( double x , double y , Math:: Vec3 & ret_point , Math:: vec3 & ret_normal , Math:: vec3 & ret_up , int force = 0 )

Возвращает данные топологии для указанной точки террейна.
### Аргументы

- *double* **x** - Координата X точки.
- *double* **y** - Координата Y точки.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_point** - Мировые координаты точки.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_normal** - Координаты нормали.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_up** - Координаты вектора "Up".
- *int* **force** - Флаг принудительной загрузки. Используйте 1, чтобы загружать файлы в любом случае; иначе 0. Значение по умолчанию: 0.

### Возвращаемое значение

**1**, если данные топологии успешно получены; иначе 0.
