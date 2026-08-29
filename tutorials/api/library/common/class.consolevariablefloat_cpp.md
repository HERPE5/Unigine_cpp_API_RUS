# Unigine::ConsoleVariableFloat Class (CPP)

**Header:** #include <UnigineConsole.h>


## ConsoleVariableFloat Class

### Методы класса

---

## void set ( float value ) const

Задаёт значение переменной.
### Аргументы

- *float* **value** - Значение переменной.

## float get ( ) const

Получает значение переменной.
### Возвращаемое значение

Значение переменной.
## ConsoleVariableFloat ( const char * name , const char * desc , int save , float value , float min , float max )

Конструктор консольной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const char ** **desc** - Описание переменной.
- *int* **save** - Значение, указывающее, следует ли сохранять значение переменной в файл конфигурации: **1** — сохранять переменную; иначе **0**.
- *float* **value** - Значение переменной типа float.
- *float* **min** - Минимальное значение переменной.
- *float* **max** - Максимальное значение переменной.

## operator float ( ) const

Оператор приведения типа для переменной.
### Возвращаемое значение

Значение переменной.
## float operator= ( float value )

Оператор присваивания для переменной.
### Аргументы

- *float* **value** - Значение переменной.

## void setGetFunc ( float(*) func )

Задаёт функцию, которая будет вызвана при вызове функции [get()](#c_get) для переменной.
### Аргументы

- *float(*)* **func** - Указатель на функцию.

## void setSetFunc ( void (*)(float) func )

Задаёт функцию, которая будет вызвана при вызове функции [set()](#c_set_float) для переменной. Например:
```cpp
ConsoleVariableFloat my_debug_mode(...);

my_debug_mode.setSetFunc([](float new_value) -> void
{
	// сделать что-то с "new_value"
	// и/или выполнить здесь некоторые вызовы API
});

```


### Аргументы

- *void (*)(float)* **func** - Указатель на функцию.

## ~ConsoleVariableFloat ( )

Деструктор.
