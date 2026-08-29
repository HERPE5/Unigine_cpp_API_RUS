# CigiSymbolSurfaceDef Class (CPP)

**Header:** #include <plugins/Unigine/CIGIConnector/UnigineCIGIConnector.h>

**Inherits from:** CigiHostPacket


## CigiSymbolSurfaceDef Class

### Методы класса

---

## int getSurfaceID ( ) const

Возвращает **Surface ID**, указанный в пакете.
### Возвращаемое значение

Surface ID.
## int getEntityID ( ) const

Возвращает **Entity ID**, указанный в пакете.
### Возвращаемое значение

Entity ID.
## int getSurfaceState ( ) const

Возвращает значение параметра **Surface State**, указанное в пакете. Определяет, будет ли поверхность активной.
### Возвращаемое значение

Значение параметра Surface State: 1 (Active), если поверхность включена; иначе 0 (Destroyed).
## int getAttachType ( ) const

Возвращает значение параметра **Attach Type**, указанное в пакете. Определяет, будет ли поверхность присоединена к сущности или к view.
### Возвращаемое значение

Значение параметра Attach Type: 0 (Entity), заданное параметром [Entity ID](#getEntityID_int); иначе 1 (View).
> **Notice:** Если указанная сущность или view не существуют, этот пакет игнорируется.


## int getBillboard ( ) const

Возвращает значение параметра **Billboard**, указанное в пакете. Определяет способ ориентации поверхности.
### Возвращаемое значение

Значение параметра Billboard. Поддерживаются следующие значения:
- 1 – Billboard. Поверхность ориентируется так, чтобы вектор нормали из центра поверхности был параллелен вектору обзора.
- 0 - Non-Billboard. The surface shall be oriented in relation to the entity’s local coordinate system by the Yaw, Pitch, and Roll parameters.


> **Notice:** Если поверхность присоединена к view, IG игнорирует этот параметр.


## int getPerspective ( ) const

Возвращает значение параметра **Perspective Growth Enable**, указанное в пакете.
### Возвращаемое значение

Параметр **Perspective Growth Enable**: 1 (Enabled), если перспективное увеличение включено; иначе 0 (Disabled).
## Math:: vec3 getOffset ( ) const

Возвращает смещение указанной поверхности в виде трёхкомпонентного вектора значений параметров **X Offset, Y Offset и Z Offset** либо **Left, Right и Top**, указанных в пакете.
### Возвращаемое значение

Трёхкомпонентный вектор:
- [X Offset, Y Offset, Z Offset] - if the surface is attached to an entity. The values are relative to the entity’s reference point.
- [Left, Right, Top] - if the surface is attached to a view. The IG shall place it at this distance from the left edge of the viewport to the surface’s leftmost and rightmost boundary and from the bottom edge of the viewport to the surface’s topmost boundary respectively. This distance is measured as a fraction of the viewport’s width.


## Math:: vec3 getRotation ( ) const

Возвращает ориентацию указанной поверхности в виде трёхкомпонентного вектора значений параметров **Yaw, Pitch и Roll** (для поверхностей, присоединённых к сущности) и значения параметра **Bottom** (для поверхностей, присоединённых к view), указанных в пакете.
### Возвращаемое значение

Трёхкомпонентный вектор. Значения [Yaw, Pitch, Roll] - если поверхность присоединена к сущности; иначе [Bottom, Y, Z].
> **Notice:** Если указанная поверхность присоединена к View, последние два компонента вектора игнорируются.


## float getWidth ( ) const

Возвращает значение параметра **Width**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Width** в диапазоне [0.0; 180.0] для поверхностей, являющихся присоединёнными к сущности Billboard с отключённым [Perspective Growth](#getPerspective_int); значение **больше 0** для присоединённых к сущности Billboard с включённым [Perspective Growth](#getPerspective_int) и для Non-Billboard.
## float getHeight ( ) const

Возвращает значение параметра **Height**, указанное в пакете.
### Возвращаемое значение

Значение параметра **Height** в диапазоне [0.0; 180.0] для поверхностей, являющихся Billboard, присоединённых к сущности с отключённым [Perspective Growth](#getPerspective_int); значение **больше 0** для присоединённых к сущности Billboard с включённым [Perspective Growth](#getPerspective_int) и для Non-Billboard.
## Math:: vec3 getMin ( ) const

Возвращает трёхкомпонентный вектор, содержащий значения параметров **Min U, Min V**, указанных в пакете. Определяет UV-координаты, соответствующие левой и нижней границам поверхности символов.
### Возвращаемое значение

Трёхкомпонентный вектор значений параметров [Min U, Min V].
## Math:: vec3 getMax ( ) const

Возвращает трёхкомпонентный вектор, содержащий значения параметров **Max U, Max V**, указанных в пакете. Определяет UV-координаты, соответствующие правой и верхней границам поверхности символов.
### Возвращаемое значение

Трёхкомпонентный вектор значений параметров [Max U, Max V].
