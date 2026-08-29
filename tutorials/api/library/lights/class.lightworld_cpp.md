# Unigine.LightWorld Class (CPP)

**Header:** #include <UnigineLights.h>

**Inherits from:** Light


Этот класс используется для создания [world light sources](../../../objects/lights/world/index.md). Такой источник света имитирует солнечный свет и использует [parallel-split shadow mapping](../../../principles/render/lights_shadows/shadows/pssm.md).


### Пример


Следующий код показывает, как создать источник света world и задать его параметры (интенсивность, рассеивание и т.д.).


```cpp
#include <UnigineLights.h>

using namespace Unigine;

	/* .. */

// создание источника света world с белым цветом (1.0f, 1.0f, 1.0f, 1.0f)
	LightWorldPtr thesun = LightWorld::create(Math::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// установка имени источника света world
	thesun->setName("Sun");

	// установка угла отключения источника света world
	thesun->setDisableAngle(90.0f);

	// установка интенсивности света
	thesun->setIntensity(1.0f);

	// установка типа рассеивания в рассеивание от солнца
	thesun->setScattering(LightWorld::SCATTERING_SUN);


```


### Задание позиции


Источник света world - это бесконечно удалённый источник, поэтому его физическая позиция не важна, важно только направление, так как оно определяет ориентацию теней. Направление света можно изменить с помощью метода [*setRotation()*](../../../api/library/nodes/class.node_cpp.md#setRotation_quat_int_void).


Проиллюстрируем это, задав корректную позицию Солнца для определённого географического местоположения (широта, долгота), даты и времени. Для расчёта значений elevation и azimuth используем следующую функцию *sunPosition()*:


<details>
<summary>функция sunPosition() | Закрыть</summary>

**Функция sunPosition():**


```cpp
#include <UnigineWorld.h>

using namespace Unigine;

/// функция, вычисляющая азимут и высоту для заданной даты, времени (GMT) и геокоординат (https://stackoverflow.com/questions/8708048/position-of-the-sun-given-time-of-day-latitude-and-longitude)
void sunPosition(double& elevation, double& azimuth, double lat, double lon, int year = 2012, int month = 12, int day = 22, double hour = 12, int min = 00, int sec = 00) {
	double pi = 3.141592650f;
	double twopi = 2 * pi;
	double deg2rad = pi / 180.0f;

	// получение дня года, например 1 фев = 32, 1 мар = 61 в високосные годы
	int month_days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 };
	for (int i = 0; i < month; i++)
		day += month_days[i];
	int leapdays = (year % 4) == 0 && ((year % 400) == 0 || (year % 100) != 0) && day >= 60 && !(month == 2 && day == 60);
	if (leapdays > 0) day++;

	// получение юлианской даты - 2400000
	hour += min / 60.0f + sec / 3600.0f; // час плюс дробная часть
	double delta = year - 1949.0f;
	double leap = int(delta / 4.0f); // предыдущие високосные годы
	double jd = 32916.5f + delta * 365 + leap + day + hour / 24.0f;

	// вычисление входного значения для Astronomer's Almanac как разницы между
	// юлианской датой и JD 2451545.0 (полдень, 1 января 2000)
	double time = jd - 51545.0f;

	// вычисление средней долготы и средней аномалии
	double mnlong = 280.460f + 0.9856474f * time;
	mnlong = remainder(mnlong, 360);
	if (mnlong < 0) mnlong += 360;
	double mnanom = 357.528f + 0.9856003f * time;
	mnanom = remainder(mnanom, 360);
	if (mnanom < 0) mnanom += 360;
	mnanom *= deg2rad;

	// вычисление эклиптической долготы и наклона эклиптики
	double eclong = mnlong + 1.915f * Math::sin(mnanom) + 0.020f * Math::sin(2 * mnanom);
	eclong = remainder(eclong, 360);
	if (eclong < 0) eclong += 360;
	double oblqec = 23.439f - 0.0000004f * time;
	eclong *= deg2rad;
	oblqec *= deg2rad;

	// вычисление небесных координат: прямого восхождения и склонения
	double num = Math::cos(oblqec) * Math::sin(eclong);
	double den = Math::cos(eclong);
	double ra = Math::atan(num / den);
	if (den < 0) ra += pi;
	if (den >= 0 && num < 0) ra += twopi;
	double dec = Math::asin(Math::sin(oblqec) * Math::sin(eclong));

	// вычисление локальных координат: среднего гринвичского звёздного времени
	double gmst = 6.697375f + 0.0657098242f * time + hour;
	gmst = remainder(gmst, 24);
	if (gmst < 0) gmst += 24.0f;

	// вычисление местного среднего звёздного времени
	double lmst = gmst + lon / 15.0f;
	lmst = remainder(lmst, 24);
	if (lmst < 0) lmst += 24.0f;
	lmst = lmst * 15.0f * deg2rad;

	// вычисление часового угла
	double ha = lmst - ra;
	if (ha < -pi) ha += twopi;
	if (ha > pi) ha -= twopi;

	// преобразование широты в радианы
	lat = lat * deg2rad;

	// вычисление азимута и высоты
	elevation = Math::asin(Math::sin(dec) * Math::sin(lat) + Math::cos(dec) * Math::cos(lat) * Math::cos(ha));
	azimuth = Math::asin(-Math::cos(dec) * Math::sin(ha) / Math::cos(elevation));

	// логику и обозначения см. в Spencer, J.W. 1989. Solar Energy. 42(4):353
	int cosAzPos = (0 <= Math::sin(dec) - Math::sin(elevation) * Math::sin(lat));
	int sinAzNeg = (Math::sin(azimuth) < 0);
	if (cosAzPos && sinAzNeg) azimuth += twopi;
	if (!cosAzPos) azimuth = pi - azimuth;

	// возврат высоты и азимута
	elevation = elevation / deg2rad;
	azimuth = azimuth / deg2rad;
}


```

</details>


Таким образом, мы можем просто задать позицию Солнца следующим образом:


```cpp
#include <UnigineWorld.h>

int AppWorldLogic::init()
{

	/* ... */

	// геокоординаты точки (широта и долгота)
	double lat = 56.49771;
	double lon = 84.97437;

	// переменные для хранения вычисленных значений высоты и азимута
	double elevation, azimuth;

	// получение стандартного источника света world с именем "sun"
	LightWorldPtr sun = checked_ptr_cast<LightWorld>(World::getNodeByName("sun"));
	if (sun)
	{
		// вычисление азимута и высоты
		// for the specified date,
		// GMT time and geo-coordinates
		sunPosition(elevation, azimuth, lat, lon,
			2019, 2, 5, 				// 5 февраля 2019
			4, 0, 0);					// 04:00:00 (GMT)

		// установка реальной позиции Солнца для вычисленных значений азимута и высоты
		sun->setRotation(Math::quat(90, 270, 270) * Math::quat((float)azimuth, 0, 0) * Math::quat(0, 90, 0) * Math::quat((float)elevation, 0, 0) * Math::quat(90, 0, 0));
	}

	return 1;
}


```


## LightWorld Class

### Перечисления

## SCATTERING

| Имя | Описание |
|---|---|
| **SCATTERING_NONE** = 0 | Рендерить атмосферу без влияния глобальных источников света (солнца и луны), т.е. градиент света не будет изменяться ни в каком направлении. |
| **SCATTERING_SUN** = 1 | Рендерить атмосферу в соответствии с освещением Солнца. |
| **SCATTERING_MOON** = 2 | Рендерить атмосферу в соответствии с освещением Луны. |

## SHADOW_CASCADE_MODE

| Имя | Описание |
|---|---|
| **SHADOW_CASCADE_MODE_DYNAMIC** = 0 | Режим динамической генерации каскадов теней. В этом режиме каскады теней строятся динамически относительно позиции камеры. Все тени вычисляются динамически, что позволяет изменять время суток (цикл дня и ночи). |
| **SHADOW_CASCADE_MODE_STATIC** = 1 | Режим статической генерации каскадов теней. В этом режиме каскады теней строятся и запекаются относительно позиции источника света. Этот режим подходит как способ оптимизации производительности для небольших ArchViz-проектов, где каскады теней можно разделить на 2 секции: проходимая область с тенями высокого разрешения (так как они наблюдаются вблизи) и непроходимая область с тенями низкого разрешения (так как они наблюдаются издалека). > **Notice:** Изменение времени суток недоступно в этом режиме, так как каскады теней запечены. |

### Методы класса

## void setMode ( int mode )

Задаёт новый режим рендеринга для источника света. Эта опция определяет, будет ли свет рендериться как динамический или статический.
### Аргументы

- *int* **mode** - Режим источника света, одна из переменных [MODE_*](../../../api/library/lights/class.light_cpp.md#MODE_DYNAMIC).

## int getMode () const

Возвращает текущий режим рендеринга для источника света. Эта опция определяет, будет ли свет рендериться как динамический или статический.
### Возвращаемое значение

Текущий режим источника света, одна из переменных [MODE_*](../../../api/library/lights/class.light_cpp.md#MODE_DYNAMIC).
## void setShadowZFar ( float zfar )

Задаёт новое расстояние до дальней плоскости отсечения, используемое для генерации статических каскадов теней. Статические каскады генерируются относительно позиции источника света world.
> **Notice:** Этот параметр доступен только когда [shadow cascade mode](#setShadowCascadeBorder_int_float_void) источника света world установлен в [*static*](#SHADOW_CASCADE_MODE_STATIC).


### Аргументы

- *float* **zfar** - Используемое расстояние до дальней плоскости отсечения, в единицах.

## float getShadowZFar () const

Возвращает текущее расстояние до дальней плоскости отсечения, используемое для генерации статических каскадов теней. Статические каскады генерируются относительно позиции источника света world.
> **Notice:** Этот параметр доступен только когда [shadow cascade mode](#setShadowCascadeBorder_int_float_void) источника света world установлен в [*static*](#SHADOW_CASCADE_MODE_STATIC).


### Возвращаемое значение

Текущее используемое расстояние до дальней плоскости отсечения, в единицах.
## void setShadowWidth ( float width )

Задаёт новую ширину вида ортографической проекции, используемую для генерации статических каскадов теней. Статические каскады генерируются относительно позиции источника света world.
> **Notice:** Этот параметр доступен только когда [shadow cascade mode](#setShadowCascadeBorder_int_float_void) источника света world установлен в [*static*](#SHADOW_CASCADE_MODE_STATIC).


### Аргументы

- *float* **width** - Ширина вида ортографической проекции, используемой для генерации каскадов теней, в единицах.

## float getShadowWidth () const

Возвращает текущую ширину вида ортографической проекции, используемую для генерации статических каскадов теней. Статические каскады генерируются относительно позиции источника света world.
> **Notice:** Этот параметр доступен только когда [shadow cascade mode](#setShadowCascadeBorder_int_float_void) источника света world установлен в [*static*](#SHADOW_CASCADE_MODE_STATIC).


### Возвращаемое значение

Текущая ширина вида ортографической проекции, используемой для генерации каскадов теней, в единицах.
## void setShadowHeight ( float height )

Задаёт новую высоту вида ортографической проекции, используемую для генерации статических каскадов теней. Статические каскады генерируются относительно позиции источника света world.
> **Notice:** Этот параметр доступен только когда [shadow cascade mode](#setShadowCascadeBorder_int_float_void) источника света world установлен в [*static*](#SHADOW_CASCADE_MODE_STATIC).


### Аргументы

- *float* **height** - Высота вида ортографической проекции, используемой для генерации каскадов теней, в единицах.

## float getShadowHeight () const

Возвращает текущую высоту вида ортографической проекции, используемую для генерации статических каскадов теней. Статические каскады генерируются относительно позиции источника света world.
> **Notice:** Этот параметр доступен только когда [shadow cascade mode](#setShadowCascadeBorder_int_float_void) источника света world установлен в [*static*](#SHADOW_CASCADE_MODE_STATIC).


### Возвращаемое значение

Текущая высота вида ортографической проекции, используемой для генерации каскадов теней, в единицах.
## void setNumShadowCascades ( int cascades )

Задаёт новое количество каскадов теней с разными картами теней. Все карты теней имеют одинаковое разрешение, но применяются к разным каскадам. Таким образом, ближние тени имеют более высокое качество, а дальние - более низкое.
### Аргументы

- *int* **cascades** - Количество каскадов теней. Допустимые значения от 1 до 4. Значение по умолчанию - 4.

## int getNumShadowCascades () const

Возвращает текущее количество каскадов теней с разными картами теней. Все карты теней имеют одинаковое разрешение, но применяются к разным каскадам. Таким образом, ближние тени имеют более высокое качество, а дальние - более низкое.
### Возвращаемое значение

Текущее количество каскадов теней. Допустимые значения от 1 до 4. Значение по умолчанию - 4.
## void setShadowCascadeMode ( LightWorld::SHADOW_CASCADE_MODE mode )

Задаёт новый режим генерации каскадов теней для источника света world.
### Аргументы

- *[LightWorld::SHADOW_CASCADE_MODE](../../../api/library/lights/class.lightworld_cpp.md#SHADOW_CASCADE_MODE)* **mode** - Режим каскадов теней, одна из переменных [SHADOW_CASCADE_MODE_*](#SHADOW_CASCADE_MODE_DYNAMIC).

## LightWorld::SHADOW_CASCADE_MODE getShadowCascadeMode () const

Возвращает текущий режим генерации каскадов теней для источника света world.
### Возвращаемое значение

Текущий режим каскадов теней, одна из переменных [SHADOW_CASCADE_MODE_*](#SHADOW_CASCADE_MODE_DYNAMIC).
## Math:: vec2 getRenderShadowDepthRange () const

Возвращает текущий диапазон глубины теней для источника света.
### Возвращаемое значение

Текущий диапазон глубины теней для источника света в виде двухкомпонентного вектора (min, max).
## void setDisableAngle ( float angle )

Задаёт новый угол, при котором источник света отключается (тени и диффузная составляющая отключаются). Однако источник света всё ещё влияет на рассеивание.
### Аргументы

- *float* **angle** - Угол, при котором источник света отключается.

## float getDisableAngle () const

Возвращает текущий угол, при котором источник света отключается (тени и диффузная составляющая отключаются). Однако источник света всё ещё влияет на рассеивание.
### Возвращаемое значение

Текущий угол, при котором источник света отключается.
## void setScattering ( LightWorld::SCATTERING scattering )

Задаёт новый тип освещения для источника света world.
### Аргументы

- *[LightWorld::SCATTERING](../../../api/library/lights/class.lightworld_cpp.md#SCATTERING)* **scattering** - Тип освещения, заданный для источника света world, одна из переменных [SCATTERING_*](#SCATTERING_MOON).

## LightWorld::SCATTERING getScattering () const

Возвращает текущий тип освещения, заданный для источника света world.
### Возвращаемое значение

Текущий тип освещения, заданный для источника света world, одна из переменных [SCATTERING_*](#SCATTERING_MOON).
## void setOneCascadePerFrame ( bool frame )

Задаёт новое значение, указывающее, включён ли режим One Cascade Per Frame. Этот режим распределяет обновление каскадов теней по нескольким кадрам рендеринга: тени от статической геометрии рендерятся только в один каскад за кадр.
> **Notice:** Тени от прозрачных поверхностей не могут быть запечены. Чтобы такие тени были видны при включённом любом режиме запекания освещения, настройте прозрачные поверхности: включите для них [dynamic lighting mode](../../../api/library/objects/class.object_cpp.md#SURFACE_LIGHTING_MODE_DYNAMIC).


### Аргументы

- *bool* **frame** - Значение **true** включает режим One Cascade Per Frame; **false** - отключает его.

## bool isOneCascadePerFrame () const

Возвращает текущее значение, указывающее, включён ли режим One Cascade Per Frame. Этот режим распределяет обновление каскадов теней по нескольким кадрам рендеринга: тени от статической геометрии рендерятся только в один каскад за кадр.
> **Notice:** Тени от прозрачных поверхностей не могут быть запечены. Чтобы такие тени были видны при включённом любом режиме запекания освещения, настройте прозрачные поверхности: включите для них [dynamic lighting mode](../../../api/library/objects/class.object_cpp.md#SURFACE_LIGHTING_MODE_DYNAMIC).


### Возвращаемое значение

**true**, если режим One Cascade Per Frame включён; иначе **false**.
---

## static LightWorldPtr create ( const Math:: vec4 & color )

Конструктор. Создаёт новый источник света world с заданным цветом.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет нового источника света.

## void setShadowCascadeBorder ( int num , float r )

Задаёт множитель для расстояния до границы указанного каскада теней, на котором рендерятся соответствующие тени.
### Аргументы

- *int* **num** - Номер каскада в диапазоне [0;[num_cascades](#getNumShadowCascades_int)-1].
- *float* **r** - Устанавливаемый множитель расстояния, в диапазоне [0; 1].

## float getShadowCascadeBorder ( int num ) const

Возвращает множитель для расстояния до границы указанного каскада теней, на котором рендерятся соответствующие тени.
### Аргументы

- *int* **num** - Номер каскада в диапазоне [0;[num_cascades](#getNumShadowCascades_int)-1].

### Возвращаемое значение

Текущий множитель расстояния, в диапазоне [0;1].
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Light](../../../api/library/lights/class.light_cpp.md).
## Math:: Mat4 getRenderShadowCascadeModelview ( int num ) const

Возвращает видовую матрицу для указанного каскада теней.
### Аргументы

- *int* **num** - Номер каскада теней в диапазоне [0;[num_cascades](#getNumShadowCascades_int)-1].

### Возвращаемое значение

Видовая матрица каскада теней.
## Math:: mat4 getRenderShadowCascadeProjection ( int num ) const

Возвращает матрицу проекции каскада теней для указанного номера каскада.
### Аргументы

- *int* **num** - Номер каскада теней в диапазоне [0;[num_cascades](#getNumShadowCascades_int)-1].

### Возвращаемое значение

Матрица проекции каскада теней.
## void updateRenderShadowCascadeMatrices ( const Math:: Vec3 & camera_position , float zfar )

Обновляет матрицы проекции каскадов теней источника света в соответствии с указанной позицией камеры и расстоянием до дальней плоскости отсечения.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **camera_position** - Позиция камеры в мировых координатах.
- *float* **zfar** - Расстояние до дальней плоскости отсечения по Z, в единицах.
