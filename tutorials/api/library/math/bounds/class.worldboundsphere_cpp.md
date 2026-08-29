# Unigine::WorldBoundSphere Struct (CPP)

**Header:** #include <UnigineMathLibBounds.h>


Эта структура служит для построения ограничивающей сферы в координатах двойной точности.


Используя эту структуру, можно легко найти общую ограничивающую сферу для нескольких объектов путём её расширения.


## Класс WorldBoundSphere

### Методы класса

---

## static WorldBoundSpherePtr create ( )

Конструктор. Создаёт пустую ограничивающую сферу.
## WorldBoundSphere ( double x , double y , double z , double radius )

Конструктор. Инициализация координатами центра и радиусом ограничивающей сферы.
### Аргументы

- *double* **x** - Координата X центра ограничивающей сферы.
- *double* **y** - Координата Y центра ограничивающей сферы.
- *double* **z** - Координата Z центра ограничивающей сферы.
- *double* **radius** - Радиус ограничивающей сферы.

## WorldBoundSphere ( Math:: Vec3 & center , Math::Scalar radius )

Конструктор. Инициализирует ограничивающую сферу центром и радиусом ограничивающей сферы.
### Аргументы

- *Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **center** - Центр ограничивающей сферы.
- *Math::Scalar* **radius** - Радиус ограничивающей сферы.

## WorldBoundSphere ( const dvec3 * points , int num_points , bool optimal )

Конструктор. Инициализация вектором точек.
### Аргументы

- *const [dvec3](../../../../api/library/math/class.dvec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек в векторе.
- *bool* **optimal** - Флаг, определяющий, следует ли использовать оптимальную сферу. Если false, сфера будет расширена для включения всех заданных точек.

## WorldBoundSphere ( const WorldBoundSphere & bs )

Конструктор. Инициализирует заданной ограничивающей сферой.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## WorldBoundSphere ( const WorldBoundSphere & bs , const Math:: Mat4 & transform )

Инициализация ограничивающей сферой с заданием указанной матрицы трансформации для новой ограничивающей сферы.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## WorldBoundSphere ( const BoundSphere & bs )

Конструктор. Инициализирует заданной ограничивающей сферой.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## WorldBoundSphere ( const BoundSphere & bs , const Math:: Mat4 & transform )

Инициализация ограничивающей сферой с заданием указанной матрицы трансформации для новой ограничивающей сферы.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## WorldBoundSphere ( const WorldBoundBox & bb )

Конструктор. Инициализирует заданным ограничивающим параллелепипедом.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

## WorldBoundSphere & operator= ( const WorldBoundSphere & bs )

Оператор присваивания для ограничивающей сферы.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void clear ( )

Очищает ограничивающую сферу.
## void setCenter ( const dvec3 & center )

Задаёт указанные координаты для центра ограничивающей сферы.
### Аргументы

- *const [dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **center** - Координаты центра ограничивающей сферы.

## void set ( const Math:: Vec3 & center , Math::Scalar radius )

Задаёт ограничивающую сферу её центром и радиусом.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **center** - Центр ограничивающей сферы.
- *Math::Scalar* **radius** - Радиус ограничивающей сферы.

## void set ( double x_ , double y_ , double z_ , double radius_ )

Задаёт ограничивающую сферу указанными координатами центра и радиусом.
### Аргументы

- *double* **x_** - Координата X центра ограничивающей сферы.
- *double* **y_** - Координата Y центра ограничивающей сферы.
- *double* **z_** - Координата Z центра ограничивающей сферы.
- *double* **radius_** - Радиус ограничивающей сферы.

## void set ( const Math:: Vec3 * points , int num_points , bool optimal )

Задаёт ограничивающую сферу вектором точек.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек в векторе.
- *bool* **optimal** - Флаг, определяющий, следует ли использовать оптимальную сферу. Если **false**, сфера будет расширена для включения всех заданных точек.

## void set ( const WorldBoundSphere & bs )

Задаёт ограничивающую сферу.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void set ( const WorldBoundSphere & bs , const Math:: Mat4 & transform )

Задаёт ограничивающую сферу другой ограничивающей сферой с учётом матрицы трансформации.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## void set ( const BoundSphere & bs )

Задаёт ограничивающую сферу.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void set ( const BoundSphere & bs , const Math:: Mat4 & transform )

Задаёт ограничивающую сферу другой ограничивающей сферой с учётом матрицы трансформации.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## void set ( const WorldBoundBox & bb )

Задаёт ограничивающую сферу ограничивающим параллелепипедом.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

## bool isValid ( ) const

Проверяет статус ограничивающей сферы.
### Возвращаемое значение

**true**, если радиус ограничивающей сферы имеет положительное значение.
## void setTransform ( const Math:: Mat4 & transform )

Задаёт указанную матрицу трансформации для ограничивающей сферы.
### Аргументы

- *const  Math::[Mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## int compare ( const WorldBoundSphere & bs )

Сравнивает ограничивающую сферу с заданной. Степень точности равна **1.0e-6f**.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера для сравнения.

### Возвращаемое значение

**1**, если радиусы и центры обеих ограничивающих сфер равны; иначе **0**.
## int operator== ( const WorldBoundSphere & bs ) const

Сравнивает ограничивающую сферу с заданной с точностью, равной **1.0e-6f**.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера для сравнения.

### Возвращаемое значение

**1**, если радиусы и центры обеих ограничивающих сфер равны; иначе **0**.
## int operator!= ( const WorldBoundSphere & bs ) const

Оператор сравнения ограничивающих сфер на неравенство.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера для сравнения.

### Возвращаемое значение

**1**, если радиусы и центры обеих ограничивающих сфер не равны; иначе **0**.
## void expand ( const Math:: Vec3 & point )

Расширяет текущую ограничивающую сферу для включения заданной точки.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

## void expand ( const Math:: Vec3 * points , int num_points )

Расширяет текущую ограничивающую сферу для включения всех точек вектора.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек.

## void expand ( const WorldBoundSphere & bs )

Расширяет текущую ограничивающую сферу для включения заданной ограничивающей сферы.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void expand ( const WorldBoundBox & bb )

Расширяет текущую ограничивающую сферу для включения заданного ограничивающего параллелепипеда.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

## void expandRadius ( const Math:: Vec3 & point )

Расширяет радиус ограничивающей сферы.
```cpp
float r = length(center - point);
if (center.w < r)
	radius = r;

```


### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки, задающей конечную точку радиуса.

## void expandRadius ( const Math:: Vec3 * points , int num_points )

Расширяет радиус текущей ограничивающей сферы для включения всех точек вектора.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек.

## void expandRadius ( const WorldBoundSphere & bs )

Расширяет радиус ограничивающей сферы, используя радиус заданной ограничивающей сферы.
```cpp
double r = length(bs.center - center) + bs.radius;
if (radius < r)
	radius = r;

```


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void expandRadius ( const BoundBox & bb )

Расширяет радиус ограничивающей сферы, используя максимальную и минимальную точки заданного ограничивающего параллелепипеда.
### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

## int inside ( const Math:: Vec3 & point ) const

Проверяет, находится ли заданная точка внутри текущей ограничивающей сферы.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

### Возвращаемое значение

**1**, если заданная точка находится внутри ограничивающей сферы; иначе **0**.
## int inside ( const Math:: Vec3 & point , Math::Scalar radius ) const

Проверяет, находится ли сфера внутри ограничивающей сферы.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты центра сферы.
- *Math::Scalar* **radius** - Радиус сферы.

### Возвращаемое значение

**1**, если сфера находится внутри ограничивающей сферы; иначе **0**.
## int inside ( const Math:: Vec3 & min , const Math:: Vec3 & max ) const

Проверяет, находится ли параллелепипед внутри ограничивающей сферы.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальные координаты параллелепипеда.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальные координаты параллелепипеда.

### Возвращаемое значение

**1**, если параллелепипед находится внутри ограничивающей сферы; иначе **0**.
## int inside ( const WorldBoundSphere & bs ) const

Проверяет, находится ли заданная ограничивающая сфера внутри текущей ограничивающей сферы.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если заданная ограничивающая сфера находится внутри текущей ограничивающей сферы; иначе **0**.
## int inside ( const WorldBoundBox & bb ) const

Проверяет, находится ли ограничивающий параллелепипед внутри ограничивающей сферы.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если ограничивающий параллелепипед находится внутри ограничивающей сферы; иначе **0**.
## int insideValid ( const Math:: Vec3 & point ) const

Проверяет, находится ли заданная точка внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.

### Возвращаемое значение

**1**, если заданная точка находится внутри ограничивающей сферы; иначе **0**.
## int insideValid ( const Math:: Vec3 & point , Math::Scalar radius ) const

Проверяет, находится ли заданная сфера внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Центр сферы.
- *Math::Scalar* **radius** - Радиус сферы.

### Возвращаемое значение

**1**, если сфера находится внутри ограничивающей сферы; иначе **0**.
## int insideValid ( const Math:: Vec3 & min , const Math:: Vec3 & max ) const

Проверяет, находится ли параллелепипед внутри ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальные координаты параллелепипеда.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальные координаты параллелепипеда.

### Возвращаемое значение

**1**, если параллелепипед находится внутри ограничивающей сферы; иначе **0**.
## int insideValid ( const WorldBoundSphere & bs ) const

Проверяет, находится ли ограничивающая сфера внутри ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если ограничивающая сфера находится внутри ограничивающей сферы; иначе **0**.
## int insideValid ( const WorldBoundBox & bb ) const

Проверяет, находится ли ограничивающий параллелепипед внутри ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если ограничивающий параллелепипед находится внутри ограничивающей сферы; иначе **0**.
## int insideAll ( const WorldBoundSphere & bs ) const

Проверяет, находится ли целиком заданная ограничивающая сфера внутри текущей ограничивающей сферы.
### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если вся заданная сфера находится внутри текущей ограничивающей сферы; иначе **0**.
## int insideAll ( const WorldBoundBox & bb ) const

Проверяет, находится ли целиком ограничивающий параллелепипед внутри ограничивающей сферы.
### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если весь параллелепипед находится внутри ограничивающей сферы; иначе **0**.
## int insideAllValid ( const WorldBoundSphere & bs ) const

Проверяет, находится ли целиком заданная ограничивающая сфера внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**1**, если вся ограничивающая сфера находится внутри ограничивающей сферы; иначе **0**.
## int insideAllValid ( const WorldBoundBox & bb ) const

Проверяет, находится ли целиком заданный ограничивающий параллелепипед внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [WorldBoundBox](../../../../api/library/math/bounds/class.worldboundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**1**, если весь ограничивающий параллелепипед находится внутри ограничивающей сферы; иначе **0**.
## bool rayIntersection ( const Math:: Vec3 & point , const Math:: Vec3 & direction ) const

Проверяет пересечение луча с текущей ограничивающей сферой.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **direction** - Вектор направления луча.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## bool getIntersection ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 ) const

Проверяет пересечение линии с текущей ограничивающей сферой.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## bool rayIntersectionValid ( const Math:: Vec3 & point , const Math:: Vec3 & direction ) const

Проверяет пересечение луча с текущей ограничивающей сферой.
> **Notice:** Этот метод не проверяет, является ли текущая ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **direction** - Вектор направления луча.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## bool getIntersectionValid ( const Math:: Vec3 & p0 , const Math:: Vec3 & p1 ) const

Проверяет пересечение линии с текущей ограничивающей сферой.
> **Notice:** Этот метод не проверяет, является ли текущая ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## Math::Scalar distance ( ) const

Возвращает расстояние от начала координат до ближайшей точки текущей ограничивающей сферы.
### Возвращаемое значение

Расстояние от начала координат, в единицах.
## Math::Scalar distance ( const Math:: Vec3 & point ) const

Возвращает расстояние от заданной точки до ближайшей точки текущей ограничивающей сферы.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

### Возвращаемое значение

Расстояние от точки, в единицах.
## Math::Scalar distanceValid ( ) const

Возвращает расстояние от начала координат до ближайшей точки текущей ограничивающей сферы.
### Возвращаемое значение

Расстояние от начала координат, в единицах.
## Math::Scalar distanceValid ( const Math:: Vec3 & point ) const

Возвращает расстояние от заданной точки до ближайшей точки текущей ограничивающей сферы.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка

### Возвращаемое значение

Расстояние от точки, в единицах.
## bool isCameraVisible ( const Math:: Vec3 & camera , Math::Scalar min_distance , Math::Scalar max_distance ) const

Возвращает значение, указывающее, находится ли ограничивающая сфера в пределах видимости камеры.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **camera** - Координаты позиции камеры.
- *Math::Scalar* **min_distance** - Минимальное расстояние видимости, в метрах.
- *Math::Scalar* **max_distance** - Максимальное расстояние видимости, в метрах.

### Возвращаемое значение

**true**, если ограничивающая сфера находится в пределах видимости камеры; иначе **false**.
## WorldBoundSphere operator* ( const dmat4 & m , const WorldBoundSphere & bs )

Возвращает ограничивающую сферу с применённой заданной матрицей трансформации.
### Аргументы

- *const [dmat4](../../../../api/library/math/class.dmat4_cpp.md) &* **m** - Матрица трансформации.
- *const [WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

Ограничивающая сфера с заданной трансформацией.
