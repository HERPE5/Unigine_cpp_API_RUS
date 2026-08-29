# Unigine::AnimationBind Class (CPP)

**Header:** #include <UnigineAnimation.h>


Этот класс используется для управления [bindings](../../../../principles/animations/index.md#animation_binding) [animation objects](../../../../principles/animations/index.md#animation_object) из кода. Объекты анимации служат прокси в последовательностях анимации и привязываются к конкретным объектам (материалам, узлам, параметрам свойств или runtime-объектам) на этапе воспроизведения.


## AnimationBind Class

### Перечисления

## TYPE

Тип привязки.
| Имя | Описание |
|---|---|
| **ANIMATION_BIND** = 0 | Обычная привязка. |
| **ANIMATION_BIND_NODE** = 1 | Привязка к узлу. |
| **ANIMATION_BIND_PROPERTY_PARAMETER** = 2 | Привязка к параметру свойства. |
| **ANIMATION_BIND_MATERIAL** = 3 | Привязка к материалу. |
| **ANIMATION_BIND_RUNTIME** = 4 | Привязка к runtime-объекту. |

### Методы класса

## AnimationBind::TYPE getType () const

Возвращает текущий тип привязки.
### Возвращаемое значение

Текущий тип привязки.
## const char * getTypeName () const

Возвращает имя текущего типа привязки.
### Возвращаемое значение

Имя текущего типа привязки.
