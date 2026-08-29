# Unigine::Tree::Iterator Class (CPP)

**Header:** #include <UnigineTree.h>


## Tree::Iterator Class

### Методы класса

---

## Node * get ( )

Возвращает указатель на узел итератора.
### Возвращаемое значение

Указатель на узел итератора.
## Iterator ( )

Конструктор по умолчанию.
## Iterator ( const Iterator & it )

Конструктор копирования.
### Аргументы

- *const Iterator &* **it** - Итератор.

## int operator!= ( const Iterator & it ) const

Проверяет, различаются ли два итератора.
### Аргументы

- *const Iterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы не совпадают; иначе 0.
## int operator!= ( const typename Tree < Key, Data >::ConstIterator & it ) const

Проверяет, различаются ли два итератора.
### Аргументы

- *const typename [Tree](../../../../api/library/containers/tree/class.tree_cpp.md)< Key, Data >::ConstIterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы не совпадают; иначе 0.
## Node & operator* ( )

Возвращает ссылку на узел итератора.
### Возвращаемое значение

Ссылка на узел итератора.
## Iterator & operator++ ( )

Увеличивает позицию итератора.
### Возвращаемое значение

Итератор, указывающий на следующий элемент.
## Iterator operator++ ( )

Увеличивает позицию итератора.
### Возвращаемое значение

Итератор, указывающий на текущий элемент.
## Iterator & operator-- ( )

Уменьшает позицию итератора.
### Возвращаемое значение

Итератор, указывающий на предыдущий элемент.
## Iterator operator-- ( )

Уменьшает позицию итератора.
### Возвращаемое значение

Итератор, указывающий на текущий элемент.
## Node * operator-> ( )

Возвращает указатель на узел итератора.
### Возвращаемое значение

Узел итератора.
## Iterator & operator= ( const Iterator & it )

Оператор присваивания для итератора.
### Аргументы

- *const Iterator &* **it** - Итератор.

## int operator== ( const Iterator & it ) const

Проверяет, совпадают ли два итератора.
### Аргументы

- *const Iterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы совпадают; иначе 0.
## int operator== ( const typename Tree < Key, Data >::ConstIterator & it ) const

Проверяет, совпадают ли два итератора.
### Аргументы

- *const typename [Tree](../../../../api/library/containers/tree/class.tree_cpp.md)< Key, Data >::ConstIterator &* **it** - Второй итератор.

### Возвращаемое значение

1, если итераторы совпадают; иначе 0.
## ~Iterator ( )

Деструктор.
