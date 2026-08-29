# Unigine.TerrainGlobalLods Class (CPP)

**Header:** #include <UnigineObjects.h>


Этот класс используется для управления группой [LOD](../../../objects/objects/terrain/terrain_global/index.md#lods) (уровней детализации) объекта [global terrain](../../../objects/objects/terrain/terrain_global/index.md).


## TerrainGlobalLods Class

### Методы класса

---

## int getDataFormat ( )

Возвращает значение, указывающее текущий формат изображения для данных тайла.
### Возвращаемое значение

Формат изображения данных тайла. Одно из значений [Image::FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1).
## int getDataType ( )

Возвращает значение, указывающее текущий формат изображения для данных тайла.
### Возвращаемое значение

Тип изображения данных тайла. Одно из значений [Image::IMAGE_*](../../../api/library/common/class.image_cpp.md#IMAGE_2D).
## int getMaskFormat ( )

Возвращает значение, указывающее текущий формат изображения для маски тайла.
### Возвращаемое значение

Формат изображения маски тайла. Одно из значений [Image::FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1).
## void setNumLayers ( int layers )

Задаёт количество слоёв группы LOD.
### Аргументы

- *int* **layers** - Количество слоёв.

## int getNumLayers ( )

Возвращает количество слоёв группы LOD.
### Возвращаемое значение

Количество слоёв.
## int getNumLods ( )

Возвращает общее количество LOD в группе.
### Возвращаемое значение

Общее количество LOD.
## int addLod ( )

Добавляет новый LOD.
### Возвращаемое значение

Индекс последнего добавленного LOD.
## void insertLod ( int num )

Вставляет новый LOD в указанную позицию.
### Аргументы

- *int* **num** - Позиция для вставки нового LOD.

## void removeLod ( int num )

Удаляет LOD с указанным номером.
### Аргументы

- *int* **num** - Номер LOD.

## void clearLods ( )

Удаляет все LOD.
## int fetch ( const BoundSphere & bs , const BoundBox & bb , int force = 0 )

Загружает данные всех LOD для тайлов в пределах указанного ограничивающего объёма и ограничивающей сферы.
### Аргументы

- *const [BoundSphere](../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const [BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий объём.
- *int* **force** - Флаг принудительной загрузки. Используйте 1, чтобы загружать файлы в любом случае; иначе 0. Значение по умолчанию: 0.

### Возвращаемое значение

**1**, если данные всех LOD успешно получены; иначе 0.
## int fetchData ( double x , double y , Pixel & ret_pixel , int layer , bool force )

Получает данные для точки террейна с указанными координатами и помещает их в заданную выходную структуру.
### Аргументы

- *double* **x** - Координата X точки на террейне.
- *double* **y** - Координата Y точки на террейне.
- *Pixel &* **ret_pixel** - Выходная [Pixel structure](../../../api/library/common/class.image_cpp.md#pixel) для хранения цвета пикселя.
- *int* **layer** - Номер слоя.
- *bool* **force** - Флаг принудительной загрузки. > **Notice:** Рекомендуется устанавливать этот флаг в 0, когда это возможно, чтобы избежать всплесков нагрузки.

  - Если указано 1, данные будут получены немедленно.
  - Если указано 0, операция будет поставлена в очередь в отдельном потоке.

### Возвращаемое значение

**1**, если данные для указанного пикселя успешно получены; иначе 0.
## int getType ( )

Возвращает тип LOD.
## const char * getName ( )

Возвращает имя группы LOD.
### Возвращаемое значение

Имя группы LOD.
## Ptr < TerrainGlobalLod > getLod ( int num )

Возвращает LOD с указанным номером.
### Аргументы

- *int* **num** - Номер LOD.

### Возвращаемое значение

Указатель на TerrainGlobalLod.
## String getVideoMemoryUsage ( )

Возвращает информацию об общем использовании видеопамяти для всех LOD в группе.
### Возвращаемое значение

Общее использование видеопамяти для всех LOD.
