# Unigine::Plugins::IG::Component Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот класс представляет интерфейс Component IG.

> **Notice:** Плагин IG должен быть загружен.


## Component Class

### Перечисления

## COMPONENT_TYPE

| Name | Description |
|---|---|
| **COMPONENT_TYPE_ENTITY** = 0 | Класс компонента Entity. |
| **COMPONENT_TYPE_VIEW** = 1 | Класс компонента View. |
| **COMPONENT_TYPE_GROUP** = 2 | Класс компонента View Group. |
| **COMPONENT_TYPE_SENSOR** = 3 | Класс компонента Sensor. |
| **COMPONENT_TYPE_REG_WATER** = 4 | Класс компонента Regional Water. |
| **COMPONENT_TYPE_REG_TERRAIN** = 5 | Класс компонента Regional Terrain. |
| **COMPONENT_TYPE_REG_WEATHER** = 6 | Класс компонента Regional Weather. |
| **COMPONENT_TYPE_GLOBAL_WATER** = 7 | Класс компонента Global Water. |
| **COMPONENT_TYPE_GLOBAL_TERRAIN** = 8 | Класс компонента Global Terrain. |
| **COMPONENT_TYPE_GLOBAL_WEATHER** = 9 | Класс компонента Global Weather. |
| **COMPONENT_TYPE_ATMOSPHERE** = 10 | Класс компонента Atmosphere. |
| **COMPONENT_TYPE_CELESTIAL** = 11 | Класс компонента Celestial. |
| **COMPONENT_TYPE_EVENT** = 12 | Класс компонента Event. |
| **COMPONENT_TYPE_SYSTEM** = 13 | Класс компонента System. |
| **COMPONENT_TYPE_SYMBOL_SURFACE** = 14 | Класс компонента Symbol Surface. |
| **COMPONENT_TYPE_SYMBOL** = 15 | Класс компонента Symbol. |

### Методы класса

---

## int getID ( ) const

Возвращает ID компонента.
### Возвращаемое значение

ID компонента.
## Component::COMPONENT_TYPE getComponentType ( )

Возвращает класс компонента.
### Возвращаемое значение

Класс компонента CIGI.
## int64_t getInstanceID ( )

Возвращает ID экземпляра.
### Возвращаемое значение

ID экземпляра.
## Ptr < Node > getNode ( ) const

Возвращает узел, назначенный компоненту.
### Возвращаемое значение

Узел, назначенный компоненту.
## Ptr < Property > getProperty ( ) const

Возвращает узел, назначенный компоненту.
### Возвращаемое значение

Свойство, назначенное компоненту.
## void setParameterData ( const char * name , const void * value )

Задаёт данные параметра компонента с указанным именем.
### Аргументы

- *const char ** **name** - Имя параметра.
- *const void ** **value** - Указатель на буфер с задаваемыми данными параметра.

## void setParameterInt ( const char * name , int value )

Задаёт значение параметра компонента с указанным именем, используя указанное целочисленное значение.
### Аргументы

- *const char ** **name** - Имя параметра.
- *int* **value** - Задаваемое значение.

## int getParameterInt ( const char * name )

Возвращает текущее значение параметра с указанным именем.
### Аргументы

- *const char ** **name** - Имя параметра.

### Возвращаемое значение

Текущее значение параметра с указанным именем.
## void setParameterFloat ( const char * name , float value )

Задаёт значение float-параметра компонента с указанным именем, используя указанное значение с плавающей точкой.
### Аргументы

- *const char ** **name** - Имя параметра.
- *float* **value** - Задаваемое значение.

## float getParameterFloat ( const char * name )

Возвращает текущее значение float-параметра с указанным именем.
### Аргументы

- *const char ** **name** - Имя параметра.

### Возвращаемое значение

Текущее значение float-параметра с указанным именем.
## void setParameterDouble ( const char * name , double value )

Задаёт значение параметра компонента с указанным именем, используя указанное значение double.
### Аргументы

- *const char ** **name** - Имя параметра.
- *double* **value** - Задаваемое значение.

## double getParameterDouble ( const char * name )

Возвращает текущее значение double-параметра с указанным именем.
### Аргументы

- *const char ** **name** - Имя параметра.

### Возвращаемое значение

Текущее значение double-параметра с указанным именем.
