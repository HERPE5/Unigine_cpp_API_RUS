# Класс Unigine::InputEventJoyButton (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии кнопки джойстика.


### См. также


- Пример на C++


## Класс InputEventJoyButton

### Перечисления

## ACTION

| Имя | Описание |
|---|---|
| **ACTION_DOWN** = 0 | Состояние кнопки "нажата". |
| **ACTION_UP** = 1 | Состояние кнопки "отпущена". |

### Методы класса

---

## InputEventJoyButton ( )

Конструктор по умолчанию.
## InputEventJoyButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события ввода кнопки джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventJoyButton ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , InputEventJoyButton::ACTION action , int connection_id , int button )

Конструктор события ввода кнопки джойстика.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *[InputEventJoyButton::ACTION](../../../api/library/controls/class.inputeventjoybutton_cpp.md#ACTION)* **action** - Тип события ввода кнопки джойстика, одно из значений [ACTION_*](#ACTION_DOWN).
- *int* **connection_id** - Идентификатор соединения.
- *int* **button** - Индекс кнопки джойстика.

## void setAction ( InputEventJoyButton::ACTION action )

Устанавливает тип события ввода кнопки джойстика.
### Аргументы

- *[InputEventJoyButton::ACTION](../../../api/library/controls/class.inputeventjoybutton_cpp.md#ACTION)* **action** - Тип события ввода кнопки джойстика, одно из значений [ACTION_*](#ACTION_DOWN).

## InputEventJoyButton::ACTION getAction ( ) const

Возвращает тип события ввода кнопки джойстика.
### Возвращаемое значение

Тип события ввода кнопки джойстика, одно из значений [ACTION_*](#ACTION_DOWN).
## void setConnectionID ( int id )

Устанавливает идентификатор соединения.
### Аргументы

- *int* **id** - Идентификатор соединения.

## int getConnectionID ( ) const

Возвращает текущий идентификатор соединения.
### Возвращаемое значение

Идентификатор соединения.
## void setButton ( int button )

Устанавливает индекс кнопки джойстика.
### Аргументы

- *int* **button** - Индекс кнопки джойстика.

## int getButton ( ) const

Возвращает индекс кнопки джойстика.
### Возвращаемое значение

Индекс кнопки джойстика.
