# Unigine::Importer Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс используется для управления импортёром файлов. Импортёры файлов используются [import system](../../../../api/library/common/import/index.md) движка для переноса данных, хранящихся в различных неродных форматах, в UNIGINE. Каждый импортёр может использоваться для импорта нескольких форматов файлов, но для одного формата файла не должно быть [registered](../../../../api/library/common/import/class.import_cpp.md#registerImporter_ImporterID_cstr_ImporterCreationFunction_ImporterDeletionFunction_vptr_int_vptr) двух или более импортёров.


Импортёр имеет [set of flags](#IMPORT_LIGHTS), определяющих, какие компоненты сцены должны быть извлечены и импортированы. Поэтому импортёр должен быть [initialized](#init_cstr_int_bool) перед использованием.


Каждый импортёр генерирует объекты UNIGINE на основе метаданных, извлечённых из импортируемых файлов, и использует набор [processors](../../../../api/library/common/import/class.importprocessor_cpp.md) для выполнения всех необходимых вспомогательных операций (подготовка данных, сохранение файлов, управление файлами и т. д.). Импортёр позволяет добавлять любое количество пре- и пост-процессоров. Однако для каждого компонента сцены можно задать только один процессор.


> **Notice:** Это базовый класс для всех импортёров. Ваш пользовательский класс импортёра должен быть унаследован от него.


Вы можете настроить действия, выполняемые при импорте всей сцены, а также при импорте текстур, материалов, мешей, анимаций, источников света и камер, переопределив соответствующие функции-обработчики событий для вашего пользовательского импортёра


```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	virtual bool onInit(const ImportScenePtr &scene, const char *filepath) override;
	virtual bool onImport(const char *output_path) override;
	virtual bool onImportTexture(const Unigine::ImportProcessor &processor, const Unigine::ImportTexturePtr &import_texture) override;
	virtual bool onImportMaterial(const Unigine::ImportProcessor &processor, const Unigine::MaterialPtr &material, const Unigine::ImportMaterial &import_material) override;
	virtual bool onImportMesh(const Unigine::ImportProcessor &processor, const Unigine::MeshPtr &mesh, const Unigine::ImportMesh &import_mesh) override;
	virtual bool onImportMeshSkinned(const Unigine::ImportProcessor &processor, const Unigine::MeshSkinnedPtr &mesh_skinned, const Unigine::ImportMeshSkinned &import_mesh_skinned) override;
	virtual bool onImportLight(const Unigine::ImportProcessor &processor, const Unigine::LightPtr &light, const Unigine::ImportLight &import_light) override;
	virtual bool onImportCamera(const Unigine::ImportProcessor &processor, const Unigine::PlayerPtr &camera, const Unigine::ImportCamera &import_camera);
	virtual bool onImportNode(const Unigine::ImportProcessor &processor, const Unigine::NodePtr &node, const Unigine::ImportNode &import_node) override;
	virtual bool onImportNodeChild(const ImportProcessorPtr &processor, const Unigine::NodePtr &node_parent, const ImportNodePtr &import_node_parent, const Unigine::NodePtr &node_child, const ImportNodePtr &import_node_child) override;
	virtual bool onImportAnimation(const Unigine::ImportProcessor &processor, const Unigine::MeshSkinnedAnimationPtr &animation, const Unigine::ImportMeshSkinned &import_mesh_skinned, const Unigine::ImportAnimation &import_animation) override;
	virtual bool onImportSkeleton(const Unigine::ImportProcessor &processor, const Unigine::SkeletonPtr &skeleton, const Unigine::ImportSkeleton &import_skeleton) override;
	virtual bool onCheckSupportedAnimation(const Unigine::ImportMeshSkinnedPtr &import_mesh_skinned, const Unigine::ImportAnimationPtr &import_animation) override;
	virtual bool onCheckDefaultAnimation(const Unigine::ImportMeshSkinnedPtr &import_mesh_skinned, const Unigine::ImportAnimationPtr &import_animation) override;

private:
	ImportScene *import_scene();
	void import_textures(const Unigine::ImportScene &scene);
	void import_materials(const Unigine::ImportScene &scene);
	void import_animations(const Unigine::ImportScene &scene);

	void process_node(const Unigine::ImportScene &import_scene, const Unigine::ImportNode &parent, fbx::FbxNode *fbx_node);
	void process_mesh(const Unigine::ImportScene &import_scene, const Unigine::ImportNode &node, fbx::FbxNode *fbx_node, fbx::FbxMesh *fbx_mesh);
	void process_light(const Unigine::ImportScene &import_scene, const Unigine::ImportNode &node, fbx::FbxNode *fbx_node, fbx::FbxLight *fbx_light);
	void process_camera(const Unigine::ImportScene &import_scene, const Unigine::ImportNode &node, fbx::FbxNode *fbx_node, fbx::FbxCamera *fbx_camera);

/*...*/

};

```


## Importer Class

### Перечисления

## Axis

Ось.
| Name | Description |
|---|---|
| **None** = -1 | Нет оси. |
| **X** = None + 1 | Ось X. |
| **NX** = X + 1 | Отрицательная ось X. |
| **Y** = NX + 1 | Ось Y. |
| **NY** = Y + 1 | Отрицательная ось Y. |
| **Z** = NY + 1 | Ось Z. |
| **NZ** = Z + 1 | Отрицательная ось Z. |

### Методы класса

## void setAnimationsProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта анимаций.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта анимаций.

## const char * getAnimationsProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта анимаций.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта анимаций.
## void setSkeletonsProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта скелетов.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта скелетов.

## const char * getSkeletonsProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта скелетов.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта скелетов.
## void setLightsProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта источников света.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта источников света.

## const char * getLightsProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта источников света.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта источников света.
## void setMeshesProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта мешей.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта мешей.

## const char * getMeshesProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта мешей.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта мешей.
## void setMeshSkinnedsProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта скиновых мешей.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта скиновых мешей.

## const char * getMeshSkinnedsProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта скиновых мешей.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта скиновых мешей.
## void setNodesProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта узлов.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта узлов.

## const char * getNodesProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта узлов.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта узлов.
## void setCamerasProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта камер.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта камер.

## const char * getCamerasProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта камер.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта камер.
## void setMaterialsProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта материалов.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта материалов.

## const char * getMaterialsProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта материалов.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта материалов.
## void setOutputFilepath ( const char * filepath )

Задаёт новый результирующий выходной путь для импортированных компонентов сцены. Если генерируется набор файлов, будет возвращён путь к результирующему файлу `*.node`.
### Аргументы

- *const char ** **filepath** - Путь к выходному файлу.

## const char * getOutputFilepath () const

Возвращает текущий результирующий выходной путь для импортированных компонентов сцены. Если генерируется набор файлов, будет возвращён путь к результирующему файлу `*.node`.
### Возвращаемое значение

Текущий путь к выходному файлу.
## void setTexturesProcessor ( const char * processor )

Задаёт новый [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта текстур.
### Аргументы

- *const char ** **processor** - [Processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта текстур.

## const char * getTexturesProcessor () const

Возвращает текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта, используемый для импорта текстур.
### Возвращаемое значение

Текущий [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта текстур.
---

## static ImporterPtr create ( )

Конструктор. Создаёт пустой импортёр.
## Ptr < Importer > getImporter ( ) const

Возвращает сам [importer](../../../../api/library/common/import/class.importer_cpp.md).
### Возвращаемое значение

Сам импортёр.
## bool containsParameter ( const char * name ) const

Возвращает значение, указывающее, содержит ли список параметров импорта параметр с указанным именем.
### Аргументы

- *const char ** **name** - Имя параметра.

### Возвращаемое значение

true, если список параметров импорта содержит параметр с указанным именем; иначе false.
## void setParameterInt ( const char * name , int v )

Задаёт новое значение указанного параметра типа *integer*. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя параметра типа *integer*.
- *int* **v** - Новое значение для установки.

## int getParameterInt ( const char * name ) const

Возвращает текущее значение указанного параметра типа *integer*. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя параметра типа *integer*.

### Возвращаемое значение

Значение параметра типа *integer*.
## void setParameterFloat ( const char * name , float v )

Задаёт новое значение указанного параметра типа *float*. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя параметра типа *float*.
- *float* **v** - Новое значение для установки.

## float getParameterFloat ( const char * name ) const

Возвращает текущее значение указанного параметра типа *float*. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя параметра типа *float*.

### Возвращаемое значение

Значение параметра типа *float*.
## void setParameterDouble ( const char * name , double v )

Задаёт новое значение указанного параметра типа *double*. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя параметра типа *double*.
- *double* **v** - Новое значение для установки.

## double getParameterDouble ( const char * name ) const

Возвращает текущее значение указанного параметра типа *double*. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя параметра типа *double*.

### Возвращаемое значение

Значение параметра типа *double*.
## void setParameterString ( const char * name , const char * v )

Задаёт новое значение указанного строкового параметра. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя строкового параметра.
- *const char ** **v** - Новое значение для установки.

## const char * getParameterString ( const char * name ) const

Возвращает текущее значение указанного строкового параметра. Существуют [built-in parameters](../../../../principles/import_system/index_cpp.md#param_int), которые также можно использовать в пользовательских импортёрах.
### Аргументы

- *const char ** **name** - Имя строкового параметра.

### Возвращаемое значение

Значение строкового параметра.
## bool addPreProcessor ( const char * type_name )

Добавляет [pre-processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта с указанным именем типа. Существуют [built-in pre-processors](../../../../principles/import_system/index_cpp.md#preprocessors), которые также можно добавлять в пользовательские импортёры.
### Аргументы

- *const char ** **type_name** - Имя типа пре-процессора.

### Возвращаемое значение

true, если указанный пре-процессор импорта успешно добавлен; иначе false.
## void removePreProcessor ( const char * type_name )

Удаляет [pre-processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта с указанным именем типа. Существуют [built-in pre-processors](../../../../principles/import_system/index_cpp.md#preprocessors), которые также можно добавлять в пользовательские импортёры.
### Аргументы

- *const char ** **type_name** - Имя типа пре-процессора.

## bool hasPreProcessor ( const char * type_name )

Возвращает значение, указывающее, используется ли импортёром [pre-processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта с указанным именем типа. Существуют [built-in pre-processors](../../../../principles/import_system/index_cpp.md#preprocessors), которые также можно добавлять в пользовательские импортёры.
### Аргументы

- *const char ** **type_name** - Имя типа пре-процессора.

### Возвращаемое значение

true, если пре-процессор импорта с указанным именем типа используется импортёром; иначе false.
## bool addPostProcessor ( const char * type_name )

Добавляет [post-processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта с указанным именем типа. Существуют [built-in post-processors](../../../../principles/import_system/index_cpp.md#postprocessors), которые также можно добавлять в пользовательские импортёры.
### Аргументы

- *const char ** **type_name** - Имя типа пост-процессора для проверки.

## void removePostProcessor ( const char * type_name )

Удаляет [post-processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта с указанным именем типа. Существуют [built-in post-processors](../../../../principles/import_system/index_cpp.md#postprocessors), которые также можно добавлять в пользовательские импортёры.
### Аргументы

- *const char ** **type_name** - Имя типа пост-процессора.

## bool hasPostProcessor ( const char * type_name )

Возвращает значение, указывающее, используется ли импортёром [post-processor](../../../../api/library/common/import/class.importprocessor_cpp.md) импорта с указанным именем типа. Существуют [built-in post-processors](../../../../principles/import_system/index_cpp.md#postprocessors), которые также можно добавлять в пользовательские импортёры.
### Аргументы

- *const char ** **type_name** - Имя типа пост-процессора для проверки.

### Возвращаемое значение

true, если пост-процессор импорта с указанным именем типа используется импортёром; иначе false.
## Ptr < ImportScene > getScene ( ) const

Возвращает импортированную сцену.
### Возвращаемое значение

Экземпляр класса *[ImportScene](../../../../api/library/common/import/class.importscene_cpp.md)*.
## bool init ( const char * filepath , int flags = ~0 )

Инициализирует импортёр для указанного файла с использованием заданных флагов. Флаги импорта определяют, какие компоненты сцены должны быть импортированы.
### Аргументы

- *const char ** **filepath** - Путь к импортируемому файлу.
- *int* **flags** - Набор флагов импорта. Любая комбинация флагов [IMPORT_*](#IMPORT_LIGHTS) или ~0, чтобы установить все из них.

### Возвращаемое значение

true, если импортёр был успешно инициализирован; иначе 0.
## bool import ( const char * output_path )

Импортирует содержимое входного файла в указанный выходной путь.
### Аргументы

- *const char ** **output_path** - Выходной путь.

### Возвращаемое значение

true, если содержимое входного файла успешно импортировано в указанный выходной путь; иначе false.
## const char * getSourceFilepath ( ) const

Возвращает путь к исходному файлу.
### Возвращаемое значение

Путь к исходному файлу.
## int getFlags ( ) const

Возвращает текущий набор флагов импорта (*[IMPORT_*](#IMPORT_LIGHTS)*), заданных при инициализации.
## bool computeBoundBox ( const Ptr < ImportMesh > & import_mesh )

Вычисляет ограничивающий прямоугольник (bound box) для указанного меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **import_mesh** - Импортированный меш, для которого требуется вычислить ограничивающий прямоугольник.

### Возвращаемое значение

true, если ограничивающий прямоугольник для указанного меша успешно вычислен; иначе false.
## bool preprocess ( )

Запускает выполнение всех [added](#addPreProcessor_cstr_bool) пре-процессоров.
### Возвращаемое значение

true, если предварительная обработка завершена успешно.
## Ptr < Node > convertNode ( const Ptr < ImportProcessor > & processor , const Ptr < ImportNode > & root_node )

Преобразует метаданные, хранящиеся в экземпляре класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, в узел UNIGINE (иерархию узлов).
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **root_node** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, представляющий корневой узел импортируемой иерархии.

### Возвращаемое значение

Результирующий [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md), хранящий указанный импортированный узел (иерархию узлов).
## bool importTexture ( const Ptr < ImportProcessor > & processor , const Ptr < ImportTexture > & import_texture )

Импортирует указанную текстуру и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированной текстуры в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте текстур, при реализации пользовательского импортёра вы можете переопределить метод **[onImportTexture()](../../../...md#onImportTexture_ImportProcessor_ImportTexture_bool)**.

### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)> &* **import_texture** - Экземпляр класса *[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)*.

### Возвращаемое значение

true, если указанная текстура была успешно импортирована; иначе false.
## bool importMaterial ( const Ptr < ImportProcessor > & processor , const Ptr < Material > & material , const Ptr < ImportMaterial > & import_material )

Импортирует указанный материал и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированного материала в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте материалов, при реализации пользовательского импортёра вы можете переопределить метод **[onImportMaterial()](../../../...md#onImportMaterial_ImportProcessor_Material_ImportMaterial_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)> &* **material** - Целевой [UNIGINE's material instance](../../../../api/library/rendering/class.material_cpp.md) для хранения указанного импортированного материала.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)> &* **import_material** - Экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*.

### Возвращаемое значение

true, если указанный материал был успешно импортирован; иначе false.
## bool importMesh ( const Ptr < ImportProcessor > & processor , const Ptr < Mesh > & mesh , const Ptr < ImportMesh > & import_mesh )

Импортирует указанный меш и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированного меша в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте мешей, при реализации пользовательского импортёра вы можете переопределить метод **[onImportMesh()](../../../...md#onImportMesh_ImportProcessor_Mesh_ImportMesh_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Целевой [UNIGINE's mesh instance](../../../../api/library/rendering/class.mesh_cpp.md) для хранения указанного импортированного меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **import_mesh** - Экземпляр класса *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*.

### Возвращаемое значение

true, если указанный меш был успешно импортирован; иначе false.
## bool importMeshSkinned ( const Ptr < ImportProcessor > & processor , const Ptr < MeshSkinned > & mesh_skinned , const Ptr < ImportMeshSkinned > & import_mesh_skinned )

Импортирует указанный скиновый меш и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированного скинового меша в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте скиновых мешей, при реализации пользовательского импортёра вы можете переопределить метод **[onImportMeshSkinned()](../../../...md#onImportMeshSkinned_ImportProcessor_MeshSkinned_ImportMeshSkinned_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinned](../../../../api/library/rendering/class.meshskinned_cpp.md)> &* **mesh_skinned** - Целевой [UNIGINE's skinned mesh instance](../../../../api/library/rendering/class.meshskinned_cpp.md) для хранения указанного импортированного скинового меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*.

### Возвращаемое значение

true, если указанный скиновый меш был успешно импортирован; иначе false.
## Ptr < Light > importLight ( const Ptr < ImportProcessor > & processor , const Ptr < ImportLight > & import_light )

 Импортирует указанный источник света и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированного источника света в соответствующий файл `*.node` в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте источников света, при реализации пользовательского импортёра вы можете переопределить метод **[onImportLight()](../../../...md#onImportLight_ImportProcessor_ImportLight_Light)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)> &* **import_light** - Экземпляр класса *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*.

### Возвращаемое значение

[UNIGINE's light instance](../../../../api/library/lights/class.light_cpp.md), хранящий указанный импортированный источник света.
## Ptr < Player > importCamera ( const Ptr < ImportProcessor > & processor , const Ptr < ImportCamera > & import_camera )

 Импортирует указанную камеру и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированного игрока в соответствующий файл `*.node` в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте камер, при реализации пользовательского импортёра вы можете переопределить метод **[onImportCamera()](../../../...md#onImportCamera_ImportProcessor_ImportCamera_Player)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)> &* **import_camera** - Экземпляр класса *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*.

### Возвращаемое значение

[UNIGINE's player instance](../../../../api/library/players/class.player_cpp.md), хранящий указанную импортированную камеру.
## bool importAnimation ( const Ptr < ImportProcessor > & processor , const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportAnimation > & import_animation )

Импортирует указанную анимацию меша и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированной анимации меша в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте анимаций мешей, при реализации пользовательского импортёра вы можете переопределить метод **[onImportAnimation()](../../../...md#onImportAnimation_ImportProcessor_MeshSkinnedAnimation_ImportAnimation_bool)**.

### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - Целевой [UNIGINE's mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md) для хранения указанной импортированной анимации меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*.

### Возвращаемое значение

true, если указанная анимация была успешно импортирована; иначе false.
## bool importAnimation ( const Ptr < ImportProcessor > & processor , const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation )

Импортирует указанную анимацию меша и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированной анимации меша в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте анимаций мешей, при реализации пользовательского импортёра вы можете переопределить метод **[onImportAnimation()](../../../...md#onImportAnimation_ImportProcessor_MeshSkinnedAnimation_ImportMeshSkinned_ImportAnimation_bool)**.

### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - Целевой [UNIGINE's mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md) для хранения указанной импортированной анимации меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*.

### Возвращаемое значение

true, если указанная анимация была успешно импортирована; иначе false.
## bool importSkeleton ( const Ptr < ImportProcessor > & processor , const Ptr < Skeleton > & skeleton , const Ptr < ImportSkeleton > & import_skeleton )

Импортирует указанный скелет и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированного скелета в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте скелетов, при реализации пользовательского импортёра вы можете переопределить метод **[onImportSkeleton()](../../../...md#onImportSkeleton_ImportProcessor_Skeleton_ImportSkeleton_bool)**.

### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Skeleton](../../../../api/library/animations/skeletal/class.skeleton_cpp.md)> &* **skeleton** - Целевой [UNIGINE's skeleton instance](../../../../api/library/animations/skeletal/class.skeleton_cpp.md) для хранения указанного импортированного скелета.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)> &* **import_skeleton** - Экземпляр класса *[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)*.

### Возвращаемое значение

true, если указанный скелет был успешно импортирован; иначе false.
## bool checkSupportedAnimation ( const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation ) const

Возвращает значение, указывающее, поддерживается ли импорт указанной анимации указанного импортированного меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*.

### Возвращаемое значение

true, если импорт указанной анимации указанного импортированного меша поддерживается; иначе false.
## bool checkDefaultAnimation ( const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation ) const

Возвращает значение, указывающее, является ли указанная анимация анимацией по умолчанию для указанного импортированного меша.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*.

### Возвращаемое значение

true, если указанная анимация является анимацией по умолчанию для указанного импортированного меша; иначе false.
## Ptr < Node > importNode ( const Ptr < ImportProcessor > & processor , const Ptr < ImportNode > & import_node )

Импортирует указанный узел и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированного узла в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте узлов, при реализации пользовательского импортёра вы можете переопределить метод **[onImportNode()](../../../...md#onImportNode_ImportProcessor_ImportNode_Node)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node** - Экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*.

### Возвращаемое значение

Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного узла.
## bool importNodeChild ( const Ptr < ImportProcessor > & processor , const Ptr < Node > & node_parent , const Ptr < ImportNode > & import_node_parent , const Ptr < Node > & node_child , const Ptr < ImportNode > & import_node_child )

Импортирует указанный родительский узел с указанным дочерним узлом и использует указанный [processor](../../../../api/library/common/import/class.importprocessor_cpp.md) для обработки и сохранения сгенерированных узлов в соответствующий файл в выходном каталоге, указанном в методе **[import()](../../../...md#import_cstr_bool)**.
> **Notice:** Чтобы настроить действия, выполняемые при импорте узлов, при реализации пользовательского импортёра вы можете переопределить метод **[onImportNodeChild()](../../../...md#onImportNodeChild_ImportProcessor_Node_ImportNode_Node_ImportNode_bool)**.


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_parent** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного родительского узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_parent** - Экземпляр класса [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md) для родительского узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_child** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного дочернего узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_child** - Экземпляр класса [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md) для дочернего узла.

### Возвращаемое значение

true, если указанный родительский узел вместе с указанным дочерним узлом были успешно импортированы; иначе false.
## bool postprocess ( )

Запускает выполнение всех [added](#addPostProcessor_cstr_bool) пост-процессоров. Пост-процессоры могут использоваться для управления файлами, сгенерированными в процессе импорта.
### Возвращаемое значение

true, если пост-обработка завершена успешно.
## bool getBasis ( Importer::Axis up_axis , Importer::Axis front_axis , Math:: dmat4 & ret )

Возвращает матрицу преобразования для базиса, заданного осями.
### Аргументы

- *[Importer::Axis](../../../../api/library/common/import/class.importer_cpp.md#Axis)* **up_axis** - Ось "вверх" базиса.
- *[Importer::Axis](../../../../api/library/common/import/class.importer_cpp.md#Axis)* **front_axis** - Ось "вперёд" базиса.
- *Math::[dmat4](../../../../api/library/math/class.dmat4_cpp.md) &* **ret** - Матрица преобразования для базиса, заданного осями.

### Возвращаемое значение

true, если матрица преобразования для базиса была успешно вычислена; иначе false.
## bool onComputeBoundBox ( const Ptr < ImportMesh > & import_mesh )

Расширяемый метод для пользовательского вычисления ограничивающего прямоугольника.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **import_mesh** - Импортированный меш, для которого требуется вычислить ограничивающий прямоугольник.

### Возвращаемое значение

true, если ограничивающий прямоугольник для указанного меша был успешно вычислен; иначе false.
## bool onInit ( const Ptr < ImportScene > & import_scene , const char * filepath )

Строит и инициализирует импортированную [scene](../../../../api/library/common/import/class.importscene_cpp.md) на основе данных, содержащихся в указанном входном файле.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportScene](../../../../api/library/common/import/class.importscene_cpp.md)> &* **import_scene** - Импортированная сцена (построенная из данных, содержащихся в указанном входном файле).
- *const char ** **filepath** - Путь к импортируемому входному файлу.

### Возвращаемое значение

true, если сцена была успешно инициализирована с использованием данных из указанного входного файла; иначе false.
## bool onImport ( const char * output_path )

Функция-обработчик события импорта. Эта функция вызывается каждый раз при вызове функции *[import()](../../../...md#import_cstr_bool)*. Вы можете задать собственные действия, выполняемые при импорте сцены.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	bool onImport(const char *output_path) override;

/*...*/

};

/*...*/

bool MyCustomImporter::onImport(const char *output_path)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const char ** **output_path** - Выходной путь для сохранения сгенерированных файлов с импортированными данными.

### Возвращаемое значение

true, если операция импорта для указанного выходного пути была успешной; иначе false.
## bool onImportTexture ( const Ptr < ImportProcessor > & processor , const Ptr < ImportTexture > & import_texture )

Функция-обработчик события импорта текстуры. Эта функция вызывается каждый раз при вызове функции *[importTexture()](../../../...md#importTexture_ImportProcessor_ImportTexture_bool)*. Вы можете задать собственные действия, выполняемые при импорте текстуры.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	bool onImportTexture(const ImportProcessorPtr &processor, const ImportTexturePtr &import_texture) override;

/*...*/

};

/*...*/

bool MyCustomImporter::onImportTexture(const ImportProcessorPtr &processor, const ImportTexturePtr &import_texture)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)> &* **import_texture** - Экземпляр класса *[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)*.

### Возвращаемое значение

true, если указанная текстура была успешно импортирована; иначе false.
## bool onImportMaterial ( const Ptr < ImportProcessor > & processor , const Ptr < Material > & material , const Ptr < ImportMaterial > & import_material )

Функция-обработчик события импорта материала. Эта функция вызывается каждый раз при вызове функции **[importMaterial()](../../../...md#importMaterial_ImportProcessor_Material_ImportMaterial_bool)**. Вы можете задать собственные действия, выполняемые при импорте материала.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	bool onImportMaterial(const ImportProcessorPtr &processor, const Unigine::MaterialPtr &material, const ImportMaterialPtr &import_material) override;

/*...*/

};

/*...*/

bool MyCustomImporter::onImportMaterial(const ImportProcessorPtr &processor, const Unigine::MaterialPtr &material, const ImportMaterialPtr &import_material)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Material](../../../../api/library/rendering/class.material_cpp.md)> &* **material** - Целевой [UNIGINE's material instance](../../../../api/library/rendering/class.material_cpp.md) для хранения указанного импортированного материала.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)> &* **import_material** - Экземпляр класса [ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md).

### Возвращаемое значение

true, если указанный материал был успешно импортирован; иначе false.
## Ptr < Light > onImportLight ( const Ptr < ImportProcessor > & processor , const Ptr < ImportLight > & import_light )

Функция-обработчик события импорта источника света. Эта функция вызывается каждый раз при вызове функции **[importLight()](../../../...md#importLight_ImportProcessor_ImportLight_Light)**. Вы можете задать собственные действия, выполняемые при импорте источника света.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	Unigine::LightPtr onImportLight(const ImportProcessorPtr &processor, const ImportLightPtr &import_light) override;

/*...*/

};

/*...*/

Unigine::LightPtr MyCustomImporter::onImportLight(const ImportProcessorPtr &processor, const ImportLightPtr &import_light)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)> &* **import_light** - Экземпляр класса [ImportLight](../../../../api/library/common/import/class.importlight_cpp.md).

### Возвращаемое значение

[UNIGINE's light instance](../../../../api/library/lights/class.light_cpp.md), хранящий указанный импортированный источник света.
## Ptr < Player > onImportCamera ( const Ptr < ImportProcessor > & processor , const Ptr < ImportCamera > & import_camera )

Функция-обработчик события импорта камеры. Эта функция вызывается каждый раз при вызове функции **[importCamera()](../../../...md#importCamera_ImportProcessor_ImportCamera_Player)**. Вы можете задать собственные действия, выполняемые при импорте камеры.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	Unigine::PlayerPtr onImportCamera(const ImportProcessorPtr &processor, const ImportCameraPtr &import_camera) override;

/*...*/

};

/*...*/

Unigine::PlayerPtr MyCustomImporter::onImportCamera(const ImportProcessorPtr &processor, const ImportCameraPtr &import_camera)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)> &* **import_camera** - Экземпляр класса [ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md).

### Возвращаемое значение

[UNIGINE's player instance](../../../../api/library/players/class.player_cpp.md), хранящий указанную импортированную камеру.
## bool onImportMesh ( const Ptr < ImportProcessor > & processor , const Ptr < Mesh > & mesh , const Ptr < ImportMesh > & import_mesh )

Функция-обработчик события импорта меша. Эта функция вызывается каждый раз при вызове функции **[importMesh()](../../../...md#importMesh_ImportProcessor_Mesh_ImportMesh_bool)**. Вы можете задать собственные действия, выполняемые при импорте меша.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	bool onImportMesh(const ImportProcessorPtr &processor, const Unigine::MeshPtr &mesh, const ImportMeshPtr &import_mesh) override;

/*...*/

};

/*...*/

bool MyCustomImporter::onImportMesh(const ImportProcessorPtr &, const Unigine::MeshPtr &mesh, const ImportMeshPtr &import_mesh)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Целевой [UNIGINE's mesh instance](../../../../api/library/rendering/class.mesh_cpp.md) для хранения указанного импортированного меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **import_mesh** - Экземпляр класса [ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md).

### Возвращаемое значение

true, если указанный меш был успешно импортирован; иначе false.
## bool onImportMeshSkinned ( const Ptr < ImportProcessor > & processor , const Ptr < MeshSkinned > & mesh_skinned , const Ptr < ImportMeshSkinned > & import_mesh_skinned )

Функция-обработчик события импорта скинового меша. Эта функция вызывается каждый раз при вызове функции **[importMeshSkinned()](../../../...md#importMeshSkinned_ImportProcessor_MeshSkinned_ImportMeshSkinned_bool)**. Вы можете задать собственные действия, выполняемые при импорте скинового меша.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	bool onImportMeshSkinned(const ImportProcessorPtr &processor, const Unigine::MeshSkinnedPtr &mesh_skinned, const ImportMeshSkinnedPtr &import_mesh_skinned) override;

/*...*/

};

/*...*/

bool MyCustomImporter::onImportMeshSkinned(const ImportProcessorPtr &processor, const Unigine::MeshSkinnedPtr &mesh_skinned, const ImportMeshSkinnedPtr &import_mesh_skinned)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinned](../../../../api/library/rendering/class.meshskinned_cpp.md)> &* **mesh_skinned** - Целевой [UNIGINE's skinned mesh instance](../../../../api/library/rendering/class.meshskinned_cpp.md) для хранения указанного импортированного скинового меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Экземпляр класса [ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md).

### Возвращаемое значение

true, если указанный скиновый меш был успешно импортирован; иначе false.
## Ptr < Node > onImportNode ( const Ptr < ImportProcessor > & processor , const Ptr < ImportNode > & import_node )

Функция-обработчик события импорта узла. Эта функция вызывается каждый раз при вызове функции **[importNode()](../../../...md#importNode_ImportProcessor_ImportNode_Node)**. Вы можете задать собственные действия, выполняемые при импорте узла.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	Unigine::NodePtr onImportNode(const ImportProcessorPtr &processor, const ImportNodePtr &import_node) override;

/*...*/

};

/*...*/

Unigine::NodePtr MyCustomImporter::onImportNode(const ImportProcessorPtr &processor, const ImportNodePtr &import_node)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node** - Экземпляр класса [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md).

### Возвращаемое значение

[UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md), хранящий указанный импортированный узел.
## bool onImportNodeChild ( const Ptr < ImportProcessor > & processor , const Ptr < Node > & node_parent , const Ptr < ImportNode > & import_node_parent , const Ptr < Node > & node_child , const Ptr < ImportNode > & import_node_child )

Функция-обработчик события импорта узла. Эта функция вызывается каждый раз при вызове функции **[importNodeChild()](../../../...md#importNodeChild_ImportProcessor_Node_ImportNode_Node_ImportNode_bool)**. Вы можете задать собственные действия, выполняемые при импорте и обработке иерархий узлов (например, присвоение свойств дочерним узлам).
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	bool onImportNodeChild(const ImportProcessorPtr &processor, const Unigine::NodePtr &node_parent, const ImportNodePtr &import_node_parent, const Unigine::NodePtr &node_child, const ImportNodePtr &import_node_child) override;

/*...*/

};

/*...*/

bool MyCustomImporter::onImportNodeChild(const ImportProcessorPtr &processor, const Unigine::NodePtr &node_parent, const ImportNodePtr &import_node_parent, const Unigine::NodePtr &node_child, const ImportNodePtr &import_node_child)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_parent** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного родительского узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_parent** - Экземпляр класса [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md) для родительского узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Node](../../../../api/library/nodes/class.node_cpp.md)> &* **node_child** - Целевой [UNIGINE's node instance](../../../../api/library/nodes/class.node_cpp.md) для хранения указанного импортированного дочернего узла.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **import_node_child** - Экземпляр класса [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md) для дочернего узла.

### Возвращаемое значение

true, если указанный родительский узел и анимация его дочернего узла были успешно импортированы; иначе false.
## bool onImportAnimation ( const Ptr < ImportProcessor > & processor , const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportAnimation > & import_animation )

Функция-обработчик события импорта анимации. Эта функция вызывается каждый раз при вызове функции *[importAnimation()](../../../...md#importAnimation_ImportProcessor_MeshSkinnedAnimation_ImportAnimation_bool)*. Вы можете задать собственные действия, выполняемые при импорте анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - Целевой [UNIGINE's mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md) для хранения указанной импортированной анимации меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Указатель на [ImportAnimation structure](../../../../api/library/common/import/class.importanimation_cpp.md). Метаданные анимации, которую требуется импортировать.

### Возвращаемое значение

true, если указанная анимация меша была успешно импортирована; иначе false.
## bool onImportAnimation ( const Ptr < ImportProcessor > & processor , const Ptr < MeshSkinnedAnimation > & animation , const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation )

Функция-обработчик события импорта анимации. Эта функция вызывается каждый раз при вызове функции *[importAnimation()](../../../...md#importAnimation_ImportProcessor_MeshSkinnedAnimation_ImportMeshSkinned_ImportAnimation_bool)*. Вы можете задать собственные действия, выполняемые при импорте анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[MeshSkinnedAnimation](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md)> &* **animation** - Целевой [UNIGINE's mesh animation instance](../../../../api/library/rendering/class.meshskinnedanimation_cpp.md) для хранения указанной импортированной анимации меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Указатель на [ImportMeshSkinned structure](../../../../api/library/common/import/class.importmeshskinned_cpp.md). Метаданные скинового меша, который требуется импортировать.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Указатель на [ImportAnimation structure](../../../../api/library/common/import/class.importanimation_cpp.md). Метаданные анимации, которую требуется импортировать.

### Возвращаемое значение

true, если указанная анимация меша была успешно импортирована; иначе false.
## bool onImportSkeleton ( const Ptr < ImportProcessor > & processor , const Ptr < Skeleton > & skeleton , const Ptr < ImportSkeleton > & import_skeleton )

Функция-обработчик события импорта скелета. Эта функция вызывается каждый раз при вызове функции **[importSkeleton()](../../../...md#importSkeleton_ImportProcessor_Skeleton_ImportSkeleton_bool)**. Вы можете задать собственные действия, выполняемые при импорте скелета.
```cpp
class MyCustomImporter : public Unigine::Importer
{
public:
	MyCustomImporter();
	virtual ~MyCustomImporter();

/*...*/

// переопределения функций событий
protected:
	bool onImportSkeleton(const ImportProcessorPtr &processor, const Unigine::SkeletonPtr &skeleton, const ImportSkeletonPtr &import_skeleton) override;

/*...*/

};

/*...*/

bool MyCustomImporter::onImportSkeleton(const ImportProcessorPtr &processor, const Unigine::SkeletonPtr &skeleton, const ImportSkeletonPtr &import_skeleton)
{
	bool result = false;

	// ваши пользовательские действия

	return result;
}

```


### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md)> &* **processor** - [Import processor](../../../../api/library/common/import/class.importprocessor_cpp.md), используемый для этой операции импорта.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Skeleton](../../../../api/library/animations/skeletal/class.skeleton_cpp.md)> &* **skeleton** - Целевой [UNIGINE's skeleton instance](../../../../api/library/animations/skeletal/class.skeleton_cpp.md) для хранения указанного импортированного скелета.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)> &* **import_skeleton** - Экземпляр класса [ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md).

### Возвращаемое значение

true, если указанный скелет был успешно импортирован; иначе false.
## bool onCheckSupportedAnimation ( const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation ) const

Функция-обработчик события проверки поддержки импорта анимации. Эта функция вызывается каждый раз при вызове функции *[checkSupportedAnimation()](../../../...md#checkSupportedAnimation_ImportMeshSkinned_ImportAnimation_bool)*. Вы можете задать собственные действия, выполняемые при импорте анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Указатель на [ImportMeshSkinned structure](../../../../api/library/common/import/class.importmeshskinned_cpp.md). Метаданные импортированного скинового меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Указатель на [ImportAnimation structure](../../../../api/library/common/import/class.importanimation_cpp.md). Метаданные импортированной анимации.

### Возвращаемое значение

true, если импорт указанной анимации меша поддерживается; иначе false.
## bool onCheckDefaultAnimation ( const Ptr < ImportMeshSkinned > & import_mesh_skinned , const Ptr < ImportAnimation > & import_animation ) const

Функция-обработчик события проверки анимации по умолчанию. Эта функция вызывается каждый раз при вызове функции *[checkDefaultAnimation()](../../../...md#checkDefaultAnimation_ImportMeshSkinned_ImportAnimation_bool)*. Вы можете задать собственные действия, выполняемые при импорте анимации.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **import_mesh_skinned** - Указатель на [ImportMeshSkinned structure](../../../../api/library/common/import/class.importmeshskinned_cpp.md). Метаданные импортированного скинового меша.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **import_animation** - Указатель на [ImportAnimation structure](../../../../api/library/common/import/class.importanimation_cpp.md). Метаданные импортированной анимации.

### Возвращаемое значение

true, если указанная анимация меша является анимацией по умолчанию для импортированного меша; иначе false.
