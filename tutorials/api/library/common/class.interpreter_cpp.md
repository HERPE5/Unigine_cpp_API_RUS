# Unigine::Interpreter Class (CPP)

**Header:** #include <UnigineInterpreter.h>


Интерпретатор Unigine.


Чтобы сгруппировать элементы (определения, библиотеки, переменные, функции, классы) вместе, нужно создать **группу** через *[addGroup()](#addGroup_const_char_ptr_int)*. Затем эту группу можно назначить в качестве аргумента элементу следующими методами:

- *[addExternDefine()](#addExternDefine_const_char_ptr_int_void)*
- *[addExternLibrary()](#addExternLibrary_const_char_ptr_int_void)*
- *[addExternVariable()](#addExternVariable_const_char_ptr_ExternVariableBase_ptr_int_void)*
- *[addExternFunction()](#addExternFunction_const_char_ptr_ExternFunctionBase_ptr_int_void)*
- *[addExternClass()](#addExternClass_const_char_ptr_ExternClassBase_ptr_int_void)*

Если одна и та же группа добавлена к нескольким элементам, все они могут быть удалены из интерпретатора одновременно через *[removeGroup()](#removeGroup_const_char_ptr_void)*.
## Interpreter Class

### Методы класса

---

## static void * get ( )

Возвращает текущий указатель интерпретатора.
### Возвращаемое значение

Указатель интерпретатора.
## static ExternClassBase * getExternClass ( const char * name )

Возвращает внешний пользовательский класс из UnigineScript.
### Аргументы

- *const char ** **name** - Имя класса.

### Возвращаемое значение

Указатель на внешний класс.
## static ExternFunctionBase * getExternFunction ( const char * name )

Возвращает внешнюю пользовательскую функцию из UnigineScript.
### Аргументы

- *const char ** **name** - Имя функции.

### Возвращаемое значение

Указатель на внешнюю функцию.
## static ExternVariableBase * getExternVariable ( const char * name )

Возвращает внешнюю пользовательскую переменную из UnigineScript.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Указатель на внешнюю переменную.
## static int getStack ( )

Возвращает текущую глубину стека интерпретатора.
### Возвращаемое значение

Глубина стека интерпретатора.
## static void addExternClass ( const char * name , ExternClassBase * extern_class , int group_id )

Добавляет внешний пользовательский класс в UnigineScript. Для создания внешней функции используйте команду MakeExternClass().
### Аргументы

- *const char ** **name** - Имя класса.
- *ExternClassBase ** **extern_class** - Указатель на внешний класс.
- *int* **group_id** - Идентификатор группы.

## void addExternDefine ( const char * name , int group_id )

Добавляет определение в UnigineScript. Эта функция аналогична *#define Foo*.
### Аргументы

- *const char ** **name** - Имя определения.
- *int* **group_id** - Идентификатор группы.

## void addExternFunction ( const char * name , ExternFunctionBase * extern_function , int group_id )

Добавляет внешнюю пользовательскую функцию в UnigineScript. Для создания внешней функции используйте команду *[addExternFunction()](#addExternFunction_const_char_ptr_ExternFunctionBase_ptr_int_void)*.
### Аргументы

- *const char ** **name** - Имя функции.
- *ExternFunctionBase ** **extern_function** - Указатель на внешнюю функцию.
- *int* **group_id** - Идентификатор группы.

## void addExternLibrary ( const char * name , int group_id )

Добавляет пространство имён внешней библиотеки в UnigineScript.
> **Notice:** Все внешние переменные и функции с именами вида *library.function()* будут рассматриваться как функции библиотеки.


### Аргументы

- *const char ** **name** - Имя библиотеки.
- *int* **group_id** - Идентификатор группы.

## void addExternVariable ( const char * name , ExternVariableBase * extern_variable , int group_id )

Добавляет внешнюю пользовательскую переменную в UnigineScript.
### Аргументы

- *const char ** **name** - Имя переменной.
- *ExternVariableBase ** **extern_variable** - Указатель на внешнюю переменную.
- *int* **group_id** - Идентификатор группы.

## int addGroup ( const char * group_name )

Добавляет новую группу с указанным именем. Эта группа назначается в качестве аргумента элементу следующими методами:
- *[addExternDefine()](#addExternDefine_const_char_ptr_int_void)*
- *[addExternLibrary()](#addExternLibrary_const_char_ptr_int_void)*
- *[addExternVariable()](#addExternVariable_const_char_ptr_ExternVariableBase_ptr_int_void)*
- *[addExternFunction()](#addExternFunction_const_char_ptr_ExternFunctionBase_ptr_int_void)*
- *[addExternClass()](#addExternClass_const_char_ptr_ExternClassBase_ptr_int_void)*

Если одна и та же группа добавлена к нескольким элементам (определениям, библиотекам, переменным, функциям, классам), все они могут быть удалены из интерпретатора одновременно через [removeGroup()](#removeGroup_const_char_ptr_void).
### Аргументы

- *const char ** **group_name** - Имя группы.

### Возвращаемое значение

Идентификатор группы.
## void error ( const char * format )

Функция ошибки интерпретатора.
### Аргументы

- *const char ** **format** - Строка формата. Она аналогична строке формата для printf() в C.

## static Variable popStack ( )

Извлекает переменную из текущего стека интерпретатора.
### Возвращаемое значение

Переменная.
## static void removeExternClass ( const char * name )

Удаляет пользовательский класс из UnigineScript.
### Аргументы

- *const char ** **name** - Имя класса.

## static void removeExternDefine ( const char * name )

Удаляет внешнее определение с указанным именем из UnigineScript. Эта функция аналогична *#undef Foo*.
### Аргументы

- *const char ** **name** - Имя определения.

## static void removeExternFunction ( const char * name )

Удаляет внешнюю пользовательскую функцию из UnigineScript.
### Аргументы

- *const char ** **name** - Имя функции.

## static void removeExternLibrary ( const char * name )

Удаляет пространство имён внешней библиотеки из UnigineScript.
### Аргументы

- *const char ** **name** - Имя библиотеки.

## static void removeExternVariable ( const char * name )

Удаляет внешнюю пользовательскую переменную из UnigineScript.
### Аргументы

- *const char ** **name** - Имя переменной.

## void removeGroup ( const char * group_name )

Удаляет все элементы (определения, библиотеки, переменные, функции, классы), добавленные методами *[addExternDefine()](#addExternDefine_const_char_ptr_int_void)*, *[addExternLibrary()](#addExternLibrary_const_char_ptr_int_void)*, *[addExternVariable()](#addExternVariable_const_char_ptr_ExternVariableBase_ptr_int_void)*, *[addExternFunction()](#addExternFunction_const_char_ptr_ExternFunctionBase_ptr_int_void)* и *[addExternClass()](#addExternClass_const_char_ptr_ExternClassBase_ptr_int_void)*, принадлежащие указанной группе.
### Аргументы

- *const char ** **group_name** - Имя группы.
