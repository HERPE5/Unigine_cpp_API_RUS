# Accessing Nodes and Files via Properties


> **Примечание:** Подход, описанный в этой статье, не предназначен для проектов, использующих C# Component System, где ассеты управляются через [components](../../../api/library/common/logic/component_system/cs/class.component.md#parameters).


Каждый ресурс ([asset](../../../editor2/assets_workflow/index.md)), используемый в вашем проекте, будь то узел, меш, материал, текстура или что-либо ещё, имеет уникальный идентификатор (GUID). **GUID** идентифицирует путь к ассету (т.е. расположение ассета в проекте). GUID используются для сохранения всех связей и зависимостей между ассетами, **независимо от их имени и расположения в проекте** (когда вы меняете имя или расположение ассета в проекте, его GUID не меняется).


Использование GUID для связывания ваших ассетов безопаснее, чем использование имён файлов, так как вам не нужно беспокоиться о том, что ваш материал потеряет текстуру при изменении её имени. Однако управление GUID напрямую довольно запутанно.


[Property](../../../principles/properties/index.md) позволяет связывать определённые ассеты с [node](../../../start/index.md#node) через GUID, даже не задумываясь о них, давая вам лёгкий доступ к этим ассетам. Есть ряд типов параметров свойства, делающих это возможным:


- **material** - для материалов
- **property** - для свойств
- **file** - для всех остальных файлов (текстур, мешей, звуков и т.д.)


Тип параметра свойства *node* позволяет аналогичным образом связать узел с другим узлом, используя ID.


Художники и программисты, разрабатывающие проект, должны иметь возможность работать независимо: художники готовят контент (текстуры, материалы, модели и т.д.), в то время как программисты пишут код, реализующий логику, выполняющую определённые операции с контентом.


Использование свойств упрощает весь процесс:


- Художники могут безопасно перемещать или переименовывать файлы и узлы. Программисты всегда работают со свойствами: создают их, устанавливают и считывают значения параметров (которые могут представлять ссылки на различные ассеты). Художники также могут устанавливать параметры свойства, они делают это [via the Editor](../../../editor2/properties_settings/organizing_properties/index.md#assign_property).
- Ни художникам, ни программистам не нужно работать с ID узлов или GUID и запоминать их. У программиста всегда под рукой переменная (параметр свойства), дающая доступ к любому необходимому узлу или файлу.


Общий рабочий процесс на основе свойств понятен и прост. Есть два основных случая, в зависимости от логики вашего проекта:


- [For projects implemented without the Component System](#no_cs)
- [For C++ projects implemented using the Component System](#using_cs)


## Общий рабочий процесс


Общий рабочий процесс для всех проектов, не использующих [C++ Component System](../../../principles/component_system/component_system_cpp/index.md), должен быть следующим:


1. Сначала мы создаём свойство для хранения ссылок на все узлы и ассеты, которые нам нужны, и сохраняем его в папку `data` нашего проекта. Например, свойство может выглядеть так: ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.16.0.2" name="my_property" parent_name="node_base" manual="1" editable="1"> <parameter name="some_float" type="float">30.5</parameter> <parameter name="some_string" type="string">Hello from my_property!</parameter> <parameter name="some_node" type="node">0</parameter> <parameter name="some_material" type="material"></parameter> <parameter name="some_mesh" type="file"></parameter> <parameter name="some_file" type="file"></parameter> </property> ```
2. Затем откройте UnigineEditor, выберите нужный узел, нажмите *Add new property* и перетащите файл свойства в поле нового свойства, затем перетащите все необходимые ассеты и узлы в соответствующие поля свойства (см. видео ниже). ![](assign_prop_params.gif) *Связывание узлов и ассетов со свойством*
3. Так как мы не используем компоненты, нам придётся быть привязанными к именам узлов, которым назначены свойства со ссылками на ассеты. Поэтому в методе *[init()](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_init)* класса *WorldLogic* мы получаем узел по его имени: ```cpp int AppWorldLogic::init() { /* ... */ NodePtr node = World::getNodeByName("node_name"); /* ... */ return 1; } ```
4. Затем мы получаем назначенное ему свойство: ```cpp PropertyPtr property = node->getProperty(); ```
5. Теперь мы можем использовать свойство для получения доступа к узлам и файлам:

  - **чтобы получить материал**, мы можем просто использовать соответствующий параметр узла: ```cpp property->getParameterPtr("node_param_name")->getValueMaterial(); ```
  - **чтобы получить путь к файлу**, мы можем просто использовать: ```cpp const char *path = property->getParameterPtr("file_param_name")->getValueFile(); ``` Так как у нас есть путь к нашему файлу, мы можем использовать его, например: ```cpp // для создания ссылки на узел NodeReferencePtr node_ref = NodeReference::create(path_to_node_file); // для загрузки источника звука SoundSourcePtr sound = SoundSource::create(path_to_sound_file); ```


Давайте рассмотрим пример, иллюстрирующий этот рабочий процесс.


### Пример использования


В этом примере мы будем манипулировать узлами и ассетами, связанными с определённым узлом, используя свойство через C++ и C#.


Давайте создадим простой объект MeshStatic с именем *my_object*, унаследуем материал от **[mesh_base](../../../content/materials/library/mesh_base/index.md)**, чтобы назначить его поверхностям нашего объекта, и добавим какой-нибудь аудиофайл (`*.mp3` или `*.oga`) в наш проект.


Итак, мы связываем файл `*.mesh`, материал, узел **material_ball** из мира по умолчанию и аудиофайл, используя [property file described above](#property).


В нашем коде мы будем:


- Вращать связанный узел.
- Изменять связанный материал и сохранять изменения.
- Генерировать новый объект, используя связанный меш.
- Воспроизводить связанный аудиофайл.


#### Реализация на C++


Ниже вы найдёте реализацию на C++ примера, [described above](#example_description). Вы можете скопировать и вставить её в файл `AppWorldLogic.cpp` вашего проекта.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

**AppWorldLogic.cpp**


```cpp
#include "AppWorldLogic.h"
#include <UnigineMaterials.h>
#include <UnigineSounds.h>
#include <UnigineGame.h>
#include <UnigineWorld.h>
#include <UnigineFileSystem.h>

using namespace Unigine;
using namespace Math;
NodePtr my_node;                   // узел, которому назначено свойство со ссылками
PropertyPtr property;              // свойство со всеми необходимыми ссылками
MaterialPtr material;              // связанный материал
NodePtr param_node;                // связанный узел
SoundSourcePtr sound;	      	   // источник звука для воспроизведения
ObjectMeshStaticPtr generated_obj; // объект, который будет сгенерирован с использованием меша

AppWorldLogic::AppWorldLogic() {

}

AppWorldLogic::~AppWorldLogic() {

}

int AppWorldLogic::init() {
	// получаем узел, которому назначено свойство со ссылками на ассеты
	my_node = World::getNodeByName("my_object");

	// получаем свойство, которое будет использоваться для доступа ко всем необходимым файлам
	property = my_node->getProperty();
	// используем доступ к параметрам свойства для выполнения нужных действий
	if (property) {
		// получаем материал из соответствующего параметра свойства
		material = property->getParameterPtr("some_material")->getValueMaterial();

		// получаем путь к файлу меша из соответствующего параметра свойства
		const char *mesh_file_name = property->getParameterPtr("some_mesh")->getValueFile();

		// создаём объект с использованием меша
		generated_obj = ObjectMeshStatic::create(mesh_file_name);

		// устанавливаем позицию объекта относительно позиции другого узла
		generated_obj->setWorldPosition(my_node->getWorldPosition());
		generated_obj->translate(vec3(-1.0f, 0.0f, 0.0f));

		// получаем путь к звуковому файлу из соответствующего параметра свойства
		const char *sound_file_name = property->getParameterPtr("some_file")->getValueFile();

		// получаем узел из соответствующего параметра свойства
		param_node = property->getParameterPtr("some_node")->getValueNode();

		// создаём и воспроизводим звук из файла
		sound = SoundSource::create(sound_file_name);
		sound->setMaxDistance(100.0f);
		sound->setLoop(1);
		sound->play();

		// выводим результаты в консоль
		Log::message("Path to mesh file: %s\nPath to sound file: %s\nNode ID: %d\n", mesh_file_name, sound_file_name, param_node->getID());
	}
	return 1;
}

// начало главного цикла
int AppWorldLogic::update() {
	// Разместите здесь код, вызываемый перед обновлением каждого кадра рендеринга: укажите все связанные с графикой функции, которые должны вызываться каждый кадр во время выполнения вашего приложения.

	float ifps = Game::getIFps();

	// изменяем материал
	material->setParameterFloat4("albedo_color", vec4(Game::getRandomFloat(0.0f, 1.0f), Game::getRandomFloat(0.0f, 1.0f), Game::getRandomFloat(0.0f, 1.0f), 1.0f));

	// вращаем связанный узел
	param_node->setRotation(param_node->getRotation() * quat(0, 0, 30.0f * ifps));

	return 1;
}

int AppWorldLogic::postUpdate() {
	// Движок вызывает эту функцию перед рендерингом каждого кадра рендеринга: корректировка поведения после обновления состояния узла.

	return 1;
}

int AppWorldLogic::updatePhysics() {
	// Разместите здесь код, вызываемый перед обновлением каждого кадра физики: управление физикой в вашем приложении и размещение расчётов, не связанных с рендерингом.
	// Движок вызывает updatePhysics() с фиксированной частотой (по умолчанию 60 раз в секунду) независимо от значения FPS.
	// ПРЕДУПРЕЖДЕНИЕ: не создавайте, не удаляйте и не изменяйте трансформации узлов здесь, так как рендеринг уже выполняется.

	return 1;
}
// конец главного цикла

int AppWorldLogic::shutdown() {
	// Разместите здесь код, вызываемый при завершении работы мира: удаление ресурсов, созданных во время выполнения скрипта мира, чтобы избежать утечек памяти.
	// сохраняем текущий цвет материала (проверьте это в UnigineEditor, чтобы убедиться, что он был изменён)
	material->save();
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream) {
	// Разместите здесь код, вызываемый при сохранении состояния мира: сохранение пользовательских данных в файл.

	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream) {
	// Разместите здесь код, вызываемый при восстановлении состояния мира: восстановление пользовательских данных из файла здесь.

	UNIGINE_UNUSED(stream);
	return 1;
}

```

</details>


#### Реализация на C#


> **Примечание:** В проектах на C#, использующих [C# Component System](../../../principles/component_system/component_system_cs/index.md), доступ к файлам и узлам обычно [implemented via components](../../../code/csharp/usage/using_cs_component_system/index.md).


Ниже вы найдёте реализацию на C# примера, [described above](#example_description). Вы можете скопировать и вставить её в файл `AppWorldLogic.cs` вашего проекта.


<details>
<summary>AppWorldLogic.cs | Close</summary>

**AppWorldLogic.cs**


```csharp
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Unigine;

namespace UnigineApp
{
	class AppWorldLogic : WorldLogic
	{
		// Логика мира, вступает в силу только когда мир загружен.
		// Эти методы вызываются сразу после соответствующих методов скрипта мира (UnigineScript).
		Node my_node;						// узел, которому назначено свойство со ссылками
		Property property;					// свойство со всеми необходимыми ссылками
		Material material;					// связанный материал
		Node param_node;					// связанный узел
		SoundSource sound;					// источник звука для воспроизведения
		ObjectMeshStatic generated_obj;		// объект, который будет сгенерирован с использованием меша

		public AppWorldLogic()
		{
		}

		public override bool Init()
		{
			// получаем узел, которому назначено свойство со ссылками на ассеты
			my_node = World.GetNodeByName("my_object");

			// получаем свойство, которое будет использоваться для доступа ко всем необходимым файлам
			property = my_node.GetProperty();
			// используем доступ к параметрам свойства для выполнения нужных действий
			if (property) {
				// получаем материал из соответствующего параметра свойства
				material = property.GetParameterPtr("some_material").ValueMaterial;

				// получаем путь к файлу меша из соответствующего параметра свойства
				String mesh_file_name = property.GetParameterPtr("some_mesh").ValueFile;

				// создаём объект с использованием меша
				generated_obj = new ObjectMeshStatic(mesh_file_name);

				// устанавливаем позицию объекта относительно позиции другого узла
				generated_obj.WorldPosition = my_node.WorldPosition;
				generated_obj.Translate(-1.0f, 0.0f, 0.0f);

				// получаем путь к звуковому файлу из соответствующего параметра свойства
				String sound_file_name = property.GetParameterPtr("some_file").ValueFile;

				// получаем узел из соответствующего параметра свойства
				param_node = property.GetParameterPtr("some_node").ValueNode;

				// создаём и воспроизводим звук из файла
				sound = new SoundSource(sound_file_name);
				sound.MaxDistance = 100.0f;
				sound.Loop = 1;
				sound.Play();

				// выводим результаты в консоль
				Log.Message("Path to mesh file: {0}\nPath to sound file: {1}\nNode ID: {2}\n", mesh_file_name, sound_file_name, param_node.ID);
			}
			return true;
		}

		// начало главного цикла
		public override bool Update()
		{
			// Разместите здесь код, вызываемый перед обновлением каждого кадра рендеринга: укажите все связанные с графикой функции, которые должны вызываться каждый кадр во время выполнения вашего приложения.
			float ifps = Game.IFps;

			// изменяем материал
			 material.SetParameterFloat4("albedo_color", new vec4(Game.GetRandomFloat(0.0f, 1.0f), Game.GetRandomFloat(0.0f, 1.0f), Game.GetRandomFloat(0.0f, 1.0f), 1.0f));

			// вращаем связанный узел
			param_node.SetRotation(param_node.GetRotation() * new quat(0, 0, 30.0f * ifps));

			return true;
		}

		public override bool PostUpdate()
		{
			// Движок вызывает эту функцию перед рендерингом каждого кадра рендеринга: корректировка поведения после обновления состояния узла.
			return true;
		}

		// конец главного цикла

		public override bool Shutdown()
		{
			// Разместите здесь код, вызываемый при завершении работы мира: удаление ресурсов, созданных во время выполнения скрипта мира, чтобы избежать утечек памяти.
			// сохраняем текущий цвет материала (проверьте это в UnigineEditor, чтобы убедиться, что он был изменён)
			material.Save();

			return true;
		}

		public override bool Save(Stream stream)
		{
			// Разместите здесь код, вызываемый при сохранении состояния мира: сохранение пользовательских данных в файл.
			return true;
		}

		public override bool Restore(Stream stream)
		{
			// Разместите здесь код, вызываемый при восстановлении состояния мира: восстановление пользовательских данных из файла здесь.
			return true;
		}
	}
}

```

</details>


## Рабочий процесс C++ Component System


Если вы используете [C++ Component System](../../../principles/component_system/component_system_cpp/index.md) в вашем проекте, рекомендуется следующий рабочий процесс:


1. Создайте компонент, унаследовав класс от *[ComponentBase](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md)*. Шаблон этого класса доступен в заголовочном файле *UnigineComponentSystem.h*.
2. Добавьте поля для хранения ссылок на все необходимые узлы и файлы, материалы, меши и т.д. (с помощью макросов *PROP_PARAM*).
3. Сгенерируйте файл `*.prop` для этого класса (путём компиляции и запуска приложения).
4. Откройте ваш мир в UnigineEditor и назначьте свойство сгенерированного компонента нужным узлам.
5. Укажите все ссылки на используемые узлы, материалы, текстуры, меши, другие файлы, перетащив их из *[Asset Browser](../../../editor2/assets_workflow/index.md#asset_browser)* прямо в соответствующее поле свойства в окне *[Parameters](../../../editor2/interface/index.md#parameters)*. ![](assign_prop_params.gif) *Связывание узлов и ассетов со свойством.*
6. Экземпляр компонента создаётся при запуске вашего приложения. Этот экземпляр имеет переменные, обеспечивающие доступ ко всем используемым ассетам.


Более подробную информацию об использовании C++ Component System см. в [C++ Component System Usage Example](../../../code/usage/using_component_system/index.md).


## Глобальные свойства для нескольких миров


Иногда вам может понадобиться свойство со ссылками на ассеты (как [described above](#example_description)), которое вы хотите использовать в нескольких мирах - своего рода **глобальное самодостаточное свойство, не назначенное ни одному узлу**. Такое свойство можно использовать, например, для хранения настроек определённого типа оружия (FBX-модель, звуки стрельбы, узлы с системами частиц для VFX и т.д.), используемых глобально на различных уровнях игры.


Рабочий процесс здесь следующий:


1. Сначала мы создаём свойство для хранения ссылок на все узлы и ассеты, которые нам нужны, и сохраняем его в папку `data` нашего проекта. Например, свойство может выглядеть так: ```xml <?xml version="1.0" encoding="utf-8"?> <property version="2.16.0.2" name="my_property" parent_name="node_base" manual="1" editable="1"> <parameter name="some_float" type="float">30.5</parameter> <parameter name="some_string" type="string">Hello from my_property!</parameter> <parameter name="some_node" type="node">0</parameter> <parameter name="some_material" type="material"></parameter> <parameter name="some_mesh" type="file"></parameter> <parameter name="some_file" type="file"></parameter> </property> ```
2. Затем откройте UnigineEditor, найдите созданное свойство в окне *Properties*, щёлкните на нём правой кнопкой мыши и выберите *Create Child*. Будет создано свойство с именем `my_property_0` (при желании вы можете его переименовать). ![](inherit_property.png) *Создание дочернего свойства*
3. Левел-дизайнеры вносят изменения, перетаскивая все необходимые ассеты и узлы в соответствующие поля дочернего свойства `my_property_0`, а также устанавливая другие параметры (если есть). ![](assign_gprop_params.gif) *Связывание узлов и ассетов со свойством*
4. Программисты могут **получить доступ к любому из этих ассетов через это глобальное свойство из любого мира**. Так как мы не используем компоненты, нам придётся находить свойство со ссылками на ассеты по его имени (*my_property_0*). Поэтому в методе *[init()](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_init)* класса *WorldLogic* мы делаем следующее: ```cpp int AppWorldLogic::init() { /* ... */ PropertyPtr property = Properties::findManualProperty("my_property_0"); /* ... */ return 1; } ```
5. Теперь мы можем использовать свойство для получения доступа к узлам и файлам:

  - **чтобы получить материал**, мы можем просто использовать соответствующий параметр узла: ```cpp property->getParameterPtr("node_param_name")->getValueMaterial(); ```
  - **чтобы получить путь к файлу**, мы можем просто использовать: ```cpp const char *path = property->getParameterPtr("file_param_name")->getValueFile(); ``` Так как у нас есть путь к нашему файлу, мы можем использовать его, например: ```cpp // для создания ссылки на узел NodeReferencePtr node_ref = NodeReference::create(path_to_node_file); // для загрузки источника звука SoundSourcePtr sound = SoundSource::create(path_to_sound_file); ```


### Реализация на C++


Итак, реализация на C++ примера ([described above](#example)) для глобального свойства будет переписана, как показано ниже. Вы можете скопировать и вставить код в файл `AppWorldLogic.cpp` вашего проекта.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

**AppWorldLogic.cpp**


```cpp
#include "AppWorldLogic.h"
#include <UnigineMaterials.h>
#include <UnigineSounds.h>
#include <UnigineGame.h>
#include <UnigineWorld.h>
#include <UnigineFileSystem.h>

using namespace Unigine;
using namespace Math;
PropertyPtr property;              // свойство со всеми необходимыми ссылками
MaterialPtr material;              // связанный материал
NodePtr param_node;                // связанный узел
SoundSourcePtr sound;	      	   // источник звука для воспроизведения
ObjectMeshStaticPtr generated_obj; // объект, который будет сгенерирован с использованием меша

AppWorldLogic::AppWorldLogic() {

}

AppWorldLogic::~AppWorldLogic() {

}

int AppWorldLogic::init() {
	// получаем свойство, которое будет использоваться для доступа ко всем необходимым файлам, по его имени
	property = Properties::findManualProperty("my_property_0");
	// используем доступ к параметрам свойства для выполнения нужных действий
	if (property) {
		// получаем материал из соответствующего параметра свойства
		material = property->getParameterPtr("some_material")->getValueMaterial();

		// получаем путь к файлу меша из соответствующего параметра свойства
		const char *mesh_file_name = property->getParameterPtr("some_mesh")->getValueFile();

		// создаём объект с использованием меша
		generated_obj = ObjectMeshStatic::create(mesh_file_name);

		// устанавливаем позицию объекта относительно позиции другого узла
		generated_obj->setWorldPosition(my_node->getWorldPosition());
		generated_obj->translate(vec3(-1.0f, 0.0f, 0.0f));

		// получаем путь к звуковому файлу из соответствующего параметра свойства
		const char *sound_file_name = property->getParameterPtr("some_file")->getValueFile();

		// получаем узел из соответствующего параметра свойства
		param_node = property->getParameterPtr("some_node")->getValueNode();

		// создаём и воспроизводим звук из файла
		sound = SoundSource::create(sound_file_name);
		sound->setMaxDistance(100.0f);
		sound->setLoop(1);
		sound->play();

		// выводим результаты в консоль
		Log::message("Path to mesh file: %s\nPath to sound file: %s\nNode ID: %d\n", mesh_file_name, sound_file_name, param_node->getID());
	}
	return 1;
}

// начало главного цикла
int AppWorldLogic::update() {
	// Разместите здесь код, вызываемый перед обновлением каждого кадра рендеринга: укажите все связанные с графикой функции, которые должны вызываться каждый кадр во время выполнения вашего приложения.

	float ifps = Game::getIFps();

	// изменяем материал
	material->setParameterFloat4("albedo_color", vec4(Game::getRandomFloat(0.0f, 1.0f), Game::getRandomFloat(0.0f, 1.0f), Game::getRandomFloat(0.0f, 1.0f), 1.0f));

	// вращаем связанный узел
	param_node->setRotation(param_node->getRotation() * quat(0, 0, 30.0f * ifps));

	return 1;
}

int AppWorldLogic::postUpdate() {
	// Движок вызывает эту функцию перед рендерингом каждого кадра рендеринга: корректировка поведения после обновления состояния узла.

	return 1;
}

int AppWorldLogic::updatePhysics() {
	// Разместите здесь код, вызываемый перед обновлением каждого кадра физики: управление физикой в вашем приложении и размещение расчётов, не связанных с рендерингом.
	// Движок вызывает updatePhysics() с фиксированной частотой (по умолчанию 60 раз в секунду) независимо от значения FPS.
	// ПРЕДУПРЕЖДЕНИЕ: не создавайте, не удаляйте и не изменяйте трансформации узлов здесь, так как рендеринг уже выполняется.

	return 1;
}
// конец главного цикла

int AppWorldLogic::shutdown() {
	// Разместите здесь код, вызываемый при завершении работы мира: удаление ресурсов, созданных во время выполнения скрипта мира, чтобы избежать утечек памяти.
	// сохраняем текущий цвет материала (проверьте это в UnigineEditor, чтобы убедиться, что он был изменён)
	material->save();
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream) {
	// Разместите здесь код, вызываемый при сохранении состояния мира: сохранение пользовательских данных в файл.

	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream) {
	// Разместите здесь код, вызываемый при восстановлении состояния мира: восстановление пользовательских данных из файла здесь.

	UNIGINE_UNUSED(stream);
	return 1;
}

```

</details>


### Реализация на C#


Реализация на C# примера ([described above](#example)) для глобального свойства будет переписана, как показано ниже. Вы можете скопировать и вставить код в файл `AppWorldLogic.cs` вашего проекта.


<details>
<summary>AppWorldLogic.cs | Close</summary>

**AppWorldLogic.cs**


```csharp
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Unigine;

namespace UnigineApp
{
	class AppWorldLogic : WorldLogic
	{
		// Логика мира, вступает в силу только когда мир загружен.
		// Эти методы вызываются сразу после соответствующих методов скрипта мира (UnigineScript).
		Property property;					// свойство со всеми необходимыми ссылками
		Material material;					// связанный материал
		Node param_node;					// связанный узел
		SoundSource sound;					// источник звука для воспроизведения
		ObjectMeshStatic generated_obj;		// объект, который будет сгенерирован с использованием меша

		public AppWorldLogic()
		{
		}

		public override bool Init()
		{
			// получаем свойство, которое будет использоваться для доступа ко всем необходимым файлам, по его имени
			property = Properties.FindManualProperty("my_property_0");
			// используем доступ к параметрам свойства для выполнения нужных действий
			if (property) {
				// получаем материал из соответствующего параметра свойства
				material = property.GetParameterPtr("some_material").ValueMaterial;

				// получаем путь к файлу меша из соответствующего параметра свойства
				String mesh_file_name = property.GetParameterPtr("some_mesh").ValueFile;

				// создаём объект с использованием меша
				generated_obj = new ObjectMeshStatic(mesh_file_name);

				// устанавливаем позицию объекта относительно позиции другого узла
				generated_obj.WorldPosition = my_node.WorldPosition;
				generated_obj.Translate(-1.0f, 0.0f, 0.0f);

				// получаем путь к звуковому файлу из соответствующего параметра свойства
				String sound_file_name = property.GetParameterPtr("some_file").ValueFile;

				// получаем узел из соответствующего параметра свойства
				param_node = property.GetParameterPtr("some_node").ValueNode;

				// создаём и воспроизводим звук из файла
				sound = new SoundSource(sound_file_name);
				sound.MaxDistance = 100.0f;
				sound.Loop = 1;
				sound.Play();

				// выводим результаты в консоль
				Log.Message("Path to mesh file: {0}\nPath to sound file: {1}\nNode ID: {2}\n", mesh_file_name, sound_file_name, param_node.ID);
			}
			return true;
		}

		// начало главного цикла
		public override bool Update()
		{
			// Разместите здесь код, вызываемый перед обновлением каждого кадра рендеринга: укажите все связанные с графикой функции, которые должны вызываться каждый кадр во время выполнения вашего приложения.
			float ifps = Game.IFps;

			// изменяем материал
			 material.SetParameterFloat4("albedo_color", new vec4(Game.GetRandomFloat(0.0f, 1.0f), Game.GetRandomFloat(0.0f, 1.0f), Game.GetRandomFloat(0.0f, 1.0f), 1.0f));

			// вращаем связанный узел
			param_node.SetRotation(param_node.GetRotation() * new quat(0, 0, 30.0f * ifps));

			return true;
		}

		public override bool PostUpdate()
		{
			// Движок вызывает эту функцию перед рендерингом каждого кадра рендеринга: корректировка поведения после обновления состояния узла.
			return true;
		}

		// конец главного цикла

		public override bool Shutdown()
		{
			// Разместите здесь код, вызываемый при завершении работы мира: удаление ресурсов, созданных во время выполнения скрипта мира, чтобы избежать утечек памяти.
			// сохраняем текущий цвет материала (проверьте это в UnigineEditor, чтобы убедиться, что он был изменён)
			material.Save();

			return true;
		}

		public override bool Save(Stream stream)
		{
			// Разместите здесь код, вызываемый при сохранении состояния мира: сохранение пользовательских данных в файл.
			return true;
		}

		public override bool Restore(Stream stream)
		{
			// Разместите здесь код, вызываемый при восстановлении состояния мира: восстановление пользовательских данных из файла здесь.
			return true;
		}
	}
}

```

</details>
