# Unigine.RenderEnvironmentPreset Class (CPP)

**Header:** #include <UnigineRender.h>


Этот класс представляет [environment preset](../../../editor2/settings/render_settings/environment/index.md#presets). У каждого пресета есть настройки, которые можно получать/задавать с помощью методов класса.


Чтобы получить экземпляр класса, используйте метод *[Render::getEnvironmentPreset()](../../../api/library/rendering/class.render_cpp.md#getEnvironmentPreset_int_RenderEnvironmentPreset)*:

```cpp
// получаем второй пресет окружения
RenderEnvironmentPresetPtr preset = Render::getEnvironmentPreset(1);

```


## RenderEnvironmentPreset Class

### Методы класса

---

## int getNum ( ) const

Возвращает номер пресета.
### Возвращаемое значение

Номер пресета. Доступные значения: **0**, **1**, **2**.
## void setIntensity ( float intensity )

Задаёт интенсивность указанного пресета. Интенсивность пресета используется для смешивания указанного пресета окружения с остальными.
> **Notice:** Пресеты накладываются друг на друга: первый пресет перекрывает нулевой, второй перекрывает первый и нулевой.


### Аргументы

- *float* **intensity** - Интенсивность пресета.

## float getIntensity ( ) const

Возвращает интенсивность пресета. Интенсивность пресета используется для смешивания пресета окружения с остальными.
> **Notice:** Пресеты накладываются друг на друга: первый пресет перекрывает нулевой, второй перекрывает первый и нулевой.


### Возвращаемое значение

Интенсивность пресета.
## void setScatteringMieLUTName ( const char * name )

Задаёт путь к [Mie LUT texture](../../../editor2/settings/render_settings/environment/index.md#mie_lut) (текстура для настройки цвета света вокруг солнца) для пресета. Текстура Mie используется как для солнца, так и для луны.
### Аргументы

- *const char ** **name** - Путь к текстуре.

## const char * getScatteringMieLUTName ( ) const

Возвращает путь к [Mie LUT texture](../../../editor2/settings/render_settings/environment/index.md#mie_lut) (текстура для настройки цвета света вокруг солнца), заданной для пресета. Текстура Mie используется как для солнца, так и для луны.
### Возвращаемое значение

Путь к текстуре.
## void setScatteringLightColorLUTName ( const char * name )

Задаёт путь к [light color texture](../../../editor2/settings/render_settings/environment/index.md#light_lut) (текстура, определяющая цвет LightWorld в разное время суток) для пресета.
### Аргументы

- *const char ** **name** - Путь к текстуре.

## const char * getScatteringLightColorLUTName ( ) const

Возвращает путь к [light color texture](../../../editor2/settings/render_settings/environment/index.md#light_lut) (текстура, определяющая цвет LightWorld в разное время суток).
### Возвращаемое значение

Путь к текстуре.
## void setScatteringBaseLUTName ( const char * name )

Задаёт путь к [base LUT texture](../../../editor2/settings/render_settings/environment/index.md#base_lut) (текстура, определяющая базовый цвет неба) для пресета.
### Аргументы

- *const char ** **name** - Путь к текстуре.

## const char * getScatteringBaseLUTName ( ) const

Возвращает путь к [base LUT texture](../../../editor2/settings/render_settings/environment/index.md#base_lut) (текстура, определяющая базовый цвет неба), заданной для пресета.
### Возвращаемое значение

Путь к текстуре.
## void setHazeMaxDistance ( float distance )

Задаёт [distance](../../../editor2/settings/render_settings/environment/index.md#haze_max_distance), начиная с которого дымка становится полностью плотной, так что позади неё ничего не видно. Для больших терраинов рекомендуется устанавливать этот параметр равным параметру [Far](../../../api/library/rendering/class.camera_cpp.md#getZFar_float) вашей камеры. Это необходимо, чтобы удалённые объекты плавно растворялись в дали, а не резко обрезались.
### Аргументы

- *float* **distance** - Максимальное расстояние видимости дымки.

## float getHazeMaxDistance ( ) const

Возвращает расстояние, начиная с которого дымка становится полностью плотной, так что позади неё ничего не видно.
### Возвращаемое значение

Максимальное расстояние видимости дымки.
## void setHazeColor ( const Math:: vec4 & color )

Задаёт [color of the haze](../../../editor2/settings/render_settings/environment/index.md#haze_color) для пресета. Эта функция вступит в силу только если через *[setEnvironmentHazeMode()](../../../api/library/rendering/class.render_cpp.md#setEnvironmentHazeMode_int_void)* задан режим *[HAZE_SOLID](../../../api/library/rendering/class.render_cpp.md#HAZE_SOLID)*.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет дымки.

## Math:: vec4 getHazeColor ( ) const

Возвращает [color of the haze](../../../editor2/settings/render_settings/environment/index.md#haze_color) для пресета.
> **Notice:** Эта функция вернёт цвет только если через *[setEnvironmentHazeMode()](../../../api/library/rendering/class.render_cpp.md#setEnvironmentHazeMode_int_void)* задан режим [HAZE_SOLID](../../../api/library/rendering/class.render_cpp.md#HAZE_SOLID).


### Возвращаемое значение

Цвет дымки.
## void setHazeDensity ( float density )

Задаёт [density of the haze](../../../editor2/settings/render_settings/environment/index.md#haze_density) для пресета.
### Аргументы

- *float* **density** - Плотность дымки.

## float getHazeDensity ( ) const

Возвращает [density of the haze](../../../editor2/settings/render_settings/environment/index.md#haze_density), заданную для пресета.
### Возвращаемое значение

Плотность дымки.
## void setReflectionIntensity ( float intensity )

Задаёт интенсивность отражения окружения для пресета. Значение **0** означает отсутствие отражения окружения для пресета.
> **Notice:** Рекомендуется использовать значение параметра по умолчанию, чтобы сохранить реалистичность изображения.


### Аргументы

- *float* **intensity** - Значение интенсивности отражения окружения.

## float getReflectionIntensity ( ) const

Возвращает интенсивность отражений окружения для пресета. Значение **0** означает отсутствие отражений окружения для пресета.
### Возвращаемое значение

Значение интенсивности отражений окружения.
## void setSkyIntensity ( float intensity )

Задаёт интенсивность неба окружения для пресета. Значение **0.0f** означает отсутствие неба окружения для пресета.
> **Notice:** Рекомендуется использовать значение параметра по умолчанию, чтобы сохранить реалистичность изображения. Если, например, небо выглядит слишком тёмным на фоне освещения от него, перед изменением интенсивности окружения следует проверить настройки экспозиции и тонмаппинга.


### Аргументы

- *float* **intensity** - Значение интенсивности неба окружения.

## float getSkyIntensity ( ) const

Возвращает интенсивность неба окружения, заданную для пресета.
### Возвращаемое значение

Значение интенсивности неба окружения.
## void setAmbientIntensity ( float intensity )

Задаёт интенсивность фонового освещения окружения для пресета. Значение **0** означает отсутствие фонового освещения окружения для пресета. Чем выше значение, тем сильнее фоновое освещение влияет на окружение.
> **Notice:** Рекомендуется использовать значение параметра по умолчанию, чтобы сохранить реалистичность изображения.


### Аргументы

- *float* **intensity** - Значение интенсивности фонового освещения окружения. Значение может быть больше 1.0f (полезно для тёмных сцен).

## float getAmbientIntensity ( ) const

Возвращает интенсивность фонового освещения окружения для пресета. Значение **0** означает отсутствие фонового освещения окружения для пресета. Чем выше значение, тем сильнее фоновое освещение влияет на окружение.
### Возвращаемое значение

Значение интенсивности фонового освещения окружения. Значение может быть больше 1.0f.
## void setTexture ( const Ptr < Texture > & texture )

Задаёт [cubemap defining the environment color](../../../editor2/settings/render_settings/environment/index.md#env_texture), для пресета. Эта текстура используется для имитации отражений и освещения ландшафта в соответствии с маской земли.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Кубическая текстура, определяющая цвет окружения.

## Ptr < Texture > getTexture ( ) const

Возвращает [cubemap defining the environment color](../../../editor2/settings/render_settings/environment/index.md#env_texture), заданную для пресета. Эта текстура используется для имитации отражений и освещения ландшафта в соответствии с маской земли.
### Возвращаемое значение

Кубическая текстура, определяющая цвет окружения.
## void setTextureName ( const char * name )

Задаёт путь к [cubemap defining the environment color](../../../editor2/settings/render_settings/environment/index.md#env_texture), для пресета. Эта текстура используется для имитации отражений и освещения ландшафта в соответствии с маской земли.
### Аргументы

- *const char ** **name** - Путь к кубической текстуре, определяющей цвет окружения.

## const char * getTextureName ( ) const

Возвращает путь к [cubemap defining the environment color](../../../editor2/settings/render_settings/environment/index.md#env_texture), заданной для пресета. Эта текстура используется для имитации отражений и освещения ландшафта в соответствии с маской земли.
### Возвращаемое значение

Путь к кубической текстуре, определяющей цвет окружения.
## void setTextureColor ( const Math:: vec4 & color )

Задаёт [environment color multiplier](../../../editor2/settings/render_settings/environment/index.md#env_texture_color) для пресета. Альфа-канал определяет видимость кубической текстуры окружения над рассеиванием (scattering). Цветовой множитель нужен, когда требуется одновременно отображать небо с фото-текстурой и динамическими градиентами.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цветовой множитель окружения.

## Math:: vec4 getTextureColor ( ) const

Возвращает [environment color multiplier](../../../editor2/settings/render_settings/environment/index.md#env_texture_color), заданный для пресета. Альфа-канал определяет видимость кубической текстуры окружения над рассеиванием (scattering). Цветовой множитель нужен, когда требуется одновременно отображать небо с фото-текстурой и динамическими градиентами.
### Возвращаемое значение

Цветовой множитель окружения.
## void setTextureRotation ( const Math:: vec3 & rotation )

Задаёт поворот текстуры окружения по трём осям.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **rotation** - Поворот текстуры по осям X, Y, Z, в градусах.

## Math:: vec3 getTextureRotation ( ) const

Возвращает поворот текстуры окружения по трём осям, в градусах.
### Возвращаемое значение

Поворот текстуры по осям X, Y, Z, в градусах.
## void setTextureBlur ( float blur )

Задаёт интенсивность размытия текстуры окружения. Это значение можно использовать для создания размытой панорамы на фоне.
> **Notice:** Отражения и фоновое освещение не размываются.


### Аргументы

- *float* **blur** - Интенсивность размытия.

## float getTextureBlur ( ) const

Возвращает интенсивность размытия текстуры окружения.
> **Notice:** Отражения и фоновое освещение не размываются.


### Возвращаемое значение

Интенсивность размытия.
## float getMoonTextureIntensity ( ) const

Возвращает [intensity multiplier](../../../editor2/settings/render_settings/environment/index.md#moon_intensity) текстуры Луны. Позволяет увеличивать/уменьшать яркость Луны.
### Возвращаемое значение

Интенсивность текстуры Луны.
## void setMoonTextureIntensity ( float intensity )

Задаёт [intensity multiplier](../../../editor2/settings/render_settings/environment/index.md#moon_intensity) текстуры Луны. Позволяет увеличивать/уменьшать яркость Луны.
### Аргументы

- *float* **intensity** - Интенсивность текстуры Луны.

## void setSunTextureColor ( const Math:: vec4 & color )

Задаёт [color multiplier](../../../editor2/settings/render_settings/environment/index.md#sun_color) для текущей текстуры Солнца. По умолчанию равен (1,1,1,1).
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цветовой множитель.

## float getMoonAngularSize ( ) const

Возвращает текущий [angular size](../../../editor2/settings/render_settings/environment/index.md#moon_size) Луны в градусах, как видно с Земли. По умолчанию размер Луны составляет 0.5 градуса.
### Возвращаемое значение

Угловой размер Луны.
## float getSunTextureIntensity ( ) const

Возвращает [intensity multiplier](../../../editor2/settings/render_settings/environment/index.md#sun_intensity) текстуры Солнца. Позволяет увеличивать/уменьшать яркость Солнца.
### Возвращаемое значение

Интенсивность текстуры Солнца.
## Math:: vec4 getMoonTextureColor ( ) const

Возвращает [color multiplier](../../../editor2/settings/render_settings/environment/index.md#moon_color) текстуры Луны.
### Возвращаемое значение

Цветовой множитель.
## void setSunTextureName ( const char * name )

Задаёт [Sun texture](../../../editor2/settings/render_settings/environment/index.md#sun) с указанным именем.
### Аргументы

- *const char ** **name** - Имя текстуры Солнца.

## void setMoonTextureColor ( const Math:: vec4 & color )

Задаёт [color multiplier](../../../editor2/settings/render_settings/environment/index.md#moon_color) для текущей текстуры Луны. По умолчанию равен (1,1,1,1).
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цветовой множитель.

## void setSunTextureIntensity ( float intensity )

Задаёт [intensity multiplier](../../../editor2/settings/render_settings/environment/index.md#sun_intensity) текстуры Солнца. Позволяет увеличивать/уменьшать яркость Солнца.
### Аргументы

- *float* **intensity** - Интенсивность текстуры Солнца.

## void setMoonAngularSize ( float size )

Задаёт [angular size](../../../editor2/settings/render_settings/environment/index.md#moon_size) Луны в градусах. Значение задаётся для наблюдателя на Земле. По умолчанию размер Луны составляет 0.5 градуса, как видно с Земли.
### Аргументы

- *float* **size** - Угловой размер Луны.

## Math:: vec4 getSunTextureColor ( ) const

Возвращает [color multiplier](../../../editor2/settings/render_settings/environment/index.md#sun_color) текстуры Солнца. По умолчанию равен (1,1,1,1).
### Возвращаемое значение

Цветовой множитель.
## void setMoonTextureName ( const char * name )

Задаёт имя [Moon texture](../../../editor2/settings/render_settings/environment/index.md#moon).
### Аргументы

- *const char ** **name** - Имя текстуры Луны.

## void setSunAngularSize ( float size )

Задаёт [angular size](../../../editor2/settings/render_settings/environment/index.md#sun_size) Солнца в градусах. Значение задаётся для наблюдателя на Земле. По умолчанию размер Солнца составляет 0.5 градуса, как видно с Земли.
### Аргументы

- *float* **size** - Угловой размер Солнца.

## float getSunAngularSize ( ) const

Возвращает [angular size](../../../editor2/settings/render_settings/environment/index.md#sun_size) Солнца в градусах, как видно с Земли. По умолчанию размер Солнца составляет 0.5 градуса.
### Возвращаемое значение

Угловой размер Солнца.
## const char * getSunTextureName ( ) const

Возвращает имя [Sun texture](../../../editor2/settings/render_settings/environment/index.md#sun).
### Возвращаемое значение

Имя текстуры Солнца.
## const char * getMoonTextureName ( ) const

Возвращает имя [Moon texture](../../../editor2/settings/render_settings/environment/index.md#moon).
### Возвращаемое значение

Имя текстуры Луны.
## void setHazePhysicalStartHeight ( float height )

Задаёт новое опорное значение высоты для двух параметров ([Half Visibility Distance](#setHazePhysicalHalfVisibilityDistance_float_void) и [Half Faloff Height](#setHazePhysicalHalfFalloffHeight_float_void)).
### Аргументы

- *float* **height** - Новое опорное значение высоты, в единицах.

## float getHazePhysicalStartHeight ( ) const

Возвращает текущее опорное значение высоты для двух параметров ([Half Visibility Distance](#setHazePhysicalHalfVisibilityDistance_float_void) и [Half Faloff Height](#setHazePhysicalHalfFalloffHeight_float_void)).
### Возвращаемое значение

Текущее опорное значение высоты, в единицах.
## void setHazePhysicalHalfVisibilityDistance ( float distance )

Задаёт расстояние до границы, на которой видимость составляет 50%. В реальном мире нулевой видимости не существует, поэтому граница половинной видимости используется для настройки дистанции дымки.
### Аргументы

- *float* **distance** - Новое значение расстояния, в единицах.

## float getHazePhysicalHalfVisibilityDistance ( ) const

Возвращает текущее расстояние до границы, на которой видимость составляет 50%. В реальном мире нулевой видимости не существует, поэтому граница половинной видимости используется для настройки дистанции дымки.
### Возвращаемое значение

Текущее расстояние до границы, на которой видимость составляет 50%, в единицах.
## void setHazePhysicalHalfFalloffHeight ( float height )

Задаёт высоту градиента плотности дымки. Чем *выше* значение, тем *дольше* плотность дымки уменьшается с ростом высоты, делая переход между чистым небом и дымкой более плавным.
### Аргументы

- *float* **height** - Новая высота градиента плотности дымки.

## float getHazePhysicalHalfFalloffHeight ( ) const

Возвращает текущую высоту градиента плотности дымки. Чем *выше* значение, тем *дольше* плотность дымки уменьшается с ростом высоты, делая переход между чистым небом и дымкой более плавным.
### Возвращаемое значение

Текущая высота градиента плотности дымки.
## void setHazePhysicalAmbientLightIntensity ( float intensity )

Задаёт новую интенсивность влияния фонового освещения на дымку (насколько фоновое освещение влияет на дымку).
### Аргументы

- *float* **intensity** - Новое значение интенсивности влияния фонового освещения.

## float getHazePhysicalAmbientLightIntensity ( ) const

Возвращает текущую интенсивность влияния фонового освещения на дымку (насколько фоновое освещение влияет на дымку).
### Возвращаемое значение

Текущее значение интенсивности влияния фонового освещения.
## void setHazePhysicalAmbientColorSaturation ( float saturation )

Задаёт новую интенсивность вклада фонового цвета в дымку (насколько солнечный свет влияет на дымку).
### Аргументы

- *float* **saturation** - Новое значение интенсивности вклада фонового цвета в дымку.

## float getHazePhysicalAmbientColorSaturation ( ) const

Возвращает текущую интенсивность вклада фонового цвета в дымку (насколько солнечный свет влияет на дымку).
### Возвращаемое значение

Текущее значение интенсивности вклада фонового цвета в дымку.
## void setHazePhysicalSunLightIntensity ( float intensity )

Задаёт новую интенсивность влияния солнечного света на дымку (насколько солнечный свет влияет на дымку).
### Аргументы

- *float* **intensity** - Новое значение интенсивности влияния солнечного света.

## float getHazePhysicalSunLightIntensity ( ) const

Возвращает текущую интенсивность влияния солнечного света на дымку, определяющую, насколько солнечный свет влияет на дымку.
### Возвращаемое значение

Текущее значение интенсивности влияния солнечного света.
## void setHazePhysicalSunColorSaturation ( float saturation )

Задаёт новую интенсивность влияния солнечного света на дымку (насколько солнечный свет влияет на дымку).
> **Notice:** "Цвет солнечного света" здесь означает не просто цветовой множитель источника [*WorldLight*](../../../api/library/lights/class.lightworld_cpp.md), а скорее [*Scattering LUT Light Color*](#setScatteringLightColorLUTName_cstr_void).


### Аргументы

- *float* **saturation** - Новое значение интенсивности вклада цвета солнечного света в дымку.

## float getHazePhysicalSunColorSaturation ( ) const

Возвращает текущую интенсивность влияния солнечного света на дымку (насколько солнечный свет влияет на дымку).
### Возвращаемое значение

Текущая интенсивность вклада цвета солнечного света в дымку.
## void setHazeScatteringMieIntensity ( float intensity )

Задаёт минимальное значение интенсивности Ми для областей, затенённых геометрией. Это значение определяет долю интенсивности Ми, видимую при взгляде на поверхность прямо в лоб. Установка этого значения в 1 отключает эффект Френеля. Этот параметр можно использовать вместе с *Mie Frontside Intensity**[setHazeScatteringMieFrontSideIntensity](../../...md#setHazeScatteringMieFrontSideIntensity_float_void)* и *Mie Fresnel Power**[setHazeScatteringMieFresnelPower](../../...md#setHazeScatteringMieFresnelPower_float_void)* для управления окклюзией света от источников света типа *World*. Работает как для непрозрачных, так и для прозрачных объектов.
### Аргументы

- *float* **intensity** - Новое минимальное значение интенсивности Ми для областей, затенённых геометрией, в диапазоне [0.0f, 1.0f].

## float getHazeScatteringMieIntensity ( ) const

Возвращает текущее минимальное значение интенсивности Ми для областей, затенённых геометрией. Это значение определяет долю интенсивности Ми, видимую при взгляде на поверхность прямо в лоб. Установка этого значения в 1 отключает эффект Френеля. Этот параметр можно использовать вместе с *Mie Frontside Intensity**[setHazeScatteringMieFrontSideIntensity](../../...md#setHazeScatteringMieFrontSideIntensity_float_void)* и *Mie Fresnel Power**[setHazeScatteringMieFresnelPower](../../...md#setHazeScatteringMieFresnelPower_float_void)* для управления окклюзией света от источников света типа *World*. Работает как для непрозрачных, так и для прозрачных объектов.
### Возвращаемое значение

Текущее минимальное значение интенсивности Ми для областей, затенённых геометрией, в диапазоне [0.0f, 1.0f].
## void setHazeScatteringMieFrontSideIntensity ( float intensity )

Задаёт затухание эффекта Френеля для интенсивности Ми. Это значение используется для управления окклюзией света от источника World light геометрией.
### Аргументы

- *float* **intensity** - Затухание эффекта Френеля для интенсивности Ми.

## float getHazeScatteringMieFrontSideIntensity ( ) const

Возвращает затухание эффекта Френеля для интенсивности Ми. Это значение используется для управления окклюзией света от источника World light геометрией.
### Возвращаемое значение

Затухание эффекта Френеля для интенсивности Ми.
## void setHazeScatteringMieFresnelPower ( float power )

Задаёт степень эффекта Френеля для видимости Ми. *Более высокие* значения сужают затрагиваемые области, а *более низкие* позволяют эффекту Френеля затрагивать больше областей.
### Аргументы

- *float* **power** - Новая степень эффекта Френеля.

## float getHazeScatteringMieFresnelPower ( ) const

Возвращает текущую степень эффекта Френеля для видимости Ми. *Более высокие* значения сужают затрагиваемые области, а *более низкие* позволяют эффекту Френеля затрагивать больше областей.
### Возвращаемое значение

Текущая степень эффекта Френеля.
