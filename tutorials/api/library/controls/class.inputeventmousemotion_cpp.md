# Класс Unigine::InputEventMouseMotion (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии движения мыши.


### См. также


- Пример на C++


## Класс InputEventMouseMotion

### Методы класса

---

## InputEventMouseMotion ( )

Конструктор по умолчанию.
## InputEventMouseMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , const Math:: ivec2 & delta )

Конструктор события движения мыши.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **delta** - Изменение позиции мыши относительно предыдущего события.

## InputEventMouseMotion ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события движения мыши.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## void setDelta ( const Math:: ivec2 & delta )

Устанавливает изменение позиции мыши относительно предыдущего события.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **delta** - Изменение позиции мыши относительно предыдущего события.

## Math:: ivec2 getDelta ( ) const

Возвращает изменение позиции мыши относительно предыдущего события.
### Возвращаемое значение

Изменение позиции мыши относительно предыдущего события.
