# Unigine::Plugins::Weather::WeatherLayerCloud Class (CPP)

**Header:** #include <plugins/Unigine/Weather/UnigineWeather.h>

**Inherits from:** WeatherLayer


Этот класс используется для представления слоя облаков в пределах [weather region](../../../../api/library/plugins/weather/class.region_cpp.md). Он позволяет задать тип облаков и получить текущий *[Cloud Layer](../../../../objects/objects/cloud_layer/index.md)* для управления его настройками.


## WeatherLayerCloud Class

### Методы класса

## int getCloudType () const

Возвращает текущий тип облаков, заданный для слоя.
### Возвращаемое значение

Текущий индекс [cloud type](../../../../ig/weather/settings.md#clouds) для слоя.
## void setNode ( const Ptr < ObjectCloudLayer >& node )

Задаёт новый узел, представляющий слой облаков (*[ObjectCloudLayer](../../../../objects/objects/cloud_layer/index.md)*).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ObjectCloudLayer](../../../../api/library/objects/class.objectcloudlayer_cpp.md)>&* **node** - Узел, представляющий слой облаков.

## Ptr < ObjectCloudLayer > getNode () const

Возвращает текущий узел, представляющий слой облаков (*[ObjectCloudLayer](../../../../objects/objects/cloud_layer/index.md)*).
### Возвращаемое значение

Текущий узел, представляющий слой облаков.
---

## void setCloudType ( int cloud_type , bool reset_cloud_to_default )

Задаёт новый тип облаков для слоя.
### Аргументы

- *int* **cloud_type** - Индекс [cloud type](../../../../ig/weather/settings.md#clouds) для слоя.
- *bool* **reset_cloud_to_default** - true, чтобы сбросить все параметры слоя облаков на значения по умолчанию, false, чтобы сохранить текущие значения.
