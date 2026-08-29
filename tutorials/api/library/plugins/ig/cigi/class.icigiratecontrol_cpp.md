# CigiRateControl Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiRateControl Class

### Методы класса

---

## int getEntityID ( ) const

Возвращает ID сущности, указанный в пакете.
### Возвращаемое значение

ID сущности.
## int getPartID ( ) const

Возвращает ID сочленённой части, указанный в пакете.
### Возвращаемое значение

ID сочленённой части.
## int getToPart ( ) const

Возвращает значение параметра **Aply to Articulated Part**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Aply to Articulated Part**: 1 - скорость, указанная в пакете, применяется к сочленённой части; 0 - скорость, указанная в пакете, применяется к сущности.
## int getLocal ( ) const

Возвращает значение параметра **Coordinate System**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Coordinate System**: 1 - Local; 0 - World/Parent.
## Math:: vec3 getLinear ( ) const

Возвращает вектор линейной скорости, указанный в пакете.
### Возвращаемое значение

Вектор линейной скорости.
## Math:: vec3 getAngular ( ) const

Возвращает вектор угловой скорости, указанный в пакете.
### Возвращаемое значение

Вектор угловой скорости.
