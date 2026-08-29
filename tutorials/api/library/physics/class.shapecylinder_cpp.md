# Unigine::ShapeCylinder Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Shape


Этот класс используется для создания коллизионной формы в форме [cylinder](../../../principles/physics/shapes/index.md#cylinder).


### См. также


UnigineScript samples:


-
-
-
-
-
-


## ShapeCylinder Class

### Методы класса

---

## static ShapeCylinderPtr create ( )

Конструктор. Создаёт новый cylinder с нулевым радиусом и нулевой высотой.
## static ShapeCylinderPtr create ( float radius , float height )

Конструктор. Создаёт новый cylinder с указанными размерами.
### Аргументы

- *float* **radius** - Радиус cylinder, в единицах.
- *float* **height** - Высота cylinder, в единицах.

## static ShapeCylinderPtr create ( const Ptr < Body > & body , float radius , float height )

Конструктор. Создаёт новый cylinder с указанными размерами и добавляет его к указанному телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Тело, которому будет принадлежать cylinder.
- *float* **radius** - Радиус cylinder, в единицах.
- *float* **height** - Высота cylinder, в единицах.

## void setHeight ( float height )

Задаёт высоту cylinder.
### Аргументы

- *float* **height** - Высота cylinder, в единицах.

## float getHeight ( )

Возвращает текущую высоту cylinder.
### Возвращаемое значение

Высота cylinder, в единицах.
## void setRadius ( float radius )

Задаёт радиус cylinder.
### Аргументы

- *float* **radius** - Радиус cylinder, в единицах.

## float getRadius ( )

Возвращает текущий радиус cylinder.
### Возвращаемое значение

Радиус cylinder, в единицах.
