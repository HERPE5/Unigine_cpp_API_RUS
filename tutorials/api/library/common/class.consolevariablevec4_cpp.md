# Unigine::ConsoleVariableVec4 Class (CPP)

**Header:** #include <UnigineConsole.h>


Класс ConsoleVariableVec4 используется для создания консольной переменной типа *vec4* (вектор из 4 компонентов float).


## ConsoleVariableVec4 Class

### Методы класса

---

## void set ( Math:: vec4 value ) const

Задаёт значение переменной.
### Аргументы

- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **value** - Значение переменной.

## Math:: vec4 get ( ) const

Получает значение переменной.
### Возвращаемое значение

Значение переменной.
## ConsoleVariableVec4 ( const char * name , const char * desc , int save , Math:: vec4 value , Math:: vec4 min , Math:: vec4 max )

Конструктор консольной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const char ** **desc** - Описание переменной.
- *int* **save** - Значение, указывающее, следует ли сохранять значение переменной в файл конфигурации: **1** — сохранять переменную; иначе **0**.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **value** - Значение переменной типа Vec4.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **min** - Минимальное значение переменной.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **max** - Максимальное значение переменной.

## operator Math::vec4 ( ) const

Оператор приведения типа для переменной.
### Возвращаемое значение

Значение переменной.
## Math:: vec4 operator= ( Math:: vec4 value )

Оператор присваивания для переменной.
### Аргументы

- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **value** - Значение переменной.

## void setGetFunc ( vec4(*) func )

Задаёт функцию, которая будет вызвана при вызове функции [get()](#c_get) для переменной.
### Аргументы

- *vec4(*)* **func** - Указатель на функцию.

## void setSetFunc ( void (*)(vec4) func )

Задаёт функцию, которая будет вызвана при вызове функции [set()](#c_set_vec4) для переменной. Например:
```cpp
ConsoleVariableVec4 my_debug_mode(...);

my_debug_mode.setSetFunc([](vec4 new_value) -> void
{
	// сделать что-то с "new_value"
	// и/или выполнить здесь некоторые вызовы API
});

```


### Аргументы

- *void (*)(vec4)* **func** - Указатель на функцию.

## ~ConsoleVariableVec4 ( )

Деструктор.
