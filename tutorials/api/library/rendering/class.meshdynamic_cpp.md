# Unigine.MeshDynamic Class (CPP)

**Header:** #include <UnigineMeshDynamic.h>


Этот класс используется для процедурного создания динамических мешей (т.е. треугольников, линий или точек) и их изменения во время выполнения.


## MeshDynamic Class

### Перечисления

## BUFFER

| Name | Description |
|---|---|
| **USAGE_IMMUTABLE_VERTEX** = 1 << 0 | Буфер вершин будет создан в памяти GPU как неизменяемый ресурс. |
| **USAGE_IMMUTABLE_INDICES** = 1 << 1 | Буфер индексов будет создан в памяти GPU как неизменяемый ресурс. |
| **USAGE_IMMUTABLE_ALL** = (USAGE_IMMUTABLE_VERTEX \| USAGE_IMMUTABLE_INDICES) | Буферы вершин и индексов будут созданы в памяти GPU как неизменяемые ресурсы. |
| **USAGE_DYNAMIC_VERTEX** = 1 << 2 | Буфер вершин будет создан в памяти GPU как динамический ресурс. |
| **USAGE_DYNAMIC_INDICES** = 1 << 3 | Буфер индексов будет создан в памяти GPU как динамический ресурс. |
| **USAGE_DYNAMIC_ALL** = (USAGE_DYNAMIC_VERTEX \| USAGE_DYNAMIC_INDICES) | Буферы вершин и индексов будут созданы в памяти GPU как динамические ресурсы. |
| **USAGE_FLUSH_VERTEX** = 1 << 4 | Данные обновлённых вершин будут отправлены с CPU на GPU. |
| **USAGE_FLUSH_INDICES** = 1 << 5 | Данные обновлённых индексов будут отправлены с CPU на GPU. |
| **USAGE_FLUSH_ALL** = (USAGE_FLUSH_VERTEX \| USAGE_FLUSH_INDICES) | Данные обновлённых вершин и индексов будут отправлены с CPU на GPU. |
| **USAGE_MISC_SHARED** = 1 << 6 | Данные доступны внешнему графическому API (применимо только для DX12 и Vulkan). |

## TYPE

| Name | Description |
|---|---|
| **TYPE_HALF** = 0 | Тип данных с плавающей точкой половинной точности. |
| **TYPE_FLOAT** = 1 | Тип данных с плавающей точкой. |
| **TYPE_UCHAR** = 2 | Тип данных беззнаковый символ. |
| **TYPE_USHORT** = 3 | Тип данных беззнаковое короткое целое. |
| **NUM_TYPES** = 4 | Количество типов данных. |

## MODE

| Name | Description |
|---|---|
| **MODE_POINTS** = 0 | Режим рендеринга точек. |
| **MODE_LINES** = 1 | Режим рендеринга линий. |
| **MODE_TRIANGLES** = 2 | Режим рендеринга треугольников. |
| **MODE_TRIANGLE_PATCHES** = 3 | Режим рендеринга треугольных патчей. |
| **MODE_QUAD_PATCHES** = 4 | Режим рендеринга четырёхугольных патчей. |
| **NUM_MODES** = 5 | Количество режимов рендеринга. |

### Методы класса

## void setFlags ( int flags )

Задаёт новый набор флагов динамического меша.
> **Notice:** Флаг [USAGE_IMMUTABLE_VERTEX](#USAGE_IMMUTABLE_VERTEX) не может использоваться вместе с флагом [USAGE_DYNAMIC_VERTEX](#USAGE_DYNAMIC_VERTEX).
>
>
> Флаг [USAGE_IMMUTABLE_INDICES](#USAGE_IMMUTABLE_INDICES) не может использоваться вместе с флагом [USAGE_DYNAMIC_INDICES](#USAGE_DYNAMIC_INDICES).
>
>
> [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) может использоваться только вместе с [USAGE_IMMUTABLE_ALL](#USAGE_IMMUTABLE_ALL).


### Аргументы

- *int* **flags** - Флаги создания. Комбинация флагов [USAGE_IMMUTABLE_*](#USAGE_IMMUTABLE_VERTEX), [USAGE_DYNAMIC_*](#USAGE_DYNAMIC_VERTEX) и [USAGE_FLUSH_*](#USAGE_FLUSH_VERTEX).

## int getFlags () const

Возвращает текущий набор флагов динамического меша.
> **Notice:** Флаг [USAGE_IMMUTABLE_VERTEX](#USAGE_IMMUTABLE_VERTEX) не может использоваться вместе с флагом [USAGE_DYNAMIC_VERTEX](#USAGE_DYNAMIC_VERTEX).
>
>
> Флаг [USAGE_IMMUTABLE_INDICES](#USAGE_IMMUTABLE_INDICES) не может использоваться вместе с флагом [USAGE_DYNAMIC_INDICES](#USAGE_DYNAMIC_INDICES).
>
>
> [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) может использоваться только вместе с [USAGE_IMMUTABLE_ALL](#USAGE_IMMUTABLE_ALL).


### Возвращаемое значение

Текущие флаги создания. Комбинация флагов [USAGE_IMMUTABLE_*](#USAGE_IMMUTABLE_VERTEX), [USAGE_DYNAMIC_*](#USAGE_DYNAMIC_VERTEX) и [USAGE_FLUSH_*](#USAGE_FLUSH_VERTEX).
## bool isUsageShared () const

Возвращает текущее значение, указывающее, включён ли для Mesh Dynamic флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED).
### Возвращаемое значение

**true**, если флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) для Mesh Dynamic включён; иначе **false**.
---

## Ptr < MeshDynamic > create ( int flags )

Создаёт новый экземпляр динамического меша в соответствии с заданными флагами.
> **Notice:** Флаг [USAGE_IMMUTABLE_VERTEX](#USAGE_IMMUTABLE_VERTEX) не может использоваться вместе с флагом [USAGE_DYNAMIC_VERTEX](#USAGE_DYNAMIC_VERTEX).
>
>
> Флаг [USAGE_IMMUTABLE_INDICES](#USAGE_IMMUTABLE_INDICES) не может использоваться вместе с флагом [USAGE_DYNAMIC_INDICES](#USAGE_DYNAMIC_INDICES).
>
>
> [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) может использоваться только вместе с [USAGE_IMMUTABLE_ALL](#USAGE_IMMUTABLE_ALL).


### Аргументы

- *int* **flags** - Флаги создания. Комбинация флагов [USAGE_IMMUTABLE_*](#USAGE_IMMUTABLE_VERTEX), [USAGE_DYNAMIC_*](#USAGE_DYNAMIC_VERTEX) и [USAGE_FLUSH_*](#USAGE_FLUSH_VERTEX).

### Возвращаемое значение

Умный указатель на MeshDynamic.
## bool copy ( const Ptr < MeshDynamic > & dest ) const

Копирует динамический меш в заданную цель.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshDynamic](../../../api/library/rendering/class.meshdynamic_cpp.md)> &* **dest** - Целевой динамический меш, в который копируется меш.

### Возвращаемое значение

true, если динамический меш успешно скопирован в заданную цель; иначе false.
## void bind ( )

Привязывает данные динамического меша (буферы индексов и вершин) к стадии input assembler.
## void unbind ( )

Отвязывает данные динамического меша (буферы индексов и вершин).
## void flushVertex ( )

Сбрасывает (flush) буфер вершин и отправляет все данные на GPU. Этот метод вызывается автоматически, если длина буфера вершин меняется. Если вы изменяете содержимое буфера вершин, вам следует вызвать этот метод.
## void flushIndices ( )

Сбрасывает (flush) буфер индексов и отправляет все данные на GPU. Этот метод вызывается автоматически, если длина буфера индексов меняется. Если вы изменяете содержимое буфера индексов, вам следует вызвать этот метод.
## int renderSurface ( int mode )

Рендерит поверхность.
### Аргументы

- *int* **mode** - Режим рендеринга. Одно из значений [MODE](#MODE).

### Возвращаемое значение

Количество отрендеренных примитивов. Тип примитива определяется режимом рендеринга.
## int renderInstancedSurface ( int mode , int num )

Рендерит заданное количество инстансов поверхности.
### Аргументы

- *int* **mode** - Режим рендеринга. Одно из значений [MODE](#MODE).
- *int* **num** - Количество рендерящихся инстансов.

### Возвращаемое значение

Количество отрендеренных примитивов. Тип примитива определяется режимом рендеринга.
## int renderSurface ( int mode , int base , int begin , int end )

Рендерит поверхность, заданную начальным и конечным индексами.
### Аргументы

- *int* **mode** - Режим рендеринга. Одно из значений [MODE](#MODE).
- *int* **base** - Значение, добавляемое к каждому индексу перед чтением вершины из буфера вершин.
- *int* **begin** - Первый индекс поверхности, считываемый GPU из буфера индексов.
- *int* **end** - Последний индекс поверхности, считываемый GPU из буфера индексов.

### Возвращаемое значение

Количество отрендеренных примитивов. Тип примитива определяется режимом рендеринга.
## int renderInstancedSurface ( int mode , int base , int begin , int end , int num )

Рендерит заданное количество инстансов поверхности, заданной начальным и конечным индексами.
### Аргументы

- *int* **mode** - Режим рендеринга. Одно из значений [MODE](#MODE).
- *int* **base** - Значение, добавляемое к каждому индексу перед чтением вершины из буфера вершин.
- *int* **begin** - Первый индекс поверхности, считываемый GPU из буфера индексов.
- *int* **end** - Последний индекс поверхности, считываемый GPU из буфера индексов.
- *int* **num** - Количество рендерящихся инстансов.

### Возвращаемое значение

Количество отрендеренных примитивов. Тип примитива определяется режимом рендеринга.
## int render ( int mode , int flush )

Рендерит динамический меш с заданными флагами и режимом.
### Аргументы

- *int* **mode** - Режим рендеринга. Одно из значений [MODE](#MODE).
- *int* **flush** - Флаг сброса (flush). Одна из переменных [USAGE_FLUSH_*](#USAGE_FLUSH_VERTEX).

### Возвращаемое значение

Количество отрендеренных треугольников.
## size_t getSystemMemoryUsage ( ) const

Возвращает текущий объём системной памяти, используемой динамическим мешем, в байтах.
### Возвращаемое значение

Объём системной памяти, используемой динамическим мешем, в байтах.
## size_t getVideoMemoryUsage ( ) const

Возвращает текущий объём видеопамяти, используемой динамическим мешем.
### Возвращаемое значение

Объём видеопамяти, используемой динамическим мешем, в байтах.
## void setVertexFormat ( const MeshDynamic::Attribute [] & attributes , int attributes_size )

Задаёт формат вершин, используемый динамическим мешем.
### Аргументы

- *const [MeshDynamic::Attribute](../../../api/library/rendering/class.meshdynamic_cpp.md#Attribute)[] &* **attributes** - Массив атрибутов, используемых для формата вершин, может содержать до 16 атрибутов на вершину. Нумерация начинается с **0**. Каждый атрибут состоит из:

  - Смещения вершины в байтах, зависящего от типа и размера вершины.
  - Типа вершины: одно из значений [TYPE_*](#TYPE)
  - Размера вершины: может быть **1,2,3,4** для типа *float*; **2,4** для типа *half*; **4** для типа *UChar* > **Notice:** При передаче в шейдер атрибут **0** всегда приходит с размером **4**, независимо от размера, заданного в методе. Все остальные атрибуты приходят с заданными размерами.
- *int* **attributes_size** - Количество элементов в массиве *attributes*.

## int getVertexSize ( ) const

Возвращает размер вершины динамического меша.
### Возвращаемое значение

Размер вершины.
## int getNumAttributes ( ) const

Возвращает количество атрибутов вершин динамического меша.
## void clearVertex ( )

Удаляет все вершины динамического меша.
## void allocateVertex ( int num )

Выделяет заданное количество вершин в буфере вершин. С помощью этой функции память можно выделить один раз, а не частями, что ускоряет создание.
### Аргументы

- *int* **num** - Количество вершин, для которых выделяется память.

## void removeVertex ( int num , int size )

Удаляет заданное количество элементов, начиная с заданного, из буфера вершин динамического меша.
### Аргументы

- *int* **num** - Номер первой удаляемой вершины.
- *int* **size** - Количество удаляемых вершин.

## void setNumVertex ( int num )

Задаёт общее количество вершин для динамического меша.
### Аргументы

- *int* **num** - Новое количество вершин.

## int getNumVertex ( ) const

Возвращает общее количество вершин для динамического меша.
## void addVertexArray ( const void * vertex , int num_vertex )

Добавляет набор новых элементов в буфер вершин динамического меша за один раз.
### Аргументы

- *const void ** **vertex** - Массив добавляемых вершин.
- *int* **num_vertex** - Количество добавляемых вершин.

## void setVertexArray ( const void * vertex , int num_vertex )

Заменяет текущий буфер вершин динамического меша заданным массивом вершин.
### Аргументы

- *const void ** **vertex** - Массив добавляемых вершин.
- *int* **num_vertex** - Количество добавляемых вершин.

## void addVertexHalf1 ( int attribute , float x )

Добавляет новую вершину с одной координатой half в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.

## void addVertexHalf2 ( int attribute , float x , float y )

Добавляет новую вершину с 2 координатами half в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.

## void addVertexHalf3 ( int attribute , float x , float y , float z )

Добавляет новую вершину с 3 координатами half в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.

## void addVertexHalf4 ( int attribute , float x , float y , float z , float w )

Добавляет новую вершину с 4 координатами half в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.
- *float* **w** - W координата вершины.

## void addVertexFloat ( int attribute , float* OUT_value , int value_size )

Добавляет новую вершину с координатами типа *float* в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float** **OUT_value** - Массив координат вершины типа *float* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void addVertexFloat1 ( int attribute , float x )

Добавляет новую вершину с одной координатой float в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.

## void addVertexFloat2 ( int attribute , float x , float y )

Добавляет новую вершину с 2 координатами float в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.

## void addVertexFloat3 ( int attribute , float x , float y , float z )

Добавляет новую вершину с 3 координатами float в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.

## void addVertexFloat4 ( int attribute , float x , float y , float z , float w )

Добавляет новую вершину с 4 координатами float в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.
- *float* **w** - W координата вершины.

## void addVertexUChar ( int attribute , uchar* OUT_value , int value_size )

Добавляет новую вершину с координатами типа *unsigned char* в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *uchar** **OUT_value** - Массив координат вершины типа *uchar* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void addVertexUChar1 ( int attribute , unsigned char x )

Добавляет новую вершину с одной координатой unsigned char в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.

## void addVertexUChar2 ( int attribute , unsigned char x , unsigned char y )

Добавляет новую вершину с 2 координатами unsigned char в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.

## void addVertexUChar3 ( int attribute , unsigned char x , unsigned char y , unsigned char z )

Добавляет новую вершину с 3 координатами unsigned char в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.
- *unsigned char* **z** - Z координата вершины.

## void addVertexUChar4 ( int attribute , unsigned char x , unsigned char y , unsigned char z , unsigned char w )

Добавляет новую вершину с 4 координатами unsigned char в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.
- *unsigned char* **z** - Z координата вершины.
- *unsigned char* **w** - W координата вершины.

## void addVertexUShort ( int attribute , ushort* OUT_value , int value_size )

Добавляет новую вершину с координатами типа *unsigned short* в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *ushort** **OUT_value** - Массив координат вершины типа *ushort* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void addVertexUShort1 ( int attribute , unsigned short x )

Добавляет новую вершину с одной координатой unsigned short в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.

## void addVertexUShort2 ( int attribute , unsigned short x , unsigned short y )

Добавляет новую вершину с 2 координатами unsigned short в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.

## void addVertexUShort3 ( int attribute , unsigned short x , unsigned short y , unsigned short z )

Добавляет новую вершину с 3 координатами unsigned short в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.
- *unsigned short* **z** - Z координата вершины.

## void addVertexUShort4 ( int attribute , unsigned short x , unsigned short y , unsigned short z , unsigned short w )

Добавляет новую вершину с 4 координатами unsigned short в динамический меш.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.
- *unsigned short* **z** - Z координата вершины.
- *unsigned short* **w** - W координата вершины.

## void setVertexHalf1 ( int attribute , float x )

Задаёт координаты типа half и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.

## void setVertexHalf2 ( int attribute , float x , float y )

Задаёт координаты типа half и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.

## void setVertexHalf3 ( int attribute , float x , float y , float z )

Задаёт координаты типа half и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.

## void setVertexHalf4 ( int attribute , float x , float y , float z , float w )

Задаёт координаты типа half и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.
- *float* **w** - W координата вершины.

## void setVertexFloat ( int attribute , float* OUT_value , int value_size )

Задаёт координаты типа *float* и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float** **OUT_value** - Массив координат типа *float* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void setVertexFloat1 ( int attribute , float x )

Задаёт координаты типа float и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.

## void setVertexFloat2 ( int attribute , float x , float y )

Задаёт координаты типа float и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.

## void setVertexFloat3 ( int attribute , float x , float y , float z )

Задаёт координаты типа float и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.

## void setVertexFloat4 ( int attribute , float x , float y , float z , float w )

Задаёт координаты типа float и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.
- *float* **w** - W координата вершины.

## void setVertexUChar ( int attribute , uchar* OUT_value , int value_size )

Задаёт координаты типа *uchar* и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *uchar** **OUT_value** - Массив координат типа *uchar* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void setVertexUChar1 ( int attribute , unsigned char x )

Задаёт координаты типа uchar и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.

## void setVertexUChar2 ( int attribute , unsigned char x , unsigned char y )

Задаёт координаты типа uchar и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.

## void setVertexUChar3 ( int attribute , unsigned char x , unsigned char y , unsigned char z )

Задаёт координаты типа uchar и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.
- *unsigned char* **z** - Z координата вершины.

## void setVertexUChar4 ( int attribute , unsigned char x , unsigned char y , unsigned char z , unsigned char w )

Задаёт координаты типа uchar и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.
- *unsigned char* **z** - Z координата вершины.
- *unsigned char* **w** - W координата вершины.

## void setVertexUShort ( int attribute , ushort* OUT_value , int value_size )

Задаёт координаты типа *ushort* и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *ushort** **OUT_value** - Массив координат типа *ushort* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void setVertexUShort1 ( int attribute , unsigned short x )

Задаёт координаты типа ushort и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.

## void setVertexUShort2 ( int attribute , unsigned short x , unsigned short y )

Задаёт координаты типа ushort и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.

## void setVertexUShort3 ( int attribute , unsigned short x , unsigned short y , unsigned short z )

Задаёт координаты типа ushort и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.
- *unsigned short* **z** - Z координата вершины.

## void setVertexUShort4 ( int attribute , unsigned short x , unsigned short y , unsigned short z , unsigned short w )

Задаёт координаты типа ushort и заданный атрибут для последней вершины в буфере вершин динамического меша.
### Аргументы

- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.
- *unsigned short* **z** - Z координата вершины.
- *unsigned short* **w** - W координата вершины.

## void setVertexHalf1 ( int vertex , int attribute , float x )

Задаёт координаты типа half и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.

## void setVertexHalf2 ( int vertex , int attribute , float x , float y )

Задаёт координаты типа half и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.

## void setVertexHalf3 ( int vertex , int attribute , float x , float y , float z )

Задаёт координаты типа half и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.

## void setVertexHalf4 ( int vertex , int attribute , float x , float y , float z , float w )

Задаёт координаты типа half и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.
- *float* **w** - W координата вершины.

## void setVertexFloat ( int vertex , int attribute , float* OUT_value , int value_size )

Задаёт координаты типа *float* и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float** **OUT_value** - Массив координат типа *float* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void setVertexFloat1 ( int vertex , int attribute , float x )

Задаёт координаты типа float и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.

## void setVertexFloat2 ( int vertex , int attribute , float x , float y )

Задаёт координаты типа float и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.

## void setVertexFloat3 ( int vertex , int attribute , float x , float y , float z )

Задаёт координаты типа float и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.

## void setVertexFloat4 ( int vertex , int attribute , float x , float y , float z , float w )

Задаёт координаты типа float и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *float* **x** - X координата вершины.
- *float* **y** - Y координата вершины.
- *float* **z** - Z координата вершины.
- *float* **w** - W координата вершины.

## void setVertexUChar ( int vertex , int attribute , uchar* OUT_value , int value_size )

Задаёт координаты типа *uchar* и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *uchar** **OUT_value** - Массив координат типа *uchar* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void setVertexUChar1 ( int vertex , int attribute , unsigned char x )

Задаёт координаты типа uchar и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.

## void setVertexUChar2 ( int vertex , int attribute , unsigned char x , unsigned char y )

Задаёт координаты типа uchar и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.

## void setVertexUChar3 ( int vertex , int attribute , unsigned char x , unsigned char y , unsigned char z )

Задаёт координаты типа uchar и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.
- *unsigned char* **z** - Z координата вершины.

## void setVertexUChar4 ( int vertex , int attribute , unsigned char x , unsigned char y , unsigned char z , unsigned char w )

Задаёт координаты типа uchar и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned char* **x** - X координата вершины.
- *unsigned char* **y** - Y координата вершины.
- *unsigned char* **z** - Z координата вершины.
- *unsigned char* **w** - W координата вершины.

## void setVertexUShort ( int vertex , int attribute , ushort* OUT_value , int value_size )

Задаёт координаты типа *ushort* и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *ushort** **OUT_value** - Массив координат типа *ushort* для задания. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **value_size** - Количество элементов в массиве *value*.

## void setVertexUShort1 ( int vertex , int attribute , unsigned short x )

Задаёт координаты типа ushort и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.

## void setVertexUShort2 ( int vertex , int attribute , unsigned short x , unsigned short y )

Задаёт координаты типа ushort и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.

## void setVertexUShort3 ( int vertex , int attribute , unsigned short x , unsigned short y , unsigned short z )

Задаёт координаты типа ushort и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.
- *unsigned short* **z** - Z координата вершины.

## void setVertexUShort4 ( int vertex , int attribute , unsigned short x , unsigned short y , unsigned short z , unsigned short w )

Задаёт координаты типа ushort и заданный атрибут для заданной вершины в буфере вершин динамического меша.
### Аргументы

- *int* **vertex** - Номер вершины.
- *int* **attribute** - Задаваемый атрибут.
- *unsigned short* **x** - X координата вершины.
- *unsigned short* **y** - Y координата вершины.
- *unsigned short* **z** - Z координата вершины.
- *unsigned short* **w** - W координата вершины.

## void clearIndices ( )

Удаляет все индексы динамического меша.
## void allocateIndices ( int num )

Выделяет заданное количество индексов вершин в буфере индексов. С помощью этой функции память можно выделить один раз, а не частями, что ускоряет создание.
### Аргументы

- *int* **num** - Количество индексов, для которых выделяется память.

## void removeIndices ( int num , int size )

Удаляет заданное количество индексов, начиная с заданного, из буфера индексов динамического меша.
### Аргументы

- *int* **num** - Номер первого удаляемого индекса.
- *int* **size** - Количество удаляемых индексов.

## void setNumIndices ( int num )

Задаёт общее количество индексов для динамического меша.
### Аргументы

- *int* **num** - Новое количество индексов.

## int getNumIndices ( ) const

Возвращает общее количество индексов для динамического меша.
### Возвращаемое значение

Количество индексов.
## void addIndex ( int index )

Добавляет новый индекс в буфер индексов динамического меша.
### Аргументы

- *int* **index** - Добавляемый индекс.

## void addIndexFast ( int index )

Добавляет новый индекс в буфер индексов динамического меша.
### Аргументы

- *int* **index** - Добавляемый индекс.

## void addIndices ( int i0 , int i1 )

Добавляет два новых индекса в буфер индексов динамического меша за один раз. Этот метод можно использовать для добавления индексов для линейных полос (line strips) одним вызовом функции.
### Аргументы

- *int* **i0** - Первый добавляемый индекс.
- *int* **i1** - Второй добавляемый индекс.

## void addIndices ( int i0 , int i1 , int i2 )

Добавляет три новых индекса в буфер индексов динамического меша за один раз. Этот метод можно использовать для добавления индексов для треугольника одним вызовом функции.
### Аргументы

- *int* **i0** - Первый добавляемый индекс.
- *int* **i1** - Второй добавляемый индекс.
- *int* **i2** - Третий добавляемый индекс.

## void addIndices ( int i0 , int i1 , int i2 , int i3 )

Добавляет четыре новых индекса в буфер индексов динамического меша за один раз. Этот метод можно использовать для добавления индексов для четырёхугольника одним вызовом функции.
### Аргументы

- *int* **i0** - Первый добавляемый индекс.
- *int* **i1** - Второй добавляемый индекс.
- *int* **i2** - Третий добавляемый индекс.
- *int* **i3** - Четвёртый добавляемый индекс.

## void addIndicesArray ( const int * indices , int indices_size )

Добавляет набор новых элементов в буфер индексов динамического меша за один раз.
### Аргументы

- *const int ** **indices** - Массив добавляемых индексов.
- *int* **indices_size** - Количество добавляемых индексов.

## void setIndicesArray ( const int * indices , int indices_size )

Заменяет текущий буфер индексов динамического меша заданным массивом индексов.
### Аргументы

- *const int ** **indices** - Массив задаваемых индексов.
- *int* **indices_size** - Количество задаваемых индексов.

## Vector <int> & getIndicesArray ( )

Возвращает буфер индексов динамического меша.
### Возвращаемое значение

Вектор, содержащий буфер индексов динамического меша.
## void addPoints ( int num_points )

Добавляет заданное количество точек в динамический меш.
### Аргументы

- *int* **num_points** - Количество добавляемых точек.

## void addLineStrip ( int num_vertex )

Добавляет линейную полосу (line strip) в динамический меш. Этот метод не добавляет вершины, вместо этого он выделяет индексы, для которых затем должны быть созданы вершины одним из методов [*addVertex*()*](#addVertexHalf1_int_float_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_vertex** - Количество вершин, составляющих полосу.

## void addTriangles ( int num_triangles )

Добавляет заданное количество треугольников в динамический меш.
### Аргументы

- *int* **num_triangles** - Количество добавляемых треугольников.

## void addTriangleFan ( int num_vertex )

Добавляет веер треугольников (triangle fan) в динамический меш. Этот метод не добавляет вершины, вместо этого он выделяет индексы, для которых затем должны быть созданы вершины одним из методов [*addVertex*()*](#addVertexHalf1_int_float_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_vertex** - Количество вершин, составляющих веер.

## void addTriangleStrip ( int num_vertex )

Добавляет полосу треугольников (triangle strip) в динамический меш. Этот метод не добавляет вершины, вместо этого он выделяет индексы, для которых затем должны быть созданы вершины одним из методов [*addVertex*()*](#addVertexHalf1_int_float_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_vertex** - Количество вершин, составляющих полосу.

## void addTriangleQuads ( int num_quads )

Добавляет заданное количество четырёхугольников в динамический меш. Этот метод не добавляет вершины, вместо этого он выделяет индексы, для которых затем должны быть созданы вершины одним из методов [*addVertex*()*](#addVertexHalf1_int_float_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_quads** - Количество добавляемых четырёхугольников.

## int saveState ( const Ptr < Stream > & stream ) const

Сохраняет текущее состояние динамического меша (вершины, индексы и т.д.) в заданный поток.
Для сохранения в поток требуется создать blob для сохранения. Для восстановления сохранённого состояния используется метод [restoreState()](#restoreState_Stream_int):


```cpp
// инициализируем меш и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
dynamicMesh->saveState(blob_state);

// меняем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
dynamicMesh->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который сохраняется состояние динамического меша.

### Возвращаемое значение

true, если текущее состояние динамического меша успешно сохранено; иначе false.
## int restoreState ( const Ptr < Stream > & stream )

Восстанавливает ранее сохранённое состояние динамического меша (вершины, индексы и т.д.) из заданного потока.
Для восстановления из потока требуется создать blob для сохранения и сохранить состояние с помощью метода [saveState()](#saveState_Stream_int):


```cpp
// инициализируем меш и задаём его состояние
//...//

// сохраняем состояние
BlobPtr blob_state = Blob::create();
dynamicMesh->saveState(blob_state);

// меняем состояние
//...//

// восстанавливаем состояние
blob_state->seekSet(0);				// возвращаем каретку в начало blob
dynamicMesh->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, из которого загружается ранее сохранённое состояние динамического меша.

### Возвращаемое значение

true, если ранее сохранённое состояние динамического меша успешно восстановлено; иначе false.
## Ptr < ResourceExternalMemory > getExternalMemoryVertexBuffer ( ) const

Возвращает указатель на буфер вершин ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
### Возвращаемое значение

Указатель на буфер вершин ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
## Ptr < ResourceExternalMemory > getExternalMemoryIndexBuffer ( ) const

Возвращает указатель на буфер индексов ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
### Возвращаемое значение

Указатель на буфер индексов ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
