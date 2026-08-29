# Unigine::Plugins::Geodetics::Converter Class (CPP)

**Header:** #include <plugins/Unigine/Geodetics/UnigineGeodetics.h>


Этот класс используется для преобразования геодезических координат (**широта, долгота и высота**) в мировую 3D-позицию и обратно. Он поддерживает несколько геодезических режимов: режим на основе **GeodeticPivot** для сцен с привязкой к pivot, и режимы на основе плагина, использующие коды **EPSG** или строки проекции **WKT2** через библиотеку GDAL. Конвертер также обрабатывает трансформации с учётом террейна (плоский или изогнутый террейн), преобразования углов Эйлера между локальным геодезическим пространством и мировым, а также преобразования систем координат между геодезическим и геоцентрическим (ECEF) представлениями.

> **Notice:** Геодезические преобразования доступны **только** если загружен [Geodetics Plugin](../../../../code/plugins/geodetics/index.md).


## Converter Class

### Перечисления

## GEODETIC_MODE

Геодезический режим, определяющий, как выполняются преобразования из мировых координат в геодезические и обратно.
| Name | Description |
|---|---|
| **GEODETIC_MODE_NOT_AVAILABLE** = 0 | Преобразования геодезических координат недоступны. Во время инициализации не найдено ни корректной проекции, ни *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*. |
| **GEODETIC_MODE_GEODETIC_PIVOT** = 1 | Преобразования выполняются с использованием узла *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*, найденного в сцене. Поддерживает режимы как плоского, так и изогнутого террейна. |
| **GEODETIC_MODE_GEODETICS_PLUGIN_EPSG** = 2 | Преобразования выполняются с использованием плагина Geodetics с проекцией, заданной кодом **EPSG**. |
| **GEODETIC_MODE_GEODETICS_PLUGIN_WKT2** = 3 | Преобразования выполняются с использованием плагина Geodetics с проекцией, заданной строкой **WKT2**. |

## TERRAIN_MODE

Тип объекта террейна, присутствующего в сцене, используемый для определения способа разрешения параметров, связанных с террейном, во время инициализации.
| Name | Description |
|---|---|
| **TERRAIN_MODE_NO_TERRAIN** = 0 | В сцене не найдено ни одного объекта террейна. |
| **TERRAIN_MODE_LANDSCAPE_TERRAIN** = 1 | В сцене присутствует **[ObjectLandscapeTerrain](../../../../objects/objects/terrain/landscape_terrain/index.md)** (landscape terrain), используемый в качестве опорного террейна. |
| **TERRAIN_MODE_TERRAIN_GLOBAL** = 2 | В сцене присутствует **[ObjectTerrainGlobal](../../../../objects/objects/terrain/terrain_global/index.md)** (global terrain), используемый в качестве опорного террейна. |

### Методы класса

## void setAutoWorldInit ( bool init )

Устанавливает новый флаг, указывающий, вызывает ли конвертер автоматически **[initialize()](../../../...md#initialize_int)** при загрузке сцены и **[clear()](../../../...md#clear_void)** при её завершении. Если включено, конвертер подписывается на события *init/shutdown* сцены и автоматически управляет своим жизненным циклом.
### Аргументы

- *bool* **init** - Установите **true**, чтобы включить автоматическое управление жизненным циклом конвертера; **false** — чтобы отключить его.

## bool isAutoWorldInit () const

Возвращает текущий флаг, указывающий, вызывает ли конвертер автоматически **[initialize()](../../../...md#initialize_int)** при загрузке сцены и **[clear()](../../../...md#clear_void)** при её завершении. Если включено, конвертер подписывается на события *init/shutdown* сцены и автоматически управляет своим жизненным циклом.
### Возвращаемое значение

**true**, если автоматическое управление жизненным циклом конвертера включено; иначе **false**.
## bool isInitialized () const

Возвращает текущий флаг, указывающий, был ли конвертер успешно инициализирован с корректным геодезическим режимом.
### Возвращаемое значение

**true**, если **[initialize()](../../../...md#initialize_int)** успешно завершился и геодезический режим не равен **[GEODETIC_MODE_NOT_AVAILABLE](../../../...md#GEODETIC_MODE_NOT_AVAILABLE)**; иначе **false**.
## bool isTerrainCurved () const

Возвращает текущий флаг, указывающий, рассматривается ли террейн как изогнутый (сферический/эллипсоидальный), а не плоский. Применяется только в режиме **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)**.
### Возвращаемое значение

**true**, если узел глобального террейна является дочерним для *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*, а у pivot переменная *flat* не установлена в 1; иначе **false**.
## Math:: Vec3 getOrigin () const

Возвращает текущее начало координат сцены в геодезических координатах (широта, долгота, высота). В режиме *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)* это начало координат pivot; в режимах плагина это начало координат, считанное из переменной *sandworm_origin* узла террейна.
### Возвращаемое значение

Текущее начало координат сцены в геодезических координатах (широта, долгота, высота).
## Converter::TERRAIN_MODE getTerrainMode () const

Возвращает текущий режим террейна, указывающий, какой тип объекта террейна (если есть) был обнаружен во время инициализации. Возможные значения см. в **[TERRAIN_MODE](../../../...md#TERRAIN_MODE_NO_TERRAIN)**.
### Возвращаемое значение

Текущий режим террейна.
## Ptr < ObjectLandscapeTerrain > getLandscapeTerrain () const

Возвращает текущий активный экземпляр **[ObjectLandscapeTerrain](../../../../objects/objects/terrain/landscape_terrain/index.md)**, найденный в сцене во время инициализации, либо null, если landscape terrain отсутствует.
### Возвращаемое значение

Текущий активный экземпляр **ObjectLandscapeTerrain**, либо null, если landscape terrain отсутствует.
## Ptr < ObjectTerrainGlobal > getTerrainGlobal () const

Возвращает текущий экземпляр **[ObjectTerrainGlobal](../../../../objects/objects/terrain/terrain_global/index.md)**, найденный в сцене во время инициализации, либо null, если global terrain отсутствует.
### Возвращаемое значение

Текущий активный экземпляр **[ObjectTerrainGlobal](../../../../objects/objects/terrain/terrain_global/index.md)**, либо null, если landscape terrain отсутствует.
## Converter::GEODETIC_MODE getGeodeticMode () const

Возвращает текущий геодезический режим, выбранный во время инициализации. Возможные значения см. в **[TERRAIN_MODE](../../../...md#TERRAIN_MODE_NO_TERRAIN)**.
### Возвращаемое значение

Текущий геодезический режим, выбранный во время инициализации.
## int getEPSGProjection () const

Возвращает текущий код EPSG текущей проекции, считанный из переменной *sandworm_epsg* узла террейна. Возвращает **-1**, если проекция EPSG не задана.
### Возвращаемое значение

Текущий
## String getWKT2Projection () const

Возвращает текущую строку проекции WKT2 текущей проекции, считанную из переменной *sandworm_projection* узла террейна. Возвращает пустую строку, если проекция WKT2 не задана.
### Возвращаемое значение

Текущий WKT2 projection string of the current projection.
## void setForceRotateCoordinatesToENU ( bool enu )

Устанавливает новый флаг, управляющий тем, принудительно ли поворачиваются координаты в выравнивание осей East-North-Up (ENU) во время геодезических преобразований в режимах плагина. Если включено, X соответствует востоку, а Y — северу. Этот флаг автоматически устанавливается из переменной *coordinate_system* узла террейна во время инициализации.
### Аргументы

- *bool* **enu** - Установите **true**, чтобы включить принудительный поворот координат в выравнивание осей East-North-Up (ENU) во время геодезических преобразований в режимах плагина; **false** — чтобы отключить его.

## bool isForceRotateCoordinatesToENU () const

Возвращает текущий флаг, управляющий тем, принудительно ли поворачиваются координаты в выравнивание осей East-North-Up (ENU) во время геодезических преобразований в режимах плагина. Если включено, X соответствует востоку, а Y — северу. Этот флаг автоматически устанавливается из переменной *coordinate_system* узла террейна во время инициализации.
### Возвращаемое значение

**true**, если принудительный поворот координат в выравнивание осей East-North-Up (ENU) во время геодезических преобразований в режимах плагина включён; иначе **false**.
## getGeodeticPivot () const

Возвращает текущий узел *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*, найденный в сцене во время инициализации, либо null, если *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)* отсутствует.
> **Notice:** Актуально только в режиме **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)**.

### Возвращаемое значение

Текущий *GeodeticPivot* node found in the world during initialization; otherwise null.
## void setGeodeticPivotMode ( GeodeticPivot::UP_AXIS mode )

Устанавливает новый режим оси up, используемый при вычислении нулевого базиса через *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*. Управляет тем, является ли направление up **geodetic normal** (нормалью к поверхности эллипсоида) или **geocentric normal** (направлением к центру Земли).
> **Notice:** Актуально только в режиме **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)**.

### Аргументы

- *[GeodeticPivot::UP_AXIS](../../../../api/library/geodetics/class.geodeticpivot_cpp.md#UP_AXIS)* **mode** - Режим оси up, используемый при вычислении нулевого базиса через *GeodeticPivot*.

## GeodeticPivot::UP_AXIS getGeodeticPivotMode () const

Возвращает текущий режим оси up, используемый при вычислении нулевого базиса через *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*. Управляет тем, является ли направление up **geodetic normal** (нормалью к поверхности эллипсоида) или **geocentric normal** (направлением к центру Земли).
> **Notice:** Актуально только в режиме **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)**.

### Возвращаемое значение

Текущий up-axis mode used when computing the zero basis via the *GeodeticPivot*.
---

## bool initialize ( )

Сканирует текущую сцену на наличие узла *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)* и объектов террейна (**[ObjectTerrainGlobal](../../../../objects/objects/terrain/terrain_global/index.md)** или **[ObjectLandscapeTerrain](../../../../objects/objects/terrain/landscape_terrain/index.md)**), чтобы определить подходящий геодезический режим. Если найден *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*, он используется напрямую; иначе для настройки проекции на основе GDAL используются переменные террейна *sandworm_epsg* или *sandworm_projection*. Должен вызываться после загрузки сцены, если **[isAutoWorldInit()](../../../...md#isAutoWorldInit_int)** отключён.
### Возвращаемое значение

true, если установлен корректный геодезический режим; false, если не найдена пригодная геодезическая конфигурация.
## void clear ( )

Сбрасывает всё состояние конвертера к значениям по умолчанию: устанавливает геодезический режим в **[GEODETIC_MODE_NOT_AVAILABLE](../../../...md#GEODETIC_MODE_NOT_AVAILABLE)**, очищает проекцию, начало координат, ссылки на террейн и указатель *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)*. После вызова этого метода **[isInitialized()](../../../...md#isInitialized_int)** возвращает false.
## Math:: dvec3 worldToGeodetic ( const Math:: Vec3 & world_position ) const

Преобразует мировую 3D-позицию в геодезические координаты (широта, долгота, высота). В режиме **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)** использует плоское или изогнутое отображение pivot в зависимости от **[isTerrainCurved()](../../../...md#isTerrainCurved_int)**. В режимах плагина делегирует выполнение плагину Geodetics *[transformer](../../../../api/library/geodetics/geodetics_plugin/class.transformer_cpp.md)*.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **world_position** - Позиция в 3D-мировом пространстве.

### Возвращаемое значение

Геодезические координаты как (широта, долгота, высота). Если конвертер не инициализирован, входная позиция возвращается приведённой к типу **dvec3**.
## Math:: Vec3 geodeticToWorld ( const Math:: dvec3 & geodetic_coordinate ) const

Преобразует геодезические координаты (широта, долгота, высота) в мировую 3D-позицию. В режиме **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)** использует плоское или изогнутое отображение pivot в зависимости от **[isTerrainCurved()](../../../...md#isTerrainCurved_int)**. В режимах плагина делегирует выполнение плагину Geodetics *[transformer](../../../../api/library/geodetics/geodetics_plugin/class.transformer_cpp.md)* и извлекает компонент трансляции из результирующей матрицы трансформации.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Геодезические координаты как (широта, долгота, высота).

### Возвращаемое значение

Позиция в 3D-мировом пространстве. Если конвертер не инициализирован, входная координата возвращается приведённой к типу **Vec3**.
## Math:: quat eulerToRotation ( const Math:: vec3 & euler ) const

Преобразует углы Эйлера в мировом пространстве (тангаж, крен, курс в градусах, порядок ZYX) в кватернион вращения в мировом пространстве. Это преобразование не зависит от системы координат и не учитывает локальную геодезическую ориентацию в конкретной точке.
### Аргументы

- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **euler** - Углы Эйлера в градусах как (тангаж, крен, курс), применяемые в порядке ZYX.

### Возвращаемое значение

Кватернион, представляющий вращение в мировом пространстве.
## Math:: vec3 rotationToEuler ( const Math:: quat & rotation ) const

Преобразует кватернион вращения в мировом пространстве в углы Эйлера (тангаж, крен, курс в градусах, порядок ZYX). Это преобразование не зависит от системы координат и не учитывает локальную геодезическую ориентацию в конкретной точке.
### Аргументы

- *const  Math::[quat](../../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион, представляющий вращение в мировом пространстве.

### Возвращаемое значение

Углы Эйлера в градусах как (тангаж, крен, курс), разложенные в порядке ZYX.
## Math:: quat geodeticEulerToRotation ( const Math:: dvec3 & geodetic_coordinate , const Math:: vec3 & euler ) const

Преобразует углы Эйлера, заданные в локальной геодезической системе координат (выровненной по ENU) в указанной геодезической позиции, в кватернион вращения в мировом пространстве. Ориентация локальной системы определяется *[getZeroRotation()](../../../...md#getZeroRotation_dvec3_quat)* в этой точке. Это полезно для размещения объектов, чей курс, тангаж и крен заданы относительно локального горизонта.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Геодезические координаты (широта, долгота, высота), определяющие локальную систему отсчёта.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **euler** - Углы Эйлера в градусах как (тангаж, крен, курс) в локальной геодезической системе координат, применяемые в порядке ZYX.

### Возвращаемое значение

Кватернион, представляющий вращение в мировом пространстве.
## Math:: vec3 rotationToGeodeticEuler ( const Math:: dvec3 & geodetic_coordinate , const Math:: quat & rotation ) const

Преобразует кватернион вращения в мировом пространстве в углы Эйлера, заданные в локальной геодезической системе координат (выровненной по ENU) в указанной геодезической позиции. Это обратное преобразование к *[geodeticEulerToRotation()](../../../...md#geodeticEulerToRotation_dvec3_vec3_quat)*.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Геодезические координаты (широта, долгота, высота), определяющие локальную систему отсчёта.
- *const  Math::[quat](../../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион, представляющий вращение в мировом пространстве.

### Возвращаемое значение

Углы Эйлера в градусах как (тангаж, крен, курс) в локальной геодезической системе координат, разложенные в порядке ZYX.
## Math:: quat getZeroRotation ( const Math:: dvec3 & geodetic_coordinate ) const

Возвращает кватернион вращения локальной геодезической системы отсчёта в указанной геодезической позиции. Это компонент вращения, извлечённый из *[getZeroBasis()](../../../...md#getZeroBasis_dvec3_Mat4)*. У объекта с этим вращением ось forward будет направлена на север, а ось up — от поверхности Земли.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Геодезические координаты (широта, долгота, высота), в которых вычисляется ориентация локальной системы координат.

### Возвращаемое значение

Кватернион, представляющий ориентацию локальной геодезической системы координат в мировом пространстве (нулевой курс, нулевой тангаж, нулевой крен в этой точке).
## Math:: Mat4 getZeroBasis ( const Math:: dvec3 & geodetic_coordinate ) const

Возвращает полную матрицу трансформации локальной геодезической системы отсчёта в указанной геодезической позиции. Матрица кодирует как позицию в мировом пространстве, так и локальную ориентацию: ось X указывает на восток, ось Y указывает на север, ось Z указывает вверх (от поверхности Земли). В режиме плоского террейна *[GeodeticPivot](../../../../api/library/geodetics/class.geodeticpivot_cpp.md)* компонент Z оси forward обнуляется, чтобы сохранить её горизонтальность.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Геодезические координаты (широта, долгота, высота), в которых вычисляется базис локальной системы координат.

### Возвращаемое значение

Матрица трансформации с позицией, установленной в точку мирового пространства, и осями, выровненными по локальной геодезической системе координат (восток, север, вверх).
## Math:: vec3 getZeroUpDirection ( const Math:: dvec3 & geodetic_coordinate ) const

Возвращает направление up локальной геодезической системы отсчёта в указанной геодезической позиции в мировом пространстве. Это ось Z матрицы, возвращаемой *[getZeroBasis()](../../../...md#getZeroBasis_dvec3_Mat4)*, т.е. направление от поверхности Земли в этой точке.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Геодезические координаты (широта, долгота, высота), в которых вычисляется локальное направление up.

### Возвращаемое значение

Нормализованный вектор, направленный от поверхности Земли в указанной геодезической точке, выраженный в мировом пространстве.
## Math:: Vec3 worldToProjection ( const Math:: Vec3 & world_position ) const

Преобразует позицию в мировом пространстве в позицию в пространстве проекции, добавляя смещение начала координат проекции. Это смещение — позиция мирового начала координат, выраженная в системе координат проекции (например, в метрах UTM). Неприменимо в режимах **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)** или **[GEODETIC_MODE_NOT_AVAILABLE](../../../...md#GEODETIC_MODE_NOT_AVAILABLE)** — в этих случаях вход возвращается без изменений.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **world_position** - Позиция в 3D-мировом пространстве.

### Возвращаемое значение

Позиция в системе координат проекции (например, в метрах UTM). Равна входному значению в режимах GeodeticPivot или недоступности.
## Math:: Vec3 projectionToWorld ( const Math:: Vec3 & projection_position ) const

Преобразует позицию в пространстве проекции в позицию в мировом пространстве, вычитая смещение начала координат проекции. Это обратное преобразование к **worldToProjection()**. Неприменимо в режимах **[GEODETIC_MODE_GEODETIC_PIVOT](../../../...md#GEODETIC_MODE_GEODETIC_PIVOT)** или **[GEODETIC_MODE_NOT_AVAILABLE](../../../...md#GEODETIC_MODE_NOT_AVAILABLE)** — в этих случаях вход возвращается без изменений.
### Аргументы

- *const  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) &* **projection_position** - Позиция в системе координат проекции (например, в метрах UTM).

### Возвращаемое значение

Позиция в 3D-мировом пространстве. Равна входному значению в режимах GeodeticPivot или недоступности.
## Math:: dvec3 geodeticToGeocentric ( const Math:: dvec3 & geodetic_coordinate , double major_axis = 6378137.0 , double minor_axis = 6356752.314245 ) const

Преобразует геодезические координаты (широта, долгота, высота) в геоцентрические (ECEF — Earth-Centered, Earth-Fixed) декартовы координаты, используя замкнутые уравнения эллипсоида. Значения полуосей по умолчанию соответствуют эллипсоиду WGS84.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Геодезические координаты как (широта в градусах, долгота в градусах, высота в метрах).
- *double* **major_axis** - Большая полуось опорного эллипсоида в метрах. По умолчанию значение WGS84 — 6378137.0 м.
- *double* **minor_axis** - Малая полуось опорного эллипсоида в метрах. По умолчанию значение WGS84 — 6356752.314245 м.

### Возвращаемое значение

Декартовы координаты ECEF в метрах как (X, Y, Z).
## Math:: dvec3 geocentricToGeodetic ( const Math:: dvec3 & geocentric_coordinate , double major_axis = 6378137.0 , double minor_axis = 6356752.314245 ) const

Преобразует геоцентрические (ECEF — Earth-Centered, Earth-Fixed) декартовы координаты в геодезические координаты (широта, долгота, высота), используя замкнутое решение для опорного эллипсоида. Значения полуосей по умолчанию соответствуют эллипсоиду WGS84.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geocentric_coordinate** - Декартовы координаты ECEF в метрах как (X, Y, Z).
- *double* **major_axis** - Большая полуось опорного эллипсоида в метрах. По умолчанию значение WGS84 — 6378137.0 м.
- *double* **minor_axis** - Малая полуось опорного эллипсоида в метрах. По умолчанию значение WGS84 — 6356752.314245 м.

### Возвращаемое значение

Геодезические координаты как (широта в градусах, долгота в градусах, высота в метрах).
## Math:: vec3 geocentricEulerToGeodeticEuler ( const Math:: dvec3 & geodetic_coordinate , const Math:: vec3 & geocentric_euler ) const

Преобразует ориентацию, выраженную как геоцентрические углы Эйлера (Psi/Theta/Phi — рыскание/тангаж/крен в теле ECEF), в геодезические углы Эйлера (курс, тангаж, крен относительно локальной системы North-East-Down) в указанной геодезической позиции. Полезно для преобразования ориентаций, получаемых от систем, работающих в системе ECEF (например, симуляции DIS/HLA), в интуитивно понятные локальные значения курс/тангаж/крен.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Geodetic coordinates (latitude, longitude, altitude) that define the local NED reference frame used for the conversion.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **geocentric_euler** - Ориентация в геоцентрическом теле (ECEF) как (Psi, Theta, Phi) в радианах — рыскание вокруг Z, затем тангаж вокруг Y, затем крен вокруг X.

### Возвращаемое значение

Углы Эйлера в локальной геодезической системе координат (NED) как (тангаж, крен, курс) в радианах.
## Math:: vec3 geodeticEulerToGeocentricEuler ( const Math:: dvec3 & geodetic_coordinate , const Math:: vec3 & geodetic_euler ) const

Преобразует ориентацию, выраженную как геодезические углы Эйлера (курс, тангаж, крен относительно локальной системы North-East-Down), в геоцентрические углы Эйлера (Psi/Theta/Phi в теле ECEF) в указанной геодезической позиции. Это обратное преобразование к **geocentricEulerToGeodeticEuler()**, полезное для преобразования локально заданных ориентаций в тело ECEF для взаимодействия со стандартами симуляции, такими как DIS/HLA.
### Аргументы

- *const  Math::[dvec3](../../../../api/library/math/class.dvec3_cpp.md) &* **geodetic_coordinate** - Geodetic coordinates (latitude, longitude, altitude) that define the local NED reference frame used for the conversion.
- *const  Math::[vec3](../../../../api/library/math/class.vec3_cpp.md) &* **geodetic_euler** - Углы Эйлера в локальной геодезической системе координат (NED) как (тангаж, крен, курс) в градусах — курс вокруг локальной оси Down, тангаж вокруг локальной оси East, крен вокруг локальной оси North.

### Возвращаемое значение

Ориентация в геоцентрическом теле (ECEF) как (Psi, Theta, Phi) в радианах — рыскание вокруг Z, затем тангаж вокруг Y, затем крен вокруг X.
