# Класс Unigine::InputEventVRButton (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии кнопки VR-контроллера.


## Класс InputEventVRButton

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_DOWN** = 0 | Состояние кнопки "нажата". |
| **ACTION_UP** = 1 | Состояние кнопки "отпущена". |

### Методы класса

---

## InputEventVRButton ( )

Конструктор по умолчанию.
## InputEventVRButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события ввода кнопки VR-контроллера.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventVRButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventVRButton::ACTION action , int connection_id , Input::VR_BUTTON button )

Конструктор события ввода кнопки VR-контроллера.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventVRButton::ACTION](../../../api/library/controls/class.inputeventvrbutton_cpp.md#ACTION)* **action** - Тип события ввода кнопки VR-контроллера, одно из значений [ACTION_*](#ACTION_DOWN).
- *int* **connection_id** - Идентификатор соединения.
- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Индекс кнопки VR-контроллера.

## void setAction ( InputEventVRButton::ACTION action )

Устанавливает тип события ввода кнопки VR-контроллера.
### Аргументы

- *[InputEventVRButton::ACTION](../../../api/library/controls/class.inputeventvrbutton_cpp.md#ACTION)* **action** - Тип события ввода кнопки VR-контроллера, одно из значений [ACTION_*](#ACTION_DOWN).

## InputEventVRButton::ACTION getAction ( ) const

Возвращает тип события ввода кнопки VR-контроллера.
### Возвращаемое значение

Тип события ввода кнопки VR-контроллера, одно из значений [ACTION_*](#ACTION_DOWN).
## void setConnectionID ( int connectionid )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **connectionid** - Идентификатор соединения.

## int getConnectionID ( ) const

Возвращает текущий идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setButton ( Input::VR_BUTTON button )

Устанавливает индекс кнопки VR-контроллера.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Индекс кнопки VR-контроллера.

## Input::VR_BUTTON getButton ( ) const

Возвращает индекс кнопки VR-контроллера.
### Возвращаемое значение

Индекс кнопки VR-контроллера.
