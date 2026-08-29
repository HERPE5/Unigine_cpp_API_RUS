# Unigine::Reflection Class (CPP)

**Header:** #include <UnigineInterpreter.h>


Этот класс используется для создания рефлексий для пользовательских или внешних классов и пространств имён. Он позволяет получать имена и строки пользовательских атрибутов для всех переменных, массивов, пользовательских классов и пространств имён внутри него. Такие атрибуты можно использовать для умной автоматической генерации кода для GUI или любой игровой логики. Например, можно получить атрибуты, разобрать их нужным образом и передать их в [Expression](../../../api/library/common/class.expression_cpp.md), который скомпилирует итоговый код.


## Reflection Class

### Методы класса

---

## Reflection ( void * interpreter , const Variable & v )

### Аргументы

- *void ** **interpreter**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v**

## int getNumFunctionDefaultArgs ( int num )

### Аргументы

- *int* **num**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**

## Variable callExternClassFunction ( Variable object , const char * function , int num_args , const Variable * args )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *int* **num_args**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args**

## Variable callExternClassFunction ( Variable object , int function )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**

## Variable callExternClassFunction ( Variable object , int function , int num_args , const Vector < Variable > & args )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *int* **num_args**
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Variable](../../../api/library/common/class.variable_cpp.md)> &* **args**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**

## Variable callExternClassFunction ( Variable object , const char * function )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**

## Variable callExternClassFunction ( Variable object , const char * function , int num_args , const Vector < Variable > & args )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *int* **num_args**
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Variable](../../../api/library/common/class.variable_cpp.md)> &* **args**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**

## Variable callExternClassFunction ( Variable object , const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 , const Variable & arg8 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg8**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 , const Variable & arg8 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg8**

## Variable callExternClassFunction ( Variable object , int function , int num_args , const Variable * args )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *int* **num_args**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args**

## Variable callExternClassFunction ( Variable object , int function , const Variable & arg0 , const Variable & arg1 )

### Аргументы

- *[Variable](../../../api/library/common/class.variable_cpp.md)* **object**
- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**

## Variable callExternFunction ( const char * function , int num_args , const Vector < Variable > & args )

### Аргументы

- *const char ** **function**
- *int* **num_args**
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Variable](../../../api/library/common/class.variable_cpp.md)> &* **args**

## Variable callExternFunction ( int function , int num_args , const Variable * args )

### Аргументы

- *int* **function**
- *int* **num_args**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**

## Variable callExternFunction ( const char * function )

### Аргументы

- *const char ** **function**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 , const Variable & arg8 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg8**

## Variable callExternFunction ( const char * function , const Variable & arg0 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**

## Variable callExternFunction ( int function , const Variable & arg0 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 , const Variable & arg8 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg8**

## Variable callExternFunction ( int function , int num_args , const Vector < Variable > & args )

### Аргументы

- *int* **function**
- *int* **num_args**
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Variable](../../../api/library/common/class.variable_cpp.md)> &* **args**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**

## Variable callExternFunction ( const char * function , int num_args , const Variable * args )

### Аргументы

- *const char ** **function**
- *int* **num_args**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) ** **args**

## Variable callExternFunction ( int function )

### Аргументы

- *int* **function**

## Variable callExternFunction ( const char * function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 , const Variable & arg7 )

### Аргументы

- *const char ** **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg7**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 , const Variable & arg2 , const Variable & arg3 , const Variable & arg4 , const Variable & arg5 , const Variable & arg6 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg2**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg3**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg4**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg5**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg6**

## Variable callExternFunction ( int function , const Variable & arg0 , const Variable & arg1 )

### Аргументы

- *int* **function**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg0**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **arg1**

## int reflect ( void * interpreter , const Variable & v )

### Аргументы

- *void ** **interpreter**
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v**
