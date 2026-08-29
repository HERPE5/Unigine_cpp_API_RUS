# Unigine::FileSystemAssets Class (CPP)

**Header:** #include <UnigineFileSystem.h>

> **Notice:** This class is a singleton.


Этот класс представляет подсистему [file system](../../../principles/filesystem/index_cpp.md) движка, которая используется для управления [assets and runtime files](../../../editor2/assets_workflow/assets_runtimes.md).


> **Notice:** Этот класс находится в пространстве имён **Unigine**.


Вы можете использовать консольные команды `assets_info` и `assets_list` для просмотра информации о неродных ассетах и сгенерированных для них runtime-файлах.


## FileSystemAssets Class

### Методы класса

---

## bool isAsset ( const UGUID & any_guid )

Возвращает значение, указывающее, является ли файл с указанным GUID [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) (т.е. имеет ли сгенерированные для него [runtime files](../../../principles/filesystem/index_cpp.md#assets_runtimes)).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл с указанным GUID является неродным ассетом; иначе false.
## bool isAsset ( const char * path )

Возвращает значение, указывающее, является ли файл с указанным путём [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) (т.е. имеет ли сгенерированные для него [runtime files](../../../principles/filesystem/index_cpp.md#assets_runtimes)).
### Аргументы

- *const char ** **path** - Путь к файлу.

### Возвращаемое значение

true, если файл с указанным путём является неродным ассетом; иначе false.
## UGUID getAssetGUID ( const char * path )

Возвращает GUID [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) (имеющего сгенерированный runtime-файл или файлы) для указанного пути.
### Аргументы

- *const char ** **path** - Путь к runtime-файлу или файлу ассета.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) неродного ассета, соответствующего указанному пути, если он существует; иначе пустой GUID.
> **Notice:** Этот метод вернёт пустой GUID для любого ассета, для которого не сгенерированы runtime-файлы.


## UGUID getAssetGUID ( const UGUID & any_guid )

Возвращает GUID [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) (имеющего сгенерированный runtime-файл или файлы) для указанного GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) неродного ассета, соответствующего указанному пути, если он существует; иначе пустой GUID.
> **Notice:** Этот метод вернёт пустой GUID для любого ассета, для которого не сгенерированы runtime-файлы.


## int getNumRuntimes ( const char * asset_path )

Возвращает количество [runtime files](../../../editor2/assets_workflow/assets_runtimes.md) для [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) с указанным путём.
### Аргументы

- *const char ** **asset_path** - Путь к файлу ассета.

### Возвращаемое значение

Количество runtime-файлов, сгенерированных для указанного ассета.
## int getNumRuntimes ( const UGUID & asset_path )

Возвращает количество [runtime files](../../../editor2/assets_workflow/assets_runtimes.md) для [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_path** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета.

### Возвращаемое значение

Количество runtime-файлов, сгенерированных для указанного ассета.
## bool isPrimary ( const char * path )

Возвращает значение, указывающее, является ли runtime-файл, соответствующий указанному пути, [primary](../../../principles/filesystem/index_cpp.md#primary_runtime).
### Аргументы

- *const char ** **path** - Путь к runtime-файлу.

### Возвращаемое значение

true, если runtime-файл, соответствующий указанному пути, является первичным; иначе false.
## bool isPrimary ( const UGUID & any_guid )

Возвращает значение, указывающее, является ли runtime-файл, соответствующий указанному GUID, [primary](../../../principles/filesystem/index_cpp.md#primary_runtime).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) runtime-файла.

### Возвращаемое значение

true, если runtime-файл, соответствующий указанному GUID, является первичным; иначе false.
## UGUID getPrimaryGUID ( const UGUID & any_guid )

Возвращает GUID [primary runtime file](../../../principles/filesystem/index_cpp.md#primary_runtime) для указанного GUID файла, если он существует.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

Возвращаемое значение определяется указанным GUID следующим образом:
- GUID файла ассета -> GUID его первичного runtime-файла, если есть; иначе пустой GUID.
- GUID первичного runtime-файла -> GUID этого первичного runtime-файла.
- GUID runtime-файла -> GUID первичного runtime-файла для его ассета, если есть; иначе пустой GUID.
- Любой другой GUID файла -> пустой GUID.


## UGUID getPrimaryGUID ( const char * path )

Возвращает GUID [primary runtime file](../../../principles/filesystem/index_cpp.md#primary_runtime) для указанного пути к файлу, если он существует.
### Аргументы

- *const char ** **path** - Любой путь к файлу.

### Возвращаемое значение

Возвращаемое значение определяется указанным GUID следующим образом:
- Путь к файлу ассета -> GUID его первичного runtime-файла, если есть; иначе пустой GUID.
- Путь к первичному runtime-файлу -> GUID этого первичного runtime-файла.
- Путь к runtime-файлу -> GUID первичного runtime-файла для его ассета, если есть; иначе пустой GUID.
- Любой другой путь к файлу -> пустой GUID.


## bool isMeta ( const UGUID & any_guid )

Возвращает значение, указывающее, является ли файл с указанным GUID файлом [`*.meta`](../../../editor2/assets_workflow/assets_runtimes.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл с указанным GUID является файлом `*.meta`; иначе false.
## bool isRuntime ( const char * path )

Возвращает значение, указывающее, является ли файл, соответствующий указанному пути, сгенерированным [runtime-файлом](../../../principles/filesystem/index_cpp.md#assets_runtimes).
### Аргументы

- *const char ** **path** - Любой путь к файлу.

### Возвращаемое значение

true, если файл, соответствующий указанному пути, является сгенерированным runtime-файлом; иначе false.
> **Notice:** Этот метод вернёт 0 для любого [native asset](../../../editor2/assets_workflow/assets_runtimes.md).


## bool isRuntime ( const UGUID & any_guid )

Возвращает значение, указывающее, является ли файл, соответствующий указанному GUID, сгенерированным [runtime-файлом](../../../principles/filesystem/index_cpp.md#assets_runtimes).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

true, если файл, соответствующий указанному пути, является сгенерированным runtime-файлом; иначе false.
> **Notice:** Этот метод вернёт 0 для любого [native asset](../../../editor2/assets_workflow/assets_runtimes.md).


## bool isRuntimePath ( const char * path )

Возвращает значение, указывающее, является ли указанный путь путём к сгенерированному runtime-файлу.
### Аргументы

- *const char ** **path** - Любой путь к файлу.

### Возвращаемое значение

true, если указанный путь является путём к сгенерированному runtime-файлу; иначе false.
## String getRuntimeAlias ( const char * runtime_path )

Возвращает [alias](../../../principles/filesystem/index_cpp.md#alias) сгенерированного runtime-файла, указанного заданным путём.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.

### Возвращаемое значение

[Alias](../../../principles/filesystem/index_cpp.md#alias), установленный для указанного сгенерированного runtime-файла, если он существует; иначе nullptr.
## String getRuntimeAlias ( const UGUID & runtime_guid )

Возвращает [alias](../../../principles/filesystem/index_cpp.md#alias) сгенерированного runtime-файла, указанного заданным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.

### Возвращаемое значение

[Alias](../../../principles/filesystem/index_cpp.md#alias), установленный для указанного сгенерированного runtime-файла, если он существует; иначе nullptr.
## String getRuntimeAlias ( String asset_path , int index )

Возвращает [alias](../../../principles/filesystem/index_cpp.md#alias) сгенерированного runtime-файла, указанного заданным путём к неродному ассету и индексом runtime-файла.
### Аргументы

- *[String](../../../api/library/common/class.string_cpp.md)* **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.

### Возвращаемое значение

[Alias](../../../principles/filesystem/index_cpp.md#alias), установленный для указанного сгенерированного runtime-файла, если он существует; иначе nullptr.
## String getRuntimeAlias ( const UGUID & asset_guid , int index )

Возвращает [alias](../../../principles/filesystem/index_cpp.md#alias) сгенерированного runtime-файла, указанного заданным GUID неродного ассета и индексом runtime-файла.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.

### Возвращаемое значение

[Alias](../../../principles/filesystem/index_cpp.md#alias), установленный для указанного сгенерированного runtime-файла, если он существует; иначе nullptr.
## bool setRuntimeGUID ( const char * runtime_path , const UGUID & new_runtime_guid )

Устанавливает новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для сгенерированного runtime-файла с указанным путём.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - Новый устанавливаемый GUID.

### Возвращаемое значение

true, если новый GUID успешно установлен; иначе false.
## bool setRuntimeGUID ( const UGUID & runtime_guid , const UGUID & new_runtime_guid )

Устанавливает новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для сгенерированного runtime-файла с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - Новый устанавливаемый GUID.

### Возвращаемое значение

true, если новый GUID успешно установлен; иначе false.
## bool setRuntimeGUID ( const char * asset_path , int index , const UGUID & new_runtime_guid )

Устанавливает новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для сгенерированного runtime-файла, указанного заданным путём к неродному ассету и индексом runtime-файла.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - Новый устанавливаемый GUID.

### Возвращаемое значение

true, если новый GUID успешно установлен; иначе false.
## bool setRuntimeGUID ( const UGUID & asset_guid , int index , const UGUID & new_runtime_guid )

Устанавливает новый [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для сгенерированного runtime-файла, указанного заданным GUID неродного ассета и индексом runtime-файла.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - Новый устанавливаемый GUID.

### Возвращаемое значение

true, если новый GUID успешно установлен; иначе false.
## UGUID getRuntimeGUID ( const char * asset_path , int index )

Возвращает текущий [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла, указанного заданным путём к неродному ассету и индексом runtime-файла.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.

### Возвращаемое значение

Текущий [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла для указанного ассета и индекса runtime-файла, если есть; иначе пустой GUID.
## UGUID getRuntimeGUID ( const UGUID & asset_guid , int index )

Возвращает текущий [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла, указанного заданным GUID неродного ассета и индексом runtime-файла.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.

### Возвращаемое значение

Текущий [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла для указанного ассета и индекса runtime-файла, если есть; иначе пустой GUID.
## UGUID addRuntime ( const char * asset_path , const char * alias , int primary = 0 )

Создаёт новый [runtime-файл](../../../principles/filesystem/index_cpp.md#assets_runtimes) для ассета с указанным путём. Для нового runtime-файла будет сгенерирован новый GUID.
### Аргументы

- *const char ** **asset_path** - Путь к ассету, для которого создаётся новый runtime-файл.
- *const char ** **alias** - [Alias](../../../principles/filesystem/index_cpp.md#alias) для нового runtime-файла.
- *int* **primary** - Используйте 1, чтобы создать новый runtime-файл как первичный; иначе 0.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) нового созданного runtime-файла, если он успешно создан; иначе пустой GUID.
## UGUID addRuntime ( const UGUID & asset_guid , const char * alias , int primary = 0 )

Создаёт новый [runtime-файл](../../../principles/filesystem/index_cpp.md#assets_runtimes) для ассета с указанным GUID. Для нового runtime-файла будет сгенерирован новый GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого создаётся новый runtime-файл.
- *const char ** **alias** - [Alias](../../../principles/filesystem/index_cpp.md#alias) для нового runtime-файла.
- *int* **primary** - Используйте 1, чтобы создать новый runtime-файл как первичный; иначе 0.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) нового созданного runtime-файла, если он успешно создан; иначе пустой GUID.
## bool addRuntime ( const char * asset_path , const char * alias , const UGUID & runtime_guid , int primary = 0 )

Создаёт новый [runtime-файл](../../../principles/filesystem/index_cpp.md#assets_runtimes) для ассета с указанным путём. Новому runtime-файлу будет присвоен указанный GUID.
### Аргументы

- *const char ** **asset_path** - Путь к ассету, для которого создаётся новый runtime-файл.
- *const char ** **alias** - [Alias](../../../principles/filesystem/index_cpp.md#alias) для нового runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для нового runtime-файла.
- *int* **primary** - Используйте 1, чтобы создать новый runtime-файл как первичный; иначе 0.

### Возвращаемое значение

true, если новый runtime-файл успешно создан; иначе false.
## bool addRuntime ( const UGUID & asset_guid , const char * alias , const UGUID & runtime_guid , int primary = 0 )

Создаёт новый [runtime-файл](../../../principles/filesystem/index_cpp.md#assets_runtimes) для ассета с указанным GUID. Новому runtime-файлу будет присвоен указанный GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого создаётся новый runtime-файл.
- *const char ** **alias** - [Alias](../../../principles/filesystem/index_cpp.md#alias) для нового runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) для нового runtime-файла.
- *int* **primary** - Используйте 1, чтобы создать новый runtime-файл как первичный; иначе 0.

### Возвращаемое значение

true, если новый runtime-файл успешно создан; иначе false.
## bool clearRuntimes ( const char * asset_path )

Удаляет все сгенерированные [runtime files](../../../principles/filesystem/index_cpp.md#assets_runtimes) для ассета с указанным путём.
### Аргументы

- *const char ** **asset_path** - Путь к ассету, для которого удаляются все сгенерированные runtime-файлы.

### Возвращаемое значение

true, если все сгенерированные runtime-файлы для указанного ассета успешно удалены; иначе false.
## bool clearRuntimes ( const UGUID & asset_guid )

Удаляет все сгенерированные [runtime files](../../../principles/filesystem/index_cpp.md#assets_runtimes) для ассета с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого удаляются все сгенерированные runtime-файлы.

### Возвращаемое значение

true, если все сгенерированные runtime-файлы для указанного ассета успешно удалены; иначе false.
## UGUID copyRuntime ( const char * runtime_path , const char * new_asset_path )

Добавляет копию сгенерированного runtime-файла с указанным путём к другому ассету с указанным путём.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const char ** **runtime_path** - Путь к копируемому сгенерированному runtime-файлу.
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## UGUID copyRuntime ( const char * runtime_path , const UGUID & new_asset_guid )

Добавляет копию сгенерированного runtime-файла с указанным путём к другому ассету с указанным GUID.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const char ** **runtime_path** - Путь к копируемому сгенерированному runtime-файлу.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## UGUID copyRuntime ( const UGUID & runtime_guid , const char * new_asset_path )

Добавляет копию сгенерированного runtime-файла с указанным путём к другому ассету с указанным путём.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) копируемого сгенерированного runtime-файла.
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## UGUID copyRuntime ( const UGUID & runtime_guid , const UGUID & new_asset_guid )

Добавляет копию сгенерированного runtime-файла с указанным GUID к другому ассету, указанному по GUID.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) копируемого сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## UGUID copyRuntime ( const char * asset_path , int index , const char * new_asset_path )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по пути, к другому ассету с указанным путём.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const char ** **asset_path** - Путь к файлу ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## UGUID copyRuntime ( const char * asset_path , int index , const UGUID & new_asset_guid )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по пути, к другому ассету с указанным GUID.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const char ** **asset_path** - Путь к файлу ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## UGUID copyRuntime ( const UGUID & asset_guid , int index , const char * new_asset_path )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по GUID, к другому ассету с указанным путём.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_UGUID_int).
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## UGUID copyRuntime ( const UGUID & asset_guid , int index , const UGUID & new_asset_guid )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по GUID, к другому ассету с указанным GUID.
> **Notice:** Для созданной копии runtime-файла будет сгенерирован новый GUID.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_UGUID_int).
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) новой копии runtime-файла, если она успешно создана; иначе пустой GUID.
## bool copyRuntime ( const char * runtime_path , const char * new_asset_path , const UGUID & new_runtime_guid )

Добавляет копию сгенерированного runtime-файла, указанного по пути, к другому ассету с указанным путём.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const char ** **runtime_path** - Путь к копируемому сгенерированному runtime-файлу.
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool copyRuntime ( const char * runtime_path , const UGUID & new_asset_guid , const UGUID & new_runtime_guid )

Добавляет копию сгенерированного runtime-файла, указанного по пути, к другому ассету с указанным GUID.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const char ** **runtime_path** - Путь к копируемому сгенерированному runtime-файлу.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool copyRuntime ( const UGUID & runtime_guid , const char * new_asset_path , const UGUID & new_runtime_guid )

Добавляет копию сгенерированного runtime-файла, указанного по GUID, к другому ассету с указанным путём.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) of the asset file to which the generated runtime file to be copied belongs.
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool copyRuntime ( const UGUID & runtime_guid , const UGUID & new_asset_guid , const UGUID & new_runtime_guid )

Добавляет копию сгенерированного runtime-файла, указанного по GUID, к другому ассету с указанным GUID.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) копируемого сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool copyRuntime ( const char * asset_path , int index , const char * new_asset_path , const UGUID & new_runtime_guid )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по пути, к другому ассету с указанным путём.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const char ** **asset_path** - Путь к файлу ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool copyRuntime ( const char * asset_path , int index , const UGUID & new_asset_guid , const UGUID & new_runtime_guid )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по пути, к другому ассету с указанным GUID.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const char ** **asset_path** - Путь к файлу ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool copyRuntime ( const UGUID & asset_guid , int index , const char * new_asset_path , const UGUID & new_runtime_guid )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по GUID, к другому ассету с указанным путём.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_UGUID_int).
- *const char ** **new_asset_path** - Путь к другому ассету, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool copyRuntime ( const UGUID & asset_guid , int index , const UGUID & new_asset_guid , const UGUID & new_runtime_guid )

Добавляет копию runtime-файла с указанным индексом, сгенерированного для ассета, указанного по GUID, к другому ассету с указанным GUID.
> **Notice:** Созданной копии runtime-файла будет присвоен указанный GUID runtime-файла.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, которому принадлежит копируемый сгенерированный runtime-файл.
- *int* **index** - Индекс копируемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_UGUID_int).
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) ассета, для которого добавляется копия сгенерированного runtime-файла.
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md), устанавливаемый для новой копии runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно скопирован; иначе false.
## bool removeRuntime ( const char * runtime_path )

Удаляет указанный сгенерированный runtime-файл и удаляет его из списка runtime-файлов соответствующего ассета.
### Аргументы

- *const char ** **runtime_path** - Путь к удаляемому сгенерированному runtime-файлу.

### Возвращаемое значение

true, если указанный runtime-файл успешно удалён; иначе false.
## bool removeRuntime ( const UGUID & runtime_guid )

Удаляет указанный сгенерированный runtime-файл и удаляет его из списка runtime-файлов соответствующего ассета.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) удаляемого сгенерированного runtime-файла.

### Возвращаемое значение

true, если указанный runtime-файл успешно удалён; иначе false.
## bool removeRuntime ( const char * asset_path , int index )

Удаляет сгенерированный runtime-файл с указанным индексом и удаляет его из списка runtime-файлов ассета, указанного по пути.
### Аргументы

- *const char ** **asset_path** - Путь к файлу ассета, для которого удаляется указанный сгенерированный runtime-файл.
- *int* **index** - Индекс удаляемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).

### Возвращаемое значение

true, если указанный runtime-файл успешно удалён; иначе false.
## bool removeRuntime ( const UGUID & asset_guid , int index )

Удаляет сгенерированный runtime-файл с указанным индексом и удаляет его из списка runtime-файлов ассета, указанного по GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, для которого удаляется указанный сгенерированный runtime-файл.
- *int* **index** - Индекс удаляемого сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_UGUID_int).

### Возвращаемое значение

true, если указанный runtime-файл успешно удалён; иначе false.
## UGUID resolve ( const UGUID & any_guid )

Разрешает указанный GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

Возвращаемое значение GUID определяется указанным GUID следующим образом:
- GUID файла [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) -> GUID его первичного runtime-файла, если есть; иначе GUID файла ассета.
- Любой другой GUID файла -> GUID файла как есть.


```cpp
// если сгенерирован первичный runtime-файл
resolve(asset_guid);		//	-> primary_guid
resolve(primary_guid);		//	-> primary_guid
resolve(runtime_guid);		//	-> runtime_guid

// если первичный runtime-файл не сгенерирован
resolve(asset_guid);		//	-> asset_guid
resolve(primary_guid);		//	-> primary_guid
resolve(runtime_guid);		//	-> runtime_guid

```


## UGUID resolveAsset ( const UGUID & any_guid )

Разрешает указанный GUID в соответствующий GUID ассета, если он есть, или оставляет указанный GUID без изменений.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

Возвращаемое значение GUID определяется указанным GUID следующим образом:
- GUID [primary runtime file](../../../principles/filesystem/index_cpp.md#primary_runtime) -> GUID исходного файла ассета.
- GUID сгенерированного runtime-файла -> GUID исходного файла ассета.
- GUID файла [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) -> GUID как есть.
- Любой другой GUID файла -> GUID как есть.


```cpp
resolveAsset(asset_guid);		//	-> asset_guid
resolveAsset(primary_guid);		//	-> asset_guid
resolveAsset(runtime_guid);		//	-> asset_guid

```


## UGUID resolvePrimary ( const UGUID & any_guid )

Разрешает указанный GUID в соответствующий GUID первичного runtime-файла, если он есть.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **any_guid** - Любой [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла.

### Возвращаемое значение

Возвращаемое значение GUID определяется указанным GUID следующим образом:
- Любой GUID сгенерированного runtime-файла -> GUID первичного runtime-файла для исходного ассета.
- GUID файла [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md) -> GUID его первичного runtime-файла, если есть; иначе пустой GUID.
- Любой другой GUID файла -> пустой GUID.


```cpp
// если сгенерирован первичный runtime-файл
resolvePrimary(asset_guid);		//	-> primary_guid
resolvePrimary(primary_guid);	//	-> primary_guid
resolvePrimary(runtime_guid);	//	-> primary_guid

// если первичный runtime-файл не сгенерирован
resolvePrimary(asset_guid);			//	-> empty guid
resolvePrimary(runtime_guid);		//	-> empty guid

```


## UGUID resolveRuntimeAlias ( const char * path )

Разрешает указанный [alias](../../../principles/filesystem/index_cpp.md#alias) сгенерированного runtime-файла в соответствующий GUID, если он есть.
### Аргументы

- *const char ** **path** - [Alias](../../../principles/filesystem/index_cpp.md#alias) runtime-файла.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла с указанным псевдонимом, если он есть; иначе пустой GUID
## bool setRuntimeAlias ( const UGUID & asset_guid , int index , const char * new_alias )

Устанавливает новый [alias](../../../principles/filesystem/index_cpp.md#alias) для сгенерированного runtime-файла, указанного заданным GUID неродного ассета и индексом runtime-файла.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.
- *const char ** **new_alias** - Новый устанавливаемый псевдоним.

### Возвращаемое значение

true, если новый псевдоним успешно установлен; иначе false.
## bool setRuntimeAlias ( const UGUID & runtime_guid , const char * new_alias )

Устанавливает новый [alias](../../../principles/filesystem/index_cpp.md#alias) для сгенерированного runtime-файла с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.
- *const char ** **new_alias** - Новый устанавливаемый псевдоним.

### Возвращаемое значение

true, если новый псевдоним успешно установлен; иначе false.
## bool setRuntimeAlias ( const char * runtime_path , const char * new_alias )

Устанавливает новый [alias](../../../principles/filesystem/index_cpp.md#alias) для сгенерированного runtime-файла с указанным путём.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.
- *const char ** **new_alias** - Новый устанавливаемый псевдоним.

### Возвращаемое значение

true, если новый псевдоним успешно установлен; иначе false.
## bool setRuntimeAlias ( const char * asset_path , int index , const char * new_alias )

Устанавливает новый [alias](../../../principles/filesystem/index_cpp.md#alias) для сгенерированного runtime-файла, указанного заданным путём к неродному ассету и индексом runtime-файла.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.
- *const char ** **new_alias** - Новый устанавливаемый псевдоним.

### Возвращаемое значение

true, если новый псевдоним успешно установлен; иначе false.
## bool setRuntimePrimary ( const char * asset_path , int index , int primary )

Устанавливает или снимает статус [primary](../../../principles/filesystem/index_cpp.md#primary_runtime) для сгенерированного runtime-файла, указанного заданным путём к неродному ассету и индексом runtime-файла.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.
- *int* **primary** - 1, чтобы сделать runtime-файл первичным; 0, чтобы снять этот статус, если он уже установлен.

### Возвращаемое значение

true, если runtime-файл успешно установлен как первичный; иначе false.
> **Notice:** Может существовать только один первичный runtime-файл, поэтому при установке нового runtime-файла как первичного статус предыдущего снимается.


## bool setRuntimePrimary ( const char * runtime_path , int primary )

Устанавливает или снимает статус [primary](../../../principles/filesystem/index_cpp.md#primary_runtime) для сгенерированного runtime-файла с указанным путём.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.
- *int* **primary** - 1, чтобы сделать runtime-файл первичным; 0, чтобы снять этот статус, если он уже установлен.

### Возвращаемое значение

true, если runtime-файл успешно установлен как первичный; иначе false.
> **Notice:** Может существовать только один первичный runtime-файл, поэтому при установке нового runtime-файла как первичного статус предыдущего снимается.


## bool setRuntimePrimary ( const UGUID & runtime_guid , int primary )

Устанавливает или снимает статус [primary](../../../principles/filesystem/index_cpp.md#primary_runtime) для сгенерированного runtime-файла с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.
- *int* **primary** - 1, чтобы сделать runtime-файл первичным; 0, чтобы снять этот статус, если он уже установлен.

### Возвращаемое значение

true, если runtime-файл успешно установлен как первичный; иначе false.
> **Notice:** Может существовать только один первичный runtime-файл, поэтому при установке нового runtime-файла как первичного статус предыдущего снимается.


## bool setRuntimePrimary ( const UGUID & asset_guid , int index , int primary )

Устанавливает или снимает статус [primary](../../../principles/filesystem/index_cpp.md#primary_runtime) для сгенерированного runtime-файла, указанного заданным GUID неродного ассета и индексом runtime-файла.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла.
- *int* **primary** - 1, чтобы сделать runtime-файл первичным; 0, чтобы снять этот статус, если он уже установлен.

### Возвращаемое значение

true, если runtime-файл успешно установлен как первичный; иначе false.
> **Notice:** Может существовать только один первичный runtime-файл, поэтому при установке нового runtime-файла как первичного статус предыдущего снимается.


## bool setRuntimeParameter ( const UGUID & asset_guid , int index , const char * parameter_name , const char * new_parameter_value )

Устанавливает новый параметр с указанным именем и значением для сгенерированного runtime-файла, указанного по GUID неродного ассета.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя устанавливаемого параметра.
- *const char ** **new_parameter_value** - Устанавливаемое значение параметра.

### Возвращаемое значение

true, если новый параметр runtime-файла успешно установлен; иначе false.
## bool setRuntimeParameter ( const char * asset_path , int index , const char * parameter_name , const char * new_parameter_value )

Устанавливает новый параметр с указанным именем и значением для сгенерированного runtime-файла, указанного по пути к неродному ассету.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя устанавливаемого параметра.
- *const char ** **new_parameter_value** - Устанавливаемое значение параметра.

### Возвращаемое значение

true, если новый параметр runtime-файла успешно установлен; иначе false.
## bool setRuntimeParameter ( const UGUID & runtime_guid , const char * parameter_name , const char * new_parameter_value )

Устанавливает новый параметр с указанным именем и значением для сгенерированного runtime-файла с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.
- *const char ** **parameter_name** - Имя устанавливаемого параметра.
- *const char ** **new_parameter_value** - Устанавливаемое значение параметра.

### Возвращаемое значение

true, если новый параметр runtime-файла успешно установлен; иначе false.
## bool setRuntimeParameter ( const char * runtime_path , const char * parameter_name , const char * new_parameter_value )

Устанавливает новый параметр с указанным именем и значением для сгенерированного runtime-файла с указанным путём.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.
- *const char ** **parameter_name** - Имя устанавливаемого параметра.
- *const char ** **new_parameter_value** - Устанавливаемое значение параметра.

### Возвращаемое значение

true, если новый параметр runtime-файла успешно установлен; иначе false.
## String getRuntimeParameter ( const UGUID & asset_guid , int index , const char * parameter_name ) const

Возвращает значение указанного параметра указанного runtime-файла, либо пустую строку, если такого параметра не существует.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, для runtime-файла которого возвращается параметр.
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя возвращаемого параметра.

### Возвращаемое значение

Значение указанного параметра, либо пустая строка, если такого параметра не существует.
## String getRuntimeParameter ( const char * asset_path , int index , const char * parameter_name ) const

Возвращает значение указанного параметра указанного runtime-файла, либо пустую строку, если такого параметра не существует.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя возвращаемого параметра.

### Возвращаемое значение

Значение указанного параметра, либо пустая строка, если такого параметра не существует.
## String getRuntimeParameter ( const UGUID & runtime_guid , const char * parameter_name ) const

Возвращает значение указанного параметра указанного runtime-файла, либо пустую строку, если такого параметра не существует.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.
- *const char ** **parameter_name** - Имя возвращаемого параметра.

### Возвращаемое значение

Значение указанного параметра, либо пустая строка, если такого параметра не существует.
## String getRuntimeParameter ( const char * runtime_path , const char * parameter_name ) const

Возвращает значение указанного параметра указанного runtime-файла, либо пустую строку, если такого параметра не существует.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.
- *const char ** **parameter_name** - Имя возвращаемого параметра.

### Возвращаемое значение

Значение указанного параметра, либо пустая строка, если такого параметра не существует.
## bool hasRuntimeParameter ( const UGUID & asset_guid , int index , const char * parameter_name ) const

Проверяет, есть ли у указанного runtime-файла указанный параметр.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, для runtime-файла которого проверяется параметр.
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя проверяемого параметра.

### Возвращаемое значение

true, если у runtime-файла есть указанный параметр; иначе false.
## bool hasRuntimeParameter ( const char * asset_path , int index , const char * parameter_name ) const

Проверяет, есть ли у указанного runtime-файла указанный параметр.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя проверяемого параметра.

### Возвращаемое значение

true, если у runtime-файла есть указанный параметр; иначе false.
## bool hasRuntimeParameter ( const UGUID & runtime_guid , const char * parameter_name ) const

Проверяет, есть ли у указанного runtime-файла указанный параметр.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.
- *const char ** **parameter_name** - Имя проверяемого параметра.

### Возвращаемое значение

true, если у runtime-файла есть указанный параметр; иначе false.
## bool hasRuntimeParameter ( const char * runtime_path , const char * parameter_name ) const

Проверяет, есть ли у указанного runtime-файла указанный параметр.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.
- *const char ** **parameter_name** - Имя проверяемого параметра.

### Возвращаемое значение

true, если у runtime-файла есть указанный параметр; иначе false.
## bool removeRuntimeParameter ( const UGUID & asset_guid , int index , const char * parameter_name ) const

Удаляет указанный параметр runtime-файла ассета с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **asset_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) файла ассета, для runtime-файла которого удаляется параметр.
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя удаляемого параметра.

### Возвращаемое значение

true, если указанный параметр runtime-файла успешно удалён; false, если такого параметра не существует.
## bool removeRuntimeParameter ( const char * asset_path , int index , const char * parameter_name ) const

Удаляет указанный параметр runtime-файла ассета с указанным путём.
### Аргументы

- *const char ** **asset_path** - Путь к [non-native asset](../../../editor2/assets_workflow/assets_runtimes.md).
- *int* **index** - Индекс сгенерированного runtime-файла в диапазоне от 0 до [total number of runtimes generated for the asset](#getNumRuntimes_cstr_int).
- *const char ** **parameter_name** - Имя удаляемого параметра.

### Возвращаемое значение

true, если указанный параметр runtime-файла успешно удалён; false, если такого параметра не существует.
## bool removeRuntimeParameter ( const UGUID & runtime_guid , const char * parameter_name ) const

Удаляет указанный параметр runtime-файла с указанным GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **runtime_guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) сгенерированного runtime-файла.
- *const char ** **parameter_name** - Имя удаляемого параметра.

### Возвращаемое значение

true, если указанный параметр runtime-файла успешно удалён; false, если такого параметра не существует.
## bool removeRuntimeParameter ( const char * runtime_path , const char * parameter_name ) const

Удаляет указанный параметр runtime-файла с указанным путём.
### Аргументы

- *const char ** **runtime_path** - Путь к сгенерированному runtime-файлу.
- *const char ** **parameter_name** - Имя удаляемого параметра.

### Возвращаемое значение

true, если указанный параметр runtime-файла успешно удалён; false, если такого параметра не существует.
