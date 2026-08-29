# Unigine::GeodeticPivot Class (CPP)

**Header:** #include <UnigineGeodeticPivot.h>

**Inherits from:** Node


Этот класс используется для создания и изменения объекта [geodetic pivot](../../../objects/geodetics/geodeticpivot/index.md), который используется для размещения объектов сцены в их реальных мировых позициях (широта, долгота и высота). Geodetic pivot содержит эллипсоид с точкой pivot.


> **Notice:** В редакциях UNIGINE SDK, отличных от Engineering и Sim, объект geodetic pivot эквивалентен [NodeDummy](../../../api/library/nodes/class.nodedummy_cpp.md).


**Важно:**


Если по какой-либо причине вам нужно получить трансформации сущности (например, позицию и вращение самолёта), чтобы использовать их для настройки камеры на этой сущности или любого луча, испускаемого этой сущностью к земле, или что-то подобное, необходимо учитывать следующее при использовании Geodetic Pivot:


- Ось Up начинается в предполагаемом центре модели Земли-эллипсоида и направлена наружу. ![](pivot_model.png)
- Когда объект смещается вверх вдоль этой оси, его мировые координаты X и Y также изменятся относительно спроецированного террейна (ожидаемое направление — серая линия, фактическое направление — оранжевая линия). ![](surface_fragment.png) Таким образом, если использовать напрямую трансформации, полученные от движка (например, мировые координаты самолёта для ориентации камеры), результат будет отличаться от ожидаемого.
- Чтобы получить скорректированные (и ожидаемые) трансформации, необходимо установить нормаль **на Geodetic** в соответствующем методе ([toWorld()](#toWorld_dvec3_int_dmat4), [toWorldPreserveRotation()](#toWorldPreserveRotation_mat4_dvec3_int_mat4)), необходимые пересчёты будут выполнены автоматически.


Ниже приведён пример простого конвертера, позволяющего преобразовывать геодезические координаты в мировые и обратно:


```cpp
class Converter
{
public:
	static Converter *get()
	{
		static Converter instance;
		return &instance;
	}

	void init()
	{
		geodetic_pivot = static_ptr_cast<Unigine::GeodeticPivot>(Unigine::World::getNodeByType(Unigine::Node::GEODETIC_PIVOT));
		if (geodetic_pivot)
		{
			Unigine::ObjectTerrainGlobalPtr terrain_global = static_ptr_cast<Unigine::ObjectTerrainGlobal>(Unigine::World::getNodeByType(Unigine::Node::OBJECT_TERRAIN_GLOBAL));
			is_curved_terrain = terrain_global && terrain_global->findAncestor(Unigine::Node::GEODETIC_PIVOT) != -1;
		}

		inited = geodetic_pivot.isValid();
	}

	Unigine::Math::dvec3 worldToGeodetic(const Unigine::Math::Vec3 &world_pos) const
	{
		UNIGINE_ASSERT(inited && "Converter is not initialized!");

		if (is_curved_terrain)
			return geodetic_pivot->toGeodetic(translate(world_pos));
		return geodetic_pivot->mapFlatToGeodetic(world_pos);
	}

	Unigine::Math::Vec3 geodeticToWorld(const Unigine::Math::dvec3 &geo_pos) const
	{
		UNIGINE_ASSERT(inited && "Converter is not initialized!");

		if (is_curved_terrain)
			return Unigine::Math::Vec3(geodetic_pivot->toWorld(geo_pos).getTranslate());
		return Unigine::Math::Vec3(geodetic_pivot->mapGeodeticToFlat(geo_pos));
	}

	Unigine::Math::Mat4 getZeroBasis(const Unigine::Math::dvec3 &geo_pos) const
	{
		UNIGINE_ASSERT(inited && "Converter is not initialized!");

		if (is_curved_terrain)
			return geodetic_pivot->toWorld(geo_pos, Unigine::GeodeticPivot::UP_AXIS_GEODETIC_NORMAL);

		// преобразуем изогнутое вращение в плоское (forward.z = 0)
		Unigine::Math::dmat4 transform = geodetic_pivot->toWorld(geo_pos, Unigine::GeodeticPivot::UP_AXIS_GEODETIC_NORMAL);
		Unigine::Math::dvec3 up = Unigine::Math::dvec3_up;
		Unigine::Math::dvec3 forward = transform.getColumn3(1);
		forward.z = 0;
		forward = normalize(forward);
		Unigine::Math::dvec3 right = cross(forward, up);
		transform.setColumn3(0, right);
		transform.setColumn3(1, forward);
		transform.setColumn3(2, up);
		return Unigine::Math::Mat4(transform);
	}

private:
	Converter() = default;
	~Converter() = default;

	bool inited = false;
	bool is_curved_terrain = false;
	Unigine::GeodeticPivotPtr geodetic_pivot;
};

```


Чтобы использовать этот класс *Converter*:


```cpp
Converter::get()->init(); // вызывается в world::init

// в любом месте кода
Conveter::get()->worldToGeodetic ...

```


### См. также


Пример UnigineScript


## GeodeticPivot Class

### Перечисления

## UP_AXIS

| Name | Description |
|---|---|
| **UP_AXIS_GEOCENTRIC_NORMAL** = 0 | Ось Up выровнена с линией, начинающейся из центра Земли. |
| **UP_AXIS_GEODETIC_NORMAL** = 1 | Ось Up выровнена с нормалью к поверхности. Переключение на этот тип оси требуется, если полученные координаты будут использоваться для установки трансформаций чего-либо относительно сущности (например, камеры на самолёте или лазерного луча от самолёта). |

### Методы класса

---

## static GeodeticPivotPtr create ( )

Конструктор GeodeticPivot. Создаёт экземпляр GeodeticPivot с настройками по умолчанию:
- Начало координат установлено в dvec3(0.0,0.0,0.0).
- Размер области искривления — 2048000×2048000 км.
- Разрешение текстуры области — 2048.


## void setEllipsoid ( const Ptr < Ellipsoid > & ellipsoid )

Устанавливает эллипсоид, используемый для Geodetic Pivot.
> **Notice:** Прямое изменение эллипсоида Geodetic Pivot делает состояние pivot несогласованным. Следует принудительно обновить внутреннее состояние узла GeodeticPivot в соответствии с изменённым эллипсоидом, установив его через метод *setEllipsoid()*.


```cpp
// создаём новый geodetic pivot
GeodeticPivotPtr pivot = GeodeticPivot::create();

// задаём для него локальный (X - Y - Z) базис начала координат
pivot->setOriginBasis(GeodeticPivot::ORIGIN_BASIS_LOCAL);

// получаем эллипсоид, используемый в данный момент geodetic pivot
EllipsoidPtr ellipsoid = pivot->getEllipsoid();

// задаём быстрый режим вычислений для эллипсоида
ellipsoid->setMode(Ellipsoid::MODE_FAST);

// задаём новую большую полуось для эллипсоида
ellipsoid->setSemimajorAxis(6378137.0f - 500.0f);

/* ... */

// принудительно обновляем geodetic pivot в соответствии с изменённым эллипсоидом
pivot->setEllipsoid(ellipsoid);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Ellipsoid](../../../api/library/geodetics/class.ellipsoid_cpp.md)> &* **ellipsoid** - Устанавливаемый эллипсоид.

## Ptr < Ellipsoid > getEllipsoid ( )

Возвращает эллипсоид, используемый в данный момент Geodetic Pivot.
> **Notice:** Прямое изменение эллипсоида Geodetic Pivot делает состояние pivot несогласованным. Следует принудительно обновить внутреннее состояние узла GeodeticPivot в соответствии с изменённым эллипсоидом, установив его через метод [*setEllipsoid()*](#setEllipsoid_Ellipsoid_void).


```cpp
// создаём новый geodetic pivot
GeodeticPivotPtr pivot = GeodeticPivot::create();

// задаём для него локальный (X - Y - Z) базис начала координат
pivot->setOriginBasis(GeodeticPivot::ORIGIN_BASIS_LOCAL);

// получаем эллипсоид, используемый в данный момент geodetic pivot
EllipsoidPtr ellipsoid = pivot->getEllipsoid();

// задаём быстрый режим вычислений для эллипсоида
ellipsoid->setMode(Ellipsoid::MODE_FAST);

// задаём новую большую полуось для эллипсоида
ellipsoid->setSemimajorAxis(6378137.0f - 500.0f);

/* ... */

// принудительно обновляем geodetic pivot в соответствии с изменённым эллипсоидом
pivot->setEllipsoid(ellipsoid);

```


### Возвращаемое значение

Эллипсоид, используемый в данный момент Geodetic Pivot.
## void setOrigin ( const Math:: dvec3 & origin )

Устанавливает новую позицию (широта, долгота и высота) на эллипсоиде.
```cpp
// по умолчанию GeodeticPivot будет использовать эталонный эллипсоид WGS84
GeodeticPivotPtr pivot = GeodeticPivot::create();
// обновляем начало координат
dvec3 new_york_origin = dvec3(40.71427,-74.00597,57.0);
pivot->setOrigin(new_york_origin);
ObjectMeshStaticPtr flat_new_york_ground = ObjectMeshStatic::create("flat_new_york_ground.mesh");
pivot->addChild(flat_new_york_ground); // меш будет изогнут, как только ObjectMeshStatic станет дочерним для GeodeticPivot

```


### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **origin** - Вектор начала координат в координатах эллипсоида.

## Math:: dvec3 getOrigin ( )

Возвращает позицию (широта, долгота и высота) на эллипсоиде.
### Возвращаемое значение

Вектор начала координат в координатах эллипсоида.
## void setOriginBasis ( int basis )

Устанавливает новый [origin basis](#ORIGIN_BASIS_ENU) для объекта GeodeticPivot:
- Если установлен [ORIGIN_BASIS_LOCAL](#ORIGIN_BASIS_LOCAL), привязка к геокоординатам отключена. GeodeticPivot можно разместить где угодно.
- Если установлен [ORIGIN_BASIS_ENU](#ORIGIN_BASIS_ENU), GeodeticPivot размещается в мировой позиции ECF с ориентацией ENU (восток - север - вверх) согласно заданной широте / долготе / высоте. Позиция GeodeticPivot заблокирована. > **Notice:** Направление оси Up (Z+) в ENU указывает вверх вдоль нормали эллипсоида, тогда как в реализации ENU в UNIGINE оно идёт от центра Земли.


### Аргументы

- *int* **basis** - Одна из переменных [ORIGIN_BASIS_*](#ORIGIN_BASIS_ENU).

## int getOriginBasis ( )

Возвращает [origin basis](#ORIGIN_BASIS_ENU), установленный для объекта GeodeticPivot:
- Если установлен [ORIGIN_BASIS_LOCAL](#ORIGIN_BASIS_LOCAL), привязка к геокоординатам отключена. GeodeticPivot можно разместить где угодно.
- Если установлен [ORIGIN_BASIS_ENU](#ORIGIN_BASIS_ENU), GeodeticPivot размещается в мировой позиции ECF с ориентацией ENU (восток - север - вверх) согласно заданной широте / долготе / высоте. Позиция GeodeticPivot заблокирована. > **Notice:** Направление оси Up (Z+) в ENU указывает вверх вдоль нормали эллипсоида, тогда как в реализации ENU в UNIGINE оно идёт от центра Земли.


### Возвращаемое значение

Одна из переменных [ORIGIN_BASIS_*](#ORIGIN_BASIS_ENU).
## void mapEllipsoidToFlat ( const Math:: vec3 & ellipsoid_point , Math:: vec3 & ret_flat_point , Math:: vec3 & ret_ellipsoid_normal )

Отображает координаты эллипсоида точки в координаты плоскости (используя широту и долготу как координаты X и Y, а высоту как Z).
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ellipsoid_point** - Координаты эллипсоида точки
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_flat_point** - Координаты точки на плоскости.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_ellipsoid_normal** - Координаты нормали точки эллипсоида.

## void mapEllipsoidToFlat ( const Math:: dvec3 & ellipsoid_point , Math:: dvec3 & ret_flat_point , Math:: dvec3 & ret_ellipsoid_normal )

Отображает координаты эллипсоида точки в координаты плоскости (используя широту и долготу как координаты X и Y, а высоту как Z).
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ellipsoid_point** - Координаты эллипсоида точки
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret_flat_point** - Координаты точки на плоскости.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret_ellipsoid_normal** - Координаты нормали точки эллипсоида.

## Math:: mat4 mapEllipsoidToFlat ( const Math:: mat4 & ellipsoid_transform )

Отображает трансформацию эллипсоида в трансформацию плоскости (используя широту и долготу как координаты X и Y, а высоту как Z).
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **ellipsoid_transform** - Трансформация эллипсоида.

### Возвращаемое значение

Трансформация плоскости.
## Math:: dmat4 mapEllipsoidToFlat ( const Math:: dmat4 & ellipsoid_transform )

Отображает трансформацию эллипсоида в трансформацию плоскости (используя широту и долготу как координаты X и Y, а высоту как Z).
### Аргументы

- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ellipsoid_transform** - Трансформация эллипсоида.

### Возвращаемое значение

Трансформация плоскости.
## void mapFlatToEllipsoid ( const Math:: vec3 & flat_point , Math:: vec3 & ret_ellipsoid_point , Math:: vec3 & ret_ellipsoid_normal )

Отображает координаты плоскости в эллипсоид (использует координаты X и Y как широту и долготу, а Z как высоту).
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **flat_point** - Координаты точки на плоскости.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_ellipsoid_point** - Координаты эллипсоида точки
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **ret_ellipsoid_normal** - Координаты нормали точки эллипсоида.

## void mapFlatToEllipsoid ( const Math:: dvec3 & flat_point , Math:: dvec3 & ret_ellipsoid_point , Math:: dvec3 & ret_ellipsoid_normal )

Отображает координаты плоскости в эллипсоид (использует координаты X и Y как широту и долготу, а Z как высоту).
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **flat_point** - Координаты точки на плоскости.
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret_ellipsoid_point** - Координаты эллипсоида точки
- *Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **ret_ellipsoid_normal** - Координаты нормали точки эллипсоида.

## Math:: mat4 mapFlatToEllipsoid ( const Math:: mat4 & flat_transform )

Отображает трансформацию плоскости в трансформацию эллипсоида (использует координаты X и Y как широту и долготу, а Z как высоту).
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **flat_transform** - Трансформация плоскости.

### Возвращаемое значение

Трансформация эллипсоида.
## Math:: dmat4 mapFlatToEllipsoid ( const Math:: dmat4 & flat_transform )

Отображает трансформацию плоскости в трансформацию эллипсоида (использует координаты X и Y как широту и долготу, а Z как высоту).
### Аргументы

- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **flat_transform** - Трансформация плоскости.

### Возвращаемое значение

Трансформация эллипсоида.
## Math:: dvec3 mapFlatToGeodetic ( const Math:: dvec3 & flat_point )

Отображает координаты плоскости в геодезические координаты широты / долготы / высоты согласно началу координат pivot.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **flat_point** - Координаты плоскости.

### Возвращаемое значение

Геодезические координаты.
## Math:: dvec3 mapFlatToGeodetic ( const Math:: vec3 & flat_point )

Отображает координаты плоскости в геодезические координаты широты / долготы / высоты согласно началу координат pivot.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **flat_point** - Координаты плоскости.

### Возвращаемое значение

Геодезические координаты.
## void mapFlatsToGeodetic ( const double * src_x , const double * src_y , int size , double * OUT_ret_lat , double * OUT_ret_lon )

Выполняет пакетное отображение координат плоскости в геодезические координаты широты / долготы согласно началу координат pivot и помещает результат в соответствующие выходные массивы.
### Аргументы

- *const double ** **src_x** - Массив координат X плоскости.
- *const double ** **src_y** - Массив координат Y плоскости.
- *int* **size** - Размер массива.
- *double ** **OUT_ret_lat** - Выходной массив координат широты. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *double ** **OUT_ret_lon** - Выходной массив координат долготы. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Math:: dvec3 mapGeodeticToFlat ( const Math:: dvec3 & geodetic_coords )

Отображает геодезические координаты широты / долготы / высоты в координаты плоскости согласно широте / долготе / высоте начала координат pivot.
### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coords** - Геодезические координаты.

### Возвращаемое значение

Координаты плоскости.
## void mapGeodeticsToFlat ( const double * lat , const double * lon , int size , double * OUT_ret_x , double * OUT_ret_y )

Выполняет пакетное отображение геодезических координат широты / долготы в координаты плоскости согласно широте / долготе начала координат pivot и помещает результат в соответствующие выходные массивы.
### Аргументы

- *const double ** **lat** - Массив геодезических координат широты.
- *const double ** **lon** - Массив геодезических координат долготы.
- *int* **size** - Размер массива.
- *double ** **OUT_ret_x** - Выходной массив координат X плоскости. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *double ** **OUT_ret_y** - Выходной массив координат Y плоскости. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Math:: mat4 mapMeshEllipsoidToFlat ( Ptr < Mesh > & mesh , const Math:: mat4 & ellipsoid_transform )

Отображает изогнутый меш на плоскость (используя широту / долготу / высоту как координаты X / Y / Z).
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Отображаемый меш.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **ellipsoid_transform** - Трансформация эллипсоида меша.

### Возвращаемое значение

Позиция на плоскости, где нужно разместить узел.
## Math:: dmat4 mapMeshEllipsoidToFlat ( Ptr < Mesh > & mesh , const Math:: dmat4 & ellipsoid_transform )

Отображает изогнутый меш на плоскость (используя широту / долготу / высоту как координаты X / Y / Z).
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Отображаемый меш.
- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **ellipsoid_transform** - Трансформация эллипсоида меша.

### Возвращаемое значение

Позиция на плоскости, где нужно разместить узел.
## Math:: mat4 mapMeshFlatToEllipsoid ( Ptr < Mesh > & mesh , const Math:: mat4 & flat_transform )

Отображает плоский меш на эллипсоид (использует координаты X и Y как широту и долготу, а Z как высоту).
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Отображаемый меш.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **flat_transform** - Трансформация плоскости меша.

### Возвращаемое значение

Позиция на эллипсоиде, где нужно разместить узел.
## Math:: dmat4 mapMeshFlatToEllipsoid ( Ptr < Mesh > & mesh , const Math:: dmat4 & flat_transform )

Отображает плоский меш на эллипсоид (использует координаты X и Y как широту и долготу, а Z как высоту).
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Отображаемый меш.
- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **flat_transform** - Трансформация плоскости меша.

### Возвращаемое значение

Позиция на эллипсоиде, где нужно разместить узел.
## Math:: dvec3 toGeodetic ( const Math:: mat4 & world_transform )

Возвращает геодезические координаты для указанной матрицы мировой трансформации.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **world_transform** - Мировая трансформация.

### Возвращаемое значение

Геодезические координаты.
## Math:: dvec3 toGeodetic ( const Math:: dmat4 & world_transform )

Возвращает геодезические координаты для указанной матрицы мировой трансформации.
### Аргументы

- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **world_transform** - Мировая трансформация.

### Возвращаемое значение

Геодезические координаты.
## Math:: dmat4 toWorld ( const Math:: dvec3 & geodetic_coords , GeodeticPivot::UP_AXIS up_axis = Enum.GeodeticPivot.UP_AXIS.GEOCENTRIC_NORMAL )

Возвращает матрицу мировой трансформации для указанных геодезических координат.
> **Notice:** Если полученные координаты будут использоваться для установки трансформаций чего-либо относительно сущности (например, камеры на самолёте или лазерного луча от самолёта), переключите тип оси Up на [geodetic normal](#UP_AXIS_GEODETIC_NORMAL).


### Аргументы

- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coords** - Геодезические координаты.
- *[GeodeticPivot::UP_AXIS](../../../api/library/geodetics/class.geodeticpivot_cpp.md#UP_AXIS)* **up_axis** - Тип [UP axis](#up_axis). Если полученные координаты будут использоваться для установки трансформаций чего-либо относительно сущности (например, камеры на самолёте или лазерного луча от самолёта), переключите тип оси Up на [geodetic normal](#UP_AXIS_GEODETIC_NORMAL).

### Возвращаемое значение

Мировая трансформация.
## Math:: mat4 toWorldPreserveRotation ( const Math:: mat4 & world_transform , const Math:: dvec3 & geodetic_coords , GeodeticPivot::UP_AXIS up_axis = Enum.GeodeticPivot.UP_AXIS.GEOCENTRIC_NORMAL )

Возвращает новую матрицу мировой трансформации, сохраняющую вращение относительно нормали.
> **Notice:** Если полученные координаты будут использоваться для установки трансформаций чего-либо относительно сущности (например, камеры на самолёте или лазерного луча от самолёта), переключите тип оси Up на [geodetic normal](#UP_AXIS_GEODETIC_NORMAL).


### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **world_transform** - Мировая трансформация.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coords** - Геодезические координаты.
- *[GeodeticPivot::UP_AXIS](../../../api/library/geodetics/class.geodeticpivot_cpp.md#UP_AXIS)* **up_axis** - Тип [UP axis](#up_axis). Если полученные координаты будут использоваться для установки трансформаций чего-либо относительно сущности (например, камеры на самолёте или лазерного луча от самолёта), переключите тип оси Up на [geodetic normal](#UP_AXIS_GEODETIC_NORMAL).

### Возвращаемое значение

Новая мировая трансформация.
## Math:: dmat4 toWorldPreserveRotation ( const Math:: dmat4 & world_transform , const Math:: dvec3 & geodetic_coords , GeodeticPivot::UP_AXIS up_axis = Enum.GeodeticPivot.UP_AXIS.GEOCENTRIC_NORMAL )

Возвращает новую матрицу мировой трансформации, сохраняющую вращение относительно нормали.
> **Notice:** Если полученные координаты будут использоваться для установки трансформаций чего-либо относительно сущности (например, камеры на самолёте или лазерного луча от самолёта), переключите тип оси Up на [geodetic normal](#UP_AXIS_GEODETIC_NORMAL).


### Аргументы

- *const  Math::[dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **world_transform** - Мировая трансформация.
- *const  Math::[dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coords** - Геодезические координаты.
- *[GeodeticPivot::UP_AXIS](../../../api/library/geodetics/class.geodeticpivot_cpp.md#UP_AXIS)* **up_axis** - Тип [UP axis](#up_axis). Если полученные координаты будут использоваться для установки трансформаций чего-либо относительно сущности (например, камеры на самолёте или лазерного луча от самолёта), переключите тип оси Up на [geodetic normal](#UP_AXIS_GEODETIC_NORMAL).

### Возвращаемое значение

Новая мировая трансформация.
## static int type ( )

Возвращает тип объекта.
### Возвращаемое значение

Идентификатор типа [GeodeticPivot](../../../api/library/nodes/class.node_cpp.md#GEODETIC_PIVOT).
