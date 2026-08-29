# ObjectVolumeSphere Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для создания [volume sphere](../../../objects/effects/volumetrics/volume_sphere.md). В зависимости от назначенного материала она может использоваться для рендеринга [fog](../../../content/materials/library/volume_fog_base/index.md) или видимого объёма [light](../../../content/materials/library/volume_light_base/index.md) вокруг источника света. Объёмная сфера также может иметь форму эллипсоида.


## ObjectVolumeSphere Class

### Методы класса

---

## static ObjectVolumeSpherePtr create ( const Math:: vec3 & radius )

Конструктор. Создаёт новый объект объёмной сферы с заданными значениями радиуса.
> **Notice:** Если объекту назначен материал [volume light](../../../content/materials/library/volume_light_base/index.md), он рендерится только на основе значения радиуса по оси X. Если значения радиуса по осям Y или Z меньше, объект обрезается по этим осям.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **radius** - Значения радиуса нового объекта объёмной сферы в единицах. Если указано отрицательное значение, вместо него будет использовано **0**.

## void setRadius ( const Math:: vec3 & radius )

Обновляет значения радиуса объёмной сферы. Если объекту назначен материал [volume light](../../../content/materials/library/volume_light_base/index.md), он рендерится только на основе значения радиуса по оси X. Если значения радиуса по осям Y или Z меньше, чем по оси X, объект обрезается по этим осям.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **radius** - Новые значения радиуса объёмной сферы в единицах. Если указано отрицательное значение, вместо него будет использовано 0.

## Math:: vec3 getRadius ( ) const

Возвращает значения радиуса объёмной сферы.
### Возвращаемое значение

Значения радиуса объёмной сферы в единицах.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Object](../../../api/library/objects/class.object_cpp.md).
