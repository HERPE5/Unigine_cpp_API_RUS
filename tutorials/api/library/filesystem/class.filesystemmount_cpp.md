# Unigine::FileSystemMount Class (CPP)

**Header:** #include <UnigineFileSystem.h>


Этот класс представляет [**mount point**](../../../principles/filesystem/index_cpp.md#mount_points), которая используется для расширения [file system](../../../principles/filesystem/index_cpp.md) движка. Точка монтирования — это своего рода симлинк, позволяющий расширять виртуальную файловую систему вашего проекта, добавляя любые внешние папки и пакеты в каталог **data**.


## FileSystemMount Class

### Методы класса

## int getAccess () const

Возвращает текущий режим доступа точки монтирования, одно из значений [ACCESS_*](#ACCESS_READONLY).
### Возвращаемое значение

Текущий режим доступа точки монтирования.
## const char * getDataPath () const

Возвращает текущий абсолютный путь к смонтированной папке/пакету.
### Возвращаемое значение

Текущий абсолютный путь к смонтированной папке/пакету.
## const char * getName () const

Возвращает текущее имя точки монтирования.
### Возвращаемое значение

Текущее имя точки монтирования.
## const char * getUMountPath () const

Возвращает текущий абсолютный путь к файлу `*.umount`.
### Возвращаемое значение

Текущий абсолютный путь к файлу `*.umount`.
## const char * getVirtualPath () const

Возвращает текущий [virtual path](../../../principles/filesystem/index_cpp.md#virtual_paths) к папке, в которую монтируется содержимое внешней папки/пакета.
### Возвращаемое значение

Текущий виртуальный путь к папке.
---

## void setExclusiveFilters ( Vector < String > & OUT_filters )

Устанавливает список исключающих фильтров (исключений из списка игнорирования, заданного *[setIgnoreFilters()](../../...md#setIgnoreFilters_VECString_void)*), используемых для включения только определённых файлов при монтировании. Фильтры задаются в виде масок (например, *"*.jpg", "some_folder_*/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и позволяют ограничить видимый набор файлов только теми, что соответствуют указанным шаблонам.
> **Notice:** В конце **масок для каталогов** обязателен **завершающий слэш** ('/')!

### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **OUT_filters** - Список масок, используемых для фильтрации файлов в смонтированной папке/пакете. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void getExclusiveFilters ( Vector < String > & OUT_filters ) const

Возвращает список исключающих фильтров (исключений из списка игнорирования, заданного *[setIgnoreFilters()](../../...md#setIgnoreFilters_VECString_void)*), используемых для включения только определённых файлов при монтировании. Фильтры задаются в виде масок (например, *"*.jpg", "some_folder_*/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и позволяют ограничить видимый набор файлов только теми, что соответствуют указанным шаблонам.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_filters** - Список масок, используемых в данный момент для фильтрации файлов в смонтированной папке/пакете. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Vector < String > getExclusiveFilters ( ) const

Возвращает список исключающих фильтров (исключений из списка игнорирования, заданного *[setIgnoreFilters()](../../...md#setIgnoreFilters_VECString_void)*), используемых для включения только определённых файлов при монтировании. Фильтры задаются в виде масок (например, *"*.jpg", "some_folder_*/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и позволяют ограничить видимый набор файлов только теми, что соответствуют указанным шаблонам.
## void setIgnoreFilters ( Vector < String > & OUT_filters )

Устанавливает список фильтров игнорирования (чёрный список), используемых для исключения определённых файлов или каталогов из хранения в базе данных GUID. Фильтры задаются в виде масок **с полной поддержкой стандартных шаблонов масок** (например, *"*.tmp", "cache_*/", "**/.git/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и помогают предотвратить отслеживание или присвоение GUID ненужным файлам.
> **Notice:** В конце **масок для каталогов** обязателен **завершающий слэш** ('/')!

### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [String](../../../api/library/common/class.string_cpp.md) > &* **OUT_filters** - Список масок, используемых для исключения игнорируемых файлов в смонтированной папке/пакете. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void getIgnoreFilters ( Vector < String > & OUT_filters ) const

Возвращает список фильтров игнорирования (чёрный список), используемых для исключения определённых файлов или каталогов из хранения в базе данных GUID. Фильтры задаются в виде масок **с полной поддержкой стандартных шаблонов масок** (например, *"*.tmp", "cache_*/", "**/.git/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и помогают предотвратить отслеживание или присвоение GUID ненужным файлам.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_filters** - Список масок, используемых в данный момент для исключения игнорируемых файлов в смонтированной папке/пакете. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Vector < String > getIgnoreFilters ( ) const

Возвращает список фильтров игнорирования (чёрный список), используемых для исключения определённых файлов или каталогов из хранения в базе данных GUID. Фильтры задаются в виде масок **с полной поддержкой стандартных шаблонов масок** (например, *"*.tmp", "cache_*/", "**/.git/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и помогают предотвратить отслеживание или присвоение GUID ненужным файлам.
## void getVirtualFiles ( Vector < String > & OUT_files ) const

Возвращает список [virtual paths](../../../principles/filesystem/index_cpp.md#virtual_paths) ко всем файлам в смонтированной папке/пакете.
> **Notice:** Содержимое вложенных точек монтирования внутри смонтированной папки не будет включено в список.


### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_files** - Выходной вектор для хранения списка файлов, хранящихся в смонтированной папке/пакете. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## bool isPathFilteredOut ( const char * path ) const

Возвращает значение, указывающее, отфильтрован ли указанный путь фильтрами [ignore](#getIgnoreFilters_VECString_void) и [exclusive](#getExclusiveFilters_VECString_void).
### Аргументы

- *const char ** **path** - Любой путь к файлу.

### Возвращаемое значение

true, если указанный путь отфильтрован после применения фильтров ignore и exclusive, если они заданы; иначе false.
## void setGuidsDBIgnoreFilters ( const Vector < String > & filters )

Устанавливает список фильтров игнорирования (чёрный список) [GUIDs database](../../../principles/filesystem/index_cpp.md#guids) (`guids.db`), используемых для исключения определённых файлов или каталогов из хранения в базе данных GUID. Фильтры задаются в виде масок **с полной поддержкой стандартных шаблонов масок** (например, *"*.tmp", "cache_*/", "**/.git/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и помогают предотвратить отслеживание или присвоение GUID ненужным или временным файлам, сохраняя файл `guids.db` организованным и актуальным, без излишнего разрастания.
> **Notice:** В конце **масок для каталогов** обязателен **завершающий слэш** ('/')!

### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **filters** - Список масок, используемых для исключения файлов или каталогов из базы данных GUID.

## void getGuidsDBIgnoreFilters ( Vector < String > & OUT_filters ) const

Возвращает список фильтров игнорирования (чёрный список) [GUIDs database](../../../principles/filesystem/index_cpp.md#guids) (`guids.db`), используемых для исключения определённых файлов или каталогов из хранения в базе данных GUID. Фильтры задаются в виде масок **с полной поддержкой стандартных шаблонов масок** (например, *"*.tmp", "cache_*/", "**/.git/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и помогают предотвратить отслеживание или присвоение GUID ненужным или временным файлам, сохраняя файл `guids.db` организованным и актуальным, без излишнего разрастания.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_filters** - Выходной список масок, используемых в данный момент для исключения файлов или каталогов из базы данных GUID. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Vector < String > getGuidsDBIgnoreFilters ( ) const

Возвращает список фильтров игнорирования (чёрный список) [GUIDs database](../../../principles/filesystem/index_cpp.md#guids) (`guids.db`), используемых для исключения определённых файлов или каталогов из хранения в базе данных GUID. Фильтры задаются в виде масок **с полной поддержкой стандартных шаблонов масок** (например, *"*.tmp", "cache_*/", "**/.git/"*, и т.д. - [read more about wildcards](../../../principles/filesystem/wildcards.md)) и помогают предотвратить отслеживание или присвоение GUID ненужным или временным файлам, сохраняя файл `guids.db` организованным и актуальным, без излишнего разрастания.
