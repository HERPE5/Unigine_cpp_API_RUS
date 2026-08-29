# Unigine::ObstacleSphere Class (CPP)

**Header:** #include <UniginePathFinding.h>

**Inherits from:** Obstacle


Этот класс используется для создания [sphere-shaped obstacle](../../../objects/navigations/obstacle/obstacle_sphere/index.md), которое обнаруживается и обходится другими объектами в процессе поиска пути.


### См. также


- Пример использования [Creating Routes](../../../code/usage/navigation_and_pathfinding/routes/index_cpp.md), демонстрирующий создание маршрутов и их пересчёт с учётом препятствий
- Раздел *[Navigation](../../../sdk/api_samples/cpp/navigation.md)* в C++ Samples
- Раздел *[Navigation](../../../sdk/api_samples/cs/navigation.md)* в C# Component Samples
- Раздел *[Pathfinding](../../../code/uniginescript/samples/pathfinding.md)* в UnigineScript samples


## ObstacleSphere Class

### Методы класса

## void setRadius ( float radius )

Задаёт новый радиус obstacle sphere.
### Аргументы

- *float* **radius** - Радиус сферы. Если указано отрицательное значение, вместо него используется **0**.

## float getRadius () const

Возвращает текущий радиус obstacle sphere.
### Возвращаемое значение

Текущий радиус сферы. Если указано отрицательное значение, вместо него используется **0**.
---

## static ObstacleSpherePtr create ( float radius )

Конструктор. Создаёт новое препятствие в форме сферы указанного размера.
### Аргументы

- *float* **radius** - Радиус сферы.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Obstacle](../../../api/library/pathfinding/class.obstacle_cpp.md).
