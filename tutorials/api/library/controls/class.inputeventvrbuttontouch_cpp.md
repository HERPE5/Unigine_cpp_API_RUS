# Класс Unigine::InputEventVRButtonTouch (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии касания кнопки VR-контроллера.


## Класс InputEventVRButtonTouch

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_DOWN** = 0 | Состояние кнопки "нажата". |
| **ACTION_UP** = 1 | Состояние кнопки "отпущена". |

### Методы класса

---

## InputEventVRButtonTouch ( )

Конструктор по умолчанию.
## InputEventVRButtonTouch ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события касания кнопки VR-контроллера.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventVRButtonTouch ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventVRButtonTouch::ACTION action , int connection_id , Input::VR_BUTTON button )

Конструктор события касания кнопки VR-контроллера.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventVRButtonTouch::ACTION](../../../api/library/controls/class.inputeventvrbuttontouch_cpp.md#ACTION)* **action** - Тип события касания кнопки VR-контроллера, одно из значений [ACTION_*](#ACTION_DOWN).
- *int* **connection_id** - Идентификатор соединения.
- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Индекс касания кнопки VR-контроллера.

## void setAction ( InputEventVRButtonTouch::ACTION action )

Устанавливает тип события касания кнопки VR-контроллера.
### Аргументы

- *[InputEventVRButtonTouch::ACTION](../../../api/library/controls/class.inputeventvrbuttontouch_cpp.md#ACTION)* **action** - Тип события касания кнопки VR-контроллера, одно из значений [ACTION_*](#ACTION_DOWN).

## InputEventVRButtonTouch::ACTION getAction ( ) const

Возвращает тип события касания кнопки VR-контроллера.
### Возвращаемое значение

Тип события касания кнопки VR-контроллера, одно из значений [ACTION_*](#ACTION_DOWN).
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
