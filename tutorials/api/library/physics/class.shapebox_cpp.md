# Unigine::ShapeBox Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Shape


Этот класс используется для создания коллизионной формы в форме [box](../../../principles/physics/shapes/index.md#box).


### См. также


UnigineScript samples:


-
-
-
-
-
-
-
-
-
-


## ShapeBox Class

### Методы класса

---

## static ShapeBoxPtr create ( )

Конструктор. Создаёт новый box с нулевыми размерами.
## static ShapeBoxPtr create ( const Math:: vec3 & size )

Конструктор. Создаёт новый box с указанными размерами.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размеры box, в единицах.

## static ShapeBoxPtr create ( const Ptr < Body > & body , const Math:: vec3 & size )

Конструктор. Создаёт новый box с указанными размерами и добавляет его к указанному телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Тело, которому будет принадлежать box.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размеры box, в единицах.

## void setSize ( const Math:: vec3 & size )

Задаёт размеры box.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размеры box, в единицах.

## Math:: vec3 getSize ( )

Возвращает текущие размеры box.
### Возвращаемое значение

Размеры box, в единицах.
