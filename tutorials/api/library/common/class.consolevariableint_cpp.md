# Unigine::ConsoleVariableInt Class (CPP)

**Header:** #include <UnigineConsole.h>


Класс ConsoleVariableInt используется для создания целочисленной консольной переменной.


Пример для консольной переменной *show_fps*:


```cpp
ConsoleVariableInt show_fps("show_fps","show frames per second counter\n"
  "0 is to hide FPS counter\n"
  "1 is to show FPS counter\n"
  "2 is to show more detailed FPS counter",1,1,0,2);

```


## ConsoleVariableInt Class

### Методы класса

---

## void set ( int value ) const

Задаёт значение переменной.
### Аргументы

- *int* **value** - Значение переменной.

## int get ( ) const

Получает значение переменной.
### Возвращаемое значение

Значение переменной.
## ConsoleVariableInt ( const char * name , const char * desc , int save , int value , int min , int max )

Конструктор консольной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const char ** **desc** - Описание переменной.
- *int* **save** - Значение, указывающее, следует ли сохранять значение переменной в файл конфигурации: **1** — сохранять переменную; иначе **0**.
- *int* **value** - Целочисленное значение переменной.
- *int* **min** - Минимальное значение переменной.
- *int* **max** - Максимальное значение переменной.

## operator int ( ) const

Оператор приведения типа для переменной.
### Возвращаемое значение

Значение переменной.
## int operator= ( int value )

Оператор присваивания для переменной.
### Аргументы

- *int* **value** - Значение переменной.

## void setGetFunc ( int(*) func )

Задаёт функцию, которая будет вызвана при вызове функции [get()](#c_get) для переменной.
### Аргументы

- *int(*)* **func** - Указатель на функцию.

## void setSetFunc ( void (*)(int) func )

Задаёт функцию, которая будет вызвана при вызове функции [set()](#c_set_int) для переменной. Например:
```cpp
ConsoleVariableInt my_debug_mode(...);

my_debug_mode.setSetFunc([](int new_value) -> void
{
	// сделать что-то с "new_value"
	// и/или выполнить здесь некоторые вызовы API
});

```


### Аргументы

- *void (*)(int)* **func** - Указатель на функцию.

## ~ConsoleVariableInt ( )

Деструктор.
