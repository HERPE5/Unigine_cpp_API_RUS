# Abstract Materials


Чтобы упростить программирование шейдеров и скрыть сложность реализации различных возможностей, были добавлены абстрактные материалы (Abstract Materials). Подобно абстрактным классам в объектно-ориентированном программировании, они служат шаблонным определением определённых параметров и функциональности.


Сам абстрактный материал нельзя назначить объектам, он используется для наследования от него других абстрактных и базовых материалов, расширяя его функциональность, что даёт большую гибкость.


Вы можете создать собственный пользовательский абстрактный материал или использовать предоставленные "из коробки" *[Mesh](../../../code/materials_shaders/abstract_materials/mesh.md) / [Mesh Transparent](../../../code/materials_shaders/abstract_materials/mesh_transparent.md) / [Mesh Unlit](../../../code/materials_shaders/abstract_materials/mesh_unlit.md) / [Decal](../../../code/materials_shaders/abstract_materials/decal.md)* с тесселяцией или без неё для создания пользовательского базового материала.


> **Примечание:** Создать экземпляр абстрактного материала невозможно.


## Наследование и переопределение


Наследуясь от абстрактного материала, вы можете переопределить любые значения и добавить другие компоненты в дочерний материал:


```glsl
AbstractMaterial A
{
		Slider t = 0.5
}

BaseMaterial B <parent = A>
{
		Slider t = 1.0
		Slider t2 = 2.0
}

```


> **Примечание:** Абстрактные материалы не поддерживают множественное наследование.


Когда дочерний материал реализует шейдер с тем же именем, исходный код родительского и дочернего шейдера объединяется (код родительского шейдера предшествует дочернему):


```glsl
AbstractMaterial A
{
		Shader example =
		#{
				// A_fragment
		#}
}

AbstractMaterial B <parent = A>
{
		Shader example =
		#{
				// B_fragment
		#}
}

// результирующий пример шейдера для абстрактного материала B будет выглядеть так:
Shader example =
#{
		// A_fragment
		// B_fragment
#}


```


Вы можете расширить и включить код другого шейдера с помощью наследования и маркера **#shader shader_name**.


```glsl
AbstractMaterial A
{
		// включаем другой код шейдера
		Shader a =
		#{
				// код шейдера A
				#shader b
		#}

		Shader b =
		#{
				// код шейдера B1
		#}
}

AbstractMaterial B <parent = A>
{
		// расширяем код родительского шейдера
		Shader b =
		#{
				// код шейдера B2
		#}
}

// результирующий пример шейдера для абстрактного материала B будет выглядеть так:
Shader a =
#{
		// код шейдера A
		// код шейдера B1
		// код шейдера B2
#}

```


Те же правила применяются к коду [Script](../../../code/formats/materials_formats/ulon_materials/scripts.md) (используйте **#script script_name** в качестве маркера).


Элементы в [Groups](../../../code/formats/materials_formats/ulon_materials/groups.md) родительского и дочернего материалов с одинаковым именем могут быть объединены. Обе группы должны иметь аргумент **merge_group**, установленный в true. Первая запись группы определяет место в UI редактора, где размещаются все элементы этой группы (родительские и дочерние):


```glsl
AbstractMaterial A
{
		Group A1
		{
				Slider T1

				Group example <merge_group=true>
				{
					   Slider T2
				}
		}
}

BaseMaterial B <parent = A>
{
		Group B1
		{
				Slider T3

				Group example <merge_group=true>
				{
					   Slider T4
				}
		}
}

// результирующая группировка для BaseMaterial B будет выглядеть так ("example" в BaseMaterial B объединён с родительской группой example):
Group A1
{
		Slider T1

		Group example
		{
			   Slider T2
			   Slider T4
		}
}

Group B1
{
		Slider T3
}


```


> **Примечание:** Группы в одном материале могут иметь одинаковые имена. Если ни у одной из этих групп аргумент **merge_group** не установлен в true, они будут показаны в UI редактора как отдельные группы.


## Сравнение с традиционной логикой базового материала


Абстрактные материалы обобщают внутреннюю логику и предоставляют упрощённый интерфейс ввода и вывода для производных базовых материалов. Традиционный подход подразумевает много повторяющейся работы для создания материалов с разным шейдингом для одних и тех же типов объектов. Поэтому рекомендуется использовать сочетание абстрактного и базового материала. См. следующие примеры, которые помогают достичь одного и того же модифицированного эффекта SSAO.


### Комбинация абстрактного и базового материала


Этот пример демонстрирует, как объединяются абстрактный и базовый материал.


<details>
<summary>Abstract Material (my_abstract.abstmat) | Close</summary>

`my_abstract.abstmat`


```glsl
AbstractMaterial <preview_hidden=true var_prefix=var texture_prefix=tex>
{
	Texture2D color <source=procedural>

	Shader common=
	#{
	#}

	Shader base_shader=
	#{
		#include <core/materials/shaders/render/common.h>

		STRUCT_FRAG_BEGIN
			INIT_COLOR(float4)
		STRUCT_FRAG_END

		#shader common

		MAIN_FRAG_BEGIN(FRAGMENT_IN)
			#shader fragment
		MAIN_FRAG_END
	#}

	Pass post
	{
		Fragment=base_shader
	}

	Expression RENDER_CALLBACK_END_POST_MATERIALS=
	#{
		Texture source = engine.render.getTemporaryTexture(engine.render_state.getScreenColorTexture());

		source.copy(engine.render_state.getScreenColorTexture());
		setTexture("color", source);
		renderPassToTexture("post", engine.render_state.getScreenColorTexture());

		engine.render.releaseTemporaryTexture(source);
	#}
}


```

</details>


<details>
<summary>Base Material (my_base.basemat) | Close</summary>

`my_base.basemat`


```glsl
BaseMaterial <parent=my_abstract>
{
	Texture2D normal <source=gbuffer_normal>
	Texture2D scene_depth <source=current_depth>
	Texture2D modulation = "core/textures/common/checker_d.texture"
	Texture2D <source=ssao>

	Slider global_scale = 2

	Shader common=
	#{
		float3 triplanar_sample(float2 uv, float depth_in)
		{
			float3 normal_ws = mul3(s_imodelview, unpackGBufferNormal(TEXTURE(tex_normal, uv).rgb));
			float3 position_ws = s_camera_position + mul3(s_imodelview, nativeDepthToPositionVS(depth_in, uv));

			float4 texcoord = position_ws.xyyz * var_global_scale;
			float3 weight = triplanarWeightFast(normal_ws, 0.5f);

			return TEXTURE_TRIPLANAR(tex_modulation, texcoord, weight).rgb;
		}

		float4 final(float2 uv, float depth_in)
		{
			float4 base = TEXTURE(tex_color, uv);
			float ssao = TEXTURE(tex_ssao, uv).r;

			float3 effect = triplanar_sample(uv, depth_in);
			return float4(lerp(base.rgb * effect, base.rgb, ssao), base.a);
		}
	#}

	Shader fragment=
	#{
		float depth = TEXTURE(tex_scene_depth, IN_UV).r;
		if (depth == 0.0f || depth == 1.0f)
			discard;

		OUT_COLOR = final(IN_UV, depth);
	#}
}

```

</details>


### Только базовый материал


Этот пример демонстрирует тот же сценарий использования, что и [above](#abstract_base), но с использованием только базового материала.


<details>
<summary>Base Material only (my_single_base.basemat) | Close</summary>

`my_single_base.basemat`


```glsl
BaseMaterial <preview_hidden=true var_prefix=var texture_prefix=tex>
{
	Texture2D color <source=procedural>
	Texture2D normal <source=gbuffer_normal>
	Texture2D scene_depth <source=current_depth>
	Texture2D modulation = "core/textures/common/checker_d.texture"
	Texture2D <source=ssao>

	Slider global_scale = 2

	Shader base_shader=
	#{
		#include <core/materials/shaders/render/common.h>

		STRUCT_FRAG_BEGIN
			INIT_COLOR(float4)
		STRUCT_FRAG_END

		float3 triplanar_sample(float2 uv, float depth_in)
		{
			float3 normal_ws = mul3(s_imodelview, unpackGBufferNormal(TEXTURE(tex_normal, uv).rgb));
			float3 position_ws = s_camera_position + mul3(s_imodelview, nativeDepthToPositionVS(depth_in, uv));

			float4 texcoord = position_ws.xyyz * var_global_scale;
			float3 weight = triplanarWeightFast(normal_ws, 0.5f);

			return TEXTURE_TRIPLANAR(tex_modulation, texcoord, weight).rgb;
		}

		float4 final(float2 uv, float depth_in)
		{
			float4 base = TEXTURE(tex_color, uv);
			float ssao = TEXTURE(tex_ssao, uv).r;

			float3 effect = triplanar_sample(uv, depth_in);
			return float4(lerp(effect, base.rgb, ssao), base.a);
		}

		MAIN_FRAG_BEGIN(FRAGMENT_IN)
			float depth = TEXTURE(tex_scene_depth, IN_UV).r;
			if (depth == 0.0f || depth == 1.0f)
				discard;

			OUT_COLOR = final(IN_UV, depth);
		MAIN_FRAG_END
	#}

	Pass post
	{
		Fragment=base_shader
	}

	Expression RENDER_CALLBACK_END_POST_MATERIALS=
	#{
		Texture source = engine.render.getTemporaryTexture(engine.render_state.getScreenColorTexture());

		source.copy(engine.render_state.getScreenColorTexture());
		setTexture("color", source);
		renderPassToTexture("post", engine.render_state.getScreenColorTexture());

		engine.render.releaseTemporaryTexture(source);
	#}
}

```

</details>


## Создание и использование собственного материала


Давайте создадим материал с нуля. Для этого примера мы возьмём базовый абстрактный материал для эффектов пост-обработки.


### 1. Создание родительского абстрактного материала


Создайте новый текстовый файл с расширением `*.abstmat`. Имя файла используется как имя материала, назовём его `my_abstract`.


Абстрактный материал содержит все базовые параметры, наследуемые всеми дочерними материалами, а также базовый код шейдера. Эти базовые вещи объявляются следующим образом:


```glsl
AbstractMaterial <preview_hidden=true var_prefix=var texture_prefix=tex>
{

	// Добавим экранную текстуру, мы используем её позже в BaseMaterial
	Texture2D color <source=procedural>

	Shader common=
	#{
	#}

	// Здесь основная часть нашего фрагментного шейдера:
	Shader base_shader= // Объявляем узел шейдера для дальнейшего использования
	#{
		#include <core/materials/shaders/render/common.h> //Базовый include UUSL

		// Рендерим в одну текстуру с 4 каналами
		STRUCT_FRAG_BEGIN
			INIT_COLOR(float4)
		STRUCT_FRAG_END

		// Здесь мы добавим код из наследуемых материалов
		#shader common

		// Объявляем главную функцию фрагмента
		MAIN_FRAG_BEGIN(FRAGMENT_IN)
			// Здесь мы добавим код из наследуемых материалов
			#shader fragment
		MAIN_FRAG_END
	#}
}

```


Теперь нам нужно добавить проход рендеринга, так как один шейдер сам по себе ничего не рендерит. Поскольку мы реализуем материал пост-эффекта, следует добавить проход *post* и указать шейдеры, которые будут использоваться для него (мы будем использовать наш **base_shader** как фрагментный шейдер).


> **Примечание:** Если вершинный шейдер не указан, будет использован шейдер по умолчанию из `core/materials/shaders/default/empty.vert`.


```glsl
Pass post
{
	Fragment=base_shader
}

```


UNIGINE поддерживает функциональность [Scriptable Materials](../../../content/materials/scriptable.md), позволяющую выполнять выражения (фрагменты кода) на определённых этапах [rendering sequence](../../../principles/render/sequence/index.md), и мы собираемся её использовать.


```glsl
// Подпишем наше выражение USC на callback рендеринга после всех пост-эффектов движка
Expression RENDER_CALLBACK_END_POST_MATERIALS=
#{
	// Делаем копию экранной текстуры
	Texture source = engine.render.getTemporaryTexture(engine.render_state.getScreenColorTexture());
	source.copy(engine.render_state.getScreenColorTexture());

	// Устанавливаем её как исходную текстуру для пост-эффекта
	setTexture("color", source);

	// Рендерим проход "post" напрямую на экран
	renderPassToTexture("post", engine.render_state.getScreenColorTexture());

	// Так как мы больше не будем использовать вновь запрошенную текстуру, можно сообщить движку, что её может использовать кто-то другой.
	engine.render.releaseTemporaryTexture(source);
#}

```


Собрав всё вместе, мы получаем полный код нашего абстрактного материала, который можно скопировать и вставить в текстовый редактор и сохранить как файл `my_abstract.abstmat` в папку `data` вашего проекта:


<details>
<summary>Complete Abstract Material Code (my_abstract_base1.basemat) | Close</summary>

`my_abstract_base1.basemat`


```glsl
AbstractMaterial <preview_hidden=true var_prefix=var texture_prefix=tex>
{

	// Добавим экранную текстуру, мы используем её позже в BaseMaterial
	Texture2D color <source=procedural>

	Shader common=
	#{
	#}

	// Здесь основная часть нашего фрагментного шейдера:
	Shader base_shader= // Объявляем узел шейдера для дальнейшего использования
	#{
		#include <core/materials/shaders/render/common.h> //Базовый include UUSL

		// Рендерим в одну текстуру с 4 каналами
		STRUCT_FRAG_BEGIN
			INIT_COLOR(float4)
		STRUCT_FRAG_END

		// Здесь мы добавим код из наследуемых материалов
		#shader common

		// Объявляем главную функцию фрагмента
		MAIN_FRAG_BEGIN(FRAGMENT_IN)
			// Здесь мы добавим код из наследуемых материалов
			#shader fragment
		MAIN_FRAG_END
	#}

	// Добавляем проход post для рендеринга нашего эффекта
	Pass post
	{
		Fragment=base_shader
	}

	// Подпишем наше выражение USC на callback рендеринга после всех пост-эффектов движка
	Expression RENDER_CALLBACK_END_POST_MATERIALS=
	#{
		// Делаем копию экранной текстуры
		Texture source = engine.render.getTemporaryTexture(engine.render_state.getScreenColorTexture());
		source.copy(engine.render_state.getScreenColorTexture());

		// Устанавливаем её как исходную текстуру для пост-эффекта
		setTexture("color", source);

		// Рендерим проход "post" напрямую на экран
		renderPassToTexture("post", engine.render_state.getScreenColorTexture());

		// Так как мы больше не будем использовать вновь запрошенную текстуру, можно сообщить движку, что её может использовать кто-то другой.
		engine.render.releaseTemporaryTexture(source);
	#}
}

```

</details>


### 2. Наследование базового материала от абстрактного


Теперь мы унаследуем базовый материал от созданного абстрактного (`my_abstract.abstmat`), чтобы расширить его функциональность.


Для начала мы реализуем простой пост-эффект цветового фильтра.


Создайте новый файл с расширением `*.basemat`. Опять же, имя файла используется как имя базового материала.


Опишите базовый материал, указав, что его родителем является абстрактный материал `my_abstract`:


```glsl
BaseMaterial <parent=my_abstract>
{

	// Добавляем параметр цвета, который будет определять цвет оптического фильтра
	Color my_color = [0.5 0.5 0.5 1]

	// Все переменные шейдера, определённые в материале, должны иметь префикс, чтобы на них можно было ссылаться в шейдерах
	// Для слайдеров, цветов и других базовых параметров он задаётся через var_prefix, сейчас установленный как 'var'
	// Для текстур это texture_prefix, сейчас установленный как 'tex'
	Shader fragment=
	#{
		// Сэмплируем экранную текстуру
		float4 sample = TEXTURE(tex_color, IN_UV);

		// Умножаем экранную текстуру на указанный цвет
		OUT_COLOR = sample * var_my_color;
	#}
}

```


> **Примечание:** Все переменные шейдера, определённые в материале, должны иметь префикс, чтобы на них можно было ссылаться в шейдерах:
>
>
> - Префикс для **слайдера, цвета** и **других базовых параметров** задаётся с помощью аргумента **var_prefix**.
> - Префикс для **текстур** задаётся с помощью аргумента **texture_prefix**.
>
>
> Например:
>
>
> ```glsl
> // Задаём префиксы
> AbstractMaterial <preview_hidden=true var_prefix=var texture_prefix=tex>
>
> /*...*/
>
> // Добавляем параметр
> Color my_color = [0.5 0.5 0.5 1]
>
> /*...*/
>
> // Ссылаемся на переменную
> OUT_COLOR = sample * var_my_color;
>
>
> ```


Сохраните ваш базовый материал как `my_abstract_base1.basemat` в папку `data` вашего проекта.


Вот и всё. Того, что мы написали, достаточно для создания простого эффекта пост-обработки.


### 3. Добавление ещё одного производного материала


Теперь мы создадим ещё один, более сложный материал, производный от нашего абстрактного.


Этот материал будет использовать трипланарное отображение (triplanar mapping) для наложения указанной текстуры *modulation* с указанной *интенсивностью* в затенённых областях (согласно карте SSAO)


Давайте создадим новый файл базового материала и зададим тот же абстрактный материал (`my_abstract.abstmat`) в качестве его родителя.


Вот полный код нашего второго базового материала (сохраните его как `my_abstract_base2.basemat` в папку `data` вашего проекта):


<details>
<summary>Complete Abstract Material Code (my_abstract_base2.basemat) | Close</summary>

`my_abstract_base2.basemat`


```glsl
BaseMaterial <parent=my_abstract>
{
	// Для этого примера требуется больше текстур сцены
	Texture2D normal <source=gbuffer_normal>
	Texture2D scene_depth <source=current_depth>
	Texture2D <source=ssao>

	// Текстура modulation, масштаб UV и интенсивность эффекта
	Texture2D modulation = "core/textures/common/checker_d.texture"
	Slider global_scale = 2
	Slider power = 10 <min=0 max=3>

	Shader common=
	#{
		float3 triplanar_sample(float2 uv, float depth_in)
		{
			float3 normal_ws = mul3(s_imodelview, unpackGBufferNormal(TEXTURE(tex_normal, uv).rgb));
			float3 position_ws = s_camera_position + mul3(s_imodelview, nativeDepthToPositionVS(depth_in, uv));

			float4 texcoord = position_ws.xyyz * var_global_scale;
			float3 weight = triplanarWeightFast(normal_ws, 0.5f);

			return TEXTURE_TRIPLANAR(tex_modulation, texcoord, weight).rgb;
		}

		float4 final(float2 uv, float depth_in)
		{
			float4 base = TEXTURE(tex_color, uv);
			float ssao = TEXTURE(tex_ssao, uv).r;

			float3 effect = triplanar_sample(uv, depth_in);
			return float4(lerp(base.rgb * effect * var_power, base.rgb, ssao), base.a);
		}
	#}

	Shader fragment=
	#{
		// Сэмплируем текстуру глубины
		float depth = TEXTURE(tex_scene_depth, IN_UV).r;
		if (depth == 0.0f || depth == 1.0f)
		   discard;

		OUT_COLOR = final(IN_UV, depth);
	#}
}

```

</details>


### 4. Наследование пользовательских материалов от базовых и их использование


Значения параметров, объявленных в базовых материалах, можно изменять в реальном времени только в унаследованных пользовательских материалах. Поэтому вам нужно унаследовать пользовательские материалы от базовых материалов для ваших проектов и настроить их по необходимости (назначить и изменить значения параметров и т.д.).


Чтобы протестировать наш первый пост-эффект, сделайте следующее:


- Найдите `my_abstract_base1.basemat` в окне *Materials*, щёлкните на нём правой кнопкой мыши, выберите **Create Child** и переименуйте новый материал в `my_color_filter`. ![](create_child.png)
- Так как это пост-эффект, для его глобального применения нужно открыть *Settings -> Render -> Custom Post Materials*
- Нажмите **Add New Material** и укажите материал `my_color_filter`. После этого можно изменить цвет фильтра. ![](assign_scriptable.png)


Вот финальное изображение с применённым нашим первым пост-материалом.


![](material1.gif)


Повторите шаги выше для базового материала `my_abstract_base2.basemat`, чтобы протестировать второй пост-эффект. Вот как это может выглядеть:


![](material2.gif)
