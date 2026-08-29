# Unigine::Plugins::Weather::Meteo Class (CPP)

**Header:** #include <plugins/Unigine/Weather/UnigineWeather.h>


Этот класс используется для управления глобальными метеоусловиями (дальность видимости, скорость и направление ветра).

> **Notice:** Плагин Weather должен быть загружен.


## Meteo Class

### Методы класса

## MeteoCameraEffects * getCameraEffects () const

Возвращает текущий экземпляр [camera effects](../../../../api/library/plugins/weather/class.meteocameraeffects_cpp.md), используемый для создания динамических эффектов отрисовки осадков при изменении позиции и скорости камеры.
### Возвращаемое значение

Текущий экземпляр camera effects.
## Region * getGlobalRegion () const

Возвращает текущий главный глобальный [weather region](../../../../api/library/plugins/weather/class.region_cpp.md).
### Возвращаемое значение

Текущий главный глобальный [weather region](../../../../api/library/plugins/weather/class.region_cpp.md).
## int getNumRegions () const

Возвращает текущее общее количество [weather regions](../../../../api/library/plugins/weather/class.region_cpp.md).
### Возвращаемое значение

Текущее общее количество [weather regions](../../../../api/library/plugins/weather/class.region_cpp.md).
## double getCloudBottom () const

Возвращает текущую высоту нижней границы самого нижнего слоя облаков среди всех [weather regions](../../../../api/library/plugins/weather/class.region_cpp.md).
### Возвращаемое значение

Текущая высота нижней границы самого нижнего слоя облаков среди всех weather regions.
---

## Region * getRegion ( long long id , bool auto_create )

Возвращает интерфейс [weather region/layer](../../../../api/library/plugins/weather/class.region_cpp.md) по его идентификатору. Если weather region/layer с таким id не существует, он будет создан.
### Аргументы

- *long long* **id** - Идентификатор weather region.
- *bool* **auto_create** - true, чтобы автоматически создать регион с указанным ID, если он ещё не существует; false - чтобы вернуть nullptr, если регион не существует.

### Возвращаемое значение

Интерфейс [Weather region](../../../../api/library/plugins/weather/class.region_cpp.md), если он существует; иначе - nullptr.
## bool removeRegion ( long long id )

Удаляет [weather region](../../../../api/library/plugins/weather/class.region_cpp.md) с указанным идентификатором.
### Аргументы

- *long long* **id** - Идентификатор weather region для удаления.

### Возвращаемое значение

true, если регион с указанным идентификатором успешно удалён; иначе false.
## void clearRegions ( )

Удаляет все [weather regions and layers](../../../../api/library/plugins/weather/class.region_cpp.md).
## Math:: vec3 getMeanWindVelocityGeodetic ( const Math::dvec3& geo_pos ) const

Возвращает среднюю скорость ветра в указанной геодезической точке. Этот метод объединяет параметры ветра всех [weather regions and layers](../../../../api/library/plugins/weather/class.region_cpp.md), влияющих на эту точку.
### Аргументы

- *const  Math::dvec3&* **geo_pos** - Геодезические координаты точки (широта, долгота, высота), для которой должны быть вычислены средняя скорость и направление ветра.

### Возвращаемое значение

Вектор, задающий среднюю скорость ветра (в метрах в секунду) по всем направлениям для указанной точки.
## Math:: vec3 getMeanWindVelocityWorld ( const Math::Vec3& world_pos ) const

Возвращает среднюю скорость ветра в указанной мировой точке. Этот метод объединяет параметры ветра всех [weather regions and layers](../../../../api/library/plugins/weather/class.region_cpp.md), влияющих на эту точку.
### Аргументы

- *const  Math::Vec3&* **world_pos** - Мировые координаты точки (широта, долгота, высота), для которой должны быть вычислены средняя скорость и направление ветра.

### Возвращаемое значение

Вектор, задающий среднюю скорость ветра (в метрах в секунду) по всем направлениям для указанной точки.
## void * addOnCreateRegionCallback ( Unigine:: CallbackBase1 < Unigine::Plugins::IG::Region >* func )

Задаёт функцию callback, вызываемую при создании нового [weather region](../../../../api/library/plugins/weather/class.region_cpp.md).
### Аргументы

- *Unigine::[CallbackBase1](../../../../api/library/common/callbacks/class.callbackbase1_cpp.md) <  Unigine::Plugins::IG::Region >** **func** - Указатель на callback. Функция callback должна иметь следующую сигнатуру: (*Unigine::Plugins::IG::Region* ***region**)

### Возвращаемое значение

ID последнего добавленного callback Create Region, если callback был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnCreateRegionCallback_void_ptr_bool) этого callback при необходимости.
## bool removeOnCreateRegionCallback ( void * id )

Удаляет указанный callback из списка callback Create Region.
### Аргументы

- *void ** **id** - ID callback Create Region, полученный при его [adding](#addOnCreateRegionCallback_CallbackBase1_ptr_void_ptr).

### Возвращаемое значение

true, если callback Create Region с указанным ID был успешно удалён; иначе false.
## void clearOnCreateRegionCallbacks ( )

Очищает все [added](#addOnCreateRegionCallback_CallbackBase1_ptr_void_ptr) callback Create Region.
## void * addOnRemoveRegionCallback ( Unigine:: CallbackBase1 < Unigine::Plugins::IG::Region >* func )

Задаёт функцию callback, вызываемую при удалении [weather region](../../../../api/library/plugins/weather/class.region_cpp.md).
### Аргументы

- *Unigine::[CallbackBase1](../../../../api/library/common/callbacks/class.callbackbase1_cpp.md) <  Unigine::Plugins::IG::Region >** **func** - Указатель на callback. Функция callback должна иметь следующую сигнатуру: (*Unigine::Plugins::IG::Region* ***region**)

### Возвращаемое значение

ID последнего добавленного callback Remove Region, если callback был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnRemoveRegionCallback_void_ptr_bool) этого callback при необходимости.
## bool removeOnRemoveRegionCallback ( void * id )

Удаляет указанный callback из списка callback Remove Region.
### Аргументы

- *void ** **id** - ID callback Remove Region, полученный при его [adding](#addOnRemoveRegionCallback_CallbackBase1_ptr_void_ptr).

### Возвращаемое значение

true, если callback Remove Region с указанным ID был успешно удалён; иначе false.
## void clearOnRemoveRegionCallbacks ( )

Очищает все [added](#addOnRemoveRegionCallback_CallbackBase1_ptr_void_ptr) callback Remove Region.
## void * addOnLightningStrikeCallback ( Unigine:: CallbackBase2 < Unigine:: Math:: Vec3 , int > * func )

Задаёт функцию callback, вызываемую при ударе молнии.
### Аргументы

- *Unigine::[CallbackBase2](../../../../api/library/common/callbacks/class.callbackbase2_cpp.md) <  Unigine:: Math::[Vec3](../../../../api/library/math/class.vec3_cpp.md), int > ** **func** - Указатель на callback. Функция callback должна иметь следующую сигнатуру: (*Unigine::Math::Vec3* **geo_pos**, *int* **type**)

### Возвращаемое значение

ID последнего добавленного callback Lightning Strike, если callback был успешно добавлен; иначе **nullptr**. Этот ID можно использовать для [remove](#removeOnLightningStrikeCallback_void_ptr_bool) этого callback при необходимости.
## bool removeOnLightningStrikeCallback ( void * id )

Удаляет указанный callback из списка callback Lightning Strike.
### Аргументы

- *void ** **id** - ID callback Lightning Strike, полученный при его [adding](#addOnLightningStrikeCallback_CallbackBase2_ptr_void_ptr).

### Возвращаемое значение

true, если callback Lightning Strike с указанным ID был успешно удалён; иначе false.
## void clearOnLightningStrikeCallbacks ( )

Очищает все [added](#addOnLightningStrikeCallback_CallbackBase2_ptr_void_ptr) callback Lightning Strike.
## void * addOnMeteoChangedCallback ( CallbackBase * callback )

Добавляет callback на изменение глобальных метеоусловий.
```cpp
/// функция callback, вызываемая при изменении погодных условий
void SomeClass::my_weather_callback()
{
	// задаём ориентацию флюгера по ветру
	Vec3 geo_position = ig_manager->getConverter()->worldToGeodetic(vane_node->getWorldPosition());
	vec3 wind_direction = ig_manager->getMeteo()->getMeanWindSpeed(geo_position);
	vane_node->setWorldDirection(wind_direction, vec3_up);
}

// ...
// где-то в коде
void SomeClass::init()
{
	// добавляем "my_weather_callback" для вызова при изменении погодных условий
	ig_manager->getMeteo()->addOnMeteoChangedCallback(this, Unigine::MakeCallback(this, &SomeClass::my_weather_callback ));
}

```


### Аргументы

- *[CallbackBase](../../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback** - Указатель на callback.

### Возвращаемое значение

ID подписчика callback. Этот ID можно использовать для [remove](#removeOnMeteoChangedCallback_void_ptr_bool) этого callback при необходимости.
## void removeOnMeteoChangedCallback ( void * subscriber )

Удаляет callback на изменение глобальных метеоусловий для указанного подписчика.
### Аргументы

- *void ** **subscriber** - ID подписчика callback, указанный при его [adding](#addOnMeteoChangedCallback_CallbackBase_ptr_void_ptr).

## void clearOnMeteoChangedCallbacks ( )

Очищает все [added](#addOnMeteoChangedCallback_CallbackBase_ptr_void_ptr) callback на изменение глобальных метеоусловий.
## void findWeatherLayersGeodetic ( const Math::dvec3& geo_pos , Vector <MeteoPositionParam>& vector ) const

Returns the list of all [weather layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) (base, clouds, precipitation) of all [weather regions](../../../../api/library/plugins/weather/class.region_cpp.md) containing the specified geodetic position (and thus affecting it) along with their corresponding [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) factors (as *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)* structure).
### Аргументы

- *const  Math::dvec3&* **geo_pos** - Geocoordinates of the point for which all affecting layers of all regions are to be found.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<MeteoPositionParam>&* **vector** - The list of all [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) in the weather region containing the specified position (and thus affecting it) along with their corresponding [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) factors (as *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)* structure).

## void findWeatherLayersGeodetic ( const Vec3& geo_pos , Vector <MeteoPositionParam>& vector ) const

Returns the list of all [weather layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) (base, clouds, precipitation) of all [weather regions](../../../../api/library/plugins/weather/class.region_cpp.md) containing the specified world position (and thus affecting it) along with their corresponding [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) factors (as *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)* structure).
### Аргументы

- *const Vec3&* **geo_pos** - World coordinates of the point for which all affecting layers of all regions are to be found.
- *[Vector](../../../../api/library/containers/vector/class.vector_cpp.md)<MeteoPositionParam>&* **vector** - The list of all [layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) in the weather region containing the specified position (and thus affecting it) along with their corresponding [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) factors (as *[MeteoPositionParam](../../../../api/library/plugins/weather/class.meteopositionparam_cpp.md)* structure).

## void lightningStrikeGeodetic ( const Math::dvec3& geo_pos , int type = -1 )

Генерирует эффект удара молнии в указанной геодезической точке.
### Аргументы

- *const  Math::dvec3&* **geo_pos** - Геокоординаты места удара молнии.
- *int* **type**

## void lightningStrikeWorld ( const Math::Vec3& world_pos , int type = -1 )

Генерирует эффект удара молнии в указанной мировой точке.
### Аргументы

- *const  Math::Vec3&* **world_pos** - Мировые координаты места удара молнии.
- *int* **type**

## Region * getRegionByIndex ( int index )

Возвращает [weather region](../../../../api/library/plugins/weather/class.region_cpp.md) по его индексу.
### Аргументы

- *int* **index** - Индекс weather region в диапазоне от 0 до [total number of regions.](#getNumRegions_int)

### Возвращаемое значение

Weather region с указанным индексом, если он существует; иначе nullptr.
