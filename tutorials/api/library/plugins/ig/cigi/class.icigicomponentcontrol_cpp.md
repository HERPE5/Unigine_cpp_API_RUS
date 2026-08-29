# CigiComponentControl Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiComponentControl Class

### Перечисления

## CIGI_COMPONENT

| Name | Description |
|---|---|
| **CIGI_COMPONENT_ENTITY** = 0 | Класс компонента Entity. |
| **CIGI_COMPONENT_VIEW** = 1 | Класс компонента View. |
| **CIGI_COMPONENT_GROUP** = 2 | Класс компонента View Group. |
| **CIGI_COMPONENT_SENSOR** = 3 | Класс компонента Sensor. |
| **CIGI_COMPONENT_REG_WATER** = 4 | Класс компонента Regional Water. |
| **CIGI_COMPONENT_REG_TERRAIN** = 5 | Класс компонента Regional Terrain. |
| **CIGI_COMPONENT_REG_WEATHER** = 6 | Класс компонента Regional Weather. |
| **CIGI_COMPONENT_GLOBAL_WATER** = 7 | Класс компонента Global Water. |
| **CIGI_COMPONENT_GLOBAL_TERRAIN** = 8 | Класс компонента Global Terrain. |
| **CIGI_COMPONENT_GLOBAL_WEATHER** = 9 | Класс компонента Global Weather. |
| **CIGI_COMPONENT_ATMOSPHERE** = 10 | Класс компонента Atmosphere. |
| **CIGI_COMPONENT_CELESTIAL** = 11 | Класс компонента Celestial. |
| **CIGI_COMPONENT_EVENT** = 12 | Класс компонента Event. |
| **CIGI_COMPONENT_SYSTEM** = 13 | Класс компонента System. |
| **CIGI_COMPONENT_SYMBOL_SURFACE** = 14 | Класс компонента Symbol Surface. |
| **CIGI_COMPONENT_SYMBOL** = 15 | Класс компонента Symbol. |

### Методы класса

---

## int getInstanceID ( ) const

Возвращает ID экземпляра, указанный в пакете.
### Возвращаемое значение

ID экземпляра.
## int getComponentID ( ) const

Возвращает ID компонента, указанный в пакете.
### Возвращаемое значение

ID компонента.
## int getComponentClass ( ) const

Возвращает класс компонента, указанный в пакете.
### Возвращаемое значение

Класс компонента CIGI. Одно из значений [CIGI_COMPONENT_*](#CIGI_COMPONENT_ENTITY).
## int getComponentState ( ) const

Возвращает значение параметра **Component State**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Component State**. Одно из значений [CIGI_STATE_*](../../../../../api/library/plugins/ig/cigi/class.cigi_connector_cpp.md#CIGI_STATE_DISABLED).
## unsigned int getData1 ( ) const

Возвращает значение параметра **Data 1**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Data 1**.
## unsigned int getData2 ( ) const

Возвращает значение параметра **Data 2**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Data 2**.
## unsigned int getData3 ( ) const

Возвращает значение параметра **Data 3**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Data 3**.
## unsigned int getData4 ( ) const

Возвращает значение параметра **Data 4**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Data 4**.
## unsigned int getData5 ( ) const

Возвращает значение параметра **Data 5**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Data 5**.
## unsigned int getData6 ( ) const

Возвращает значение параметра **Data 6**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Data 6**.
