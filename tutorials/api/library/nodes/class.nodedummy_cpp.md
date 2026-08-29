# Unigine::NodeDummy Class (CPP)

**Header:** #include <UnigineNodes.h>

**Inherits from:** Node


**Пустой узел (dummy node)** — это узел нулевого размера, не имеющий визуального представления. Он используется для организации других узлов в иерархию: пустой узел служит родительским узлом и позволяет объединять в группу другие узлы, сделанные его дочерними.

> **Notice:** Ограничивающий параллелепипед пустого узла равен объединению ограничивающих параллелепипедов всех его дочерних узлов.


### Создание пустого узла


Создайте экземпляр класса NodeDummy. Также можно задать такие настройки, как имя, трансформация и т.д.


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

	// создание пустого узла
	NodeDummyPtr dummy = NodeDummy::create();
	// задание имени
	dummy->setName("DummyNode");

	return 1;
}


```

</details>


### Организация иерархии узлов


Чтобы организовать узлы в иерархию, выполните следующее:

1. Создайте экземпляр класса NodeDummy.
2. Создайте узел и добавьте его как дочерний к созданному пустому узлу.


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

	// создание пустого узла
	NodeDummyPtr root = NodeDummy::create();
	// задание имени узла
	root->setName("root");

	// создание дочерних узлов
	for (int y = -10; y <= 10; y++)
	{
		for (int x = -10; x <= 10; x++)
		{

			// создание узла (экземпляра класса ObjectMeshStatic из указанного mesh-файла)
			ObjectMeshStaticPtr node = ObjectMeshStatic::create("core/meshes/box.mesh");
			// задание трансформации узла
			node->setWorldTransform(translate(Vec3(x * 2.0f, y * 2.0f, 0.0f)));
			// задание имени узла
			node->setName(String::format("mesh_%d_%d", x + 10, y + 10).get());
			// добавление узла как дочернего к корневому пустому узлу
			root->addWorldChild(node);
		}
	}

	return 1;
}


```

</details>


## Класс NodeDummy

### Методы класса

---

## static NodeDummyPtr create ( )

Конструктор. Создаёт пустой узел.
## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [NodeDummy](../../../api/library/nodes/class.node_cpp.md#NODE_DUMMY).
