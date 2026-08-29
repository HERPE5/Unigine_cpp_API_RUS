# Mesh Unlit


Реализует базовую функциональность рендеринга для неосвещённого (unlit) меша. Не отбрасывает и не принимает тени, поэтому может служить основой для собственной реализации освещения (например, raymarching). Может использоваться для следующих объектов (унаследовано от родительского абстрактного материала — *[Mesh](../../../code/materials_shaders/abstract_materials/mesh.md)*):


- [ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md)
- [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md)
- [ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md)
- [ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md)
- [ObjectMeshClutter](../../../api/library/objects/class.objectmeshclutter_cpp.md)
- [ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md)


> **Примечание:** *Mesh Unlit* имеет те же [states](../../../code/materials_shaders/abstract_materials/mesh.md#features) и [shaders](../../../code/materials_shaders/abstract_materials/mesh.md#shaders), что и родительский абстрактный материал *Mesh*.


Исходный код этого абстрактного материала можно найти здесь: `<SDK>/data/core/materials/abstract/mesh/mesh_unlit.abstmat`


### See Also


- [Unlit Materials Example](../../../content/samples/material_examples/unlit_materials.md)


## Features


Абстрактный материал *Mesh Unlit* имеет функции, реализованные в виде внутренних состояний (states), которые можно включать по мере необходимости в дочернем материале:


### States


*Mesh Unlit* содержит те же states, что и родительский абстрактный материал Mesh, но добавляет новые или изменённые значения некоторых существующих.


| Name | Default | Description |
|---|---|---|
| static_shadow | true | Переопределяет значение state из Unigine::Mesh. |
| gbuffer | false | Включает запись отложенных буферов (deferred buffers) для материала. |
| transparent_blur | false | Включает рендеринг эффекта размытия прозрачности. |
| refraction | false | Включает рендеринг постобработки преломления. |


## Shaders


### fragment


Входные данные и функции те же, что и для абстрактного материала *[Mesh](../../../code/materials_shaders/abstract_materials/mesh.md#shader_fragment)*. Материал *Unlit* реализует свою "неосвещённую" функциональность, используя буфер emission в качестве вывода результирующего цвета и пропуская отложенный конвейер (deferred pipeline).


#### Output Data


| Name | Type | Description |
|---|---|---|
| OUT_FRAG_COLOR | float4 | Итоговый цвет фрагмента в виде emission |


## Usage Example


<details>
<summary>Unlit Mesh | Close</summary>

```xml
BaseMaterial <parent=Unigine::mesh_unlit>
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
        float4 sample_color(float2 uv)
        {
            return TEXTURE(tex_albedo, uv) * var_albedo;
        }
    #}

    Shader fragment =
    #{
        float4 color = srgbInv(sample_color(DATA_UV.xy));

        OUT_FRAG_EMISSION = color.rgb;
        OUT_FRAG_OPACITY = color.a;
    #}
}

```

</details>
