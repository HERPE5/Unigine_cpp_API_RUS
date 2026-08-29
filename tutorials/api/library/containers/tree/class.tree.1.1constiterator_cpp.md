# Unigine::Tree::ConstIterator Class (CPP)

**Header:** #include <UnigineTree.h>


## Tree::ConstIterator Class

### Методы класса

---

## const Node * get ( ) const

Возвращает указатель на узел итератора.
### Возвращаемое значение

Указатель на узел константного итератора.
## ConstIterator ( )

Конструктор по умолчанию.
## ConstIterator ( const ConstIterator & it )

Конструктор копирования.
### Аргументы

- *const ConstIterator &* **it** - ConstIterator.

## int operator!= ( const typename Tree < Key, Data >::Iterator & it ) const

Проверяет, различаются ли два итератора.
### Аргументы

- *const typename [Tree](../../../../api/library/containers/tree/class.tree_cpp.md)< Key, Data >::Iterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы не совпадают; иначе 0.
## int operator!= ( const ConstIterator & it ) const

Проверяет, различаются ли два итератора.
### Аргументы

- *const ConstIterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы не совпадают; иначе 0.
## const Node & operator* ( ) const

Возвращает ссылку на узел итератора.
### Возвращаемое значение

Ссылка на узел константного итератора.
## ConstIterator & operator++ ( )

Увеличивает позицию итератора.
### Возвращаемое значение

Константный итератор, указывающий на следующий элемент.
## ConstIterator operator++ ( )

Увеличивает позицию итератора.
### Возвращаемое значение

Константный итератор, указывающий на следующий элемент.
## ConstIterator & operator-- ( )

Уменьшает позицию итератора.
### Возвращаемое значение

Константный итератор, указывающий на предыдущий элемент.
## ConstIterator operator-- ( )

Уменьшает позицию итератора.
### Возвращаемое значение

Константный итератор, указывающий на предыдущий элемент.
## const Node * operator-> ( ) const

Возвращает указатель на узел итератора.
### Возвращаемое значение

Указатель на узел константного итератора.
## ConstIterator & operator= ( const ConstIterator & it )

Оператор присваивания для итератора.
### Аргументы

- *const ConstIterator &* **it** - ConstIterator.

## int operator== ( const typename Tree < Key, Data >::Iterator & it ) const

Проверяет, совпадают ли два итератора.
### Аргументы

- *const typename [Tree](../../../../api/library/containers/tree/class.tree_cpp.md)< Key, Data >::Iterator &* **it** - Второй итератор.

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
