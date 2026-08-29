# Unigine::WindowEventGeneric Class (CPP)

**Header:** #include <UnigineWindowManager.h>

**Inherits from:** WindowEvent


Этот класс используется для получения типа события окна.


## WindowEventGeneric Class

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_RESIZED** = 0 | Размер окна был изменён. Этому событию всегда предшествует [ACTION_SIZE_CHANGED](#ACTION_SIZE_CHANGED). |
| **ACTION_MOVED** = 1 | Окно было перемещено. |
| **ACTION_SIZE_CHANGED** = 2 | Размер окна изменился либо в результате вызова API, либо через изменение размера окна системой или пользователем. За этим событием следует [ACTION_RESIZED](#ACTION_RESIZED), если размер был изменён внешним событием, т.е. пользователем или менеджером окон. |
| **ACTION_FOCUS_GAINED** = 3 | Окно получило фокус клавиатуры. |
| **ACTION_FOCUS_LOST** = 4 | Окно потеряло фокус клавиатуры. |
| **ACTION_MOUSE_ENTER** = 5 | Окно получило фокус мыши. |
| **ACTION_MOUSE_LEAVE** = 6 | Окно потеряло фокус мыши. |
| **ACTION_SHOWN** = 7 | Окно было показано. |
| **ACTION_HIDDEN** = 8 | Окно было скрыто. |
| **ACTION_MINIMIZED** = 9 | Окно было свёрнуто. |
| **ACTION_MAXIMIZED** = 10 | Окно было развёрнуто. |
| **ACTION_RESTORED** = 11 | Окно было восстановлено до нормального размера и позиции. |
| **ACTION_CLOSE** = 12 | Менеджер окон запрашивает закрытие окна. |
| **ACTION_UNSTACK_MOVE** = 13 | Окно было извлечено из стека и вытянуто из группы. |

### Методы класса

---

## WindowEventGeneric ( )

Конструктор по умолчанию.
## WindowEventGeneric ( unsigned long long timestamp , unsigned long long win_id )

Конструктор общего события окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Идентификатор окна.

## WindowEventGeneric ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos )

Конструктор общего события окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Идентификатор окна.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## WindowEventGeneric ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos , const Math:: ivec2 & position , const Math:: ivec2 & size )

Конструктор общего события окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Идентификатор окна.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Позиция окна.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Размер окна.

## WindowEventGeneric ( unsigned long long timestamp , unsigned long long win_id , const Math:: ivec2 & mouse_pos , const Math:: ivec2 & position , const Math:: ivec2 & size , WindowEventGeneric::ACTION action )

Конструктор общего события окна.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *unsigned long long* **win_id** - Идентификатор окна.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **position** - Позиция окна.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Размер окна.
- *[WindowEventGeneric::ACTION](../../../api/library/gui/class.windoweventgeneric_cpp.md#ACTION)* **action** - Тип общего действия, выполненного с окном во время события.

## void setAction ( WindowEventGeneric::ACTION action )

Задаёт тип общего действия, выполненного с окном во время события.
### Аргументы

- *[WindowEventGeneric::ACTION](../../../api/library/gui/class.windoweventgeneric_cpp.md#ACTION)* **action** - Тип общего действия, выполненного с окном во время события.

## WindowEventGeneric::ACTION getAction ( ) const

Возвращает тип общего действия, выполненного с окном во время события.
### Возвращаемое значение

Тип общего действия, выполненного с окном во время события.
