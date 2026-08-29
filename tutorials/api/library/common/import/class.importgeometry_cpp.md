# Unigine::ImportGeometry Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс представляет элемент геометрии в составе [ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md) или [ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md). Меш может содержать несколько геометрий, каждая со своей матрицей преобразования и набором элементов [ImportSurface](../../../../api/library/common/import/class.importsurface_cpp.md), определяющих отдельные отрисовываемые поверхности.


## ImportGeometry Class

### Методы класса

## void setBoundBox ( const Math:: WorldBoundBox & box )

Задаёт новый ограничивающий прямоугольник элемента геометрии.
### Аргументы

- *const  Math::[WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md)&* **box** - Ограничивающий прямоугольник элемента геометрии.

## Math:: WorldBoundBox getBoundBox () const

Возвращает текущий ограничивающий прямоугольник элемента геометрии.
### Возвращаемое значение

Текущий ограничивающий прямоугольник элемента геометрии.
## void setData ( void * data )

Задаёт новые метаданные импортированного элемента геометрии.
### Аргументы

- *void ** **data** - Метаданные элемента геометрии.

## void * getData () const

Возвращает текущие метаданные импортированного элемента геометрии.
### Возвращаемое значение

Текущие метаданные элемента геометрии.
## void setTransform ( const Math:: dmat4 & transform )

Задаёт новую матрицу преобразования импортированного элемента геометрии.
### Аргументы

- *const  Math::[dmat4](../../../../api/library/math/class.dmat4_cpp.md)&* **transform** - Матрица преобразования элемента геометрии.

## Math:: dmat4 getTransform () const

Возвращает текущую матрицу преобразования импортированного элемента геометрии.
### Возвращаемое значение

Текущая матрица преобразования элемента геометрии.
---

## void copyFrom ( const Ptr < ImportGeometry > & o )

Копирует данные из указанного исходного элемента геометрии.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)> &* **o** - Исходный элемент геометрии.

## Ptr < ImportSurface > addSurface ( )

Добавляет новую поверхность в список поверхностей элемента геометрии и возвращает соответствующий экземпляр *[ImportSurface](../../../../api/library/common/import/class.importsurface_cpp.md)*.
### Возвращаемое значение

Новая добавленная поверхность.
## void copySurfacesFrom ( const Ptr < ImportGeometry > & other )

Копирует все поверхности из указанного исходного элемента геометрии.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)> &* **other** - Исходный элемент геометрии.

## void moveSurfacesFrom ( const Ptr < ImportGeometry > & other )

Перемещает все поверхности из указанного исходного элемента геометрии.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportGeometry](../../../../api/library/common/import/class.importgeometry_cpp.md)> &* **other** - Исходный элемент геометрии.

## Ptr < ImportSurface > getSurface ( int index ) const

Возвращает поверхность элемента геометрии по её индексу в списке.
### Аргументы

- *int* **index** - Индекс поверхности в диапазоне от 0 до ([total number of surfaces](#getNumSurfaces_int) - 1).

### Возвращаемое значение

Импортированная поверхность с указанным индексом.
## int getNumSurfaces ( ) const

Возвращает количество поверхностей в списке. Список поверхностей представлен набором структур *[ImportSurface](../../../../api/library/common/import/class.importsurface_cpp.md)*.
### Возвращаемое значение

Количество поверхностей в импортированном элементе геометрии.
## void clearSurfaces ( )

Очищает список поверхностей элемента геометрии.
