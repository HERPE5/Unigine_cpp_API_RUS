# Unigine::ShapeCapsule Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Shape


Этот класс используется для создания коллизионной формы в форме [capsule](../../../principles/physics/shapes/index.md#capsule).


### См. также


UnigineScript samples:


-
-
-
-


## ShapeCapsule Class

### Методы класса

---

## static ShapeCapsulePtr create ( )

Конструктор. Создаёт новую capsule с нулевым радиусом и нулевой высотой.
## static ShapeCapsulePtr create ( float radius , float height )

Конструктор. Создаёт новую capsule с указанными размерами.
### Аргументы

- *float* **radius** - Радиус capsule, в единицах.
- *float* **height** - Высота capsule, в единицах.

## static ShapeCapsulePtr create ( const Ptr < Body > & body , float radius , float height )

Конструктор. Создаёт новую capsule с указанными размерами и добавляет её к указанному телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Тело, которому будет принадлежать capsule.
- *float* **radius** - Радиус capsule, в единицах.
- *float* **height** - Высота capsule, в единицах.

## void setHeight ( float height )

Задаёт высоту capsule.
### Аргументы

- *float* **height** - Высота capsule, в единицах.

## float getHeight ( )

Возвращает текущую высоту capsule.
### Возвращаемое значение

Высота capsule, в единицах.
## void setRadius ( float radius )

Задаёт радиус capsule.
### Аргументы

- *float* **radius** - Радиус capsule, в единицах.

## float getRadius ( )

Возвращает текущий радиус capsule.
### Возвращаемое значение

Радиус capsule, в единицах.
## Math:: Vec3 getBottomCap ( )

Возвращает координаты центра верхней полусферы capsule.
### Возвращаемое значение

Координаты центра верхней полусферы capsule.
## Math:: Vec3 getTopCap ( )

Возвращает координаты центра нижней полусферы capsule.
### Возвращаемое значение

Координаты центра нижней полусферы capsule.
