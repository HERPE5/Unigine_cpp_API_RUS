# Mesh Transparent


Реализует базовую функциональность рендеринга для прозрачного меша. Может использоваться для следующих объектов (унаследовано от родительского абстрактного материала — *[Mesh](../../../code/materials_shaders/abstract_materials/mesh.md)*):


- [ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md)
- [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)
- [ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)
- [ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)
- [ObjectMeshClutter](../../../api/library/objects/class.objectmeshclutter_cpp.md)
- [ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)


> **Примечание:** *Mesh Transparent* имеет те же [states](../../../code/materials_shaders/abstract_materials/mesh.md#features) и [shaders](../../../code/materials_shaders/abstract_materials/mesh.md#shaders), что и родительский абстрактный материал *Mesh*.


Исходный код этого абстрактного материала можно найти здесь: `<SDK>/data/core/materials/abstract/mesh/mesh_transparent.abstmat`


## Features


Абстрактный материал *Mesh Transparent* имеет функции, реализованные в виде внутренних состояний (states), которые можно включать по мере необходимости в дочернем материале:


| State Name | Default | Conditions | Description |
|---|---|---|---|
| transparent_blur | false | (none) | Включает рендеринг эффекта размытия прозрачности. |
| refraction | false | (none) | Включает рендеринг постобработки преломления. |
| refraction_information_lost_fix | false | refraction | Включает коррекцию преломления для областей с "потерянной информацией", используя информацию из областей за пределами внутреннего объёма объекта. |
| refraction_front_side | false | refraction && refraction_information_lost_fix | Рендерит преломление только для лицевых граней. Эту опцию можно использовать для стеклянных объектов без полостей внутри. Когда опция включена, поверхность должна перекрывать все прозрачные объекты, расположенные позади неё. |
| planar_reflection | false | (none) | Включает рендеринг динамических отражений. С помощью этой опции можно создавать реалистичные плоские зеркала и плоские отражающие поверхности (паркет, плоские лакированные поверхности и т.д.) |
| reflection_size | 7 | planar_reflection | Размер карты отражения, в пикселях. Возможные значения: [128, 256, 512, 1024, 2048, 4096, quart_height, half_height, height] |
| reflection_two_sided | false | (none) | Использовать опцию Two Sided для отражений |
| reflection_show_pivot | false | (none) | Включить двусторонний режим плоского отражения. |
| reflection_blur | true | (none) | Показать точку опоры отражения. |
| ambient_light | true | (none) | Включает поддержку двух и более [World Lights](../../../objects/lights/world/index.md). |
| ambient | true | (none) | Включить рендеринг материала, освещённого источником света environment probe. |
| environment_probe | true | ambient | Включить рендеринг материала, освещённого источником света environment probe. |
| voxel_probe | true | ambient | Включить рендеринг материала, освещённого источником света voxel probe. |
| planar_probe | true | ambient | Включить рендеринг материала, освещённого источником света planar probe. |
| light_omni | true | (none) | Включить рендеринг материала, освещённого источником omni light. |
| light_proj | true | (none) | Включить рендеринг материала, освещённого проекционным источником света. |
| light_world | true | (none) | Включить рендеринг материала, освещённого источником world light. |
| multiple_environment_probes | false | environment_probe | Освещает прозрачный объект несколькими environment probe и проецирует на этот объект их кубические карты. |
| lerp_cascades | false | (none) | Интерполяция каскадов |
| shadow_filter_mode | 2 | (none) | Режим фильтрации. Возможные значения: [none, low, medium, high ultra] |
| shadow_penumbra_mode | 0 | (none) | Режим полутени. Возможные значения: [none, low, medium, high ultra] |
| shadow_filter_noise | true | (none) | Шум фильтрации |
| shadow_penumbra_noise | true | (none) | Шум полутени |


## Shaders


### fragment


Для каждого типа света вызывается соответствующий PASS, на основе которого выбирается нужная логика шейдинга:


- transparent_blur
- refraction
- ambient
- light_omni
- light_proj
- light_world
- light_environment_probe
- light_voxel_probe
- light_planar_probe


Fragment shader имеет следующие выходные значения:


#### Output Data


| Name | Type | Description |
|---|---|---|
| OUT_FRAG_TRANSPARENT_REFRACTION | float2 | Смещение UV для прозрачного преломления (требует включённых transparent_blur и refraction) |
| OUT_FRAG_TRANSPARENT_BLUR | float | Радиус размытия прозрачности |


#### Textures


Список доступных текстур, которые предопределены и используются во fragment shader:


| Texture name | Texture type | State | Pass | Description |
|---|---|---|---|---|
| TEX_REFLECTION_CUBE | Cube | ambient | ambient | Кубическая карта отражений |
| TEX_REFLECTION_2D | 2D | ambient && planar_reflection | ambient | Текстура отражения |
| [TEX_TRANSPARENT_ENVIRONMENT_PROBE](../../../code/formats/materials_formats/base_material_format.md#element_texture) | 2D | ambient && multiple_environment_probes | ambient | Environment probes, отрендеренные на прозрачных объектах |
| [TEX_SKY_LUT](../../../principles/render/sequence/index.md#common_pass) | 2D Array | ambient && ambient_light | ambient | Массив таблиц поиска неба (sky lookup tables) |
| [TEX_REFLECT](../../../principles/render/sequence/index.md#dynamic_reflections) | 2D | ambient | light_planar_probe | Текстура плоского отражения |
| [TEX_REFLECT](../../../principles/render/sequence/index.md#dynamic_reflections) | Cube | ambient | light_environment_probe | Кубическая текстура отражения |
| TEX_LIGHTMAP | 2D | lightmap | ambient, deferred | Запечённая текстура lightmap |


## Usage Example


<details>
<summary>Transparent Mesh | Close</summary>

```xml
BaseMaterial <parent=Unigine::mesh_transparent>
{
    Texture2D albedo = "core/textures/common/checker_d.dds"
    Color albedo = [1 1 1 0.5]

    // оптимизация
    State static_shadow = true
    State vertex_velocity = false

    Shader vertex_struct =
    #{
        INIT_BASE_DATA
    #}

    Shader common =
    #{
        float4 sample_color(float2 uv)
        {
            return TEXTURE(tex_albedo, uv) * var_albedo;
        }
    #}

    Shader fragment =
    #{
        float4 color = sample_color(DATA_UV.xy);

        OUT_FRAG_ALBEDO = color.rgb;
        OUT_FRAG_SPECULAR = 0.5f;
        OUT_FRAG_ROUGHNESS = 1.0f;
        OUT_FRAG_METALNESS = 0.0f;

        OUT_FRAG_OPACITY = color.a;
    #}
}

```

</details>
