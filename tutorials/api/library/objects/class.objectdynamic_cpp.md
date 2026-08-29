# ObjectDynamic Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Класс ObjectDynamic позволяет создать динамический объект, который может отрисовываться с использованием любого типа геометрии (формат вершин объекта можно изменять). Класс поддерживает инстансинг, а также режимы отрисовки точками/линиями/треугольниками. Классу ObjectDynamic требуется пользовательский шейдер для рендеринга, встроенные шейдеры недоступны.


## ObjectDynamic Class

### Перечисления

## MODE

| Name | Description |
|---|---|
| **MODE_POINTS** = 0 | Mode to render the points. |
| **MODE_LINES** = 1 | Mode to render the lines. |
| **MODE_TRIANGLES** = 2 | Mode to render the triangles. |
| **MODE_TRIANGLE_PATCHES** = 3 | Mode to render the triangle patches. |
| **MODE_QUAD_PATCHES** = 4 | Mode to render the quad patches. |

### Методы класса

---

## static ObjectDynamicPtr create ( int flags = 0 )

Конструктор. Создаёт новый динамический объект. По умолчанию флаги не используются.
### Аргументы

- *int* **flags** - Динамические флаги: один из флагов [*OBJECT_DYNAMIC_**](#DYNAMIC_ALL) или [*OBJECT_IMMUTABLE_**](#IMMUTABLE_ALL).

## const ObjectDynamic::Attribute * getAttributes ( ) const

Возвращает массив атрибутов вершин.
### Возвращаемое значение

Массив атрибутов вершин.
## void setBoundBox ( const Math:: BoundBox & bb )

Задаёт ограничивающий объём заданного размера для указанной поверхности динамического объекта.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий объём.

## void setBoundBox ( const Math:: BoundBox & bb , int surface )

Задаёт ограничивающий объём заданного размера для указанной поверхности динамического объекта.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий объём.
- *int* **surface** - Номер поверхности в диапазоне от 0 до общего количества поверхностей динамического меша.

## void setIndex ( int num , int index )

Обновляет индекс в буфере индексов (заменяет индекс с заданным номером указанным индексом вершины).
### Аргументы

- *int* **num** - Номер индекса в буфере индексов.
- *int* **index** - Индекс вершины, который нужно задать в буфере индексов.

## int getIndex ( int num ) const

Возвращает индекс вершины по номеру индекса.
### Аргументы

- *int* **num** - Номер индекса.

### Возвращаемое значение

Индекс вершины в буфере индексов.
## void setIndicesArray ( const int * indices , int indices_size )

Обновляет заданный массив индексов.
> **Notice:** Чтобы применить изменения, после обновления массива индексов нужно вызвать метод [*flushIndices()*](#flushIndices_void).


### Аргументы

- *const int ** **indices** - Массив индексов, который нужно задать.
- *int* **indices_size** - Количество индексов, которые нужно задать.

## void setInstancing ( bool instancing )

Активирует аппаратную технику [instancing](../../../editor2/instancing_nodes/index.md).
### Аргументы

- *bool* **instancing** - Флаг инстансинга. **1** для включения аппаратного [instancing](../../../editor2/instancing_nodes/index.md), **0** для отключения.

## bool getInstancing ( ) const

Возвращает значение, указывающее, включён ли флаг аппаратного [instancing](../../../editor2/instancing_nodes/index.md).
### Возвращаемое значение

**1**, если флаг аппаратного [instancing](#setInstancing_int_void) включён; иначе **0**.
## int getNumAttributes ( ) const

Возвращает количество атрибутов вершин.
### Возвращаемое значение

Количество атрибутов вершин.
## void setNumIndices ( int indices )

Задаёт количество индексов вершин.
### Аргументы

- *int* **indices** - Количество индексов.

## int getNumIndices ( ) const

Возвращает количество индексов вершин, используемых объектом.
### Возвращаемое значение

Количество индексов.
## void setNumVertex ( int vertex )

Задаёт количество вершин меша.
### Аргументы

- *int* **vertex** - Количество вершин меша.

## int getNumVertex ( ) const

Возвращает количество вершин, составляющих объект.
### Возвращаемое значение

Количество вершин.
## void setMaterialNodeType ( Node::TYPE type )

Задаёт тип узла, который будет использоваться рендерером для определения того, какие материалы могут применяться к объекту.
> **Notice:** Поскольку ObjectDynamic является пользовательским объектом, тип узла для корректной обработки объекта рендерером должен определяться пользователем. Задание неподходящего типа узла может привести к сбоям системы.


### Аргументы

- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **type** - Идентификатор типа узла. Один из [node type identifiers](../../../api/library/nodes/class.node_cpp.md#DECAL_BEGIN).

## Node::TYPE getMaterialNodeType ( ) const

Возвращает тип узла, который используется рендерером для определения того, какие материалы могут применяться к объекту.
> **Notice:** Поскольку ObjectDynamic является пользовательским объектом, тип узла для корректной обработки объекта рендерером должен определяться пользователем. Задание неподходящего типа узла может привести к сбоям системы.


### Возвращаемое значение

Идентификатор типа узла. Один из [node type identifiers](../../../api/library/nodes/class.node_cpp.md#DECAL_BEGIN).
## void setParameterBool ( const char * name , bool value )

Задаёт булев параметр шейдера с указанным значением.
### Аргументы

- *const char ** **name** - Имя параметра шейдера.
- *bool* **value** - Значение параметра.

## void setParameterFloat ( const char * name , const float * value , int value_size )

Задаёт числовой (float) параметр шейдера с указанным значением.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const float ** **value** - Значение параметра.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setParameterFloatArray ( const char * name , const float * value , int value_size , int num )

Задаёт массив указанного количества числовых (float) параметров шейдера.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const float ** **value** - Значение параметра.
- *int* **value_size** - Количество значений, которые нужно задать.
- *int* **num** - Количество параметров шейдера.

## void setParameterInt ( const char * name , const int * value , int value_size )

Задаёт целочисленный параметр шейдера с указанным значением.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const int ** **value** - Значение параметра.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setSurfaceBegin ( int begin , int surface )

Задаёт начальный индекс для указанной поверхности объекта.
### Аргументы

- *int* **begin** - Индекс, который нужно задать в качестве начального для поверхности.
- *int* **surface** - Номер целевой поверхности.

## int getSurfaceBegin ( int surface ) const

Возвращает начальный индекс указанной поверхности объекта.
### Аргументы

- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей.

### Возвращаемое значение

Начальный индекс.
## void setSurfaceEnd ( int end , int surface )

Задаёт конечный индекс для указанной поверхности объекта.
### Аргументы

- *int* **end** - Индекс, который нужно задать в качестве конечного для поверхности.
- *int* **surface** - Номер целевой поверхности.

## int getSurfaceEnd ( int surface ) const

Возвращает конечный индекс указанной поверхности объекта.
### Аргументы

- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей.

### Возвращаемое значение

Конечный индекс.
## void setSurfaceMode ( ObjectDynamic::MODE mode , int surface )

Задаёт примитивы, которыми отрисовывается поверхность объекта: треугольники (по умолчанию), линии или точки.
### Аргументы

- *[ObjectDynamic::MODE](../../../api/library/objects/class.objectdynamic_cpp.md#MODE)* **mode** - Режим отрисовки поверхности.
- *int* **surface** - Номер целевой поверхности.

## ObjectDynamic::MODE getSurfaceMode ( int surface ) const

Возвращает примитивы, используемые для отрисовки поверхности объекта: треугольники (по умолчанию), линии или точки.
### Аргументы

- *int* **surface** - Номер целевой поверхности.

### Возвращаемое значение

Режим отрисовки поверхности:
- OBJECT_DYNAMIC_MODE_POINTS = 0
- OBJECT_DYNAMIC_MODE_LINES
- OBJECT_DYNAMIC_MODE_TRIANGLES


## void setSurfaceName ( const char * name , int surface )

Задаёт имя для указанной поверхности.
> **Notice:** Имя будет задано, только если указанная поверхность была добавлена методом *[addSurface()](#addSurface_cstr_void)*.


### Аргументы

- *const char ** **name** - Имя поверхности.
- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей.

## void setVertex ( int num , const void * vertex )

Обновляет вершину в буфере вершин.
### Аргументы

- *int* **num** - Номер вершины.
- *const void ** **vertex** - Указатель на вершину.

## void setVertexArray ( const void * vertex , int num_vertex )

Обновляет массив вершин.
### Аргументы

- *const void ** **vertex** - Указатель на массив вершин.
- *int* **num_vertex** - Количество вершин.

## void setVertexFloat ( int attribute , const float * value , int value_size )

Обновляет последнюю добавленную вершину до вершины типа float с заданными параметрами.
### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const float ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setVertexFloat ( int vertex , int attribute , const float * value , int value_size )

Обновляет указанную вершину до вершины типа float с заданными параметрами.
### Аргументы

- *int* **vertex** - Индекс вершины.
- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const float ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setVertexFormat ( const ObjectDynamic::Attribute * attributes , int attributes_size )

Задаёт количество атрибутов вершин.
Пример задания 4 различных атрибутов вершин:


```cpp
const ObjectDynamic::Attribute attributes[] = {
	{ 0, ObjectDynamic::TYPE_FLOAT, 3 },
	{ 8, ObjectDynamic::TYPE_HALF, 4 },
	{ 16, ObjectDynamic::TYPE_HALF, 4 },
	{ 24, ObjectDynamic::TYPE_HALF, 4 }
};

// задаём формат вершин
dynamic->setVertexFormat(attributes, 4);

```


### Аргументы

- *const [ObjectDynamic::Attribute](../../../api/library/objects/class.objectdynamic_cpp.md#Attribute) ** **attributes** - Количество атрибутов вершины, может быть до 16 атрибутов на одну вершину. Нумерация начинается с **0**. Каждый атрибут состоит из:

  - Смещения вершины в байтах, зависящего от типа и размера вершины.
  - Типа вершины: [TYPE_FLOAT](#TYPE_FLOAT), [TYPE_HALF](#TYPE_HALF), [TYPE_UCHAR](#TYPE_UCHAR)
  - Размера вершины: может быть **1,2,3,4** для типа *float*; **2,4** для типа *half*; **4** для типа *UChar* > **Notice:** При передаче в шейдер атрибут **0** всегда имеет размер **4**, независимо от того, какой размер указан в методе. Все остальные атрибуты передаются с указанными размерами.
- *int* **attributes_size** - Количество атрибутов, которые нужно задать.

## void setVertexHalf ( int attribute , const float * value , int value_size )

Обновляет последнюю добавленную вершину до вершины типа half-float с заданными параметрами.
### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const float ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setVertexHalf ( int vertex , int attribute , const float * value , int value_size )

Обновляет последнюю добавленную вершину до вершины типа half-float с заданными параметрами.
### Аргументы

- *int* **vertex** - Индекс вершины.
- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const float ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## int getVertexSize ( ) const

Возвращает размер текущей вершины в байтах.
### Возвращаемое значение

Размер вершины.
## void setVertexUChar ( int attribute , const unsigned char * value , int value_size )

Обновляет последнюю добавленную вершину до вершины типа unsigned char с заданными параметрами.
### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const unsigned char ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setVertexUChar ( int vertex , int attribute , const unsigned char * value , int value_size )

Обновляет последнюю добавленную вершину до вершины типа unsigned char с заданными параметрами.
### Аргументы

- *int* **vertex** - Индекс вершины.
- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const unsigned char ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setVertexUShort ( int attribute , const unsigned short * value , int value_size )

Обновляет последнюю добавленную вершину до вершины типа unsigned short с заданными параметрами.
### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const unsigned short ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void setVertexUShort ( int vertex , int attribute , const unsigned short * value , int value_size )

Обновляет указанную вершину до вершины типа unsigned short с заданными параметрами.
### Аргументы

- *int* **vertex** - Индекс вершины.
- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const unsigned short ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void addIndex ( int index )

Добавляет индекс в буфер индексов.
### Аргументы

- *int* **index** - Индекс, который нужно добавить.

## void addIndicesArray ( const int * indices , int indices_size )

Добавляет массив указанного количества индексов.
### Аргументы

- *const int ** **indices** - Массив индексов.
- *int* **indices_size** - Количество индексов, которые нужно задать.

## void addLineStrip ( int num_vertex )

Добавляет полосу линий (line strip) к объекту.
> **Notice:** Этот метод не добавляет новые вершины, а выделяет их индексы. Вершины должны создаваться методами [addVertexFloat()](#addVertexFloat_int_float_int_void), [addVertexHalf()](#addVertexHalf_int_float_int_void) или [addVertexUChar()](#addVertexUChar_int_uchar_int_void) в соответствии с требуемым типом вершины.


### Аргументы

- *int* **num_vertex** - Количество вершин.

## void addPoints ( int num_points )

Добавляет точки к объекту.
> **Notice:** Этот метод не добавляет новые вершины, а выделяет их индексы. Вершины должны создаваться методами [addVertexFloat()](#addVertexFloat_int_float_int_void), [addVertexHalf()](#addVertexHalf_int_float_int_void) или [addVertexUChar()](#addVertexUChar_int_uchar_int_void) в соответствии с требуемым типом вершины.


### Аргументы

- *int* **num_points** - Количество точек.

## void addSurface ( const char * name )

Добавляет все последние перечисленные и неприсвоенные вершины и треугольники к новой поверхности с указанным именем.
### Аргументы

- *const char ** **name** - Имя новой поверхности.

## void addTriangleFan ( int num_vertex )

Добавляет веер треугольников (triangle fan) к объекту.
> **Notice:** Этот метод не добавляет новые вершины, а выделяет их индексы. Вершины должны создаваться методами [addVertexFloat()](#addVertexFloat_int_float_int_void), [addVertexHalf()](#addVertexHalf_int_float_int_void) или [addVertexUChar()](#addVertexUChar_int_uchar_int_void) в соответствии с требуемым типом вершины.


### Аргументы

- *int* **num_vertex** - Количество вершин, составляющих веер.

## void addTriangleQuads ( int num_quads )

Добавляет заданное количество четырёхугольников к мешу. Этот метод не добавляет вершины, а выделяет индексы, для которых затем должны быть созданы вершины функцией [addVertex()](#addVertex_void_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_quads** - Количество четырёхугольников.

## void addTriangles ( int num_triangles )

Добавляет заданное количество треугольников к объекту.
> **Notice:** Этот метод не добавляет новые вершины, а выделяет их индексы. Вершины должны создаваться методами [addVertexFloat()](#addVertexFloat_int_float_int_void), [addVertexHalf()](#addVertexHalf_int_float_int_void) или [addVertexUChar()](#addVertexUChar_int_uchar_int_void) в соответствии с требуемым типом вершины.


### Аргументы

- *int* **num_triangles** - Количество треугольников.

## void addTriangleStrip ( int num_vertex )

Добавляет полосу треугольников (triangle strip) к объекту.
> **Notice:** Этот метод не добавляет новые вершины, а выделяет их индексы. Вершины должны создаваться методами [addVertexFloat()](#addVertexFloat_int_float_int_void), [addVertexHalf()](#addVertexHalf_int_float_int_void) или [addVertexUChar()](#addVertexUChar_int_uchar_int_void) в соответствии с требуемым типом вершины.


### Аргументы

- *int* **num_vertex** - Количество вершин, составляющих полосу.

## void addVertex ( const void * vertex )

Добавляет вершину в буфер вершин.
### Аргументы

- *const void ** **vertex** - Указатель на вершину.

## void addVertexArray ( const void * vertex , int num_vertex )

Добавляет массив указанного количества вершин.
### Аргументы

- *const void ** **vertex** - Указатель на массив вершин.
- *int* **num_vertex** - Количество вершин.

## void addVertexFloat ( int attribute , const float * value , int value_size )

Добавляет к объекту вершину типа float с заданным атрибутом, координатами и размером.
> **Notice:** Перед добавлением вершины убедитесь, что все её атрибуты заданы методом [setVertexFormat()](#setVertexFormat_Attribute_int_void).


### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const float ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void addVertexHalf ( int attribute , const float * value , int value_size )

Добавляет к объекту вершину типа half-float с заданным атрибутом, координатами и размером.
> **Notice:** Перед добавлением вершины убедитесь, что все её атрибуты заданы методом [setVertexFormat()](#setVertexFormat_Attribute_int_void).


### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const float ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void addVertexUChar ( int attribute , const unsigned char * value , int value_size )

Добавляет к объекту вершину со значением типа unsigned char с заданным атрибутом, координатами и размером.
### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const unsigned char ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void addVertexUShort ( int attribute , const unsigned short * value , int value_size )

Добавляет к объекту вершину со значением типа unsigned short с заданным атрибутом, координатами и размером.
### Аргументы

- *int* **attribute** - Номер атрибута, заданный в методе [setVertexFormat()](#setVertexFormat_Attribute_int_void).
- *const unsigned short ** **value** - Координаты вершины.
- *int* **value_size** - Количество значений, которые нужно задать.

## void allocateIndices ( int num )

Выделяет буфер индексов для заданного количества индексов, которые будут использоваться объектом. С помощью этой функции память может быть выделена один раз, а не частями, что ускоряет создание.
### Аргументы

- *int* **num** - Количество индексов, которые будут храниться в буфере.

## void allocateVertex ( int num )

Выделяет буфер вершин для заданного количества вершин, которые будут использоваться объектом. С помощью этой функции память может быть выделена один раз, а не частями, что ускоряет создание.
### Аргументы

- *int* **num** - Количество вершин, которые будут храниться в буфере.

## void clearIndices ( )

Очищает все индексы вершин объекта.
## void clearSurfaces ( )

Очищает все настройки поверхностей.
## void clearVertex ( )

Очищает все текущие настройки вершин.
## void flushIndices ( )

Сбрасывает буфер индексов и отправляет все данные на GPU. Если вы изменяете содержимое буфера индексов, необходимо вызывать этот метод.
## void flushVertex ( )

Сбрасывает буфер вершин и отправляет все данные на GPU. Этот метод вызывается автоматически, если изменяется длина буфера вершин. Если вы изменяете содержимое буфера вершин, необходимо вызывать этот метод.
## void removeIndices ( int num , int size )

Удаляет заданное количество индексов, начиная с указанного индекса.
### Аргументы

- *int* **num** - Номер индекса в буфере индексов.
- *int* **size** - Количество индексов, которые нужно удалить.

## void removeVertex ( int num , int size , int indices )

Удаляет заданное количество вершин, начиная с указанной вершины. Чтобы исправить буфер индексов после удаления вершин, передайте 1 в качестве 3-го аргумента.
### Аргументы

- *int* **num** - Номер вершины в буфере вершин.
- *int* **size** - Количество вершин, которые нужно удалить.
- *int* **indices** - 1 для исправления буфера индексов после удаления вершин; иначе 0.

## static int type ( )

Возвращает тип объекта.
### Возвращаемое значение

Идентификатор типа [Object Dynamic](../../../api/library/nodes/class.node_cpp.md#OBJECT_DYNAMIC).
## void updateSurfaceBegin ( int surface )

Синхронизирует начальный индекс поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей.

## void updateSurfaceEnd ( int surface )

Синхронизирует конечный индекс поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей.
