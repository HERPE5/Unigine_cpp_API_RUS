# Класс Unigine::InputEventVRDevice (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии VR-устройства.


## Класс InputEventVRDevice

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_CONNECTED** = 0 | Состояние устройства "подключено". |
| **ACTION_DISCONNECTED** = 1 | Состояние устройства "отключено". |

### Методы класса

---

## InputEventVRDevice ( )

Конструктор по умолчанию.
## InputEventVRDevice ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события VR-устройства.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventVRDevice ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventVRDevice::ACTION action , int connection_id , InputVRDevice::TYPE type )

Конструктор события VR-устройства.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventVRDevice::ACTION](../../../api/library/controls/class.inputeventvrdevice_cpp.md#ACTION)* **action** - Тип события VR-устройства, одно из значений [ACTION_*](#ACTION_CONNECTED).
- *int* **connection_id** - Идентификатор соединения.
- *[InputVRDevice::TYPE](../../../api/library/controls/class.inputvrdevice_cpp.md#TYPE)* **type** - Тип VR-устройства.

## void setAction ( InputEventVRDevice::ACTION action )

Устанавливает тип события VR-устройства.
### Аргументы

- *[InputEventVRDevice::ACTION](../../../api/library/controls/class.inputeventvrdevice_cpp.md#ACTION)* **action** - Тип события VR-устройства, одно из значений [ACTION_*](#ACTION_CONNECTED).

## InputEventVRDevice::ACTION getAction ( ) const

Возвращает тип события VR-устройства.
### Возвращаемое значение

Тип события VR-устройства, одно из значений [ACTION_*](#ACTION_CONNECTED).
## void setConnectionID ( int connectionid )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **connectionid** - Идентификатор соединения.

## int getConnectionID ( ) const

Возвращает текущий идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setType ( InputEventVRDevice::TYPE type )

Устанавливает тип VR-устройства.
### Аргументы

- *[InputEventVRDevice::TYPE](../../../api/library/controls/class.inputeventvrdevice_cpp.md#TYPE)* **type** - Тип VR-устройства.

## InputEventVRDevice::TYPE getType ( ) const

Возвращает тип VR-устройства.
### Возвращаемое значение

Тип VR-устройства.
