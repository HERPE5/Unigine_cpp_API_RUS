# Класс Unigine::InputEventJoyPovMotion (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии изменения POV-переключателя джойстика.


### См. также


- Пример на C++


## Класс InputEventJoyPovMotion

### Методы класса

---

## InputEventJoyPovMotion ( )

Конструктор по умолчанию.
## InputEventJoyPovMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события изменения POV-переключателя джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventJoyPovMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , int connection_id , int pov , int value )

Конструктор события изменения POV-переключателя джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *int* **connection_id** - Идентификатор соединения.
- *int* **pov** - Индекс POV-переключателя.
- *int* **value** - Позиция POV-переключателя.

## void setConnectionID ( int id )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **id** - Устанавливаемый идентификатор соединения.

## int getConnectionID ( ) const

Возвращает идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setPov ( int pov )

Устанавливает индекс POV-переключателя.
### Аргументы

- *int* **pov** - Индекс POV-переключателя.

## int getPov ( ) const

Возвращает индекс POV-переключателя.
### Возвращаемое значение

Индекс POV-переключателя.
## void setValue ( int value )

Устанавливает позицию POV-переключателя.
### Аргументы

- *int* **value** - Позиция POV-переключателя.

## int getValue ( ) const

Возвращает позицию POV-переключателя.
### Возвращаемое значение

Позиция POV-переключателя.
