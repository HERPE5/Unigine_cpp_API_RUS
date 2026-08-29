# Unigine::Map Class (CPP)

**Header:** #include <UnigineMap.h>


Шаблонный контейнер map.


> **Warning:** В UnigineScript map — это тип, который отображает значения на ключи. Подробности см. в статье [Containers](../../../code/uniginescript/language/containers/index.md#maps).


## Map Class

### Методы класса

---

## Map ( )

Конструктор по умолчанию, создающий пустой map.
## Type & get ( const Key & key )

Возвращает элемент по ключу.
### Аргументы

- *const Key &* **key** - Ключ элемента.

### Возвращаемое значение

Элемент.
## void append ( const Key & key , const Type & t )

Добавляет элемент.
### Аргументы

- *const Key &* **key** - Ключ.
- *const Type &* **t** - Элемент.

## void append ( const Map <Key, Type> & m )

Добавляет map.
### Аргументы

- *const [Map](../../../api/library/containers/class.map_cpp.md)<Key, Type> &* **m** - Map.

## Map < Key, Type >::Iterator findData ( const Type & t ) const

Ищет элемент в map.
### Аргументы

- *const Type &* **t** - Элемент.

### Возвращаемое значение

Итератор.
## Type & operator[] ( const Key & key )

Доступ к map.
### Аргументы

- *const Key &* **key** - Ключ элемента.

### Возвращаемое значение

Элемент.
