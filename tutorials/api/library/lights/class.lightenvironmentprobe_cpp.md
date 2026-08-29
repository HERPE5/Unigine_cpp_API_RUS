# Unigine::LightEnvironmentProbe Class (CPP)

**Header:** #include <UnigineLights.h>

**Inherits from:** Light


Этот класс позволяет создавать Environment Probe и управлять ими — см. [Environment Probes](../../../objects/lights/envprobe/index.md).


## LightEnvironmentProbe Class

### Перечисления

## GRAB_DYNAMIC_FACES_PER_FRAME

| Имя | Описание |
|---|---|
| **GRAB_DYNAMIC_FACES_PER_FRAME_MODE_1** = 0 | Обновлять только одну грань каждый кадр. |
| **GRAB_DYNAMIC_FACES_PER_FRAME_MODE_2** = 1 | Обновлять две грани каждый кадр. |
| **GRAB_DYNAMIC_FACES_PER_FRAME_MODE_3** = 2 | Обновлять три грани каждый кадр. |
| **GRAB_DYNAMIC_FACES_PER_FRAME_MODE_4** = 3 | Обновлять четыре грани каждый кадр. |
| **GRAB_DYNAMIC_FACES_PER_FRAME_MODE_5** = 4 | Обновлять пять граней каждый кадр. |
| **GRAB_DYNAMIC_FACES_PER_FRAME_MODE_6** = 5 | Обновлять все шесть граней каждый кадр. |

## GRAB_SUPERSAMPLING

| Имя | Описание |
|---|---|
| **GRAB_SUPERSAMPLING_MODE_1** = 0 | Один сэмпл на пиксель. |
| **GRAB_SUPERSAMPLING_MODE_2** = 1 | Два сэмпла на пиксель. |
| **GRAB_SUPERSAMPLING_MODE_4** = 2 | Четыре сэмпла на пиксель. |
| **GRAB_SUPERSAMPLING_MODE_8** = 3 | Восемь сэмплов на пиксель. |

## GRAB_RESOLUTION

| Имя | Описание |
|---|---|
| **GRAB_RESOLUTION_MODE_32** = 0 | Разрешение текстуры 32 пикселя. |
| **GRAB_RESOLUTION_MODE_64** = 1 | Разрешение текстуры 64 пикселя. |
| **GRAB_RESOLUTION_MODE_128** = 2 | Разрешение текстуры 128 пикселей. |
| **GRAB_RESOLUTION_MODE_256** = 3 | Разрешение текстуры 256 пикселей. |
| **GRAB_RESOLUTION_MODE_512** = 4 | Разрешение текстуры 512 пикселей. |
| **GRAB_RESOLUTION_MODE_1024** = 5 | Разрешение текстуры 1024 пикселя. |
| **GRAB_RESOLUTION_MODE_2048** = 6 | Разрешение текстуры 2048 пикселей. |
| **GRAB_RESOLUTION_MODE_4096** = 7 | Разрешение текстуры 4096 пикселей. |

## GRAB_MODE

| Имя | Описание |
|---|---|
| **GRAB_MODE_BAKED** = 0 | Отражения статические (кубическая карта заранее запечена). |
| **GRAB_MODE_DYNAMIC** = 1 | Отражения обновляются в реальном времени (кубическая карта генерируется динамически). |

## SPECULAR_BRDF_MODE

| Имя | Описание |
|---|---|
| **SPECULAR_BRDF_MODE_BLINN** = 0 | Модель отражения Blinn-Phong. |
| **SPECULAR_BRDF_MODE_GGX** = 1 | Модель распределения света GGX. |

## PROJECTION_MODE

| Имя | Описание |
|---|---|
| **PROJECTION_MODE_SPHERE** = 0 | Сферическая форма проекции. |
| **PROJECTION_MODE_BOX** = 1 | Кубическая форма проекции. |
| **PROJECTION_MODE_RAYMARCHING** = 2 | Режим raymarching, используемый для расчёта отражений от окружающих поверхностей. |

## LAST_STEP_MODE

| Имя | Описание |
|---|---|
| **LAST_STEP_MODE_ENVIRONMENT_PROBE** = 0 | Кубическая карта, используемая для последнего шага, совпадает с картой для всех предыдущих шагов. |
| **LAST_STEP_MODE_ONLY_SKY** = 1 | Кубическая карта содержит только небо и облака. |

## SECONDARY_BOUNCE_PROJECTION_MODE

| Имя | Описание |
|---|---|
| **SECONDARY_BOUNCE_PROJECTION_MODE_SPHERE** = 0 | Сферическая проекция. |
| **SECONDARY_BOUNCE_PROJECTION_MODE_RAYMARCHING** = 1 | Raymarching. |

### Методы класса

## void setGrabMode ( LightEnvironmentProbe::GRAB_MODE mode )

Задаёт новый режим, используемый для захвата света и отражений для *Environment Probe*.
### Аргументы

- *[LightEnvironmentProbe::GRAB_MODE](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#GRAB_MODE)* **mode** - Режим захвата, устанавливаемый для *Environment Probe*. Одно из значений *GRAB_MODE*.

## LightEnvironmentProbe::GRAB_MODE getGrabMode () const

Возвращает текущий режим, используемый для захвата света и отражений для *Environment Probe*.
### Возвращаемое значение

Текущий режим захвата, устанавливаемый для *Environment Probe*. Одно из значений *GRAB_MODE*.
## void setTextureFilePath ( const char * path )

Задаёт новый путь к файлу кубической текстуры отражений, используемому для *Environment Probe*.
### Аргументы

- *const char ** **path** - Путь к файлу кубической текстуры.

## String getTextureFilePath () const

Возвращает текущий путь к файлу кубической текстуры отражений, используемому для *Environment Probe*.
### Возвращаемое значение

Текущий путь к файлу кубической текстуры.
## void setAmbientContrast ( float contrast = 1.0f )

Задаёт новое значение контраста ambient-освещения (Indirect Diffuse) для *Environment Probe*.
### Аргументы

- *float* **contrast** - Значение контраста ambient-освещения в диапазоне [0.0f, 1.0f].

## float getAmbientContrast () const

Возвращает текущее значение контраста ambient-освещения (Indirect Diffuse) для *Environment Probe*.
### Возвращаемое значение

Текущее значение контраста ambient-освещения в диапазоне [0.0f, 1.0f].
## void setAmbientEnabled ( bool enabled )

Задаёт новое значение, указывающее, включено ли ambient-освещение (Indirect Diffuse) для *Environment Probe*.
### Аргументы

- *bool* **enabled** - Значение **true** включает ambient-освещение (Indirect Diffuse) для *Environment Probe*; **false** - отключает его.

## bool isAmbientEnabled () const

Возвращает текущее значение, указывающее, включено ли ambient-освещение (Indirect Diffuse) для *Environment Probe*.
### Возвращаемое значение

**true**, если ambient-освещение (Indirect Diffuse) для *Environment Probe* включено; иначе **false**.
## void setSpecularEnabled ( bool enabled )

Задаёт новое значение, указывающее, включены ли зеркальные отражения для *Environment Probe*.
### Аргументы

- *bool* **enabled** - Значение **true** включает зеркальные отражения для *Environment Probe*; **false** - отключает их.

## bool isSpecularEnabled () const

Возвращает текущее значение, указывающее, включены ли зеркальные отражения для *Environment Probe*.
### Возвращаемое значение

**true**, если зеркальные отражения для *Environment Probe* включены; иначе **false**.
## void setSphereReflectionParallax ( float parallax )

Задаёт новое значение коррекции параллакса для кубических карт отражений, проецируемых *Environment Probe*. При минимальном значении 0 кубические карты отражений просто проецируются на объекты и не следуют за перспективой наблюдателя. Это приводит к нереалистичным отражениям на большинстве поверхностей. Коррекция параллакса позволяет учитывать позицию камеры.
> **Notice:** Коррекция параллакса недоступна для отражений на прозрачных объектах.


### Аргументы

- *float* **parallax** - Значение коррекции параллакса, устанавливаемое для кубических карт отражений, проецируемых *Environment Probe*, в диапазоне **[0;1]**:

  - При минимальном значении 0 коррекция параллакса отключена (отражения будут выглядеть так, будто объекты находятся на бесконечном расстоянии).
  - При максимальном значении 1 коррекция параллакса включена (отражения будут выглядеть так, будто объекты находятся на расстоянии, близком к радиусу *Environment Probe*).
  - Промежуточные значения представляют коэффициент линейной интерполяции для коррекции параллакса и устанавливаются, когда *Environment Probe* используется для вписывания среднего или небольшого объекта в окружение для дополнительной коррекции.

## float getSphereReflectionParallax () const

Возвращает текущее значение коррекции параллакса для кубических карт отражений, проецируемых *Environment Probe*. При минимальном значении 0 кубические карты отражений просто проецируются на объекты и не следуют за перспективой наблюдателя. Это приводит к нереалистичным отражениям на большинстве поверхностей. Коррекция параллакса позволяет учитывать позицию камеры.
> **Notice:** Коррекция параллакса недоступна для отражений на прозрачных объектах.


### Возвращаемое значение

Текущее значение коррекции параллакса, устанавливаемое для кубических карт отражений, проецируемых *Environment Probe*, в диапазоне **[0;1]**:
- При минимальном значении 0 коррекция параллакса отключена (отражения будут выглядеть так, будто объекты находятся на бесконечном расстоянии).
- При максимальном значении 1 коррекция параллакса включена (отражения будут выглядеть так, будто объекты находятся на расстоянии, близком к радиусу *Environment Probe*).
- Промежуточные значения представляют коэффициент линейной интерполяции для коррекции параллакса и устанавливаются, когда *Environment Probe* используется для вписывания среднего или небольшого объекта в окружение для дополнительной коррекции.


## void setGrabZFar ( float zfar )

Задаёт новое расстояние до дальней плоскости отсечения, используемое для захвата изображения.
### Аргументы

- *float* **zfar** - Расстояние до дальней плоскости отсечения.

## float getGrabZFar () const

Возвращает текущее расстояние до дальней плоскости отсечения, используемое для захвата изображения.
### Возвращаемое значение

Текущее расстояние до дальней плоскости отсечения.
## void setGrabZNear ( float znear )

Задаёт новое расстояние до ближней плоскости отсечения, используемое для захвата изображения.
### Аргументы

- *float* **znear** - Расстояние до ближней плоскости отсечения.

## float getGrabZNear () const

Возвращает текущее расстояние до ближней плоскости отсечения, используемое для захвата изображения.
### Возвращаемое значение

Текущее расстояние до ближней плоскости отсечения.
## void setGrabViewportMask ( int mask )

Задаёт новую маску, определяющую материалы, для которых отражения должны рендериться в viewport.
> **Notice:** Маска viewport отражений может быть указана только для динамических отражений (когда [Grab Mode](#setGrabMode_int_void) установлен в DYNAMIC).


### Аргументы

- *int* **mask** - Маска viewport отражений (целое число, каждый бит которого используется для представления маски).

## int getGrabViewportMask () const

Возвращает текущую маску, определяющую материалы, для которых отражения должны рендериться в viewport.
> **Notice:** Маска viewport отражений может быть указана только для динамических отражений (когда [Grab Mode](#setGrabMode_int_void) установлен в DYNAMIC).


### Возвращаемое значение

Текущая маска viewport отражений (целое число, каждый бит которого используется для представления маски).
## void setGrabGGXMipmapsQuality ( Render::GGX_MIPMAPS_QUALITY quality )

Задаёт новое качество мипмапов GGX.
### Аргументы

- *[Render::GGX_MIPMAPS_QUALITY](../../../api/library/rendering/class.render_cpp.md#GGX_MIPMAPS_QUALITY)* **quality** - Качество мипмапов GGX, одно из значений *[GGX_MIPMAPS_QUALITY](../../../api/library/rendering/class.render_cpp.md#GGX_MIPMAPS_QUALITY)*.

## Render::GGX_MIPMAPS_QUALITY getGrabGGXMipmapsQuality () const

Возвращает текущее качество мипмапов GGX.
### Возвращаемое значение

Текущее качество мипмапов GGX, одно из значений *[GGX_MIPMAPS_QUALITY](../../../api/library/rendering/class.render_cpp.md#GGX_MIPMAPS_QUALITY)*.
## void setGrabSupersampling ( LightEnvironmentProbe::GRAB_SUPERSAMPLING supersampling = MODE_1 )

Задаёт новый режим суперсэмплирования для захвата изображения.
### Аргументы

- *[LightEnvironmentProbe::GRAB_SUPERSAMPLING](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#GRAB_SUPERSAMPLING)* **supersampling** - Устанавливаемый режим суперсэмплирования, одно из значений GRAB_SUPERSAMPLING.

## LightEnvironmentProbe::GRAB_SUPERSAMPLING getGrabSupersampling () const

Возвращает текущий режим суперсэмплирования для захвата изображения.
### Возвращаемое значение

Текущий устанавливаемый режим суперсэмплирования, одно из значений GRAB_SUPERSAMPLING.
## void setGrabResolution ( LightEnvironmentProbe::GRAB_RESOLUTION resolution )

Задаёт новое разрешение маски отражений в пикселях.
### Аргументы

- *[LightEnvironmentProbe::GRAB_RESOLUTION](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#GRAB_RESOLUTION)* **resolution** - Разрешение маски отражений в пикселях, одно из значений GRAB_RESOLUTION.

## LightEnvironmentProbe::GRAB_RESOLUTION getGrabResolution () const

Возвращает текущее разрешение маски отражений в пикселях.
### Возвращаемое значение

Текущее разрешение маски отражений в пикселях, одно из значений GRAB_RESOLUTION.
## void setGrabDynamicFacesPerFrame ( LightEnvironmentProbe::GRAB_DYNAMIC_FACES_PER_FRAME frame )

Задаёт новый интервал обновления кубической текстуры, используемой для динамических отражений.
### Аргументы

- *[LightEnvironmentProbe::GRAB_DYNAMIC_FACES_PER_FRAME](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#GRAB_DYNAMIC_FACES_PER_FRAME)* **frame** - Значение, указывающее текущий интервал обновления динамической кубической текстуры (граней за кадр).

## LightEnvironmentProbe::GRAB_DYNAMIC_FACES_PER_FRAME getGrabDynamicFacesPerFrame () const

Возвращает текущий интервал обновления кубической текстуры, используемой для динамических отражений.
### Возвращаемое значение

Текущее значение, указывающее текущий интервал обновления динамической кубической текстуры (граней за кадр).
## void setBoxSize ( const Math:: vec3 && size )

Задаёт новый размер для *Environment Probe*, когда *[Projection Mode](#setProjectionMode_int_void)* установлен в Box.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &&* **size** - Размер бокса *Environment Probe* по осям X, Y и Z.

## Math:: vec3 & getBoxSize () const

Возвращает текущий размер для *Environment Probe*, когда *[Projection Mode](#setProjectionMode_int_void)* установлен в Box.
### Возвращаемое значение

Текущий размер бокса *Environment Probe* по осям X, Y и Z.
## void setBoxGlossCorners ( float corners )

Задаёт новое значение коэффициента, управляющего глянцевостью отражений в углах кубической проекции.
> **Notice:** Доступно только когда *[Projection Mode](#setProjectionMode_int_void)* установлен в Box.


### Аргументы

- *float* **corners** - Значение коэффициента, управляющего глянцевостью отражений в углах кубической проекции.

## float getBoxGlossCorners () const

Возвращает текущее значение коэффициента, управляющего глянцевостью отражений в углах кубической проекции.
> **Notice:** Доступно только когда *[Projection Mode](#setProjectionMode_int_void)* установлен в Box.


### Возвращаемое значение

Текущее значение коэффициента, управляющего глянцевостью отражений в углах кубической проекции.
## void setBoxAmbientParallax ( float parallax )

Задаёт новый коэффициент ambient-параллакса для кубической проекции.
> **Notice:** Доступно только когда *[Projection Mode](#setProjectionMode_int_void)* установлен в Box.


### Аргументы

- *float* **parallax** - Коэффициент ambient-параллакса.

## float getBoxAmbientParallax () const

Возвращает текущий коэффициент ambient-параллакса для кубической проекции.
> **Notice:** Доступно только когда *[Projection Mode](#setProjectionMode_int_void)* установлен в Box.


### Возвращаемое значение

Текущий коэффициент ambient-параллакса.
## void setLocalSpace ( bool space )

Задаёт новое значение, указывающее, включено ли локальное пространство (локальные координаты) для *Environment Probe*. Может использоваться для сцен с движущимися объектами.
### Аргументы

- *bool* **space** - Значение **true** включает локальное пространство (локальные координаты) для *Environment Probe*; **false** - отключает его.

## bool isLocalSpace () const

Возвращает текущее значение, указывающее, включено ли локальное пространство (локальные координаты) для *Environment Probe*. Может использоваться для сцен с движущимися объектами.
### Возвращаемое значение

**true**, если локальное пространство (локальные координаты) для *Environment Probe* включено; иначе **false**.
## void setCutoutByShadow ( bool shadow = false )

Задаёт новое значение, указывающее, включена ли обрезка отражений, перекрытых препятствиями. Эта возможность использует [depth texture](../../../api/library/lights/class.light_cpp.md#getBakedDepthTextureFilePath_cstr), захваченную для *Environment Probe*, для определения отражений, которые должны быть видны.
### Аргументы

- *bool* **shadow** - Значение **true** включает обрезку отражений, перекрытых препятствиями; **false** - отключает её.

## bool isCutoutByShadow () const

Возвращает текущее значение, указывающее, включена ли обрезка отражений, перекрытых препятствиями. Эта возможность использует [depth texture](../../../api/library/lights/class.light_cpp.md#getBakedDepthTextureFilePath_cstr), захваченную для *Environment Probe*, для определения отражений, которые должны быть видны.
### Возвращаемое значение

**true**, если обрезка отражений, перекрытых препятствиями, включена; иначе **false**.
## void setSkyCutout ( bool cutout = false )

Задаёт новое значение, указывающее, включена ли обрезка неба для захвата изображения.
### Аргументы

- *bool* **cutout** - Значение **true** включает обрезку неба для захвата изображения; **false** - отключает её.

## bool isSkyCutout () const

Возвращает текущее значение, указывающее, включена ли обрезка неба для захвата изображения.
### Возвращаемое значение

**true**, если обрезка неба для захвата изображения включена; иначе **false**.
## void setAdditiveBlending ( bool blending = false )

Задаёт новое значение, указывающее, включено ли аддитивное смешивание для *Environment Probe*. Эта опция обеспечивает большую гибкость в управлении отражениями. Её можно использовать для смешивания отражений нескольких Environment Probe вместе и управления ими по отдельности.
### Аргументы

- *bool* **blending** - Значение **true** включает режим аддитивного смешивания для *Environment Probe*; **false** - отключает его.

## bool isAdditiveBlending () const

Возвращает текущее значение, указывающее, включено ли аддитивное смешивание для *Environment Probe*. Эта опция обеспечивает большую гибкость в управлении отражениями. Её можно использовать для смешивания отражений нескольких Environment Probe вместе и управления ими по отдельности.
### Возвращаемое значение

**true**, если режим аддитивного смешивания для *Environment Probe* включён; иначе **false**.
## void setMultiplyBySkyColor ( bool color )

Включает или отключает модуляцию цвета солнца для *Environment Probe* (изменение света в *Environment Probe* при изменении цвета солнца). Этот параметр можно использовать для Environment Probe, запечённых на открытом воздухе
### Аргументы

- *bool* **color** - Значение **true** включает модуляцию цвета солнца для *Environment Probe*; **false** - отключает её.

## bool isMultiplyBySkyColor () const

Возвращает текущее значение, включающее или отключающее модуляцию цвета солнца для *Environment Probe* (изменение света в *Environment Probe* при изменении цвета солнца). Этот параметр можно использовать для Environment Probe, запечённых на открытом воздухе
### Возвращаемое значение

**true**, если модуляция цвета солнца для *Environment Probe* включена; иначе **false**.
## void setProjectionMode ( LightEnvironmentProbe::PROJECTION_MODE mode )

Задаёт новый режим проекции, используемый для *Environment Probe*.
### Аргументы

- *[LightEnvironmentProbe::PROJECTION_MODE](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#PROJECTION_MODE)* **mode** - Режим проекции, используемый для *Environment Probe*, одно из значений *PROJECTION_MODE*.

## LightEnvironmentProbe::PROJECTION_MODE getProjectionMode () const

Возвращает текущий режим проекции, используемый для *Environment Probe*.
### Возвращаемое значение

Текущий режим проекции, используемый для *Environment Probe*, одно из значений *PROJECTION_MODE*.
## void setGrabByBakeLighting ( bool lighting )

Задаёт новое значение, указывающее, должна ли [cubemap texture](#setTextureFilePath_String_void) изменяться инструментом [Bake Lighting Tool](../../../editor2/lighting/gi/bake_lighting/index.md).
### Аргументы

- *bool* **lighting** - Значение **true** включает захват кубической текстуры инструментом Bake Lighting Tool; **false** - отключает его.

## bool isGrabByBakeLighting () const

Возвращает текущее значение, указывающее, должна ли [cubemap texture](#setTextureFilePath_String_void) изменяться инструментом [Bake Lighting Tool](../../../editor2/lighting/gi/bake_lighting/index.md).
### Возвращаемое значение

**true**, если захват кубической текстуры инструментом Bake Lighting Tool включён; иначе **false**.
## void setGrabDistanceScale ( float scale = 0.5f )

Задаёт новый масштаб расстояния для отражения.
### Аргументы

- *float* **scale** - Множитель масштаба расстояния для отражения.

## float getGrabDistanceScale () const

Возвращает текущий масштаб расстояния для отражения.
### Возвращаемое значение

Текущий множитель масштаба расстояния для отражения.
## void setAttenuationDistance ( const Math:: vec3 & distance )

Задаёт новое расстояние от формы источника света, на котором источник света ничего не освещает.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **distance** - Расстояние от формы источника света, на котором источник света ничего не освещает.

## Math:: vec3 getAttenuationDistance () const

Возвращает текущее расстояние от формы источника света, на котором источник света ничего не освещает.
### Возвращаемое значение

Текущее расстояние от формы источника света, на котором источник света ничего не освещает.
## void setGrabBakeVisibilityLightmap ( bool lightmap )

Задаёт новое значение, указывающее, выполняется ли запекание поверхностей с лайтмапами в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **lightmap** - Значение **true** включает запекание поверхностей с лайтмапами в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityLightmap () const

Возвращает текущее значение, указывающее, выполняется ли запекание поверхностей с лайтмапами в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание поверхностей с лайтмапами в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityVoxelProbe ( bool probe )

Задаёт новое значение, указывающее, выполняется ли запекание источников света *Voxel Probe* в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Voxel Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **probe** - Значение **true** включает запекание Voxel Probe в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityVoxelProbe () const

Возвращает текущее значение, указывающее, выполняется ли запекание источников света *Voxel Probe* в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Voxel Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание Voxel Probe в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityEnvironmentProbe ( bool probe )

Задаёт новое значение, указывающее, выполняется ли запекание других источников света *Environment Probe* в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Voxel Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **probe** - Значение **true** включает запекание других Environment Probe в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityEnvironmentProbe () const

Возвращает текущее значение, указывающее, выполняется ли запекание других источников света *Environment Probe* в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Voxel Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание других Environment Probe в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityLightProj ( bool proj )

Задаёт новое значение, указывающее, выполняется ли запекание проекционных источников света в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **proj** - Значение **true** включает запекание проекционных источников света в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityLightProj () const

Возвращает текущее значение, указывающее, выполняется ли запекание проекционных источников света в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание проекционных источников света в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityLightOmni ( bool omni )

Задаёт новое значение, указывающее, выполняется ли запекание точечных источников света в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **omni** - Значение **true** включает запекание точечных источников света в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityLightOmni () const

Возвращает текущее значение, указывающее, выполняется ли запекание точечных источников света в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание точечных источников света в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityLightWorld ( bool world )

Задаёт новое значение, указывающее, выполняется ли запекание источников света world в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **world** - Значение **true** включает запекание источников света world в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityLightWorld () const

Возвращает текущее значение, указывающее, выполняется ли запекание источников света world в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание источников света world в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilitySky ( bool sky )

Задаёт новое значение, указывающее, выполняется ли запекание освещения от неба в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **sky** - Значение **true** включает запекание освещения от неба в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilitySky () const

Возвращает текущее значение, указывающее, выполняется ли запекание освещения от неба в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание освещения от неба в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityEmission ( bool emission )

Задаёт новое значение, указывающее, выполняется ли запекание источников света emission в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **emission** - Значение **true** включает запекание источников света emission в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityEmission () const

Возвращает текущее значение, указывающее, выполняется ли запекание источников света emission в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание источников света emission в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityHaze ( bool haze )

Задаёт новое значение, указывающее, выполняется ли запекание дымки в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **haze** - Значение **true** включает запекание дымки в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityHaze () const

Возвращает текущее значение, указывающее, выполняется ли запекание дымки в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание дымки в *Environment Probe* включено; иначе **false**.
## void setGrabBakeVisibilityClouds ( bool clouds )

Задаёт новое значение, указывающее, выполняется ли запекание облаков в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Аргументы

- *bool* **clouds** - Значение **true** включает запекание облаков в *Environment Probe*; **false** - отключает его.

## bool isGrabBakeVisibilityClouds () const

Возвращает текущее значение, указывающее, выполняется ли запекание облаков в *Environment Probe*. Эту опцию можно использовать вместе с [additive blending](#setAdditiveBlending_int_void) для большей гибкости в [light baking](../../../editor2/lighting/gi/bake_lighting/index.md). Таким образом, можно сделать Environment Probe независимыми друг от друга и комбинировать их для получения своего рода динамического эффекта GI.
### Возвращаемое значение

**true**, если запекание облаков в *Environment Probe* включено; иначе **false**.
## void setGrabEnvironmentReflectionIntensity ( float intensity )

Задаёт новую интенсивность отражения окружения.
### Аргументы

- *float* **intensity** - Интенсивность отражения окружения.

## float getGrabEnvironmentReflectionIntensity () const

Возвращает текущую интенсивность отражения окружения.
### Возвращаемое значение

Текущая интенсивность отражения окружения.
## void setGrabEnvironmentAmbientIntensity ( float intensity )

Задаёт новую интенсивность ambient-освещения окружения.
### Аргументы

- *float* **intensity** - Интенсивность ambient-освещения окружения.

## float getGrabEnvironmentAmbientIntensity () const

Возвращает текущую интенсивность ambient-освещения окружения.
### Возвращаемое значение

Текущая интенсивность ambient-освещения окружения.
## void setRaymarchingSpecularBRDF ( LightEnvironmentProbe::SPECULAR_BRDF_MODE brdf )

Задаёт новую модель распределения света для матовых поверхностей. [GGX](#SPECULAR_BRDF_MODE) более реалистична, хотя увеличивает шум и незначительно снижает производительность.
### Аргументы

- *[LightEnvironmentProbe::SPECULAR_BRDF_MODE](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#SPECULAR_BRDF_MODE)* **brdf** - Модель распределения света для матовых поверхностей, одно из значений *[SPECULAR_BRDF_MODE](#SPECULAR_BRDF_MODE)*. GGX более реалистична, хотя увеличивает шум и незначительно снижает производительность.

## LightEnvironmentProbe::SPECULAR_BRDF_MODE getRaymarchingSpecularBRDF () const

Возвращает текущую модель распределения света для матовых поверхностей. [GGX](#SPECULAR_BRDF_MODE) более реалистична, хотя увеличивает шум и незначительно снижает производительность.
### Возвращаемое значение

Текущая модель распределения света для матовых поверхностей, одно из значений *[SPECULAR_BRDF_MODE](#SPECULAR_BRDF_MODE)*. GGX более реалистична, хотя увеличивает шум и незначительно снижает производительность.
## void setRaymarchingSpecularReplaceWithDiffuseRoughnessThreshold ( float threshold )

Задаёт новое значение шероховатости, начиная с которого *Indirect Specular* перестаёт рассчитываться и заменяется на *Indirect Diffuse*. Эта настройка используется для оптимизации матовых отражений.
### Аргументы

- *float* **threshold** - Значение шероховатости, начиная с которого *Indirect Specular* перестаёт рассчитываться и заменяется на *Indirect Diffuse*.

## float getRaymarchingSpecularReplaceWithDiffuseRoughnessThreshold () const

Возвращает текущее значение шероховатости, начиная с которого *Indirect Specular* перестаёт рассчитываться и заменяется на *Indirect Diffuse*. Эта настройка используется для оптимизации матовых отражений.
### Возвращаемое значение

Текущее значение шероховатости, начиная с которого *Indirect Specular* перестаёт рассчитываться и заменяется на *Indirect Diffuse*.
## void setRaymarchingSpecularInformationLostRaysMultiplier ( float multiplier )

Задаёт новый множитель для [number of rays](#RaymarchingSpecularNumRays) в областях, где обычно возникает эффект призрачности (ghosting). Увеличение этого значения уменьшает призрачность, но чем больше случаев призрачности, тем сильнее это влияет на производительность.
### Аргументы

- *float* **multiplier** - Множитель для [number of rays](#getRaymarchingSpecularNumRays_int) для indirect specular в областях, где обычно возникает эффект призрачности.

## float getRaymarchingSpecularInformationLostRaysMultiplier () const

Возвращает текущий множитель для [number of rays](#RaymarchingSpecularNumRays) в областях, где обычно возникает эффект призрачности. Увеличение этого значения уменьшает призрачность, но чем больше случаев призрачности, тем сильнее это влияет на производительность.
### Возвращаемое значение

Текущий множитель для [number of rays](#getRaymarchingSpecularNumRays_int) для indirect specular в областях, где обычно возникает эффект призрачности.
## void setRaymarchingSpecularMipOffset ( float offset )

Задаёт новое смещение мипмапов для кубической карты, используемой для расчёта зеркальных отражений. Увеличение значения влияет на производительность, освещение становится менее детализированным и реалистичным, небольшие объекты на кубической карте могут быть потеряны. Значение 0 даёт наиболее визуально достоверный результат, но требует больше лучей для устранения шума.
### Аргументы

- *float* **offset** - Смещение мипмапов для кубической карты, используемой для расчёта зеркальных отражений. Увеличение значения влияет на производительность, освещение становится менее детализированным и реалистичным, небольшие объекты на кубической карте могут быть потеряны. Значение 0 даёт наиболее визуально достоверный результат, но требует больше лучей для устранения шума.

## float getRaymarchingSpecularMipOffset () const

Возвращает текущее смещение мипмапов для кубической карты, используемой для расчёта зеркальных отражений. Увеличение значения влияет на производительность, освещение становится менее детализированным и реалистичным, небольшие объекты на кубической карте могут быть потеряны. Значение 0 даёт наиболее визуально достоверный результат, но требует больше лучей для устранения шума.
### Возвращаемое значение

Текущее смещение мипмапов для кубической карты, используемой для расчёта зеркальных отражений. Увеличение значения влияет на производительность, освещение становится менее детализированным и реалистичным, небольшие объекты на кубической карте могут быть потеряны. Значение 0 даёт наиболее визуально достоверный результат, но требует больше лучей для устранения шума.
## void setRaymarchingSpecularThresholdOcclusion ( float occlusion )

Задаёт новое значение, ограничивающее имитацию перекрытия кубической карты окружения в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным. Этот параметр в основном используется для помещений для коррекции ложных отражений в перекрытых областях (ложные отражения заменяются чёрным цветом). Для открытых пространств рекомендуются более высокие значения этого параметра.
### Аргументы

- *float* **occlusion** - Значение, ограничивающее имитацию перекрытия кубической карты окружения для зеркальных отражений в областях, где информация не может быть получена.

## float getRaymarchingSpecularThresholdOcclusion () const

Возвращает текущее значение, ограничивающее имитацию перекрытия кубической карты окружения в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным. Этот параметр в основном используется для помещений для коррекции ложных отражений в перекрытых областях (ложные отражения заменяются чёрным цветом). Для открытых пространств рекомендуются более высокие значения этого параметра.
### Возвращаемое значение

Текущее значение, ограничивающее имитацию перекрытия кубической карты окружения для зеркальных отражений в областях, где информация не может быть получена.
## void setRaymarchingSpecularThreshold ( float threshold )

Задаёт новый порог, используемый для расчёта зеркальных отражений для ограничения имитации отражений в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным.
### Аргументы

- *float* **threshold** - Порог, используемый для расчёта зеркальных отражений для ограничения имитации зеркальности в областях, где информация не может быть получена.

## float getRaymarchingSpecularThreshold () const

Возвращает текущий порог, используемый для расчёта зеркальных отражений для ограничения имитации отражений в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным.
### Возвращаемое значение

Текущий порог, используемый для расчёта зеркальных отражений для ограничения имитации зеркальности в областях, где информация не может быть получена.
## void setRaymarchingSpecularNumStepsRoughnessThreshold ( float threshold )

Задаёт новое значение шероховатости, при котором [number of steps](#RaymarchingSpecularNumSteps) равно 1. Это требуется для оптимизации, так как максимально корректный расчёт матовых отражений может быть излишним.
### Аргументы

- *float* **threshold** - Значение шероховатости, при котором [number of steps](#getRaymarchingSpecularNumSteps_int) равно 1.

## float getRaymarchingSpecularNumStepsRoughnessThreshold () const

Возвращает текущее значение шероховатости, при котором [number of steps](#RaymarchingSpecularNumSteps) равно 1. Это требуется для оптимизации, так как максимально корректный расчёт матовых отражений может быть излишним.
### Возвращаемое значение

Текущее значение шероховатости, при котором [number of steps](#getRaymarchingSpecularNumSteps_int) равно 1.
## void setRaymarchingSpecularNumSteps ( int steps )

Задаёт новое количество шагов на луч, используемых для расчёта трассировки. Количество шагов определяет точность отражений и оказывает разумное влияние на производительность. Чем выше значение, тем точнее учитываются препятствия между объектами.
### Аргументы

- *int* **steps** - Количество шагов на луч, используемых для расчёта трассировки.

## int getRaymarchingSpecularNumSteps () const

Возвращает текущее количество шагов на луч, используемых для расчёта трассировки. Количество шагов определяет точность отражений и оказывает разумное влияние на производительность. Чем выше значение, тем точнее учитываются препятствия между объектами.
### Возвращаемое значение

Текущее количество шагов на луч, используемых для расчёта трассировки.
## void setRaymarchingSpecularNumRays ( int rays )

Задаёт новое количество лучей на пиксель, используемых для расчёта зеркальных отражений от шероховатых поверхностей. Использование большего количества лучей обеспечивает более точный расчёт шероховатости отражений, однако это более затратно.
### Аргументы

- *int* **rays** - Количество лучей на пиксель, используемых для расчёта зеркальных отражений от шероховатых поверхностей.

## int getRaymarchingSpecularNumRays () const

Возвращает текущее количество лучей на пиксель, используемых для расчёта зеркальных отражений от шероховатых поверхностей. Использование большего количества лучей обеспечивает более точный расчёт шероховатости отражений, однако это более затратно.
### Возвращаемое значение

Текущее количество лучей на пиксель, используемых для расчёта зеркальных отражений от шероховатых поверхностей.
## void setRaymarchingSpecularStepSize ( float size )

Задаёт новый размер шага трассировки, используемого для расчёта зеркальных отражений. Более высокие значения приводят к более длинным трассировкам (однако мелкие объекты могут быть пропущены), более низкие значения дают более детализированные отражения мелких объектов.
### Аргументы

- *float* **size** - Размер шага трассировки, используемого для расчёта indirect specular отражения.

## float getRaymarchingSpecularStepSize () const

Возвращает текущий размер шага трассировки, используемого для расчёта зеркальных отражений. Более высокие значения приводят к более длинным трассировкам (однако мелкие объекты могут быть пропущены), более низкие значения дают более детализированные отражения мелких объектов.
### Возвращаемое значение

Текущий размер шага трассировки, используемого для расчёта indirect specular отражения.
## void setRaymarchingDiffuseTranslucenceAnisotropy ( float anisotropy )

Задаёт новое значение, определяющее степень проникновения света через прозрачные поверхности.
### Аргументы

- *float* **anisotropy** - Значение, определяющее степень проникновения света через прозрачные поверхности. Примеры значений дают следующий эффект:

  - 0 — свет не проникает через поверхности.
  - 0.5 — свет распределяется поровну по обе стороны поверхности (вдоль направления луча и в сторону источника света)
  - 1.0 — весь свет проходит через поверхность вдоль направления луча.

## float getRaymarchingDiffuseTranslucenceAnisotropy () const

Возвращает текущее значение, определяющее степень проникновения света через прозрачные поверхности.
### Возвращаемое значение

Текущее значение, определяющее степень проникновения света через прозрачные поверхности. Примеры значений дают следующий эффект:
- 0 — свет не проникает через поверхности.
- 0.5 — свет распределяется поровну по обе стороны поверхности (вдоль направления луча и в сторону источника света)
- 1.0 — весь свет проходит через поверхность вдоль направления луча.


## void setRaymarchingDiffuseInformationLostRaysMultiplier ( float multiplier )

Задаёт новый множитель для [number of rays](#getRaymarchingDiffuseNumRays_int) для indirect diffuse в областях, где обычно возникает эффект призрачности. Увеличение этого значения уменьшает призрачность, но чем больше случаев призрачности, тем сильнее это влияет на производительность.
### Аргументы

- *float* **multiplier** - Множитель для [number of rays](#getRaymarchingDiffuseNumRays_int) для indirect diffuse в областях, где обычно возникает эффект призрачности.

## float getRaymarchingDiffuseInformationLostRaysMultiplier () const

Возвращает текущий множитель для [number of rays](#getRaymarchingDiffuseNumRays_int) для indirect diffuse в областях, где обычно возникает эффект призрачности. Увеличение этого значения уменьшает призрачность, но чем больше случаев призрачности, тем сильнее это влияет на производительность.
### Возвращаемое значение

Текущий множитель для [number of rays](#getRaymarchingDiffuseNumRays_int) для indirect diffuse в областях, где обычно возникает эффект призрачности.
## void setRaymarchingDiffuseMipOffset ( float offset )

Задаёт новое смещение мипмапов для кубической карты, используемой для расчёта рассеянного света. Увеличение значения влияет на производительность, освещение становится менее детализированным и реалистичным, небольшие объекты на кубической карте могут быть потеряны. Значение 0 даёт наиболее визуально достоверный результат, но требует больше лучей для устранения шума.
### Аргументы

- *float* **offset** - Смещение мипмапов для кубической карты, используемой для расчёта рассеянного света.

## float getRaymarchingDiffuseMipOffset () const

Возвращает текущее смещение мипмапов для кубической карты, используемой для расчёта рассеянного света. Увеличение значения влияет на производительность, освещение становится менее детализированным и реалистичным, небольшие объекты на кубической карте могут быть потеряны. Значение 0 даёт наиболее визуально достоверный результат, но требует больше лучей для устранения шума.
### Возвращаемое значение

Текущее смещение мипмапов для кубической карты, используемой для расчёта рассеянного света.
## void setRaymarchingDiffuseThresholdOcclusion ( float occlusion )

Задаёт новое значение, ограничивающее имитацию перекрытия кубической карты окружения в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным. Этот параметр в основном используется для помещений для коррекции ложных отражений в перекрытых областях (ложные отражения заменяются чёрным цветом). Для открытых пространств рекомендуются более высокие значения этого параметра.
### Аргументы

- *float* **occlusion** - Значение, ограничивающее имитацию перекрытия кубической карты окружения для рассеянного света в областях, где информация не может быть получена.

## float getRaymarchingDiffuseThresholdOcclusion () const

Возвращает текущее значение, ограничивающее имитацию перекрытия кубической карты окружения в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным. Этот параметр в основном используется для помещений для коррекции ложных отражений в перекрытых областях (ложные отражения заменяются чёрным цветом). Для открытых пространств рекомендуются более высокие значения этого параметра.
### Возвращаемое значение

Текущее значение, ограничивающее имитацию перекрытия кубической карты окружения для рассеянного света в областях, где информация не может быть получена.
## void setRaymarchingDiffuseThreshold ( float threshold )

Задаёт новый порог, используемый для расчёта рассеянного света для ограничения имитации отражений в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным.
### Аргументы

- *float* **threshold** - Порог, используемый для расчёта рассеянного света для ограничения имитации рассеянного света в областях, где информация не может быть получена.

## float getRaymarchingDiffuseThreshold () const

Возвращает текущий порог, используемый для расчёта рассеянного света для ограничения имитации отражений в областях, где информация не может быть получена. Более высокие значения делают эффект менее выраженным.
### Возвращаемое значение

Текущий порог, используемый для расчёта рассеянного света для ограничения имитации рассеянного света в областях, где информация не может быть получена.
## void setRaymarchingDiffuseNumSteps ( int steps )

Задаёт новое количество шагов на луч, используемых для расчёта трассировки. Количество шагов определяет точность непрямого освещения и оказывает разумное влияние на производительность. Чем выше значение, тем точнее учитываются препятствия между объектами.
### Аргументы

- *int* **steps** - Количество шагов на луч, используемых для расчёта трассировки.

## int getRaymarchingDiffuseNumSteps () const

Возвращает текущее количество шагов на луч, используемых для расчёта трассировки. Количество шагов определяет точность непрямого освещения и оказывает разумное влияние на производительность. Чем выше значение, тем точнее учитываются препятствия между объектами.
### Возвращаемое значение

Текущее количество шагов на луч, используемых для расчёта трассировки.
## void setRaymarchingDiffuseNumRays ( int rays )

Задаёт новое количество лучей на пиксель, используемых для расчёта рассеянных отражений от шероховатых поверхностей. Использование большего количества лучей обеспечивает более точный расчёт шероховатости отражений, однако это более затратно.
### Аргументы

- *int* **rays** - Количество лучей на пиксель, используемых для расчёта рассеянных отражений от шероховатых поверхностей.

## int getRaymarchingDiffuseNumRays () const

Возвращает текущее количество лучей на пиксель, используемых для расчёта рассеянных отражений от шероховатых поверхностей. Использование большего количества лучей обеспечивает более точный расчёт шероховатости отражений, однако это более затратно.
### Возвращаемое значение

Текущее количество лучей на пиксель, используемых для расчёта рассеянных отражений от шероховатых поверхностей.
## void setRaymarchingDiffuseStepSize ( float size )

Задаёт новый размер шага трассировки, используемого для расчёта рассеянного отражения. Более высокие значения приводят к более длинным трассировкам (однако мелкие объекты могут быть пропущены), более низкие значения дают более детализированные отражения мелких объектов.
### Аргументы

- *float* **size** - Размер шага трассировки, используемого для расчёта рассеянного отражения.

## float getRaymarchingDiffuseStepSize () const

Возвращает текущий размер шага трассировки, используемого для расчёта рассеянного отражения. Более высокие значения приводят к более длинным трассировкам (однако мелкие объекты могут быть пропущены), более низкие значения дают более детализированные отражения мелких объектов.
### Возвращаемое значение

Текущий размер шага трассировки, используемого для расчёта рассеянного отражения.
## void setRaymarchingNoiseFramesNumber ( int number )

Задаёт новое количество вариаций шумового паттерна, изменяющегося каждый кадр. Более высокие значения дают более динамичный эффект шума, но значительное временное накопление кадров создаёт впечатление, что используется больше лучей. Меньшие значения дают более статичный шумовой паттерн.
### Аргументы

- *int* **number** - Количество вариаций шумового паттерна

## int getRaymarchingNoiseFramesNumber () const

Возвращает текущее количество вариаций шумового паттерна, изменяющегося каждый кадр. Более высокие значения дают более динамичный эффект шума, но значительное временное накопление кадров создаёт впечатление, что используется больше лучей. Меньшие значения дают более статичный шумовой паттерн.
### Возвращаемое значение

Текущее количество вариаций шумового паттерна
## void setRaymarchingSpecularNonLinearStepSize ( float size )

Задаёт новое значение корректировки размера шага raymarching. Значение 0 означает, что размер шага одинаков для каждого шага, а при значении 1 каждый последующий шаг raymarching вдвое шире предыдущего.
### Аргументы

- *float* **size** - Значение корректировки размера шага raymarching.

## float getRaymarchingSpecularNonLinearStepSize () const

Возвращает текущее значение корректировки размера шага raymarching. Значение 0 означает, что размер шага одинаков для каждого шага, а при значении 1 каждый последующий шаг raymarching вдвое шире предыдущего.
### Возвращаемое значение

Текущее значение корректировки размера шага raymarching.
## void setRaymarchingSpecularPerspectiveCompensation ( float compensation )

Задаёт новую перспективную компенсацию для размера шага raymarching. 0 означает, что размер шага raymarching привязан к World Space, а 1 означает, что он привязан к Screen Space. В результате при значении 1 длина луча на расстоянии от камеры будет больше, чем на близком расстоянии, что имеет смысл для крупных объектов, но детали на мелких объектах вдали могут быть потеряны.
### Аргументы

- *float* **compensation** - Перспективная компенсация для размера шага raymarching.

## float getRaymarchingSpecularPerspectiveCompensation () const

Возвращает текущую перспективную компенсацию для размера шага raymarching. 0 означает, что размер шага raymarching привязан к World Space, а 1 означает, что он привязан к Screen Space. В результате при значении 1 длина луча на расстоянии от камеры будет больше, чем на близком расстоянии, что имеет смысл для крупных объектов, но детали на мелких объектах вдали могут быть потеряны.
### Возвращаемое значение

Текущая перспективная компенсация для размера шага raymarching.
## void setRaymarchingSpecularReconstructionSamples ( int samples )

Задаёт новое количество итераций, необходимых для более точного определения пересечения луча с поверхностью в экранном пространстве для indirect specular. Более высокие значения точнее определяют пересечение, однако значительно влияют на производительность.
### Аргументы

- *int* **samples** - Количество итераций для определения пересечения.

## int getRaymarchingSpecularReconstructionSamples () const

Возвращает текущее количество итераций, необходимых для более точного определения пересечения луча с поверхностью в экранном пространстве для indirect specular. Более высокие значения точнее определяют пересечение, однако значительно влияют на производительность.
### Возвращаемое значение

Текущее количество итераций для определения пересечения.
## void setRaymarchingSpecularThresholdBinarySearch ( float search )

Задаёт новое пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность. Более высокие значения могут вызвать больше ложных пересечений, но упрощают процесс определения пересечения.
### Аргументы

- *float* **search** - Пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность.

## float getRaymarchingSpecularThresholdBinarySearch () const

Возвращает текущее пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность. Более высокие значения могут вызвать больше ложных пересечений, но упрощают процесс определения пересечения.
### Возвращаемое значение

Текущее пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность.
## void setRaymarchingDiffuseNonLinearStepSize ( float size )

Задаёт новое значение корректировки размера шага raymarching. Значение 0 означает, что размер шага одинаков для каждого шага, а при значении 1 каждый последующий шаг raymarching вдвое шире предыдущего.
### Аргументы

- *float* **size** - Значение корректировки размера шага raymarching. The value of 0 means that the step size is the same for each step, and at the value of 1 each subsequent raymarching step is twice wider than the previous one.

## float getRaymarchingDiffuseNonLinearStepSize () const

Возвращает текущее значение корректировки размера шага raymarching. Значение 0 означает, что размер шага одинаков для каждого шага, а при значении 1 каждый последующий шаг raymarching вдвое шире предыдущего.
### Возвращаемое значение

Текущее значение корректировки размера шага raymarching. The value of 0 means that the step size is the same for each step, and at the value of 1 each subsequent raymarching step is twice wider than the previous one.
## void setRaymarchingDiffusePerspectiveCompensation ( float compensation )

Задаёт новую перспективную компенсацию для размера шага raymarching. 0 означает, что размер шага raymarching привязан к World Space, а 1 означает, что он привязан к Screen Space. В результате при значении 1 длина луча на расстоянии от камеры будет больше, чем на близком расстоянии, что имеет смысл для крупных объектов, но детали на мелких объектах вдали могут быть потеряны.
### Аргументы

- *float* **compensation** - Перспективная компенсация для размера шага raymarching.

## float getRaymarchingDiffusePerspectiveCompensation () const

Возвращает текущую перспективную компенсацию для размера шага raymarching. 0 означает, что размер шага raymarching привязан к World Space, а 1 означает, что он привязан к Screen Space. В результате при значении 1 длина луча на расстоянии от камеры будет больше, чем на близком расстоянии, что имеет смысл для крупных объектов, но детали на мелких объектах вдали могут быть потеряны.
### Возвращаемое значение

Текущая перспективная компенсация для размера шага raymarching.
## void setRaymarchingDiffuseReconstructionSamples ( int samples )

Sets a new number of iterations required for a more accurate detection of the screen-space ray-surface intersection for the indirect diffuse. Higher values define the intersection more precisely, however significantly affect performance.
### Аргументы

- *int* **samples** - Количество итераций для определения пересечения.

## int getRaymarchingDiffuseReconstructionSamples () const

Returns the current number of iterations required for a more accurate detection of the screen-space ray-surface intersection for the indirect diffuse. Higher values define the intersection more precisely, however significantly affect performance.
### Возвращаемое значение

Текущее количество итераций для определения пересечения.
## void setRaymarchingDiffuseThresholdBinarySearch ( float search )

Задаёт новое пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность. Более высокие значения могут вызвать больше ложных пересечений, но упрощают процесс определения пересечения.
### Аргументы

- *float* **search** - Пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность.

## float getRaymarchingDiffuseThresholdBinarySearch () const

Возвращает текущее пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность. Более высокие значения могут вызвать больше ложных пересечений, но упрощают процесс определения пересечения.
### Возвращаемое значение

Текущее пороговое значение, используемое для определения пересечения, которое задаёт глубину проникновения луча под поверхность.
## void setRaymarchingAmbientOcclusionRadius ( float radius )

Задаёт новый радиус сэмплируемых пикселей, используемых в эффекте Ambient Occlusion, управляющий степенью затемнённой области.
### Аргументы

- *float* **radius** - Радиус сэмплируемых пикселей, используемых в эффекте Ambient Occlusion.

## float getRaymarchingAmbientOcclusionRadius () const

Возвращает текущий радиус сэмплируемых пикселей, используемых в эффекте Ambient Occlusion, управляющий степенью затемнённой области.
### Возвращаемое значение

Текущий радиус сэмплируемых пикселей, используемых в эффекте Ambient Occlusion.
## void setRaymarchingAmbientOcclusionIntensity ( float intensity )

Задаёт новую интенсивность ambient occlusion. Учтите, что ambient occlusion не существует в реальном мире, это способ имитации теней между объектами. Для фотореалистичной визуализации рекомендуется сохранять это значение равным 0.
### Аргументы

- *float* **intensity** - Значение интенсивности ambient occlusion.

## float getRaymarchingAmbientOcclusionIntensity () const

Возвращает текущую интенсивность ambient occlusion. Учтите, что ambient occlusion не существует в реальном мире, это способ имитации теней между объектами. Для фотореалистичной визуализации рекомендуется сохранять это значение равным 0.
### Возвращаемое значение

Текущее значение интенсивности ambient occlusion.
## void setRaymarchingLastStepMode ( LightEnvironmentProbe::LAST_STEP_MODE mode )

Задаёт новую кубическую карту, используемую для последнего шага raymarching. Доступны следующие режимы:
- **Environment Probe** — кубическая карта, используемая для последнего шага, совпадает с картой для всех предыдущих шагов.
- **Only Sky** — кубическая карта содержит только небо и облака. Эта опция предназначена для исправления некорректного параллакса, который может возникать в отражениях из-за бесконечной длины последнего шага.


### Аргументы

- *[LightEnvironmentProbe::LAST_STEP_MODE](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#LAST_STEP_MODE)* **mode** - Кубическая карта для последнего шага. Одно из значений *[LAST_STEP_MODE](#LAST_STEP_MODE)*.

## LightEnvironmentProbe::LAST_STEP_MODE getRaymarchingLastStepMode () const

Возвращает текущую кубическую карту, используемую для последнего шага raymarching. Доступны следующие режимы:
- **Environment Probe** — кубическая карта, используемая для последнего шага, совпадает с картой для всех предыдущих шагов.
- **Only Sky** — кубическая карта содержит только небо и облака. Эта опция предназначена для исправления некорректного параллакса, который может возникать в отражениях из-за бесконечной длины последнего шага.


### Возвращаемое значение

Текущая кубическая карта для последнего шага. Одно из значений *[LAST_STEP_MODE](#LAST_STEP_MODE)*.
## void setRaymarchingSecondaryBounceProjectionMode ( LightEnvironmentProbe::SECONDARY_BOUNCE_PROJECTION_MODE mode )

Задаёт новый режим проекции вторичного отскока.
### Аргументы

- *[LightEnvironmentProbe::SECONDARY_BOUNCE_PROJECTION_MODE](../../../api/library/lights/class.lightenvironmentprobe_cpp.md#SECONDARY_BOUNCE_PROJECTION_MODE)* **mode** - Режим проекции вторичного отскока. Одно из значений *[SECONDARY_BOUNCE_PROJECTION_MODE](#SECONDARY_BOUNCE_PROJECTION_MODE)*.

## LightEnvironmentProbe::SECONDARY_BOUNCE_PROJECTION_MODE getRaymarchingSecondaryBounceProjectionMode () const

Возвращает текущий режим проекции вторичного отскока.
### Возвращаемое значение

Текущий режим проекции вторичного отскока. Одно из значений *[SECONDARY_BOUNCE_PROJECTION_MODE](#SECONDARY_BOUNCE_PROJECTION_MODE)*.
## void setReflectionCubicFiltering ( bool filtering )

Задаёт новое значение, указывающее, включена ли бикубическая интерполяция для кубической карты Enviropment Probe вместо стандартной билинейной интерполяции. Этот эффект применяется только к отражённому освещению и рассчитывается, если пиксель имеет низкое значение *[Roughness](../../../content/materials/library/mesh_base/index.md#parameter_roughness)*. Изменения применяются только к первому мипу кубической карты. Эффект визуально представляет собой лёгкое размытие соседних пикселей. Однако это не сглаживание и может повлиять на визуальное качество проб высокого разрешения.
Эту опцию можно комбинировать с *[setSrgbModified()](../../...md#setSrgbModified_int_void)* для достижения лучшего градиента между пикселями.


> **Notice:** - Включение этой опции влияет на производительность, поэтому рекомендуется включать её только для Environment Probe, влияющих на большое количество отражающих/зеркальных пикселей, особенно если это Probe низкого разрешения в реальном времени.
> - Чтобы эта опция действовала на **прозрачную** поверхность, для материала должно быть включено состояние *[Reflection Cubic Filtering](../../../content/materials/library/mesh_base/index.md#option_reflection_cubic_filtering)* (для непрозрачных материалов опция применяется автоматически).
> - Опция не влияет на [Impostors](../../../editor2/tools/impostors_creator/index.md).


### Аргументы

- *bool* **filtering** - Значение **true** включает бикубическую интерполяцию для Enviropment Probe; **false** - отключает её.

## bool isReflectionCubicFiltering () const

Возвращает текущее значение, указывающее, включена ли бикубическая интерполяция для кубической карты Enviropment Probe вместо стандартной билинейной интерполяции. Этот эффект применяется только к отражённому освещению и рассчитывается, если пиксель имеет низкое значение *[Roughness](../../../content/materials/library/mesh_base/index.md#parameter_roughness)*. Изменения применяются только к первому мипу кубической карты. Эффект визуально представляет собой лёгкое размытие соседних пикселей. Однако это не сглаживание и может повлиять на визуальное качество проб высокого разрешения.
Эту опцию можно комбинировать с *[setSrgbModified()](../../...md#setSrgbModified_int_void)* для достижения лучшего градиента между пикселями.


> **Notice:** - Включение этой опции влияет на производительность, поэтому рекомендуется включать её только для Environment Probe, влияющих на большое количество отражающих/зеркальных пикселей, особенно если это Probe низкого разрешения в реальном времени.
> - Чтобы эта опция действовала на **прозрачную** поверхность, для материала должно быть включено состояние *[Reflection Cubic Filtering](../../../content/materials/library/mesh_base/index.md#option_reflection_cubic_filtering)* (для непрозрачных материалов опция применяется автоматически).
> - Опция не влияет на [Impostors](../../../editor2/tools/impostors_creator/index.md).


### Возвращаемое значение

**true**, если бикубическая интерполяция для Enviropment Probe включена; иначе **false**.
## void setSrgbModified ( bool modified )

Задаёт новое значение, указывающее, преобразуется ли кубическая карта *Environment Probe* или расчёт в реальном времени в цветовую модель sRGB и модифицируется ли до более низкого динамического диапазона. Применение этой опции делает переход между соседними пикселями пробы более плавным, что визуально улучшает пробы низкого разрешения или пробы, содержащие яркие или постоянные пиксели. Включение или отключение этой опции требует перезапекания статической кубической карты, иначе освещение будет визуально некорректным. Если статическая *Environment Probe* использует повторно кубическую карту, запечённую с включённой этой опцией, её также следует включить для этой пробы.
Эту опцию можно комбинировать с *[setReflectionCubicFiltering()](../../...md#setReflectionCubicFiltering_int_void)* для достижения лучшего градиента между пикселями.


### Аргументы

- *bool* **modified** - Значение **true** включает преобразование в sRGB и более низкий динамический диапазон для кубической карты или расчёта в реальном времени; **false** - отключает его.

## bool isSrgbModified () const

Возвращает текущее значение, указывающее, преобразуется ли кубическая карта *Environment Probe* или расчёт в реальном времени в цветовую модель sRGB и модифицируется ли до более низкого динамического диапазона. Применение этой опции делает переход между соседними пикселями пробы более плавным, что визуально улучшает пробы низкого разрешения или пробы, содержащие яркие или постоянные пиксели. Включение или отключение этой опции требует перезапекания статической кубической карты, иначе освещение будет визуально некорректным. Если статическая *Environment Probe* использует повторно кубическую карту, запечённую с включённой этой опцией, её также следует включить для этой пробы.
Эту опцию можно комбинировать с *[setReflectionCubicFiltering()](../../...md#setReflectionCubicFiltering_int_void)* для достижения лучшего градиента между пикселями.


### Возвращаемое значение

**true**, если преобразование в sRGB и более низкий динамический диапазон для кубической карты или расчёта в реальном времени включено; иначе **false**.
## void setRenderAboveVoxelProbes ( bool probes )

Задаёт новое значение, указывающее, рендерится ли эта *Environment Probe* поверх Voxel Probe (или других Environment Probe) для имитации отскока GI от солнца. При включении *Environment Probe* аддитивно смешивается с Voxel Probe (или другими Environment Probe). Если несколько Environment Probe имеют эту настройку включённой, они рендерятся согласно указанному [order](../../../api/library/lights/class.light_cpp.md#setOrder_int_void).
### Аргументы

- *bool* **probes** - Значение **true** включает рендеринг *Environment Probe* поверх других проб; **false** - отключает его.

## bool isRenderAboveVoxelProbes () const

Возвращает текущее значение, указывающее, рендерится ли эта *Environment Probe* поверх Voxel Probe (или других Environment Probe) для имитации отскока GI от солнца. При включении *Environment Probe* аддитивно смешивается с Voxel Probe (или другими Environment Probe). Если несколько Environment Probe имеют эту настройку включённой, они рендерятся согласно указанному [order](../../../api/library/lights/class.light_cpp.md#setOrder_int_void).
### Возвращаемое значение

**true**, если рендеринг *Environment Probe* поверх других проб включён; иначе **false**.
---

## static LightEnvironmentProbePtr create ( const Math:: vec4 & color , const Math:: vec3 & attenuation_distance , const char * name = 0 )

Конструктор. Создаёт новую *Environment Probe* с модуляцией кубической карты на основе заданных параметров.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет *Environment Probe*.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **attenuation_distance** - Радиусы *Environment Probe*.
- *const char ** **name** - Путь к кубической текстуре *Environment Probe*.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [LightEnvironmentProbe](../../../api/library/nodes/class.node_cpp.md#LIGHT_ENVIRONMENT_PROBE).
