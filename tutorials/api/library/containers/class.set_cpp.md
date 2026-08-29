# Unigine::Set Class (CPP)

**Header:** #include <UnigineSet.h>


Множество (set) — это шаблон контейнера, в котором каждый элемент должен быть уникальным, так как значение элемента идентифицирует его. Значения хранятся в *порядке возрастания*.


Чтобы создать новое множество, вы можете использовать [default constructor](#Set) или один из следующих способов:


- Создать новое множество с помощью конструктора со списком инициализации: ```cpp const Set<int> my_set{ 1, 6, 4, 3, 7 }; // проверяем результат for (const auto &it : my_set) Log::message("%d ", it.key); ```
- Создать новое множество с помощью конструктора копирования: ```cpp // конструктор, принимающий список инициализации const Set<String> initial{ "a", "e" }; // конструктор копирования const Set<String> copied(initial); // проверяем результат for (const auto &it : copied) Log::message("%s ", it.key.get()); ```


Также вы можете изменять множество с помощью функций-членов класса *[append()](#append_const_Key_ref_void)* и *[insert()](#insert_Key_rvref_void)*. Рассмотрите некоторые примеры использования:


- Создать новое множество и добавлять в него элементы по одному: ```cpp Set<int> my_set; my_set.append(1); my_set.append(10); my_set.append(4); // проверяем результат for (const auto &it : my_set) Log::message("%d ", it.key); ```
- Создать новое множество и добавить в него другое множество: ```cpp // создаём множество с помощью списка инициализации const Set<int> my_set_0{ 1, 6, 4, 3, 7 }; // объявляем новое множество Set<int> my_set_1; // добавляем "my_set_0" в него my_set_1.append(my_set_0); // проверяем результат for (const auto &it : my_set) Log::message("%d ", it.key); ```
- Изменить существующее множество, которое уже содержит элементы: > **Notice:** Если элемент уже существует в исходном множестве, он не будет добавлен. ```cpp // создаём множества с помощью списков инициализации Set<String> initial{ "a", "b", "c", "d", "e" }; Set<String> to_add{ "m", "n", "o" }; // добавляем ключи множества "to_add" в множество "initial" initial.append(to_add); // вставляем ключ в множество "initial" initial.insert("s"); // проверяем результат for (const auto &it : initial) Log::message("%s ", it.key.get()); ```


## Set Class

### Методы класса

---

## Set ( )

Конструктор по умолчанию, создающий пустое множество.
## Set ( std::initializer_list<Key> list )

Конструктор. Создаёт множество из ключей заданного списка.
### Аргументы

- *std::initializer_list<Key>* **list** - Список ключей.

## Set ( Set <Key, Allocator> && o )

Конструктор. Создаёт множество путём копирования исходного множества.
### Аргументы

- *[Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &&* **o** - Исходное множество.

## Set ( const Set <Key, Allocator> & o )

Конструктор. Создаёт множество путём копирования исходного множества.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &* **o** - Исходное множество.

## void append ( const Key & key )

Добавляет ключ.
### Аргументы

- *const Key &* **key** - Ключ.

## void append ( Key && key )

Добавляет ключ.
### Аргументы

- *Key &&* **key** - Ключ.

## void insert ( Key && key )

Вставляет заданный ключ в множество.
### Аргументы

- *Key &&* **key** - Ключ.

## void insert ( const Key & key )

Вставляет заданный ключ в множество.
### Аргументы

- *const Key &* **key** - Ключ.

## Set <Key, Allocator> & operator= ( const Set <Key, Allocator> & o )

Оператор присваивания для множества.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &* **o** - Множество.

## Set <Key, Allocator> & operator= ( Set <Key, Allocator> && o )

Оператор присваивания для множества.
### Аргументы

- *[Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &&* **o** - Множество.

## void append ( const Set <Key, Allocator> & s )

Добавляет заданное множество к текущему.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &* **s** - Множество.

## void append ( Set <Key, Allocator> && s )

Добавляет заданное множество к текущему.
### Аргументы

- *[Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &&* **s** - Множество.

## void insert ( const Set <Key, Allocator> & o )

Вставляет заданное множество в текущее.
### Аргументы

- *const [Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &* **o** - Множество.

## void insert ( Set <Key, Allocator> && o )

Вставляет заданное множество в текущее.
### Аргументы

- *[Set](../../../api/library/containers/class.set_cpp.md)<Key, Allocator> &&* **o** - Множество.
