# Класс Unigine::InputEventMouseWheel (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputEvent


Этот класс обрабатывает информацию о событии колеса мыши.


### См. также


- Пример на C++


## Класс InputEventMouseWheel

### Методы класса

---

## static InputEventMouseWheelPtr create ( )

Конструктор по умолчанию.
## InputEventMouseWheel ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos )

Конструктор события колеса мыши.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.

## InputEventMouseWheel ( unsigned long long timestamp , const Math:: ivec2 & mouse_pos , int wheel , int wheel_h )

Конструктор события колеса мыши.
### Аргументы

- *unsigned long long* **timestamp** - Временная метка события.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **mouse_pos** - Позиция мыши.
- *int* **wheel** - Величина вертикальной прокрутки (положительное значение — от пользователя, отрицательное — к пользователю).
- *int* **wheel_h** - Величина горизонтальной прокрутки (положительное значение — вправо, отрицательное — влево).

## void setWheel ( int wheel )

Устанавливает изменение вертикальной прокрутки мыши.
### Аргументы

- *int* **wheel** - Величина вертикальной прокрутки, положительная от пользователя и отрицательная к пользователю.

## int getWheel ( ) const

Возвращает изменение вертикальной прокрутки мыши.
### Возвращаемое значение

Величина вертикальной прокрутки, положительная от пользователя и отрицательная к пользователю.
## void setWheelHorizontal ( int horizontal )

Устанавливает изменение горизонтальной прокрутки мыши.
### Аргументы

- *int* **horizontal** - Величина горизонтальной прокрутки, положительная вправо и отрицательная влево.

## int getWheelHorizontal ( ) const

Возвращает изменение горизонтальной прокрутки мыши.
### Возвращаемое значение

Величина горизонтальной прокрутки, положительная вправо и отрицательная влево.
