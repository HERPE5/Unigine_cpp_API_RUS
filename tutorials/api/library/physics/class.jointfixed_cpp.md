# Unigine::JointFixed Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Joint


Этот класс используется для создания [fixed joints](../../../principles/physics/joints/index.md#fixed).


### Пример


Следующий код иллюстрирует соединение двух [bodies](../../../api/library/physics/class.body_cpp.md) (b0 и b1) с помощью fixed joint.


```cpp
include <UniginePhysics.h>

/* .. */

JointFixedPtr joint = JointFixed::create(b0, b1);

// задаём общие параметры ограничений joint
joint->setLinearRestitution(0.8f);
joint->setAngularRestitution(0.8f);
joint->setLinearSoftness(0.0f);
joint->setAngularSoftness(0.0f);

// задаём количество итераций
joint->setNumIterations(4);

```


### См. также


- Пример использования: [Creating a Simple Mechanism Using Various Types of Joints](../../../code/usage/simple_mechanism_joints/index_cpp.md)

  -
  -
  -
  -
  -
  -


## JointFixed Class

### Методы класса

## void setWorldRotation ( const Math:: mat3 & rotation )

Задаёт новую матрицу поворота точки крепления в мировой системе координат.
### Аргументы

- *const  Math::[mat3](../../../api/library/math/class.mat3_cpp.md)&* **rotation** - Матрица поворота в мировом пространстве координат.

## Math:: mat3 getWorldRotation () const

Возвращает текущую матрицу поворота точки крепления в мировой системе координат.
### Возвращаемое значение

Текущая матрица поворота в мировом пространстве координат.
## void setRotation0 ( const Math:: mat3 & rotation0 )

Задаёт новую матрицу поворота точки крепления в системе координат первого соединённого тела.
### Аргументы

- *const  Math::[mat3](../../../api/library/math/class.mat3_cpp.md)&* **rotation0** - Матрица поворота в пространстве координат тела.

## Math:: mat3 getRotation0 () const

Возвращает текущую матрицу поворота точки крепления в системе координат первого соединённого тела.
### Возвращаемое значение

Текущая матрица поворота в пространстве координат тела.
## void setRotation1 ( const Math:: mat3 & rotation1 )

Задаёт новую матрицу поворота точки крепления в системе координат второго соединённого тела.
### Аргументы

- *const  Math::[mat3](../../../api/library/math/class.mat3_cpp.md)&* **rotation1** - Матрица поворота в пространстве координат тела.

## Math:: mat3 getRotation1 () const

Возвращает текущую матрицу поворота точки крепления в системе координат второго соединённого тела.
### Возвращаемое значение

Текущая матрица поворота в пространстве координат тела.
---

## static JointFixedPtr create ( )

Конструктор. Создаёт joint с точкой крепления в начале мировых координат.
## static JointFixedPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 )

Конструктор. Создаёт joint, соединяющий два указанных тела. Точка крепления размещается между центрами масс тел.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Первое тело, соединяемое с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Второе тело, соединяемое с помощью joint.

## static JointFixedPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 , const Math:: Vec3 & anchor )

Конструктор. Создаёт fixed joint, соединяющий два указанных тела, с точкой крепления, размещённой в указанных координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Первое тело, соединяемое с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Второе тело, соединяемое с помощью joint.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **anchor** - Координаты точки крепления.
