# Unigine::BucketHashMap Class (CPP)

**Header:** #include <UnigineHashMap.h>


Шаблон контейнера хэш-карты. Хэш-карта хранит элементы, представленные парами ключ-значение, в *неопределённом* порядке. Данные хранятся следующим образом:


![](buckethashmap_data_storage.png)


> **Notice:** Такой подход к хранению данных может быть уместен только в том случае, если вам нужно, чтобы адрес хэш-карты оставался неизменным. Для более производительного способа хранения данных хэш-карты используйте класс *[HashMap](../../../api/library/containers/class.hashmap_cpp.md)*.


Хэш-карту можно использовать, например, для поиска узлов по их именам.


Чтобы создать новую хэш-карту, вы можете использовать [default constructor](#BucketHashMap) или один из следующих способов:


- Создать хэш-карту с помощью списка инициализации: ```cpp // create a hash map using an initializer list const BucketHashMap<String, int> hashMap_0{ { "a", 1 },	{ "b", 2 },	{ "c", 3 },	}; // check the result for (const auto &k : hashMap_0) Log::message("%s : %d \n", k.key.get(), k.data); ``` Хэш-карту, хранящую значения пользовательского типа, можно создать следующим образом: ```cpp // declare an enumeration enum class MyEnum { One, Two, Three, }; // create a hash map using an initializer list const BucketHashMap<String, MyEnum> hashMap_1 { { "One", MyEnum::One }, { "Two", MyEnum::Two }, { "Three", MyEnum::Three }, }; // check the result for (const auto &k : hashMap_1) Log::message("%s : %d \n", k.key.get(), k.data); ```
- Создать хэш-карту с помощью конструктора копирования: ```cpp // создаём хэш-карту с помощью списка инициализации const BucketHashMap<String, int> initial{ { "a", 1 },{ "b", 2 },{ "c", 3 },{ "d", 4 }, }; // конструктор копирования BucketHashMap<String, int> copied(initial); // проверяем результат for (const auto &k : copied) Log::message("%s : %d \n", k.key.get(), k.data); ```


Вы можете изменять созданную хэш-карту, используя функции-члены класса, описанные в статье. Рассмотрите некоторые примеры использования:


- Чтобы добавить элементы в текущую хэш-карту, вы можете использовать функции *[append()](#append_const_BucketHashMap_ref_void)* или *[insert()](#insert_const_BucketHashMap_ref_void)*: ```cpp // create hash maps using initializer lists BucketHashMap<String, int> initial{ { "a", 1 }, { "b", 2 }, { "c", 3 }, }; const BucketHashMap<String, int> to_append{ { "m", 7 }, { "n", 8 }, { "o", 9 }, }; // append items of one hash map to another initial.append(to_append); // insert an item into the "initial" hash map initial.insert("s", 10); // check the result for (const auto &k : initial) Log::message("%s : %d \n", k.key.get(), k.data); ```
- Получить значение по ключу из хэш-карты и вставить элемент, если такого ключа нет: ```cpp // creare an empty hash map BucketHashMap<int, int> hashMap{ { 1, 10 } }; // try to get values by the specified keys Log::message("Value %d\n", hashMap[1]); // if there is no such key, it will be added to the hash map with the default value Log::message("Value %d\n", hashMap[2]); // check the result - the new item with the default value is added to the hash map for (const auto &k: hashMap) Log::message("%d : %d \n", k.key, k.data); ```
- Извлечь элемент из хэш-карты: ```cpp // create a hash map BucketHashMap<int, int> hashMap { {1, 1}, {2, 2}, {3, 3}, }; // declare a key and a value const int key = 0; const int value = 4; // append a new item to the hash map hashMap.append(key,value); // get an item iterator by its key auto it = hashMap.find(key); // take the item from the hash map int c = hashMap.take(it); // check the result - the taken item is removed from the hash map for (const auto &k : hashMap) Log::message("%d : %d \n", k.key, k.data); ```
- Удалить элемент из хэш-карты: ```cpp // create a hash map BucketHashMap<int, int> hashMap{ { 1, 1 },{ 2, 2 },{ 3, 3 }, }; // get an item iterator by its key auto it = hashMap.find(2); // remove the item from the hash map hashMap.remove(it); // check the result for (const auto &k: hashMap) Log::message("%d : %d \n", k.key, k.data); ```
- Получить элементы по значениям из хэш-карты: ```cpp // create a hash map BucketHashMap<String, int> hashMap{ { "a", 1 }, { "b", 2 }, { "c", 3 }, }; // get an item iterator by its value auto it = hashMap.findData(2); // check the result Log::message("%s \n", it->key.get()); ```
- Получить значение/значения из хэш-карты: ```cpp // create a hash map BucketHashMap<String, int> hashMap{ { "a", 1 },{ "b", 2 },{ "c", 3 }, }; // get a key by its value Log::message("%d \n", hashMap.value("a")); // get a vector of all values of the hash map Vector<int> ret = hashMap.values(); for (int i = 0; i < ret.size(); i++) Log::message("%d \n",ret[i]); ```


## Класс BucketHashMap

### Методы класса

---

## BucketHashMap ( )

Конструктор по умолчанию, создающий пустую хэш-карту.
## BucketHashMap ( std::initializer_list< Pair <Key,Value>> list )

Конструктор. Создаёт хэш-карту из заданных пар ключ-значение.
### Аргументы

- *std::initializer_list<[Pair](../../../api/library/containers/class.pair_cpp.md)<Key,Value>>* **list** - Список пар.

## BucketHashMap ( const BucketHashMap& o )

Конструктор. Создаёт хэш-карту путём копирования исходной хэш-карты.
### Аргументы

- *const BucketHashMap&* **o** - Хэш-карта.

## BucketHashMap ( BucketHashMap&& o )

Конструктор. Создаёт хэш-карту путём перемещения исходной хэш-карты в неё.
### Аргументы

- *BucketHashMap&&* **o** - Хэш-карта.

## Iterator append ( const Key& key , const Value& value )

Добавляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *const Key&* **key** - Ключ.
- *const Value&* **value** - Значение.

### Возвращаемое значение

Итератор элемента.
## Iterator append ( const Key& key , Value&& value )

Добавляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *const Key&* **key** - Ключ, который будет скопирован в хэш-карту.
- *Value&&* **value** - Значение, которое будет перемещено в хэш-карту.

### Возвращаемое значение

Итератор элемента.
## Iterator append ( Key&& key , const Value& value )

Добавляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *Key&&* **key** - Ключ, который будет перемещён в хэш-карту.
- *const Value&* **value** - Значение, которое будет скопировано в хэш-карту.

### Возвращаемое значение

Итератор элемента.
## Iterator append ( Key&& key , Value&& value )

Добавляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *Key&&* **key** - Ключ, который будет перемещён в хэш-карту.
- *Value&&* **value** - Значение, которое будет перемещено в хэш-карту.

### Возвращаемое значение

Итератор элемента.
## Value& append ( const Key& key )

Добавляет элемент с заданным ключом в хэш-карту.
### Аргументы

- *const Key&* **key** - Ключ.

### Возвращаемое значение

Значение.
## Value& append ( Key&& key )

Добавляет элемент с заданным ключом в хэш-карту.
### Аргументы

- *Key&&* **key** - Ключ, который будет перемещён в хэш-карту.

### Возвращаемое значение

Значение.
## void append ( const BucketHashMap& o )

Добавляет элементы со всеми доступными ключами из переданной хэш-карты в текущую хэш-карту.
### Аргументы

- *const BucketHashMap&* **o** - Хэш-карта для добавления.

## void append ( BucketHashMap&& o )

Добавляет элементы со всеми доступными ключами, перемещая переданную хэш-карту в текущую хэш-карту.
### Аргументы

- *BucketHashMap&&* **o** - Хэш-карта для добавления.

## void append ( const Vector& vector )

Добавляет элементы со всеми доступными ключами из переданного вектора в хэш-карту.
### Аргументы

- *const Vector&* **vector** - Вектор, содержащий ключ (или ключи) для добавления.

## void append ( Vector&& vector )

Добавляет элементы со всеми доступными ключами, перемещая переданный вектор в хэш-карту.
### Аргументы

- *Vector&&* **vector** - Вектор, содержащий ключ (или ключи) для добавления.

## Iterator insert ( const Key& key , const Value& value )

Вставляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *const Key&* **key** - Ключ.
- *const Value&* **value** - Значение.

### Возвращаемое значение

Итератор элемента.
## Iterator insert ( const Key& key , Value&& value )

Вставляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *const Key&* **key** - Ключ, который будет скопирован в хэш-карту.
- *Value&&* **value** - Значение, которое будет перемещено в хэш-карту.

### Возвращаемое значение

Итератор элемента.
## Iterator insert ( Key&& key , const Value& value )

Вставляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *Key&&* **key** - Ключ, который будет перемещён в хэш-карту.
- *const Value&* **value** - Значение, которое будет скопировано в хэш-карту.

### Возвращаемое значение

Итератор элемента.
## Iterator insert ( Key&& key , Value&& value )

Вставляет элемент с заданным ключом и значением в хэш-карту.
### Аргументы

- *Key&&* **key** - Ключ, который будет перемещён в хэш-карту.
- *Value&&* **value** - Значение, которое будет перемещено в хэш-карту.

### Возвращаемое значение

Итератор элемента.
## Value& insert ( const Key& key )

Вставляет элемент с заданным ключом в хэш-карту.
### Аргументы

- *const Key&* **key** - Ключ, который будет скопирован в хэш-карту.

### Возвращаемое значение

Значение.
## Value& insert ( Key&& key )

Вставляет элемент с заданным ключом в хэш-карту.
### Аргументы

- *Key&&* **key** - Ключ, который будет перемещён в хэш-карту.

### Возвращаемое значение

Значение.
## void insert ( const BucketHashMap& o )

Вставляет элементы со всеми доступными ключами, копируя переданную хэш-карту в текущую хэш-карту.
### Аргументы

- *const BucketHashMap&* **o** - Хэш-карта, содержащая ключ (или ключи) для вставки.

## void insert ( BucketHashMap&& o )

Вставляет элементы со всеми доступными ключами, перемещая переданную хэш-карту в текущую хэш-карту.
### Аргументы

- *BucketHashMap&&* **o** - Хэш-карта, содержащая ключ (или ключи) для вставки.

## void insert ( const Vector& vector )

Вставляет элементы со всеми доступными ключами, копируя переданный вектор в хэш-карту.
### Аргументы

- *const Vector&* **vector** - Вектор, содержащий ключ (или ключи) для вставки.

## void insert ( Vector&& vector )

Вставляет элементы со всеми доступными ключами, перемещая переданный вектор в хэш-карту.
### Аргументы

- *Vector&&* **vector** - Вектор, содержащий ключ (или ключи) для вставки.

## Value take ( const Key& key , const Value& def )

Удаляет элемент из хэш-карты по его ключу и возвращает значение элемента. Если такого элемента нет, возвращается значение по умолчанию.
### Аргументы

- *const Key&* **key** - Ключ.
- *const Value&* **def**

### Возвращаемое значение

Значение удалённого элемента.
## Value take ( const Key& key )

Удаляет элемент из хэш-карты по его ключу и возвращает значение элемента. Если такого элемента нет, возвращается значение, построенное по умолчанию.
### Аргументы

- *const Key&* **key** - Ключ.

### Возвращаемое значение

Значение удалённого элемента.
## Value take ( Iterator it )

Удаляет элемент из хэш-карты по его итератору и возвращает значение элемента. Если такого элемента нет, возвращается значение, построенное по умолчанию.
### Аргументы

- *Iterator* **it** - Итератор элемента.

### Возвращаемое значение

Значение удалённого элемента.
## Value take ( ConstIterator it )

Удаляет элемент из хэш-карты по его итератору и возвращает значение элемента. Если такого элемента нет, возвращается значение, построенное по умолчанию.
### Аргументы

- *ConstIterator* **it** - Итератор элемента.

### Возвращаемое значение

Значение удалённого элемента.
## bool contains ( const Key& key , const Value& value ) const

Проверяет, существует ли в хэш-карте элемент с указанными ключом и значением.
### Аргументы

- *const Key&* **key** - Ключ.
- *const Value&* **value** - Значение.

### Возвращаемое значение

**true**, если элемент существует; иначе **false**.
## Iterator findData ( const Value& value )

Ищет в хэш-карте элемент с указанным значением.
### Аргументы

- *const Value&* **value** - Значение.

### Возвращаемое значение

Итератор элемента.
## ConstIterator findData ( const Value& value ) const

Ищет в хэш-карте элемент с указанным значением.
### Аргументы

- *const Value&* **value** - Значение.

### Возвращаемое значение

Итератор элемента.
## void removeData ( const Value& value )

Удаляет первое вхождение указанного значения из хэш-карты.
### Аргументы

- *const Value&* **value** - Значение.

## Value& get ( Key&& key )

Возвращает значение по указанному ключу.
### Аргументы

- *Key&&* **key** - Ключ.

### Возвращаемое значение

Значение.
## const Value& get ( const Key& key ) const

Возвращает значение по указанному ключу.
### Аргументы

- *const Key&* **key** - Ключ.

### Возвращаемое значение

Значение.
## const Value& get ( const Key& key , const Value& value ) const

Возвращает значение по указанному ключу. Если элемента с этим ключом нет, возвращается значение по умолчанию.
### Аргументы

- *const Key&* **key** - Ключ.
- *const Value&* **value** - Значение по умолчанию.

### Возвращаемое значение

Значение.
## Value& operator[] ( Key&& key )

Доступ к элементу хэш-карты. Значение возвращается, если оно доступно по ключу; если элемент недоступен, добавляется новая пара (Key,Value).
### Аргументы

- *Key&&* **key** - Ключ.

### Возвращаемое значение

Значение полученного элемента, если доступно.
## Value& operator[] ( const Key& key ) const

Доступ к элементу хэш-карты.
### Аргументы

- *const Key&* **key** - Ключ.

### Возвращаемое значение

Значение полученного элемента.
## Value value ( const Key& key ) const

Возвращает значение с указанным ключом из хэш-карты. Если такого ключа нет, возвращает значение, построенное по умолчанию.
### Аргументы

- *const Key&* **key** - Ключ.

### Возвращаемое значение

Значение полученного элемента.
## Value value ( const Key& key , const Value& value ) const

Возвращает значение с указанным ключом из хэш-карты. Если такого ключа нет, возвращает указанное значение по умолчанию.
### Аргументы

- *const Key&* **key** - Ключ.
- *const Value&* **value** - Значение по умолчанию.

### Возвращаемое значение

Значение полученного элемента.
## const Value& valueRef ( const Key& key ) const

Возвращает ссылку на значение с указанным ключом из хэш-карты. Если такого ключа нет, возвращает значение, построенное по умолчанию.
### Аргументы

- *const Key&* **key** - Ключ.

### Возвращаемое значение

Значение полученного элемента.
## const Value& valueRef ( const Key& key , const Value& value ) const

Возвращает ссылку на значение с указанным ключом из хэш-карты. Если такого ключа нет, возвращает значение по умолчанию.
### Аргументы

- *const Key&* **key**
- *const Value&* **value** - Значение по умолчанию.

### Возвращаемое значение

Значение полученного элемента.
## Vector <Value> values ( ) const

Возвращает вектор всех значений хэш-карты.
### Возвращаемое значение

Вектор значений хэш-карты.
## void getValues ( Vector <Value>& values ) const

Добавляет значения хэш-карты в заданный вектор.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<Value>&* **values** - Вектор значений хэш-карты.

## BucketHashMap & operator= ( const BucketHashMap & o )

Присваивает указанную хэш-карту, копируя её.
### Аргументы

- *const [BucketHashMap](../../../api/library/containers/class.buckethashmap_cpp.md) &* **o** - Хэш-карта.

### Возвращаемое значение

Хэш-карта.
## BucketHashMap & operator= ( BucketHashMap&& o )

Присваивает указанную хэш-карту, перемещая её.
### Аргументы

- *BucketHashMap&&* **o** - Хэш-карта.

### Возвращаемое значение

Хэш-карта.
## emplaceRange ( InputIt first , InputIt last )

Вставляет в хэш-карту диапазон значений, заданный итераторами-аргументами.
### Аргументы

- *InputIt* **first** - Итератор, обозначающий начало диапазона.
- *InputIt* **last** - Итератор, обозначающий конец диапазона.

## bool contains ( const Key & k ) const

Проверяет, присутствует ли заданный ключ в хэш-карте.
### Аргументы

- *const Key &* **k** - Проверяемый ключ.

### Возвращаемое значение

**true**, если хэш-карта содержит указанный ключ; иначе **false**.
## Iterator find ( const Key & k ) const

Возвращает итератор указанного ключа.
### Аргументы

- *const Key &* **k** - Проверяемый ключ.

### Возвращаемое значение

Итератор элемента.
## ConstIterator find ( const Key & k ) const

Возвращает итератор указанного ключа.
### Аргументы

- *const Key &* **k** - Проверяемый ключ.

### Возвращаемое значение

Итератор элемента.
## Item * findFast ( const Key & key ) const

Находит элемент с указанным ключом.
### Аргументы

- *const Key &* **key** - Искомый ключ.

### Возвращаемое значение

Указатель на элемент хэш-карты.
## Vector <Key> keys ( ) const

Возвращает вектор, содержащий все ключи хэш-карты.
### Возвращаемое значение

Вектор ключей.
## void getKeys ( Vector <Key>& keys ) const

Добавляет ключи хэш-карты в указанный вектор.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<Key>&* **keys** - Вектор для хранения ключей.

## const Key & getKey ( size_t index ) const

Возвращает ключ по его индексу.
### Аргументы

- *size_t* **index** - Номер индекса ключа в хэш-карте.

### Возвращаемое значение

Ключ.
## bool remove ( const Key& k )

Удаляет указанный ключ из хэш-карты.
### Аргументы

- *const Key&* **k** - Удаляемый ключ.

### Возвращаемое значение

**true**, если ключ успешно удалён; иначе **false**.
## void remove ( Iterator it )

Удаляет из хэш-карты элемент, на который в данный момент указывает итератор.
### Аргументы

- *Iterator* **it** - Итератор, указывающий на удаляемый элемент.

## void remove ( ConstIterator it )

Удаляет из хэш-карты элемент, на который в данный момент указывает итератор.
### Аргументы

- *ConstIterator* **it** - Итератор, указывающий на удаляемый элемент.

## void remove ( const BucketHashMap& o )

Удаляет указанную хэш-карту из текущей хэш-карты.
### Аргументы

- *const BucketHashMap&* **o** - Хэш-карта.

## void remove ( const Vector <Key>& v )

Удаляет указанные ключи из хэш-карты.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<Key>&* **v** - Вектор, хранящий ключи.

## bool erase ( const ConstIterator & it )

Удаляет из хэш-карты элемент, на который в данный момент указывает итератор.
### Аргументы

- *const ConstIterator &* **it** - Итератор, указывающий на удаляемый элемент.

### Возвращаемое значение

true при успехе, иначе false.
## bool erase ( const Iterator & it )

Удаляет из хэш-карты элемент, на который в данный момент указывает итератор.
### Аргументы

- *const Iterator &* **it** - Итератор, указывающий на удаляемый элемент.

### Возвращаемое значение

true при успехе, иначе false.
## bool erase ( const Key& k )

Удаляет из хэш-карты элемент с указанным ключом.
### Аргументы

- *const Key&* **k** - Ключ удаляемого элемента.

### Возвращаемое значение

true при успехе, иначе false.
## void erase ( const BucketHashMap& o )

Удаляет указанную хэш-карту из текущей хэш-карты.
### Аргументы

- *const BucketHashMap&* **o** - Удаляемая хэш-карта.

## void erase ( const Vector <Key>& v )

Удаляет указанные ключи из хэш-карты.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<Key>&* **v** - Вектор, хранящий ключи.

## void subtract ( const Vector <Key>& vector )

Удаляет указанные ключи из хэш-карты.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<Key>&* **vector** - Вектор, хранящий ключи.

## void subtract ( const BucketHashMap & o )

Удаляет указанную хэш-карту из текущей хэш-карты.
### Аргументы

- *const [BucketHashMap](../../../api/library/containers/class.buckethashmap_cpp.md) &* **o** - Удаляемая хэш-карта.

## void clear ( )

Удаляет все пары ключ-значение из хэш-карты.
## void destroy ( )

Удаляет все пары ключ-значение из хэш-карты и освобождает память.
## void reserve ( size_t size )

Резервирует место для хранения, чтобы избежать повторного выделения памяти.
### Аргументы

- *size_t* **size** - Резервируемый размер хэша.

## void shrink ( )

Удаляет неиспользуемую ёмкость.
## Iterator begin ( ) const

Возвращает итератор, указывающий на первый элемент хэш-карты.
### Возвращаемое значение

Итератор, указывающий на первый элемент.
## Iterator end ( ) const

Возвращает итератор, указывающий на позицию, следующую за последним элементом хэш-карты.
### Возвращаемое значение

Итератор, указывающий на последний элемент.
## ConstIterator cbegin ( ) const

Возвращает константный итератор, указывающий на первый элемент хэш-карты.
### Возвращаемое значение

ConstIterator, указывающий на первый элемент.
## ConstIterator cend ( ) const

Возвращает константный итератор, указывающий на позицию, следующую за последним элементом хэш-карты.
### Возвращаемое значение

ConstIterator, указывающий на последний элемент.
## Counter size ( ) const

Возвращает количество пар ключ-значение в хэш-карте.
### Возвращаемое значение

Количество пар ключ-значение в хэш-карте.
## Counter space ( ) const

Возвращает текущую ёмкость (количество элементов, которое хэш может в данный момент содержать).
### Возвращаемое значение

Количество элементов, которое хэш может в данный момент содержать.
## size_t getMemoryUsage ( ) const

Показывает объём памяти, используемой хэш-картой, в байтах.
### Возвращаемое значение

Используемая память в байтах.
## bool empty ( ) const

Проверяет, пуста ли хэш-карта.
### Возвращаемое значение

**true**, если хэш-карта пуста, иначе **false**
## void swap ( BucketHashMap & o )

Меняет местами эту хэш-карту с хэш-картой, указанной в качестве аргумента.
### Аргументы

- *[BucketHashMap](../../../api/library/containers/class.buckethashmap_cpp.md) &* **o** - Хэш-карта.
