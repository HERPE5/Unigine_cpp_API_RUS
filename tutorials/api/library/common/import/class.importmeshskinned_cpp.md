# Unigine::ImportMeshSkinned Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является промежуточным представлением скинового меша из исходного файла. В отличие от [ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md) (используемого для статической геометрии), он также хранит ссылку на [ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md) для деформации на основе суставов и путь к связанному файлу анимации. Во время импорта он преобразуется в ассет MeshSkinned.


## ImportMeshSkinned Class

### Методы класса

## void setData ( void * data )

Задаёт новые метаданные импортированного скинового меша.
### Аргументы

- *void ** **data** - Метаданные скинового меша.

## void * getData () const

Возвращает текущие метаданные импортированного скинового меша.
### Возвращаемое значение

Текущие метаданные скинового меша.
## void setName ( const char * name )

Задаёт новое имя скинового меша.
### Аргументы

- *const char ** **name** - Имя скинового меша.

## const char * getName () const

Возвращает текущее имя скинового меша.
### Возвращаемое значение

Текущее имя скинового меша.
## void setFilepath ( const char * filepath )

Задаёт новый путь к выходному файлу скинового меша.
### Аргументы

- *const char ** **filepath** - Путь к выходному файлу скинового меша.

## const char * getFilepath () const

Возвращает текущий путь к выходному файлу скинового меша.
### Возвращаемое значение

Текущий путь к выходному файлу скинового меша.
## void setAnimationFilepath ( const char * filepath )

Задаёт новый путь к выходному файлу анимации, связанному с этим скиновым мешем.
### Аргументы

- *const char ** **filepath** - Путь к выходному файлу анимации.

## const char * getAnimationFilepath () const

Возвращает текущий путь к выходному файлу анимации, связанному с этим скиновым мешем.
### Возвращаемое значение

Текущий путь к выходному файлу анимации.
## void setSkeleton ( const Ptr < ImportSkeleton >& skeleton )

Задаёт новый [import skeleton](../../../../api/library/common/import/class.importskeleton_cpp.md), назначенный скиновому мешу.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)>&* **skeleton** - Скелет, назначенный скиновому мешу.

## Ptr < ImportSkeleton > getSkeleton () const

Возвращает текущий [import skeleton](../../../../api/library/common/import/class.importskeleton_cpp.md), назначенный скиновому мешу.
### Возвращаемое значение

Текущий скелет, назначенный скиновому мешу.
---

## static ImportMeshSkinnedPtr create ( )

Конструктор. Создаёт пустой экземпляр *ImportMeshSkinned*.
## int getNumNodes ( ) const

Возвращает количество импортированных узлов, к которым скиновый меш присоединён в качестве атрибута.
### Возвращаемое значение

Количество узлов, к которым скиновый меш присоединён в качестве атрибута.
## void addNode ( const Ptr < ImportNode > & node )

Добавляет новый узел в список импортированных узлов, к которым скиновый меш присоединён в качестве атрибута.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Новый импортированный узел для добавления.

## bool removeNode ( const Ptr < ImportNode > & node )

Удаляет указанный импортированный узел из списка импортированных узлов, к которым скиновый меш присоединён в качестве атрибута.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел для удаления.

### Возвращаемое значение

true, если указанный импортированный узел был успешно удалён из списка; иначе false.
## Ptr < ImportNode > getNode ( int index ) const

Возвращает импортированный узел с указанным индексом из списка импортированных узлов, к которым скиновый меш присоединён в качестве атрибута.
### Аргументы

- *int* **index** - Индекс узла в списке.

### Возвращаемое значение

Импортированный узел с указанным индексом (если он существует).
## int getNumGeometries ( ) const

Возвращает количество элементов в списке геометрии скинового меша (набор элементов *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*, составляющих геометрию скинового меша).
### Возвращаемое значение

Количество элементов в списке геометрии скинового меша.
## Ptr < ImportGeometry > addGeometry ( )

Добавляет новый элемент в список геометрии скинового меша и возвращает соответствующий экземпляр *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*.
### Возвращаемое значение

Новый добавленный элемент геометрии.
## void copyGeometriesFrom ( const Ptr < ImportMeshSkinned > & other )

Копирует все элементы геометрии из указанного исходного скинового меша и добавляет их в список геометрии скинового меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **other** - Исходный скиновый меш.

## void moveGeometriesFrom ( const Ptr < ImportMeshSkinned > & other )

Перемещает все элементы геометрии из указанного исходного скинового меша и добавляет их в список геометрии скинового меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **other** - Исходный скиновый меш.

## Ptr < ImportGeometry > getGeometry ( int index ) const

Возвращает элемент геометрии скинового меша по его индексу. Геометрия скинового меша может состоять из нескольких элементов *[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)*.
### Аргументы

- *int* **index** - Индекс элемента геометрии.

### Возвращаемое значение

Элемент геометрии с указанным индексом.
## void clearGeometries ( )

Очищает список геометрии скинового меша.
