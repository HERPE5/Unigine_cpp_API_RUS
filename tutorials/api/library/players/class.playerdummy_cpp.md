# Unigine.PlayerDummy Class (CPP)

**Header:** #include <UniginePlayers.h>

**Inherits from:** Player


Этот класс используется для создания фиктивной камеры (dummy), представляющей собой простой viewport в мир. Она не имеет физических свойств и не может сталкиваться с объектами.


### См. также


- C++ sample
- C# component samples:

  -
  -


## PlayerDummy Class

### Методы класса

---

## static PlayerDummyPtr create ( )

Конструктор. Создаёт новый dummy player.
## void setViewDirection ( const Math:: vec3 & direction )

Задаёт новый вектор направления взгляда Player.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Новый задаваемый вектор направления взгляда.

## Math:: vec3 getViewDirection ( ) const

Возвращает текущий вектор направления взгляда Player.
### Возвращаемое значение

Текущий вектор направления взгляда Player.
## static int type ( )

Возвращает тип player.
### Возвращаемое значение

[type identifier](../../../api/library/nodes/class.node_cpp.md#PLAYER_DUMMY) PlayerDummy.
