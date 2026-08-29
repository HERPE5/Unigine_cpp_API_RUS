# Unigine::NavigationSector Class (CPP)

**Header:** #include <UniginePathFinding.h>

**Inherits from:** Navigation


> **Warning:** Функция 3D-навигации является экспериментальной и не рекомендуется для использования в production.


Этот класс используется для создания области навигации в форме параллелепипеда, в пределах которой могут рассчитываться 2D- и 3D-маршруты.


#### См. также


- Статья [Navigation Sector](../../../objects/navigations/navigation/navigation_sector/index.md)
- Пример использования [Creating Routes](../../../code/usage/navigation_and_pathfinding/routes/index_cpp.md), демонстрирующий создание маршрутов и их пересчёт с учётом препятствий
- C++ samples:

  -
  -
- C# samples:

  -
  -
  -

  -
  -
  -
  -
  -
  -


## NavigationSector Class

### Методы класса

## void setSize ( const Math:: vec3 & size )

Задаёт новый размер navigation sector.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **size** - Размеры параллелепипеда.

## Math:: vec3 getSize () const

Возвращает текущий размер navigation sector.
### Возвращаемое значение

Текущие размеры параллелепипеда.
---

## static NavigationSectorPtr create ( const Math:: vec3 & arg1 )

Конструктор. Создаёт navigation sector указанного размера.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **arg1** - Размеры параллелепипеда.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Navigation](../../../api/library/pathfinding/class.navigation_cpp.md).
