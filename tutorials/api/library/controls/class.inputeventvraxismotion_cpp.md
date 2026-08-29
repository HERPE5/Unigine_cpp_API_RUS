# Класс Unigine::InputEventVRAxisMotion (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии изменения оси VR-контроллера.


## Класс InputEventVRAxisMotion

### Методы класса

---

## InputEventVRAxisMotion ( )

Конструктор по умолчанию.
## InputEventVRAxisMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события изменения оси VR-контроллера.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventVRAxisMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , int connection_id , int axis , float value )

Конструктор события изменения оси VR-контроллера.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *int* **connection_id** - Идентификатор соединения.
- *int* **axis** - Индекс оси VR-контроллера.
- *float* **value** - Значение позиции оси.

## void setConnectionID ( int connectionid )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **connectionid** - Устанавливаемый идентификатор соединения.

## int getConnectionID ( ) const

Возвращает текущий идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setAxis ( int axis )

Устанавливает ось VR-контроллера.
### Аргументы

- *int* **axis** - Ось VR-контроллера.

## int getAxis ( ) const

Возвращает ось VR-контроллера.
### Возвращаемое значение

Ось VR-контроллера.
## void setValue ( float value )

Устанавливает значение позиции оси.
### Аргументы

- *float* **value** - Значение позиции оси.

## float getValue ( ) const

Возвращает значение позиции оси.
### Возвращаемое значение

Значение позиции оси.
