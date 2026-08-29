# Unigine::Plugins::IG::LightController Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


## LightController Class

### Методы класса

---

## void setEnabled ( const Ptr < Node > & parent_node , const char * path , bool enable )

Включает или отключает все источники света указанного родительского узла в заданной [category](../../../../../ig/light.md#lights_hierarchy).
### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../../api/library/nodes/class.node_cpp.md)> &* **parent_node** - Родительский узел включаемых источников света.
- *const char ** **path** - Категория источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *bool* **enable** - true, чтобы включить источники света, false, чтобы отключить.

## void setEnabled ( const char * path , bool enable )

Включает или отключает все источники света в заданной [category](../../../../../ig/light.md#lights_hierarchy).
### Аргументы

- *const char ** **path** - Категория источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *bool* **enable** - true, чтобы включить источники света, false, чтобы отключить.

## void setEnabled ( Unigine:: Vector <unsigned int> & hash_path , bool enable )

Включает или отключает все источники света в заданной [category](../../../../../ig/light.md#lights_hierarchy), используя её хеш.
> **Notice:** Переключение источников света с помощью хеша пути выполняется быстрее, чем с использованием категорий, поэтому рекомендуется к применению там, где это уместно.


### Аргументы

- *Unigine::[Vector](../../../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **hash_path** - Хеш категории источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *bool* **enable** - true, чтобы включить источники света, false, чтобы отключить.

## void setStrobed ( const char * path , bool enable )

Включает или отключает стробирование источников света в заданной [category](../../../../../ig/light.md#lights_hierarchy).
### Аргументы

- *const char ** **path** - Категория источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *bool* **enable** - true, чтобы включить стробирование, false, чтобы отключить.

## void setStrobed ( Unigine:: Vector <unsigned int> & hash_path , bool enable )

Включает или отключает стробирование источников света в заданной [category](../../../../../ig/light.md#lights_hierarchy), используя её хеш.
### Аргументы

- *Unigine::[Vector](../../../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **hash_path** - Хеш категории источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *bool* **enable** - true, чтобы включить стробирование, false, чтобы отключить.

## void setBright ( const char * path , float bright )

Задаёт интенсивность источников света в заданной [category](../../../../../ig/light.md#lights_hierarchy).
### Аргументы

- *const char ** **path** - Категория источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *float* **bright** - Значение интенсивности света в диапазоне [0.0f; 1.0f].

## void setBright ( Unigine:: Vector <unsigned int> & hash_path , float bright )

Задаёт интенсивность источников света в заданной [category](../../../../../ig/light.md#lights_hierarchy), используя её хеш.
### Аргументы

- *Unigine::[Vector](../../../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **hash_path** - Хеш категории источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *float* **bright** - Значение интенсивности света в диапазоне [0.0f; 1.0f].

## void getIndexPath ( const char * path , Unigine:: Vector <unsigned int> & ret_hash_path )

Заполняет массив данных вектора значениями хеша пути.
### Аргументы

- *const char ** **path** - Категория источников света в [lights hierarchy](../../../../../ig/light.md#lights_hierarchy).
- *Unigine::[Vector](../../../../../api/library/containers/vector/class.vector_cpp.md)<unsigned int> &* **ret_hash_path** - Указатель на массив, хранящий хеш пути.
