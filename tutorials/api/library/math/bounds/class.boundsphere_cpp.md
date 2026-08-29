# Unigine::BoundSphere Struct (CPP)

**Header:** #include <UnigineMathLibBounds.h>


Эта структура служит для построения ограничивающей сферы в координатах одинарной точности.

> **Notice:** Экземпляры этой структуры автоматически удаляются, когда это необходимо.


В случае координат двойной точности ограничивающую сферу следует строить с использованием структуры **[WorldBoundSphere](../../../../api/library/math/bounds/class.worldboundsphere_cpp.md)**. Она включает те же функции, что и структура *BoundSphere*, но её функции работают с координатами двойной точности.


> **Notice:** Для поддержки как сборок с одинарной, так и с двойной точностью можно использовать только структуру *WorldBoundSphere*. Движок автоматически заменит её на *BoundSphere*, если это потребуется.


## Класс BoundSphere

### Методы класса

---

## BoundSphere ( )

Конструктор. Создаёт пустую ограничивающую сферу.
## BoundSphere ( const vec3 & center , float radius )

Конструктор. Инициализация центром и радиусом ограничивающей сферы.
### Аргументы

- *const [vec3](../../../../api/library/math/class.vec3_cpp.md) &* **center** - Центр ограничивающей сферы.
- *float* **radius** - Радиус ограничивающей сферы.

## BoundSphere ( float x , float y , float z , float radius )

Конструктор. Инициализация координатами центра и радиусом ограничивающей сферы.
### Аргументы

- *float* **x** - Координата X центра ограничивающей сферы.
- *float* **y** - Координата Y центра ограничивающей сферы.
- *float* **z** - Координата Z центра ограничивающей сферы.
- *float* **radius** - Радиус ограничивающей сферы.

## BoundSphere ( const vec3 * points , int num_points , bool optimal )

Конструктор. Инициализация вектором точек.
### Аргументы

- *const [vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек в векторе.
- *bool* **optimal** - Флаг, определяющий, следует ли использовать оптимальную сферу. Если false, сфера будет расширена для включения всех заданных точек.

## BoundSphere ( const BoundSphere & bs )

Инициализация ограничивающей сферой.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## BoundSphere ( const BoundSphere & bs , const mat4 & transform )

Конструктор. Инициализация ограничивающей сферой с заданием указанной матрицы трансформации для новой ограничивающей сферы.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const [mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## explicit BoundSphere ( const BoundBox & bb )

Конструктор. Инициализация ограничивающим параллелепипедом.
### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

## BoundSphere & operator= ( const BoundSphere & bs )

Оператор присваивания для ограничивающей сферы.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void clear ( )

Очищает ограничивающую сферу.
## void set ( const Math:: vec3 & center , float radius )

Задаёт ограничивающую сферу её центром и радиусом.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **center** - Центр ограничивающей сферы.
- *float* **radius** - Радиус ограничивающей сферы.

## void set ( float x_ , float y_ , float z_ , float radius_ )

Задаёт ограничивающую сферу указанными координатами центра и радиусом.
### Аргументы

- *float* **x_** - Координата X центра ограничивающей сферы.
- *float* **y_** - Координата Y центра ограничивающей сферы.
- *float* **z_** - Координата Z центра ограничивающей сферы.
- *float* **radius_** - Радиус ограничивающей сферы.

## void set ( const Math:: vec3 * points , int num_points , bool optimal )

Задаёт ограничивающую сферу вектором точек.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек в векторе.
- *bool* **optimal** - Флаг, определяющий, следует ли использовать оптимальную сферу. Если **false**, сфера будет расширена для включения всех заданных точек.

## void set ( const BoundSphere & bs )

Задаёт ограничивающую сферу.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void set ( const BoundSphere & bs , const Math:: mat4 & transform )

Задаёт ограничивающую сферу другой ограничивающей сферой с учётом матрицы трансформации.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.
- *const  Math::[mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## void set ( const BoundBox & bb )

Задаёт ограничивающую сферу ограничивающим параллелепипедом.
### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

## void setCenter ( const vec3& center )

Задаёт указанные координаты для центра ограничивающей сферы.
### Аргументы

- *const vec3&* **center** - Координаты центра ограничивающей сферы.

## void setTransform ( const Math:: mat4 & transform )

Задаёт указанную матрицу трансформации для ограничивающей сферы.
### Аргументы

- *const  Math::[mat4](../../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## void setTransform ( const Math:: dmat4 & transform )

Задаёт указанную матрицу трансформации для ограничивающей сферы.
### Аргументы

- *const  Math::[dmat4](../../../../api/library/math/class.dmat4_cpp.md) &* **transform** - Матрица трансформации.

## int compare ( const BoundSphere & bs )

Сравнивает ограничивающую сферу с заданной. Степень точности равна **1.0e-6f**.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера для сравнения.

### Возвращаемое значение

**1**, если радиусы и центры обеих ограничивающих сфер равны; иначе **0**.
## int operator== ( const BoundSphere & bs ) const

Сравнивает ограничивающую сферу с заданной с точностью, равной **1.0e-6f**.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера для сравнения.

### Возвращаемое значение

**1**, если радиусы и центры обеих ограничивающих сфер равны; иначе **0**.
## int operator!= ( const BoundSphere & bs ) const

Оператор сравнения ограничивающих сфер на неравенство.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера для сравнения.

### Возвращаемое значение

**1**, если радиусы и центры обеих ограничивающих сфер не равны; иначе **0**.
## BoundSphere operator* ( const mat4 & m , const BoundSphere & bs )

Возвращает ограничивающую сферу с применённой заданной матрицей трансформации.
### Аргументы

- *const [mat4](../../../../api/library/math/class.mat4_cpp.md) &* **m** - Матрица трансформации.
- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

Ограничивающая сфера с заданной трансформацией.
## BoundSphere operator* ( const dmat4 & m , const BoundSphere & bs )

Возвращает ограничивающую сферу с применённой заданной матрицей трансформации.
### Аргументы

- *const [dmat4](../../../../api/library/math/class.dmat4_cpp.md) &* **m** - Матрица трансформации.
- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

Ограничивающая сфера с заданной трансформацией.
## void expand ( const Math:: vec3 & point )

Расширяет текущую ограничивающую сферу так, чтобы она включала заданную точку.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

## void expand ( const Math:: vec3 * points , int num_points )

Расширяет текущую ограничивающую сферу для включения всех точек вектора.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек.

## void expand ( const BoundSphere & bs )

Расширяет текущую ограничивающую сферу так, чтобы она включала заданную ограничивающую сферу.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера для включения.

## void expand ( const BoundBox & bb )

Расширяет текущую ограничивающую сферу так, чтобы она включала заданный ограничивающий параллелепипед.
### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед для включения.

## void expandRadius ( const Math:: vec3 & point )

Расширяет радиус ограничивающей сферы.
```cpp
float r = length(center - point);
if (center.w < r)
	radius = r;

```


### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки, задающей конечную точку радиуса.

## void expandRadius ( const Math:: vec3 * points , int num_points )

Расширяет радиус текущей ограничивающей сферы для включения всех точек вектора.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) ** **points** - Вектор точек.
- *int* **num_points** - Количество точек.

## void expandRadius ( const BoundSphere & bs )

Расширяет радиус ограничивающей сферы, используя радиус заданной ограничивающей сферы.
```cpp
float r = length(bs.center - center) + bs.radius;
if (radius < r)
	radius = r;

```


### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

## void expandRadius ( const BoundBox & bb )

Расширяет радиус ограничивающей сферы, используя максимальную и минимальную точки заданного ограничивающего параллелепипеда. Использует метод [expandRadius](#expandRadius_const_vec3_ref_void).
```cpp
const vec3 &min = bb.getMin();
const vec3 &max = bb.getMax();
expandRadius(vec3(min.x, min.y, min.z));
expandRadius(vec3(max.x, min.y, min.z));
expandRadius(vec3(min.x, max.y, min.z));
expandRadius(vec3(max.x, max.y, min.z));
expandRadius(vec3(min.x, min.y, max.z));
expandRadius(vec3(max.x, min.y, max.z));
expandRadius(vec3(min.x, max.y, max.z));
expandRadius(vec3(max.x, max.y, max.z));

```


### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

## bool inside ( const Math:: vec3 & point ) const

Проверяет, находится ли заданная точка внутри текущей ограничивающей сферы.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

### Возвращаемое значение

**true**, если заданная точка находится внутри ограничивающей сферы; иначе **false**.
## bool inside ( const Math:: vec3 & point , float radius ) const

Проверяет, находится ли сфера внутри ограничивающей сферы.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Центр сферы.
- *float* **radius** - Радиус сферы.

### Возвращаемое значение

**true**, если сфера находится внутри ограничивающей сферы; иначе **false**.
## bool inside ( const Math:: vec3 & min , const Math:: vec3 & max ) const

Проверяет, находится ли параллелепипед внутри ограничивающей сферы.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальные координаты параллелепипеда.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальные координаты параллелепипеда.

### Возвращаемое значение

**true**, если параллелепипед находится внутри ограничивающей сферы; иначе **false**.
## bool inside ( const BoundSphere & bs ) const

Проверяет, находится ли заданная ограничивающая сфера внутри ограничивающей сферы.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**true**, если заданная ограничивающая сфера находится внутри ограничивающей сферы; иначе **false**.
## bool inside ( const BoundBox & bb ) const

Проверяет, находится ли ограничивающий параллелепипед внутри ограничивающей сферы.
### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**true**, если ограничивающий параллелепипед находится внутри ограничивающей сферы; иначе **false**.
## bool insideValid ( const Math:: vec3 & point ) const

Проверяет, находится ли заданная точка внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка.

### Возвращаемое значение

**true**, если заданная точка находится внутри ограничивающей сферы; иначе **false**.
## bool insideValid ( const Math:: vec3 & point , float radius ) const

Проверяет, находится ли заданная сфера внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Центр сферы.
- *float* **radius** - Радиус сферы.

### Возвращаемое значение

**true**, если сфера находится внутри ограничивающей сферы; иначе **false**.
## bool insideValid ( const Math:: vec3 & min , const Math:: vec3 & max ) const

Проверяет, находится ли параллелепипед внутри ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **min** - Минимальные координаты параллелепипеда.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **max** - Максимальные координаты параллелепипеда.

### Возвращаемое значение

**true**, если параллелепипед находится внутри ограничивающей сферы; иначе **false**.
## bool insideValid ( const BoundSphere & bs ) const

Проверяет, находится ли ограничивающая сфера внутри ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**true**, если ограничивающая сфера находится внутри ограничивающей сферы; иначе **false**.
## bool insideValid ( const BoundBox & bb ) const

Проверяет, находится ли ограничивающий параллелепипед внутри ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**true**, если ограничивающий параллелепипед находится внутри ограничивающей сферы; иначе **false**.
## bool insideAll ( const BoundSphere & bs ) const

Проверяет, находится ли вся заданная ограничивающая сфера внутри текущей ограничивающей сферы.
### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**true**, если вся ограничивающая сфера находится внутри ограничивающей сферы; иначе **false**.
## bool insideAll ( const BoundBox & bb ) const

Проверяет, находится ли весь заданный ограничивающий параллелепипед внутри текущей ограничивающей сферы.
### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**true**, если весь ограничивающий параллелепипед находится внутри ограничивающей сферы; иначе **false**.
## bool insideAllValid ( const BoundSphere & bs ) const

Проверяет, находится ли вся заданная ограничивающая сфера внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [BoundSphere](../../../../api/library/math/bounds/class.boundsphere_cpp.md) &* **bs** - Ограничивающая сфера.

### Возвращаемое значение

**true**, если вся ограничивающая сфера находится внутри ограничивающей сферы; иначе **false**.
## bool insideAllValid ( const BoundBox & bb ) const

Проверяет, находится ли весь заданный ограничивающий параллелепипед внутри текущей ограничивающей сферы.
> **Notice:** Метод не проверяет, является ли ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const [BoundBox](../../../../api/library/math/bounds/class.boundbox_cpp.md) &* **bb** - Ограничивающий параллелепипед.

### Возвращаемое значение

**true**, если весь ограничивающий параллелепипед находится внутри ограничивающей сферы; иначе **false**.
## bool rayIntersection ( const Math:: vec3 & point , const Math:: vec3 & direction ) const

Проверяет пересечение луча с текущей ограничивающей сферой.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **direction** - Вектор направления луча.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## bool getIntersection ( const Math:: vec3 & p0 , const Math:: vec3 & p1 ) const

Проверяет пересечение линии с текущей ограничивающей сферой.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## bool rayIntersectionValid ( const Math:: vec3 & point , const Math:: vec3 & direction ) const

Проверяет пересечение луча с текущей ограничивающей сферой.
> **Notice:** Этот метод не проверяет, является ли текущая ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Начальная точка луча.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **direction** - Вектор направления луча.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## bool getIntersectionValid ( const Math:: vec3 & p0 , const Math:: vec3 & p1 ) const

Проверяет пересечение линии с текущей ограничивающей сферой.
> **Notice:** Этот метод не проверяет, является ли текущая ограничивающая сфера допустимой (имеет положительный радиус).


### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p0** - Начальная точка линии.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **p1** - Конечная точка линии.

### Возвращаемое значение

**true**, если пересечение произошло; иначе **false**.
## float distance ( ) const

Возвращает расстояние от начала координат до ближайшей точки текущей ограничивающей сферы.
### Возвращаемое значение

Расстояние от начала координат, в единицах.
## float distance ( const Math:: vec3 & point ) const

Возвращает расстояние от заданной точки до ближайшей точки текущей ограничивающей сферы.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.

### Возвращаемое значение

Расстояние от точки, в единицах.
## float distanceValid ( ) const

Возвращает расстояние от начала координат до ближайшей точки текущей ограничивающей сферы.
### Возвращаемое значение

Расстояние от начала координат, в единицах.
## float distanceValid ( const Math:: vec3 & point ) const

Возвращает расстояние от заданной точки до ближайшей точки текущей ограничивающей сферы.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **point** - Точка

### Возвращаемое значение

Расстояние от точки, в единицах.
## bool isValid ( ) const

Проверяет статус ограничивающей сферы.
### Возвращаемое значение

**true**, если радиус ограничивающей сферы имеет положительное значение; иначе **false**.
## bool isCameraVisible ( const vec3& camera , float min_distance , float max_distance ) const

Возвращает значение, указывающее, находится ли ограничивающая сфера в пределах видимости камеры.
### Аргументы

- *const vec3&* **camera** - Координаты позиции камеры.
- *float* **min_distance** - Минимальное расстояние видимости, в метрах.
- *float* **max_distance** - Максимальное расстояние видимости, в метрах.

### Возвращаемое значение

**true**, если ограничивающая сфера находится в пределах видимости камеры; иначе **false**.
