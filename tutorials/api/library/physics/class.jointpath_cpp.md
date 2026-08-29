# Unigine::JointPath Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Joint


Path joint используется совместно с [BodyPath](../../../api/library/physics/class.bodypath_cpp.md): он присоединяет произвольное BodyRigid для перемещения вдоль его пути.


> **Notice:** *Path* — это сплайн, вдоль которого может перемещаться объект.


### См. также


UnigineScript samples:


-
-


### Пример


Следующий код иллюстрирует соединение [rigid body](../../../api/library/physics/class.bodyrigid_cpp.md) (b0) и [path body](../../../api/library/physics/class.bodypath_cpp.md) (b1) с помощью path joint.


```cpp
include <UniginePhysics.h>

/* .. */

JointPathPtr joint = JointPath::create(b0, b1);

// задаём линейное демпфирование, скорость и предел силы
joint->setLinearDamping(200.0f);
joint->setLinearVelocity(-100.0f);
joint->setLinearForce(1000.0f);

// задаём ориентацию тела относительно пути
joint->setRotation0(mat3(rotateZ(90.0f)));

// задаём количество итераций
joint->setNumIterations(4);

```


## JointPath Class

### Методы класса

## float getCurrentLinearVelocity () const

Возвращает текущую скорость линейного мотора.
### Возвращаемое значение

Текущая скорость присоединённого мотора, в единицах в секунду.
## void setWorldRotation ( const Math:: mat3 & rotation )

Задаёт новую матрицу поворота точки крепления в мировой системе координат.
### Аргументы

- *const  Math::[mat3](../../../api/library/math/class.mat3_cpp.md)&* **rotation** - Матрица поворота в мировом пространстве координат.

## Math:: mat3 getWorldRotation () const

Возвращает текущую матрицу поворота точки крепления в мировой системе координат.
### Возвращаемое значение

Текущая матрица поворота в мировом пространстве координат.
## void setRotation0 ( const Math:: mat3 & rotation0 )

Задаёт новую матрицу поворота точки крепления в системе координат соединённого rigid body.
### Аргументы

- *const  Math::[mat3](../../../api/library/math/class.mat3_cpp.md)&* **rotation0** - Матрица поворота точки крепления в системе координат соединённого rigid body.

## Math:: mat3 getRotation0 () const

Возвращает текущую матрицу поворота точки крепления в системе координат соединённого rigid body.
### Возвращаемое значение

Текущая матрица поворота точки крепления в системе координат соединённого rigid body.
## void setLinearVelocity ( float velocity )

Задаёт новую целевую скорость присоединённого линейного мотора.
### Аргументы

- *float* **velocity** - Целевая скорость в единицах в секунду.

## float getLinearVelocity () const

Возвращает текущую целевую скорость присоединённого линейного мотора.
### Возвращаемое значение

Текущая целевая скорость в единицах в секунду.
## void setLinearForce ( float force )

Задаёт новую максимальную силу присоединённого линейного мотора. **0** означает, что мотор не присоединён.
### Аргументы

- *float* **force** - Максимальная сила. Если указано отрицательное значение, вместо него используется **0**. **0** отсоединяет мотор.

## float getLinearForce () const

Возвращает текущую максимальную силу присоединённого линейного мотора. **0** означает, что мотор не присоединён.
### Возвращаемое значение

Текущая максимальная сила. Если указано отрицательное значение, вместо него используется **0**. **0** отсоединяет мотор.
## void setLinearDamping ( float damping )

Задаёт новое линейное затухание joint.
### Аргументы

- *float* **damping** - Линейное затухание. Если указано отрицательное значение, вместо него используется **0**.

## float getLinearDamping () const

Возвращает текущее линейное затухание joint.
### Возвращаемое значение

Текущее линейное затухание. Если указано отрицательное значение, вместо него используется **0**.
---

## static JointPathPtr create ( )

Конструктор. Создаёт path joint с точкой крепления в начале мировых координат.
## static JointPathPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 )

Конструктор. Создаёт path joint, соединяющий два указанных тела. Точка крепления размещается в центре rigid body, присоединённого к path body.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - [BodyRigid](../../../api/library/physics/class.bodyrigid_cpp.md), соединяемое с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - [BodyPath](../../../api/library/physics/class.bodypath_cpp.md), соединяемое с помощью joint.

## static JointPathPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 , const Math:: Vec3 & anchor )

Конструктор. Создаёт path joint, соединяющий два указанных тела, с точкой крепления, размещённой в указанных координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - [BodyRigid](../../../api/library/physics/class.bodyrigid_cpp.md), соединяемое с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - [BodyPath](../../../api/library/physics/class.bodypath_cpp.md), соединяемое с помощью joint.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **anchor** - Координаты точки крепления.
