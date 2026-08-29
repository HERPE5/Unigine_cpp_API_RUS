# CigiMaritimeControl Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiMaritimeControl Class

### Методы класса

---

## int getRegionID ( ) const

Возвращает ID экологического региона, указанный в пакете.
### Возвращаемое значение


- **Entity ID**, если [Scope](#getScope_int) установлен в Entity (2).
- **Region ID**, если [Scope](#getScope_int) установлен в Regional (1).


> **Notice:** Это значение будет игнорироваться, если [Scope](#getScope_int) установлен в Global (0).


## int getSurfaceEnabled ( ) const

Возвращает значение параметра **Surface Conditions Enable**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Surface Conditions Enable**: 1 - поверхностные условия задаются этим пакетом; 0 - поверхностные условия в регионе или сущности будут совпадать с глобальными морскими поверхностными условиями.
## int getWhitecapEnabled ( ) const

Возвращает значение параметра **Whitecap Enable**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Whitecap Enable**: 1, если барашки волн включены; иначе 0.
## int getScope ( ) const

Возвращает значение параметра **Scope**, указанное в пакете. Определяет, является ли погода глобальной, региональной или назначенной сущности.
### Возвращаемое значение

Значение параметра **Scope**. Поддерживаются следующие значения:
- 0 - Глобальная
- 1 - Региональная
- 2 - Сущности


## float getHeight ( ) const

Возвращает значение параметра **Sea Surface Height**, указываемое в пакете.
### Возвращаемое значение

Значение параметра **Sea Surface Height**.
## float getTemperature ( ) const

Возвращает значение параметра **Surface Water Temperature**, указываемое в пакете.
### Возвращаемое значение

Значение параметра **Surface Water Temperature**, в градусах Цельсия.
## float getClarity ( ) const

Возвращает значение параметра **Surface Clarity**, указываемое в пакете.
### Возвращаемое значение

Значение параметра **Surface Clarity** в диапазоне [0; 100].
