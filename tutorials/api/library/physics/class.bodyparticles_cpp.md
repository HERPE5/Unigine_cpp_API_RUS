# Unigine::BodyParticles Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Body


BodyParticles — это базовый класс для классов [BodyCloth](../../../api/library/physics/class.bodycloth_cpp.md) и [BodyRope](../../../api/library/physics/class.bodyrope_cpp.md). Он использует [mass-spring simulation model](../../../principles/physics/bodies/cloth/index.md#model), т.е. частицы, соединённые внутренними joints. Частицы имеют [sphere shape](#setRadius_float_void) и характеризуются [position](#setParticlePosition_int_Vec3_void), [mass](#setParticleMass_int_float_void) и [velocity](#setParticleVelocity_int_vec3_void). Общая [mass](#setMass_float_void) всей ткани распределяется между ними. К частицам можно прикладывать [force](#addParticleForce_int_vec3_void) или [impulse](#addParticleImpulse_int_vec3_void). Внутренние joints могут [stretched](../../../principles/physics/bodies/cloth/index.md#stretching) ([linear](#setLinearRestitution_float_void) и [angular](#setAngularRestitution_float_void) отдельно), либо линейные joints также можно [scaled](#setLinearStretch_float_void), что даёт такой же эффект растяжения. При растяжении на заданное расстояние joints [torn](../../../principles/physics/bodies/cloth/index.md#tearing) (расстояние задаётся отдельно для [linear](#setLinearThreshold_float_void) и [angular](#setAngularThreshold_float_void) joints).


### См. также


- Пример использования [Creating and Attaching a Cloth](../../../code/usage/cloth_particle_joint/index_cpp.md), демонстрирующий настройку параметров rope


## BodyParticles Class

### Перечисления

## ITERATIONS_MODE

Режим итераций. Определяет способ вычисления количества итераций для решения ограничений тела частиц.
| Имя | Описание |
|---|---|
| **ITERATIONS_MODE_OVERRIDE** = 0 | В этом режиме результирующее количество итераций равно значению [Iterations](#setNumIterations_int_void), заданному для тела. |
| **ITERATIONS_MODE_MULTIPLICATION** = 1 | В этом режиме результирующее количество итераций равно [value set for the body](#setNumIterations_int_void), умноженному на [global physics iterations number](../../../editor2/settings/physics_global/index.md#iterations). |

### Методы класса

---

## void setAngularRestitution ( float restitution )

Задаёт упругость (restitution) внутренних joints тела при угловом складывании треугольников, образованных частицами, относительно друг друга.
### Аргументы

- *float* **restitution** - Угловая упругость joints. Указанное значение ограничивается диапазоном **[0;1.0]**.

## float getAngularRestitution ( ) const

Возвращает текущую упругость внутренних joints тела при угловом складывании треугольников, образованных частицами, относительно друг друга.
### Возвращаемое значение

Угловая упругость joints.
## void setAngularThreshold ( float threshold )

Задаёт порог углового складывания треугольников частиц, соединённых внутренними joints. При превышении этого порога joints разрываются.
### Аргументы

- *float* **threshold** - Порог углового складывания joints. Если указано отрицательное значение, вместо него используется **0**.

## float getAngularThreshold ( ) const

Возвращает текущий порог углового складывания треугольников частиц, соединённых внутренними joints. При превышении этого порога joints разрываются.
### Возвращаемое значение

Порог углового складывания joints.
## void setCollision ( int collision )

Задаёт значение, указывающее, включено ли столкновение с телом.
### Аргументы

- *int* **collision** - Положительное значение, чтобы включить столкновение, **0** — чтобы отключить.

## int getCollision ( ) const

Возвращает значение, указывающее, включено ли столкновение с телом.
### Возвращаемое значение

Положительное значение, если столкновение включено, **0**, если отключено.
## void setCollisionMask ( int mask )

Задаёт битовую маску столкновений для тела. Два объекта сталкиваются, если у обоих совпадающие маски.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getCollisionMask ( ) const

Возвращает битовую маску столкновений для тела. Два объекта сталкиваются, если у обоих совпадающие маски.
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## void setDistance ( float distance )

Задаёт расстояние симуляции тела.
### Аргументы

- *float* **distance** - Расстояние симуляции. Если указано отрицательное значение, вместо него используется **0**.

## float getDistance ( ) const

Возвращает текущее расстояние симуляции тела.
### Возвращаемое значение

Расстояние симуляции.
## void setFriction ( float friction )

Задаёт трение тела при контакте с другими поверхностями.
### Аргументы

- *float* **friction** - Трение тела. Если указано отрицательное значение, вместо него используется **0**.

## float getFriction ( ) const

Возвращает текущее трение тела при контакте с другими поверхностями.
### Возвращаемое значение

Трение тела.
## void setLinearDamping ( float damping )

Задаёт значение, указывающее, насколько уменьшается линейная скорость частиц со временем.
### Аргументы

- *float* **damping** - Значение линейного затухания. Если указано отрицательное значение, вместо него используется **0**.

## float getLinearDamping ( ) const

Возвращает значение, указывающее, насколько уменьшается линейная скорость частиц со временем.
### Возвращаемое значение

Значение линейного затухания.
## void setLinearRestitution ( float restitution )

Задаёт упругость внутренних joints тела при линейном растяжении.
### Аргументы

- *float* **restitution** - Линейная упругость joints. Указанное значение ограничивается диапазоном **[0;1.0]**.

## float getLinearRestitution ( ) const

Возвращает текущую упругость внутренних joints тела при линейном растяжении.
### Возвращаемое значение

Линейная упругость joints.
## void setLinearStretch ( float stretch )

Задаёт масштаб длины линейных joints (относительно топологии исходного меша).
### Аргументы

- *float* **stretch** - Масштаб растяжения для линейных joints. Если указано отрицательное значение, вместо него используется **0**.

## float getLinearStretch ( ) const

Возвращает текущий масштаб длины линейных joints (относительно топологии исходного меша).
### Возвращаемое значение

Масштаб растяжения для линейных joints.
## void setLinearThreshold ( float threshold )

Задаёт порог линейного растяжения внутренних joints тела. При превышении этого порога joints разрываются.
### Аргументы

- *float* **threshold** - Порог линейного растяжения. Если указано отрицательное значение, вместо него используется **0**.

## float getLinearThreshold ( ) const

Возвращает текущее линейное растяжение внутренних joints тела. При превышении этого порога joints разрываются.
### Возвращаемое значение

Порог линейного растяжения joints.
## void setMass ( float mass )

Задаёт массу тела.
### Аргументы

- *float* **mass** - Масса тела. Если указано отрицательное значение, вместо него используется **0**.

## float getMass ( ) const

Возвращает текущую массу тела.
### Возвращаемое значение

Масса тела.
## void setNumIterations ( int iterations )

Задаёт количество итераций, используемых для решения внутренних joints между частицами. Обратите внимание, что при слишком низком значении точность расчётов пострадает.
### Аргументы

- *int* **iterations** - Количество итераций. Если указано неположительное значение, вместо него используется **1**.

## int getNumIterations ( ) const

Возвращает текущее количество итераций, используемых для решения внутренних joints между частицами.
### Возвращаемое значение

Количество итераций.
## int getNumParticles ( ) const

Возвращает общее количество частиц, составляющих тело.
### Возвращаемое значение

Количество частиц.
## void setParticleMass ( int num , float mass )

Задаёт массу для указанной частицы.
### Аргументы

- *int* **num** - Номер частицы.
- *float* **mass** - Масса частицы.

## float getParticleMass ( int num ) const

Возвращает текущую массу указанной частицы.
### Аргументы

- *int* **num** - Номер частицы.

### Возвращаемое значение

Масса частицы.
## void setParticlePosition ( int num , const Math:: Vec3 & position )

Задаёт позицию указанной частицы тела.
### Аргументы

- *int* **num** - Номер частицы.
- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция частицы в мировых координатах.

## Math:: Vec3 getParticlePosition ( int num ) const

Возвращает текущую позицию указанной частицы.
### Аргументы

- *int* **num** - Номер частицы.

### Возвращаемое значение

Позиция частицы в мировых координатах.
## void setParticleVelocity ( int num , const Math:: vec3 & velocity )

Задаёт скорость указанной частицы.
### Аргументы

- *int* **num** - Номер частицы.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **velocity** - Скорость частицы.

## Math:: vec3 getParticleVelocity ( int num ) const

Возвращает текущую скорость указанной частицы.
### Аргументы

- *int* **num** - Номер частицы.

### Возвращаемое значение

Скорость частицы.
## void setRadius ( float radius )

Задаёт радиус частиц, составляющих тело и представленных сферическими формами.
### Аргументы

- *float* **radius** - Радиус сферических частиц.

## float getRadius ( ) const

Возвращает текущий радиус частиц, составляющих тело и представленных сферическими формами.
### Возвращаемое значение

Радиус сферических частиц.
## void setRestitution ( float restitution )

Задаёт упругость (restitution) тела при отскоке.
### Аргументы

- *float* **restitution** - Упругость тела. Указанное значение ограничивается диапазоном **[0;1.0]**.

## float getRestitution ( ) const

Возвращает текущую упругость тела при отскоке.
### Возвращаемое значение

Упругость тела.
## void setRigidity ( float rigidity )

Задаёт жёсткость движения внутренних joints тела, т.е. насколько интерполированные линейная и угловая скорости всех joints влияют на скорости каждого отдельного joint.
### Аргументы

- *float* **rigidity** - Жёсткость взаимодействия joints. Указанное значение ограничивается диапазоном **[0;1.0]**:

  - При значении **0** joints двигаются независимо.
  - При значении **1** joints двигаются равномерно, так как интерполированная скорость значительно изменяет скорости каждого joint.

## float getRigidity ( ) const

Возвращает текущую жёсткость движения внутренних joints тела, т.е. насколько интерполированные линейная и угловая скорости всех joints влияют на скорости каждого отдельного joint.
### Возвращаемое значение

Жёсткость движения joints:
- При значении **0** joints двигаются независимо.
- При значении **1** joints двигаются равномерно, так как интерполированная скорость значительно изменяет скорости каждого joint.


## void addParticleForce ( int num , const Math:: vec3 & force )

Прикладывает силу к указанной частице. Проинтегрированные силы применяются после вызова обновления.
### Аргументы

- *int* **num** - Номер частицы.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **force** - Величина прикладываемой силы.

## void addParticleImpulse ( int num , const Math:: vec3 & impulse )

Прикладывает импульс к указанной частице. Импульсы немедленно влияют на скорости частиц.
### Аргументы

- *int* **num** - Номер частицы.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **impulse** - Величина прикладываемого импульса.

## void setIterationsMode ( BodyParticles::ITERATIONS_MODE mode )

Задаёт режим итераций, используемый для тела частиц. Режим определяет, как вычисляется количество итераций для решения ограничений тела частиц. Этот метод добавляет гибкость в тонкой настройке производительности и качества симуляции для каждого тела частиц.
### Аргументы

- *[BodyParticles::ITERATIONS_MODE](../../../api/library/physics/class.bodyparticles_cpp.md#ITERATIONS_MODE)* **mode** - Режим итераций, используемый для тела частиц:

  - **OVERRIDE** - результирующее количество итераций равно [value set for the body](#setNumIterations_int_void).
  - **MULTIPLICATION** - результирующее количество итераций равно [value set for the body](#setNumIterations_int_void), умноженному на [global physics iterations number](../../../editor2/settings/physics_global/index.md#iterations).

## BodyParticles::ITERATIONS_MODE getIterationsMode ( ) const

Возвращает текущий режим итераций, используемый для тела частиц. Режим определяет, как вычисляется количество итераций для решения ограничений тела частиц. Этот метод добавляет гибкость в тонкой настройке производительности и качества симуляции для каждого тела частиц.
### Возвращаемое значение

Текущий режим итераций тела частиц:
- **OVERRIDE** - результирующее количество итераций равно [value set for the body](#setNumIterations_int_void).
- **MULTIPLICATION** - результирующее количество итераций равно [value set for the body](#setNumIterations_int_void), умноженному на [global physics iterations number](../../../editor2/settings/physics_global/index.md#iterations).
