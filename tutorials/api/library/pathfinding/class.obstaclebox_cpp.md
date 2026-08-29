# Unigine::ObstacleBox Class (CPP)

**Header:** #include <UniginePathFinding.h>

**Inherits from:** Obstacle


Этот класс используется для создания [cuboid-shaped obstacle](../../../objects/navigations/obstacle/obstacle_box/index.md), которое обнаруживается и обходится другими объектами в процессе поиска пути.


### См. также


- Пример использования [Creating Routes](../../../code/usage/navigation_and_pathfinding/routes/index_cpp.md), демонстрирующий создание маршрутов и их пересчёт с учётом препятствий
- Раздел *[Navigation](../../../sdk/api_samples/cpp/navigation.md)* в C++ Samples
- Раздел *[Navigation](../../../sdk/api_samples/cs/navigation.md)* в C# Component Samples
- Раздел *[Pathfinding](../../../code/uniginescript/samples/pathfinding.md)* в UnigineScript samples


## ObstacleBox Class

### Методы класса

## void setSize ( const Math:: vec3 & size )

Задаёт новый размер obstacle box.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **size** - Размеры параллелепипеда.

## Math:: vec3 getSize () const

Возвращает текущий размер obstacle box.
### Возвращаемое значение

Текущие размеры параллелепипеда.
---

## static ObstacleBoxPtr create ( const Math:: vec3 & arg1 )

Конструктор. Создаёт новое препятствие в форме параллелепипеда указанного размера.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **arg1** - Размеры параллелепипеда.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Obstacle](../../../api/library/pathfinding/class.obstacle_cpp.md).
