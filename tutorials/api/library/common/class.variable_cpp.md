# Unigine::Variable Class (CPP)

**Header:** #include <UnigineInterpreter.h>


Универсальная переменная для функторов.


## Variable Class

### Методы класса

---

## Variable ( )

Конструктор по умолчанию.
## Variable ( const Variable & v )

Конструктор копирования.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( int v )

Явный конструктор для переменной типа int.
### Аргументы

- *int* **v** - Значение переменной.

## explicit Variable ( long long v )

Явный конструктор для переменной типа long long.
### Аргументы

- *long long* **v** - Значение переменной.

## explicit Variable ( float v )

Явный конструктор для переменной типа float.
### Аргументы

- *float* **v** - Значение переменной.

## explicit Variable ( double v )

Явный конструктор для переменной типа double.
### Аргументы

- *double* **v** - Значение переменной.

## explicit Variable ( const vec2 & v )

Явный конструктор для переменной типа vec2.
### Аргументы

- *const [vec2](../../../api/library/math/class.vec2_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const vec3 & v )

Явный конструктор для переменной типа vec3.
### Аргументы

- *const [vec3](../../../api/library/math/class.vec3_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const vec4 & v )

Явный конструктор для переменной типа vec4.
### Аргументы

- *const [vec4](../../../api/library/math/class.vec4_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const dvec2 & v )

Явный конструктор для переменной типа dvec2.
### Аргументы

- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const dvec3 & v )

Явный конструктор для переменной типа dvec3.
### Аргументы

- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const dvec4 & v )

Явный конструктор для переменной типа dvec4.
### Аргументы

- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const ivec2 & v )

Явный конструктор для переменной типа ivec2.
### Аргументы

- *const [ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const ivec3 & v )

Явный конструктор для переменной типа ivec3.
### Аргументы

- *const [ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const ivec4 & v )

Явный конструктор для переменной типа ivec4.
### Аргументы

- *const [ivec4](../../../api/library/math/class.ivec4_cpp.md) &* **v** - Значение переменной.

## explicit Variable ( const mat4 & m )

Явный конструктор для переменной типа mat4.
### Аргументы

- *const [mat4](../../../api/library/math/class.mat4_cpp.md) &* **m** - Значение переменной.

## explicit Variable ( const dmat4 & m )

Явный конструктор для переменной типа dmat4.
### Аргументы

- *const [dmat4](../../../api/library/math/class.dmat4_cpp.md) &* **m** - Значение переменной.

## explicit Variable ( const quat & q )

Явный конструктор для переменной типа quad.
### Аргументы

- *const [quat](../../../api/library/math/class.quat_cpp.md) &* **q** - Значение переменной.

## explicit Variable ( const char * s )

Явный конструктор для переменной строкового типа.
### Аргументы

- *const char ** **s** - Значение переменной.

## Variable ( void * interpreter , const char * type_name , void * object , int append , int manage )

Конструктор объекта внешнего класса.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const char ** **type_name** - Имя типа объекта внешнего класса.
- *void ** **object** - Указатель на объект.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Body Ptr & body , int append , int manage )

Конструктор объекта класса на основе умного указателя Body.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Body](../../../api/library/physics/class.body_cpp.md)Ptr &* **body** - Умный указатель на Body.
- *int* **append** - Скрипт возьмёт на себя владение Body и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Body посредством подсчёта ссылок.

## Variable ( void * interpreter , const Camera Ptr & camera , int append , int manage )

Конструктор объекта класса на основе умного указателя Camera.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Camera](../../../api/library/rendering/class.camera_cpp.md)Ptr &* **camera** - Умный указатель на Camera.
- *int* **append** - Скрипт возьмёт на себя владение камерой и будет отвечать за её удаление.
- *int* **manage** - Скрипт будет управлять временем жизни камеры посредством подсчёта ссылок.

## Variable ( void * interpreter , const Controls Ptr & controls , int append , int manage )

Конструктор объекта класса на основе умного указателя Controls.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Controls](../../../api/library/controls/class.controls_cpp.md)Ptr &* **controls** - Умный указатель на Controls.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const DatasetPtr & dataset , int append , int manage )

Конструктор объекта класса на основе умного указателя Dataset.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const DatasetPtr &* **dataset** - Умный указатель на Dataset.
- *int* **append** - Скрипт возьмёт на себя владение Dataset и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Dataset посредством подсчёта ссылок.

## Variable ( void * interpreter , const Decal Ptr & decal , int append , int manage )

Конструктор объекта класса на основе умного указателя Decal.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Decal](../../../api/library/decals/class.decal_cpp.md)Ptr &* **decal** - Умный указатель на Decal.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Ellipsoid Ptr & ellipsoid , int append , int manage )

Конструктор объекта класса на основе умного указателя Ellipsoid.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Ellipsoid](../../../api/library/geodetics/class.ellipsoid_cpp.md)Ptr &* **ellipsoid** - Умный указатель на Ellipsoid.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Gui Ptr & gui , int append , int manage )

Конструктор объекта класса на основе умного указателя Gui.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Gui](../../../api/library/gui/class.gui_cpp.md)Ptr &* **gui** - Умный указатель на Gui.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Image Ptr & image , int append , int manage )

Конструктор объекта класса на основе умного указателя Image.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Image](../../../api/library/common/class.image_cpp.md)Ptr &* **image** - Умный указатель на Image.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Light Ptr & light , int append , int manage )

Конструктор объекта класса на основе умного указателя Light.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Light](../../../api/library/lights/class.light_cpp.md)Ptr &* **light** - Умный указатель на Light.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Material Ptr & material , int append , int manage )

Конструктор объекта класса на основе умного указателя Material.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Material](../../../api/library/rendering/class.material_cpp.md)Ptr &* **material** - Умный указатель на Material.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Mesh Ptr & mesh , int append , int manage )

Конструктор объекта класса на основе умного указателя Mesh.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Mesh](../../../api/library/rendering/class.mesh_cpp.md)Ptr &* **mesh** - Умный указатель на Mesh.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Node Ptr & node , int append , int manage )

Конструктор объекта класса на основе умного указателя Node.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Node](../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Умный указатель на Node.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Object Ptr & object , int append , int manage )

Конструктор объекта класса на основе умного указателя Object.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Object](../../../api/library/objects/class.object_cpp.md)Ptr &* **object** - Умный указатель на Object.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Path Ptr & path , int append , int manage )

Конструктор объекта класса на основе умного указателя Path.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Path](../../../api/library/common/class.path_cpp.md)Ptr &* **path** - Умный указатель на Path.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Player Ptr & player , int append , int manage )

Конструктор объекта класса на основе умного указателя Player.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Player](../../../api/library/players/class.player_cpp.md)Ptr &* **player** - Умный указатель на Player.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Shape Ptr & shape , int append , int manage )

Конструктор объекта класса на основе умного указателя Shape.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Shape](../../../api/library/physics/class.shape_cpp.md)Ptr &* **shape** - Умный указатель на Shape.
- *int* **append** - Скрипт возьмёт на себя владение Shape и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Shape посредством подсчёта ссылок.

## Variable ( void * interpreter , const Stream Ptr & stream , int append , int manage )

Конструктор объекта класса на основе умного указателя Stream.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Stream](../../../api/library/common/class.stream_cpp.md)Ptr &* **stream** - Умный указатель на Stream.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Property Ptr & property , int append , int manage )

Конструктор объекта класса на основе умного указателя Property.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Property](../../../api/library/common/class.property_cpp.md)Ptr &* **property** - Умный указатель на Property.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const PropertyParameter Ptr & property_parameter , int append , int manage )

Конструктор объекта класса на основе умного указателя PropertyParameter.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [PropertyParameter](../../../api/library/common/class.propertyparameter_cpp.md)Ptr &* **property_parameter** - Умный указатель на PropertyParameter.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const RenderEnvironmentPreset Ptr & preset , int append , int manage )

Конструктор объекта класса на основе умного указателя RenderEnvironmentPreset.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [RenderEnvironmentPreset](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md)Ptr &* **preset** - Умный указатель на RenderEnvironmentPreset.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const TerrainGlobalDetail Ptr & detail , int append , int manage )

Конструктор объекта класса на основе умного указателя TerrainGlobalDetail.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalDetail](../../../api/library/objects/class.terrainglobaldetail_cpp.md)Ptr &* **detail** - Умный указатель на TerrainGlobalDetail.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalDetail и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни TerrainGlobalDetail посредством подсчёта ссылок.

## Variable ( void * interpreter , const TerrainGlobalLodHeight Ptr & lod , int append , int manage )

Конструктор объекта класса на основе умного указателя TerrainGlobalLodHeight.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalLodHeight](../../../api/library/objects/class.terraingloballodheight_cpp.md)Ptr &* **lod** - Умный указатель на TerrainGlobalLodHeight.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalLodHeight и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни TerrainGlobalLodHeight посредством подсчёта ссылок.

## Variable ( void * interpreter , const TerrainGlobalLod Ptr & lod , int append , int manage )

Конструктор объекта класса на основе умного указателя TerrainGlobalLod.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalLod](../../../api/library/objects/class.terraingloballod_cpp.md)Ptr &* **lod** - Умный указатель на TerrainGlobalLod.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalLod и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни TerrainGlobalLod посредством подсчёта ссылок.

## Variable ( void * interpreter , const TerrainGlobalLods Ptr & lods , int append , int manage )

Конструктор объекта класса на основе умного указателя TerrainGlobalLods.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalLods](../../../api/library/objects/class.terraingloballods_cpp.md)Ptr &* **lods** - Умный указатель на TerrainGlobalLods.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalLods и будет отвечать за его удаление.
- *int* **manage**

## Variable ( void * interpreter , const TypeInfo & type_info , void * object , int append , int manage )

Конструктор объекта внешнего класса.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TypeInfo](../../../api/library/common/class.typeinfo_cpp.md) &* **type_info** - Информация о типе.
- *void ** **object** - Указатель на объект.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Widget Ptr & widget , int append , int manage )

Конструктор объекта класса на основе умного указателя Widget.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Widget](../../../api/library/gui/class.widget_cpp.md)Ptr &* **widget** - Умный указатель на Widget.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( void * interpreter , const Xml Ptr & xml , int append , int manage )

Конструктор объекта класса на основе умного указателя Xml.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Xml](../../../api/library/common/class.xml_cpp.md)Ptr &* **xml** - Умный указатель на Xml.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## Variable ( const UGUID & g )

Конструктор объекта класса на основе умного указателя [UGUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Умный указатель на [UGUID](../../../api/library/filesystem/class.uguid_cpp.md).

## Variable ( void * interpreter , const Joint Ptr & joint , int append , int manage )

Конструктор объекта класса на основе умного указателя [Joint](../../../api/library/physics/class.joint_cpp.md).
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Joint](../../../api/library/physics/class.joint_cpp.md)Ptr &* **joint** - Умный указатель на Joint.
- *int* **append** - Скрипт возьмёт на себя владение Joint и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Joint посредством подсчёта ссылок.

## void set ( const Variable & v )

Задаёт переменную.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение переменной.

## const Variable & get ( ) const

Возвращает текущую переменную.
### Возвращаемое значение

Значение переменной.
## void setBody ( void * interpreter , const Body Ptr & body , int append , int manage )

Задаёт умный указатель Body для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Body](../../../api/library/physics/class.body_cpp.md)Ptr &* **body** - Умный указатель на Body.
- *int* **append** - Скрипт возьмёт на себя владение Body и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Body посредством подсчёта ссылок.

## const Body Ptr & getBody ( void * interpreter )

Возвращает текущую переменную как умный указатель Body, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на Body.
## int isBody ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом Body.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом Body; иначе **0**.
## void setCamera ( void * interpreter , const Camera Ptr & camera , int append , int manage )

Задаёт умный указатель Camera для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Camera](../../../api/library/rendering/class.camera_cpp.md)Ptr &* **camera** - Умный указатель на Camera.
- *int* **append** - Скрипт возьмёт на себя владение Camera и будет отвечать за её удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Camera посредством подсчёта ссылок.

## const Camera Ptr & getCamera ( void * interpreter )

Возвращает текущую переменную как умный указатель Camera, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на Camera.
## int isCamera ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом Camera.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом Camera; иначе **0**.
## void setControls ( void * interpreter , const Controls Ptr & controls , int append , int manage )

Задаёт умный указатель controls для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Controls](../../../api/library/controls/class.controls_cpp.md)Ptr &* **controls** - Умный указатель на Controls.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## const Controls Ptr & getControls ( void * interpreter ) const

Возвращает текущую переменную как умный указатель controls, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на Controls.
## int isControls ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом controls.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом controls; иначе **0**.
## Variable::VariableData * getData ( )

## void setDataset ( void * interpreter , const DatasetPtr & dataset , int append , int manage )

Задаёт умный указатель Dataset для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const DatasetPtr &* **dataset** - Умный указатель на Dataset.
- *int* **append** - Скрипт возьмёт на себя владение Dataset и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Dataset посредством подсчёта ссылок.

## const DatasetPtr & getDataset ( void * interpreter )

Возвращает текущую переменную как умный указатель Dataset, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на Dataset.
## int isDataset ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом Dataset.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом Dataset; иначе **0**.
## void setDecal ( void * interpreter , const Decal Ptr & decal , int append , int manage )

Задаёт умный указатель decal для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Decal](../../../api/library/decals/class.decal_cpp.md)Ptr &* **decal** - Умный указатель на Decal.
- *int* **append** - Скрипт возьмёт на себя владение decal и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни decal посредством подсчёта ссылок.

## const Decal Ptr & getDecal ( void * interpreter ) const

Возвращает текущую переменную как умный указатель decal, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isDecal ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом decal.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Возвращает **1**, если переменная является объектом decal; иначе **0**.
## void setDVec2 ( const dvec2 & v )

Задаёт двухкомпонентный вектор для переменной.
### Аргументы

- *const [dvec2](../../../api/library/math/class.dvec2_cpp.md) &* **v** - Значение переменной.

## const dvec2 & getDVec2 ( )

Возвращает текущую переменную как двухкомпонентный вектор, если это возможно.
### Возвращаемое значение

Значение переменной.
## int isDVec2 ( )

Возвращает значение, указывающее, является ли переменная трёхкомпонентным вектором.
### Возвращаемое значение

**1**, если переменная является двухкомпонентным вектором; иначе **0**.
## void setDVec3 ( const dvec3 & v )

Задаёт трёхкомпонентный вектор для переменной.
### Аргументы

- *const [dvec3](../../../api/library/math/class.dvec3_cpp.md) &* **v** - Значение переменной.

## const dvec3 & getDVec3 ( ) const

Возвращает текущую переменную как трёхкомпонентный вектор, если это возможно.
### Возвращаемое значение

Значение переменной.
## int isDVec3 ( ) const

Возвращает значение, указывающее, является ли переменная трёхкомпонентным вектором.
### Возвращаемое значение

**1**, если переменная является трёхкомпонентным вектором; иначе **0**.
## void setDVec4 ( const dvec4 & v )

Задаёт четырёхкомпонентный вектор для переменной.
### Аргументы

- *const [dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **v** - Значение переменной.

## const dvec4 & getDVec4 ( ) const

Возвращает текущую переменную как четырёхкомпонентный вектор, если это возможно.
### Возвращаемое значение

Значение переменной.
## int isDVec4 ( ) const

Возвращает значение, указывающее, является ли переменная четырёхкомпонентным вектором.
### Возвращаемое значение

Возвращает **1**, если переменная является четырёхкомпонентным вектором; иначе **0**.
## void setEllipsoid ( void * interpreter , const Ellipsoid Ptr & ellipsoid , int append , int manage )

Задаёт умный указатель ellipsoid для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Ellipsoid](../../../api/library/geodetics/class.ellipsoid_cpp.md)Ptr &* **ellipsoid** - Умный указатель на Ellipsoid.
- *int* **append** - Скрипт возьмёт на себя владение ellipsoid и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни ellipsoid посредством подсчёта ссылок.

## const Ellipsoid Ptr & getEllipsoid ( void * interpreter )

Возвращает текущую переменную как умный указатель ellipsoid, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на Ellipsoid.
## int isEllipsoid ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом ellipsoid.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом ellipsoid; иначе **0**.
## int isExternClass ( ) const

Возвращает значение, указывающее, принадлежит ли переменная внешнему классу.
### Возвращаемое значение

1, если переменная принадлежит внешнему классу; иначе 0.
## void setExternClassObject ( void * interpreter , const char * type_name , void * object , int append , int manage )

Задаёт объект внешнего класса для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const char ** **type_name** - Имя типа объекта внешнего класса.
- *void ** **object** - Указатель на объект.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## void setExternClassObject ( void * interpreter , const TypeInfo & type_info , void * object , int append , int manage )

Задаёт объект внешнего класса для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TypeInfo](../../../api/library/common/class.typeinfo_cpp.md) &* **type_info** - Информация о типе.
- *void ** **object** - Указатель на объект.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## void setExternClassObject ( void * interpreter , Type * object , int append , int manage )

Задаёт объект внешнего класса для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *Type ** **object** - Указатель на объект.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## void * getExternClassObject ( void * interpreter , const TypeInfo & type_info ) const

Возвращает указатель на объект внешнего класса.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TypeInfo](../../../api/library/common/class.typeinfo_cpp.md) &* **type_info** - Информация о типе.

## Type * getExternClassObject ( void * interpreter ) const

Возвращает тип объекта внешнего класса.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Тип объекта.
## int isExternClassObject ( void * interpreter ) const

Возвращает значение, указывающее, принадлежит ли объект внешнему классу.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

1, если переменная принадлежит внешнему классу; иначе 0.
## Type & getExternClassObjectRef ( void * interpreter ) const

Возвращает тип объекта внешнего класса, хранящегося в переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Тип объекта.
## TypeInfo getExternClassType ( void * interpreter ) const

Возвращает информацию о типе объекта внешнего класса, хранящегося в переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Информация о типе.
## void setGui ( void * interpreter , const Gui Ptr & gui , int append , int manage )

Задаёт умный указатель gui для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Gui](../../../api/library/gui/class.gui_cpp.md)Ptr &* **gui** - Умный указатель на Gui.
- *int* **append** - Скрипт возьмёт на себя владение данными gui и будет отвечать за их удаление.
- *int* **manage** - Скрипт будет управлять временем жизни данных gui посредством подсчёта ссылок.

## const Gui Ptr & getGui ( void * interpreter ) const

Возвращает текущую переменную как умный указатель gui, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isGui ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом gui.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Возвращает **1**, если переменная является объектом gui; иначе **0**.
## void setImage ( void * interpreter , const Image Ptr & image , int append , int manage )

Задаёт умный указатель image для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Image](../../../api/library/common/class.image_cpp.md)Ptr &* **image** - Умный указатель на Image.
- *int* **append** - Скрипт возьмёт на себя владение image и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни image посредством подсчёта ссылок.

## const Image Ptr & getImage ( void * interpreter ) const

Возвращает текущую переменную как умный указатель image, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isImage ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом image.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Возвращает **1**, если переменная является объектом image; иначе **0**.
## void setJoint ( void * interpreter , const Joint Ptr & joint , int append , int manage )

Задаёт умный указатель [Joint](../../../api/library/physics/class.joint_cpp.md) для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Joint](../../../api/library/physics/class.joint_cpp.md)Ptr &* **joint** - Умный указатель на [Joint](../../../api/library/physics/class.joint_cpp.md).
- *int* **append** - Скрипт возьмёт на себя владение Joint и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Joint посредством подсчёта ссылок.

## const Joint Ptr & getJoint ( void * interpreter )

Возвращает текущую переменную как умный указатель [Joint](../../../api/library/physics/class.joint_cpp.md), если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на Joint.
## int isJoint ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом [Joint](../../../api/library/physics/class.joint_cpp.md).
### Аргументы

- *void ** **interpreter**

### Возвращаемое значение

**1**, если переменная является объектом Joint; иначе **0**.
## void setLight ( void * interpreter , const Light Ptr & light , int append , int manage )

Задаёт умный указатель light для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Light](../../../api/library/lights/class.light_cpp.md)Ptr &* **light** - Умный указатель на Light.
- *int* **append** - Скрипт возьмёт на себя владение light и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни light посредством подсчёта ссылок.

## const Light Ptr & getLight ( void * interpreter ) const

Возвращает текущую переменную как умный указатель light, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isLight ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом light.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом light; иначе **0**.
## void setLong ( long long v )

Задаёт значение long long для переменной.
### Аргументы

- *long long* **v** - Значение переменной.

## long long getLong ( ) const

Возвращает текущую переменную как значение long long, если это возможно.
### Возвращаемое значение

Значение переменной.
## int isLong ( ) const

Возвращает значение, указывающее, является ли переменная значением long long.
### Возвращаемое значение

**1**, если переменная является значением long long; иначе **0**.
## void setMaterial ( void * interpreter , const Material Ptr & material , int append , int manage )

Задаёт умный указатель material для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Material](../../../api/library/rendering/class.material_cpp.md)Ptr &* **material** - Умный указатель на Material.
- *int* **append** - Скрипт возьмёт на себя владение material и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни material посредством подсчёта ссылок.

## const Material Ptr & getMaterial ( void * interpreter ) const

Возвращает текущую переменную как умный указатель material, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isMaterial ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом material.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом material; иначе **0**.
## void setMesh ( void * interpreter , const Mesh Ptr & mesh , int append , int manage )

Задаёт умный указатель mesh для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Mesh](../../../api/library/rendering/class.mesh_cpp.md)Ptr &* **mesh** - Умный указатель на Mesh.
- *int* **append** - Скрипт возьмёт на себя владение данными mesh и будет отвечать за их удаление.
- *int* **manage** - Скрипт будет управлять временем жизни данных mesh посредством подсчёта ссылок.

## const Mesh Ptr & getMesh ( void * interpreter ) const

Возвращает текущую переменную как умный указатель mesh, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isMesh ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом mesh.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом mesh; иначе **0**.
## void setNode ( void * interpreter , const Node Ptr & node , int append , int manage )

Задаёт умный указатель node для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Node](../../../api/library/nodes/class.node_cpp.md)Ptr &* **node** - Умный указатель на Node.
- *int* **append** - Скрипт возьмёт на себя владение node и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни node посредством подсчёта ссылок.

## const Node Ptr & getNode ( void * interpreter ) const

Возвращает текущую переменную как умный указатель node, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isNode ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом node.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Возвращает **1**, если переменная является объектом node; иначе **0**.
## int isNull ( ) const

Возвращает значение, указывающее, является ли переменная нулевым значением.
### Возвращаемое значение

**1**, если переменная является нулевым значением; иначе **0**.
## void setObject ( void * interpreter , const Object Ptr & object , int append , int manage )

Задаёт умный указатель object для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Object](../../../api/library/objects/class.object_cpp.md)Ptr &* **object** - Умный указатель на Object.
- *int* **append** - Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.

## const Object Ptr & getObject ( void * interpreter ) const

Возвращает текущую переменную как умный указатель object, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isObject ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом object.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом object; иначе **0**.
## void setPath ( void * interpreter , const Path Ptr & path , int append , int manage )

Задаёт умный указатель path для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Path](../../../api/library/common/class.path_cpp.md)Ptr &* **path** - Умный указатель на Path.
- *int* **append** - Скрипт возьмёт на себя владение данными path и будет отвечать за их удаление.
- *int* **manage** - Скрипт будет управлять временем жизни данных path посредством подсчёта ссылок.

## const Path Ptr & getPath ( void * interpreter ) const

Возвращает текущую переменную как умный указатель path, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isPath ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом path.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом path; иначе **0**.
## void setPlayer ( void * interpreter , const Player Ptr & player , int append , int manage )

Задаёт умный указатель player для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Player](../../../api/library/players/class.player_cpp.md)Ptr &* **player** - Умный указатель на Player.
- *int* **append** - Скрипт возьмёт на себя владение player и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни player посредством подсчёта ссылок.

## const Player Ptr & getPlayer ( void * interpreter ) const

Возвращает текущую переменную как умный указатель player, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isPlayer ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом player.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом player; иначе **0**.
## void setProperty ( void * interpreter , const Property Ptr & property , int append , int manage )

Задаёт умный указатель property для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Property](../../../api/library/common/class.property_cpp.md)Ptr &* **property** - Умный указатель на Property.
- *int* **append** - Скрипт возьмёт на себя владение property и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни property посредством подсчёта ссылок.

## const Property Ptr & getProperty ( void * interpreter ) const

Возвращает текущую переменную как умный указатель property, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isProperty ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом property.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом property; иначе **0**.
## void setPropertyParameter ( void * interpreter , const PropertyParameter Ptr & property_parameters , int append , int manage )

Задаёт умный указатель property parameter для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [PropertyParameter](../../../api/library/common/class.propertyparameter_cpp.md)Ptr &* **property_parameters** - Умный указатель на PropertyParameter.
- *int* **append** - Скрипт возьмёт на себя владение property parameter и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни property parameter посредством подсчёта ссылок.

## const PropertyParameter Ptr & getPropertyParameter ( void * interpreter )

Возвращает текущую переменную как умный указатель property parameter, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isPropertyParameter ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом property parameter.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом property parameter; иначе **0**.
## void setRenderEnvironmentPreset ( void * interpreter , const RenderEnvironmentPreset Ptr & preset , int append , int manage )

Задаёт умный указатель RenderEnvironmentPreset для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [RenderEnvironmentPreset](../../../api/library/rendering/class.renderenvironmentpreset_cpp.md)Ptr &* **preset**
- *int* **append** - Скрипт возьмёт на себя владение RenderEnvironmentPreset и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни RenderEnvironmentPreset посредством подсчёта ссылок.

## const RenderEnvironmentPreset Ptr & getRenderEnvironmentPreset ( void * interpreter )

Возвращает текущую переменную как умный указатель RenderEnvironmentPreset, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на RenderEnvironmentPreset.
## int isRenderEnvironmentPreset ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом RenderEnvironmentPreset.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом RenderEnvironmentPreset; иначе **0**.
## void setShape ( void * interpreter , const Shape Ptr & shape , int append , int manage )

Задаёт умный указатель Shape для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Shape](../../../api/library/physics/class.shape_cpp.md)Ptr &* **shape** - Умный указатель на Shape.
- *int* **append** - Скрипт возьмёт на себя владение Shape и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни Shape посредством подсчёта ссылок.

## const Shape Ptr & getShape ( void * interpreter )

Возвращает текущую переменную как Shape, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на Shape.
## int isShape ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом Shape.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом Shape; иначе **0**.
## void setStream ( void * interpreter , const Stream Ptr & stream , int append , int manage )

Задаёт умный указатель stream для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Stream](../../../api/library/common/class.stream_cpp.md)Ptr &* **stream** - Умный указатель на Stream.
- *int* **append** - Скрипт возьмёт на себя владение данными stream и будет отвечать за их удаление.
- *int* **manage** - Скрипт будет управлять временем жизни данных stream посредством подсчёта ссылок.

## const Stream Ptr & getStream ( void * interpreter ) const

Возвращает текущую переменную как умный указатель stream, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isStream ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом stream.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Возвращает **1**, если переменная является объектом stream; иначе **0**.
## void setTerrainGlobalLod ( void * interpreter , const TerrainGlobalLod Ptr & lod , int append , int manage )

Задаёт умный указатель TerrainGlobalLod для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalLod](../../../api/library/objects/class.terraingloballod_cpp.md)Ptr &* **lod** - Умный указатель на TerrainGlobalLod.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalLod и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни TerrainGlobalLod посредством подсчёта ссылок.

## const TerrainGlobalLod Ptr & getTerrainGlobalLod ( void * interpreter )

Возвращает текущую переменную как умный указатель TerrainGlobalLod, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на TerrainGlobalLod.
## int isTerrainGlobalLod ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом TerrainGlobalLod.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

1, если переменная является объектом TerrainGlobalLod; иначе 0.
## void setTerrainGlobalLods ( void * interpreter , const TerrainGlobalLods Ptr & lods , int append , int manage )

Задаёт умный указатель TerrainGlobalLods для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalLods](../../../api/library/objects/class.terraingloballods_cpp.md)Ptr &* **lods** - Умный указатель на TerrainGlobalLods.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalLods и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни TerrainGlobalLods посредством подсчёта ссылок.

## const TerrainGlobalLods Ptr & getTerrainGlobalLods ( void * interpreter )

Возвращает текущую переменную как умный указатель TerrainGlobalLods, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на TerrainGlobalLods.
## int isTerrainGlobalLods ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом TerrainGlobalLods.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

1, если переменная является объектом TerrainGlobalLods; иначе 0.
## void setTerrainGlobalLodHeight ( void * interpreter , const TerrainGlobalLodHeight Ptr & lod , int append , int manage )

Задаёт умный указатель TerrainGlobalLodHeight для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalLodHeight](../../../api/library/objects/class.terraingloballodheight_cpp.md)Ptr &* **lod** - Умный указатель на TerrainGlobalLodHeight.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalLodHeight и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни TerrainGlobalLodHeight посредством подсчёта ссылок.

## const TerrainGlobalLodHeight Ptr & getTerrainGlobalLodHeight ( void * interpreter )

Возвращает текущую переменную как умный указатель TerrainGlobalLodHeight, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на TerrainGlobalLodHeight.
## int isTerrainGlobalLodHeight ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом TerrainGlobalLodHeight.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

1, если переменная является объектом TerrainGlobalLodHeight; иначе 0.
## void setTerrainGlobalDetail ( void * interpreter , const TerrainGlobalDetail Ptr & detail , int append , int manage )

Задаёт умный указатель TerrainGlobalDetail для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [TerrainGlobalDetail](../../../api/library/objects/class.terrainglobaldetail_cpp.md)Ptr &* **detail** - Умный указатель на TerrainGlobalDetail.
- *int* **append** - Скрипт возьмёт на себя владение TerrainGlobalDetail и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни TerrainGlobalDetail посредством подсчёта ссылок.

## const TerrainGlobalDetail Ptr & getTerrainGlobalDetail ( void * interpreter )

Возвращает текущую переменную как умный указатель TerrainGlobalDetail, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Умный указатель на TerrainGlobalDetail.
## int isTerrainGlobalDetail ( void * interpreter )

Возвращает значение, указывающее, является ли переменная объектом TerrainGlobalDetail.
### Аргументы

- *void ** **interpreter**

### Возвращаемое значение

1, если переменная является объектом TerrainGlobalDetail; иначе 0.
## int getType ( ) const

Возвращает тип переменной.
### Возвращаемое значение

Тип переменной (см. перечисление Unigine::Variable::).
## String getTypeInfo ( ) const

Возвращает информацию о типе переменной.
### Возвращаемое значение

Строка с информацией о типе переменной.
## String getTypeName ( ) const

Возвращает имя типа переменной.
### Возвращаемое значение

Строка с именем типа переменной.
## void setUserClass ( int type , int number , int instance )

Задаёт пользовательский класс для переменной.
### Аргументы

- *int* **type** - Идентификатор типа пользовательского класса.
- *int* **number** - Номер пользовательского класса.
- *int* **instance** - Экземпляр пользовательского класса.

## int isUserClass ( ) const

Возвращает значение, указывающее, является ли переменная пользовательским классом.
### Возвращаемое значение

Возвращает **1**, если переменная является пользовательским классом; иначе **0**.
## int getUserClassInstance ( ) const

Возвращает экземпляр пользовательского класса.
### Возвращаемое значение

Экземпляр пользовательского класса.
## int getUserClassNumber ( ) const

Возвращает номер пользовательского класса.
### Возвращаемое значение

Номер пользовательского класса.
## int getUserClassType ( ) const

Возвращает тип пользовательского класса.
### Возвращаемое значение

Идентификатор типа пользовательского класса.
## void setWidget ( void * interpreter , const Widget Ptr & widget , int append , int manage )

Задаёт умный указатель widget для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Widget](../../../api/library/gui/class.widget_cpp.md)Ptr &* **widget** - Умный указатель на Widget.
- *int* **append** - Скрипт возьмёт на себя владение widget и будет отвечать за его удаление.
- *int* **manage** - Скрипт будет управлять временем жизни widget посредством подсчёта ссылок.

## const Widget Ptr & getWidget ( void * interpreter ) const

Возвращает текущую переменную как умный указатель widget, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isWidget ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом widget.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

**1**, если переменная является объектом widget; иначе **0**.
## void setXml ( void * interpreter , const Xml Ptr & xml , int append , int manage )

Задаёт умный указатель XML для переменной.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
- *const [Xml](../../../api/library/common/class.xml_cpp.md)Ptr &* **xml** - Умный указатель на XML.
- *int* **append** - Скрипт возьмёт на себя владение данными XML и будет отвечать за их удаление.
- *int* **manage** - Скрипт будет управлять временем жизни данных XML посредством подсчёта ссылок.

## const Xml Ptr & getXml ( void * interpreter ) const

Возвращает текущую переменную как умный указатель XML, если это возможно.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Значение переменной.
## int isXml ( void * interpreter ) const

Возвращает значение, указывающее, является ли переменная объектом XML.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

### Возвращаемое значение

Возвращает **1**, если переменная является объектом XML; иначе **0**.
## void appendExternClass ( void * interpreter ) const

Скрипт возьмёт на себя владение объектом и будет отвечать за его удаление.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

## void manageExternClass ( void * interpreter ) const

Скрипт будет управлять временем жизни объекта посредством подсчёта ссылок.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

## int operator!= ( const Variable & v ) const

Сравнение переменных на неравенство.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator% ( const Variable & v ) const

Операция взятия остатка от деления переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator& ( const Variable & v ) const

Побитовое И переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## int operator&& ( const Variable & v ) const

Логическое И переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator* ( const Variable & v ) const

Умножение переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator+ ( const Variable & v ) const

Сложение переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator- ( const Variable & v ) const

Вычитание переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator/ ( const Variable & v ) const

Деление переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## int operator< ( const Variable & v ) const

Сравнение переменных "меньше".
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator<< ( const Variable & v ) const

Побитовый сдвиг переменной влево.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## int operator<= ( const Variable & v ) const

Сравнение переменных "меньше или равно".
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable & operator= ( const Variable & v )

Оператор присваивания для переменной.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение переменной.

## int operator== ( const Variable & v ) const

Сравнение переменных на равенство.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## int operator> ( const Variable & v ) const

Сравнение переменных "больше".
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## int operator>= ( const Variable & v ) const

Сравнение переменных "больше или равно".
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator>> ( const Variable & v ) const

Побитовый сдвиг переменной вправо.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator^ ( const Variable & v ) const

Побитовое исключающее ИЛИ переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## Variable operator| ( const Variable & v ) const

Побитовое ИЛИ переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## int operator|| ( const Variable & v ) const

Логическое ИЛИ переменных.
### Аргументы

- *const [Variable](../../../api/library/common/class.variable_cpp.md) &* **v** - Значение второй переменной.

### Возвращаемое значение

Результирующая переменная.
## void releaseExternClass ( void * interpreter ) const

Скрипт откажется от владения объектом и очистит все ссылки на него.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.

## void removeExternClass ( void * interpreter ) const

Скрипт откажется от владения объектом и не будет отвечать за его удаление.
### Аргументы

- *void ** **interpreter** - Указатель на интерпретатор.
