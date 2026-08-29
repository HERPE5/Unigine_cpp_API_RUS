# Unigine::Vector::ConstIterator Class (CPP)

**Header:** #include <UnigineVector.h>


## Vector::ConstIterator Class

### Методы класса

---

## DataTypeType Definition

### Описание

Полное объявление:
 *typedef Type Unigine::Vector< Type >::ConstIterator::DataType*


### Возвращаемое значение

 Type
---

## const Type & get ( ) const

Возвращает указатель на узел итератора.
### Возвращаемое значение

Указатель на узел итератора.
## ConstIterator ( )

Конструктор по умолчанию.
## ConstIterator ( const Iterator & it )

Конструктор копирования.
### Аргументы

- *const Iterator &* **it** - Итератор.

## int operator!= ( const typename Vector < Type >::Iterator & it ) const

Проверяет, различаются ли два итератора.
### Аргументы

- *const typename [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Type >::Iterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы не совпадают; иначе 0.
## int operator!= ( const ConstIterator & it ) const

Проверяет, различаются ли два итератора.
### Аргументы

- *const ConstIterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы не совпадают; иначе 0.
## const Type & operator* ( ) const

Возвращает ссылку на узел итератора.
### Возвращаемое значение

Ссылка на узел итератора.
## ConstIterator operator+ ( int n ) const

Увеличивает позицию итератора.
### Аргументы

- *int* **n** - Приращение итератора.

### Возвращаемое значение

Итератор, указывающий на следующий элемент.
## ConstIterator & operator++ ( )

Увеличивает позицию итератора.
### Возвращаемое значение

Итератор, указывающий на следующий элемент.
## ConstIterator operator++ ( )

Увеличивает позицию итератора.
### Возвращаемое значение

Итератор, указывающий на текущий элемент.
## ConstIterator & operator+= ( int n )

Увеличивает позицию итератора.
### Аргументы

- *int* **n** - Приращение итератора.

### Возвращаемое значение

Итератор, указывающий на следующий элемент.
## ConstIterator operator- ( int n ) const

Уменьшает позицию итератора.
### Аргументы

- *int* **n** - Уменьшение итератора.

### Возвращаемое значение

Итератор, указывающий на предыдущий элемент.
## int operator- ( const Iterator & it ) const

Возвращает расстояние между итераторами.
### Аргументы

- *const Iterator &* **it** - Второй итератор.

### Возвращаемое значение

Расстояние между итераторами.
## int operator- ( const ConstIterator & it ) const

Возвращает расстояние между итераторами.
### Аргументы

- *const ConstIterator &* **it** - Второй итератор.

### Возвращаемое значение

Расстояние между итераторами.
## ConstIterator & operator-= ( int n )

Уменьшает позицию итератора.
### Аргументы

- *int* **n** - Уменьшение итератора.

### Возвращаемое значение

Итератор, указывающий на предыдущий элемент.
## const Type * operator-> ( ) const

Возвращает указатель на узел итератора.
### Возвращаемое значение

Узел итератора.
## ConstIterator & operator= ( const ConstIterator & it )

Оператор присваивания для итератора.
### Аргументы

- *const ConstIterator &* **it** - Итератор.

## int operator== ( const typename Vector < Type >::Iterator & it ) const

Проверяет, совпадают ли два итератора.
### Аргументы

- *const typename [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< Type >::Iterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы совпадают; иначе 0.
## int operator== ( const ConstIterator & it ) const

Проверяет, совпадают ли два итератора.
### Аргументы

- *const ConstIterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы совпадают; иначе 0.
## ~ConstIterator ( )

Деструктор.
