# Unigine::Import Class (CPP)

**Header:** #include <UnigineImport.h>

> **Notice:** Этот класс является одиночкой (singleton).


Это класс менеджера импорта. Он используется для создания [importers](../../../../api/library/common/import/class.importer_cpp.md) и [processors](../../../../api/library/common/import/class.importprocessor_cpp.md) и управления ими, а также для непосредственного [import](#doImport_cstr_cstr_String) файлов в неродных форматах, если импортёр для таких файлов был предварительно [registered](#registerImporter_ImporterID_cstr_ImporterCreationFunction_ImporterDeletionFunction_vptr_int_vptr).


Вы можете динамически управлять набором доступных импортёров, [adding](#registerImporter_ImporterID_cstr_ImporterCreationFunction_ImporterDeletionFunction_vptr_int_vptr) их в реестр или [removing](#unregisterImporter_vptr_bool) из него.


Каждый импортёр имеет *уникальный идентификатор (или ID)*, представленный структурой **ImporterID**, объединяющей следующие значения:


- **Vendor Name** — имя компании или лица, предоставляющего импортёр.
- **Importer Name** — имя импортёра (например, может быть несколько импортёров с одинаковым именем *FBXImporter*, но от разных поставщиков).


Каждый импортёр имеет индекс **приоритета**, указывающий порядок, в котором он будет использоваться для обработки файлов среди других доступных импортёров, зарегистрированных для того же расширения файла (используется импортёр с *более высоким* значением приоритета среди доступных).


Вы также можете получить [list of all currently supported file extensions](#getSupportedExtensions_VECString) или [list of all file extensions supported by a specific importer](#getImporterExtensions_cstr_cstr_VECString).


## Import Class

### Методы класса

---

## bool isInitialized ( )

Возвращает значение, указывающее, инициализирован ли менеджер импорта.
### Возвращаемое значение

true, если менеджер импорта инициализирован; иначе false.
## bool containsImporter ( const Import::ImporterID & id , const char * extension )

Возвращает значение, указывающее, доступен ли [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика для обработки файлов с указанным расширением.
### Аргументы

- *const [Import::ImporterID](../../../../api/library/common/import/class.import_cpp.md#ImporterID) &* **id** - Структура *[ImporterID](#ImporterID)*.
- *const char ** **extension** - Расширение файлов, поддерживаемых импортёром.

### Возвращаемое значение

true, если доступен импортёр с указанным ID для обработки файлов с указанным расширением; иначе false.
## bool containsImporter ( const char * vendor_name , const char * importer_name , const char * extension )

Возвращает значение, указывающее, доступен ли [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика для обработки файлов с указанным расширением.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.
- *const char ** **extension** - Расширение файлов, поддерживаемых импортёром.

### Возвращаемое значение

true, если доступен импортёр с указанным именем и именем поставщика для обработки файлов с указанным расширением; иначе false.
## static void * registerImporter ( ImporterID id , const char * extension , ImporterCreationFunction creation_func , ImporterDeletionFunction deletion_func , const char * args = nullptr , int int = 0 )

Регистрирует новый [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанными параметрами.
### Аргументы

- *ImporterID* **id** - Структура *[ImporterID](#ImporterID)*.
- *const char ** **extension** - Расширение файлов, поддерживаемых импортёром.
- *ImporterCreationFunction* **creation_func** - Функция создания импортёра со следующей сигнатурой: ```cpp Importer * (*)(void *args) ``` .
- *ImporterDeletionFunction* **deletion_func** - Функция удаления импортёра со следующей сигнатурой: ```cpp void (*)(Importer *importer, void *args) ``` .
- *const char ** **args** - Список аргументов импортёра.
- *int* **int** - Приоритет импортёра для обработки файлов с указанным расширением.

### Возвращаемое значение

Дескриптор импортёра, если он был успешно зарегистрирован; иначе **nullptr**.
## static void * registerImporter ( const char * vendor_name , const char * importer_name , const char * extension , ImporterCreationFunction creation_func , ImporterDeletionFunction deletion_func , const char * args = nullptr , int int = 0 )

Регистрирует новый [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанными параметрами.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.
- *const char ** **extension** - Расширение файлов, поддерживаемых импортёром.
- *ImporterCreationFunction* **creation_func** - Функция создания импортёра со следующей сигнатурой: ```cpp Importer * (*)(void *args) ``` .
- *ImporterDeletionFunction* **deletion_func** - Функция удаления импортёра со следующей сигнатурой: ```cpp void (*)(Importer *importer, void *args) ``` .
- *const char ** **args** - Список аргументов импортёра.
- *int* **int** - Приоритет импортёра для обработки файлов с указанным расширением.

### Возвращаемое значение

Дескриптор импортёра, если он был успешно зарегистрирован; иначе **nullptr**.
## bool unregisterImporter ( void * handle )

Отменяет регистрацию указанного [importer](../../../../api/library/common/import/class.importer_cpp.md).
### Аргументы

- *void ** **handle** - Дескриптор импортёра.

### Возвращаемое значение

true, если указанный импортёр был успешно снят с регистрации; иначе false.
## int getImporterPriority ( const Import::ImporterID & id , const char * extension )

Возвращает [priority](#priority) импортёра с указанным ID для обработки файлов с указанным расширением.
### Аргументы

- *const [Import::ImporterID](../../../../api/library/common/import/class.import_cpp.md#ImporterID) &* **id** - Структура *[ImporterID](#ImporterID)*.
- *const char ** **extension** - Расширение импортируемого файла.

### Возвращаемое значение

Приоритет импортёра с указанным ID для указанного расширения.
## int getImporterPriority ( const char * vendor_name , const char * importer_name , const char * extension )

Возвращает [priority](#priority) импортёра с указанным именем и именем поставщика для обработки файлов с указанным расширением.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.
- *const char ** **extension** - Расширение импортируемого файла.

### Возвращаемое значение

Приоритет импортёра с указанным именем и именем поставщика для указанного расширения.
## bool isSupportedExtension ( const char * extension )

Возвращает значение, указывающее, поддерживается ли указанное расширение файла импортёром.
### Аргументы

- *const char ** **extension** - Строка с завершающим нулевым символом, содержащая проверяемое расширение файла.

### Возвращаемое значение

true, если указанное расширение файла поддерживается импортёром; иначе false.
## Vector < String > getSupportedExtensions ( ) const

Возвращает список всех поддерживаемых расширений файлов в виде вектора строк.
### Возвращаемое значение

Список всех поддерживаемых расширений в виде вектора строк.
## Vector < String > getImporterExtensions ( const char * vendor_name , const char * importer_name )

Возвращает список всех расширений, поддерживаемых [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.

### Возвращаемое значение

Список всех расширений, поддерживаемых импортёром с указанным именем и именем поставщика.
## Vector < String > getImporterExtensions ( const Import::ImporterID & id )

Возвращает список всех расширений, поддерживаемых [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным ID.
### Аргументы

- *const [Import::ImporterID](../../../../api/library/common/import/class.import_cpp.md#ImporterID) &* **id** - Структура *[ImporterID](#ImporterID)*.

### Возвращаемое значение

Список всех расширений, поддерживаемых импортёром с указанным ID.
## Vector < Import::ImporterID > getImporterIDsByExtension ( const char * extension , bool sort_by_priority = true )

Возвращает список идентификаторов (*[ImporterID](#ImporterID)*) импортёров, доступных для обработки файлов с указанным расширением.
### Аргументы

- *const char ** **extension** - Расширение импортируемых файлов.
- *bool* **sort_by_priority** - Установите true, если требуется сортировать импортёры по значению [priority](#priority); иначе установите false.

### Возвращаемое значение

Список идентификаторов (структур *[ImporterID](#ImporterID)*) импортёров, доступных для указанного расширения.
## Vector < Import::ImporterID > getImporterIDsByExtension ( const char * vendor_name , const char * extension , bool sort_by_priority = true )

Возвращает список идентификаторов (*[ImporterID](#ImporterID)*) импортёров указанного поставщика, доступных для обработки файлов с указанным расширением.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **extension** - Расширение импортируемых файлов.
- *bool* **sort_by_priority** - Установите true, если требуется сортировать импортёры по значению [priority](#priority); иначе установите false.

### Возвращаемое значение

Список идентификаторов (структур *[ImporterID](#ImporterID)*) импортёров указанного поставщика, доступных для указанного расширения.
## Vector < Import::ImporterID > getImporterIDsByExtension ( const Import::ImporterID & id , const char * extension , bool sort_by_priority = true )

Возвращает список идентификаторов (*[ImporterID](#ImporterID)*) импортёров с указанным ID для обработки файлов с указанным расширением.
### Аргументы

- *const [Import::ImporterID](../../../../api/library/common/import/class.import_cpp.md#ImporterID) &* **id** - Структура *[ImporterID](#ImporterID)*.
- *const char ** **extension** - Расширение импортируемых файлов.
- *bool* **sort_by_priority** - Установите true, если требуется сортировать импортёры по значению [priority](#priority); иначе установите false.

### Возвращаемое значение

Список идентификаторов (структур *[ImporterID](#ImporterID)*) импортёров с указанным ID для указанного расширения.
## Vector < Import::ImporterID > getImporterIDsByExtension ( const char * vendor_name , const char * importer_name , const char * extension , bool sort_by_priority = true )

Возвращает список идентификаторов (*[ImporterID](#ImporterID)*) [importers](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика для обработки файлов с указанным расширением.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.
- *const char ** **extension** - Расширение импортируемых файлов.
- *bool* **sort_by_priority** - Установите true, если требуется сортировать импортёры по значению [priority](#priority); иначе установите false.

### Возвращаемое значение

Список идентификаторов (структур *[ImporterID](#ImporterID)*) импортёров с указанным именем и именем поставщика для указанного расширения.
## Vector < Import::ImporterID > getImporterIDs ( )

Возвращает список идентификаторов (структур *[ImporterID](#ImporterID)*) всех доступных [importers](../../../../api/library/common/import/class.importer_cpp.md).
### Возвращаемое значение

Список идентификаторов (структур *[ImporterID](#ImporterID)*) всех доступных импортёров.
## Ptr < Importer > createImporter ( const Import::ImporterID & id , const char * extension )

Создаёт [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным ID для обработки файлов с указанным расширением.
### Аргументы

- *const [Import::ImporterID](../../../../api/library/common/import/class.import_cpp.md#ImporterID) &* **id** - Структура *[ImporterID](#ImporterID)*.
- *const char ** **extension** - Расширение импортируемых файлов.

### Возвращаемое значение

Новый созданный [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным ID для обработки файлов с указанным расширением (если он был успешно создан).
## Ptr < Importer > createImporter ( const char * vendor_name , const char * importer_name , const char * extension )

Создаёт [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика для обработки файлов с указанным расширением.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.
- *const char ** **extension** - Расширение импортируемых файлов.

### Возвращаемое значение

Новый созданный [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика для обработки файлов с указанным расширением (если он был успешно создан).
## Ptr < Importer > createImporterByFileName ( const char * filename )

Создаёт [importer](../../../../api/library/common/import/class.importer_cpp.md) для обработки указанного файла на основе предоставленного расширения.
### Аргументы

- *const char ** **filename** - Имя импортируемого файла.

### Возвращаемое значение

Новый созданный [importer](../../../../api/library/common/import/class.importer_cpp.md) для обработки файлов с указанным расширением (если он был успешно создан).
## Ptr < Importer > createImporterByFileName ( const char * vendor_name , const char * filename )

Создаёт [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем поставщика для обработки указанного файла на основе предоставленного расширения.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **filename** - Имя импортируемого файла.

### Возвращаемое значение

Новый созданный [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем поставщика для обработки указанного файла на основе предоставленного расширения (если он был успешно создан).
## Ptr < Importer > createImporterByFileName ( const Import::ImporterID & id , const char * filename )

Создаёт [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным ID для обработки указанного файла на основе предоставленного расширения.
### Аргументы

- *const [Import::ImporterID](../../../../api/library/common/import/class.import_cpp.md#ImporterID) &* **id** - Структура *[ImporterID](#ImporterID)*.
- *const char ** **filename** - Имя импортируемого файла.

### Возвращаемое значение

Новый созданный [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным ID для обработки указанного файла на основе предоставленного расширения (если он был успешно создан).
## Ptr < Importer > createImporterByFileName ( const char * vendor_name , const char * importer_name , const char * filename )

Создаёт [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика для обработки указанного файла на основе предоставленного расширения.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.
- *const char ** **filename** - Имя импортируемого файла.

### Возвращаемое значение

Новый созданный [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика для обработки указанного файла на основе предоставленного расширения (если он был успешно создан).
## String doImport ( const char * filepath , const char * output_path )

Импортирует содержимое из указанного входного файла в указанный выходной путь с использованием подходящего [importer](../../../../api/library/common/import/class.importer_cpp.md). Этот метод возвращает путь к результирующему выходному файлу.
### Аргументы

- *const char ** **filepath** - Путь к импортируемому входному файлу.
- *const char ** **output_path** - Выходной путь для размещения файлов с импортированными [scene elements](../../../../api/library/common/import/class.importscene_cpp.md).

### Возвращаемое значение

Путь к результирующему выходному файлу.
## String doImport ( const char * vendor_name , const char * filepath , const char * output_path )

Импортирует содержимое из указанного входного файла в указанный выходной путь с использованием подходящего [importer](../../../../api/library/common/import/class.importer_cpp.md) от указанного поставщика. Этот метод возвращает путь к результирующему выходному файлу.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **filepath** - Путь к импортируемому входному файлу.
- *const char ** **output_path** - Выходной путь для размещения файлов с импортированными [scene elements](../../../../api/library/common/import/class.importscene_cpp.md).

### Возвращаемое значение

Путь к результирующему выходному файлу.
## String doImport ( const Import::ImporterID & id , const char * filepath , const char * output_path )

Импортирует содержимое из указанного входного файла в указанный выходной путь с использованием [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным ID. Этот метод возвращает путь к результирующему выходному файлу.
### Аргументы

- *const [Import::ImporterID](../../../../api/library/common/import/class.import_cpp.md#ImporterID) &* **id** - Структура *[ImporterID](#ImporterID)*.
- *const char ** **filepath** - Путь к импортируемому входному файлу.
- *const char ** **output_path** - Выходной путь для размещения файлов с импортированными [scene elements](../../../../api/library/common/import/class.importscene_cpp.md).

### Возвращаемое значение

Путь к результирующему выходному файлу.
## String doImport ( const char * vendor_name , const char * importer_name , const char * filepath , const char * output_path )

Импортирует содержимое из указанного входного файла в указанный выходной путь с использованием [importer](../../../../api/library/common/import/class.importer_cpp.md) с указанным именем и именем поставщика. Этот метод возвращает путь к результирующему выходному файлу.
### Аргументы

- *const char ** **vendor_name** - Имя поставщика импортёра.
- *const char ** **importer_name** - Имя импортёра.
- *const char ** **filepath** - Путь к импортируемому входному файлу.
- *const char ** **output_path** - Выходной путь для размещения файлов с импортированными [scene elements](../../../../api/library/common/import/class.importscene_cpp.md).

### Возвращаемое значение

Путь к результирующему выходному файлу.
## bool containsImportProcessor ( const char * type_name )

Возвращает значение, указывающее, доступен ли [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md) с указанным именем типа.
### Аргументы

- *const char ** **type_name** - Имя типа процессора импорта.

### Возвращаемое значение

true, если доступен процессор импорта с указанным именем типа; иначе false.
## Ptr < ImportProcessor > createImportProcessor ( const char * type_name )

Создаёт новый процессор импорта указанного типа.
> **Notice:** Указанное имя типа процессора должно быть предварительно [registered](#registerImportProcessor_cstr_ImportProcessorCreationFunction_ImportProcessorDeletionFunction_vptr_vptr).


### Аргументы

- *const char ** **type_name** - Имя типа процессора импорта.

### Возвращаемое значение

Новый созданный [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md) с указанным именем типа (если он был успешно создан).
## static void * registerImportProcessor ( const char * type_name , ImportProcessorCreationFunction creation_func , ImportProcessorDeletionFunction deletion_func , void * args = nullptr )

Регистрирует новый [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md) с указанными параметрами.
### Аргументы

- *const char ** **type_name** - Имя типа процессора импорта.
- *ImportProcessorCreationFunction* **creation_func** - Функция создания процессора импорта со следующей сигнатурой: ```cpp ImportProcessor * (*)(void *args) ``` .
- *ImportProcessorDeletionFunction* **deletion_func** - Функция удаления процессора импорта со следующей сигнатурой: ```cpp void (*)(ImportProcessor *processor, void *args); ``` .
- *void ** **args** - Аргументы процессора импорта.

### Возвращаемое значение

Дескриптор процессора импорта, если он был успешно зарегистрирован; иначе **nullptr**.
## bool unregisterImportProcessor ( void * handle )

Отменяет регистрацию указанного [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md).
### Аргументы

- *void ** **handle** - Дескриптор процессора импорта.

### Возвращаемое значение

true, если указанный [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md) был успешно снят с регистрации; иначе false.
