# Mesh


Реализует базовую функциональность рендеринга меша. Может использоваться для следующих объектов:


- [ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md)
- [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)
- [ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)
- [ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)
- [ObjectMeshClutter](../../../api/library/objects/class.objectmeshclutter_cpp.md)
- [ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)


Исходный код этого абстрактного материала можно найти здесь: `<SDK>/data/core/materials/abstract/mesh/mesh.abstmat`


## Features


Абстрактный материал для меша имеет функции, реализованные в виде внутренних состояний (states), которые можно включать по мере необходимости в дочернем материале:


| Name | Description |
|---|---|
| [Engine](#feature_engine) | Базовые функции материала *Mesh*. |
| [Post Processing](#feature_post_processing) | Эффекты постобработки, поддерживаемые материалом. |
| [Specular AA](#feature_specular_aa) | Функция [Specular Anti-Aliasing](../../../content/materials/library/mesh_base/index.md#option_specular_aa). |
| [Tessellation](#feature_tessellation) | Функция [Tessellation](../../../content/materials/library/mesh_base/index.md#tessellated_displacement) для меша. |


> **Примечание:** Следующие states, options и параметры представляют собой базовую функциональность, которая также доступна в абстрактных материалах [Mesh Transparent](../../../code/materials_shaders/abstract_materials/mesh_transparent.md) и [Mesh Unlit](../../../code/materials_shaders/abstract_materials/mesh_unlit.md).


### Engine


Группа Engine.

| alpha_fade ( State ) |  |
|---|---|
| Description: | Добавляет плавные переходы в областях, граничащих с пределами видимости меша (определяемыми настройками fade и visibility для поверхности, которой назначен материал). Может использоваться для плавных переходов между LOD. |
| Internal: | true |
| Default: | **false** |
| gbuffer ( State ) |  |
| Description: | Включает запись отложенных буферов (deferred buffers) для материала. |
| Editable: | false |
| Default: | **true** |
| lightmap ( State ) |  |
| Description: | Включает lightmap для геометрии, которой назначен данный материал. |
| Internal: | true |
| Default: | **false** |
| wireframe_antialiasing ( State ) |  |
| Description: | Включает сглаживание каркасного отображения (wireframe) для геометрии, которой назначен данный материал. |
| Internal: | true |
| Default: | **false** |
| force_velocity ( State ) |  |
| Description: | Включение этой опции заставляет движок вычислять velocity, необходимую для поддержки [TAA](../../../principles/render/antialiasing/taa.md) для меша. |
| Editable: | false |
| Default: | **false** |
| dynamic ( State ) |  |
| Description: | Включает запись в [velocity buffer](../../../principles/render/sequence/index.md#velocity). |
| Internal: | true |
| Default: | **false** |
| Condition: | (!force_velocity) |
| static_shadow ( State ) |  |
| Description: | Включает использование материала **Unigine::mesh_static_shadow** вместо данного материала для теней. Отключено для forward-материалов, поддерживающих *ObjectMeshStatic* или *ObjectParticles*. |
| Editable: | false |
| Default: | **false** |
| Condition: | (!tessellation_shadow && !custom_depth) |
| custom_depth ( State ) |  |
| Description: | Включает запись пользовательской глубины (custom depth) в Z-буфер. |
| Editable: | false |
| Default: | **0** |
| custom_depth_shadow ( State ) |  |
| Description: | Флаг, указывающий, влияет ли custom depth на тени. |
| Editable: | false |
| Default: | **true** |
| Condition: | (custom_depth) |
| tessellation ( State ) |  |
| Description: | Включает тесселяцию для геометрии, которой назначен данный материал. |
| Editable: | false |
| Default: | **false** |
| emission ( State ) |  |
| Description: | Включает рендеринг emission. Этот эффект имитирует свечение от чрезвычайно ярких поверхностей и может использоваться для создания самосветящихся объектов (ламп, огня и т.д.) |
| Editable: | false |
| Default: | **false** |
| auxiliary ( State ) |  |
| Description: | Включает вспомогательный (auxiliary) проход рендеринга для материала. Может использоваться для пользовательских постэффектов, таких как тепловизор и т.д. |
| Editable: | false |
| Default: | **false** |
| blend_src ( Option ) |  |
| Description: | Опция, используемая для масштабирования исходного цвета (цвета перекрывающего материала). |
| Editable: | false |
| Default: | **src_alpha** |
| blend_dest ( Option ) |  |
| Description: | Опция, используемая для масштабирования цвета назначения (цвета перекрываемого материала). |
| Editable: | false |
| Default: | **one_minus_src_alpha** |
| transparent ( Option ) |  |
| Description: | Тип прозрачности материала. |
| Editable: | false |
| Default: | **none** |
| overlap ( Option ) |  |
| Description: | Рендерит полигоны, к которым применён материал, поверх изображения. Может использоваться для элементов UI. |
| Editable: | false |
| Default: | **false** |
| two_sided ( Option ) |  |
| Description: | Рендерит полигоны, к которым применён материал, дважды за проход освещения. Эту опцию следует отключать для повышения производительности, когда не требуется рендерить обе стороны полигонов. |
| Editable: | false |
| Default: | **false** |
| depth_test ( Option ) |  |
| Description: | Включает и выключает тест глубины для материала. Может использоваться, чтобы сделать видимыми объекты, перекрытые другими (например, персонажа за стеной). |
| Editable: | false |
| Default: | **true** |
| depth_mask ( Option ) |  |
| Description: | Флаг, указывающий, включена ли запись в [depth buffer](../../../editor2/materials_settings/index.md#depth_write) для материала (только для *[Object](../../../api/library/objects/class.object_cpp.md)*). |
| Editable: | false |
| Default: | **true** |


### Post Processing


Следующие states определяют биты в маске материала (material mask):

| material_ssao ( State ) |  |
|---|---|
| Description: | Включает screen-space ambient occlusion (SSAO) для данного материала (только Alpha Test и Opaque, не Alpha Blend материалы). |
| Default: | **true** |
| Condition: | (gbuffer)&&(transparent!=2) |
| material_ssr ( State ) |  |
| Description: | Включает screen-space reflections (SSR) для данного материала (только Alpha Test и Opaque, не Alpha Blend материалы). |
| Default: | **true** |
| Condition: | (gbuffer)&&(transparent!=2) |
| material_sssss ( State ) |  |
| Description: | Включает Screen-Space Subsurface Scattering (SSSSS) для данного материала (только Alpha Test и Opaque, не Alpha Blend материалы). |
| Default: | **false** |
| Condition: | (gbuffer)&&(transparent!=2) |
| material_dof ( State ) |  |
| Description: | Включает эффект Depth of Field (DOF) для данного материала. |
| Default: | **true** |
| Condition: | (gbuffer) |
| material_motion_blur ( State ) |  |
| Description: | Включает motion blur для данного материала. |
| Default: | **true** |
| Condition: | (gbuffer) |
| material_screen_space_shadows ( State ) |  |
| Description: | Включает screen space shadows для данного материала. |
| Default: | **true** |
| Condition: | (gbuffer) |
| material_shoreline_wetness ( State ) |  |
| Description: | Включает эффект намокания (wetness) для объектов у береговой линии для данного материала (только Alpha Test и Opaque, не Alpha Blend материалы). |
| Default: | **true** |
| Condition: | (gbuffer)&&(transparent!=2) |


### Specular AA


| specular_aa ( State ) |  |
|---|---|
| Description: | Сглаживание бликов (specular highlights). Это сглаживание выполняется за счёт увеличения roughness в местах, где нормали меняют ориентацию. Используется геометрия модели, карта нормалей не требуется. |
| Editable: | true |
| Internal: | false |
| Default: | **false** |
| specular_aa_intensity ( Slider ) |  |
| Description: | Сила эффекта сглаживания бликов, от 0 до 1. Более высокие значения дают более размытый результат с меньшим количеством артефактов. |
| Editable: | true |
| Internal: | false |
| specular_aa_threshold ( Slider ) |  |
| Description: | Максимальное значение смещения, вычитаемого из значения гладкости (smoothness) для уменьшения артефактов. |
| specular_aa_albedo_impact ( State ) |  |
| Description: | Интенсивность затемнения albedo на металлических поверхностях. |
| specular_aa_specular_impact ( Slider ) |  |
| Description: | Интенсивность затемнения specular на диэлектрических поверхностях. |
| specular_aa_roughness_impact ( State ) |  |
| Description: | Интенсивность roughness. |


### Tessellation


| tessellation_shadow ( State ) |  |
|---|---|
| Description: | Включает тесселяцию для прохода теней. |
| Default: | **false** |
| Condition: | (tessellation) |


| tessellation_density ( Slider ) |  |
|---|---|
| Description: | Коэффициент субпиксельного уменьшения полигонов. Значение **1** соответствует максимальной плотности меша, определяемой параметром **Factor**. **Notice**: *хотя более низкие значения значительно уменьшают количество полигонов и повышают производительность, будьте осторожны — при движении камеры могут появляться визуальные артефакты. Чтобы избавиться от "дрожания" и сохранить малое количество полигонов, рекомендуется увеличивать **Density**, одновременно уменьшая значения **Factor**.* |
| Default: | **0.5** |
| Condition: | (tessellation) |
| tessellation_shadow_factor ( Slider ) |  |
| Description: | Коэффициент интенсивности тесселяции для полигонов теней: *более высокие* значения дают *больше* полигонов. |
| Default: | **0.25** |
| Condition: | (tessellation)&&(tessellation_shadow) |
| tessellation_shadow_density ( Slider ) |  |
| Description: | Коэффициент субпиксельного уменьшения полигонов теней. Значение **1** соответствует максимальной плотности меша, определяемой параметром **Shadow Factor**. |
| Default: | **0.1** |
| Condition: | (tessellation)&&(tessellation_shadow) |
| tessellation_distance_falloff_near ( Slider ) |  |
| Description: | Расстояние (в единицах) от камеры, на котором начинается затухание тесселяции. |
| Default: | **2** |
| Condition: | (tessellation) |
| tessellation_distance_falloff_far ( Slider ) |  |
| Description: | Диапазон расстояния затухания тесселяции, в единицах. Эффект тесселяции рендерится в диапазоне расстояний от **Near** до **Near + Far**. |
| Default: | **50** |
| Condition: | (tessellation) |
| tessellation_distance_falloff_exp ( Slider ) |  |
| Description: | Определяет, как быстро интенсивность тесселяции уменьшается с расстоянием. |
| Default: | **1** |
| Condition: | (tessellation) |
| tessellation_distance_falloff_max_mip ( Slider ) |  |
| Description: | Максимальный допустимый уровень mip-карты текстуры **Displacement**, позволяющий избежать потери деталей тесселяции на расстоянии. |
| Default: | **6** |
| Condition: | (tessellation) |
| tessellation_culling_near ( Slider ) |  |
| Description: | Расстояние (в единицах) от камеры, на котором начинается отсечение (culling) тесселяции. |
| Default: | **1** |
| Condition: | (tessellation) |
| tessellation_culling_back_face ( Slider ) |  |
| Description: | Угол (в градусах) между камерой и полигоном контрольного меша, при котором полигон не тесселируется. |
| Default: | **0.5** |
| Condition: | (tessellation) |
| tessellation_culling_screen_border ( Slider ) |  |
| Description: | Смещение границы экрана, используемое для предотвращения нежелательного отсечения тесселированных полигонов за пределами экрана. |
| Default: | **0.1** |
| Condition: | (tessellation) |
| tessellation_shadow_culling_back_face ( Slider ) |  |
| Description: | Угол (в градусах) между камерой и полигоном теней контрольного меша, при котором этот полигон не тесселируется. |
| Default: | **0.8** |
| Condition: | (tessellation)&&(tessellation_shadow) |
| tessellation_shadow_culling_screen_border ( Slider ) |  |
| Description: | Смещение границы экрана, используемое для предотвращения нежелательного отсечения тесселированных полигонов теней за пределами экрана. |
| Default: | **0.05** |
| Condition: | (tessellation)&&(tessellation_shadow) |


## Shaders


Список доступного шейдерного кода, включающего типы для текущего абстрактного материала. Эти пользовательские шейдеры включаются в шейдер абстрактного материала в соответствующем месте с помощью маркера.


### common


Весь шейдерный код, который вы здесь описываете (переменные, функции, defines, константы и т.д.), включается в каждый из остальных типов шейдеров: vertex, control, evaluate, fragment.


### vertex_struct


С помощью следующих структур можно получить доступ к базовым и пользовательским данным в этих шейдерах: vertex, control, evaluate, fragment.


| Name | Arguments | Description |
|---|---|---|
| INIT_BASE_DATA | *(none)* | Инициализирует переменные базовой структуры (доступны во всех шейдерах). |
| INIT_USER_DATA | **TYPE** — тип пользовательских данных **NAME** — имя пользовательских данных | Инициализирует пользовательские данные, которые будут интерполироваться между вершинами и **передаваться через шейдерный конвейер**. |
| INIT_USER_NOINTERPOLATION_DATA | **TYPE** — тип пользовательских данных **NAME** — имя пользовательских данных | Инициализирует пользовательские данные, которые не будут интерполироваться между вершинами, но всё равно **будут передаваться через шейдерный конвейер**. |


**INIT_BASE_DATA** инициализирует следующий набор семантик:


| Name | Type | Description | Access |
|---|---|---|---|
| INIT_POSITION | float4 | Добавляет позицию |  |
| INIT_FRONTFACE | bool | Добавляет входную семантику, указывающую грань примитива (лицевая или нет). | (none) |
| INIT_DATA_POSITION | float3 | Добавляет позицию в пространстве вида (view-space). |  |
| INIT_DATA_OBLIQUE_FRUSTUM | float | Добавляет наклонный фрустум (oblique frustum). | (none) |
| INIT_DATA_ALPHA_FADE | float | Добавляет alpha fade. | *(none)* |
| INIT_DATA_TESSELLATION_FACTOR | float | Добавляет коэффициент тесселяции. Требует включённой [tessellation](#feature_tessellation). |  |
| INIT_DATA_TESSELLATION_MIP | float | Добавляет пользовательскую семантику tessellation mip. Требует включённой [tessellation](#feature_tessellation). | (none) |
| INIT_DATA_TESSELLATION_SCALE | float | Добавляет пользовательскую семантику масштаба тесселяции. Требует включённой [tessellation](#feature_tessellation). | (none) |
| INIT_DATA_UV | float4 | Добавляет пользовательскую семантику UV-координат. |  |
| INIT_DATA_NEW_POSITION | float3 | Добавляет пользовательскую семантику новой позиции. Обновляется автоматически. | (none) |
| INIT_DATA_OLD_POSITION | float3 | Добавляет пользовательскую семантику старой позиции. Обновляется автоматически. | (none) |
| INIT_DATA_COLOR | float4 | Добавляет пользовательскую семантику цвета. |  |
| INIT_DATA_BINORMAL | float3 | Добавляет пользовательскую семантику бинормали. |  |
| INIT_DATA_NORMAL | float3 | Добавляет пользовательскую семантику нормали. |  |
| INIT_DATA_SIGN_BINORMAL | float | Добавляет пользовательскую семантику знака бинормали. |  |


### vertex


Выполняет операции (например, преобразования) над отдельными вершинами, полученными со стадии Input Assembler. Вы можете использовать предоставленные **Input data** для изменения **[Output data](#vertex_output_data)**.


#### Input Data


| Name | Type | Description |
|---|---|---|
| VERTEX_IN_POSITION | float3 | Позиция вершины в пространстве объекта |
| VERTEX_IN_UV | float4 | UV-координаты вершины |
| VERTEX_IN_COLOR | float4 | Цвет вершины |
| VERTEX_IN_BASIS | float4 | Кватернион базиса в пространстве. Обновляется автоматически для корректного вычисления velocity. |
| VERTEX_IN_TANGENT | float3 | Тангенс базиса в пространстве объекта. Обновляется автоматически для корректного вычисления velocity. |
| VERTEX_IN_BINORMAL | float3 | Бинормаль базиса в пространстве объекта. Обновляется автоматически для корректного вычисления velocity. |
| VERTEX_IN_NORMAL | float3 | Нормаль базиса в пространстве объекта. Обновляется автоматически для корректного вычисления velocity. |
| DATA_SIGN_BINORMAL | float | Знак бинормали в пространстве объекта. |
| VERTEX_IN_TRANSFORM | float4x4 | Преобразование из пространства объекта в пространство вида. |
| VERTEX_IN_MODELVIEW | float4x4 | Преобразование из мирового пространства в пространство вида. Обновляется автоматически для корректного вычисления velocity. |
| VERTEX_IN_IMODELVIEW | float4x4 | Преобразование из пространства вида в мировое пространство. Обновляется автоматически для корректного вычисления velocity. |
| VERTEX_IN_INSTANCE | uint | ID батчированного инстанса объекта. |
| VERTEX_IN_TIME | float | Текущее глобальное время движка, прошедшее с момента его инициализации, в мс. Обновляется автоматически для корректного вычисления velocity. |
| VERTEX_IN_GAME_TIME | float | Текущее игровое время, связанное с Game::setScale и Game::setIFps. Обновляется автоматически для корректного вычисления velocity. |


Используйте эти переменные как есть, поскольку они автоматически обновляются в процессе обработки материала (например, из-за вычислений velocity вершинный шейдер выполняется дважды).


#### Output Data


| Name | Type | Description |
|---|---|---|
| DATA_POSITION | float3 | Позиция вершины в пространстве вида |
| DATA_TANGENT | float3 | Тангенс вершины в пространстве вида |
| DATA_BINORMAL | float3 | Бинормаль вершины в пространстве вида |
| DATA_NORMAL | float3 | Нормаль вершины в пространстве вида |
| DATA_UV | float4 | Содержит набор UV-координат вершины: - **xy** — базовые UV - **zw** — UV лайтмапы |
| DATA_COLOR | float4 | RGBA-цвет вершины |
| DATA_TESSELLATION_FACTOR | float | Коэффициент тесселяции меша. Доступен только при включённом state tessellation. |


### evaluate


Здесь интерполируются все тесселированные данные вершин.


#### Input Data


> **Notice:** - Используйте префикс **IN_EVAL_** вместо **IN_** (например, *IN_EVAL_DATA_POSITION(index)*), чтобы получить неинтерполированное значение для конкретной вершины текущего патча, где index — индекс вершины треугольника от 0 до 2.
> - Все **IN_#DATA_NAME** здесь неявно вызывают **IN_INTERPOLATE_DATA()**.


#### Functions


> **Notice:** Функции сэмплирования текстур учитывают **DATA_TESSELLATION_MIP**.


| Name | Arguments | Description |
|---|---|---|
| TEXTURE | **Name** — имя слота текстуры **UV** — значение UV текстуры | Сэмплирует текстуру. |
| TEXTURE_MIP_OFFSET | **Name** — имя слота текстуры **UV** — значение UV текстуры **Offset** — значение смещения UV текстуры | Сэмплирует текстуру со смещением mipmap. |


### fragment


Формирует значения цвета для каждого интерполированного фрагмента пикселя. Вы можете использовать предоставленные **Input data** для изменения **[Output data](#fragment_output_data)**.


#### Input Data


| Name | Type | Description |
|---|---|---|
| DATA_NORMAL | float3 | Нормаль в пространстве вида |
| DATA_BINORMAL | float3 | Бинормаль в пространстве вида |
| DATA_TANGENT | float3 | Тангенс в пространстве вида |
| DATA_UV | float4 | Набор UV-координат - **xy** — базовые UV - **zw** — UV лайтмапы |
| DATA_COLOR | float4 | Цвет вершины |
| DATA_ALPHA_FADE | float | Значение alpha fade |


#### Output Data


> **Notice:** Для материалов Alpha Test и Transparent (в одном из следующих проходов: *Deferred, Auxiliary, Shadow*) порог непрозрачности отбрасывает пиксель, если **opacity <= threshold**.


| Name | Type | Default | Description |
|---|---|---|---|
| OUT_FRAG_ALBEDO | float3 | (0, 0, 0) | Модификатор цвета albedo GBuffer |
| OUT_FRAG_OPACITY | float | 1 | Альфа текущего пикселя |
| OUT_FRAG_OPACITY_THRESHOLD | float | 0.5 | Порог непрозрачности |
| OUT_FRAG_METALNESS | float | 0 | Значение metalness GBuffer |
| OUT_FRAG_ROUGHNESS | float | 0 | Значение roughness GBuffer |
| OUT_FRAG_SPECULAR | float | 0 | Значение specular GBuffer |
| OUT_FRAG_MICROFIBER | float | 0 | Значение microfiber GBuffer |
| OUT_FRAG_NORMAL | float3 | DATA_NORMAL | Нормаль в пространстве вида |
| OUT_FRAG_TRANSLUCENT | float | 0 | Значение translucent GBuffer |
| OUT_FRAG_BEVEL | float | 0 | Радиус фаски (bevel) |
| OUT_FRAG_CAVITY | float | 0 | Маска cavity |
| OUT_FRAG_CONVEXITY | float | 0 | Маска convexity |
| OUT_FRAG_EMISSION | float3 | (0, 0, 0) | Значение цвета emission (требует включённого [emission](#emission)) |
| OUT_FRAG_AUXILIARY | float4 | (0, 0, 0, 0) | Значение вспомогательного (auxiliary) цвета (требует включённого [auxiliary](#auxiliary)) |
| OUT_FRAG_DELTA_DEPTH | float | 0 | Дельта глубины (требует включённого [custom_depth](#custom_depth)) |


## Usage Examples


### Normal Mapping


<details>
<summary>Normal Mapping | Close</summary>

```xml
BaseMaterial <parent=Unigine::mesh>
{
	Texture2D normal = "core/textures/post_filter_wet_normal.dds"

	Color albedo = [1 1 1 1]

	// оптимизация
	State static_shadow = true
	State vertex_velocity = false

	Shader vertex_struct =
	#{
		INIT_BASE_DATA
	#}

	Shader common =
	#{
		float3 color_to_normal_ts(float4 color)
		{
			float3 normal;
			normal.xy = color.xy * 2.0f - float2_one;
			normal.z = sqrt(saturate(1.0f - length(normal.xy)));
			return normalize(normal);
		}

		float3 sample_normalmap(float2 uv, float3x3 rotate_view_to_tangent)
		{
			float4 normalmap = TEXTURE(tex_normal, uv);
			float3 normal = color_to_normal_ts(normalmap);
			return mul3(normal, rotate_view_to_tangent);
		}
	#}

	Shader fragment =
	#{
		const float3x3 rotate_view_to_tangent = matrix3Row(DATA_TANGENT, DATA_BINORMAL, DATA_NORMAL);

		OUT_FRAG_ALBEDO = var_albedo.rgb;
		OUT_FRAG_SPECULAR = 0.5f;
		OUT_FRAG_ROUGHNESS = 1.0f;
		OUT_FRAG_METALNESS = 0.0f;
		OUT_FRAG_NORMAL = sample_normalmap(DATA_UV.xy, rotate_view_to_tangent);
	#}
}

```

</details>


### Albedo Texture


<details>
<summary>Albedo Texture | Close</summary>

```xml
BaseMaterial <parent=Unigine::mesh>
{
	Texture2D albedo = "core/textures/common/checker_d.dds"
	Color albedo = [1 1 1 1]

	// оптимизация
	State static_shadow = true
	State vertex_velocity = false

	Shader vertex_struct =
	#{
		INIT_BASE_DATA
	#}

	Shader common =
	#{
		float3 sample_albedo(float2 uv)
		{
			return TEXTURE(tex_albedo, uv).rgb * var_albedo.rgb;
		}
	#}

	Shader fragment =
	#{
		OUT_FRAG_ALBEDO = sample_albedo(DATA_UV.xy);
		OUT_FRAG_SPECULAR = 0.5f;
		OUT_FRAG_ROUGHNESS = 1.0f;
		OUT_FRAG_METALNESS = 0.0f;
	#}
}

```

</details>
