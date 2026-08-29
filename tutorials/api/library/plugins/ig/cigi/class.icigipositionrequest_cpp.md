# CigiPositionRequest Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiPositionRequest Class

### Методы класса

---

## int getObjectID ( ) const

Возвращает Object ID, указанный в пакете.
### Возвращаемое значение

Object ID. Поддерживаются следующие диапазоны значений в зависимости от [Object Class](#getObjectClass_int):
- [0; 65535] - Если Object Class в диапазоне [0; 2].
- [1; 255] - Если Object Class=3.
- [0; 255] - Если Object Class=4.


## int getPartID ( ) const

Возвращает значение параметра **Articulated Part ID**, указанное в пакете. Идентифицирует сочленённую часть, положение которой запрашивается.
### Возвращаемое значение

Articulated Part ID.
## int getUpdateMode ( ) const

Возвращает значение параметра **Update Mode**, указанное в пакете. Определяет, будет ли IG сообщать положение запрашиваемого объекта каждый кадр.
### Возвращаемое значение

Значение параметра Update Mode. Поддерживаются следующие значения:
- 0 - Однократно.
- 1 - Непрерывно.


## int getObjectClass ( ) const

Возвращает значение параметра **Object Class**, указанное в пакете. Указывает тип объекта, положение которого запрашивается.
### Возвращаемое значение

Значение параметра Object Class. Поддерживаются следующие значения:
- 0 - [Entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md).
- 1 - [Articulated Part](../../../../../api/library/plugins/ig/api/class.articulatedpart_cpp.md).
- 2 - [View](../../../../../api/library/plugins/ig/api/class.view_cpp.md).
- 3 - [View Group](../../../../../api/library/plugins/ig/api/class.viewgroup_cpp.md).
- 4 - Трекер движения.


## int getCoordSystem ( ) const

Возвращает значение параметра **Coordinate System**, указанное в пакете. Определяет желаемую систему координат, относительно которой будут заданы положение и ориентация.
### Возвращаемое значение

Значение параметра Coordinate System. Поддерживаются следующие значения:
- 0 - Geodetic. Положение задаётся геодезической широтой, долготой и высотой. Ориентация задаётся относительно опорной плоскости.
- 1 - Parent Entity. Положение и ориентация задаются относительно сущности, к которой присоединена указанная сущность или view. Это значение недействительно для сущностей верхнего уровня.
- 2 - Submodel. Положение и ориентация задаются относительно опорной системы координат сочленённой части. Это значение действительно только когда [Object Class](#getObjectClass_int) установлен в Articulated Part (1).


> **Notice:** Если Object Class установлен в Motion Tracker (4), система координат определяется отслеживающим устройством, и этот параметр
