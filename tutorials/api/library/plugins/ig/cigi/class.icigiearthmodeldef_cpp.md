# CigiEarthModelDef Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiEarthModelDef Class

### Методы класса

---

## int getCustomEnabled ( ) const

Возвращает значение параметра **Custom ERM Enable**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Custom ERM Enable**: 1 - IG должен использовать значения [Equatorial Radius](#getRadius_double) и [Flattening](#getFlattening_double) для описания эллипсоида; 0 - IG должен использовать эталонную модель **WGS 84**, и все остальные параметры этого пакета должны игнорироваться.
## double getRadius ( ) const

Возвращает значение параметра **Equatorial Radius**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Equatorial Radius**. Определяет большую полуось эллипсоида.
## double getFlattening ( ) const

Возвращает значение параметра **Flattening**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Flattening**. Определяет сжатие эллипсоида.
