# Unigine::ObstacleCapsule Class (CPP)

**Header:** #include <UniginePathFinding.h>

**Inherits from:** Obstacle


Этот класс используется для создания [capsule-shaped obstacle](../../../objects/navigations/obstacle/obstacle_capsule/index.md), которое обнаруживается и обходится другими объектами в процессе поиска пути.


### См. также


- Пример использования [Creating Routes](../../../code/usage/navigation_and_pathfinding/routes/index_cpp.md), демонстрирующий создание маршрутов и их пересчёт с учётом препятствий
- Раздел *[Navigation](../../../sdk/api_samples/cpp/navigation.md)* в C++ Samples
- Раздел *[Navigation](../../../sdk/api_samples/cs/navigation.md)* в C# Component Samples
- Раздел *[Pathfinding](../../../code/uniginescript/samples/pathfinding.md)* в UnigineScript samples


## ObstacleCapsule Class

### Методы класса

## void setRadius ( float radius )

Задаёт новый радиус obstacle capsule.
### Аргументы

- *float* **radius** - Радиус капсулы. Если указано отрицательное значение, вместо него используется **0**.

## float getRadius () const

Возвращает текущий радиус obstacle capsule.
### Возвращаемое значение

Текущий радиус капсулы. Если указано отрицательное значение, вместо него используется **0**.
## void setHeight ( float height )

Задаёт новую высоту obstacle capsule.
### Аргументы

- *float* **height** - Высота капсулы. Если указано отрицательное значение, вместо него используется **0**.

## float getHeight () const

Возвращает текущую высоту obstacle capsule.
### Возвращаемое значение

Текущая высота капсулы. Если указано отрицательное значение, вместо него используется **0**.
---

## static ObstacleCapsulePtr create ( float radius , float height )

Конструктор. Создаёт новое препятствие в форме капсулы указанного размера.
### Аргументы

- *float* **radius** - Радиус капсулы.
- *float* **height** - Высота капсулы.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Obstacle](../../../api/library/pathfinding/class.obstacle_cpp.md).
