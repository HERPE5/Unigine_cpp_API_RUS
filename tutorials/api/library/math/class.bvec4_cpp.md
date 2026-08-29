# Unigine::Math::bvec4 Struct (CPP)

**Header:** #include <UnigineMathLibBVec4.h>


Этот класс представляет вектор из 4 компонентов типа byte (unsigned char). Этот вектор используется для параметров цвета вершин.


## bvec4 Struct

### Методы класса

---

## bvec4 ( )

Конструктор по умолчанию. Создаёт нулевой вектор.
## explicit bvec4 ( unsigned char v )

Конструктор. Инициализирует вектор заданным скалярным значением: x=v, y=v, z=v, w=v.
### Аргументы

- *unsigned char* **v** - Скаляр.

## bvec4 ( unsigned char x , unsigned char y , unsigned char z , unsigned char w )

Конструктор. Инициализирует вектор заданными значениями типа unsigned char.
### Аргументы

- *unsigned char* **x** - Компонент X вектора.
- *unsigned char* **y** - Компонент Y вектора.
- *unsigned char* **z** - Компонент Z вектора.
- *unsigned char* **w** - Компонент W вектора.

## explicit bvec4 ( const unsigned char* v )

Конструктор. Инициализирует вектор заданным указателем на массив элементов типа unsigned char: x=v[0], y=v[1], z=v[2], w=v[3].
### Аргументы

- *const unsigned char** **v** - Указатель на массив элементов типа unsigned char.

## bvec4 ( const bvec4& v )

Конструктор. Инициализирует вектор путём копирования заданного исходного вектора.
### Аргументы

- *const bvec4&* **v** - Исходный вектор.

## explicit bvec4 ( const vec4& v )

Конструктор. Инициализирует вектор заданным исходным вектором [vec4](../../../api/library/math/class.vec4_cpp.md).
### Аргументы

- *const vec4&* **v** - Исходный вектор.

## explicit bvec4 ( const dvec4& v )

Конструктор. Инициализирует вектор заданным исходным вектором [dvec4](../../../api/library/math/class.dvec4_cpp.md).
### Аргументы

- *const dvec4&* **v** - Исходный вектор.

## explicit bvec4 ( const ivec4& v )

Конструктор. Инициализирует вектор заданным исходным вектором [ivec4](../../../api/library/math/class.ivec4_cpp.md).
### Аргументы

- *const ivec4&* **v** - Исходный вектор.

## bvec4 ( const vec4& v , float scale )

Конструктор. Инициализирует вектор заданным исходным вектором [vec4](../../../api/library/math/class.vec4_cpp.md) и множителем масштаба.
### Аргументы

- *const vec4&* **v** - Исходный вектор.
- *float* **scale** - Масштаб.

## void set ( unsigned char x_ , unsigned char y_ , unsigned char z_ , unsigned char w_ )

Устанавливает вектор по компонентам.
### Аргументы

- *unsigned char* **x_** - Компонент X вектора.
- *unsigned char* **y_** - Компонент Y вектора.
- *unsigned char* **z_** - Компонент Z вектора.
- *unsigned char* **w_** - Компонент W вектора.

## void set ( const unsigned char* val )

Устанавливает вектор, используя массив элементов типа unsigned char: x=val[0], y=val[1], z=val[2], w=val[3].
### Аргументы

- *const unsigned char** **val** - Указатель на массив элементов типа unsigned char.

## void set ( unsigned char val )

Устанавливает компоненты вектора равными указанному скалярному значению: x=val, y=val, z=val, w=val.
### Аргументы

- *unsigned char* **val** - Скалярное значение.

## void set ( const bvec4& val )

Устанавливает вектор равным указанному вектору.
### Аргументы

- *const bvec4&* **val** - Исходный вектор.

## void set ( const vec4& val , float scale )

Устанавливает вектор, используя заданный вектор [vec4](../../../api/library/math/class.vec4_cpp.md) и множитель масштаба.
### Аргументы

- *const vec4&* **val** - Исходный вектор.
- *float* **scale** - Масштаб.

## unsigned char * get ( )

Возвращает указатель на вектор.
### Возвращаемое значение

Указатель на вектор.
## const unsigned char * get ( ) const

Возвращает константный указатель на вектор.
### Возвращаемое значение

Указатель на вектор.
## void get ( unsigned char* val ) const

Возвращает вектор, сохраняя его в аргументе.
### Аргументы

- *unsigned char** **val** - Указатель на вектор для сохранения полученных данных.

## unsigned char * operator unsigned char * ( ) const

Выполняет преобразование типа в unsigned char *.
### Возвращаемое значение

Указатель на значение.
## const unsigned char * operator const unsigned char * ( ) const

Выполняет преобразование типа в const unsigned char *.
### Возвращаемое значение

Указатель на значение.
## void * operator void * ( )

Выполняет преобразование типа в void *.
## const void * operator const void * ( ) const

Выполняет преобразование типа в const void *.
## unsigned char & operator[] ( int i )

Выполняет доступ к элементу вектора, используя заданный индекс элемента.
### Аргументы

- *int* **i** - Индекс элемента вектора.

### Возвращаемое значение

Элемент вектора.
## unsigned char operator[] ( int i ) const

Выполняет доступ к элементу вектора по ссылке, используя заданный индекс элемента.
### Аргументы

- *int* **i** - Индекс элемента вектора.

### Возвращаемое значение

Ссылка на элемент вектора.
## bvec4 & operator= ( const bvec4 & val )

Выполняет присваивание вектора. Целевой вектор = Исходный вектор.
### Аргументы

- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **val** - Исходный вектор.

### Возвращаемое значение

Результат.
## int compare ( const bvec4 & v0 , const bvec4 & v1 )

Выполняет сравнение на равенство.
### Аргументы

- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v0** - Первое значение.
- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v1** - Второе значение.

### Возвращаемое значение

**1**, если первый вектор равен второму; в противном случае **0**.
## int operator== ( const bvec4 & v0 , const bvec4 & v1 )

Выполняет сравнение на равенство.
### Аргументы

- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v0** - Первое значение.
- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v1** - Второе значение.

### Возвращаемое значение

**1**, если первый вектор равен второму; в противном случае **0**.
## int operator!= ( const bvec4 & v0 , const bvec4 & v1 )

Сравнение на неравенство.
### Аргументы

- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v0** - Первое значение.
- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v1** - Второе значение.

### Возвращаемое значение

**1**, если первый вектор не равен второму; в противном случае **0**.
## bvec4 min ( const bvec4 & v0 , const bvec4 & v1 )

Создаёт новый минимальный вектор на основе входных данных.
### Аргументы

- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v0** - Первое значение.
- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v1** - Второе значение.

### Возвращаемое значение

Вектор, каждый компонент которого является минимумом соответствующих компонентов исходных векторов.
## bvec4 max ( const bvec4 & v0 , const bvec4 & v1 )

Создаёт новый максимальный вектор на основе входных данных.
### Аргументы

- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v0** - Первое значение.
- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v1** - Второе значение.

### Возвращаемое значение

Вектор, каждый компонент которого является максимумом соответствующих компонентов исходных векторов.
## bvec4 clamp ( const bvec4 & v , const bvec4 & v0 , const bvec4 & v1 )

Ограничивает вектор на основе векторов нижнего и верхнего пределов.
### Аргументы

- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v** - Вектор для ограничения.
- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v0** - Нижний предел ограничения.
- *const [bvec4](../../../api/library/math/class.bvec4_cpp.md) &* **v1** - Верхний предел ограничения.

### Возвращаемое значение

Вектор, каждый компонент исходного вектора которого ограничен диапазоном, заданным соответствующими компонентами нижнего и верхнего векторов.
