# ObjectVolumeBox Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для создания [volume box](../../../objects/effects/volumetrics/volume_box.md). В зависимости от назначенного материала, он может использоваться для рендеринга [fog](../../../content/materials/library/volume_fog_base/index.md), [light shafts](../../../content/materials/library/volume_shaft_base/index.md) от мирового источника света или [clouds](../../../content/materials/library/volume_cloud_base/index.md).


## ObjectVolumeBox Class

### Методы класса

---

## static ObjectVolumeBoxPtr create ( const Math:: vec3 & size )

Конструктор. Создаёт новый объект объёмного бокса с заданными размерами.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Размеры нового объекта объёмного бокса, в единицах.

## void setSize ( const Math:: vec3 & size )

Задаёт новые размеры объёмного бокса.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **size** - Новые размеры объёмного бокса, в единицах. Если указано отрицательное значение, вместо него будет использовано 0.

## Math:: vec3 getSize ( ) const

Возвращает размеры объёмного бокса.
### Возвращаемое значение

Размеры объёмного бокса, в единицах.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Object](../../../api/library/objects/class.object_cpp.md).
