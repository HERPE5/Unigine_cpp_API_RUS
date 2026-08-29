# Unigine::WindowEvent Class (CPP)

**Header:** #include <UnigineWindowManager.h>


Класс для обработки событий окна. Позволяет получать тип, время создания, позицию, размер и id окна, для которого было создано событие.


## WindowEvent Class

### Перечисления

## TYPE

| Имя | Описание |
|---|---|
| **WINDOW_EVENT** = 0 | Изменение состояния окна. |
| **WINDOW_EVENT_GENERIC** = 1 | Событие трансформации окна (например, перемещение, изменение размера, сворачивание и т.д.). |
| **WINDOW_EVENT_DROP** = 2 | Событие перетаскивания файла или папки в окно. |
| **WINDOW_EVENT_DPI** = 3 | Событие изменения уровня DPI. |
| **NUM_WINDOW_EVENTS** = 4 | Счётчик событий. |

### Методы класса

---

## WindowEvent::TYPE getType ( ) const

Возвращает тип события окна.
### Возвращаемое значение

Тип события окна, одно из значений [TYPE.WINDOW_EVENT](#TYPE).
## const char * getTypeName ( ) const

Возвращает имя события окна.
### Возвращаемое значение

Имя события окна.
## void setTimestamp ( unsigned long long timestamp )

Задаёт временную метку события.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события, в миллисекундах.

## unsigned long long getTimestamp ( ) const

Возвращает временную метку события.
### Возвращаемое значение

Временная метка события, в миллисекундах.
## void setWinID ( unsigned long long winid )

Задаёт идентификатор окна.
### Аргументы

- *unsigned long long* **winid** - Идентификатор окна.

## unsigned long long getWinID ( ) const

Возвращает идентификатор окна.
### Возвращаемое значение

Идентификатор окна.
## void setMousePosition ( const Math:: ivec2 & position )

Задаёт позицию мыши в момент создания события.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Позиция мыши в момент создания события.

## Math:: ivec2 getMousePosition ( ) const

Возвращает позицию мыши в момент создания события.
### Возвращаемое значение

Позиция мыши в момент создания события.
## void setPosition ( const Math:: ivec2 & position )

Задаёт позицию окна в момент создания события.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Позиция окна в момент создания события.

## Math:: ivec2 getPosition ( ) const

Возвращает позицию окна в момент создания события.
### Возвращаемое значение

Позиция окна в момент создания события.
## void setSize ( const Math:: ivec2 & size )

Задаёт размер окна в момент создания события.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Размер окна в момент создания события.

## Math:: ivec2 getSize ( ) const

Возвращает размер окна в момент создания события.
### Возвращаемое значение

Размер окна в момент создания события.
## void setWindow ( const Ptr < EngineWindow > & window )

Задаёт окно, для которого было создано событие.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Окно, для которого было создано событие.

## Ptr < EngineWindow > getWindow ( ) const

Возвращает окно, для которого было создано событие.
### Возвращаемое значение

Окно, для которого было создано событие.
