# Unigine::ImportLight Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является промежуточным представлением источника света из исходного файла. Связанный [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md) определяет его положение и ориентацию в сцене. Во время импорта он преобразуется в [Light](../../../../api/library/lights/class.light_cpp.md) UNIGINE с помощью [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md).


## ImportLight Class

### Методы класса

## void setData ( void * data )

Задаёт новые метаданные источника света.
### Аргументы

- *void ** **data** - Метаданные источника света.

## void * getData () const

Возвращает текущие метаданные источника света.
### Возвращаемое значение

Текущие метаданные источника света.
## void setNode ( const Ptr < ImportNode >& node )

Задаёт новый узел сцены, к которому источник света присоединён в качестве атрибута.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)>&* **node** - Узел сцены.

## Ptr < ImportNode > getNode () const

Возвращает текущий узел сцены, к которому источник света присоединён в качестве атрибута.
### Возвращаемое значение

Текущий узел сцены.
---

## static ImportLightPtr create ( )

Конструктор. Создаёт пустой экземпляр *ImportLight*.
