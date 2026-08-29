# Unigine.Node Class (CPP)

**Header:** #include <UnigineNode.h>


В терминологии Unigine все объекты, добавленные в сцену, называются [nodes](../../../objects/nodes/index.md). Узлы могут быть разных типов, определяющих их визуальное представление и поведение.


Узел создаётся и хранится в мире. Все изменения сохраняются в файл `.world`.


Узел также можно [saved](../../../api/library/engine/class.world_cpp.md#saveNode_cstr_Node_int_int) во внешний файл `.node`, а затем при необходимости [imported](../../../api/library/engine/class.world_cpp.md#loadNode_cstr_int_Node) в мир. Также можно создать [reference](../../../api/library/nodes/class.nodereference_cpp.md) на экспортированный узел.


С узлом можно связать любые [string data](#setData_cstr_cstr_void) (записываемые напрямую в файл *.node или *.world) или произвольную [user variable](#setVariable_Variable_void).


### См. также


- Как управлять [ownership](../../../code/uniginescript/memory_management.md)
- Как работать с [matrix transformations](../../../code/fundamentals/matrix_transformations/index_cpp.md) узла


### Создание узла


Класс Node не предоставляет создание узла. Можно создать экземпляр любого класса, унаследованного от класса Node, а затем получить узел через автоматическое приведение типа (upcasting).


Например:

1. Создайте меш-параллелепипед с использованием класса [Mesh](../../../api/library/rendering/class.mesh_cpp.md).
2. Используйте меш-параллелепипед для создания экземпляра класса [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md). Этот класс унаследован от класса Node.
3. Получите узел через upcasting.


```cpp
// AppWorldLogic.cpp

#include "AppWorldLogic.h"

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init() {


	// объявление умного указателя для любого типа узла, унаследованного от класса Node (например, ObjectMeshDynamic)
	// и вызов конструктора соответствующего класса
	ObjectMeshDynamicPtr object_mesh = ObjectMeshDynamic::create("core/meshes/box.mesh");

	// объявление умного указателя для узла
	// и получение указателя на узел из созданного ObjectMeshDynamic
	NodePtr node = object_mesh;

	return 1;
}

```


Теперь вы можете работать с экземпляром ObjectMeshDynamic как с узлом.


### Редактирование узла и сохранение изменений


Класс Node содержит общие настройки узла. Кроме того, каждый узел имеет специальные настройки, которые зависят от типа узла.

> **Notice:** Специальные настройки узла можно найти в статье о соответствующем классе.


Редактирование узла также включает редактирование материалов и свойств, назначенных узлу.


Чтобы отредактированный узел был сохранён в файле `.world`, необходимо включить соответствующую опцию через метод *[setSaveToWorldEnabled()](#setSaveToWorldEnabled_int_void)*.

> **Notice:** Узел будет сохранён в файл `*.world` только если эта опция включена также для всех его предков.


Например:

1. Создайте меш-параллелепипед с использованием класса [Mesh](../../../api/library/rendering/class.mesh_cpp.md).
2. Сохраните меш на диске. Это необходимо, так как узел, который мы собираемся сохранить в файл `.world`, должен ссылаться на меш, хранящийся на диске.
3. Используйте сохранённый файл `.mesh` для создания экземпляра класса [ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md). Этот класс унаследован от класса Node.
4. Получите узел из экземпляра ObjectMeshStatic через upcasting.
5. Включите сохранение в файл `.world` для узла (и всех его дочерних узлов).
6. Отредактируйте узел и сохраните мир, вызвав консольную команду `world_save`.


```cpp
#include "AppWorldLogic.h"

#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init() {

	// создание меша
	MeshPtr mesh = Mesh::create();
	mesh->addBoxSurface("box_0",vec3(1.0f));
	// сохранение меша в файл на диске
	mesh->save("unigine_project/meshes/my_mesh.mesh");
	// объявление умного указателя для любого типа узла, унаследованного от класса Node (например, ObjectMeshStatic)
	// и вызов конструктора соответствующего класса для создания экземпляра любого класса, унаследованного от класса Node (например, ObjectMeshStatic)
	ObjectMeshStaticPtr object_mesh = ObjectMeshStatic::create("unigine_project/meshes/my_mesh.mesh");

	// объявление умного указателя для узла,
	// получение указателя на узел из созданного ObjectMeshStatic,
	NodePtr node = object_mesh;

	// включение сохранения узла (и всех его дочерних узлов) в файл .world
	node->setSaveToWorldEnabledRecursive(true);

	// изменение имени узла
	node->setName("my_node");
	// изменение трансформации узла
	node->setWorldTransform(translate(Vec3(0.0f, 0.0f, 2.0f)));

	// сохранение изменений узла в файле .world
	Console::run("world_save");

	return 1;
}

```


### Экспорт и импорт узла


Чтобы экспортировать узел, хранящийся в мире, во внешний файл `.node`, необходимо передать его методу *[saveNode()](../../../api/library/engine/class.world_cpp.md#saveNode_cstr_Node_int_int)* класса World.


Чтобы импортировать существующий узел, хранящийся в файле `.node`, в мир, необходимо вызвать метод *[loadNode()](../../../api/library/engine/class.world_cpp.md#loadNode_cstr_int_Node)* класса World.


For example:


1. Создайте меш-параллелепипед с использованием класса [Mesh](../../../api/library/rendering/class.mesh_cpp.md).
2. Сохраните меш на диске. Это необходимо, так как узел, который мы собираемся экспортировать, должен ссылаться на меш, хранящийся на диске.
3. Используйте сохранённый файл `.mesh` для создания экземпляра класса [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md). Этот класс унаследован от класса Node.
4. Получите узел из экземпляра ObjectMeshStatic через upcasting.
5. Экспортируйте узел во внешний файл `.node`.
6. Импортируйте ранее экспортированный узел, чтобы проверить результат.


```cpp
#include "AppWorldLogic.h"

#include <UnigineNode.h>
#include <UnigineObjects.h>
#include <UnigineWorld.h>
#include <UnigineEditor.h>
#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init() {

	// создание меша
	MeshPtr mesh = Mesh::create();
	mesh->addBoxSurface("box_0", vec3(1.0f));
	// save a mesh into a file on the disk
	mesh->save("unigine_project/meshes/my_mesh.mesh");
	// создание экземпляра любого класса, унаследованного от класса Node (например, ObjectMeshStatic)
	ObjectMeshStaticPtr object_mesh = ObjectMeshStatic::create("unigine_project/meshes/my_mesh.mesh");
	// объявление умного указателя для узла
	// и получение указателя на узел из созданного NodeDummy
	NodePtr node = object_mesh;
	// экспорт узла в файл .node
	World::saveNode("unigine_project/nodes/my_node.node", node);
	// импорт экспортированного узла для проверки результата
	NodePtr imported_node = World::loadNode("unigine_project/nodes/my_node.node");
	// задание позиции узла
	imported_node->setPosition(Vec3(4.0f, 0.0f, 1.0f));

	return 1;
}

```


### Удаление узла


По умолчанию время жизни каждого нового узла совпадает со временем жизни **World** (то есть такой узел будет удалён при закрытии мира). Но также можно выбрать способ управления временем жизни узла:


- **движком (Engine)** - в этом случае узел будет удалён автоматически при завершении работы движка.
- **вручную** - в этом случае узел должен быть удалён пользователем вручную.


Для удаления узла можно использовать следующие два метода:


- [*deleteLater()*](../../../api/library/common/class.ptr_cpp.md#deleteLater_void) - выполняет отложенное удаление, в этом случае объект будет удалён во время следующего этапа swap главного цикла (рендеринг объекта прекращается немедленно, но он ещё некоторое время существует в памяти, поэтому его можно, например, получить у родителя). Этот метод упрощает удаление объекта из вторичного потока, поэтому его можно вызвать и забыть о деталях, позволив движку взять на себя управление процессом удаления, что может использоваться для будущих оптимизаций.
- [*deleteForce()*](../../../api/library/common/class.ptr_cpp.md#deleteForce_void) - выполняет немедленное удаление, что может потребоваться в некоторых случаях. Вызов этого метода для объектов, зависящих от главного цикла (например, узлов), безопасен только при выполнении из основного потока.


```cpp
// AppWorldLogic.cpp

#include <UnigineNode.h>
#include <UnigineObjects.h>
#include <UnigineWorld.h>
#include <UnigineEditor.h>
#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init() {

	// создание меша
	MeshPtr mesh = Mesh::create();
	mesh->addBoxSurface("box_0", vec3(1.0f));
	// save a mesh into a file on the disk
	mesh->save("unigine_project/meshes/my_mesh.mesh");
	// создание экземпляра любого класса, унаследованного от класса Node (например, ObjectMeshStatic)
	ObjectMeshStaticPtr object_mesh = ObjectMeshStatic::create("unigine_project/meshes/my_mesh.mesh");
	// declare a smart pointer for the node
	// and obtain the node pointer from the created NodeDummy
	NodePtr node = object_mesh;

	// выполнение действий с узлом
	// ...

	// удаление узла
	node.deleteLater();

	return 1;
}

```


## Класс Node

### Перечисления

## TYPE

| Название | Описание |
|---|---|
| **ANY_TYPE** = -1 | Любой тип узла. |
| **NODE_BEGIN** = 0 | Начало диапазона узлов. |
| **NODE_DUMMY** = 0 | Пустой узел (dummy). См. класс [NodeDummy](../../../api/library/nodes/class.nodedummy_cpp.md). |
| **NODE_LAYER** = 1 | Узел-слой. См. класс [NodeLayer](../../../api/library/nodes/class.nodelayer_cpp.md). |
| **NODE_TRIGGER** = 2 | Пустой узел (dummy), который может вызывать callback'и при включении/отключении или перемещении. См. класс [NodeTrigger](../../../api/library/nodes/class.nodetrigger_cpp.md). |
| **NODE_REFERENCE** = 3 | Ссылка на узел, ссылающаяся на внешний файл NODE. См. класс [NodeReference](../../../api/library/nodes/class.nodereference_cpp.md). |
| **NODE_EXTERN** = 4 | Внешний узел (extern). См. класс [NodeExtern](../../../api/library/nodes/class.nodeextern_cpp.md). |
| **NODE_ANIMATION_PLAYBACK** = 5 | Узел воспроизведения анимации. См. класс [NodeAnimationPlayback](../../../api/library/nodes/class.nodeanimationplayback_cpp.md). |
| **NODE_SKELETON_POSE** = 6 | Узел позы скелета. См. класс [NodeSkeletonPose](../../../api/library/nodes/class.nodeskeletonpose_cpp.md). |
| **NODE_END** = 6 | Конец диапазона узлов. |
| **WORLD_BEGIN** = 7 | Начало диапазона мировых узлов. |
| **WORLD_SPLINE_GRAPH** = 7 | Мировой сплайн-граф. См. класс [WorldSplineGraph](../../../api/library/worlds/class.worldsplinegraph_cpp.md). |
| **WORLD_TRIGGER** = 8 | Мировой триггер. См. класс [WorldTrigger](../../../api/library/worlds/class.worldtrigger_cpp.md). |
| **WORLD_CLUTTER** = 9 | Мировой clutter. См. класс [WorldClutter](../../../api/library/worlds/class.worldclutter_cpp.md). |
| **WORLD_SWITCHER** = 10 | Переключатель узлов (для отключения частей мира). См. класс [WorldSwitcher](../../../api/library/worlds/class.worldswitcher_cpp.md). |
| **WORLD_OCCLUDER** = 11 | Мировой окклюдер. См. класс [WorldOccluder](../../../api/library/worlds/class.worldoccluder_cpp.md). |
| **WORLD_OCCLUDER_MESH** = 12 | Мировой меш-окклюдер. См. класс [WorldOccluderMesh](../../../api/library/worlds/class.worldoccludermesh_cpp.md). |
| **WORLD_TRANSFORM_PATH** = 13 | Трансформер, заданный путём. См. класс [WorldTransformPath](../../../api/library/worlds/class.worldtransformpath_cpp.md) |
| **WORLD_TRANSFORM_JOINT** = 14 | Трансформер, заданный шарниром (joint). См. класс [WorldTransformJoint](../../../api/library/worlds/class.worldtransformjoint_cpp.md). |
| **WORLD_EXPRESSION** = 15 | Узел, позволяющий выполнять произвольное выражение. См. класс [WorldExpression](../../../api/library/worlds/class.worldexpression_cpp.md). |
| **WORLD_EXTERN** = 16 | Внешний мир. См. класс [WorldExtern](../../../api/library/worlds/class.worldextern_cpp.md). |
| **WORLD_END** = 16 | Конец диапазона мировых узлов. |
| **GEODETIC_BEGIN** = 17 | Начало диапазона геодезических узлов. |
| **GEODETIC_PIVOT** = 17 | Узел геодезического пивота. См. класс [GeodeticPivot](../../../api/library/geodetics/class.geodeticpivot_cpp.md). |
| **GEODETIC_END** = 17 | Конец диапазона геодезических узлов. |
| **FIELD_BEGIN** = 18 | Начало диапазона узлов полей. |
| **FIELD_SPACER** = 18 | Узел Field Spacer. См. класс [FieldSpacer](../../../api/library/fields/class.fieldspacer_cpp.md). |
| **FIELD_ANIMATION** = 19 | Узел Field Animation. См. класс [FieldAnimation](../../../api/library/fields/class.fieldanimation_cpp.md). |
| **FIELD_HEIGHT** = 20 | Узел Field Height. См. класс [FieldHeight](../../../api/library/fields/class.fieldheight_cpp.md). |
| **FIELD_SHORELINE** = 21 | Узел Field Shoreline. См. класс [FieldShoreline](../../../api/library/fields/class.fieldshoreline_cpp.md). |
| **FIELD_WEATHER** = 22 | Узел Field Weather. См. класс [FieldWeather](../../../api/library/fields/class.fieldweather_cpp.md). |
| **FIELD_END** = 22 | Конец диапазона узлов полей. |
| **PARTICLES_FIELD_BEGIN** = 23 | Начало диапазона полей частиц. |
| **PARTICLES_FIELD_SPACER** = 23 | Узел Particles Field Spacer. См. класс [ParticlesFieldSpacer](../../../api/library/objects/class.particlesfieldspacer_cpp.md). |
| **PARTICLES_FIELD_DEFLECTOR** = 24 | Узел Particles Field Deflector. См. класс [ParticlesFieldDeflector](../../../api/library/objects/class.particlesfielddeflector_cpp.md). |
| **PARTICLES_FIELD_END** = 24 | Конец диапазона узлов полей частиц. |
| **LIGHT_BEGIN** = 25 | Начало диапазона узлов источников света. |
| **LIGHT_VOXEL_PROBE** = 25 | Воксельный пробник. См. класс [LightVoxelProbe](../../../api/library/lights/class.lightvoxelprobe_cpp.md). |
| **LIGHT_ENVIRONMENT_PROBE** = 26 | Пробник окружения. См. класс [LightEnvironmentProbe](../../../api/library/lights/class.lightenvironmentprobe_cpp.md). |
| **LIGHT_PLANAR_PROBE** = 27 | Плоский пробник. См. класс [LightPlanarProbe](../../../api/library/lights/class.lightplanarprobe_cpp.md). |
| **LIGHT_OMNI** = 28 | Всенаправленный источник света. См. класс [LightOmni](../../../api/library/lights/class.lightomni_cpp.md). |
| **LIGHT_PROJ** = 29 | Проекционный источник света. См. класс [LightProj](../../../api/library/lights/class.lightproj_cpp.md). |
| **LIGHT_WORLD** = 30 | Мировой источник света. См. класс [LightWorld](../../../api/library/lights/class.lightworld_cpp.md). |
| **LIGHT_END** = 30 | Конец диапазона узлов источников света. |
| **DECAL_BEGIN** = 31 | Начало диапазона узлов декалей. |
| **DECAL_PROJ** = 31 | Узел проекционной декали. См. класс [DecalProj](../../../api/library/decals/class.decalproj_cpp.md). |
| **DECAL_ORTHO** = 32 | Узел ортографической декали. См. класс [DecalOrtho](../../../api/library/decals/class.decalortho_cpp.md). |
| **DECAL_MESH** = 33 | Узел меш-декали. См. класс [DecalMesh](../../../api/library/decals/class.decalmesh_cpp.md). |
| **DECAL_END** = 33 | Конец диапазона узлов декалей. |
| **LANDSCAPE_LAYER_BEGIN** = 34 | Начало диапазона слоёв ландшафта. |
| **LANDSCAPE_LAYER_MAP** = 34 | Карта слоёв ландшафта. См. класс [LandscapeLayerMap](../../../api/library/objects/landscape_terrain/class.landscapelayermap_cpp.md). |
| **LANDSCAPE_LAYER_END** = 34 | Конец диапазона слоёв ландшафта. |
| **OBJECT_BEGIN** = 35 | Начало диапазона узлов объектов. |
| **OBJECT_DUMMY** = 35 | Пустой объект (dummy). См. класс [ObjectDummy](../../../api/library/objects/class.objectdummy_cpp.md). |
| **OBJECT_DYNAMIC** = 36 | Динамический объект. См. класс [ObjectDynamic](../../../api/library/objects/class.objectdynamic_cpp.md). |
| **OBJECT_MESH_STATIC** = 37 | Объект статичного меша. См. класс [ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md). |
| **OBJECT_MESH_CLUSTER** = 38 | Объект [Mesh Cluster](../../../objects/objects/mesh_cluster/index.md). См. класс [ObjectMeshCluster](../../../api/library/objects/class.objectmeshcluster_cpp.md). |
| **OBJECT_MESH_CLUTTER** = 39 | Объект [Mesh Clutter](../../../objects/objects/mesh_clutter/index.md). См. класс [ObjectMeshClutter](../../../api/library/objects/class.objectmeshclutter_cpp.md). |
| **OBJECT_MESH_SKINNED_LEGACY** = 40 | Устаревший объект скиннированного меша. См. класс [ObjectMeshSkinnedLegacy](../../../api/library/objects/class.objectmeshskinnedlegacy_cpp.md). |
| **OBJECT_MESH_SKINNED** = 41 | Объект скиннированного меша. См. класс [ObjectMeshSkinned](../../../api/library/objects/class.objectmeshskinned_cpp.md). |
| **OBJECT_MESH_DYNAMIC** = 42 | Объект динамического меша. См. класс [ObjectMeshDynamic](../../../api/library/objects/class.objectmeshdynamic_cpp.md). |
| **OBJECT_MESH_SPLINE_CLUSTER** = 43 | Объект Mesh Spline Cluster. См. класс [ObjectMeshSplineCluster](../../../api/library/objects/class.objectmeshsplinecluster_cpp.md). |
| **OBJECT_LANDSCAPE_TERRAIN** = 44 | Объект LandscapeTerrain. См. класс [ObjectLandscapeTerrain](../../../api/library/objects/landscape_terrain/class.objectlandscapeterrain_cpp.md). |
| **OBJECT_TERRAIN_GLOBAL** = 45 | Объект глобального ландшафта. См. класс [ObjectTerrainGlobal](../../../api/library/objects/class.objectterrainglobal_cpp.md). |
| **OBJECT_GRASS** = 46 | Трава. См. класс [ObjectGrass](../../../api/library/objects/class.objectgrass_cpp.md). |
| **OBJECT_PARTICLES** = 47 | Объект частиц. См. класс [ObjectParticles](../../../api/library/objects/class.objectparticles_cpp.md). |
| **OBJECT_BILLBOARDS** = 48 | Объект [Billboards](../../../objects/objects/billboards/index.md) для рендеринга большого количества биллбордов. См. класс [ObjectBillboard](../../../api/library/objects/class.objectbillboards_cpp.md). |
| **OBJECT_VOLUME_BOX** = 49 | Объект объёмного параллелепипеда. См. класс [ObjectVolumeBox](../../../api/library/objects/class.objectvolumebox_cpp.md). |
| **OBJECT_VOLUME_SPHERE** = 50 | Объект объёмной сферы. См. класс [ObjectVolumeSphere](../../../api/library/objects/class.objectvolumesphere_cpp.md). |
| **OBJECT_VOLUME_OMNI** = 51 | Объект объёмного всенаправленного света. См. класс [ObjectVolumeOmni](../../../api/library/objects/class.objectvolumeomni_cpp.md). |
| **OBJECT_VOLUME_PROJ** = 52 | Объект объёмного проекционного света. См. класс [ObjectVolumeProj](../../../api/library/objects/class.objectvolumeproj_cpp.md). |
| **OBJECT_GUI** = 53 | Объект GUI. См. класс [ObjectGui](../../../api/library/objects/class.objectgui_cpp.md). |
| **OBJECT_GUI_MESH** = 54 | Объект меша GUI. См. класс [ObjectGuiMesh](../../../api/library/objects/class.objectguimesh_cpp.md). |
| **OBJECT_WATER_GLOBAL** = 55 | Объект глобальной воды. См. класс [ObjectWaterGlobal](../../../api/library/objects/class.objectwaterglobal_cpp.md). |
| **OBJECT_WATER_MESH** = 56 | Объект меша воды. См. класс [ObjectWaterMesh](../../../api/library/objects/class.objectwatermesh_cpp.md). |
| **OBJECT_SKY** = 57 | Объект неба. См. класс [ObjectSky](../../../api/library/objects/class.objectsky_cpp.md). |
| **OBJECT_CLOUD_LAYER** = 58 | Объект слоя облаков. См. класс [ObjectCloudLayer](../../../api/library/objects/class.objectcloudlayer_cpp.md). |
| **OBJECT_EXTERN** = 59 | Внешний объект (extern). См. класс [ObjectExtern](../../../api/library/objects/class.objectextern_cpp.md). |
| **OBJECT_TEXT** = 60 | Текстовый объект. См. класс [ObjectText](../../../api/library/objects/class.objecttext_cpp.md). |
| **OBJECT_END** = 60 | Конец диапазона узлов объектов. |
| **PLAYER_BEGIN** = 61 | Начало диапазона узлов игроков. |
| **PLAYER_DUMMY** = 61 | Пустой игрок (dummy). См. класс [PlayerDummy](../../../api/library/players/class.playerdummy_cpp.md). |
| **PLAYER_SPECTATOR** = 62 | Наблюдающий игрок. См. класс [PlayerSpectator](../../../api/library/players/class.playerspectator_cpp.md). |
| **PLAYER_PERSECUTOR** = 63 | Преследующий игрок. См. класс [PlayerPersecutor](../../../api/library/players/class.playerpersecutor_cpp.md). |
| **PLAYER_ACTOR** = 64 | Действующий игрок. См. класс [PlayerActor](../../../api/library/players/class.playeractor_cpp.md). |
| **PLAYER_END** = 64 | Конец диапазона узлов игроков. |
| **PHYSICAL_BEGIN** = 65 | Начало диапазона физических узлов. |
| **PHYSICAL_WIND** = 65 | Объект физического ветра. См. класс [PhysicalWind](../../../api/library/physics/class.physicalwind_cpp.md). |
| **PHYSICAL_FORCE** = 66 | Узел физической силы, позволяющий симулировать точечные силы, приложенные к динамическим объектам. См. класс [PhysicalForce](../../../api/library/physics/class.physicalforce_cpp.md). |
| **PHYSICAL_NOISE** = 67 | Узел физического шума, позволяющий симулировать поле сил. См. класс [PhysicalNoise](../../../api/library/physics/class.physicalnoise_cpp.md). |
| **PHYSICAL_WATER** = 68 | Объект физической воды, не имеющий визуального представления. См. класс [PhysicalWater](../../../api/library/physics/class.physicalwater_cpp.md). |
| **PHYSICAL_TRIGGER** = 69 | Физический триггер. См. класс [PhysicalTrigger](../../../api/library/physics/class.physicaltrigger_cpp.md). |
| **PHYSICAL_END** = 69 | Конец диапазона физических узлов. |
| **NAVIGATION_BEGIN** = 70 | Начало диапазона узлов навигации. |
| **NAVIGATION_SECTOR** = 70 | Сектор, в пределах которого выполняется поиск пути. См. класс [NavigationSector](../../../api/library/pathfinding/class.navigationsector_cpp.md). |
| **NAVIGATION_MESH** = 71 | Область навигации на основе меша, в пределах которой выполняется поиск пути. См. класс [NavigationMesh](../../../api/library/pathfinding/class.navigationmesh_cpp.md). |
| **NAVIGATION_END** = 71 | Конец диапазона узлов навигации. |
| **OBSTACLE_BEGIN** = 72 | Начало диапазона узлов препятствий. |
| **OBSTACLE_BOX** = 72 | Препятствие в форме параллелепипеда, избегаемое при поиске пути. См. класс [ObstacleBox](../../../api/library/pathfinding/class.obstaclebox_cpp.md). |
| **OBSTACLE_SPHERE** = 73 | Препятствие в форме сферы, избегаемое при поиске пути. См. класс [ObstacleSphere](../../../api/library/pathfinding/class.obstaclesphere_cpp.md). |
| **OBSTACLE_CAPSULE** = 74 | Препятствие в форме капсулы, избегаемое при поиске пути. См. класс [ObstacleCapsule](../../../api/library/pathfinding/class.obstaclecapsule_cpp.md). |
| **OBSTACLE_END** = 74 | Конец диапазона узлов препятствий. |
| **SOUND_BEGIN** = 75 | Начало диапазона звуковых узлов. |
| **SOUND_SOURCE** = 75 | Источник звука. См. класс [SoundSource](../../../api/library/sounds/class.soundsource_cpp.md). |
| **SOUND_REVERB** = 76 | Зона реверберации звука. См. класс [SoundReverb](../../../api/library/sounds/class.soundreverb_cpp.md). |
| **SOUND_END** = 76 | Конец диапазона звуковых узлов. |
| **NUM_NODES** = 77 | Счётчик типов узлов. |
| **NUM_WORLDS** = WORLD_END - WORLD_BEGIN + 1 | Счётчик типов мировых узлов. |
| **NUM_GEODETICS** = GEODETIC_END - GEODETIC_BEGIN + 1 | Счётчик типов геодезических узлов. |
| **NUM_FIELDS** = FIELD_END - FIELD_BEGIN + 1 | Счётчик типов узлов полей. |
| **NUM_PARTICLES_FIELDS** = PARTICLES_FIELD_END - PARTICLES_FIELD_BEGIN + 1 | Счётчик типов узлов полей частиц. |
| **NUM_LIGHTS** = LIGHT_END - LIGHT_BEGIN + 1 | Счётчик типов узлов источников света. |
| **NUM_DECALS** = DECAL_END - DECAL_BEGIN + 1 | Счётчик типов узлов декалей. |
| **NUM_OBJECTS** = OBJECT_END - OBJECT_BEGIN + 1 | Счётчик типов узлов объектов. |
| **NUM_PLAYERS** = PLAYER_END - PLAYER_BEGIN + 1 | Счётчик типов узлов игроков. |
| **NUM_PHYSICALS** = PHYSICAL_END - PHYSICAL_BEGIN + 1 | Счётчик типов физических узлов. |
| **NUM_NAVIGATIONS** = NAVIGATION_END - NAVIGATION_BEGIN + 1 | Счётчик типов узлов навигации. |
| **NUM_OBSTACLES** = OBSTACLE_BEGIN - OBSTACLE_END + 1 | Счётчик типов узлов препятствий. |
| **NUM_SOUNDS** = SOUND_END - SOUND_BEGIN + 1 | Счётчик типов звуковых узлов. |
| **DUMMY** = 0 | Пустой узел (dummy). См. класс [NodeDummy](../../../api/library/nodes/class.nodedummy_cpp.md). |
| **LAYER** = 1 | Узел-слой. См. класс [NodeLayer](../../../api/library/nodes/class.nodelayer_cpp.md). |
| **TRIGGER** = 2 | Пустой узел (dummy), который может вызывать callback'и при включении/отключении или перемещении. См. класс [NodeTrigger](../../../api/library/nodes/class.nodetrigger_cpp.md). |
| **REFERENCE** = 3 | Ссылка на узел, ссылающаяся на внешний файл NODE. См. класс [NodeReference](../../../api/library/nodes/class.nodereference_cpp.md). |
| **EXTERN** = 4 | Внешний узел (extern). См. класс [NodeExtern](../../../api/library/nodes/class.nodeextern_cpp.md). |

## LIFETIME

| Название | Описание |
|---|---|
| **LIFETIME_WORLD** = 0 | Временем жизни узла управляет мир. Узел будет автоматически удалён при закрытии мира. |
| **LIFETIME_ENGINE** = 1 | Временем жизни узла управляет движок. Узел будет автоматически удалён при завершении работы движка. |
| **LIFETIME_MANUAL** = 2 | Временем жизни узла управляет пользователь. Узел должен быть удалён пользователем вручную. |

### Методы класса

## Ptr < GeodeticPivot > getGeodeticPivot () const

Возвращает текущий указатель на геодезический пивот узла.
### Возвращаемое значение

Текущий геодезический пивот, или NULL, если узел не является дочерним для узла геодезического пивота.
## void setVariable ( const Variable & variable )

Задаёт новое значение единственного неименованного параметра-переменной узла. Если эта переменная не существует, она будет создана с указанным значением (при запросе несуществующего значения будет возвращено 0).
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **variable** - Значение переменной.

## const Variable & getVariable () const

Возвращает текущее значение единственного неименованного параметра-переменной узла. Если эта переменная не существует, она будет создана с указанным значением (при запросе несуществующего значения будет возвращено 0).
### Возвращаемое значение

Текущее значение переменной.
## void setWorldScale ( const Math:: vec3 & scale )

Задаёт новый масштаб узла в мировом пространстве.
> **Notice:** **По возможности следует избегать масштабирования узлов**, так как оно требует дополнительных вычислений и может привести к накоплению ошибок.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **scale** - Масштаб узла в мировом пространстве.

## Math:: vec3 getWorldScale () const

Возвращает текущий масштаб узла в мировом пространстве.
> **Notice:** **По возможности следует избегать масштабирования узлов**, так как оно требует дополнительных вычислений и может привести к накоплению ошибок.


### Возвращаемое значение

Текущий масштаб узла в мировом пространстве.
## void setWorldPosition ( const Math:: Vec3 & position )

Задаёт новую позицию узла в мировых координатах.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md)&* **position** - Позиция узла в мировых координатах.

## Math:: Vec3 getWorldPosition () const

Возвращает текущую позицию узла в мировых координатах.
### Возвращаемое значение

Текущая позиция узла в мировых координатах.
## void setScale ( const Math:: vec3 & scale )

Задаёт новый масштаб узла.
> **Notice:** **По возможности следует избегать масштабирования узлов**, так как оно требует дополнительных вычислений и может привести к накоплению ошибок.


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md)&* **scale** - Масштаб узла в локальном пространстве.

## Math:: vec3 getScale () const

Возвращает текущий масштаб узла.
> **Notice:** **По возможности следует избегать масштабирования узлов**, так как оно требует дополнительных вычислений и может привести к накоплению ошибок.


### Возвращаемое значение

Текущий масштаб узла в локальном пространстве.
## void setPosition ( const Math:: Vec3 & position )

Задаёт новую позицию узла.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md)&* **position** - Позиция узла в локальном пространстве.

## Math:: Vec3 getPosition () const

Возвращает текущую позицию узла.
### Возвращаемое значение

Текущая позиция узла в локальном пространстве.
## Math:: vec3 getBodyAngularVelocity () const

Возвращает текущую угловую скорость физического тела узла в мировом пространстве.
### Возвращаемое значение

Текущая угловая скорость физического тела узла в мировом пространстве.
## Math:: vec3 getBodyLinearVelocity () const

Возвращает текущую линейную скорость физического тела узла в локальном пространстве.
### Возвращаемое значение

Текущая линейная скорость физического тела узла в локальном пространстве.
## Ptr < BodyRigid > getObjectBodyRigid () const

Возвращает текущее [rigid body](../../../principles/physics/bodies/rigid/index.md), назначенное узлу, если он является узлом объекта.
### Возвращаемое значение

Текущее [rigid body](../../../principles/physics/bodies/rigid/index.md), назначенное узлу, если он является узлом объекта; иначе NULL (0).
## Ptr < Body > getObjectBody () const

Возвращает текущее физическое тело, назначенное узлу, если он является узлом объекта.
### Возвращаемое значение

Текущее физическое тело, назначенное узлу, если он является узлом объекта; иначе NULL (0).
## Math:: WorldBoundSphere getWorldBoundSphere () const

Возвращает текущую ограничивающую сферу узла в мировой системе координат.
### Возвращаемое значение

Текущая ограничивающая сфера узла в мировой системе координат.
## Math:: WorldBoundBox getWorldBoundBox () const

Возвращает текущий ограничивающий параллелепипед узла в мировой системе координат.
### Возвращаемое значение

Текущий [world bounding box](../../../api/library/math/bounds/class.worldboundbox_cpp.md).
## Math:: BoundSphere getBoundSphere () const

Возвращает текущую ограничивающую сферу узла.
> **Notice:** Координаты ограничивающей сферы указаны в локальной системе координат узла. Чтобы получить ограничивающую сферу в мировых координатах, используйте метод [*getWorldBoundSphere()*](#getWorldBoundSphere_WorldBoundSphere).


### Возвращаемое значение

Текущая [bounding sphere](../../../api/library/math/bounds/class.boundsphere_cpp.md) узла.
## Math:: BoundBox getBoundBox () const

Возвращает текущий ограничивающий параллелепипед узла.
> **Notice:** Координаты ограничивающего параллелепипеда указаны в локальной системе координат узла. Чтобы получить ограничивающий параллелепипед в мировых координатах, используйте метод [*getWorldBoundBox()*](#getWorldBoundBox_WorldBoundBox).


### Возвращаемое значение

Текущий [bounding box](../../../api/library/math/bounds/class.boundbox_cpp.md) узла.
## void setOldWorldTransform ( const Math:: Mat4 & transform )

Задаёт новую старую (предыдущего кадра) матрицу трансформации узла в мировых координатах.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)&* **transform** - Старая (предыдущего кадра) матрица трансформации узла в мировых координатах.

## Math:: Mat4 getOldWorldTransform () const

Возвращает текущую старую (предыдущего кадра) матрицу трансформации узла в мировых координатах.
### Возвращаемое значение

Текущая старая (предыдущего кадра) матрица трансформации узла в мировых координатах.
## void setWorldTransform ( const Math:: Mat4 & transform )

Задаёт новую матрицу трансформации узла в мировых координатах.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)&* **transform** - Матрица трансформации узла в мировых координатах.

## Math:: Mat4 getWorldTransform () const

Возвращает текущую матрицу трансформации узла в мировых координатах.
### Возвращаемое значение

Текущая матрица трансформации узла в мировых координатах.
## void setTransform ( const Math:: Mat4 & transform )

Задаёт новую матрицу трансформации узла в координатах его родителя.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md)&* **transform** - Матрица трансформации узла в локальных координатах.

## Math:: Mat4 getTransform () const

Возвращает текущую матрицу трансформации узла в координатах его родителя.
### Возвращаемое значение

Текущая матрица трансформации узла в локальных координатах.
## int getNumProperties () const

Возвращает текущее общее количество свойств, связанных с узлом.
### Возвращаемое значение

Текущее общее количество свойств, связанных с узлом.
## Ptr < Node > getPossessor () const

Возвращает текущего владельца (possessor) узла. Владельцами могут быть следующие узлы:
- NodeReference
- WorldCluster
- WorldClutter
- WorldLayer

Эта функция может применяться только к корневому узлу внутри ссылки на узел.
### Возвращаемое значение

Текущий владелец узла, если он существует; иначе NULL.
## int getNumChildren () const

Возвращает текущее количество дочерних узлов узла.
### Возвращаемое значение

Текущее количество дочерних узлов.
## Ptr < Node > getRootNode () const

Возвращает текущий корневой узел для узла. Этот метод ищет корневой узел среди всех родителей и [possessors](#getPossessor_Node) узла вверх по иерархии. Если узел не имеет родителя или владельца, будет возвращён сам узел.
### Возвращаемое значение

Текущий корневой узел для узла.
## void setParent ( const Ptr < Node >& parent )

Задаёт нового родителя узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>&* **parent** - Родитель узла или **NULL** (**0**), если у узла нет родителя.

## Ptr < Node > getParent () const

Возвращает текущего родителя узла.
### Возвращаемое значение

Текущий родитель узла или **NULL** (**0**), если у узла нет родителя.
## int getNumAncestors () const

Возвращает текущее количество предков узла.
### Возвращаемое значение

Текущее количество предков узла.
## void setName ( const char * name )

Задаёт новое имя узла.
### Аргументы

- *const char ** **name** - Имя узла.

## const char * getName () const

Возвращает текущее имя узла.
### Возвращаемое значение

Текущее имя узла.
## void setQuery ( bool query )

Задаёт новое значение, указывающее, используется ли occlusion query для узла. По умолчанию false (не используется).
### Аргументы

- *bool* **query** - Установите **true**, чтобы включить использование occlusion query для узла; **false** - чтобы отключить.

## bool isQuery () const

Возвращает текущее значение, указывающее, используется ли occlusion query для узла. По умолчанию false (не используется).
### Возвращаемое значение

**true**, если для узла используется occlusion query; иначе **false**.
## void setClutterInteractionEnabled ( bool enabled )

Задаёт новое значение, указывающее, включено ли для узла взаимодействие с [World Clutters](../../../api/library/worlds/class.worldclutter_cpp.md) и [Mesh Clutters](../../../api/library/objects/class.objectmeshclutter_cpp.md).
> **Notice:** Рекомендуется отключать эту опцию для повышения производительности, когда вырезание узла из clutter'ов не требуется. Особенно если мир содержит значительное количество таких узлов.


### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить взаимодействие с [World Clutters](../../../api/library/worlds/class.worldclutter_cpp.md) и [Mesh Clutters](../../../api/library/objects/class.objectmeshclutter_cpp.md); **false** - чтобы отключить.

## bool isClutterInteractionEnabled () const

Возвращает текущее значение, указывающее, включено ли для узла взаимодействие с [World Clutters](../../../api/library/worlds/class.worldclutter_cpp.md) и [Mesh Clutters](../../../api/library/objects/class.objectmeshclutter_cpp.md).
> **Notice:** Рекомендуется отключать эту опцию для повышения производительности, когда вырезание узла из clutter'ов не требуется. Особенно если мир содержит значительное количество таких узлов.


### Возвращаемое значение

**true**, если взаимодействие с [World Clutters](../../../api/library/worlds/class.worldclutter_cpp.md) и [Mesh Clutters](../../../api/library/objects/class.objectmeshclutter_cpp.md) включено; иначе **false**.
## void setGrassInteractionEnabled ( bool enabled )

Задаёт новое значение, указывающее, включено ли для узла взаимодействие с узлами [Grass](../../../api/library/objects/class.objectgrass_cpp.md).
> **Notice:** Рекомендуется отключать эту опцию для повышения производительности, когда вырезание узла из травы не требуется. Особенно если мир содержит значительное количество таких узлов.


### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить взаимодействие с узлами [Grass](../../../api/library/objects/class.objectgrass_cpp.md); **false** - чтобы отключить.

## bool isGrassInteractionEnabled () const

Возвращает текущее значение, указывающее, включено ли для узла взаимодействие с узлами [Grass](../../../api/library/objects/class.objectgrass_cpp.md).
> **Notice:** Рекомендуется отключать эту опцию для повышения производительности, когда вырезание узла из травы не требуется. Особенно если мир содержит значительное количество таких узлов.


### Возвращаемое значение

**true**, если взаимодействие с узлами [Grass](../../../api/library/objects/class.objectgrass_cpp.md) включено; иначе **false**.
## void setTriggerInteractionEnabled ( bool enabled )

Задаёт новое значение, указывающее, включено ли для узла взаимодействие с узлами [WorldTrigger](../../../api/library/worlds/class.worldtrigger_cpp.md).
> **Notice:** Рекомендуется отключать эту опцию для повышения производительности, когда взаимодействие узла с [World Triggers](../../../api/library/worlds/class.worldtrigger_cpp.md) не требуется. Особенно если мир содержит значительное количество таких узлов.


### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить взаимодействие с [World Triggers](../../../api/library/worlds/class.worldtrigger_cpp.md); **false** - чтобы отключить.

## bool isTriggerInteractionEnabled () const

Возвращает текущее значение, указывающее, включено ли для узла взаимодействие с узлами [WorldTrigger](../../../api/library/worlds/class.worldtrigger_cpp.md).
> **Notice:** Рекомендуется отключать эту опцию для повышения производительности, когда взаимодействие узла с [World Triggers](../../../api/library/worlds/class.worldtrigger_cpp.md) не требуется. Особенно если мир содержит значительное количество таких узлов.


### Возвращаемое значение

**true**, если взаимодействие с [World Triggers](../../../api/library/worlds/class.worldtrigger_cpp.md) включено; иначе **false**.
## void setImmovable ( bool immovable )

Задаёт новое значение, указывающее, является ли узел неподвижным (clutter) объектом, то есть перемещён ли он в отдельное пространственное дерево для неподвижных (статичных) объектов, оптимизирующее управление узлами. Существует ряд ограничений для узлов, считающихся неподвижными. Любое действие, затрагивающее пространственное дерево, запрещено и вызывает предупреждение: нельзя изменять состояние узла (включён/отключён), поверхности, границы, трансформацию, дистанцию видимости, а также перемещать узел, назначать не-пустое физическое тело или даже отключать флаг *Immovable*, так как это также приводит к перестроению пространственного дерева.
> **Notice:** При необходимости эти предупреждения можно отключить с помощью метода [*World::setMovingImmovableNodeMode()*](../../../api/library/engine/class.world_cpp.md#setMovingImmovableNodeMode_int_void).


### Аргументы

- *bool* **immovable** - Установите **true**, чтобы включить свойство неподвижного (clutter) объекта для узла; **false** - чтобы отключить.

## bool isImmovable () const

Возвращает текущее значение, указывающее, является ли узел неподвижным (clutter) объектом, то есть перемещён ли он в отдельное пространственное дерево для неподвижных (статичных) объектов, оптимизирующее управление узлами. Существует ряд ограничений для узлов, считающихся неподвижными. Любое действие, затрагивающее пространственное дерево, запрещено и вызывает предупреждение: нельзя изменять состояние узла (включён/отключён), поверхности, границы, трансформацию, дистанцию видимости, а также перемещать узел, назначать не-пустое физическое тело или даже отключать флаг *Immovable*, так как это также приводит к перестроению пространственного дерева.
> **Notice:** При необходимости эти предупреждения можно отключить с помощью метода [*World::setMovingImmovableNodeMode()*](../../../api/library/engine/class.world_cpp.md#setMovingImmovableNodeMode_int_void).


### Возвращаемое значение

**true**, если для узла включено свойство неподвижного (clutter) объекта; иначе **false**.
## void setHandled ( bool handled )

Задаёт новое значение, указывающее, отображается ли манипулятор (handle) узла. Эта опция действительна только для невидимых узлов, таких как источники света и звука, системы частиц и управляющие миром узлы ([WorldOccluder](../../../api/library/worlds/class.worldoccluder_cpp.md), триггеры, выражения и т.д.)
### Аргументы

- *bool* **handled** - Установите **true**, чтобы включить отображение манипулятора узла; **false** - чтобы отключить.

## bool isHandled () const

Возвращает текущее значение, указывающее, отображается ли манипулятор узла. Эта опция действительна только для невидимых узлов, таких как источники света и звука, системы частиц и управляющие миром узлы ([WorldOccluder](../../../api/library/worlds/class.worldoccluder_cpp.md), триггеры, выражения и т.д.)
### Возвращаемое значение

**true**, если отображение манипулятора узла включено; иначе **false**.
## void setEnabled ( bool enabled )

Задаёт новое значение, указывающее, включены ли узел и его родительские узлы.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить узел; **false** - чтобы отключить.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включены ли узел и его родительские узлы.
### Возвращаемое значение

**true**, если узел включён; иначе **false**.
## bool isExtern () const

Возвращает текущее значение, указывающее, является ли узел внешним (extern) узлом (его тип - один из следующих: *[NODE_EXTERN](#NODE_EXTERN), [OBJECT_EXTERN](#OBJECT_EXTERN), [WORLD_EXTERN](#WORLD_EXTERN)*).
### Возвращаемое значение

**true**, если узел является внешним узлом; иначе **false**.
## bool isField () const

Возвращает текущее значение, указывающее, является ли узел узлом поля (его тип - один из *[FIELD_*](#FIELD_ANIMATION)*).
### Возвращаемое значение

**true**, если узел является узлом поля; иначе **false**.
## bool isParticlesField () const

Возвращает текущее значение, указывающее, является ли узел узлом поля частиц (его тип - один из *[PARTICLES_FIELD_*](#PARTICLES_FIELD_BEGIN)*).
### Возвращаемое значение

**true**, если узел является узлом поля частиц; иначе **false**.
## bool isSound () const

Возвращает текущее значение, указывающее, является ли узел звуковым узлом (его тип - *[SOUND_*](#SOUND_BEGIN)*).
### Возвращаемое значение

**true**, если узел является звуковым узлом; иначе **false**.
## bool isObstacle () const

Возвращает текущее значение, указывающее, является ли узел узлом препятствия (его тип - *[OBSTACLE_*](#OBSTACLE_BEGIN)*).
### Возвращаемое значение

**true**, если узел является узлом препятствия; иначе **false**.
## bool isNavigation () const

Возвращает текущее значение, указывающее, является ли заданный узел узлом навигации.
### Возвращаемое значение

**true**, если узел является узлом навигации; иначе **false**.
## bool isPhysical () const

Возвращает текущее значение, указывающее, является ли узел физическим узлом (его тип - *[PHYSICAL_*](#PHYSICAL_BEGIN)*).
### Возвращаемое значение

**true**, если узел является физическим узлом; иначе **false**.
## bool isPlayer () const

Возвращает текущее значение, указывающее, является ли узел узлом игрока (его тип - *[PLAYER_*](#PLAYER_BEGIN)*).
### Возвращаемое значение

**true**, если узел является узлом игрока; иначе **false**.
## bool isObject () const

Возвращает текущее значение, указывающее, является ли узел узлом объекта (его тип - *[OBJECT_*](#OBJECT_BEGIN)*).
### Возвращаемое значение

**true**, если узел является узлом объекта; иначе **false**.
## bool isDecal () const

Возвращает текущее значение, указывающее, является ли узел узлом декали (его тип - *[DECAL_*](#DECAL_BEGIN)*).
### Возвращаемое значение

**true**, если узел является узлом декали; иначе **false**.
## bool isLight () const

Возвращает текущее значение, указывающее, является ли узел источником света (его тип - *[LIGHT_*](#LIGHT_BEGIN)*).
### Возвращаемое значение

**true**, если узел является источником света; иначе **false**.
## bool isGeodetic () const

Возвращает текущее значение, указывающее, является ли узел геодезическим узлом.
### Возвращаемое значение

**true**, если узел является геодезическим узлом; иначе **false**.
## bool isWorld () const

Возвращает текущее значение, указывающее, является ли узел мировым узлом (его тип - *[WORLD_*](#WORLD_BEGIN)*).
### Возвращаемое значение

**true**, если узел является мировым узлом; иначе **false**.
## bool isImmovableSupported () const

Возвращает текущее значение, указывающее, может ли узел быть перемещён в отдельное пространственное дерево для неподвижных (статичных) объектов, оптимизирующее управление узлами.
### Возвращаемое значение

**true**, если узел может быть неподвижным; иначе **false**.
## bool isSurfacesCollisionSupported () const

Возвращает текущее значение, указывающее, поддерживаются ли столкновения с поверхностями узла.
### Возвращаемое значение

**true**, если столкновения с поверхностями узла поддерживаются; иначе **false**.
## bool isSurfacesIntersectionSupported () const

Возвращает текущее значение, указывающее, поддерживаются ли пересечения с поверхностями узла.
### Возвращаемое значение

**true**, если пересечения с поверхностями узла поддерживаются; иначе **false**.
## const char * getTypeName () const

Возвращает текущее имя типа узла.
### Возвращаемое значение

Текущее имя типа узла.
## Node::TYPE getType () const

Возвращает текущий тип узла.
### Возвращаемое значение

Текущий идентификатор типа узла.
## void setID ( int id )

Задаёт новый runtime-ID узла. Он может отличаться от файлового ID, который получается через *[*getIDFromFile()*](#getIDFromFile_int)*.
> **Notice:** См. также функцию *[*Unigine::World::getNodeByID()*](../../../api/library/engine/class.world_cpp.md#getNodeByID_int_Node)*.


### Аргументы

- *int* **id** - Runtime-ID узла.

## int getID () const

Возвращает текущий runtime-ID узла. Он может отличаться от файлового ID, который получается через *[*getIDFromFile()*](#getIDFromFile_int)*.
> **Notice:** См. также функцию *[*Unigine::World::getNodeByID()*](../../../api/library/engine/class.world_cpp.md#getNodeByID_int_Node)*.


### Возвращаемое значение

Текущий runtime-ID узла.
## int getIDFromFile () const

Возвращает текущий ID узла, загруженного из файла `*.node` или `*.world`. Он может отличаться от runtime-ID узла, который получается через *[*getID()*](#getID_int)*.
### Возвращаемое значение

Текущий ID узла, загруженного из файла `*.node` или `*.world`.
## void setSaveToWorldEnabled ( bool enabled )

Задаёт новое значение, указывающее, включено ли сохранение в файл `*.world` для узла и всех его дочерних узлов (если есть).
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить сохранение в файл `*.world` для узла и всех его дочерних узлов (если есть); **false** - чтобы отключить.

## bool isSaveToWorldEnabled () const

Возвращает текущее значение, указывающее, включено ли сохранение в файл `*.world` для узла и всех его дочерних узлов (если есть).
### Возвращаемое значение

**true**, если сохранение в файл `*.world` для узла и всех его дочерних узлов (если есть) включено; иначе **false**.
## bool isSaveToWorldEnabledSelf () const

Возвращает текущее значение, указывающее, включено ли сохранение в файл `*.world` для узла.
### Возвращаемое значение

**true**, если сохранение в файл `*.world` для узла включено; иначе **false**.
## void setShowInEditorEnabled ( bool enabled )

Задаёт новое значение, указывающее, включено ли отображение узла в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md).
> **Notice:** Узел будет отображаться в иерархии только если эта опция включена также для всех его предков.


### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отображение узла в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md); **false** - чтобы отключить.

## bool isShowInEditorEnabled () const

Возвращает текущее значение, указывающее, включено ли отображение узла в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md).
> **Notice:** Узел будет отображаться в иерархии только если эта опция включена также для всех его предков.


### Возвращаемое значение

**true**, если отображение узла в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md) включено; иначе **false**.
## bool isShowInEditorEnabledSelf () const

Возвращает текущее значение, указывающее, включено ли отображение узла в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md).
### Возвращаемое значение

**true**, если отображение узла в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md) включено; иначе **false**.
## int getNumWorldTriggers () const

Возвращает текущее количество World Triggers, внутри которых в данный момент находится узел.
### Возвращаемое значение

Текущее количество World Triggers, внутри которых в данный момент находится узел, или 0, если узел в данный момент не находится ни в одном World Trigger.
## Math:: WorldBoundSphere getSpatialBoundSphere () const

Возвращает текущую ограничивающую сферу с мировыми координатами, которая участвует в физических вычислениях, но не учитывает дочерние узлы. Эта ограничивающая сфера используется пространственным деревом.
### Возвращаемое значение

Текущая ограничивающая сфера с мировыми координатами.
## Math:: WorldBoundBox getSpatialBoundBox () const

Возвращает текущий ограничивающий параллелепипед с мировыми координатами, который участвует в физических вычислениях, но не учитывает дочерние узлы. Этот ограничивающий параллелепипед используется пространственным деревом.
### Возвращаемое значение

Текущий ограничивающий параллелепипед с мировыми координатами.
## bool isLandscapeLayer () const

Возвращает текущее значение, указывающее, является ли узел слоем ландшафта (его тип - [*LANDSCAPE_LAYER_**](#LANDSCAPE_LAYER_BEGIN)).
### Возвращаемое значение

**true**, если узел является слоем ландшафта; иначе **false**.
## Math:: Mat4 getIWorldTransform () const

Возвращает текущую обратную матрицу трансформации узла для трансформаций в мировых координатах.
### Возвращаемое значение

Текущая обратная матрица трансформации.
## Math:: Vec3 getOldWorldPosition () const

Возвращает текущую старую (предыдущего кадра) позицию узла в мировых координатах.
### Возвращаемое значение

Текущая старая (предыдущего кадра) позиция узла в мировых координатах.
## void setLifetime ( Node::LIFETIME lifetime )

Задаёт новый тип управления временем жизни для корня (либо [parent](#getParent_Node), либо [possessor](#getPossessor_Node)) узла, либо для самого узла (если он не является дочерним и не принадлежит другому узлу).
> **Notice:** Время жизни каждого узла в иерархии определяется его корнем (либо [parent](#getParent_Node), либо [possessor](#getPossessor_Node)). Таким образом, тип управления временем жизни, заданный для дочернего узла, отличающийся от заданного для корня, игнорируется.


### Аргументы

- *[Node::LIFETIME](../../../api/library/nodes/class.node_cpp.md#LIFETIME)* **lifetime** - Тип управления временем жизни для корневого узла (см. перечисление [*LIFETIME*](#LIFETIME)).

## Node::LIFETIME getLifetime () const

Возвращает текущий тип управления временем жизни для корня (либо [parent](#getParent_Node), либо [possessor](#getPossessor_Node)) узла, либо для самого узла (если он не является дочерним и не принадлежит другому узлу).
> **Notice:** Время жизни каждого узла в иерархии определяется его корнем (либо [parent](#getParent_Node), либо [possessor](#getPossessor_Node)). Таким образом, тип управления временем жизни, заданный для дочернего узла, отличающийся от заданного для корня, игнорируется.


### Возвращаемое значение

Текущий тип управления временем жизни для корневого узла (см. перечисление [*LIFETIME*](#LIFETIME)).
## Event<const Ptr < Node > &> getEventTransformChanged () const

событие, срабатывающее при изменении трансформации узла. Это событие срабатывает немедленно при возникновении изменения, независимо от того, где оно было сделано, не дожидаясь следующего кадра. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TransformChanged
void transformchanged_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события TransformChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections transformchanged_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
publisher->getEventTransformChanged().connect(transformchanged_event_connections, transformchanged_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
publisher->getEventTransformChanged().connect(transformchanged_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события TransformChanged (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
transformchanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection transformchanged_event_connection;

// подписка на событие TransformChanged с функцией-обработчиком, сохраняя соединение
publisher->getEventTransformChanged().connect(transformchanged_event_connection, transformchanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
transformchanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
transformchanged_event_connection.setEnabled(true);

// ...

// удаление подписки на событие TransformChanged через соединение
transformchanged_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события TransformChanged, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события TransformChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventTransformChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId transformchanged_handler_id;

// подписка на событие TransformChanged с функцией-обработчиком лямбда и сохранением ID соединения
transformchanged_handler_id = publisher->getEventTransformChanged().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события TransformChanged (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
publisher->getEventTransformChanged().disconnect(transformchanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TransformChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventTransformChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventTransformChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, int> getEventPropertyNodeSlotsChanged () const

событие, срабатывающее при изменении количества слотов свойств узла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**, int **num_slots**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PropertyNodeSlotsChanged
void propertynodeslotschanged_event_handler(const Ptr<Node> & node,  int num_slots)
{
	Log::message("\Обработка события PropertyNodeSlotsChanged\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections propertynodeslotschanged_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventPropertyNodeSlotsChanged().connect(propertynodeslotschanged_event_connections, propertynodeslotschanged_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventPropertyNodeSlotsChanged().connect(propertynodeslotschanged_event_connections, [](const Ptr<Node> & node,  int num_slots) {
		Log::message("\Обработка события PropertyNodeSlotsChanged (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
propertynodeslotschanged_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection propertynodeslotschanged_event_connection;

// подписка на событие PropertyNodeSlotsChanged с функцией-обработчиком, сохраняя соединение
Node::getEventPropertyNodeSlotsChanged().connect(propertynodeslotschanged_event_connection, propertynodeslotschanged_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
propertynodeslotschanged_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
propertynodeslotschanged_event_connection.setEnabled(true);

// ...

// удаление подписки на событие PropertyNodeSlotsChanged через соединение
propertynodeslotschanged_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события PropertyNodeSlotsChanged, реализованный как член класса
	void event_handler(const Ptr<Node> & node,  int num_slots)
	{
		Log::message("\Обработка события PropertyNodeSlotsChanged\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventPropertyNodeSlotsChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId propertynodeslotschanged_handler_id;

// подписка на событие PropertyNodeSlotsChanged с функцией-обработчиком лямбда и сохранением ID соединения
propertynodeslotschanged_handler_id = Node::getEventPropertyNodeSlotsChanged().connect(e_connections, [](const Ptr<Node> & node,  int num_slots) {
		Log::message("\Обработка события PropertyNodeSlotsChanged (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventPropertyNodeSlotsChanged().disconnect(propertynodeslotschanged_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PropertyNodeSlotsChanged при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventPropertyNodeSlotsChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventPropertyNodeSlotsChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, const Ptr < Property > &, int> getEventPropertyNodeAdd () const

событие, срабатывающее при назначении узлу нового свойства. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**, const Ptr<Property> & **property**, int **property_index**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PropertyNodeAdd
void propertynodeadd_event_handler(const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index)
{
	Log::message("\Обработка события PropertyNodeAdd\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections propertynodeadd_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventPropertyNodeAdd().connect(propertynodeadd_event_connections, propertynodeadd_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventPropertyNodeAdd().connect(propertynodeadd_event_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index) {
		Log::message("\Обработка события PropertyNodeAdd (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
propertynodeadd_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection propertynodeadd_event_connection;

// подписка на событие PropertyNodeAdd с функцией-обработчиком, сохраняя соединение
Node::getEventPropertyNodeAdd().connect(propertynodeadd_event_connection, propertynodeadd_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
propertynodeadd_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
propertynodeadd_event_connection.setEnabled(true);

// ...

// удаление подписки на событие PropertyNodeAdd через соединение
propertynodeadd_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события PropertyNodeAdd, реализованный как член класса
	void event_handler(const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index)
	{
		Log::message("\Обработка события PropertyNodeAdd\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventPropertyNodeAdd().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId propertynodeadd_handler_id;

// подписка на событие PropertyNodeAdd с функцией-обработчиком лямбда и сохранением ID соединения
propertynodeadd_handler_id = Node::getEventPropertyNodeAdd().connect(e_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index) {
		Log::message("\Обработка события PropertyNodeAdd (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventPropertyNodeAdd().disconnect(propertynodeadd_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PropertyNodeAdd при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventPropertyNodeAdd().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventPropertyNodeAdd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, const Ptr < Property > &, int> getEventPropertyNodeRemove () const

событие, срабатывающее при удалении свойства из списка свойств узла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**, const Ptr<Property> & **property**, int **property_index**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PropertyNodeRemove
void propertynoderemove_event_handler(const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index)
{
	Log::message("\Обработка события PropertyNodeRemove\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections propertynoderemove_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventPropertyNodeRemove().connect(propertynoderemove_event_connections, propertynoderemove_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventPropertyNodeRemove().connect(propertynoderemove_event_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index) {
		Log::message("\Обработка события PropertyNodeRemove (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
propertynoderemove_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection propertynoderemove_event_connection;

// подписка на событие PropertyNodeRemove с функцией-обработчиком, сохраняя соединение
Node::getEventPropertyNodeRemove().connect(propertynoderemove_event_connection, propertynoderemove_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
propertynoderemove_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
propertynoderemove_event_connection.setEnabled(true);

// ...

// удаление подписки на событие PropertyNodeRemove через соединение
propertynoderemove_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события PropertyNodeRemove, реализованный как член класса
	void event_handler(const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index)
	{
		Log::message("\Обработка события PropertyNodeRemove\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventPropertyNodeRemove().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId propertynoderemove_handler_id;

// подписка на событие PropertyNodeRemove с функцией-обработчиком лямбда и сохранением ID соединения
propertynoderemove_handler_id = Node::getEventPropertyNodeRemove().connect(e_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index) {
		Log::message("\Обработка события PropertyNodeRemove (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventPropertyNodeRemove().disconnect(propertynoderemove_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PropertyNodeRemove при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventPropertyNodeRemove().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventPropertyNodeRemove().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, const Ptr < Property > &, int> getEventPropertyChangeEnabled () const

событие, срабатывающее при изменении состояния *enabled* свойства узла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**, const Ptr<Property> & **property**, int **property_index**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PropertyChangeEnabled
void propertychangeenabled_event_handler(const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index)
{
	Log::message("\Обработка события PropertyChangeEnabled\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections propertychangeenabled_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventPropertyChangeEnabled().connect(propertychangeenabled_event_connections, propertychangeenabled_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventPropertyChangeEnabled().connect(propertychangeenabled_event_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index) {
		Log::message("\Обработка события PropertyChangeEnabled (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
propertychangeenabled_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection propertychangeenabled_event_connection;

// подписка на событие PropertyChangeEnabled с функцией-обработчиком, сохраняя соединение
Node::getEventPropertyChangeEnabled().connect(propertychangeenabled_event_connection, propertychangeenabled_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
propertychangeenabled_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
propertychangeenabled_event_connection.setEnabled(true);

// ...

// удаление подписки на событие PropertyChangeEnabled через соединение
propertychangeenabled_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события PropertyChangeEnabled, реализованный как член класса
	void event_handler(const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index)
	{
		Log::message("\Обработка события PropertyChangeEnabled\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventPropertyChangeEnabled().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId propertychangeenabled_handler_id;

// подписка на событие PropertyChangeEnabled с функцией-обработчиком лямбда и сохранением ID соединения
propertychangeenabled_handler_id = Node::getEventPropertyChangeEnabled().connect(e_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property,  int property_index) {
		Log::message("\Обработка события PropertyChangeEnabled (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventPropertyChangeEnabled().disconnect(propertychangeenabled_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PropertyChangeEnabled при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventPropertyChangeEnabled().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventPropertyChangeEnabled().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, int, int> getEventPropertyNodeSwap () const

событие, срабатывающее при обмене позициями двух свойств в списке свойств узла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**, int **index_from**, int **index_to**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PropertyNodeSwap
void propertynodeswap_event_handler(const Ptr<Node> & node,  int index_from,  int index_to)
{
	Log::message("\Обработка события PropertyNodeSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections propertynodeswap_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventPropertyNodeSwap().connect(propertynodeswap_event_connections, propertynodeswap_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventPropertyNodeSwap().connect(propertynodeswap_event_connections, [](const Ptr<Node> & node,  int index_from,  int index_to) {
		Log::message("\Обработка события PropertyNodeSwap (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
propertynodeswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection propertynodeswap_event_connection;

// подписка на событие PropertyNodeSwap с функцией-обработчиком, сохраняя соединение
Node::getEventPropertyNodeSwap().connect(propertynodeswap_event_connection, propertynodeswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
propertynodeswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
propertynodeswap_event_connection.setEnabled(true);

// ...

// удаление подписки на событие PropertyNodeSwap через соединение
propertynodeswap_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события PropertyNodeSwap, реализованный как член класса
	void event_handler(const Ptr<Node> & node,  int index_from,  int index_to)
	{
		Log::message("\Обработка события PropertyNodeSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventPropertyNodeSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId propertynodeswap_handler_id;

// подписка на событие PropertyNodeSwap с функцией-обработчиком лямбда и сохранением ID соединения
propertynodeswap_handler_id = Node::getEventPropertyNodeSwap().connect(e_connections, [](const Ptr<Node> & node,  int index_from,  int index_to) {
		Log::message("\Обработка события PropertyNodeSwap (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventPropertyNodeSwap().disconnect(propertynodeswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PropertyNodeSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventPropertyNodeSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventPropertyNodeSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, const Ptr < Property > &> getEventPropertySurfaceAdd () const

событие, срабатывающее при назначении свойства поверхности объекта. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**, const Ptr<Property> & **property**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PropertySurfaceAdd
void propertysurfaceadd_event_handler(const Ptr<Node> & node,  const Ptr<Property> & property)
{
	Log::message("\Обработка события PropertySurfaceAdd\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections propertysurfaceadd_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventPropertySurfaceAdd().connect(propertysurfaceadd_event_connections, propertysurfaceadd_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventPropertySurfaceAdd().connect(propertysurfaceadd_event_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property) {
		Log::message("\Обработка события PropertySurfaceAdd (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
propertysurfaceadd_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection propertysurfaceadd_event_connection;

// подписка на событие PropertySurfaceAdd с функцией-обработчиком, сохраняя соединение
Node::getEventPropertySurfaceAdd().connect(propertysurfaceadd_event_connection, propertysurfaceadd_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
propertysurfaceadd_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
propertysurfaceadd_event_connection.setEnabled(true);

// ...

// удаление подписки на событие PropertySurfaceAdd через соединение
propertysurfaceadd_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события PropertySurfaceAdd, реализованный как член класса
	void event_handler(const Ptr<Node> & node,  const Ptr<Property> & property)
	{
		Log::message("\Обработка события PropertySurfaceAdd\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventPropertySurfaceAdd().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId propertysurfaceadd_handler_id;

// подписка на событие PropertySurfaceAdd с функцией-обработчиком лямбда и сохранением ID соединения
propertysurfaceadd_handler_id = Node::getEventPropertySurfaceAdd().connect(e_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property) {
		Log::message("\Обработка события PropertySurfaceAdd (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventPropertySurfaceAdd().disconnect(propertysurfaceadd_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PropertySurfaceAdd при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventPropertySurfaceAdd().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventPropertySurfaceAdd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, const Ptr < Property > &> getEventPropertySurfaceRemove () const

событие, срабатывающее при удалении свойства с поверхности объекта. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**, const Ptr<Property> & **property**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события PropertySurfaceRemove
void propertysurfaceremove_event_handler(const Ptr<Node> & node,  const Ptr<Property> & property)
{
	Log::message("\Обработка события PropertySurfaceRemove\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections propertysurfaceremove_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventPropertySurfaceRemove().connect(propertysurfaceremove_event_connections, propertysurfaceremove_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventPropertySurfaceRemove().connect(propertysurfaceremove_event_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property) {
		Log::message("\Обработка события PropertySurfaceRemove (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
propertysurfaceremove_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection propertysurfaceremove_event_connection;

// подписка на событие PropertySurfaceRemove с функцией-обработчиком, сохраняя соединение
Node::getEventPropertySurfaceRemove().connect(propertysurfaceremove_event_connection, propertysurfaceremove_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
propertysurfaceremove_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
propertysurfaceremove_event_connection.setEnabled(true);

// ...

// удаление подписки на событие PropertySurfaceRemove через соединение
propertysurfaceremove_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события PropertySurfaceRemove, реализованный как член класса
	void event_handler(const Ptr<Node> & node,  const Ptr<Property> & property)
	{
		Log::message("\Обработка события PropertySurfaceRemove\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventPropertySurfaceRemove().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId propertysurfaceremove_handler_id;

// подписка на событие PropertySurfaceRemove с функцией-обработчиком лямбда и сохранением ID соединения
propertysurfaceremove_handler_id = Node::getEventPropertySurfaceRemove().connect(e_connections, [](const Ptr<Node> & node,  const Ptr<Property> & property) {
		Log::message("\Обработка события PropertySurfaceRemove (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventPropertySurfaceRemove().disconnect(propertysurfaceremove_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий PropertySurfaceRemove при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventPropertySurfaceRemove().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventPropertySurfaceRemove().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &> getEventCacheNodeAdd () const

событие, срабатывающее при добавлении узла в кэш. Возникает однократно при вызове [NodeReference::create()](../../../api/library/nodes/class.nodereference_cpp.md#NodeReference_constchar) или [*World::loadNode()*](../../../api/library/engine/class.world_cpp.md#loadNode_cstr_int_Node). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CacheNodeAdd
void cachenodeadd_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события CacheNodeAdd\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections cachenodeadd_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventCacheNodeAdd().connect(cachenodeadd_event_connections, cachenodeadd_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventCacheNodeAdd().connect(cachenodeadd_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события CacheNodeAdd (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
cachenodeadd_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection cachenodeadd_event_connection;

// подписка на событие CacheNodeAdd с функцией-обработчиком, сохраняя соединение
Node::getEventCacheNodeAdd().connect(cachenodeadd_event_connection, cachenodeadd_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
cachenodeadd_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
cachenodeadd_event_connection.setEnabled(true);

// ...

// удаление подписки на событие CacheNodeAdd через соединение
cachenodeadd_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события CacheNodeAdd, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события CacheNodeAdd\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventCacheNodeAdd().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId cachenodeadd_handler_id;

// подписка на событие CacheNodeAdd с функцией-обработчиком лямбда и сохранением ID соединения
cachenodeadd_handler_id = Node::getEventCacheNodeAdd().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события CacheNodeAdd (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventCacheNodeAdd().disconnect(cachenodeadd_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CacheNodeAdd при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventCacheNodeAdd().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventCacheNodeAdd().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &> getEventNodeLoad () const

событие, срабатывающее при загрузке узла из файла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события NodeLoad
void nodeload_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события NodeLoad\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections nodeload_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventNodeLoad().connect(nodeload_event_connections, nodeload_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventNodeLoad().connect(nodeload_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeLoad (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
nodeload_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection nodeload_event_connection;

// подписка на событие NodeLoad с функцией-обработчиком, сохраняя соединение
Node::getEventNodeLoad().connect(nodeload_event_connection, nodeload_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
nodeload_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
nodeload_event_connection.setEnabled(true);

// ...

// удаление подписки на событие NodeLoad через соединение
nodeload_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события NodeLoad, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события NodeLoad\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventNodeLoad().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId nodeload_handler_id;

// подписка на событие NodeLoad с функцией-обработчиком лямбда и сохранением ID соединения
nodeload_handler_id = Node::getEventNodeLoad().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeLoad (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventNodeLoad().disconnect(nodeload_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий NodeLoad при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventNodeLoad().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventNodeLoad().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &> getEventNodeRemove () const

событие, срабатывающее при удалении узла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события NodeRemove
void noderemove_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события NodeRemove\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections noderemove_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventNodeRemove().connect(noderemove_event_connections, noderemove_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventNodeRemove().connect(noderemove_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeRemove (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
noderemove_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection noderemove_event_connection;

// подписка на событие NodeRemove с функцией-обработчиком, сохраняя соединение
Node::getEventNodeRemove().connect(noderemove_event_connection, noderemove_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
noderemove_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
noderemove_event_connection.setEnabled(true);

// ...

// удаление подписки на событие NodeRemove через соединение
noderemove_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события NodeRemove, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события NodeRemove\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventNodeRemove().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId noderemove_handler_id;

// подписка на событие NodeRemove с функцией-обработчиком лямбда и сохранением ID соединения
noderemove_handler_id = Node::getEventNodeRemove().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeRemove (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventNodeRemove().disconnect(noderemove_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий NodeRemove при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventNodeRemove().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventNodeRemove().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &> getEventNodeChangeEnabled () const

событие, срабатывающее при изменении состояния *enabled* узла. Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события NodeChangeEnabled
void nodechangeenabled_event_handler(const Ptr<Node> & node)
{
	Log::message("\Обработка события NodeChangeEnabled\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections nodechangeenabled_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventNodeChangeEnabled().connect(nodechangeenabled_event_connections, nodechangeenabled_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventNodeChangeEnabled().connect(nodechangeenabled_event_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeChangeEnabled (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
nodechangeenabled_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection nodechangeenabled_event_connection;

// подписка на событие NodeChangeEnabled с функцией-обработчиком, сохраняя соединение
Node::getEventNodeChangeEnabled().connect(nodechangeenabled_event_connection, nodechangeenabled_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
nodechangeenabled_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
nodechangeenabled_event_connection.setEnabled(true);

// ...

// удаление подписки на событие NodeChangeEnabled через соединение
nodechangeenabled_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события NodeChangeEnabled, реализованный как член класса
	void event_handler(const Ptr<Node> & node)
	{
		Log::message("\Обработка события NodeChangeEnabled\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventNodeChangeEnabled().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId nodechangeenabled_handler_id;

// подписка на событие NodeChangeEnabled с функцией-обработчиком лямбда и сохранением ID соединения
nodechangeenabled_handler_id = Node::getEventNodeChangeEnabled().connect(e_connections, [](const Ptr<Node> & node) {
		Log::message("\Обработка события NodeChangeEnabled (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventNodeChangeEnabled().disconnect(nodechangeenabled_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий NodeChangeEnabled при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventNodeChangeEnabled().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventNodeChangeEnabled().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, const Ptr < Node > &> getEventNodeClone () const

событие, срабатывающее при копировании узла через [Node::clone()](../../../api/library/nodes/class.node_cpp.md#clone_Node). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **node_clone**, const Ptr<Node> & **node_original**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события NodeClone
void nodeclone_event_handler(const Ptr<Node> & node_clone,  const Ptr<Node> & node_original)
{
	Log::message("\Обработка события NodeClone\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections nodeclone_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventNodeClone().connect(nodeclone_event_connections, nodeclone_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventNodeClone().connect(nodeclone_event_connections, [](const Ptr<Node> & node_clone,  const Ptr<Node> & node_original) {
		Log::message("\Обработка события NodeClone (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
nodeclone_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection nodeclone_event_connection;

// подписка на событие NodeClone с функцией-обработчиком, сохраняя соединение
Node::getEventNodeClone().connect(nodeclone_event_connection, nodeclone_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
nodeclone_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
nodeclone_event_connection.setEnabled(true);

// ...

// удаление подписки на событие NodeClone через соединение
nodeclone_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события NodeClone, реализованный как член класса
	void event_handler(const Ptr<Node> & node_clone,  const Ptr<Node> & node_original)
	{
		Log::message("\Обработка события NodeClone\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventNodeClone().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId nodeclone_handler_id;

// подписка на событие NodeClone с функцией-обработчиком лямбда и сохранением ID соединения
nodeclone_handler_id = Node::getEventNodeClone().connect(e_connections, [](const Ptr<Node> & node_clone,  const Ptr<Node> & node_original) {
		Log::message("\Обработка события NodeClone (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventNodeClone().disconnect(nodeclone_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий NodeClone при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventNodeClone().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventNodeClone().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<const Ptr < Node > &, const Ptr < Node > &> getEventNodeSwap () const

событие, срабатывающее при обмене узлами через [Node::swap()](../../../api/library/nodes/class.node_cpp.md#swap_Node_void). Вы можете подписаться на события через *connect()* и отписаться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Дополнительную информацию см. в статье [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Node> & **first_node**, const Ptr<Node> & **second_node**)*
<details>
<summary>Смотреть пример | Закрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события NodeSwap
void nodeswap_event_handler(const Ptr<Node> & first_node,  const Ptr<Node> & second_node)
{
	Log::message("\Обработка события NodeSwap\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который позже можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnections
EventConnections nodeswap_event_connections;

// привязка к этому экземпляру при подписке на событие (можно привязывать подписки на разные события)
Node::getEventNodeSwap().connect(nodeswap_event_connections, nodeswap_event_handler);

// другие подписки также привязаны к этому экземпляру EventConnections
// (например, можно подписываться с использованием лямбд)
Node::getEventNodeSwap().connect(nodeswap_event_connections, [](const Ptr<Node> & first_node,  const Ptr<Node> & second_node) {
		Log::message("\Обработка события NodeSwap (лямбда)\n");
	}
);

// ...

// позже все эти привязанные подписки можно удалить одной строкой
nodeswap_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создание экземпляра класса EventConnection
EventConnection nodeswap_event_connection;

// подписка на событие NodeSwap с функцией-обработчиком, сохраняя соединение
Node::getEventNodeSwap().connect(nodeswap_event_connection, nodeswap_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
nodeswap_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
nodeswap_event_connection.setEnabled(true);

// ...

// удаление подписки на событие NodeSwap через соединение
nodeswap_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Экземпляр EventConnection/EventConnections можно добавить как член класса,
//  обрабатывающего событие. В этом случае все привязанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события NodeSwap, реализованный как член класса
	void event_handler(const Ptr<Node> & first_node,  const Ptr<Node> & second_node)
	{
		Log::message("\Обработка события NodeSwap\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указание экземпляра класса, если метод-обработчик принадлежит какому-либо классу
Node::getEventNodeSwap().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется со всеми его подписками автоматически
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением определённого ID соединения
//   и последующей отпиской по этому ID
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определение конкретного ID соединения для последующей отписки
EventConnectionId nodeswap_handler_id;

// подписка на событие NodeSwap с функцией-обработчиком лямбда и сохранением ID соединения
nodeswap_handler_id = Node::getEventNodeSwap().connect(e_connections, [](const Ptr<Node> & first_node,  const Ptr<Node> & second_node) {
		Log::message("\Обработка события NodeSwap (лямбда)\n");
	}
);

// удаление подписки позже с использованием ID
Node::getEventNodeSwap().disconnect(nodeswap_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий NodeSwap при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Node::getEventNodeSwap().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Node::getEventNodeSwap().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## bool isCache () const

Возвращает текущее значение, указывающее, хранится ли узел или любой из его родительских узлов в кэше.
### Возвращаемое значение

**true**, если узел в кэше включён; иначе **false**.
## const char * getSrcFilePath () const

Возвращает текущий путь к источнику узла. Например, относительный путь к файлу `*.world` с описанием этого узла, или идентификатор исходного файла `*.node` в формате `guid://...`
### Возвращаемое значение

Текущий путь к источнику узла.
## String getHierarchyPath () const

Возвращает текущую [nodes hierarchy](../../../principles/world_structure/index.md#nodes_hierarchy). Отображает имя узла и имена всех его родительских узлов, как указано в окне *World Hierarchy*.
### Возвращаемое значение

Текущее имя узла и имена всех его родительских узлов.
## String getInfo () const

Возвращает текущую информацию о заданном узле: тип, имя, ID, путь к файлу, иерархию.
### Возвращаемое значение

Текущая информация об узле.
---

## Ptr < Node > getAncestor ( int num ) const

Возвращает предка узла по его номеру.
### Аргументы

- *int* **num** - ID предка.

### Возвращаемое значение

Узел-предок.
## Ptr < Node > getChild ( int num ) const

Возвращает дочерний узел по его номеру.
### Аргументы

- *int* **num** - ID дочернего узла.

### Возвращаемое значение

Дочерний узел.
## bool isChild ( const Ptr < Node > & n ) const

Проверяет, является ли заданный узел дочерним для узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Проверяемый узел.

### Возвращаемое значение

true, если заданный узел является дочерним; иначе false.
## void setChildIndex ( const Ptr < Node > & n , int index )

Задаёт индекс для заданного дочернего узла узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Дочерний узел.
- *int* **index** - Индекс узла.

## int getChildIndex ( const Ptr < Node > & n )

Возвращает индекс заданного дочернего узла узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Дочерний узел.

### Возвращаемое значение

Индекс узла.
## void setData ( const char * name , const char * data )

Задаёт пользовательские данные, связанные с узлом.
- Если узел был загружен из файла `*.node`, данные сохраняются напрямую в тег data этого файла.
- Если узел загружен из файла `*.world`, данные сохраняются в тег data узла в файле `*.world`.
- Если узел загружен из файла `*.world` как NodeReference, данные будут сохранены в тег data NodeReference в файле `*.world`.


### Аргументы

- *const char ** **name** - Строка, содержащая ключ, идентифицирующий пользовательские данные для хранения в файле `*.node`. > **Notice:** Ключ "editor_data" зарезервирован для UnigineEditor.
- *const char ** **data** - Новые пользовательские данные. Данные могут содержать строку в формате XML.

## const char * getData ( const char * name )

Возвращает пользовательские данные, связанные с узлом.
- Если узел был загружен из файла `*.node`, возвращаются данные из тега data этого файла.
- Если узел загружен из файла `*.world`, возвращаются данные из тега data узла в файле `*.world`.
- Если узел загружен из файла `*.world` как NodeReference, возвращаются данные из тега data NodeReference в файле `*.world`.


### Аргументы

- *const char ** **name** - Строка, содержащая ключ, идентифицирующий пользовательские данные, хранящиеся в файле `*.node`. > **Notice:** Ключ "editor_data" зарезервирован для UnigineEditor.

### Возвращаемое значение

Пользовательские строковые данные. Данные могут быть строкой в формате XML.
## void updateEnabled ( )

Обновляет внутреннее состояние узла в соответствии с текущим состоянием "*enabled*".
## bool isEnabledSelf ( ) const

Возвращает значение, указывающее, включён ли узел.
### Возвращаемое значение

true, если узел включён; иначе false.
## void getHierarchy ( Vector < Ptr < Node >> & OUT_hierarchy )

Получает всю иерархию узла и помещает её в буфер иерархии.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_hierarchy** - Буфер иерархии. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## Ptr < Node > getNode ( int id )

Возвращает указатель на узел.
### Аргументы

- *int* **id** - Идентификатор узла.

### Возвращаемое значение

Указатель на узел.
## bool isNode ( const Ptr < Node > & node )

Проверяет указатель на узел.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Указатель на узел.

### Возвращаемое значение

true, если узел допустим; иначе false.
## bool isNode ( int id )

Проверяет указатель на узел.
### Аргументы

- *int* **id** - Указатель на узел.

### Возвращаемое значение

true, если узел допустим; иначе false.
## int addProperty ( const char * name )

Наследует новое свойство от свойства с заданным именем и добавляет его в список свойств, связанных с узлом. Унаследованное свойство будет внутренним, такие свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *const char ** **name** - Имя добавляемого свойства.

### Возвращаемое значение

Индекс нового свойства узла, если оно было успешно добавлено; иначе -1.
## int addProperty ( const UGUID & guid )

Наследует новое свойство от свойства с заданным GUID и добавляет его в список свойств, связанных с узлом. Унаследованное свойство будет внутренним, такие свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) добавляемого свойства.

### Возвращаемое значение

Индекс нового свойства узла, если оно было успешно добавлено; иначе -1.
## int addProperty ( const Ptr < Property > & property )

Наследует новое свойство от указанного и добавляет его в список свойств, связанных с узлом. Унаследованное свойство будет внутренним, такие свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Добавляемое свойство.

### Возвращаемое значение

Индекс нового свойства узла, если оно было успешно добавлено; иначе -1.
## bool insertProperty ( int num , const char * name )

Вставляет свойство с указанным именем в указанную позицию.
### Аргументы

- *int* **num** - Позиция, в которую нужно вставить новое свойство, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *const char ** **name** - Имя вставляемого свойства.

### Возвращаемое значение

true, если свойство с указанным именем успешно вставлено в указанную позицию; иначе false.
## bool insertProperty ( int num , const UGUID & guid )

Вставляет свойство с указанным GUID в указанную позицию.
### Аргументы

- *int* **num** - Позиция, в которую нужно вставить новое свойство, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) вставляемого свойства.

### Возвращаемое значение

true, если свойство с указанным GUID успешно вставлено в указанную позицию; иначе false.
## bool insertProperty ( int num , const Ptr < Property > & property )

Вставляет указанное свойство в указанную позицию.
### Аргументы

- *int* **num** - Позиция, в которую нужно вставить новое свойство, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Добавляемое свойство.

### Возвращаемое значение

true, если указанное свойство успешно вставлено в указанную позицию; иначе false.
## bool insertProperty ( int num , const UGUID & guid , const UGUID & new_guid )

### Аргументы

- *int* **num**
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid**
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_guid**

## bool insertProperty ( int num , const Ptr < Property > & property , const UGUID & new_guid )

### Аргументы

- *int* **num**
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property**
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_guid**

## bool setProperty ( const char * name )

Обновляет первое свойство узла (с индексом 0) в списке свойств, связанных с узлом. Будет задано новое внутреннее свойство, унаследованное от свойства с указанным именем. Такие внутренние свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *const char ** **name** - Имя задаваемого свойства.

### Возвращаемое значение

true, если свойство узла успешно обновлено; иначе false.
## bool setProperty ( const UGUID & guid )

Обновляет первое свойство узла (с индексом 0) в списке свойств, связанных с узлом. Будет задано новое внутреннее свойство, унаследованное от свойства с указанным GUID. Такие внутренние свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) задаваемого свойства.

### Возвращаемое значение

true, если свойство узла успешно обновлено; иначе false.
## bool setProperty ( const Ptr < Property > & property )

Обновляет первое свойство узла (с индексом 0) в списке свойств, связанных с узлом. Будет задано новое внутреннее свойство, унаследованное от указанного. Такие внутренние свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Задаваемое свойство.

### Возвращаемое значение

true, если свойство узла успешно обновлено; иначе false.
## bool setProperty ( int num , const char * name )

Обновляет свойство узла с указанным номером. Будет задано новое внутреннее свойство, унаследованное от свойства с указанным именем. Такие внутренние свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *const char ** **name** - Имя задаваемого свойства.

### Возвращаемое значение

true, если указанное свойство узла успешно обновлено; иначе false.
## bool setProperty ( int num , const UGUID & guid )

Обновляет свойство узла с указанным номером. Будет задано новое внутреннее свойство, унаследованное от свойства с указанным GUID. Такие внутренние свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) задаваемого свойства.

### Возвращаемое значение

true, если указанное свойство узла успешно обновлено; иначе false.
## bool setProperty ( int num , const Ptr < Property > & property )

Обновляет свойство узла с указанным номером. Будет задано новое внутреннее свойство, унаследованное от указанного. Такие внутренние свойства сохраняются в файле `*.world` или `*.node`.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Задаваемое свойство.

### Возвращаемое значение

true, если указанное свойство узла успешно обновлено; иначе false.
## bool setProperty ( int num , const UGUID & guid , const UGUID & new_guid )

### Аргументы

- *int* **num**
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid**
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_guid**

## bool setProperty ( int num , const Ptr < Property > & property , const UGUID & new_guid )

### Аргументы

- *int* **num**
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property**
- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **new_guid**

## void setPropertyEnabled ( int num , bool enable )

Включает или отключает свойство узла с указанным номером.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *bool* **enable** - true, чтобы включить указанное свойство узла, false - чтобы отключить.

## bool isPropertyEnabled ( int num ) const

Возвращает значение, указывающее, включено ли свойство узла с указанным номером.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).

### Возвращаемое значение

true, если указанное свойство включено; иначе false.
## void swapProperty ( int from_num , int to_num )

Меняет местами два свойства с указанными номерами в списке свойств, связанных с узлом.
> **Notice:** Порядок свойств в списке определяет последовательность выполнения логики соответствующих [components](../../../principles/component_system/index.md) (если есть).


### Аргументы

- *int* **from_num** - Номер первого свойства узла для обмена, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).
- *int* **to_num** - Номер второго свойства узла для обмена, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).

## void removeProperty ( int num )

Удаляет свойство узла с указанным номером.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).

## void removeProperty ( const char * name )

Удаляет свойство узла с указанным именем.
> **Notice:** Если с узлом связано несколько свойств с одинаковым именем, будет удалено только первое.


### Аргументы

- *const char ** **name** - Имя удаляемого свойства узла.

## void removeProperty ( const UGUID & guid )

Удаляет свойство узла, GUID или родительский GUID которого равен указанному.
> **Notice:** Если с узлом связано несколько таких свойств, будет удалено только первое.


### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) удаляемого свойства (или GUID его родителя).

## void removeProperty ( const Ptr < Property > & property )

Удаляет указанное свойство узла или свойство узла, унаследованное от него.
> **Notice:** Если с узлом связано несколько таких свойств, будет удалено только первое.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Удаляемое свойство узла.

## void clearProperties ( )

Очищает список свойств, связанных с узлом.
## Ptr < Property > getProperty ( int num ) const

Возвращает свойство узла с указанным номером, если оно существует.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).

### Возвращаемое значение

Умный указатель на свойство узла, если существует; иначе NULL.
## const char * getPropertyName ( int num ) const

Возвращает имя свойства узла с указанным номером.
### Аргументы

- *int* **num** - Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int).

### Возвращаемое значение

Имя свойства, если существует; иначе NULL.
## int findProperty ( const char * name ) const

Ищет свойство с указанным именем среди назначенных узлу.
### Аргументы

- *const char ** **name** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) искомого свойства узла.

### Возвращаемое значение

Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int), если такое свойство существует; иначе -1.
## int findProperty ( const UGUID & guid ) const

Ищет свойство с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md) среди назначенных узлу.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - [GUID](../../../api/library/filesystem/class.uguid_cpp.md) искомого свойства узла.

### Возвращаемое значение

Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int), если такое свойство существует; иначе -1.
## int findProperty ( const Ptr < Property > & property ) const

Ищет указанное свойство среди назначенных узлу.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **property** - Искомое свойство узла.

### Возвращаемое значение

Номер свойства узла, в диапазоне от 0 до [total number of node properties](#getNumProperties_int), если такое свойство существует; иначе -1.
## bool hasQueryForce ( ) const

Возвращает значение, указывающее, принудительно ли включена движком для узла опция *[Culled By Occlusion Query](../../../editor2/node_parameters/transformation_common/index.md#query)*.
### Возвращаемое значение

true, если опция *[Culled By Occlusion Query](../../../editor2/node_parameters/transformation_common/index.md#query)* принудительно включена движком для узла; иначе false.
## void setRotation ( const Math:: quat & rot , bool identity = 0 )

Задаёт вращение узла.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **rot** - Кватернион, представляющий вращение узла в локальном пространстве.
- *bool* **identity** - Флаг, указывающий, следует ли игнорировать или учитывать масштаб узла: > **Notice:** - Рекомендуется устанавливать этот флаг для всех немасштабированных узлов для повышения производительности и точности. > - **По возможности следует избегать масштабирования узлов**, так как оно требует дополнительных вычислений и может привести к накоплению ошибок.

  - false - масштаб узла учитывается. В этом случае выполняются дополнительные вычисления для извлечения текущего масштаба узла и его применения при построении итоговой матрицы трансформации. Эти дополнительные операции снижают производительность и могут привести к накоплению ошибок.
  - true - масштаб узла игнорируется (предполагается равным **1** по всем осям). Таким образом, количество вычислений, выполняемых для каждого вращения, уменьшается, а накопление ошибок минимально.

## Math:: quat getRotation ( ) const

Возвращает вращение узла.
### Возвращаемое значение

Кватернион, представляющий вращение узла в локальном пространстве.
## void setWorldRotation ( const Math:: quat & rot , bool identity = 0 )

Задаёт вращение узла в мировом пространстве.
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **rot** - Вращение узла в мировом пространстве.
- *bool* **identity** - Флаг, указывающий, следует ли игнорировать или учитывать масштаб узла: > **Notice:** - Рекомендуется устанавливать этот флаг для всех немасштабированных узлов для повышения производительности и точности. > - **По возможности следует избегать масштабирования узлов**, так как оно требует дополнительных вычислений и может привести к накоплению ошибок.

  - false - масштаб узла учитывается. В этом случае выполняются дополнительные вычисления для извлечения текущего масштаба узла и его применения при построении итоговой матрицы трансформации. Эти дополнительные операции снижают производительность и могут привести к накоплению ошибок.
  - true - масштаб узла игнорируется (предполагается равным **1** по всем осям). Таким образом, количество вычислений, выполняемых для каждого вращения, уменьшается, а накопление ошибок минимально.

## Math:: quat getWorldRotation ( ) const

Возвращает вращение узла в мировом пространстве.
### Возвращаемое значение

Вращение узла в мировом пространстве.
## void setTransformWithoutChildren ( const Math:: Mat4 & transform )

Задаёт матрицу трансформации узла в локальных координатах (трансформации всех дочерних узлов не затрагиваются). Этот метод можно использовать для изменения трансформации узла относительно его дочерних узлов.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Новая матрица трансформации, задаваемая для узла (локальные координаты).

## Node::TYPE getTypeID ( const char * type )

Возвращает ID типа узла с заданным именем.
### Аргументы

- *const char ** **type** - Имя типа узла.

### Возвращаемое значение

ID типа узла, если такой тип существует; иначе -1.
## const char * getTypeName ( Node::TYPE type )

Возвращает имя типа узла с заданным ID.
### Аргументы

- *[Node::TYPE](../../../api/library/nodes/class.node_cpp.md#TYPE)* **type** - ID типа узла.

### Возвращаемое значение

Имя типа узла.
## void setVariable ( const char * name , const Variable & v )

Задаёт значение переменной с заданным именем. Если такая переменная не существует, она будет добавлена с указанным значением.
```cpp
NodeDummyPtr container;
if(container->hasVariable("key1")) {
	container->setVariable("key1", Variable(42));
}
Variable value = container->getVariable("key1");
container->removeVariable("key1");

```


### Аргументы

- *const char ** **name** - Имя переменной.
- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение переменной.

## Variable getVariable ( const char * name ) const

Возвращает переменную с заданным именем.
```cpp
NodeDummyPtr container;
if(container->hasVariable("key1")) {
	container->setVariable("key1", Variable(42));
}
Variable value = container->getVariable("key1");
container->removeVariable("key1");

```


### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

Переменная, если она существует; иначе переменная со значением 0.
## void setWorldParent ( const Ptr < Node > & n )

Задаёт нового родителя узла. Трансформации текущего узла будут выполняться в мировых координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Новый родительский узел или NULL (0).

## void setWorldTransformWithoutChildren ( const Math:: Mat4 & transform )

Задаёт матрицу трансформации узла в мировых координатах (трансформации всех дочерних узлов не затрагиваются). Этот метод можно использовать для изменения трансформации узла относительно его дочерних узлов.
### Аргументы

- *const  Math::[Mat4](../../../api/library/math/class.mat4_cpp.md) &* **transform** - Новая матрица трансформации, задаваемая для узла (мировые координаты).

## Math:: vec3 getBodyWorldVelocity ( const Math:: Vec3 & point ) const

Возвращает линейную скорость точки физического тела узла в мировом пространстве.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **point**

### Возвращаемое значение

Линейная скорость в мировом пространстве.
## void addChild ( const Ptr < Node > & n )

Добавляет дочерний узел к узлу. Трансформации нового дочернего узла будут выполняться в координатах родителя.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Новый дочерний узел.

## void addWorldChild ( const Ptr < Node > & n )

Добавляет дочерний узел к узлу. Трансформации нового дочернего узла будут выполняться в мировых координатах.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Новый дочерний узел.

## Ptr < Node > clone ( ) const

Клонирует узел.
### Возвращаемое значение

Клонированный узел.
## int findAncestor ( int type ) const

Возвращает ID предка узла заданного типа.
### Аргументы

- *int* **type** - Идентификатор типа предка. Одна из предопределённых переменных [*NODE_**](#NODE_DUMMY).

### Возвращаемое значение

ID предка, если он существует; иначе -1.
## int findAncestor ( const char * name ) const

Возвращает ID предка узла с заданным именем.
### Аргументы

- *const char ** **name** - Имя предка.

### Возвращаемое значение

ID предка, если он существует; иначе -1.
## int findChild ( const char * name ) const

Ищет дочерний узел с заданным именем среди дочерних узлов узла.
### Аргументы

- *const char ** **name** - Имя дочернего узла.

### Возвращаемое значение

Номер дочернего узла, если найден; иначе -1.
## Ptr < Node > findNode ( const char * name , int recursive = 0 ) const

Ищет узел с заданным именем среди дочерних узлов узла.
### Аргументы

- *const char ** **name** - Имя искомого дочернего узла.
- *int* **recursive** - **1**, если поиск рекурсивный (то есть выполняется для дочерних узлов дочерних узлов); иначе **0**.

### Возвращаемое значение

Дочерний узел, если найден; иначе NULL.
## void findNodes ( const char * name , Vector < Ptr < Node >> & OUT_nodes , int recursive = 0 ) const

Ищет узел с заданным именем среди дочерних узлов узла и помещает их в указанный выходной буфер *nodes*.
### Аргументы

- *const char ** **name** - Имя искомого узла.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Выходной буфер, в который будут помещены все найденные узлы с указанным именем. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
- *int* **recursive** - **1**, если поиск рекурсивный (то есть выполняется для дочерних узлов дочерних узлов); иначе **0**.

## int hasVariable ( const char * name )

Возвращает значение, указывающее, есть ли у узла параметр-переменная с заданным именем.
```cpp
NodeDummyPtr container;
if(container->hasVariable("key1")) {
	container->setVariable("key1", Variable(42));
}
Variable value = container->getVariable("key1");
container->removeVariable("key1");

```


### Аргументы

- *const char ** **name** - Имя переменной.

### Возвращаемое значение

**1**, если у узла есть параметр-переменная с заданным именем; иначе **0**.
## int hasVariable ( )

Возвращает значение, указывающее, есть ли у узла единственный неименованный параметр-переменная.
### Возвращаемое значение

1, если у узла есть единственный неименованный параметр-переменная; иначе 0.
## bool loadWorld ( const Ptr < Xml > & xml )

Загружает состояние узла из Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

true, если состояние узла успешно загружено; иначе false.
## void removeChild ( const Ptr < Node > & n )

Удаляет дочерний узел (добавленный методом *[addChild()](#addChild_Node_void)*) из списка дочерних узлов.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Удаляемый дочерний узел.

## void removeVariable ( const char * name )

Удаляет параметр-переменную с заданным именем.
```cpp
NodeDummyPtr container;
if(container->hasVariable("key1")) {
	container->setVariable("key1", Variable(42));
}
Variable value = container->getVariable("key1");
container->removeVariable("key1");

```


### Аргументы

- *const char ** **name** - Имя параметра-переменной.

### Возвращаемое значение

## void removeWorldChild ( const Ptr < Node > & n )

Удаляет дочерний узел (добавленный методом *[addWorldChild()](#addWorldChild_Node_void)*) из списка дочерних узлов.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Удаляемый дочерний узел.

## void renderVisualizer ( )

Отображает ограничивающий параллелепипед / сферу объекта.
> **Notice:** Необходимо включить визуализатор движка консольной командой `show_visualizer 1`.


## bool saveState ( const Ptr < Stream > & stream ) const

Сохраняет состояние узла в бинарный поток.
**Пример** использования методов saveState() и [restoreState()](#restoreState_Stream_int):


```cpp
// инициализация узла и задание его состояния
NodeDummyPtr node = NodeDummy::create();
node->setPosition(Vec3(1, 1, 0));

// сохранение состояния
BlobPtr blob_state = Blob::create();
node->saveState(blob_state);

// изменение состояния
node->setPosition(Vec3(0, 0, 0));

// восстановление состояния
blob_state->seekSet(0);		// возврат каретки в начало blob
node->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.

### Возвращаемое значение

true, если состояние узла успешно сохранено; иначе false.
## bool restoreState ( const Ptr < Stream > & stream )

Восстанавливает состояние узла из бинарного потока.
**Пример** использования методов [saveState()](#saveState_Stream_int) и restoreState():


```cpp
// инициализация узла и задание его состояния
NodeDummyPtr node = NodeDummy::create();
node->setPosition(Vec3(1, 1, 0));

// сохранение состояния
BlobPtr blob_state = Blob::create();
node->saveState(blob_state);

// изменение состояния
node->setPosition(Vec3(0, 0, 0));

// восстановление состояния
blob_state->seekSet(0);		// возврат каретки в начало blob
node->restoreState(blob_state);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Умный указатель на поток.

### Возвращаемое значение

true, если состояние узла успешно восстановлено; иначе false.
## bool saveWorld ( const Ptr < Xml > & xml ) const

Сохраняет узел в Xml.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Xml](../../../api/library/common/class.xml_cpp.md)> &* **xml** - Умный указатель на Xml.

### Возвращаемое значение

true, если узел успешно сохранён; иначе false.
## void swap ( const Ptr < Node > & n ) const

Меняет местами два узла.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **n** - Узел для обмена.

## Math:: vec3 toLocal ( const Math:: Vec3 & p ) const

Преобразует заданный вектор из мирового пространства в локальное пространство узла.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **p** - Вектор в мировом пространстве.

### Возвращаемое значение

Вектор в локальном пространстве.
## Math:: Vec3 toWorld ( const Math:: vec3 & p ) const

Преобразует заданный вектор из локального пространства в мировое пространство.
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **p** - Вектор в локальном пространстве.

### Возвращаемое значение

Вектор в мировом пространстве.
## void translate ( const Math:: Vec3 & t )

Перемещает узел относительно его локальной системы координат: трансформация родительского узла не учитывается.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **t** - Вектор перемещения.

## void translate ( Math::Scalar x , Math::Scalar y , Math::Scalar z )

Перемещает узел относительно его локальной системы координат: трансформация родительского узла не учитывается.
### Аргументы

- *Math::Scalar* **x** - Перемещение узла вдоль оси X, в единицах.
- *Math::Scalar* **y** - Перемещение узла вдоль оси Y, в единицах.
- *Math::Scalar* **z** - Перемещение узла вдоль оси Z, в единицах.

## void worldTranslate ( const Math:: Vec3 & t )

Перемещает узел в мировом пространстве с использованием указанного вектора.
### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **t** - Вектор перемещения.

## void worldTranslate ( Math::Scalar x , Math::Scalar y , Math::Scalar z )

Перемещает узел в мировом пространстве с использованием значений, заданных для соответствующих осей.
### Аргументы

- *Math::Scalar* **x** - Перемещение узла вдоль оси X, в единицах.
- *Math::Scalar* **y** - Перемещение узла вдоль оси Y, в единицах.
- *Math::Scalar* **z** - Перемещение узла вдоль оси Z, в единицах.

## void worldLookAt ( const Math:: Vec3 & target , const Math:: vec3 & up )

Переориентирует узел, чтобы он "смотрел" на целевую точку, и задаёт указанный вектор вверх:
- Если узел связан с [Player-related](#isPlayer_int), он будет "смотреть" на целевую точку вдоль отрицательной оси Z. Ось Y будет ориентирована вдоль указанного вектора вверх.
- Другие узлы будут "смотреть" на целевую точку вдоль оси Y. Ось Z будет ориентирована вдоль указанного вектора вверх.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **target** - Координаты целевой точки в мировом пространстве.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **up** - Вектор вверх узла в мировом пространстве. По умолчанию вектор вверх ориентирован вдоль оси Z.

## void worldLookAt ( const Math:: Vec3 & target )

Переориентирует узел, чтобы он "смотрел" на целевую точку. Вектор вверх ориентирован вдоль оси Z.
- Если узел связан с [Player-related](#isPlayer_int), он будет "смотреть" на целевую точку вдоль отрицательной оси Z. Ось Y будет ориентирована вдоль мировой оси Z.
- Другие узлы будут "смотреть" на целевую точку вдоль оси Y.


### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **target** - Координаты целевой точки в мировом пространстве.

## void rotate ( const Math:: quat & r )

Вращает узел относительно его локальной системы координат: трансформация родительского узла не учитывается. Вращение определяется указанным [quaternion](../../../api/library/math/class.quat_cpp.md).
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **r** - Кватернион вращения.

## void rotate ( const Math:: vec3 & angles )

Вращает узел в локальном пространстве. Вращение определяется углами Эйлера, переданными в виде вектора [vec3](../../../api/library/math/class.vec3_cpp.md).
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **angles**

## void rotate ( float angle_x , float angle_y , float angle_z )

Вращает узел в мировом пространстве согласно заданным углам Эйлера.
### Аргументы

- *float* **angle_x** - Угол тангажа (pitch), в градусах.
- *float* **angle_y** - Угол крена (roll), в градусах.
- *float* **angle_z** - Угол рыскания (yaw), в градусах.

## void worldRotate ( const Math:: quat & r )

Вращает узел в мировом пространстве. Вращение определяется указанным [quaternion](../../../api/library/math/class.quat_cpp.md).
### Аргументы

- *const  Math::[quat](../../../api/library/math/class.quat_cpp.md) &* **r** - Кватернион вращения.

## void worldRotate ( const Math:: vec3 & angles )

Вращает узел в мировом пространстве. Вращение определяется углами Эйлера, переданными в виде вектора [vec3](../../../api/library/math/class.vec3_cpp.md).
### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **angles** - Вектор, содержащий углы Эйлера (Pitch, Yaw, Roll).

## void worldRotate ( float angle_x , float angle_y , float angle_z )

Вращает узел в мировом пространстве согласно заданным углам Эйлера.
### Аргументы

- *float* **angle_x** - Угол тангажа (pitch), в градусах.
- *float* **angle_y** - Угол крена (roll), в градусах.
- *float* **angle_z** - Угол рыскания (yaw), в градусах.

## void setDirection ( const Math:: vec3 & dir , const Math:: vec3 & up , MathLib::AXIS axis = AXIS_NZ )

Обновляет вектор направления узла и переориентирует узел: указанная ось узла становится ориентированной вдоль указанного вектора в локальных координатах. Например, после выполнения приведённого ниже кода ось X узла окажется направлена вдоль оси Y в локальных координатах.
```cpp
// получение узла
NodePtr node = World::getNodeByName("material_ball");
// задание направления оси X вдоль оси Y в локальных координатах
node->setDirection(vec3(0.0f,1.0f,0.0f),vec3(0.0f,0.0f,1.0f),Math::AXIS_X);

```


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **dir** - Новый вектор направления в локальных координатах. Вектор направления всегда имеет единичную длину.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **up** - Новый вектор вверх в локальных координатах. Если этот аргумент пропущен, будет использована ось Z (в локальных координатах). Обратите внимание, что указанный вектор вверх является лишь подсказкой: вектор вверх узла указывает в направлении, подсказанном указанным вектором вверх. Вектор вверх узла совпадает с указанным вектором вверх (*up*) только если он перпендикулярен указанному вектору направления (*dir*).
- *MathLib::AXIS* **axis** - Ось, вдоль которой должен быть направлен вектор направления. По умолчанию - отрицательная ось Z.

## Math:: vec3 getDirection ( MathLib::AXIS axis = AXIS_NZ ) const

Возвращает нормализованный вектор направления, указывающий вдоль заданной оси узла в локальных координатах (то есть относительно родителя узла). По умолчанию возвращается вектор направления, указывающий вдоль отрицательной оси Z узла (в локальных координатах). Вектор направления всегда имеет единичную длину.
```cpp
node->getDirection(node->isPlayer() ? Math::AXIS_NZ : Math::AXIS_Y); // вектор направления вперёд
node->getDirection(node->isPlayer() ? Math::AXIS_Z : Math::AXIS_NY); // вектор направления назад
node->getDirection(node->isPlayer() ? Math::AXIS_Y : Math::AXIS_Z); // вектор направления вверх
node->getDirection(node->isPlayer() ? Math::AXIS_NY : Math::AXIS_NZ); // вектор направления вниз
node->getDirection(Math::AXIS_X); // вектор направления вправо
node->getDirection(Math::AXIS_NX); // вектор направления влево

```


### Аргументы

- *MathLib::AXIS* **axis** - Ось, вдоль которой указывает вектор направления. По умолчанию - отрицательная ось Z.

### Возвращаемое значение

Вектор направления в локальных координатах.
## void setWorldDirection ( const Math:: vec3 & dir , const Math:: vec3 & up , MathLib::AXIS axis = AXIS_NZ )

Обновляет вектор направления узла и переориентирует узел: указанная ось узла становится ориентированной вдоль указанного вектора в мировых координатах. Например, после выполнения приведённого ниже кода ось X узла окажется направлена вдоль оси Y в мировых координатах:
```cpp
// получение узла
NodePtr node = World::getNodeByName("material_ball");
// задание направления оси X вдоль оси Y в мировых координатах
node->setWorldDirection(vec3(0.0f,1.0f,0.0f),vec3(0.0f,0.0f,1.0f), Math::AXIS_X);

```


### Аргументы

- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **dir** - Новый вектор направления в мировых координатах. Вектор направления всегда имеет единичную длину.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **up** - Новый вектор вверх в мировых координатах. Если этот аргумент пропущен, будет использована ось Z (в локальных координатах). Обратите внимание, что указанный вектор вверх является лишь подсказкой: вектор вверх узла указывает в направлении, подсказанном указанным вектором вверх. Вектор вверх узла совпадает с указанным вектором вверх (*up*) только если он перпендикулярен указанному вектору направления (*dir*).
- *MathLib::AXIS* **axis** - Ось, вдоль которой должен быть направлен вектор направления. По умолчанию - отрицательная ось Z.

## Math:: vec3 getWorldDirection ( MathLib::AXIS axis = AXIS_NZ ) const

Возвращает нормализованный вектор направления, указывающий вдоль заданной оси узла в мировых координатах. По умолчанию возвращается вектор направления, указывающий вдоль отрицательной оси Z узла. Вектор направления всегда имеет единичную длину.
```cpp
node->getWorldDirection(node->isPlayer() ? Math::AXIS_NZ : Math::AXIS_Y); // вектор направления вперёд
node->getWorldDirection(node->isPlayer() ? Math::AXIS_Z : Math::AXIS_NY); // вектор направления назад
node->getWorldDirection(node->isPlayer() ? Math::AXIS_Y : Math::AXIS_Z); // вектор направления вверх
node->getWorldDirection(node->isPlayer() ? Math::AXIS_NY : Math::AXIS_NZ); // вектор направления вниз
node->getWorldDirection(Math::AXIS_X); // вектор направления вправо
node->getWorldDirection(Math::AXIS_NX); // вектор направления влево

```


### Аргументы

- *MathLib::AXIS* **axis** - Ось, вдоль которой указывает вектор направления. По умолчанию - отрицательная ось Z.

### Возвращаемое значение

Вектор направления в мировых координатах.
## Ptr < Node > getCloneNode ( const Ptr < Node > & original_node )

Возвращает узел, клонированный из указанного исходного узла.
> **Notice:** Этот метод предназначен только для использования внутри [node clone callback](#getEventNodeClone_Event).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **original_node** - Исходный узел, который был клонирован.

### Возвращаемое значение

Клон указанного исходного узла, если он существует; иначе сам исходный узел.
## Ptr < Property > getCloneProperty ( const Ptr < Property > & original_property )

Возвращает свойство узла, клонированное из указанного исходного свойства.
> **Notice:** Этот метод предназначен только для использования внутри [node clone callback](#getEventNodeClone_Event).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Property](../../../api/library/common/class.property_cpp.md)> &* **original_property** - Исходное свойство узла, которое было клонировано.

### Возвращаемое значение

Клон указанного исходного свойства узла, если он существует; иначе само исходное свойство узла.
## void setSaveToWorldEnabledRecursive ( bool enable )

Задаёт значение, указывающее, включено ли сохранение в файл `*.world` для узла и всех его дочерних узлов (если есть).
### Аргументы

- *bool* **enable** - true, чтобы включить сохранение в файл `*.world` для узла и всех его дочерних узлов (если есть); 0, чтобы отключить.

## void setShowInEditorEnabledRecursive ( bool enable )

Задаёт значение, указывающее, включено ли отображение в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md) для узла и всех его дочерних узлов (если есть).
### Аргументы

- *bool* **enable** - true, чтобы включить отображение в окне *World Hierarchy* [UnigineEditor](../../../editor2/index.md) для узла и всех его дочерних узлов (если есть); 0, чтобы отключить.

## Node::LIFETIME getLifetimeSelf ( ) const

Возвращает тип управления временем жизни, заданный для самого узла.
> **Notice:** Время жизни каждого узла в иерархии определяется его корнем (либо [parent](#getParent_Node), либо [possessor](#getPossessor_Node)). Задание типа управления временем жизни для дочернего узла, отличающегося от заданного для корня, не имеет эффекта.


### Возвращаемое значение

Тип управления временем жизни для узла (см. перечисление [*LIFETIME*](#LIFETIME)).
## Math:: WorldBoundBox getHierarchyBoundBox ( bool only_enabled_nodes = false ) const

Возвращает ограничивающий параллелепипед с локальными координатами, учитывающий дочерние узлы, но не участвующий в физических вычислениях. Исключение объектов из пространственного дерева значительно уменьшает размер дерева и повышает производительность за счёт экономии времени на пересчёт ограничивающего параллелепипеда при трансформации узлов.
### Аргументы

- *bool* **only_enabled_nodes** - Установите true, чтобы получить результат, учитывающий только включённые узлы иерархии, или false - чтобы учитывать все узлы иерархии независимо от их состояния *enabled*.

### Возвращаемое значение

Ограничивающий параллелепипед с мировыми координатами.
## Math:: WorldBoundSphere getHierarchyBoundSphere ( bool only_enabled_nodes = false ) const

Возвращает ограничивающую сферу с локальными координатами, учитывающую дочерние узлы, но не участвующую в физических вычислениях. Исключение объектов из пространственного дерева значительно уменьшает размер дерева и повышает производительность за счёт экономии времени на пересчёт ограничивающей сферы при трансформации узлов.
### Аргументы

- *bool* **only_enabled_nodes** - Установите true, чтобы получить результат, учитывающий только включённые узлы иерархии, или false - чтобы учитывать все узлы иерархии независимо от их состояния *enabled*.

### Возвращаемое значение

Ограничивающая сфера с мировыми координатами.
## Math:: WorldBoundBox getHierarchyWorldBoundBox ( bool only_enabled_nodes = false ) const

Возвращает ограничивающий параллелепипед с мировыми координатами, учитывающий дочерние узлы, но не участвующий в физических вычислениях. Исключение объектов из пространственного дерева значительно уменьшает размер дерева и повышает производительность за счёт экономии времени на пересчёт ограничивающего параллелепипеда при трансформации узлов.
### Аргументы

- *bool* **only_enabled_nodes** - Установите true, чтобы получить результат, учитывающий только включённые узлы иерархии, или false - чтобы учитывать все узлы иерархии независимо от их состояния *enabled*.

### Возвращаемое значение

Ограничивающий параллелепипед с мировыми координатами.
## Math:: WorldBoundSphere getHierarchyWorldBoundSphere ( bool only_enabled_nodes = false ) const

Возвращает ограничивающую сферу с мировыми координатами, учитывающую дочерние узлы, но не участвующую в физических вычислениях. Исключение объектов из пространственного дерева значительно уменьшает размер дерева и повышает производительность за счёт экономии времени на пересчёт ограничивающей сферы при трансформации узлов.
### Аргументы

- *bool* **only_enabled_nodes** - Установите true, чтобы получить результат, учитывающий только включённые узлы иерархии, или false - чтобы учитывать все узлы иерархии независимо от их состояния *enabled*.

### Возвращаемое значение

Ограничивающая сфера с мировыми координатами.
## Math:: WorldBoundBox getHierarchySpatialBoundBox ( bool only_enabled_nodes = false ) const

Возвращает ограничивающий параллелепипед с мировыми координатами, учитывающий все дочерние узлы и физику. Этот ограничивающий параллелепипед используется пространственным деревом.
### Аргументы

- *bool* **only_enabled_nodes** - Установите true, чтобы получить результат, учитывающий только включённые узлы иерархии, или false - чтобы учитывать все узлы иерархии независимо от их состояния *enabled*.

### Возвращаемое значение

Ограничивающий параллелепипед с мировыми координатами.
## Math:: WorldBoundSphere getHierarchySpatialBoundSphere ( bool only_enabled_nodes = false ) const

Возвращает ограничивающую сферу с мировыми координатами, учитывающую все дочерние узлы и физику. Эта ограничивающая сфера используется пространственным деревом.
### Аргументы

- *bool* **only_enabled_nodes** - Установите true, чтобы получить результат, учитывающий только включённые узлы иерархии, или false - чтобы учитывать все узлы иерархии независимо от их состояния *enabled*.

### Возвращаемое значение

Ограничивающая сфера с мировыми координатами.
## virtual void updateSpatialTree ( )

Обновляет границы узла в [spatial tree](../../../principles/world_management/index.md#outdoor) в текущем кадре. Этот метод можно использовать, если вы используете собственную логику, влияющую на границы или позицию узла, и вам нужно, чтобы изменения были учтены в текущем кадре, а также для обработки таких изменений для ваших пользовательских узлов (*[ObjectExtern](../../../api/library/objects/class.objectextern_cpp.md), [NodeExtern](../../../api/library/nodes/class.nodeextern_cpp.md)*), которые иначе игнорируются. Вызов этого метода позволяет быстро применить изменения для этого узла без полного пересчёта дерева. Но следует учитывать, что границы узла, быстро обновлённые таким способом, **могут быть неточными** (они могут только расширяться, поскольку сужение потребует пересчёта дерева). Если требуются 100% точные границы в текущем кадре, вызовите метод *[World::updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)*. Также можно просто указать пространственному дереву обновить границы узла в следующем кадре через метод *[updateSpatialTreeDelayed()](../../...md#updateSpatialTreeDelayed_void)*.
## void updateSpatialTreeDelayed ( )

Помечает границы узла в пространственном дереве для обновления в следующем кадре (в этом случае все границы будут 100% точными, в отличие от метода *[updateSpatialTree()](../../...md#updateSpatialTree_void)*). Этот метод можно использовать, если вы используете собственную логику, влияющую на границы или позицию узла, а также для обработки таких изменений для ваших пользовательских узлов (*[ObjectExtern](../../../api/library/objects/class.objectextern_cpp.md), [NodeExtern](../../../api/library/nodes/class.nodeextern_cpp.md)*), которые иначе игнорируются. Изменения будут применены только в следующем кадре; если требуется, чтобы изменения были учтены прямо в текущем кадре, используйте метод *[World::updateSpatial()](../../../api/library/engine/class.world_cpp.md#updateSpatial_void)* для 100% точных границ (медленный), либо быстрый метод *[updateSpatialTree()](../../...md#updateSpatialTree_void)*, который только расширяет границы узла при необходимости.
## Ptr < WorldTrigger > getWorldTrigger ( int num )

Возвращает один из World Trigger, внутри которого в данный момент находится узел, по его номеру. Для любого узла в мире можно [check whether it is currently inside any World Trigger](#getNumWorldTriggers_int) и получить доступ к любому из таких триггеров, просто вызвав этот метод.
### Аргументы

- *int* **num** - Номер World Trigger в списке World Trigger, внутри которых в данный момент находится узел.

### Возвращаемое значение

World Trigger с указанным номером, внутри которого в данный момент находится узел.
## UGUID getLostNodePropertyGUID ( int num ) const

Возвращает [GUID](../../../api/library/filesystem/class.uguid_cpp.md) потерянного свойства, назначенного узлу. Если по какой-то причине свойство, назначенное указанному слоту узла, отсутствует, этот метод можно использовать для получения его GUID.
### Аргументы

- *int* **num** - Номер целевого слота свойства.

### Возвращаемое значение

[GUID](../../../api/library/filesystem/class.uguid_cpp.md) потерянного свойства.
## void renderBounds ( bool render_node_bound = true , bool render_instance_bound = false )

Отображает границы узла. Метод применяется для проверки фактического размера границ узла, рендерящихся на CPU, которые могут отличаться от размера меша, рендерящегося на GPU, если последний был изменён шейдером. Для узлов, состоящих из нескольких экземпляров меша (Clutter, Cluster), также доступен рендеринг границ каждого отдельного экземпляра меша.
### Аргументы

- *bool* **render_node_bound** - true, чтобы включить отображение границ узла, false, чтобы отключить.
- *bool* **render_instance_bound** - true, чтобы включить отображение границ для каждого отдельного экземпляра меша (применимо для узлов Clutter и Cluster), false, чтобы отключить.

## int getIDFromFile ( ) const

Возвращает ID узла из файла `*.node` или `*.world`, если узел был загружен из этого файла.
### Возвращаемое значение

ID узла из файла `*.node` или `*.world`. Для узла, созданного через код, возвращается -1.
## void applyReplacePaths ( )

Восстанавливает способность движка заменять запечённые текстуры (lightmap, shadow map) внутри Node Reference во время выполнения. Этот метод следует применять, если иерархия внутри Node Reference или путь к запечённой текстуре были изменены, что привело к рендерингу неподходящей lightmap или shadow map.
## void getNodes ( Vector < Ptr < Node >> & OUT_nodes )

Берёт коллекцию узлов, очищает её, а затем добавляет в неё все существующие узлы. Это включает узлы из мира и других источников, таких как кэшированные узлы или узлы, загружаемые в данный момент через AsyncQueue.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)>> &* **OUT_nodes** - Коллекция узлов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## bool hasData ( const char * name ) const

Проверяет, есть ли у узла связанные пользовательские данные.
### Аргументы

- *const char ** **name** - Строка, содержащая ключ, идентифицирующий пользовательские данные, хранящиеся в файле `*.node`.

### Возвращаемое значение

true, если у заданного узла есть пользовательские данные; иначе false.
## void removeData ( const char * name )

Удаляет пользовательские данные, связанные с узлом.
### Аргументы

- *const char ** **name** - String containing a key identifying user data stored in the `*.node` file.
