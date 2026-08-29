# Unigine::Ptr Class (CPP)

**Header:** #include <UniginePtr.h>


***Ptr<Type>*** — это шаблон умного указателя, используемый для управления временем жизни объектов.


Не все методы внутренних классов C++ движка доступны пользователю, некоторые используются движком только внутренне. Для обеспечения безопасного доступа используется интерфейс, который хранит указатель на внутренний объект.


Чтобы создать экземпляр внутреннего класса, объявите умный указатель и вызовите метод *create()* с необходимыми параметрами конструирования:


```cpp
// Создание экземпляра объекта внутреннего класса
<Class>Ptr instance = <Class>::create(<construction_parameters>);
// Доступ к методам объекта через умный указатель
instance->someMethod();

```


### Владеющие и не владеющие объекты


Объекты, управляемые ***Ptr<Type>***, можно разделить на владеющие и не владеющие:


- **[Ownership Objects](../../../code/fundamentals/smartpointers.md#ownership_object)** Эти объекты полностью управляются ***Ptr<Type>***. Счётчик ссылок автоматически увеличивается или уменьшается при копировании, перемещении или уничтожении умных указателей. Когда уничтожается последний ***Ptr***, ссылающийся на объект, сам объект **удаляется автоматически**. ```cpp // Создаём новое изображение ImagePtr img = Image::create(); // Теперь два указателя указывают на наше изображение (инкремент счётчика ссылок) ImagePtr img2 = img; // Удаляем изображение (поскольку оба указателя больше не ссылаются на него, а счётчик ссылок равен нулю) img2 = img = nullptr; ```
- **[Non-Ownership Objects](../../../code/fundamentals/smartpointers.md#non_ownership_object)** Эти объекты **не удаляются автоматически** умными указателями. Для их безопасного удаления предусмотрены следующие методы:

  - *[deleteLater()](#deleteLater_void)* - отложенное удаление, объект будет удалён на следующем этапе *[swap()](../../../code/fundamentals/execution_sequence/main_loop.md)* последовательности выполнения; ```cpp // поведение deleteLater() node.deleteLater(); // сразу после вызова deleteLater() if (node.isDeleted())	//true Log::message("node is deleted"); if (node.isNull())		//false Log::message("node is null"); if (node.isValid())		//true Log::message("node is valid"); if (node.get())			//true Log::message("Got the pointer to the object!"); // ... после swap() ... if (node.isDeleted())	//true Log::message("node is deleted"); if (node.isNull())		//true Log::message("node is null"); if (node.isValid())		//false Log::message("node is valid"); if (node.get())			//false Log::message("Got the pointer to the object!"); ```
  - *[deleteForce()](#deleteForce_void)* - немедленное удаление. ```cpp // поведение deleteForce() node.deleteForce(); // узел удаляется немедленно if (node.isDeleted())	//true Log::message("node is deleted"); if (node.isNull())		//true Log::message("node is null"); if (node.isValid())		//false Log::message("node is valid"); if (node.get())			//false Log::message("Got the pointer to the object!"); ```


### См. также


- **[Working with Smart Pointers](../../../code/fundamentals/smartpointers.md)** - статья, объясняющая систему умных указателей C++ в UNIGINE.


## Ptr Class

### Методы класса

---

## Ptr ( )

Конструктор по умолчанию, создающий nullptr-указатель.
## Ptr ( UnigineBaseObject * obj , bool take_ownership )

Конструктор. Создаёт умный указатель из необработанного указателя **UnigineBaseObject***. Опционально принимает владение объектом и увеличивает счётчик ссылок.
### Аргументы

- *UnigineBaseObject ** **obj** - Необработанный указатель на **UnigineBaseObject**.
- *bool* **take_ownership** - Если true, указатель владеет объектом и освободит его. Если false, указатель увеличивает счётчик ссылок, но не берёт на себя владение.

## Ptr ( const Ptr & pointer )

Конструктор. Инициализирует новый экземпляр ***Ptr*** путём копирования существующего ***Ptr*** того же типа.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md) &* **pointer** - Умный указатель для копирования.

## Ptr ( Ptr && pointer )

Конструктор. Инициализирует новый экземпляр ***Ptr***, забирая владение существующим временным ***Ptr***. Новый экземпляр берёт на себя управление базовым объектом, а исходный ***Ptr*** остаётся пустым (nullptr).
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md) &&* **pointer** - Умный указатель, из которого передаётся владение.

## Ptr ( const Ptr <OtherType> & pointer )

Конструктор. Создаёт новый экземпляр ***Ptr<Type>*** путём копирования другого **Ptr<OtherType>**, базовый тип которого приводим к Type. Новый ***Ptr*** разделяет владение тем же объектом, счётчик ссылок увеличивается.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<OtherType> &* **pointer** - Умный указатель совместимого типа для копирования.

## Ptr ( Ptr <OtherType> && pointer )

Конструктор. Создаёт новый экземпляр ***Ptr<Type>***, забирая владение другим **Ptr<OtherType>**, тип которого приводим к Type. Новый ***Ptr*** управляет тем же объектом, а исходный ***Ptr*** остаётся пустым.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<OtherType> &&* **pointer** - Умный указатель совместимого типа для перемещения.

## explicit Ptr ( Type * pointer )

Конструктор. Создаёт новый ***Ptr<Type>*** из необработанного указателя на **Type**.
### Аргументы

- *Type ** **pointer** - Указатель заданного типа.

## Type * get ( ) const

Возвращает внутренний адрес (необработанный указатель), которым управляет ***Ptr***.
### Возвращаемое значение

Указатель.
## void clear ( )

Освобождает указатель на управляемый объект и уменьшает внутренний счётчик ссылок. Если объект является *[ownership object](../../../code/fundamentals/smartpointers.md#ownership_object)* и этот ***Ptr*** последний, хранящий ссылку на него, этот метод также инициирует фактическое уничтожение базового объекта. Для *[non-ownership objects](../../../code/fundamentals/smartpointers.md#non_ownership_object)* метод только устанавливает указатель в nullptr, а сам объект продолжает управляться движком.
## bool operator bool ( )

Проверяет, равен ли указатель нулю.
### Возвращаемое значение

**true**, если указатель не равен нулю; иначе **false**.
## Type * operator-> ( ) const

Предоставляет доступ к членам объекта, которым управляет ***Ptr***.
### Возвращаемое значение

Указатель на управляемый объект.
## Type & operator* ( )

Предоставляет доступ к объекту, которым управляет ***Ptr***. Разыменовывает внутренний указатель и возвращает ссылку на базовый объект.
### Возвращаемое значение

Ссылка на управляемый объект.
## Ptr operator= ( std::nullptr_t nullptr )

Освобождает владение управляемым объектом и устанавливает ***Ptr*** в пустое значение (nullptr).
### Аргументы

- *std::nullptr_t* **nullptr** - Присваивает ***Ptr*** значение null.

### Возвращаемое значение

Ссылка на текущий объект ***Ptr***.
## Ptr operator= ( const Ptr & pointer )

Копирует владение от другого ***Ptr*** того же типа. Счётчик ссылок разделяемого объекта увеличивается.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md) &* **pointer** - Исходный умный указатель для копирования.

### Возвращаемое значение

Ссылка на текущий объект ***Ptr***.
## Ptr operator= ( const Ptr && pointer )

Передаёт владение от другого ***Ptr*** того же типа. Исходный ***Ptr*** остаётся пустым.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md) &&* **pointer** - Исходный умный указатель для перемещения.

### Возвращаемое значение

Ссылка на текущий объект ***Ptr***.
## Ptr <Type> & operator= ( const Ptr <OtherType> & pointer )

Копирует владение от ***Ptr*** типа, приводимого к ***Type***. Счётчик ссылок увеличивается.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<OtherType> &* **pointer** - Исходный умный указатель совместимого типа.

### Возвращаемое значение

Ссылка на текущий объект ***Ptr***.
## Ptr <Type> & operator= ( const Ptr <OtherType> && pointer )

Передаёт владение от ***Ptr*** типа, приводимого к ***Type***. Исходный ***Ptr*** остаётся пустым.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<OtherType> &&* **pointer** - Исходный умный указатель совместимого типа.

### Возвращаемое значение

Ссылка на текущий объект ***Ptr***.
## Ptr <Type> & operator= ( const OtherType * pointer )

Присваивает необработанный указатель типа, приводимого к ***Type***. ***Ptr*** берёт на себя владение указателем.
### Аргументы

- *const OtherType ** **pointer** - Необработанный указатель для присваивания.

### Возвращаемое значение

Ссылка на текущий объект ***Ptr***.
## bool isValid ( ) const

Проверяет, указывает ли ***Ptr*** в данный момент на действительный, существующий объект (значение указателя не nullptr).
### Возвращаемое значение

true, если внутренний адрес не nullptr; иначе false.
## bool isNull ( ) const

Проверяет, хранит ли ***Ptr*** в данный момент значение nullptr.
### Возвращаемое значение

true, если значение nullptr; иначе false.
## bool isDeleted ( ) const

Проверяет, указывает ли ***Ptr*** в данный момент на nullptr или запланирован ли объект к удалению (например, через *[deleteLater()](#deleteLater_void)* или движком).
### Возвращаемое значение

true, если объект удалён; иначе false.
## template < typename T >

## T * getInternalObject ( )

Возвращает внутренний объект, на который указывает указатель.
## void deleteLater ( )

 Выполняет отложенное удаление объекта. Указываемый объект будет удалён на следующем этапе *[swap()](../../../code/fundamentals/execution_sequence/main_loop.md)* последовательности выполнения.
> **Notice:** Этот метод можно вызывать **только для [non-ownership objects](../../../code/fundamentals/smartpointers.md#non_ownership_object).**


```cpp
NodePtr node = NodeDummy::create();

// Проверяем, существует ли узел
if (node)
	Log::message("The node is alive!\n");

// Удаляем узел
node.deleteLater();

```


## void deleteForce ( )

 Выполняет принудительное удаление объекта. Указываемый объект будет удалён немедленно. Вызов этого метода для объектов, зависящих от главного цикла (например, узлов), **безопасен только при выполнении из главного потока**.
> **Notice:** Этот метод можно вызывать **только для [non-ownership objects](../../../code/fundamentals/smartpointers.md#non_ownership_object).**


```cpp
NodePtr node = NodeDummy::create();

// Проверяем, существует ли узел
if (node)
	Log::message("The node is alive!\n");

// Удаляем узел
node.deleteForce();

```
