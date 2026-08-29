# CigiEnvironmentRequest Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiEnvironmentRequest Class

### Методы класса

---

## int getRequestID ( ) const

Возвращает значение параметра **Request ID**, указанное в пакете. Идентифицирует запрос экологических условий.
### Возвращаемое значение

ID запроса.
## int getRequestType ( ) const

Возвращает значение параметра **Request Type**, указанное в пакете. Определяет, каким пакетом IG должен ответить.
### Возвращаемое значение

Значение параметра Request Type. Поддерживаются следующие значения:
- 1 - [Maritime Surface Conditions](../../../../../api/library/plugins/ig/cigi/class.icigimaritimeresponse_cpp.md).
- 2 - [Terrestrial Surface Conditions](../../../../../api/library/plugins/ig/cigi/class.icigiterrestrialresponse_cpp.md).
- 4 - [Weather Conditions](../../../../../api/library/plugins/ig/cigi/class.icigiweatherresponse_cpp.md).
- 8 - [Aerosol Concentration](../../../../../api/library/plugins/ig/cigi/class.icigiaerosolresponse_cpp.md).


## Math:: dvec3 getPosition ( ) const

Возвращает трёхкомпонентный вектор значений параметров **Latitude, Longitude and Altitude**, указанных в пакете. Задаёт геодезическую широту, долготу и высоту, для которых запрашивается экологическое состояние.
### Возвращаемое значение

Трёхкомпонентный вектор значений параметров **[Latitude, Longitude, Altitude]**.
