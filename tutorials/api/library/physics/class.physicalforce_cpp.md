# Unigine.PhysicalForce Class (CPP)

**Header:** #include <UniginePhysicals.h>

**Inherits from:** Physical


Этот класс используется для симуляции точечной силы, которая притягивает физические тела [up to or away from](#setAttractor_float_void). Она также может [rotate](#setRotator_float_void) их вокруг центра силы.


> **Notice:** Physical force может воздействовать только на тело [*cloth*](../../../api/library/physics/class.bodycloth_cpp.md), [*rope*](../../../api/library/physics/class.bodyrope_cpp.md) или [*rigid*](../../../api/library/physics/class.bodyrigid_cpp.md). Если используется rigid body, ему также должна быть назначена [shape](../../../api/library/physics/shapes_cpp.md).


### См. также


- Статья *[Physical Force](../../../objects/effects/physicals/physical_force/index.md)*

  -
  -


## PhysicalForce Class

### Методы класса

---

## static PhysicalForcePtr create ( float radius )

Конструктор. Создаёт узел physical force с указанным радиусом в единицах.
### Аргументы

- *float* **radius** - Радиус узла physical force в единицах.

## void setAttenuation ( float attenuation )

Обновляет коэффициент затухания для physical force.
### Аргументы

- *float* **attenuation** - Новый коэффициент затухания.

## float getAttenuation ( )

Возвращает текущий коэффициент затухания для physical force.
### Возвращаемое значение

Коэффициент затухания.
## void setAttractor ( float attractor )

Обновляет силу притяжения, применяемую к объектам в радиусе physical force.
### Аргументы

- *float* **attractor** - Новое значение силы притяжения. Положительные значения отталкивают объекты от точки силы, отрицательные — притягивают к ней.

## float getAttractor ( )

Возвращает текущую силу притяжения, применяемую к объектам в радиусе physical force. Положительные значения отталкивают объекты от точки силы, отрицательные — притягивают к ней.
### Возвращаемое значение

Значение силы притяжения.
## void setRadius ( float radius )

Обновляет радиус применения physical force.
### Аргументы

- *float* **radius** - Новый радиус в единицах. Если указано отрицательное значение, вместо него используется 0.

## float getRadius ( )

Возвращает текущий радиус, заданный для применения physical force.
### Возвращаемое значение

Радиус в единицах.
## void setRotator ( float rotator )

Обновляет силу вращения, применяемую к объектам в радиусе physical force.
### Аргументы

- *float* **rotator** - Новое значение силы вращения. Задайте положительное значение для вращения по часовой стрелке или отрицательное — против часовой стрелки.

## float getRotator ( )

Возвращает текущую силу вращения, применяемую к объектам в радиусе physical force.
### Возвращаемое значение

Значение силы вращения.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Physical](../../../api/library/physics/class.physical_cpp.md).
