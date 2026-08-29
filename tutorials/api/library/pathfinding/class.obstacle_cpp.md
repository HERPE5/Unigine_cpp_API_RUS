# Unigine::Obstacle Class (CPP)

**Header:** #include <UniginePathFinding.h>

**Inherits from:** Node


Этот класс создаёт препятствия, обнаруживаемые и обходимые в процессе поиска пути.


### См. также


- Пример использования [Creating Routes](../../../code/usage/navigation_and_pathfinding/routes/index_cpp.md), демонстрирующий создание маршрутов и их пересчёт с учётом препятствий
- Раздел *[Navigation](../../../sdk/api_samples/cpp/navigation.md)* в C++ Samples
- Раздел *[Navigation](../../../sdk/api_samples/cs/navigation.md)* в C# Component Samples
- Раздел *[Pathfinding](../../../code/uniginescript/samples/pathfinding.md)* в UnigineScript samples


## Obstacle Class

### Методы класса

## void setObstacleMask ( int mask )

Задаёт новую маску препятствия. Маска препятствия box/sphere/capsule должна [match](../../../principles/bit_masking/index.md) с маской препятствий маршрута, рассчитываемого в процессе поиска пути. В противном случае препятствие не будет учитываться при поиске пути.
### Аргументы

- *int* **mask** - Целочисленное значение, каждый бит которого используется для задания маски.

## int getObstacleMask () const

Возвращает текущую маску препятствия. Маска препятствия box/sphere/capsule должна [match](../../../principles/bit_masking/index.md) с маской препятствий маршрута, рассчитываемого в процессе поиска пути. В противном случае препятствие не будет учитываться при поиске пути.
### Возвращаемое значение

Текущее целочисленное значение, каждый бит которого используется для задания маски.
