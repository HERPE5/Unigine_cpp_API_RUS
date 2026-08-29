# ObjectMeshDynamic Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для процедурного создания динамических мешей (то есть треугольников), линий или точек и их изменения во время выполнения. Также можно загрузить существующий меш как динамический для его последующего изменения.


#### See Also


- Article on [ObjectMeshDynamic class usage examples](../../../code/usage/dynamic_meshes/index_cpp.md)
- C++ sample
- C# sample

  -
  -
  -
  -
  -
  -


## ObjectMeshDynamic Class

### Методы класса

## void setNumIndices ( int indices )

Задаёт новое количество индексов вершин.
### Аргументы

- *int* **indices** - Количество индексов вершин.

## int getNumIndices () const

Возвращает текущее количество индексов вершин.
### Возвращаемое значение

Текущее количество индексов вершин.
## void setNumVertex ( int vertex )

Задаёт новое количество вершин меша.
### Аргументы

- *int* **vertex** - Количество вершин меша.

## int getNumVertex () const

Возвращает текущее количество вершин меша.
### Возвращаемое значение

Текущее количество вершин меша.
## void setMeshName ( const char * name )

Задаёт новое имя меша.
### Аргументы

- *const char ** **name** - Имя меша.

## const char * getMeshName () const

Возвращает текущее имя меша.
### Возвращаемое значение

Текущее имя меша.
## void setUpdateDistanceLimit ( float limit )

Задаёт новое расстояние от камеры, в пределах которого объект должен обновляться. Значение по умолчанию: бесконечность.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Аргументы

- *float* **limit** - Расстояние от камеры, в пределах которого объект должен обновляться.

## float getUpdateDistanceLimit () const

Возвращает текущее расстояние от камеры, в пределах которого объект должен обновляться. Значение по умолчанию: бесконечность.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Возвращаемое значение

Текущее расстояние от камеры, в пределах которого объект должен обновляться.
## void setFPSInvisible ( int fpsinvisible )

Задаёт новое значение частоты обновления, когда объект вообще не отрисовывается. Значение по умолчанию: 0 fps.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Аргументы

- *int* **fpsinvisible** - Значение частоты обновления, когда объект вообще не отрисовывается.

## int getFPSInvisible () const

Возвращает текущее значение частоты обновления, когда объект вообще не отрисовывается. Значение по умолчанию: 0 fps.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Возвращаемое значение

Текущее значение частоты обновления, когда объект вообще не отрисовывается.
## void setFPSVisibleShadow ( int shadow )

Задаёт новое значение частоты обновления, когда отрисовывается только тень объекта. Значение по умолчанию: 30 fps.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Аргументы

- *int* **shadow** - Значение частоты обновления, когда отрисовывается только тень объекта.

## int getFPSVisibleShadow () const

Возвращает текущее значение частоты обновления, когда отрисовывается только тень объекта. Значение по умолчанию: 30 fps.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Возвращаемое значение

Текущее значение частоты обновления, когда отрисовывается только тень объекта.
## void setFPSVisibleCamera ( int camera )

Задаёт новое значение частоты обновления, когда объект отрисовывается в области просмотра.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Аргументы

- *int* **camera** - Значение частоты обновления, когда объект отрисовывается в области просмотра.

## int getFPSVisibleCamera () const

Возвращает текущее значение частоты обновления, когда объект отрисовывается в области просмотра.
> **Notice:** Этот метод эффективен, когда объекту назначено [BODY_ROPE](../../../api/library/physics/class.body_cpp.md#BODY_ROPE), [BODY_CLOTH](../../../api/library/physics/class.body_cpp.md#BODY_CLOTH) или [BODY_WATER](../../../api/library/physics/class.body_cpp.md#BODY_WATER).


### Возвращаемое значение

Текущее значение частоты обновления, когда объект отрисовывается в области просмотра.
## bool isUniqueMesh () const

Возвращает текущее значение, указывающее, является ли меш, используемый объектом, уникальным (отличным от меша, по умолчанию используемого совместно с другими динамическими объектами меша в мире).
### Возвращаемое значение

**true**, если объект использует уникальный меш; иначе **false**.
## bool isUsageShared () const

Возвращает текущее значение, указывающее, включён ли для динамического объекта меша флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED).
### Возвращаемое значение

**true**, если флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) для динамического объекта меша включён; иначе **false**.
---

## static ObjectMeshDynamicPtr create ( const Ptr < Mesh > & mesh , int flags = 0 )

Конструктор ObjectMeshDynamic.
> **Notice:** Поверхность по умолчанию с именем "`dynamic`" создаётся автоматически, что позволяет добавлять геометрию к объекту сразу после создания без явного указания индекса поверхности.
>
>
> Чтобы добавить больше поверхностей, используйте *[addSurface()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#addSurface_cstr_void)*. Первый вызов просто присваивает пользовательское имя существующей внутренней поверхности и не изменяет общее количество поверхностей (любая геометрия, созданная до вызова, если таковая имеется, сохраняется). Последующие вызовы создают дополнительные поверхности по мере необходимости.


> **Notice:** Флаг [USAGE_IMMUTABLE_VERTEX](#USAGE_IMMUTABLE_VERTEX) нельзя использовать вместе с флагом [USAGE_DYNAMIC_VERTEX](#USAGE_DYNAMIC_VERTEX).
>
>
> Флаг [USAGE_IMMUTABLE_INDICES](#USAGE_IMMUTABLE_INDICES) нельзя использовать вместе с флагом [USAGE_DYNAMIC_INDICES](#USAGE_DYNAMIC_INDICES).
>
>
> [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) можно использовать только вместе с [USAGE_IMMUTABLE_ALL](#USAGE_IMMUTABLE_ALL).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Умный указатель на [Mesh](../../../api/library/rendering/class.mesh_cpp.md).
- *int* **flags** - Динамический флаг: один из [USAGE_DYNAMIC_*](#USAGE_DYNAMIC_ALL) или [USAGE_IMMUTABLE_*](#USAGE_IMMUTABLE_ALL).

## static ObjectMeshDynamicPtr create ( int flags = 0 )

Конструктор ObjectMeshDynamic.
> **Notice:** Поверхность по умолчанию с именем "`dynamic`" создаётся автоматически, что позволяет добавлять геометрию к объекту сразу после создания без явного указания индекса поверхности.
>
>
> Чтобы добавить больше поверхностей, используйте *[addSurface()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#addSurface_cstr_void)*. Первый вызов просто присваивает пользовательское имя существующей внутренней поверхности и не изменяет общее количество поверхностей (любая геометрия, созданная до вызова, если таковая имеется, сохраняется). Последующие вызовы создают дополнительные поверхности по мере необходимости.


> **Notice:** Флаг [USAGE_IMMUTABLE_VERTEX](#USAGE_IMMUTABLE_VERTEX) нельзя использовать вместе с флагом [USAGE_DYNAMIC_VERTEX](#USAGE_DYNAMIC_VERTEX).
>
>
> Флаг [USAGE_IMMUTABLE_INDICES](#USAGE_IMMUTABLE_INDICES) нельзя использовать вместе с флагом [USAGE_DYNAMIC_INDICES](#USAGE_DYNAMIC_INDICES).
>
>
> [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) можно использовать только вместе с [USAGE_IMMUTABLE_ALL](#USAGE_IMMUTABLE_ALL).


### Аргументы

- *int* **flags** - Динамический флаг: один из [USAGE_DYNAMIC_*](#USAGE_DYNAMIC_ALL) или [USAGE_IMMUTABLE_*](#USAGE_IMMUTABLE_ALL).

## static ObjectMeshDynamicPtr create ( const char * path , int flags = 0 )

Конструктор ObjectMeshDynamic.
> **Notice:** Поверхность по умолчанию с именем "`dynamic`" создаётся автоматически, что позволяет добавлять геометрию к объекту сразу после создания без явного указания индекса поверхности.
>
>
> Чтобы добавить больше поверхностей, используйте *[addSurface()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#addSurface_cstr_void)*. Первый вызов просто присваивает пользовательское имя существующей внутренней поверхности и не изменяет общее количество поверхностей (любая геометрия, созданная до вызова, если таковая имеется, сохраняется). Последующие вызовы создают дополнительные поверхности по мере необходимости.


> **Notice:** Флаг [USAGE_IMMUTABLE_VERTEX](#USAGE_IMMUTABLE_VERTEX) нельзя использовать вместе с флагом [USAGE_DYNAMIC_VERTEX](#USAGE_DYNAMIC_VERTEX).
>
>
> Флаг [USAGE_IMMUTABLE_INDICES](#USAGE_IMMUTABLE_INDICES) нельзя использовать вместе с флагом [USAGE_DYNAMIC_INDICES](#USAGE_DYNAMIC_INDICES).
>
>
> [USAGE_MISC_SHARED](#USAGE_MISC_SHARED) можно использовать только вместе с [USAGE_IMMUTABLE_ALL](#USAGE_IMMUTABLE_ALL).


### Аргументы

- *const char ** **path** - Путь к файлу меша.
- *int* **flags** - Динамический флаг: один из [USAGE_DYNAMIC_*](#USAGE_DYNAMIC_ALL) или [USAGE_IMMUTABLE_*](#USAGE_IMMUTABLE_ALL).

## void setBoundBox ( const Math:: BoundBox & bb )

Задаёт ограничивающий объём заданного размера для указанной поверхности динамического меша.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий объём.

## void setBoundBox ( const Math:: BoundBox & bb , int surface )

Задаёт ограничивающий объём заданного размера для указанной поверхности динамического меша.
### Аргументы

- *const  Math::[BoundBox](../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий объём.
- *int* **surface** - Номер поверхности в диапазоне от 0 до общего количества поверхностей динамического меша.

## void setColor ( int num , const Math:: vec4 & color )

Обновляет цвет указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет.

## Math:: vec4 getColor ( int num ) const

Возвращает цвет указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.

### Возвращаемое значение

Цвет.
## void setIndex ( int num , int index )

Обновляет индекс в буфере индексов (заменяет индекс с заданным номером указанным индексом вершины).
### Аргументы

- *int* **num** - Номер индекса в диапазоне от 0 до общего количества индексов в буфере индексов.
- *int* **index** - Индекс вершины, который нужно задать в буфере индексов.

## int getIndex ( int num ) const

Возвращает индекс вершины по номеру индекса.
### Аргументы

- *int* **num** - Номер индекса в диапазоне от 0 до общего количества индексов в буфере индексов.

### Возвращаемое значение

Индекс вершины в буфере индексов.
## void setIndicesArray ( int * OUT_indices , int indices_size )

Обновляет массив индексов.
### Аргументы

- *int ** **OUT_indices** - Исходный массив, используемый для обновления индексов. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **indices_size** - Размер массива индексов.

## int setMesh ( const Ptr < Mesh > & mesh )

Позволяет выполнить повторную инициализацию ObjectMeshDynamic: копирует заданный меш в текущий динамический меш. Например, вы можете скопировать один меш в другой следующим образом:
```cpp
// создаём экземпляры ObjectMeshDynamic
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create();
ObjectMeshDynamicPtr dynamicMesh_2 = ObjectMeshDynamic::create();

// создаём экземпляр Mesh
MeshPtr firstMesh = Mesh::create();

// получаем меш ObjectMeshDynamic и копируем его в экземпляр класса Mesh
dynamicMesh->getMesh(firstMesh);

// помещаем меш firstMesh в экземпляр dynamicMesh_2
dynamicMesh_2->setMesh(firstMesh);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Умный указатель на меш.

### Возвращаемое значение

**1**, если меш успешно скопирован; иначе **0**.
## int getMesh ( const Ptr < Mesh > & mesh ) const

Копирует текущий динамический меш в полученный меш. Например, вы можете получить геометрию динамического меша, а затем изменить её:
```cpp
// динамический меш, из которого будет получена геометрия
MeshPtr mesh_0 = Mesh::create("box.mesh");
ObjectMeshDynamicPtr dynamicMesh = ObjectMeshDynamic::create(mesh_0);
// создаём новый меш
MeshPtr mesh_1 = Mesh::create();
// копируем геометрию в экземпляр Mesh
if(dynamicMesh->getMesh(mesh_1)) {
	// выполняем какие-то действия с полученным мешем
} else {
	Log::error("Не удалось скопировать меш\n");
}

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Умный указатель на меш.

### Возвращаемое значение

**1**, если меш успешно скопирован; иначе **0**.
## Math:: vec3 getNormal ( int num ) const

Возвращает координаты вектора нормали указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.

### Возвращаемое значение

Вектор нормали.
## void setSurfaceBegin ( int begin , int surface )

Задаёт начальный индекс для указанной поверхности динамического объекта меша.
### Аргументы

- *int* **begin** - Индекс, который нужно задать в качестве начального для поверхности.
- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей меша.

## int getSurfaceBegin ( int surface ) const

Возвращает начальный индекс указанной поверхности меша.
### Аргументы

- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей меша.

### Возвращаемое значение

Начальный индекс поверхности.
## void setSurfaceEnd ( int end , int surface )

Задаёт конечный индекс для указанной поверхности динамического объекта меша.
### Аргументы

- *int* **end** - Индекс, который нужно задать в качестве конечного для поверхности.
- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей меша.

## int getSurfaceEnd ( int surface ) const

Возвращает конечный индекс указанной поверхности меша.
### Аргументы

- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей меша.

### Возвращаемое значение

Конечный индекс поверхности.
## void setSurfaceName ( const char * name , int surface )

Задаёт имя для указанной поверхности.
> **Notice:** Имя будет задано, только если указанная поверхность была добавлена методом *[addSurface()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#addSurface_cstr_void)*.


### Аргументы

- *const char ** **name** - Имя поверхности.
- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей меша.

## void setTangent ( int num , const Math:: quat & tangent )

Обновляет координаты касательного вектора указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.
- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **tangent** - Координаты касательного вектора.

## Math:: quat getTangent ( int num ) const

Возвращает координаты касательного вектора указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.

### Возвращаемое значение

Касательный вектор.
## void setTexCoord ( int num , const Math:: vec4 & texcoord )

Обновляет текстурные координаты указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **texcoord** - Новые пары координат для обоих текстурных каналов.

## Math:: vec4 getTexCoord ( int num ) const

Возвращает текстурные координаты указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.

### Возвращаемое значение

Пары координат для обоих текстурных каналов.
## void setVertex ( int num , const Math:: vec3 & xyz )

Обновляет координаты указанной вершины.
### Аргументы

- *int* **num** - Номер вершины.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **xyz** - Новые координаты вершины в системе координат меша.

## Math:: vec3 getVertex ( int num ) const

Возвращает координаты указанной вершины.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества вершин меша.

### Возвращаемое значение

Координаты вершины в системе координат меша.
## void setVertexArray ( ObjectMeshDynamic::Vertex* OUT_vertex , int vertex_size )

Обновляет массив вершин динамического меша.
### Аргументы

- *[ObjectMeshDynamic::Vertex*](../../../api/library/objects/class.objectmeshdynamic_cpp.md#Vertex*)* **OUT_vertex** - Исходный массив, используемый для обновления массива вершин динамического меша. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **vertex_size** - Размер массива вершин.

## const ObjectMeshDynamic::Vertex * getVertexArray ( ) const

Возвращает массив вершин динамического меша.
### Возвращаемое значение

Указатель на массив вершин.
## bool isFlushed ( ) const

Возвращает значение, указывающее, были ли данные вершин меша сброшены (операция создания/загрузки) в видеопамять.
### Возвращаемое значение

true, если данные вершин меша были сброшены (операция создания/загрузки) в видеопамять; иначе false.
## void addColor ( const Math:: vec4 & color )

Добавляет цвет с заданными координатами к последней добавленной вершине.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет.

## void addIndex ( int index )

Добавляет индекс в буфер индексов.
### Аргументы

- *int* **index** - Индекс, который нужно добавить.

## void addIndicesArray ( int* OUT_indices , int indices_size )

Добавляет массив индексов.
### Аргументы

- *int** **OUT_indices** - Массив индексов, который нужно добавить. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **indices_size** - Размер массива индексов.

## void addSurface ( const char * name )

Добавляет все последние перечисленные и неприсвоенные вершины и треугольники к новой поверхности с указанным именем.
> **Notice:** Для удобства *[ObjectMeshDynamic::create()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#ObjectMeshDynamic_constPtrMesh_int)* инициализирует объект одной внутренней поверхностью с именем "`dynamic`". Первый вызов *[addSurface()](../../../api/library/objects/class.objectmeshdynamic_cpp.md#addSurface_cstr_void)* просто присваивает этой поверхности пользовательское имя и не изменяет общее количество поверхностей (любая геометрия, созданная до вызова, если таковая имеется, сохраняется). Последующие вызовы создают дополнительные поверхности по мере необходимости.


### Аргументы

- *const char ** **name** - Имя новой поверхности.

## void addTangent ( const Math:: quat & tangent )

Добавляет касательный вектор с заданными координатами к последней добавленной вершине.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **tangent** - Координаты касательного вектора.

## void addTexCoord ( const Math:: vec4 & texcoord )

Добавляет текстурные координаты к последней добавленной вершине.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **texcoord** - Пары координат для обоих текстурных каналов.

## void addTriangleFan ( int num_vertex )

Добавляет веер треугольников (triangle fan) к мешу. Этот метод не добавляет вершины, а выделяет индексы, для которых затем должны быть созданы вершины функцией [addVertex()](#addVertex_vec3_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_vertex** - Количество вершин, составляющих веер.

## void addTriangleQuads ( int num_quads )

Добавляет заданное количество четырёхугольников к мешу. Этот метод не добавляет вершины, а выделяет индексы, для которых затем должны быть созданы вершины функцией [addVertex()](#addVertex_vec3_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_quads** - Количество четырёхугольников.

## void addTriangles ( int num_triangles )

Добавляет заданное количество треугольников к мешу. Этот метод не добавляет вершины, а выделяет индексы, для которых затем должны быть созданы вершины функцией [addVertex()](#addVertex_vec3_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_triangles** - Количество треугольников.

## void addTriangleStrip ( int num_vertex )

Добавляет полосу треугольников (triangle strip) к мешу. Этот метод не добавляет вершины, а выделяет индексы, для которых затем должны быть созданы вершины функцией [addVertex()](#addVertex_vec3_void). Индексы будут указывать на вершины, начиная с текущей последней вершины в буфере вершин.
### Аргументы

- *int* **num_vertex** - Количество вершин, составляющих полосу.

## void addVertex ( const Math:: vec3 & xyz )

Добавляет вершину с заданными координатами к мешу.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **xyz** - Координаты вершины в системе координат меша.

## void addVertexArray ( Vertex* OUT_vertex , int vertex_size )

Добавляет массив вершин к динамическому мешу.
### Аргументы

- *Vertex** **OUT_vertex** - Массив вершин, который нужно добавить. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.
- *int* **vertex_size** - Размер массива вершин.

## void allocateIndices ( int num )

Выделяет заданное количество индексов вершин в буфере индексов. С помощью этой функции память может быть выделена один раз, а не частями, что ускоряет создание.
### Аргументы

- *int* **num** - Количество индексов вершин, которые будут храниться в буфере.

## void allocateVertex ( int num )

Выделяет заданное количество вершин в буфере вершин. С помощью этой функции память может быть выделена один раз, а не частями, что ускоряет создание.
### Аргументы

- *int* **num** - Количество вершин, которое нужно выделить.

## void clearIndices ( )

Очищает все индексы вершин меша.
## void clearSurfaces ( )

Очищает все настройки поверхностей.
## void clearVertex ( )

Очищает все настройки вершин меша.
## void flushIndices ( )

Сбрасывает буфер индексов и отправляет все данные на GPU. Этот метод вызывается автоматически, если изменяется длина буфера индексов. Если вы изменяете содержимое буфера индексов, необходимо вызывать этот метод.
## void flushVertex ( )

Сбрасывает буфер вершин и отправляет все данные на GPU. Этот метод вызывается автоматически, если изменяется длина буфера вершин. Если вы изменяете содержимое буфера вершин, необходимо вызывать этот метод.
## bool loadMesh ( const char * path )

Загружает меш для текущего меша из файла. Эта функция не изменяет имя меша.
### Аргументы

- *const char ** **path** - Имя файла меша.

### Возвращаемое значение

true, если меш загружен успешно; иначе false.
## void removeIndices ( int num , int size )

Удаляет заданное количество индексов, начиная с указанного индекса.
### Аргументы

- *int* **num** - Номер индекса.
- *int* **size** - Количество индексов, которые нужно удалить.

## void removeSurface ( int surface )

Удаляет поверхность с указанным индексом.
### Аргументы

- *int* **surface** - Индекс поверхности.

## void removeSurfaces ( const char * name )

Удаляет поверхности с указанным именем.
### Аргументы

- *const char ** **name** - Имя поверхности.

## void removeVertex ( int num , int size , int indices )

Удаляет заданное количество вершин, начиная с указанной вершины. Чтобы исправить буфер индексов после удаления вершин, передайте true в качестве 3-го аргумента.
### Аргументы

- *int* **num** - Номер вершины.
- *int* **size** - Количество вершин, которые нужно удалить.
- *int* **indices** - 1 для исправления буфера индексов после удаления вершин; иначе 0.

## bool saveMesh ( const char * path )

Сохраняет динамический меш в формате `.mesh` или `.anim`.
### Аргументы

- *const char ** **path** - Имя файла меша.

### Возвращаемое значение

true, если меш успешно сохранён; иначе false.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Object](../../../api/library/objects/class.object_cpp.md).
## bool updateBounds ( )

Вычисляет ограничивающий объём и ограничивающую сферу для текущего меша.
### Возвращаемое значение

true, если границы успешно вычислены; иначе false.
## bool updateIndices ( )

Обновляет буферы вершин и индексов, удаляя дублирующиеся вершины и переупорядочивая индексы созданного меша для оптимизации и ускорения рендеринга.
### Возвращаемое значение

true, если индексы успешно обновлены; иначе false.
## void updateSurfaceBegin ( int surface )

Синхронизирует начальный индекс поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности в диапазоне от 0 до общего количества поверхностей меша.

## void updateSurfaceEnd ( int surface )

Синхронизирует конечный индекс поверхности.
### Аргументы

- *int* **surface** - Номер целевой поверхности.

## bool updateTangents ( )

Обновляет касательные векторы вершин меша.
### Возвращаемое значение

true, если касательные векторы успешно обновлены; иначе false.
## void putUniqueMesh ( )

Делает меш, используемый объектом, уникальным (отличным от меша, по умолчанию используемого совместно с другими объектами Dynamic Mesh в мире).
## Ptr < ResourceExternalMemory > getExternalMemoryVertexBuffer ( ) const

Возвращает указатель на буфер вершин ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
### Возвращаемое значение

Указатель на буфер вершин ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
## Ptr < ResourceExternalMemory > getExternalMemoryIndexBuffer ( ) const

Возвращает указатель на буфер индексов ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
### Возвращаемое значение

Указатель на буфер индексов ресурса в видеопамяти. Если для ресурса не включён флаг [USAGE_MISC_SHARED](#USAGE_MISC_SHARED), этот метод возвращает nullptr.
