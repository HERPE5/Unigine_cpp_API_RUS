# Unigine::ArrayVector Class (CPP)

**Header:** #include <UnigineInterpreter.h>


Позволяет использовать [vectors](../../../code/uniginescript/language/containers/index.md#vector) UnigineScript.


## ArrayVector Class

### Методы класса

---

## ArrayVector ( const ArrayVector & vector )

Конструктор копирования.
### Аргументы

- *const [ArrayVector](../../../api/library/containers/class.arrayvector_cpp.md) &* **vector** - Вектор.

## void set ( int index , const Variable & v ) const

Устанавливает элемент по индексу.
### Аргументы

- *int* **index** - Индекс элемента.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Устанавливаемый элемент.

## static ArrayVector get ( void * interpreter , const Variable & id )

Возвращает вектор из UnigineScript.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **id** - ID вектора.

### Возвращаемое значение

Вектор.
## const Variable & get ( int index ) const

Возвращает элемент по индексу.
### Аргументы

- *int* **index** - Индекс элемента.

### Возвращаемое значение

Элемент.
## void append ( const Variable & v ) const

Добавляет элемент в вектор.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Элемент.

## void append ( int pos , const Variable & v ) const

Добавляет элемент в вектор в заданную позицию.
### Аргументы

- *int* **pos** - Индекс позиции.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Элемент.

## void clear ( ) const

Очищает все элементы вектора.
## int find ( const Variable & v ) const

Возвращает индекс заданного элемента.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Элемент.

### Возвращаемое значение

Индекс, если найден; в противном случае -1.
## ArrayVector & operator= ( const ArrayVector & vector )

Оператор присваивания для вектора.
### Аргументы

- *const [ArrayVector](../../../api/library/containers/class.arrayvector_cpp.md) &* **vector** - Присваиваемый вектор.

## const Variable & operator[] ( int index ) const

Доступ к вектору.
### Аргументы

- *int* **index** - Индекс элемента.

### Возвращаемое значение

Элемент.
## void remove ( int pos ) const

Удаляет элемент из заданной позиции вектора.
### Аргументы

- *int* **pos** - Индекс позиции.

## void resize ( int size ) const

Изменяет размер вектора.
### Аргументы

- *int* **size** - Новая ёмкость вектора.

## int size ( ) const

Возвращает длину вектора.
### Возвращаемое значение

Длина вектора.
