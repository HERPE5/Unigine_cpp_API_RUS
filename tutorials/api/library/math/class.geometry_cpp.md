# Unigine::Geometry Class (CPP)

**Header:** #include <UnigineMathLibGeometry.h>


Этот класс используется для представления набора общих 3D математических функций, таких как пересечение линии с плоскостью, ближайшие точки на двух линиях и т.д.


## Geometry Class

### Методы класса

---

## void getClosestPointOnLine ( const Math:: dvec3 & point , const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , Math:: dvec3 & ret )

Сканирует указанный отрезок линии и ищет точку, ближайшую к опорной точке. Найденная точка помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Опорная точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка линии.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Возвращаемый вектор.

## void getClosestPointOnLine ( const Math:: vec3 & point , const Math:: vec3 & p0 , const Math:: vec3 & p1 , Math:: vec3 & ret )

Сканирует указанный отрезок линии и ищет точку, ближайшую к опорной точке. Найденная точка помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Опорная точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Возвращаемый вектор.

## bool getClosestPointOnTriangle ( const Math:: dvec3 & point , const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 , Math:: dvec3 & ret )

Сканирует указанный треугольник и ищет точку, ближайшую к опорной точке. Найденная точка помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Опорная точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Возвращаемый вектор.

### Возвращаемое значение

**true**, если точка находится внутри треугольника; иначе **false**
## bool getClosestPointOnTriangle ( const Math:: vec3 & point , const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 , Math:: vec3 & ret )

Сканирует указанный треугольник и ищет точку, ближайшую к опорной точке. Найденная точка помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Опорная точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Возвращаемый вектор.

### Возвращаемое значение

**true**, если точка находится внутри треугольника; иначе **false**
## bool getClosestPointsOnLines ( const Math:: dvec3 & p00 , const Math:: dvec3 & p01 , const Math:: dvec3 & p10 , const Math:: dvec3 & p11 , Math:: dvec3 & ret_0 , Math:: dvec3 & ret_1 )

Сканирует две указанные линии и ищет пару ближайших точек. Ближайшие точки первой и второй линий помещаются в соответствующий возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p00** - Начальная точка первой линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p01** - Конечная точка первой линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p10** - Начальная точка второй линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p11** - Конечная точка второй линии.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret_0** - Первый возвращаемый вектор.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret_1** - Второй возвращаемый вектор.

### Возвращаемое значение

**true**, если линии пересекаются; иначе **false**
## bool getClosestPointsOnLines ( const Math:: vec3 & p00 , const Math:: vec3 & p01 , const Math:: vec3 & p10 , const Math:: vec3 & p11 , Math:: vec3 & ret_0 , Math:: vec3 & ret_1 )

Сканирует две указанные линии и ищет пару ближайших точек. Ближайшие точки первой и второй линий помещаются в соответствующие возвращаемые векторы.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p00** - Начальная точка первой линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p01** - Конечная точка первой линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p10** - Начальная точка второй линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p11** - Конечная точка второй линии.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_0** - Первый возвращаемый вектор.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_1** - Второй возвращаемый вектор.

### Возвращаемое значение

**true**, если линии пересекаются; иначе **false**
## bool irayBoundBoxIntersection ( const Math:: dvec3 & point , const Math:: dvec3 & idirection , const Math:: dvec3 & min , const Math:: dvec3 & max )

Проверяет наличие пересечения между лучом и ограничивающим прямоугольником. Та же функция, что и [rayBoundBoxIntersection()](#rayBoundBoxIntersection_dvec3_dvec3_dvec3_dvec3_bool), но использует обратное направление луча, что повышает производительность.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **idirection** - Обратное направление луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **min** - Минимальные координаты ограничивающего прямоугольника, выровненного по осям.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **max** - Максимальные координаты ограничивающего прямоугольника, выровненного по осям.

### Возвращаемое значение

**true**, если данный луч пересекает данный ограничивающий прямоугольник; иначе **false**.
## bool irayBoundBoxIntersection ( const Math:: vec3 & point , const Math:: vec3 & idirection , const Math:: vec3 & min , const Math:: vec3 & max )

Проверяет наличие пересечения между лучом и ограничивающим прямоугольником. Та же функция, что и [rayBoundBoxIntersection()](#rayBoundBoxIntersection_vec3_vec3_vec3_vec3_bool), но использует обратное направление луча, что повышает производительность.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **idirection** - Обратное направление луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальные координаты ограничивающего прямоугольника, выровненного по осям.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальные координаты ограничивающего прямоугольника, выровненного по осям.

### Возвращаемое значение

**true**, если данный луч пересекает данный ограничивающий прямоугольник; иначе **false**.
## bool linePlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec4 & plane )

Проверяет наличие пересечения между линией и плоскостью.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## bool linePlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec4 & plane )

Проверяет наличие пересечения между линией и плоскостью.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка линии.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## bool linePlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec3 & plane_point , const Math:: vec3 & plane_normal )

Проверяет наличие пересечения между линией и плоскостью.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_point** - Точка плоскости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## bool linePlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec3 & plane_point , const Math:: dvec3 & plane_normal )

Проверяет наличие пересечения между линией и плоскостью.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Начальная точка линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_point** - Точка плоскости.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## bool linePlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec4 & plane , Math:: vec3 & ret )

Вычисляет точку пересечения линии и плоскости. Если функция возвращает **true**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## bool linePlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec4 & plane , Math:: dvec3 & ret )

Вычисляет точку пересечения линии и плоскости. Если функция возвращает **true**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка линии.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## bool linePlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec3 & plane_point , const Math:: vec3 & plane_normal , Math:: vec3 & ret )

Вычисляет точку пересечения линии и плоскости. Если функция возвращает **true**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_point** - Точка плоскости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## bool linePlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec3 & plane_point , const Math:: dvec3 & plane_normal , Math:: dvec3 & ret )

Вычисляет точку пересечения линии и плоскости. Если функция возвращает **true**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка линии.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_point** - Точка плоскости.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Возвращаемый вектор.

### Возвращаемое значение

**true**, если данная линия пересекает данную плоскость; иначе **false**.
## void orthoBasis ( const Math:: vec3 & v , Math:: vec3 & tangent , Math:: vec3 & binormal )

Создаёт ортогональное преобразование. Выходные векторы тангенса и бинормали помещаются в соответствующий возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - Входной вектор.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **tangent** - Возвращаемый вектор.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **binormal** - Возвращаемый вектор.

## void orthoBasis ( const Math:: dvec3 & v , Math:: dvec3 & tangent , Math:: dvec3 & binormal )

Создаёт ортогональное преобразование. Выходные векторы тангенса и бинормали помещаются в соответствующие возвращаемые векторы.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - Входной вектор.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **tangent** - Возвращаемый вектор.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **binormal** - Возвращаемый вектор.

## Math:: quat orthoTangent ( const Math:: vec3 & tangent , const Math:: vec3 & binormal , const Math:: vec3 & normal )

Создаёт ортогональный базис касательного пространства треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **tangent** - Вектор тангенса.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **binormal** - Вектор бинормали.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Вектор нормали.

### Возвращаемое значение

Базис тангенса.
## Math:: quat orthoTangent ( const Math:: vec4 & tangent , const Math:: vec3 & normal )

Создаёт ортогональный базис касательного пространства треугольника.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **tangent** - Вектор тангенса.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Вектор нормали.

### Возвращаемое значение

Базис тангенса.
## void orthoTransform ( const Math:: dvec3 & v , Math:: dmat4 & transform )

Создаёт ортогональное преобразование. Преобразование помещается в возвращаемую матрицу.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - Входной вектор.
- *Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **transform** - Возвращаемая матрица.

## void orthoTransform ( const Math:: vec3 & v , Math:: mat4 & transform )

Создаёт ортогональное преобразование. Преобразование помещается в возвращаемую матрицу.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - Входной вектор.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Возвращаемая матрица.

## float pointPolygonDistance ( const Math:: vec3 & point , const Math:: vec3 * vertex , int[] indices , int num_indices , const Math:: vec4 & plane )

Возвращает расстояние от точки до полигона.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *int[]* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость полигона.

### Возвращаемое значение

Расстояние.
## double pointPolygonDistance ( const Math:: dvec3 & point , const Math:: dvec3 * vertex , int[] indices , int num_indices , const Math:: dvec4 & plane )

Возвращает расстояние от точки до полигона.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *int[]* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость полигона.

### Возвращаемое значение

Расстояние.
## float pointPolygonDistance ( const Math:: vec3 & point , const Math:: vec3 * vertex , unsigned short [] indices , int num_indices , const Math:: vec4 & plane )

Возвращает расстояние от точки до полигона.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *unsigned short []* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость полигона.

### Возвращаемое значение

Расстояние.
## double pointPolygonDistance ( const Math:: dvec3 & point , const Math:: dvec3 * vertex , unsigned short [] indices , int num_indices , const Math:: dvec4 & plane )

Возвращает расстояние от точки до полигона.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *unsigned short []* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость полигона.

### Возвращаемое значение

Расстояние.
## bool pointPolygonInside ( const Math:: vec3 & point , const Math:: vec3 * vertex , int[] indices , int num_indices , const Math:: vec3 & normal )

Проверяет, находится ли точка внутри полигона.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *int[]* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Нормаль к плоскости полигона.

### Возвращаемое значение

**true**, если точка находится внутри данного полигона; иначе **false**.
## bool pointPolygonInside ( const Math:: dvec3 & point , const Math:: dvec3 * vertex , int[] indices , int num_indices , const Math:: dvec3 & normal )

Проверяет, находится ли точка внутри полигона.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *int[]* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **normal** - Нормаль к плоскости полигона.

### Возвращаемое значение

**true**, если точка находится внутри данного полигона; иначе **false**.
## bool pointPolygonInside ( const Math:: vec3 & point , const Math:: vec3 * vertex , unsigned short [] indices , int num_indices , const Math:: vec3 & normal )

Проверяет, находится ли точка внутри полигона.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *unsigned short []* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Нормаль к плоскости полигона.

### Возвращаемое значение

**true**, если точка находится внутри данного полигона; иначе **false**.
## bool pointPolygonInside ( const Math:: dvec3 & point , const Math:: dvec3 * vertex , unsigned short [] indices , int num_indices , const Math:: dvec3 & normal )

Проверяет, находится ли точка внутри полигона.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *unsigned short []* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **normal** - Нормаль к плоскости полигона.

### Возвращаемое значение

**true**, если точка находится внутри данного полигона; иначе **false**.
## void pointTriangleCoordinates ( const Math:: vec2 & point , const Math:: vec2 & v0 , const Math:: vec2 & v1 , const Math:: vec2 & v2 , float & a , float & b )

Вычисляет барицентрические координаты треугольника. Координаты помещаются в соответствующие возвращаемые переменные.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **point** - Точка.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **v2** - Третья вершина треугольника.
- *float &* **a** - Возвращаемая переменная.
- *float &* **b** - Возвращаемая переменная.

## void pointTriangleCoordinates ( const Math:: vec3 & point , const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 , float & a , float & b )

Вычисляет барицентрические координаты треугольника. Координаты помещаются в соответствующие возвращаемые переменные.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *float &* **a** - Возвращаемая переменная.
- *float &* **b** - Возвращаемая переменная.

## void pointTriangleCoordinates ( const Math:: dvec3 & point , const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 , double & a , double & b )

Вычисляет барицентрические координаты треугольника. Координаты помещаются в соответствующие возвращаемые переменные.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *double &* **a** - Возвращаемая переменная.
- *double &* **b** - Возвращаемая переменная.

## double pointTriangleDistance ( const Math:: dvec3 & point , const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 , const Math:: dvec4 & plane )

Возвращает ближайшее расстояние от точки до треугольника.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость треугольника.

### Возвращаемое значение

Расстояние.
## float pointTriangleDistance ( const Math:: vec3 & point , const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 , const Math:: vec4 & plane )

Возвращает ближайшее расстояние от точки до треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость треугольника.

### Возвращаемое значение

Расстояние.
## bool pointTriangleInside ( const Math:: vec3 & point , const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 , const Math:: vec3 & normal )

Проверяет, находится ли точка внутри треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Нормаль к плоскости треугольника.

### Возвращаемое значение

**true**, если точка находится внутри данного треугольника; иначе **false**.
## bool pointTriangleInside ( const Math:: dvec3 & point , const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 , const Math:: dvec3 & normal )

Проверяет, находится ли точка внутри треугольника.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **normal** - Нормаль к плоскости треугольника.

### Возвращаемое значение

**true**, если точка находится внутри данного треугольника; иначе **false**.
## bool pointTriangleInside ( const Math:: dvec3 & point , const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 )

Проверяет, находится ли точка внутри треугольника.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Точка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

**true**, если точка находится внутри данного треугольника; иначе **false**.
## bool pointTriangleInside ( const Math:: vec3 & point , const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 )

Проверяет, находится ли точка внутри треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

**true**, если точка находится внутри данного треугольника; иначе **false**.
## Math:: vec4 polygonPlane ( const Math:: vec3 * vertex , int[] indices , int num_indices )

Возвращает плоскость полигона.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *int[]* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.

### Возвращаемое значение

Плоскость полигона.
## Math:: dvec4 polygonPlane ( const Math:: dvec3 * vertex , int[] indices , int num_indices )

Возвращает плоскость полигона.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *int[]* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.

### Возвращаемое значение

Плоскость полигона.
## Math:: vec4 polygonPlane ( const Math:: vec3 * vertex , unsigned short [] indices , int num_indices )

Возвращает плоскость полигона.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *unsigned short []* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.

### Возвращаемое значение

Плоскость полигона.
## Math:: dvec4 polygonPlane ( const Math:: dvec3 * vertex , unsigned short [] indices , int num_indices )

Возвращает плоскость полигона.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) ** **vertex** - Указатель на структуру вершин.
- *unsigned short []* **indices** - Массив индексов вершин.
- *int* **num_indices** - Общее количество индексов вершин.

### Возвращаемое значение

Плоскость полигона.
## Math:: vec3 projectOntoPlane ( const Math:: vec3 & v , const Math:: vec3 & plane_normal )

Вычисляет проекцию вектора на заданную плоскость.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - Входной вектор.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

Проекция входного вектора на плоскость.
## Math:: dvec3 projectOntoPlane ( const Math:: dvec3 & v , const Math:: dvec3 & plane_normal )

Вычисляет проекцию вектора на заданную плоскость.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - Входной вектор.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

Проекция входного вектора на плоскость.
## bool rayBoundBoxIntersection ( const Math:: dvec3 & point , const Math:: dvec3 & direction , const Math:: dvec3 & min , const Math:: dvec3 & max )

Проверяет, пересекает ли луч ограничивающий прямоугольник. Та же функция, что и [irayBoundBoxIntersection()](#irayBoundBoxIntersection_dvec3_dvec3_dvec3_dvec3_bool), но последняя имеет более высокую производительность за счёт сокращения операций деления, так как направление луча заменяется предварительно вычисленным обратным направлением луча.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **min** - Минимальные координаты ограничивающего прямоугольника, выровненного по осям.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **max** - Максимальные координаты ограничивающего прямоугольника, выровненного по осям.

### Возвращаемое значение

**true**, если данный луч пересекает данный ограничивающий прямоугольник; иначе **false**.
## bool rayBoundBoxIntersection ( const Math:: vec3 & point , const Math:: vec3 & direction , const Math:: vec3 & min , const Math:: vec3 & max )

Проверяет, пересекает ли луч ограничивающий прямоугольник. Та же функция, что и [irayBoundBoxIntersection()](#irayBoundBoxIntersection_vec3_vec3_vec3_vec3_bool), но последняя имеет более высокую производительность за счёт сокращения операций деления, так как направление луча заменяется предварительно вычисленным обратным направлением луча.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальные координаты ограничивающего прямоугольника, выровненного по осям.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальные координаты ограничивающего прямоугольника, выровненного по осям.

### Возвращаемое значение

**true**, если данный луч пересекает данный ограничивающий прямоугольник; иначе **false**.
## bool rayPlaneIntersection ( const Math:: vec3 & point , const Math:: vec3 & direction , const Math:: vec4 & plane )

Проверяет, пересекает ли луч плоскость.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayPlaneIntersection ( const Math:: dvec3 & point , const Math:: dvec3 & direction , const Math:: dvec4 & plane )

Проверяет, пересекает ли луч плоскость.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayPlaneIntersection ( const Math:: vec3 & point , const Math:: vec3 & direction , const Math:: vec3 & plane_point , const Math:: vec3 & plane_normal )

Проверяет, пересекает ли луч плоскость.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayPlaneIntersection ( const Math:: dvec3 & point , const Math:: dvec3 & direction , const Math:: dvec3 & plane_point , const Math:: dvec3 & plane_normal )

Проверяет, пересекает ли луч плоскость.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayPlaneIntersection ( const Math:: vec3 & point , const Math:: vec3 & direction , const Math:: vec4 & plane , Math:: vec3 & ret )

Вычисляет точку пересечения луча и плоскости. Если функция возвращает **true**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayPlaneIntersection ( const Math:: dvec3 & point , const Math:: dvec3 & direction , const Math:: dvec4 & plane , Math:: dvec3 & ret )

Вычисляет точку пересечения луча и плоскости. Если функция возвращает **1**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayPlaneIntersection ( const Math:: vec3 & point , const Math:: vec3 & direction , const Math:: vec3 & plane_point , const Math:: vec3 & plane_normal , Math:: vec3 & ret )

Вычисляет точку пересечения луча и плоскости. Если функция возвращает **true**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayPlaneIntersection ( const Math:: dvec3 & point , const Math:: dvec3 & direction , const Math:: dvec3 & plane_point , const Math:: dvec3 & plane_normal , Math:: dvec3 & ret )

Вычисляет точку пересечения луча и плоскости. Если функция возвращает **1**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный луч пересекает данную плоскость; иначе **false**.
## bool rayTriangleIntersection ( const Math:: vec3 & point , const Math:: vec3 & direction , const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 )

Проверяет, пересекает ли луч треугольник.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

**true**, если данный луч пересекает данный треугольник; иначе **false**.
## bool rayTriangleIntersection ( const Math:: dvec3 & point , const Math:: dvec3 & direction , const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 )

Проверяет, пересекает ли луч треугольник.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **direction** - Направление луча.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

**true**, если данный луч пересекает данный треугольник; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec4 & plane )

Проверяет, пересекает ли отрезок плоскость.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec4 & plane )

Проверяет, пересекает ли отрезок плоскость.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec3 & plane_point , const Math:: vec3 & plane_normal )

Проверяет, пересекает ли отрезок плоскость.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec3 & plane_point , const Math:: dvec3 & plane_normal )

Проверяет, пересекает ли отрезок плоскость.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec4 & plane , Math:: vec3 & ret )

Вычисляет точку пересечения отрезка и плоскости. Если функция возвращает **1**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Плоскость.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec4 & plane , Math:: dvec3 & ret )

Вычисляет точку пересечения отрезка и плоскости. Если функция возвращает **1**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **plane** - Плоскость.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 , const Math:: vec3 & plane_point , const Math:: vec3 & plane_normal , Math:: vec3 & ret )

Вычисляет точку пересечения отрезка и плоскости. Если функция возвращает **1**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## bool segmentPlaneIntersection ( const Math:: dvec3 & p0 , const Math:: dvec3 & p1 , const Math:: dvec3 & plane_point , const Math:: dvec3 & plane_normal , Math:: dvec3 & ret )

Вычисляет точку пересечения отрезка и плоскости. Если функция возвращает **1**, точка пересечения помещается в возвращаемый вектор.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p0** - Начальная точка отрезка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **p1** - Конечная точка отрезка.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_point** - Точка на плоскости.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **plane_normal** - Нормаль к плоскости.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret** - Return vector.

### Возвращаемое значение

**true**, если данный отрезок пересекает данную плоскость; иначе **false**.
## double triangleArea ( const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 )

Возвращает площадь треугольника.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

Площадь треугольника.
## float triangleArea ( const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 )

Возвращает площадь треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

Площадь треугольника.
## Math:: dvec3 triangleNormal ( const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 )

Возвращает вектор нормали треугольника.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

Вектор нормали треугольника.
## Math:: vec3 triangleNormal ( const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 )

Возвращает вектор нормали треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

Вектор нормали треугольника.
## Math:: vec4 trianglePlane ( const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 )

Возвращает плоскость треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

Плоскость треугольника.
## Math:: dvec4 trianglePlane ( const Math:: dvec3 & v0 , const Math:: dvec3 & v1 , const Math:: dvec3 & v2 )

Возвращает плоскость треугольника.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

Плоскость треугольника.
## Math:: vec4 triangleTangent ( const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 , const Math:: vec2 & t0 , const Math:: vec2 & t1 , const Math:: vec2 & t2 )

Возвращает касательное пространство треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **t0** - Вектор тангенса первой вершины треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **t1** - Вектор тангенса второй вершины треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **t2** - Вектор тангенса третьей вершины треугольника.

### Возвращаемое значение

Вектор касательного пространства треугольника.
## Math:: vec4 triangleTangent ( const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 , const Math:: vec2 & t0 , const Math:: vec2 & t1 , const Math:: vec2 & t2 , const Math:: vec3 & normal )

Возвращает касательное пространство треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **t0** - Вектор тангенса первой вершины треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **t1** - Вектор тангенса второй вершины треугольника.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **t2** - Вектор тангенса третьей вершины треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **normal** - Нормаль.

### Возвращаемое значение

Вектор касательного пространства треугольника.
## Math:: vec4 triangleTangent ( const Math:: vec3 & v0 , const Math:: vec3 & v1 , const Math:: vec3 & v2 )

Возвращает касательное пространство треугольника.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v0** - Первая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v1** - Вторая вершина треугольника.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **v2** - Третья вершина треугольника.

### Возвращаемое значение

Вектор касательного пространства треугольника.
## void TriangleRasterize ( Vertex * vertex , int x0 , int y0 , int x1 , int y1 , Shader & shader )

Размещает заданный треугольник в заданных экранных координатах, растеризует его и применяет указанный шейдер к каждому пикселю.
### Аргументы

- *Vertex ** **vertex** - Указатель на структуру вершин.
- *int* **x0** - Координата X верхнего левого угла экранного пространства.
- *int* **y0** - Координата Y верхнего левого угла экранного пространства.
- *int* **x1** - Координата X нижнего правого угла экранного пространства.
- *int* **y1** - Координата Y нижнего правого угла экранного пространства.
- *[Shader](../../../api/library/rendering/class.shader_cpp.md) &* **shader** - Шейдер.
