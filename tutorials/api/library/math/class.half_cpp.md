# Unigine::Math::half Struct (CPP)

**Header:** #include <UnigineMathLibCommon.h>


Этот класс представляет тип half (16-битное число с плавающей точкой).


## half Class

### Методы класса

---

## half ( )

Конструктор по умолчанию. Создаёт нулевое значение.
## half ( const half& h )

Конструктор. Инициализирует значение заданным значением типа half.
### Аргументы

- *const half&* **h** - Значение типа half.

## explicit half ( int i )

Конструктор. Инициализирует значение заданным целочисленным значением.
### Аргументы

- *int* **i** - Целочисленное значение.

## explicit half ( float f )

Конструктор. Инициализирует значение заданным значением типа float.
### Аргументы

- *float* **f** - Значение типа float.

## void setFloat ( float f )

Задаёт значение с использованием заданного значения типа float.
### Аргументы

- *float* **f** - Значение типа float.

## float getFloat ( ) const

Возвращает значение типа float.
### Возвращаемое значение

Значение типа float.
## float operator float ( ) const

Выполняет преобразование типа в float.
### Возвращаемое значение

Значение типа float.
## unsigned short operator unsigned short ( ) const

Выполняет преобразование типа в unsigned short.
## half & operator= ( half v )

Выполняет операцию присваивания. Назначение = Источник.
### Аргументы

- *[half](../../../api/library/math/class.half_cpp.md)* **v** - Источник.

## half & operator= ( float f )

Выполняет операцию присваивания. Назначение = Источник.
### Аргументы

- *float* **f** - Источник.
