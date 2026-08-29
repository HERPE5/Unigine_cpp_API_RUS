# Unigine.Renderer Class (CPP)

**Header:** #include <UnigineRender.h>

> **Notice:** Этот класс является синглтоном.


Базовый интерфейс для установки состояния рендерера (изменения параметров проходов рендеринга): передачи униформ шейдера, установки матриц *modelview* и *projection* и т.д. Этот класс используется для рендеринга пользовательских узлов (например, узла, унаследованного от *[ObjectExtern](../../../api/library/objects/class.objectextern_cpp.md)*).


Класс *Renderer* предоставляет следующие структуры, представляющие константные буферы:


## Renderer Class

### Перечисления

## RENDER_STEREO_EYE

Перечисление стереоглаз.
| Name | Description |
|---|---|
| **RENDER_STEREO_EYE_NONE** = 0 | Ни один из стереоглаз. |
| **RENDER_STEREO_EYE_LEFT** = 1 | Левый стереоглаз. |
| **RENDER_STEREO_EYE_RIGHT** = 2 | Правый стереоглаз. |
| **RENDER_STEREO_EYE_LEFT_FOCUS** = 3 | Вид фокуса левого глаза. |
| **RENDER_STEREO_EYE_RIGHT_FOCUS** = 4 | Вид фокуса правого глаза. |

### Structs

## struct CBufferCamera

Структура, представляющая буфер для хранения параметров камеры.
### Fields

- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **camera_projection** - Матрица проекции камеры.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **camera_iprojection** - Обратная матрица проекции камеры.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **oblique_frustum_plane** - Мировые координаты плоскости отсечения наклонной пирамиды видимости в формате *(Nx, Ny, Nz, D)*, где *Nx*, *Ny*, *Nz* - координаты нормали плоскости, а D - расстояние от начала координат до плоскости.
- *int* **is_oblique_frustum** - Флаг, указывающий, является ли пирамида видимости наклонной.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **projection** - Матрица проекции.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **iprojection** - Обратная матрица проекции.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **projection_screen** - Матрица проекции для экранного эффекта.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **iprojection_screen** - Обратная матрица проекции для экранного эффекта.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **imodelview** - Обратная матрица вида.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **old_imodelview** - Старая обратная матрица вида, используемая для рендеринга предыдущего кадра.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **old_imodelview_delta** - Разница между старой обратной матрицей вида и текущей обратной матрицей вида.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **modelview** - Матрица вида.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **old_modelview** - Старая матрица вида.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **camera_offset** - Дополнительное преобразование камеры (смещение). Это преобразование применяется после преобразования вида. Смещение не влияет на матрицу вида или позицию камеры.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **camera_position** - Позиция камеры.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **camera_direction** - Инвертированный нормализованный вектор направления камеры.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **projection_row_0** - Первая строка матрицы проекции камеры.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **projection_row_1** - Вторая строка матрицы проекции камеры.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **projection_row_2** - Третья строка матрицы проекции камеры.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **modelview_projection_x** - Первая строка матрицы вида-проекции.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **modelview_projection_y** - Вторая строка матрицы вида-проекции.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **modelview_projection_w** - Третья строка матрицы вида-проекции.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **modelview_projection_old_x** - Первая строка старой матрицы вида-проекции, используемой для рендеринга предыдущего кадра.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **modelview_projection_old_y** - Вторая строка старой матрицы вида-проекции, используемой для рендеринга предыдущего кадра.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **modelview_projection_old_w** - Третья строка старой матрицы вида-проекции, используемой для рендеринга предыдущего кадра.
- *float* **camera_fov** - Вертикальное поле зрения камеры.
- *int* **shadow_cascade_target** - Текущий каскад теней, используемый для рендеринга теней.

## struct CBufferScattering

Структура, представляющая буфер для хранения [scattering parameters](../../../editor2/settings/render_settings/environment/index.md).
### Fields

- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **scattering_sun_dir** - Вектор направления источника World light, имеющего [scattering mode](../../../api/library/lights/class.lightworld_cpp.md#SCATTERING) Sun.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **scattering_moon_dir** - Вектор направления источника World light, имеющего [scattering mode](../../../api/library/lights/class.lightworld_cpp.md#SCATTERING) Moon.
- *float* **environment_ambient_intensity** - [Intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getAmbientIntensity_float) фонового освещения окружения. Чем выше значение, тем сильнее фоновое освещение влияет на окружение. 0 означает отсутствие отражения окружения.
- *float* **environment_reflection_intensity** - [Intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getReflectionIntensity_float) отражения окружения.
- *float* **environment_sky_intensity** - [Intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getSkyIntensity_float) неба окружения. 0 означает отсутствие неба окружения.
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **haze_color** - [Haze color](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazeColor_vec4).
- *float* **haze_max_distance** - [Distance](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazeMaxDistance_float), начиная с которого дымка становится полностью плотной, так что позади неё ничего не видно.
- *float* **haze_density** - [Density of the haze](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazeDensity_float).
- *float* **haze_physical_start_height** - Значение [reference height](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazePhysicalStartHeight_float) для дистанции половинной видимости и высоты половинного затухания.
- *float* **haze_physical_density** - [Distance](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazePhysicalHalfVisibilityDistance_float) до границы, на которой видимость составляет 50%. В реальном мире нулевой видимости не существует, поэтому граница половинной видимости используется для настройки дистанции дымки.
- *float* **haze_physical_falloff** - [Height](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazePhysicalHalfFalloffHeight_float) градиента плотности дымки. Чем выше значение, тем дольше плотность дымки уменьшается с ростом высоты, делая переход между чистым небом и дымкой более плавным.
- *float* **haze_physical_zero_visibility_height** - Высота, на которой дымка полностью перекрывает сцену.
- *float* **haze_physical_screen_space_global_illumination** - [Value](../../../api/library/rendering/class.render_cpp.md#setEnvironmentHazeScreenSpaceGlobalIllumination_int_void), указывающее, включён ли эффект Screen-Space Haze Global Illumination.
- *float* **haze_physical_ambient_light_intensity** - [Intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazePhysicalAmbientLightIntensity_float) влияния фонового освещения на дымку (насколько фоновое освещение влияет на дымку).
- *float* **haze_physical_ambient_color_saturation** - [Intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazePhysicalAmbientColorSaturation_float) вклада фонового цвета в дымку (насколько солнечный свет влияет на дымку).
- *float* **haze_physical_sun_light_intensity** - [Intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazePhysicalSunLightIntensity_float) влияния солнечного света на дымку (насколько солнечный свет влияет на дымку).
- *float* **haze_physical_sun_color_saturation** - [Intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazePhysicalSunColorSaturation_float) влияния солнечного света на дымку (насколько солнечный свет влияет на дымку).
- *float* **haze_scattering_mie_intensity** - Минимальное значение [Mie intensity](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazeScatteringMieIntensity_float) для областей, затенённых геометрией. Это значение определяет долю интенсивности Ми, видимую при взгляде на поверхность прямо в лоб.
- *float* **haze_scattering_mie_front_side_intensity** - [Falloff](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazeScatteringMieFrontSideIntensity_float) эффекта Френеля для интенсивности Ми. Это значение используется для управления окклюзией света от источника World light геометрией.
- *float* **haze_scattering_mie_fresnel_power** - [Power](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md#getHazeScatteringMieFresnelPower_float) эффекта Френеля для видимости Ми. Более высокие значения сужают затрагиваемые области, а более низкие позволяют эффекту Френеля затрагивать больше областей.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **sky_up** - Вектор "вверх" неба.
- *float* **sky_altitude** - Высота неба.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **sky_transform** - Матрица трансформации неба.
- *Math::[vec3](../../../api/library/math/class.vec3_cpp.md)* **sun_color** - Цвет солнца.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **sun_rotation** - Матрица поворота солнца.
- *Math::[mat4](../../../api/library/math/class.mat4_cpp.md)* **moon_rotation** - Матрица поворота луны.

## struct CBufferTonemapper

Структура, представляющая буфер для хранения [tone mapping parameters](../../../editor2/settings/render_settings/color/index.md#tonemapper).
### Fields

- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **filmic_curve** - Вектор параметров для [tone mapping curve](../../../editor2/settings/render_settings/color/index.md#filmic).
- *Math::[vec4](../../../api/library/math/class.vec4_cpp.md)* **filmic_white** - Параметр, определяющий яркость, при которой пиксель становится чисто белым на итоговом изображении.
- *float* **filmic_saturation_recovery** - Значение [color saturation recovery](../../../api/library/rendering/class.render_cpp.md#getFilmicSaturationRecovery_float) для filmic-тонмаппера.
- *float* **aces_white_clip** - Параметр [white clip](../../../api/library/rendering/class.render_cpp.md#getACESWithReinhardWhiteClip_float) для оператора ACES. Определяет точку отсечения для белого цвета.
- *float* **aces_toe** - [Toe parameter](../../../api/library/rendering/class.render_cpp.md#getACESToe_float) для оператора ACES. Определяет тёмные цвета. Более высокие значения дают более тёмные цвета.
- *float* **aces_shoulder_angle** - [Shoulder angle parameter](../../../api/library/rendering/class.render_cpp.md#getACESShoulderAngle_float) для оператора ACES. Определяет, насколько сильно должен быть добавлен overshoot к shoulder кривой.
- *float* **aces_shoulder_strength** - [Shoulder strength parameter](../../../api/library/rendering/class.render_cpp.md#getACESShoulderStrength_float) для оператора ACES. Определяет силу перехода между средней частью кривой и её shoulder.
- *float* **aces_shoulder_length** - [Shoulder length parameter](../../../api/library/rendering/class.render_cpp.md#getACESShoulderLength_float) для оператора ACES. Определяет количество f-ступеней, добавляемых к динамическому диапазону кривой. Определяет, насколько сильно кривая учитывает светлые участки.
- *float* **aces_with_reinhard_mix** - Вклад оператора [ACES with Reinhard tone mapping](../../../api/library/rendering/class.render_cpp.md#getACESWithReinhardMix_float).
- *float* **aces_with_reinhard_white_clip** - Параметр [white clip](../../../api/library/rendering/class.render_cpp.md#getACESWithReinhardWhiteClip_float) для оператора ACES with Reinhard. Определяет точку отсечения для белого цвета оператора ACES with Reinhard.
- *float* **aces_with_reinhard_toe** - [Toe parameter](../../../api/library/rendering/class.render_cpp.md#getACESWithReinhardToe_float) для оператора ACES with Reinhard. Определяет тёмные цвета. Более высокие значения дают более тёмные цвета.
- *float* **aces_with_reinhard_shoulder_angle** - [Shoulder angle](../../../api/library/rendering/class.render_cpp.md#getACESWithReinhardShoulderAngle_float) для оператора ACES with Reinhard. Определяет, насколько сильно должен быть добавлен overshoot к shoulder кривой.
- *float* **aces_with_reinhard_shoulder_strength** - [Shoulder strength](../../../api/library/rendering/class.render_cpp.md#getACESWithReinhardShoulderStrength_float) для оператора ACES with Reinhard. Определяет силу перехода между средней частью кривой и её shoulder.
- *float* **aces_with_reinhard_shoulder_length** - [Shoulder length](../../../api/library/rendering/class.render_cpp.md#getACESWithReinhardShoulderLength_float) для оператора ACES with Reinhard. Определяет количество f-ступеней, добавляемых к динамическому диапазону кривой. Определяет, насколько сильно кривая учитывает светлые участки.
- *float* **reinhard_contribution** - Вклад оператора [Reinhard tone mapping](../../../api/library/rendering/class.render_cpp.md#getReinhardContribution_float).
- *float* **reinhard_luma_based_contribution** - Вклад оператора [Reinhard Luma-Based tone mapping](../../../api/library/rendering/class.render_cpp.md#getReinhardLumaBasedContribution_float). Определяет общий вклад, который оператор Reinhard вносит в финальную цветокоррекцию изображения.

### Методы класса

## Ptr < Texture > getTextureGBufferVelocity () const

Возвращает текущую [Gbuffer velocity texture](../../../principles/render/sequence/index.md#velocity).
### Возвращаемое значение

Текущая текстура скорости Gbuffer.
## Ptr < Texture > getTextureGBufferFeatures () const

Возвращает текущую текстуру, хранящую интенсивность [screen-space bevel effect](../../../api/library/rendering/class.render_cpp.md#setSSBevel_int_void).
### Возвращаемое значение

Текущая текстура, хранящая интенсивность фасок. Текстура имеет формат **RGBA8**, значение интенсивности записывается в канал **R**.
## Ptr < Texture > getTextureGBufferMaterialMask () const

Возвращает текущую [Gbuffer material mask texture](../../../principles/render/sequence/index.md#material_mask).
### Возвращаемое значение

Текущая текстура маски материала Gbuffer.
## Ptr < Texture > getTextureGBufferNormal () const

Возвращает текущую [Gbuffer normal texture](../../../principles/render/sequence/index.md#normal).
### Возвращаемое значение

Текущая текстура нормалей Gbuffer.
## Ptr < Texture > getTextureGBufferShading () const

Возвращает текущую [Gbuffer shading texture](../../../principles/render/sequence/index.md#shading).
### Возвращаемое значение

Текущая текстура шейдинга Gbuffer.
## Ptr < Texture > getTextureGBufferAlbedo () const

Возвращает текущую [Gbuffer albedo texture](../../../principles/render/sequence/index.md#albedo).
### Возвращаемое значение

Текущая текстура альбедо Gbuffer.
## Ptr < Texture > getTextureClouds () const

Возвращает текущую текстуру облаков. Эта текстура рендерится во время отдельного прохода облаков.
### Возвращаемое значение

Текущая текстура облаков.
## Ptr < Texture > getTextureAutoWhiteBalance () const

Возвращает текущую [auto white balance texture](../../../editor2/settings/render_settings/camera_effects/index.md#white_balance).
### Возвращаемое значение

Текущая текстура автоматического баланса белого.
## Ptr < Texture > getTextureAutoExposure () const

Возвращает текущую текстуру автоэкспозиции.
### Возвращаемое значение

Текущая текстура автоэкспозиции.
## Ptr < Texture > getTextureDOFMask () const

Возвращает текущую текстуру маски DoF. Эта текстура используется на [camera effects stage](../../../principles/render/sequence/index.md#dof).
### Возвращаемое значение

Текущая текстура маски DoF.
## Ptr < Texture > getTextureSSCurvature () const

Возвращает текущую текстуру, используемую эффектом [Screen-Space Dirt (SSDirt)](../../../editor2/settings/render_settings/ssdirt/index.md).
### Возвращаемое значение

Текущая текстура кривизны, используемая эффектом [Screen-Space Dirt (SSDirt)](../../../editor2/settings/render_settings/ssdirt/index.md).
## Ptr < Texture > getTextureSSR () const

Возвращает текущую [SSR texture](../../../principles/render/sequence/index.md#ssr).
### Возвращаемое значение

Текущая текстура SSR.
## Ptr < Texture > getTextureSSGI () const

Возвращает текущую [SSGI texture](../../../principles/render/sequence/index.md#ssgi).
### Возвращаемое значение

Текущая текстура SSGI.
## Ptr < Texture > getTextureSSShadowShafts () const

Возвращает текущую текстуру Screen-Space Shadow Shafts.
### Возвращаемое значение

Текущая текстура Screen-Space Shadow Shafts.
## Ptr < Texture > getTextureSSAO () const

Возвращает текущую [SSAO texture](../../../principles/render/sequence/index.md#ssao).
### Возвращаемое значение

Текущая текстура SSAO.
## Ptr < Texture > getTextureBentNormal () const

Возвращает текущую текстуру bent normal. Эта текстура используется на [Screen-Space Global Illumination stage](../../../principles/render/sequence/index.md#ssgi).
### Возвращаемое значение

Текущая текстура bent normal.
## Ptr < Texture > getTextureIndirectLights () const

Возвращает текущую массивную текстуру, хранящую содержимое [deferred reflections buffer](../../../principles/render/sequence/index.md#deferred_reflection). Текстура содержит два слоя формата **RG11B10F**: первый слой хранит цвет отражения окружения, а второй - фоновое освещение окружения.
### Возвращаемое значение

Текущая текстура, хранящая содержимое буфера отложенных отражений.
## Ptr < Texture > getTextureDirectLights () const

Возвращает текущую массивную текстуру, хранящую содержимое [deferred light buffer](../../../principles/render/sequence/index.md#lights). Текстура содержит два слоя формата **RG11B10F**: первый слой хранит рассеянный свет, а второй - зеркальный свет.
### Возвращаемое значение

Текущая текстура, хранящая содержимое буфера отложенного освещения.
## Ptr < Texture > getTextureTransparentBlur () const

Возвращает текущую текстуру размытия прозрачности. Эта текстура рендерится во время прохода размытия прозрачности.
### Возвращаемое значение

Текущая текстура размытия прозрачности.
## Ptr < Texture > getTextureRefractionMask () const

Возвращает текущую текстуру маски [refraction](../../../principles/render/sequence/index.md#refraction_apply).
### Возвращаемое значение

Текущая текстура маски преломления.
## Ptr < Texture > getTextureRefraction () const

Возвращает текущую [refraction texture](../../../principles/render/sequence/index.md#refraction).
### Возвращаемое значение

Текущая текстура преломления.
## Ptr < Texture > getTextureAuxiliary () const

Возвращает текущую [auxiliary texture](../../../principles/render/sequence/index.md#auxiliary).
### Возвращаемое значение

Текущая вспомогательная текстура.
## Ptr < Texture > getTextureLinearDepth () const

Возвращает текущую текстуру, хранящую данные линейной глубины.
### Возвращаемое значение

Текущая текстура, хранящая данные линейной глубины.
## Ptr < Texture > getTextureOpacityDepth () const

Возвращает текущую [opacity depth texture](../../../principles/render/sequence/index.md#depth_pre_pass).
### Возвращаемое значение

Текущая текстура opacity depth.
## Ptr < Texture > getTextureCurrentDepth () const

Возвращает текущую [depth texture](../../../principles/render/sequence/index.md#depth).
### Возвращаемое значение

Текущая текстура глубины.
## Ptr < Texture > getTextureNormalUnpack () const

Возвращает текущую текстуру, хранящую распакованные нормали. Доступна для следующих постэффектов: SSR, SSGI, SSRTGI, Shadows screen space.
### Возвращаемое значение

Текущая текстура, хранящая распакованные нормали.
## Ptr < Texture > getTextureColorOldReprojection () const

Возвращает текущую [color old reprojection texture](../../../principles/render/sequence/index.md#linear_depth_for_ss).
### Возвращаемое значение

Текущая текстура color old reprojection.
## Ptr < Texture > getTextureColorOld () const

Возвращает текущую [color old texture](../../../principles/render/sequence/index.md#linear_depth_for_ss).
### Возвращаемое значение

Текущая текстура color old.
## Ptr < Texture > getTextureColorOpacity () const

Возвращает текущую текстуру color opacity.
### Возвращаемое значение

Текущая текстура color opacity.
## Ptr < Texture > getTextureColor () const

Возвращает текущую [color texture](../../../principles/render/sequence/index.md#opaque_deferred).
### Возвращаемое значение

Текущая текстура цвета.
## Ptr < RenderTarget > getPostRenderTarget () const

Возвращает текущий пост-[render target](../../../api/library/rendering/class.rendertarget_cpp.md).
### Возвращаемое значение

Текущий пост-рендер-таргет.
## Ptr < RenderTarget > getRenderTarget () const

Возвращает текущий [render target](../../../api/library/rendering/class.rendertarget_cpp.md).
### Возвращаемое значение

Текущий рендер-таргет.
## int getHeight () const

Возвращает текущую высоту экрана.
### Возвращаемое значение

Текущая высота экрана.
## int getWidth () const

Возвращает текущую ширину экрана.
### Возвращаемое значение

Текущая ширина экрана.
## Ptr < Light > getCurrentLight () const

Возвращает текущий рендерящийся источник света. Этот метод можно использовать для получения карт теней для определённого источника света в [event handler](../../../api/library/rendering/class.render_cpp.md#getEventBegin_Event) (см. событие [BeginShadows](../../../api/library/rendering/class.render_cpp.md#getEventBeginShadows_Event)).
### Возвращаемое значение

Текущий рендерящийся источник света.
## void setObliqueFrustum ( bool frustum )

Задаёт новое значение, указывающее, является ли пирамида видимости наклонной.
> **Notice:** Рекомендуется задавать наклонную пирамиду видимости с помощью этого метода, так как он не влияет на матрицу проекции. Для указания ближней плоскости отсечения используйте метод [setObliqueFrustumPlane()](#setObliqueFrustumPlane_Vec4_void).

### Аргументы

- *bool* **frustum** - **true**, чтобы включить наклонную пирамиду видимости; **false** - чтобы отключить её.

## bool isObliqueFrustum () const

Возвращает текущее значение, указывающее, является ли пирамида видимости наклонной.
> **Notice:** Рекомендуется задавать наклонную пирамиду видимости с помощью этого метода, так как он не влияет на матрицу проекции. Для указания ближней плоскости отсечения используйте метод [setObliqueFrustumPlane()](#setObliqueFrustumPlane_Vec4_void).

### Возвращаемое значение

**true**, если пирамида видимости наклонная; иначе **false**.
## float getZFar () const

Возвращает текущую дальнюю плоскость отсечения.
### Возвращаемое значение

Текущая дальняя плоскость отсечения.
## float getZNear () const

Возвращает текущую ближнюю плоскость отсечения.
### Возвращаемое значение

Текущая ближняя плоскость отсечения.
## Math:: Mat4 getIModelview () const

Возвращает текущую обратную матрицу вида.
### Возвращаемое значение

Текущая обратная матрица вида.
## Math:: mat4 getProjectionWithoutTAA () const

Возвращает текущую матрицу проекции без TAA.
### Возвращаемое значение

Текущая матрица проекции без TAA.
## Ptr < Viewport > getViewport () const

Возвращает текущий умный указатель на рендерящийся вьюпорт.
### Возвращаемое значение

Текущий умный указатель на рендерящийся вьюпорт.
## void setProjectionFullViewport ( const Math:: mat4 & viewport )

Задаёт новую матрицу проекции полного вьюпорта. В *[PSSM](../../../principles/render/lights_shadows/shadows/pssm.md)* полным вьюпортом является 0-й каскад; при VR foveated rendering - это контекстный вьюпорт. Эта матрица может использоваться для вычисления Screen Space Scaling объекта (например, *[ObjectParticles](../../../api/library/objects/class.objectparticles_cpp.md)*), обеспечивая сохранение согласованного размера между каскадами и контекстным/фокусным вьюпортами.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md)&* **viewport** - Матрица проекции, используемая для рендеринга полного вьюпорта.

## Math:: mat4 getProjectionFullViewport () const

Возвращает текущую матрицу проекции полного вьюпорта. В *[PSSM](../../../principles/render/lights_shadows/shadows/pssm.md)* полным вьюпортом является 0-й каскад; при VR foveated rendering - это контекстный вьюпорт. Эта матрица может использоваться для вычисления Screen Space Scaling объекта (например, *[ObjectParticles](../../../api/library/objects/class.objectparticles_cpp.md)*), обеспечивая сохранение согласованного размера между каскадами и контекстным/фокусным вьюпортами.
### Возвращаемое значение

Текущая матрица проекции, используемая для рендеринга полного вьюпорта.
## int getStereoMode () const

Возвращает текущий стереорежим.
### Возвращаемое значение

Текущий стереорежим. Одна из переменных [RENDER_STEREO_*](#RENDER_STEREO_VERTICAL).
## Renderer::RENDER_STEREO_EYE getStereoCurrentEye () const

Возвращает текущий стереоглаз.
### Возвращаемое значение

Текущий стереоглаз. Одна из переменных [RENDER_STEREO_EYE_*](#RENDER_STEREO_EYE).
## int getSkipFlags () const

Возвращает текущий [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_DYNAMIC_REFLECTIONS) для рендерящегося вьюпорта.
### Возвращаемое значение

Текущий [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_DYNAMIC_REFLECTIONS).
## int getReflectionViewportMask () const

Возвращает текущую маску вьюпорта отражений.
### Возвращаемое значение

Текущая маска вьюпорта отражений.
## int getViewportMask () const

Возвращает текущую маску вьюпорта.
### Возвращаемое значение

Текущая маска вьюпорта.
## bool isStereo () const

Возвращает текущее значение, указывающее, включён ли стереорендеринг.
### Возвращаемое значение

**true**, если стереорендеринг включён; иначе **false**.
## bool isShadow () const

Возвращает текущее значение, указывающее, рендерятся ли тени.
### Возвращаемое значение

**true**, если рендеринг теней включён; иначе **false**.
## bool isReflection () const

Возвращает текущее значение, указывающее, выполняется ли рендеринг отражений.
### Возвращаемое значение

**true**, если рендеринг отражений выполняется; иначе **false**.
## bool isNode () const

Возвращает текущее значение, указывающее, выполняется ли рендеринг узла.
### Возвращаемое значение

**true**, если рендеринг узла выполняется; иначе **false**.
## Renderer::CBufferScattering getShaderCBufferScattering () const

Возвращает текущий буфер, содержащий параметры рассеивания, передаваемые в пользовательский шейдер. Этот метод можно использовать в [event handler](../../../api/library/rendering/class.render_cpp.md#getEventBegin_Event) для получения параметров рассеивания на определённом этапе последовательности рендеринга и передачи их в пользовательский шейдер.
### Возвращаемое значение

Текущий буфер, содержащий параметры рассеивания, передаваемые в пользовательский шейдер.
## Renderer::CBufferCamera getShaderCBufferCamera () const

Возвращает текущий буфер, содержащий параметры камеры, передаваемые в пользовательский шейдер. Этот метод можно использовать в [event handler](../../../api/library/rendering/class.render_cpp.md#getEventBegin_Event) для получения параметров камеры на определённом этапе последовательности рендеринга и передачи их в пользовательский шейдер.
### Возвращаемое значение

Текущий буфер, содержащий параметры камеры, передаваемые в пользовательский шейдер.
## bool isStereoPeripheral () const

Возвращает текущее значение, указывающее, включён ли периферийный стереорендеринг.
### Возвращаемое значение

**true**, если периферийный стереорендеринг включён; иначе **false**.
## Renderer::CBufferTonemapper getShaderCBufferTonemapper () const

Возвращает текущий буфер, содержащий параметры тонмаппинга, передаваемые в пользовательский шейдер. Этот метод можно использовать в [event handler](../../../api/library/rendering/class.render_cpp.md#getEventBegin_Event) для получения параметров тонмаппинга на определённом этапе последовательности рендеринга и передачи их в пользовательский шейдер.
### Возвращаемое значение

Текущий буфер, содержащий параметры тонмаппинга, передаваемые в пользовательский шейдер.
## void setVR ( bool vr )

Задаёт новое значение, указывающее, включён ли режим рендеринга VR.
### Аргументы

- *bool* **vr** - **true**, чтобы включить режим рендеринга VR; **false** - чтобы отключить его.

## bool isVR () const

Возвращает текущее значение, указывающее, включён ли режим рендеринга VR.
### Возвращаемое значение

**true**, если режим рендеринга VR включён; иначе **false**.
---

## void clearStates ( )

Очищает состояния рендеринга и текстуры.
> **Notice:** Шейдер также будет очищен.


## void clearShader ( )

Очищает шейдер.
## void setBlendFunc ( Render::PASS pass , const Ptr < Material > & material ) const

Задаёт функцию блендинга света для заданного прохода рендеринга и материала.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одно из следующих значений:

  - [PASS_AMBIENT](../../../api/library/rendering/class.render_cpp.md#PASS_AMBIENT)
  - [PASS_LIGHT_OMNI](../../../api/library/rendering/class.render_cpp.md#PASS_LIGHT_OMNI)
  - [PASS_LIGHT_PROJ](../../../api/library/rendering/class.render_cpp.md#PASS_LIGHT_PROJ)
  - [PASS_LIGHT_WORLD](../../../api/library/rendering/class.render_cpp.md#PASS_LIGHT_WORLD)
  - [PASS_EMISSION](../../../api/library/rendering/class.render_cpp.md#PASS_EMISSION)
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.

## void setBufferMask ( Render::PASS pass , const Ptr < Material > & material ) const

Задаёт маску буфера для заданного прохода рендеринга и материала.
> **Notice:** Если материал не использует маску глубины и указан [ambient pass](../../../api/library/rendering/class.render_cpp.md#PASS_AMBIENT), будет установлена маска [BUFFER_COLOR](../../../api/library/rendering/class.renderstate_cpp.md#BUFFER_COLOR); в противном случае будет установлена маска [BUFFER_ALL](../../../api/library/rendering/class.renderstate_cpp.md#BUFFER_ALL).


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одно из следующих значений:

  - [PASS_DEFERRED](../../../api/library/rendering/class.render_cpp.md#PASS_DEFERRED)
  - [PASS_AMBIENT](../../../api/library/rendering/class.render_cpp.md#PASS_AMBIENT)
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.

## void setCameraPosition ( const Math:: Vec3 & position )

Задаёт новую позицию камеры.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Новая позиция камеры.

## Math:: Vec3 getCameraPosition ( ) const

Возвращает текущую позицию камеры.
### Возвращаемое значение

Текущая позиция камеры.
## void setDepthFunc ( Render::PASS pass , const Ptr < Material > & material ) const

Задаёт функцию глубины для заданного прохода рендеринга и материала.
> **Notice:** Если у материала включена опция *depth_test*, будет использоваться функция [DEPTH_GEQUAL](../../../api/library/rendering/class.renderstate_cpp.md#DEPTH_GEQUAL); в противном случае функция сравнения глубины будет отключена.


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME), кроме следующих: PASS_DEFERRED, PASS_SHADOW, PASS_DEPTH_PRE_PASS, PASS_EMISSION.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.

## bool hasGeodeticPivot ( )

Возвращает значение, указывающее, имеет ли рендерящаяся сцена GeodeticPivot.
### Возвращаемое значение

true, если рендерящаяся сцена имеет GeodeticPivot; иначе false.
## Math:: Mat4 getIModelview ( ) const

Возвращает текущую обратную матрицу вида.
### Возвращаемое значение

Возвращает текущую обратную матрицу вида.
## void setMaterial ( Render::PASS pass , const Ptr < Material > & material )

Задаёт материал и инициализирует все текстуры материала для указанного прохода рендеринга.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.

## void setModelview ( const Math:: Mat4 & modelview )

Задаёт текущую матрицу вида.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **modelview** - Новая матрица вида.

## Math:: Mat4 getModelview ( ) const

Возвращает текущую матрицу вида.
### Возвращаемое значение

Возвращает текущую матрицу вида.
## bool isNode ( ) const

Возвращает значение, указывающее, выполняется ли рендеринг узла.
### Возвращаемое значение

true, если рендеринг узла выполняется, иначе false.
## Vector < Ptr < Object >> getObjects ( )

Получает список всех объектов рендерящейся сцены и помещает его в буфер.
### Возвращаемое значение

Буфер, содержащий все объекты сцены.
## void setObliqueFrustumPlane ( const Math:: Vec4 & plane )

Задаёт наклонную ближнюю плоскость отсечения пирамиды видимости.
> **Notice:** Этот метод не влияет на матрицу проекции. Для включения наклонной пирамиды видимости используйте метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


### Аргументы

- *const  Math::[Vec4](../../../api/library/math/class.vec4_cpp.md) &* **plane** - Мировые координаты наклонной ближней плоскости отсечения (Nx, Ny, Nz, D), где Nx, Ny, Nz - координаты нормали плоскости, D - расстояние от начала координат до плоскости.

## Math:: Vec4 getObliqueFrustumPlane ( ) const

Возвращает наклонную ближнюю плоскость отсечения пирамиды видимости.
### Возвращаемое значение

Мировые координаты наклонной ближней плоскости отсечения (Nx, Ny, Nz, D), где Nx, Ny, Nz - координаты нормали плоскости, D - расстояние от начала координат до плоскости.
## void setOldModelview ( const Math:: Mat4 & modelview )

Обновляет старую матрицу вида.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **modelview** - Старая матрица вида.

## Math:: Mat4 getOldModelview ( ) const

Возвращает старую матрицу вида.
### Возвращаемое значение

Старая матрица вида.
## void setOldProjection ( const Math:: mat4 & projection )

Обновляет старую матрицу проекции.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **projection** - Старая матрица проекции.

## Math:: mat4 getOldProjection ( ) const

Возвращает старую матрицу проекции.
### Возвращаемое значение

Старая матрица проекции.
## void setPolygonCull ( Render::PASS pass , const Ptr < Material > & material ) const

Задаёт режим отсечения полигонов для заданного прохода рендеринга и материала.
> **Notice:** Если материал односторонний, полигоны, обращённые назад, будут отсечены; в противном случае отсечение полигонов для материала будет отключено.


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [RENDER_PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.

## Math:: mat4 getProjectionWithoutTAA ( ) const

Возвращает текущую матрицу проекции без TAA.
### Возвращаемое значение

Матрица проекции без TAA.
## void setProjection ( const Math:: mat4 & projection )

Обновляет текущую матрицу проекции.
> **Notice:** Не рекомендуется использовать этот метод для задания наклона ближней плоскости отсечения пирамиды видимости, так как в этом случае ряд функций (таких как облака, тени, TAA, ряд оптимизаций движка и т.д.) будут работать некорректно. Используйте вместо этого метод [setObliqueFrustum()](#setObliqueFrustum_int_void).


### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **projection** - Матрица проекции, которую нужно задать.

## Math:: mat4 getProjection ( ) const

Возвращает текущую матрицу проекции.
### Возвращаемое значение

Текущая матрица проекции.
## bool isReflection ( ) const

Возвращает значение, указывающее, выполняется ли рендеринг отражений.
### Возвращаемое значение

true, если рендеринг отражений выполняется, иначе false.
## int getReflectionViewportMask ( ) const

Возвращает текущую маску вьюпорта отражений.
### Возвращаемое значение

Текущая маска вьюпорта отражений.
## void setShaderParameters ( Render::PASS pass , const Ptr < Shader > & shader , bool is_screen_space = 0 )

Задаёт параметры указанного шейдера для заданного прохода рендеринга.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shader](../../../api/library/rendering/class.shader_cpp.md)> &* **shader** - Умный указатель на шейдер.
- *bool* **is_screen_space** - Флаг экранного пространства: **1**, чтобы задать параметры для экранного эффекта; иначе 0.

## void setShaderParameters ( Render::PASS pass , const Ptr < Shader > & shader , const Ptr < Material > & material , bool is_screen_space = 0 )

Задаёт параметры указанного шейдера для заданного прохода рендеринга и материала.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shader](../../../api/library/rendering/class.shader_cpp.md)> &* **shader** - Умный указатель на шейдер.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.
- *bool* **is_screen_space** - Флаг экранного пространства: **1**, чтобы задать параметры для экранного эффекта; иначе 0.

## void setShaderParameters ( Render::PASS pass , const Ptr < Shader > & shader , const Ptr < Material > & material , const Ptr < Object > & object , int surface , bool is_screen_space = 0 )

Задаёт параметры указанного шейдера для заданного прохода рендеринга, материала, объекта и поверхности.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Shader](../../../api/library/rendering/class.shader_cpp.md)> &* **shader** - Умный указатель на шейдер.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Умный указатель на объект.
- *int* **surface** - Номер поверхности.
- *bool* **is_screen_space** - Флаг экранного пространства: **1**, чтобы задать параметры для экранного эффекта; иначе 0.

## void setShaderParameters ( Render::PASS pass , const Ptr < Material > & material , bool is_screen_space = 0 )

Задаёт параметры шейдера для заданного прохода рендеринга и материала.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Умный указатель на материал.
- *bool* **is_screen_space** - Флаг экранного пространства: **1**, чтобы задать параметры для экранного эффекта; иначе 0.

## void setShaderParameters ( Render::PASS pass , const Ptr < Object > & object , int surface , bool is_screen_space = 0 )

Задаёт параметры шейдера для заданного прохода рендеринга, объекта и поверхности.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Проход рендеринга. Одна из переменных [PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Object](../../../api/library/objects/class.object_cpp.md)> &* **object** - Умный указатель на объект.
- *int* **surface** - Номер поверхности.
- *bool* **is_screen_space** - Флаг экранного пространства: **1**, чтобы задать параметры для экранного эффекта; иначе 0.

## bool isShadow ( ) const

Возвращает значение, указывающее, рендерятся ли тени.
### Возвращаемое значение

true, если тени рендерятся; иначе false.
## int checkSkipFlags ( int flags ) const

Возвращает значение, указывающее, установлен ли заданный [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_DYNAMIC_REFLECTIONS).
### Аргументы

- *int* **flags** - [Skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_DYNAMIC_REFLECTIONS).

### Возвращаемое значение

true, если заданный [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_DYNAMIC_REFLECTIONS) установлен; иначе false.
## int getSkipFlags ( ) const

Возвращает [skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_DYNAMIC_REFLECTIONS), установленный для рендерящегося вьюпорта.
### Возвращаемое значение

[Skip flag](../../../api/library/rendering/class.viewport_cpp.md#SKIP_DYNAMIC_REFLECTIONS).
## bool isStereo ( ) const

Возвращает значение, указывающее, включён ли стереорендеринг.
### Возвращаемое значение

true, если стереорендеринг включён; иначе false.
## int getStereoMode ( ) const

Возвращает текущий стереорежим.
### Возвращаемое значение

Одна из переменных [RENDER_STEREO_*](#RENDER_STEREO_VERTICAL).
## Renderer::RENDER_STEREO_EYE getStereoCurrentEye ( ) const

Возвращает текущий стереоглаз.
### Возвращаемое значение

Одна из переменных [RENDER_STEREO_EYE_*](#RENDER_STEREO_EYE).
## Ptr < Texture > getTextureAutoExposure ( ) const

Возвращает текстуру автоэкспозиции.
### Возвращаемое значение

Текстура автоэкспозиции.
## Ptr < Texture > getTextureAuxiliary ( ) const

Возвращает [auxiliary texture](../../../principles/render/sequence/index.md#auxiliary).
### Возвращаемое значение

Вспомогательная текстура.
## Ptr < Texture > getTextureBentNormal ( ) const

Возвращает текстуру bent normal. Эта текстура используется на [Screen-Space Global Illumination stage](../../../principles/render/sequence/index.md#ssgi).
### Возвращаемое значение

Текстура bent normal.
## Ptr < Texture > getTextureClouds ( ) const

Возвращает текстуру облаков. Эта текстура рендерится во время отдельного прохода облаков.
### Возвращаемое значение

Текстура облаков.
## Ptr < Texture > getTextureColor ( ) const

Возвращает [color texture](../../../principles/render/sequence/index.md#opaque_deferred).
### Возвращаемое значение

Текстура цвета.
## Ptr < Texture > getTextureColorOld ( ) const

Возвращает [color old texture](../../../principles/render/sequence/index.md#linear_depth_for_ss).
### Возвращаемое значение

Текстура color old.
## Ptr < Texture > getTextureColorOldReprojection ( ) const

Возвращает [color old reprojection texture](../../../principles/render/sequence/index.md#linear_depth_for_ss).
### Возвращаемое значение

Текстура color old reprojection.
## Ptr < Texture > getTextureColorOpacity ( ) const

Возвращает текстуру color opacity.
### Возвращаемое значение

Текстура color opacity.
## Ptr < Texture > getTextureCurrentDepth ( ) const

Возвращает [current depth texture](../../../principles/render/sequence/index.md#depth).
### Возвращаемое значение

Текущая текстура глубины.
## Ptr < Texture > getTextureDOFMask ( ) const

Возвращает текстуру маски DoF. Эта текстура используется на [camera effects stage](../../../principles/render/sequence/index.md#dof).
### Возвращаемое значение

Текстура маски DoF
## Ptr < Texture > getTextureGBufferFeatures ( ) const

Возвращает текстуру, хранящую интенсивность [screen-space bevel effect](../../../api/library/rendering/class.render_cpp.md#setSSBevel_int_void).
### Возвращаемое значение

Текстура, хранящая интенсивность фасок. Текстура имеет формат **RGBA8**, значение интенсивности записывается в канал **R**.
## Ptr < Texture > getTextureGBufferAlbedo ( ) const

Возвращает [Gbuffer albedo texture](../../../principles/render/sequence/index.md#albedo).
### Возвращаемое значение

Текстура альбедо Gbuffer.
## Ptr < Texture > getTextureGBufferMaterialMask ( ) const

Возвращает [Gbuffer material mask texture](../../../principles/render/sequence/index.md#material_mask).
### Возвращаемое значение

Текстура маски материала Gbuffer.
## Ptr < Texture > getTextureGBufferNormal ( ) const

Возвращает [Gbuffer normal texture](../../../principles/render/sequence/index.md#normal).
### Возвращаемое значение

Текстура нормалей Gbuffer.
## Ptr < Texture > getTextureGBufferShading ( ) const

Возвращает [Gbuffer shading texture](../../../principles/render/sequence/index.md#shading).
### Возвращаемое значение

Текстура шейдинга Gbuffer.
## Ptr < Texture > getTextureGBufferVelocity ( ) const

Возвращает [Gbuffer velocity texture](../../../principles/render/sequence/index.md#velocity).
### Возвращаемое значение

Текстура скорости Gbuffer.
## Ptr < Texture > getTextureDirectLights ( ) const

Возвращает массивную текстуру, хранящую содержимое [deferred light buffer](../../../principles/render/sequence/index.md#lights). Текстура содержит два слоя формата **RG11B10F**: первый слой хранит рассеянный свет, а второй - зеркальный свет.
### Возвращаемое значение

Текстура, хранящая содержимое буфера отложенного освещения.
## Ptr < Texture > getTextureIndirectLights ( ) const

Возвращает массивную текстуру, хранящую содержимое [deferred reflections buffer](../../../principles/render/sequence/index.md#deferred_reflection). Текстура содержит два слоя формата **RG11B10F**: первый слой хранит цвет отражения окружения, а второй - фоновое освещение окружения.
### Возвращаемое значение

Текстура, хранящая содержимое буфера отложенных отражений.
## Ptr < Texture > getTextureOpacityDepth ( ) const

Возвращает [opacity depth texture](../../../principles/render/sequence/index.md#depth_pre_pass).
### Возвращаемое значение

Текстура opacity depth.
## Ptr < Texture > getTextureRefraction ( ) const

Возвращает [refraction texture](../../../principles/render/sequence/index.md#refraction).
### Возвращаемое значение

Текстура преломления.
## Ptr < Texture > getTextureSSR ( ) const

Возвращает [SSR texture](../../../principles/render/sequence/index.md#ssr).
### Возвращаемое значение

Текстура SSR.
## Ptr < Texture > getTextureSSAO ( ) const

Возвращает [SSAO texture](../../../principles/render/sequence/index.md#ssao).
### Возвращаемое значение

Текстура SSAO.
## Ptr < Texture > getTextureSSGI ( ) const

Возвращает [SSGI texture](../../../principles/render/sequence/index.md#ssgi).
### Возвращаемое значение

Текстура SSGI.
## Ptr < Texture > getTextureSSShadowShafts ( ) const

Возвращает текстуру Screen-Space Shadow Shafts.
### Возвращаемое значение

Текстура Screen-Space Shadow Shafts.
## Ptr < Texture > getTextureTransparentBlur ( ) const

Возвращает текстуру размытия прозрачности. Эта текстура рендерится во время прохода размытия прозрачности.
### Возвращаемое значение

Текстура размытия прозрачности.
## Ptr < RenderTarget > getRenderTarget ( ) const

Возвращает [render target](../../../api/library/rendering/class.rendertarget_cpp.md).
### Возвращаемое значение

Рендер-таргет.
## Ptr < RenderTarget > getPostRenderTarget ( ) const

Возвращает пост-[render target](../../../api/library/rendering/class.rendertarget_cpp.md).
### Возвращаемое значение

Пост-рендер-таргет.
## Ptr < Viewport > getViewport ( ) const

Возвращает рендерящийся вьюпорт.
### Возвращаемое значение

Умный указатель на рендерящийся вьюпорт.
## int getViewportMask ( ) const

Возвращает текущую маску вьюпорта.
### Возвращаемое значение

Возвращает текущую маску вьюпорта.
## float getZFar ( ) const

Возвращает текущую дальнюю плоскость отсечения.
### Возвращаемое значение

Возвращает текущую дальнюю плоскость отсечения.
## float getZNear ( ) const

Возвращает текущую ближнюю плоскость отсечения.
### Возвращаемое значение

Возвращает текущую ближнюю плоскость отсечения.
## void saveState ( )

Сохраняет текущие матрицы рендерера.
## void restoreState ( )

Восстанавливает текущие матрицы рендерера.
## bool useDynamicReflections ( ) const

Возвращает значение, указывающее, включён ли рендеринг динамических отражений.
### Возвращаемое значение

true, если рендеринг динамических отражений включён; иначе false.
## bool useOcclusionQueries ( ) const

Возвращает значение, указывающее, включён ли тест occlusion query.
### Возвращаемое значение

true, если тест occlusion query включён; иначе false.
## bool usePostEffects ( ) const

Возвращает значение, указывающее, включён ли рендеринг постэффектов.
### Возвращаемое значение

true, если рендеринг постэффектов включён; иначе false.
## bool useShadows ( ) const

Возвращает значение, указывающее, включён ли рендеринг теней.
### Возвращаемое значение

true, если рендеринг теней включён; иначе false.
## bool useTAA ( ) const

Возвращает значение, указывающее, включено ли Temporal Anti-Aliasing (TAA).
### Возвращаемое значение

true, если Temporal Anti-Aliasing (TAA) включено; иначе false.
## void setUseTAAOffset ( bool offset )

Задаёт значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного вычисления TAA, когда режим рендеринга для *Viewport* установлен в [RENDER_DEPTH](../../../api/library/rendering/class.viewport_cpp.md#RENDER_DEPTH).
### Аргументы

- *bool* **offset** - true, чтобы включить пропуск проверки режима рендеринга и использовать TAA; иначе false.

## bool isUseTAAOffset ( ) const

Возвращает значение, указывающее, включён ли пропуск проверки режима рендеринга для использования TAA. Может использоваться для обеспечения корректного вычисления TAA, когда режим рендеринга для *Viewport* установлен в [RENDER_DEPTH](../../../api/library/rendering/class.viewport_cpp.md#RENDER_DEPTH).
### Возвращаемое значение

true, если пропуск проверки режима рендеринга для использования TAA включён; иначе false.
## bool useVelocityBuffer ( ) const

Возвращает значение, указывающее, включён ли рендеринг в буфер скорости.
### Возвращаемое значение

true, если рендеринг в буфер скорости включён; иначе false.
## bool useVisualizer ( ) const

Возвращает значение, указывающее, включён ли рендеринг визуализатора.
### Возвращаемое значение

true, если рендеринг визуализатора включён; иначе false.
## Ptr < Texture > getTextureSSCurvature ( ) const

Возвращает текстуру, используемую эффектом [Screen-Space Dirt (SSDirt)](../../../editor2/settings/render_settings/ssdirt/index.md).
### Возвращаемое значение

Текстура кривизны, используемая эффектом [Screen-Space Dirt (SSDirt)](../../../editor2/settings/render_settings/ssdirt/index.md).
## Ptr < Texture > getTextureAutoWhiteBalance ( ) const

Возвращает [auto white balance texture](../../../editor2/settings/render_settings/camera_effects/index.md#white_balance).
### Возвращаемое значение

Текстура автоматического баланса белого.
## Ptr < Texture > getTextureRefractionMask ( ) const

Возвращает текстуру маски [refraction](../../../principles/render/sequence/index.md#refraction_apply).
### Возвращаемое значение

Текстура маски преломления.
## Ptr < Texture > createCustomTexture3D ( const char * name , int width , int height , int depth , int format , int flags = 0 )

Создаёт пользовательскую 3D-текстуру. Такие текстуры можно использовать в ваших материалах.
В вашем [base material](../../../content/materials/index.md#base_materials):

```xml
<!-- ... -->
<texture type="texture_name"/>
<!-- ... -->

```


Создайте соответствующую пользовательскую текстуру с помощью кода:

```cpp
// ...
 // creating a custom texture
 Renderer::createCustomTexture3D("texture_name", 512, 512, 512, Texture::FORMAT_RGBA8);

```


### Аргументы

- *const char ** **name** - Имя текстуры.
- *int* **width** - Ширина текстуры, в пикселях.
- *int* **height** - Высота текстуры, в пикселях.
- *int* **depth** - Глубина текстуры, в пикселях.
- *int* **format** - Формат текстуры, одно из значений [Texture::FORMAT_](../../../api/library/rendering/class.texture_cpp.md#FORMAT_ATI1).
- *int* **flags** - Флаги текстуры. Комбинация флагов (таких как [Texture::FORMAT_USAGE_](../../../api/library/rendering/class.texture_cpp.md#FORMAT_USAGE_DYNAMIC), [Texture::SAMPLER_WRAP_](../../../api/library/rendering/class.texture_cpp.md#SAMPLER_WRAP_BORDER) и т.д.)

### Возвращаемое значение

Новая созданная пользовательская 3D-текстура.
## Ptr < Texture > createCustomTexture2D ( const char * name , int width , int height , int format , int flags = 0 )

Создаёт пользовательский массив 2D-текстур. Такую текстуру можно использовать в ваших материалах.
В вашем [base material](../../../content/materials/index.md#base_materials):

```xml
<!-- ... -->
<texture type="texture_name"/>
<!-- ... -->

```


Создайте соответствующую пользовательскую текстуру с помощью кода:

```cpp
// ...
 // creating a custom texture
 Renderer::createCustomTexture2D("texture_name", 512, 512, Texture::FORMAT_RGBA8);

```


### Аргументы

- *const char ** **name** - Имя текстуры.
- *int* **width** - Ширина текстуры, в пикселях.
- *int* **height** - Высота текстуры, в пикселях.
- *int* **format** - Формат текстуры, одно из значений [Texture::FORMAT_](../../../api/library/rendering/class.texture_cpp.md#FORMAT_ATI1).
- *int* **flags** - Флаги текстуры. Комбинация флагов (таких как [Texture::FORMAT_USAGE_](../../../api/library/rendering/class.texture_cpp.md#FORMAT_USAGE_DYNAMIC), [Texture::SAMPLER_WRAP_](../../../api/library/rendering/class.texture_cpp.md#SAMPLER_WRAP_BORDER) и т.д.)

### Возвращаемое значение

Новая созданная пользовательская 2D-текстура.
## Ptr < Texture > createCustomTexture2DArray ( const char * name , int width , int height , int depth , int format , int flags = 0 )

Создаёт пользовательский массив 2D-текстур. Такую текстуру можно использовать в ваших материалах.
```xml
<!-- ... -->
<texture type="texture_name"/>
<!-- ... -->

```


Создайте соответствующую пользовательскую текстуру с помощью кода:

```cpp
// ...
 // creating a custom texture
 Renderer::createCustomTexture2DArray("texture_name", 512, 512, 16, Texture::FORMAT_RGBA8);

```


### Аргументы

- *const char ** **name** - Имя текстуры.
- *int* **width** - Ширина текстуры, в пикселях.
- *int* **height** - Высота текстуры, в пикселях.
- *int* **depth** - Количество элементов в массиве.
- *int* **format** - Формат текстуры, одно из значений [Texture::FORMAT_](../../../api/library/rendering/class.texture_cpp.md#FORMAT_ATI1).
- *int* **flags** - Флаги текстуры. Комбинация флагов (таких как [Texture::FORMAT_USAGE_](../../../api/library/rendering/class.texture_cpp.md#FORMAT_USAGE_DYNAMIC), [Texture::SAMPLER_WRAP_](../../../api/library/rendering/class.texture_cpp.md#SAMPLER_WRAP_BORDER) и т.д.)

### Возвращаемое значение

Новый созданный пользовательский массив 2D-текстур.
## Ptr < Texture > getCustomTexture ( const char * name )

Возвращает пользовательскую текстуру по её имени. Пользовательские текстуры можно создать с помощью методов [*createCustomTexture3D()*](#createCustomTexture3D_cstr_int_int_int_int_int_Texture), [*createCustomTexture3D()*](#createCustomTexture3D_cstr_int_int_int_int_int_Texture) и [*createCustomTexture3D()*](#createCustomTexture3D_cstr_int_int_int_int_int_Texture).
### Аргументы

- *const char ** **name** - Имя пользовательской текстуры.

### Возвращаемое значение

Пользовательская текстура, соответствующая указанному имени, если она существует, иначе nullptr.
## Renderer::CBufferCamera getShaderCBufferCamera ( ) const

Возвращает буфер, содержащий параметры камеры, передаваемые в пользовательский шейдер. Этот метод можно использовать в [event handler](../../../api/library/rendering/class.render_cpp.md#getEventBegin_Event) для получения параметров камеры на определённом этапе последовательности рендеринга и передачи их в пользовательский шейдер.
### Возвращаемое значение

Буфер, содержащий параметры камеры, передаваемые в пользовательский шейдер.
## Renderer::CBufferScattering getShaderCBufferScattering ( ) const

Возвращает буфер, содержащий параметры рассеивания, передаваемые в пользовательский шейдер. Этот метод можно использовать в [event handler](../../../api/library/rendering/class.render_cpp.md#getEventBegin_Event) для получения параметров рассеивания на определённом этапе последовательности рендеринга и передачи их в пользовательский шейдер.
### Возвращаемое значение

Буфер, содержащий параметры рассеивания, передаваемые в пользовательский шейдер.
## Ptr < Light > getCurrentLight ( ) const

Возвращает текущий рендерящийся источник света. Этот метод можно использовать для получения карт теней для определённого источника света в [event handler](../../../api/library/rendering/class.render_cpp.md#getEventBegin_Event) (см. событие [BeginShadows](../../../api/library/rendering/class.render_cpp.md#getEventBeginShadows_Event)).
### Возвращаемое значение

Текущий рендерящийся источник света.
## void setOverlapEnvironmentTexture ( const Ptr < Texture > & texture )

Задаёт новую кубическую текстуру окружения.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Кубическая текстура окружения, которую нужно использовать.

## Ptr < Texture > getOverlapEnvironmentTexture ( ) const

Возвращает текущую используемую кубическую текстуру окружения.
### Возвращаемое значение

Текущая используемая кубическая текстура окружения.
## void resetOverlapEnvironmentTexture ( )

Сбрасывает кубическую текстуру окружения на значение по умолчанию (текстура окружения не используется).
## Ptr < Texture > getTextureNormalUnpack ( ) const

Возвращает текстуру, хранящую распакованные нормали. Доступна для следующих постэффектов: SSR, SSGI, SSRTGI, Shadows screen space.
### Возвращаемое значение

Текстура, хранящая распакованные нормали.
## Ptr < Texture > getTextureLinearDepth ( ) const

Возвращает текстуру, хранящую данные линейной глубины.
### Возвращаемое значение

Текстура, хранящая данные линейной глубины.
## void renderMesh ( const Ptr < MeshRender > & mesh , const Ptr < Material > & material , const char * pass_name , const Math:: Mat4 & transform , const Ptr < Camera > & camera )

Рендерит указанный [render mesh](../../../api/library/rendering/class.meshrender_cpp.md) с применённым к нему указанным материалом во время указанного прохода рендеринга, как видно с указанной камеры.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)> &* **mesh** - Render mesh для рендеринга.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Материал, используемый для рендеринга меша.
- *const char ** **pass_name** - Имя прохода рендеринга, во время которого рендерится меш.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Трансформация, передаваемая в шейдер для рендеринга.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)> &* **camera** - Камера, используемая для рендеринга меша.

## bool isStereoPeripheral ( ) const

Возвращает значение, указывающее, включён ли режим рендеринга Stereo Peripheral. Этот режим рендеринга используется для HMD-устройств, имеющих контекстный (низкого разрешения) и фокусный (высокого разрешения) дисплеи.
### Возвращаемое значение

true, если периферийный стереорендеринг включён; иначе false.
## bool useUpscale ( ) const

Возвращает значение, указывающее, включён ли апскейлинг. Это технология, используемая для рендеринга изображений высокого разрешения на основе источника более низкого разрешения.
### Возвращаемое значение

true, если апскейлинг (*DLSS или FSR*) используется, и финальное изображение рендерится с постобработкой; иначе false.
## bool useDepthPrePass ( ) const

Возвращает значение, указывающее, включён ли *[depth pre-pass](../../../principles/render/sequence/index.md#depth_pre_pass)*. В этом предварительном проходе GPU выполняет тест глубины для отсечения поверхностей.
### Возвращаемое значение

true, если depth pre-pass используется; иначе false.
