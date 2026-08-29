# CigiTrajectoryDef Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiTrajectoryDef Class

### Методы класса

---

## int getEntityID ( ) const

Возвращает ID сущности, указанный в пакете.
### Возвращаемое значение

ID сущности.
## Math:: vec3 getAcceleration ( ) const

Возвращает координаты вектора ускорения, указанного в пакете.
### Возвращаемое значение

Вектор ускорения [entity](#getEntityID_int).
## float getRetardationRate ( ) const

Возвращает значение параметра **Retardation Rate**, указанное в пакете. Определяет величину ускорения, приложенного против вектора мгновенной линейной скорости сущности. Используется для симуляции сопротивления и других сил трения, действующих на [entity](#getEntityID_int).
### Возвращаемое значение

Значение параметра **Retardation Rate**.
## float getTerminalVelocity ( ) const

Возвращает значение параметра **Terminal Velocity**, указанное в пакете. Определяет максимальную скорость, которую может набрать сущность.
### Возвращаемое значение

Значение параметра **Terminal Velocity**.
