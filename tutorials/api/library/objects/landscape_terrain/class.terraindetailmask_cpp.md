# Unigine.TerrainDetailMask Class (CPP)

**Header:** #include <UnigineObjects.h>


Этот класс используется для управления детализирующими масками объекта [Landscape Terrain](../../../../objects/objects/terrain/landscape_terrain/index.md). Каждая детализирующая маска может иметь неограниченное количество [details](../../../../api/library/objects/landscape_terrain/class.terraindetail_cpp.md), определяющих её внешний вид. Детализирующие маски отрисовываются в соответствии с их порядком рендеринга (маска с наивысшим порядком отрисовывается поверх всех остальных).


## TerrainDetailMask Class

### Методы класса

---

## void setName ( const char * name )

Задаёт новое имя детализирующей маски.
### Аргументы

- *const char ** **name** - Новое имя детализирующей маски террейна.

## const char * getName ( )

Возвращает имя детализирующей маски.
### Возвращаемое значение

Текущее имя детализирующей маски.
## void setEnabled ( bool enabled )

Задаёт значение, указывающее, включена ли детализирующая маска террейна.
### Аргументы

- *bool* **enabled** - true, чтобы включить детализирующую маску террейна, false — чтобы отключить.

## bool isEnabled ( )

Возвращает значение, указывающее, включена ли детализирующая маска террейна.
### Возвращаемое значение

true, если детализирующая маска террейна включена; иначе false.
## int getRenderOrder ( )

Возвращает порядок рендеринга детализирующей маски. Порядок рендеринга масок можно изменить с помощью метода [*swapRenderOrder()*](#swapRenderOrder_TerrainDetailMask_void).
### Возвращаемое значение

Порядок рендеринга детализирующей маски в диапазоне **[0; 19]**.
## void swapRenderOrder ( const Ptr < TerrainDetailMask > & mask )

Меняет местами порядок рендеринга этой детализирующей маски с указанной.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[TerrainDetailMask](../../../../api/library/objects/landscape_terrain/class.terraindetailmask_cpp.md)> &* **mask** - Целевая детализирующая маска.

## Ptr < TerrainDetail > addDetail ( )

Добавляет новую деталь для этой маски.
### Возвращаемое значение

Новая деталь, добавленная для этой маски.
## int getNumDetails ( )

Возвращает количество деталей этой детализирующей маски.
### Возвращаемое значение

Количество деталей этой детализирующей маски.
## Ptr < TerrainDetail > getDetail ( int num )

Возвращает деталь по её индексу.
### Аргументы

- *int* **num** - Индекс детали.

### Возвращаемое значение

Деталь с указанным индексом (если она существует); иначе сообщается об ошибке нарушения assert.
## int isDetail ( const Ptr < TerrainDetail > & detail )

Проверяет, принадлежит ли указанная деталь этой детализирующей маске.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[TerrainDetail](../../../../api/library/objects/landscape_terrain/class.terraindetail_cpp.md)> &* **detail** - Проверяемая деталь.

### Возвращаемое значение

1, если указанная деталь террейна принадлежит этой маске; иначе 0.
## int findDetailIndex ( const char * name )

Возвращает индекс детали по её имени.
### Аргументы

- *const char ** **name** - Имя детали.

### Возвращаемое значение

Индекс детали с указанным именем (если она существует); иначе -1.
## Ptr < TerrainDetail > findDetail ( const char * name )

Возвращает деталь, привязанную к детализирующей маске, по её имени.
### Аргументы

- *const char ** **name** - Имя детали.

### Возвращаемое значение

Деталь с указанным именем (если она существует); иначе nullptr.
## void setDetailIndex ( const Ptr < TerrainDetail > & detail , int index )

Заменяет деталь с указанным индексом на заданную деталь.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[TerrainDetail](../../../../api/library/objects/landscape_terrain/class.terraindetail_cpp.md)> &* **detail** - Деталь, устанавливаемая вместо детали с указанным индексом.
- *int* **index** - Индекс детали, заменяемой указанной.

## int getDetailIndex ( const Ptr < TerrainDetail > & detail )

Возвращает индекс указанной детали.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[TerrainDetail](../../../../api/library/objects/landscape_terrain/class.terraindetail_cpp.md)> &* **detail** - Деталь, для которой нужно найти индекс.

### Возвращаемое значение

Индекс указанной детали (если она существует); иначе -1.
## void swapDetail ( int num_0 , int num_1 )

Меняет местами две детали с указанными индексами.
### Аргументы

- *int* **num_0** - Индекс первой детали.
- *int* **num_1** - Индекс второй детали.

## int getIndex ( )

Возвращает индекс детализирующей маски.
### Возвращаемое значение

Индекс детализирующей маски в диапазоне **[0; 19]**.
## void setDithering ( float dithering )

Задаёт новое значение дизеринга для детализирующей маски [landscape terrain](../../../../objects/objects/terrain/landscape_terrain/index.md). Дизеринг позволяет уменьшить графические артефакты при увеличенных значениях Mask Contrast, заданных для деталей. Это значение умножается на [global dither amount](../../../../api/library/rendering/class.render_cpp.md#setLandscapeTerrainMaskDithering_float_void).
### Аргументы

- *float* **dithering** - Новое значение дизеринга для детализирующей маски в диапазоне [0.0f; 1.0f].

## float getDithering ( ) const

Возвращает текущее значение дизеринга для детализирующей маски [landscape terrain](../../../../objects/objects/terrain/landscape_terrain/index.md). Дизеринг позволяет уменьшить графические артефакты при увеличенных значениях Mask Contrast, заданных для деталей. Это значение умножается на [global dither amount](../../../../api/library/rendering/class.render_cpp.md#setLandscapeTerrainMaskDithering_float_void).
### Возвращаемое значение

Текущее значение дизеринга для детализирующей маски в диапазоне [0.0f; 1.0f].
## void setDefaultValue ( float value )

Задаёт значение по умолчанию (фоновое) для маски.
### Аргументы

- *float* **value** - Значение, используемое для маски по умолчанию.

## float getDefaultValue ( ) const

Возвращает текущее значение по умолчанию (фоновое) для маски.
### Возвращаемое значение

Значение, используемое в настоящее время для маски по умолчанию.
## void setMaskByAlbedo ( const Math:: vec4 & albedo )

Задаёт новый цвет альбедо, используемый в качестве маски.
### Аргументы

- *const  Math::[vec4](../../../../api/library/math/class.vec4_cpp.md) &* **albedo** - Цвет альбедо, используемый в качестве маски, в виде четырёхкомпонентного вектора (R,G,B,A).

## Math:: vec4 getMaskByAlbedo ( ) const

Возвращает цвет альбедо, используемый в настоящее время в качестве маски.
### Возвращаемое значение

Цвет альбедо, используемый в настоящее время в качестве маски, в виде четырёхкомпонентного вектора (R,G,B,A).
