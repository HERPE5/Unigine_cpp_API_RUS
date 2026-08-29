# Класс Unigine::InputEventJoyAxisMotion (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии изменения оси джойстика.


### См. также


- Пример на C++


## Класс InputEventJoyAxisMotion

### Методы класса

---

## InputEventJoyAxisMotion ( )

Конструктор по умолчанию.
## InputEventJoyAxisMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события изменения оси джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventJoyAxisMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , int connection_id , int axis , float value )

Конструктор события изменения оси джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *int* **connection_id** - Идентификатор соединения.
- *int* **axis** - Индекс оси джойстика.
- *float* **value** - Значение позиции оси.

## void setConnectionID ( int id )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **id** - Идентификатор соединения.

## int getConnectionID ( ) const

Возвращает текущий идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setAxis ( int axis )

Устанавливает индекс оси джойстика.
### Аргументы

- *int* **axis** - Индекс оси джойстика.

## int getAxis ( ) const

Устанавливает индекс оси джойстика.
### Возвращаемое значение

Индекс оси джойстика.
## void setValue ( float value )

Устанавливает значение позиции оси.
### Аргументы

- *float* **value** - Значение позиции оси.

## float getValue ( ) const

Возвращает значение позиции оси.
### Возвращаемое значение

Значение позиции оси.
