# Класс Unigine::InputEventJoyDevice (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс управляет информацией о событии устройства джойстика.


### См. также


- Пример на C++


## Класс InputEventJoyDevice

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_CONNECTED** = 0 | Состояние джойстика "подключён". |
| **ACTION_DISCONNECTED** = 1 | Состояние джойстика "отключён". |

### Методы класса

---

## InputEventJoyDevice ( )

Конструктор по умолчанию.
## InputEventJoyDevice ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventJoyDevice ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventJoyDevice::ACTION action , int connection_id , int player_index , const char * model_guid )

Конструктор события джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventJoyDevice::ACTION](../../../api/library/controls/class.inputeventjoydevice_cpp.md#ACTION)* **action** - Тип события джойстика, одно из значений [ACTION_*](#ACTION_CONNECTED).
- *int* **connection_id** - Идентификатор соединения.
- *int* **player_index** - Индекс игрока.
- *const char ** **model_guid** - GUID модели джойстика.

## void setAction ( InputEventJoyDevice::ACTION action )

Устанавливает тип события джойстика.
### Аргументы

- *[InputEventJoyDevice::ACTION](../../../api/library/controls/class.inputeventjoydevice_cpp.md#ACTION)* **action** - Тип события джойстика, одно из значений [ACTION_*](#ACTION_CONNECTED).

## InputEventJoyDevice::ACTION getAction ( ) const

Возвращает тип события джойстика.
### Возвращаемое значение

Тип события джойстика, одно из значений [ACTION_*](#ACTION_CONNECTED).
## void setConnectionID ( int id )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **id** - Идентификатор соединения для установки.

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

Устанавливает GUID модели джойстика.
### Аргументы

- *const char ** **modelguid** - GUID модели джойстика.

## const char * getModelGUID ( ) const

Возвращает GUID модели джойстика.
### Возвращаемое значение

GUID модели джойстика.
