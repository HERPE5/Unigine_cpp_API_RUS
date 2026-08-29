# Unigine::Plugins::Weather::MeteoPositionParam Structure

> **Warning:** Функциональность, описанная в этой статье, недоступна в редакции Community SDK.
> Для её использования следует перейти на редакцию SDK [**Sim**](https://l.unigine.com/SdhugY462).


Эта структура данных используется для хранения [weather layers](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md) вместе с их соответствующими коэффициентами [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float), полученными для определённой точки, и имеет следующий набор параметров:

| **impact** | Степень [impact](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md#getImpact_double_float) условий слоя. |
|---|---|
| **layer** | [Weather layer](../../../../api/library/plugins/weather/class.weatherlayer_cpp.md). |

 Структура **MeteoPositionParam** объявлена следующим образом:
```cpp
struct MeteoPositionParam
{
	float impact = 1.0f;
	WeatherLayer *layer = nullptr;
};

```
