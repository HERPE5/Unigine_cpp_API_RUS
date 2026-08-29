# Unigine::ImportScene Class (CPP)

**Header:** #include <UnigineImport.h>


Этот класс является контейнером верхнего уровня для всех данных, извлечённых из исходного файла во время импорта. Он управляет графом сцены (иерархией элементов [ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)) и параллельными коллекциями компонентов сцены. Во время импорта [Importer](../../../../api/library/common/import/class.importer_cpp.md) заполняет ImportScene, а затем [ImportProcessor](../../../../api/library/common/import/class.importprocessor_cpp.md) преобразует её содержимое в ассеты UNIGINE.


Сцена может включать следующие компоненты:


- [animations](../../../../api/library/common/import/class.importanimation_cpp.md)
- [cameras](../../../../api/library/common/import/class.importcamera_cpp.md)
- [lights](../../../../api/library/common/import/class.importlight_cpp.md)
- [meshes](../../../../api/library/common/import/class.importmesh_cpp.md)
- [skinned meshes](../../../../api/library/common/import/class.importmeshskinned_cpp.md)
- [nodes](../../../../api/library/common/import/class.importnode_cpp.md)
- [skeletons](../../../../api/library/common/import/class.importskeleton_cpp.md)
- [materials](../../../../api/library/common/import/class.importmaterial_cpp.md)
- [textures](../../../../api/library/common/import/class.importtexture_cpp.md)


## ImportScene Class

### Методы класса

---

## static ImportScenePtr create ( )

Конструктор. Создаёт пустой экземпляр импортируемой сцены.
## int getNumNodes ( ) const

Возвращает общее количество узлов в импортированной сцене.
### Возвращаемое значение

Количество узлов в импортированной сцене.
## Ptr < ImportNode > getNode ( int i ) const

Возвращает узел, содержащийся в импортированной сцене, по его индексу.
### Аргументы

- *int* **i** - Индекс узла сцены в диапазоне от 0 до ([total number of nodes in the scene](#getNumNodes_int) - 1).

### Возвращаемое значение

Узел сцены с указанным индексом (экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*, если он существует).
## Ptr < ImportNode > addNode ( const Ptr < ImportNode > & parent )

Добавляет новый узел в качестве атрибута к указанному узлу графа сцены и возвращает соответствующий экземпляр *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **parent** - Узел графа сцены, к которому добавляется новый узел.

### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)*.
## bool removeNode ( const Ptr < ImportNode > & node )

Удаляет указанный узел графа сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Удаляемый узел графа сцены.

### Возвращаемое значение

true, если указанный узел графа сцены был успешно удалён из сцены; иначе false.
## int getNumMeshes ( ) const

Возвращает общее количество мешей в импортированной сцене.
### Возвращаемое значение

Количество мешей в импортированной сцене.
## Ptr < ImportMesh > getMesh ( int i ) const

Возвращает меш, содержащийся в импортированной сцене, по его индексу.
### Аргументы

- *int* **i** - Индекс меша в диапазоне от 0 до ([total number of meshes in the scene](#getNumMeshes_int) - 1).

### Возвращаемое значение

Меш с указанным индексом (экземпляр класса *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*, если он существует).
## Ptr < ImportMesh > addMesh ( const Ptr < ImportNode > & node )

Добавляет новый меш в качестве атрибута к указанному импортированному узлу и возвращает соответствующий экземпляр *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел графа сцены, к которому добавляется новый меш.

### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)*.
## void removeMesh ( const Ptr < ImportMesh > & mesh )

Удаляет указанный меш из списка мешей импортированной сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMesh](../../../../api/library/common/import/class.importmesh_cpp.md)> &* **mesh** - Удаляемый меш.

## int getNumMeshSkinneds ( ) const

Возвращает общее количество скиновых мешей в импортированной сцене.
### Возвращаемое значение

Количество скиновых мешей в импортированной сцене.
## Ptr < ImportMeshSkinned > getMeshSkinned ( int i ) const

Возвращает скиновый меш, содержащийся в импортированной сцене, по его индексу.
### Аргументы

- *int* **i** - Индекс скинового меша в диапазоне от 0 до ([total number of skinned meshes in the scene](#getNumMeshSkinneds_int) - 1).

### Возвращаемое значение

Скиновый меш с указанным индексом (экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*, если он существует).
## Ptr < ImportMeshSkinned > addMeshSkinned ( const Ptr < ImportNode > & node )

Добавляет новый скиновый меш в качестве атрибута к указанному импортированному узлу и возвращает соответствующий экземпляр *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел графа сцены, к которому добавляется новый скиновый меш.

### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)*.
## void removeMeshSkinned ( const Ptr < ImportMeshSkinned > & mesh_skinned )

Удаляет указанный скиновый меш из списка скиновых мешей импортированной сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMeshSkinned](../../../../api/library/common/import/class.importmeshskinned_cpp.md)> &* **mesh_skinned** - Удаляемый скиновый меш.

## int getNumLights ( ) const

Возвращает общее количество источников света в импортированной сцене.
### Возвращаемое значение

Количество источников света в импортированной сцене.
## Ptr < ImportLight > getLight ( int i ) const

Возвращает источник света, содержащийся в импортированной сцене, по его индексу.
### Аргументы

- *int* **i** - Индекс источника света в диапазоне от 0 до ([total number of lights in the scene](#getNumLights_int) - 1).

### Возвращаемое значение

Источник света с указанным индексом (экземпляр класса *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*, если он существует).
## Ptr < ImportLight > addLight ( const Ptr < ImportNode > & node )

Добавляет новый источник света в качестве атрибута к указанному импортированному узлу и возвращает соответствующий экземпляр *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел графа сцены, к которому добавляется источник света.

### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)*.
## void removeLight ( const Ptr < ImportLight > & light )

Удаляет указанный источник света из списка источников света импортированной сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportLight](../../../../api/library/common/import/class.importlight_cpp.md)> &* **light** - Удаляемый источник света.

## int getNumCameras ( ) const

Возвращает общее количество камер в импортированной сцене.
### Возвращаемое значение

Количество камер в импортированной сцене.
## Ptr < ImportCamera > getCamera ( int i ) const

Возвращает камеру, содержащуюся в импортированной сцене, по её индексу.
### Аргументы

- *int* **i** - Индекс камеры в диапазоне от 0 до ([total number of cameras in the scene](#getNumCameras_int) - 1).

### Возвращаемое значение

Камера с указанным индексом (экземпляр класса *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*, если он существует).
## Ptr < ImportCamera > addCamera ( const Ptr < ImportNode > & node )

Добавляет новую камеру в качестве атрибута к указанному импортированному узлу и возвращает соответствующий экземпляр *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportNode](../../../../api/library/common/import/class.importnode_cpp.md)> &* **node** - Узел графа сцены, к которому добавляется новая камера.

### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)*.
## void removeCamera ( const Ptr < ImportCamera > & camera )

Удаляет указанную камеру из сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportCamera](../../../../api/library/common/import/class.importcamera_cpp.md)> &* **camera** - Удаляемая камера.

## int getNumAnimations ( ) const

Возвращает общее количество анимаций в импортированной сцене.
### Возвращаемое значение

Количество анимаций в импортированной сцене.
## Ptr < ImportAnimation > getAnimation ( int i ) const

Возвращает анимацию, содержащуюся в импортированной сцене, по её индексу.
### Аргументы

- *int* **i** - Индекс анимации в диапазоне от 0 до ([total number of animations in the scene](#getNumAnimations_int) - 1).

### Возвращаемое значение

Анимация с указанным индексом (экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*, если он существует).
## Ptr < ImportAnimation > addAnimation ( )

Добавляет указанную анимацию в сцену и возвращает экземпляр добавленной анимации.
### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)*.
## void removeAnimation ( const Ptr < ImportAnimation > & animation )

Удаляет указанную анимацию из сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportAnimation](../../../../api/library/common/import/class.importanimation_cpp.md)> &* **animation** - Удаляемая анимация.

## int getNumSkeletons ( ) const

Возвращает общее количество скелетов в импортированной сцене.
### Возвращаемое значение

Количество скелетов в импортированной сцене.
## Ptr < ImportSkeleton > getSkeleton ( int i ) const

Возвращает скелет, содержащийся в импортированной сцене, по его индексу.
### Аргументы

- *int* **i** - Индекс скелета в диапазоне от 0 до ([total number of skeletons in the scene](#getNumSkeletons_int) - 1).

### Возвращаемое значение

Скелет с указанным индексом (экземпляр класса *[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)*, если он существует).
## Ptr < ImportSkeleton > addSkeleton ( )

Добавляет новый скелет в сцену и возвращает соответствующий экземпляр *[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)*.
### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)*.
## void removeSkeleton ( const Ptr < ImportSkeleton > & skeleton )

Удаляет указанный скелет из сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportSkeleton](../../../../api/library/common/import/class.importskeleton_cpp.md)> &* **skeleton** - Удаляемый скелет.

## int getNumMaterials ( ) const

Возвращает общее количество материалов в импортированной сцене.
### Возвращаемое значение

Количество материалов в импортированной сцене.
## Ptr < ImportMaterial > getMaterial ( int i ) const

Возвращает материал, содержащийся в импортированной сцене, по его индексу.
### Аргументы

- *int* **i** - Индекс материала в диапазоне от 0 до ([total number of materials in the scene](#getNumMaterials_int) - 1).

### Возвращаемое значение

Материал с указанным индексом (экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*, если он существует).
## Ptr < ImportMaterial > addMaterial ( )

Добавляет указанный материал в сцену и возвращает экземпляр добавленного материала.
### Возвращаемое значение

Новый добавленный экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*.
## Ptr < ImportMaterial > getMaterial ( const char * name ) const

Возвращает материал, содержащийся в импортированной сцене, по его имени.
### Аргументы

- *const char ** **name** - Имя материала.

### Возвращаемое значение

Материал с указанным именем (экземпляр класса *[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)*, если он существует).
## void replaceMaterial ( const Ptr < ImportMaterial > & old_material , const Ptr < ImportMaterial > & new_material )

Заменяет указанный материал, содержащийся в импортированной сцене, другим.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)> &* **old_material** - Заменяемый материал.
- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)> &* **new_material** - Новый материал, заменяющий исходный.

## void removeMaterial ( const Ptr < ImportMaterial > & material )

Удаляет указанный материал из сцены.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[ImportMaterial](../../../../api/library/common/import/class.importmaterial_cpp.md)> &* **material** - Удаляемый материал.

## int getNumTextures ( ) const

Возвращает общее количество текстур в импортированной сцене.
### Возвращаемое значение

Количество текстур в импортированной сцене.
## Ptr < ImportTexture > getTexture ( int i ) const

Возвращает текстуру, содержащуюся в импортированной сцене, по её индексу.
### Аргументы

- *int* **i** - Индекс текстуры в диапазоне от 0 до ([total number of textures in the scene](#getNumTextures_int) - 1).

### Возвращаемое значение

Текстура с указанным индексом (экземпляр класса *[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)*, если он существует).
## Ptr < ImportTexture > getTexture ( const char * filepath )

Возвращает текстуру, содержащуюся в импортированной сцене, по её пути к файлу.
### Аргументы

- *const char ** **filepath** - Путь к файлу текстуры.

### Возвращаемое значение

Текстура с указанным путём к файлу (экземпляр класса *[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)*, если он существует).
## Ptr < ImportTexture > findTexture ( const char * filepath ) const

Возвращает текстуру, содержащуюся в импортированной сцене, по её пути к файлу.
### Аргументы

- *const char ** **filepath** - Путь к файлу текстуры.

### Возвращаемое значение

Текстура с указанным путём к файлу (экземпляр класса *[ImportTexture](../../../../api/library/common/import/class.importtexture_cpp.md)*, если он существует).
