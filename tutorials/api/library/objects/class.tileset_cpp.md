# Unigine.TileSet Class (CPP)

**Header:** #include <UnigineTileset.h>


Этот класс используется для управления обычным [tileset](../../../objects/objects/terrain/terrain_global/index.md#tiling) объекта ObjectTerrainGlobal. Tileset может содержать произвольное количество тайлов. Каждый тайл представлен следующими элементами:

- **Data** - изображение с данными тайла.
- **Mask** - одноканальное изображение, описывающее веса данных. > **Notice:** Если у тайла нет маски, все веса считаются равными 1.


## Tileset Class

### Методы класса

---

## int getImageType ( )

Возвращает числовой код типа изображения, используемого в tileset.
### Возвращаемое значение

Идентификатор типа изображения. См. переменные [FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1).
## int setTileData ( const Math:: ivec2 & tile_coord , const Ptr < Image > & data )

Задаёт данные для указанного тайла, копируя их из исходного изображения.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **data** - Исходное изображение, содержащее новые данные тайла, которые нужно задать.

### Возвращаемое значение

1, если данные тайла успешно заданы; иначе 0.
## int getTileData ( const Math:: ivec2 & tile_coord , Ptr < Image > & data , int force = 1 )

Копирует данные указанного тайла в заданный экземпляр изображения.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).
- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **data** - Изображение, в которое копируются данные тайла.
- *int* **force** - Флаг принудительной загрузки. > **Notice:** Рекомендуется устанавливать этот флаг в 0, когда это возможно, чтобы избежать всплесков нагрузки.

  - Если указано 1, данные будут скопированы немедленно.
  - Если указано 0, операция копирования данных будет поставлена в очередь в отдельном потоке.

### Возвращаемое значение

1, если данные тайла успешно скопированы в изображение; иначе 0.
## int getTileDataState ( const Math:: ivec2 & tile_coord )

Возвращает состояние данных тайла с указанными координатами.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

Состояние данных тайла. Одно из значений [TILE_STATE_*](#TILE_STATE_NONE).
## int getTileResolution ( )

Возвращает разрешение тайла tileset.
### Возвращаемое значение

Разрешение тайла, в пикселях.
> **Notice:** Тайлы квадратные и имеют одинаковое количество пикселей по обоим измерениям.


## Math:: ivec2 getTileCoord ( const Math:: dvec2 & flat_position )

Возвращает координаты тайла, содержащего указанную точку на террейне.
### Аргументы

- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **flat_position** - Координаты точки на террейне (X, Y).

### Возвращаемое значение

Координаты тайла в tileset (X, Y).
## int reloadTileData ( const Math:: ivec2 & tile_coord )

Перезагружает данные тайла с указанными координатами из [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если данные тайла успешно загружены из [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md); иначе 0.
## Math:: dvec2 getTilePixelFlatPosition ( const Math:: ivec2 & tile_coord , const Math:: vec2 & pixel_coord , int use_half_pixel_offset = 0 )

Возвращает координаты точки на террейне (X, Y), соответствующей указанному пикселю заданного тайла.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **pixel_coord** - Координаты пикселя на тайле (X, Y).
- *int* **use_half_pixel_offset** - 1 для использования полупиксельного смещения; 0 для нулевого смещения.

### Возвращаемое значение

Координаты точки на террейне (X, Y).
## int isTileMaskLoaded ( const Math:: ivec2 & tile_coord )

Возвращает значение, указывающее, загружена ли маска для тайла с указанными координатами.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если маска для тайла загружена; иначе 0.
## Math:: vec2 getTilePixelCoord ( const Math:: dvec2 & flat_position , int use_half_pixel_offset = 0 )

Возвращает локальные координаты тайла для пикселя, соответствующего указанной точке на террейне. Чтобы определить тайл, содержащий этот пиксель, используйте метод [getTileCoord()](#getTileCoord_dvec2_ivec2).
### Аргументы

- *const  Math::[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **flat_position** - Координаты точки на террейне (X, Y).
- *int* **use_half_pixel_offset** - 1 для использования полупиксельного смещения; 0 для нулевого смещения.

### Возвращаемое значение

Локальные координаты пикселя на тайле (X, Y).
## int saveTile ( const Math:: ivec2 & tile_coord , int force = 0 )

Сохраняет изменения указанного тайла в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).
- *int* **force** - Флаг принудительной загрузки. > **Notice:** Рекомендуется устанавливать этот флаг в 0, когда это возможно, чтобы избежать всплесков нагрузки.

  - Если указано 1, изменения будут сохранены немедленно.
  - Если указано 0, операция сохранения будет поставлена в очередь в отдельном потоке.

### Возвращаемое значение

1, если изменения указанного тайла успешно сохранены в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md); иначе 0.
## int saveAll ( int force = 1 )

Сохраняет изменения всех тайлов в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
### Аргументы

- *int* **force** - Флаг принудительной загрузки. > **Notice:** Рекомендуется устанавливать этот флаг в 0, когда это возможно, чтобы избежать всплесков нагрузки.

  - Если указано 1, изменения будут сохранены немедленно.
  - Если указано 0, операция сохранения будет поставлена в очередь в отдельном потоке.

### Возвращаемое значение

1, если все изменения успешно сохранены в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md); иначе 0.
## float getLifeTime ( const Math:: ivec2 & tile_coord )

Возвращает текущее время жизни тайла. Этот параметр определяет, как долго указанный тайл будет храниться в RAM без обращения к нему.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

Время жизни тайла, в секундах.
## int getDataFormat ( )

Возвращает значение, указывающее текущий формат изображения для данных тайла.
### Возвращаемое значение

Формат изображения данных тайла. Одно из значений [Image::FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1).
## int getMaskFormat ( )

Возвращает значение, указывающее текущий формат изображения для маски тайла.
### Возвращаемое значение

Формат изображения маски тайла. Одно из значений [Image::FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1).
## const char * getPath ( )

Возвращает путь к [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
### Возвращаемое значение

Путь к [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
## int getTileMask ( const Math:: ivec2 & tile_coord , Ptr < Image > & mask , int force = 1 )

Копирует маску указанного тайла в заданный экземпляр изображения.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).
- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **mask** - Изображение, в которое копируется маска тайла.
- *int* **force** - Флаг принудительной загрузки. > **Notice:** Рекомендуется устанавливать этот флаг в 0, когда это возможно, чтобы избежать всплесков нагрузки.

  - Если указано 1, маска будет скопирована немедленно.
  - Если указано 0, операция копирования маски будет поставлена в очередь в отдельном потоке.

### Возвращаемое значение

1, если маска тайла успешно скопирована в изображение; иначе 0.
## int removeTileMask ( const Math:: ivec2 & tile_coord )

Удаляет маску тайла с указанными координатами из tileset.
> **Notice:** Этот метод не удаляет маску из [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).


### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1 if the mask of the tile was successfully removed from the tileset; otherwise, 0.
## int setTileMask ( const Math:: ivec2 & tile_coord , const Ptr < Image > & mask )

Задаёт маску для указанного тайла, копируя её из исходного изображения.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **mask** - Исходное изображение, содержащее новую маску тайла, которую нужно задать.

### Возвращаемое значение

1, если маска тайла успешно задана; иначе 0.
## int reloadTileMask ( const Math:: ivec2 & tile_coord )

Перезагружает маску тайла с указанными координатами из [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если маска тайла успешно загружена из [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md); иначе 0.
## float getTileDensity ( )

Возвращает плотность тайлов (количество пикселей на единицу) tileset.
### Возвращаемое значение

Плотность тайлов, в пикселях на единицу.
## int hasTileFileMask ( const Math:: ivec2 & tile_coord )

Возвращает значение, указывающее, есть ли у тайла с указанными координатами маска в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если у указанного тайла есть маска в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md); иначе 0.
## int hasTileMask ( const Math:: ivec2 & tile_coord )

Возвращает значение, указывающее, есть ли у тайла с указанными координатами маска в tileset.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если у указанного тайла есть маска в tileset; иначе 0.
## int isTileDataLoaded ( const Math:: ivec2 & tile_coord )

Возвращает значение, указывающее, загружены ли данные для тайла с указанными координатами.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если данные для тайла загружены; иначе 0.
## int getTileMaskState ( const Math:: ivec2 & tile_coord )

Возвращает состояние маски тайла с указанными координатами.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

Состояние маски тайла. Одно из значений [TILE_STATE_*](#TILE_STATE_NONE).
## float getTileSize ( )

Возвращает фактический размер тайла в tileset.
### Возвращаемое значение

Размер тайла, в единицах.
## int hasTile ( const Math:: ivec2 & tile_coord )

Возвращает значение, указывающее, существует ли тайл с указанными координатами в tileset.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если тайл с указанными координатами существует в tileset; иначе 0.
## int hasTileFile ( const Math:: ivec2 & tile_coord )

Возвращает значение, указывающее, существует ли тайл с указанными координатами в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если тайл с указанными координатами существует в [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md); иначе 0.
## int removeTile ( const Math:: ivec2 & tile_coord )

Удаляет тайл с указанными координатами из tileset.
> **Notice:** Этот метод не удаляет тайл из [tileset file](../../../api/library/objects/class.tilesetfile_cpp.md).


### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

1, если тайл успешно удалён из tileset; иначе 0.
## int setLifeTime ( const Math:: ivec2 & tile_coord , float seconds )

Задаёт время жизни для указанного тайла. Этот параметр определяет, как долго указанный тайл будет храниться в RAM без обращения к нему.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).
- *float* **seconds** - Время жизни тайла, в секундах.

### Возвращаемое значение

1, если время жизни для указанного тайла успешно задано; иначе 0.
## Math:: dvec2 getTileFlatPosition ( const Math:: ivec2 & tile_coord )

Возвращает координаты точки на террейне (X, Y), соответствующей левому верхнему углу указанного тайла.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **tile_coord** - Координаты тайла в tileset (X, Y).

### Возвращаемое значение

Координаты точки на террейне (X, Y).
## float fetchData ( const Math:: Vec2 & position , Math:: vec4 & result , int layer , bool force )

Получает данные для указанной точки на террейне и помещает их в выходной вектор.
### Аргументы

- *const  Math::[Vec2](../../../api/library/math/class.vec2_cpp.md) &* **position** - Координаты точки на террейне (X, Y).
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **result** - Выходной вектор для хранения данных, полученных для указанной точки.
- *int* **layer** - Номер слоя.
- *bool* **force** - Флаг принудительной загрузки. > **Notice:** Рекомендуется устанавливать этот флаг в 0, когда это возможно, чтобы избежать всплесков нагрузки.

  - Если указано 1, данные будут получены немедленно.
  - Если указано 0, операция будет поставлена в очередь в отдельном потоке.

### Возвращаемое значение

1.0f, если данные успешно получены; иначе 0.0f.
