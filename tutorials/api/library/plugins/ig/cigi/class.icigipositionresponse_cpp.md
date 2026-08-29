# CigiPositionResponse Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiIGPacket


## CigiPositionResponse Class

### Методы класса

---

## void setObjectID ( int id )

Задаёт значение параметра **Object ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **Object ID**.

## void setPartID ( int id )

Задаёт значение параметра **Part ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **Part ID**.

## void setObjectClass ( int c )

Задаёт значение параметра **Object Class**, указываемое в пакете.
### Аргументы

- *int* **c** - Значение параметра **Object Class**. Поддерживаются следующие значения:

  - 0 - [Entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md).
  - 1 - [Articulated Part](../../../../../api/library/plugins/ig/api/class.articulatedpart_cpp.md).
  - 2 - [View](../../../../../api/library/plugins/ig/api/class.view_cpp.md).
  - 3 - [View Group](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md).
  - 4 - Трекер движения.

## void setCoordSystem ( int s )

Задаёт значение параметра **Coordinate System**, указываемое в пакете.
### Аргументы

- *int* **s** - Значение параметра **Coordinate System**. Поддерживаются следующие значения:

  - 0 - Геодезическая система координат.
  - 1 - Локальная система координат сущности
  - 2 - Локальная система координат субмодели

## void setPosition ( const Math::dvec3& p )

Задаёт значения параметров, определяющих **Position**, указываемых в пакете.
### Аргументы

- *const  Math::dvec3&* **p** - Координаты положения.

  - Для геодезической системы координат: (Lat, Lon, Alt)
  - Для локальных систем координат: (X-offset, Y-offset, Z-offset)

## void setRotation ( const Math::vec3& r )

Задаёт значения параметров, определяющих **Rotation**, указываемых в пакете.
### Аргументы

- *const  Math::vec3&* **r** - Углы Эйлера поворота: (Roll, Pitch, Yaw).
