# Unigine::Polygon Class (CPP)

**Header:** #include <UnigineMathLibPolygon.h>


Этот класс создаёт индексированный полигон (выпуклый или вогнутый) с использованием вершин и нормали плоскости.


## Polygon Class

### Методы класса

---

## void clear ( )

Очищает данные (вершины и индексы) полигона.
## bool createConvex ( const vec3* v , int num_vertex , const vec3& normal )

Создаёт выпуклый полигон.
### Аргументы

- *const vec3** **v** - Указатель на массив вершин.
- *int* **num_vertex** - Количество вершин. > **Notice:** Должно быть больше или равно 3.
- *const vec3&* **normal** - Нормаль полигона.

### Возвращаемое значение

true, если выпуклый полигон был успешно создан; иначе false.
## bool createConvex ( const Vector < vec3 >& v , const vec3& normal )

Создаёт выпуклый полигон.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec3](../../../api/library/math/class.vec3_cpp.md)>&* **v** - Вектор вершин полигона.
- *const vec3&* **normal** - Нормаль полигона.

### Возвращаемое значение

true, если выпуклый полигон был успешно создан; иначе false.
## bool createConcave ( const vec3* v , int num_vertex , const vec3& normal )

Создаёт вогнутый полигон.
### Аргументы

- *const vec3** **v** - Указатель на массив вершин.
- *int* **num_vertex** - Количество вершин. > **Notice:** Должно быть больше или равно 3.
- *const vec3&* **normal** - Нормаль полигона.

### Возвращаемое значение

true, если вогнутый полигон был успешно создан; иначе false.
## bool createConcave ( const Vector < vec3 >& v , const vec3& normal )

Создаёт вогнутый полигон.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[vec3](../../../api/library/math/class.vec3_cpp.md)>&* **v** - Вектор вершин полигона.
- *const vec3&* **normal** - Нормаль полигона.

### Возвращаемое значение

true, если вогнутый полигон был успешно создан; иначе false.
## int getNumVertex ( ) const

Возвращает количество вершин.
### Возвращаемое значение

Количество вершин.
## const vec3 & getVertex ( int num ) const

Возвращает вершину с заданным номером.
### Аргументы

- *int* **num** - Номер вершины.

### Возвращаемое значение

Результирующая вершина.
## int getVertexIndex ( int num ) const

Возвращает индекс вершины с заданным номером.
### Аргументы

- *int* **num** - Номер вершины.

### Возвращаемое значение

Индекс вершины.
## int getNumIndices ( ) const

Возвращает количество индексов.
### Возвращаемое значение

Количество индексов.
## int getIndex ( int num ) const

Возвращает индекс с заданным номером.
### Аргументы

- *int* **num** - Номер индекса.

### Возвращаемое значение

Результирующий индекс.
