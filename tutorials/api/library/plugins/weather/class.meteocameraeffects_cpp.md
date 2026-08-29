# Unigine::Plugins::Weather::MeteoCameraEffects Class (CPP)

**Header:** #include <plugins/Unigine/Weather/UnigineWeather.h>


## MeteoCameraEffects Class

### Методы класса

## Math:: dvec3 getPosition () const

Возвращает текущую позицию камеры в мировом пространстве.
### Возвращаемое значение

Текущая позиция камеры в мировом пространстве.
## Math:: vec3 getVelocity () const

Возвращает текущую скорость камеры.
### Возвращаемое значение

Текущая скорость камеры в виде трёхкомпонентного вектора, каждая компонента которого представляет скорость вдоль соответствующей оси, в метрах в секунду.
## bool isRenderCloudsTransparentAutoOrder () const

Возвращает текущее значение, указывающее, включена ли автоматическая настройка [transparency rendering order for clouds](../../../../editor2/settings/render_settings/clouds/index.md#accurate_transparent_order).
### Возвращаемое значение

**true**, если автоматическая настройка порядка отрисовки прозрачности для облаков включена; иначе **false**.
## bool isRenderCloudsInterleaveOptimization () const

Возвращает текущее значение, указывающее, включена ли [interleaved rendering optimization for clouds](../../../../editor2/settings/render_settings/clouds/index.md#interleaved_rendering).
### Возвращаемое значение

**true**, если оптимизация чересстрочной отрисовки для облаков включена; иначе **false**.
## bool isRenderAnimationEnabled () const

Возвращает текущее значение, указывающее, включена ли анимация ветра (растительность и вода подвержены влиянию ветра).
### Возвращаемое значение

**true**, если анимация ветра включена (растительность и вода подвержены влиянию ветра); иначе **false**.
## float getCurrentVisibility () const

Возвращает текущую видимость, в метрах.
### Возвращаемое значение

Текущая видимость, в метрах.
## Math:: vec3 getCurrentWind () const

Возвращает текущую скорость ветра по всем направлениям.
### Возвращаемое значение

Текущая скорость ветра по всем направлениям.
---

## void setCloudsOptimizationDistance ( double interleave_1 , double interleave_2 )

Задаёт расстояния от камеры, на которых должны использоваться два уровня [interleaved rendering optimization for clouds](../../../../editor2/settings/render_settings/clouds/index.md#interleaved_rendering).
### Аргументы

- *double* **interleave_1** - Расстояние от камеры (в метрах), на котором для облаков должна использоваться оптимизация чересстрочной отрисовки 2x2.
- *double* **interleave_2** - Расстояние от камеры (в метрах), на котором для облаков должна использоваться оптимизация чересстрочной отрисовки 4x4.
