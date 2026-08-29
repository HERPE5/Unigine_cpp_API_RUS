# Unigine::WindowEventDpi Class (CPP)

**Header:** #include <UnigineWindowManager.h>

**Inherits from:** WindowEvent


## WindowEventDpi Class

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_DPI_CHANGED** = 0 | Уровень DPI был изменён. |
| **ACTION_SIZE_SCALED** = 1 | Размер окна был масштабирован. |

### Методы класса

---

## WindowEventDpi ( )

Конструктор по умолчанию.
## WindowEventDpi ( unsigned long long timestamp , unsigned long long win_id )

Конструктор события DPI окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, для которого задаётся DPI.

## WindowEventDpi ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos )

Конструктор события DPI окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, для которого задаётся DPI.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## WindowEventDpi ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos , const Math:: ivec2 & position , const Math:: ivec2 & size )

Конструктор события DPI окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, для которого задаётся DPI.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Позиция окна.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Размер окна.

## WindowEventDpi ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos , const Math:: ivec2 & position , const Math:: ivec2 & size , WindowEventDrop::ACTION action , int dpi )

Конструктор события DPI окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, для которого задаётся DPI.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Позиция окна.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Размер окна.
- *[WindowEventDrop::ACTION](../../../api/library/gui/class.windoweventdrop_cpp.md#ACTION)* **action** - Тип действия DPI, выполненного с окном во время события.
- *int* **dpi** - Уровень DPI.

## void setAction ( WindowEventDpi::ACTION action )

Задаёт тип действия DPI, выполненного с окном во время события.
### Аргументы

- *[WindowEventDpi::ACTION](../../../api/library/gui/class.windoweventdpi_cpp.md#ACTION)* **action** - Тип действия DPI, выполненного с окном во время события.

## WindowEventDpi::ACTION getAction ( ) const

Возвращает тип действия DPI, выполненного с окном во время события.
### Возвращаемое значение

Тип действия DPI, выполненного с окном во время события.
## void setDpi ( int dpi )

Задаёт уровень DPI.
### Аргументы

- *int* **dpi** - Уровень DPI.

## int getDpi ( ) const

Возвращает текущий уровень DPI.
### Возвращаемое значение

Уровень DPI.
