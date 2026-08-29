# Unigine::BodyRope Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** BodyParticles


Этот класс используется для симуляции [ropes, cables, wires](../../../principles/physics/bodies/rope/index.md) и т.д. Это тело использует [Mass-Spring model](../../../principles/physics/bodies/rope/index.md#model) для симуляции, обеспечивая способность каната [fold, stretch](../../../principles/physics/bodies/rope/index.md#stretching) и даже [tear](../../../principles/physics/bodies/rope/index.md#tearing). В отличие от плоской [BodyCloth](../../../api/library/physics/class.bodycloth_cpp.md), эти тела всегда сохраняют то же количество полигонов в поперечном сечении, что и в исходном меше каната. Это означает, что канат при скручивании никогда не будет выглядеть плоским.


#### См. также


- Пример использования [Creating Pylons and Wires Using Ropes](../../../code/usage/ropes_creating_pylons_and_wires/index_cpp.md), демонстрирующий назначение rope body динамическому mesh-объекту и настройку его параметров

  -
  -
  -
  -


## BodyRope Class

### Методы класса

---

## static BodyRopePtr create ( )

Конструктор. Создаёт rope body со свойствами по умолчанию.
## static BodyRopePtr create ( const Ptr < Object > & object )

Конструктор. Создаёт rope body со свойствами по умолчанию для указанного объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, представленный новым rope body.
