# Palette Class (CPP)

**Header:** #include <UniginePalette.h>


Эта структура представляет собой набор значений для 12 основных цветов цветового спектра, используемый для определения [saturation and hue adjustment](../../../editor2/settings/render_settings/color/index.md#saturation_palette).


Ниже показан пример использования:


```cpp
#include <UniginePalette.h>

Palette p = Palette(0.5f);
Render::setColorCorrectionHueShift(p);

```


## Palette Class

### Перечисления

## Color

| Name | Description |
|---|---|
| **RED** = 0 | Красный цвет. |
| **ORANGE** = 1 | Оранжевый цвет. |
| **YELLOW** = 2 | Жёлтый цвет. |
| **CHARTREUSE** = 3 | Цвет шартрез. |
| **GREEN** = 4 | Зелёный цвет. |
| **SPRINGGREEN** = 5 | Весенне-зелёный цвет. |
| **CYAN** = 6 | Голубой цвет. |
| **AZURE** = 7 | Лазурный цвет. |
| **BLUE** = 8 | Синий цвет. |
| **VIOLET** = 9 | Фиолетовый цвет. |
| **MAGENTA** = 10 | Пурпурный цвет. |
| **ROSE** = 11 | Розовый цвет. |
| **SIZE** = 12 | Количество цветов. |

### Методы класса

---

## Palette ( )

Конструктор. Инициализирует структуру нулевыми значениями.
## Palette ( const Palette & palette )

Конструктор. Инициализирует структуру, используя указанный Palette.
### Аргументы

- *const [Palette](../../../api/library/common/class.palette_cpp.md) &* **palette** - Исходный Palette.

## Palette ( const float (&)[12] palette )

Конструктор. Инициализирует структуру, используя указанный массив значений float.
### Аргументы

- *const float (&)[12]* **palette** - Исходный массив из 12 значений float.

## Palette ( float value )

Конструктор. Инициализирует структуру, используя указанное значение float для всех значений.
### Аргументы

- *float* **value** - Значение, задаваемое для всех значений цветов.

## Palette & operator= ( const Palette & palette )

Выполняет присваивание структуры. Целевая палитра = исходная палитра.
### Аргументы

- *const [Palette](../../../api/library/common/class.palette_cpp.md) &* **palette** - Исходная палитра.

### Возвращаемое значение

Результат.
## bool operator== ( const Palette & palette ) const

Проверяет, совпадают ли две палитры.
### Аргументы

- *const [Palette](../../../api/library/common/class.palette_cpp.md) &* **palette** - Вторая палитра.

### Возвращаемое значение

Возвращает true, если палитры совпадают; иначе false.
## bool operator== ( const float (&)[12] palette ) const

Проверяет, совпадают ли две палитры.
### Аргументы

- *const float (&)[12]* **palette** - Вторая палитра, представленная массивом из 12 значений float.

### Возвращаемое значение

Возвращает true, если палитры совпадают; иначе false.
## bool operator== ( float value ) const

Проверяет, равны ли все значения палитры указанному значению.
### Аргументы

- *float* **value** - Значение для проверки.

### Возвращаемое значение

Возвращает true, если все значения палитры равны указанному значению; иначе false.
## bool operator!= ( const Palette & palette ) const

Проверяет, различаются ли две палитры.
### Аргументы

- *const [Palette](../../../api/library/common/class.palette_cpp.md) &* **palette** - Вторая палитра.

### Возвращаемое значение

Возвращает true, если палитры различаются; иначе false.
## bool operator!= ( const float (&)[12] palette ) const

Проверяет, различаются ли две палитры.
### Аргументы

- *const float (&)[12]* **palette** - Вторая палитра, представленная массивом из 12 значений float.

### Возвращаемое значение

Возвращает true, если палитры различаются; иначе false.
## bool operator!= ( float value ) const

Проверяет, отличается ли хотя бы одно значение палитры от указанного значения.
### Аргументы

- *float* **value** - Значение для проверки.

### Возвращаемое значение

Возвращает true, если хотя бы одно значение палитры отличается от указанного значения; иначе false.
## void clear ( float value = 0.0f )

Задаёт указанное значение всем значениям цветов.
### Аргументы

- *float* **value** - Новое значение.

## void copy ( const Palette & src )

Копирует все значения из указанной палитры.
### Аргументы

- *const [Palette](../../../api/library/common/class.palette_cpp.md) &* **src** - Исходная палитра.
