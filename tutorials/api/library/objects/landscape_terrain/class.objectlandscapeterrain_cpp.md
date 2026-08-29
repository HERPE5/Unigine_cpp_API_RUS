# Unigine.ObjectLandscapeTerrain Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для создания объекта [Landscape Terrain](../../../../objects/objects/terrain/landscape_terrain/index.md) и управления им, а также его детализирующими масками.


### См. также


- C++ sample


## ObjectLandscapeTerrain Class

### Методы класса

---

## ObjectLandscapeTerrain ( )

Конструктор ObjectLandscapeTerrain.
## void setActiveTerrain ( bool enabled )

Задаёт значение, указывающее, активен ли landscape terrain.
### Аргументы

- *bool* **enabled** - true, чтобы сделать landscape terrain активным, false — чтобы сделать его неактивным.

## bool isActiveTerrain ( )

Возвращает значение, указывающее, активен ли landscape terrain.
### Возвращаемое значение

true, если landscape terrain активен; иначе false.
## void setIntersectionPrecision ( float begin )

Задаёт новое значение точности, используемое для обнаружения пересечений.
### Аргументы

- *float* **begin** - Точность обнаружения пересечений как доля максимальной точности в диапазоне [0; 1]. Значение по умолчанию: 0.5f. Максимальная точность определяется движком на основе данных вашего Landscape Terrain.

## float getIntersectionPrecision ( )

Возвращает текущее значение точности, используемое для обнаружения пересечений.
### Возвращаемое значение

Точность обнаружения пересечений как доля максимальной точности в диапазоне [0; 1]. Значение по умолчанию: 0.5f. Максимальная точность определяется движком на основе данных вашего Landscape Terrain.
## int getNumDetailMasks ( )

Возвращает общее количество детализирующих масок landscape terrain.
### Возвращаемое значение

Общее количество детализирующих масок landscape terrain.
## Ptr < TerrainDetailMask > getDetailMask ( int num )

Возвращает детализирующую маску по её индексу. Количество детализирующих масок фиксировано и равно 20.
### Аргументы

- *int* **num** - Индекс детализирующей маски в диапазоне **[0; 19]**.

### Возвращаемое значение

Детализирующая маска с указанным индексом.
## Ptr < TerrainDetailMask > getDetailMaskSortRender ( int num )

Возвращает детализирующую маску по её порядку рендеринга. Количество детализирующих масок фиксировано и равно 20, порядок рендеринга масок — от дальних к ближним.
### Аргументы

- *int* **num** - Порядок рендеринга детализирующей маски, в диапазоне **[0; 19]**.

### Возвращаемое значение

Детализирующая маска с указанным порядком рендеринга.
## Ptr < TerrainDetailMask > findDetailMask ( const char * name )

Возвращает номер дочерней детализирующей маски по её имени. Поиск выполняется только среди непосредственных дочерних элементов.
### Аргументы

- *const char ** **name** - Имя детализирующей маски.

### Возвращаемое значение

Детализирующая маска с указанным именем (если она существует); иначе nullptr.
## void getDetailMasks ( const Vector < Ptr < TerrainDetailMask > > & masks )

Формирует список всех детализирующих масок landscape terrain и помещает их в указанный буфер. Количество детализирующих масок фиксировано и равно 20.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[TerrainDetailMask](../../../../api/library/objects/landscape_terrain/class.terraindetailmask_cpp.md)> > &* **masks** - Буфер, в который помещается список детализирующих масок.

## void getDetailMasksSortRender ( const Vector < Ptr < TerrainDetailMask > > & masks )

Формирует список всех детализирующих масок landscape terrain в порядке их рендеринга (от дальних к ближним) и помещает их в указанный буфер. Количество детализирующих масок фиксировано и равно 20.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[TerrainDetailMask](../../../../api/library/objects/landscape_terrain/class.terraindetailmask_cpp.md)> > &* **masks** - Буфер, в который помещается список детализирующих масок.

## long long getLastStreamingFrame ( ) const

Возвращает номер кадра, в котором был выполнен последний коммит в *Virtual Texture*. Этот метод позволяет проверить, полностью ли загружены данные *Landscape Terrain* на текущий момент (*Virtual Texture* создана и последний коммит в неё уже применён).
```cpp
#include "AppWorldLogic.h"
#include <UnigineWorld.h>
#include <UnigineGame.h>

using namespace Unigine;
ObjectLandscapeTerrainPtr terrain;

int AppWorldLogic::init()
{
	terrain = checked_ptr_cast<ObjectLandscapeTerrain>(World::getNodeByName("ObjectLandscapeTerrain"));

	return 1;
}

int AppWorldLogic::update()
{
	if (!terrain.isValid())
		return 1;
	int64_t last_commit_frame = terrain->getLastStreamingFrame();
	if (last_commit_frame == -1)
	{
		Log::message("Virtual Texture ещё не создана\n");
		return 1;
		// ещё не готово
	}
	if ((Game::getFrame() - last_commit_frame) > 45)
	{
		Log::message("Обновление Virtual Texture завершено (все коммиты применены)\n");
		// ...
	}
	else
	{
		Log::message("Обновление Virtual Texture ожидается (commit_frame = %d)\n", last_commit_frame);
		// ...
	}
	return 1;
}


```


### Возвращаемое значение

Номер последнего кадра стриминга.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [ObjectLandscapeTerrain](../../../../api/library/nodes/class.node_cpp.md#OBJECT_LANDSCAPE_TERRAIN).
## size_t getVideoMemoryUsage ( )

## size_t getDetailVideoMemoryUsage ( )

## int getNumReloadTiles ( )

## int getNumReloadBounds ( )

## bool isReloading ( )

## bool isReloading ( const Math:: WorldBoundBox & bb )

### Аргументы

- *const  Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb**
