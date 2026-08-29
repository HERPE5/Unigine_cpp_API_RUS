# Unigine::Plugins::DataBridge::Manager Class (CPP)

**Header:** #include <plugins/Unigine/DataBridge/UnigineDataBridge.h>

> **Notice:** Этот класс является синглтоном.


Этот класс управляет плагином DataBridge и предоставляет доступ к переменным.


## Manager Class

### Методы класса

---

## NetworkManager * getNetworkManager ( )

Возвращает интерфейс Network Manager.
### Возвращаемое значение

Указатель на интерфейс Network Manager.
## DataBridgeUI * getDataBridgeUI ( )

Возвращает пользовательский интерфейс DataBridge.
### Возвращаемое значение

Указатель на DataBridge UI.
## DBVariable * getVariable ( const char * path )

Возвращает переменную DataBridge по её пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Указатель на переменную DataBridge.
## DBVariable * getVariable ( unsigned long long id )

Возвращает переменную DataBridge по её ID.
### Аргументы

- *unsigned long long* **id** - ID переменной.

### Возвращаемое значение

Указатель на переменную DataBridge.
## DBVariable * getRootVariable ( ) const

Возвращает корневую переменную.
### Возвращаемое значение

Указатель на переменную DataBridge.
## DBVariable * createVariable ( const char * path , unsigned long long id )

Возвращает переменную, созданную с указанными аргументами.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *unsigned long long* **id** - ID переменной.

### Возвращаемое значение

Указатель на переменную DataBridge.
## void queueVariableToRemove ( const char * path )

Помечает переменную по указанному пути для удаления.
### Аргументы

- *const char ** **path** - Путь к переменной.

## void queueVariableToRemove ( unsigned long long id )

Помечает переменную с указанным ID для удаления.
### Аргументы

- *unsigned long long* **id** - ID переменной.

## void queueVariableToRemove ( DBVariable * OUT_var )

Помечает переменную для удаления.
### Аргументы

- *[DBVariable](../../../../api/library/plugins/databridge/class.dbvariable_cpp.md) ** **OUT_var** - Переменная DataBridge. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void removeQueuedVariables ( )

Удаляет все переменные, помеченные для удаления методом **queueVariableToRemove**.
## void setVariableInt32 ( const char * path , int val )

Задаёт целочисленное значение переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *int* **val** - Целочисленное значение.

## void setVariableUInt32 ( const char * path , unsigned int val )

Задаёт беззнаковое целочисленное значение переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *unsigned int* **val** - Беззнаковое целочисленное значение.

## void setVariableInt64 ( const char * path , long long val )

Задаёт значение long long переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *long long* **val** - Значение long long.

## void setVariableUInt64 ( const char * path , unsigned long long val )

Задаёт значение unsigned long long переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *unsigned long long* **val** - Значение unsigned long long.

## void setVariableFloat32 ( const char * path , float val )

Задаёт значение с плавающей точкой переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *float* **val** - Значение с плавающей точкой.

## void setVariableFloat64 ( const char * path , double val )

Задаёт значение double переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *double* **val** - Значение double.

## void setVariableString ( const char * path , const char * val )

Задаёт строковое значение переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *const char ** **val** - Строковое значение.

## void setVariableBlob ( const char * path , Ptr < Blob > & val )

Задаёт значение blob переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.
- *[Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Blob](../../../../api/library/common/class.blob_cpp.md)> &* **val** - Значение blob.

## int getVariableInt32 ( const char * path )

Возвращает целочисленное значение, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Целочисленное значение.
## unsigned int getVariableUInt32 ( const char * path )

Возвращает беззнаковое целочисленное значение, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Беззнаковое целочисленное значение.
## long long getVariableInt64 ( const char * path )

Возвращает значение long long, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Значение long long.
## unsigned long long getVariableUInt64 ( const char * path )

Возвращает значение unsigned long long, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Значение unsigned long long.
## float getVariableFloat32 ( const char * path )

Возвращает значение с плавающей точкой, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Значение с плавающей точкой.
## double getVariableFloat64 ( const char * path )

Возвращает значение double, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Значение double.
## String getVariableString ( const char * path )

Возвращает строковое значение, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Строковое значение.
## Ptr < Blob > getVariableBlob ( const char * path )

Возвращает значение blob, заданное для переменной по указанному пути.
### Аргументы

- *const char ** **path** - Путь к переменной.

### Возвращаемое значение

Значение blob.
