# Unigine::BodyFracture Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Body


Этот класс используется для симуляции разрушаемых [fracture bodies](../../../principles/physics/bodies/fracture/index.md).

> **Notice:** Fracture body можно использовать с мешами в форме простых примитивов: boxes, spheres, capsules, cylinders и т.д. Сложные меши нельзя процедурно разрушать.

 Существует три паттерна разрушения:
- [Cracking](../../../principles/physics/bodies/fracture/index.md#crack) ([*createCrackPieces()*](#createCrackPieces_Vec3_vec3_int_int_float_int))
- [Shattering](../../../principles/physics/bodies/fracture/index.md#shatter) ([*createShatterPieces()*](#createShatterPieces_int_int))
- [Slicing](../../../principles/physics/bodies/fracture/index.md#slice) ([*createSlicePieces()*](#createSlicePieces_Vec3_vec3_int))


Новым поверхностям, создаваемым при разрушении, назначаются собственные [material](#setMaterial_Material_void) и [properties](#setSurfaceProperty_cstr_void).

> **Notice:** [Material](#setMaterial_Material_void) и properties должны быть заданы до разрушения объекта.

 Также перед разрушением должен быть задан [minimum volume threshold](#setThreshold_float_void). Объём получившегося фрагмента должен быть больше порогового значения, иначе объект не будет разрушен.
Fracture body по сути является [rigid body](#getBodyRigid_BodyRigid) и перемещается согласно [rigid bodies dynamics](../../../principles/physics/bodies/index.md#rigid_bodies_dynamics).


### Пример Shattering


[Shattering](../../../principles/physics/bodies/fracture/index.md#shatter) — это паттерн разрушения, случайным образом разделяющий объём меша на заданное количество выпуклых фрагментов.


<details>
<summary>Shattering.h | Закрыть</summary>

```cpp
#pragma once
#include <UnigineGame.h>
#include <UnigineControls.h>

// подключаем заголовочный файл Component System
#include <UnigineComponentSystem.h>

using namespace Unigine;

class Shattering : public ComponentBase
{
public:

	COMPONENT_DEFINE(Shattering, ComponentBase)

	// объявляем методы, вызываемые на соответствующих этапах последовательности выполнения
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// параметр, задающий объект для разрушения (shatter)
	PROP_PARAM(Node, dynamicObject);
	// параметр, задающий материал, применяемый к осколкам
	PROP_PARAM(Material, shatteredObjectMaterial);

protected:

	// переопределения главного цикла мира
	void init();
	void update();
	void shutdown();

	// fracture body для разрушаемого объекта
	BodyFracturePtr bf;
};

```

</details>


<details>
<summary>Shattering.cpp | Закрыть</summary>

```cpp
#include "Shattering.h"
#include <UnigineConsole.h>
#include <UnigineRender.h>

REGISTER_COMPONENT(Shattering);		// макрос регистрации компонента в Component System

void Shattering::init()
{
	// создаём fracture body для разрушаемого объекта
	bf = BodyFracture::create(checked_ptr_cast<ObjectMeshDynamic>(dynamicObject->getNode(dynamicObject->getID())));
	// задаём минимальный порог объёма для разрушения
	bf->setThreshold(0.01f);
	// задаём материал для осколков
	bf->setMaterial(shatteredObjectMaterial);
	// разбиваем объект на осколки
	bf->createShatterPieces(2);
	// изменяем флаг разрушения
	bf->setBroken(true);
}

void Shattering::update() {}
void Shattering::shutdown() {}

```

</details>


### Пример Slicing


[Slicing](../../../principles/physics/bodies/fracture/index.md#slice) — это паттерн разрушения, разделяющий объём меша на две части плоскостью в указанной точке тела. Угол разреза определяется заданной нормалью.


<details>
<summary>Slicing.h | Закрыть</summary>

```cpp
#pragma once
#include <UnigineGame.h>
#include <UnigineControls.h>

// подключаем заголовочный файл Component System
#include <UnigineComponentSystem.h>

using namespace Unigine;

class Slicing : public ComponentBase
{
public:

	COMPONENT_DEFINE(Slicing, ComponentBase)

	// объявляем методы, вызываемые на соответствующих этапах последовательности выполнения
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// параметр, задающий разрезаемый объект
	PROP_PARAM(Node, dynamicObject);
	// параметр, задающий материал, применяемый к срезам
	PROP_PARAM(Material, slicedObjectMaterial);

protected:

	// переопределения главного цикла мира
	void init();
	void update();
	void shutdown();

	// fracture body для разрезаемого объекта
	BodyFracturePtr bf;
};

```

</details>


<details>
<summary>Slicing.cpp | Закрыть</summary>

```cpp
#include "Slicing.h"
#include <UnigineConsole.h>
#include <UnigineRender.h>

REGISTER_COMPONENT(Slicing);		// макрос регистрации компонента в Component System

using namespace Math;

void Slicing::init()
{
	// создаём fracture body для разрезаемого объекта
	bf = BodyFracture::create(checked_ptr_cast<ObjectMeshDynamic>(dynamicObject->getNode(dynamicObject->getID())));
	// задаём минимальный порог объёма для разреза
	bf->setThreshold(0.01f);
	// задаём материал для срезов
	bf->setMaterial(slicedObjectMaterial);
	// разрезаем тело в указанной точке
	vec3 point = bf->getTransform() * vec3_zero;
	bf->createSlicePieces(point, vec3_one);
	// изменяем флаг разрушения
	bf->setBroken(true);
}

void Slicing::update() {}
void Slicing::shutdown() {}

```

</details>


### Пример Cracking


[Cracking](../../../principles/physics/bodies/fracture/index.md#crack) — это паттерн разрушения, формирующий радиальные трещины от точки столкновения.


<details>
<summary>Cracking.h | Закрыть</summary>

```cpp
#pragma once
#include <UnigineGame.h>
#include <UnigineControls.h>

// подключаем заголовочный файл Component System
#include <UnigineComponentSystem.h>

using namespace Unigine;

class Cracking : public ComponentBase
{
public:

	COMPONENT_DEFINE(Cracking, ComponentBase)

	// объявляем методы, вызываемые на соответствующих этапах последовательности выполнения
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// параметр, задающий объект для образования трещин
	PROP_PARAM(Node, dynamicObject);
	// параметр, задающий материал, применяемый к фрагментам
	PROP_PARAM(Material, crackedObjectMaterial);

protected:

	// переопределения главного цикла мира
	void init();
	void update();
	void shutdown();

	// fracture body для объекта с трещинами
	BodyFracturePtr bf;
};

```

</details>


<details>
<summary>Cracking.cpp | Закрыть</summary>

```cpp
#include "Cracking.h"
#include <UnigineConsole.h>
#include <UnigineRender.h>

REGISTER_COMPONENT(Cracking);		// макрос регистрации компонента в Component System

using namespace Math;

void Cracking::init()
{
	// создаём fracture body для объекта с трещинами
	bf = BodyFracture::create(checked_ptr_cast<ObjectMeshDynamic>(dynamicObject->getNode(dynamicObject->getID())));
	// задаём минимальный порог объёма для образования трещин
	bf->setThreshold(0.01f);
	// задаём материал для фрагментов
	bf->setMaterial(crackedObjectMaterial);
	// разрушаем тело в указанной точке
	vec3 point = bf->getTransform() * vec3_zero;
	bf->createCrackPieces(point, vec3_one,7,3,0.1f);
	// изменяем флаг разрушения
	bf->setBroken(true);
}

void Cracking::update() {}
void Cracking::shutdown() {}

```

</details>


### См. также


- C++ samples:

  -
  -
  -
- C# Component samples:

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


## BodyFracture Class

### Методы класса

---

## static BodyFracturePtr create ( )

Конструктор. Создаёт fracture body со свойствами по умолчанию.
## static BodyFracturePtr create ( const Ptr < Object > & object )

Конструктор. Создаёт fracture body со свойствами по умолчанию для указанного объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, представленный новым fracture body.

## void setAngularDamping ( float damping )

Задаёт затухание угловой скорости тела.
### Аргументы

- *float* **damping** - Значение углового затухания.

## float getAngularDamping ( ) const

Возвращает текущее затухание угловой скорости тела.
### Возвращаемое значение

Значение углового затухания.
## Ptr < BodyRigid > getBodyRigid ( ) const

Возвращает внутреннее тело [BodyRigid](../../../api/library/physics/class.bodyrigid_cpp.md), которое представляет fracture body до его разрушения.
### Возвращаемое значение

Внутреннее тело BodyRigid.
## void setBroken ( bool broken )

Задаёт значение, указывающее, разрушен ли объект или остаётся в цельном состоянии.
### Аргументы

- *bool* **broken** - true, чтобы указать объект как [broken](../../../principles/physics/bodies/fracture/index.md#broken); false, чтобы он оставался цельным.

## bool isBroken ( ) const

Возвращает значение, указывающее, разрушен ли объект или остаётся в цельном состоянии.
### Возвращаемое значение

true, если объект уже [broken](../../../principles/physics/bodies/fracture/index.md#broken); false, если он всё ещё цельный.
## void setCollisionMask ( int mask )

Задаёт битовую маску столкновений для тела. Два объекта сталкиваются, если у обоих совпадающие маски. См. также подробности о дополнительной [collision exclusion mask](#setExclusionMask_int_void).
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getCollisionMask ( ) const

Возвращает битовую маску столкновений для тела. Два объекта сталкиваются, если у обоих совпадающие маски. См. также подробности о дополнительной [collision exclusion mask](#getExclusionMask_int).
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setDensity ( float density )

Задаёт плотность тела. Изменение плотности влияет на массу, которая вычисляется путём умножения объёма тела на плотность.
### Аргументы

- *float* **density** - Плотность тела.

## float getDensity ( ) const

Возвращает текущую плотность тела.
### Возвращаемое значение

Плотность тела.
## void setError ( float error )

Задаёт допустимую погрешность аппроксимации при создании выпуклой формы для меша.
### Аргументы

- *float* **error** - Погрешность аппроксимации. Если указано отрицательное значение, вместо него используется **0**.

## float getError ( ) const

Возвращает текущую допустимую погрешность аппроксимации при создании выпуклой формы для меша.
### Возвращаемое значение

Погрешность аппроксимации.
## void setExclusionMask ( int mask )

Задаёт битовую маску для предотвращения столкновений тела с другими телами. Эта маска не зависит от [collision mask](#setCollisionMask_int_void). Чтобы тела с совпадающими масками столкновений не сталкивались, должен совпадать хотя бы один бит их маски исключения. **0** означает столкновение со всеми телами с совпадающей маской столкновений.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getExclusionMask ( ) const

Возвращает битовую маску, предотвращающую столкновения тела с другими телами. Эта маска не зависит от [collision mask](#getCollisionMask_int). Чтобы тела с совпадающими масками столкновений не сталкивались, должен совпадать хотя бы один бит их маски исключения.
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setFriction ( float friction )

Задаёт трение тела относительно других поверхностей.
### Аргументы

- *float* **friction** - Значение трения.

## float getFriction ( ) const

Возвращает текущее трение тела относительно других поверхностей.
### Возвращаемое значение

Значение трения.
## void setFrozenAngularVelocity ( float velocity )

Задаёт порог угловой скорости для заморозки симуляции тела. Если угловая скорость тела остаётся ниже этого порога в течение числа [Frozen frames](../../../api/library/physics/class.physics_cpp.md#setNumFrozenFrames_int_void) (вместе с линейной), тело перестаёт обновляться.
### Аргументы

- *float* **velocity** - Угловая скорость "заморозки". Если значение ниже, чем [engine.physics.setFrozenAngularVelocity](../../../api/library/physics/class.physics_cpp.md#setFrozenAngularVelocity_float_void), оно переопределяется.

## float getFrozenAngularVelocity ( ) const

Возвращает текущий порог угловой скорости для заморозки симуляции тела. Если угловая скорость тела остаётся ниже этого порога в течение числа [Frozen frames](../../../api/library/physics/class.physics_cpp.md#setNumFrozenFrames_int_void) (вместе с линейной), тело перестаёт обновляться.
### Возвращаемое значение

Угловая скорость "заморозки".
## void setFrozenLinearVelocity ( float velocity )

Задаёт порог линейной скорости для заморозки симуляции тела. Если линейная скорость тела остаётся ниже этого порога в течение числа [Frozen frames](../../../api/library/physics/class.physics_cpp.md#setNumFrozenFrames_int_void) (вместе с угловой), тело перестаёт обновляться.
### Аргументы

- *float* **velocity** - Линейная скорость "заморозки". Если значение ниже, чем [engine.physics.setFrozenLinearVelocity](../../../api/library/physics/class.physics_cpp.md#setFrozenLinearVelocity_float_void), оно переопределяется.

## float getFrozenLinearVelocity ( ) const

Возвращает текущий порог линейной скорости для заморозки симуляции тела. Если линейная скорость тела остаётся ниже этого порога в течение числа [Frozen frames](../../../api/library/physics/class.physics_cpp.md#setNumFrozenFrames_int_void) (вместе с угловой), тело перестаёт обновляться.
### Возвращаемое значение

Линейная скорость "заморозки".
## void setPhysicsIntersectionMask ( int mask )

Задаёт [physics intersection mask](../../../principles/bit_masking/index.md#physics_intersection_mask) для тела.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getPhysicsIntersectionMask ( ) const

Возвращает текущую [physics intersection mask](../../../principles/bit_masking/index.md#physics_intersection_mask) для тела.
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setLinearDamping ( float damping )

Задаёт затухание линейной скорости тела.
### Аргументы

- *float* **damping** - Значение линейного затухания.

## float getLinearDamping ( ) const

Возвращает текущее затухание линейной скорости тела.
### Возвращаемое значение

Значение линейного затухания.
## void setMass ( float mass )

Задаёт массу тела. Изменение массы влияет на плотность, которая вычисляется путём деления массы на объём тела.
### Аргументы

- *float* **mass** - Масса тела.

## float getMass ( ) const

Возвращает текущую массу тела.
### Возвращаемое значение

Масса тела.
## void setMaterial ( const Ptr < Material > & material )

Задаёт материал для поверхностей разлома, появляющихся после разрушения тела.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.

## Ptr < Material > getMaterial ( ) const

Возвращает материал для поверхностей разлома, появляющихся после разрушения тела.
### Возвращаемое значение

Умный указатель на материал поверхностей разлома.
## void setMaxAngularVelocity ( float velocity )

Задаёт максимально возможную угловую скорость для тела. Если значение ниже, чем [engine.physics.setMaxAngularVelocity](../../../api/library/physics/class.physics_cpp.md#setMaxAngularVelocity_float_void), оно переопределяется.
### Аргументы

- *float* **velocity** - Максимально возможная угловая скорость.

## float getMaxAngularVelocity ( ) const

Возвращает текущую максимально возможную угловую скорость для тела. Если значение ниже, чем [engine.physics.setMaxAngularVelocity](../../../api/library/physics/class.physics_cpp.md#setMaxAngularVelocity_float_void), оно переопределяется.
### Возвращаемое значение

Максимально возможная угловая скорость.
## void setMaxLinearVelocity ( float velocity )

Задаёт максимально возможную линейную скорость для тела. Если значение ниже, чем [engine.physics.setMaxLinearVelocity](../../../api/library/physics/class.physics_cpp.md#setMaxLinearVelocity_float_void), оно переопределяется.
### Аргументы

- *float* **velocity** - Максимально возможная линейная скорость.

## float getMaxLinearVelocity ( ) const

Возвращает текущую максимально возможную линейную скорость для тела. Если значение ниже, чем [engine.physics.setMaxLinearVelocity](../../../api/library/physics/class.physics_cpp.md#setMaxLinearVelocity_float_void), оно переопределяется.
### Возвращаемое значение

Максимально возможная линейная скорость.
## void setSurfaceProperty ( const char * property )

Задаёт свойство для поверхностей разлома, появляющихся после разрушения тела.
### Аргументы

- *const char ** **property** - Имя свойства для поверхностей разлома.

## const char * getSurfaceProperty ( ) const

Возвращает свойство для поверхностей разлома, появляющихся после разрушения тела.
### Возвращаемое значение

Имя свойства для поверхностей разлома.
## void setRestitution ( float restitution )

Задаёт упругость (restitution), определяющую отскок тела от поверхностей.
### Аргументы

- *float* **restitution** - Значение упругости.

## float getRestitution ( ) const

Возвращает текущую упругость, определяющую отскок тела от поверхностей.
### Возвращаемое значение

Значение упругости.
## void setThreshold ( float threshold )

Задаёт минимальный порог объёма для разрушения. Если объём фрагмента меньше порогового значения, он не может быть разрушен дальше.
### Аргументы

- *float* **threshold** - Порог объёма. Если указано отрицательное значение, вместо него используется **0**.

## float getThreshold ( ) const

Возвращает текущий минимальный порог объёма для разрушения. Если объём фрагмента меньше порогового значения, он не может быть разрушен дальше.
### Возвращаемое значение

Порог объёма.
## Math:: vec3 getVelocity ( const Math::vec3& radius ) const

Возвращает суммарную линейную скорость в точке, определяемой заданным радиус-вектором, указанным в локальных координатах.
### Аргументы

- *const  Math::vec3&* **radius** - Радиус-вектор, начинающийся в центре масс тела.

### Возвращаемое значение

Суммарная линейная скорость в указанной точке.
## Math:: vec3 getWorldVelocity ( const Math::Vec3& point ) const

Возвращает суммарную линейную скорость в точке, указанной в мировых координатах.
### Аргументы

- *const  Math::Vec3&* **point** - Точка тела в мировых координатах.

### Возвращаемое значение

Суммарная линейная скорость в указанной точке.
## void addForce ( const Math::vec3& force ) const


Прикладывает силу к центру масс тела.


В отличие от [impulses](#addImpulse_vec3_vec3_void), все силы сначала накапливаются, а затем вычисляется результирующая сила и прикладывается к телу (на этапе симуляции физики, когда вызывается функция *update()* тела).


> **Notice:** Эту функцию можно вызывать только из функции *[updatePhysics()](../../../code/fundamentals/execution_sequence/code_update.md#code_updatePhysics)* мирового скрипта. Не прикладывайте силы в функции *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)*, так как это приведёт к нестабильному результату, изменяющемуся на каждом кадре рендеринга.


### Аргументы

- *const  Math::vec3&* **force** - Прикладываемая сила, в мировых координатах.

## void addForce ( const Math::vec3& radius , const Math::vec3& force ) const


Прикладывает силу к точке, определяемой заданным радиус-вектором, указанным в локальных координатах. Эта функция вычисляет векторное произведение радиус-вектора и вектора силы. Она действует как рычаг, изменяющий как линейную, так и угловую скорости тела.


В отличие от [impulses](#addImpulse_vec3_vec3_void), все силы сначала накапливаются, а затем вычисляется результирующая сила и прикладывается к телу (на этапе симуляции физики, когда вызывается функция *update()* тела).


> **Notice:** Эту функцию можно вызывать только из функции *[updatePhysics()](../../../code/fundamentals/execution_sequence/code_update.md#code_updatePhysics)* мирового скрипта. Не прикладывайте силы в функции *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)*, так как это приведёт к нестабильному результату, изменяющемуся на каждом кадре рендеринга.


### Аргументы

- *const  Math::vec3&* **radius** - Радиус-вектор, проведённый от центра масс тела до точки приложения силы, в локальных координатах.
- *const  Math::vec3&* **force** - Прикладываемая сила, в мировых координатах.

## void addImpulse ( const Math::vec3& radius , const Math::vec3& impulse )


Прикладывает импульс к точке, определяемой заданным радиус-вектором, указанным в локальных координатах.


В отличие от [forces](#addForce_vec3_void), импульсы немедленно влияют как на линейную, так и на угловую скорости тела.


### Аргументы

- *const  Math::vec3&* **radius** - Радиус-вектор, проведённый от центра масс до точки приложения импульса, в локальных координатах.
- *const  Math::vec3&* **impulse** - Прикладываемый импульс, в мировых координатах.

## void addTorque ( const Math::vec3& torque ) const


Прикладывает момент силы (torque) с точкой опоры в центре масс тела, указанным в локальных координатах.


Все значения момента силы сначала накапливаются, а затем вычисляется результирующий момент и прикладывается к телу (на этапе симуляции физики, когда вызывается обновление тела).


> **Notice:** Эту функцию можно вызывать только из функции *[updatePhysics()](../../../code/fundamentals/execution_sequence/code_update.md#code_updatePhysics)* мирового скрипта. Не прикладывайте моменты силы в функции *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)*, так как это приведёт к нестабильному результату, изменяющемуся на каждом кадре рендеринга.


### Аргументы

- *const  Math::vec3&* **torque** - Прикладываемый момент силы, в мировых координатах.

## void addTorque ( const Math::vec3& radius , const Math::vec3& torque ) const


Прикладывает момент силы с точкой опоры, определяемой заданным радиус-вектором, указанным в локальных координатах.


Эта функция вычисляет векторное произведение радиус-вектора и вектора силы.


Она действует как рычаг, изменяющий как угловую, так и линейную скорости тела.


Все значения момента силы сначала накапливаются, а затем вычисляется результирующий момент и прикладывается к телу (на этапе симуляции физики, когда вызывается обновление тела).


> **Notice:** Эту функцию можно вызывать только из функции *[updatePhysics()](../../../code/fundamentals/execution_sequence/code_update.md#code_updatePhysics)* мирового скрипта. Не прикладывайте моменты силы в функции *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)*, так как это приведёт к нестабильному результату, изменяющемуся на каждом кадре рендеринга.


### Аргументы

- *const  Math::vec3&* **radius** - Радиус-вектор, начинающийся в центре масс тела, в локальных координатах. Его конец — точка опоры для прикладываемого момента силы.
- *const  Math::vec3&* **torque** - Прикладываемый момент силы, в мировых координатах.

## void addWorldForce ( const Math::Vec3& point , const Math::vec3& force )


Прикладывает силу к указанной точке тела, заданной в мировых координатах. Эта функция вычисляет векторное произведение радиус-вектора (вектора от центра масс до точки приложения силы) и вектора силы. Она действует как рычаг, изменяющий как линейную, так и угловую скорости тела.


В отличие от [impulses](#addWorldImpulse_Vec3_vec3_void), все силы сначала накапливаются, а затем вычисляется результирующая сила и прикладывается к телу (на этапе симуляции физики, когда вызывается обновление тела).


> **Notice:** Эту функцию можно вызывать только из функции *[updatePhysics()](../../../code/fundamentals/execution_sequence/code_update.md#code_updatePhysics)* мирового скрипта. Не прикладывайте силы в функции *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)*, так как это приведёт к нестабильному результату, изменяющемуся на каждом кадре рендеринга.


### Аргументы

- *const  Math::Vec3&* **point** - Точка тела в мировых координатах.
- *const  Math::vec3&* **force** - Прикладываемая сила, в мировых координатах.

## void addWorldImpulse ( const Math::Vec3& point , const Math::vec3& impulse )

Прикладывает импульс к указанной точке тела, заданной в мировых координатах. В отличие от [forces](#addWorldForce_Vec3_vec3_void), импульсы немедленно влияют как на линейную, так и на угловую скорости тела.
### Аргументы

- *const  Math::Vec3&* **point** - Точка тела в мировых координатах.
- *const  Math::vec3&* **impulse** - Прикладываемый импульс, в мировых координатах.

## void addWorldTorque ( const Math::Vec3& point , const Math::vec3& torque )


Прикладывает момент силы с точкой опоры в указанной точке тела, заданной в мировых координатах. Эта функция вычисляет векторное произведение радиус-вектора (вектора от центра масс до точки опоры) и вектора момента силы. Она действует как рычаг, изменяющий как угловую, так и линейную скорости тела.


Все значения момента силы сначала накапливаются, а затем вычисляется результирующий момент и прикладывается к телу (на этапе симуляции физики, когда вызывается обновление тела).


> **Notice:** Эту функцию можно вызывать только из функции *[updatePhysics()](../../../code/fundamentals/execution_sequence/code_update.md#code_updatePhysics)* мирового скрипта. Не прикладывайте моменты силы в функции *[update()](../../../code/fundamentals/execution_sequence/code_update.md#code_update)*, так как это приведёт к нестабильному результату, изменяющемуся на каждом кадре рендеринга.


### Аргументы

- *const  Math::Vec3&* **point** - Точка тела в мировых координатах.
- *const  Math::vec3&* **torque** - Прикладываемый момент силы, в мировых координатах.

## int createCrackPieces ( const Math::Vec3& point , const Math::vec3& normal , int num_cuts , int num_rings , float step )

Разрушает объект на радиальные трещины в сочетании с концентрическими разломами. Если первый концентрический разлом отрисовывается дальше указанного шагового расстояния, уменьшите значение [volume threshold](#setThreshold_float_void).
### Аргументы

- *const  Math::Vec3&* **point** - Точка контакта.
- *const  Math::vec3&* **normal** - Нормаль точки контакта.
- *int* **num_cuts** - Количество радиальных разрезов, представленных как лучи, исходящие из центра точки контакта.
- *int* **num_rings** - Количество колец, образующих концентрические разломы. Фактическое количество отрисовываемых колец зависит от значения *step*.
- *float* **step** - Расстояние между концентрическими разломами.

### Возвращаемое значение

Положительное число, если объект успешно разрушен; иначе **0**.
## int createShatterPieces ( int num_pieces )

Разрушает объект на произвольные осколки.
### Аргументы

- *int* **num_pieces** - Количество осколков.

### Возвращаемое значение

Положительное число, если объект успешно разрушен; иначе **0**.
## int createSlicePieces ( const Math::Vec3& point , const Math::vec3& normal )

Разрезает объект на две части, разрезая тело в соответствии с нормалью указанной точки.
### Аргументы

- *const  Math::Vec3&* **point** - Точка контакта.
- *const  Math::vec3&* **normal** - Нормаль точки контакта.

### Возвращаемое значение

Положительное число, если объект успешно разрушен; иначе **0**.
## void setMaterialFilePath ( const char * path )

Задаёт материал, используемый для поверхностей разлома, по пути к файлу.
### Аргументы

- *const char ** **path** - Путь к файлу материала.

## String getMaterialFilePath ( ) const

Возвращает путь к файлу материала, используемому для поверхностей разлома.
### Возвращаемое значение

Путь к материалу.
## void setMaterialGUID ( const UGUID& materialguid )

Задаёт материал для поверхностей разлома по [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const UGUID&* **materialguid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала.

## UGUID getMaterialGUID ( ) const

Возвращает [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала для поверхностей разлома.
### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала.
