# Unigine::Pair Class (CPP)

**Header:** #include <UniginePair.h>


Шаблон контейнера-пары. Класс имеет члены *first* и *second*, которые обеспечивают доступ к соответствующим элементам пары.


## Pair Class

### Методы класса

---

## Pair ( )

Конструктор по умолчанию, создающий пустую пару.
## Pair ( const TypeFirst& f , const TypeSecond& s )

Конструктор. Создаёт пару из заданных элементов.
### Аргументы

- *const TypeFirst&* **f** - Первый элемент пары.
- *const TypeSecond&* **s** - Второй элемент пары.

## void Pair ( const Pair <OtherFirst,OtherSecond>& o )

Заменяет пару на заданную.
### Аргументы

- *const [Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

## void Pair ( Pair <OtherFirst,OtherSecond>& o )

Заменяет пару на заданную.
### Аргументы

- *[Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

## void Pair ( OtherFirst&& f , OtherSecond&& s )

Заменяет элементы пары заданными значениями.
### Аргументы

- *OtherFirst&&* **f** - Первый элемент пары.
- *OtherSecond&&* **s** - Второй элемент пары.

## Pair <TypeFirst, TypeSecond> & operator= ( Pair <OtherFirst,OtherSecond>& o )

Оператор присваивания для пары.
### Аргументы

- *[Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара для присваивания.

## void swap ( Pair& o )

Меняет местами две пары.
### Аргументы

- *Pair&* **o** - Пара для обмена.

## bool operator== ( const Pair <OtherFirst,OtherSecond>& o ) const

Проверяет, равны ли оба элемента пар.
### Аргументы

- *const [Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

### Возвращаемое значение

true, если пары равны; иначе false.
## bool operator!= ( const Pair <OtherFirst,OtherSecond>& o ) const

Проверяет, не равны ли две пары.
### Аргументы

- *const [Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

### Возвращаемое значение

true, если пары не равны; иначе false.
## bool operator< ( const Pair <OtherFirst,OtherSecond>& o ) const

Проверяет, меньше ли пара заданной: сравниваются первые элементы, и только если они равны, сравниваются вторые элементы.
### Аргументы

- *const [Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

### Возвращаемое значение

true, если пара меньше заданной; иначе false.
## bool operator> ( const Pair <OtherFirst,OtherSecond>& o ) const

Проверяет, больше ли пара заданной: сравниваются первые элементы, и только если они равны, сравниваются вторые элементы.
### Аргументы

- *const [Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

### Возвращаемое значение

true, если пара больше заданной; иначе false.
## bool operator<= ( const Pair <OtherFirst,OtherSecond>& o ) const

Проверяет, меньше ли пара заданной или равна ей: сравниваются первые элементы, и если они равны, сравниваются вторые элементы.
### Аргументы

- *const [Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

### Возвращаемое значение

true, если пара меньше заданной или равна ей; иначе false.
## bool operator>= ( const Pair <OtherFirst,OtherSecond>& o ) const

Проверяет, больше ли пара заданной или равна ей: сравниваются первые элементы, и если они равны, сравниваются вторые элементы.
### Аргументы

- *const [Pair](../../../api/library/containers/class.pair_cpp.md)<OtherFirst,OtherSecond>&* **o** - Пара.

### Возвращаемое значение

true, если пара больше заданной или равна ей; иначе false.
