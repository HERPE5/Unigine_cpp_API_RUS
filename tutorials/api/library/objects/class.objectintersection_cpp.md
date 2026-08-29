# ObjectIntersection Class (CPP)

**Header:** #include <UnigineObjects.h>


Этот класс используется для хранения результата пересечения объекта (координаты точки пересечения, а также индексы поверхности и экземпляра).


## ObjectIntersection Class

### Перечисления

## TYPE

| Name | Description |
|---|---|
| **OBJECT_INTERSECTION** = 0 | [ObjectIntersection](../../../api/library/objects/class.objectintersection_cpp.md) (хранит только точку пересечения, индексы поверхности и треугольника). |
| **OBJECT_INTERSECTION_NORMAL** = 1 | [ObjectIntersectionNormal](../../../api/library/objects/class.objectintersectionnormal_cpp.md) (хранит точку пересечения, индексы поверхности и треугольника + координаты нормали в точке пересечения). |
| **OBJECT_INTERSECTION_TEX_COORD** = 2 | [ObjectIntersectionTexCoord](../../../api/library/objects/class.objectintersectiontexcoord_cpp.md) (хранит точку пересечения, индексы поверхности и треугольника + координаты нормали и текстурные координаты в точке пересечения). |
| **NUM_OBJECT_INTERSECTIONS** = 3 | Количество типов пересечений объекта. |

### Методы класса

---

## static ObjectIntersectionPtr create ( )

Конструктор ObjectIntersection.
## void setIndex ( int index )

Задаёт новый номер треугольника пересечения.
### Аргументы

- *int* **index** - Номер треугольника пересечения.

## int getIndex ( ) const

Возвращает номер пересечённого треугольника.
### Возвращаемое значение

Номер пересечённого треугольника.
## void setInstance ( int instance )

Задаёт новый номер пересечённого экземпляра.
> **Notice:** Номер пересечённого экземпляра можно получить для следующих классов:
> - *[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)*
> - *[ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)*
> - *[ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)*


### Аргументы

- *int* **instance** - Номер пересечённого экземпляра.

## int getInstance ( ) const

Возвращает номер пересечённого экземпляра.
> **Notice:** Номер пересечённого экземпляра можно получить для следующих классов:
> - *[ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)*
> - *[ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)*
> - *[ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)*


### Возвращаемое значение

Номер пересечённого экземпляра.
## void setPoint ( const Math:: Vec3 & point )

Задаёт новые координаты точки пересечения.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки пересечения.

## Math:: Vec3 getPoint ( ) const

Возвращает координаты точки пересечения.
### Возвращаемое значение

Координаты точки пересечения.
## ObjectIntersection::TYPE getType ( ) const

Возвращает идентификатор типа пересечения объекта.
### Возвращаемое значение

[intersection type identifier](#OBJECT_INTERSECTION) объекта.
## const char * getTypeName ( ) const

Возвращает имя типа пересечения объекта.
### Возвращаемое значение

Имя типа пересечения объекта.
