# Unigine.ObjectCloudLayer Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для создания слоёв облаков.


## ObjectCloudLayer Class

### Методы класса

---

## static ObjectCloudLayerPtr create ( )

Конструктор. Создаёт новый пустой объект слоя облаков со свойствами по умолчанию.
## static int type ( )

Возвращает тип объекта.
### Возвращаемое значение

Идентификатор типа Object Cloud Layer.
## float getIntersectionThreshold ( ) const

Возвращает текущее значение порога пересечения.
### Возвращаемое значение

Значение порога пересечения.
## void setAnimationNoiseOffset ( const Math:: vec4 & offset )

Задаёт заданное значение смещения анимации шума.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **offset** - Смещение анимации шума (значение [vec4](../../../api/library/math/class.vec4_cpp.md), где компоненты **X**, **Y** и **Z** представляют смещения 3D-текстуры шума по осям X, Y и Z соответственно).

## void setAnimationCoverageOffset ( const Math:: vec4 & offset )

Задаёт заданное значение смещения анимации покрытия.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **offset** - Смещение анимации покрытия (значение [vec4](../../../api/library/math/class.vec4_cpp.md), где компоненты **X** и **Y** представляют смещения текстуры покрытия по осям X и Y соответственно).

## Math:: vec4 getAnimationNoiseOffset ( ) const

Возвращает текущее значение смещения анимации шума.
### Возвращаемое значение

Смещение анимации шума (значение [vec4](../../../api/library/math/class.vec4_cpp.md), где компоненты **X**, **Y** и **Z** представляют смещения 3D-текстуры шума по осям X, Y и Z соответственно).
## float getIntersectionAccuracy ( ) const

Возвращает текущее значение точности пересечения.
### Возвращаемое значение

Значение точности пересечения.
## void setIntersectionAccuracy ( float accuracy )

Задаёт заданное значение точности пересечения.
### Аргументы

- *float* **accuracy** - Значение точности пересечения.

## void setIntersectionThreshold ( float threshold )

Задаёт заданное значение порога пересечения.
### Аргументы

- *float* **threshold** - Значение порога пересечения.

## Math:: vec4 getAnimationCoverageOffset ( ) const

Возвращает текущее значение смещения анимации покрытия.
### Возвращаемое значение

Смещение анимации покрытия (значение [vec4](../../../api/library/math/class.vec4_cpp.md), где компоненты **X** и **Y** представляют смещения текстуры покрытия по осям X и Y соответственно, компоненты **Z** и **W** равны 0).
## void refreshCloudsRegionMask ( )

Обновляет маску области облаков. Метод должен вызываться после изменения маски, чтобы применить её.
## float getDensity ( const Math::Vec3& world_point ) const

Возвращает текущую плотность облаков в заданной точке.
### Аргументы

- *const  Math::Vec3&* **world_point** - Координаты точки в мировом пространстве.

### Возвращаемое значение

Плотность облаков.
