# Unigine::ImportAnimation Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является промежуточным представлением клипа анимации из исходного файла. Он хранит временной диапазон анимации и содержит ссылку на связанный [skeleton](../../../../api/library/common/import/class.importskeleton_cpp.md). Во время импорта он используется вместе с [ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md) для получения [MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md).


## ImportAnimation Class

### Методы класса

## void setData ( void * data )

Задаёт новые метаданные анимации.
### Аргументы

- *void ** **data** - Метаданные анимации.

## void * getData () const

Возвращает текущие метаданные анимации.
### Возвращаемое значение

Текущие метаданные анимации.
## void setFilepath ( const char * filepath )

Задаёт новый путь к выходному файлу анимации.
### Аргументы

- *const char ** **filepath** - Путь к выходному файлу анимации.

## const char * getFilepath () const

Возвращает текущий путь к выходному файлу анимации.
### Возвращаемое значение

Текущий путь к выходному файлу анимации.
## void setName ( const char * name )

Задаёт новое имя анимации.
### Аргументы

- *const char ** **name** - Имя анимации.

## const char * getName () const

Возвращает текущее имя анимации.
### Возвращаемое значение

Текущее имя анимации.
## void setMaxTime ( float time )

Задаёт новое время окончания анимации.
### Аргументы

- *float* **time** - Время окончания анимации, в секундах.

## float getMaxTime () const

Возвращает текущее время окончания анимации.
### Возвращаемое значение

Текущее время окончания анимации, в секундах.
## void setMinTime ( float time )

Задаёт новое время начала анимации.
### Аргументы

- *float* **time** - Время начала анимации, в секундах.

## float getMinTime () const

Возвращает текущее время начала анимации.
### Возвращаемое значение

Текущее время начала анимации, в секундах.
## void setSkeleton ( const Ptr < ImportSkeleton >& skeleton )

Задаёт новый [import skeleton](../../../../api/library/common/import/class.importskeleton_cpp.md), связанный с анимацией.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)>&* **skeleton** - Скелет, связанный с анимацией.

## Ptr < ImportSkeleton > getSkeleton () const

Возвращает текущий [import skeleton](../../../../api/library/common/import/class.importskeleton_cpp.md), связанный с анимацией.
### Возвращаемое значение

Текущий скелет, связанный с анимацией.
---

## static ImportAnimationPtr create ( )

Конструктор. Создаёт пустой экземпляр *ImportAnimation*.
