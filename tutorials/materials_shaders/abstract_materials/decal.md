# Decal


Реализует базовую функциональность рендеринга для декалей. Может использоваться для следующих объектов:


- [DecalProj](../../../api/library/decals/class.decalproj_cpp.md)
- [DecalOrtho](../../../api/library/decals/class.decalortho_cpp.md)
- [DecalMesh](../../../api/library/decals/class.decalmesh_cpp.md)


Исходный код этого абстрактного материала можно найти здесь: `<SDK>/data/core/materials/abstract/decal/decal.abstmat`


## Возможности


Абстрактный материал для декалей имеет возможности, реализованные как внутренние состояния, которые можно включить по требованию в дочернем материале.


| blend_src ( Option ) |  |
|---|---|
| Description: | Опция, используемая для масштабирования исходного цвета (цвета накладываемого материала). |
| Editable: | false |
| Default: | **src_alpha** |
| blend_dest ( Option ) |  |
| Description: | Опция, используемая для масштабирования цвета назначения (цвета закрываемого материала). |
| Editable: | false |
| Default: | **one_minus_src_alpha** |
| transparent ( Option ) |  |
| Description: | Тип прозрачности материала. |
| Editable: | false |
| Default: | **blend** |
| alpha_fade ( State ) |  |
| Description: | Добавляет плавные переходы в областях, соседствующих с ограничениями видимости (определяемыми [fade and visibility settings](../../../objects/decals/proj/index.md#visibility)). Может использоваться для плавных переходов между LOD. |
| Internal: | true |
| Default: | **false** |
| screen_projection ( State ) |  |
| Description: | Включает [screen projection](../../../content/materials/library/decal_base/index.md#option_screen_proj) для декали вместо проецирования её на поверхность. (поддерживаются только Mesh декали) |
| Editable: | false |
| Default: | **false** |
| emission ( State ) |  |
| Description: | Включает рендеринг излучения (emission). Этот эффект симулирует свечение от чрезвычайно ярких поверхностей и может использоваться для создания самосветящихся объектов (ламп, огня и т.д.) |
| Editable: | false |
| Default: | **false** |
| auxiliary ( State ) |  |
| Description: | Включает вспомогательный проход рендеринга для материала. Может использоваться для пользовательских пост-эффектов, таких как тепловизор и т.д. |
| Editable: | false |
| Default: | **false** |
| albedo ( State ) |  |
| Description: | Включает вывод в буфер альбедо декали. |
| Editable: | false |
| Default: | **true** |
| metalness_specular_translucent ( State ) |  |
| Description: | Включает вывод в буфер шейдинга декали. |
| Editable: | false |
| Default: | **true** |
| roughness_microfiber ( State ) |  |
| Description: | Включает вывод в буфер шейдинга декали. |
| Editable: | false |
| Default: | **true** |
| normal ( State ) |  |
| Description: | Включает вывод в буфер нормалей декали. |
| Editable: | false |
| Default: | **true** |
| normal_substitute ( State ) |  |
| Description: | Режим рендеринга нормалей. По умолчанию карты нормалей базового и накладываемого материала объединяются вместе. При включении этой опции используются только нормали накладываемого материала. |
| Editable: | false |
| Default: | **false** |
| tbn_mode ( State ) |  |
| Description: | Определяет тангенциальное пространство (матрица *Tangent-Binormal-Normal*), используемое для наложения нормалей: - **Take From Decal Mesh** (0) — используются нормали меша декали (для *Mesh* декалей) или плоскости (для *Orthographic* и *Projected* декалей); - **Up Direction of Decal** (1) — используется локальный вектор "вверх" декали; - **GBuffer Normal** (2) — используются нормали из экранного буфера *normal*; - **GBuffer Depth Based Normal** (3) — нормали строятся на основе содержимого экранного буфера *depth*. В отличие от *GBuffer Normal*, эта опция предоставляет неизменённые нормали, как они представлены в геометрии сцены. |
| Editable: | false |
| Default: | **0** |
| material_mask ( Mask24 ) |  |
| Description: | Битовая маска декали. Декаль будет спроецирована на поверхность, если эта маска совпадает с маской материала поверхности (хотя бы один бит). |
| Default: | **0xffffffff** |
| Condition: | (gbuffer) |
| viewport_mask ( Option ) |  |
| Description: | Маска видового окна материала. Поверхность с назначенным этим материалом будет отрендерена в видовое окно, если её маска видового окна и маска видового окна материала совпадают с маской видового окна камеры (хотя бы один бит). |
| Default: | **0xffffffff** |
| order ( Option ) |  |
| Description: | Порядок сортировки, используемый при рендеринге прозрачных объектов с альфа-смешиванием. *Прозрачным* объектам следует назначать наименьшие номера порядка, чтобы они рендерились первыми, в то время как *непрозрачным* объектам следует назначать наибольшие номера порядка, чтобы они рендерились последними. |
| Default: | **false** |


## Шейдеры


Вот список доступного кода шейдеров, включающего типы для текущего абстрактного материала. Эти пользовательские шейдеры включаются в шейдер абстрактного материала в соответствующем месте через маркер.


### common


Весь код шейдера, который вы описываете здесь (переменные, функции, define, константы и т.д.), включается в каждый другой тип шейдера: vertex, fragment.


### vertex_struct


С помощью следующих структур вы можете получить доступ к базовым и пользовательским данным в этих шейдерах: vertex, fragment.


| Name | Arguments | Description |
|---|---|---|
| INIT_USER_DATA | **TYPE** — тип пользовательских данных **NAME** — имя пользовательских данных | Инициализирует пользовательские данные, которые будут интерполироваться между вершинами и передаваться через конвейер шейдеров. |


### vertex


Выполняет операции (например, трансформации) над отдельными вершинами, полученными от этапа Input Assembler, и передаёт их скрытому geometry-шейдеру. Вы можете использовать предоставленные **входные данные** для изменения **[Output data](#vertex_output_data)**.


#### Входные данные


| Name | Type | Description |
|---|---|---|
| VERTEX_IN_TRANSFORM | float4x4 | Преобразует из объектного пространства в пространство view. |
| VERTEX_IN_ITRANSFORM | float4x4 | Преобразует из пространства view в объектное пространство. |
| VERTEX_IN_MODELVIEW | float4x4 | Преобразует из мирового пространства в пространство view. |
| VERTEX_IN_IMODELVIEW | float4x4 | Преобразует из пространства view в мировое пространство. |
| VERTEX_IN_TIME | float | Текущее глобальное время движка, прошедшее с момента инициализации движка, в мс. Обновляется автоматически для корректного расчёта скорости. |
| VERTEX_IN_GAME_TIME | float | Текущее игровое время, связанное с Game::setScale и Game::setIFps. Обновляется автоматически для корректного расчёта скорости. |
| VERTEX_IN_POSITION | float3 | Позиция вершины в объектном пространстве. |
| VERTEX_IN_UV | float4 | Спроецированные UV вершины. |
| VERTEX_IN_COLOR | float4 | Цвет вершины. Постоянное значение — float4(1, 1, 1, 1) (только для DecalProj и DecalOrtho). |
| VERTEX_IN_BASIS | float4 | Закодированный базис вершины, используйте getTangentBasis(). Постоянное значение — float4(0, 0, 0, -1) (только для DecalProj и DecalOrtho). |
| VERTEX_IN_TANGENT | float3 | Тангенс вершины в объектном пространстве. Постоянное значение — float3(1, 0, 0) (только для DecalProj и DecalOrtho). |
| VERTEX_IN_BINORMAL | float3 | Бинормаль вершины в объектном пространстве. Постоянное значение — float3(0, -1, 0) (только для DecalProj и DecalOrtho). |
| VERTEX_IN_NORMAL | float3 | Нормаль вершины в объектном пространстве. Постоянное значение — float3(0, 0, 1) (только для DecalProj и DecalOrtho). |


#### Выходные данные


| Name | Type | Description |
|---|---|---|
| DATA_POSITION | float3 | Позиция вершины в пространстве view |
| DATA_TANGENT | float3 | Тангенс вершины в пространстве view |
| DATA_BINORMAL | float3 | Бинормаль вершины в пространстве view |
| DATA_NORMAL | float3 | Нормаль вершины в пространстве view |
| DATA_UV | float4 | Содержит набор UV-координат вершины. Для DecalMesh: - **xy** — базовые UV - **zw** — UV лайтмапы Для DecalProj/DecalOrtho: - **xy** — UV для текущей вершины - **zw** — 0, 0 |
| DATA_COLOR | float4 | RGBA цвет вершины |


### fragment


Формирует данные шейдинга для каждого интерполированного пиксельного фрагмента.


#### Входные данные


| Name | Type | Description |
|---|---|---|
| DATA_TANGENT | float3 | Позиция в пространстве view. |
| DATA_BINORMAL | float3 | Тангенс в пространстве view. |
| DATA_NORMAL | float3 | Бинормаль в пространстве view. |
| DATA_SIGN_BINORMAL | float | Знак бинормали. |
| DATA_UV | float4 | Набор UV-координат. Для DecalMesh: - **xy** — базовые UV - **zw** — UV лайтмапы Для DecalProj/DecalOrtho: - **xy** — UV для текущей вершины - **zw** — 0, 0 |
| DATA_COLOR | float4 | RGBA цвет. |
| PROJECTED_NORMAL | float3 | Нормаль в пространстве view. |
| PROJECTED_POSITION | float3 | Позиция фрагмента в мировом пространстве камеры. |
| SCENE_NORMAL | float3 | Нормаль G-buffer. |
| SCENE_POSITION | float3 | Позиция фрагмента в объектном пространстве. |


#### Выходные данные


| Name | Type | Default | Description |
|---|---|---|---|
| OUT_FRAG_OPACITY | float | Определяется отдельно в большинстве случаев. (см. исходный код абстрактного материала для справки) | Общая видимость декали |
| OUT_FRAG_AUXILIARY | float4 | (0, 0, 0, 0) | Модификатор вспомогательного цвета (требует включённого [auxiliary](#auxiliary)) |
| OUT_FRAG_OPACITY_AUXILIARY | float | 1 | Вспомогательная видимость (требует включённого [auxiliary](#auxiliary)) |
| OUT_FRAG_EMISSION | float3 | (0, 0, 0) | Модификатор цвета излучения (требует включённого [emission](#emission)) |
| OUT_FRAG_ALBEDO | float3 | (0, 0, 0) | Модификатор цвета альбедо G-buffer (требует включённого [albedo](#albedo)) |
| OUT_FRAG_OPACITY_ALBEDO | float | 1 | Видимость цвета альбедо (требует включённого [albedo](#albedo)) |
| OUT_FRAG_METALNESS | float | 0 | Модификатор металличности G-buffer (требует включённого [metalness_specular_translucent](#metalness_specular_translucent)) |
| OUT_FRAG_SPECULAR | float | 0.0 | Модификатор блика G-buffer (требует включённого [metalness_specular_translucent](#metalness_specular_translucent)) |
| OUT_FRAG_TRANSLUCENT | float | 0 | Модификатор просвечиваемости G-buffer (требует включённого [metalness_specular_translucent](#metalness_specular_translucent)) |
| OUT_FRAG_OPACITY_METALNESS_SPECULAR_TRANSLUCENT | float3 | 1 | Видимость металличности, блика и просвечиваемости (требует включённого [metalness_specular_translucent](#metalness_specular_translucent)) |
| OUT_FRAG_ROUGHNESS | float | 0 | Модификатор шероховатости G-buffer (требует включённого [roughness_microfiber](#roughness_microfiber)) |
| OUT_FRAG_MICROFIBER | float | 0 | Модификатор микроворса G-buffer (требует включённого [roughness_microfiber](#roughness_microfiber)) |
| OUT_FRAG_OPACITY_ROUGHNESS_MICROFIBER | float | 0 | Видимость шероховатости и микроворса (требует включённого [roughness_microfiber](#roughness_microfiber)) |
| OUT_FRAG_NORMAL | float3 | DATA_NORMAL | Нормаль в пространстве modelview (требует включённого [normal](#normal)) |
| OUT_FRAG_OPACITY_NORMAL | float | 1 | Видимость нормали (требует включённого [normal](#normal)) |


#### Текстуры


Список доступных текстур, предопределённых и используемых во фрагментном шейдере.


| Name | Type | Description |
|---|---|---|
| depth | 2D | Текстура, хранящая нативную глубину непрозрачности. |
| material_mask | 2D | Текстура, хранящая маску материала. |
| gbuffer_normal | 2D | Текстура, использующая G-buffer для хранения закодированной нормали. |


## Пример использования


<details>
<summary>Decal | Close</summary>

```xml
BaseMaterial <parent=Unigine::decal>
{
	TextureCube cubemap = "core/textures/common/environment_probe_default.texture"
	Slider z_offset = 0.5f <min=0 max=0.8>

	Shader common=
	#{
		float3 sample_albedo(float3 scene_position, float3 data_normal)
		{
			const float3x3 view_to_camera_world = toFloat3x3(s_imodelview);
			const float3x3 rotate_view_to_world = view_to_camera_world;

			float3 view_direction  = positionToViewDirection(scene_position);

			float3 cube_sample_uvw = reflect(-view_direction, data_normal);
			cube_sample_uvw = mul3(rotate_view_to_world, cube_sample_uvw) - float3(0.0f, 0.0f, var_z_offset);
			return TEXTURE(tex_cubemap, cube_sample_uvw).rgb;
		}
	#}

	Shader fragment=
	#{
		OUT_FRAG_ALBEDO = sample_albedo(SCENE_POSITION, DATA_NORMAL);
		OUT_FRAG_SPECULAR = 1.0f;
		OUT_FRAG_ROUGHNESS = 1.0f;
	#}
}

```

</details>
