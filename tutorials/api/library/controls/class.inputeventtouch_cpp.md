# Класс Unigine::InputEventTouch (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии касания.


### См. также


- Пример на C++


## Класс InputEventTouch

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_DOWN** = 0 | Состояние касания "нажато". |
| **ACTION_MOTION** = 1 | Состояние касания "нажато и перемещается". |
| **ACTION_UP** = 2 | Состояние касания "отпущено". |

### Методы класса

---

## InputEventTouch ( )

Конструктор по умолчанию.
## InputEventTouch ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события касания.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventTouch ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventTouch::ACTION action , long long device_id , long long touch_id )

Конструктор события касания.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventTouch::ACTION](../../../api/library/controls/class.inputeventtouch_cpp.md#ACTION)* **action** - Тип события касания, одно из значений [ACTION_*](#ACTION_DOWN).
- *long long* **device_id** - Идентификатор устройства.
- *long long* **touch_id** - Идентификатор касания.

## InputEventTouch ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventTouch::ACTION action , long long device_id , long long touch_id , const Math:: ivec2 & pos , const Math:: ivec2 & delta , float pressure )

Конструктор события касания.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventTouch::ACTION](../../../api/library/controls/class.inputeventtouch_cpp.md#ACTION)* **action** - Тип события касания, одно из значений [ACTION_*](#ACTION_DOWN).
- *long long* **device_id** - Идентификатор устройства.
- *long long* **touch_id** - Идентификатор касания.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **pos** - Позиция касания.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **delta** - Изменение позиции касания относительно предыдущего события.
- *float* **pressure** - Сила, с которой в данный момент нажат палец.

## void setAction ( InputEventTouch::ACTION action )

Устанавливает тип события касания.
### Аргументы

- *[InputEventTouch::ACTION](../../../api/library/controls/class.inputeventtouch_cpp.md#ACTION)* **action** - Тип события касания, одно из значений [ACTION_*](#ACTION_DOWN).

## InputEventTouch::ACTION getAction ( ) const

Возвращает тип события касания.
### Возвращаемое значение

Тип события касания, одно из значений [ACTION_*](#ACTION_DOWN).
## void setDeviceID ( long long id )

Устанавливает идентификатор устройства касания.
### Аргументы

- *long long* **id** - Идентификатор устройства.

## long long getDeviceID ( ) const

Возвращает текущий идентификатор устройства касания.
### Возвращаемое значение

Идентификатор устройства.
## void setTouchID ( long long id )

Устанавливает идентификатор касания.
### Аргументы

- *long long* **id** - Идентификатор касания.

## long long getTouchID ( ) const

Возвращает текущий идентификатор касания.
### Возвращаемое значение

Идентификатор касания.
## void setPosition ( const Math:: ivec2 & pos )

Устанавливает позицию касания.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **pos** - Позиция касания.

## Math:: ivec2 getPosition ( ) const

Возвращает текущую позицию касания.
### Возвращаемое значение

Позиция касания.
## void setDelta ( const Math:: ivec2 & delta )

Устанавливает изменение позиции мыши относительно предыдущего события.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **delta** - Изменение позиции мыши относительно предыдущего события.

## Math:: ivec2 getDelta ( ) const

Возвращает изменение позиции мыши относительно предыдущего события.
### Возвращаемое значение

Изменение позиции мыши относительно предыдущего события.
## void setPressure ( float pressure )

Устанавливает силу, с которой нажат палец.
### Аргументы

- *float* **pressure** - Сила, с которой нажат палец.

## float getPressure ( ) const

Возвращает силу, с которой нажат палец.
### Возвращаемое значение

Сила, с которой в данный момент нажат палец.
