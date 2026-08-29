# Класс Unigine::InputEventPadDevice (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии геймпада.


### См. также


- Пример на C++


## Класс InputEventPadDevice

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_CONNECTED** = 0 | Состояние геймпада "подключён". |
| **ACTION_DISCONNECTED** = 1 | Состояние геймпада "отключён". |

### Методы класса

---

## InputEventPadDevice ( )

Конструктор по умолчанию.
## InputEventPadDevice ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события геймпада.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventPadDevice ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventPadDevice::ACTION action , int connection_id , int player_index , const char * model_guid )

Конструктор события геймпада.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventPadDevice::ACTION](../../../api/library/controls/class.inputeventpaddevice_cpp.md#ACTION)* **action** - Тип события геймпада, одно из значений [ACTION_*](#ACTION_CONNECTED).
- *int* **connection_id** - Идентификатор соединения.
- *int* **player_index** - Индекс игрока.
- *const char ** **model_guid** - GUID модели геймпада.

## void setAction ( InputEventPadDevice::ACTION action )

Устанавливает тип события геймпада.
### Аргументы

- *[InputEventPadDevice::ACTION](../../../api/library/controls/class.inputeventpaddevice_cpp.md#ACTION)* **action** - Тип события геймпада, одно из значений [ACTION_*](#ACTION_CONNECTED).

## InputEventPadDevice::ACTION getAction ( ) const

Возвращает тип события геймпада.
### Возвращаемое значение

Тип события геймпада, одно из значений [ACTION_*](#ACTION_CONNECTED).
## void setConnectionID ( int id )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **id** - Идентификатор соединения.

## int getConnectionID ( ) const

Возвращает идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setPlayerIndex ( int index )

Устанавливает индекс игрока.
### Аргументы

- *int* **index** - Индекс игрока.

## int getPlayerIndex ( ) const

Возвращает индекс игрока.
### Возвращаемое значение

Индекс игрока.
## void setModelGUID ( const char * modelguid )

Устанавливает GUID модели геймпада.
### Аргументы

- *const char ** **modelguid** - GUID модели геймпада.

## const char * getModelGUID ( ) const

Возвращает GUID модели геймпада.
### Возвращаемое значение

GUID модели геймпада.
