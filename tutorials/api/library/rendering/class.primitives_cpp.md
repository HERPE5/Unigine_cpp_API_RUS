# Primitives Class (CPP)

**Header:** #include <UniginePrimitives.h>


Этот класс содержит методы, позволяющие создавать геометрические примитивы - [dynamic meshes](../../../api/library/rendering/class.meshdynamic_cpp.md) предопределённых форм, или добавлять поверхности предопределённых форм к уже существующим динамическим мешам.


### Пример использования


Ниже приведён небольшой пример, демонстрирующий, как создать примитив capsule и добавить к нему поверхность box:


```cpp
#include <UnigineObjects.h>
#include <UniginePrimitives.h>
// ...

// создаём примитив в форме capsule с заданными параметрами
ObjectMeshDynamicPtr MyPrimitive = Primitives::createCapsule(0.5f, 3, 16, 32);

// добавляем поверхность в форме box к созданной capsule
Primitives::addBoxSurface(MyPrimitive, vec3(2.0f), mat4_identity);

```


## Primitives Class

### Методы класса

---

## Ptr < ObjectMeshDynamic > createBox ( const Math:: vec3 & size )

Создаёт динамический меш в форме box.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размер box по осям X, Y и Z.

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## Ptr < ObjectMeshDynamic > createCapsule ( float radius , float height , int stacks = 16 , int slices = 32 )

Создаёт динамический меш в форме capsule.
### Аргументы

- *float* **radius** - Радиус capsule.
- *float* **height** - Высота capsule.
- *int* **stacks** - Количество stacks, делящих capsule радиально.
- *int* **slices** - Количество slices, делящих capsule горизонтально.

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## Ptr < ObjectMeshDynamic > createCylinder ( float radius , float height , int stacks = 1 , int slices = 32 )

Создаёт динамический меш в форме cylinder.
### Аргументы

- *float* **radius** - Радиус cylinder.
- *float* **height** - Высота cylinder.
- *int* **stacks** - Количество stacks, делящих cylinder радиально.
- *int* **slices** - Количество slices, делящих cylinder горизонтально.

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## Ptr < ObjectMeshDynamic > createDodecahedron ( float radius )

Создаёт динамический меш в форме dodecahedron.
### Аргументы

- *float* **radius** - Радиус dodecahedron.

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## Ptr < ObjectMeshDynamic > createIcosahedron ( float radius )

Создаёт динамический меш в форме icosahedron.
### Аргументы

- *float* **radius** - Радиус icosahedron.

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## Ptr < ObjectMeshDynamic > createPlane ( float width , float height , float step )

Создаёт динамический меш в форме plane. Она делится на равные квадраты, размер которых определяется заданным шагом.
### Аргументы

- *float* **width** - Ширина plane.
- *float* **height** - Высота plane.
- *float* **step** - Шаг подразделения поверхности (вертикально и горизонтально).

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## Ptr < ObjectMeshDynamic > createPrism ( float size_0 , float size_1 , float height , int sides = 8 )

Создаёт динамический меш в форме prism.
### Аргументы

- *float* **size_0** - Радиус окружности, описанной вокруг верхнего основания prism.
- *float* **size_1** - Радиус окружности, описанной вокруг нижнего основания prism.
- *float* **height** - Высота prism.
- *int* **sides** - Количество граней prism.

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## Ptr < ObjectMeshDynamic > createSphere ( float radius , int stacks = 16 , int slices = 32 )

Создаёт динамический меш в форме sphere.
### Аргументы

- *float* **radius** - Радиус sphere.
- *int* **stacks** - Количество stacks, делящих sphere радиально.
- *int* **slices** - Количество slices, делящих sphere горизонтально.

### Возвращаемое значение

Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
## void addBoxSurface ( Ptr < ObjectMeshDynamic > & object , const Math:: vec3 & size , const Math:: mat4 & transform )

Добавляет box заданного размера к ObjectMeshDynamic.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размер box по осям X, Y и Z.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации box.

## void addCapsuleSurface ( Ptr < ObjectMeshDynamic > & object , float radius , float height , const Math:: mat4 & transform , int stacks = 16 , int slices = 32 )

Добавляет capsule заданного размера к ObjectMeshDynamic. Stacks и slices определяют подразделение поверхности.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *float* **radius** - Радиус capsule.
- *float* **height** - Высота capsule вдоль центральной оси.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации capsule.
- *int* **stacks** - Количество stacks, делящих capsule радиально.
- *int* **slices** - Количество slices, делящих capsule горизонтально.

## void addCylinderSurface ( Ptr < ObjectMeshDynamic > & object , float radius , float height , const Math:: mat4 & transform , int stacks = 1 , int slices = 32 )

Добавляет cylinder заданного размера к ObjectMeshDynamic. Stacks и slices определяют подразделение поверхности.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *float* **radius** - Радиус cylinder.
- *float* **height** - Высота cylinder.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации cylinder.
- *int* **stacks** - Количество stacks, делящих cylinder радиально.
- *int* **slices** - Количество slices, делящих cylinder горизонтально.

## void addDodecahedronSurface ( Ptr < ObjectMeshDynamic > & object , float radius , const Math:: mat4 & transform )

Добавляет dodecahedron (многогранник с двенадцатью плоскими гранями) заданного размера к ObjectMeshDynamic.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *float* **radius** - Радиус dodecahedron.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## void addIcosahedronSurface ( Ptr < ObjectMeshDynamic > & object , float radius , const Math:: mat4 & transform )

Добавляет icosahedron (многогранник с двадцатью плоскими гранями) заданного размера к ObjectMeshDynamic.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *float* **radius** - Радиус icosahedron.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## void addPlaneSurface ( Ptr < ObjectMeshDynamic > & object , float width , float height , float step , const Math:: mat4 & transform )

Добавляет поверхность plane к динамическому мешу. Plane делится на равные квадраты, размер которых определяется заданным шагом.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *float* **width** - Ширина plane.
- *float* **height** - Высота plane.
- *float* **step** - Шаг подразделения поверхности (вертикально и горизонтально).
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации plane.

## void addPrismSurface ( Ptr < ObjectMeshDynamic > & object , float size_0 , float size_1 , float height , const Math:: mat4 & transform , int sides = 8 )

Добавляет prism к динамическому мешу.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *float* **size_0** - Радиус окружности, описанной вокруг верхнего основания prism.
- *float* **size_1** - Радиус окружности, описанной вокруг нижнего основания prism.
- *float* **height** - Размер вдоль центральной оси prism.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации prism.
- *int* **sides** - Количество граней prism.

## void addSphereSurface ( Ptr < ObjectMeshDynamic > & object , float radius , const Math:: mat4 & transform , int stacks = 16 , int slices = 32 )

Добавляет поверхность sphere к динамическому мешу. Stacks и slices определяют подразделение поверхности.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)> &* **object** - Экземпляр [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md).
- *float* **radius** - Радиус sphere.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.
- *int* **stacks** - Количество stacks, делящих sphere радиально.
- *int* **slices** - Количество slices, делящих sphere горизонтально.
