# Unigine::ConsoleVariableVec3 Class (CPP)

**Header:** #include <UnigineConsole.h>


Класс ConsoleVariableVec3 используется для создания консольной переменной типа *vec3* (вектор из 3 компонентов float).


## ConsoleVariableVec3 Class

### Методы класса

---

## void set ( Math:: vec3 value ) const

Задаёт значение переменной.
### Аргументы

- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **value** - Значение переменной.

## Math:: vec3 get ( ) const

Получает значение переменной.
### Возвращаемое значение

Значение переменной.
## ConsoleVariableVec3 ( const char * name , const char * desc , int save , Math:: vec3 value , Math:: vec3 min , Math:: vec3 max )

Конструктор консольной переменной.
### Аргументы

- *const char ** **name** - Имя переменной.
- *const char ** **desc** - Описание переменной.
- *int* **save** - Значение, указывающее, следует ли сохранять значение переменной в файл конфигурации: **1** — сохранять переменную; иначе **0**.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **value** - Значение переменной типа Vec3.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **min** - Минимальное значение переменной.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **max** - Максимальное значение переменной.

## operator Math::vec3 ( ) const

Оператор приведения типа для переменной.
### Возвращаемое значение

Значение переменной.
## Math:: vec3 operator= ( Math:: vec3 value )

Оператор присваивания для переменной.
### Аргументы

- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **value** - Значение переменной.

## void setGetFunc ( vec3(*) func )

Задаёт функцию, которая будет вызвана при вызове функции [get()](#c_get) для переменной.
### Аргументы

- *vec3(*)* **func** - Указатель на функцию.

## void setSetFunc ( void (*)(vec3) func )

Задаёт функцию, которая будет вызвана при вызове функции [set()](#c_set_vec3) для переменной. Например:
```cpp
ConsoleVariableVec3 my_debug_mode(...);

my_debug_mode.setSetFunc([](vec3 new_value) -> void
{
	// сделать что-то с "new_value"
	// и/или выполнить здесь некоторые вызовы API
});

```


### Аргументы

- *void (*)(vec3)* **func** - Указатель на функцию.

## ~ConsoleVariableVec3 ( )

Деструктор.
