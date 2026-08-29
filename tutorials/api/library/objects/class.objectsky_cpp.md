# ObjectSky Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для создания [sky](../../../objects/objects/sky/index.md).


### See Also


Примеры на UnigineScript:


-
-


## ObjectSky Class

### Методы класса

---

## static ObjectSkyPtr create ( )

Конструктор. Создаёт новый объект неба.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа узла [ObjectSky](../../../api/library/nodes/class.node_cpp.md#OBJECT_SKY).
## void setSpherical ( bool spherical )

Задаёт значение, указывающее, должна ли кубическая карта фона неба проецироваться на всю сферу, а не на полусферу.
### Аргументы

- *bool* **spherical** - **true** для всей сферы; **false** для полусферы неба.

## bool isSpherical ( ) const

Возвращает значение, указывающее, проецируется ли кубическая карта фона неба на всю сферу, а не на полусферу.
### Возвращаемое значение

**true**, если небо представляет собой сферу; **false**, если полусферу.
