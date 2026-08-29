# Unigine::UlonValue Class (CPP)

**Header:** #include <UnigineUlon.h>


Этот класс используется для представления [value](../../../api/library/common/class.ulonnode_cpp.md) узла [ULON](../../../code/formats/ulon_format.md).


## UlonValue Class

### Members

## bool isArray () const

Возвращает текущее значение, указывающее, является ли значение узла ULON массивом.
### Return value

**true**, если значение узла ULON является массивом; в противном случае **false**.
## void setUsage ( bool usage )

Задаёт новое значение, указывающее, используется ли значение узла ULON (получено через один из методов *get*()*).
### Arguments

- *bool* **usage** - Установите **true**, чтобы включить использование значения узла ULON; **false** - чтобы отключить его.

## bool isUsage () const

Возвращает текущее значение, указывающее, используется ли значение узла ULON (получено через один из методов *get*()*).
### Return value

**true**, если использование значения узла ULON включено; в противном случае **false**.
---

## static UlonValuePtr create ( )

Конструктор. Создаёт значение узла ULON.
## static UlonValuePtr create ( const char * arg1 )

Конструктор. Создаёт значение узла ULON из указанного исходного буфера.
### Arguments

- *const char ** **arg1** - Исходный буфер значения узла ULON.

## const char * getStr ( ) const

Возвращает значение узла ULON в виде неформатированной строки.
### Return value

Значение узла ULON в виде неформатированной строки.
## double getDouble ( ) const

Возвращает значение узла ULON в виде double.
### Return value

Значение узла ULON типа double.
## float getFloat ( ) const

Возвращает значение узла ULON в виде float.
### Return value

Значение узла ULON типа float.
## int getInt ( ) const

Возвращает значение узла ULON в виде целого числа.
### Return value

Значение узла ULON типа integer.
## long long getLong ( ) const

Возвращает значение узла ULON в виде 64-битного long long.
### Return value

Значение узла ULON типа 64-битный long long.
## short getShort ( ) const

Возвращает значение узла ULON в виде 16-битного short.
### Return value

## char getChar ( ) const

Возвращает значение узла ULON в виде char.
### Return value

Значение узла ULON типа char.
## bool getBool ( ) const

Возвращает значение узла ULON в виде булева значения.
### Return value

Значение узла ULON типа boolean.
## Vector < String > getArray ( ) const

Возвращает значение узла ULON в виде массива строк.
### Return value

Массив строк, представляющих элементы массива.
## Math:: dvec4 getDVec4 ( ) const

Возвращает значение узла ULON в виде вектора [dvec4](../../../api/library/math/class.dvec4_cpp.md).
### Return value

Значение узла ULON в виде вектора [dvec4](../../../api/library/math/class.dvec4_cpp.md).
## Math:: vec4 getVec4 ( ) const

Возвращает значение узла ULON в виде вектора [vec4](../../../api/library/math/class.vec4_cpp.md).
### Return value

Значение узла ULON в виде вектора [vec4](../../../api/library/math/class.vec4_cpp.md).
## Math:: ivec4 getIVec4 ( ) const

Возвращает значение узла ULON в виде вектора [ivec4](../../../api/library/math/class.ivec4_cpp.md).
### Return value

Значение узла ULON в виде вектора [ivec4](../../../api/library/math/class.ivec4_cpp.md).
## void get ( Math:: dvec4 & ret ) const

Получает значение узла ULON в виде [dvec4](../../../api/library/math/class.dvec4_cpp.md) и помещает его в указанный выходной вектор.
### Arguments

- *Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **ret** - Выходной вектор [dvec4](../../../api/library/math/class.dvec4_cpp.md).

## void get ( Math:: vec4 & ret ) const

Получает значение узла ULON в виде [vec4](../../../api/library/math/class.vec4_cpp.md) и помещает его в указанный выходной вектор.
### Arguments

- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - Выходной вектор [vec4](../../../api/library/math/class.vec4_cpp.md).

## void get ( Math:: ivec4 & ret ) const

Получает значение узла ULON в виде [ivec4](../../../api/library/math/class.ivec4_cpp.md) и помещает его в указанный выходной вектор.
### Arguments

- *Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **ret** - Выходной вектор [ivec4](../../../api/library/math/class.ivec4_cpp.md).

## int read ( const char * src )

Считывает значение узла ULON из указанного исходного буфера.
### Arguments

- *const char ** **src** - Исходный буфер значения узла ULON.
