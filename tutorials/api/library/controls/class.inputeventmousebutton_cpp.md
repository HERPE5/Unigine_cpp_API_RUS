# Класс Unigine::InputEventMouseButton (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс управляет информацией о событии кнопки мыши.


### См. также


- Пример на C++


## Класс InputEventMouseButton

### Перечисления

## ACTION

| Name | Description |
|---|---|
| **ACTION_DOWN** = 0 | Кнопка мыши была нажата. |
| **ACTION_UP** = 1 | Кнопка мыши была отпущена. |

### Методы класса

---

## InputEventMouseButton ( )

Конструктор по умолчанию.
## InputEventMouseButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события ввода кнопки мыши.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventMouseButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventMouseButton::ACTION action , Input::MOUSE_BUTTON button )

Конструктор события ввода кнопки мыши.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventMouseButton::ACTION](../../../api/library/controls/class.inputeventmousebutton_cpp.md#ACTION)* **action** - Выполненное действие.
- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Кнопка мыши.

## void setAction ( InputEventMouseButton::ACTION action )

Задаёт действие, которое должно быть выполнено кнопкой мыши.
### Аргументы

- *[InputEventMouseButton::ACTION](../../../api/library/controls/class.inputeventmousebutton_cpp.md#ACTION)* **action** - Действие, выполняемое кнопкой мыши.

## InputEventMouseButton::ACTION getAction ( ) const

Возвращает действие, выполняемое кнопкой мыши.
### Возвращаемое значение

Действие, выполняемое кнопкой мыши.
## void setButton ( Input::MOUSE_BUTTON button )

Задаёт кнопку мыши для события ввода.
### Аргументы

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Кнопка мыши, одно из значений [MOUSE_BUTTON_*](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON).

## Input::MOUSE_BUTTON getButton ( ) const

Возвращает кнопку мыши для события ввода.
### Возвращаемое значение

Кнопка мыши, одно из значений [MOUSE_BUTTON_*](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON).
