# CigiWeatherResponse Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>


## CigiWeatherResponse Class

### Методы класса

---

## void setRequestID ( int id )

Задаёт значение параметра **Request ID**, указываемое в пакете.
### Аргументы

- *int* **id** - Значение параметра **Request ID**.

## void setHumidity ( int h )

Задаёт значение параметра **Humidity**, указываемое в пакете.
### Аргументы

- *int* **h** - Значение параметра **Humidity** в диапазоне [0; 100].

## void setTemperature ( float t )

Задаёт значение параметра **Air Temperature**, указываемое в пакете.
### Аргументы

- *float* **t** - Значение параметра **Air Temperature**, в градусах Цельсия.

## void setVisibility ( float v )

Задаёт значение параметра **Visibility Range**, указываемое в пакете.
### Аргументы

- *float* **v** - Значение параметра **Visibility Range**.

## void setHorizontal ( float h )

Задаёт значение параметра **Horizontal Wind Speeed**, указываемое в пакете.
### Аргументы

- *float* **h** - Значение параметра **Horizontal Wind Speeed**.

## void setVertical ( float v )

Задаёт значение параметра **Vertical Wind Speeed**, указываемое в пакете.
### Аргументы

- *float* **v** - Значение параметра **Vertical Wind Speeed**.

## void setDirection ( float d )

Задаёт значение параметра **Wind Direction**, указываемое в пакете.
### Аргументы

- *float* **d** - Значение параметра **Wind Direction** в диапазоне [0; 360].

## void setPressure ( float p )

Задаёт значение параметра **Barometric Pressure**, указываемое в пакете.
### Аргументы

- *float* **p** - Значение параметра **Barometric Pressure**.
