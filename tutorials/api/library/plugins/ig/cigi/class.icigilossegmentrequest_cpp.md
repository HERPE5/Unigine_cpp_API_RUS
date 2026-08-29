# CigiLosSegmentRequest Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiLosSegmentRequest Class

### Методы класса

---

## int getLosID ( ) const

Возвращает LOS ID, указанный в пакете.
### Возвращаемое значение

LOS ID.
## int getSrcEntityID ( ) const

Возвращает Source Entity ID, указанный в пакете.
### Возвращаемое значение

Source Entity ID.
## int getDestEntityID ( ) const

Возвращает значение параметра **Destination Entity ID**, указанное в пакете. Определяет сущность, относительно которой заданы конечные точки тестового сегмента.
### Возвращаемое значение

Destination Entity ID.
## int getRequestType ( ) const

Возвращает значение параметра **Request Type**, указанное в пакете. Определяет тип ответа, который IG вернёт на этот запрос.
### Возвращаемое значение

Значение параметра **Request Type**. Поддерживаются следующие значения:
- 0 - Basic. IG должен ответить пакетом [**Line of Sight Response**](../../../../../api/library/plugins/ig/cigi/class.icigilosresponse_cpp.md).
- 1 - Extended. IG должен ответить пакетом [**Line of Sight Extended Response**](../../../../../api/library/plugins/ig/cigi/class.icigilosextresponse_cpp.md).


## int getSrcCoordSystem ( ) const

Возвращает значение параметра **Source Point Coordinate System**, указанное в пакете. Указывает систему координат, относительно которой задана начальная точка тестового сегмента.
### Возвращаемое значение

Значение параметра Source Point Coordinate System. Поддерживаются следующие значения:
- 0 - Geodetic. Точка задаётся широтой, долготой и высотой.
- 1 - Entity. Точка задаётся относительно опорной точки сущности, указанной [Entity ID](#getSrcEntityID_int).


## int getDestCoordSystem ( ) const

Возвращает значение параметра **Destination Point Coordinate System**, указанное в пакете. Указывает систему координат, относительно которой задана конечная точка тестового сегмента.
### Возвращаемое значение

Значение параметра Destination Point Coordinate System. Поддерживаются следующие значения:
- 0 - Geodetic. Конечная точка задаётся широтой, долготой и высотой.
- 1 - Entity. Возможны два случая:

  1. Если [**Destination Entity ID Valid**](#getDestEntityValid_int) установлен в Not Valid (0), конечная точка задаётся относительно опорной точки сущности, указанной [Source Entity ID](#getSrcEntityID_int).
  2. Если [**Destination Entity ID Valid**](#getDestEntityValid_int) установлен в Valid (1), конечная точка задаётся относительно опорной точки сущности, указанной [Destination Entity ID](#getDestEntityID_int).


## int getRespCoordSystem ( ) const

Возвращает значение параметра **Response Coordinate System**, указанное в пакете. Это значение определяет систему координат, используемую в ответе.
### Возвращаемое значение

Значение параметра Response Coordinate System. Поддерживаются следующие значения:
- 0 - Geodetic. Точка пересечения сообщается как широта, долгота и высота.
- 1 - Entity. Точка пересечения задаётся относительно опорной точки пересечённой сущности.


## int getDestEntityValid ( ) const

Возвращает значение параметра **Destination Entity ID Valid**, указанное в пакете. Определяет, содержит ли параметр [Destination Entity ID](#getDestEntityID_int) действительный ID сущности.
### Возвращаемое значение

Значение параметра действительности сущности назначения. Поддерживаются следующие значения:
- 0 - Not Valid. Конечная точка назначения задаётся относительно исходной сущности (указанной [Source Entity ID](#getSrcEntityID_int)) либо геодезической системы координат, в зависимости от значения параметра [Destination Point Coordinate System](#getDestCoordSystem_int).
- 1 - Valid. Конечная точка назначения задаётся относительно сущности, указанной [Destination Entity ID](#getDestEntityID_int), только если [Destination Point Coordinate System](#getDestCoordSystem_int) установлен в Entity (1).


## int getAlphaThreshold ( ) const

Возвращает значение параметра **Alpha Threshold**, указанное в пакете. Определяет минимальное значение alpha (т.е. минимальную непрозрачность) поверхности, при котором генерируется ответ LOS.
### Возвращаемое значение

Значение параметра Alpha Threshold.
## int getUpdatePeriod ( ) const

Возвращает значение параметра **Update Period**, указанное в пакете. Определяет интервал между последовательными ответами на этот запрос.
### Возвращаемое значение

Значение параметра Update Period. Поддерживаются следующие значения:
- 0 - Однократный запрос.
- >0 - период обновления. Значение n>0 указывает, что IG должен возвращать ответ каждый n-й кадр.


## int getMaterialMask ( ) const

Возвращает значение параметра **Material Mask**, указанное в пакете. Определяет природные и антропогенные объекты, учитываемые при проверке сегмента LOS.
### Возвращаемое значение

Значение параметра Material Mask. Каждый бит представляет диапазон кодов материалов; установка этого бита в единицу (1) приведёт к тому, что IG будет регистрировать пересечения с полигонами, коды материалов которых находятся в этом диапазоне.
> **Notice:** Диапазоны кодов материалов зависят от IG.


## Math:: dvec3 getSrcPosition ( ) const

Возвращает положение Source Point, представленное трёхкомпонентным вектором значений параметров **Source Latitude, Source Longitude, Source Altitude** либо **Source X Offset, Source Y Offset, Source Z Offset**, указанных в пакете в соответствии со значением параметра [Source Point Coordinate System](#getSrcCoordSystem_int).
### Возвращаемое значение

Трёхкомпонентный вектор, задающий положение Source Point. Поддерживаются следующие значения:
- [Latitude, Longitude, Altitude] - если Source Point Coordinate System установлен в Geodetic (0).
- [X Offset, Y Offset, Z Offset] - если Source Point Coordinate System установлен в Entity (1).


## Math:: dvec3 getDestPosition ( ) const

Возвращает положение Destination Point, представленное трёхкомпонентным вектором значений параметров **Destination Latitude, Destination Longitude, Destination Altitude** либо **Destination X Offset, Destination Y Offset, Destination Z Offset**, указанных в пакете в соответствии со значением параметра [Destination Point Coordinate System](#getDestCoordSystem_int).
### Возвращаемое значение

Трёхкомпонентный вектор, задающий положение Destination Point. Поддерживаются следующие значения:
- [Latitude, Longitude, Altitude] - если Destination Point Coordinate System установлен в Geodetic (0).
- [X Offset, Y Offset, Z Offset] - если Destination Point Coordinate System установлен в Entity (1). Это смещение может быть задано относительно исходной сущности либо сущности назначения, в зависимости от значения флага Destination Entity ID Valid.
