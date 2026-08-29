# Unigine::ImportMesh Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является промежуточным представлением статического меша из исходного файла. Меш организован как набор элементов [ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md), каждый из которых содержит элементы [ImportSurface](../../../../api/library/common/import/class.importsurface_cpp.md) с назначением материалов и настройками рендеринга. Во время импорта он преобразуется в [Mesh](../../../../api/library/rendering/class.mesh_cpp.md) UNIGINE с помощью [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md). Для скиновых мешей с поддержкой скелета см. [ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md).


## ImportMesh Class

### Методы класса

## void setData ( void * data )

Задаёт новые метаданные импортированного меша.
### Аргументы

- *void ** **data** - Метаданные меша.

## void * getData () const

Возвращает текущие метаданные импортированного меша.
### Возвращаемое значение

Текущие метаданные меша.
## void setName ( const char * name )

Задаёт новое имя меша.
### Аргументы

- *const char ** **name** - Имя меша.

## const char * getName () const

Возвращает текущее имя меша.
### Возвращаемое значение

Текущее имя меша.
## void setFilepath ( const char * filepath )

Задаёт новый путь к выходному файлу меша.
### Аргументы

- *const char ** **filepath** - Путь к выходному файлу меша.

## const char * getFilepath () const

Возвращает текущий путь к выходному файлу меша.
### Возвращаемое значение

Текущий путь к выходному файлу меша.
---

## static ImportMeshPtr create ( )

Конструктор. Создаёт пустой экземпляр *ImportMesh*.
## int getNumNodes ( ) const

Возвращает количество импортированных узлов, к которым меш присоединён в качестве атрибута.
### Возвращаемое значение

Количество узлов, к которым меш присоединён в качестве атрибута.
## void addNode ( const Ptr < ImportNode > & node )

Добавляет новый узел в список импортированных узлов, к которым меш присоединён в качестве атрибута.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Новый импортированный узел для добавления.

## bool removeNode ( const Ptr < ImportNode > & node )

Удаляет указанный импортированный узел из списка импортированных узлов, к которым меш присоединён в качестве атрибута.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел для удаления.

### Возвращаемое значение

true, если указанный импортированный узел был успешно удалён из списка; иначе false.
## Ptr < ImportNode > getNode ( int index ) const

Возвращает импортированный узел с указанным индексом из списка импортированных узлов, к которым меш присоединён в качестве атрибута.
### Аргументы

- *int* **index** - Индекс узла в списке.

### Возвращаемое значение

Импортированный узел с указанным индексом (если он существует).
## int getNumGeometries ( ) const

Возвращает количество элементов в списке геометрии меша (набор элементов *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*, составляющих геометрию меша).
### Возвращаемое значение

Количество элементов в списке геометрии меша.
## Ptr < ImportGeometry > addGeometry ( )

Добавляет новый элемент в список геометрии меша и возвращает соответствующий экземпляр *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*.
### Возвращаемое значение

Новый добавленный элемент геометрии.
## void copyGeometriesFrom ( const Ptr < ImportMesh > & other )

Копирует все элементы геометрии из указанного исходного меша и добавляет их в список геометрии меша (набор элементов *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*, составляющих геометрию меша).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **other** - Исходный меш.

## void moveGeometriesFrom ( const Ptr < ImportMesh > & other )

Перемещает все элементы геометрии из указанного исходного меша и добавляет их в список геометрии меша (набор элементов *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*, составляющих геометрию меша).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **other** - Исходный меш.

## Ptr < ImportGeometry > getGeometry ( int index ) const

Возвращает элемент геометрии меша по его индексу. Геометрия меша может состоять из нескольких элементов *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*.
### Аргументы

- *int* **index** - Индекс элемента геометрии.

### Возвращаемое значение

Элемент геометрии с указанным индексом.
## void clearGeometries ( )

Очищает список геометрии меша (набор элементов *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*, составляющих геометрию меша).
