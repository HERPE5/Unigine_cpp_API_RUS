# Unigine::ArrayMap Class (CPP)

**Header:** #include <UnigineInterpreter.h>


Позволяет использовать [maps](../../../../code/uniginescript/language/containers/index.md#maps) UnigineScript.


## ArrayMap Class

### Методы класса

---

## ArrayMap ( const ArrayMap & map )

Конструктор копирования.
### Аргументы

- *const [ArrayMap](../../../../api/library/containers/arraymap/class.arraymap_cpp.md) &* **map** - Карта.

## void set ( const Variable & key , const Variable & v ) const

Устанавливает элемент по ключу.
### Аргументы

- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **key** - Ключ элемента.
- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **v** - Устанавливаемый элемент.

## static ArrayMap get ( void * interpreter , const Variable & id )

Возвращает карту из UnigineScript.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **id** - ID карты.

### Возвращаемое значение

Карта.
## const Variable & get ( const Variable & key ) const

Возвращает элемент по ключу.
### Аргументы

- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **key** - Ключ элемента.

### Возвращаемое значение

Элемент.
## int size ( ) const

Возвращает длину карты.
### Возвращаемое значение

Длина карты.
## void clear ( ) const

Очищает все элементы карты.
## void append ( const Variable & key , const Variable & v ) const

Добавляет элемент с заданным ключом в карту.
### Аргументы

- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **key** - Ключ элемента.
- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **v** - Элемент.

## void remove ( const Variable & key ) const

Удаляет элемент с заданным ключом из карты.
### Аргументы

- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **key** - Ключ элемента.

## Iterator back ( )

Возвращает итератор, указывающий на последний элемент.
### Возвращаемое значение

Итератор на последний элемент.
## Iterator begin ( )

Возвращает итератор, указывающий на первый элемент.
### Возвращаемое значение

Итератор на первый элемент.
## Iterator end ( )

Возвращает итератор, указывающий на конечный элемент.
### Возвращаемое значение

Итератор на конечный элемент.
## Iterator find ( const Variable & key ) const

Ищет элемент по заданному ключу.
### Аргументы

- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **key** - Ключ элемента.

### Возвращаемое значение

Итератор на найденный элемент; в противном случае — итератор на конец.
## ArrayMap & operator= ( const ArrayMap & map )

Оператор присваивания для карты.
### Аргументы

- *const [ArrayMap](../../../../api/library/containers/arraymap/class.arraymap_cpp.md) &* **map** - Присваиваемая карта.

## const Variable & operator[] ( const Variable & key ) const

Доступ к карте.
### Аргументы

- *const [Variable](../../../../api/library/common/class.variable_cpp.md) &* **key** - Ключ элемента.

### Возвращаемое значение

Элемент.
