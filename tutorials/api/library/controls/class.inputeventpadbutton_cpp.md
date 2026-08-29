# Класс Unigine::InputEventPadButton (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии кнопки геймпада.


### См. также


- Пример на C++


## Класс InputEventPadButton

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_DOWN** = 0 | Состояние кнопки "нажата". |
| **ACTION_UP** = 1 | Состояние кнопки "отпущена". |

### Методы класса

---

## InputEventPadButton ( )

Конструктор по умолчанию.
## InputEventPadButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события ввода кнопки геймпада.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventPadButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventJoyButton::ACTION action , int connection_id , int button )

Конструктор события ввода кнопки геймпада.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventJoyButton::ACTION](../../../api/library/controls/class.inputeventjoybutton_cpp.md#ACTION)* **action** - Тип события ввода кнопки геймпада, одно из значений *[ACTION_*](../../...md#ACTION_DOWN)*.
- *int* **connection_id** - Идентификатор соединения.
- *int* **button** - Индекс кнопки геймпада.

## void setAction ( InputEventPadButton::ACTION action )

Устанавливает тип события ввода кнопки геймпада.
### Аргументы

- *[InputEventPadButton::ACTION](../../../api/library/controls/class.inputeventpadbutton_cpp.md#ACTION)* **action** - Тип события ввода кнопки геймпада, одно из значений *[ACTION_*](../../...md#ACTION_DOWN)*.

## InputEventPadButton::ACTION getAction ( ) const

Возвращает тип события ввода кнопки геймпада.
### Возвращаемое значение

Тип события ввода кнопки геймпада, одно из значений *[ACTION_*](../../...md#ACTION_DOWN)*.
## void setConnectionID ( int id )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **id** - Идентификатор соединения.

## int getConnectionID ( ) const

Возвращает текущий идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setButton ( Input::GAMEPAD_BUTTON button )

Устанавливает кнопку геймпада.
### Аргументы

- *[Input::GAMEPAD_BUTTON](../../../api/library/controls/class.input_cpp.md#GAMEPAD_BUTTON)* **button** - Кнопка геймпада, одно из значений *[Input::GAMEPAD_BUTTON_*](../../../api/library/controls/class.input_cpp.md#GAMEPAD_BUTTON_A)*.

## Input::GAMEPAD_BUTTON getButton ( ) const

Возвращает кнопку геймпада.
### Возвращаемое значение

Кнопка геймпада, одно из значений *[Input::GAMEPAD_BUTTON_*](../../../api/library/controls/class.input_cpp.md#GAMEPAD_BUTTON_A)*.
