# Unigine::JointParticles Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Joint


Этот класс используется для закрепления [cloth body](../../../api/library/physics/class.bodycloth_cpp.md) или [rope body](../../../api/library/physics/class.bodyrope_cpp.md) на [rigid bodies](../../../api/library/physics/class.bodyrigid_cpp.md), [ragdolls](../../../api/library/physics/class.bodyragdoll_cpp.md) или [dummy bodies](../../../api/library/physics/class.bodydummy_cpp.md).


### Пример


Следующий код иллюстрирует соединение [rope body](../../../api/library/physics/class.bodyrope_cpp.md) (rope) и [dummy body](../../../api/library/physics/class.bodydummy_cpp.md) (dummy) с помощью particles joint. Точка крепления размещается в позиции dummy body.


```cpp
include <UniginePhysics.h>

/* .. */

//точка крепления размещается в позиции dummy body, размер области закрепления (0.5f, 0.5f, 1.5f)
JointParticlesPtr joint = JointParticles::create(dummy, rope, dummy->getObject()->getPosition(), Vec3(0.5f, 0.5f, 1.5f));

// задаём порог закрепления
joint->setThreshold(0.001f);

// задаём количество итераций
joint->setNumIterations(4);

```


### См. также


Примеры использования:


- [Creating and Attaching a Cloth](../../../code/usage/cloth_particle_joint/index_cpp.md)
- [Creating Pylons and Wires Using Ropes](../../../code/usage/ropes_creating_pylons_and_wires/index_cpp.md)


## JointParticles Class

### Методы класса

## int getNumParticles () const

Возвращает текущее общее количество закреплённых частиц cloth или rope body.
### Возвращаемое значение

Текущее количество закреплённых частиц.
## void setThreshold ( float threshold )

Задаёт новый порог, определяющий расстояние для закрепления вершин cloth или rope body к другому телу. Если вершины находятся ближе порога, они закрепляются вместе; иначе частицы остаются свободными.
### Аргументы

- *float* **threshold** - Порог расстояния закрепления.

## float getThreshold () const

Возвращает текущий порог, определяющий расстояние для закрепления вершин cloth или rope body к другому телу. Если вершины находятся ближе порога, они закрепляются вместе; иначе частицы остаются свободными.
### Возвращаемое значение

Текущий порог расстояния закрепления.
## void setSize ( const Math:: vec3 & size )

Задаёт новый размер области закреплённых вершин cloth или rope body к другому телу.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **size** - Размер закреплённой области.

## Math:: vec3 getSize () const

Возвращает текущий размер области закреплённых вершин cloth или rope body к другому телу.
### Возвращаемое значение

Текущий размер закреплённой области.
---

## static JointParticlesPtr create ( )

Конструктор. Создаёт particles joint с точкой крепления в начале мировых координат.
## static JointParticlesPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 )

Конструктор. Создаёт particles joint, соединяющий два указанных тела. Точка крепления размещается в центре тела, к которому закрепляется cloth или rope.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Первое тело, соединяемое с помощью joint. Может быть одним из следующих:

  - [BodyRigid](../../../api/library/physics/class.bodyrigid_cpp.md)
  - [BodyRagdoll](../../../api/library/physics/class.bodyragdoll_cpp.md)
  - [BodyDummy](../../../api/library/physics/class.bodydummy_cpp.md)
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Второе тело, соединяемое с помощью joint. Может быть одним из следующих:

  - [BodyCloth](../../../api/library/physics/class.bodycloth_cpp.md)
  - [BodyRope](../../../api/library/physics/class.bodyrope_cpp.md)

## static JointParticlesPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 , const Math:: Vec3 & anchor , const Math:: vec3 & size )

Конструктор. Создаёт particles joint, соединяющий два указанных тела, с указанным размером области закрепления и точкой крепления, размещённой в указанных координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Первое тело, соединяемое с помощью joint. Может быть одним из следующих:

  - [BodyRigid](../../../api/library/physics/class.bodyrigid_cpp.md)
  - [BodyRagdoll](../../../api/library/physics/class.bodyragdoll_cpp.md)
  - [BodyDummy](../../../api/library/physics/class.bodydummy_cpp.md)
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Второе тело, соединяемое с помощью joint. Может быть одним из следующих:

  - [BodyCloth](../../../api/library/physics/class.bodycloth_cpp.md)
  - [BodyRope](../../../api/library/physics/class.bodyrope_cpp.md)
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **anchor** - Координаты точки крепления.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Область для закрепления вершин cloth или rope body к другому телу.

## float getParticleMass ( int num )

Возвращает массу закреплённой частицы cloth или rope body.
### Аргументы

- *int* **num** - Номер частицы.

### Возвращаемое значение

Масса частицы.
## Math:: vec3 getParticlePosition ( int num )

Возвращает позицию закреплённой частицы cloth или rope body.
### Аргументы

- *int* **num** - Номер частицы.

### Возвращаемое значение

Позиция частицы.
## void clearParticles ( )

Полностью открепляет cloth или rope body.
