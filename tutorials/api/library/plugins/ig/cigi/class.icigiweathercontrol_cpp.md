# CigiWeatherControl Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiWeatherControl Class

### Методы класса

---

## int getRegionID ( ) const

Возвращает ID экологического региона, указанный в пакете.
### Возвращаемое значение


- **Entity ID**, если [Scope](#getScope_int) установлен в Entity (2).
- **Region ID**, если [Scope](#getScope_int) установлен в Regional (1).


> **Notice:** Это значение будет игнорироваться, если [Scope](#getScope_int) установлен в Global (0).


## int getLayerID ( ) const

Возвращает ID слоя, указанный в пакете.
### Возвращаемое значение

ID слоя. Поддерживаются следующие значения:
- 0 - Ground Fog
- 1 - Cloud Layer 1
- 2 - Cloud Layer 2
- 3 - Cloud Layer 3
- 4 - Rain
- 5 - Snow
- 6 - Sleet
- 7 - Hail
- 8 - Sand
- 9 - Dust
- 10 – 255 - Определяется IG


## int getWeatherEnabled ( ) const

Возвращает значение параметра **Weather Enable**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Weather Enable**: 1, если слой погоды/сущность и её атмосферные эффекты включены; иначе 0.
## int getScudEnabled ( ) const

Возвращает значение параметра **Scud Enable**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Scud Enable**: 1, если слой погоды создаёт эффекты низкой облачности (scud) в своих переходных полосах; иначе 0.
## int getWindEnabled ( ) const

Возвращает значение параметра **Random Winds Enable**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Random Winds Enable**: 1, если к локальным эффектам ветра применяются случайная частота и длительность; иначе 0.
## int getLightingEnabled ( ) const

Возвращает значение параметра **Random Lightning Enable**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Random Lightning Enable**: 1, если слой погоды или сущность демонстрируют случайные эффекты молний; иначе 0.
> **Notice:** Частота и интенсивность молний изменяются в соответствии с параметром [Severity](#getSeverity_int)


## int getCloudType ( ) const

Возвращает значение параметра **Cloud Type**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Cloud Type**. Поддерживаются следующие значения:
- 0 - None
- 1 - Altocumulus
- 2 - Altostratus
- 3 - Cirrocumulus
- 4 - Cirrostratus
- 5 - Cirrus
- 6 - Cumulonimbus
- 7 - Cumulus
- 8 - Nimbostratus
- 9 - Stratocumulus
- 10 - Stratus
- 11 – 15 - Прочее


## int getScope ( ) const

Возвращает значение параметра **Scope**, указанное в пакете. Определяет, является ли погода глобальной, региональной или назначенной сущности.
### Возвращаемое значение

Значение параметра **Scope**. Поддерживаются следующие значения:
- 0 - Глобальная
- 1 - Региональная
- 2 - Сущности


## int getSeverity ( ) const

Возвращает значение параметра **Severity**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Severity**: 0 – 5 (от наименее к наиболее выраженному).
## int getHumidity ( ) const

Возвращает значение параметра **Humidity**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Humidity** в диапазоне [0; 100].
## float getTemperature ( ) const

Возвращает значение параметра **Air Temperature**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Air Temperature**, в градусах Цельсия.
## float getVisibility ( ) const

Возвращает значение параметра **Visibility Range**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Visibility Range**.
## float getScudFrequency ( ) const

Возвращает значение параметра **Scud Frequency**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Scud Frequency** в диапазоне [0; 100].
## float getCoverage ( ) const

Возвращает значение параметра **Coverage**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Coverage** в диапазоне [0; 100].
## float getElevation ( ) const

Возвращает значение параметра **Base Elevation**, указанное в пакете. Определяет высоту основания (низа) слоя погоды.
### Возвращаемое значение

Значение параметра **Base Elevation**.
## float getThickness ( ) const

Возвращает значение параметра **Thickness**, указанное в пакете. Определяет вертикальную толщину слоя погоды. Высота верхней границы слоя равна этому значению плюс значение, заданное параметром [Base Elevation](#getElevation_float).
### Возвращаемое значение

Значение параметра **Thickness**.
## float getWindSpeedHorizontal ( ) const

Возвращает значение параметра **Horizontal Wind Speeed**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Horizontal Wind Speeed**.
## float getWindSpeedVertical ( ) const

Возвращает значение параметра **Vertical Wind Speeed**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Vertical Wind Speeed**.
## float getWindDirection ( ) const

Возвращает значение параметра **Wind Direction**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Wind Direction** в диапазоне [0; 360].
## float getPressure ( ) const

Возвращает значение параметра **Barometric Pressure**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Barometric Pressure**.
## float getAerosol ( ) const

Возвращает значение параметра **Aerosol Concentration**, указанное в пакете. Определяет концентрацию воды, дыма, пыли или других частиц, взвешенных в воздухе.
> **Notice:** Этот параметр предоставляется в первую очередь для сенсорных приложений; любой визуальный эффект вторичен и зависит от IG и слоя.


### Возвращаемое значение

Значение параметра **Aerosol Concentration**.
## float getTransitionThicknessTop ( ) const

Возвращает толщину верхней **Transition Band**, указанную в пакете.
### Возвращаемое значение

Толщина верхней **Transition Band**, в метрах.
## float getTransitionThicknessBottom ( ) const

Возвращает толщину нижней **Transition Band**, указанную в пакете.
### Возвращаемое значение

Толщина нижней **Transition Band**, в метрах.
