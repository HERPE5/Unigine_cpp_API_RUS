# Unigine::JointSuspension Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Joint


> **Warning:** Этот тип joint устарел и будет удалён в следующих релизах. Рекомендуется использовать вместо него [Wheel Joint](../../../api/library/physics/class.jointwheel_cpp.md).


Этот класс используется для создания suspension joint. Тела, представляющие как раму (frame), так и колесо (wheel), должны быть [rigid bodies](../../../principles/physics/bodies/rigid/index.md).


### Пример


Следующий код иллюстрирует соединение двух [rigid bodies](../../../api/library/physics/class.bodyrigid_cpp.md) (frame и wheel) с помощью suspension joint.


```cpp
include <UniginePhysics.h>

/* .. */

JointSuspensionPtr joint = JointSuspension::create(frame, wheel);

// задаём координаты точки крепления joint
joint->setWorldAnchor(wheel->getObject()->getWorldTransform() * Vec3(0.0f));

// задаём координаты осей joint
joint->setWorldAxis0(vec3(0.0f,0.0f,1.0f));
joint->setWorldAxis1(vec3(0.0f,1.0f,0.0f));

// задаём линейное демпфирование и жёсткость пружины
joint->setLinearDamping(2.0f);
joint->setLinearSpring(200.0f);

// задаём нижний и верхний пределы хода подвески [-0.5; 0.0]
joint->setLinearLimitFrom(-0.5f);
joint->setLinearLimitTo(0.0f);

// задаём целевую высоту подвески
joint->setLinearDistance(0.5f);

// задаём максимальную угловую скорость и момент силы
joint->setAngularVelocity(-20.0f);
joint->setAngularTorque(10.0f);

// задаём общие параметры ограничений joint
joint->setLinearRestitution(0.2f);
joint->setAngularRestitution(0.2f);
joint->setLinearSoftness(0.2f);
joint->setAngularSoftness(0.2f);

// задаём количество итераций
joint->setNumIterations(8);

```


### См. также



  -
  -
  -


## JointSuspension Class

### Методы класса

## float getCurrentLinearDistance () const

Возвращает текущее сжатие подвески.
### Возвращаемое значение

Текущая высота подвески, в единицах.
## float getCurrentAngularVelocity () const

Возвращает текущую скорость вращения колеса.
### Возвращаемое значение

Текущая скорость, в радианах в секунду.
## void setAngularVelocity ( float velocity )

Задаёт новую целевую скорость вращения колеса.
### Аргументы

- *float* **velocity** - Целевая скорость в радианах в секунду.

## float getAngularVelocity () const

Возвращает текущую целевую скорость вращения колеса.
### Возвращаемое значение

Текущая целевая скорость в радианах в секунду.
## void setAngularTorque ( float torque )

Задаёт новый максимальный момент силы присоединённого углового мотора. **0** означает, что мотор не присоединён.
### Аргументы

- *float* **torque** - Максимальный момент силы. Если указано отрицательное значение, вместо него используется **0**. **0** отсоединяет мотор.

## float getAngularTorque () const

Возвращает текущий максимальный момент силы присоединённого углового мотора. **0** означает, что мотор не присоединён.
### Возвращаемое значение

Текущий максимальный момент силы. Если указано отрицательное значение, вместо него используется **0**. **0** отсоединяет мотор.
## void setAngularDamping ( float damping )

Задаёт новое угловое затухание joint (затухание вращения колеса).
### Аргументы

- *float* **damping** - Угловое затухание. Если указано отрицательное значение, вместо него используется **0**.

## float getAngularDamping () const

Возвращает текущее угловое затухание joint (затухание вращения колеса).
### Возвращаемое значение

Текущее угловое затухание. Если указано отрицательное значение, вместо него используется **0**.
## void setLinearSpring ( float spring )

Задаёт новый коэффициент жёсткости подвески. **0** означает, что подвеска не присоединена.
### Аргументы

- *float* **spring** - Коэффициент жёсткости. Если указано отрицательное значение, вместо него используется **0**. **0** отсоединяет подвеску.

## float getLinearSpring () const

Возвращает текущий коэффициент жёсткости подвески. **0** означает, что подвеска не присоединена.
### Возвращаемое значение

Текущий коэффициент жёсткости. Если указано отрицательное значение, вместо него используется **0**. **0** отсоединяет подвеску.
## void setLinearLimitTo ( float to )

Задаёт новый верхний предел хода подвески. Этот предел определяет, насколько далеко соединённое тело может перемещаться вдоль оси joint.
### Аргументы

- *float* **to** - Верхний предел в единицах.

## float getLinearLimitTo () const

Возвращает текущий верхний предел хода подвески. Этот предел определяет, насколько далеко соединённое тело может перемещаться вдоль оси joint.
### Возвращаемое значение

Текущий верхний предел в единицах.
## void setLinearLimitFrom ( float from )

Задаёт новый нижний предел хода подвески. Этот предел определяет, насколько далеко соединённое тело может перемещаться вдоль оси joint.
### Аргументы

- *float* **from** - Нижний предел в единицах.

## float getLinearLimitFrom () const

Возвращает текущий нижний предел хода подвески. Этот предел определяет, насколько далеко соединённое тело может перемещаться вдоль оси joint.
### Возвращаемое значение

Текущий нижний предел в единицах.
## void setLinearDistance ( float distance )

Задаёт новую целевую высоту подвески.
### Аргументы

- *float* **distance** - Высота, в единицах.

## float getLinearDistance () const

Возвращает текущую целевую высоту подвески.
### Возвращаемое значение

Текущая высота, в единицах.
## void setLinearDamping ( float damping )

Задаёт новое линейное затухание подвески.
### Аргументы

- *float* **damping** - Линейное затухание. Если указано отрицательное значение, вместо него используется **0**.

## float getLinearDamping () const

Возвращает текущее линейное затухание подвески.
### Возвращаемое значение

Текущее линейное затухание. Если указано отрицательное значение, вместо него используется **0**.
## void setWorldAxis0 ( const Math:: vec3 & axis0 )

Задаёт новую ось подвески в мировых координатах.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis0** - Ось подвески в мировых координатах.

## Math:: vec3 getWorldAxis0 () const

Возвращает текущую ось подвески в мировых координатах.
### Возвращаемое значение

Текущая ось подвески в мировых координатах.
## void setWorldAxis1 ( const Math:: vec3 & axis1 )

Задаёт новую ось оси колеса (spindle axis) в мировых координатах.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis1** - Ось колеса в мировых координатах.

## Math:: vec3 getWorldAxis1 () const

Возвращает текущую ось колеса в мировых координатах.
### Возвращаемое значение

Текущая ось колеса в мировых координатах.
## void setAxis00 ( const Math:: vec3 & axis00 )

Задаёт новые координаты оси подвески, вдоль которой колесо перемещается вертикально. Это амортизатор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis00** - Ось подвески, в мировых координатах.

## Math:: vec3 getAxis00 () const

Возвращает текущие координаты оси подвески, вдоль которой колесо перемещается вертикально. Это амортизатор.
### Возвращаемое значение

Текущая ось подвески, в мировых координатах.
## void setAxis10 ( const Math:: vec3 & axis10 )

Задаёт новую ось колеса (spindle axis) в координатах рамы (body 0): ось, вокруг которой вращается колесо при движении вперёд (или назад).
![](../../../principles/physics/joints/wheel_joint1.jpg)


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis10** - Ось колеса в координатах рамы (body 0).

## Math:: vec3 getAxis10 () const

Возвращает текущую ось колеса в координатах рамы (body 0): ось, вокруг которой вращается колесо при движении вперёд (или назад).
![](../../../principles/physics/joints/wheel_joint1.jpg)


### Возвращаемое значение

Текущая ось колеса в координатах рамы (body 0).
## void setAxis11 ( const Math:: vec3 & axis11 )

Задаёт новую ось колеса (spindle axis) в координатах колеса (body 1): ось, вокруг которой вращается колесо при повороте (steering).
![](../../../principles/physics/joints/wheel_joint1.jpg)


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **axis11** - Ось колеса в координатах колеса (body 1).

## Math:: vec3 getAxis11 () const

Возвращает текущую ось колеса в координатах колеса (body 1): ось, вокруг которой вращается колесо при повороте (steering).
![](../../../principles/physics/joints/wheel_joint1.jpg)


### Возвращаемое значение

Текущая ось колеса в координатах колеса (body 1).
---

## static JointSuspensionPtr create ( )

Конструктор. Создаёт suspension joint с точкой крепления в начале мировых координат.
## static JointSuspensionPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 )

Конструктор. Создаёт suspension joint, соединяющий два указанных тела. Точка крепления размещается между центрами масс тел.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Рама (frame), соединяемая с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Колесо (wheel), соединяемое с помощью joint.

## static JointSuspensionPtr create ( const Ptr < Body > & body0 , const Ptr < Body > & body1 , const Math:: Vec3 & anchor , const Math:: vec3 & axis0 , const Math:: vec3 & axis1 )

Конструктор. Создаёт suspension joint, соединяющий два указанных тела, с указанными координатами оси подвески и оси колеса и точкой крепления, размещённой в указанных координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body0** - Рама (frame), соединяемая с помощью joint.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Body](../../../api/library/physics/class.body_cpp.md)> &* **body1** - Колесо (wheel), соединяемое с помощью joint.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **anchor** - Координаты точки крепления.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **axis0** - Координаты оси подвески.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **axis1** - Координаты оси колеса.
