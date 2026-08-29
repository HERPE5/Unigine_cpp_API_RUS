# CigiAtmosphereControl Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiAtmosphereControl Class

### Методы класса

---

## int getModelEnabled ( ) const

Возвращает значение параметра **Atmospheric Model Enable**, указанное в пакете.
### Возвращаемое значение

Параметр **Atmospheric Model Enable**: 1, если IG будет использовать атмосферную модель для определения спектральных яркостей в сенсорных приложениях; иначе 0.
## int getHumidity ( ) const

Возвращает значение параметра **Global Humidity**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Global Humidity** в диапазоне [0; 100].
## float getTemperature ( ) const

Возвращает значение параметра **Global Air Temperature**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Global Air Temperature**, в градусах Цельсия.
## float getVisibility ( ) const

Возвращает значение параметра **Global Visibility Range**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Global Visibility Range**.
## float getWindSpeedHorizontal ( ) const

Возвращает значение параметра **Global Horizontal Wind Speeed**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Global Horizontal Wind Speeed**.
## float getWindSpeedVertical ( ) const

Возвращает значение параметра **Global Vertical Wind Speeed**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Global Vertical Wind Speeed**.
## float getWindDirection ( ) const

Возвращает значение параметра **Global Wind Direction**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Global Wind Direction** в диапазоне [0; 360].
## float getPressure ( ) const

Возвращает значение параметра **Global Barometric Pressure**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Global Barometric Pressure**.
