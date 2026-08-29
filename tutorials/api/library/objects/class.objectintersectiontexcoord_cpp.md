# ObjectIntersectionTexCoord Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** ObjectIntersectionNormal


Этот класс используется для хранения текстурных координат пересечения объекта.


## ObjectIntersectionTexCoord Class

### Методы класса

---

## static ObjectIntersectionTexCoordPtr create ( )

Конструктор ObjectIntersectionTexCoord.
## void setTexCoord ( const Math:: vec4 & coord )

Задаёт новые текстурные координаты точки пересечения.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **coord** - Текстурные координаты точки пересечения.

## Math:: vec4 getTexCoord ( ) const

Возвращает текстурные координаты точки пересечения.
### Возвращаемое значение

Текстурные координаты точки пересечения (где vec4.xy — для первого UV-канала, vec4.zw — для второго UV-канала).
