# Unigine::ShapeConvex Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Shape


Этот класс используется для создания коллизионной формы в форме [convex hull](../../../principles/physics/shapes/index.md#convex).


### См. также


UnigineScript samples:


-
-
-
-
-
-
-


## ShapeConvex Class

### Методы класса

---

## static ShapeConvexPtr create ( )

Конструктор. Создаёт новый пустой convex hull.
## static ShapeConvexPtr create ( const Ptr < Object > & object , int surface )

Конструктор. Создаёт convex hull для указанной поверхности объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, поверхность которого будет аппроксимирована.
- *int* **surface** - Номер поверхности, аппроксимируемой convex hull.

## static ShapeConvexPtr create ( const Ptr < Body > & body , const Ptr < Object > & object , int surface )

Конструктор. Создаёт convex hull для указанной поверхности объекта и добавляет его к указанному телу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body** - Тело, которому будет принадлежать convex hull.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, поверхность которого будет аппроксимирована.
- *int* **surface** - Номер поверхности, аппроксимируемой convex hull.

## int setObject ( const Ptr < Object > & object , int surface , float error = 0.01 )

Задаёт поверхность объекта, для которой должен быть создан convex hull.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, поверхность которого будет аппроксимирована.
- *int* **surface** - Номер поверхности, аппроксимируемой convex hull. Если в функцию в качестве номера поверхности передано **-1**, convex hull создаётся для всех поверхностей меша. > **Notice:** Для динамического меша convex hull не создаётся для всех поверхностей.
- *float* **error** - Допустимая погрешность, используемая при создании convex hull. Это необязательный параметр.

### Возвращаемое значение

**1**, если convex hull успешно создан; иначе **0**.
