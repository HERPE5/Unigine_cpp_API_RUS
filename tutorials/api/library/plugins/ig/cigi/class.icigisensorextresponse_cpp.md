# CigiSensorExtResponse Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiIGPacket


## CigiSensorExtResponse Class

### Методы класса

---

## void setViewID ( int id )

Задаёт значение параметра **View ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **View ID**.

## void setEntityID ( int id )

Задаёт значение параметра **Entity ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **Entity ID**.

## void setSensorID ( int id )

Задаёт значение параметра **Sensor ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **Sensor ID**.

## void setEntityValid ( int valid )

Задаёт значение параметра **Entity Valid**, указываемое в пакете.
### Аргументы

- *int* **valid** - Значение параметра **Entity ID Valid**. Поддерживаются следующие значения:

  - 0 - недействительно (если отслеживаемая точка цели не является частью сущности)
  - 1 - действительно (если отслеживаемая точка цели является частью сущности)

## void setSensorStatus ( int status )

Задаёт значение параметра **Sensor Status**, указываемое в пакете.
### Аргументы

- *int* **status** - Значение параметра **Sensor Status**. Поддерживаются следующие значения:

  - 0 - Поиск цели
  - 1 - Слежение за целью
  - 2 - Приближающаяся потеря захвата
  - 3 - Потеря захвата

## void setGateSize ( const Math::ivec3& size )

Задаёт значения параметров, определяющих **Gate Size**, указываемых в пакете.
### Аргументы

- *const  Math::ivec3&* **size** - **Gate Sizes**, в пикселях: (X-size, Y-size). > **Notice:** Используются только первые два компонента вектора.

## void setGateOffset ( const Math::vec3& offset )

Задаёт значения параметров, определяющих **Gate Position**, указываемых в пакете.
### Аргументы

- *const  Math::vec3&* **offset** - Координаты **Gate Position**: (X-coordinate, Y-coordinate). > **Notice:** Используются только первые два компонента вектора.

## void setTrackPoint ( const Math::dvec3& point )

Задаёт значения параметров, определяющих **Track Point Coordinates**, указываемых в пакете.
### Аргументы

- *const  Math::dvec3&* **point** - Координаты точки слежения: (*Latitude, Longitude, Altitude*).

  - *Latitude* - [-90.0; 90.0] относительно экватора.
  - *Longitude* - [-180.0; 180.0] относительно нулевого меридиана.
  - *Altitude* - метры над средним уровнем моря.
