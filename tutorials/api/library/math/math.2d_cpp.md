# Функции 2D-математики (CPP)

**Заголовочный файл:** #include <UnigineMathLib2d.h>


Этот класс представляет собой набор двумерных математических функций.


> **Примечание:** Функции 2D-математики являются членами пространства имён **Unigine::Math**.


## Класс Math

### Методы класса

---

## void findIntersection ( const vec2 & p1 , const vec2 & p2 , const vec2 & p3 , const vec2 & p4 , int & lines_intersect , int & segments_intersect , vec2 & intersection , vec2 & close_p1 , vec2 & close_p2 )

Находит точку пересечения двух линий, заданных парами точек **p1 - p2** и **p3 - p4**, и заполняет значения последних 5 аргументов.
### Аргументы

- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p1** - Координаты начальной точки первого отрезка.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p2** - Координаты конечной точки первого отрезка.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p3** - Координаты начальной точки второго отрезка.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p4** - Координаты конечной точки второго отрезка.
- *int &* **lines_intersect** - 1, если линии, которым принадлежат отрезки, пересекаются; иначе 0.
- *int &* **segments_intersect** - 1, если отрезки пересекаются; иначе 0.
- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **intersection** - Координаты точки пересечения двух отрезков.
- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **close_p1** - Координаты первой из двух ближайших точек, принадлежащих первому отрезку.
- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **close_p2** - Координаты второй из двух ближайших точек, принадлежащих второму отрезку.

## int findIntersection ( const vec2 & p1 , const vec2 & p2 , const vec2 & p3 , const vec2 & p4 , vec2 & intersection )

Находит точку пересечения двух линий, заданных парами точек **p1 - p2** и **p3 - p4**.
### Аргументы

- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p1** - Координаты начальной точки первого отрезка.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p2** - Координаты конечной точки первого отрезка.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p3** - Координаты начальной точки второго отрезка.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p4** - Координаты конечной точки второго отрезка.
- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **intersection** - Координаты точки пересечения двух отрезков.

### Возвращаемое значение

1, если отрезки пересекаются; иначе 0.
## void findIntersection ( const dvec2 & p1 , const dvec2 & p2 , const dvec2 & p3 , const dvec2 & p4 , int & lines_intersect , int & segments_intersect , vec2 & intersection , vec2 & close_p1 , vec2 & close_p2 )

Находит точку пересечения двух линий, заданных парами точек **p1 - p2** и **p3 - p4**, и заполняет значения последних 5 аргументов.
### Аргументы

- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p1** - Координаты начальной точки первого отрезка.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p2** - Координаты конечной точки первого отрезка.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p3** - Координаты начальной точки второго отрезка.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p4** - Координаты конечной точки второго отрезка.
- *int &* **lines_intersect** - 1, если линии, которым принадлежат отрезки, пересекаются; иначе 0.
- *int &* **segments_intersect** - 1, если отрезки пересекаются; иначе 0.
- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **intersection** - Координаты точки пересечения двух отрезков.
- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **close_p1** - Координаты первой из двух ближайших точек, принадлежащих первому отрезку.
- *[vec2](../../../api/library/math/class.vec2_cpp.md) &* **close_p2** - Координаты второй из двух ближайших точек, принадлежащих второму отрезку.

## int findIntersection ( const dvec2 & p1 , const dvec2 & p2 , const dvec2 & p3 , const dvec2 & p4 , dvec2 & intersection )

Находит точку пересечения двух линий, заданных парами точек **p1 - p2** и **p3 - p4**.
### Аргументы

- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p1** - Координаты начальной точки первого отрезка.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p2** - Координаты конечной точки первого отрезка.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p3** - Координаты начальной точки второго отрезка.
- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **p4** - Координаты конечной точки второго отрезка.
- *[dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **intersection** - Координаты точки пересечения двух отрезков.

### Возвращаемое значение

1, если отрезки пересекаются; иначе 0.
## float getPolygonArea ( const Vector < vec2 > & points )

Возвращает площадь заданного многоугольника в квадратных единицах.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **points** - Вектор, содержащий все точки многоугольника.

### Возвращаемое значение

Площадь многоугольника, в квадратных единицах.
## float getPolygonAreaSigned ( const Vector < vec2 > & points )

Возвращает площадь заданного многоугольника в квадратных единицах.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **points** - Вектор, содержащий все точки многоугольника.

### Возвращаемое значение

Площадь многоугольника, в квадратных единицах.
> **Примечание:** Отрицательное значение означает, что многоугольник ориентирован по часовой стрелке.


## float getTriangleArea ( const vec2 & p1 , const vec2 & p2 , const vec2 & p3 )

Возвращает площадь заданного треугольника в квадратных единицах.
### Аргументы

- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p1** - Координаты первой вершины треугольника.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p2** - Координаты второй вершины треугольника.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **p3** - Координаты третьей вершины треугольника.

### Возвращаемое значение

Площадь треугольника, в квадратных единицах.
> **Примечание:** Отрицательное значение означает, что многоугольник ориентирован по часовой стрелке.


## int pointTriangleInside ( const vec2 & point , const vec2 & v0 , const vec2 & v1 , const vec2 & v2 )

Возвращает значение, указывающее, находится ли заданная точка внутри указанного треугольника.
### Аргументы

- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **point** - Координаты проверяемой точки.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v0** - Координаты первой вершины треугольника.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v1** - Координаты второй вершины треугольника.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v2** - Координаты третьей вершины треугольника.

### Возвращаемое значение

1, если заданная точка находится внутри указанного треугольника; иначе 0.
## int polygonIsOrientedClockwise ( const Vector < vec2 > & points )

Возвращает значение, указывающее, ориентирован ли заданный многоугольник по часовой стрелке.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **points** - Вектор, содержащий все точки многоугольника.

### Возвращаемое значение

1, если заданный многоугольник ориентирован по часовой стрелке; иначе 0.
## void resizePolygon ( const Vector < vec2 > & points , float offset , Vector < vec2 > & result_points , int append_to_result )

Возвращает набор точек, представляющих изменённый по размеру многоугольник. Многоугольник изменяется путём смещения его рёбер внутрь или наружу на заданное значение смещения. Это обычно называют "раздутием" или "сдутием" многоугольника, в зависимости от того, положительное значение смещения (расширение) или отрицательное (сжатие). Поддерживаются вогнутые многоугольники, ориентации CCW и CW.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **points** - Вектор, содержащий все точки многоугольника.
- *float* **offset** - Значение, на которое каждая точка многоугольника смещается наружу (положительное значение) или внутрь (отрицательное значение).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **result_points** - Вектор, содержащий все точки сдутого/раздутого многоугольника.
- *int* **append_to_result** - Флаг, указывающий, должны ли результирующие точки быть добавлены к точкам исходного многоугольника - 0 (значение по умолчанию), или заменить их - 1.

## int setPolygonToCCW ( Vector < vec2 > & points )

Задаёт ориентацию многоугольника против часовой стрелки.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **points** - Вектор, содержащий все точки многоугольника.

### Возвращаемое значение

1, если ориентация многоугольника против часовой стрелки успешно задана; иначе 0.
## float sign ( const vec2 & point , const vec2 & segment_p1 , const vec2 & segment_p2 )

Возвращает значение, указывающее, к какой части отрезка принадлежит точка.
### Аргументы

- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **point** - Координаты проверяемой точки.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **segment_p1** - Координаты начальной точки отрезка.
- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **segment_p2** - Координаты конечной точки отрезка.

## void triangulatePolygon ( const Vector < vec2 > & points , Vector <unsigned short> & indices , int append_to_result )

Выполняет триангуляцию с помощью алгоритма отсечения ушей (сложность: O(n^2)/O(n)).
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **points** - Вектор, содержащий все точки многоугольника.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<unsigned short> &* **indices** - Вектор, содержащий все индексы точек.
- *int* **append_to_result** - Флаг, указывающий, должны ли результирующие точки быть добавлены к точкам исходного многоугольника - 0 (значение по умолчанию), или заменить их - 1.
