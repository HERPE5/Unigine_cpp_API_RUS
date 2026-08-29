# Unigine::Ellipsoid Class (CPP)

**Header:** #include <UnigineEllipsoid.h>


Класс Ellipsoid выполняет геодезические преобразования:


- Задаёт настройки эллипсоида: большая полуось, коэффициент сжатия
- Выполняет преобразование систем координат (ECF, ENU, NED, Geodetic)
- Решает прямую и обратную геодезические задачи с разными режимами вычислений (алгоритмы Great Circle и Vincenty)


Этот класс используется для создания экземпляра Ellipsoid для класса [GeodeticPivot](../../../api/library/geodetics/class.geodeticpivot_cpp.md).


Ниже приведён фрагмент кода, демонстрирующий использование класса Ellipsoid:


```cpp
#include "UnigineMathLib.h"
#include "UnigineGeodetics.h"
#include "UnigineEllipsoid.h"

using namespace Unigine;
using namespace Unigine::Math;

/* ... */

// задаём геодезическое начало координат
dvec3 tomsk_origin = dvec3(58.49771, 84.97437, 117.0);

// создаём новый объект GeodeticPivot
GeodeticPivotPtr pivot = GeodeticPivot::create();

// создаём новый эллипсоид и задаём его настройки
EllipsoidPtr ellipsoid = pivot->getEllipsoid();
ellipsoid->setSemimajorAxis(80000.0f);
ellipsoid->setMode(Ellipsoid::MODE_FAST);

// устанавливаем эллипсоид для pivot
pivot->setOrigin(tomsk_origin);
pivot->setEllipsoid(ellipsoid);

```


## Ellipsoid Class

### Методы класса

---

## static EllipsoidPtr create ( double semimajor_axis , double flattening )

Конструктор. Создаёт новый экземпляр класса Ellipsoid с указанным коэффициентом сжатия и большой полуосью.
### Аргументы

- *double* **semimajor_axis** - Большая полуось.
- *double* **flattening** - Коэффициент сжатия.

## static EllipsoidPtr create ( )

Конструктор. Создаёт новый экземпляр класса Ellipsoid (эллипсоид WGS84).
## Math:: dvec3 getENUSurfacePoint ( const Math:: dvec3 & geodetic_origin , const Math:: dvec3 & tangent_point )

Возвращает точку поверхности с использованием координат касательной точки.
> **Notice:** Направление оси Up (Z+) в ENU указывает вверх вдоль нормали эллипсоида, тогда как в реализации ENU в UNIGINE оно идёт от центра Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **tangent_point** - Координаты касательной точки, преобразуемые (искривляемые) в координаты поверхности (смещение относительно точки соединения).

### Возвращаемое значение

Координаты точки поверхности.
## Math:: dvec3 getENUTangentPoint ( const Math:: dvec3 & geodetic_origin , const Math:: dvec3 & surface_point )

Возвращает координаты ENU касательной точки на основе географических координат.
> **Notice:** Направление оси Up (Z+) в ENU указывает вверх вдоль нормали эллипсоида, тогда как в реализации ENU в UNIGINE оно идёт от центра Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **surface_point** - Координаты точки поверхности, преобразуемые (уплощаемые) в касательную точку (смещение относительно точки соединения).

### Возвращаемое значение

Координаты касательной точки.
## Math:: quat getENUWorldRotation ( const Math:: dvec3 & geodetic_origin )

Возвращает кватернион мирового вращения в координатах ENU.
> **Notice:** Направление оси Up (Z+) в ENU указывает вверх вдоль нормали эллипсоида, тогда как в реализации ENU в UNIGINE оно идёт от центра Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).

### Возвращаемое значение

Мировое вращение в координатах ENU.
## Math:: dmat4 getENUWorldTransform ( const Math:: dvec3 & geodetic_origin )

Возвращает матрицу мирового преобразования в координатах ENU.
> **Notice:** Направление оси Up (Z+) в ENU указывает вверх вдоль нормали эллипсоида, тогда как в реализации ENU в UNIGINE оно идёт от центра Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).

### Возвращаемое значение

Матрица мирового преобразования в координатах ENU.
## void setFlattening ( double flattening )

Устанавливает новый коэффициент сжатия для эллипсоида.
### Аргументы

- *double* **flattening** - Коэффициент сжатия эллипсоида. Если значение равно 0, эллипсоид имеет форму сферы, при 1 эллипсоид имеет форму окружности (полностью плоскую).

## double getFlattening ( )

Возвращает коэффициент сжатия эллипсоида.
### Возвращаемое значение

Коэффициент сжатия эллипсоида.
## double getMeanRadius ( )

Возвращает средний радиус эллипсоида.
### Возвращаемое значение

Средний радиус эллипсоида.
## int isSupported ( )

Возвращает значение, указывающее, включена ли функция геодезии.
### Возвращаемое значение

1, если функция геодезии включена; иначе 0.
## void setMode ( int mode )

Устанавливает режим вычислений.
### Аргументы

- *int* **mode** - Переменная режима вычислений. Может принимать одно из следующих значений:

  - [MODE_FAST](#MODE_FAST)
  - [MODE_ACCURATE](#MODE_ACCURATE)

## int getMode ( )

Возвращает целочисленное значение режима вычислений: 1, если режим MODE_ACCURATE, 0, если режим MODE_FAST.
### Возвращаемое значение

1, если режим MODE_ACCURATE, 0, если режим MODE_FAST.
## Math:: dvec3 getNEDSurfacePoint ( const Math:: dvec3 & geodetic_origin , const Math:: dvec3 & tangent_point )

Возвращает точку поверхности с использованием координат касательной точки.
> **Notice:** Направление оси Down в NED указывает вниз вдоль нормали эллипсоида, тогда как в реализации NED в UNIGINE оно проходит через центр Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **tangent_point** - Координаты касательной точки, преобразуемые (искривляемые) в координаты поверхности (смещение относительно точки соединения).

### Возвращаемое значение

Координаты точки поверхности.
## Math:: dvec3 getNEDTangentPoint ( const Math:: dvec3 & geodetic_origin , const Math:: dvec3 & surface_point )

Возвращает координаты NED касательной точки на основе географических координат.
> **Notice:** Направление оси Down в NED указывает вниз вдоль нормали эллипсоида, тогда как в реализации NED в UNIGINE оно проходит через центр Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **surface_point** - Координаты точки поверхности, преобразуемые (уплощаемые) в касательную точку (смещение относительно точки соединения).

### Возвращаемое значение

Координаты касательной точки.
## Math:: quat getNEDWorldRotation ( const Math:: dvec3 & geodetic_origin )

Возвращает кватернион мирового вращения в координатах NED.
> **Notice:** Направление оси Down в NED указывает вниз вдоль нормали эллипсоида, тогда как в реализации NED в UNIGINE оно проходит через центр Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).

### Возвращаемое значение

Мировое вращение в координатах NED.
## Math:: dmat4 getNEDWorldTransform ( const Math:: dvec3 & geodetic_origin )

Возвращает матрицу мирового преобразования в координатах NED.
> **Notice:** Направление оси Down в NED указывает вниз вдоль нормали эллипсоида, тогда как в реализации NED в UNIGINE оно проходит через центр Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).

### Возвращаемое значение

Матрица мирового преобразования в координатах NED.
## void setSemimajorAxis ( double axis )

Устанавливает новую большую полуось эллипсоида.
### Аргументы

- *double* **axis** - Длина большой полуоси в единицах.

## double getSemimajorAxis ( )

Возвращает длину большой полуоси эллипсоида в единицах.
### Возвращаемое значение

Большая полуось эллипсоида.
## double getSemimajorEccentricitySqr ( )

Возвращает квадрат эксцентриситета, вычисленный вдоль большой полуоси.
### Возвращаемое значение

Квадрат эксцентриситета, вычисленный вдоль большой полуоси.
## double getSemiminorAxis ( )

Возвращает малую полуось эллипсоида в единицах.
### Возвращаемое значение

Малая полуось эллипсоида в единицах.
## double getSemiminorEccentricitySqr ( )

Возвращает квадрат эксцентриситета, вычисленный вдоль малой полуоси.
### Возвращаемое значение

Квадрат эксцентриситета, вычисленный вдоль малой полуоси.
## Math:: dvec3 solveGeodeticDirect ( const Math:: dvec3 & geodetic_start , double bearing , double distance )

Решает прямую геодезическую задачу: вычисляет координаты конечной точки на эллипсоиде, используя заданную начальную точку, расстояние между точками и значение азимута.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_start** - Начальная точка на эллипсоиде.
- *double* **bearing** - Значение азимута.
- *double* **distance** - Расстояние между двумя точками на эллипсоиде.

## void solveGeodeticInverse ( const Math:: dvec3 & geodetic_start , const Math:: dvec3 & geodetic_end , double & bearing , double & distance )

Решает обратную геодезическую задачу: вычисляет расстояние и значение азимута, используя заданные начальную и конечную точки на эллипсоиде.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_start** - Начальная точка на эллипсоиде.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_end** - Конечная точка на эллипсоиде.
- *double &* **bearing** - Переменная для сохранения вычисленного значения азимута.
- *double &* **distance** - Переменная для сохранения вычисленного значения расстояния.

## Math:: dvec3 toECF ( const Math:: dvec3 & geodetic_coords )

Преобразует геодезические координаты в декартовы (ECF).
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coords** - Координаты эллипсоида (широта (градусы), долгота (градусы) и высота (метры)), преобразуемые в декартовы.

### Возвращаемое значение

Декартовы координаты.
## Math:: dvec3 toENU ( const Math:: dvec3 & geodetic_origin , const Math:: dvec3 & geodetic_coords )

Преобразует геодезические координаты в ENU (восток, север, вверх).
> **Notice:** Направление оси Up (Z+) в ENU указывает вверх вдоль нормали эллипсоида, тогда как в реализации ENU в UNIGINE оно идёт от центра Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coords** - Координаты, преобразуемые в ENU.

### Возвращаемое значение

Координаты ENU.
## Math:: dvec3 toGeodetic ( const Math:: dvec3 & ecf_coords , int need_alt = 1 )

Преобразует декартовы координаты (ECF) в координаты эллипсоида.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ecf_coords** - Декартовы координаты ECF, преобразуемые в координаты эллипсоида.
- *int* **need_alt** - Флаг, указывающий, нужно ли вычислять высоту. 1 — вычислять высоту, 0 — пропустить вычисление высоты. Значение по умолчанию — 1.

### Возвращаемое значение

Координаты эллипсоида (широта (градусы), долгота (градусы) и высота (метры)
## Math:: dvec3 toNED ( const Math:: dvec3 & geodetic_origin , const Math:: dvec3 & geodetic_coords )

Преобразует геодезические координаты в NED (север, восток, вниз).
> **Notice:** Направление оси Down в NED указывает вниз вдоль нормали эллипсоида, тогда как в реализации NED в UNIGINE оно проходит через центр Земли.

### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_origin** - Начало координат в координатах эллипсоида (широта (градусы), долгота (градусы) и высота (метры)).
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coords** - Координаты, преобразуемые в NED.

### Возвращаемое значение

Координаты NED.
