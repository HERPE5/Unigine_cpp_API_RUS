# CigiSensorResponse Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiIGPacket


## CigiSensorResponse Class

### Методы класса

---

## void setViewID ( int id )

Задаёт значение параметра **View ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **View ID**.

## void setSensorID ( int id )

Задаёт значение параметра **Sensor ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **Sensor ID**.

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
