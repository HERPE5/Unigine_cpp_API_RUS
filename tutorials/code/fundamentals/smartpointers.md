# Working with Smart Pointers


## Некоторые основы


В UNIGINE экземпляры классов C++ API (таких как: *Node, Mesh, Body, Image* и так далее...) хранят только указатели на экземпляры внутренних классов C++, их нельзя создавать и удалять через стандартные операторы *new/delete*. Поэтому их следует объявлять как **умные указатели** (*[Unigine::Ptr](../../api/library/common/class.ptr_cpp.md)*), которые позволяют автоматически управлять их временем жизни. У UNIGINE есть собственный оптимизированный аллокатор памяти для более быстрого и эффективного управления памятью. Каждый умный указатель хранит счётчик ссылок, т.е. сколько умных указателей указывают на управляемый объект. Подсчёт ссылок потокобезопасен, так как изменение счётчика является атомарной операцией.


Не все методы внутренних классов C++ движка доступны пользователю, некоторые из них используются только движком. Это специфичные функции, которые либо используются только для некоторых внутренних целей, либо не могут быть переданы пользователю "как есть". Поэтому для отфильтровывания таких методов используется промежуточный уровень, называемый **интерфейсом**. Этот интерфейс хранит указатель на экземпляр внутреннего класса C++ движка.


**Чтобы создать экземпляр** внутреннего класса, следует объявить для него умный указатель и вызвать метод *create()* — конструктор класса — предоставив параметры конструирования при необходимости.


```cpp
// создание экземпляра объекта внутреннего класса
<Class>Ptr instance = <Class>::create(<construction_parameters>);

```


## Время жизни


Мы можем разделить все объекты на две группы в зависимости от способа управления их временем жизни:


- **Объекты *Ownership*** (*Image, Texture, Mesh, Tileset* и т.д.) эти объекты управляются в соответствии со счётчиком ссылок: когда последний умный указатель уничтожается, счётчик становится равным 0, и управляемый объект автоматически удаляется. В этом случае предполагается, что объект больше не нужен (движок ничего о нём не знает, а у пользователя нет указателя, чтобы его использовать), и поэтому он удаляется. (например, такие объекты, объявленные внутри области видимости, будут автоматически удалены при выходе из этой области видимости). ```cpp // создаём новое изображение ImagePtr img = Image::create(); // теперь два указателя указывают на наше изображение (инкремент счётчика ссылок) ImagePtr img2 = img; // удаляем изображение (так как оба указателя больше не указывают на него, и счётчик ссылок равен нулю) img2 = img = nullptr; ``` <details> <summary>Complete list of Ownership Objects | close</summary> **Complete list of *Ownership* Objects:** | - *[AnimationCurve](../../api/library/animations/timeline/class.animationcurve_cpp.md)* - *[AnimationCurveBool](../../api/library/animations/timeline/class.animationcurvebool_cpp.md)* - *[AnimationCurveDouble](../../api/library/animations/timeline/class.animationcurvedouble_cpp.md)* - *[AnimationCurveFloat](../../api/library/animations/timeline/class.animationcurvefloat_cpp.md)* - *[AnimationCurveInt](../../api/library/animations/timeline/class.animationcurveint_cpp.md)* - *[AnimationCurveQuat](../../api/library/animations/timeline/class.animationcurvequat_cpp.md)* - *[AnimationCurveScalar](../../api/library/animations/timeline/class.animationcurvescalar_cpp.md)* - *[AnimationCurveString](../../api/library/animations/timeline/class.animationcurvestring_cpp.md)* - *[AnimationCurveUGUID](../../api/library/animations/timeline/class.animationcurveuguid_cpp.md)* - *[AnimationFrame](../../api/library/animations/timeline/class.animationframe_cpp.md)* - *[AnimationMask](../../api/library/animations/timeline/class.animationmask_cpp.md)* - *[AnimationModifier](../../api/library/animations/timeline/class.animationmodifier_cpp.md)* - *[AnimationModifierBones](../../api/library/animations/timeline/class.animationmodifierbones_cpp.md)* - *[AnimationModifierBool](../../api/library/animations/timeline/class.animationmodifierbool_cpp.md)* - *[AnimationModifierDVec2](../../api/library/animations/timeline/class.animationmodifierdvec2_cpp.md)* - *[AnimationModifierDVec3](../../api/library/animations/timeline/class.animationmodifierdvec3_cpp.md)* - *[AnimationModifierDVec4](../../api/library/animations/timeline/class.animationmodifierdvec4_cpp.md)* - *[AnimationModifierDouble](../../api/library/animations/timeline/class.animationmodifierdouble_cpp.md)* - *[AnimationModifierFVec2](../../api/library/animations/timeline/class.animationmodifierfvec2_cpp.md)* - *[AnimationModifierFVec3](../../api/library/animations/timeline/class.animationmodifierfvec3_cpp.md)* - *[AnimationModifierFVec4](../../api/library/animations/timeline/class.animationmodifierfvec4_cpp.md)* - *[AnimationModifierFloat](../../api/library/animations/timeline/class.animationmodifierfloat_cpp.md)* - *[AnimationModifierInfo](../../api/library/animations/timeline/class.animationmodifierinfo_cpp.md)* - *[AnimationModifierInt](../../api/library/animations/timeline/class.animationmodifierint_cpp.md)* - *[AnimationModifierIVec2](../../api/library/animations/timeline/class.animationmodifierivec2_cpp.md)* - *[AnimationModifierIVec3](../../api/library/animations/timeline/class.animationmodifierivec3_cpp.md)* - *[AnimationModifierIVec4](../../api/library/animations/timeline/class.animationmodifierivec4_cpp.md)* - *[AnimationModifierMat4](../../api/library/animations/timeline/class.animationmodifiermat4_cpp.md)* - *[AnimationModifierNode](../../api/library/animations/timeline/class.animationmodifiernode_cpp.md)* - *[AnimationModifierQuat](../../api/library/animations/timeline/class.animationmodifierquat_cpp.md)* - *[AnimationModifierScalar](../../api/library/animations/timeline/class.animationmodifierscalar_cpp.md)* - *[AnimationModifierString](../../api/library/animations/timeline/class.animationmodifierstring_cpp.md)* - *[AnimationModifierTrack](../../api/library/animations/timeline/class.animationmodifiertrack_cpp.md)* - *[AnimationModifierUGUID](../../api/library/animations/timeline/class.animationmodifieruguid_cpp.md)* - *[AnimationModifierVec2](../../api/library/animations/timeline/class.animationmodifiervec2_cpp.md)* - *[AnimationModifierVec3](../../api/library/animations/timeline/class.animationmodifiervec3_cpp.md)* - *[AnimationModifierVec4](../../api/library/animations/timeline/class.animationmodifiervec4_cpp.md)* - *[Blob](../../api/library/common/class.blob_cpp.md)* - *[Camera](../../api/library/rendering/class.camera_cpp.md)* - *[Curve2d](../../api/library/common/class.curve2d_cpp.md)* | - *[Dir](../../api/library/filesystem/class.dir_cpp.md)* - *[Ellipsoid](../../api/library/geodetics/class.ellipsoid_cpp.md)* - *[File](../../api/library/filesystem/class.file_cpp.md)* - *[GameIntersection](../../api/library/engine/class.gameintersection_cpp.md)* - *[Image](../../api/library/common/class.image_cpp.md)* - *[ImageConverter](../../api/library/common/class.imageconverter_cpp.md)* - *[ImportAnimation](../../api/library/common/import/class.importanimation_cpp.md)* - *[ImportCamera](../../api/library/common/import/class.importcamera_cpp.md)* - *[ImportGeometry](../../api/library/common/import/class.importgeometry_cpp.md)* - *[ImportLight](../../api/library/common/import/class.importlight_cpp.md)* - *[ImportMaterial](../../api/library/common/import/class.importmaterial_cpp.md)* - *[ImportMesh](../../api/library/common/import/class.importmesh_cpp.md)* - *[ImportMeshSkinned](../../api/library/common/import/class.importmeshskinned_cpp.md)* - *[ImportNode](../../api/library/common/import/class.importnode_cpp.md)* - *[ImportProcessor](../../api/library/common/import/class.importprocessor_cpp.md)* - *[ImportScene](../../api/library/common/import/class.importscene_cpp.md)* - *[ImportSkeleton](../../api/library/common/import/class.importskeleton_cpp.md)* - *[ImportSurface](../../api/library/common/import/class.importsurface_cpp.md)* - *[Importer](../../api/library/common/import/class.importer_cpp.md)* - *[InputEvent](../../api/library/controls/class.inputevent_cpp.md)* - *[InputEventJoyAxisMotion](../../api/library/controls/class.inputeventjoyaxismotion_cpp.md)* - *[InputEventJoyButton](../../api/library/controls/class.inputeventjoybutton_cpp.md)* - *[InputEventJoyDevice](../../api/library/controls/class.inputeventjoydevice_cpp.md)* - *[InputEventJoyPovMotion](../../api/library/controls/class.inputeventjoypovmotion_cpp.md)* - *[InputEventKeyboard](../../api/library/controls/class.inputeventkeyboard_cpp.md)* - *[InputEventMouseButton](../../api/library/controls/class.inputeventmousebutton_cpp.md)* - *[InputEventMouseMotion](../../api/library/controls/class.inputeventmousemotion_cpp.md)* - *[InputEventMouseWheel](../../api/library/controls/class.inputeventmousewheel_cpp.md)* - *[InputEventPadAxisMotion](../../api/library/controls/class.inputeventpadaxismotion_cpp.md)* - *[InputEventPadButton](../../api/library/controls/class.inputeventpadbutton_cpp.md)* - *[InputEventPadDevice](../../api/library/controls/class.inputeventpaddevice_cpp.md)* - *[InputEventPadTouchMotion](../../api/library/controls/class.inputeventpadtouchmotion_cpp.md)* - *[InputEventSystem](../../api/library/controls/class.inputeventsystem_cpp.md)* - *[InputEventText](../../api/library/controls/class.inputeventtext_cpp.md)* - *[InputEventTouch](../../api/library/controls/class.inputeventtouch_cpp.md)* - *[InputEventVRButton](../../api/library/controls/class.inputeventvrbutton_cpp.md)* - *[InputEventVRButtonTouch](../../api/library/controls/class.inputeventvrbuttontouch_cpp.md)* - *[InputEventVRDevice](../../api/library/controls/class.inputeventvrdevice_cpp.md)* - *[InputEventVRAxisMotion](../../api/library/controls/class.inputeventvraxismotion_cpp.md)* - *[Json](../../api/library/common/class.json_cpp.md)* - *[LandscapeFetch](../../api/library/objects/landscape_terrain/class.landscapefetch_cpp.md)* - *[LandscapeImages](../../api/library/objects/landscape_terrain/class.landscapeimages_cpp.md)* - *[LandscapeMapFileCompression](../../api/library/objects/landscape_terrain/class.landscapemapfilecompression_cpp.md)* | - *[LandscapeMapFileCreator](../../api/library/objects/landscape_terrain/class.landscapemapfilecreator_cpp.md)* - *[LandscapeMapFileSettings](../../api/library/objects/landscape_terrain/class.landscapemapfilesettings_cpp.md)* - *[LandscapeTextures](../../api/library/objects/landscape_terrain/class.landscapetextures_cpp.md)* - *[Mesh](../../api/library/rendering/class.mesh_cpp.md)* - *[MeshDynamic](../../api/library/rendering/class.meshdynamic_cpp.md)* - *[MeshRender](../../api/library/rendering/class.meshrender_cpp.md)* - *[MeshSkinned](../../api/library/rendering/class.meshskinned_cpp.md)* - *[MeshSkinnedAnimation](../../api/library/rendering/class.meshskinnedanimation_cpp.md)* - *[ObjectIntersection](../../api/library/objects/class.objectintersection_cpp.md)* - *[ObjectIntersectionNormal](../../api/library/objects/class.objectintersectionnormal_cpp.md)* - *[ObjectIntersectionTexCoord](../../api/library/objects/class.objectintersectiontexcoord_cpp.md)* - *[PackageUng](../../api/library/filesystem/class.packageung_cpp.md)* - *[Path](../../api/library/common/class.path_cpp.md)* - *[PathRouteIntersection](../../api/library/pathfinding/class.pathrouteintersection_cpp.md)* - *[PhysicsIntersection](../../api/library/physics/class.physicsintersection_cpp.md)* - *[PhysicsIntersectionNormal](../../api/library/physics/class.physicsintersectionnormal_cpp.md)* - *[RegExp](../../api/library/common/class.regexp_cpp.md)* - *[RenderTarget](../../api/library/rendering/class.rendertarget_cpp.md)* - *[ResourceExternalMemory](../../api/library/rendering/class.resourceexternalmemory_cpp.md)* - *[ResourceFence](../../api/library/rendering/class.resourcefence_cpp.md)* - *[Shader](../../api/library/rendering/class.shader_cpp.md)* - *[ShapeContact](../../api/library/physics/class.shapecontact_cpp.md)* - *[Skeleton](../../api/library/animations/skeletal/class.skeleton_cpp.md)* - *[SkeletonPoseDecomposed](../../api/library/animations/skeletal/class.skeletonposedecomposed_cpp.md)* - *[SkeletonPoseMatrix](../../api/library/animations/skeletal/class.skeletonposematrix_cpp.md)* - *[Socket](../../api/library/networking/class.socket_cpp.md)* - *[SSLSocket](../../api/library/networking/class.sslsocket_cpp.md)* - *[Stream](../../api/library/common/class.stream_cpp.md)* - *[StructuredBuffer](../../api/library/rendering/class.structuredbuffer_cpp.md)* - *[SystemDialog](../../api/library/engine/class.systemdialog_cpp.md)* - *[Texture](../../api/library/rendering/class.texture_cpp.md)* - *[TextureRamp](../../api/library/rendering/class.textureramp_cpp.md)* - *[TilesetFile](../../api/library/objects/class.tilesetfile_cpp.md)* - *[UlonArg](../../api/library/common/class.ulonarg_cpp.md)* - *[UlonNode](../../api/library/common/class.ulonnode_cpp.md)* - *[UlonValue](../../api/library/common/class.ulonvalue_cpp.md)* - *[Viewport](../../api/library/rendering/class.viewport_cpp.md)* - *[WindowEvent](../../api/library/gui/class.windowevent_cpp.md)* - *[WindowEventDpi](../../api/library/gui/class.windoweventdpi_cpp.md)* - *[WindowEventDrop](../../api/library/gui/class.windoweventdrop_cpp.md)* - *[WindowEventGeneric](../../api/library/gui/class.windoweventgeneric_cpp.md)* - *[WorldIntersection](../../api/library/worlds/class.worldintersection_cpp.md)* - *[WorldIntersectionNormal](../../api/library/worlds/class.worldintersectionnormal_cpp.md)* - *[WorldIntersectionTexCoord](../../api/library/worlds/class.worldintersectiontexcoord_cpp.md)* - *[Xml](../../api/library/common/class.xml_cpp.md)* | |---|---|---| </details>
- **Объекты *Non-Ownership*** (узлы, виджеты, материалы, свойства и т.д.) — эти объекты взаимодействуют с движком и становятся управляемыми им с момента их создания (они участвуют в главном цикле, могут быть получены по именам и т.д.). **Время жизни этих объектов не определяется счётчиком ссылок**, они предоставляют механизм слабых ссылок, поэтому можно проверить, был ли объект удалён или нет. Чтобы удалить такие объекты, следует использовать *[deleteLater()](../../api/library/common/class.ptr_cpp.md#deleteLater_void)* или соответствующий метод менеджера (например: *[Materials::removeMaterial()](../../api/library/rendering/class.materials_cpp.md#removeMaterial_UGUID_int_int_int)*). ```cpp NodePtr node; void somefunc1(){ // создаём новый пустой узел node = NodeDummy::create(); } void somefunc2(){ // проверяем, существует ли узел if (node) Log::message("The node is alive\n"); // удаляем узел node.deleteLater(); } ```


Вместо ручного управления ссылками на узлы, вы можете просто выбрать для него политику управления временем жизни:


- **World-managed** — в этом случае узел будет удалён при закрытии мира. Эта политика используется по умолчанию для каждого нового узла.
- **Engine-managed** — в этом случае узел будет удалён автоматически при завершении работы движка (можно использовать для узлов, которые должны сохраняться при смене миров).


> **Примечание:** Время жизни каждого узла в иерархии определяется его корнем (либо родителем, либо владельцем). Установка типа управления временем жизни для дочернего узла, отличного от установленного для корня, не имеет эффекта.


## Повышающее и понижающее приведение типов


Иногда (например, при использовании *World::getNodeByName()* и т.д.) мы получаем значение *NodePtr*, которое является указателем на базовый класс, но чтобы выполнить операции с определённым объектом (например, *ObjectMeshDynamicPtr*), нам нужно выполнить **понижающее приведение (downcasting)** (т.е. преобразование из указателя-на-базовый в указатель-на-производный). Были введены следующие методы:


- **static_ptr_cast** — статическое приведение без каких-либо проверок (в соответствии с семантикой C++)
- **checked_ptr_cast** — понижающее приведение с выполнением автоматической проверки типа
- **dynamic_ptr_cast** — динамическое приведение (в соответствии с семантикой C++)


Иногда вам также может понадобиться выполнить **повышающее приведение (upcasting)** (т.е. преобразование из указателя-на-производный в указатель-на-базовый), этот тип приведения выполняется автоматически.


> **Примечание:** Неявное преобразование типов для умных указателей UNIGINE не допускается.


Примеры кода ниже демонстрируют описанные выше моменты.


**Пример 1**


```cpp
#include <UnigineEditor.h>
using namespace Unigine;
/* .. */

// находим указатель на узел по заданному имени
NodePtr baseptr = World::getNodeByName("my_meshdynamic");

// приводим указатель-на-производный от указателя-на-базовый с автоматической проверкой типа
ObjectMeshDynamicPtr derivedptr = checked_ptr_cast<ObjectMeshDynamic>(baseptr);

// статическое приведение: указатель-на-производный (File) от указателя-на-базовый (Stream)
if(stream->getType() == Stream::FILE)
    FilePtr file = static_ptr_cast<File>(stream);

// повышающее приведение к указателю на класс Object, который является базовым классом для ObjectMeshDynamic
ObjectPtr object = derivedptr;

// повышающее приведение к указателю на класс Node, который является базовым классом для всех объектов сцены
NodePtr node = derivedptr;

```


## Удаление объектов


У умного указателя есть деструктор ***[clear()](../../api/library/common/class.ptr_cpp.md#clear_void)***, предназначенный для объектов *[ownership](#ownership_object)*, очищающий указатель и удаляющий объект только в случае, если умный указатель, вызывающий этот метод, является последним, указывающим на объект (*интерфейс*, в данном случае). Это следует учитывать.


Что касается объектов *[non-ownership](#non_ownership_object)*, их можно удалить одним из следующих методов:


- ***[deleteLater()](../../api/library/common/class.ptr_cpp.md#deleteLater_void)*** — выполняет отложенное удаление, в этом случае объект будет удалён во время следующего этапа *[swap()](../../code/fundamentals/execution_sequence/main_loop.md)* главного цикла (рендеринг объекта прекращается немедленно, но он всё ещё существует в памяти некоторое время, так что вы можете получить его, например, у его родителя). Этот метод упрощает удаление объекта из вторичного потока, поэтому вы можете вызвать его и забыть о деталях, позволяя движку взять под контроль процесс удаления, что может использоваться для будущих оптимизаций;
- ***[deleteForce()](../../api/library/common/class.ptr_cpp.md#deleteForce_void)*** — выполняет немедленное удаление, что может быть необходимо в некоторых случаях. Вызов этого метода для объектов, зависящих от главного цикла (например, узлов), безопасен только при выполнении из главного потока.


Оба этих метода можно безопасно вызывать более одного раза для одного объекта (а также после того, как объект был удалён движком), не вызывая двойного удаления. Так что не волнуйтесь, вызывайте его всякий раз, когда объект больше не нужен.


## См. также


- Для получения дополнительной информации о методах класса *Ptr* см. страницу *[Ptr class](../../api/library/common/class.ptr_cpp.md)*.
