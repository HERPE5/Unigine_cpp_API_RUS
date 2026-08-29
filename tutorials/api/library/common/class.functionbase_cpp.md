# Unigine::FunctionBase Class (CPP)

**Header:** #include <UnigineFunction.h>


Базовый класс функции.


## FunctionBase Class

### Методы класса

---

## FunctionBase ( )

Конструктор по умолчанию.
## void setArg ( int num , const Variable & a )

Задаёт значение аргумента.
### Аргументы

- *int* **num** - Номер аргумента.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **a** - Значение аргумента.

## const Variable & getArg ( int num )

Получает значение аргумента.
### Аргументы

- *int* **num** - Номер аргумента.

### Возвращаемое значение

Значение аргумента.
## void setName ( const Variable & n )

Задаёт имя функции.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **n** - Имя функции.

## const Variable & getName ( ) const

Возвращает имя функции.
### Возвращаемое значение

Имя функции.
## virtual int getNumArgs ( ) const =0

Возвращает количество аргументов.
### Возвращаемое значение

Количество аргументов.
## Variable runEditor ( ) const

Выполняет функцию скрипта редактора.
### Возвращаемое значение

Возвращаемое значение функции скрипта редактора.
## Variable runSystem ( ) const

Выполняет функцию системного скрипта.
### Возвращаемое значение

Возвращаемое значение функции системного скрипта.
## Variable runWorld ( ) const

Выполняет функцию скрипта мира.
### Возвращаемое значение

Возвращаемое значение функции скрипта мира.
