# Unigine.NodeReference Class (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Node


[NodeReference](../../../objects/nodes/reference/index.md) — это узел, который ссылается на внешний ассет `*.node` на диске, получаемый путём [exporting](../../../editor2/exporting_nodes/index.md#export_to_noderef) узла из мира. Мир может содержать несколько узлов NodeReference, ссылающихся на один и тот же файл `*.node`.


Файл `*.node` обычно содержит заранее подготовленный узел (или иерархию узлов) со ссылками на все материалы, свойства и физические тела, необходимые для его рендеринга и поведения. Все изменения, внесённые в NodeReference через UNIGINE Editor, сохраняются в этот файл. При редактировании NodeReference через код реализуйте [saving changes](../../../api/library/engine/class.world_cpp.md#saveNode_cstr_Node_int_int) в файл `*.node`.


NodeReference следует использовать для распространения множества идентичных объектов, повторяющихся в мире: в отличие от обычных узлов, узлы-ссылки загружаются в мир быстрее благодаря использованию [internal cache](../../../principles/world_management/index.md#node_cache). Это также упростит применение одинаковых изменений ко всем повторяющимся объектам.


> **Notice:** Каждый NodeReference имеет собственную внутреннюю копию узлов, загруженную из ассета `*.node`, поэтому требуется сохранить изменения в ассет и перезагрузить все узлы NodeReference. Доступна [Automatic reloading](../../../api/library/engine/class.world_cpp.md#setAutoReloadNodeReferences_int_void).


NodeReference поддерживает вложенность, то есть ссылка на узел может включать другие ссылки на узлы, что полезно для реализации сложных решений с [instancing](../../../editor2/instancing_nodes/index.md).


> **Notice:** Сам NodeReference не имеет [bounds](../../../principles/world_management/index.md#bounds) и исключён из пространственного дерева.


Экземпляр NodeReference является [Possessor](../../../api/library/nodes/class.node_cpp.md#getPossessor_Node) хранимых им узлов, поэтому он отвечает за их загрузку и удаление. Можно [detach](#detachReference_Node) узел от экземпляра NodeReference, чтобы им управлял World.


### Автоматическая распаковка


Режим *Automatic Unpacking* определяет, где размещается содержимое NodeReference в иерархии узлов мира при загрузке во время выполнения (при запуске мира или при создании нового NodeReference). Когда включён, содержимое NodeReference извлекается для упрощения управления иерархией. Это глобальная настройка для всех миров, используемых в вашем проекте.


> **Notice:** - **Автоматическая распаковка отключена** в проектах *C++* и *только UnigineScript* по умолчанию для обратной совместимости.
> - **Автоматическая распаковка включена** в проектах *C#* по умолчанию.


Используйте *[World::isUnpackNodeReferences()](../../../api/library/engine/class.world_cpp.md#isUnpackNodeReferences_int)*, чтобы проверить, включена ли автоматическая распаковка в вашем проекте.


Переключить режим автоматической распаковки можно, вызвав *[World::setUnpackNodeReferences()](../../../api/library/engine/class.world_cpp.md#setUnpackNodeReferences_int_void)* в [system logic](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) перед загрузкой мира:


```cpp
#include <UnigineWorld.h>

using namespace Unigine;

int AppSystemLogic::init()
{
	// включение автоматической распаковки перед загрузкой мира
	World::setUnpackNodeReferences(1);

	return 1;
}


```


Режим автоматической распаковки влияет на [relation between the transformations](#node_trasformations) NodeReference и узлов, хранимых им.


#### Автоматическая распаковка отключена


Если автоматическая распаковка отключена (по умолчанию в проектах *только C++ / UnigineScript*), содержимое узлов NodeReference добавляется в корень иерархии узлов мира и доступно только как [references](#getReference_Node).


![](unpack_off.png)

*Автоматическая распаковка отключена.*


```cpp
#include <UnigineNodes.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	// создание экземпляра NodeReference
	NodeReferencePtr nodeRef = NodeReference::create("unigine_project/nodes/node_reference_0.node");

	// получение узла-ссылки
	NodePtr group = nodeRef->getReference();

	// поиск нужного узла
	NodePtr node_2 = group->getChild(group->findChild("Node_2"));

	return 1;
}


```


#### Автоматическая распаковка включена


Когда автоматическая распаковка NodeReference включена (по умолчанию в проектах *C#*), содержимое узлов NodeReference извлекается для упрощения управления иерархией. Это выполняется только во время выполнения и не влияет на ваши файлы `*.world` и `*.node`.


![](unpack_on.png)

*Автоматическая распаковка включена.*


Иерархия содержимого NodeReference присоединяется к нему в качестве непосредственного дочернего узла, поэтому доступ к ней осуществляется напрямую:


```cpp
#include <UnigineNodes.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	// создание экземпляра NodeReference
	NodeReferencePtr nodeRef = NodeReference::create("nodes/node_reference_0.node");

	// получение корневого узла заранее подготовленной иерархии
	NodePtr group = nodeRef->getChild(0);

	// поиск нужного узла среди всех потомков
	NodePtr node_2 = nodeRef->findNode("Node_2", 1);

	return 1;
}


```


### Трансформации NodeReference


Локальная трансформация корневого узла, хранимого NodeReference, не обязательно единичная — она может быть, например, смещена относительно позиции NodeReference.


> **Notice:** Изменение трансформации узлов, хранимых NodeReference, не влияет на трансформацию самого NodeReference.


Если [automatic unpacking of NodeReference](#unpacking) включена, трансформации узлов просто подчиняются [parent-child relation](../../../principles/world_structure/index.md#nodes_hierarchy). Однако если автоматическая распаковка отключена (то есть содержимое узла добавлено в корень иерархии узлов мира), для содержимого NodeReference используется [matrix hierarchy](../../../code/fundamentals/matrix_transformations/index_cpp.md#hierarchy). Таким образом, при перемещении NodeReference корневой узел его содержимого также перемещается относительно этого NodeReference. При этом изменяется локальная матрица трансформации корневого узла-ссылки.


> **Notice:** Изменение трансформации NodeReference **сбрасывает все изменения**, внесённые в локальную трансформацию хранимого им корневого узла, только если *автоматическая распаковка* отключена.


Эта связь трансформаций может быть разрушена [detaching](#detachReference_Node) узла-ссылки от экземпляра NodeReference. Обратите внимание, что распакованный отсоединённый узел останется дочерним для NodeReference, и на его матрицу трансформации по-прежнему будет влиять трансформация NodeReference. В этом случае может потребоваться удалить родительскую связь отсоединённого узла с помощью метода [*setParent()*](../../../api/library/nodes/class.node_cpp.md#setParent_Node_void).


### Внутренняя копия узлов


Каждый NodeReference имеет собственную внутреннюю копию узлов, загруженную из ассета `*.node`, что позволяет применять уникальные изменения к каждому экземпляру идентичных NodeReference отдельно во время выполнения (добавление, удаление и изменение узлов внутри NodeReference).


Другие экземпляры NodeReference не будут обновлены во время выполнения при применении изменений к одному экземпляру. Если требуется распространить эти изменения во время выполнения от одного экземпляра NodeReference на все остальные NodeReference в мире, связанные с тем же ассетом `*.node` на диске, следует сохранить изменения в ассет и перезагрузить все NodeReference. Доступна [Automatic runtime reloading](../../../api/library/engine/class.world_cpp.md#setAutoReloadNodeReferences_int_void).


### Создание ссылки на узел


Чтобы создать NodeReference, необходимо указать путь к существующему файлу `*.node`. Например, можно экспортировать узел в файл `*.node`, а затем создать NodeReference с его использованием:


```cpp
#include <UnigineNodes.h>

#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	/// создание меша
	MeshPtr mesh = Mesh::create();
	mesh->addBoxSurface("box_0", Math::vec3(1.0f));
	// создание динамического меша с использованием меша
	ObjectMeshDynamicPtr dynamic = ObjectMeshDynamic::create(mesh);
	// экспорт динамического меша в файл *.node
	World::saveNode("unigine_project/nodes/node_reference_0.node", dynamic);
	// создание ссылки на узел
	NodeReferencePtr nodeRef = NodeReference::create("unigine_project/nodes/node_reference_0.node");

	return 1;
}


```


Также можно привести экземпляр Node к NodeReference. Однако такое приведение типа возможно только если тип Node является [NODE_REFERENCE](../../../api/library/nodes/class.node_cpp.md#NODE_REFERENCE). Например:


```cpp
#include <UnigineLogic.h>
#include <UnigineStreams.h>

class AppWorldLogic: public Unigine::WorldLogic
{

public:
	AppWorldLogic();
	virtual ~AppWorldLogic();

	int init() override;

	int update() override;
	int postUpdate() override;
	int updatePhysics() override;

	int shutdown() override;

	int save(const Unigine::StreamPtr &stream) override;
	int restore(const Unigine::StreamPtr &stream) override;

	private:

	void nodeCast(Unigine::NodePtr node);

};


```


```cpp
#include <UnigineConsole.h>

#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;

void AppWorldLogic::nodeCast(NodePtr node)
{
	// проверка, является ли узел NodeReference
	if (node->getType() == Node::NODE_REFERENCE)
	{
		// приведение узла к NodeReference
		NodeReferencePtr nodeRef = checked_ptr_cast<NodeReference>(node);
		// задание имени NodeReference
		nodeRef->setName("NodeReference_cast");
	}
}

int AppWorldLogic::init()
{

	// создание NodeReference из файла
	NodeReferencePtr nodeRef_0 = NodeReference::create("unigine_project/nodes/node_reference_0.node");

	// задание имени
	nodeRef_0->setName("NodeReference_0");

	// сохранение изменений в файл *.world
	Console::run("world_save");
	// получение добавленного NodeReference как Node
	NodePtr node = World::getNodeByName("NodeReference_0");
	// приведение полученного Node к NodeReference
	nodeCast(node);

	return 1;
}


```


В результате узел *NodeReference_0* будет преобразован в узел *NodeReference_cast*.


### Редактирование ссылки на узел


Редактирование NodeReference включает:


- [Changing the path](#setNodePath_cstr_void) к файлу `.node`, на который указывает ссылка.
- Редактирование узла, хранимого ссылкой.


Чтобы получить доступ к узлу, на который ссылается *NodeReference*, используйте метод *[getReference()](#getReference_Node)*. Чтобы сохранить изменённый узел-ссылку в тот же ассет `*.node`, используйте метод *[World::saveNode()](../../../api/library/engine/class.world_cpp.md#saveNode_cstr_Node_int_int)* следующим образом:


```cpp
#include <UnigineNodes.h>

#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	// create a NodeReference instance
	NodeReferencePtr nodeRef = NodeReference::create("unigine_project/nodes/node_reference_0.node");

	// задание имени
	nodeRef->setName("NodeReference_0");

	// получение узла, хранимого ссылкой, и проверка, является ли он ObjectMeshDynamic
	if (nodeRef->getReference()->getType() == Node::OBJECT_MESH_DYNAMIC) {
		// приведение узла-ссылки к типу ObjectMeshDynamic
		ObjectMeshDynamicPtr dynamic = checked_ptr_cast<ObjectMeshDynamic>(nodeRef->getReference());
		// сохранение изменений узла-ссылки в файл *.node
		World::saveNode(nodeRef->getNodePath(), dynamic);
	}

	return 1;
}


```


В результате исходный файл `*.node`, на который ссылается NodeReference, будет обновлён, и узел *NodeReference_0* будет ссылаться на обновлённый узел с назначенным материалом. Если требуется, чтобы все NodeReference, ссылающиеся на изменённый ассет `*.node`, обновлялись автоматически, следует предварительно включить автоматическую перезагрузку NodeReference, вызвав метод [*setAutoReloadNodeReferences()*](../../../api/library/engine/class.world_cpp.md#setAutoReloadNodeReferences_int_void).


> **Notice:** При сохранении узлов в ассет `*.node` учитывается их [local transformation](#node_trasformations).


### См. также


- Статья [Nodes](../../../objects/nodes/index.md), где перечислены основные различия между обычными узлами и узлами-ссылками
- Статья [Node Reference](../../../objects/nodes/reference/index.md)
- [Node References: Must-Knows](../../../videotutorials/essentials/node_reference.md), демонстрирующее особенности *Node Reference*


## Класс NodeReference

### Методы класса

## void setNodePath ( const char * path )

Задаёт новую ссылку на файл `*.node`.
```cpp
// создание экземпляра NodeReference
NodeReferencePtr nodeRef = NodeReference::create("unigine_project/nodes/reference_0.node");
// ...

// изменение узла-ссылки
nodeRef->setNodePath("unigine_project/nodes/reference_1.node");
// ...

// возврат пути к узлу-ссылке
Log::message("The referenced node is: %s\n", nodeRef->getNodePath());

```


### Аргументы

- *const char ** **path** - Путь к файлу `*.node`.

## const char * getNodePath () const

Возвращает текущую ссылку на файл `*.node`.
```cpp
// создание экземпляра NodeReference
NodeReferencePtr nodeRef = NodeReference::create("unigine_project/nodes/reference_0.node");
// ...

// изменение узла-ссылки
nodeRef->setNodePath("unigine_project/nodes/reference_1.node");
// ...

// возврат пути к узлу-ссылке
Log::message("The referenced node is: %s\n", nodeRef->getNodePath());

```


### Возвращаемое значение

Текущий путь к файлу `*.node`.
## Ptr < Node > getReference () const

Возвращает текущий узел, хранимый ссылкой. Используйте этот метод, когда требуется изменить узел, на который указывает ссылка. Если возвращается экземпляр *[NodeDummy](../../../api/library/nodes/class.nodedummy_cpp.md)*, это означает, что несколько узлов одного уровня иерархии были [converted into the *NodeReference*](../../../objects/nodes/reference/index.md#convert_several_nodes).
```cpp
// создание экземпляра NodeReference
NodeReferencePtr nodeRef = NodeReference::create("unigine_project/nodes/single_nref.node");
// получение узла, хранимого ссылкой
NodePtr node = nodeRef->getReference();
// если узел является NodeDummy
if (node->getType() == Node::NODE_DUMMY) {
	// вывод имени типа каждого дочернего узла корневого узла, хранимого ссылкой
	for (int i = 0; i < node->getNumChildren(); i++) {
		Log::message("%d: %s\n", i, node->getChild(i)->getTypeName());
	}
}


```


### Возвращаемое значение

Текущий экземпляр узла.
---

## static NodeReferencePtr create ( const char * name )

Конструктор. Создаёт новый объект, ссылающийся на узел из заданного файла.
### Аргументы

- *const char ** **name** - Путь к файлу `*.node`.

## static bool canBeReference ( const char * name , const Ptr < Node > & node )

Возвращает значение, указывающее, не содержит ли иерархия заданного узла ссылку на узел с заданным именем.
### Аргументы

- *const char ** **name** - Имя ссылки на узел.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Node](../../../api/library/nodes/class.node_cpp.md)> &* **node** - Проверяемый узел.

### Возвращаемое значение

true, если иерархия заданного узла не содержит ссылку на узел с заданным именем; иначе false.
## Ptr < Node > detachReference ( )

Возвращает узел, хранимый ссылкой, и освобождает право владения этим узлом, так что он больше не принадлежит *NodeReference* и не связан с ним. Узлом теперь управляет World.
Чтобы удалить узел, выполните следующее:


```cpp
// создание нового экземпляра NodeReference
NodeReferencePtr nodeRef = NodeReference::create("unigine_project/nodes/node_reference_0.node");
// выполнение каких-либо действий
// ...
// получение узла, хранимого ссылкой, и освобождение владения узлом со стороны NodeReference
NodePtr node = nodeRef->detachReference();
// уничтожение указателя NodeReference, так как NodeReference больше не ссылается на узел
nodeRef.deleteForce();


```


### Возвращаемое значение

Корневой узел внутренней иерархии.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [NodeReference](../../../api/library/nodes/class.node_cpp.md#NODE_REFERENCE).
