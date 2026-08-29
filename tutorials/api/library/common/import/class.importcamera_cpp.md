# Unigine::ImportCamera Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является промежуточным представлением камеры из исходного файла. Связанный [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md) определяет её положение и ориентацию в сцене. Во время импорта она преобразуется в [Player](../../../../api/library/players/class.player_cpp.md) UNIGINE с помощью [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md).


## ImportCamera Class

### Методы класса

## void setData ( void * data )

Задаёт новые метаданные импортированной камеры.
### Аргументы

- *void ** **data** - Метаданные камеры.

## void * getData () const

Возвращает текущие метаданные импортированной камеры.
### Возвращаемое значение

Текущие метаданные камеры.
## void setNode ( const Ptr < ImportNode >& node )

Задаёт новый узел сцены, к которому камера присоединена в качестве атрибута.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)>&* **node** - Узел сцены.

## Ptr < ImportNode > getNode () const

Возвращает текущий узел сцены, к которому камера присоединена в качестве атрибута.
### Возвращаемое значение

Текущий узел сцены.
---

## static ImportCameraPtr create ( )

Конструктор. Создаёт пустой экземпляр *ImportCamera*.
