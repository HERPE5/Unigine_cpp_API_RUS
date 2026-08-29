# Unigine::ShapeSphere Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Shape


Этот класс используется для создания коллизионной формы в виде [sphere](../../../principles/physics/shapes/index.md#sphere).


### См. также


Примеры UnigineScript:


-
-
-
-
-
-


## ShapeSphere Class

### Методы класса

---

## static ShapeSpherePtr create ( )

Конструктор. Создаёт новую сферу с нулевым радиусом.
## static ShapeSpherePtr create ( float radius )

Конструктор. Создаёт новую сферу с заданным радиусом.
### Аргументы

- *float* **radius** - Радиус сферы в единицах.

## static ShapeSpherePtr create ( const Ptr < Body > & body , float radius )

Конструктор. Создаёт новую сферу с заданным радиусом и добавляет её к заданному телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Тело, которому будет принадлежать форма.
- *float* **radius** - Радиус сферы в единицах.

## void setRadius ( float radius )

Задаёт радиус сферы.
### Аргументы

- *float* **radius** - Радиус сферы в единицах.

## float getRadius ( )

Возвращает текущий радиус сферы.
### Возвращаемое значение

Радиус сферы в единицах.
## void setCenter ( const Math:: Vec3 & center )

Задаёт координаты центра сферы.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **center** - Координаты центра сферы.

## Math:: Vec3 getCenter ( )

Возвращает текущие координаты центра сферы.
### Возвращаемое значение

Текущие координаты центра сферы.
