# Unigine.WorldTransformJoint Class (CPP)

**Заголовочный файл:** #include <UnigineWorlds.h>

**Наследуется от:** Node


Этот класс используется для создания [joint transforms](../../../objects/worlds/world_transforms/transform_bone/index.md). У него должен быть родитель типа [ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md) или [ObjectMeshSkinnedLegacy](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md). Необходимо указать [joint](#setJointName_cstr_void), который будет использоваться для его трансформаций. Чтобы другие узлы перемещались вместе с этими трансформациями, их следует назначить дочерними для WorldTransformJoint.


### См. также


Пример на UnigineScript


## WorldTransformJoint Class

### Методы класса

---

## static WorldTransformJointPtr create ( const char * name = 0 )

Конструктор. Создаёт WorldTransformJoint в мировых координатах с указанным именем сустава.
### Аргументы

- *const char ** **name** — имя сустава.

## void setJointName ( const char * name )

Задаёт имя сустава, используемого для трансформации.
### Аргументы

- *const char ** **name** — имя сустава.

## const char * getJointName ( ) const

Возвращает имя сустава, используемого для трансформации.
### Возвращаемое значение

Имя сустава.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [World](../../../api/library/engine/class.world_cpp.md).
