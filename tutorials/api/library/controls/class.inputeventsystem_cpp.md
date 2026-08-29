# Класс Unigine::InputEventSystem (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает системные события, такие как изменение языка ввода раскладки клавиатуры.


## Класс InputEventSystem

### Перечисления

## ACTION

Действия системного события.
| Имя | Описание |
|---|---|
| **ACTION_KEYBOARD_LAYOUT_CHANGED** = 0 | Раскладка клавиатуры изменена. |

### Методы класса

---

## InputEventSystem ( )

Конструктор по умолчанию.
## InputEventSystem ( unsigned int timestamp , const Math:: ivec2 & mouse_pos )

Конструктор по умолчанию.
### Аргументы

- *unsigned int* **timestamp** - Временная метка события (время, когда произошло событие).
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Координаты позиции курсора мыши по осям X и Y.

## InputEventSystem ( unsigned int timestamp , const Math:: ivec2 & mouse_pos , InputEventSystem::ACTION action )

Конструктор по умолчанию.
### Аргументы

- *unsigned int* **timestamp** - Временная метка события (время, когда произошло событие).
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Координаты позиции курсора мыши по осям X и Y.
- *[InputEventSystem::ACTION](../../../api/library/controls/class.inputeventsystem_cpp.md#ACTION)* **action** - Действие системного события.

## void setAction ( InputEventSystem::ACTION action )

Устанавливает действие для системного события.
### Аргументы

- *[InputEventSystem::ACTION](../../../api/library/controls/class.inputeventsystem_cpp.md#ACTION)* **action** - Новое действие, устанавливаемое для системного события.

## InputEventSystem::ACTION getAction ( ) const

Возвращает действие системного события.
### Возвращаемое значение

Текущее действие системного события.
