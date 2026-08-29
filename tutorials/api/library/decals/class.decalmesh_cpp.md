# Класс Unigine.DecalMesh (CPP)

**Заголовочный файл:** #include <UnigineDecals.h>

**Наследуется от:** Decal


Этот класс описывает, как создавать и изменять [mesh decals](../../../objects/decals/mesh/index.md).


### Создание Mesh Decal


Следующий код иллюстрирует, как создать mesh decal, задать его параметры и добавить узел в UnigineEditor.


```cpp
// AppWorldLogic.h

#include <UnigineLogic.h>
#include <UnigineObjects.h>
#include <UnigineEditor.h>
#include <UnigineDecals.h>

class AppWorldLogic : public Unigine::WorldLogic {

public:
	AppWorldLogic();
	virtual ~AppWorldLogic();

	virtual int init();

	virtual int update();
	virtual int postUpdate();
	virtual int updatePhysics();

	virtual int shutdown();

	virtual int save(const Unigine::StreamPtr &stream);
	virtual int restore(const Unigine::StreamPtr &stream);

private:
	Unigine::DecalMeshPtr decal_mesh;
};

```


```cpp
// AppWorldLogic.cpp

#include "AppWorldLogic.h";

using namespace Unigine;

int AppWorldLogic::init()
{
	// create a mesh with a surface (e.g. a box primitive)
	MeshPtr mesh = Mesh::create();
	mesh->addBoxSurface("box_0", Math::vec3(1.0f));

	// create a mesh decal using created mesh and setting its radius to 10, material to "decal_base_0"
	decal_mesh = DecalMesh::create();
	decal_mesh->setMesh(mesh);
	decal_mesh->setRadius(10.0f);
	decal_mesh->setMaterialPath("decal_base_0.mat");

	// set the name and position of the decal
	decal_mesh->setName("Mesh Decal");
	decal_mesh->setWorldPosition(Math::Vec3(0.0f, 0.0f, 5.0f));

	return 1;
}

```


## Класс DecalMesh

### Методы класса

---

## static DecalMeshPtr create ( )

Конструктор. Создаёт новый *Mesh Decal*.
## static DecalMeshPtr create ( const char * path )

Конструктор DecalMesh. Создаёт *Mesh Decal* с исходным мэшем, загруженным из указанного файла.
### Аргументы

- *const char ** **path** - Путь к файлу исходного мэша.

## void setMeshPath ( const char * path )

Устанавливает новый путь к исходному мэшу для текущей mesh-декали. Если мэш находится в процедурном режиме, он будет сброшен.
> **Notice:** Мэш должен содержать одну поверхность. Если мэш содержит несколько поверхностей, будет использована только поверхность с индексом 0. Таким образом, область декали будет отличаться от исходного мэша.


### Аргументы

- *const char ** **path** - Новый путь к исходному файлу *.mesh*, который нужно установить.

## const char * getMeshPath ( ) const

Возвращает путь к исходному файлу *.mesh*, используемому в данный момент для декали.
### Возвращаемое значение

Путь к исходному файлу *.mesh*.
## static int type ( )

Возвращает идентификатор типа DecalMesh.
### Возвращаемое значение

Идентификатор типа.
## Ptr<ConstMesh> getMeshCurrentRAM ( ) const

 Возвращает текущий исходный мэш, используемый объектом и загруженный в память (RAM).
### Возвращаемое значение

Текущий исходный мэш, используемый объектом.
## Ptr < MeshRender > getMeshCurrentVRAM ( )

Возвращает текущий рендер-мэш, используемый объектом и загруженный в видеопамять (VRAM).
### Возвращаемое значение

Текущий рендер-мэш, используемый объектом.
## Ptr<ConstMesh> getMeshForceRAM ( )

Возвращает исходный мэш, используемый объектом, и немедленно загружает его в память (RAM).
### Возвращаемое значение

Исходный мэш, используемый объектом.
## Ptr < MeshRender > getMeshForceVRAM ( )

Возвращает рендер-мэш, используемый объектом, и немедленно загружает его в видеопамять (VRAM). При этом статический мэш также будет загружен в память (RAM).
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

Рендер-мэш, используемый объектом.
## Ptr<ConstMesh> getMeshAsyncRAM ( )

Возвращает исходный мэш, используемый объектом, и загружает его в память (RAM) асинхронно.
### Возвращаемое значение

Исходный мэш, используемый объектом.
## Ptr < MeshRender > getMeshAsyncVRAM ( )

**[ Main Thread ]**Возвращает рендер-мэш, используемый объектом, и загружает его в видеопамять (VRAM) асинхронно. При этом статический мэш также будет загружен в память (RAM).
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

Рендер-мэш, используемый объектом.
## Ptr < Mesh > getMeshDynamicRAM ( )

Возвращает процедурный исходный мэш, связанный с объектом, и обеспечивает его загрузку в системную память (RAM). Этот метод доступен только когда мэш находится в **динамическом** (*[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*) режиме. *Процедурный мэш* — это мэш, созданный через код и использующий особый режим стриминга. В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* объект остаётся в памяти после создания и выгружается только вручную с помощью *[deleteDynamicMesh()](../../../api/library/objects/class.objectmeshstatic_cpp.md#deleteDynamicMesh_int)* или при изменении процедурного режима.
> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

Процедурный исходный мэш, используемый объектом.
## Ptr < MeshRender > getMeshDynamicVRAM ( )

Возвращает процедурный рендер-мэш, связанный с объектом, и обеспечивает его загрузку в видеопамять (VRAM). Этот метод доступен только когда мэш находится в **динамическом** (*[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*) режиме. *Процедурный мэш* — это мэш, созданный через код и использующий особый режим стриминга. В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* объект остаётся в памяти после создания и выгружается только вручную с помощью *[deleteDynamicMesh()](../../../api/library/objects/class.objectmeshstatic_cpp.md#deleteDynamicMesh_int)* или при изменении процедурного режима.
> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

Процедурный рендер-мэш, используемый объектом.
## bool loadAsyncVRAM ( )

**[ Main Thread ]**Асинхронно загружает мэш в видеопамять (VRAM), если включён [async streaming mode for meshes](../../../api/library/rendering/class.render_cpp.md#STREAMING_MODE). В противном случае выполняется [forced](#loadForceVRAM_bool) загрузка. Этот метод рекомендуется использовать для реализации собственной системы предзагрузки (т.е. асинхронной предварительной загрузки мэшей в видеопамять до их использования).
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

true, если мэш загружен успешно, иначе false. Если мэш уже загружен в VRAM, будет возвращено true.
## bool loadAsyncRAM ( )

Асинхронно загружает мэш в память (RAM), если включён [async streaming mode for meshes](../../../api/library/rendering/class.render_cpp.md#STREAMING_MODE). В противном случае выполняется [forced](#loadForceRAM_bool) загрузка. Этот метод рекомендуется использовать для реализации собственной системы предзагрузки (т.е. асинхронной предварительной загрузки мэшей в видеопамять до их использования).
### Возвращаемое значение

true, если мэш загружен успешно, иначе false. Если мэш уже загружен в RAM, будет возвращено true.
## bool loadForceVRAM ( )

Выполняет немедленную принудительную загрузку мэша в видеопамять (VRAM). Принудительная загрузка в VRAM выполняется в главном потоке.
> **Notice:** Загрузка в VRAM должна выполняться только в главном потоке.


### Возвращаемое значение

true, если мэш загружен успешно, иначе false. Если мэш уже загружен в VRAM, будет возвращено true.
## bool loadForceRAM ( )

Выполняет немедленную принудительную загрузку мэша в память (RAM).
### Возвращаемое значение

true, если мэш загружен успешно, иначе false. Если мэш уже загружен в RAM, будет возвращено true.
## void setMeshProceduralMode ( ObjectMeshStatic::PROCEDURAL_MODE mode , int mesh_render_flags = 0 )

Устанавливает процедурный режим для мэша. Указанный режим определяет, как процедурные данные хранятся, обновляются и выгружаются.
> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[ObjectMeshStatic::PROCEDURAL_MODE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE)* **mode** - Один из режимов *[PROCEDURAL_MODE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE)*, применяемый к мэшу.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX), управляющие тем, как хранятся данные вершин и индексов для рендер-мэша.

## ObjectMeshStatic::PROCEDURAL_MODE getMeshProceduralMode ( ) const

Возвращает значение, указывающее, какой процедурный режим назначен мэшу. Значение соответствует одному из доступных типов *[PROCEDURAL_MODE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE)*, определяющих, как процедурные данные хранятся, обновляются и выгружаются.
> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

Текущий процедурный режим мэша.
## bool isMeshNull ( ) const

Возвращает значение, указывающее, является ли исходный мэш, используемый объектом, пустым (не существует, не назначен, не загружен и т.д.).
### Возвращаемое значение

true, если исходный мэш, используемый объектом, пуст; иначе false.
## bool isMeshLoadedRAM ( ) const

Возвращает значение, указывающее, загружен ли исходный мэш, используемый объектом, в память (RAM).
### Возвращаемое значение

true, если исходный мэш, используемый объектом, загружен в RAM; иначе false.
## bool isMeshLoadedVRAM ( ) const

Возвращает значение, указывающее, загружен ли исходный мэш, используемый объектом, в видеопамять (VRAM).
### Возвращаемое значение

true, если исходный мэш, используемый объектом, загружен в VRAM; иначе false.
## int getStatDrawCalls ( ) const

Возвращает количество вызовов отрисовки (DIP) для декали за последний кадр.
### Возвращаемое значение

Количество вызовов отрисовки (DIP) для декали за последний кадр.
## int getStatDrawCountViewport ( ) const

Возвращает количество раз, когда декаль была отрисована во вьюпорте за последний кадр.
### Возвращаемое значение

Количество раз, когда декаль была отрисована во вьюпорте за последний кадр.
## int getStatDrawCountReflection ( ) const

Возвращает количество раз, когда декаль была отрисована во время рендеринга отражений за последний кадр.
### Возвращаемое значение

Количество раз, когда декаль была отрисована во время рендеринга за последний кадр.
## int getStatDrawCountShadow ( ) const

Возвращает количество раз, когда декаль была отрисована во время рендеринга теней за последний кадр.
### Возвращаемое значение

Количество раз, когда декаль была отрисована во время рендеринга теней за последний кадр.
## long long getStatFrame ( ) const

Возвращает номер [Engine frame](../../../api/library/engine/class.engine_cpp.md#getFrame_int64_t), в котором декаль была отрисована в последний раз.
### Возвращаемое значение

Номер кадра, в котором декаль была отрисована в последний раз.
## Ptr < Mesh > createCopyMeshRAM ( ) const

Создаёт и возвращает копию исходного мэша, используемого объектом, загружая его напрямую с диска, если он отсутствует в кэше. Этот метод не выполняет стриминг скопированного мэша в кэш памяти, что снижает использование RAM.
### Возвращаемое значение

Копия исходного мэша, или nullptr, если исходный мэш отсутствует в RAM или путь к его файлу недействителен.
## bool getCopyMeshRAM ( Ptr < Mesh > & result ) const

Извлекает копию исходного мэша, используемого объектом, и записывает её в предоставленный объект мэша. Если мэш отсутствует в кэше, он загружается напрямую с диска. Этот метод не выполняет стриминг скопированного мэша в кэш памяти, что снижает использование RAM.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **result** - Объект, который получит копию исходного мэша.

### Возвращаемое значение

true, если мэш скопирован успешно, false, если исходный мэш отсутствует в RAM или путь к его файлу недействителен.
## bool isMeshProceduralDone ( ) const

Возвращает значение, указывающее, завершены ли все асинхронные операции над процедурным мэшем.
> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если ни одна асинхронная операция с геометрией не активна, иначе false.
## bool isMeshProceduralActive ( ) const

Возвращает значение, указывающее, выполняется ли в данный момент асинхронная операция над процедурным мэшем.
> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если асинхронная операция с геометрией активна, иначе false.
## bool isMeshProceduralDynamic ( ) const

Возвращает значение, указывающее, является ли текущий процедурный режим *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*.
> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если активен *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*, иначе false.
## bool applyCopyMeshProceduralForce ( const Ptr<ConstMesh> & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Копирует все данные вершин из заданного мэша в процедурный мэш объекта принудительно, выполняя операцию немедленно. Работает только когда **процедурный режим включён**.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[const Ptr<ConstMesh> &](#ConstMeshPtr)* **mesh** - Исходный мэш, из которого копируются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если мэш скопирован успешно, иначе false.
## bool applyMoveMeshProceduralForce ( const Ptr < Mesh > & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Перемещает все данные вершин из заданного мэша в процедурный мэш объекта принудительно, выполняя операцию немедленно без выделения памяти и копирования данных (семантика перемещения). Работает только когда **процедурный режим включён**.


В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* этот метод ведёт себя идентично своему асинхронному варианту.


Эта операция **обменивает данные мэша объекта с заданным мэшем**. При повторном использовании того же объекта мэша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Исходный мэш, из которого перемещаются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если мэш перемещён (перенесён без копирования) успешно, иначе false.
## bool applyMoveMeshProceduralForce ( const Ptr < Mesh > & mesh_ram , const Ptr < MeshRender > & mesh_vram )

**[ Main Thread ]**
Перемещает все данные вершин и рендеринга из заданных *mesh_ram* и *mesh_vram* в процедурный мэш объекта принудительно, выполняя операцию немедленно с использованием семантики перемещения, без копирования данных или выделения VRAM. Работает только когда **процедурный режим включён**.


Эта операция **обменивает данные мэша объекта с заданным мэшем**. При повторном использовании того же объекта мэша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh_ram** - Исходный мэш, содержащий данные вершин.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)> &* **mesh_vram** - Исходный мэш, содержащий данные рендеринга.

### Возвращаемое значение

true, если данные перемещены (перенесены без копирования) успешно, иначе false.
## bool applyCopyMeshProceduralAsync ( const Ptr<ConstMesh> & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Копирует все данные вершин из заданного мэша в процедурный мэш объекта асинхронно. Операция не является принудительной и выполняется в фоновом режиме без заметной задержки. Работает только когда **процедурный режим включён**.


В режимах *[PROCEDURAL_MODE_FILE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_FILE)* и *[PROCEDURAL_MODE_BLOB](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_BLOB)* этот метод работает быстрее по сравнению с принудительным вариантом, так как запись файлов и операции с памятью выполняются в фоновых потоках.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[const Ptr<ConstMesh> &](#ConstMeshPtr)* **mesh** - Исходный мэш, из которого копируются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если мэш скопирован успешно, иначе false.
## bool applyMoveMeshProceduralAsync ( const Ptr < Mesh > & mesh , int mesh_render_flags = 0 )

**[ Main Thread ]**
Перемещает все данные вершин из заданного мэша в процедурный мэш объекта асинхронно. Операция не является принудительной и выполняется в фоновом режиме без заметной задержки, без выделения памяти и копирования данных (семантика перемещения). Работает только когда **процедурный режим включён**.


В режимах *[PROCEDURAL_MODE_FILE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_FILE)* и *[PROCEDURAL_MODE_BLOB](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_BLOB)* этот метод работает быстрее по сравнению с принудительным вариантом, так как запись файлов и операции с памятью выполняются в фоновых потоках.


Эта операция **обменивает данные мэша объекта с заданным мэшем**. При повторном использовании того же объекта мэша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh** - Исходный мэш, из которого копируются данные вершин.
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

## bool applyMoveMeshProceduralAsync ( const Ptr < Mesh > & mesh_ram , const Ptr < MeshRender > & mesh_vram )

**[ Main Thread ]**
Перемещает все данные вершин и рендеринга из заданных mesh_ram и mesh_vram в процедурный мэш объекта асинхронно, без копирования или выделения VRAM. Операция не является принудительной и выполняется в фоновом режиме без заметной задержки. Работает только когда **процедурный режим включён**.


В режимах *[PROCEDURAL_MODE_FILE](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_FILE)* и *[PROCEDURAL_MODE_BLOB](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_BLOB)* этот метод работает быстрее, так как запись файлов и операции с памятью выполняются в фоновых потоках.


В режиме *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)* этот метод ведёт себя идентично своему принудительному варианту.


Эта операция **обменивает данные мэша объекта с заданным мэшем**. При повторном использовании того же объекта мэша для дальнейшей генерации данных убедитесь, что его внутреннее состояние (например, количество поверхностей) корректно.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)> &* **mesh_ram** - Исходный мэш, содержащий данные вершин.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)> &* **mesh_vram** - Исходный мэш, содержащий данные рендеринга.

### Возвращаемое значение

true, если данные перемещены успешно, иначе false.
## bool deleteDynamicMesh ( )

**[ Main Thread ]**
Освобождает всю память, используемую процедурным мэшем, включая VRAM и RAM. Работает только когда процедурный режим установлен на *[PROCEDURAL_MODE_DYNAMIC](../../../api/library/objects/class.objectmeshstatic_cpp.md#PROCEDURAL_MODE_DYNAMIC)*.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Возвращаемое значение

true, если память освобождена успешно, иначе false.
## bool runGenerateMeshProceduralAsync ( CallbackBase1 < Ptr < Mesh >> * callback_generate , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает асинхронную генерацию процедурных данных мэша. Функция *callback_generate* выполняется в фоновом потоке и должна создать и заполнить объект мэша новыми данными. Сгенерированный мэш будет передан объекту по завершении, без блокировки главного потока. Работает только когда **процедурный режим включён**.


Обратите внимание, что обратный вызов выполняется в одном выделенном потоке, управляемом движком; он не распараллеливается и не должен порождать дополнительные потоки.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Функция обратного вызова, отвечающая за создание и заполнение исходного мэша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если изменение завершено и успешно применено, иначе false
## bool runGenerateMeshProceduralAsync ( CallbackBase1 < Ptr < Mesh >> * callback_generate , CallbackBase * callback_done , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает асинхронную генерацию процедурных данных мэша. Функция *callback_generate* выполняется в фоновом потоке и должна создать и заполнить объект мэша новыми данными. Сгенерированный мэш будет передан объекту по завершении, без блокировки главного потока. После применения мэша к объекту будет вызван необязательный callback_done. Работает только когда **процедурный режим включён**.


Обратите внимание, что обратный вызов выполняется в одном выделенном потоке, управляемом движком; он не распараллеливается и не должен порождать дополнительные потоки.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Функция обратного вызова, отвечающая за создание и заполнение исходного мэша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *[CallbackBase](../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback_done** -  Необязательный обратный вызов, выполняемый после полного применения геометрии. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_done() ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если генерация завершена и успешно применена, иначе false
## bool runGenerateMeshProceduralForce ( CallbackBase1 < Ptr < Mesh >> * callback_generate , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает немедленную (принудительную) генерацию процедурных данных мэша. Функция *callback_generate* выполняется в главном потоке и должна создать и заполнить объект мэша новыми данными. Сгенерированный мэш применяется к объекту сразу после завершения генерации. Работает только когда **процедурный режим включён**.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Функция обратного вызова, отвечающая за создание и заполнение исходного мэша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если генерация завершена и успешно применена, иначе false
## bool runGenerateMeshProceduralForce ( CallbackBase1 < Ptr < Mesh >> * callback_generate , CallbackBase * callback_done , int mesh_render_flags = 0 )

**[ Main Thread ]**
Запускает немедленную (принудительную) генерацию процедурных данных мэша. Функция *callback_generate* выполняется в главном потоке и должна создать и заполнить объект Mesh данными вершин. После применения мэша к объекту в главном потоке вызывается необязательный *callback_done*. Работает только когда **процедурный режим включён**.


> **Notice:** Обратите внимание, что изменение процедурного мэша **напрямую влияет на стриминг и использование памяти (RAM, VRAM и диска)** в зависимости от выбранного процедурного режима. Подробности см. в разделе [Procedural Mesh Workflow](#procedural_workflow).

### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Mesh](../../../api/library/rendering/class.mesh_cpp.md)>> ** **callback_generate** -  Функция обратного вызова, отвечающая за создание и заполнение исходного мэша. Выполняется в главном потоке. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_generate(Ptr<Mesh> mesh) ```
- *[CallbackBase](../../../api/library/common/callbacks/class.callbackbase_cpp.md) ** **callback_done** -  Необязательный обратный вызов, выполняемый после полного применения геометрии. Функция должна быть обёрнута с помощью *[MakeCallback()](../../../api/library/common/class.unigine.namespace_cpp.md#MakeCallback_Classm_RetClassm)* и иметь следующую сигнатуру: ```cpp void callback_done() ```
- *int* **mesh_render_flags** - Необязательные [usage flags](../../../api/library/rendering/class.meshrender_cpp.md#USAGE_DYNAMIC_VERTEX) для *[MeshRender](../../../api/library/rendering/class.meshrender_cpp.md)*.

### Возвращаемое значение

true, если генерация завершена и успешно применена, иначе false
