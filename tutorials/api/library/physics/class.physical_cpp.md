# Unigine.Physical Class (CPP)

**Header:** #include <UniginePhysicals.h>

**Inherits from:** Node


Этот класс используется для создания physicals, представляющих невидимую силу, воздействующую на физические [bodies](../../../api/library/physics/class.body_cpp.md) с коллизионными [shapes](../../../api/library/physics/class.shape_cpp.md) и совпадающей [physical mask](../../../api/library/physics/class.body_cpp.md#setPhysicalMask_int_void).


## Physical Class

### Методы класса

---

## void setPhysicalMask ( int mask )

Задаёт битовую маску для физических взаимодействий. Объект Physical будет взаимодействовать с другим объектом, если у обоих совпадающие маски.
### Аргументы

- *int* **mask** - Целочисленное значение, каждый бит которого используется для задания битовой маски.

## int getPhysicalMask ( )

Возвращает битовую маску для физических взаимодействий. Объект Physical будет взаимодействовать с другим объектом, если у обоих совпадающие маски.
### Возвращаемое значение

Целочисленное значение, каждый бит которого используется для задания битовой маски.
