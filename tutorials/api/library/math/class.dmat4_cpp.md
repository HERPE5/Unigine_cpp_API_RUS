# Unigine::Math::dmat4 Struct (CPP)

**Header:** #include <UnigineMathLibDMat4.h>


Этот класс представляет матрицу из **двенадцати (3x4)** компонентов типа double.


Матрица *dmat4* используется только для мировых трансформаций (перемещение, масштабирование, вращение). Эта матрица не используется для 3D-проекции, поэтому её последняя строка пропущена (именно поэтому её размер 3x4, а не 4x4). Это позволяет избежать высокого расхода памяти и потери производительности при использовании координат двойной точности.


Первый, второй и третий столбцы матрицы представляют вращение и масштаб начала координат. Последний столбец содержит перемещение начала координат относительно мирового начала координат.


![](dmat4_matrix.png)


Для любых других целей можно использовать матрицу [mat4](../../../api/library/math/class.mat4_cpp.md).


## dmat4 Struct

### Методы класса

---

## dmat4 ( )

Конструктор по умолчанию. Создаёт единичную матрицу.
## dmat4 ( const dvec3& c0 , const dvec3& c1 , const dvec3& c2 , const dvec3& c3 )

Конструктор. Инициализирует матрицу с использованием трёх заданных векторов [dvec3](../../../api/library/math/class.dvec3_cpp.md).
```text
Результирующая матрица:
    | col0.x  	 col1.x	  	col2.x	   col3.x |
M=  | col0.y   	 col1.y	  	col2.y     col3.y |
    | col0.z   	 col1.z	  	col2.z     col3.z |

```


### Аргументы

- *const dvec3&* **c0** - Исходный вектор для первого столбца.
- *const dvec3&* **c1** - Исходный вектор для второго столбца.
- *const dvec3&* **c2** - Исходный вектор для третьего столбца.
- *const dvec3&* **c3** - Исходный вектор для четвёртого столбца.

## dmat4 ( const quat& q , const dvec3& v )

Конструктор. Инициализирует матрицу с использованием заданного [quaternion](../../../api/library/math/class.quat_cpp.md) и вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
### Аргументы

- *const quat&* **q** - Исходный кватернион.
- *const dvec3&* **v** - Исходный вектор.

## dmat4 ( const mat3& m , const dvec3& v )

Конструктор. Инициализирует матрицу с использованием заданной исходной матрицы [mat3](../../../api/library/math/class.mat3_cpp.md) (3x3) и вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
### Аргументы

- *const mat3&* **m** - Исходная матрица (3x3).
- *const dvec3&* **v** - Исходный вектор.

## dmat4 ( const mat3& m )

Конструктор. Инициализирует матрицу с использованием заданной исходной матрицы [mat3](../../../api/library/math/class.mat3_cpp.md) (3x3). Элементы матрицы заполняются соответствующими элементами исходной матрицы.
```text
Результирующая матрица:
    | m00  	 m01  	 m02	  0.0f |
M=  | m10    m11  	 m12      0.0f |
    | m20    m21     m22      0.0f |

```


### Аргументы

- *const mat3&* **m** - Исходная матрица (3x3).

## dmat4 ( const mat2& m )

Конструктор. Инициализирует матрицу с использованием заданной исходной матрицы [mat2](../../../api/library/math/class.mat2_cpp.md) (2x2). Элементы матрицы заполняются соответствующими элементами исходной матрицы.
```text
Результирующая матрица:
    | m00  	 m01  	 0.0f	  0.0f |
M=  | m10    m11  	 0.0f     0.0f |
    | 0.0f   0.0f    1.0f     0.0f |

```


### Аргументы

- *const mat2&* **m** - Исходная матрица (2x2).

## dmat4 ( double v )

Конструктор. Инициализирует матрицу заданным скалярным значением.
```cpp
dmat4(2.0);

/* Creates a matrix
| 2.0 	2.0 	2.0		2.0	|
| 2.0 	2.0 	2.0		2.0	|
| 2.0 	2.0 	2.0		2.0	|
*/

```


### Аргументы

- *double* **v** - Скалярное значение.

## dmat4 ( const dmat4& m )

Конструктор. Инициализирует матрицу путём копирования заданной исходной матрицы.
### Аргументы

- *const dmat4&* **m** - Исходная матрица.

## explicit dmat4 ( const mat4& m )

Конструктор. Инициализирует матрицу с использованием заданной исходной матрицы [mat4](../../../api/library/math/class.mat4_cpp.md) (4x4). Элементы матрицы заполняются соответствующими элементами исходной матрицы.
### Аргументы

- *const mat4&* **m** - Исходная матрица (4x4).

## explicit dmat4 ( const quat& q )

Конструктор. Инициализирует матрицу с использованием заданного исходного [quaternion](../../../api/library/math/class.quat_cpp.md).
### Аргументы

- *const quat&* **q** - Исходный кватернион.

## dmat4 ( const dmat4x4_values& m , int transposed )

Конструктор. Инициализирует матрицу с использованием заданных значений исходной матрицы.
### Аргументы

- *[const dmat4x4_values&](/api/library/math/auxiliary_types#dmat4x4_values)* **m** - Исходное значение, хранящее значения матрицы типа double.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## dmat4 ( const mat4x4_values& m , int transposed )

Конструктор. Инициализирует матрицу с использованием заданных значений исходной матрицы.
### Аргументы

- *[const mat4x4_values&](/api/library/math/auxiliary_types#mat4x4_values)* **m** - Исходное значение, хранящее значения матрицы типа float.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## dmat4 ( const dmat4x3_values& m , int transposed )

Конструктор. Инициализирует матрицу с использованием заданных значений исходной матрицы.
### Аргументы

- *[const dmat4x3_values&](/api/library/math/auxiliary_types#dmat4x3_values)* **m** - Исходное значение, хранящее значения матрицы типа double.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## dmat4 ( const mat4x3_values& m , int transposed )

Конструктор. Инициализирует матрицу значениями типа double с использованием заданных значений исходной матрицы типа float.
### Аргументы

- *[const mat4x3_values&](/api/library/math/auxiliary_types#mat4x3_values)* **m** - Исходное значение, хранящее значения матрицы типа float.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## dmat4 ( double m00_ , double m10_ , double m20_ , double m01_ , double m11_ , double m21_ , double m02_ , double m12_ , double m22_ , double m03_ , double m13_ , double m23_ )

Конструктор. Инициализирует матрицу заданными элементами типа double.
```text
 Результирующая матрица:
    | m00  	 m01  	 m02	 m03 |
M=  | m10    m11  	 m12     m13 |
    | m20    m21     m22     m23 |

```


### Аргументы

- *double* **m00_** - Элемент 00.
- *double* **m10_** - Элемент 10.
- *double* **m20_** - Элемент 20.
- *double* **m01_** - Элемент 01.
- *double* **m11_** - Элемент 11.
- *double* **m21_** - Элемент 21.
- *double* **m02_** - Элемент 02.
- *double* **m12_** - Элемент 12.
- *double* **m22_** - Элемент 22.
- *double* **m03_** - Элемент 03.
- *double* **m13_** - Элемент 13.
- *double* **m23_** - Элемент 23.

## dmat4 ( double v , ConstexprTag )

Конструктор. Инициализирует каждый элемент матрицы заданным элементом типа double.
```text
 Результирующая матрица:
    | v    v 	v   v |
M=  | v    v  	v   v |
    | v    v    v   v |

```


### Аргументы

- *double* **v** - Элемент, которым заполняется матрица.
- *ConstexprTag*  - Вспомогательный тег.

## dmat4 ( double m00_ , double m10_ , double m20_ , double m01_ , double m11_ , double m21_ , double m02_ , double m12_ , double m22_ , double m03_ , double m13_ , double m23_ , ConstexprTag )

Конструктор. Инициализирует матрицу заданными элементами типа double.
```text
 Результирующая матрица:
    | m00  	 m01  	 m02	 m03 |
M=  | m10    m11  	 m12     m13 |
    | m20    m21     m22     m23 |

```


### Аргументы

- *double* **m00_** - Элемент 00.
- *double* **m10_** - Элемент 10.
- *double* **m20_** - Элемент 20.
- *double* **m01_** - Элемент 01.
- *double* **m11_** - Элемент 11.
- *double* **m21_** - Элемент 21.
- *double* **m02_** - Элемент 02.
- *double* **m12_** - Элемент 12.
- *double* **m22_** - Элемент 22.
- *double* **m03_** - Элемент 03.
- *double* **m13_** - Элемент 13.
- *double* **m23_** - Элемент 23.
- *ConstexprTag*  - Вспомогательный тег.

## void set ( int row , int column , double v )

Задаёт новое значение элемента матрицы, указанного строкой и столбцом.
### Аргументы

- *int* **row** - Строка.
- *int* **column** - Столбец.
- *double* **v** - Устанавливаемое значение.

## void set ( const mat4x4_values& m , int transposed )

Задаёт матрицу с использованием аргумента со значениями типа float.
### Аргументы

- *[const mat4x4_values&](/api/library/math/auxiliary_types#mat4x4_values)* **m** - Исходное значение, хранящее значения матрицы типа float.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## void set ( const dmat4x4_values& m , int transposed )

Задаёт матрицу с использованием аргумента со значениями типа double.
### Аргументы

- *[const dmat4x4_values&](/api/library/math/auxiliary_types#dmat4x4_values)* **m** - Исходное значение, хранящее значения матрицы типа double.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## void set ( const mat4x3_values& m , int transposed )

Задаёт матрицу с использованием аргумента со значениями типа float.
### Аргументы

- *[const mat4x3_values&](/api/library/math/auxiliary_types#mat4x3_values)* **m** - Исходное значение, хранящее значения матрицы типа float.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## void set ( const dmat4x3_values& m , int transposed )

Задаёт матрицу с использованием аргумента со значениями типа double.
### Аргументы

- *[const dmat4x3_values&](/api/library/math/auxiliary_types#dmat4x3_values)* **m** - Исходное значение, хранящее значения матрицы типа double.
- *int* **transposed** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## void set ( const mat2& m )

Задаёт новые значения матрицы с использованием заданной исходной матрицы [mat2](../../../api/library/math/class.mat2_cpp.md) (2x2). Элементы матрицы заполняются соответствующими элементами исходной матрицы.
### Аргументы

- *const mat2&* **m** - Исходная матрица (2x2).

## void set ( const mat3& m )

Задаёт новые значения матрицы с использованием заданной исходной матрицы [mat3](../../../api/library/math/class.mat3_cpp.md) (3x3). Элементы матрицы заполняются соответствующими элементами исходной матрицы.
### Аргументы

- *const mat3&* **m** - Исходная матрица (3x3).

## void set ( const quat& q , const dvec3& v )

Задаёт новые значения матрицы с использованием заданного [quaternion](../../../api/library/math/class.quat_cpp.md) и вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
### Аргументы

- *const quat&* **q** - Исходный кватернион.
- *const dvec3&* **v** - Исходный вектор.

## void set ( const quat& q )

Задаёт новые значения матрицы с использованием заданного исходного [quaternion](../../../api/library/math/class.quat_cpp.md).
### Аргументы

- *const quat&* **q** - Исходный кватернион.

## void set ( const mat4& m )

Задаёт новые значения матрицы с использованием заданной исходной матрицы [mat4](../../../api/library/math/class.mat4_cpp.md) (4x4). Элементы матрицы заполняются соответствующими элементами исходной матрицы.
### Аргументы

- *const mat4&* **m** - Исходная матрица (4x4).

## void set ( const dmat4& m )

Задаёт матрицу равной указанной исходной матрице.
### Аргументы

- *const dmat4&* **m** - Исходная матрица.

## void set ( const mat3& m , const dvec3& v )

Задаёт новые значения матрицы с использованием заданной исходной матрицы [mat3](../../../api/library/math/class.mat3_cpp.md) (3x3) и вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
### Аргументы

- *const mat3&* **m** - Исходная матрица (3x3).
- *const dvec3&* **v** - Исходный вектор.

## double & get ( int row , int column )

Возвращает ссылку на элемент матрицы, указанный заданной строкой и столбцом.
### Аргументы

- *int* **row** - Строка.
- *int* **column** - Столбец.

### Возвращаемое значение

Ссылка на элемент матрицы.
## double get ( int row , int column ) const

Возвращает значение элемента матрицы, указанного заданной строкой и столбцом.
### Аргументы

- *int* **row** - Строка.
- *int* **column** - Столбец.

### Возвращаемое значение

Значение элемента матрицы.
## void get ( dmat4x3_values& m , int transpose ) const

Возвращает значения матрицы, заполняя указанный аргумент.
### Аргументы

- *[dmat4x3_values&](/api/library/math/auxiliary_types#dmat4x3_values)* **m** - Целевое значение для хранения значений матрицы типа double.
- *int* **transpose** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## void get ( dmat4x4_values& m , int transpose ) const

Возвращает значения матрицы, заполняя указанный аргумент.
### Аргументы

- *[dmat4x4_values&](/api/library/math/auxiliary_types#dmat4x4_values)* **m** - Целевое значение для хранения значений матрицы типа double.
- *int* **transpose** - Если установлено в **0** (по умолчанию), матрица задаётся в стиле column-major; если установлено в 1, матрица транспонирована.

## dmat4x3_values & get ( )

Возвращает значение, хранящее значения матрицы типа double.
### Возвращаемое значение

Значение, хранящее значения матрицы типа double.
## const dmat4x3_values & get ( ) const

Возвращает константное значение, хранящее значения матрицы типа double.
### Возвращаемое значение

Константное значение, хранящее значения матрицы типа double.
## void setColumn ( int column , const dvec4& v )

Задаёт указанный столбец матрицы, используя заданный вектор [dvec4](../../../api/library/math/class.dvec4_cpp.md) в качестве источника.
### Аргументы

- *int* **column** - Столбец.
- *const dvec4&* **v** - Исходный вектор.

## dvec4 getColumn ( int column ) const

Возвращает указанный столбец матрицы.
### Аргументы

- *int* **column** - Столбец.

### Возвращаемое значение

Вектор [dvec4](../../../api/library/math/class.vec4_cpp.md) со значениями столбца.
## void setColumn3 ( int column , const dvec3& v )

Задаёт указанный столбец матрицы, используя заданный трёхкомпонентный вектор [dvec3](../../../api/library/math/class.dvec3_cpp.md) в качестве источника.
### Аргументы

- *int* **column** - Столбец.
- *const dvec3&* **v** - Трёхкомпонентный исходный вектор.

## dvec3 getColumn3 ( int column ) const

Возвращает указанный столбец матрицы.
### Аргументы

- *int* **column** - Столбец.

### Возвращаемое значение

Вектор [dvec3](../../../api/library/math/class.dvec3_cpp.md) со значениями столбца.
## void setIdentity ( )

Задаёт матрицу равной единичной матрице.
## void setRotate ( const dvec3& axis , double angle )

Задаёт матрицу вращения для заданной оси.
### Аргументы

- *const dvec3&* **axis** - Ось вращения.
- *double* **angle** - Угол вращения, в градусах.

## quat getRotate ( ) const

Возвращает [quaternion](../../../api/library/math/class.quat_cpp.md), представляющий вращательную часть матрицы.
### Возвращаемое значение

Вращательная часть матрицы.
## void setRotateX ( double angle )

Задаёт матрицу вращения по X.
### Аргументы

- *double* **angle** - Угол вращения, в градусах.

## void setRotateY ( double angle )

Задаёт матрицу вращения по Y.
### Аргументы

- *double* **angle** - Угол вращения, в градусах.

## void setRotateZ ( double angle )

Задаёт матрицу вращения по Z.
### Аргументы

- *double* **angle** - Угол вращения, в градусах.

## void setRow ( int row , const dvec4& v )

Задаёт указанную строку матрицы, используя заданный вектор [dvec4](../../../api/library/math/class.dvec4_cpp.md) в качестве источника.
### Аргументы

- *int* **row** - Строка.
- *const dvec4&* **v** - Исходный вектор.

## dvec4 getRow ( int row ) const

Возвращает указанную строку матрицы.
### Аргументы

- *int* **row** - Строка.

### Возвращаемое значение

Вектор [dvec4](../../../api/library/math/class.dvec4_cpp.md) со значениями строки.
## void setRow3 ( int row , const dvec3& v )

Задаёт указанную строку матрицы, используя заданный трёхкомпонентный вектор [dvec3](../../../api/library/math/class.dvec3_cpp.md) в качестве источника, последний элемент строки остаётся неизменным.
### Аргументы

- *int* **row** - Строка.
- *const dvec3&* **v** - Трёхкомпонентный исходный вектор.

## dvec3 getRow3 ( int row ) const

Возвращает первые три элемента указанной строки матрицы.
### Аргументы

- *int* **row** - Строка.

### Возвращаемое значение

Вектор [dvec3](../../../api/library/math/class.dvec3_cpp.md) с первыми тремя элементами указанной строки матрицы.
## void setScale ( const dvec3& v )

Заполняет матрицу масштабирования с использованием заданного исходного вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
```text
Матрица масштабирования:
    | v.x   	0.0f  	  0.0f	    0.0f |
S=  | 0.0f      v.y  	  0.0f      0.0f |
    | 0.0f      0.0f      v.z  		0.0f |

```


### Аргументы

- *const dvec3&* **v** - Source vector.

## vec3 getScale ( ) const

Возвращает трёхкомпонентный вектор [vec3](../../../api/library/math/class.vec3_cpp.md), представляющий масштабирующую часть матрицы.
### Возвращаемое значение

Трёхкомпонентный вектор с масштабирующей частью матрицы.
## void setTranslate ( const dvec3& v )

Заполняет матрицу перемещения с использованием заданного исходного вектора [dvec3](../../../api/library/math/class.dvec3_cpp.md).
```text
Матрица перемещения:
    | 1.0f   	0.0f  	  0.0f	    v.x |
T=  | 0.0f      1.0f  	  0.0f      v.y |
    | 0.0f      0.0f      1.0f  	v.z |

```


### Аргументы

- *const dvec3&* **v** - Source vector.

## dvec3 getTranslate ( ) const

Возвращает трёхкомпонентный вектор [vec3](../../../api/library/math/class.vec3_cpp.md), представляющий часть перемещения матрицы.
### Возвращаемое значение

Трёхкомпонентный вектор с частью перемещения матрицы.
## void setZero ( )

Задаёт все элементы матрицы равными **0**.
## const double * operator const double * ( ) const

Выполняет преобразование типа в const double *.
## const void * operator const void * ( ) const

Выполняет преобразование типа в const void *.
## double * operator double * ( )

Выполняет преобразование типа в double *.
## void * operator void * ( )

Выполняет преобразование типа в void *.
## dmat4 & operator*= ( const dmat4& m )

Выполняет умножение матриц.
### Аргументы

- *const dmat4&* **m** - Матрица.

### Возвращаемое значение

Результирующая матрица.
## dmat4 & operator*= ( double v )

Выполняет умножение на скаляр.
### Аргументы

- *double* **v** - Скалярное значение.

### Возвращаемое значение

Resulting matrix.
## dmat4 & operator+= ( const dmat4& m )

Выполняет сложение матриц.
### Аргументы

- *const dmat4&* **m** - Матрица.

### Возвращаемое значение

Результирующая матрица.
## dmat4 operator- ( ) const

Выполняет отрицание матрицы.
### Возвращаемое значение

Resulting matrix.
## dmat4 & operator-= ( const dmat4& m )

Выполняет вычитание матриц.
### Аргументы

- *const dmat4&* **m** - Матрица.

### Возвращаемое значение

Результирующая матрица.
## dmat4 & operator= ( const dmat4& m )

Выполняет присваивание матрицы. Целевая матрица = Исходная матрица.
### Аргументы

- *const dmat4&* **m** - Исходная матрица.

### Возвращаемое значение

Result.
## double & operator[] ( int i )

Выполняет доступ к элементу массива матрицы по ссылке, используя заданный индекс элемента.
### Аргументы

- *int* **i** - Индекс элемента матрицы.

### Возвращаемое значение

Ссылка на элемент матрицы.
## double operator[] ( int i ) const

Выполняет доступ к элементу массива матрицы, используя заданный индекс элемента.
### Аргументы

- *int* **i** - Индекс элемента матрицы.

### Возвращаемое значение

Элемент матрицы.
## dvec3 getAxisX ( ) const

Возвращает нормализованный вектор, представляющий ось X. Вызовите этот метод, чтобы получить правый или левый вектор матрицы:
```cpp
matrix.getAxisX(); // левый вектор
-matrix.getAxisX(); // правый вектор

```


### Возвращаемое значение

Вектор, представляющий ось X.
## dvec3 getAxisY ( ) const

Возвращает нормализованный вектор, представляющий ось Y. Вызовите этот метод, чтобы получить задний или передний вектор матрицы:
```cpp
matrix.getAxisY(); // задний вектор
-matrix.getAxisY(); // передний вектор

```


### Возвращаемое значение

Вектор, представляющий ось Y.
## dvec3 getAxisZ ( ) const

Возвращает нормализованный вектор, представляющий ось Z. Вызовите этот метод, чтобы получить верхний или нижний вектор матрицы:
```cpp
matrix.getAxisZ(); // верхний вектор
-matrix.getAxisZ(); // нижний вектор

```


### Возвращаемое значение

Вектор, представляющий ось Z.
## double determinant ( const dmat4& m )

Возвращает определитель заданной матрицы.
### Аргументы

- *const dmat4&* **m** - Входная матрица.

### Возвращаемое значение

Определитель матрицы.
## dmat4 translate ( const dvec3& v )

Возвращает матрицу перемещения с использованием заданного вектора перемещения [dvec3](../../../api/library/math/class.dvec3_cpp.md).
```text
Матрица перемещения:
    | 1.0f   	0.0f  	  0.0f	    v.x |
T=  | 0.0f      1.0f  	  0.0f      v.y |
    | 0.0f      0.0f      1.0f  	v.z |

```


### Аргументы

- *const dvec3&* **v** - Вектор перемещения.

### Возвращаемое значение

Матрица перемещения.
## dmat4 translate ( const dvec4& v )

Возвращает матрицу перемещения с использованием заданного вектора перемещения [dvec4](../../../api/library/math/class.dvec4_cpp.md).
```text
Матрица перемещения:
    | 1.0f   	0.0f  	  0.0f	    v.x |
T=  | 0.0f      1.0f  	  0.0f      v.y |
    | 0.0f      0.0f      1.0f  	v.z |

```


### Аргументы

- *const dvec4&* **v** - Вектор перемещения.

### Возвращаемое значение

Матрица перемещения.
## dmat4 translate ( const dvec2& v )

Возвращает матрицу перемещения с использованием заданного вектора перемещения [dvec2](../../../api/library/math/class.dvec2_cpp.md).
```text
Матрица перемещения:
    | 1.0f   	0.0f  	  0.0f	    v.x |
T=  | 0.0f      1.0f  	  0.0f      v.y |
    | 0.0f      0.0f      1.0f  	v.z |

```


### Аргументы

- *const dvec2&* **v** - Вектор перемещения.

### Возвращаемое значение

Матрица перемещения.
## dmat4 translate ( double x , double y , double z )

Возвращает матрицу перемещения с использованием вектора перемещения [dvec3](../../../api/library/math/class.dvec3_cpp.md) с заданными компонентами.
```text
Матрица перемещения:
    | 1.0f   	0.0f  	  0.0f	    v.x |
T=  | 0.0f      1.0f  	  0.0f      v.y |
    | 0.0f      0.0f      1.0f  	v.z |

```


### Аргументы

- *double* **x** - Компонент X вектора перемещения.
- *double* **y** - Компонент Y вектора перемещения.
- *double* **z** - Компонент Z вектора перемещения.

### Возвращаемое значение

Матрица перемещения.
## dmat4 rotate ( const dvec3& axis , double angle )

Возвращает матрицу вращения для заданной оси и угла.
### Аргументы

- *const dvec3&* **axis** - Ось вращения.
- *double* **angle** - Угол вращения, в градусах.

### Возвращаемое значение

Rotated matrix.
## dmat4 rotate ( double x , double y , double z , double angle )

Возвращает матрицу вращения для угла и оси с заданными компонентами.
### Аргументы

- *double* **x** - Компонент X вектора вращения.
- *double* **y** - Компонент Y вектора вращения.
- *double* **z** - Компонент Z вектора вращения.
- *double* **angle** - Угол вращения, в градусах.

### Возвращаемое значение

Повёрнутая матрица.
## dmat4 rotateX ( double angle )

Возвращает матрицу, повёрнутую вокруг оси X на заданный угол.
### Аргументы

- *double* **angle** - Угол вращения, в градусах.

### Возвращаемое значение

Повёрнутая матрица.
## dmat4 rotateY ( double angle )

Возвращает матрицу, повёрнутую вокруг оси Y на заданный угол.
### Аргументы

- *double* **angle** - Угол вращения, в градусах.

### Возвращаемое значение

Повёрнутая матрица.
## dmat4 rotateZ ( double angle )

Возвращает матрицу, повёрнутую вокруг оси Z на заданный угол.
### Аргументы

- *double* **angle** - Угол вращения, в градусах.

### Возвращаемое значение

Повёрнутая матрица.
## dmat4 scale ( const dvec3& v )

Возвращает матрицу, масштабированную заданным исходным вектором [dvec3](../../../api/library/math/class.dvec3_cpp.md).
```text
Матрица масштабирования:
    | v.x   	0.0f  	  0.0f	    0.0f |
S=  | 0.0f      v.y  	  0.0f      0.0f |
    | 0.0f      0.0f      v.z  		0.0f |

```


### Аргументы

- *const dvec3&* **v** - Исходный вектор.

### Возвращаемое значение

Масштабированная матрица.
## dmat4 scale ( double x , double y , double z )

Возвращает матрицу, масштабированную заданным исходным вектором [dvec3](../../../api/library/math/class.dvec3_cpp.md).
```text
Матрица масштабирования:
    | v.x   	0.0f  	  0.0f	    0.0f |
S=  | 0.0f      v.y  	  0.0f      0.0f |
    | 0.0f      0.0f      v.z  		0.0f |

```


### Аргументы

- *double* **x** - Компонент X вектора масштаба.
- *double* **y** - Компонент Y вектора масштаба.
- *double* **z** - Компонент Z вектора масштаба.

### Возвращаемое значение

Масштабированная матрица.
## dmat4 scale ( double x )

Возвращает матрицу, масштабированную заданным исходным вектором [dvec3](../../../api/library/math/class.dvec3_cpp.md), в котором каждый компонент равен одному заданному значению.
```text
Матрица масштабирования:
    | v.x   	0.0f  	  0.0f	    0.0f |
S=  | 0.0f      v.y  	  0.0f      0.0f |
    | 0.0f      0.0f      v.z  		0.0f |

```


### Аргументы

- *double* **x** - Компоненты X, Y и Z вектора масштаба.

### Возвращаемое значение

Масштабированная матрица.
## unsigned int hash ( ) const

Возвращает хэш, полученный смешиванием хэш-значений компонентов вектора.
### Возвращаемое значение

32-битное значение хэша.
## dmat4 mul ( dmat4 & ret , const dmat4 & m , double v )

Умножение матриц.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ret** - Матрица для хранения результата.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - Значение матрицы.
- *double* **v** - Значение скаляра.

### Возвращаемое значение

Результирующая матрица.
## dmat4 mul ( dmat4 & ret , const dmat4 & m0 , const dmat4 & m1 )

Умножение матриц.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ret** - Матрица для хранения результата.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m0** - Значение первой матрицы.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m1** - Значение второй матрицы.

### Возвращаемое значение

Результирующая матрица.
## vec2 mul ( vec2 & ret , const dmat4 & m , const vec2 & v )

Умножение матрицы на вектор.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec2 mul ( vec2 & ret , const vec2 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul ( vec3 & ret , const dmat4 & m , const vec3 & v )

Умножение матрицы на вектор.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul ( vec3 & ret , const vec3 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul ( vec4 & ret , const dmat4 & m , const vec4 & v )

Умножение матрицы на вектор.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [vec4](../../../api/library/math/class.vec4_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul ( vec4 & ret , const vec4 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [vec4](../../../api/library/math/class.vec4_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec2 mul ( vec2 & ret , const dmat4 & m , const dvec2 & v )

Умножение матрицы на вектор.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec2 mul ( vec2 & ret , const dvec2 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul ( vec3 & ret , const dmat4 & m , const dvec3 & v )

Умножение матрицы на вектор.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul ( vec3 & ret , const dvec3 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul ( vec4 & ret , const dmat4 & m , const dvec4 & v )

Умножение матрицы на вектор.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul ( vec4 & ret , const dvec4 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## dvec2 mul ( dvec2 & ret , const dmat4 & m , const dvec2 & v )

Умножение матрицы на вектор.
### Аргументы

- *[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## dvec2 mul ( dvec2 & ret , const dvec2 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## dvec3 mul ( dvec3 & ret , const dmat4 & m , const dvec3 & v )

Умножение матрицы на вектор.
### Аргументы

- *[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## dvec3 mul ( dvec3 & ret , const dvec3 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## dvec4 mul ( dvec4 & ret , const dmat4 & m , const dvec4 & v )

Умножение матрицы на вектор.
### Аргументы

- *[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## dvec4 mul ( dvec4 & ret , const dvec4 & v , const dmat4 & m )

Умножение вектора на матрицу.
### Аргументы

- *[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec2 mul3 ( vec2 & ret , const dmat4 & m , const vec2 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec2 mul3 ( vec2 & ret , const vec2 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul3 ( vec3 & ret , const dmat4 & m , const vec3 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul3 ( vec3 & ret , const vec3 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul3 ( vec4 & ret , const dmat4 & m , const vec4 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [vec4](../../../api/library/math/class.vec4_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul3 ( vec4 & ret , const vec4 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [vec4](../../../api/library/math/class.vec4_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec2 mul3 ( vec2 & ret , const dmat4 & m , const dvec2 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec2 mul3 ( vec2 & ret , const dvec2 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul3 ( vec3 & ret , const dmat4 & m , const dvec3 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec3 mul3 ( vec3 & ret , const dvec3 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul3 ( vec4 & ret , const dmat4 & m , const dvec4 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## vec4 mul3 ( vec4 & ret , const dvec4 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[vec4](../../../api/library/math/class.vec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## dvec2 mul3 ( dvec2 & ret , const dmat4 & m , const dvec2 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## dvec2 mul3 ( dvec2 & ret , const dvec2 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## dvec3 mul3 ( dvec3 & ret , const dmat4 & m , const dvec3 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## dvec3 mul3 ( dvec3 & ret , const dvec3 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## dvec4 mul3 ( dvec4 & ret , const dmat4 & m , const dvec4 & v )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующий вектор.
## dvec4 mul3 ( dvec4 & ret , const dvec4 & v , const dmat4 & m )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **ret** - The vector to store the result.
- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - The value of the vector.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.

### Возвращаемое значение

Результирующий вектор.
## dmat4 mul3 ( dmat4 & ret , const dmat4 & m0 , const dmat4 & m1 )

Возвращает результат умножения трёх компонентов указанных аргументов.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ret** - Матрица для хранения результата.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m0** - Значение первой матрицы.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m1** - Значение второй матрицы.

### Возвращаемое значение

Результирующая матрица.
## dmat4 mul4 ( dmat4 & ret , const dmat4 & m0 , const dmat4 & m1 )

Возвращает результат умножения указанных аргументов.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ret** - Матрица для хранения результата.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m0** - Значение первой матрицы.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m1** - Значение второй матрицы.

### Возвращаемое значение

Результирующая матрица.
## dmat4 mult ( dmat4 & ret , const dmat4 & m , const dvec3 & v )

Возвращает матрицу, у которой перемещение (последний столбец) умножено на указанный вектор.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ret** - The matrix to store the result.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - The value of the matrix.
- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - The value of the vector.

### Возвращаемое значение

Результирующая матрица.
## dmat4 add ( dmat4 & ret , const dmat4 & m0 , const dmat4 & m1 )

Выполняет сложение с указанными аргументами.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ret** - Матрица для хранения результата.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m0** - Значение первой матрицы.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m1** - Значение второй матрицы.

### Возвращаемое значение

Результирующая матрица.
## dmat4 sub ( dmat4 & ret , const dmat4 & m0 , const dmat4 & m1 )

Вычитает каждый элемент второго аргумента из соответствующего элемента первого аргумента.
### Аргументы

- *[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ret** - Матрица для хранения результата.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m0** - Значение первой матрицы.
- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m1** - Значение второй матрицы.

### Возвращаемое значение

Результирующая матрица.
