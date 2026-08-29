# CigiHatHotRequest Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiHatHotRequest Class

### Методы класса

---

## int getHatHotID ( ) const

Возвращает значение параметра **HAT/HOT ID**, указанное в пакете.
### Возвращаемое значение

Значение параметра **HAT/HOT ID**.
## int getEntityID ( ) const

Возвращает ID сущности, указанный в пакете.
### Возвращаемое значение

ID сущности.
## int getRequestType ( ) const

Возвращает значение параметра **Request Type**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Request Type**. Поддерживаются следующие значения:
- 0 - HAT
- 1 - HOT
- 2 - Расширенный


## int getCoordSystem ( ) const

Возвращает значение параметра **Coordinate System**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Coordinate System**. Поддерживаются следующие значения:
- 0 - Геодезическая
- 1 - Сущности


## int getUpdatePeriod ( ) const

Возвращает значение параметра **Update Period**, указанное в пакете. Определяет интервал между последовательными ответами на этот запрос.
### Возвращаемое значение

Значение параметра **Update Period**:
- 0 - Однократный запрос
- > 0 - период обновления


## Math:: dvec3 getPosition ( ) const

Возвращает координаты точки, из которой выполняется запрос HAT/HOT.
### Возвращаемое значение

Координаты точки, из которой выполняется запрос HAT/HOT.
