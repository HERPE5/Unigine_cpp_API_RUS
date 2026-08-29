# Класс Unigine::InputEventKeyboard (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс управляет информацией о событии клавиатуры.


### См. также


- Пример на C++


## Класс InputEventKeyboard

### Перечисления

## ACTION

| Name | Description |
|---|---|
| **ACTION_DOWN** = 0 | Клавиша клавиатуры удерживается нажатой. |
| **ACTION_REPEAT** = 1 | Клавиша клавиатуры была нажата повторно. |
| **ACTION_UP** = 2 | Клавиша клавиатуры была отпущена. |

### Методы класса

---

## InputEventKeyboard ( )

Конструктор по умолчанию.
## InputEventKeyboard ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventKeyboard::ACTION action , Input::KEY key )

Конструктор события ввода клавиатуры.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventKeyboard::ACTION](../../../api/library/controls/class.inputeventkeyboard_cpp.md#ACTION)* **action** - Выполненное действие.
- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Значение клавиши виртуальной клавиатуры (зависит от языка).

## InputEventKeyboard ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события ввода клавиатуры.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## void setAction ( InputEventKeyboard::ACTION action )

Задаёт действие, которое должно быть выполнено клавиатурой.
### Аргументы

- *[InputEventKeyboard::ACTION](../../../api/library/controls/class.inputeventkeyboard_cpp.md#ACTION)* **action** - Действие, выполняемое клавиатурой.

## InputEventKeyboard::ACTION getAction ( ) const

Возвращает действие, выполняемое клавиатурой.
### Возвращаемое значение

Действие, выполняемое клавиатурой.
## void setKey ( Input::KEY key )

Задаёт зависимое от языка значение клавиши клавиатуры.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Значение клавиши виртуальной клавиатуры (зависит от языка клавиатуры).

## Input::KEY getKey ( ) const

Возвращает зависимое от языка значение клавиши клавиатуры.
### Возвращаемое значение

Значение клавиши виртуальной клавиатуры (зависит от языка клавиатуры).
