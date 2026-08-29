# Unigine::Plugins::IG::IGConfig Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот класс используется для управления [IG configuration](../../../../../ig/config.md) через API.

> **Notice:** Плагин IG должен быть загружен.


Структура **CloudTypeDef** представляет определения [cloud type](../../../../../ig/weather/config.md#config_cloud_types). Она объявляется следующим образом:


```cpp
struct CloudTypeDef
{
	int type = 0;
	Unigine::String name;
	Unigine::String material;
};

```


Структура **PrecipitationTypeDef** представляет определения [precipitation type](../../../../../ig/weather/config.md#config_precipitation_types). Она объявляется следующим образом:


```cpp
struct PrecipitationTypeDef
{
	int type = 0;
	Unigine::String name;
	Unigine::String far_node_path;
	Unigine::String near_node_path;
};

```


Структура **SynckerChannelDef** представляет определения каналов Syncker. Она объявляется следующим образом:


```cpp
struct SynckerChannelDef
{
	Unigine::String slave_name;
	int view_id = 0;
	bool use_projection = false;
};

```


Структура **DatabaseDef** представляет определения [database](../../../../../ig/config.md#config_databases). Она объявляется следующим образом:


```cpp
struct DatabaseDef
{
	int database_id = 0;
	Unigine::String world_name;
	Unigine::Math::Vec3 geodetic_origin;
};

```


Структура **ViewTypeDef** представляет определения [view type](../../../../../ig/config.md#config_view_types). Она объявляется следующим образом:


```cpp
struct ViewTypeDef
{
	int view_type_id = 0;
	Unigine::String post_material;
};

```


Структура **EntityTypeDef** представляет определения [entity type](../../../../../ig/config.md#config_entities) с компонентами, сочленёнными частями и объёмами. Она объявляется следующим образом:


```cpp
struct EntityTypeDef
{
	int64_t id = 0;
	Unigine::String name;
	Unigine::String path;
	int64_t inherit_id = 0;

	struct ComponentDef
	{
		struct ComponentParameterDef
		{
			ITEM_TYPE type = ITEM_TYPE::UNKNOWN;
			Unigine::String name;
			Unigine::String parameter_name;
		};
		bool inherited = false;
		int id = 0;
		Unigine::String name;
		Unigine::String node_path;
		Unigine::String property_name;
		Unigine::Vector<ComponentParameterDef> parameters;
	};
	Unigine::Map<int, ComponentDef> components;

	struct ArticulatedPartDef
	{
		bool inherited = false;
		int id = 0;
		Unigine::String name;
		Unigine::Vector<Unigine::String> node_path;
		Unigine::Vector<Unigine::Math::ivec3> is_inverted;
	};
	Unigine::Map<int, ArticulatedPartDef> articulated_parts;

	struct VolumeDef
	{
		bool inherited = false;
		int id = 0;
		int shape_id = 0;
		Unigine::String node_path;
		Unigine::String name;
	};
	Unigine::Map<int, VolumeDef> volume_definitions;
};

```


## IGConfig Class

### Перечисления

## ITEM_TYPE

| Name | Description |
|---|---|
| **ITEM_TYPE_UNKNOWN** = 0 | Тип параметра не определён. |
| **ITEM_TYPE_INT** = 1 | Тип параметра — целочисленный. |
| **ITEM_TYPE_FLOAT** = 2 | Тип параметра — float. |
| **ITEM_TYPE_DOUBLE** = 3 | Тип параметра — double. |
| **ITEM_TYPE_STRING** = 4 | Тип параметра — строка. |

### Методы класса

---

## void setValue ( const char * name , int value )

Задаёт значение указанного параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **value** - Задаваемое целочисленное значение.

## void setValue ( const char * name , float value )

Задаёт значение указанного параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *float* **value** - Задаваемое значение float.

## void setValue ( const char * name , const char * value )

Задаёт значение указанного параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const char ** **value** - Задаваемое строковое значение.

## void setValue ( const char * name , double value )

Задаёт значение указанного параметра.
### Аргументы

- *const char ** **name** - Имя параметра.
- *double* **value** - Значение параметра.

## int getValue ( const char * name , int default_value ) const

Возвращает значение указанного параметра. Если этот параметр не был задан в файле [ig_config.xml](../../../../../ig/config.md), для параметра устанавливается default_value.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **default_value** - Значение, устанавливаемое, если параметр не задан в файле [ig_config.xml](../../../../../ig/config.md).

### Возвращаемое значение

Значение параметра.
## float getValue ( const char * name , float default_value ) const

Возвращает значение указанного параметра. Если этот параметр не был задан в файле [ig_config.xml](../../../../../ig/config.md), для параметра устанавливается default_value.
### Аргументы

- *const char ** **name** - Имя параметра.
- *float* **default_value** - Значение, устанавливаемое, если параметр не задан в файле [ig_config.xml](../../../../../ig/config.md).

### Возвращаемое значение

Значение параметра.
## String getValue ( const char * name , const char * default_value ) const

Возвращает значение указанного параметра. Если этот параметр не был задан в файле [ig_config.xml](../../../../../ig/config.md), для параметра устанавливается default_value.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const char ** **default_value** - Значение, устанавливаемое, если параметр не задан в файле [ig_config.xml](../../../../../ig/config.md).

### Возвращаемое значение

Значение параметра.
## double getValue ( const char * name , double default_value ) const

Возвращает значение указанного параметра. Если этот параметр не был задан в файле [ig_config.xml](../../../../../ig/config.md), для параметра устанавливается default_value.
### Аргументы

- *const char ** **name** - Имя параметра.
- *double* **default_value** - Значение, устанавливаемое, если параметр не задан в файле [ig_config.xml](../../../../../ig/config.md).

### Возвращаемое значение

Значение параметра.
## const String & getPath ( ) const

Возвращает путь к текущему файлу [ig_config.xml](../../../../../ig/config.md).
### Возвращаемое значение

Путь к файлу [ig_config.xml](../../../../../ig/config.md).
## bool load ( const char * filename = "ig_config.xml" )

Загружает конфигурацию IG из файла с указанным именем.
### Аргументы

- *const char ** **filename** - Путь к [IG configuration file](../../../../../ig/config.md).

### Возвращаемое значение

**true**, если конфигурация IG успешно загружена из указанного файла; иначе **false**.
## bool save ( const char * filename )

Сохраняет конфигурацию IG в указанный файл.
### Аргументы

- *const char ** **filename** - Путь к файлу, в который сохраняется конфигурация IG.

### Возвращаемое значение

**true**, если конфигурация IG успешно сохранена в указанный файл; иначе **false**.
## bool save ( )

Сохраняет конфигурацию IG в текущий файл.
### Возвращаемое значение

**true**, если конфигурация IG успешно сохранена; иначе **false**.
## bool reload ( )

Перезагружает конфигурацию IG.
### Возвращаемое значение

**true**, если конфигурация IG успешно перезагружена; иначе **false**.
## void removeVariable ( const char * name )

Удаляет указанную переменную из файла конфигурации.
### Аргументы

- *const char ** **name** - Имя удаляемой переменной.

## bool isVariableExist ( const char * name ) const

Возвращает значение, указывающее, существует ли переменная с указанным именем.
### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

**true**, если переменная с указанным именем существует; иначе **false**.
## const Unigine:: HashMap < Unigine:: String , int64_t> & getEntityTypeNames ( ) const

Возвращает список доступных имён типов (type_name -> type_id).
### Возвращаемое значение

Список доступных имён типов (type_name -> type_id).
## Unigine:: HashMap <int64_t, EntityTypeDef> & getEntityTypes ( )

Возвращает список доступных типов (type_id -> EntityTypeDef).
### Возвращаемое значение

Список доступных типов (type_id -> EntityTypeDef).
## Unigine:: HashMap <int, DatabaseDef> & getDatabases ( )

Возвращает список доступных миров (id -> DatabaseDef).
### Возвращаемое значение

Список доступных миров (id -> DatabaseDef).
## Unigine:: HashMap <int, ViewTypeDef> & getViewTypes ( )

Возвращает список доступных постэффектов камеры (id -> ViewTypeDef).
### Возвращаемое значение

Список доступных постэффектов камеры (id -> ViewTypeDef).
## Unigine:: HashMap <int, CloudTypeDef> & getCloudTypes ( )

Возвращает список доступных типов облаков (id -> CloudTypeDef).
### Возвращаемое значение

Список доступных типов облаков (id -> CloudTypeDef).
## Unigine:: HashMap <int, SynckerChannelDef> & getSynckerChannels ( )

Возвращает список доступных каналов Syncker (id -> SynckerChannelDef).
### Возвращаемое значение

Список доступных каналов Syncker (id -> SynckerChannelDef).
## Unigine:: HashMap <int, PrecipitationTypeDef> & getPrecipitationTypes ( )

Возвращает список доступных типов осадков (id -> PrecipitationTypeDef).
### Возвращаемое значение

Список доступных типов осадков (id -> PrecipitationTypeDef).
