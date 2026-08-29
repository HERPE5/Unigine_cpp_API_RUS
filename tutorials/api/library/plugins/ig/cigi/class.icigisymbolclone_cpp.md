# CigiSymbolClone Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiSymbolClone Class

### Методы класса

---

## int getSymbolID ( ) const

Возвращает **Symbol ID**, указанный в пакете. Идентификатор определяемого символа.
### Возвращаемое значение

Значение параметра Symbol ID.
## int getSourceID ( ) const

Возвращает **Source ID**, указанный в пакете. Определяет, будет ли новый символ копией существующего символа или экземпляром шаблона символа, определённого IG.
### Возвращаемое значение

Значение параметра Source ID.
## int getSourceType ( ) const

Возвращает значение параметра **Source Type**, указанное в пакете. Определяет, является ли тип исходного символа Symbol Template или Symbol.
### Возвращаемое значение

Значение параметра Source Type: 1, если тип источника — Symbol Template; иначе 0.
