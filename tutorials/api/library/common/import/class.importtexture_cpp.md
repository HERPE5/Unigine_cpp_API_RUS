# Unigine::ImportTexture Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является промежуточным представлением текстуры, на которую есть ссылка в исходном файле. Он хранит путь к файлу текстуры, исходный путь из исходного ассета и имя пресета обработки. Во время импорта [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md) сохраняет текстуру в выходной каталог.


## ImportTexture Class

### Методы класса

## void setData ( void * data )

Задаёт новые метаданные импортированной текстуры.
### Аргументы

- *void ** **data** - Метаданные текстуры.

## void * getData () const

Возвращает текущие метаданные импортированной текстуры.
### Возвращаемое значение

Текущие метаданные текстуры.
## void setFilepath ( const char * filepath )

Задаёт новый путь к выходному файлу текстуры.
### Аргументы

- *const char ** **filepath** - Путь к выходному файлу текстуры.

## const char * getFilepath () const

Возвращает текущий путь к выходному файлу текстуры.
### Возвращаемое значение

Текущий путь к выходному файлу текстуры.
## void setOriginalFilepath ( const char * filepath )

Задаёт новый путь к исходному файлу текстуры.
### Аргументы

- *const char ** **filepath** - Путь к исходному файлу текстуры.

## const char * getOriginalFilepath () const

Возвращает текущий путь к исходному файлу текстуры.
### Возвращаемое значение

Текущий путь к исходному файлу текстуры.
## void setPreset ( const char * preset )

Задаёт новый [texture preset](../../../../editor2/assets_workflow/texture_import.md#texture_preset), используемый для импортированной текстуры.
### Аргументы

- *const char ** **preset** - Используемый пресет текстуры.

## const char * getPreset () const

Возвращает текущий [texture preset](../../../../editor2/assets_workflow/texture_import.md#texture_preset), используемый для импортированной текстуры.
### Возвращаемое значение

Текущий используемый пресет текстуры.
---

## static ImportTexturePtr create ( )

Конструктор. Создаёт пустой экземпляр *ImportTexture*.
