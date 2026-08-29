# Unigine::NodeLayer Class (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Node


[layer node](../../../objects/nodes/layer/index.md) — это узел нулевого размера, не имеющий визуального представления и позволяющий сохранять все свои дочерние узлы в отдельный файл `.node`. Узлы-слои следует использовать для разделения мира на несколько логических частей и сохранения каждой из них в файл `.node`, чтобы каждый слой и его дочерние узлы можно было редактировать без влияния на исходный файл `.world`.

> **Notice:** Сам узел-слой не хранится в файле `.node`.


### Создание слоя


Создайте экземпляр класса NodeLayer. Также можно задать такие настройки, как имя, трансформация и т.д.


<details>
<summary>AppWorldLogic.cpp | Закрыть</summary>

`AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"

#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	// создание узла-слоя
	NodeLayerPtr layer = NodeLayer::create("nodes/layer_0.node");
	// задание имени узла
	layer->setName("layer_0");

	return 1;
}


```

</details>


### Редактирование слоя


Редактирование узла-слоя включает добавление, удаление, изменение его дочерних узлов. Например, новые узлы можно добавить следующим образом:


<details>
<summary>AppWorldLogic.cpp | Закрыть</summary>

`AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"

#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	// создание узла-слоя
	NodeLayerPtr layer = NodeLayer::create("nodes/layer_0.node");
	// задание имени узла
	layer->setName("layer_0");

	// создание дочерних узлов
	for (int y = -10; y <= 10; y++)
	{
		for (int x = -10; x <= 10; x++)
		{

			// создание меша
			MeshPtr mesh = Mesh::create();
			mesh->addBoxSurface("box_0", vec3(1.0f));
			// создание узла (например, экземпляра класса ObjectMeshDynamic)
			ObjectMeshDynamicPtr node = ObjectMeshDynamic::create(mesh);

			// задание трансформации узла
			node->setWorldTransform(translate(Vec3(x * 2.0f, y * 2.0f, 0.0f)));
			// задание имени узла
			node->setName(String::format("mesh_%d_%d", x + 10, y + 10).get());
			// добавление узла как дочернего к узлу-слою
			layer->addWorldChild(node);
		}
	}

	return 1;
}


```

</details>


### Сохранение слоя


Изменения, внесённые в дочерние узлы узла-слоя, можно сохранить на диске, сохранив мир. Узлы будут сохранены в отдельный файл `.node`, указанный для слоя, а не в файл `.world`.


<details>
<summary>AppWorldLogic.cpp | Закрыть</summary>

`AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"

#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Math;

int AppWorldLogic::init()
{

	// создание узла-слоя
	NodeLayerPtr layer = NodeLayer::create("nodes/layer_0.node");
	// задание имени узла
	layer->setName("layer_0");

	// создание дочерних узлов
	for (int y = -10; y <= 10; y++)
	{
		for (int x = -10; x <= 10; x++)
		{

			// создание меша
			MeshPtr mesh = Mesh::create();
			mesh->addBoxSurface("box_0", vec3(1.0f));
			// создание узла (например, экземпляра класса ObjectMeshDynamic)
			ObjectMeshDynamicPtr node = ObjectMeshDynamic::create(mesh);

			// задание трансформации узла
			node->setWorldTransform(translate(Vec3(x * 2.0f, y * 2.0f, 0.0f)));
			// задание имени узла
			node->setName(String::format("mesh_%d_%d", x + 10, y + 10).get());
			// добавление узла как дочернего к узлу-слою
			layer->addWorldChild(node);
		}
	}

	// проверка, могут ли узел-слой и его предки быть сохранены в файл .world
	if (!layer->isSaveToWorldEnabled()) layer->setSaveToWorldEnabledRecursive(true);
	// сохранение мира
	World::saveWorld();

	return 1;
}


```

</details>


Вместо сохранения мира можно вручную сохранить дочерние узлы слоя в файл `.node` с использованием функции [World::saveNodes()](../../../api/library/engine/class.world_cpp.md#saveNodes_cstr_VECNode_int_int):


```cpp
// объявление массива узлов
Vector<NodePtr> nodes;
// добавление дочерних узлов слоя в объявленный массив
for (int i = 0; i < layer->getNumChildren(); i++) {
	nodes.append(layer->getChild(i));
}
// сохранение узлов в файл .node
if (World::saveNodes(layer->getNodePath(), nodes) == 0) {
	Log::error("Layer hasn't been saved\n");
}


```


### См. также


- Статья о [*Layer*](../../../objects/nodes/layer/index.md)


## Класс NodeLayer

### Методы класса

## void setNodePath ( const char * path )

Задаёт новый путь к узлу-слою: путь к файлу `*.node`, в котором хранятся дочерние узлы слоя.
### Аргументы

- *const char ** **path** - Путь к файлу `.node`.

## const char * getNodePath () const

Возвращает текущий путь к узлу-слою: путь к файлу `*.node`, в котором хранятся дочерние узлы слоя.
### Возвращаемое значение

Текущий путь к файлу `.node`.
---

## static NodeLayerPtr create ( const char * name )

Конструктор. Создаёт узел-слой с указанным именем файла для его хранения.
### Аргументы

- *const char ** **name** - Имя слоя.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [NodeLayer](../../../api/library/nodes/class.node_cpp.md#NODE_LAYER).
