# Класс Unigine::InputEventPadAxisMotion (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии изменения оси геймпада.


### См. также


- Пример на C++


## Класс InputEventPadAxisMotion

### Методы класса

---

## InputEventPadAxisMotion ( )

Конструктор по умолчанию.
## InputEventPadAxisMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события изменения оси геймпада.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventPadAxisMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , int connection_id , int axis , float value )

Конструктор события изменения оси геймпада.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *int* **connection_id** - Идентификатор соединения.
- *int* **axis** - Индекс оси геймпада.
- *float* **value** - Значение позиции оси.

## void setConnectionID ( int id )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **id** - Устанавливаемый идентификатор соединения.

## int getConnectionID ( ) const

Возвращает текущий идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setAxis ( Input::GAMEPAD_AXIS axis )

Устанавливает ось геймпада.
### Аргументы

- *[Input::GAMEPAD_AXIS](../../../api/library/controls/class.input_cpp.md#GAMEPAD_AXIS)* **axis** - Ось геймпада, одно из значений *[Input::GAMEPAD_AXIS_*](../../../api/library/controls/class.input_cpp.md#GAMEPAD_AXIS_LEFT_X)*.

## Input::GAMEPAD_AXIS getAxis ( ) const

Возвращает ось геймпада.
### Возвращаемое значение

Ось геймпада, одно из значений *[Input::GAMEPAD_AXIS_*](../../../api/library/controls/class.input_cpp.md#GAMEPAD_AXIS_LEFT_X)*.
## void setValue ( float value )

Устанавливает значение позиции оси.
### Аргументы

- *float* **value** - Значение позиции оси.

## float getValue ( ) const

Возвращает значение позиции оси.
### Возвращаемое значение

Значение позиции оси.
