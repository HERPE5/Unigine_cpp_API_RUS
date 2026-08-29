# Unigine::Navigation Class (CPP)

**Header:** #include <UniginePathFinding.h>

**Inherits from:** Node


> **Warning:** Функция 3D-навигации является экспериментальной и не рекомендуется для использования в production.


Этот класс содержит функции, позволяющие получать или изменять параметры области навигации, в пределах которой выполняется поиск пути. Область навигации может быть либо [navigation sector](../../../api/library/pathfinding/class.navigationsector_cpp.md), либо [navigation mesh](../../../api/library/pathfinding/class.navigationmesh_cpp.md).


Например, с помощью функций этого класса можно [scale velocity](#setVelocity_float_void) точки, перемещающейся внутри области навигации. Также можно изменить [danger factor](#setDangerous_float_void) области.


#### См. также


- Статьи раздела [Navigation Area](../../../objects/navigations/navigation/index.md)
- Раздел *[Navigation](../../../sdk/api_samples/cpp/navigation.md)* в C++ Samples
- Раздел *[Navigation](../../../sdk/api_samples/cs/navigation.md)* в C# Component Samples
- Раздел *[Pathfinding](../../../code/uniginescript/samples/pathfinding.md)* в UnigineScript samples


## Navigation Class

### Методы класса

## void setVelocity ( float velocity )

Задаёт новый коэффициент масштабирования скорости точки, перемещающейся внутри области навигации по рассчитанному маршруту.
### Аргументы

- *float* **velocity** - Коэффициент масштабирования скорости.

## float getVelocity () const

Возвращает текущий коэффициент масштабирования скорости точки, перемещающейся внутри области навигации по рассчитанному маршруту.
### Возвращаемое значение

Текущий коэффициент масштабирования скорости.
## void setQuality ( int quality )

Задаёт новое качество оптимизации уже рассчитанного маршрута. Значение качества определяет количество итераций, используемых для спрямления пути.
### Аргументы

- *int* **quality** - Значение качества. Если указано отрицательное значение, вместо него используется 0.

## int getQuality () const

Возвращает текущее качество оптимизации уже рассчитанного маршрута. Значение качества определяет количество итераций, используемых для спрямления пути.
### Возвращаемое значение

Текущее значение качества. Если указано отрицательное значение, вместо него используется 0.
## int getNumNavigations () const

Возвращает текущее количество областей навигации, пересекающих текущую.
### Возвращаемое значение

Текущее количество связанных областей навигации.
## void setNavigationMask ( int mask )

Задаёт новую маску навигации области навигации. Маска навигации области навигации должна [match](../../../principles/bit_masking/index.md) the [navigation mask](../../../api/library/pathfinding/class.pathroute_cpp.md#setNavigationMask_int_void) маршрута, рассчитываемого в её пределах. В противном случае область не будет участвовать в поиске пути.
### Аргументы

- *int* **mask** - Целочисленное значение, каждый бит которого используется для задания маски.

## int getNavigationMask () const

Возвращает текущую маску навигации области навигации. Маска навигации области навигации должна [match](../../../principles/bit_masking/index.md) the [navigation mask](../../../api/library/pathfinding/class.pathroute_cpp.md#setNavigationMask_int_void) маршрута, рассчитываемого в её пределах. В противном случае область не будет участвовать в поиске пути.
### Возвращаемое значение

Текущее целочисленное значение, каждый бит которого используется для задания маски.
## void setDangerous ( float dangerous )

Задаёт новый фактор опасности, указывающий, должна ли точка, перемещающаяся внутри области навигации, стараться избегать этой области.
> **Notice:** Если фактор опасности превышает [maximum danger factor](../../../api/library/pathfinding/class.pathroute_cpp.md#setMaxDangerous_float_void), заданный для маршрута, область навигации будет исключена из расчётов поиска пути.


### Аргументы

- *float* **dangerous** - Фактор опасности.

## float getDangerous () const

Возвращает текущий фактор опасности, указывающий, должна ли точка, перемещающаяся внутри области навигации, стараться избегать этой области.
> **Notice:** Если фактор опасности превышает [maximum danger factor](../../../api/library/pathfinding/class.pathroute_cpp.md#setMaxDangerous_float_void), заданный для маршрута, область навигации будет исключена из расчётов поиска пути.


### Возвращаемое значение

Текущий фактор опасности.
---

## Ptr < Navigation > getNavigation ( int num )

Возвращает указанную связанную область навигации.
### Аргументы

- *int* **num** - Номер области навигации.

### Возвращаемое значение

Область навигации.
## int inside ( const Ptr < Navigation > & navigation )

Возвращает значение, указывающее, является ли указанная область Navigation частью данной области Navigation.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Navigation](../../../api/library/pathfinding/class.navigation_cpp.md)> &* **navigation** - Область навигации

## int inside2D ( const Math:: Vec3 & point , float radius )

В зависимости от типа области навигации функция выполняет следующее:
- Для *navigation sector* проверяет, находится ли заданная точка внутри navigation sector. Высота navigation sector (координата Z) игнорируется.
- Для *navigation mesh* проверяет, находится ли заданная точка внутри navigation mesh и находится ли расстояние от точки до mesh в диапазоне [-height;height]. Здесь height — высота navigation mesh.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.
- *float* **radius** - Радиус точки. Радиус используется для исключения выхода точки за пределы navigation mesh. Если радиус задан, вероятность того, что точка окажется внутри navigation mesh, выше. > **Notice:** При вызове функции для [NavigationSector](../../../api/library/pathfinding/class.navigationsector_cpp.md) этот параметр не имеет значения.

### Возвращаемое значение

**1**, если точка находится внутри области навигации; иначе **0**.
## int inside3D ( const Math:: Vec3 & point , float radius )

В зависимости от типа области навигации функция выполняет следующее:
- Для *navigation sector* проверяет, находится ли заданная точка внутри области навигации. Обратите внимание, что высота navigation sector (координата Z) также учитывается.
- Для *navigation mesh* проверяет, находится ли заданная точка внутри navigation mesh и находится ли расстояние от точки до mesh в диапазоне [0;height]. Здесь height — высота navigation mesh.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point** - Координаты точки.
- *float* **radius** - Радиус точки. Радиус используется для исключения выхода точки за пределы navigation mesh. Если радиус задан, вероятность того, что точка окажется внутри navigation mesh, выше. > **Notice:** При вызове функции для [NavigationSector](../../../api/library/pathfinding/class.navigationsector_cpp.md) этот параметр не имеет значения.

### Возвращаемое значение

**1**, если точка находится внутри области навигации; иначе **0**.
