# Unigine.SplinePoint Class (CPP)

**Заголовочный файл:** #include <UnigineWorlds.h>


Этот класс используется для управления отдельными точками [world spline graph](../../../api/library/worlds/class.worldsplinegraph_cpp.md).


## SplinePoint Class

### Методы класса

---

## void setEnabled ( bool enable , bool with_segments = 1 )

Задаёт значение, указывающее, включена ли точка сплайна.
### Аргументы

- *bool* **enable** — **1** для включения точки сплайна, 0 для отключения.
- *bool* **with_segments** — используйте **true** для включения также всех [segments](../../../api/library/worlds/class.splinesegment_cpp.md), которым принадлежит точка, false для включения только самой точки сплайна.

## bool isEnabled ( ) const

Возвращает значение, указывающее, включена ли точка сплайна.
### Возвращаемое значение

**true**, если точка сплайна включена; в противном случае — **false**.
## void setPosition ( const Math::Vec3& position )

Задаёт новую позицию точки сплайна.
### Аргументы

- *const  Math::Vec3&* **position** — новая позиция для установки.

## Math:: Vec3 getPosition ( ) const

Возвращает текущую позицию точки сплайна.
### Возвращаемое значение

Текущая позиция точки сплайна.
## void getSplineSegments ( Vector < Ptr < SplineSegment > > & OUT_segments ) const

Возвращает список сегментов, которым принадлежит точка сплайна, и помещает их в указанный вектор элементов [SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md).
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md)> > &* **OUT_segments** — вектор для хранения списка сегментов, которым принадлежит точка сплайна. > **Примечание:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void clearSources ( )

Очищает список [source nodes](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) для точки сплайна.
## void assignSource ( const char * name )

Назначает [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с указанным именем для точки сплайна.
### Аргументы

- *const char ** **name** — имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

## void removeSource ( const char * name )

Удаляет [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с указанным именем.
### Аргументы

- *const char ** **name** — имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) для удаления.

## void getSources ( Vector < String > & OUT_sources ) const

Возвращает список [source nodes](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node), назначенных точке сплайна, и помещает его в указанный вектор.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **OUT_sources** — список исходных узлов, назначенных точке сплайна. > **Примечание:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void copy ( const Ptr < SplinePoint > & src )

Копирует все параметры из указанной исходной точки сплайна.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplinePoint](../../../api/library/worlds/class.splinepoint_cpp.md)> &* **src** — исходная точка сплайна.

## Ptr < SplinePoint > clone ( )

Возвращает клон точки сплайна.
### Возвращаемое значение

Клон точки сплайна.
## Ptr < WorldSplineGraph > getParent ( ) const

Возвращает узел *WorldSplineGraph*, которому принадлежит точка сплайна.
### Возвращаемое значение

Узел [*WorldSplineGraph*](../../../api/library/worlds/class.worldsplinegraph_cpp.md), которому принадлежит точка сплайна.
## int getNumSegments ( ) const

Возвращает общее количество [segments](../../../api/library/worlds/class.splinesegment_cpp.md), использующих данную точку сплайна.
### Возвращаемое значение

Общее количество сегментов, использующих данную точку сплайна.
## int getNumSources ( ) const

Возвращает общее количество [source nodes](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node), назначенных данной точке сплайна.
### Возвращаемое значение

Общее количество исходных узлов, назначенных данной точке сплайна.
## int getSourceNodeType ( const char * name ) const

Возвращает тип [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node) с указанным именем.
### Аргументы

- *const char ** **name** — имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

### Возвращаемое значение

Тип исходного узла.
## void setLinkVariant ( const char * name , int variant )

Задаёт вариант связи для исходного узла-развязки (junction) с указанным именем.
### Аргументы

- *const char ** **name** — имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).
- *int* **variant** — номер варианта связи для исходного узла-развязки.

## int getLinkVariant ( const char * name ) const

Возвращает текущий вариант связи для исходного узла-развязки с указанным именем.
### Аргументы

- *const char ** **name** — имя [source node](../../../api/library/worlds/class.worldsplinegraph_cpp.md#source_node).

### Возвращаемое значение

Номер варианта связи для исходного узла-развязки.
## int getLinkWorldPosition ( const Ptr < SplineSegment > & segment , Math:: Vec3 & position ) const

Получает текущую позицию связи (кости) исходного узла-развязки и помещает её в указанный вектор *position*.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SplineSegment](../../../api/library/worlds/class.splinesegment_cpp.md)> &* **segment** — сегмент сплайна, для которого требуется получить позицию соответствующей связи (кости) исходного узла-развязки.
- *Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** — вектор для хранения позиции связи (кости) исходного узла-развязки, соответствующей указанному [spline segment](../../../api/library/worlds/class.splinesegment_cpp.md).

### Возвращаемое значение

1, если текущая позиция связи (кости) исходного узла-развязки, соответствующая указанному сегменту сплайна, была получена успешно; в противном случае 0.
## Ptr < Node > getNode ( int index )

Возвращает узел, назначенный точке, по его номеру.
### Аргументы

- *int* **index** — номер нужного узла в ряду узлов, размещённых в этой точке, в диапазоне от 0 до [total number of nodes placed at the point](#getNumNodes_int).

### Возвращаемое значение

Узел, размещённый в этой точке в указанной позиции (номере).
## int getNumNodes ( ) const

Возвращает общее количество узлов, размещённых в этой точке сплайна.
### Возвращаемое значение

Общее количество узлов, размещённых в этой точке сплайна.
