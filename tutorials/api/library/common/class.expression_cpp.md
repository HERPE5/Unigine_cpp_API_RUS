# Unigine::Expression Class (CPP)


Этот класс позволяет выполнять заданный фрагмент кода во время выполнения. Выражению (Expression) можно передать до 4 аргументов любого типа. Функция [*setVariable()*](#setVariable_string_variable_void) задаёт значения таких аргументов. Например:


```cpp
Expression e0 = Expression(Engine::get()->getWorldInterpreter(), "133.0 * 133.0");
if (e0.isCompiled()) {
	Log::message("%f\n", e0.run().getFloat());
}

Expression e1 = Expression(Engine::get()->getWorldInterpreter(), " \
	{\
		int a, b, c, d; \
		return a + b + c + d; \
	}\
");

e1.setVariable("a", Variable(1));
e1.setVariable("b", Variable(2));
e1.setVariable("c", Variable(3));
e1.setVariable("d", Variable(4));

if (e1.isCompiled()) {
	Log::message("%d\n", e1.run().getInt());
}

Expression e2 = Expression(Engine::get()->getWorldInterpreter(), "\
	{\
		string name;\
		File file = new File(name, \"rb\");\
			int size = file.getSize();\
		file.close();\
		delete file;\
		return size;\
	}\
");
e2.setVariable("name", Variable("test.cpp"));
if (e2.isCompiled()) {
	Log::message("%d\n", e2.run().getInt());
}

```


```text
double: 17689
int: 10
int: 1302

```


## Expression Class

### Методы класса

---

## Expression ( void * interpreter , const char * src , int scope = 0 )

Конструктор. Создаёт выражение из указанного исходного буфера.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const char ** **src** - Указатель на исходный буфер. Исходный буфер — это строка, содержащая исходный код выражения.
- *int* **scope** - 1, чтобы рассматривать пространство имён выражения как глобальное; иначе 0 (по умолчанию).

## int isCompiled ( )

Возвращает значение, указывающее, было ли скомпилировано данное выражение.
### Возвращаемое значение

**1**, если выражение скомпилировано; иначе **0**.
## int getFunction ( const char* name , int num_args )

Возвращает идентификатор функции из пространства имён выражения. Его можно использовать для вызова функции по идентификатору вместо имени (ускоряет вызов функции; почти так же быстро, как прямой вызов).
### Аргументы

- *const char** **name** - Имя функции.
- *int* **num_args** - Количество аргументов функции.

### Возвращаемое значение

Идентификатор функции.
## int isFunction ( const char* name , int num_args )

Проверяет, существует ли заданная пользовательская функция в пространстве имён выражения.
### Аргументы

- *const char** **name** - Полное имя целевой функции.
- *int* **num_args** - Количество аргументов целевой функции.

### Возвращаемое значение

**1**, если функция существует; иначе **0**.
## void setName ( const char* name )

Задаёт имя пространства имён для выражения, которое можно использовать при вызове методов выражения.
### Аргументы

- *const char** **name** - Имя пространства имён.

## const char* getName ( )

Получает имя, используемое как имя пространства имён при вызове методов выражения.
### Возвращаемое значение

Имя пространства имён.
## void setVariable ( const char* name , variable value )

Задаёт значение переменной из пространства имён выражения по её имени.
### Аргументы

- *const char** **name** - Имя переменной.
- *[variable](../../../api/library/common/class.variable_cpp.md)* **value** - Значение переменной для установки.

## variable getVariable ( const char* name )

Возвращает идентификатор переменной из пространства имён выражения. Его можно использовать для передачи переменной по идентификатору вместо имени. Это ускоряет передачу переменной и может использоваться, когда важна производительность.
### Аргументы

- *const char** **name** - Имя переменной.

### Возвращаемое значение

Переменная, если она существует; иначе **0**.
## int isVariable ( const char* name )

Проверяет, существует ли заданная пользовательская переменная в пространстве имён выражения.
### Аргументы

- *const char** **name** - Имя целевой переменной.

### Возвращаемое значение

**1**, если переменная существует; иначе **0**.
## variable run ( )

Выполняет заданное выражение.
### Возвращаемое значение

Значение аргумента.
## bool saveState ( const Ptr < Stream > & stream )

Сохраняет данные выражения (все его параметры) в указанный бинарный поток.
**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_int):


```cpp
// инициализируем выражение и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
e1->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
e1->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который будут сохранены данные выражения.

### Возвращаемое значение

true, если данные выражения успешно сохранены; иначе false.
## bool restoreState ( const Ptr < Stream > & stream )

Восстанавливает данные выражения (все его параметры) из указанного бинарного потока.
**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_int):


```cpp
// инициализируем выражение и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
e1->saveState(blob_state);

// изменяем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
e1->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в котором хранятся сохранённые данные выражения.

### Возвращаемое значение

true, если данные выражения успешно восстановлены; иначе false.
