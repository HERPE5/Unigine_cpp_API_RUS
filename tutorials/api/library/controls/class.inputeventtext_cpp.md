# Класс Unigine::InputEventText (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс управляет информацией о текстовом событии.


## Класс InputEventText

### Методы класса

---

## InputEventText ( )

Конструктор по умолчанию.
## InputEventText ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события текстового ввода.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventText ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , unsigned int unicode )

Конструктор события текстового ввода.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *unsigned int* **unicode** - Символ Unicode.

## void setUnicode ( unsigned int unicode )

Задаёт вводимый символ.
### Аргументы

- *unsigned int* **unicode** - Символ Unicode.

## unsigned int getUnicode ( ) const

Возвращает вводимый символ.
### Возвращаемое значение

Символ Unicode.
