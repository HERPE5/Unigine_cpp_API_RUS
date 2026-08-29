# Unigine::ImportNode Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является промежуточным представлением узла сцены из исходного файла (FBX, glTF и др.). Каждый узел имеет матрицу преобразования и может иметь дочерние узлы, образующие иерархию. В зависимости от его роли в исходном файле узел может ссылаться на [ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md), [ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md), [ImportLight](../../../../api/library/common/import/class.importlight_cpp.md) или [ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md). Узлы также используются как суставы в [ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md). Во время импорта иерархия узлов преобразуется в [Nodes](../../../../api/library/nodes/class.node_cpp.md) UNIGINE с помощью [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md).


## ImportNode Class

### Методы класса

## void setData ( void * data )

Задаёт новые метаданные импортированного узла.
### Аргументы

- *void ** **data** - Метаданные узла.

## void * getData () const

Возвращает текущие метаданные импортированного узла.
### Возвращаемое значение

Текущие метаданные узла.
## void setFilepath ( const char * filepath )

Задаёт новый путь к выходному файлу узла.
### Аргументы

- *const char ** **filepath** - Выходной файл узла.

## const char * getFilepath () const

Возвращает текущий путь к выходному файлу узла.
### Возвращаемое значение

Текущий выходной файл узла.
## void setCamera ( const Ptr < ImportCamera >& camera )

Задаёт новый атрибут узла камеры.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)>&* **camera** - Атрибут Camera: экземпляр класса *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*, если атрибут камеры назначен узлу; иначе nullptr.

## Ptr < ImportCamera > getCamera () const

Возвращает текущий атрибут узла камеры.
### Возвращаемое значение

Текущий атрибут Camera: экземпляр класса *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*, если атрибут камеры назначен узлу; иначе nullptr.
## void setLight ( const Ptr < ImportLight >& light )

Задаёт новый атрибут узла источника света.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)>&* **light** - Атрибут light: экземпляр класса *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*, если атрибут источника света назначен узлу; иначе nullptr.

## Ptr < ImportLight > getLight () const

Возвращает текущий атрибут узла источника света.
### Возвращаемое значение

Текущий атрибут light: экземпляр класса *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*, если атрибут источника света назначен узлу; иначе nullptr.
## void setMesh ( const Ptr < ImportMesh >& mesh )

Задаёт новый атрибут узла меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)>&* **mesh** - Атрибут mesh: экземпляр класса *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*, если атрибут меша назначен узлу; иначе nullptr.

## Ptr < ImportMesh > getMesh () const

Возвращает текущий атрибут узла меша.
### Возвращаемое значение

Текущий атрибут mesh: экземпляр класса *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*, если атрибут меша назначен узлу; иначе nullptr.
## void setMeshSkinned ( const Ptr < ImportMeshSkinned >& skinned )

Задаёт новый атрибут узла скинового меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)>&* **skinned** - Атрибут скинового меша: экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*, если атрибут скинового меша назначен узлу; иначе nullptr.

## Ptr < ImportMeshSkinned > getMeshSkinned () const

Возвращает текущий атрибут узла скинового меша.
### Возвращаемое значение

Текущий атрибут скинового меша: экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*, если атрибут скинового меша назначен узлу; иначе nullptr.
## void setName ( const char * name )

Задаёт новое имя импортированного узла сцены.
### Аргументы

- *const char ** **name** - Имя узла сцены.

## const char * getName () const

Возвращает текущее имя импортированного узла сцены.
### Возвращаемое значение

Текущее имя узла сцены.
## void setParent ( const Ptr < ImportNode >& parent )

Задаёт новый родительский узел импортированного узла сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)>&* **parent** - Родительский узел импортированного узла сцены.

## Ptr < ImportNode > getParent () const

Возвращает текущий родительский узел импортированного узла сцены.
### Возвращаемое значение

Текущий родительский узел импортированного узла сцены.
## void setTransform ( const Math:: dmat4 & transform )

Задаёт новую матрицу преобразования импортированного узла сцены.
### Аргументы

- *const  Math::[dmat4](../../../../api/library/math/class.dmat4_cpp.md)&* **transform** - Матрица преобразования узла.

## Math:: dmat4 getTransform () const

Возвращает текущую матрицу преобразования импортированного узла сцены.
### Возвращаемое значение

Текущая матрица преобразования узла.
---

## static ImportNodePtr create ( )

Конструктор. Создаёт пустой экземпляр *ImportNode*.
## void addChild ( const Ptr < ImportNode > & node )

Добавляет указанный узел в качестве дочернего к импортированному узлу сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел для добавления в качестве дочернего к импортированному узлу.

## bool removeChild ( const Ptr < ImportNode > & node )

Удаляет указанный узел из списка дочерних узлов импортированного узла сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел для удаления из списка дочерних узлов.

## Ptr < ImportNode > getChild ( int index ) const

Возвращает дочерний узел импортированного узла с указанным индексом.
### Аргументы

- *int* **index** - Индекс дочернего узла в диапазоне от 0 до ([total number of children](#getNumChildren_int) - 1).

### Возвращаемое значение

Дочерний узел импортированного узла с указанным индексом.
## int getNumChildren ( ) const

Возвращает количество дочерних узлов импортированного узла.
### Возвращаемое значение

Количество дочерних узлов.
