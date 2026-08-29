# Класс Unigine::InputEventPadTouchMotion (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии физической сенсорной панели геймпада.


### См. также


- Пример на C++


## Класс InputEventPadTouchMotion

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_DOWN** = 0 | Состояние касания "нажато". |
| **ACTION_MOTION** = 1 | Состояние касания "нажато и перемещается". |
| **ACTION_UP** = 2 | Состояние касания "отпущено". |

### Методы класса

---

## InputEventPadTouchMotion ( )

Конструктор по умолчанию.
## InputEventPadTouchMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события сенсорной панели.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventPadTouchMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , int connection_id , int action , int touch , int finger , float pressure , const Math:: vec2 & position )

Конструктор события сенсорной панели.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *int* **connection_id** - Идентификатор соединения.
- *int* **action** - Тип события сенсорного ввода, одно из значений [ACTION_*](#ACTION_DOWN).
- *int* **touch** - Индекс сенсорной панели геймпада, число от 0 до [total number](../../../api/library/controls/class.inputgamepad_cpp.md#getNumTouches_int) сенсорных панелей.
- *int* **finger** - Индекс пальца, число от 0 до [total number](../../../api/library/controls/class.inputgamepad_cpp.md#getNumTouchFingers_int_int) поддерживаемых пальцев.
- *float* **pressure** - Сила, с которой в данный момент нажат палец.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **position** - Нормализованная позиция касания по осям от (0,0) до (1,1).

## void setConnectionID ( int connectionid )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **connectionid** - Идентификатор соединения.

## int getConnectionID ( ) const

Возвращает идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setAction ( InputEventPadTouchMotion::ACTION action )

Устанавливает тип события сенсорной панели.
### Аргументы

- *[InputEventPadTouchMotion::ACTION](../../../api/library/controls/class.inputeventpadtouchmotion_cpp.md#ACTION)* **action** - Тип события сенсорного ввода, одно из значений [ACTION_*](#ACTION_DOWN).

## InputEventPadTouchMotion::ACTION getAction ( ) const

Возвращает тип события сенсорной панели.
### Возвращаемое значение

Тип события сенсорного ввода, одно из значений [ACTION_*](#ACTION_DOWN).
## void setTouch ( int touch )

Устанавливает индекс сенсорной панели геймпада.
### Аргументы

- *int* **touch** - Индекс сенсорной панели геймпада, число от 0 до [total number](../../../api/library/controls/class.inputgamepad_cpp.md#getNumTouches_int) сенсорных панелей.

## int getTouch ( ) const

Возвращает индекс сенсорной панели геймпада.
### Возвращаемое значение

Индекс сенсорной панели геймпада, число от 0 до [total number](../../../api/library/controls/class.inputgamepad_cpp.md#getNumTouches_int) сенсорных панелей.
## void setTouchFinger ( int finger )

Устанавливает индекс пальца.
### Аргументы

- *int* **finger** - Индекс пальца, число от 0 до [total number](../../../api/library/controls/class.inputgamepad_cpp.md#getNumTouchFingers_int_int) поддерживаемых пальцев.

## int getTouchFinger ( ) const

Возвращает индекс пальца.
### Возвращаемое значение

Индекс пальца, число от 0 до [total number](../../../api/library/controls/class.inputgamepad_cpp.md#getNumTouchFingers_int_int) поддерживаемых пальцев.
## void setPosition ( const Math:: vec2 & position )

Устанавливает позицию касания.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **position** - Нормализованная позиция касания по осям от (0,0) до (1,1).

## Math:: vec2 getPosition ( ) const

Возвращает текущую позицию касания.
### Возвращаемое значение

Нормализованная позиция касания по осям от (0,0) до (1,1).
## void setPressure ( float pressure )

Устанавливает силу, с которой нажат палец.
### Аргументы

- *float* **pressure** - Сила, с которой нажат палец, значение от 0 (не нажат) до 1 (нажат полностью).

## float getPressure ( ) const

Возвращает силу, с которой нажат палец.
### Возвращаемое значение

Сила, с которой в данный момент нажат палец, значение от 0 (не нажат) до 1 (нажат полностью).
