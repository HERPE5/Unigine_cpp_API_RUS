# Unigine.SplineSegment Class (CPP)

**Header:** #include <UnigineWorlds.h>


Этот класс используется для управления отдельными сегментами [world spline graph](../../../api/library/worlds/class.worldsplinegraph_cpp.md).


## SplineSegment Class

### Методы класса

---

## void setStartPoint ( const Ptr < SplinePoint > & point )

Задаёт указанную точку сплайна в качестве начальной точки сегмента.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **point** - [Spline point](../../../api/library/worlds/class.splinepoint_cpp.md), задаваемая в качестве начальной точки сегмента.

## Ptr < SplinePoint > getStartPoint ( ) const

Возвращает текущую начальную точку сегмента.
### Возвращаемое значение

Начальная точка сегмента.
## void setEndPoint ( const Ptr < SplinePoint > & point )

Задаёт указанную точку сплайна в качестве конечной точки сегмента.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **point** - [Spline point](../../../api/library/worlds/class.splinepoint_cpp.md), задаваемая в качестве конечной точки сегмента.

## Ptr < SplinePoint > getEndPoint ( ) const

Возвращает текущую конечную точку сегмента.
### Возвращаемое значение

Конечная точка сегмента.
## void setStartTangent ( const Math::vec3& tangent )

Задаёт координаты касательной для начальной точки сегмента сплайна.
### Аргументы

- *const  Math::vec3&* **tangent** - Координаты касательной начальной точки.

## Math:: vec3 getStartTangent ( ) const

Возвращает текущие координаты касательной для начальной точки сегмента сплайна.
### Возвращаемое значение

Координаты касательной начальной точки.
## void setStartUp ( const Math::vec3& up )

Задаёт координаты ["up" vector](../../../api/library/worlds/class.worldsplinegraph_cpp.md#up) для начальной точки сегмента.
### Аргументы

- *const  Math::vec3&* **up** - Координаты вектора "up" начальной точки.

## Math:: vec3 getStartUp ( ) const

Возвращает текущие координаты ["up" vector](../../../api/library/worlds/class.worldsplinegraph_cpp.md#up) для начальной точки сегмента сплайна.
### Возвращаемое значение

Координаты вектора "up" начальной точки.
## void setEndTangent ( const Math::vec3& tangent )

Задаёт координаты касательной для конечной точки сегмента сплайна.
### Аргументы

- *const  Math::vec3&* **tangent** - Координаты касательной конечной точки.

## Math:: vec3 getEndTangent ( ) const

Возвращает текущие координаты касательной для конечной точки сегмента сплайна.
### Возвращаемое значение

Координаты касательной конечной точки.
## void setEndUp ( const Math::vec3& up )

Задаёт координаты ["up" vector](../../../api/library/worlds/class.worldsplinegraph_cpp.md#up) для конечной точки сегмента.
### Аргументы

- *const  Math::vec3&* **up** - Координаты вектора "up" конечной точки.

## Math:: vec3 getEndUp ( ) const

Возвращает текущие координаты ["up" vector](../../../api/library/worlds/class.worldsplinegraph_cpp.md#up) для конечной точки сегмента сплайна.
### Возвращаемое значение

Координаты вектора "up" конечной точки.
## void setEnabled ( bool enable , bool with_points = 1 )

Задаёт значение, указывающее, включён ли сегмент сплайна.
### Аргументы

- *bool* **enable** - **true**, чтобы включить сегмент сплайна, false, чтобы отключить.
- *bool* **with_points** - **true**, чтобы включить также все [points](../../../api/library/worlds/class.splinepoint_cpp.md), принадлежащие сегменту, false, чтобы включить только сам сегмент.

## bool isEnabled ( ) const

Возвращает значение, указывающее, включён ли сегмент сплайна.
### Возвращаемое значение

**true**, если сегмент сплайна включён; иначе **false**.
## Math:: Vec3 calcPoint ( float t ) const

Возвращает координаты точки в параметрически заданной позиции на сегменте (вдоль оси T).
![](../math/cubic_bezier.gif)


### Аргументы

- *float* **t** - Позиция точки на сегменте, заданная параметрически вдоль оси T (оси времени) в диапазоне **[0.0f, 1.0f]**.

### Возвращаемое значение

Координаты точки.
## Math:: vec3 calcTangent ( float t ) const

Возвращает координаты касательной для точки в параметрически заданной позиции на сегменте (вдоль оси T).
![](../math/cubic_bezier.gif)


### Аргументы

- *float* **t** - Позиция точки на сегменте, заданная параметрически вдоль оси T (оси времени) в диапазоне **[0.0f, 1.0f]**.

### Возвращаемое значение

Координаты касательной для точки в указанной позиции на сегменте.
## Math:: vec3 calcUpVector ( float t ) const

Возвращает координаты ["up" vector](../../../api/library/worlds/class.worldsplinegraph_cpp.md#up) для точки в параметрически заданной позиции на сегменте (вдоль оси T).
![](../math/cubic_bezier.gif)


### Аргументы

- *float* **t** - Позиция точки на сегменте, заданная параметрически вдоль оси T (оси времени) в диапазоне **[0.0f, 1.0f]**.

### Возвращаемое значение

Координаты вектора "up" для точки в указанной позиции на сегменте.
## float linearToParametric ( float l ) const

Выполняет преобразование линейной позиции в соответствии с длиной сегмента сплайна в параметрическую позицию (вдоль оси T).
![](../math/cubic_bezier.gif)


### Аргументы

- *float* **l** - Линейная позиция на сегменте сплайна в диапазоне [0.0f, 1.0f].

### Возвращаемое значение

Параметрическая позиция точки на сегменте вдоль оси T (оси времени) в диапазоне **[0.0f, 1.0f]**.
## float getLength ( ) const

Возвращает длину сегмента сплайна.
### Возвращаемое значение

Длина сегмента сплайна, в единицах.
## void clearSources ( )

Очищает список [source nodes](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) для сегмента сплайна.
## void assignSource ( const char * name , int forward_axis = 0 )

Назначает [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем сегменту сплайна и задаёт для него указанную ось направления.
### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).
- *int* **forward_axis** - Ось направления для исходного узла. Одна из переменных [FORWARD_](#FORWARD_X). По умолчанию используется ось **X**.

## void removeSource ( const char * name , int forward_axis = FORWARD_Y )

Удаляет [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем.
### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) для удаления.
- *int* **forward_axis** - Ось направления для исходного узла. Одна из переменных [FORWARD_](#FORWARD_X). По умолчанию используется ось **Y**.

## void getSources ( Vector < String > & OUT_sources ) const

Возвращает список [source nodes](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node), назначенных сегменту сплайна, и помещает его в указанный вектор.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **OUT_sources** - Список исходных узлов, назначенных сегменту сплайна. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void setSegmentMode ( const char * name , int segment_mode = SEGMENT_TILING )

Задаёт режим сегмента для [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем.
### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).
- *int* **segment_mode** - Режим для [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем. Одна из переменных [SEGMENT_*](#SEGMENT_STRETCH). По умолчанию используется [SEGMENT_TILING](#SEGMENT_TILING).

## int getSegmentMode ( const char * name ) const

Возвращает текущий режим сегмента для [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем.
### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

### Возвращаемое значение

Режим для [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем. Одна из переменных [SEGMENT_*](#SEGMENT_STRETCH). По умолчанию используется [SEGMENT_STRETCH](#SEGMENT_STRETCH).
## void setUVTiling ( const char * name , int enable_uv_tiling = 0 )

Задаёт значение, указывающее, включено ли тайлинг UV для текстур материала [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем.
### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).
- *int* **enable_uv_tiling** - **1**, чтобы включить тайлинг UV для текстур материала исходного узла, **0** - чтобы растягивать текстуры. Значение по умолчанию - **0**.

## int getUVTiling ( const char * name ) const

Возвращает значение, указывающее, включён ли тайлинг UV для текстур материала [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем.
### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

### Возвращаемое значение

**1**, если тайлинг UV для текстур материала [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) включён; иначе (текстуры растягиваются) **0**.
## void setAdaptiveAngleThreshold ( const char * name , float adaptive_angle_threshold = 1.0f )

Задаёт пороговое значение угла для разделения [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем. Если угол между касательными двух последовательных частей сегмента сплайна превышает это значение, узел будет разделён.
> **Notice:** Этот параметр используется только для режима [SEGMENT_ADAPTIVE](#SEGMENT_ADAPTIVE).


### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).
- *float* **adaptive_angle_threshold** - Пороговое значение угла для исходного узла с заданным именем, в градусах. Значение по умолчанию - **1.0f**.

## float getAdaptiveAngleThreshold ( const char * name ) const

Возвращает текущее пороговое значение угла для разделения [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем. Если угол между касательными двух последовательных частей сегмента сплайна превышает это значение, узел будет разделён.
> **Notice:** Этот параметр используется только для режима [SEGMENT_ADAPTIVE](#SEGMENT_ADAPTIVE).


### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

### Возвращаемое значение

Пороговое значение угла для исходного узла с заданным именем, в градусах. Значение по умолчанию - **1.0f**.
## void setGap ( const char * name , float gap = 0.0f )

Задаёт размер зазора между соседними копиями [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем, замощённого вдоль сегмента сплайна.
> **Notice:** Этот параметр используется только для режима [SEGMENT_TILING](#SEGMENT_TILING).


### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).
- *float* **gap** - Размер зазора, в единицах.

## float getGap ( const char * name ) const

Возвращает текущий размер зазора между соседними копиями [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с заданным именем, замощённого вдоль сегмента сплайна.
> **Notice:** Этот параметр используется только для режима [SEGMENT_TILING](#SEGMENT_TILING).


### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

### Возвращаемое значение

Текущий размер зазора, в единицах.
## void copy ( const Ptr < SplineSegment > & src , int copy_endpoints_data = 1 )

Копирует все параметры из указанного исходного сегмента сплайна.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md)> &* **src** - Исходный сегмент сплайна.
- *int* **copy_endpoints_data** - **1**, чтобы также скопировать все параметры [endpoints](../../../api/library/worlds/class.splinepoint_cpp.md) сегмента, 0 - использовать значения по умолчанию. Значение по умолчанию - 0.

## Ptr < SplineSegment > clone ( int clone_points = 0 )

Возвращает клон сегмента сплайна.
### Аргументы

- *int* **clone_points** - **1**, чтобы также скопировать все параметры [endpoints](../../../api/library/worlds/class.splinepoint_cpp.md) сегмента, 0 - использовать значения по умолчанию. Значение по умолчанию - 0.

### Возвращаемое значение

Клон сегмента сплайна.
## Ptr < WorldSplineGraph > getParent ( ) const

Возвращает узел *WorldSplineGraph*, которому принадлежит сегмент сплайна.
### Возвращаемое значение

Узел [*WorldSplineGraph*](../../../api/library/worlds/class.worldsplinegraph_cpp.md), которому принадлежит сегмент сплайна.
## int getNumSources ( ) const

Возвращает общее количество [source nodes](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node), назначенных данному сегменту сплайна.
### Возвращаемое значение

Общее количество исходных узлов, назначенных данному сегменту сплайна.
## int getNumNodes ( ) const

Возвращает общее количество узлов, размещённых вдоль сегмента сплайна.
### Возвращаемое значение

Общее количество узлов, размещённых вдоль сегмента сплайна.
## int getForwardAxis ( const char * name )

Возвращает ось направления, используемую для исходного узла с указанным именем.
### Аргументы

- *const char ** **name** - Имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

### Возвращаемое значение

Ось направления для исходного узла. Одна из переменных [FORWARD_](#FORWARD_X).
## Ptr < Node > getNode ( int index )

Возвращает узел, назначенный сегменту, по его номеру.
### Аргументы

- *int* **index** - Номер нужного узла в ряду узлов, размещённых вдоль сегмента, в диапазоне от 0 до [total number of nodes placed along the segment](#getNumNodes_int).

### Возвращаемое значение

Узел, размещённый вдоль сегмента в указанной позиции (номере).
