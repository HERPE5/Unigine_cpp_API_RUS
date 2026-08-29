# ObjectDummy Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


[Dummy object](../../../objects/objects/dummy/index.md) может использоваться, когда требуется невидимый объект с физическими свойствами. Например, как базовый объект для удержания видимого физического объекта, зафиксированного с помощью [joints](../../../api/library/physics/class.joint_cpp.md). Он также может служить корневым узлом для организации иерархии, как и [NodeDummy](../../../api/library/nodes/class.nodedummy_cpp.md).


## ObjectDummy Class

### Методы класса

---

## static ObjectDummyPtr create ( )

Конструктор. Создаёт новый объект-пустышку.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Object](../../../api/library/objects/class.object_cpp.md).
