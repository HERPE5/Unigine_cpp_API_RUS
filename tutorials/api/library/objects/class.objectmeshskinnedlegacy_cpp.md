# ObjectMeshSkinnedLegacy Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Этот класс используется для создания и изменения [skinned meshes](../../../objects/objects/mesh_skinned_legacy/index.md). Skinned Mesh используются для рендеринга анимированных персонажей.


#### Applying Animation


Анимация применяется к *ObjectMeshSkinnedLegacy* через его слои. Слои хранят позы скелета, поза берётся из анимации.


По умолчанию при создании *ObjectMeshSkinnedLegacy* имеет только один активный базовый слой, поза которого используется для анимации. Можно добавить больше слоёв для хранения различных поз, которые могут быть смешаны или обработаны иным образом (с помощью таких функций, как *[*lerpLayer*](#lerpLayer_int_int_int_float_void)*, *[*copyLayer*](#copyLayer_int_int_void)*, *[*importLayer*](#importLayer_int_void)*, *[*inverseLayer*](#inverseLayer_int_int_void)* и *[*mulLayer*](#mulLayer_int_int_int_float_void)*), при этом итоговая поза сохраняется в базовом слое для финального вывода рендеринга.


**Автоматическое смешивание (blending)** анимаций, подходящее для простых случаев использования, реализовано внутри ObjectMeshSkinnedLegacy. Чтобы слой был включён в итоговое смешивание, он должен быть включён и иметь ненулевой вес. Эти значения можно изменить с помощью **[setLayer()](../../...md#setLayer_int_int_float_void)**, **[setLayerEnabled()](../../...md#setLayerEnabled_int_int_void)** и **[setLayerWeight()](../../...md#setLayerWeight_int_float_void)**. При смешивании применяется среднее арифметическое взвешенное: сначала нормализуются все веса слоёв, после чего каждый компонент умножается на соответствующий вес и суммируется.


Похожий подход используется для масштабирования, и немного другой — для вращений, но при работе на уровне слоя это не критично.


**Настраиваемое (customized) смешивание** анимаций, включая частичное смешивание костей, аддитивную анимацию и т.д., реализуется с помощью пользовательской логики. Вы можете управлять отдельными костями на слоях с помощью **[setLayerBoneTransform()](../../...md#setLayerBoneTransform_int_int_mat4_void)** / **[getLayerBoneTransform()](../../...md#getLayerBoneTransform_int_int_mat4)**, а также их аналогов для отдельных компонентов: позиции, вращения и масштаба. Эти функции позволяют создавать маски для костей, а затем работать исключительно с этими костями в цикле.


##### Creating and Playing Animation


Чтобы добавить анимацию к ObjectMeshSkinnedLegacy и воспроизвести её, выполните следующее:


1. Задайте количество слоёв анимации с помощью **[setNumLayers()](../../...md#setNumLayers_int_void)**. По умолчанию есть только один слой, поза которого используется для анимации.
2. Включите каждый слой и задайте вес анимации для смешивания, вызвав функцию **[setLayer()](../../...md#setLayer_int_int_float_void)**.
3. Добавьте файл анимации `*.anim` с помощью функции **[setLayerAnimationFilePath()](../../...md#setLayerAnimationFilePath_int_cstr_void)**.
4. Воспроизведите добавленную анимацию, вызвав функцию **[setLayerFrame()](../../...md#setLayerFrame_int_float_int_int_float)** для каждого слоя анимации.


Смешивание выполняется между всеми слоями. Вклад каждого слоя зависит от его веса. Кроме того, при необходимости вы можете вручную задать трансформации отдельных костей, используя **[setBoneTransform()](../../...md#setBoneTransform_int_mat4_void)** или **[setBoneTransformWithChildren()](../../...md#setBoneTransformWithChildren_int_mat4_void)**.


###### Usage Example


Следующий пример показывает, как смешать две разные анимации, назначенные мешу. Вы можете использовать меш и анимации из примеров UNIGINE, расположенных в следующих папках наборов примеров:


- `<cpp_samples>/data/showcase_content/person`
- `<csharp_component_samples>/data/showcase_content/agent`


Анимации добавляются с помощью функции **[setLayerAnimationFilePath()](../../...md#setLayerAnimationFilePath_int_cstr_void)**.


В этом примере доступ к ресурсам анимации осуществляется через [Component System](../../../principles/component_system/index.md).


1. [Create a component](../../../code/usage/using_component_system/index.md) для управления загрузкой анимации и сгенерируйте для него свойство.
2. Назначьте свойство целевому узлу-контроллеру.
3. Назначьте нужные ресурсы анимации параметрам свойства в UnigineEditor. ![](property_assets.png) *Назначение ресурсов анимации параметрам свойства через редактор*
4. Реализуйте логику создания skinned-меша с указанными анимациями. Полный исходный код: ```cpp #pragma once #include <UnigineComponentSystem.h> #include <UnigineObjects.h> class SkinnedMeshController: public Unigine::ComponentBase { public: COMPONENT(SkinnedMeshController, ComponentBase); COMPONENT_INIT(init); COMPONENT_UPDATE(update); COMPONENT_SHUTDOWN(shutdown); PROP_NAME("skinned_controller_property"); // property parameters for mesh and animation assets PROP_PARAM(File, mesh_asset); PROP_PARAM(File, anim_asset_1); PROP_PARAM(File, anim_asset_2); protected: void init(); void update(); void shutdown(); private: // the pointer to the skinned mesh object Unigine::ObjectMeshSkinnedLegacyPtr skinned_mesh; }; ``` ```cpp #include "SkinnedMeshController.h" #include <UnigineGame.h> // register the component REGISTER_COMPONENT(SkinnedMeshController); using namespace Unigine; void SkinnedMeshController::init() { // create the new ObjectMeshSkinnedLegacy mesh based on an existing mesh skinned_mesh = ObjectMeshSkinnedLegacy::create(mesh_asset); // we need two layers to get poses from two animations skinned_mesh->setNumLayers(2); // load animations from the files on separate layers skinned_mesh->setLayerAnimationFilePath(0, anim_asset_1); skinned_mesh->setLayerAnimationFilePath(1, anim_asset_2); // enable each layer and set an animation weight skinned_mesh->setLayer(0, true, 0.7f); skinned_mesh->setLayer(1, true, 0.3f); } void SkinnedMeshController::update() { // play each animation, getting new poses with each frame update skinned_mesh->setLayerFrame(0, Game::getTime() * 25.0f); skinned_mesh->setLayerFrame(1, Game::getTime() * 25.0f); } void SkinnedMeshController::shutdown() { } ```


#### Updating Bone Transformations


Некоторым методам требуется обновление данных анимации перед тем, как рендерер выполнит своё обновление и фактически отрисует skinned-меш. Такое обновление позволяет получить корректный результат смешивания между кадрами и слоями. Это обновление выполняется на основе состояния внутренних флагов обновления, указывающих, были ли какие-либо трансформации костей.


Последовательность выполнения обновления трансформаций костей следующая:


1. Вызовите метод, устанавливающий флаг обновления. Этот флаг показывает, что экземпляр должен быть обновлён.
2. Обновите трансформации костей, вызвав соответствующие функции. Эти функции проверяют флаг, и если он установлен, вычисляют трансформации и сбрасывают флаг в значение по умолчанию.
3. Во время рендеринга движок выполняет анимации и трансформации, вычисленные на предыдущем шаге, либо пересчитывает их, если флаг обновления был установлен. Если вычисления были выполнены, флаг сбрасывается в значение по умолчанию.


Если вы попытаетесь обновить трансформации костей до установки флага обновления, функции не будут вычислять новые трансформации, и движок их не выполнит.


При изменении трансформации кости необходимо уведомить об этих трансформациях все skinned-меши, использующие эту кость, чтобы обновить меш. При изменении трансформаций кости экземпляры skinned-меша получают флаг обновления. При использовании функции *[setLayerFrame()](#setLayerFrame_int_float_int_int_float)* вы задаёте необходимые трансформации для указанного skinned-меша.


#### Instancing


Поверхности идентичных skinned-мешей, которым назначены одинаковые материалы и одинаковое количество костей, прикреплённых к их вершинам, автоматически инстансируются и отрисовываются за один вызов отрисовки (draw call).


Буферы данных для инстансированных объектов, хранящие трансформации костей, ограничены по размеру; поэтому если у skinned-мешей много костей, только небольшое количество мешей может заполнить буфер данных экземпляров для отрисовки за один вызов отрисовки.


> **Notice:** Чем больше количество костей и чем больше костей прикреплено к одной поверхности, тем менее эффективным будет инстансинг.


#### Procedural Mesh Modifications


Процедурный режим для skinned-мешей позволяет изменять геометрию объекта во время выполнения. Это может быть полезно, например, при генерации вариаций персонажей, динамической подгонке брони или одежды, или деформации модели в ответ на игровые события.


В отличие от [procedural modes](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE), доступных для статических мешей, у skinned-мешей есть **только один режим** — эквивалентный *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* (процедурный меш остаётся в VRAM и не будет выгружен).


Процедурные обновления для skinned-мешей выполняются исключительно в главном потоке движка с помощью *[applyMeshProcedural()](../../...md#applyMeshProcedural_ConstMeshSkinned_int)*. Если исходный меш содержит совместимые элементы (например, кости, поверхности, данные скининга), соответствующие оригиналу, то анимации, морф-таргеты и другое поведение продолжат работать без прерывания. В противном случае меш останется статическим, без применения анимации или морфинга.


#### Reusing Animations


Анимации одного персонажа можно использовать для другого.


##### Animation Frame Masks


Маски — простейший способ повторного использования анимаций, несколько слов о том, как они работают. Каждому слою *ObjectMeshSkinnedLegacy* можно назначить некоторую анимацию, и на основе её кадров она будет изменять трансформации костей на этом слое. Вы можете использовать **[masks](#ANIM_FRAME_USES_NONE)**, чтобы выбрать, какие компоненты кадра анимации (позиция, вращение, масштаб, их комбинации или все сразу) используются для каждого конкретного слоя. Если какой-либо компонент отсутствует в маске, соответствующее значение будет взято из T-позы.


В качестве примера возьмём анимацию глаз для этих двух скелетов:


![](anim_mask_1.jpg)


У них абсолютно одинаковая иерархия костей, а также имена костей, различаются только пропорции. Если мы применим анимацию глаз левого скелета к правому, получим следующий результат:


![](anim_mask_2.jpg)


Исходная анимация полностью изменила пропорции второго скелета. Это можно исправить, задав маску **[ANIM_FRAME_USES_ROTATION](#ANIM_FRAME_USES_ROTATION)** для костей глаз и **[ANIM_FRAME_USES_NONE](#ANIM_FRAME_USES_NONE)** для остальных костей с помощью методов **[setLayerBoneFrameUses()](../../...md#setLayerBoneFrameUses_int_int_int_void)* / *[getLayerBoneFrameUses()](../../...md#getLayerBoneFrameUses_int_int_int)**. Таким образом, все значения, кроме вращения глаз, будут взяты из T-позы:


![](eyes_anim.gif)


Если у скелетов разные имена костей, сначала следует применить ретаргетинг (retargeting), а затем использовать маски. В этом случае не так важно иметь похожие скелеты.


##### Retargeting


Чтобы полностью повторно использовать анимацию, исходный и целевой скелеты должны иметь схожую иерархию костей, а их T-позы не должны значительно отличаться.


Это допустимо и будет работать корректно:


![](skeletons_good.jpg)


поскольку у нас схожие иерархии костей, и все кости имеют схожие базисы в T-позах, различаются только пропорции, но эта пропорция почти одинакова для всех костей.


Но мы не можем использовать следующее:


![](skeletons_bad.jpg)


Хотя иерархия выглядит похожей, T-позы отличаются, и кости имеют разные базисы.


Эти ограничения можно игнорировать, если вам нужно выполнить ретаргетинг только для некоторого подмножества костей (например: выполнить ретаргетинг костей с разными именами, а затем использовать только маски).


#### Inverse Kinematics (IK)


*ObjectMeshSkinnedLegacy* поддерживает инверсную кинематику (IK) для цепочек костей (**IK-цепочки**). Инверсная кинематика предоставляет способ управления вращением сустава на основе положения **конечного эффектора (end-effector)**, а не через прямое вращение сустава. Вы задаёте положение эффектора, и решатель IK пытается найти вращение так, чтобы конечный сустав максимально точно совпадал с этим положением. Это можно использовать для правильного позиционирования ступней персонажа на неровной поверхности и обеспечения правдоподобного взаимодействия с миром. Значение **tolerance** задаёт порог, при котором цель считается достигшей своего конечного положения, и решатель IK прекращает итерации.


IK-цепочка может иметь произвольную длину (содержать произвольное количество костей), она имеет вспомогательный вектор, позволяющий управлять направлением изгиба. Вы также можете задать вращение для последнего сустава цепочки.


Каждая IK-цепочка имеет значение **weight**, которое можно использовать для управления влиянием цели на последний сустав цепочки. Это позволяет выполнять плавные переходы от исходной анимации к требуемому целевому положению конечности.


Для визуализации IK-цепочек можно использовать следующие методы: **[addVisualizeIKChain()](../../...md#addVisualizeIKChain_int_void)*, *[removeVisualizeIKChain()](../../...md#removeVisualizeIKChain_int_void)** и **[clearVisualizeIKChain()](../../...md#clearVisualizeIKChain_void)**.


![](ik_visualizer.gif)


### See Also


- *[Mesh](../../../api/library/rendering/class.mesh_cpp.md)* class
- Article on [Mesh File Formats](../../../code/formats/file_formats.md#mesh)
- Animation samples in *[C++](../../../sdk/api_samples/cpp/animation.md)* and *[C# Component Samples](../../../sdk/api_samples/cs/animation.md)* suites


## ObjectMeshSkinnedLegacy Class

### Перечисления

## BONE_SPACE

Определяет, какая трансформация кости должна быть переопределена трансформацией bind-узла.
| Name | Description |
|---|---|
| **BONE_SPACE_WORLD** = 0 | Мировые координаты. |
| **BONE_SPACE_OBJECT** = 1 | Координаты относительно объекта skinned-меша. |
| **BONE_SPACE_LOCAL** = 2 | Координаты относительно родительской кости. |

## NODE_SPACE

Определяет тип трансформации bind-узла, используемой для переопределения трансформации указанной кости.
| Name | Description |
|---|---|
| **NODE_SPACE_WORLD** = 0 | Мировая трансформация узла. |
| **NODE_SPACE_LOCAL** = 1 | Локальная трансформация узла. |

## BIND_MODE

Тип смешивания трансформаций bind-узла и кости.
| Name | Description |
|---|---|
| **BIND_MODE_OVERRIDE** = 0 | Заменяет трансформацию кости трансформацией bind-узла. |
| **BIND_MODE_ADDITIVE** = 1 | Трансформация bind-узла добавляется к текущей трансформации кости. |

## ANIM_FRAME_USES

Компоненты кадра, используемые для анимации.
| Name | Description |
|---|---|
| **ANIM_FRAME_USES_NONE** = 0 | Компоненты кадра не используются. |
| **ANIM_FRAME_USES_POSITION** = 1 << 0 | Используется только позиция. |
| **ANIM_FRAME_USES_ROTATION** = 1 << 1 | Используется только вращение. |
| **ANIM_FRAME_USES_SCALE** = 1 << 2 | Используется только масштаб. |
| **ANIM_FRAME_USES_ALL** = POSITION \| ROTATION \| SCALE | Используются все компоненты кадра. |
| **ANIM_FRAME_USES_POSITION_AND_ROTATION** = POSITION \| ROTATION | Используются только позиция и вращение. |
| **ANIM_FRAME_USES_POSITION_AND_SCALE** = POSITION \| SCALE | Используются только позиция и масштаб. |
| **ANIM_FRAME_USES_ROTATION_AND_SCALE** = ROTATION \| SCALE | Используются только вращение и масштаб. |

## CHAIN_CONSTRAINT

| Name | Description |
|---|---|
| **CHAIN_CONSTRAINT_NONE** = 0 | К IK/LookAt-цепочке ограничения не применяются. Трансформации цепочки сохраняются как есть после применения решателя. |
| **CHAIN_CONSTRAINT_POLE_VECTOR** = 1 | К IK/LookAt-цепочке применяется указанный опорный вектор (pole vector). Для IK-цепочки опорный вектор определяет плоскость изгиба. Для LookAt-цепочки опорный вектор определяет плоскость оси UP. Это ограничение применяется после применения решателя. |
| **CHAIN_CONSTRAINT_BONE_ROTATIONS** = 2 | На каждом шаге применения решателя к цепочке применяются ограничения вращения костей, если они были настроены ранее. |

## INTERPOLATION_ACCURACY

| Name | Description |
|---|---|
| **INTERPOLATION_ACCURACY_LOW** = 0 | Применяется линейная интерполяция с нормализацией кватерниона (nlerp). |
| **INTERPOLATION_ACCURACY_MEDIUM** = 1 | Для вращения применяется линейная интерполяция с нормализацией кватерниона (nlerp), но коэффициент интерполяции корректируется для приближения к равномерной угловой скорости вращения. |
| **INTERPOLATION_ACCURACY_HIGH** = 2 | Для вращений используется функция slerp. |

### Методы класса

## int getNumBones () const

Возвращает текущее количество всех костей, участвующих в анимации.
### Возвращаемое значение

Текущее количество костей skinned-меша.
## void setNumLayers ( int layers )

Задаёт новое количество слоёв анимации для смешивания. Например, при смешивании двух слоёв трансформации костей между слоями интерполируются, а позиции вершин могут вычисляться на основе интерполированных результатов. Подробнее см. статью [Skinned Mesh](../../../objects/objects/mesh_skinned_legacy/index.md).
### Аргументы

- *int* **layers** - Количество слоёв анимации (должно быть больше 0).

## int getNumLayers () const

Возвращает текущее количество слоёв анимации для смешивания. Например, при смешивании двух слоёв трансформации костей между слоями интерполируются, а позиции вершин могут вычисляться на основе интерполированных результатов. Подробнее см. статью [Skinned Mesh](../../../objects/objects/mesh_skinned_legacy/index.md).
### Возвращаемое значение

Текущее количество слоёв анимации (должно быть больше 0).
## bool isStopped () const

Возвращает текущий статус остановки.
### Возвращаемое значение

**true**, если анимация остановлена; иначе **false**.
## bool isPlaying () const

Возвращает текущий статус воспроизведения.
### Возвращаемое значение

**true**, если анимация воспроизводится; иначе **false**.
## void setSpeed ( float speed )

Задаёт новое значение множителя для [time](#setTime_float_void) воспроизведения анимации.
### Аргументы

- *float* **speed** - Значение множителя скорости воспроизведения.

## float getSpeed () const

Возвращает текущее значение множителя для [time](#setTime_float_void) воспроизведения анимации.
### Возвращаемое значение

Текущее значение множителя скорости воспроизведения.
## void setTime ( float time )

Задаёт новое время анимации в кадрах анимации. Отсчёт времени начинается с нулевого кадра. Если время задано между кадрами, анимация смешивается. Если время задано за пределами диапазона кадров анимации, анимация зацикливается.
> **Notice:** Функция *[setTime()](../../...md#setTime_float_void)* соответствует опциям [Play](../../../objects/objects/mesh_skinned_legacy/index.md#play) и [Stop](../../../objects/objects/mesh_skinned_legacy/index.md#stop) в редакторе. Во всех остальных случаях для задания анимации используйте *[setLayerFrame()](../../...md#setLayerFrame_int_float_int_int_float)*.


### Аргументы

- *float* **time** - Время анимации в кадрах анимации.

## float getTime () const

Возвращает текущее время анимации в кадрах анимации. Отсчёт времени начинается с нулевого кадра. Если время задано между кадрами, анимация смешивается. Если время задано за пределами диапазона кадров анимации, анимация зацикливается.
> **Notice:** Функция *[setTime()](../../...md#setTime_float_void)* соответствует опциям [Play](../../../objects/objects/mesh_skinned_legacy/index.md#play) и [Stop](../../../objects/objects/mesh_skinned_legacy/index.md#stop) в редакторе. Во всех остальных случаях для задания анимации используйте *[setLayerFrame()](../../...md#setLayerFrame_int_float_int_int_float)*.


### Возвращаемое значение

Текущее время анимации в кадрах анимации.
## void setLoop ( bool loop )

Задаёт новое значение, указывающее, зациклена ли анимация или воспроизводится только один раз.
### Аргументы

- *bool* **loop** - Установите **true**, чтобы включить зацикленное воспроизведение анимации; **false** — чтобы отключить.

## bool isLoop () const

Возвращает текущее значение, указывающее, зациклена ли анимация или воспроизводится только один раз.
### Возвращаемое значение

**true**, если зацикленное воспроизведение анимации включено; иначе **false**.
## void setControlled ( bool controlled )

Задаёт новое значение, указывающее, управляется ли анимация родительским ObjectMeshSkinnedLegacy.
### Аргументы

- *bool* **controlled** - Установите **true**, чтобы анимация управлялась родительским ObjectMeshSkinnedLegacy; **false** — чтобы отключить.

## bool isControlled () const

Возвращает текущее значение, указывающее, управляется ли анимация родительским ObjectMeshSkinnedLegacy.
### Возвращаемое значение

**true**, если анимация управляется родительским ObjectMeshSkinnedLegacy; иначе **false**.
## void setQuaternion ( bool quaternion )

Задаёт новое значение, указывающее, используется ли режим скининга с двойными кватернионами (dual-quaternion). Модель двойных кватернионов — точный, вычислительно эффективный, надёжный и гибкий способ представления жёстких трансформаций, используемый в скелетной анимации. Подробнее см. [a Wikipedia article on dual quaternions](https://en.wikipedia.org/wiki/Dual_quaternion) и [a beginners guide to dual-quaternions](http://cs.gmu.edu/~jmlien/teaching/cs451/uploads/Main/dual-quaternion.pdf).
### Аргументы

- *bool* **quaternion** - Установите **true**, чтобы включить режим скининга с двойными кватернионами; **false** — чтобы отключить.

## bool isQuaternion () const

Возвращает текущее значение, указывающее, используется ли режим скининга с двойными кватернионами (dual-quaternion). Модель двойных кватернионов — точный, вычислительно эффективный, надёжный и гибкий способ представления жёстких трансформаций, используемый в скелетной анимации. Подробнее см. [a Wikipedia article on dual quaternions](https://en.wikipedia.org/wiki/Dual_quaternion) и [a beginners guide to dual-quaternions](http://cs.gmu.edu/~jmlien/teaching/cs451/uploads/Main/dual-quaternion.pdf).
### Возвращаемое значение

**true**, если режим скининга с двойными кватернионами включён; иначе **false**.
## void setUpdateDistanceLimit ( float limit = 200 )

Задаёт новое расстояние от камеры, в пределах которого объект должен обновляться.
### Аргументы

- *float* **limit** - Расстояние от камеры, в пределах которого объект должен обновляться, в единицах.

## float getUpdateDistanceLimit () const

Возвращает текущее расстояние от камеры, в пределах которого объект должен обновляться.
### Возвращаемое значение

Текущее расстояние от камеры, в пределах которого объект должен обновляться, в единицах.
## void setFPSInvisible ( int fpsinvisible = 0 )

Задаёт новое значение частоты обновления, когда объект вообще не отрисовывается.
### Аргументы

- *int* **fpsinvisible** - Значение частоты обновления, когда объект вообще не отрисовывается.

## int getFPSInvisible () const

Возвращает текущее значение частоты обновления, когда объект вообще не отрисовывается.
### Возвращаемое значение

Текущее значение частоты обновления, когда объект вообще не отрисовывается.
## void setFPSVisibleShadow ( int shadow = 30 )

Задаёт новое значение частоты обновления, когда отрисовывается только тень объекта.
### Аргументы

- *int* **shadow** - Значение частоты обновления, когда отрисовывается только тень объекта.

## int getFPSVisibleShadow () const

Возвращает текущее значение частоты обновления, когда отрисовывается только тень объекта.
### Возвращаемое значение

Текущее значение частоты обновления, когда отрисовывается только тень объекта.
## void setFPSVisibleCamera ( int camera = -1 )

Задаёт новое значение частоты обновления, когда объект отрисовывается в области просмотра.
### Аргументы

- *int* **camera** - Частота обновления, когда объект отрисовывается в области просмотра.

## int getFPSVisibleCamera () const

Возвращает текущее значение частоты обновления, когда объект отрисовывается в области просмотра.
### Возвращаемое значение

Текущее значение частоты обновления, когда объект отрисовывается в области просмотра.
## void setVisualizeAllBones ( bool bones )

Задаёт новое значение, указывающее, включена ли визуализация костей и их базисных векторов. Визуализатор можно использовать для отладки, отображая позиции костей и их базисные векторы одновременно для нескольких мешей.
### Аргументы

- *bool* **bones** - Установите **true**, чтобы включить визуализацию костей и их базисных векторов; **false** — чтобы отключить.

## bool isVisualizeAllBones () const

Возвращает текущее значение, указывающее, включена ли визуализация костей и их базисных векторов. Визуализатор можно использовать для отладки, отображая позиции костей и их базисные векторы одновременно для нескольких мешей.
### Возвращаемое значение

**true**, если визуализация костей и их базисных векторов включена; иначе **false**.
## int getNumIKChains () const

Возвращает текущее количество [IK chains](#ik_chains) skinned-меша.
### Возвращаемое значение

Текущее количество IK-цепочек.
## Event<const Ptr < ObjectMeshSkinnedLegacy > &> getEventEndBoneConstraints () const

Событие, вызываемое после применения ограничений вращения костей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события EndBoneConstraints
void endboneconstraints_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события EndBoneConstraints\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endboneconstraints_event_connections;

// link to this instance when subscribing for an event (subscription for various events can be linked)
objectmeshskinnedlegacy->getEventEndBoneConstraints().connect(endboneconstraints_event_connections, endboneconstraints_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
objectmeshskinnedlegacy->getEventEndBoneConstraints().connect(endboneconstraints_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndBoneConstraints (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endboneconstraints_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endboneconstraints_event_connection;

// subscribe for the EndBoneConstraints event with a handler function keeping the connection
objectmeshskinnedlegacy->getEventEndBoneConstraints().connect(endboneconstraints_event_connection, endboneconstraints_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endboneconstraints_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endboneconstraints_event_connection.setEnabled(true);

// ...

// remove subscription for the EndBoneConstraints event via the connection
endboneconstraints_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndBoneConstraints, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события EndBoneConstraints\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
objectmeshskinnedlegacy->getEventEndBoneConstraints().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. You can subscribe and unsubscribe via the handler function directly
//////////////////////////////////////////////////////////////////////////////

// subscribe for the EndBoneConstraints event with a handler function
objectmeshskinnedlegacy->getEventEndBoneConstraints().connect(endboneconstraints_event_handler);

// remove subscription for the EndBoneConstraints event later by the handler function
objectmeshskinnedlegacy->getEventEndBoneConstraints().disconnect(endboneconstraints_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Subscribe to an event saving an ID and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////

// define a connection ID to be used to unsubscribe later
EventConnectionId endboneconstraints_handler_id;

// subscribe for the EndBoneConstraints event with a lambda handler function and keeping connection ID
endboneconstraints_handler_id = objectmeshskinnedlegacy->getEventEndBoneConstraints().connect([](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndBoneConstraints (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
objectmeshskinnedlegacy->getEventEndBoneConstraints().disconnect(endboneconstraints_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Ignoring all EndBoneConstraints events when necessary
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
objectmeshskinnedlegacy->getEventEndBoneConstraints().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectmeshskinnedlegacy->getEventEndBoneConstraints().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<ObjectMeshSkinnedLegacy> & **skinned**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndBoneConstraints
void endboneconstraints_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события EndBoneConstraints\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endboneconstraints_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndBoneConstraints().connect(endboneconstraints_event_connections, endboneconstraints_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndBoneConstraints().connect(endboneconstraints_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndBoneConstraints (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endboneconstraints_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endboneconstraints_event_connection;

// подписываемся на событие EndBoneConstraints с функцией-обработчиком, сохраняя соединение
publisher->getEventEndBoneConstraints().connect(endboneconstraints_event_connection, endboneconstraints_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endboneconstraints_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endboneconstraints_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndBoneConstraints через соединение
endboneconstraints_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndBoneConstraints, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события EndBoneConstraints\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndBoneConstraints().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endboneconstraints_handler_id;

// подписываемся на событие EndBoneConstraints с лямбда-обработчиком, сохраняя идентификатор соединения
endboneconstraints_handler_id = publisher->getEventEndBoneConstraints().connect(e_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndBoneConstraints (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndBoneConstraints().disconnect(endboneconstraints_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndBoneConstraints при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndBoneConstraints().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndBoneConstraints().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < ObjectMeshSkinnedLegacy > &> getEventBeginBoneConstraints () const

Событие, вызываемое перед применением ограничений вращения костей. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события BeginBoneConstraints
void beginboneconstraints_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события BeginBoneConstraints\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginboneconstraints_event_connections;

// link to this instance when subscribing for an event (subscription for various events can be linked)
objectmeshskinnedlegacy->getEventBeginBoneConstraints().connect(beginboneconstraints_event_connections, beginboneconstraints_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
objectmeshskinnedlegacy->getEventBeginBoneConstraints().connect(beginboneconstraints_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginBoneConstraints (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginboneconstraints_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginboneconstraints_event_connection;

// subscribe for the BeginBoneConstraints event with a handler function keeping the connection
objectmeshskinnedlegacy->getEventBeginBoneConstraints().connect(beginboneconstraints_event_connection, beginboneconstraints_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginboneconstraints_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginboneconstraints_event_connection.setEnabled(true);

// ...

// remove subscription for the BeginBoneConstraints event via the connection
beginboneconstraints_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginBoneConstraints, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события BeginBoneConstraints\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
objectmeshskinnedlegacy->getEventBeginBoneConstraints().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. You can subscribe and unsubscribe via the handler function directly
//////////////////////////////////////////////////////////////////////////////

// subscribe for the BeginBoneConstraints event with a handler function
objectmeshskinnedlegacy->getEventBeginBoneConstraints().connect(beginboneconstraints_event_handler);

// remove subscription for the BeginBoneConstraints event later by the handler function
objectmeshskinnedlegacy->getEventBeginBoneConstraints().disconnect(beginboneconstraints_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Subscribe to an event saving an ID and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////

// define a connection ID to be used to unsubscribe later
EventConnectionId beginboneconstraints_handler_id;

// subscribe for the BeginBoneConstraints event with a lambda handler function and keeping connection ID
beginboneconstraints_handler_id = objectmeshskinnedlegacy->getEventBeginBoneConstraints().connect([](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginBoneConstraints (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
objectmeshskinnedlegacy->getEventBeginBoneConstraints().disconnect(beginboneconstraints_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Ignoring all BeginBoneConstraints events when necessary
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
objectmeshskinnedlegacy->getEventBeginBoneConstraints().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectmeshskinnedlegacy->getEventBeginBoneConstraints().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<ObjectMeshSkinnedLegacy> & **skinned**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginBoneConstraints
void beginboneconstraints_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события BeginBoneConstraints\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginboneconstraints_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginBoneConstraints().connect(beginboneconstraints_event_connections, beginboneconstraints_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginBoneConstraints().connect(beginboneconstraints_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginBoneConstraints (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginboneconstraints_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginboneconstraints_event_connection;

// подписываемся на событие BeginBoneConstraints с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginBoneConstraints().connect(beginboneconstraints_event_connection, beginboneconstraints_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginboneconstraints_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginboneconstraints_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginBoneConstraints через соединение
beginboneconstraints_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginBoneConstraints, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события BeginBoneConstraints\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginBoneConstraints().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginboneconstraints_handler_id;

// подписываемся на событие BeginBoneConstraints с лямбда-обработчиком, сохраняя идентификатор соединения
beginboneconstraints_handler_id = publisher->getEventBeginBoneConstraints().connect(e_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginBoneConstraints (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginBoneConstraints().disconnect(beginboneconstraints_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginBoneConstraints при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginBoneConstraints().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginBoneConstraints().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < ObjectMeshSkinnedLegacy > &> getEventEndIKSolvers () const

Событие, вызываемое после применения решателей IK. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события EndIKSolvers
void endiksolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события EndIKSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endiksolvers_event_connections;

// link to this instance when subscribing for an event (subscription for various events can be linked)
objectmeshskinnedlegacy->getEventEndIKSolvers().connect(endiksolvers_event_connections, endiksolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
objectmeshskinnedlegacy->getEventEndIKSolvers().connect(endiksolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndIKSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endiksolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endiksolvers_event_connection;

// subscribe for the EndIKSolvers event with a handler function keeping the connection
objectmeshskinnedlegacy->getEventEndIKSolvers().connect(endiksolvers_event_connection, endiksolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endiksolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endiksolvers_event_connection.setEnabled(true);

// ...

// remove subscription for the EndIKSolvers event via the connection
endiksolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndIKSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события EndIKSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
objectmeshskinnedlegacy->getEventEndIKSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. You can subscribe and unsubscribe via the handler function directly
//////////////////////////////////////////////////////////////////////////////

// subscribe for the EndIKSolvers event with a handler function
objectmeshskinnedlegacy->getEventEndIKSolvers().connect(endiksolvers_event_handler);

// remove subscription for the EndIKSolvers event later by the handler function
objectmeshskinnedlegacy->getEventEndIKSolvers().disconnect(endiksolvers_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Subscribe to an event saving an ID and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////

// define a connection ID to be used to unsubscribe later
EventConnectionId endiksolvers_handler_id;

// subscribe for the EndIKSolvers event with a lambda handler function and keeping connection ID
endiksolvers_handler_id = objectmeshskinnedlegacy->getEventEndIKSolvers().connect([](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndIKSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
objectmeshskinnedlegacy->getEventEndIKSolvers().disconnect(endiksolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Ignoring all EndIKSolvers events when necessary
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
objectmeshskinnedlegacy->getEventEndIKSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectmeshskinnedlegacy->getEventEndIKSolvers().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<ObjectMeshSkinnedLegacy> & **skinned**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndIKSolvers
void endiksolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события EndIKSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endiksolvers_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndIKSolvers().connect(endiksolvers_event_connections, endiksolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndIKSolvers().connect(endiksolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndIKSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endiksolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endiksolvers_event_connection;

// подписываемся на событие EndIKSolvers с функцией-обработчиком, сохраняя соединение
publisher->getEventEndIKSolvers().connect(endiksolvers_event_connection, endiksolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endiksolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endiksolvers_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndIKSolvers через соединение
endiksolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndIKSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события EndIKSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndIKSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endiksolvers_handler_id;

// подписываемся на событие EndIKSolvers с лямбда-обработчиком, сохраняя идентификатор соединения
endiksolvers_handler_id = publisher->getEventEndIKSolvers().connect(e_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndIKSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndIKSolvers().disconnect(endiksolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndIKSolvers при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndIKSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndIKSolvers().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < ObjectMeshSkinnedLegacy > &> getEventBeginIKSolvers () const

Событие, вызываемое перед применением решателей IK. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события BeginIKSolvers
void beginiksolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события BeginIKSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginiksolvers_event_connections;

// link to this instance when subscribing for an event (subscription for various events can be linked)
objectmeshskinnedlegacy->getEventBeginIKSolvers().connect(beginiksolvers_event_connections, beginiksolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
objectmeshskinnedlegacy->getEventBeginIKSolvers().connect(beginiksolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginIKSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginiksolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginiksolvers_event_connection;

// subscribe for the BeginIKSolvers event with a handler function keeping the connection
objectmeshskinnedlegacy->getEventBeginIKSolvers().connect(beginiksolvers_event_connection, beginiksolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginiksolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginiksolvers_event_connection.setEnabled(true);

// ...

// remove subscription for the BeginIKSolvers event via the connection
beginiksolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginIKSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события BeginIKSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
objectmeshskinnedlegacy->getEventBeginIKSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. You can subscribe and unsubscribe via the handler function directly
//////////////////////////////////////////////////////////////////////////////

// subscribe for the BeginIKSolvers event with a handler function
objectmeshskinnedlegacy->getEventBeginIKSolvers().connect(beginiksolvers_event_handler);

// remove subscription for the BeginIKSolvers event later by the handler function
objectmeshskinnedlegacy->getEventBeginIKSolvers().disconnect(beginiksolvers_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Subscribe to an event saving an ID and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////

// define a connection ID to be used to unsubscribe later
EventConnectionId beginiksolvers_handler_id;

// subscribe for the BeginIKSolvers event with a lambda handler function and keeping connection ID
beginiksolvers_handler_id = objectmeshskinnedlegacy->getEventBeginIKSolvers().connect([](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginIKSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
objectmeshskinnedlegacy->getEventBeginIKSolvers().disconnect(beginiksolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Ignoring all BeginIKSolvers events when necessary
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
objectmeshskinnedlegacy->getEventBeginIKSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectmeshskinnedlegacy->getEventBeginIKSolvers().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<ObjectMeshSkinnedLegacy> & **skinned**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginIKSolvers
void beginiksolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события BeginIKSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginiksolvers_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginIKSolvers().connect(beginiksolvers_event_connections, beginiksolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginIKSolvers().connect(beginiksolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginIKSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginiksolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginiksolvers_event_connection;

// подписываемся на событие BeginIKSolvers с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginIKSolvers().connect(beginiksolvers_event_connection, beginiksolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginiksolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginiksolvers_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginIKSolvers через соединение
beginiksolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginIKSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события BeginIKSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginIKSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginiksolvers_handler_id;

// подписываемся на событие BeginIKSolvers с лямбда-обработчиком, сохраняя идентификатор соединения
beginiksolvers_handler_id = publisher->getEventBeginIKSolvers().connect(e_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginIKSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginIKSolvers().disconnect(beginiksolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginIKSolvers при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginIKSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginIKSolvers().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < ObjectMeshSkinnedLegacy > &> getEventEndLookAtSolvers () const

Событие, вызываемое после применения решателей LookAtChain. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события EndLookAtSolvers
void endlookatsolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события EndLookAtSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endlookatsolvers_event_connections;

// link to this instance when subscribing for an event (subscription for various events can be linked)
objectmeshskinnedlegacy->getEventEndLookAtSolvers().connect(endlookatsolvers_event_connections, endlookatsolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
objectmeshskinnedlegacy->getEventEndLookAtSolvers().connect(endlookatsolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndLookAtSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endlookatsolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endlookatsolvers_event_connection;

// subscribe for the EndLookAtSolvers event with a handler function keeping the connection
objectmeshskinnedlegacy->getEventEndLookAtSolvers().connect(endlookatsolvers_event_connection, endlookatsolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endlookatsolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endlookatsolvers_event_connection.setEnabled(true);

// ...

// remove subscription for the EndLookAtSolvers event via the connection
endlookatsolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndLookAtSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события EndLookAtSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
objectmeshskinnedlegacy->getEventEndLookAtSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. You can subscribe and unsubscribe via the handler function directly
//////////////////////////////////////////////////////////////////////////////

// subscribe for the EndLookAtSolvers event with a handler function
objectmeshskinnedlegacy->getEventEndLookAtSolvers().connect(endlookatsolvers_event_handler);

// remove subscription for the EndLookAtSolvers event later by the handler function
objectmeshskinnedlegacy->getEventEndLookAtSolvers().disconnect(endlookatsolvers_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Subscribe to an event saving an ID and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////

// define a connection ID to be used to unsubscribe later
EventConnectionId endlookatsolvers_handler_id;

// subscribe for the EndLookAtSolvers event with a lambda handler function and keeping connection ID
endlookatsolvers_handler_id = objectmeshskinnedlegacy->getEventEndLookAtSolvers().connect([](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndLookAtSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
objectmeshskinnedlegacy->getEventEndLookAtSolvers().disconnect(endlookatsolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Ignoring all EndLookAtSolvers events when necessary
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
objectmeshskinnedlegacy->getEventEndLookAtSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectmeshskinnedlegacy->getEventEndLookAtSolvers().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<ObjectMeshSkinnedLegacy> & **skinned**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события EndLookAtSolvers
void endlookatsolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события EndLookAtSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections endlookatsolvers_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEndLookAtSolvers().connect(endlookatsolvers_event_connections, endlookatsolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEndLookAtSolvers().connect(endlookatsolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndLookAtSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
endlookatsolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection endlookatsolvers_event_connection;

// подписываемся на событие EndLookAtSolvers с функцией-обработчиком, сохраняя соединение
publisher->getEventEndLookAtSolvers().connect(endlookatsolvers_event_connection, endlookatsolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
endlookatsolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
endlookatsolvers_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие EndLookAtSolvers через соединение
endlookatsolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события EndLookAtSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события EndLookAtSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEndLookAtSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId endlookatsolvers_handler_id;

// подписываемся на событие EndLookAtSolvers с лямбда-обработчиком, сохраняя идентификатор соединения
endlookatsolvers_handler_id = publisher->getEventEndLookAtSolvers().connect(e_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события EndLookAtSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEndLookAtSolvers().disconnect(endlookatsolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий EndLookAtSolvers при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEndLookAtSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEndLookAtSolvers().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < ObjectMeshSkinnedLegacy > &> getEventBeginLookAtSolvers () const

Событие, вызываемое перед применением решателей LookAtChain. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события BeginLookAtSolvers
void beginlookatsolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события BeginLookAtSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginlookatsolvers_event_connections;

// link to this instance when subscribing for an event (subscription for various events can be linked)
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().connect(beginlookatsolvers_event_connections, beginlookatsolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().connect(beginlookatsolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginLookAtSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginlookatsolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginlookatsolvers_event_connection;

// subscribe for the BeginLookAtSolvers event with a handler function keeping the connection
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().connect(beginlookatsolvers_event_connection, beginlookatsolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginlookatsolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginlookatsolvers_event_connection.setEnabled(true);

// ...

// remove subscription for the BeginLookAtSolvers event via the connection
beginlookatsolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginLookAtSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события BeginLookAtSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. You can subscribe and unsubscribe via the handler function directly
//////////////////////////////////////////////////////////////////////////////

// subscribe for the BeginLookAtSolvers event with a handler function
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().connect(beginlookatsolvers_event_handler);

// remove subscription for the BeginLookAtSolvers event later by the handler function
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().disconnect(beginlookatsolvers_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Subscribe to an event saving an ID and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////

// define a connection ID to be used to unsubscribe later
EventConnectionId beginlookatsolvers_handler_id;

// subscribe for the BeginLookAtSolvers event with a lambda handler function and keeping connection ID
beginlookatsolvers_handler_id = objectmeshskinnedlegacy->getEventBeginLookAtSolvers().connect([](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginLookAtSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().disconnect(beginlookatsolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Ignoring all BeginLookAtSolvers events when necessary
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectmeshskinnedlegacy->getEventBeginLookAtSolvers().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<ObjectMeshSkinnedLegacy> & **skinned**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события BeginLookAtSolvers
void beginlookatsolvers_event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события BeginLookAtSolvers\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections beginlookatsolvers_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventBeginLookAtSolvers().connect(beginlookatsolvers_event_connections, beginlookatsolvers_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventBeginLookAtSolvers().connect(beginlookatsolvers_event_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginLookAtSolvers (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
beginlookatsolvers_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection beginlookatsolvers_event_connection;

// подписываемся на событие BeginLookAtSolvers с функцией-обработчиком, сохраняя соединение
publisher->getEventBeginLookAtSolvers().connect(beginlookatsolvers_event_connection, beginlookatsolvers_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
beginlookatsolvers_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
beginlookatsolvers_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие BeginLookAtSolvers через соединение
beginlookatsolvers_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события BeginLookAtSolvers, реализованный как член класса
	void event_handler(const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события BeginLookAtSolvers\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventBeginLookAtSolvers().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId beginlookatsolvers_handler_id;

// подписываемся на событие BeginLookAtSolvers с лямбда-обработчиком, сохраняя идентификатор соединения
beginlookatsolvers_handler_id = publisher->getEventBeginLookAtSolvers().connect(e_connections, [](const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события BeginLookAtSolvers (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventBeginLookAtSolvers().disconnect(beginlookatsolvers_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий BeginLookAtSolvers при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventBeginLookAtSolvers().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventBeginLookAtSolvers().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<float, const Ptr < ObjectMeshSkinnedLegacy > &> getEventUpdate () const

Событие, вызываемое, когда движок вызывает обновление объекта. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**


```cpp
// реализация обработчика события Update
void update_event_handler(float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события Update\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections update_event_connections;

// link to this instance when subscribing for an event (subscription for various events can be linked)
objectmeshskinnedlegacy->getEventUpdate().connect(update_event_connections, update_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
objectmeshskinnedlegacy->getEventUpdate().connect(update_event_connections, [](float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события Update (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
update_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection update_event_connection;

// subscribe for the Update event with a handler function keeping the connection
objectmeshskinnedlegacy->getEventUpdate().connect(update_event_connection, update_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
update_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
update_event_connection.setEnabled(true);

// ...

// remove subscription for the Update event via the connection
update_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Update, реализованный как член класса
	void event_handler(float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события Update\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
objectmeshskinnedlegacy->getEventUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//  4. You can subscribe and unsubscribe via the handler function directly
//////////////////////////////////////////////////////////////////////////////

// subscribe for the Update event with a handler function
objectmeshskinnedlegacy->getEventUpdate().connect(update_event_handler);

// remove subscription for the Update event later by the handler function
objectmeshskinnedlegacy->getEventUpdate().disconnect(update_event_handler);

//////////////////////////////////////////////////////////////////////////////
//   5. Subscribe to an event saving an ID and unsubscribe later by this ID
//////////////////////////////////////////////////////////////////////////////

// define a connection ID to be used to unsubscribe later
EventConnectionId update_handler_id;

// subscribe for the Update event with a lambda handler function and keeping connection ID
update_handler_id = objectmeshskinnedlegacy->getEventUpdate().connect([](float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события Update (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
objectmeshskinnedlegacy->getEventUpdate().disconnect(update_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   6. Ignoring all Update events when necessary
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
objectmeshskinnedlegacy->getEventUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
objectmeshskinnedlegacy->getEventUpdate().setEnabled(true);
```

</details>


> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(float **ifps**, const Ptr<ObjectMeshSkinnedLegacy> & **skinned**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Update
void update_event_handler(float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned)
{
	Log::message("\Обработка события Update\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections update_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventUpdate().connect(update_event_connections, update_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventUpdate().connect(update_event_connections, [](float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события Update (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
update_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection update_event_connection;

// подписываемся на событие Update с функцией-обработчиком, сохраняя соединение
publisher->getEventUpdate().connect(update_event_connection, update_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
update_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
update_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Update через соединение
update_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Update, реализованный как член класса
	void event_handler(float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned)
	{
		Log::message("\Обработка события Update\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId update_handler_id;

// подписываемся на событие Update с лямбда-обработчиком, сохраняя идентификатор соединения
update_handler_id = publisher->getEventUpdate().connect(e_connections, [](float ifps,  const Ptr<ObjectMeshSkinnedLegacy> & skinned) {
		Log::message("\Обработка события Update (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventUpdate().disconnect(update_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Update при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## int getNumBoneConstraints () const

Возвращает текущее общее количество ограничений вращения костей.
### Возвращаемое значение

Текущее общее количество ограничений.
## void setInterpolationAccuracy ( ObjectMeshSkinnedLegacy::INTERPOLATION_ACCURACY accuracy )

Задаёт новый режим интерполяции для вращений костей. Значение по умолчанию: HIGH.
### Аргументы

- *[ObjectMeshSkinnedLegacy::INTERPOLATION_ACCURACY](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md#INTERPOLATION_ACCURACY)* **accuracy** - Режим интерполяции для вращений костей. Значение по умолчанию: HIGH.

## ObjectMeshSkinnedLegacy::INTERPOLATION_ACCURACY getInterpolationAccuracy () const

Возвращает текущий режим интерполяции для вращений костей. Значение по умолчанию: HIGH.
### Возвращаемое значение

Текущий режим интерполяции для вращений костей. Значение по умолчанию: HIGH.
## void setAnimPath ( const char * path )

Задаёт новый путь к файлу, содержащему указанную анимацию.
### Аргументы

- *const char ** **path** - Путь к файлу, содержащему указанную анимацию.

## const char * getAnimPath () const

Возвращает текущий путь к файлу, содержащему указанную анимацию.
### Возвращаемое значение

Текущий путь к файлу, содержащему указанную анимацию.
## void setMeshProceduralMode ( bool mode )

Задаёт новое значение, указывающее, включён ли для объекта [procedural mesh usage mode](#procedural_modification). При включённом процедурном режиме геометрию **ObjectMeshSkinnedLegacy** можно изменять через *[applyMeshProcedural()](../../...md#applyMeshProcedural_ConstMeshSkinned_int)*. Отключение процедурного режима восстанавливает исходную геометрию объекта, удаляя все применённые изменения. Для skinned-мешей процедурное редактирование геометрии выполняется только через прямой рабочий процесс в главном потоке, в отличие от статических мешей, которые могут использовать асинхронную генерацию или [other update strategies](../../../api/library/objects/class.objectmeshstatic_cpp.md#procedural_workflow).
### Аргументы

- *bool* **mode** - Установите **true**, чтобы включить процедурный режим для меша; **false** — чтобы отключить.

## bool isMeshProceduralMode () const

Возвращает текущее значение, указывающее, включён ли для объекта [procedural mesh usage mode](#procedural_modification). При включённом процедурном режиме геометрию **ObjectMeshSkinnedLegacy** можно изменять через *[applyMeshProcedural()](../../...md#applyMeshProcedural_ConstMeshSkinned_int)*. Отключение процедурного режима восстанавливает исходную геометрию объекта, удаляя все применённые изменения. Для skinned-мешей процедурное редактирование геометрии выполняется только через прямой рабочий процесс в главном потоке, в отличие от статических мешей, которые могут использовать асинхронную генерацию или [other update strategies](../../../api/library/objects/class.objectmeshstatic_cpp.md#procedural_workflow).
### Возвращаемое значение

**true**, если процедурный режим для меша включён; иначе **false**.
## bool isLoaded () const

Возвращает текущее значение, указывающее, загружен ли меш (он либо процедурный, либо загружен методом [setMeshPath()](#setMeshPath_cstr_void)).
### Возвращаемое значение

**true**, если меш процедурный или загружен из файла меша; иначе **false**.
## void setMeshPath ( const char * path )

Задаёт новый путь к файлу меша. Если для объекта включён флаг *Procedural*, меш не будет загружен.
### Аргументы

- *const char ** **path** - Путь к файлу меша.

## const char * getMeshPath () const

Возвращает текущий путь к файлу меша. Если для объекта включён флаг *Procedural*, меш не будет загружен.
### Возвращаемое значение

Текущий путь к файлу меша.
---

## static ObjectMeshSkinnedLegacyPtr create ( const char * path )

Конструктор ObjectMeshSkinnedLegacy.
### Аргументы

- *const char ** **path** - Путь к файлу skinned-меша.

## static ObjectMeshSkinnedLegacyPtr create ( )

Конструктор ObjectMeshSkinnedLegacy.
## int getBoneChild ( int bone , int child ) const

Возвращает номер потомка указанной кости.
### Аргументы

- *int* **bone** - Номер кости.
- *int* **child** - Номер потомка.

### Возвращаемое значение

Номер потомка в коллекции всех костей.
## void setBoneTransformWithChildren ( int bone , const Math:: mat4 & transform )

Задаёт трансформацию для кости и всех её потомков (без учёта трансформаций узла).
> **Notice:** Кости могут масштабироваться только равномерно.


### Аргументы

- *int* **bone** - Номер кости.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## const char * getBoneName ( int bone ) const

Возвращает имя указанной кости.
### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Имя кости.
## int getBoneParent ( int bone ) const

Возвращает номер родительской кости для указанной кости.
### Аргументы

- *int* **bone** - Номер кости, для которой будет возвращён родитель.

### Возвращаемое значение

Номер родительской кости, если родитель существует; иначе -1.
## void setBoneTransform ( int bone , const Math:: mat4 & transform )

Задаёт матрицу трансформации для указанной кости (без учёта трансформаций узла).
> **Notice:** Кости могут масштабироваться только равномерно.


### Аргументы

- *int* **bone** - Номер кости.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации.

## Math:: mat4 getBoneTransform ( int bone ) const

Возвращает матрицу трансформации указанной кости относительно родительского объекта (без учёта трансформаций самого узла Mesh Skinned).
### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Матрица трансформации.
## void setBoneTransforms ( const int * bones , const Math:: mat4 * transforms , int num_bones )

Задаёт матрицу трансформации для указанных костей.
### Аргументы

- *const int ** **bones** - Номера костей.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) ** **transforms** - Матрицы трансформации.
- *int* **num_bones** - Количество костей.

## int getCIndex ( int num , int surface ) const

Возвращает [coordinate index](../../../api/library/rendering/class.mesh_cpp.md#cindices) для указанной вершины указанной поверхности.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества координатных индексов указанной поверхности. > **Notice:** Чтобы получить общее количество координатных индексов для указанной поверхности, используйте метод [getNumCIndices()](#getNumCIndices_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Координатный индекс.
## Math:: vec4 getColor ( int num , int surface ) const

Возвращает цвет указанной [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) указанной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) в диапазоне от 0 до общего количества записей цветов вершин указанной поверхности. > **Notice:** Чтобы получить общее количество записей цветов вершин для поверхности, вызовите метод [*getNumColors()*](#getNumColors_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Цвет вершины.
## void setLayer ( int layer , bool enabled , float weight )

Включает или отключает указанный слой анимации и задаёт значение параметра weight.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *bool* **enabled** - Флаг включения. true для включения слоя, false для отключения.
- *float* **weight** - Вес слоя анимации.

## void setLayerEnabled ( int layer , bool enabled )

Включает или отключает указанный слой анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *bool* **enabled** - true для включения слоя анимации, false для отключения.

## bool isLayerEnabled ( int layer ) const

Возвращает значение, указывающее, включён ли указанный слой анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.

### Возвращаемое значение

true, если слой отключён; иначе false.
## void setLayerWeight ( int layer , float weight )

Задаёт вес слоя анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *float* **weight** - Вес слоя анимации.

## float getLayerWeight ( int layer ) const

Возвращает вес слоя анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.

### Возвращаемое значение

Вес слоя анимации.
## bool getMesh ( Ptr < MeshSkinned > & mesh ) const

Копирует текущий меш в целевой меш.
```cpp
// skinned-меш, из которого будет получена геометрия
ObjectMeshSkinnedLegacyPtr skinnedMesh = ObjectMeshSkinnedLegacy::create("skinned.mesh");
// создаём новый меш
MeshSkinnedPtr mesh = MeshSkinned::create();
// копируем геометрию в созданный меш
if (skinnedMesh->getMesh(mesh)) {
	// выполняем какие-то действия с полученным мешем
}
else {
	Log::error("Не удалось скопировать меш\n");
}

```


### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshSkinned](../../../api/library/rendering/class.meshskinned_cpp.md)> &* **mesh** - Целевой меш для копирования.

### Возвращаемое значение

**1**, если меш успешно скопирован; иначе **0**.
## bool getMeshSurface ( const Ptr < Mesh > & mesh , int surface , int target = -1 ) const

Копирует указанную поверхность меша в целевой меш.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Целевой [Mesh](../../../api/library/rendering/class.mesh_cpp.md), в который копируется поверхность.
- *int* **surface** - Номер поверхности меша, которую нужно скопировать.
- *int* **target** - Номер морф-таргета поверхности, который нужно скопировать. Значение по умолчанию: -1 (все морф-таргеты).

### Возвращаемое значение

Номер новой добавленной поверхности меша.
## Math:: vec3 getNormal ( int num , int surface , int target = 0 ) const

Возвращает нормаль для указанной [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) указанного таргета поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) в диапазоне от 0 до общего количества записей касательных вершин указанного таргета поверхности. > **Notice:** Нормали вершин вычисляются с использованием касательных вершин. Чтобы получить общее количество записей касательных вершин для таргета поверхности, вызовите метод [*getNumTangents()*](#getNumTangents_int_int).
- *int* **surface** - Номер поверхности меша.
- *int* **target** - Номер таргета поверхности. Значение по умолчанию: 0.

### Возвращаемое значение

Нормаль вершины.
## int getNumBoneChildren ( int bone ) const

Возвращает количество потомков указанной кости.
### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Количество дочерних костей.
## int getNumCIndices ( int surface ) const

Возвращает количество [coordinate indices](../../../api/library/rendering/class.mesh_cpp.md#cindices) для указанной поверхности меша.
### Аргументы

- *int* **surface** - Mesh surface number.

### Возвращаемое значение

Количество координатных индексов.
## int getNumColors ( int surface ) const

Возвращает общее количество записей цветов вершин для указанной поверхности.
> **Notice:** Цвета задаются для [triangle vertices](../../../api/library/rendering/class.mesh_cpp.md#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности.

### Возвращаемое значение

Количество записей цветов вершин.
## int getNumSurfaceTargets ( int surface ) const

Возвращает количество морф-таргетов поверхности для указанной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество морф-таргетов поверхности.
## int getNumTangents ( int surface ) const

Возвращает количество записей касательных вершин для указанной поверхности меша.
> **Notice:** Касательные задаются для [triangle vertices](../../../api/library/rendering/class.mesh_cpp.md#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество касательных векторов поверхности.
## int getNumTexCoords0 ( int surface ) const

Возвращает количество текстурных координат первой UV-карты для указанной поверхности меша.
> **Notice:** Текстурные координаты первой UV-карты задаются для [triangle vertices](../../../api/library/rendering/class.mesh_cpp.md#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество текстурных координат первой UV-карты.
## int getNumTexCoords1 ( int surface ) const

Возвращает количество текстурных координат второй UV-карты для указанной поверхности меша.
> **Notice:** Текстурные координаты второй UV-карты задаются для [triangle vertices](../../../api/library/rendering/class.mesh_cpp.md#tvertex).


### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество текстурных координат второй UV-карты.
## int getNumTIndices ( int surface ) const

Возвращает количество индексов треугольников для указанной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество [triangle indices](../../../api/library/rendering/class.mesh_cpp.md#tindices).
## int getNumVertex ( int surface ) const

Возвращает количество [coordinate vertices](../../../api/library/rendering/class.mesh_cpp.md#cvertex) для указанной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Количество вершин поверхности.
## Math:: vec3 getSkinnedNormal ( int num , int index , int surface ) const

Возвращает skinned-нормаль для указанной [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex).
> **Notice:** Skinned-нормаль — это пересчитанная нормаль с учётом костей и морф-таргетов, используемых в скининге.


### Аргументы

- *int* **num** - Номер [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) в диапазоне от 0 до общего количества записей касательных вершин указанного таргета поверхности. > **Notice:** Нормали вершин вычисляются с использованием касательных вершин. Чтобы получить общее количество записей касательных вершин для таргета поверхности, вызовите метод [*getNumTangents()*](#getNumTangents_int_int).
- *int* **index** - [Coordinate index](../../../api/library/rendering/class.mesh_cpp.md#cindices) вершины. > **Notice:** если передано -1, координатный индекс будет получен для первой вершины, чей [triangle index](../../../api/library/rendering/class.mesh_cpp.md#tindices) равен указанному номеру [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Skinned-нормаль.
## Math:: quat getSkinnedTangent ( int num , int index , int surface ) const

Возвращает skinned-касательный вектор для указанной [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex).
> **Notice:** Skinned-касательный вектор — это пересчитанный касательный вектор с учётом костей и морф-таргетов, используемых в скининге.


### Аргументы

- *int* **num** - Номер [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) в диапазоне от 0 до общего количества записей касательных вершин указанного таргета поверхности. > **Notice:** Чтобы получить общее количество записей касательных вершин для таргета поверхности, вызовите метод [*getNumTangents()*](#getNumTangents_int_int).
- *int* **index** - [Coordinate index](../../../api/library/rendering/class.mesh_cpp.md#cindices) вершины. > **Notice:** если передано -1, координатный индекс будет получен для первой вершины, чей [triangle index](../../../api/library/rendering/class.mesh_cpp.md#tindices) равен указанному номеру [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Skinned-касательная.
## Math:: vec3 getSkinnedVertex ( int num , int surface ) const

Возвращает skinned-координаты указанной [coordinate vertex](../../../api/library/rendering/class.mesh_cpp.md#cvertex).
> **Notice:** Skinned-вершина — это пересчитанная вершина с учётом костей и морф-таргетов, используемых в скининге.


### Аргументы

- *int* **num** - Номер [coordinate vertex](../../../api/library/rendering/class.mesh_cpp.md#cvertex) в диапазоне от 0 до общего количества координатных вершин указанной поверхности. > **Notice:** Чтобы получить общее количество координатных вершин для указанной поверхности, используйте метод [getNumVertex()](#getNumVertex_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Координаты вершины.
## bool isNeedUpdate ( ) const

Возвращает значение, указывающее, требуется ли обновление *ObjectMeshSkinnedLegacy* (например, после добавления новых анимаций).
### Возвращаемое значение

true, если skinned-меш требует обновления; иначе false.
## const char * getSurfaceTargetName ( int surface , int target ) const

Возвращает имя морф-таргета для указанной поверхности меша.
### Аргументы

- *int* **surface** - Номер поверхности меша.
- *int* **target** - Номер морф-таргета.

### Возвращаемое значение

Имя морф-таргета.
## Math:: quat getTangent ( int num , int surface , int target = 0 ) const

Возвращает касательную для указанной [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) указанного таргета поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) в диапазоне от 0 до общего количества записей касательных вершин указанной поверхности. > **Notice:** Чтобы получить общее количество записей касательных вершин для поверхности, вызовите метод [getNumTangents()](#getNumTangents_int_int).
- *int* **surface** - Номер поверхности меша.
- *int* **target** - Номер таргета поверхности. Значение по умолчанию: 0.

### Возвращаемое значение

Касательная вершины.
## Math:: vec2 getTexCoord0 ( int num , int surface ) const

Возвращает текстурные координаты первой UV-карты для указанной [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) указанной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) в диапазоне от 0 до общего количества записей текстурных координат первой UV-карты указанной поверхности. > **Notice:** Чтобы получить общее количество записей текстурных координат первой UV-карты для поверхности, вызовите метод [getNumTexCoords0()](#getNumTexCoords0_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Текстурные координаты первой UV-карты.
## Math:: vec2 getTexCoord1 ( int num , int surface ) const

Возвращает текстурные координаты второй UV-карты для указанной [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) указанной поверхности.
### Аргументы

- *int* **num** - Номер [triangle vertex](../../../api/library/rendering/class.mesh_cpp.md#tvertex) в диапазоне от 0 до общего количества записей текстурных координат второй UV-карты указанной поверхности. > **Notice:** Чтобы получить общее количество записей текстурных координат второй UV-карты для поверхности, вызовите метод [getNumTexCoords1()](#getNumTexCoords1_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Текстурные координаты второй UV-карты.
## int getTIndex ( int num , int surface ) const

Возвращает [triangle index](../../../api/library/rendering/class.mesh_cpp.md#tindices) для указанной поверхности по номеру индекса.
### Аргументы

- *int* **num** - Номер вершины в диапазоне от 0 до общего количества индексов треугольников для указанной поверхности. > **Notice:** Чтобы получить общее количество индексов треугольников для указанной поверхности, используйте метод [getNumTIndices()](#getNumTIndices_int_int).
- *int* **surface** - Номер поверхности меша.

### Возвращаемое значение

Индекс треугольника.
## Math:: vec3 getVertex ( int num , int surface , int target = 0 ) const

Возвращает координаты указанной [coordinate vertex](../../../api/library/rendering/class.mesh_cpp.md#cvertex) указанного таргета поверхности.
### Аргументы

- *int* **num** - Номер [coordinate vertex](../../../api/library/rendering/class.mesh_cpp.md#cvertex) в диапазоне от 0 до общего количества координатных вершин указанной поверхности. > **Notice:** Чтобы получить общее количество координатных вершин для указанной поверхности, используйте метод [getNumCVertex()](../../../api/library/rendering/class.mesh_cpp.md#getNumCVertex_int_int).
- *int* **surface** - Номер поверхности меша.
- *int* **target** - Номер таргета поверхности. Значение по умолчанию: 0.

### Возвращаемое значение

Координаты вершины.
## void setBoneWorldTransformWithChildren ( int bone , const Math:: Mat4 & transform )

Задаёт трансформацию для указанной кости и всех её потомков в мировой системе координат (с учётом трансформаций узла).
> **Notice:** Кости могут масштабироваться только равномерно.


### Аргументы

- *int* **bone** - Номер кости.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации в мировом пространстве.

## void setBoneWorldTransform ( int bone , const Math:: Mat4 & transform )

Задаёт трансформацию для указанной кости в мировой системе координат.
> **Notice:** Кости могут масштабироваться только равномерно.


### Аргументы

- *int* **bone** - Номер кости.
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации в мировом пространстве.

## Math:: Mat4 getBoneWorldTransform ( int bone ) const

Возвращает текущую матрицу трансформации, применённую к кости в мировой системе координат (с учётом трансформаций узла).
### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Матрица трансформации в мировом пространстве.
## void getObjectPose ( const Ptr < SkeletonPoseMatrix > & out_pose ) const

Записывает текущие трансформации костей в пространстве объекта (результат смешивания всех слоёв анимации) в указанный [SkeletonPoseMatrix](../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseMatrix](../../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)> &* **out_pose** - Выходная поза, в которую записываются трансформации костей в пространстве объекта.

## int addLayer ( )

Добавляет новый слой анимации к текущему мешу.
### Возвращаемое значение

Номер нового добавленного слоя анимации.
## void clearLayer ( int layer )

Очищает указанный слой анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.

## void copyLayer ( int dest , int src )


Копирует трансформации костей исходного слоя в целевой слой. Условия копирования следующие:


- Если у целевого слоя больше костей, чем у исходного, он сохранит свои прежние трансформации.
- Если у исходного слоя больше костей, чем у целевого, эти кости будут добавлены в целевой слой.


### Аргументы

- *int* **dest** - Номер целевого слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *int* **src** - Номер исходного слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).

## int findBone ( const char * name ) const

Ищет кость с указанным именем.
### Аргументы

- *const char ** **name** - Имя кости.

### Возвращаемое значение

Номер кости, если найдена; иначе -1.
## int findSurfaceTarget ( int surface , const char * name ) const

Ищет морф-таргет поверхности с указанным именем.
### Аргументы

- *int* **surface** - Номер поверхности меша.
- *const char ** **name** - Имя морф-таргета.

### Возвращаемое значение

Номер морф-таргета, если существует; иначе **-1**.
## void importLayer ( int layer )

Копирует текущее состояние костей в указанный слой анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.

## void inverseLayer ( int dest , int src )

Копирует инвертированные трансформации костей из исходного слоя в целевой слой.
> **Notice:** Целевой слой не очищается перед записью в него трансформаций.


### Аргументы

- *int* **dest** - Номер целевого слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *int* **src** - Номер исходного слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).

## void lerpLayer ( int dest , int layer0 , int layer1 , float weight )

Копирует интерполированные трансформации костей из двух исходных слоёв в целевой слой.
> **Notice:** Если кость отсутствует в одном из исходных слоёв, трансформация кости из другого слоя будет скопирована в целевой слой без интерполяции.


### Аргументы

- *int* **dest** - Номер целевого слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *int* **layer0** - Номер первого исходного слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *int* **layer1** - Номер второго исходного слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *float* **weight** - Вес интерполяции.

## void lerpLayerByMask ( int dest , int layer0 , int layer1 , int mask_index , float weight )

Копирует интерполированные трансформации костей из двух исходных слоёв в целевой слой, используя указанную маску костей (по индексу) для управления весами смешивания по каждой кости.
### Аргументы

- *int* **dest** - Номер целевого слоя.
- *int* **layer0** - Номер первого исходного слоя.
- *int* **layer1** - Номер второго исходного слоя.
- *int* **mask_index** - Индекс маски костей, используемой для управления весами смешивания по каждой кости.
- *float* **weight** - Вес интерполяции.

## void lerpLayerByMask ( int dest , int layer0 , int layer1 , const char * mask_name , float weight )

Копирует интерполированные трансформации костей из двух исходных слоёв в целевой слой, используя указанную маску костей (по имени) для управления весами смешивания по каждой кости.
### Аргументы

- *int* **dest** - Номер целевого слоя.
- *int* **layer0** - Номер первого исходного слоя.
- *int* **layer1** - Номер второго исходного слоя.
- *const char ** **mask_name** - Имя маски костей, используемой для управления весами смешивания по каждой кости.
- *float* **weight** - Вес интерполяции.

## void mulLayer ( int dest , int layer0 , int layer1 , float weight = 1.0f )

Копирует перемноженные трансформации костей из двух исходных слоёв в целевой слой.
### Аргументы

- *int* **dest** - Номер целевого слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *int* **layer0** - Номер первого исходного слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *int* **layer1** - Номер второго исходного слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).
- *float* **weight** - Вес интерполяции.

## void play ( )

Продолжает воспроизведение анимации, если оно было приостановлено, или запускает воспроизведение, если оно было остановлено.
## void removeLayer ( int layer )

Удаляет слой анимации.
### Аргументы

- *int* **layer** - Номер слоя в диапазоне от 0 до общего количества слоёв анимации. > **Notice:** Чтобы получить общее количество слоёв анимации, используйте метод [getNumLayers()](#getNumLayers_int).

## void stop ( )

Останавливает воспроизведение анимации. Эта функция сохраняет позицию воспроизведения, чтобы можно было возобновить воспроизведение анимации с той же точки.
## void getBlendingLayersPose ( const Ptr < SkeletonPoseDecomposed > & pose ) const

Записывает финальную смешанную позу (результат смешивания всех включённых слоёв анимации согласно их весам) в указанный [SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md). Это предоставляет декомпозированное (позиция, вращение, масштаб) представление смешанного состояния анимации.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **pose** - Выходная поза, в которую записывается результат смешивания.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Node](../../../api/library/nodes/class.node_cpp.md).
## void updateSkinned ( )

Принудительно обновляет все трансформации костей.
## void setBindNode ( int bone , const Ptr < Node > & node )

Задаёт новый узел, трансформация которого будет использоваться для управления трансформацией кости с указанным номером.
### Аргументы

- *int* **bone** - Номер кости, управляемой указанным узлом, в диапазоне от 0 до [total number of bones](#getNumBones_int).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Узел, трансформация которого используется для управления трансформацией кости.

## void removeBindNodeByBone ( int bone )

Удаляет назначенный bind-узел с кости с указанным номером.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).

## void removeBindNodeByNode ( const Ptr < Node > & node )

Удаляет указанный bind-узел.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Bind-узел, который нужно удалить.

## void removeAllBindNode ( )

Удаляет все назначенные bind-узлы.
## Ptr < Node > getBindNode ( int bone ) const

Возвращает bind-узел, в данный момент назначенный кости с указанным номером.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).

### Возвращаемое значение

Узел, трансформация которого используется для управления трансформацией кости, если он назначен; иначе - nullptr.
## void setBindNodeSpace ( int bone , ObjectMeshSkinnedLegacy::NODE_SPACE space )

Задаёт новое значение, указывающее, какая трансформация bind-узла (*World* или *Local*) будет использоваться для переопределения трансформации указанной кости.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).
- *[ObjectMeshSkinnedLegacy::NODE_SPACE](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md#NODE_SPACE)* **space** - Тип трансформации bind-узла, используемой для переопределения трансформации указанной кости, одно из значений [*NODE_SPACE**](#NODE_SPACE_LOCAL).

## ObjectMeshSkinnedLegacy::NODE_SPACE getBindNodeSpace ( int bone ) const

Возвращает текущее значение, указывающее, какая трансформация bind-узла (*World* или *Local*) используется для переопределения трансформации указанной кости.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).

### Возвращаемое значение

Тип трансформации bind-узла, используемой для переопределения трансформации указанной кости, одно из значений [*NODE_SPACE**](#NODE_SPACE_LOCAL).
## void setBindBoneSpace ( int bone , ObjectMeshSkinnedLegacy::BONE_SPACE space )

Задаёт значение, указывающее, какая трансформация указанной кости будет переопределена трансформацией bind-узла.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).
- *[ObjectMeshSkinnedLegacy::BONE_SPACE](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md#BONE_SPACE)* **space** - Тип трансформации указанной кости, переопределяемый трансформацией bind-узла, одно из значений [*BONE_SPACE**](#BONE_SPACE_LOCAL).

## ObjectMeshSkinnedLegacy::BONE_SPACE getBindBoneSpace ( int bone ) const

Возвращает текущее значение, указывающее, какая трансформация указанной кости переопределяется трансформацией bind-узла.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).

### Возвращаемое значение

Текущий тип трансформации указанной кости, переопределяемый трансформацией bind-узла, одно из значений [*BONE_SPACE**](#BONE_SPACE_LOCAL).
## void setBindMode ( int bone , ObjectMeshSkinnedLegacy::BIND_MODE mode )

Задаёт новый тип смешивания трансформаций bind-узла и кости.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).
- *[ObjectMeshSkinnedLegacy::BIND_MODE](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md#BIND_MODE)* **mode** - Новый тип смешивания трансформаций bind-узла и кости:

  - **OVERRIDE** - заменяет трансформацию кости трансформацией узла.
  - **ADDITIVE** - трансформация узла добавляется к текущей трансформации кости.

## ObjectMeshSkinnedLegacy::BIND_MODE getBindMode ( int bone ) const

Возвращает текущий тип смешивания трансформаций bind-узла и кости.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).

### Возвращаемое значение

Текущий тип смешивания трансформаций bind-узла и кости:
- **OVERRIDE** - заменяет трансформацию кости трансформацией узла.
- **ADDITIVE** - трансформация узла добавляется к текущей трансформации кости.


## void setBindNodeOffset ( int bone , const Math:: Mat4 & offset )

Задаёт новую матрицу трансформации, применяемую к трансформации узла перед её применением к трансформации кости. Этот параметр служит для дополнительной коррекции трансформации узла относительно базиса кости.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).
- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **offset** - Матрица трансформации, применяемая к трансформации узла перед её применением к трансформации кости.

## Math:: Mat4 getBindNodeOffset ( int bone ) const

Возвращает текущую матрицу трансформации, применяемую к трансформации узла перед её применением к трансформации кости. Этот параметр служит для дополнительной коррекции трансформации узла относительно базиса кости.
### Аргументы

- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).

### Возвращаемое значение

Матрица трансформации, в данный момент применяемая к трансформации узла перед её применением к трансформации кости.
## void addVisualizeBone ( int bone )

Добавляет кость с указанным номером в список костей, для которых визуализируются базисные векторы.
### Аргументы

- *int* **bone** - Номер кости, которую нужно добавить в визуализатор, в диапазоне от 0 до [total number of bones](#getNumBones_int).

## void removeVisualizeBone ( int bone )

Удаляет кость с указанным номером из списка костей, для которых визуализируются базисные векторы.
### Аргументы

- *int* **bone** - Номер кости, которую нужно удалить из визуализатора, в диапазоне от 0 до [total number of bones](#getNumBones_int).

## void clearVisualizeBones ( )

Очищает список костей, для которых визуализируются базисные векторы.
## void addVisualizeIKChain ( int chain_id )

Добавляет [IK chain](#ik_chains) с указанным ID в список цепочек, для которых визуализируются базисные векторы.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

## void removeVisualizeIKChain ( int chain_id )

Удаляет [IK chain](#ik_chains) с указанным ID из списка цепочек, для которых визуализируются базисные векторы.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

## void clearVisualizeIKChain ( )

Очищает список [IK chains](#ik_chains), для которых визуализируются базисные векторы.
## int addIKChain ( )

Добавляет новую [IK chain](#ik_chains) к skinned-мешу.
### Возвращаемое значение

ID добавленной IK-цепочки.
## void removeIKChain ( int chain_id )

Удаляет [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

## void setIKChainEnabled ( bool enabled , int chain_id )

Задаёт значение, указывающее, включена ли [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить IK-цепочку с указанным ID, или **false** — чтобы отключить.
- *int* **chain_id** - ID IK-цепочки.

## bool isIKChainEnabled ( int chain_id ) const

Возвращает значение, указывающее, включена ли [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

**true**, если IK-цепочка с указанным ID включена; иначе **false**.
## void setIKChainWeight ( float weight , int chain_id )

Задаёт новый вес для [IK chain](#ik_chains) с указанным ID. Значение веса определяет влияние целевой позиции на последний сустав цепочки.
### Аргументы

- *float* **weight** - Новое значение веса, которое нужно задать, в диапазоне [0.0f, 1.0f]. *Более высокие* значения увеличивают влияние.
- *int* **chain_id** - ID IK-цепочки.

## float getIKChainWeight ( int chain_id ) const

Возвращает текущий вес для [IK chain](#ik_chains) с указанным ID. Значение веса определяет влияние целевой позиции на последний сустав цепочки.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Текущее значение веса в диапазоне [0.0f, 1.0f]. *Более высокие* значения увеличивают влияние.
## int addIKChainBone ( int bone , int chain_id )

Добавляет кость с указанным номером в [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **bone** - Номер кости.
- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Индекс последней добавленной кости в цепочке.
## int getIKChainNumBones ( int chain_id ) const

Возвращает количество костей в [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Количество костей в IK-цепочке с указанным ID.
## void removeIKChainBone ( int bone_num , int chain_id )

Удаляет кость с указанным номером из [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **bone_num** - Номер кости.
- *int* **chain_id** - ID IK-цепочки.

## int getIKChainBone ( int bone_num , int chain_id ) const

Возвращает индекс кости с указанным номером (внутри цепочки) из [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **bone_num** - Номер кости.
- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).
## void setIKChainTargetPosition ( const Math:: Vec3 & position , int chain_id )

Задаёт новые локальные координаты целевой позиции [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Новые локальные координаты целевой позиции, которые нужно задать для IK-цепочки с указанным ID.
- *int* **chain_id** - ID IK-цепочки.

## Math:: Vec3 getIKChainTargetPosition ( int chain_id ) const

Возвращает текущие локальные координаты целевой позиции [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Локальные координаты целевой позиции IK-цепочки с указанным ID.
## void setIKChainTargetWorldPosition ( const Math:: Vec3 & position , int chain_id )

Задаёт новые мировые координаты целевой позиции [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Новые мировые координаты целевой позиции, которые нужно задать для IK-цепочки с указанным ID.
- *int* **chain_id** - ID IK-цепочки.

## Math:: Vec3 getIKChainTargetWorldPosition ( int chain_id ) const

Возвращает текущие мировые координаты целевой позиции [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Мировые координаты целевой позиции IK-цепочки с указанным ID.
## void setIKChainPolePosition ( const Math:: Vec3 & position , int chain_id )

Задаёт новую позицию опорной точки (pole, в локальных координатах) для [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Новая позиция опорной точки (в локальных координатах), которую нужно задать для IK-цепочки.
- *int* **chain_id** - ID IK-цепочки.

## Math:: Vec3 getIKChainPolePosition ( int chain_id ) const

Возвращает текущую позицию опорной точки (pole, в локальных координатах) для [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Позиция опорной точки (в локальных координатах) для IK-цепочки.
## void setIKChainPoleWorldPosition ( const Math:: Vec3 & position , int chain_id )

Задаёт новую позицию опорной точки (pole, в мировых координатах) для [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Новая позиция опорной точки (в мировых координатах), которую нужно задать для IK-цепочки.
- *int* **chain_id** - ID IK-цепочки.

## Math:: Vec3 getIKChainPoleWorldPosition ( int chain_id ) const

Возвращает текущую позицию опорной точки (pole, в мировых координатах) для [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Позиция опорной точки (в мировых координатах) для IK-цепочки.
## void setIKChainUseEffectorRotation ( bool use , int chain_id )

Задаёт значение, указывающее, следует ли использовать вращение эффектора для [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *bool* **use** - **true**, чтобы использовать вращение эффектора для IK-цепочки с указанным ID; **false** — не использовать.
- *int* **chain_id** - ID IK-цепочки.

## bool isIKChainUseEffectorRotation ( int chain_id ) const

Возвращает значение, указывающее, используется ли вращение эффектора для [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

**true**, если вращение эффектора используется для IK-цепочки с указанным ID; иначе **false**.
## void setIKChainEffectorRotation ( const Math:: quat & rotation , int chain_id )

Задаёт вращение конечного эффектора (в локальных координатах) [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион, определяющий вращение (в локальных координатах) конечного эффектора цепочки.
- *int* **chain_id** - ID IK-цепочки.

## Math:: quat getIKChainEffectorRotation ( int chain_id ) const

Возвращает текущее вращение (в локальных координатах) конечного эффектора [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Кватернион, определяющий вращение (в локальных координатах) конечного эффектора цепочки.
## void setIKChainEffectorWorldRotation ( const Math:: quat & rotation , int chain_id )

Задаёт вращение конечного эффектора (в мировых координатах) [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **rotation** - Кватернион, определяющий вращение (в мировых координатах) конечного эффектора цепочки.
- *int* **chain_id** - ID IK-цепочки.

## Math:: quat getIKChainEffectorWorldRotation ( int chain_id ) const

Возвращает текущее вращение (в мировых координатах) конечного эффектора [IK chain](#ik_chains) с указанным ID.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Кватернион, определяющий вращение (в мировых координатах) конечного эффектора цепочки.
## void setIKChainNumIterations ( int num , int chain_id )

Задаёт количество итераций, используемых для решения [IK chain](#ik_chains) с указанным ID (количество запусков алгоритма).
### Аргументы

- *int* **num** - Количество итераций, используемых для решения IK-цепочки с указанным ID.
- *int* **chain_id** - ID IK-цепочки.

## int getIKChainNumIterations ( int chain_id ) const

Возвращает количество итераций, используемых для решения [IK chain](#ik_chains) с указанным ID (количество запусков алгоритма).
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Текущее количество итераций для IK-цепочки с указанным ID.
## void setIKChainTolerance ( float tolerance , int chain_id )

Задаёт новое значение допуска (tolerance), используемое для [IK chain](#ik_chains) с указанным ID. Это значение задаёт порог, при котором цель считается достигшей своего конечного положения, и решатель IK прекращает итерации.
### Аргументы

- *float* **tolerance** - Значение допуска, которое нужно задать для IK-цепочки.
- *int* **chain_id** - ID IK-цепочки.

## float getIKChainTolerance ( int chain_id ) const

Возвращает текущее значение допуска (tolerance), используемое для [IK chain](#ik_chains) с указанным ID. Это значение задаёт порог, при котором цель считается достигшей своего конечного положения, и решатель IK прекращает итерации.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Текущее значение допуска для IK-цепочки.
## void copyBoneTransforms ( const Ptr < ObjectMeshSkinnedLegacy > & src )

Копирует все трансформации костей из указанного исходного skinned-меша.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshSkinnedLegacy](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md)> &* **src** - Source skinned mesh from which bone transforms are to be copied.

## bool applyMeshProcedural ( Ptr <ConstMeshSkinned> mesh )

**[ Main Thread ]** Заменяет текущую геометрию объекта предоставленным мешем и **загружает её в VRAM**. Может вызываться только если [procedural mode](#procedural_modification) включён через *[setMeshProceduralMode()](../../...md#setMeshProceduralMode_int_void)*. Если исходный меш содержит совместимые элементы (например, кости, поверхности, данные скининга), соответствующие оригиналу, то анимации, морф-таргеты и другое поведение продолжат работать без прерывания. В противном случае меш останется статическим, без применения анимации или морфинга.
> **Notice:** Процедурный меш остаётся в памяти и не будет выгружен автоматически.


### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstMeshSkinned>* **mesh** - Исходный меш.

### Возвращаемое значение

true, если информация из меша успешно скопирована в процедурный меш; иначе false.
## void setSurfaceTargetEnabled ( int surface , int target , bool enabled )

Переключает использование морф-таргета для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности, к которой добавляется морф-таргет.
- *int* **target** - Номер используемого морф-таргета.
- *bool* **enabled** - true для включения использования морф-таргета для поверхности, false для отключения.

## int isSurfaceTargetEnabled ( int surface , int target ) const

Возвращает значение, указывающее, включено ли использование морф-таргета для указанной поверхности.
### Аргументы

- *int* **surface** - Номер поверхности, к которой добавлен морф-таргет.
- *int* **target** - Номер морф-таргета.

### Возвращаемое значение

true, если использование морф-таргета для поверхности включено; иначе false.
## void setSurfaceTargetWeight ( int surface , int target , float weight )

Задаёт вес морф-таргета, то есть интенсивность его влияния на вершины поверхности.
### Аргументы

- *int* **surface** - Номер поверхности, к которой добавлен морф-таргет.
- *int* **target** - Номер морф-таргета.
- *float* **weight** - Вес морф-таргета.

## float getSurfaceTargetWeight ( int surface , int target ) const

Возвращает вес морф-таргета, то есть интенсивность его влияния на вершины поверхности.
### Аргументы

- *int* **surface** - Номер поверхности, к которой добавлен морф-таргет.
- *int* **target** - Номер морф-таргета.

### Возвращаемое значение

Вес морф-таргета.
## void setLayerBoneTransform ( int layer , int bone , const Math:: mat4 & transform )

Задаёт матрицу трансформации для указанной кости. Отличие от функции [setBoneTransform()](#setBoneTransform_int_mat4_void) в том, что этот метод учитывает только трансформацию в указанном слое анимации (смешивание не выполняется).
> **Notice:** Кость может масштабироваться только равномерно.


### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.
- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Матрица трансформации кости.

## Math:: mat4 getLayerBoneTransform ( int layer , int bone ) const

Возвращает матрицу трансформации указанной кости относительно родительского объекта.
> **Notice:** Отличие от [getBoneTransform()](#getBoneTransform_int_mat4) в том, что этот метод учитывает только трансформацию в слое анимации (смешивание не выполняется).


### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.

### Возвращаемое значение

Матрица трансформации кости.
## Math:: mat4 getBoneRestLocalTransform ( int bone ) const

Возвращает базовую (bind pose) трансформацию указанной кости в её локальном пространстве относительно родительской кости.
### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Матрица базовой (bind pose) трансформации в локальном пространстве кости.
## void setLayerBonePosition ( int layer , int bone , const Math:: vec3 & position )

Задаёт позицию для указанной кости.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция кости.

## Math:: vec3 getLayerBonePosition ( int layer , int bone ) const

Возвращает позицию указанной кости.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.

### Возвращаемое значение

Позиция кости.
## void setLayerBoneRotation ( int layer , int bone , const Math:: quat & rotation )

Задаёт вращение для указанной кости.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.
- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **rotation** - Вращение кости.

## Math:: quat getLayerBoneRotation ( int layer , int bone ) const

Возвращает вращение указанной кости.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.

### Возвращаемое значение

Вращение кости.
## void setLayerBoneScale ( int layer , int bone , const Math:: vec3 & scale )

Задаёт масштаб для указанной кости.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **scale** - Масштаб кости.

## Math:: vec3 getLayerBoneScale ( int layer , int bone ) const

Возвращает масштаб указанной кости.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости.

### Возвращаемое значение

Масштаб кости.
## void setLayerFrameUsesEnabled ( int layer , bool enabled )

Переключает использование масок анимации для костей в указанном слое.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *bool* **enabled** - true для включения использования масок анимации для костей в указанном слое, false для отключения.

## bool isLayerFrameUsesEnabled ( int layer ) const

Возвращает значение, указывающее, включено ли использование масок анимации для костей в указанном слое.
### Аргументы

- *int* **layer** - Номер слоя анимации.

### Возвращаемое значение

true if the use of animation masks for bones in the specified layer is enabled, otherwise false.
## void setLayerBoneFrameUses ( int layer , int bone , ObjectMeshSkinnedLegacy::ANIM_FRAME_USES uses )

Задаёт значение, указывающее, какие компоненты кадра используются для анимации указанной кости заданного слоя анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).
- *[ObjectMeshSkinnedLegacy::ANIM_FRAME_USES](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md#ANIM_FRAME_USES)* **uses** - Значение, указывающее используемые компоненты кадра.

## ObjectMeshSkinnedLegacy::ANIM_FRAME_USES getLayerBoneFrameUses ( int layer , int bone ) const

Возвращает значение, указывающее, какие компоненты кадра используются для анимации указанной кости заданного слоя анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *int* **bone** - Номер кости в диапазоне от 0 до [total number of bones](#getNumBones_int).

### Возвращаемое значение

Значение, указывающее используемые компоненты кадра.
## void setLayerPose ( int layer , const Ptr <ConstSkeletonPoseDecomposed> & pose )

Задаёт трансформации костей для указанного слоя анимации из заданного [SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md). Это перезаписывает все трансформации костей в слое значениями из позы.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<ConstSkeletonPoseDecomposed> &* **pose** - Поза, применяемая к слою.

## void getLayerPose ( int layer , const Ptr < SkeletonPoseDecomposed > & out_pose ) const

Записывает трансформации костей указанного слоя анимации в заданный [SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md).
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SkeletonPoseDecomposed](../../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)> &* **out_pose** - Выходная поза, в которую записываются трансформации костей слоя.

## int getLayerNumFrames ( int layer ) const

Возвращает количество кадров анимации для указанного слоя.
### Аргументы

- *int* **layer** - Номер слоя анимации.

### Возвращаемое значение

Количество кадров анимации.
## float setLayerFrame ( int layer , float frame , int from = -1 , int to = -1 )

Задаёт кадр для указанного слоя анимации.
### Аргументы

- *int* **layer** - Номер слоя анимации.
- *float* **frame** - Номер кадра в интервале «from-to». Если передан аргумент типа float, анимация интерполируется между соседними кадрами. 0 означает кадр from. Для больших значений вычисляется остаток от деления по модулю *(from-to)*. Если указано отрицательное значение, интерполяция будет выполнена от текущего кадра к кадру *from*.
- *int* **from** - Начальный кадр. -1 означает первый кадр анимации.
- *int* **to** - Конечный кадр. -1 означает последний кадр анимации.

### Возвращаемое значение

Номер кадра.
## float getLayerFrame ( int layer ) const

Возвращает номер кадра, переданный в качестве аргумента time при последнем вызове [setLayerFrame()](#setLayerFrame_int_float_int_int_float).
### Аргументы

- *int* **layer** - Номер слоя анимации.

### Возвращаемое значение

Номер кадра.
## int getLayerFrameFrom ( int layer ) const

Возвращает начальный кадр, переданный в качестве аргумента from при последнем вызове [setLayerFrame()](#setLayerFrame_int_float_int_int_float).
### Аргументы

- *int* **layer** - Номер слоя анимации.

### Возвращаемое значение

Начальный кадр.
## int getLayerFrameTo ( int layer ) const

Возвращает конечный кадр, переданный в качестве аргумента to при последнем вызове [setLayerFrame()](#setLayerFrame_int_float_int_int_float).
### Аргументы

- *int* **layer** - Номер слоя анимации.

### Возвращаемое значение

Конечный кадр.
## long long getAnimationResourceID ( const char * path ) const

Возвращает уникальный ID анимации по пути к ней. Этот метод также загружает анимацию, если она ещё не была загружена.
### Аргументы

- *const char ** **path** - Путь к файлу анимации. Путь может быть представлен либо путём к файлу, либо его [GUID](../../../principles/filesystem/index_cpp.md#guids), что является рекомендуемым подходом. После загрузки анимации её внутреннее представление идентифицируется по пути при использовании *[setLayerAnimationFilePath](#setLayerAnimationFilePath_int_cstr_void)* и т.д. > **Notice:** При [import](../../../editor2/fbx/index.md) модели с анимациями из контейнера FBX следует использовать следующий путь к файлам `*.anim`: `<path_to_your_fbx_file>/<file.fbx>/<your_anim_file.anim>` > Например: *object->setLayerAnimationFilePath(0,"models/soldier/soldier.fbx/run.anim");*

### Возвращаемое значение

Уникальный ID анимации.
## void setLayerAnimationFilePath ( int layer , const char * path )

Задаёт путь к анимации для указанного слоя анимации.
### Аргументы

- *int* **layer** - Номер слоя.
- *const char ** **path** - Путь к файлу анимации. > **Notice:** При [import](../../../editor2/fbx/index.md) модели с анимациями из контейнера FBX следует использовать следующий путь к файлам `*.anim`: **<path_to_your_fbx_file>/<file.fbx>/<your_anim_file.anim>** > Например: *object->setLayerAnimationFilePath(0,"models/soldier/soldier.fbx/run.anim");*

## String getLayerAnimationFilePath ( int layer ) const

Возвращает путь к анимации для указанного слоя анимации.
### Аргументы

- *int* **layer** - Номер слоя.

### Возвращаемое значение

Путь к файлу анимации.
## void setLayerAnimationResourceID ( int layer , long long resource_id ) const

Задаёт анимацию для слоя, используя уникальный ID анимации.
### Аргументы

- *int* **layer** - Номер слоя.
- *long long* **resource_id** - Уникальный ID анимации.

## long long getLayerAnimationResourceID ( int layer ) const

Возвращает уникальный ID анимации, используемой для слоя.
### Аргументы

- *int* **layer** - Номер слоя.

### Возвращаемое значение

Уникальный ID анимации.
## Math:: mat4 getBoneBindLocalTransform ( int bone ) const

Возвращает матрицу трансформации базовой позы (bind pose) кости относительно родительской кости.
> **Notice:** Чтобы получить матрицу трансформации базовой позы в пространстве объекта, используйте [getBoneBindObjectTransform()](#getBoneBindObjectTransform_int_mat4).


### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Матрица трансформации базовой позы.
## Math:: mat4 getBoneBindLocalITransform ( int bone ) const

Возвращает обратную матрицу трансформации базовой позы (bind pose) кости относительно родительской кости.
> **Notice:** Чтобы получить матрицу трансформации базовой позы в пространстве объекта, используйте [getBoneBindObjectITransform()](#getBoneBindObjectITransform_int_mat4).


### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Обратная матрица трансформации базовой позы.
## Math:: mat4 getBoneBindObjectTransform ( int bone ) const

Возвращает матрицу трансформации базовой позы (bind pose) кости в пространстве объекта.
> **Notice:** Чтобы получить матрицу трансформации базовой позы относительно родительской кости, используйте [getBoneBindLocalTransform()](#getBoneBindLocalTransform_int_mat4).


### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Матрица трансформации базовой позы.
## Math:: mat4 getBoneBindObjectITransform ( int bone ) const

Возвращает обратную матрицу трансформации базовой позы (bind pose) кости в пространстве объекта.
> **Notice:** Чтобы получить матрицу трансформации базовой позы относительно родительской кости, используйте [getBoneBindLocalITransform()](#getBoneBindLocalITransform_int_mat4).


### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Обратная матрица трансформации базовой позы.
## Math:: mat4 getBoneSkinningTransform ( int bone ) const

Возвращает матрицу кости, на основе которой кость влияет на связанные вершины, результат следующего умножения: getBoneTransform(bone) * getBoneBindObjectITransform(bone).
### Аргументы

- *int* **bone** - Номер кости.

### Возвращаемое значение

Матрица трансформации кости.
## void addVisualizeLookAtChain ( int chain_id )

Добавляет указанную цепочку LookAtChain к визуализации.
### Аргументы

- *int* **chain_id** - LookAtChain ID.

## void removeVisualizeLookAtChain ( int chain_id )

Удаляет указанную цепочку LookAtChain из визуализации.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

## void clearVisualizeLookAtChain ( )

Удаляет все цепочки LookAtChain из визуализации.
## void addVisualizeConstraint ( int constraint_index )

Добавляет указанное ограничение кости к визуализации.
### Аргументы

- *int* **constraint_index** - Индекс ограничения кости.

## void removeVisualizeConstraint ( int constraint_index )

Удаляет указанное ограничение кости из визуализации.
### Аргументы

- *int* **constraint_index** - Индекс ограничения кости.

## void clearVisualizeConstraint ( )

Удаляет все ограничения костей из визуализации.
## int addLookAtChain ( )

Добавляет новую цепочку LookAtChain и возвращает её ID.
### Возвращаемое значение

ID LookAtChain.
## void removeLookAtChain ( int chain_id )

Удаляет указанную цепочку LookAtChain по её ID.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

## int getNumLookAtChains ( ) const

Возвращает общее количество цепочек LookAtChain.
### Возвращаемое значение

Общее количество цепочек LookAtChain.
## int getLookAtChainID ( int num ) const

Возвращает ID цепочки LookAtChain по её индексу.
### Аргументы

- *int* **num** - Индекс LookAtChain.

### Возвращаемое значение

ID LookAtChain.
## void setLookAtChainEnabled ( bool enabled , int chain_id )

Переключает использование LookAtChain.
### Аргументы

- *bool* **enabled** - true для включения LookAtChain, false для отключения.
- *int* **chain_id** - ID LookAtChain.

## bool isLookAtChainEnabled ( int chain_id ) const

Проверяет, включена ли LookAtChain.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

true, если LookAtChain включена; иначе false.
## void setLookAtChainConstraint ( ObjectMeshSkinnedLegacy::CHAIN_CONSTRAINT constraint , int chain_id )

Настраивает тип ограничения кости для решателя указанной цепочки.
### Аргументы

- *[ObjectMeshSkinnedLegacy::CHAIN_CONSTRAINT](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md#CHAIN_CONSTRAINT)* **constraint** - Тип ограничения кости для решателя.
- *int* **chain_id** - ID LookAtChain.

## ObjectMeshSkinnedLegacy::CHAIN_CONSTRAINT getLookAtChainConstraint ( int chain_id ) const

Возвращает тип ограничения кости для решателя указанной цепочки.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Тип ограничения кости для решателя.
## void setLookAtChainWeight ( float weight , int chain_id )

Задаёт вес LookAtChain, который влияет на степень вращения кости к цели.
### Аргументы

- *float* **weight** - Вес цепочки.
- *int* **chain_id** - ID LookAtChain.

## float getLookAtChainWeight ( int chain_id ) const

Возвращает вес LookAtChain, который влияет на степень вращения кости к цели.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Вес цепочки.
## int addLookAtChainBone ( int bone , int chain_id )

Добавляет кость в LookAtChain и возвращает её индекс.
### Аргументы

- *int* **bone** - Кость, которую нужно добавить в цепочку.
- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Индекс кости.
## int addLookAtChainBone ( const char * bone_name , int chain_id )

Добавляет кость в LookAtChain и возвращает её индекс.
### Аргументы

- *const char ** **bone_name** - Имя кости, которую нужно добавить в цепочку.
- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Индекс кости.
## int getLookAtChainNumBones ( int chain_id ) const

Возвращает общее количество костей в LookAtChain.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Общее количество костей в LookAtChain.
## void removeLookAtChainBone ( int bone_num , int chain_id )

Удаляет кость из LookAtChain по её индексу.
### Аргументы

- *int* **bone_num** - Индекс кости, которую нужно удалить из цепочки.
- *int* **chain_id** - ID LookAtChain.

## int getLookAtChainBone ( int bone_num , int chain_id ) const

Возвращает кость из LookAtChain по её индексу.
### Аргументы

- *int* **bone_num** - Индекс кости в цепочке.
- *int* **chain_id** - ID LookAtChain.

## void setLookAtChainBoneWeight ( float weight , int bone_num , int chain_id )

Задаёт дополнительный локальный вес кости.
### Аргументы

- *float* **weight** - Вес кости в цепочке.
- *int* **bone_num** - Индекс кости в цепочке.
- *int* **chain_id** - ID LookAtChain.

## float getLookAtChainBoneWeight ( int bone_num , int chain_id ) const

Возвращает дополнительный локальный вес кости.
### Аргументы

- *int* **bone_num** - Индекс кости в цепочке.
- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Вес кости в цепочке.
## void setLookAtChainBoneUp ( const Math:: Vec3 & up , int bone_num , int chain_id )

Задаёт ось UP для кости.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **up** - Вектор UP для кости.
- *int* **bone_num** - Индекс кости в цепочке.
- *int* **chain_id** - ID LookAtChain.

## Math:: Vec3 getLookAtChainBoneUp ( int bone_num , int chain_id ) const

Возвращает ось UP для кости.
### Аргументы

- *int* **bone_num** - Индекс кости в цепочке.
- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Вектор UP для кости.
## void setLookAtChainBoneAxis ( const Math:: Vec3 & axis , int bone_num , int chain_id )

Задаёт ось, направленную на цель LookAtChain.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **axis** - Ось, направленная на цель.
- *int* **bone_num** - Индекс кости в цепочке.
- *int* **chain_id** - ID LookAtChain.

## Math:: Vec3 getLookAtChainBoneAxis ( int bone_num , int chain_id ) const

Возвращает ось, направленную на цель LookAtChain.
### Аргументы

- *int* **bone_num** - Индекс кости в цепочке.
- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Ось, направленная на цель.
## void setLookAtChainTargetPosition ( const Math:: Vec3 & position , int chain_id )

Задаёт позицию для вращения в пространстве объекта.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция для вращения в пространстве объекта.
- *int* **chain_id** - ID LookAtChain.

## Math:: Vec3 getLookAtChainTargetPosition ( int chain_id ) const

Возвращает позицию для вращения в пространстве объекта.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Позиция для вращения в пространстве объекта.
## void setLookAtChainTargetWorldPosition ( const Math:: Vec3 & position , int chain_id )

Задаёт позицию для вращения в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция для вращения в мировом пространстве.
- *int* **chain_id** - ID LookAtChain.

## Math:: Vec3 getLookAtChainTargetWorldPosition ( int chain_id ) const

Возвращает позицию для вращения в мировом пространстве.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Позиция для вращения в мировом пространстве.
## void setLookAtChainPolePosition ( const Math:: Vec3 & position , int chain_id )

Задаёт позицию опорного вектора (pole vector) в пространстве объекта.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция опорного вектора в пространстве объекта.
- *int* **chain_id** - ID LookAtChain.

## Math:: Vec3 getLookAtChainPolePosition ( int chain_id ) const

Возвращает позицию опорного вектора (pole vector) в пространстве объекта.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Позиция опорного вектора в пространстве объекта.
## void setLookAtChainPoleWorldPosition ( const Math:: Vec3 & position , int chain_id )

Задаёт позицию опорного вектора (pole vector) в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Позиция опорного вектора в мировом пространстве.
- *int* **chain_id** - ID LookAtChain.

## Math:: Vec3 getLookAtChainPoleWorldPosition ( int chain_id ) const

Возвращает позицию опорного вектора (pole vector) в мировом пространстве.
### Аргументы

- *int* **chain_id** - ID LookAtChain.

### Возвращаемое значение

Позиция опорного вектора в мировом пространстве.
## int getIKChainID ( int num ) const

Возвращает ID IKChain по её индексу.
### Аргументы

- *int* **num** - Индекс IKChain.

### Возвращаемое значение

ID IKChain.
## void setIKChainConstraint ( ObjectMeshSkinnedLegacy::CHAIN_CONSTRAINT constraint , int chain_id )

Настраивает тип ограничения кости для решателя указанной цепочки.
### Аргументы

- *[ObjectMeshSkinnedLegacy::CHAIN_CONSTRAINT](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md#CHAIN_CONSTRAINT)* **constraint** - Тип ограничения кости для решателя.
- *int* **chain_id** - ID IK-цепочки.

## ObjectMeshSkinnedLegacy::CHAIN_CONSTRAINT getIKChainConstraint ( int chain_id ) const

Возвращает тип ограничения кости для решателя указанной цепочки.
### Аргументы

- *int* **chain_id** - ID IK-цепочки.

### Возвращаемое значение

Тип ограничения кости для решателя.
## int addIKChainBone ( const char * bone_name , int chain_id )

Добавляет кость в IKChain и возвращает её индекс.
### Аргументы

- *const char ** **bone_name** - Имя кости.
- *int* **chain_id** - ID IKChain.

### Возвращаемое значение

Индекс кости.
## int addBoneConstraint ( int bone )

Добавляет ограничение вращения к указанной кости.
### Аргументы

- *int* **bone** - Индекс кости в меше.

### Возвращаемое значение

Индекс ограничения.
## int addBoneConstraint ( const char * bone_name )

Добавляет ограничение вращения к указанной кости.
### Аргументы

- *const char ** **bone_name** - Имя кости.

### Возвращаемое значение

Индекс ограничения.
## void removeBoneConstraint ( int constraint_num )

Удаляет указанное ограничение вращения кости.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

## int findBoneConstraint ( int bone ) const

Возвращает индекс ограничения вращения для указанной кости.
### Аргументы

- *int* **bone** - Индекс кости в меше.

### Возвращаемое значение

Индекс ограничения.
## int findBoneConstraint ( const char * bone_name ) const

Возвращает индекс ограничения вращения для указанной кости.
### Аргументы

- *const char ** **bone_name** - Имя кости.

### Возвращаемое значение

Индекс ограничения.
## void setBoneConstraintEnabled ( bool enabled , int constraint_num )

Включает использование ограничения вращения для кости.
### Аргументы

- *bool* **enabled** - true для включения использования ограничения вращения для кости, false для отключения.
- *int* **constraint_num** - Индекс ограничения.

## bool isBoneConstraintEnabled ( int constraint_num ) const

Возвращает значение, указывающее, включено ли использование ограничения вращения для кости.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

true, если использование ограничения вращения для кости включено; иначе false.
## int getBoneConstraintBoneIndex ( int constraint_num ) const

Возвращает индекс кости, для которой задано ограничение вращения.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Индекс кости в меше.
## void setBoneConstraintYawAxis ( const Math:: vec3 & axis , int constraint_num )

Задаёт ось yaw для ограничения вращения кости.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **axis** - Ось yaw.
- *int* **constraint_num** - Индекс ограничения.

## Math:: vec3 getBoneConstraintYawAxis ( int constraint_num ) const

Возвращает ось yaw для ограничения вращения кости.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Ось yaw.
## void setBoneConstraintPitchAxis ( const Math:: vec3 & axis , int constraint_num )

Задаёт ось pitch для ограничения вращения кости.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **axis** - Ось pitch.
- *int* **constraint_num** - Индекс ограничения.

## Math:: vec3 getBoneConstraintPitchAxis ( int constraint_num ) const

Возвращает ось pitch для ограничения вращения кости.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Ось pitch.
## void setBoneConstraintRollAxis ( const Math:: vec3 & axis , int constraint_num )

Задаёт ось roll для ограничения вращения кости.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **axis** - Ось roll.
- *int* **constraint_num** - Индекс ограничения.

## Math:: vec3 getBoneConstraintRollAxis ( int constraint_num ) const

Возвращает ось roll для ограничения вращения кости.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Ось roll.
## void setBoneConstraintYawAngles ( float min_angle , float max_angle , int constraint_num )

Задаёт минимальный и максимальный углы, ограничивающие вращение кости вдоль оси yaw.
### Аргументы

- *float* **min_angle** - Минимальный угол вращения.
- *float* **max_angle** - Максимальный угол вращения.
- *int* **constraint_num** - Индекс ограничения.

## float getBoneConstraintYawMinAngle ( int constraint_num ) const

Возвращает минимальный угол, ограничивающий вращение кости вдоль оси yaw.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Минимальный угол вращения.
## float getBoneConstraintYawMaxAngle ( int constraint_num ) const

Возвращает максимальный угол, ограничивающий вращение кости вдоль оси yaw.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Максимальный угол вращения.
## void setBoneConstraintPitchAngles ( float min_angle , float max_angle , int constraint_num )

Задаёт минимальный и максимальный углы, ограничивающие вращение кости вдоль оси pitch.
### Аргументы

- *float* **min_angle** - Минимальный угол вращения.
- *float* **max_angle** - Максимальный угол вращения.
- *int* **constraint_num** - Индекс ограничения.

## float getBoneConstraintPitchMinAngle ( int constraint_num ) const

Возвращает минимальный угол, ограничивающий вращение кости вдоль оси pitch.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Минимальный угол вращения.
## float getBoneConstraintPitchMaxAngle ( int constraint_num ) const

Возвращает максимальный угол, ограничивающий вращение кости вдоль оси pitch.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Максимальный угол вращения.
## void setBoneConstraintRollAngles ( float min_angle , float max_angle , int constraint_num )

Задаёт минимальный и максимальный углы, ограничивающие вращение кости вдоль оси roll.
### Аргументы

- *float* **min_angle** - Минимальный угол вращения.
- *float* **max_angle** - Максимальный угол вращения.
- *int* **constraint_num** - Индекс ограничения.

## float getBoneConstraintRollMinAngle ( int constraint_num ) const

Возвращает минимальный угол, ограничивающий вращение кости вдоль оси roll.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Минимальный угол вращения.
## float getBoneConstraintRollMaxAngle ( int constraint_num ) const

Возвращает максимальный угол, ограничивающий вращение кости вдоль оси roll.
### Аргументы

- *int* **constraint_num** - Индекс ограничения.

### Возвращаемое значение

Максимальный угол вращения.
