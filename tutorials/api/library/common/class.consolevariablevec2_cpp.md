# Unigine::ConsoleVariableVec2 Class (CPP)

**Header:** #include <UnigineConsole.h>


Класс ConsoleVariableVec2 используется для создания консольной переменной типа *vec2* (вектор из 2 компонентов float).


## ConsoleVariableVec2 Class

### Методы класса

---

## void set ( Math:: vec2 value ) const

Задаёт значение переменной.
### Аргументы

- *Math::[vec2](../../../api/library/math/class.vec2_cpp.md)* **value** - Значение переменной.

## Math:: vec2 get ( ) const

Получает значение переменной.
### Возвращаемое значение

Значение переменной.
## ConsoleVariableVec2 ( const char * name , const char * desc , int save , Math:: vec2 value , Math:: vec2 min , Math:: vec2 max )

Конструктор консольной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const char ** **desc** - Описание переменной.
- *int* **save** - Значение, указывающее, следует ли сохранять значение переменной в файл конфигурации: **1** — сохранять переменную; иначе **0**.
- *Math::[vec2](../../../api/library/math/class.vec2_cpp.md)* **value** - Значение переменной типа Vec2.
- *Math::[vec2](../../../api/library/math/class.vec2_cpp.md)* **min** - Минимальное значение переменной.
- *Math::[vec2](../../../api/library/math/class.vec2_cpp.md)* **max** - Максимальное значение переменной.

## operator Math::vec2 ( ) const

Оператор приведения типа для переменной.
### Возвращаемое значение

Значение переменной.
## Math:: vec2 operator= ( Math:: vec2 value )

Оператор присваивания для переменной.
### Аргументы

- *Math::[vec2](../../../api/library/math/class.vec2_cpp.md)* **value** - Значение переменной.

## void setGetFunc ( vec2(*) func )

Задаёт функцию, которая будет вызвана при вызове функции [get()](#c_get) для переменной.
### Аргументы

- *vec2(*)* **func** - Указатель на функцию.

## void setSetFunc ( void (*)(vec2) func )

Задаёт функцию, которая будет вызвана при вызове функции [set()](#c_set_vec2) для переменной. Например:
```cpp
ConsoleVariableVec2 my_debug_mode(...);

my_debug_mode.setSetFunc([](vec2 new_value) -> void
{
	// сделать что-то с "new_value"
	// и/или выполнить здесь некоторые вызовы API
});

```


### Аргументы

- *void (*)(vec2)* **func** - Указатель на функцию.

## ~ConsoleVariableVec2 ( )

Деструктор.
