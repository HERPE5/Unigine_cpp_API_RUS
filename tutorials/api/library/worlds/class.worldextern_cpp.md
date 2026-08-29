# Unigine.WorldExtern Class (CPP)

**Header:** #include <UnigineWorld.h>

**Inherits from:** Node


WorldExtern - это пользовательский мир, создаваемый через API.


## WorldExtern Class

### Методы класса

---

## static WorldExternPtr create ( const Ptr < Node > & node )

Конструктор.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Указатель на Node.

## static WorldExternPtr create ( int class_id )

Конструктор. Создаёт пользовательский мир.
### Аргументы

- *int* **class_id** - Уникальный ID класса.

## int getClassID ( ) const

Возвращает уникальный ID класса.
### Возвращаемое значение

Возвращает уникальный ID класса, если мир существует; иначе 0.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [WorldExtern](../../../api/library/nodes/class.node_cpp.md#WORLD_EXTERN).
