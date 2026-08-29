# Thread Safety in API


Гарантируется безопасное использование объектов [Unigine API](../../../api/index.md) в [main loop](../../../code/fundamentals/execution_sequence/main_loop.md). Когда дело доходит до нескольких пользовательских потоков, всё становится немного сложнее.


Так как не все классы API потокобезопасны, вам следует учитывать тип поведения члена API для достижения безопасной многопоточности в вашем приложении.


Все типы требуют особых подходов, описанных в этой статье.


### См. также


- [*Thread* Class](../../../api/library/common/mt/class.thread_cpp.md)
- [*AsyncQueue* Class](../../../api/library/filesystem/class.asyncqueue_cpp.md)
- Пример C++ API **Threads**, демонстрирующий, как создавать и запускать пользовательские потоки с использованием класса [*Thread*](../../../api/library/common/mt/class.thread_cpp.md).


## Работа с несколькими потоками


### Потокобезопасные объекты


Полностью потокобезопасные объекты можно свободно использовать в любом потоке, будь то главный цикл или пользовательский. Это обеспечивается благодаря механизмам синхронизации потоков, делающим все критические операции атомарными и защищающим структуры данных, что устраняет такие проблемы, как *состояние гонки (race condition)* и другие.


Доступ к данным разрешён только одному потоку одновременно, в то время как данные заблокированы для других потоков, поэтому нескольким потокам может потребоваться ждать друг друга, пока их задачи не завершатся.


> **Примечание:** Множество запросов к данным из нескольких потоков может вызвать дополнительные потери производительности из-за синхронизации.


Следующие члены API считаются потокобезопасными:


- [**Filesystem**](../../../api/library/filesystem/class.filesystem_cpp.md)
- [**AsyncQueue**](../../../api/library/filesystem/class.asyncqueue_cpp.md)
- [**Log**](../../../api/library/common/class.log_cpp.md)
- [**Visualizer**](../../../api/library/engine/class.visualizer_cpp.md)


#### Избежание взаимоблокировок


Существует возможность взаимной блокировки, также известной как *deadlock*, при условии, что функция заблокированного объекта выполняет функцию *callback*, которая, в свою очередь, вызывает функцию того же заблокированного объекта.


> **Примечание:** Чтобы предотвратить взаимоблокировки, следует избегать вызова потенциально заблокированных объектов из их callback-функций.


#### Операции с Landscape Terrain


[*ObjectLandscapeTerrain* classes](../../../api/library/objects/landscape_terrain/index.md) содержат набор потокобезопасных методов, предназначенных для получения данных ландшафта и обнаружения пересечений.


<details>
<summary>AppWorldLogic.h | Close</summary>

**AppWorldLogic.h**


```cpp
#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UnigineThread.h>

class AppWorldLogic : public Unigine::WorldLogic
{
public:
	AppWorldLogic();
	~AppWorldLogic() override;

	int init() override;
	int shutdown() override;
private:

	Unigine::Vector<Unigine::Thread*> threads;

};


```

</details>


<details>
<summary>AppWorldLogic.cpp | Close</summary>

**AppWorldLogic.cpp**


```cpp
#include "AppWorldLogic.h"
#include <UniginePlayers.h>
#include <UnigineGame.h>
#include <UnigineVisualizer.h>
#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Math;

class TerrainIntersectionThread : public Thread
{
public:
	TerrainIntersectionThread(PlayerPtr m)
	{
		main_player = m;
	}

	void process() override
	{
		if (!main_player)
			return;
		while (isRunning())
		{

			float x = Game::getRandomFloat(-1000.0f, 1000.0f);
			float y = Game::getRandomFloat(-1000.0f, 1000.0f);

			if (!fetch)
			{
				// создаём fetch
				fetch = LandscapeFetch::create();

				// устанавливаем маску
				fetch->setUsesHeight(true);
				fetch->setUsesNormal(true);
				fetch->setUsesAlbedo(true);
				fetch->setUsesMask(0, true);
				fetch->setUsesMask(1, true);
				fetch->setUsesMask(2, true);
				fetch->setUsesMask(3, true);

				fetch->intersectionAsync(Vec3{ x, y, 10000.0f }, Vec3{ x, y, 0.0 }, false);
			}
			else
			{
				if (fetch->isAsyncCompleted())
				{
					if (fetch->isIntersection())
					{
						Vec3 point = fetch->getPosition();
						Visualizer::renderVector(point, point + Vec3_up * 10, vec4_blue);
						Visualizer::renderVector(point, point + Vec3(fetch->getNormal() * 10), vec4_red);
						Visualizer::renderSolidSphere(1, translate(point), vec4_black);

						String string;
						string += String::format("Height : %f\n", fetch->getHeight());

						string += "Masks: \n";

						auto terrain = Landscape::getActiveTerrain();
						for (int i = 0; i < 4; i++)
						{
							// getName() не потокобезопасен,
							// не изменяйте имя маски в других потоках во время получения
							string += String::format(" - \"%s\": %.2f\n", terrain->getDetailMask(i)->getName(), fetch->getMask(i));
						}
						Visualizer::renderMessage3D(point, vec3(1, 1, 0), string.get(), vec4_green, 1);
					}
					else
					{
						Visualizer::renderMessage3D(Vec3(x, y, 0), vec3(1, 1, 0), "Out of terrain", vec4_red, 1);
					}

					fetch->intersectionAsync(Vec3{ x, y, 10000.0f }, Vec3{ x, y, 0.0 }, false);
				}
			}
		}
	}

private:
	LandscapeFetchPtr fetch;
	PlayerPtr main_player;
};

int AppWorldLogic::init()
{

	PlayerPtr main_player = checked_ptr_cast<Player>(World::getNodeByName("main_player"));

	int num_thread = 4;
	for (int i = 0; i < num_thread; ++i)
	{
		Thread* thread = new TerrainIntersectionThread(main_player);
		thread->run();
		threads.push_back(thread);
	}
	Visualizer::setEnabled(true);

	return 1;
}

int AppWorldLogic::shutdown()
{

	for (Thread* thread : threads)
	{
		thread->stop();
		delete thread;
	}

	return 1;
}


```

</details>


#### Пересечения с Global Terrain


*[ObjectTerrainGlobal](../../../api/library/objects/class.objectterrainglobal_cpp.md)* содержит набор потокобезопасных методов, предназначенных для некоторых специфичных сценариев использования.


<details>
<summary>AppWorldLogic.h | Close</summary>

**AppWorldLogic.h**


```cpp
#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UnigineThread.h>

class AppWorldLogic : public Unigine::WorldLogic
{
public:
	AppWorldLogic();
	~AppWorldLogic() override;

	int init() override;
	int shutdown() override;
private:

	Unigine::Vector<Unigine::Thread*> threads;

};


```

</details>


<details>
<summary>AppWorldLogic.cpp | Close</summary>

**AppWorldLogic.cpp**


```cpp
#include "AppWorldLogic.h"
#include <UniginePlayers.h>
#include <UnigineGame.h>
#include <UnigineVisualizer.h>
#include <UnigineObjects.h>
#include <UnigineWorld.h>

using namespace Unigine;
using namespace Math;

class TerrainIntersectionThread : public Thread
{
public:
	TerrainIntersectionThread(ObjectTerrainGlobalPtr terrain_)
	{
		terrain = terrain_;
		intersection = ObjectIntersection::create();
	}

	void process() override
	{
		while (isRunning())
		{
			float x = Game::getRandomFloat(-1000.0f, 1000.0f);
			float y = Game::getRandomFloat(-1000.0f, 1000.0f);

			int success = terrain->getIntersection(Vec3{ x, y, 10000.0f }, Vec3{ x, y, 0.0 }, intersection, 0);
			if (success)
			{
				const auto intersection_point = intersection->getPoint();
				Log::message("Thread %d: %f %f %f\n", getID(), intersection_point.x, intersection_point.y, intersection_point.z);
			}
		}
	}

private:
	ObjectTerrainGlobalPtr terrain;
	ObjectIntersectionPtr intersection;
};

int AppWorldLogic::init()
{

	const auto terrain = checked_ptr_cast<ObjectTerrainGlobal>(World::getNodeByName("Landscape"));

	int num_thread = 4;
	for (int i = 0; i < num_thread; ++i)
	{
		Thread* thread = new TerrainIntersectionThread(terrain);
		thread->run();
		threads.push_back(thread);
	}

	return 1;
}

int AppWorldLogic::shutdown()
{

	for (Thread* thread : threads)
	{
		thread->stop();
		delete thread;
	}

	return 1;
}


```

</details>


### Объекты, зависящие от главного цикла


Класс *[Node](../../../api/library/nodes/class.node_cpp.md)* и [Node-Related classes](../../../api/library/nodes/index.md) напрямую задействованы в потоках главного цикла. Для них не предусмотрены механизмы синхронизации.


Для повышения производительности узлы можно создавать и загружать в пользовательских потоках **до их интеграции** в главный цикл. Это включает:


- Создание узлов через **[API](../../../api/library/nodes/class.node_cpp.md#create_node)**
- Загрузку узла из файлов с помощью *[World::loadNode()](../../../api/library/engine/class.world_cpp.md#loadNode_cstr_int_Node)*
- Класс **[AsyncQueue](../../../api/library/filesystem/class.asyncqueue_cpp.md)** предоставляет методы для асинхронной загрузки ресурсов.
- Класс **[Async](../../../api/library/common/class.async_cpp.md)** предназначен для асинхронного выполнения фоновых задач.


Узлы могут быть полностью настроены и заполнены данными в пользовательском потоке, в котором они были созданы.


Узлы, подготовленные в фоновых потоках, **не добавляются автоматически в главный цикл движка**. Чтобы узел участвовал в рендеринге, обновлениях и физике, он должен стать частью главного цикла путём вызова метода *[Node::updateEnabled()](../../../api/library/nodes/class.node_cpp.md#updateEnabled_void)* из главного потока. После включения узел становится привязанным к главному циклу, и все дальнейшие операции (например, трансформации, изменения свойств, обновления материалов) должны выполняться из главного потока.


Следующий пример демонстрирует, как создать узел в отдельном потоке и подключить его к главному циклу.


<details>
<summary>NodeLoader.h | Close</summary>

```cpp
#pragma once
#include <UnigineComponentSystem.h>
#include <memory>

using namespace Unigine;
using namespace Math;

// Простой компонент, загружающий узел в пользовательском потоке
class NodeLoader : public ComponentBase
{
public:
	COMPONENT_DEFINE(NodeLoader, ComponentBase)

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	// Поток, загружающий узел из файла в фоновом режиме
	class UserThread final : public Unigine::Thread
	{
	public:
		UserThread();
		~UserThread();
		NodePtr my_node;			// Узел, загруженный в этом потоке

	private:
		void process() override;	// Главная функция выполнения потока
	};

private:
	void init();
	void update();
	void shutdown();

private:
	std::unique_ptr<UserThread> node_creation_thread;
};

```

</details>


<details>
<summary>NodeLoader.cpp | Close</summary>

```cpp
#include "NodeLoader.h"
#include <UnigineConsole.h>
#include <iostream>
#include <memory>

using namespace Unigine;
using namespace Unigine::Math;

NodeLoader::UserThread::UserThread()  {}
NodeLoader::UserThread::~UserThread() {}

void NodeLoader::UserThread::process()
{
	// Симулируем некоторую нагрузку
	sleep(1000);

	//Предположим, мы загружаем узел "material_ball.node" из папки "data"
	my_node = World::loadNode("material_ball.node");

	// Если узел был успешно загружен, устанавливаем его позицию
	if (my_node)
	{
		my_node->setWorldPosition(Vec3(0, 0, 0));
	}

	// Дополнительная симулированная нагрузка
	sleep(1000);
}

REGISTER_COMPONENT(NodeLoader)

void NodeLoader::init()
{
	// Запускаем фоновый поток для загрузки узла
	node_creation_thread = std::make_unique<UserThread>();
	node_creation_thread->run();
}

void NodeLoader::update()
{
	// Как только фоновый поток завершил свою работу
	if (!node_creation_thread->isRunning())
	{
		// Включаем узел в главном потоке, чтобы сделать его зависимым от главного цикла
		node_creation_thread->my_node->updateEnabled();
	}
}

void NodeLoader::shutdown()
{
	if (node_creation_thread->isRunning())
	{
		node_creation_thread->stop();
	}
}

```

</details>


Пример ниже показывает, как достичь такого же поведения с использованием C#


<details>
<summary>NodeLoader.cs | Close</summary>

```csharp
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using Unigine;

// Простой компонент, загружающий узел в пользовательском потоке
public class NodeLoader : Component
{
	// Поток, загружающий узел из файла в фоновом режиме
	Thread separateNodeCreation;
	Node ball;

	void Init()
	{
		separateNodeCreation = new Thread(() =>
			{
				// Симулируем некоторую нагрузку
				Thread.Sleep(2000);

				//Предположим, мы загружаем узел "material_ball.node" из папки "data"
				ball = World.LoadNode("material_ball.node");
				ball.Position = new dvec3(2.0f, 25.0f, 0.0f);

				// Дополнительная симулированная нагрузка
				Thread.Sleep(2000);
			}
		);
		// Запускаем фоновый поток для загрузки узла
		separateNodeCreation.Start();
	}

	void Update()
	{
		// Как только фоновый поток завершил свою работу
		if (!separateNodeCreation.IsAlive)
		{
			// Включаем узел в главном потоке, чтобы сделать его зависимым от главного цикла
			ball.UpdateEnabled();
		}

	}
}

```

</details>


Если вам нужно изменить узлы, которые уже являются частью главного цикла, из фонового потока, вы должны сначала приостановить главный цикл во избежание конфликтов, внести свои изменения, а затем возобновить цикл.


> **Примечание:** [GPU-related methods](#gpu_objects) **всегда должны** вызываться в главном цикле.


Потокобезопасность обеспечивается синхронизацией всех **потоков движка**, работающих с объектами, зависящими от главного цикла, с *[Engine::swap()](../../../code/fundamentals/execution_sequence/main_loop.md#swap)*, где выполняется отложенное удаление объектов. Но **пользовательские потоки** могут выполняться параллельно с *[Engine::swap()](../../../code/fundamentals/execution_sequence/main_loop.md#swap)* в главном потоке, в таких случаях **не следует выполнять никакие манипуляции с объектами, зависящими от главного цикла (такими как узлы), во время *Engine::swap()*.**


### Объекты, не зависящие от главного цикла


Также существуют члены API, которые не задействованы в главном цикле, для них также не предусмотрены алгоритмы синхронизации.


Вы можете полностью управлять таким объектом в любом потоке, но обратите внимание, что если вам нужно передать его в другой поток, будь то главный цикл или пользовательский поток, вам необходимо обеспечить ручную синхронизацию для согласованности его данных.


Для этой цели вы можете свободно использовать любые методы и классы, содержащиеся в файле `include/UnigineThread.h`, или другие механизмы по своему усмотрению.


Следующие члены API считаются не зависящими от потоков главного цикла:


| - [**Blob**](../../../api/library/common/class.blob_cpp.md) - [**Camera**](../../../api/library/rendering/class.camera_cpp.md) - [**Dir**](../../../api/library/filesystem/class.dir_cpp.md) - [**Ellipsoid**](../../../api/library/geodetics/class.ellipsoid_cpp.md) - [**File**](../../../api/library/filesystem/class.file_cpp.md) - [**GameIntersection**](../../../api/library/engine/class.gameintersection_cpp.md) - [**Image**](../../../api/library/common/class.image_cpp.md) - [**Json**](../../../api/library/common/class.json_cpp.md) - [**Mesh**](../../../api/library/rendering/class.mesh_cpp.md) - [**MeshDynamic**](../../../api/library/rendering/class.meshdynamic_cpp.md) - [**ObjectIntersection**](../../../api/library/objects/class.objectintersection_cpp.md) - [**ObjectIntersectionNormal**](../../../api/library/objects/class.objectintersectionnormal_cpp.md) - [**ObjectIntersectionTexCoord**](../../../api/library/objects/class.objectintersectiontexcoord_cpp.md) |  | - [**Path**](../../../api/library/common/class.path_cpp.md) - [**PathRouteIntersection**](../../../api/library/pathfinding/class.pathrouteintersection_cpp.md) - [**PhysicsIntersection**](../../../api/library/physics/class.physicsintersection_cpp.md) - [**PhysicsIntersectionNormal**](../../../api/library/physics/class.physicsintersectionnormal_cpp.md) - [**RegExp**](../../../api/library/common/class.regexp_cpp.md) - [**ShapeContact**](../../../api/library/physics/class.shapecontact_cpp.md) - [**Socket**](../../../api/library/networking/class.socket_cpp.md) - [**Stream**](../../../api/library/common/class.stream_cpp.md) - [**TilesetFile**](../../../api/library/objects/class.tilesetfile_cpp.md) - [**Viewport**](../../../api/library/rendering/class.viewport_cpp.md) - [**WorldIntersection**](../../../api/library/worlds/class.worldintersection_cpp.md) - [**WorldIntersectionNormal**](../../../api/library/worlds/class.worldintersectionnormal_cpp.md) - [**WorldIntersectionTexCoord**](../../../api/library/worlds/class.worldintersectiontexcoord_cpp.md) - [**Xml**](../../../api/library/common/class.xml_cpp.md) |
|---|---|---|


### Объекты, связанные с GPU


Некоторые методы членов взаимодействуют с Graphics API, который доступен только в главном цикле. Как только вам нужно вызвать функцию, связанную с GPU, вы должны передать объект в главный цикл и выполнить вызов в нём.


Классы [**Rendering-Related**](../../../api/library/rendering/index.md) (например, *[MeshDynamic](../../../api/library/rendering/class.meshdynamic_cpp.md)*) следует считать связанными с GPU.


Также классы [**Object-Related**](../../../api/library/objects/index.md) имеют методы, связанные с рендерингом, такие как *[*render()*](../../../api/library/objects/class.object_cpp.md#render_int_int_void)* и другие.


Ниже вы найдёте исходный код примера по умолчанию *[dynamic_03](../../../code/uniginescript/samples/objects/dynamic_03.md)*, демонстрирующего, как создать динамический меш с использованием алгоритма Marching Cubes, выполняемого асинхронно.


<details>
<summary>dynamic_03.usc | Close</summary>

**dynamic_03.usc**


```cpp
#include <core/scripts/samples.h>
#include <samples/objects/dynamic_01.h>

/*
 */
Async async_0;
Async async_1;
int size = 32;
float field_0[size * size * size];
float field_1[size * size * size];
int flags_0[size * size * size];
int flags_1[size * size * size];
ObjectMeshDynamic mesh_0;
ObjectMeshDynamic mesh_1;

using Unigine::Samples;

/*
 */
string mesh_material_names[] = ( "objects_mesh_red", "objects_mesh_green", "objects_mesh_blue", "objects_mesh_orange", "objects_mesh_yellow" );

string get_mesh_material(int material) {
	return mesh_material_names[abs(material) % mesh_material_names.size()];
}

/*
 */
void update_thread() {

	while(1) {

		float time = engine.game.getTime();

		// ждём async
		if(async_1 == NULL) async_1 = new Async();
		while(async_1 != NULL && async_1.isRunning()) wait;
		if(async_1 == NULL) continue;
		async_1.clearResult();

		// копируем меш
		Mesh mesh = new Mesh();
		mesh_1.getMesh(mesh);
		mesh_0.setMesh(mesh);
		mesh_0.setMaterial(get_mesh_material(1),"*");
		delete mesh;

		// ждём async
		if(async_0 == NULL) async_0 = new Async();
		while(async_0 != NULL && async_0.isRunning()) wait;
		if(async_0 == NULL) continue;
		async_0.clearResult();

		// меняем буферы местами
		field_1.swap(field_0);
		flags_1.swap(flags_0);

		// создаём поле
		float angle = sin(time) + 3.0f;
		mat4 transform = rotateZ(time * 25.0f) * scale(vec3(5.0f / size)) * translate(vec3(-size / 2.0f));
		async_0.run(functionid(create_field),field_0.id(),flags_0.id(),size,transform,angle);

		// создаём меш
		async_1.run(functionid(marching_cubes),mesh_1,field_1.id(),flags_1.id(),size);

		wait;
	}
}

/*
 */
int init() {

	createInterface("samples/objects/dynamic_03.world");
	engine.render.loadSettings(fullPath("samples/common/world/render.render"));
	createDefaultPlayer(Vec3(30.0f,0.0f,20.0f));
	createDefaultPlane();

	mesh_0 = addToEditor(new ObjectMeshDynamic(OBJECT_DYNAMIC_ALL));
	mesh_0.setWorldTransform(Mat4(scale(vec3(16.0f / size)) * translate(-size / 2.0f,-size / 2.0f,0.0f)));

	mesh_1 = new ObjectMeshDynamic(1);
	mesh_1.setEnabled(0);

	setDescription(format("Async dynamic marching cubes on %dx%dx%d grid",size,size,size));

	thread("update_thread");

	return 1;
}

/*
 */
void shutdown() {

	if(async_0 != NULL) async_0.wait();
	if(async_1 != NULL) async_1.wait();
	return 1;
}


```

</details>


### Многопоточный рендеринг (только DirectX12)


Когда *[render_multithreaded](../../../code/console/index.md#render_multithreaded)* включён (например, через [console](../../../code/console/index.md#render_multithreaded) или [API](../../../api/library/rendering/class.render_cpp.md#setMultithreaded_int_void)), рендеринг поверхностей распределяется по нескольким потокам для повышения производительности. Это вводит **особые ограничения использования** из-за конкурентного доступа к данным.


Вы должны **избегать изменения свойств**, влияющих на рендеринг поверхностей, пока активен этап рендеринга. Это включает настройки рендеринга, такие как *[render_distance_scale](../../../code/console/index.md#render_distance_scale)*, параметры материалов, такие как текстуры и цвета, и параметры объектов, такие как трансформации узлов или видимость. Изменение этих свойств может создать **состояния гонки (race conditions)** между главным потоком и потоками рендеринга, что потенциально может привести к непредсказуемому поведению.


Чтобы безопасно изменять свойства рендеринга, выполняйте изменения из главного потока во время *[Engine::update()](../../../code/fundamentals/execution_sequence/main_loop.md#update)* или *[Engine::swap()](../../../code/fundamentals/execution_sequence/main_loop.md#swap)*, когда потоки рендеринга простаивают.


## Потоки в UnigineScript


При использовании рабочего процесса UnigineScript также следует помнить, что объекты, зависящие от главного цикла, нельзя напрямую изменять вне главного цикла. Вместо этого рекомендуется создать *двойника* для такого объекта, который будет изменяться асинхронно, а затем заменяться с исходным объектом на этапе *flush*.


> **Примечание:** Нереентерабельные функции UnigineScript не подходят для многопоточного использования. Вам придётся создать отдельную функцию для каждого потока. Для этого можно использовать [Templates](../../../code/uniginescript/language/templates.md).


Ниже вы найдёте пример на UnigineScript по асинхронному управлению несколькими кластерами мешей. Вы можете скопировать и вставить его в файл скрипта мира вашего проекта.


<details>
<summary>cluster_03.usc | Close</summary>

**cluster_03.usc**


```cpp
#include <core/unigine.h>
#include <core/scripts/samples.h>

using Unigine::Samples;

#define NUM_CLUSTERS 4
int size = 60;

// класс для асинхронного кластера мешей
class AsyncCluster
{
	public:
	Mat4 transforms[0];
	// исходный кластер мешей
	ObjectMeshCluster cluster;
	// двойник для асинхронного изменения
	ObjectMeshCluster cluster_async;
	Async async;
};
AsyncCluster clusters[NUM_CLUSTERS];

string mesh_material_names[] = ( "stress_mesh_red", "stress_mesh_green", "stress_mesh_blue", "stress_mesh_orange", "stress_mesh_yellow" );

string get_mesh_material(int material) {
	return mesh_material_names[abs(material) % mesh_material_names.size()];
}

// шаблон для генерации функции, трансформирующей кластер в каждом потоке
template async_transforms<NUM, OFFSET_X, OFFSET_Y> void async_transforms_ ## NUM(ObjectMeshCluster cluster_async, float transforms[], float time, int size) {

	Vec3 offset = Vec3(OFFSET_X - 0.5f, OFFSET_Y - 0.5f, 0.0f) * (size + 0.5f) * 2;

	int num = 0;
	for(int y = -size; y <= size; y++) {
		for(int x = -size; x <= size; x++) {
			float rand = sin(frac(num * 0.333f) + x * y * (NUM + 1));

			Vec3 pos = (Vec3(x, y, sin(time * rand * 2.0f) + 1.5f) + offset) * 2.0f;
			transforms[num] = translate(pos) * rotateZ(time * 25 * rand);
			num++;
		}
	}

	cluster_async.createMeshes(transforms);
}

async_transforms<0,0,0>;
async_transforms<1,0,1>;
async_transforms<2,1,0>;
async_transforms<3,1,1>;

void update_thread() {

	while(1) {

		// ждём async
		for(int i = 0; i < NUM_CLUSTERS; i++) {
			while(clusters[i].async.isRunning())
				wait;
		}

		for(int i = 0; i < NUM_CLUSTERS; i++) {
			AsyncCluster c = clusters[i];

			c.async.clearResult();
			c.cluster.swap(c.cluster_async);
			c.cluster.setEnabled(1);
			c.cluster_async.setEnabled(0);
			c.async.run("async_transforms_" + i, c.cluster_async, c.transforms.id(), engine.game.getTime(), size);
		}

		wait;
	}
}

int init() {
	// создаём сцену
	PlayerSpectator player = new PlayerSpectator();
	player.setPosition(Vec3(30.0f,0.0f,20.0f));
	player.setDirection(vec3(-1.0f, 0.0f, -0.5f));
	engine.game.setPlayer(player);

	for(int i = 0; i < NUM_CLUSTERS; i++) {
		AsyncCluster c = new AsyncCluster();
		c.cluster = new ObjectMeshCluster(fullPath("samples/common/meshes/box.mesh"));
		c.cluster.setMaterial(get_mesh_material(i),"*");
		c.cluster_async = class_append(node_cast(c.cluster.clone()));
		c.async = new Async();
		int num = pow(size * 2 + 1, 2);
		c.transforms.resize(num);
		clusters[i] = c;
	}

	thread("update_thread");

	int num = pow(size * 2 + 1, 2) * NUM_CLUSTERS;
	log.message("ObjectMeshCluster with %d dynamic instances",num);

	return 1;
}

/*
 */
void shutdown() {

	for(int i = 0; i < NUM_CLUSTERS; i++) {
		clusters[i].async.wait();
	}

	return 1;
}


```

</details>
