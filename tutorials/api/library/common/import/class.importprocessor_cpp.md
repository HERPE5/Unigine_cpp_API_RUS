# Unigine::ImportProcessor Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс используется для управления процессорами импорта. Процессор импорта — это модуль, который сохраняет объекты, сгенерированные [importer](../../../../api/library/common/import/class.importer_cpp.md) на основе [metadata](../../../../api/library/common/import/class.importscene_cpp.md) всей сцены или некоторых её компонентов, в файлы в родном формате UNIGINE и выполняет вспомогательные операции в процессе импорта (подготовка данных, управление файлами и т. д.). Вы можете использовать набор разных процессоров для каждого компонента сцены или один процессор для всех них. Существуют также два особых типа процессоров:

- **Пре-процессоры** — выполняют дополнительные операции с [scene metadata](../../../../api/library/common/import/class.importscene_cpp.md) перед генерацией объектов UNIGINE.
- **Пост-процессоры** — выполняют дополнительные операции с файлами, сгенерированными в процессе импорта (например, копирование файлов в другие папки, добавление файлов в пакеты и т. д.).


> **Notice:** Это базовый класс для всех процессоров импорта. Ваш пользовательский класс процессора импорта должен быть унаследован от него.


Вы можете переопределить один (или все) методы *[onProcess*()](#onProcessAnimation_MeshSkinnedAnimation_ImportMeshSkinned_ImportAnimation_bool)*, чтобы определить типы компонентов, обрабатываемых им; эти переопределённые методы будут вызываться импортёром при выполнении соответствующих операций импорта.


> **Notice:** Для пре- и пост-процессоров следует переопределять только метод *[onProcessScene()](#onProcessScene_ImportScene_bool)*.


## ImportProcessor Class

### Методы класса

---

## static ImportProcessorPtr create ( )

Конструктор. Создаёт пустой процессор импорта.
## Ptr < ImportProcessor > getImportProcessor ( ) const

Возвращает сам [import processor](../../../../api/library/common/import/class.importprocessor_cpp.md).
### Возвращаемое значение

Сам процессор импорта.
## void setImporter ( const Ptr < Importer > & importer )

Задаёт [importer](../../../../api/library/common/import/class.importer_cpp.md) для процессора импорта.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Importer](../../../../api/library/common/import/class.importer_cpp.md)> &* **importer** - Используемый [Importer](../../../../api/library/common/import/class.importer_cpp.md).

## Ptr < Importer > getImporter ( ) const

Возвращает [importer](../../../../api/library/common/import/class.importer_cpp.md) для процессора импорта.
### Возвращаемое значение

Текущий используемый [Importer](../../../../api/library/common/import/class.importer_cpp.md).
## void setOutputPath ( const char * path )

Задаёт указанный выходной путь для размещения файлов с импортированными элементами сцены.
### Аргументы

- *const char ** **path** - Выходной путь для установки.

## const char * getOutputPath ( ) const

Возвращает текущий выходной путь, используемый для размещения файлов с импортированными элементами сцены.
### Возвращаемое значение

Текущий выходной путь.
## bool processScene ( const Ptr < ImportScene > & scene )

Выполняет обработку сцены: изменяет метаданные [scene elements](../../../../api/library/common/import/class.importscene_cpp.md) или файлы, сгенерированные в процессе импорта сцены.
> **Notice:** Этот метод используется [pre-processors and post-processors](#pre_post). Чтобы настроить действия, выполняемые при обработке сцены, при реализации пользовательского пре- или пост-процессора вы можете переопределить метод **[onProcessScene()](../../../...md#onProcessScene_ImportScene_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportScene](../../../../api/library/common/import/class.importscene_cpp.md)> &* **scene** - Обрабатываемый [Scene](../../../../api/library/common/import/class.importscene_cpp.md).

### Возвращаемое значение

true, если указанная сцена была успешно обработана; иначе false.
## bool processTexture ( const Ptr < ImportTexture > & import_texture )

Выполняет обработку текстуры: сохраняет указанную сгенерированную текстуру в соответствующий файл в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке текстуры, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessTexture()](../../../...md#onProcessTexture_ImportTexture_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)> &* **import_texture** - Экземпляр класса *[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)*, содержащий информацию об импортированной текстуре.

### Возвращаемое значение

true, если указанная текстура была успешно импортирована в файл; иначе false.
## bool processMesh ( const Ptr < Mesh > & mesh , const Ptr < ImportMesh > & import_mesh )

Выполняет обработку меша: сохраняет указанный сгенерированный меш в соответствующий файл `*.mesh` в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке меша, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessMesh()](../../../...md#onProcessMesh_Mesh_ImportMesh_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - [UNIGINE's mesh instance](../../../../api/library/rendering/class.mesh_cpp.md), сгенерированный для указанного импортированного меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **import_mesh** - Экземпляр класса *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*, содержащий информацию об импортированном меше.

### Возвращаемое значение

true, если указанный меш был успешно импортирован в файл; иначе false.
## bool processMeshSkinned ( const Ptr < MeshSkinned > & mesh_skinned , const Ptr < ImportMeshSkinned > & import_mesh_skinned )

Выполняет обработку скинового меша: сохраняет указанный сгенерированный скиновый меш в соответствующий файл `*.mesh_skinned` в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке скинового меша, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessMeshSkinned()](../../../...md#onProcessMeshSkinned_MeshSkinned_ImportMeshSkinned_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinned](../../../../api/library/rendering/class.meshskinned_cpp.md)> &* **mesh_skinned** - [UNIGINE's skinned mesh instance](../../../../api/library/rendering/class.meshskinned_cpp.md), сгенерированный для указанного импортированного скинового меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*, содержащий информацию об импортированном скиновом меше.

### Возвращаемое значение

true, если указанный скиновый меш был успешно импортирован в файл; иначе false.
## bool processLight ( const Ptr < Light > & light , const Ptr < ImportLight > & import_light )

Выполняет обработку источника света: сохраняет указанный сгенерированный источник света в соответствующий файл в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке источника света, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessLight()](../../../...md#onProcessLight_Light_ImportLight_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Light](../../../../api/library/lights/class.light_cpp.md)> &* **light** - [UNIGINE's light instance](../../../../api/library/lights/class.light_cpp.md), сгенерированный для указанного импортированного источника света.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)> &* **import_light** - Экземпляр класса *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*, содержащий информацию об импортированном источнике света.

### Возвращаемое значение

true, если указанный источник света был успешно обработан; иначе false.
## bool processCamera ( const Ptr < Player > & camera , const Ptr < ImportCamera > & import_camera )

Выполняет обработку камеры: сохраняет указанного сгенерированного игрока в соответствующий файл в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке камеры, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessCamera()](../../../...md#onProcessCamera_Player_ImportCamera_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Player](../../../../api/library/players/class.player_cpp.md)> &* **camera** - [UNIGINE's player instance](../../../../api/library/players/class.player_cpp.md), сгенерированный для указанной импортированной камеры.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)> &* **import_camera** - Экземпляр класса *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*, содержащий информацию об импортированной камере.

### Возвращаемое значение

true, если указанная камера была успешно обработана; иначе false.
## bool processAnimation ( const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportAnimation > & import_animation )

Выполняет обработку анимации меша: сохраняет указанную сгенерированную анимацию меша в соответствующий файл в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке анимации меша, при реализации пользовательского процессора импорта, вы можете переопределить метод **[onProcessAnimation()](../../../...md#onProcessAnimation_MeshSkinnedAnimation_ImportAnimation_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - [UNIGINE's mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md), сгенерированный для указанной импортированной анимации.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*, содержащий информацию об импортированной анимации.

### Возвращаемое значение

true, если указанная анимация была успешно обработана; иначе false.
## bool processAnimation ( const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation )

Выполняет обработку анимации меша: сохраняет указанную сгенерированную анимацию меша в соответствующий файл в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке анимации меша, при реализации пользовательского процессора импорта, вы можете переопределить метод **[onProcessAnimation()](../../../...md#onProcessAnimation_MeshSkinnedAnimation_ImportMeshSkinned_ImportAnimation_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - [UNIGINE's skinned mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md), сгенерированный для указанной импортированной анимации.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*, содержащий информацию об импортированном скиновом меше.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*, содержащий информацию об импортированной анимации.

### Возвращаемое значение

true, если указанная анимация была успешно обработана; иначе false.
## bool processNode ( const Ptr < Node > & node , const Ptr < ImportNode > & import_node )

Выполняет обработку узла: сохраняет указанный сгенерированный узел в соответствующий файл `*.node` в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке узла, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessNode()](../../../...md#onProcessNode_Node_ImportNode_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md), сгенерированный для указанного импортированного узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, содержащий информацию об импортированном узле.

### Возвращаемое значение

true, если указанный узел был успешно обработан; иначе false.
## bool processNodeChild ( const Ptr < Node > & node_parent , const Ptr < ImportNode > & import_node_parent , const Ptr < Node > & node_child , const Ptr < ImportNode > & import_node_child )

Выполняет обработку узла: сохраняет указанный сгенерированный узел вместе с указанным дочерним узлом в соответствующий файл `*.node` в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке узла, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessNodeChild()](../../../...md#onProcessNodeChild_Node_ImportNode_Node_ImportNode_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_parent** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного родительского узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_parent** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, содержащий информацию об импортированном родительском узле.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_child** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного дочернего узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_child** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, содержащий информацию об импортированном дочернем узле.

### Возвращаемое значение

true, если указанный родительский узел вместе с указанным дочерним узлом был успешно обработан; иначе false.
## bool processMaterial ( const Ptr < Material > & material , const Ptr < ImportMaterial > & import_material )

Выполняет обработку материала: сохраняет указанный сгенерированный материал в соответствующий файл в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке материала, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessMaterial()](../../../...md#onProcessMaterial_Material_ImportMaterial_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)> &* **material** - [UNIGINE's material instance](../../../../api/library/rendering/class.material_cpp.md), сгенерированный для указанного импортированного материала.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)> &* **import_material** - Экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*, содержащий информацию об импортированном материале.

### Возвращаемое значение

true, если указанный материал был успешно обработан; иначе false.
## bool processSkeleton ( const Ptr < Skeleton > & skeleton , const Ptr < ImportSkeleton > & import_skeleton )

Выполняет обработку скелета: сохраняет указанный сгенерированный скелет в соответствующий файл в [output directory](#getOutputPath_cstr).
> **Notice:** Чтобы настроить действия, выполняемые при обработке скелета, при [implementing a custom import processor](../../../../code/usage/custom_import_processor/index.md), вы можете переопределить метод **[onProcessSkeleton()](../../../...md#onProcessSkeleton_Skeleton_ImportSkeleton_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Skeleton](../../../../api/library/animations/skeletal/class.skeleton_cpp.md)> &* **skeleton** - [UNIGINE's skeleton instance](../../../../api/library/animations/skeletal/class.skeleton_cpp.md), сгенерированный для указанного импортированного скелета.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)> &* **import_skeleton** - Экземпляр класса *[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)*, содержащий информацию об импортированном скелете.

### Возвращаемое значение

true, если указанный скелет был успешно обработан; иначе false.
## bool onProcessScene ( const Ptr < ImportScene > & scene )

Функция-обработчик события обработки сцены. Эта функция вызывается каждый раз при вызове функции **[processScene()](../../../...md#processScene_ImportScene_bool)**. Вы можете задать собственные действия: изменение метаданных [scene elements](../../../../api/library/common/import/class.importscene_cpp.md) (пре-обработка) или файлов, сгенерированных в процессе импорта сцены (пост-обработка).
> **Notice:** Этот метод используется [pre-processors and post-processors](#pre_post).


```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessScene(ImportScene *scene) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessScene(ImportScene *scene)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportScene](../../../../api/library/common/import/class.importscene_cpp.md)> &* **scene** - Обрабатываемый [Scene](../../../../api/library/common/import/class.importscene_cpp.md).

### Возвращаемое значение

true, если указанная сцена была успешно обработана; иначе false.
## bool onProcessTexture ( const Ptr < ImportTexture > & import_texture )

Функция-обработчик события обработки текстуры. Эта функция вызывается каждый раз при вызове функции **[processTexture()](../../../...md#processTexture_ImportTexture_bool)**. Вы можете задать собственные действия, выполняемые при обработке текстуры.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessTexture(ImportTexture *import_texture) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessTexture(ImportTexture *import_texture)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)> &* **import_texture** - Экземпляр класса *[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)*, содержащий информацию об импортированной текстуре.

### Возвращаемое значение

true, если указанная текстура была успешно обработана; иначе false.
## bool onProcessMesh ( const Ptr < Mesh > & mesh , const Ptr < ImportMesh > & import_mesh )

Функция-обработчик события обработки меша. Эта функция вызывается каждый раз при вызове функции **[processMesh()](../../../...md#processMesh_Mesh_ImportMesh_bool)**. Вы можете задать собственные действия, выполняемые при обработке меша.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessMesh(MeshPtr &mesh, ImportMesh *import_mesh) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessMesh(MeshPtr &mesh, ImportMesh *import_mesh)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - [UNIGINE's mesh instance](../../../../api/library/rendering/class.mesh_cpp.md), сгенерированный для указанного импортированного меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **import_mesh** - Экземпляр класса *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*, содержащий информацию об импортированном меше.

### Возвращаемое значение

true, если указанный меш был успешно обработан; иначе false.
## bool onProcessMeshSkinned ( const Ptr < MeshSkinned > & mesh_skinned , const Ptr < ImportMeshSkinned > & import_mesh_skinned )

Функция-обработчик события обработки скинового меша. Эта функция вызывается каждый раз при вызове функции **[processMeshSkinned()](../../../...md#processMeshSkinned_MeshSkinned_ImportMeshSkinned_bool)**. Вы можете задать собственные действия, выполняемые при обработке скинового меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinned](../../../../api/library/rendering/class.meshskinned_cpp.md)> &* **mesh_skinned** - [UNIGINE's skinned mesh instance](../../../../api/library/rendering/class.meshskinned_cpp.md), сгенерированный для указанного импортированного скинового меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*, содержащий информацию об импортированном скиновом меше.

### Возвращаемое значение

true, если указанный скиновый меш был успешно обработан; иначе false.
## bool onProcessLight ( const Ptr < Light > & light , const Ptr < ImportLight > & import_light )

Функция-обработчик события обработки источника света. Эта функция вызывается каждый раз при вызове функции **[processLight()](../../../...md#processLight_Light_ImportLight_bool)**. Вы можете задать собственные действия, выполняемые при обработке источника света.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessLight(LightPtr &light, ImportLight *import_light) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessLight(LightPtr &light, ImportLight *import_light)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Light](../../../../api/library/lights/class.light_cpp.md)> &* **light** - [UNIGINE's light instance](../../../../api/library/lights/class.light_cpp.md), сгенерированный для указанного импортированного источника света.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)> &* **import_light** - Экземпляр класса *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*, содержащий информацию об импортированном источнике света.

### Возвращаемое значение

true, если указанный источник света был успешно обработан; иначе false.
## bool onProcessCamera ( const Ptr < Player > & camera , const Ptr < ImportCamera > & import_camera )

Функция-обработчик события обработки камеры. Эта функция вызывается каждый раз при вызове функции **[processCamera()](../../../...md#processCamera_Player_ImportCamera_bool)**. Вы можете задать собственные действия, выполняемые при обработке камеры.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessCamera(PlayerPtr &camera, ImportCamera *import_camera) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessCamera(PlayerPtr &camera, ImportCamera *import_camera)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Player](../../../../api/library/players/class.player_cpp.md)> &* **camera** - [UNIGINE's player instance](../../../../api/library/players/class.player_cpp.md), сгенерированный для указанной импортированной камеры.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)> &* **import_camera** - Экземпляр класса *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*, содержащий информацию об импортированной камере.

### Возвращаемое значение

true, если указанная камера была успешно обработана; иначе false.
## bool onProcessAnimation ( const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportAnimation > & import_animation )

Функция-обработчик события обработки анимации. Эта функция вызывается каждый раз при вызове функции **[processAnimation()](../../../...md#processAnimation_MeshSkinnedAnimation_ImportMeshSkinned_ImportAnimation_bool)**. Вы можете задать собственные действия, выполняемые при обработке анимации.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessAnimation(MeshSkinnedAnimationPtr &animation, ImportMeshSkinned *import_mesh_skinned, ImportAnimation *import_animation) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessAnimation(MeshSkinnedAnimationPtr &animation, ImportMeshSkinned *import_mesh_skinned, ImportAnimation *import_animation)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - [UNIGINE's mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md), сгенерированный для указанной импортированной анимации меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*, содержащий информацию об импортированной анимации.

### Возвращаемое значение

true, если указанная анимация была успешно обработана; иначе false.
## bool onProcessAnimation ( const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation )

Функция-обработчик события обработки анимации. Эта функция вызывается каждый раз при вызове функции **[processAnimation()](../../../...md#processAnimation_MeshSkinnedAnimation_ImportMeshSkinned_ImportAnimation_bool)**. Вы можете задать собственные действия, выполняемые при обработке анимации.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessAnimation(MeshSkinnedAnimationPtr &animation, ImportMeshSkinned *import_mesh_skinned, ImportAnimation *import_animation) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessAnimation(MeshSkinnedAnimationPtr &animation, ImportMeshSkinned *import_mesh_skinned, ImportAnimation *import_animation)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - [UNIGINE's skinned mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md), сгенерированный для указанной импортированной анимации.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*, содержащий информацию об импортированном скиновом меше.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*, содержащий информацию об импортированной анимации.

### Возвращаемое значение

true, если указанная анимация была успешно обработана; иначе false.
## bool onProcessNode ( const Ptr < Node > & node , const Ptr < ImportNode > & import_node )

Функция-обработчик события обработки узла. Эта функция вызывается каждый раз при вызове функции **[processNode()](../../../...md#processNode_Node_ImportNode_bool)**. Вы можете задать собственные действия, выполняемые при обработке узла.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessNode(NodePtr &node, ImportNode *import_node) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessNode(NodePtr &node, ImportNode *import_node)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node** - [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md), сгенерированный для указанного импортированного узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, содержащий информацию об импортированном узле.

### Возвращаемое значение

true, если указанный узел был успешно обработан; иначе false.
## bool onProcessNodeChild ( const Ptr < Node > & node_parent , const Ptr < ImportNode > & import_node_parent , const Ptr < Node > & node_child , const Ptr < ImportNode > & import_node_child )

Функция-обработчик события обработки узла для иерархий узлов. Эта функция вызывается каждый раз при вызове функции **[processNodeChild()](../../../...md#processNodeChild_Node_ImportNode_Node_ImportNode_bool)**. Вы можете задать собственные действия, выполняемые при обработке узлов (например, присвоение свойств дочерним узлам).
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessNodeChild(const NodePtr &node_parent, const ImportNodePtr &import_node_parent, const NodePtr &node_child, const ImportNodePtr &import_node_child) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessNode(NodePtr &node, ImportNode *import_node)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_parent** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного родительского узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_parent** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, содержащий информацию об импортированном родительском узле.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_child** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного дочернего узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_child** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, содержащий информацию об импортированном дочернем узле.

### Возвращаемое значение

true, если указанный родительский узел был успешно обработан вместе с указанным дочерним узлом; иначе false.
## bool onProcessMaterial ( const Ptr < Material > & material , const Ptr < ImportMaterial > & import_material )

Функция-обработчик события обработки материала. Эта функция вызывается каждый раз при вызове функции **[processMaterial()](../../../...md#processMaterial_Material_ImportMaterial_bool)**. Вы можете задать собственные действия, выполняемые при обработке материала.
```cpp
class MyCustomProcessor : public Unigine::ImportProcessor
{
public:
	MyCustomProcessor();
	virtual ~MyCustomProcessor();

/*...*/

// переопределения функций событий
protected:
	virtual bool onProcessMaterial(MaterialPtr &material, ImportMaterial *import_material) override;

/*...*/

};

/*...*/

bool MyCustomProcessor::onProcessMaterial(MaterialPtr &material, ImportMaterial *import_material)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)> &* **material** - [UNIGINE's material instance](../../../../api/library/rendering/class.material_cpp.md), сгенерированный для указанного импортированного материала.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)> &* **import_material** - Экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*, содержащий информацию об импортированном материале.

### Возвращаемое значение

true, если указанный материал был успешно обработан; иначе false.
## bool onProcessSkeleton ( const Ptr < Skeleton > & skeleton , const Ptr < ImportSkeleton > & import_skeleton )

Функция-обработчик события обработки скелета. Эта функция вызывается каждый раз при вызове функции **[processSkeleton()](../../../...md#processSkeleton_Skeleton_ImportSkeleton_bool)**. Вы можете задать собственные действия, выполняемые при обработке скелета.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Skeleton](../../../../api/library/animations/skeletal/class.skeleton_cpp.md)> &* **skeleton** - [UNIGINE's skeleton instance](../../../../api/library/animations/skeletal/class.skeleton_cpp.md), сгенерированный для указанного импортированного скелета.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)> &* **import_skeleton** - Экземпляр класса *[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)*, содержащий информацию об импортированном скелете.

### Возвращаемое значение

true, если указанный скелет был успешно обработан; иначе false.
