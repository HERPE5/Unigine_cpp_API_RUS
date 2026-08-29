# Unigine::WindowEventDrop Class (CPP)

**Header:** #include <UnigineWindowManager.h>

**Inherits from:** WindowEvent


Этот класс используется для обработки события перетаскивания текста или файла в окно.


## WindowEventDrop Class

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_ITEMS_DROP_BEGIN** = 0 | Начинается новый набор перетаскиваний. |
| **ACTION_ITEM_DROP** = 1 | Событие перетаскивания текста/файла. |
| **ACTION_ITEMS_DROP_END** = 2 | Текущий набор перетаскиваний завершён. |

### Методы класса

---

## WindowEventDrop ( )

Конструктор по умолчанию.
## WindowEventDrop ( unsigned long long timestamp , unsigned long long win_id )

Конструктор события перетаскивания окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, на которое было выполнено перетаскивание, если есть.

## WindowEventDrop ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos )

Конструктор события перетаскивания окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, на которое было выполнено перетаскивание, если есть.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Position of the mouse.

## WindowEventDrop ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos , const Math:: ivec2 & position , const Math:: ivec2 & size )

Конструктор события перетаскивания окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, на которое было выполнено перетаскивание, если есть.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Position of the mouse.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Position of the window.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Size of the window.

## WindowEventDrop ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos , const Math:: ivec2 & position , const Math:: ivec2 & size , WindowEventDrop::ACTION action , const char * item_path )

Конструктор события перетаскивания окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Окно, на которое было выполнено перетаскивание, если есть.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Position of the mouse.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Position of the window.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Size of the window.
- *[WindowEventDrop::ACTION](../../../api/library/gui/class.windoweventdrop_cpp.md#ACTION)* **action** - Тип действия перетаскивания, выполненного с окном во время события.
- *const char ** **item_path**

## void setAction ( WindowEventDrop::ACTION action )

Задаёт тип действия перетаскивания, выполненного с окном во время события.
### Аргументы

- *[WindowEventDrop::ACTION](../../../api/library/gui/class.windoweventdrop_cpp.md#ACTION)* **action** - Тип действия перетаскивания, выполненного с окном во время события.

## WindowEventDrop::ACTION getAction ( ) const

Возвращает тип действия перетаскивания, выполненного с окном во время события.
### Возвращаемое значение

Тип действия перетаскивания, выполненного с окном во время события.
## void setPath ( const char * path )

Задаёт абсолютный путь к перетащенному файлу.
### Аргументы

- *const char ** **path** - Абсолютный путь к перетащенному файлу.

## const char * getPath ( ) const

Возвращает абсолютный путь к перетащенному файлу.
### Возвращаемое значение

Абсолютный путь к перетащенному файлу.
