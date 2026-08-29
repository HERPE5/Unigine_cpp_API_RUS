# Unigine::Plugins::IG::ViewBase Class (CPP)

**Header:** #include <plugins/Unigine/IG/UnigineIG.h>


Этот класс представляет базовый интерфейс View IG. Он содержит общие методы для интерфейсов View и ViewGroup.

> **Notice:** Плагин IG должен быть загружен.


## ViewBase Class

### Перечисления

## VIEW_TYPE

| Name | Description |
|---|---|
| **VIEW_TYPE_VIEW** = 0 |  |
| **VIEW_TYPE_VIEWGROUP** = 1 |  |

### Методы класса

---

## void setParentEntity ( Entity * entity )

Присоединяет View(Group) как дочерний к указанной родительской [entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md).
### Аргументы

- *[Entity](../../../../../api/library/plugins/ig/api/class.entity_cpp.md) ** **entity** - Родительская сущность.

## long long getParentEntityID ( ) const

Возвращает ID родительской сущности для View(Group).
### Возвращаемое значение

ID родительской сущности.
## void setGeoPosition ( const Math::dvec3& position )

Задаёт положение View(Group), в геокоординатах (широта, долгота, высота).
### Аргументы

- *const  Math::dvec3&* **position** - Задаваемое положение View(Group), в геокоординатах (широта, долгота, высота).

## Math:: dvec3 getGeoPosition ( ) const

Возвращает текущее положение View(Group), в геокоординатах (широта, долгота, высота).
### Возвращаемое значение

Положение View(Group), в геокоординатах (широта, долгота, высота).
## void setPosition ( const Math::dvec3& position )

Задаёт положение View(Group).
### Аргументы

- *const  Math::dvec3&* **position** - Задаваемые координаты положения View(Group).

## Math:: dvec3 getPosition ( ) const

Возвращает текущее положение View(Group).
### Возвращаемое значение

Координаты положения View(Group).
## void setWorldPosition ( const Math::dvec3& pos )

Задаёт положение View(Group), в мировых координатах.
### Аргументы

- *const  Math::dvec3&* **pos** - Задаваемое положение View(Group), в мировых координатах.

## Math:: dvec3 getWorldPosition ( ) const

Возвращает текущее положение View(Group), в мировых координатах.
### Возвращаемое значение

Положение View(Group), в мировых координатах.
## void setRotationEuler ( const Math:: vec3 & euler )

Задаёт поворот View(Group).
### Аргументы

- *const  Math::[vec3](../../../../../api/library/math/class.vec3_cpp.md) &* **euler** - Задаваемые углы Эйлера поворота View(Group).

## Math:: vec3 getRotationEuler ( ) const

Возвращает текущий поворот View(Group).
### Возвращаемое значение

Углы Эйлера поворота View(Group).
## void setWorldRotationEuler ( const Math::vec3& euler )

Задаёт поворот View(Group), в мировых координатах.
### Аргументы

- *const  Math::vec3&* **euler** - Задаваемые углы Эйлера поворота View(Group).

## Math:: vec3 getWorldRotationEuler ( ) const

Возвращает текущий поворот View(Group), в мировых координатах.
### Возвращаемое значение

Углы Эйлера поворота View(Group).
## Ptr < Node > getNode ( ) const

Возвращает узел, назначенный View(Group).
### Возвращаемое значение

Узел, назначенный View(Group).
## Ptr < PlayerDummy > getPlayer ( ) const

Возвращает PlayerDummy, назначенный View(Group).
### Возвращаемое значение

PlayerDummy, назначенный View(Group).
## void copyTransformFromPlayer ( const Ptr < Player > & player )

Копирует матрицу modelview и задаёт её для View(Group).
### Аргументы

- *const [Ptr](../../../../../api/library/common/class.ptr_cpp.md)<[Player](../../../../../api/library/players/class.player_cpp.md)> &* **player** - Исходный player, из которого копируется трансформация.

## Component * getComponent ( int id )

Возвращает [interface](../../../../../api/library/plugins/ig/api/class.component_cpp.md) компонента по его ID.
### Аргументы

- *int* **id** - ID компонента.

### Возвращаемое значение

Интерфейс компонента, если он существует, иначе nullptr.
## ViewBase::VIEW_TYPE getType ( ) const

Возвращает идентификатор типа, указывающий, является ли это *View* или *ViewGroup*.
### Возвращаемое значение

Идентификатор типа view.
