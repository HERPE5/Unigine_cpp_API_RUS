# Unigine.TerrainGlobalLod Class (CPP)

**Header:** #include <UnigineObjects.h>


Этот класс используется для управления одним [LOD](../../../objects/objects/terrain/terrain_global/index.md#lods) (уровнем детализации) объекта [global terrain](../../../objects/objects/terrain/terrain_global/index.md).


## TerrainGlobalLod Class

### Перечисления

## TYPE

| Name | Description |
|---|---|
| **TERRAIN_GLOBAL_LOD** = 0 | LOD альбедо, нормалей или маски деталей объекта [global terrain](../../../objects/objects/terrain/terrain_global/index.md). |
| **TERRAIN_GLOBAL_LOD_HEIGHT** = 1 | [height LOD](../../../api/library/objects/class.terraingloballodheight_cpp.md) объекта [global terrain](../../../objects/objects/terrain/terrain_global/index.md). Этот тип LOD используется для обнаружения столкновений и пересечений. |
| **NUM_TERRAIN_GLOBAL_LODS** = 2 | Общее количество типов LOD объекта [global terrain](../../../objects/objects/terrain/terrain_global/index.md). |

### Методы класса

---

## void setClearDistance ( float distance )

Задает дистанцию очистки LOD. Начиная с этой дистанции тайлы LOD удаляются из памяти.
### Аргументы

- *float* **distance** - Дистанция очистки, в единицах.

## float getClearDistance ( )

Возвращает дистанцию очистки LOD. Начиная с этой дистанции тайлы LOD удаляются из памяти.
### Возвращаемое значение

Текущая дистанция очистки, в единицах.
## void setEnabled ( bool enabled )

Включает или отключает LOD.
### Аргументы

- *bool* **enabled** - **1** для включения LOD, 0 для его отключения.

## bool isEnabled ( )

Возвращает значение, указывающее, включен ли LOD.
### Возвращаемое значение

**1**, если LOD включен; в противном случае 0.
## void setLoadDistance ( float distance )

Задает дистанцию загрузки для LOD. Начиная с этой дистанции тайлы LOD загружаются в память.
### Аргументы

- *float* **distance** - Дистанция загрузки, в единицах.

## float getLoadDistance ( )

Возвращает текущую дистанцию загрузки для LOD. Начиная с этой дистанции тайлы LOD загружаются в память.
### Возвращаемое значение

Текущая дистанция загрузки, в единицах.
## void setPath ( const char * path )

Задает путь к папке, в которой хранится LOD.
### Аргументы

- *const char ** **path** - Путь к папке, в которой хранится LOD.

## const char * getPath ( )

Возвращает путь к папке, в которой хранится LOD.
### Возвращаемое значение

Путь к папке, в которой хранится LOD.
## void setTileDensity ( float density )

Задает плотность тайлов LOD.
### Аргументы

- *float* **density** - Плотность тайлов LOD, в метрах на пиксель.

## float getTileDensity ( )

Возвращает текущую плотность тайлов LOD.
### Возвращаемое значение

Текущая плотность тайлов LOD, в метрах на пиксель.
## Ptr < Tileset > getTileset ( )

Возвращает [tileset](../../../api/library/objects/class.tileset_cpp.md) для LOD.
### Возвращаемое значение

[Tileset](../../../api/library/objects/class.tileset_cpp.md) LOD.
## void setViewportMask ( int mask )

Задает битовую маску для рендеринга в вьюпорт. LOD рендерится, если его маска совпадает с маской игрока.
### Аргументы

- *int* **mask** - Маска вьюпорта, целое значение, каждый бит которого представляет собой маску.

## int getViewportMask ( )

Возвращает текущую битовую маску для рендеринга в вьюпорт. LOD рендерится, если его маска совпадает с маской игрока.
### Возвращаемое значение

Маска вьюпорта, целое значение, каждый бит которого представляет собой маску.
## void setVisibleDistance ( float distance )

Задает дистанцию видимости. Начиная с этой дистанции тайлы LOD становятся видимыми.
### Аргументы

- *float* **distance** - Дистанция видимости, в единицах.

## float getVisibleDistance ( )

Возвращает текущую дистанцию видимости. Начиная с этой дистанции тайлы LOD становятся видимыми.
### Возвращаемое значение

Текущая дистанция видимости, в единицах.
## int renamePath ( const char * new_path )

Задает новый путь к папке, в которой хранится LOD.
### Аргументы

- *const char ** **new_path** - Новый путь, который нужно установить.

### Возвращаемое значение

**1**, если новый путь установлен успешно; в противном случае 0.
## void reload ( )

Перезагружает LOD.
## TerrainGlobalLod::TYPE getType ( )

Возвращает тип LOD. Этот метод используется для определения того, является ли он LOD высот, используемым для обнаружения столкновений и пересечений, или обычным LOD альбедо, нормалей или маски деталей.
### Возвращаемое значение

Тип LOD, одно из значений [TYPE](#TYPE).
## const char * getTypeName ( )

Возвращает имя типа глобального LOD террейна. Этот метод используется для определения того, является ли он LOD высот, используемым для обнаружения столкновений и пересечений, или обычным LOD альбедо, нормалей или маски деталей.
### Возвращаемое значение

Имя типа глобального LOD террейна. Одно из следующих значений:
- TerrainGlobalLod
- TerrainGlobalLodHeight
