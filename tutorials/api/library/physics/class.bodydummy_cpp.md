# Unigine::BodyDummy Class (CPP)

**Header:** #include <UniginePhysics.h>

**Inherits from:** Body


Этот класс используется для создания фиктивного тела (dummy), которое служит неподвижным, невзаимодействующим (и часто [invisible](../../../api/library/objects/class.objectdummy_cpp.md)) объектом-опорой, к которому с помощью joints присоединяются другие тела.


## BodyDummy Class

### Методы класса

---

## static BodyDummyPtr create ( )

Конструктор. Создаёт фиктивное тело (dummy).
## static BodyDummyPtr create ( const Ptr < Object > & object )

Конструктор. Создаёт фиктивное тело (dummy) для указанного объекта.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Объект, аппроксимируемый новым фиктивным телом.
