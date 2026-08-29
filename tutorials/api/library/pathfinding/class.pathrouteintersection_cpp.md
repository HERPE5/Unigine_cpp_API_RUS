# Unigine::PathRouteIntersection Class (CPP)

**Header:** #include <UniginePathFinding.h>


## PathRouteIntersection Class

### Методы класса

## void setIndex ( int index )

Задаёт новый индекс пересечённого треугольника.
### Аргументы

- *int* **index** - Индекс пересечённого треугольника.

## int getIndex () const

Возвращает текущий индекс пересечённого треугольника.
### Возвращаемое значение

Текущий индекс пересечённого треугольника.
## void setPoint ( const Math:: Vec3 & point )

Задаёт новые координаты точки пересечения.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md)&* **point** - Координаты точки пересечения.

## Math:: Vec3 getPoint () const

Возвращает текущие координаты точки пересечения.
### Возвращаемое значение

Текущие координаты точки пересечения.
---

## static PathRouteIntersectionPtr create ( )

Конструктор PathRouteIntersection.
