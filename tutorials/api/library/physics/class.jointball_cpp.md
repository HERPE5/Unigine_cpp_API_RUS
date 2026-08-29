# Unigine::JointBall Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Joint


Этот класс используется для создания [ball joints](../../../principles/physics/joints/index.md#ball).


### Пример


Следующий код иллюстрирует соединение двух [bodies](../../../api/library/physics/class.body_cpp.md) (b0 и b1) с помощью ball joint.


```cpp
#include <UniginePhysics.h>

using namespace Unigine;
using namespace Unigine::Math;

/* .. */

JointBallPtr joint = JointBall::create(b0, b1);

// задаём координаты оси joint
joint->setWorldAxis(vec3(1.0f, 0.0f, 0.0f));

// задаём общие параметры ограничений joint
joint->setLinearRestitution(0.8f);
joint->setAngularRestitution(0.8f);
joint->setLinearSoftness(0.0f);
joint->setAngularSoftness(0.0f);

// задаём угловое затухание
joint->setAngularDamping(16.0f);

// задаём предел угла качания (swing), в градусах
joint->setAngularLimitAngle(30.0f);

// задаём пределы угла скручивания (twist), в градусах [-20; 20]
joint->setAngularLimitFrom(-20.0f);
joint->setAngularLimitTo(20.0f);

// задаём количество итераций
joint->setNumIterations(16);

```


### См. также


UnigineScript samples:


-
-
-
-
-
-
-


## JointBall Class

### Методы класса

## void setWorldAxis ( const Math:: vec3 & axis )

Задаёт новую ось joint. Ось joint вычисляется на основе осей соединённых тел.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis** - Ось joint.

## Math:: vec3 getWorldAxis () const

Возвращает текущую ось joint. Ось joint вычисляется на основе осей соединённых тел.
### Возвращаемое значение

Текущая ось joint.
## void setAngularLimitTo ( float to )

Задаёт новый верхний предел угла скручивания (twist). Предел скручивания определяет, насколько соединённое тело может скручиваться вокруг оси joint.
### Аргументы

- *float* **to** - Верхний предел угла скручивания, в градусах. Указанное значение ограничивается диапазоном **[-180; 180]**.

## float getAngularLimitTo () const

Возвращает текущий верхний предел угла скручивания. Предел скручивания определяет, насколько соединённое тело может скручиваться вокруг оси joint.
### Возвращаемое значение

Текущий верхний предел угла скручивания, в градусах. Указанное значение ограничивается диапазоном **[-180; 180]**.
## void setAngularLimitFrom ( float from )

Задаёт новый нижний предел угла скручивания (twist). Предел скручивания определяет, насколько соединённое тело может скручиваться вокруг оси joint.
### Аргументы

- *float* **from** - Нижний предел угла скручивания, в градусах. Указанное значение ограничивается диапазоном **[-180; 180]**.

## float getAngularLimitFrom () const

Возвращает текущий нижний предел угла скручивания. Предел скручивания определяет, насколько соединённое тело может скручиваться вокруг оси joint.
### Возвращаемое значение

Текущий нижний предел угла скручивания, в градусах. Указанное значение ограничивается диапазоном **[-180; 180]**.
## void setAngularLimitAngle ( float angle )

Задаёт новый предел угла качания (swing). Предел качания определяет, насколько соединённые тела могут отклоняться от оси joint.
### Аргументы

- *float* **angle** - Предел угла качания, в градусах. Указанное значение ограничивается диапазоном **[-180; 180]**. **0** означает отсутствие ограничения.

## float getAngularLimitAngle () const

Возвращает текущий предел угла качания. Предел качания определяет, насколько соединённые тела могут отклоняться от оси joint.
### Возвращаемое значение

Текущий предел угла качания, в градусах. Указанное значение ограничивается диапазоном **[-180; 180]**. **0** означает отсутствие ограничения.
## void setAngularDamping ( float damping )

Задаёт новое угловое затухание joint.
### Аргументы

- *float* **damping** - Угловое затухание. Если указано отрицательное значение, вместо него используется **0**.

## float getAngularDamping () const

Возвращает текущее угловое затухание joint.
### Возвращаемое значение

Текущее угловое затухание. Если указано отрицательное значение, вместо него используется **0**.
## void setAxis0 ( const Math:: vec3 & axis0 )

Задаёт новую ось первого соединённого тела.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis0** - Ось первого тела. Указанный вектор будет нормализован.

## Math:: vec3 getAxis0 () const

Возвращает текущую ось первого соединённого тела.
### Возвращаемое значение

Текущая ось первого тела. Указанный вектор будет нормализован.
## void setAxis1 ( const Math:: vec3 & axis1 )

Задаёт новую ось второго соединённого тела.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis1** - Ось второго тела. Указанный вектор будет нормализован.

## Math:: vec3 getAxis1 () const

Возвращает текущую ось второго соединённого тела.
### Возвращаемое значение

Текущая ось второго тела. Указанный вектор будет нормализован.
---

## static JointBallPtr create ( )

Конструктор. Создаёт ball joint с точкой крепления в начале мировых координат.
## static JointBallPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 )

Конструктор. Создаёт ball joint, соединяющий два указанных тела. Точка крепления размещается между центрами масс тел.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Первое тело, соединяемое с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Второе тело, соединяемое с помощью joint.

## static JointBallPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 , const Math:: Vec3 & anchor )

Конструктор. Создаёт ball joint, соединяющий два указанных тела, с точкой крепления, размещённой в указанных координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Первое тело, соединяемое с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Второе тело, соединяемое с помощью joint.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **anchor** - Координаты точки крепления.

## static JointBallPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 , const Math:: Vec3 & anchor , const Math:: vec3 & axis )

Конструктор. Создаёт ball joint, соединяющий два указанных тела, с указанными координатами оси и точкой крепления, размещённой в указанных координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Первое тело, соединяемое с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Второе тело, соединяемое с помощью joint.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **anchor** - Координаты точки крепления.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **axis** - Координаты оси.
