# Unigine::ConsoleVariableString Class (CPP)

**Header:** #include <UnigineConsole.h>


## ConsoleVariableString Class

### Методы класса

---

## void set ( const char * value ) const

Задаёт значение переменной.
### Аргументы

- *const char ** **value** - Значение переменной.

## const char * get ( ) const

Получает значение переменной.
### Возвращаемое значение

Значение переменной.
## ConsoleVariableString ( const char * name , const char * desc , int save , const char * value )

Конструктор консольной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const char ** **desc** - Описание переменной.
- *int* **save** - Значение, указывающее, следует ли сохранять значение переменной в файл конфигурации: **1** — сохранять переменную; иначе **0**.
- *const char ** **value** - Значение переменной.

## operator const char * ( ) const

Оператор приведения типа для переменной.
### Возвращаемое значение

Значение переменной.
## const char * operator= ( const char * value )

Оператор присваивания для переменной.
### Аргументы

- *const char ** **value** - Значение переменной.

## void setGetFunc ( String(*) func )

Задаёт функцию, которая будет вызвана при вызове функции [get()](#c_get) для переменной.
### Аргументы

- *String(*)* **func** - Указатель на функцию.

## void setSetFunc ( void (*)(String) func )

Задаёт функцию, которая будет вызвана при вызове функции [set()](#c_set_constcharm) для переменной. Например:
```cpp
ConsoleVariableString my_debug_mode(...);

my_debug_mode.setSetFunc([](String new_value) -> void
{
	// сделать что-то с "new_value"
	// и/или выполнить здесь некоторые вызовы API
});

```


### Аргументы

- *void (*)(String)* **func** - Указатель на функцию.

## ~ConsoleVariableString ( )

Деструктор.
