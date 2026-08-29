# Unigine.Material Class (CPP)

**Header:** #include <UnigineMaterial.h>


Этот класс используется для создания [materials](../../../principles/world_structure/index.md#materials), которые назначаются каждому узлу (или каждой поверхности объекта) и определяют, как выглядят узлы. Материалы реализуют [shaders](../../../principles/world_structure/index.md#material_shaders) и определяют, какие [options](../../../principles/world_structure/index.md#material_options), [states](../../../principles/world_structure/index.md#material_states), [parameters](../../../principles/world_structure/index.md#material_parameters) и [textures](../../../principles/world_structure/index.md#material_textures) используются для рендеринга узла во время [rendering passes](../../../principles/render/sequence/index.md).


На материалы ссылаются через [GUID](../../../content/materials/inheritance.md#material_guid). Только на [manual](../../../content/materials/index.md#manual_internal_materials) материалы можно ссылаться по имени.


Имя материала (взятое из имени файла) определяет, как материал отображается в Materials Editor (иерархия материалов, редактор поверхностей узлов).


### Пространства имён


Материалы можно разделять на разные *пространства имён (namespaces)*, чтобы избежать коллизий имён между материалами движка и [user](../../../content/materials/index.md#user_materials) материалами. Материалы движка и редактора по умолчанию имеют собственные пространства имён (`Unigine` и `Editor` соответственно). Например, *Unigine::mesh_base* или *Editor::brush_draw_post*.


Вы можете создавать *собственные* пространства имён для своих материалов. Метод [Material::getNamespaceName()](#getNamespaceName_cstr) возвращает пространство имён материала, если оно было назначено.


### Получение имён параметров и текстур


Внутренние имена текстур и параметров материала отображаются во всплывающих подсказках UnigineEditor, **щелчок по имени параметра/текстуры** (ЛКМ, один раз) копирует его внутреннее имя в буфер обмена, что позволяет легко вставить его в код.


![](material_internal_names.png)


### Наследование материалов


Если вы разрабатываете проект с большим количеством динамически создаваемых и удаляемых объектов, вы можете столкнуться с внезапным падением производительности по, казалось бы, незначительным непредвиденным причинам.


При удалении объекта все уникальные материалы, назначенные ему, также должны быть удалены через *deleteLater()* для освобождения памяти. Этот метод проверяет каждый материал (у которого **[Material::canRenderNode()](../../...md#canRenderNode_int)* == **true***) на предмет того, используется ли он также другими объектами (т.е. все остальные объекты мира проверяются по отдельности). Согласно этой политике, все проверенные материалы будут удалены на следующем этапе swap главного цикла. Если в мире тысячи объектов, вы получите просадку производительности (spike).


Чтобы избежать просадки, нужно использовать правильный конвейер наследования материалов. Не получайте материал от другого объекта через *[Object::getMaterial(surface)](../../../api/library/objects/class.object_cpp.md#getMaterial_int_Material)* и не вызывайте на нём *[Material::inherit()](../../...md#inherit_Material)*. Лучше использовать *[Object::getMaterialInherit(surface)](../../../api/library/objects/class.object_cpp.md#getMaterialInherit_int_Material)*, который создаёт новый экземпляр материала, время жизни которого связано с этим объектом, и вам не придётся удалять его вручную.


Реализация, приводящая к просадке производительности:


```cpp
MaterialPtr mat = obj->getMaterial(surface);
MaterialPtr mat_inherited = mat->inherit();
obj->setMaterial(mat_inherited, surface);
…
obj.deleteLater();
mat_inherited.deleteLater();

```


Рекомендуемая реализация:


```cpp
MaterialPtr mat_inherited = obj->getMaterialInherit(surface);
…
obj.deleteLater();

```


### Примеры использования


#### Изменение текстур


В первом примере описывается, как унаследовать материал от базового, изменить его текстуру и задать для него [texture flags](../../../api/library/rendering/class.texture_cpp.md#SAMPLER_ANISOTROPY_1). Мы наследуем новый материал *my_mesh_base_0.mat* от материала *mesh_base*, назначаем его объекту *material ball* по умолчанию, меняем его текстуру альбедо и задаём для неё флаг [SAMPLER_FILTER_POINT](../../../api/library/rendering/class.texture_cpp.md#SAMPLER_FILTER_POINT).


Добавьте следующий код в файл `AppWorldLogic.cpp`.


```cpp
#include "AppWorldLogic.h"
#include <UnigineMaterials.h>
#include <UnigineWorld.h>

using namespace Unigine;

/* .. */

int AppWorldLogic::init()
{

	// указатель на материал, который будет унаследован от mesh_base и настроен
	MaterialPtr m;

	// ищем материал mesh_base
	MaterialPtr mesh_base_mat = Materials::findManualMaterial("Unigine::mesh_base");
	if (mesh_base_mat) {
		// наследуем новый материал от mesh_base
		m = mesh_base_mat->inherit();

		// проверяем, редактируемый ли наш материал, и выполняем изменения
		if (m->isEditable()) {
			Log::message("Material (%s) is editable.\n", m->getFilePath());

			// получаем номер текстуры альбедо материала
			int num = m->findTexture("albedo");

			// меняем текстуру альбедо материала на core/textures/common/checker_d.texture
			m->setTexturePath(num, "core/textures/common/checker_d.texture");

			// получаем текущие флаги, проверяем, включена ли точечная фильтрация, и выводим результат в консоль
			int flags = m->getTextureSamplerFlags(num);
			Log::message("Flags for %s texture (%d):%d \n", m->getTextureName(num), num, flags);
			Log::message("SAMPLER_FILTER_POINT %s\n", (flags & Texture::SAMPLER_FILTER_POINT) ? "enabled" : "disabled");

			// задаём флаг SAMPLER_FILTER_POINT
			m->setTextureSamplerFlags(num, Texture::SAMPLER_FILTER_POINT);

			// получаем флаги, проверяем, включена ли точечная фильтрация, и выводим результат в консоль
			int flagsSet = m->getTextureSamplerFlags(num);
			Log::message("Flags for %s texture (%d):%d \n", m->getTextureName(num), num, flagsSet);
			Log::message("SAMPLER_FILTER_POINT %s\n", (flagsSet & Texture::SAMPLER_FILTER_POINT) ? "enabled" : "disabled");
		}

		// сохраняем ассет материала по заданному пути
		if (!Materials::findMaterialByPath("materials/my_mesh_base_0.mat"))
			m->createMaterialFile("materials/my_mesh_base_0.mat");

		// получаем объект material_ball и назначаем ему материал material_ball_0
		if (ObjectMeshStaticPtr material_ball = checked_ptr_cast<ObjectMeshStatic>(World::getNodeByName("material_ball")))
			material_ball->setMaterialFilePath("materials/my_mesh_base_0.mat", "*");
	}

	return 1;
}


```


В результате вы увидите, что текстура альбедо объекта *material ball* изменилась, и в [console](../../../code/console/index.md) отображается следующий текст:


```text
Material (guid://4dfec30f491f753f6e89094db6d3d695e89f9d6f) is editable.
Flags for albedo texture (1):524288000
FILTER_POINT disabled
Flags for albedo texture (1):1048576
FILTER_POINT enabled

```


#### Изменение состояний и параметров


Второй пример иллюстрирует, как унаследовать материал от [mesh_base](../../../content/materials/library/mesh_base/index.md) и изменить два параметра, влияющих на внешний вид отражений.


Добавьте следующий код в файл `AppWorldLogic.cpp`.


```cpp
#include "AppWorldLogic.h"
#include <UnigineMaterials.h>
#include <UnigineWorld.h>

using namespace Unigine;

/* .. */

int AppWorldLogic::init()
{

	// ищем материал mesh_base
	MaterialPtr mesh_base = Materials::findManualMaterial("Unigine::mesh_base");
	// наследуем от него новый материал и задаём путь к ассету, который будет создан при вызове save():
	MaterialPtr reflector_material = mesh_base->inherit();

	// задаём параметры metalness и roughness, чтобы поверхность выглядела как зеркало
	// по имени параметра
	reflector_material->setParameterFloat("metalness", 1.0f);
	// или по его числовому индексу (оба подхода дают одинаковый результат)
	reflector_material->setParameterFloat(reflector_material->findParameter("roughness"), 0.0f);

	// сохраняем ассет материала в файл planar_reflector.mat в папке данных проекта
	reflector_material->createMaterialFile("planar_reflector.mat");

	// назначаем новый зеркальный материал объекту ground
	ObjectMeshDynamicPtr ground = checked_ptr_cast<ObjectMeshDynamic>(World::getNodeByName("ground"));
	ground->setMaterial(reflector_material, "*");

	return 1;
}


```


## Material Class

### Перечисления

## WIDGET

| Name | Description |
|---|---|
| **WIDGET_EDIT_INT** = 0 | Текстовый виджет, позволяющий задать целочисленное значение. |
| **WIDGET_EDIT_INT2** = 1 | Текстовый виджет, позволяющий задать 2 целочисленных значения. |
| **WIDGET_EDIT_INT3** = 2 | Текстовый виджет, позволяющий задать 3 целочисленных значения. |
| **WIDGET_EDIT_INT4** = 3 | Текстовый виджет, позволяющий задать 4 целочисленных значения. |
| **WIDGET_EDIT_FLOAT** = 4 | Текстовый виджет, позволяющий задать значение с плавающей точкой или целочисленное значение. |
| **WIDGET_EDIT_FLOAT2** = 5 | Текстовый виджет, позволяющий задать 2 значения с плавающей точкой или целочисленных значения. |
| **WIDGET_EDIT_FLOAT3** = 6 | Текстовый виджет, позволяющий задать 3 значения с плавающей точкой или целочисленных значения. |
| **WIDGET_EDIT_FLOAT4** = 7 | Текстовый виджет, позволяющий задать 4 значения с плавающей точкой или целочисленных значения. |
| **WIDGET_TOGGLE** = 8 | Виджет-кнопка, позволяющая включить или отключить определённое состояние. |
| **WIDGET_COMBOBOX** = 9 | Виджет ComboBox, позволяющий выбрать текстуру из доступных. |
| **WIDGET_TEXTURE_ASSET** = 10 | Виджет ассета текстуры, позволяющий указать текстуру. |
| **WIDGET_TEXTURE_RAMP** = 11 | Виджет ассета Ramp, позволяющий указать и настроить 2D Ramp через специальный Curve Editor. |
| **WIDGET_ACCORDION** = 12 | Виджет-аккордеон, позволяющий разворачивать или сворачивать набор содержащихся в нём виджетов. |
| **WIDGET_SLIDER** = 13 | Виджет-слайдер, позволяющий указать и настроить значение с плавающей точкой или целочисленное значение. |
| **WIDGET_COLOR** = 14 | Виджет цвета, позволяющий указать цвет через диалог выбора цвета. |
| **WIDGET_UV** = 15 | Виджет ассета UV-текстуры, позволяющий указать UV-текстуру. |
| **WIDGET_MASK24** = 16 | Виджет 24-битной [mask](../../../principles/bit_masking/index.md). |
| **WIDGET_MASK32** = 17 | Виджет 32-битной [mask](../../../principles/bit_masking/index.md). |

## DATA_TYPE

| Name | Description |
|---|---|
| **DATA_TYPE_OPTION** = 0 | Опция материала. |
| **DATA_TYPE_STATE** = 1 | Состояние материала. Состояния - это флаги, используемые для шейдера, соответствующего материалу. Состояния определяют набор текстур и параметров материала. |
| **DATA_TYPE_PARAMETER** = 2 | Параметр материала. |
| **DATA_TYPE_TEXTURE** = 3 | Текстура материала. |
| **DATA_TYPE_GROUP** = 4 | Группа материала. |

### Методы класса

---

## static MaterialPtr create ( )

Конструктор. Создаёт новый экземпляр материала.
## bool isAlphaTest ( ) const

Возвращает значение, указывающее, включена ли для материала опция alpha-теста.
### Возвращаемое значение

true, если для материала включена опция alpha-теста; иначе false.
## bool isBrush ( ) const

Возвращает значение, указывающее, используется ли материал для кистей (brush) (расширение файла `*.brush` или `*.basebrush`).
### Возвращаемое значение

true, если материал используется для кистей; иначе false.
## void setBlendDestFunc ( int func )

Задаёт целевую (destination) функцию [blending](../../../principles/render/blending/index.md).
### Аргументы

- *int* **func** - Целевая функция смешивания для задания (одна из переменных [*BLEND_**](../../../api/library/rendering/class.renderstate_cpp.md#BLEND_NONE)).

## int getBlendDestFunc ( ) const

Возвращает целевую (destination) функцию [blending](../../../principles/render/blending/index.md).
### Возвращаемое значение

Целевая функция смешивания (одна из переменных [*BLEND_**](../../../api/library/rendering/class.renderstate_cpp.md#BLEND_NONE)).
## void setBlendSrcFunc ( int func )

Задаёт исходную (source) функцию [blending](../../../principles/render/blending/index.md).
### Аргументы

- *int* **func** - Исходная функция смешивания для задания (одна из переменных [*BLEND_**](../../../api/library/rendering/class.renderstate_cpp.md#BLEND_NONE), описанных в классе *RenderState*).

## int getBlendSrcFunc ( ) const

Возвращает исходную (source) функцию [blending](../../../principles/render/blending/index.md).
### Возвращаемое значение

Исходная функция смешивания (одна из переменных [*BLEND_**](../../../api/library/rendering/class.renderstate_cpp.md#BLEND_NONE), описанных в классе *RenderState*).
## void setBlendAlphaSrcFunc ( int func )

Задаёт исходную функцию [blending](../../../principles/render/blending/index.md) альфа-канала.
### Аргументы

- *int* **func** - Исходная функция смешивания альфа-канала для задания (одна из переменных [*BLEND_**](../../../api/library/rendering/class.renderstate_cpp.md#BLEND_NONE)).

## int getBlendAlphaSrcFunc ( ) const

Возвращает исходную функцию [blending](../../../principles/render/blending/index.md) альфа-канала.
### Возвращаемое значение

Исходная функция смешивания альфа-канала (одна из переменных [*BLEND_**](../../../api/library/rendering/class.renderstate_cpp.md#BLEND_NONE)).
## void setCastShadow ( bool shadow )

Включает или отключает опцию отбрасывания теней для объекта с применённым материалом.
### Аргументы

- *bool* **shadow** - true - чтобы включить отбрасывание теней; false - чтобы отключить его.

## bool isCastShadow ( ) const

Возвращает значение, указывающее, отбрасывает ли тени объект с применённым материалом.
### Возвращаемое значение

true, если отбрасывание теней включено; иначе false.
## void setCastWorldShadow ( bool shadow )

Включает или отключает отбрасывание теней от мирового источника света для объекта с применённым материалом.
### Аргументы

- *bool* **shadow** - true - чтобы включить отбрасывание теней от мирового источника света; false - чтобы отключить его.

## bool isCastWorldShadow ( ) const

Возвращает значение, указывающее, отбрасывает ли объект с применённым материалом тени от мирового источника света.
### Возвращаемое значение

true, если отбрасывание теней от мирового источника света включено; иначе false.
## Ptr < Material > getChild ( int num ) const

Возвращает дочерний материал с заданным номером.
### Аргументы

- *int* **num** - Номер дочернего материала.

### Возвращаемое значение

Умный указатель на дочерний материал.
## bool isDeferred ( ) const

Возвращает значение, указывающее, рендерится ли материал в отложенном проходе (deferred pass).
### Возвращаемое значение

true, если материал рендерится в отложенном проходе (непрозрачный); иначе false.
## void setDepthTest ( bool test )

Включает или отключает опцию проверки глубины (depth testing) для материала. Эта опция может использоваться для рендеринга определённых объектов, находящихся за другими объектами.
### Аргументы

- *bool* **test** - true - чтобы включить проверку глубины для материала; false - чтобы отключить её.

## bool isDepthTest ( ) const

Возвращает значение, указывающее, включена ли проверка глубины (depth testing) для материала. Эта опция может использоваться для рендеринга определённых объектов, находящихся за другими объектами.
### Возвращаемое значение

true, если проверка глубины для материала включена; иначе false.
## bool isEditable ( ) const

Возвращает значение, указывающее, можно ли редактировать материал.
### Возвращаемое значение

true, если материал редактируемый; иначе false.
## bool isForward ( ) const

Возвращает значение, указывающее, рендерится ли материал в прямом проходе (forward pass).
### Возвращаемое значение

true, если материал рендерится в прямом проходе (прозрачный, с функцией смешивания); иначе false.
## bool isHidden ( ) const

Возвращает значение, указывающее, скрыт ли материал.
### Возвращаемое значение

true, если материал скрыт; иначе false.
## void setShadowMask ( int mask )

Задаёт маску теней для материала.
Чтобы тень рендерилась для источника света от поверхности объекта с назначенным этим материалом, эта маска должна совпадать со следующими (хотя бы по одному биту):

- [Shadow mask of the light source](../../../api/library/lights/class.light_cpp.md#setShadowMask_int_void)
- [Shadow mask of the surface](../../../api/library/objects/class.object_cpp.md#setShadowMask_int_int_void) объекта с назначенным этим материалом

 Поверхность с назначенным материалом, освещённая источником света, отбрасывает тень, если маска теней источника света совпадает с соответствующими масками поверхности и её материала.
### Аргументы

- *int* **mask** - Целочисленное значение, каждый бит которого является маской.

## int getShadowMask ( ) const

Возвращает маску теней материала.
Чтобы тень рендерилась для источника света от поверхности объекта с назначенным этим материалом, эта маска должна совпадать со следующими (хотя бы по одному биту):

- [Shadow mask of the light source](../../../api/library/lights/class.light_cpp.md#setShadowMask_int_void)
- [Shadow mask of the surface](../../../api/library/objects/class.object_cpp.md#setShadowMask_int_int_void) объекта с назначенным этим материалом


### Возвращаемое значение

Целочисленное значение, каждый бит которого является маской.
## int getNumChildren ( ) const

Возвращает количество дочерних материалов.
### Возвращаемое значение

Количество дочерних материалов.
## int getNumParameters ( ) const

Возвращает количество параметров материала.
### Возвращаемое значение

Количество параметров материала.
## int getNumStates ( ) const

Возвращает количество состояний материала.
### Возвращаемое значение

Количество состояний материала.
## int getNumTextures ( ) const

Возвращает количество текстур, используемых материалом.
### Возвращаемое значение

Количество используемых текстур.
## void setOrder ( int order )

Задаёт порядок рендеринга материала. Чем выше порядок рендеринга, тем ниже приоритет рендеринга (материал с порядком -128 будет отрендерен первым).
### Аргументы

- *int* **order** - Порядок рендеринга, в диапазоне от -128 до 127.

## int getOrder ( ) const

Возвращает [rendering order](#setOrder_int_void) материалов.
### Возвращаемое значение

Порядок рендеринга, в диапазоне от -128 до 127.
## void setOrderClouds ( int clouds )

Задаёт порядок рендеринга прозрачных поверхностей относительно облаков. Действует только когда консольная переменная render_clouds_transparent_order задана равной 2 (Sort Transparent).
> **Notice:** Чтобы отрендерить прозрачную поверхность за облаками, для материала должна быть отключена опция [Depth Test](#isDepthTest_int), иначе поверхность будет отрендерена перед облаками независимо от значения OrderClouds.

### Аргументы

- *int* **clouds** - Порядок рендеринга прозрачных поверхностей относительно облаков. Одно из значений [*ORDER_CLOUDS_**](#ORDER_CLOUDS_DEFAULT).

## int getOrderClouds ( ) const

Возвращает порядок рендеринга прозрачных поверхностей относительно облаков.
### Возвращаемое значение

Порядок рендеринга прозрачных поверхностей относительно облаков. Одно из значений [*ORDER_CLOUDS_**](#ORDER_CLOUDS_DEFAULT).
## void setOverlap ( bool overlap )

Включает или отключает опцию overlap для материала. Эта опция позволяет рендерить материал поверх итогового изображения и может использоваться для элементов UI.
### Аргументы

- *bool* **overlap** - true - чтобы включить опцию overlap для материала; false - чтобы отключить её.

## bool isOverlap ( ) const

Возвращает значение, указывающее, включена ли опция overlap для материала. Эта опция позволяет рендерить материал поверх итогового изображения и может использоваться для элементов UI.
### Возвращаемое значение

true, если опция overlap для материала включена; иначе false.
## bool isParameterExpressionEnabled ( int num ) const

Возвращает значение, указывающее, представлено ли значение заданного параметра материала выражением на UnigineScript. Значения некоторых параметров могут вычисляться произвольным выражением, написанным на [UnigineScript](../../../code/uniginescript/index.md).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

true, если значение заданного параметра материала представлено выражением на UnigineScript; иначе false.
## void setParameterExpressionEnabled ( int num , bool enabled )

Задаёт значение, указывающее, представлено ли значение заданного параметра материала выражением на UnigineScript. Значения некоторых параметров могут вычисляться произвольным выражением, написанным на [UnigineScript](../../../code/uniginescript/index.md).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *bool* **enabled** - true - чтобы включить задание значения заданного параметра материала выражением на UnigineScript; false - чтобы отключить.

## bool isParameterOverridden ( int num ) const

Возвращает значение, указывающее, переопределён ли заданный параметр.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

true, если заданный параметр переопределён; иначе false.
## bool isParameterInt ( int num ) const

Возвращает значение, указывающее, является ли параметр с заданным номером параметром целочисленного типа.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

true, если параметр с заданным номером является [integer-type parameter](#PARAMETER_ARRAY_INT); иначе false.
## bool isParameterFloat ( int num ) const

Возвращает значение, указывающее, является ли параметр с заданным номером параметром типа float.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

true, если параметр с заданным номером является [float-type parameter](#PARAMETER_ARRAY_FLOAT); иначе false.
## float getParameterFloat ( const char * name ) const

Возвращает значение параметра типа float с заданным [name](#copy_name). Значение 0, возвращённое этим методом, не обязательно является значением параметра, так как 0 также будет возвращено, если **параметр с заданным именем не существует**. Чтобы проверить, существует ли параметр, используйте **[findParameter()](../../...md#findParameter_cstr_int)**. Также учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkParameterConditions()](../../...md#checkParameterConditions_int_int)**.
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение параметра типа float.
## Math:: vec2 getParameterFloat2 ( const char * name ) const

Возвращает значение параметра [*FLOAT2*](#PARAMETER_FLOAT2) с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение параметра как вектор [*vec2*](../../../api/library/math/class.vec2_cpp.md).
## Math:: vec3 getParameterFloat3 ( const char * name ) const

Возвращает значение параметра [*FLOAT3*](#PARAMETER_FLOAT3) с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение параметра как вектор [*vec3*](../../../api/library/math/class.vec3_cpp.md).
## Math:: vec4 getParameterFloat4 ( const char * name ) const

Возвращает значение параметра [*FLOAT4*](#PARAMETER_FLOAT4) с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение параметра как вектор [*vec4*](../../../api/library/math/class.vec4_cpp.md).
## int getParameterInt ( const char * name ) const

Возвращает значение целочисленного параметра с заданным [name](#copy_name). Значение 0, возвращённое этим методом, не обязательно является значением параметра, так как 0 также будет возвращено, если **параметр с заданным именем не существует**. Чтобы проверить, существует ли параметр, используйте **[findParameter()](../../...md#findParameter_cstr_int)**. Также учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkParameterConditions()](../../...md#checkParameterConditions_int_int)**.
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение целочисленного параметра.
## Math:: ivec2 getParameterInt2 ( const char * name ) const

Возвращает значение параметра [*INT2*](#PARAMETER_INT2) с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение параметра как вектор [*ivec2*](../../../api/library/math/class.ivec2_cpp.md).
## Math:: ivec3 getParameterInt3 ( const char * name ) const

Возвращает значение параметра [*INT3*](#PARAMETER_INT3) с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение параметра как вектор [*ivec3*](../../../api/library/math/class.ivec3_cpp.md).
## Math:: ivec4 getParameterInt4 ( const char * name ) const

Возвращает значение параметра [*INT4*](#PARAMETER_INT4) с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Значение параметра как вектор [*ivec4*](../../../api/library/math/class.ivec4_cpp.md).
## int getParameterArraySize ( int num ) const

Возвращает количество элементов в параметре-массиве с заданным номером.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Количество элементов заданного параметра-массива.
## bool isParameterArray ( int num ) const

Возвращает значение, указывающее, является ли параметр с заданным номером параметром типа массив, т.е. одним из следующих:
- [PARAMETER_ARRAY_FLOAT](#PARAMETER_ARRAY_FLOAT)
- [PARAMETER_ARRAY_FLOAT2](#PARAMETER_ARRAY_FLOAT2)
- [PARAMETER_ARRAY_FLOAT4](#PARAMETER_ARRAY_FLOAT4)
- [PARAMETER_ARRAY_INT](#PARAMETER_ARRAY_INT)
- [PARAMETER_ARRAY_INT2](#PARAMETER_ARRAY_INT2)
- [PARAMETER_ARRAY_INT4](#PARAMETER_ARRAY_INT4)


### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

true, если параметр является параметром типа массив; иначе false.
## void getParameterArray ( int num , Vector <float> & OUT_values ) const

Возвращает значение параметра-массива (тип: [*PARAMETER_ARRAY_FLOAT*](#PARAMETER_ARRAY_FLOAT)) с заданным номером и помещает его в заданный буферный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<float> &* **OUT_values** - Буферный массив для хранения значений параметра. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void setParameterArray ( int num , const Vector <float> & values )

Задаёт значение параметра-массива (тип: [*PARAMETER_ARRAY_FLOAT*](#PARAMETER_ARRAY_FLOAT)) с заданным номером, используя заданный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<float> &* **values** - Массив значений для задания.

## void getParameterArray ( int num , Vector < Math:: vec2 > & OUT_values ) const

Возвращает значение параметра-массива (тип: [*PARAMETER_ARRAY_FLOAT2*](#PARAMETER_ARRAY_FLOAT2)) с заданным номером и помещает его в заданный буферный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **OUT_values** - Буферный массив для хранения значений параметра. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void setParameterArray ( int num , const Vector < Math:: vec2 > & values )

Задаёт значение параметра-массива (тип: [*PARAMETER_ARRAY_FLOAT2*](#PARAMETER_ARRAY_FLOAT2)) с заданным номером, используя заданный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec2](../../../api/library/math/class.vec2_cpp.md)> &* **values** - Массив значений для задания.

## void getParameterArray ( int num , Vector < Math:: vec4 > & OUT_values ) const

Возвращает значение параметра-массива (тип: [*PARAMETER_ARRAY_FLOAT4*](#PARAMETER_ARRAY_FLOAT4)) с заданным номером и помещает его в заданный буферный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec4](../../../api/library/math/class.vec4_cpp.md)> &* **OUT_values** - Буферный массив для хранения значений параметра. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void setParameterArray ( int num , const Vector < Math:: vec4 > & values )

Задаёт значение параметра-массива (тип: [*PARAMETER_ARRAY_FLOAT4*](#PARAMETER_ARRAY_FLOAT4)) с заданным номером, используя заданный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[vec4](../../../api/library/math/class.vec4_cpp.md)> &* **values** - Массив значений для задания.

## void getParameterArray ( int num , Vector <int> & OUT_values ) const

Возвращает значение параметра-массива (тип: [*PARAMETER_ARRAY_INT*](#PARAMETER_ARRAY_INT)) с заданным номером и помещает его в заданный буферный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **OUT_values** - Буферный массив для хранения значений параметра. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void setParameterArray ( int num , const Vector <int> & values )

Задаёт значение параметра-массива (тип: [*PARAMETER_ARRAY_INT*](#PARAMETER_ARRAY_INT)) с заданным номером, используя заданный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int> &* **values** - Массив значений для задания.

## void getParameterArray ( int num , Vector < Math:: ivec2 > & OUT_values ) const

Возвращает значение параметра-массива (тип: [*PARAMETER_ARRAY_INT2*](#PARAMETER_ARRAY_INT2)) с заданным номером и помещает его в заданный буферный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)> &* **OUT_values** - Буферный массив для хранения значений параметра. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void setParameterArray ( int num , const Vector < Math:: ivec2 > & values )

Задаёт значение параметра-массива (тип: [*PARAMETER_ARRAY_INT2*](#PARAMETER_ARRAY_INT2)) с заданным номером, используя заданный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)> &* **values** - Массив значений для задания.

## void getParameterArray ( int num , Vector < Math:: ivec4 > & OUT_values ) const

Возвращает значение параметра-массива (тип: [*PARAMETER_ARRAY_INT4*](#PARAMETER_ARRAY_INT4)) с заданным номером и помещает его в заданный буферный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md)> &* **OUT_values** - Буферный массив для хранения значений параметра. > **Notice:** Этот выходной буфер заполняется движком в результате выполнения метода.

## void setParameterArray ( int num , const Vector < Math:: ivec4 > & values )

Задаёт значение параметра-массива (тип: [*PARAMETER_ARRAY_INT4*](#PARAMETER_ARRAY_INT4)) с заданным номером, используя заданный массив.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md)> &* **values** - Массив значений для задания.

## int setParameterExpression ( int num , const char * expression )

Задаёт выражение, используемое как значение параметра.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const char ** **expression** - Новое выражение.

### Возвращаемое значение

1, если выражение успешно задано; иначе 0.
## const char * getParameterExpression ( int num ) const

Возвращает выражение, используемое как значение параметра.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Выражение параметра, если оно существует; иначе **NULL** (**0**).
## const char * getParameterName ( int num ) const

Возвращает имя заданного параметра.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

[Parameter name](#copy_name).
## void setParameterFloat ( int num , float value )

Задаёт значение заданного [FLOAT](#PARAMETER_FLOAT) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *float* **value** - Значение параметра для задания.

## void setParameterFloat ( const char * name , float value )

Задаёт значение заданного [FLOAT](#PARAMETER_FLOAT) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа float.
- *float* **value** - Значение параметра для задания.

## float getParameterFloat ( int num ) const

Возвращает текущее значение заданного [FLOAT](#PARAMETER_FLOAT). Значение 0, возвращённое этим методом, не обязательно является значением параметра, так как 0 также будет возвращено, если **параметр с заданным номером не существует**. Чтобы проверить, существует ли параметр, используйте **[findParameter()](../../...md#findParameter_cstr_int)**. Также учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkParameterConditions()](../../...md#checkParameterConditions_int_int)**.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## void setParameterFloat2 ( int num , const Math:: vec2 & value )

Задаёт значение заданного [FLOAT2](#PARAMETER_FLOAT2) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Parameter value to be set.

## void setParameterFloat2 ( const char * name , const Math:: vec2 & value )

Задаёт значение заданного [FLOAT2](#PARAMETER_FLOAT2) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа float2.
- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md) &* **value** - Parameter value to be set.

## Math:: vec2 getParameterFloat2 ( int num ) const

Возвращает текущее значение заданного [FLOAT2](#PARAMETER_FLOAT2).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## void setParameterFloat3 ( int num , const Math:: vec3 & value )

Задаёт значение заданного [FLOAT3](#PARAMETER_FLOAT3) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Parameter value to be set.

## void setParameterFloat3 ( const char * name , const Math:: vec3 & value )

Задаёт значение заданного [FLOAT3](#PARAMETER_FLOAT3) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа float3.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **value** - Parameter value to be set.

## Math:: vec3 getParameterFloat3 ( int num ) const

Возвращает текущее значение заданного [FLOAT3](#PARAMETER_FLOAT3).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## void setParameterFloat4 ( int num , const Math:: vec4 & value )

Задаёт значение заданного [FLOAT4](#PARAMETER_FLOAT4) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Parameter value to be set.

## void setParameterFloat4 ( const char * name , const Math:: vec4 & value )

Задаёт значение заданного [FLOAT4](#PARAMETER_FLOAT4) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа float4.
- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **value** - Parameter value to be set.

## Math:: vec4 getParameterFloat4 ( int num ) const

Возвращает текущее значение заданного [FLOAT4](#PARAMETER_FLOAT4).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## void setParameterInt ( int num , int value )

Задаёт значение заданного [INT](#PARAMETER_INT) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *int* **value** - Значение параметра для задания.

## void setParameterInt ( const char * name , int value )

Задаёт значение заданного [INT](#PARAMETER_INT) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа int.
- *int* **value** - Значение параметра для задания.

## int getParameterInt ( int num ) const

Возвращает текущее значение заданного [INT](#PARAMETER_INT). Значение 0, возвращённое этим методом, не обязательно является значением параметра, так как 0 также будет возвращено, если **параметр с заданным номером не существует**. Чтобы проверить, существует ли параметр, используйте **[findParameter()](../../...md#findParameter_cstr_int)**. Также учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkParameterConditions()](../../...md#checkParameterConditions_int_int)**.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## void setParameterInt2 ( int num , const Math:: ivec2 & value )

Задаёт значение заданного [INT2](#PARAMETER_INT2) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Parameter value to be set.

## void setParameterInt2 ( const char * name , const Math:: ivec2 & value )

Задаёт значение заданного [INT2](#PARAMETER_INT2) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа int2.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **value** - Parameter value to be set.

## Math:: ivec2 getParameterInt2 ( int num ) const

Возвращает текущее значение заданного [INT2](#PARAMETER_INT2).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## void setParameterInt3 ( int num , const Math:: ivec3 & value )

Задаёт значение заданного [INT3](#PARAMETER_INT3) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Parameter value to be set.

## void setParameterInt3 ( const char * name , const Math:: ivec3 & value )

Задаёт значение заданного [INT3](#PARAMETER_INT3) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа int3.
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **value** - Parameter value to be set.

## Math:: ivec3 getParameterInt3 ( int num ) const

Возвращает текущее значение заданного [INT3](#PARAMETER_INT3).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## void setParameterInt4 ( int num , const Math:: ivec4 & value )

Задаёт значение заданного [INT4](#PARAMETER_INT4) по его номеру.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Parameter value to be set.

## void setParameterInt4 ( const char * name , const Math:: ivec4 & value )

Задаёт значение заданного [INT4](#PARAMETER_INT4) по его имени.
### Аргументы

- *const char ** **name** - Имя целевого параметра типа int4.
- *const  Math::[ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **value** - Parameter value to be set.

## Math:: ivec4 getParameterInt4 ( int num ) const

Возвращает текущее значение заданного [INT4](#PARAMETER_INT4).
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Текущее значение параметра.
## int getParameterType ( int num ) const

Возвращает тип заданного параметра.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

### Возвращаемое значение

Одна из предопределённых переменных [*PARAMETER_**](#PARAMETER_FLOAT) или **-1**, если произошла ошибка.
## Ptr < Material > getParent ( ) const

Возвращает родительский материал.
### Возвращаемое значение

Родительский материал, или **NULL** (**0**), если у текущего материала нет родителя.
## bool isParent ( const UGUID & guid ) const

Возвращает значение, указывающее, является ли материал с заданным GUID родителем текущего материала.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID материала.

### Возвращаемое значение

true, если материал является родителем; иначе false.
## bool isStateInternal ( int num ) const

Возвращает значение, указывающее, является ли заданное состояние внутренним.
### Аргументы

- *int* **num** - Номер состояния.

### Возвращаемое значение

true, если заданное состояние внутреннее; иначе false.
## bool isStateOverridden ( int num ) const

Возвращает значение, указывающее, переопределено ли заданное состояние.
### Аргументы

- *int* **num** - Номер состояния.

### Возвращаемое значение

true, если заданное состояние переопределено; иначе false.
## void setState ( int num , int value )

Задаёт значение состояния.
### Аргументы

- *int* **num** - Номер состояния.
- *int* **value** - Значение состояния для задания.

## void setState ( const char * name , int value )

Задаёт значение заданного состояния.
### Аргументы

- *const char ** **name** - Имя состояния.
- *int* **value** - Значение состояния.

## int getState ( int num ) const

Возвращает значение состояния. Значение 0, возвращённое этим методом, не обязательно является значением состояния, так как 0 также будет возвращено, если **состояние с заданным номером не существует**. Чтобы проверить, существует ли состояние, используйте **[findState()](../../...md#findState_cstr_int)**. Также учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkStateConditions()](../../...md#checkStateConditions_int_int)**.
### Аргументы

- *int* **num** - Номер состояния.

### Возвращаемое значение

Значение состояния.
## int getState ( const char * name ) const

Возвращает значение заданного состояния. Значение 0, возвращённое этим методом, не обязательно является значением состояния, так как 0 также будет возвращено, если **состояние с заданным именем не существует**. Чтобы проверить, существует ли состояние, используйте **[findState()](../../...md#findState_cstr_int)**. Также учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkStateConditions()](../../...md#checkStateConditions_int_int)**.
### Аргументы

- *const char ** **name** - Имя состояния.

### Возвращаемое значение

Значение состояния.
## const char * getStateName ( int num ) const

Возвращает имя заданного состояния.
### Аргументы

- *int* **num** - Номер состояния.

### Возвращаемое значение

Имя состояния.
## const char * getStateSwitchItem ( int num , int item ) const

Возвращает имя элемента переключателя для заданного состояния.
### Аргументы

- *int* **num** - Номер состояния.
- *int* **item** - Номер элемента.

### Возвращаемое значение

Имя элемента переключателя, или **NULL** (**0**), если произошла ошибка.
## int getStateSwitchNumItems ( int num ) const

Возвращает количество элементов переключателя для заданного состояния.
### Аргументы

- *int* **num** - Номер состояния.

### Возвращаемое значение

Количество элементов переключателя.
## int getStateType ( int num ) const

Возвращает тип заданного состояния.
### Аргументы

- *int* **num** - Номер состояния.

### Возвращаемое значение

Одна из предопределённых переменных [*MATERIAL_STATE_**](#STATE_INT) или **-1**, если произошла ошибка.
## bool isTextureInternal ( int num ) const

Возвращает значение, указывающее, является ли заданная текстура внутренней.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

true, если заданная текстура внутренняя; иначе false.
## bool isTextureOverridden ( int num ) const

Возвращает значение, указывающее, переопределена ли заданная текстура.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

true, если заданная текстура переопределена; иначе false.
## bool isTextureLoaded ( int num ) const

Возвращает значение, указывающее, загружена ли заданная текстура.
### Аргументы

- *int* **num**

### Возвращаемое значение

true, если заданная текстура загружена; иначе false.
## const char * getTextureName ( int num ) const

Возвращает имя заданной текстуры.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Имя текстуры.
## int getTextureUnit ( int num ) const

Возвращает номер юнита заданной текстуры, используемого в шейдерах.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Номер юнита текстуры.
## bool isTextureEditable ( int num ) const

Возвращает значение, указывающее, редактируема ли текстура с заданным номером (может ли быть изменена).
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

true, если текстура с заданным номером редактируема; иначе false (текстура доступна только для чтения).
## int getTextureSource ( int num ) const

Возвращает источник для текстуры с заданным номером.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Одна из предопределённых переменных **[TEXTURE_SOURCE_*](../../...md#TEXTURE_SOURCE_AUXILIARY)** или **-1**, если произошла ошибка.
## Ptr < Texture > getTexture ( const char * name )

Возвращает текстуру, используемую в материале, по её имени. Учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkTextureConditions()](../../...md#checkTextureConditions_int_int)**.
### Аргументы

- *const char ** **name** - Имя нужной текстуры (например, albedo, emission и т.д.).

### Возвращаемое значение

Текстура с заданным именем, если она существует; иначе *nullptr*.
## void setTransparent ( int transparent )

Задаёт значение, определяющее тип прозрачности материала. Если опция transparent задана равной *TRANSPARENT_NONE* или *TRANSPARENT_DEFERRED*, функции смешивания *[setBlendSrcFunc()](../../../api/library/rendering/class.material_cpp.md#setBlendSrcFunc_int_void)* и *[setBlendDestFunc()](../../../api/library/rendering/class.material_cpp.md#setBlendDestFunc_int_void)* использоваться не будут.
### Аргументы

- *int* **transparent** - Опция прозрачности (одна из переменных *[TRANSPARENT_*](#TRANSPARENT_ALPHA_TEST)*).

## int getTransparent ( ) const

Возвращает значение, определяющее тип прозрачности материала.
### Возвращаемое значение

Одна из переменных [*TRANSPARENT_**](#TRANSPARENT_ALPHA_TEST).
## void setTwoSided ( bool sided )

Включает или отключает опцию двусторонности (two sided) для материала.
### Аргументы

- *bool* **sided** - true - сделать материал двусторонним; false - сделать его односторонним.

## bool isTwoSided ( ) const

Возвращает значение, указывающее, является ли материал двусторонним.
### Возвращаемое значение

true, если материал двусторонний; иначе false.
## void setViewportMask ( int mask )

Задаёт битовую маску для рендеринга в viewport. Материал рендерится, если его маска совпадает с маской игрока.
### Аргументы

- *int* **mask** - Целое число, каждый бит которого является маской.

## int getViewportMask ( ) const

Возвращает текущую битовую маску для рендеринга в viewport. Материал рендерится, если его маска совпадает с маской игрока.
### Возвращаемое значение

Целое число, каждый бит которого является маской.
## bool isWater ( ) const

Возвращает значение, указывающее, рендерится ли материал в проходе воды (water pass).
### Возвращаемое значение

true, если материал рендерится в проходе воды; иначе false.
## int findParameter ( const char * name ) const

Ищет параметр по заданному [name](#copy_name) среди всех параметров текущего материала.
### Аргументы

- *const char ** **name** - [Parameter name](#copy_name).

### Возвращаемое значение

Номер параметра, если он найден; иначе **-1**.
## int findState ( const char * name ) const

Ищет состояние по заданному имени среди всех состояний текущего материала.
### Аргументы

- *const char ** **name** - Имя состояния.

### Возвращаемое значение

Номер состояния, если оно найдено; иначе **-1**.
## int findTexture ( const char * name ) const

Ищет текстуру по заданному [name](#copy_name) среди всех текстур, используемых текущим материалом.
### Аргументы

- *const char ** **name** - [Texture name](#copy_name).

### Возвращаемое значение

Номер текстуры, если она найдена; иначе **-1**.
## bool saveState ( const Ptr < Stream > & stream , bool forced = 0 ) const

Сохраняет настройки заданного материала (все его опции, состояния и параметры) в бинарный поток.
Для сохранения в поток требуется создать blob для сохранения. Для восстановления сохранённого состояния используется метод [restoreState()](#restoreState_Stream_int_int):


```cpp
// инициализируем объект
MaterialPtr mat = object->getMaterial(0);
mat->setViewportMask(1); // маска viewport = 1

// сохраняем состояние
BlobPtr blob_state = Blob::create();
mat->saveState(blob_state, true);

// меняем что-нибудь
mat->setViewportMask(~0);  // теперь маска viewport = 111111111

// восстанавливаем состояние
blob_state->seekSet(0);		// возвращаем каретку в начало blob
mat->restoreState(blob_state, true);  // восстанавливаем маску viewport = 1

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.
- *bool* **forced** - Принудительное сохранение настроек материала.

### Возвращаемое значение

true, если настройки материала успешно сохранены; иначе true.
## bool restoreState ( const Ptr < Stream > & stream , bool forced = 0 )

Восстанавливает состояние заданного материала (все его опции, состояния и параметры) из бинарного потока.
Для восстановления из потока требуется создать blob для сохранения и сохранить состояние с помощью метода [saveState()](#saveState_Stream_int_int):


```cpp
// инициализируем объект
MaterialPtr mat = object->getMaterial(0);
mat->setViewportMask(1); // маска viewport = 1

// сохраняем состояние
BlobPtr blob_state = Blob::create();
mat->saveState(blob_state, true);

// меняем что-нибудь
mat->setViewportMask(~0);  // теперь маска viewport = 111111111

// восстанавливаем состояние
blob_state->seekSet(0);		// возвращаем каретку в начало blob
mat->restoreState(blob_state, true);  // восстанавливаем маску viewport = 1

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.
- *bool* **forced** - Принудительное восстановление настроек материала.

### Возвращаемое значение

true, если настройки материала успешно восстановлены; иначе false.
## bool canRenderNode ( ) const

Возвращает значение, указывающее, может ли материал рендериться хотя бы для одного [type](../../../api/library/nodes/class.node_cpp.md#DECAL_MESH) узлов.
### Возвращаемое значение

true, если материал рендерится хотя бы для одного типа узлов; иначе false.
## void resetState ( int num )

Сбрасывает [overridden](#isStateOverridden_int_int) значение заданного состояния к родительскому.
### Аргументы

- *int* **num** - Номер состояния.

## void setTexturePath ( int num , const char * path )

Задаёт новый путь к текстуре с заданным номером.
### Аргументы

- *int* **num** - Номер текстуры.
- *const char ** **path** - Путь к текстуре, или **NULL**, чтобы очистить путь.

## void setTexturePath ( const char * name , const char * path )

Задаёт новый путь к текстуре с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Texture name](#copy_name).
- *const char ** **path** - Путь к текстуре, или **NULL**, чтобы очистить путь.

## void resetTexture ( int num )

Сбрасывает [overridden](#isTextureOverridden_int_int) значение заданной текстуры к родительской.
### Аргументы

- *int* **num** - Номер текстуры.

## const char * getTexturePath ( int num ) const

Возвращает путь к текстуре с заданным номером.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Путь к текстуре.
## const char * getTexturePath ( const char * name ) const

Возвращает путь к текстуре с заданным [name](#copy_name).
### Аргументы

- *const char ** **name** - [Texture name](#copy_name).

### Возвращаемое значение

Путь к текстуре.
## bool isNodeTypeSupported ( Node::TYPE type ) const

Возвращает значение, указывающее, поддерживается ли материалом заданный тип узлов.
### Аргументы

- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **type** - Тип узла: одна из переменных *[OBJECT_*](../../../api/library/nodes/class.node_cpp.md#OBJECT_BILLBOARDS)* или *[DECAL_*](../../../api/library/nodes/class.node_cpp.md#DECAL_MESH)*.

### Возвращаемое значение

true, если тип узла поддерживается; иначе false.
## bool setParent ( const Ptr < Material > & material , bool save_all_values = 1 )

Задаёт заданный материал в качестве родителя для этого материала и сохраняет значения свойств материала (если задан соответствующий флаг).
> **Notice:** Метод недоступен для [manual](#isManual_int) и [base](#isBase_int) материалов.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **material** - Материал, который будет задан родителем для этого материала.
- *bool* **save_all_values** - Флаг, указывающий, будут ли сохранены свойства материала после смены родителя.

### Возвращаемое значение

true, если родитель материала изменён; иначе false.
## bool checkTextureConditions ( int num ) const

Проверяет, выполнены ли [conditions](../../../code/formats/materials_formats/ulon_materials/conditions.md), заданные для заданной текстуры.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

true, если условия выполнены; иначе false.
## bool isInternal ( ) const

Возвращает значение, указывающее, является ли текущий материал [internal](../../../content/materials/index.md#manual_internal_materials).
### Возвращаемое значение

true, если материал внутренний; иначе false.
## int loadXml ( const Ptr < Xml > & xml )

Загружает настройки материала из заданного источника Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Узел Xml, содержащий настройки материала.

### Возвращаемое значение

true, если настройки материала успешно загружены; иначе false.
## bool loadUlon ( const Ptr < UlonNode > & ulon )

Загружает настройки материала из заданного источника [ULON](../../../code/formats/ulon_format.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[UlonNode](../../../api/library/common/class.ulonnode_cpp.md)> &* **ulon** - ULON-узел, содержащий настройки материала.

### Возвращаемое значение

true, если настройки материала успешно загружены; иначе false.
## bool hasOverrides ( ) const

Возвращает значение, указывающее, есть ли у материала хотя бы одно переопределённое свойство.
### Возвращаемое значение

true, если у материала есть хотя бы одно переопределённое свойство; иначе false.
## bool canSave ( ) const

Возвращает значение, указывающее, можно ли сохранить материал. Например, эта функция вернёт 0 для базового или ручного материала.
### Возвращаемое значение

true, если материал можно сохранить; иначе false.
## bool checkStateConditions ( int num ) const

Проверяет, выполнены ли [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), заданные для заданного состояния.
### Аргументы

- *int* **num** - Номер состояния.

### Возвращаемое значение

true, если условия выполнены; иначе false.
## bool isManual ( ) const

Возвращает значение, указывающее, является ли текущий материал [manual](../../../content/materials/index.md#manual_internal_materials).
### Возвращаемое значение

true, если материал ручной; иначе false.
## bool isAutoSave ( ) const

Возвращает значение, указывающее, может ли материал сохраняться автоматически (автоматическое сохранение материала выполняется, например, при сохранении мира). Функция вернёт 0 в следующих случаях:
- Функция *[canSave()](#canSave_int)* возвращает для материала 0.
- Материал [non-editable](#isEditable_int).
- [GUID](../../../api/library/filesystem/class.uguid_cpp.md) материала недействителен.


### Возвращаемое значение

true, если материал может сохраняться автоматически; иначе false.
## bool isLegacy ( ) const

Возвращает значение, указывающее, является ли материал устаревшим (legacy). Устаревший материал - это не-ULON [base material](../../../content/materials/index.md#base_materials), описанный в XML-файле.
### Возвращаемое значение

true, если материал устаревший; иначе false.
## bool isPreviewHidden ( ) const

Возвращает значение, указывающее, отключён ли предпросмотр в UnigineEditor для материала. Этот метод используется для пользовательских материалов (например, кистей ландшафта terrain).
### Возвращаемое значение

true, если предпросмотр в UnigineEditor отключён для материала; иначе false.
## bool checkParameterConditions ( int num ) const

Проверяет, выполнены ли [conditions](../../../code/formats/materials_formats/ulon_materials/parameters.md), заданные для заданного параметра.
### Аргументы

- *int* **num** - [Parameter name](#copy_name).

### Возвращаемое значение

true, если условия выполнены; иначе false.
## bool save ( )

Сохраняет материал по [current path](#getFilePath_String), используемому для этого материала.
> **Notice:** Метод недоступен для [manual](#isManual_int) и [base](#isBase_int) материалов.


### Возвращаемое значение

true, если материал успешно сохранён; иначе false.
## bool load ( const char * path )

Загружает материал из заданного файла. Функция может использоваться для загрузки материалов, созданных во время работы приложения, или хранящихся вне директории `data`.
### Аргументы

- *const char ** **path** - Путь к файлу материала.

### Возвращаемое значение

true, если материал успешно загружен; иначе false.
## bool saveXml ( const Ptr < Xml > & xml ) const

Сохраняет материал в заданный Xml.
> **Notice:** Метод недоступен для [manual](#isManual_int) и [base](#isBase_int) материалов.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Узел Xml.

### Возвращаемое значение

true, если материал успешно сохранён; иначе **false**.
## bool isBase ( ) const

Возвращает значение, указывающее, является ли материал [base](../../../content/materials/index.md#base_materials).
### Возвращаемое значение

true, если материал базовый; иначе false.
## bool isNodeSupported ( const Ptr < Node > & node ) const

Возвращает значение, указывающее, можно ли применить материал к заданному узлу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел.

### Возвращаемое значение

true, если заданный узел поддерживается; иначе false.
## Ptr < Material > getBaseMaterial ( ) const

Возвращает базовый материал текущего материала.
### Возвращаемое значение

Базовый материал.
## void setTexture ( int num , const Ptr < Texture > & texture )

Задаёт заданную текстуру для текстуры с заданным номером.
> **Notice:** Этот метод только задаёт указатель на текстуру, поэтому учитывайте область видимости исходного указателя на текстуру.


### Аргументы

- *int* **num** - Номер текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Текстура для задания.

## void setTexture ( const char * name , const Ptr < Texture > & texture )

Задаёт заданную текстуру для слота текстуры с заданным [name](#copy_name).
> **Notice:** Этот метод только задаёт указатель на текстуру, поэтому учитывайте область видимости исходного указателя на текстуру.


### Аргументы

- *const char ** **name** - [Texture name](#copy_name) (одна из текстур, используемых материалом, например: *albedo*).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Текстура для задания.

## Ptr < Texture > getTexture ( int num )

Возвращает текстуру, заданную для текущего материала. Учитывайте, что состояния, параметры и текстуры могут игнорироваться, если [conditions](../../../code/formats/materials_formats/ulon_materials/states.md), от которых они зависят, не выполнены. Чтобы проверить условия, вызовите **[checkTextureConditions()](../../...md#checkTextureConditions_int_int)**.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Текстура с заданным номером, если она существует; иначе *nullptr*.
## String getFilePath ( ) const

Возвращает путь к текущему файлу материала.
### Возвращаемое значение

Путь к материалу.
## UGUID getFileGUID ( ) const

Возвращает GUID текущего файла материала.
### Возвращаемое значение

GUID текущего файла материала.
## void resetParameter ( int num )

Сбрасывает [overridden](#isParameterOverridden_int_int) значение заданного параметра к родительскому.
### Аргументы

- *int* **num** - Номер параметра в диапазоне от 0 до [total number of parameters](#getNumParameters_int).

## bool reload ( )

Перезагружает материал и все его дочерние материалы.
### Возвращаемое значение

true, если материал успешно перезагружен; иначе false.
## int setTextureImage ( int num , const Ptr < Image > & image )

Задаёт заданное [image](../../../api/library/common/class.image_cpp.md) для заданной текстуры.
### Аргументы

- *int* **num** - Номер текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Изображение для задания.

### Возвращаемое значение

1, если изображение успешно задано; иначе 0.
## int getTextureImage ( int num , const Ptr < Image > & image ) const

Считывает заданную текстуру в заданное изображение.
### Аргументы

- *int* **num** - Номер текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Изображение.

### Возвращаемое значение

1, если текстура успешно считана; иначе 0.
## Ptr < TextureRamp > getTextureRamp ( int num )

Возвращает экземпляр [ramp texture](../../../api/library/rendering/class.textureramp_cpp.md) для данных, хранящихся в заданной ramp-текстуре (градиенте).
> **Notice:** Изменения, внесённые в ramp, распространяются на родительский и родственные материалы. Чтобы изменить переопределённый ramp только для этого материала, используйте метод [*getTextureRampOverride()*](#getTextureRampOverride_int_TextureRamp).


### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Экземпляр класса [TextureRamp](../../../api/library/rendering/class.textureramp_cpp.md) для данных, хранящихся в градиентной текстуре с заданным номером.
## Ptr < TextureRamp > getTextureRampOverride ( int num )

Возвращает новый экземпляр [ramp texture](../../../api/library/rendering/class.textureramp_cpp.md) для данных, хранящихся в заданной ramp-текстуре (градиенте), переопределяющий текстуру по умолчанию. Этот метод позволяет задавать отдельные RGBA-кривые, настраивая значения цвета результирующей ramp-текстуры (градиента).
> **Notice:** Изменения, внесённые в ramp, не распространяются на родительский и родственные материалы.


### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Новый экземпляр класса [TextureRamp](../../../api/library/rendering/class.textureramp_cpp.md), переопределяющий данные, хранящиеся в заданной ramp-текстуре (градиенте).
## UGUID getGUID ( ) const

Возвращает [GUID](../../../content/materials/inheritance.md#material_guid) материала.
### Возвращаемое значение

GUID материала.
## bool isFileEngine ( ) const

Возвращает значение, указывающее, является ли материал материалом ядра движка или UnigineEditor (т.е. необходимым для работы движка/редактора). Такие материалы хранятся в папках/пакетах `core`, `editor` и `editor2`.
> **Notice:** Не рекомендуется удалять файлы материалов, не относящихся к ядру (например, созданных плагинами или иным образом), во время выполнения, так как это может повлиять на кэширование материалов и привести к сбою.

### Возвращаемое значение

true, если материал является материалом ядра движка или UnigineEditor; иначе false.
## void createShaders ( bool recursive = 0 )

Создаёт все шейдеры для текущего материала и его дочерних материалов (если указано).
### Аргументы

- *bool* **recursive** - true - создать шейдеры для дочерних материалов текущего материала; иначе false.

## void destroyTextures ( )

Удаляет все текстуры, используемые текущим материалом и его дочерними материалами.
## bool isEmpty ( ) const

Возвращает значение, указывающее, используется ли пустой шейдер в качестве вершинного шейдера в текущем материале.
### Возвращаемое значение

true, если используется пустой вершинный шейдер; иначе false.
## Render::PASS getRenderPass ( const char * pass_name ) const

Возвращает тип прохода рендеринга по его имени (включая пользовательские проходы).
### Аргументы

- *const char ** **pass_name** - Имя прохода рендеринга.

### Возвращаемое значение

Номер прохода рендеринга в диапазоне от 0 до 18 + custom_passes_number, если он существует; иначе -1.
## const char * getRenderPassName ( Render::PASS type ) const

Возвращает имя прохода рендеринга по его номеру (включая пользовательские проходы).
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **type** - Номер прохода рендеринга в диапазоне [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (одна из переменных *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)*).

### Возвращаемое значение

Имя прохода рендеринга, если оно существует; иначе nullptr.
## bool runExpression ( const char * name , int w , int h , int d = 1 )

Запускает выражение материала с заданным именем. Выражение - это ссылка на файл, содержащий код на UnigineScript, который может генерировать различные элементы, используемые в материале (например, текстуры, массивы текстур, неструктурированные буферы и т.д.) или содержать другую логику. Выражения могут быть определены в [`*.basemat` file](../../../code/formats/materials_formats/ulon_base_material_format.md) следующим образом:
```cpp
Expression name = "expression.usc";

```


Пример кода *expression.usc*:


```cpp
// типичные наиболее часто используемые параметры, автоматически передаваемые выражению при его вызове.
int in_width;
int in_height;
int in_depth;
Material in_material;

// если вам нужны дополнительные параметры, задайте их через Material::setParameter*("param_name", value) перед вызовом Material::runExpression()
// затем вы можете получить к ним доступ в выражении через in_material.getParameter*("param_name")

// ...

// получаем временную текстуру
Texture texture = engine.render.getTemporaryTexture(in_width, in_height);

// получаем значение параметра материала с именем "my_extra_param"
float my_param = in_material.getParameter("my_extra_param");

// как-то изменяем временную текстуру, используя параметр my_param...

// задаём изменённую текстуру как текстуру альбедо материала
in_material->setTexture("albedo", texture);

```


Для выполнения этого выражения можно использовать следующий код:

```cpp
// ...
// задаём значение дополнительного параметра
material->setParameterFloat("my_extra_param", 2.5f);

// запускаем выражение
material->runExpression("expr_name", 512, 512, 1);
// ...

```


> **Notice:** Выражения могут выполняться только для [base materials](../../../content/materials/index.md#base_materials).


### Аргументы

- *const char ** **name** - Имя выражения. [Expression](../../../code/formats/materials_formats/ulon_materials/expressions.md) с этим именем должно быть определено в объявлении материала (файл `*.basemat`).
- *int* **w** - Ширина, например, если выражением генерируется текстура или структурированный буфер.
- *int* **h** - Высота, например, если выражением генерируется текстура или структурированный буфер.
- *int* **d** - Глубина, например, если выражением генерируется 3D-текстура, 2D-массив или структурированный буфер.

### Возвращаемое значение

true, если заданное выражение успешно выполнено; иначе false.
## bool renderScreen ( const char * pass_name )

Рендерит материал в экранном пространстве (screen-space). У материала должен быть шейдер, назначенный для заданного прохода.
### Аргументы

- *const char ** **pass_name** - Имя прохода рендеринга.

### Возвращаемое значение

false, если заданный проход не найден; иначе true.
## void renderScreen ( Render::PASS pass )

Рендерит материал в экранном пространстве (screen-space). У материала должен быть шейдер, назначенный для заданного прохода.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).

## bool renderCompute ( const char * pass_name , int group_threads_x = 1 , int group_threads_y = 1 , int group_threads_z = 1 )

Рендерит материал с использованием compute-шейдера. У материала должен быть compute-шейдер, назначенный для заданного прохода.
### Аргументы

- *const char ** **pass_name** - Имя прохода рендеринга.
- *int* **group_threads_x** - Локальный размер рабочей группы compute-шейдера по X.
- *int* **group_threads_y** - Локальный размер рабочей группы compute-шейдера по Y.
- *int* **group_threads_z** - Локальный размер рабочей группы compute-шейдера по Z.

### Возвращаемое значение

false, если заданный проход не найден; иначе true.
## void renderCompute ( Render::PASS pass , int group_threads_x = 1 , int group_threads_y = 1 , int group_threads_z = 1 )

Рендерит материал с использованием compute-шейдера. У материала должен быть compute-шейдер, назначенный для заданного прохода.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).
- *int* **group_threads_x** - Локальный размер рабочей группы compute-шейдера по X.
- *int* **group_threads_y** - Локальный размер рабочей группы compute-шейдера по Y.
- *int* **group_threads_z** - Локальный размер рабочей группы compute-шейдера по Z.

## int getNumUIItems ( ) const

Возвращает количество элементов UI. Элементы UI представляют параметры, опции, состояния, текстуры и группы материала в UnigineEditor.
### Возвращаемое значение

Общее количество элементов UI, доступных в UnigineEditor для материала.
## Material::DATA_TYPE getUIItemDataType ( int item ) const

Возвращает тип данных заданного элемента UI. Элементы UI представляют параметры, опции, состояния, текстуры и группы материала в UnigineEditor.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Тип данных элемента UI (параметр, опция, состояние, текстура или группа).
## int getUIItemDataID ( int item ) const

Возвращает id типа данных, управляемого заданным элементом UI. Элементы UI представляют параметры, опции, состояния, текстуры и группы материала в UnigineEditor.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Id данных элемента UI: одна из предопределённых переменных *[STATE_*](#STATE_INT)*, *[PARAMETER_*](#PARAMETER_INT)*, *[OPTION_*](#OPTION_TRANSPARENT)*, *[TEXTURE_SOURCE_*](#TEXTURE_SOURCE_ASSET)* или -1, если произошла ошибка.
## bool isUIItemHidden ( int item ) const

Возвращает значение, указывающее, скрыт ли заданный элемент UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

true, если заданный элемент UI скрыт; иначе false.
## const char * getUIItemTitle ( int item ) const

Возвращает заголовок, заданный для указанного элемента UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Заголовок, заданный для указанного элемента UI.
## const char * getUIItemTooltip ( int item ) const

Возвращает текст всплывающей подсказки, заданной для указанного элемента UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Текст всплывающей подсказки, заданной для указанного элемента UI.
## Material::WIDGET getUIItemWidget ( int item ) const

Возвращает тип виджета для указанного элемента UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Тип виджета элемента UI.
## int getUIItemParent ( int item ) const

Возвращает индекс родителя указанного элемента UI. Этот метод используется для получения индекса группы, к которой принадлежит заданный параметр/состояние/опция/текстура.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Глобальный индекс родительского элемента UI в диапазоне от 0 до [total number of UI items for the material](#getNumUIItems_int).
## int getUIItemNumChildren ( int item ) const

Возвращает количество дочерних элементов для группового элемента UI с заданным номером.
> **Notice:** Этот метод предназначен только для групп элементов UI ([DATA_TYPE_GROUP](#DATA_TYPE_GROUP)), другие элементы не могут иметь дочерних элементов!


### Аргументы

- *int* **item** - Индекс группы элементов UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Количество дочерних элементов заданного группового элемента UI.
## int getUIItemChild ( int item , int num ) const

Возвращает индекс дочернего элемента UI, принадлежащего заданной группе, по номеру элемента внутри группы.
> **Notice:** Этот метод предназначен только для групп элементов UI ([DATA_TYPE_GROUP](#DATA_TYPE_GROUP)), другие элементы не могут иметь дочерних элементов!


### Аргументы

- *int* **item** - Индекс группы элементов UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).
- *int* **num** - Номер элемента UI внутри группы (в списке дочерних элементов).

### Возвращаемое значение

Глобальный индекс дочернего элемента UI в диапазоне от 0 до [total number of UI items for the material](#getNumUIItems_int).
## bool isUIItemSliderMinExpand ( int item ) const

Возвращает значение, указывающее, может ли быть увеличено максимальное значение слайдера для заданного элемента UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

true, если максимальное значение может быть увеличено; иначе false.
## bool isUIItemSliderMaxExpand ( int item ) const

Возвращает значение, указывающее, может ли быть уменьшено минимальное значение слайдера для заданного элемента UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

true, если минимальное значение может быть уменьшено; иначе false.
## float getUIItemSliderMinValue ( int item ) const

Возвращает минимальное допустимое значение слайдера для заданного элемента UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Минимальное значение слайдера.
## float getUIItemSliderMaxValue ( int item ) const

Возвращает максимальное допустимое значение слайдера для заданного элемента UI.
### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Максимальное значение слайдера.
## int getUIItemGroupToggleStateID ( int item ) const

Возвращает глобальный индекс элемента UI переключателя состояния, включающего и выключающего заданную группу.
> **Notice:** Этот метод предназначен только для групп элементов UI ([DATA_TYPE_GROUP](#DATA_TYPE_GROUP))!


### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

Глобальный индекс элемента UI переключателя состояния в диапазоне от 0 до [total number of UI items for the material](#getNumUIItems_int).
## bool isUIItemGroupCollapsed ( int item ) const

Возвращает значение, указывающее, свёрнута ли в данный момент заданная группа элементов UI в интерфейсе Unigine Editor.
> **Notice:** Этот метод предназначен только для групп элементов UI ([DATA_TYPE_GROUP](#DATA_TYPE_GROUP))!


### Аргументы

- *int* **item** - Индекс элемента UI в диапазоне от 0 до [total number of UI items](#getNumUIItems_int).

### Возвращаемое значение

true, если заданная группа элементов UI в данный момент свёрнута в интерфейсе; иначе false (группа развёрнута).
## void setOption ( int num , int value )

Задаёт новое значение для заданной опции.
### Аргументы

- *int* **num** - Номер опции.
- *int* **value** - Новое значение для задания заданной опции.

## int getOption ( int num ) const

Возвращает текущее значение заданной опции.
### Аргументы

- *int* **num** - Номер опции.

### Возвращаемое значение

Текущее значение заданной опции.
## bool isOptionOverridden ( int num ) const

Возвращает значение, указывающее, переопределена ли заданная опция.
### Аргументы

- *int* **num** - Номер опции.

### Возвращаемое значение

true, если заданная опция переопределена; иначе false.
## void resetOption ( int num )

Сбрасывает [overridden](#isOptionOverridden_int_int) значение заданной опции к родительскому.
### Аргументы

- *int* **num** - Номер опции.

## bool isParent ( const Ptr < Material > & parent ) const

Возвращает значение, указывающее, является ли заданный материал родителем текущего материала.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &* **parent** - Умный указатель на материал.

### Возвращаемое значение

true, если материал является родителем; иначе false.
## Ptr < Material > clone ( ) const

Клонирует материал. Клонированный материал будет пустым: у него будет GUID, но он не будет отображаться в иерархии материалов.
### Возвращаемое значение

Клонированный материал.
## Ptr < Material > clone ( const UGUID & guid ) const

Клонирует материал и назначает ему заданный GUID.
> **Notice:** [base material](../../../content/materials/index.md#base_materials) не может быть клонирован.

### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID клонированного материала.

### Возвращаемое значение

Клонированный материал.
## Ptr < Material > inherit ( )

Наследует материал. Унаследованный материал будет пустым: у него будет GUID, но он не будет отображаться в иерархии материалов.
### Возвращаемое значение

Унаследованный материал.
## Ptr < Material > inherit ( const UGUID & guid )

Наследует новый материал от текущего и назначает ему заданный GUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID унаследованного материала.

### Возвращаемое значение

Унаследованный материал.
## const char * getNamespaceName ( ) const

Возвращает пространство имён, в котором определён этот материал.
### Возвращаемое значение

Пространство имён материала.
## const char * getManualName ( ) const

Возвращает имя ручного (manual) материала.
### Возвращаемое значение

Имя ручного материала.
## const char * widgetToString ( Material::WIDGET widget )

Возвращает имя виджета по его типу.
### Аргументы

- *[Material::WIDGET](../../../api/library/rendering/class.material_cpp.md#WIDGET)* **widget** - [Widget type](#WIDGET).

### Возвращаемое значение

Имя виджета.
## Material::WIDGET stringToWidget ( const char * str )

Возвращает тип виджета по его имени.
### Аргументы

- *const char ** **str** - Имя виджета.

### Возвращаемое значение

[Widget type](#WIDGET).
## int getTextureSamplerFlags ( int num ) const

Возвращает флаги сэмплера текстуры с заданным номером.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Флаги сэмплера текстуры.
## void setTextureSamplerFlags ( int num , int sampler_flags )

Задаёт флаги сэмплера для текстуры с заданным номером.
### Аргументы

- *int* **num** - Номер текстуры.
- *int* **sampler_flags** - Флаги сэмплера.

## int getTextureFormatFlags ( int num ) const

Возвращает флаги формата текстуры с заданным номером.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Флаги формата текстуры.
## bool createMaterialFile ( const char * path )

Создаёт файл и сохраняет в него [internal](../../../content/materials/index.md#manual_internal_materials) материал.
### Аргументы

- *const char ** **path** - Путь для сохранения материала

### Возвращаемое значение

Значение, указывающее, был ли материал успешно сохранён.
## bool isReflection2D ( ) const

Возвращает значение, указывающее, есть ли у материала 2D текстура отражения.
### Возвращаемое значение

true, если у материала есть 2D текстура отражения; иначе false.
## Ptr < Shader > getShaderAsync ( Render::PASS pass , int node )

Возвращает [rendering shader](../../../api/library/rendering/class.shader_cpp.md) для заданного прохода рендеринга и [node type](../../../api/library/nodes/class.node_cpp.md#TYPE):
- Если шейдер уже был скомпилирован ранее, функция вернёт его немедленно.
- Если шейдер ещё не скомпилирован, функция инициирует его асинхронную компиляцию в другом потоке и вернёт успешно скомпилированный шейдер. > **Notice:** Функция будет продолжать возвращать nullptr, пока шейдер не будет скомпилирован.


> **Notice:** Чтобы компилировать шейдер асинхронно, включите [asynchronous compilation mode](../../../api/library/rendering/class.render_cpp.md#getShadersCompileMode_int). В противном случае функция будет работать так же, как *[getShaderForce()](#getShaderForce_int_int_Shader)*.


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).
- *int* **node** - [Node type](../../../api/library/nodes/class.node_cpp.md#TYPE).

### Возвращаемое значение

Шейдер для заданного прохода рендеринга и типа узла, если он успешно скомпилирован. Иначе nullptr.
## Ptr < Shader > getShaderAsync ( Render::PASS pass )

Возвращает [rendering shader](../../../api/library/rendering/class.shader_cpp.md) для заданного прохода рендеринга:
- Если шейдер уже был скомпилирован ранее, функция вернёт его немедленно.
- Если шейдер ещё не скомпилирован, функция инициирует его асинхронную компиляцию в другом потоке и вернёт успешно скомпилированный шейдер. > **Notice:** Функция будет продолжать возвращать nullptr, пока шейдер не будет скомпилирован.


> **Notice:** Чтобы компилировать шейдер асинхронно, включите [asynchronous compilation mode](../../../api/library/rendering/class.render_cpp.md#getShadersCompileMode_int). В противном случае функция будет работать так же, как *[getShaderForce()](#getShaderForce_int_Shader)*.


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).

### Возвращаемое значение

Shader for the specified rendering pass, if compiled successfully. Otherwise, nullptr.
## Ptr < Shader > getShaderAsync ( const char * pass , int node )

Returns the [rendering shader](../../../api/library/rendering/class.shader_cpp.md) for the specified rendering pass and [node type](../../../api/library/nodes/class.node_cpp.md#TYPE):
- If the shader has been compiled previously, the function will return it immediately.
- If the shader hasn't been compiled yet, the function will initiate its asynchronous compilation in another thread and return the successfully compiled shader. > **Notice:** The function will keep returning nullptr until the shader is compiled.


> **Notice:** To compile the shader asynchronously, enable the [asynchronous compilation mode](../../../api/library/rendering/class.render_cpp.md#getShadersCompileMode_int). Otherwise, the function will work the same as *[getShaderForce()](#getShaderForce_cstr_int_Shader)*.


### Аргументы

- *const char ** **pass** - Rendering pass name. One of the following:

  - *wireframe*
  - *visualizer_solid*
  - *deferred*
  - *auxiliary*
  - *emission*
  - *reflection*
  - *refraction*
  - *transparent_blur*
  - *ambient*
  - *light_voxel_probe*
  - *light_environment_probe*
  - *light_omni*
  - *light_proj*
  - *light_world*
  - *shadow*
  - *depth_pre_pass*
  - *post*
  - *object_post*
- *int* **node** - [Node type](../../../api/library/nodes/class.node_cpp.md#TYPE).

### Возвращаемое значение

Шейдер для заданного прохода рендеринга и типа узла, если он успешно скомпилирован. Иначе nullptr.
## Ptr < Shader > getShaderAsync ( const char * pass )

Returns the [rendering shader](../../../api/library/rendering/class.shader_cpp.md) for the specified rendering pass:
- If the shader has been compiled previously, the function will return it immediately.
- If the shader hasn't been compiled yet, the function will initiate its asynchronous compilation in another thread and return the successfully compiled shader. > **Notice:** The function will keep returning nullptr until the shader is compiled.


> **Notice:** To compile the shader asynchronously, enable the [asynchronous compilation mode](../../../api/library/rendering/class.render_cpp.md#getShadersCompileMode_int). Otherwise, the function will work the same as *[getShaderForce()](#getShaderForce_cstr_Shader)*.


### Аргументы

- *const char ** **pass** - Rendering pass name. One of the following:

  - *wireframe*
  - *visualizer_solid*
  - *deferred*
  - *auxiliary*
  - *emission*
  - *reflection*
  - *refraction*
  - *transparent_blur*
  - *ambient*
  - *light_voxel_probe*
  - *light_environment_probe*
  - *light_omni*
  - *light_proj*
  - *light_world*
  - *shadow*
  - *depth_pre_pass*
  - *post*
  - *object_post*

### Возвращаемое значение

Shader for the specified rendering pass, if compiled successfully. Otherwise, nullptr.
## Ptr < Shader > getShaderForce ( Render::PASS pass , int node )

Returns the [rendering shader](../../../api/library/rendering/class.shader_cpp.md) for the specified rendering pass and [node type](../../../api/library/nodes/class.node_cpp.md#TYPE):
- If the shader has been compiled previously, the function will return it immediately.
- If the shader hasn't been compiled yet, the function will immediately compile and return it.


> **Notice:** The function causes a spike because it compiles the shader in the current thread.


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).
- *int* **node** - [Node type](../../../api/library/nodes/class.node_cpp.md#TYPE).

### Возвращаемое значение

Шейдер для заданного прохода рендеринга и типа узла, если он успешно скомпилирован. Иначе nullptr.
## Ptr < Shader > getShaderForce ( Render::PASS pass )

Returns the [rendering shader](../../../api/library/rendering/class.shader_cpp.md) for the specified rendering pass:
- If the shader has been compiled previously, the function will return it immediately.
- If the shader hasn't been compiled yet, the function will immediately compile and return it.


> **Notice:** The function causes a spike because it compiles the shader in the current thread.


### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).

### Возвращаемое значение

Shader for the specified rendering pass, if compiled successfully. Otherwise, nullptr.
## Ptr < Shader > getShaderForce ( const char * pass , int node )

Returns the [rendering shader](../../../api/library/rendering/class.shader_cpp.md) for the specified rendering pass and [node type](../../../api/library/nodes/class.node_cpp.md#TYPE):
- If the shader has been compiled previously, the function will return it immediately.
- If the shader hasn't been compiled yet, the function will immediately compile and return it.


> **Notice:** The function causes a spike because it compiles the shader in the current thread.


### Аргументы

- *const char ** **pass** - Rendering pass name. One of the following:

  - *wireframe*
  - *visualizer_solid*
  - *deferred*
  - *auxiliary*
  - *emission*
  - *reflection*
  - *refraction*
  - *transparent_blur*
  - *ambient*
  - *light_voxel_probe*
  - *light_environment_probe*
  - *light_omni*
  - *light_proj*
  - *light_world*
  - *shadow*
  - *depth_pre_pass*
  - *post*
  - *object_post*
- *int* **node** - [Node type](../../../api/library/nodes/class.node_cpp.md#TYPE).

### Возвращаемое значение

Шейдер для заданного прохода рендеринга и типа узла, если он успешно скомпилирован. Иначе nullptr.
## Ptr < Shader > getShaderForce ( const char * pass )

Returns the [rendering shader](../../../api/library/rendering/class.shader_cpp.md) for the specified rendering pass:
- If the shader has been compiled previously, the function will return it immediately.
- If the shader hasn't been compiled yet, the function will immediately compile and return it.


> **Notice:** The function causes a spike because it compiles the shader in the current thread.


### Аргументы

- *const char ** **pass** - Rendering pass name. One of the following:

  - *wireframe*
  - *visualizer_solid*
  - *deferred*
  - *auxiliary*
  - *emission*
  - *reflection*
  - *refraction*
  - *transparent_blur*
  - *ambient*
  - *light_voxel_probe*
  - *light_environment_probe*
  - *light_omni*
  - *light_proj*
  - *light_world*
  - *shadow*
  - *depth_pre_pass*
  - *post*
  - *object_post*

### Возвращаемое значение

Shader for the specified rendering pass, if compiled successfully. Otherwise, nullptr.
## void setTextureStreamingDensityMultiplier ( int num , float streaming_density_multiplier )

Sets a multiplier adjusting the distance at which the texture mipmaps are rendered.
### Аргументы

- *int* **num** - Номер текстуры.
- *float* **streaming_density_multiplier** - Multiplier applied to the texture mipmaps rendering distance.

## float getTextureStreamingDensityMultiplier ( int num ) const

Returns the current adjusting the distance at which the texture mipmaps are rendered.
### Аргументы

- *int* **num** - Номер текстуры.

### Возвращаемое значение

Multiplier applied to the texture mipmaps rendering distance.
## bool needCreateShaderCache ( ) const

Returns a value indicating if shader cache needs to be created for current material states and options.
### Возвращаемое значение

true if shader cache is required for current material states and options; or false, if shader combination for current material states and options is already in cache.
## bool needCreateShaderCache ( Render::PASS pass , Node::TYPE node_type ) const

Returns a value indicating if shader combination needs to be created for the given rendering pass and node type.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **node_type** - Node type.

### Возвращаемое значение

true if shader cache needs to be created for the given rendering pass and node type; or false, if shader combination for the given rendering pass and node type is already in cache.
## bool shaderCacheExist ( Render::PASS pass , Node::TYPE node_type ) const

Returns a value indicating if shader combination for the given rendering pass and node type is already in cache.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **node_type** - Node type.

### Возвращаемое значение

true if shader combination for the given rendering pass and node type is already in cache; otherwise, false.
## void createShaderForce ( Render::PASS pass , Node::TYPE node_type )

Compiles shader combination for the given rendering pass and node type. Shaders are compiled immediately, which may cause spikes, therefore this method is recommended only for critical cases, where [*createShaderAsync*](#createShaderAsync_int_int_void) doesn't ensure a satisfying result.
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **node_type** - Node type.

## void createShaderAsync ( Render::PASS pass , Node::TYPE node_type )

Compiles shader combination for the given rendering pass and node type. Shaders are compiled asynchronously, which ensures smooth performance without spikes and is suitable for most cases. For the shaders that requre to be compiled immediately, use [*createShaderForce*](#createShaderForce_int_int_void).
### Аргументы

- *[Render::PASS](../../../api/library/rendering/class.render_cpp.md#PASS)* **pass** - Rendering pass number in range [0;[NUM_PASSES](../../../api/library/rendering/class.render_cpp.md#NUM_PASSES)) (one of the *[PASS_*](../../../api/library/rendering/class.render_cpp.md#PASS_WIREFRAME)* variables).
- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **node_type** - Node type.

## void createRenderMaterials ( )

Creates render materials (internal materials required for rendering). For example, you can create all necessary render materials during initialization to avoid spikes that may occur later.
## void createShaderCache ( bool recursive = false )

Compiles all shaders for the current material and its children (if any).
### Аргументы

- *bool* **recursive** - true to compile shaders for child materials; otherwise, false.

## void createShadersFromCache ( bool recursive = false )

Compiles all shaders available in shader cache for the current material and its children (if any).
### Аргументы

- *bool* **recursive** - true to compile shaders for child materials; otherwise, false.
