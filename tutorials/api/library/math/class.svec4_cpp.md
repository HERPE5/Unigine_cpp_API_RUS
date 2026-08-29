# Unigine::Math::svec4 Struct (CPP)

**Header:** #include <UnigineMathLibSVec4.h>


Этот класс представляет вектор с 4 компонентами типа unsigned short.


## svec4 Struct

### Методы класса

---

## svec4 ( )

Конструктор по умолчанию. Создаёт нулевой вектор.
## svec4 ( const svec4& v )

Конструктор. Инициализирует вектор путём копирования заданного исходного вектора.
### Аргументы

- *const svec4&* **v** - Исходный вектор.

## svec4 ( unsigned short x , unsigned short y , unsigned short z , unsigned short w )

Конструктор. Инициализирует вектор заданными значениями типа unsigned short.
### Аргументы

- *unsigned short* **x** - Компонент X вектора.
- *unsigned short* **y** - Компонент Y вектора.
- *unsigned short* **z** - Компонент Z вектора.
- *unsigned short* **w** - Компонент W вектора.

## svec4 ( const vec4& v , float scale )

Конструктор. Инициализирует вектор заданным исходным вектором [vec4](../../../api/library/math/class.vec4_cpp.md) и множителем масштаба.
### Аргументы

- *const vec4&* **v** - Исходный вектор.
- *float* **scale** - Масштаб.

## explicit svec4 ( unsigned short v )

Конструктор. Инициализирует вектор заданным значением: x=v, y=v, z=v, w=v.
### Аргументы

- *unsigned short* **v** - Исходное значение.

## explicit svec4 ( const unsigned short* v )

Конструктор. Инициализирует вектор заданным указателем на массив элементов типа unsigned short: x=v[0], y=v[1], z=v[2], w=v[3].
### Аргументы

- *const unsigned short** **v** - Указатель на массив элементов типа unsigned short.

## explicit svec4 ( const dvec4& v )

Конструктор. Инициализирует вектор заданным исходным вектором [dvec4](../../../api/library/math/class.dvec4_cpp.md).
### Аргументы

- *const dvec4&* **v** - Исходный вектор.

## explicit svec4 ( const ivec4& v )

Конструктор. Инициализирует вектор заданным исходным вектором [ivec4](../../../api/library/math/class.ivec4_cpp.md).
### Аргументы

- *const ivec4&* **v** - Исходный вектор.

## explicit svec4 ( const vec4& v )

Конструктор. Инициализирует вектор заданным исходным вектором [vec4](../../../api/library/math/class.vec4_cpp.md).
### Аргументы

- *const vec4&* **v** - Исходный вектор.

## void set ( unsigned short val )

Устанавливает компоненты вектора равными указанному значению: x=val, y=val, z=val, w=val.
### Аргументы

- *unsigned short* **val** - Значение.

## void set ( unsigned short x_ , unsigned short y_ , unsigned short z_ , unsigned short w_ )

Устанавливает вектор по компонентам.
### Аргументы

- *unsigned short* **x_** - Компонент X вектора.
- *unsigned short* **y_** - Компонент Y вектора.
- *unsigned short* **z_** - Компонент Z вектора.
- *unsigned short* **w_** - Компонент W вектора.

## void set ( const svec4& val )

Устанавливает вектор равным указанному вектору.
### Аргументы

- *const svec4&* **val** - Исходный вектор.

## void set ( const unsigned short* val )

Устанавливает вектор, используя массив элементов типа unsigned short: x=val[0], y=val[1], z=val[2], w=val[3].
### Аргументы

- *const unsigned short** **val** - Указатель на массив элементов типа unsigned short.

## void set ( const vec4& val , float scale )

Устанавливает вектор, используя заданный вектор [vec4](../../../api/library/math/class.vec4_cpp.md) и множитель масштаба.
### Аргументы

- *const vec4&* **val** - Исходный вектор.
- *float* **scale** - Масштаб.

## unsigned short * get ( )

Возвращает указатель на вектор.
### Возвращаемое значение

Указатель на вектор.
## const unsigned short * get ( ) const

Возвращает константный указатель на вектор.
### Возвращаемое значение

Указатель на вектор.
## void get ( unsigned short* val ) const

Устанавливает массив значений типа unsigned short равным вектору.
### Аргументы

- *unsigned short** **val** - Вектор, который необходимо установить.

## svec4 & operator= ( const svec4& val )

Выполняет присваивание вектора. Целевой вектор = Исходный вектор.
### Аргументы

- *const svec4&* **val** - Исходный вектор.

### Возвращаемое значение

Результат.
## const unsigned short * operator const unsigned short * ( ) const

Выполняет преобразование типа в const unsigned short *.
## void * operator void * ( )

Выполняет преобразование типа в void *.
## const void * operator const void * ( ) const

Выполняет преобразование типа в const void *.
## unsigned short * operator unsigned short * ( )

Выполняет преобразование типа в unsigned short *.
## unsigned short operator[] ( int i ) const

Выполняет доступ к элементу вектора по ссылке, используя заданный индекс элемента.
### Аргументы

- *int* **i** - Индекс элемента вектора.

### Возвращаемое значение

Ссылка на элемент вектора.
## unsigned short & operator[] ( int i )

Выполняет доступ к элементу вектора, используя заданный индекс элемента.
### Аргументы

- *int* **i** - Индекс элемента вектора.

### Возвращаемое значение

Элемент вектора.
