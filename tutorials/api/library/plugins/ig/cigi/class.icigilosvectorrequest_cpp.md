# CigiLosVectorRequest Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiLosVectorRequest Class

### Методы класса

---

## int getLosID ( ) const

Возвращает LOS ID, указанный в пакете.
### Возвращаемое значение

LOS ID.
## int getEntityID ( ) const

Возвращает Entity ID, указанный в пакете.
### Возвращаемое значение

Entity ID.
> **Notice:** Этот параметр игнорируется, если [Source Point Coordinate System](#getSrcCoordSystem_int) установлен в Geodetic (0).


## int getRequestType ( ) const

Возвращает значение параметра **Request Type**, указанное в пакете. Определяет тип ответа, который IG вернёт на этот запрос.
### Возвращаемое значение

Значение параметра Request Type. Поддерживаются следующие значения:
- 0 - Basic. IG должен ответить пакетом [Line of Sight Response](../../../../../api/library/plugins/ig/cigi/class.icigilosresponse_cpp.md).
- 1 - Extended. IG должен ответить пакетом [Line of Sight Extended Response](../../../../../api/library/plugins/ig/cigi/class.icigilosextresponse_cpp.md).


## int getSrcCoordSystem ( ) const

Возвращает значение параметра **Source Point Coordinate System**, указанное в пакете. Этот параметр указывает систему координат, относительно которой задана исходная точка тестового вектора.
### Возвращаемое значение

Значение параметра Source Point Coordinate System. Поддерживаются следующие значения:
- 0 - Geodetic. Точка задаётся широтой, долготой и высотой. Вектор, заданный Azimuth и Elevation, задаётся относительно геодезической системы координат.
- 1 - Entity. The point shall be defined relative to the reference point of the entity specified by [Entity ID](#getEntityID_int). The vector shall also be specified relative to the entity’s coordinate system.


## int getRespCoordSystem ( ) const

Возвращает значение параметра **Response Coordinate System**, указанное в пакете. Этот параметр определяет систему координат, используемую в ответе.
### Возвращаемое значение

Значение параметра Response Coordinate System. Поддерживаются следующие значения:
- 0 - Geodetic. Точка пересечения сообщается как широта, долгота и высота.
- 1 - Entity. Точка пересечения сообщается как смещение XYZ относительно опорной точки пересечённой сущности.


## int getAlphaThreshold ( ) const

Возвращает значение параметра **Alpha Threshold**, указанное в пакете. Определяет минимальное значение alpha (т.е. минимальную непрозрачность) поверхности, при котором генерируется ответ LOS.
### Возвращаемое значение

Значение параметра Alpha Threshold.
## int getUpdatePeriod ( ) const

Возвращает значение параметра **Update Period**, указанное в пакете. Определяет интервал между последовательными ответами на этот запрос.
### Возвращаемое значение

Значение параметра Update Period. Поддерживаются следующие значения:
- 0 - Однократный запрос. IG вернёт единственный ответ.
- >0 - Указывает период обновления. Значение n>0 означает, что IG должен возвращать ответ каждый n-й кадр.


## int getMaterialMask ( ) const

Возвращает значение параметра **Material Mask**, указанное в пакете. Определяет природные и антропогенные объекты, учитываемые при проверке сегмента LOS.
### Возвращаемое значение

Значение параметра **Material Mask**. Каждый бит представляет диапазон кодов материалов; установка этого бита в единицу (1) приведёт к тому, что IG будет регистрировать пересечения с полигонами, коды материалов которых находятся в этом диапазоне.
> **Notice:** Диапазоны кодов материалов зависят от IG.


## float getAzimuth ( ) const

Возвращает значение параметра **Azimuth**, указанное в пакете. Определяет горизонтальный угол тестового вектора LOS.
### Возвращаемое значение

Значение параметра Azimuth в диапазоне **[-180.0; 180.0]**.
## float getElevation ( ) const

Возвращает значение параметра **Elevation**, указанное в пакете. Определяет вертикальный угол тестового вектора LOS.
### Возвращаемое значение

Значение параметра Elevation в диапазоне **[-90.0; 90.0]**.
## float getMinRange ( ) const

Возвращает значение параметра **Minimum Range**, указанное в пакете. Определяет минимальное расстояние вдоль тестового вектора LOS, начиная с которого выполняется проверка пересечения.
### Возвращаемое значение

Значение параметра Minimum Range, которое больше 0.
## float getMaxRange ( ) const

Возвращает значение параметра **Maximum Range**, указанное в пакете. Определяет максимальное расстояние вдоль тестового вектора LOS, на котором выполняется проверка пересечения.
### Возвращаемое значение

Значение параметра Maximum Range, которое больше значения параметра **Minimum Range**.
## Math:: dvec3 getPosition ( ) const

Возвращает положение Source Point, представленное трёхкомпонентным вектором значений параметров **Source Latitude, Source Longitude, Source Altitude** либо **Source X Offset, Source Y Offset, Source Z Offset**, указанных в пакете в соответствии со значением параметра [Source Point Coordinate System](#getSrcCoordSystem_int).
### Возвращаемое значение

Трёхкомпонентный вектор координат:
- [Latitude, Longitude, Altitude] - если Source Point Coordinate System установлен в Geodetic (0).
- [X Offset, Y Offset, Z Offset] - если Source Point Coordinate System установлен в Entity (1).
