# Unigine::Export Class (CPP)

**Header:** #include <UnigineExport.h>


Это класс менеджера экспорта. Он используется для создания [exporters](../../../../api/library/common/export/class.exporter_cpp.md) и управления ими.


Вы можете динамически управлять набором доступных экспортёров, [adding](#registerExporter_const_char_ptr_const_Vectortmplargs_ref_void) их в реестр или [removing](#unregisterExporter_const_char_ptr_bool) из него.


Также можно получить [list of all currently supported file extensions](#getSupportedExtensions_Vectortmplret).


## Export Class

### Методы класса

---

## Export ( )

Конструктор. Создаёт экспортёр с настройками по умолчанию.
## Export * get ( )

Возвращает указатель на менеджер Export.
### Возвращаемое значение

Экземпляр менеджера Export.
## void registerExporter ( const char * type_name , const Vector < String >& extensions )

Регистрирует новый экспортёр с указанным именем для заданного списка расширений файлов.
### Аргументы

- *const char ** **type_name** - Имя типа экспортёра.
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../../api/library/common/class.string_cpp.md)>&* **extensions** - Список расширений файлов, для которых должен использоваться указанный экспортёр.

## bool unregisterExporter ( const char* type_name )

Отменяет регистрацию указанного типа экспортёра.
### Аргументы

- *const char** **type_name** - Имя типа экспортёра.

## Exporter * createExporter ( const char* type_name ) const

Создаёт новый [exporter](../../../../api/library/common/export/class.exporter_cpp.md) указанного типа.
> **Notice:** Указанное имя типа экспортёра должно быть предварительно [registered](#registerExporter_const_char_ptr_const_Vectortmplargs_ref_void).


### Аргументы

- *const char** **type_name** - Имя типа экспортёра.

### Возвращаемое значение

Указатель на новый созданный [exporter](../../../../api/library/common/export/class.exporter_cpp.md) указанного типа, если он был успешно создан; иначе **nullptr**.
## Exporter * createExporterByFileName ( const char* file_name ) const

Создаёт экспортёр для выходного файла с указанным именем на основе его расширения, если такой экспортёр был предварительно зарегистрирован.
### Аргументы

- *const char** **file_name** - Имя выходного файла, содержащего данные для экспорта.

### Возвращаемое значение

Указатель на [exporter](../../../../api/library/common/export/class.exporter_cpp.md), если он был успешно создан для файла с указанным именем; иначе **nullptr**.
## bool isSupportedExporterType ( const char* type_name ) const

Возвращает значение, указывающее, поддерживается ли указанный тип экспортёра.
### Аргументы

- *const char** **type_name** - Строка с завершающим нулевым символом, содержащая проверяемый тип экспортёра.

### Возвращаемое значение

true, если указанный тип экспортёра поддерживается; иначе false.
## Vector < String > & getExporterTypes ( ) const

Возвращает список всех типов [exporters](../../../../api/library/common/export/class.exporter_cpp.md), зарегистрированных менеджером Export.
### Возвращаемое значение

Список всех типов экспортёров, зарегистрированных менеджером Export, в виде вектора строк.
## void getExporterTypes ( Vector < String > & types ) const

Возвращает список всех типов [exporters](../../../../api/library/common/export/class.exporter_cpp.md), зарегистрированных менеджером Export, и помещает его в указанный вектор.
### Аргументы

- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../../api/library/common/class.string_cpp.md)> &* **types** - Вектор для помещения списка всех зарегистрированных типов экспортёров.

## bool isSupportedExtension ( const char* extension ) const

Возвращает значение, указывающее, поддерживается ли экспортёром указанное расширение файла.
### Аргументы

- *const char** **extension** - Строка с завершающим нулевым символом, содержащая проверяемое расширение файла.

### Возвращаемое значение

true, если указанное расширение файла поддерживается экспортёром; иначе false.
## Vector < String > & getSupportedExtensions ( ) const

Возвращает список всех поддерживаемых расширений файлов в виде вектора строк.
### Возвращаемое значение

Список всех поддерживаемых расширений в виде вектора строк.
## void getSupportedExtensions ( Vector < String > & extensions ) const

Возвращает список всех поддерживаемых расширений файлов и помещает его в указанный вектор.
### Аргументы

- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../../api/library/common/class.string_cpp.md)> &* **extensions** - Вектор для помещения списка всех поддерживаемых расширений.

## Vector < String > & getSupportedExtensionsByType ( const char* type_name ) const

Возвращает список всех поддерживаемых расширений файлов для указанного типа экспортёра в виде вектора строк.
### Аргументы

- *const char** **type_name** - Имя типа экспортёра.

### Возвращаемое значение

Список всех поддерживаемых расширений в виде вектора строк.
## void getSupportedExtensionsByType ( const char* type_name , Vector < String > & extensions ) const

Возвращает список всех поддерживаемых расширений файлов для указанного типа экспортёра и помещает его в указанный вектор.
### Аргументы

- *const char** **type_name** - Имя типа экспортёра.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../../api/library/common/class.string_cpp.md)> &* **extensions** - Вектор для помещения списка всех поддерживаемых расширений.

## String getExporterTypeByExtension ( const char* extension ) const

Возвращает тип экспортёра для указанного расширения.
### Аргументы

- *const char** **extension** - Строка с завершающим нулевым символом, содержащая расширение файла.

### Возвращаемое значение

Тип экспортёра для указанного расширения, если он существует, в виде строки; иначе — пустая строка.
## bool doExport ( const NodePtr& root_node , const char* output_filepath ) const

Создаёт [exporter](../../../../api/library/common/export/class.exporter_cpp.md) и затем экспортирует узел в указанный выходной файл.
### Аргументы

- *const NodePtr&* **root_node** - Корневой узел иерархии для экспорта.
- *const char** **output_filepath** - Выходной путь для сохранения сгенерированных файлов с экспортированными данными.

### Возвращаемое значение

true, если файл успешно экспортирован; иначе false.
