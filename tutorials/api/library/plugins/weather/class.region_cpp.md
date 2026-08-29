# Unigine::Plugins::Weather::Region Class (CPP)

**Header:** #include <plugins/Unigine/Weather/UnigineWeather.h>


Этот класс используется для управления weather regions. Каждый регион содержит один или несколько [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md), каждый из которых представляет собой вертикальный профиль. [main layer](#getMainLayer_WeatherLayer) всегда существует в регионе и не может быть удалён. Это базовый слой, используемый для задания параметров погоды для региона, таких как [visibility range](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#setVisibility_float_void), [temperature](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#setTemperature_float_void), [humidity](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#setHumidity_float_void) и т.д.


> **Notice:** Плагин IG должен быть загружен.


Доступны три [types](#getRegionType_int) weather regions:

- **Global** - представляют атмосферные слои, не имеющие чётких горизонтальных границ. Атмосферные эффекты наблюдаются в любой точке в пределах вертикального диапазона.
- **Local Rectangle** - имеют тот же набор параметров (видимость, покрытие, ветер), что и *Global*, но атмосферные эффекты для них ограничены определённой областью, заданной прямоугольником.
- **Local Polygon** - имеют тот же набор параметров (видимость, покрытие, ветер), что и *Global*, но атмосферные эффекты для них ограничены определённой областью, заданной полигоном.


Глобальные метеоусловия управляются через класс [Meteo](../../../../api/library/plugins/weather/class.meteo_cpp.md).


## Region Class

### Перечисления

## REGION_TYPE

| Name | Description |
|---|---|
| **REGION_TYPE_GLOBAL** = 0 | Глобальный тип региона (атмосферные слои, не имеющие чётких горизонтальных границ). |
| **REGION_TYPE_RECTANGLE** = 1 | Тип региона "локальный прямоугольник": региональная погода с атмосферными эффектами, ограниченными определённой областью, заданной прямоугольником. |
| **REGION_TYPE_POLYGON** = 2 | Тип региона "локальный полигон": региональная погода с атмосферными эффектами, ограниченными определённой областью, заданной полигоном. |

### Методы класса

---

## void setEnabled ( bool v )

Включает или отключает weather region.
### Аргументы

- *bool* **v** - true, чтобы включить weather region; false - чтобы отключить его.

## bool isEnabled ( ) const

Возвращает значение, указывающее, включён ли в данный момент weather region.
### Возвращаемое значение

true, если weather region в данный момент включён; иначе false.
## long long getID ( ) const

Возвращает ID региона.
### Возвращаемое значение

ID региона.
## WeatherLayer * createLayer ( long long layer_id , WeatherLayerType type )

Создаёт новый weather layer для региона. Если слой с указанным ID существует и имеет другой тип, он будет заменён новым.
### Аргументы

- *long long* **layer_id** - ID создаваемого слоя.
- *WeatherLayerType* **type** - Тип создаваемого слоя, одно из следующих значений:

  - *Plugins::IG::WeatherLayerType::LAYER_BASE* - базовый слой.
  - *Plugins::IG::WeatherLayerType::LAYER_CLOUD* - [cloud layer](../../../../api/library/plugins/weather/class.weatherlayercloud_cpp.md).
  - *Plugins::IG::WeatherLayerType::LAYER_PRECIPITATION* - [precipitation layer](../../../../api/library/plugins/weather/class.weatherlayerprecipitation_cpp.md).

### Возвращаемое значение

Новый weather layer, если он успешно создан; иначе nullptr.
## WeatherLayer * getLayer ( long long layer_id )

Возвращает weather layer по его ID.
### Аргументы

- *long long* **layer_id** - ID weather layer.

### Возвращаемое значение

Weather layer с указанным ID, если он существует; иначе nullptr.
## bool removeLayer ( long long layer_id )

Удаляет weather layer с указанным ID.
### Аргументы

- *long long* **layer_id** - ID weather layer.

### Возвращаемое значение

true, если weather layer успешно создан; иначе false.
## WeatherLayer * getMainLayer ( ) const

Возвращает главный weather layer региона. Это базовый слой, используемый для задания параметров погоды, таких как [visibility range](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#setVisibility_float_void), [temperature](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#setTemperature_float_void), [humidity](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#setHumidity_float_void) и т.д. Главный слой всегда существует в регионе и не может быть удалён.
### Возвращаемое значение

Главный weather layer региона.
## void getLayers ( Vector <WeatherLayer*>& vec ) const

Возвращает список всех [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) (base, clouds, precipitation), содержащихся в weather region.
### Аргументы

- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<WeatherLayer*>&* **vec** - Список всех [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) в weather region.

## void findWeatherLayersGeodetic ( const Math::dvec3& geo_pos , Vector <MeteoPositionParam>& vector ) const

Возвращает список всех [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) (base, clouds, precipitation) weather region, содержащих указанную позицию (и, следовательно, влияющих на неё), вместе с их соответствующими коэффициентами [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) (в виде структуры *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)*).
### Аргументы

- *const  Math::dvec3&* **geo_pos** - Геокоординаты точки, для которой нужно найти все влияющие слои.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<MeteoPositionParam>&* **vector** - Список всех [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) weather region, содержащих указанную позицию (и, следовательно, влияющих на неё), вместе с их соответствующими коэффициентами [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) (в виде структуры *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)*).

## void findWeatherLayersWorld ( const Math::Vec3& world_pos , Vector <MeteoPositionParam>& vector ) const

Возвращает список всех [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) (base, clouds, precipitation) weather region, содержащих указанную позицию (и, следовательно, влияющих на неё), вместе с их соответствующими коэффициентами [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) (в виде структуры *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)*).
### Аргументы

- *const  Math::Vec3&* **world_pos** - Мировые координаты точки, для которой нужно найти все влияющие слои.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<MeteoPositionParam>&* **vector** - Список всех [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) weather region, содержащих указанную позицию (и, следовательно, влияющих на неё), вместе с их соответствующими коэффициентами [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) (в виде структуры *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)*).

## bool setShapeAsRectangle ( const Math::dvec2& size , double corner_radius = 0 )

Задаёт форму weather region в виде [rectangle](#REGION_TYPE_RECTANGLE), используя указанные ширину, высоту и радиус скругления углов.
### Аргументы

- *const  Math::dvec2&* **size** - Вектор, объединяющий ширину и высоту прямоугольника, в единицах (W, H).
- *double* **corner_radius** - Радиус скругления углов прямоугольника, в единицах. Этот параметр позволяет создать прямоугольник со скруглёнными углами. > **Notice:** Это значение не может быть больше половины размера.

### Возвращаемое значение

true, если форма региона успешно задана; иначе false.
## bool setShapeAsPolygon ( const Vector < Math:: vec2 > & points , const Vector < unsigned short > & indices )

Задаёт форму weather region в виде [polygon](#REGION_TYPE_POLYGON), используя указанные наборы координат вершин и их индексов.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[vec2](../../../../api/library/math/class.vec2_cpp.md) > &* **points** - Массив координат вершин полигона.
- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)< unsigned short > &* **indices** - Массив индексов вершин, задающих полигон.

### Возвращаемое значение

true, если форма региона успешно задана; иначе false.
## bool setShapeAsPolygonGeodetic ( const Vector < Math:: dvec2 > & geo_points )

Задаёт форму weather region в виде [polygon](#REGION_TYPE_POLYGON) как набор геокоординат точек.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[dvec2](../../../../api/library/math/class.dvec2_cpp.md) > &* **geo_points** - Массив геокоординат точек, образующих полигон.

### Возвращаемое значение

true, если форма региона успешно задана; иначе false.
## bool setShapeAsPolygonWorld ( const Vector < Math:: Vec3 > & geo_points )

Задаёт форму weather region в виде [polygon](#REGION_TYPE_POLYGON) как набор мировых координат точек.
### Аргументы

- *const [Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<  Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md) > &* **geo_points** - Массив мировых координат точек, образующих полигон.

### Возвращаемое значение

true, если форма региона успешно задана; иначе false.
## Region::REGION_TYPE getRegionType ( ) const

Задаёт тип формы weather region.
### Возвращаемое значение

Тип weather region, одно из следующих значений:
- **GLOBAL** - глобальный (атмосферные слои, не имеющие чётких горизонтальных границ)
- **RECTANGLE** - локальный (региональная погода с атмосферными эффектами, ограниченными определённой областью, заданной прямоугольником)
- **POLYGON** - локальный (региональная погода с атмосферными эффектами, ограниченными определённой областью, заданной полигоном)


## Math:: dvec2 getShapeSize ( ) const

Возвращает размер прямоугольника, определяющего или охватывающего форму weather region, в виде двухкомпонентного вектора.
### Возвращаемое значение

Двухкомпонентный вектор (W, L), содержащий ширину и длину прямоугольника (в метрах), определяющего или охватывающего форму weather region, в зависимости от его типа:
- **Global** - *(inf, inf)*
- **Rectangle** - *(rectangle_width, rectangle_length)*
- **Polygon** - *(boundbox_width, boundbox_length)*


## double getShapeRectangleRadius ( ) const

Возвращает текущий радиус скругления углов прямоугольника. Этот параметр задаёт форму прямоугольника со скруглёнными углами.
### Возвращаемое значение

Текущий радиус скругления углов прямоугольника, в единицах.
## void setTransitionSize ( double width )

Задаёт ширину переходной зоны вокруг границ weather region. Эффекты региона плавно затухают в пределах этой зоны.
### Аргументы

- *double* **width** - Новая ширина переходной зоны вокруг границ weather region для задания, в метрах.

## double getTransitionSize ( ) const

Возвращает текущую ширину переходной зоны вокруг границ weather region. Эффекты региона плавно затухают в пределах этой зоны.
### Возвращаемое значение

Текущая ширина переходной зоны вокруг границ weather region, в метрах.
## void setWorldPosition ( const Math::dvec2& world_pos )

Задаёт новые мировые координаты позиции weather region.
### Аргументы

- *const  Math::dvec2&* **world_pos** - Новые декартовы координаты для задания позиции weather region (X, Y).

## const Math::dvec2& getWorldPosition ( ) const

Возвращает текущие мировые координаты позиции weather region.
### Возвращаемое значение

Текущие декартовы координаты позиции weather region (X, Y).
## void setGeodeticPosition ( const Math::dvec2& geo_pos )

Задаёт новые геокоординаты позиции weather region.
### Аргументы

- *const  Math::dvec2&* **geo_pos** - Геокоординаты позиции weather region (Lat, Lon).

## void setRotation ( float angle_deg )

Поворачивает weather region вокруг оси Z на указанный угол.
### Аргументы

- *float* **angle_deg** - Задаваемый угол поворота, в градусах в диапазоне [-360; 360].

## float getRotation ( ) const

Возвращает текущий угол поворота weather region вокруг оси Z.
### Возвращаемое значение

Текущий угол поворота, в градусах в диапазоне [-360; 360].
## float getImpact ( const Math::dvec2& world_pos ) const

Возвращает значение, указывающее степень воздействия региона в указанной точке в зависимости от того, находится ли она полностью внутри, снаружи или где-то в пределах [transition area](#setTransitionSize_double_void).
### Аргументы

- *const  Math::dvec2&* **world_pos** - Мировые координаты (декартовы) проверяемой точки.

### Возвращаемое значение

Значение, указывающее степень воздействия региона в указанной точке:
- 0 - полностью снаружи региона (и переходной зоны)
- 1 - внутри региона
- (0 < x < 1) - в пределах переходной зоны


## void * addOnChangedCallback ( CallbackBase * callback )

Добавляет callback на изменение параметров региона.
```cpp
/// функция callback, вызываемая при изменении параметров региона
void SomeClass::my_region_callback()
{
	// действия, выполняемые при изменении параметров региона
}

// ...
// где-то в коде
void SomeClass::init()
{
	// добавляем "my_region_callback" для вызова при изменении погодных условий
	ig_manager->getMeteo()->getRegion(1)->addOnChangedCallback(this, Unigine::MakeCallback(this, &SomeClass::my_region_callback );
}

```


### Аргументы

- *[CallbackBase](../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Указатель на callback.

### Возвращаемое значение

ID подписчика callback. Этот ID можно использовать для [remove](#removeOnChangedCallback_void_ptr_bool) этого callback при необходимости.
## bool removeOnChangedCallback ( void * id )

Удаляет callback на изменение параметров региона для указанного подписчика.
### Аргументы

- *void ** **id** - ID подписчика callback, указанный при его [adding](#addOnChangedCallback_CallbackBase_ptr_void_ptr).

### Возвращаемое значение

true, если callback для указанного подписчика успешно удалён; иначе false.
## int getNumLayers ( ) const

Возвращает общее количество слоёв региона.
### Возвращаемое значение

Общее количество слоёв.
