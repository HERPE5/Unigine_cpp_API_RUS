# Creating C++ Plugin


Пользовательский библиотечный модуль (файл `*.dll` или `*.so`), содержащий набор сервисов и функций, можно загрузить и использовать в вашем приложении UNIGINE. Реализация такой библиотеки через интерфейс класса ***[Plugin](../../api/library/common/class.plugin_cpp.md)*** позволяет использовать систему плагинов UNIGINE для добавления и управления дополнительной функциональностью во время выполнения UNIGINE, выбирая, какие библиотеки загружать "на лету" без перекомпиляции исполняемого файла UNIGINE.


Это означает, что вы можете **упаковать** собственную функциональность в плагин, **повторно использовать** её в других проектах, **поделиться** ею со своей командой или даже **опубликовать** плагин в **[UNIGINE Add-On Store](https://store.unigine.com/)** и превратить его в инструмент, который другие разработчики смогут использовать *бесплатно* или как *платный продукт*.


Чтобы расширить функциональность UNIGINE, вы можете разработать два типа плагинов:


- **[Editor Plugin](../../editor2/extensions/custom_plugin.md)** - плагины, расширяющие возможности редактора UNIGINE. Например, вы можете добавлять пользовательские редакторы для объектов, реализовывать оверлеи вьюпорта и создавать UI-панели для собственных инструментов.
- **Engine Plugin** - плагины, расширяющие основную функциональность движка. Например, вы можете интегрировать сторонний SDK или добавить новые функции рендеринга.


Прежде чем приступить к реализации, обязательно ознакомьтесь с соглашениями об именовании файлов плагинов и их корректным размещением в структуре проекта.


> **Notice:** Эта статья описывает создание только **Engine Plugin**. Чтобы узнать, как создавать Editor Plugin, обратитесь к [this article](../../editor2/extensions/custom_plugin.md).


### См. также


- [Ready-to-use plugins](../../code/plugins/index.md) shipped with the ***UNIGINE SDK***
- Указывайте пользовательские пути к плагинам с помощью класса *[BootConfig](../../api/library/engine/class.bootconfig_cpp.md)*.
- См. класс *[Engine](../../api/library/engine/class.engine_cpp.md)* для методов добавления, удаления, получения информации и выполнения других операций, связанных с плагинами.


## Соглашения об именовании плагинов


Скомпилированные вами библиотеки должны соответствовать соглашению об именовании UNIGINE:


- Бинарные файлы Windows: **<VendorName><PluginName>_plugin_<precision>_x64<debug_version>.***
- Бинарные файлы Linux: **lib<VendorName><PluginName>_plugin_<precision>_x64<debug_version>.so**


> **Notice:** Плагины редактора требуют постфикс **_editorplugin** вместо **_plugin**.


**Пояснения:**


**<precision>** - определяет точность координат:


- **Single precision** - это поле опускается
- **Double precision** - используется слово ***double***


**<debug_version>** - определяет конфигурацию сборки:


- **Release build** - это поле опускается
- **Debug build** - добавляется постфикс ***d***


Пример: `VendorPluginName_plugin_double_x64d.dll`.


Таким образом, чтобы покрыть все возможные варианты использования (две операционные системы, две точности координат и две конфигурации сборки), потребуется собрать восемь бинарных файлов. Однако предоставлять полный набор не обязательно - вы можете скомпилировать только те варианты, которые нужны для вашего проекта.


## Путь к файлам плагина


Пользовательские файлы плагина должны располагаться в соответствующих папках. Они могут зависеть от сторонних библиотек и включать дополнительный контент, такой как изображения или модели. Плагин, как минимум, состоит из одного бинарного файла. Однако вы также можете распространять дополнительные ресурсы, такие как контент, документацию и полный исходный код.


Рекомендуемая структура для экспорта плагина выглядит следующим образом:


- бинарные файлы - `bin\plugins\<VendorName>\<PluginName>` (например, *bin\plugins\Vendor\Plugin\VendorPlugin_plugin_double_x64.dll*)
- заголовочные файлы и файлы расширений - `include\plugins\<VendorName>\<PluginName>\<VendorName><PluginName>.h` (например, *include\plugins\Vendor\Plugin\VendorPlugin.h*)
- сторонние библиотеки - `lib\plugins\<VendorName>\<PluginName>\`
- документация и описание плагина - `docs\plugins\<VendorName>\<PluginName>\`
- файлы контента, связанные с плагином - `data\plugins\<VendorName>\<PluginName>\`


Следование этой структуре гарантирует, что плагины автоматически обнаруживаются и загружаются движком, и остаются простыми для распространения и поддержки другими разработчиками.


Плагины, поставляемые с UNIGINE SDK, следуют той же структуре.


## 1) Настройка проекта плагина


Чтобы создать плагин, используйте встроенный **Engine Plugin Template**. Этот вариант можно выбрать при создании нового проекта.


Также необходимо заполнить поля **Plugin Name** и **Plugin Vendor**. Эти значения используются для автоматической генерации структуры проекта плагина и обеспечения соответствия [naming conventions](#naming).


![](template_engine_plugin.png)

*Template Engine Pluginin theCreate New Projecttab*


> **Notice:** Для существующего проекта перейдите в *Other Actions -> Configure*, затем выберите нужную функцию и нажмите *[Configure Project](../../sdk/projects/index_cpp.md#update_config)*.


После этого шага в папку вашего проекта UNIGINE будет добавлен проект плагина по умолчанию. Все необходимые файлы будут добавлены в соответствии с [path conventions](#path_to_plugin_files) и настройками вашего проекта API/IDE:


- **Windows OS: C++ (Qt-based / CMake) или UnigineScript** - для сборки плагина будет использоваться *CMake*.
- **Windows OS: C# (.NET) или C++ (Visual Studio)** - будет создан проект `.vcxproj`, и для сборки плагина будет использоваться *Visual Studio 2022*.
- **Linux** - для сборки плагина всегда будет использоваться *CMake*, независимо от конфигурации проекта.


Согласно соглашениям об именовании, конфигурация сборки шаблона и минимальные файлы реализации плагина будут размещены в следующей папке вашего проекта:


`source/plugins/<YourVendorName>/<YourPluginName>`


## 2) Реализация логики плагина


Теперь вы можете открыть проект плагина в предпочитаемой IDE или редакторе кода и изучить его содержимое.


Файл заголовка определяет виртуальный интерфейс, унаследованный от класса *[Plugin](../../api/library/common/class.plugin_cpp.md)*. Этот подход позволяет предоставить API, сохраняя при этом исходный код закрытым, если это необходимо при распространении плагина.


Например, если вы назвали свой плагин **"MyPlugin"**, реализация будет выглядеть следующим образом:


<details>
<summary>Plugin Header | Close</summary>

```cpp
#pragma once

#include <UniginePlugin.h>

class MyPlugin: public Unigine::Plugin
{
public:
	// конструктор и деструктор
	MyPlugin();
	virtual ~MyPlugin() override;

	// идентификация и конфигурация плагина
	int getCompilationFlags() const override;
	const char *get_name() override;
	void *get_data() override;
	int get_order() override;

	// жизненный цикл плагина
	int init() override;
	int shutdown() override;

	// логика обновления по кадрам
	void update() override;
	void postUpdate() override;
	void updatePhysics() override;
	void swap() override;

	// операции рендеринга и GUI
	void render(const Unigine::EngineWindowViewportPtr &window) override;
	void gui(const Unigine::EngineWindowViewportPtr &window) override;

	// загрузка и сохранение мира
	int loadWorld(const Unigine::XmlPtr &xml) override;
	int saveWorld(const Unigine::XmlPtr &xml) override;
};

```

</details>


Для обеспечения корректной интеграции с движком должны быть реализованы следующие методы плагина, например:


- **Конструктор** - вызывается при создании экземпляра плагина.
- **Деструктор** - вызывается при уничтожении экземпляра плагина.
- Метод **[init()](../../api/library/common/class.plugin_cpp.md#init_int)** - инициализирует плагин (вызывается один раз при загрузке движком). Здесь можно разместить код для выполнения действий, необходимых для инициализации плагина (если такие есть).
- Метод **[shutdown()](../../api/library/common/class.plugin_cpp.md#shutdown_int)** - вызывается при выгрузке плагина. Здесь можно разместить код, выполняемый при выгрузке плагина (при необходимости - специфическая очистка и другие действия).
- Метод **[get_name()](../../api/library/common/class.plugin_cpp.md#get_name_const_char_ptr)** - возвращает уникальное имя плагина. Это имя используется для поиска и управления плагином (загрузка, выгрузка и т.д.).
- Метод **[get_order()](../../api/library/common/class.plugin_cpp.md#get_order_int)** - определяет порядок выполнения плагина относительно других плагинов. Если не указан, плагин будет иметь порядок выполнения по умолчанию - 0.
- Метод **[get_data()](../../api/library/common/class.plugin_cpp.md#get_data_void_ptr)** - обычно используется для получения указателя на основной (публичный) интерфейс плагина. Может быть опущен, если не требуется.


Плагины с меньшими значениями порядка инициализируются и выполняются раньше (плагин с порядком 1 выполняется до плагина с порядком 2). Это гарантирует правильное разрешение зависимостей между плагинами (например, базовый служебный плагин должен быть загружен раньше плагинов, которые от него зависят).


Если ваш плагин должен работать синхронно с жизненным циклом движка (чтобы выполнять действия покадрово), вы можете реализовать методы *update(), render(), swap()* и другие методы, доступные в классе *[Plugin](../../api/library/common/class.plugin_cpp.md)*. Эти методы будут автоматически вызываться на соответствующем этапе [Execution Sequence](../../code/fundamentals/execution_sequence/index.md) движка.


Файл `.cpp` содержит непосредственную логику реализации вашего плагина.


<details>
<summary>Plugin Implementation | Close</summary>

```cpp
#include "MyPlugin.h"
using namespace Unigine;

extern "C" UNIGINE_EXPORT void *CreatePlugin()
{
	return new MyPlugin;
}

extern "C" UNIGINE_EXPORT void ReleasePlugin(void *plugin)
{
	delete reinterpret_cast<MyPlugin *>(plugin);
}

MyPlugin::MyPlugin()
{
}

MyPlugin::~MyPlugin()
{
}

int MyPlugin::getCompilationFlags() const
{
	// возвращаем флаги компиляции UNIGINE, для которых собран плагин (см. UNIGINE_COMPILATION_FLAG_)
	return UNIGINE_COMPILATION_FLAGS;
}

const char *MyPlugin::get_name()
{
	// возвращаем имя плагина

	// это имя будет использоваться для обращения к плагину
	// например, см. Engine::findPlugin(const char *name)

	return "MyPlugin";
}

void *MyPlugin::get_data()
{
	// возвращаем данные плагина

	// обычно это указатель на
	// публичный интерфейс данного плагина, если таковой имеется
	// см. Engine::getPlugin(const char *name)

	return nullptr;
}

int MyPlugin::get_order()
{
	// возвращаем порядок выполнения плагина
	return 0;
}

int MyPlugin::init()
{
	// движок вызывает эту функцию при инициализации плагина
	// должна возвращать 1 при успехе или 0 при ошибке

	// разместите здесь логику инициализации вашего плагина

	return 1;
}

int MyPlugin::shutdown()
{
	// движок вызывает эту функцию при выгрузке плагина
	// должна возвращать 1 при успехе или 0 при ошибке

	// разместите здесь логику деинициализации вашего плагина

	return 1;
}

void MyPlugin::update()
{
	// движок вызывает эту функцию перед обновлением каждого кадра рендеринга

	// разместите здесь логику обновления
}

void MyPlugin::postUpdate()
{
	// движок вызывает эту функцию после обновления каждого кадра рендеринга

	// разместите здесь логику пост-обновления
}

void MyPlugin::render(const Unigine::EngineWindowViewportPtr &window)
{
	// движок вызывает эту функцию перед рендерингом каждого кадра

	UNIGINE_UNUSED(window);
}

void MyPlugin::gui(const Unigine::EngineWindowViewportPtr &window)
{
	// движок вызывает эту функцию перед каждым кадром рендеринга GUI

	UNIGINE_UNUSED(window);
}

void MyPlugin::updatePhysics()
{
	// движок вызывает эту функцию перед обновлением каждого кадра физики

	// разместите здесь логику обновления физики
}

void MyPlugin::swap()
{
	// движок вызывает эту функцию перед свопом каждого кадра рендеринга
}

int MyPlugin::loadWorld(const Unigine::XmlPtr &xml)
{
	// движок вызывает эту функцию при загрузке мира
	// должна возвращать 1 при успехе или 0 при ошибке

	// здесь можно загрузить данные плагина из переданного xml

	UNIGINE_UNUSED(xml);

	return 1;
}

int MyPlugin::saveWorld(const Unigine::XmlPtr &xml)
{
	// движок вызывает эту функцию при сохранении мира
	// должна возвращать 1 при успехе или 0 при ошибке

	// здесь можно сохранить данные плагина в переданный xml

	UNIGINE_UNUSED(xml);

	return 1;
}

```

</details>


> **Notice:** Методы *CreatePlugin()* и *ReleasePlugin()* объявлены как *extern "C"*, чтобы компилироваться как обычные функции C. Это необходимо для предотвращения искажения имён функций (name mangling) и обеспечения совпадения схемы именования между исполняемым файлом UNIGINE и созданной динамической библиотекой. В противном случае бинарный код, сгенерированный двумя разными компиляторами C++, может оказаться несовместимым, поскольку не существует общепризнанного бинарного интерфейса приложений C++ (ABI).


### Базовый пример плагина


Если вы собираетесь вмешиваться в инициализацию движка, основной цикл или завершение работы, реализуйте классы, унаследованные от классов *[WorldLogic or SystemLogic](../../code/fundamentals/execution_sequence/app_logic_system.md)*. Вы можете реализовать собственную логику (а именно функции обратного вызова) в этих классах, а затем добавить её в движок для выполнения в его методах *init(), update(), shutdown()* и т.д. через интерфейс плагина.


> **Notice:** Для доступа к методам классов *World/SystemLogic* необходимо подключить `UnigineLogic.h`.


Помимо этого, вы можете определять **методы плагина** и **свободные (автономные) функции**, вызываемые из кода вашего приложения. В простых случаях эти методы и функции можно реализовать прямо в файле заголовка (например, как inline-функции), чтобы они были доступны как плагину, так и пользовательскому коду без дополнительной настройки.


В качестве примера реализуем следующий простой плагин с компонентами System и World logic, а также с методами плагина и свободными функциями, вызываемыми из вашего приложения UNIGINE (чуть позже мы увидим, как их использовать):


**Пример простого плагина:**


<details>
<summary>MyPlugin.h | Close</summary>

```cpp
#pragma once

#include <UniginePlugin.h>
#include <UnigineLogic.h>

using namespace Unigine;

// System logic:
class MySystemLogic : public SystemLogic {
public:
	// вызывается при инициализации системы
	virtual int init() override;

	// вызывается при завершении работы системы
	virtual int shutdown() override;
};

// World logic:
class MyWorldLogic : public WorldLogic {
public:
	// вызывается после инициализации мира
	virtual int init() override;

	// вызывается перед уничтожением или выгрузкой мира
	virtual int shutdown() override;
};

// Plugin implementation:
// этот класс - непосредственно плагин, загружаемый движком
class MyPlugin : public Plugin {
public:
	MyPlugin();
	virtual ~MyPlugin();

	// пример метода экземпляра (метод плагина)
	void printPluginMessage()
	{
		Log::message("printPluginMessage(): called for '%s'\n", get_name());
	};

	// методы интерфейса плагина:
	virtual int getCompilationFlags() const override;
	virtual const char* get_name() override;
	virtual void* get_data() override;
	virtual int get_order() override;

	virtual int init() override;
	virtual int shutdown() override;

private:
	// экземпляры system и world logic, управляемые плагином
	MySystemLogic system_logic;
	MyWorldLogic  world_logic;
};

// Free (standalone) function example:
// эта функция не является членом какого-либо класса
// её можно использовать как простой помощник, у неё нет доступа к 'this'
void printGlobalMessage()
{
	Log::message("printGlobalMessage(): free function called\n");
}

```

</details>


<details>
<summary>MyPlugin.cpp | Close</summary>

```cpp
#include "MyPlugin.h"

#include <UnigineEngine.h>
#include <UnigineLog.h>

using namespace Unigine;

// -------------------------
// MySystemLogic implementation
// -------------------------

int MySystemLogic::init() {
	// вызывается при инициализации system logic
	Log::message("MySystemLogic::init(): called\n");
	return 1;
}

int MySystemLogic::shutdown() {
	// вызывается при завершении работы system logic
	Log::message("MySystemLogic::shutdown(): called\n");
	return 1;
}

// -------------------------
// MyWorldLogic implementation
// -------------------------

int MyWorldLogic::init() {
	// вызывается при инициализации world logic
	Log::message("MyWorldLogic::init(): called\n");
	return 1;
}

int MyWorldLogic::shutdown() {
	// вызывается при завершении работы world logic
	Log::message("MyWorldLogic::shutdown(): called\n");
	return 1;
}

// -------------------------
// Plugin exports
// -------------------------

extern "C" UNIGINE_EXPORT void* CreatePlugin() {
	// вызывается движком для создания экземпляра плагина
	return new MyPlugin;
}

extern "C" UNIGINE_EXPORT void ReleasePlugin(void* plugin) {
	// вызывается движком для уничтожения экземпляра плагина
	delete reinterpret_cast<MyPlugin*>(plugin);
}

// -------------------------
// MyPlugin implementation
// -------------------------

MyPlugin::MyPlugin() {
	// конструктор: объект плагина создаётся здесь, но ещё не инициализирован
}

MyPlugin::~MyPlugin() {
	// деструктор: вызывается при уничтожении экземпляра плагина
}

int MyPlugin::getCompilationFlags() const {
	// возвращаем флаги компиляции UNIGINE, для которых собран плагин
	return UNIGINE_COMPILATION_FLAGS;
}

const char* MyPlugin::get_name() {
	// это имя используется движком для обращения к плагину
	return "MyPlugin";
}

void* MyPlugin::get_data() {
	// возвращаем данные плагина
	// обычно это указатель на публичный интерфейс плагина
	// в этом базовом примере мы просто возвращаем 'this'
	return this;
}

int MyPlugin::get_order() {
	// порядок выполнения плагина
	// меньшие значения инициализируются раньше
	return 0;
}

int MyPlugin::init() {
	// вызывается при инициализации плагина
	// здесь мы подключаем наши system и world logic к движку

	Engine* engine = Engine::get();

	engine->addSystemLogic(&system_logic);
	engine->addWorldLogic(&world_logic);

	return 1;
}

int MyPlugin::shutdown() {
	// вызывается при завершении работы плагина
	// здесь мы отключаем наши system и world logic от движка

	Engine* engine = Engine::get();

	engine->removeSystemLogic(&system_logic);
	engine->removeWorldLogic(&world_logic);

	return 1;
}

```

</details>


Если вы хотите скрыть реализацию внутри плагина и предоставить только чистый публичный API, конструкция усложняется. В этом случае обычно используется отдельный интерфейс (как показано в примере **[NodeViewerPlugin](#engine_plugin_sample)** ниже), чтобы движок и пользовательский код видели только интерфейс, а фактическая реализация оставалась внутри плагина.


## 3) Сборка плагина


После реализации кода плагина можно приступить к его сборке, чтобы сделать его доступным для использования в приложениях UNIGINE.


> **Notice:** - *Release*-версия движка требует *Release*-бинарники плагинов и не загружает *Debug*-версии! Для каждой версии приложения, использующей ваш плагин, обязательно собирайте соответствующую версию плагина.
> - **Не гарантируется бинарная совместимость плагинов между разными версиями SDK**. Например, плагин, собранный с SDK 2.20, может некорректно работать с SDK 2.21, и наоборот. Во избежание проблем совместимости рекомендуется всегда пересобирать плагин с использованием той же версии SDK, что используется в вашем приложении.


### Использование MS Visual Studio


Если вы используете *MS Visual Studio*, в папке вашего плагина есть файл `.vcxproj`. Укажите конфигурацию решения: *Release, Release-Double, Debug* или *Debug-Double*, и выберите *Build -> Build Solution* в меню или нажмите **Ctrl + Shift + B**.

  ![](../rebuild/configuration_p.png)
*1) Select the configuration that matches your project before building the plugin.*

  ![](../rebuild/build_p.png)
*2) Build the plugin project usingBuild -> Build SolutionorCtrl + Shift + B.*


Созданная библиотека плагина будет автоматически помещена в папку `bin/plugins`.


### Использование CMake


Если вы используете *CMake*, файл `CMakeLists.txt` автоматически добавляется в соответствующую папку вашего плагина внутри папки `source` вашего проекта UNIGINE. Чтобы собрать плагин, выполните следующие команды:


```text
cmake -B build -S .
cmake --build build

```


> **Notice:** Если вы добавляете в проект дополнительные файлы `*.cpp` или `*.h`, обязательно обновите `CMakeLists.txt` соответствующим образом, иначе эти файлы не будут скомпилированы и слинкованы в плагин.


## 4) Загрузка библиотеки плагина


На этом этапе плагин уже скомпилирован и может использоваться. Чтобы сделать его активным в проекте, его необходимо загрузить движком.


Для вашего удобства **Template Engine Plugin будет автоматически подключён в проекте**, в котором он был создан, с помощью *-extern_plugin*, поэтому дополнительная настройка не требуется!


Однако при работе с существующими (предварительно собранными) плагинами их необходимо явно подключать в проекте. Есть несколько способов указать, какие плагины должны быть подключены:


1. **Через командную строку при запуске** **Предпочтительный способ** - передать плагин в качестве аргумента командной строки с помощью `-extern_plugin`: ```text -extern_plugin VendorNamePluginName ``` > **Notice:** Имя плагина следует указывать **без префиксов и постфиксов**. Например, чтобы загрузить `VendorNamePluginName_plugin_x64d.dll`, используйте в команде `VendorNamePluginName`. Если путь к библиотеке относительный, он разрешается относительно исполняемого файла; также поддерживаются абсолютные пути.
2. **Через файл конфигурации** Также можно указать пути к плагинам и имена плагинов, которые будут загружены при запуске, непосредственно в файле конфигурации (`data/configs/default.boot`) > **Warning:** Настройки, заданные в файле конфигурации, **будут переопределены**, если используются соответствующие аргументы командной строки: > > > - *plugin_paths* будет переопределён *-plugin_path* > - *extern_plugins* будет переопределён *-extern_plugin*

  - ***plugin_paths*** - список [paths to directories](../../code/command_line.md#plugin_path), содержащим библиотеки плагинов. ```xml <plugin_paths> <path>plugins/</path> <path>../extra/plugins/</path> </plugin_paths> ```
  - ***extern_plugins*** - список [plugin libraries](../../code/command_line.md#extern_plugin) для загрузки. ```xml <extern_plugins> <plugin>UnigineSteam</plugin> <plugin>UnigineUltraleap</plugin> <plugin>UnigineDataBridge</plugin> </extern_plugins> ```


### Загрузка плагинов по требованию


Плагины также можно загружать непосредственно во время выполнения, что позволяет приложению активировать только необходимую функциональность по мере надобности.


Вы можете даже изменять плагин без завершения работы движка - просто выгрузите его, пересоберите и загрузите снова.


- **Через консоль** Плагины можно загружать, выгружать и перезагружать с помощью консольных команд: ```text Unigine~# plugin_load UnigineNodeViewerPlugin Loading "D:/UNIGINE/UNIGINE_Projects/PluginProject/bin/plugins/Unigine/NodeViewerPlugin/UnigineNodeViewerPlugin_plugin_double_x64d.dll"... EnginePlugins: "UnigineNodeViewerPlugin" plugin is initialized ```

  - [*plugin_load*](../../code/console/index.md#plugin_load)
  - [*plugin_unload*](../../code/console/index.md#plugin_unload)
  - [*plugin_reload*](../../code/console/index.md#plugin_reload)
- **Из World Logic или скрипта**

  - Добавьте и используйте плагин в **World Script** через *[engine.addPlugin()](../../api/library/engine/class.engine_cpp.md#addPlugin_const_char_ptr_bool)*.
  - То же самое можно сделать в **World Logic** проекта через *[Engine::addPlugin()](../../api/library/engine/class.engine_cpp.md#addPlugin_const_char_ptr_bool)*.
- **Из System Logic или скрипта**

  - Добавьте плагин в **System Script** или **System Logic**, а затем используйте его позже в **World Script** или **World Logic**. > **Notice:** Нельзя одновременно инициализировать плагин и вызывать его функции из того же **System Script**. Альтернативно, загрузите плагин [via the command-line argument](#command_line_plugin), а затем используйте его в System Script или System Logic.


## 5) Вызов функций библиотеки плагина


Чтобы получить доступ к классам и функциям библиотеки со стороны C++ приложения, выполните следующее:


1. Подключите файл заголовка плагина в вашем коде C++: ```cpp // заголовок плагина размещён в соответствии с соглашениями об именовании плагинов #include "plugins/Local/MyPlugin/MyPlugin.h" ``` > **Notice:** Если вы реализовали плагин только в файле `.cpp`, подключите его вместо создания отдельного файла заголовка.
2. Получите экземпляр плагина в World Logic проекта. Доступ к плагину зависит от его реализации. В нашем [basic example](#basic_plugin_example) (**MyPlugin**) вся логика реализована непосредственно в классе плагина, унаследованном от *[Unigine::Plugin](../../api/library/common/class.plugin_cpp.md)*, а API предоставлен через файл заголовка. <details> <summary>Show | Close</summary> ```cpp int AppWorldLogic::update() { if (Unigine::Input::isKeyDown(Unigine::Input::KEY_F8)) { // плагины поддерживают горячую перезагрузку - они могут загружаться или перезагружаться во время выполнения // поэтому рекомендуется выполнять дополнительные проверки перед вызовом любых // методов плагина, чтобы избежать ошибок, когда плагин недоступен // здесь движок будет искать загруженный плагин, вызывая методы get_name() int id = Unigine::Engine::get()->findPlugin("MyPlugin"); if (id != -1) { // свободная функция, определённая inline в заголовке плагина printGlobalMessage(); // прямой доступ к экземпляру плагина Unigine::Plugin* plugin = Unigine::Engine::get()->getPluginInterface(id); if (plugin) { // приведение к классу плагина и вызов его метода экземпляра MyPlugin* my_plugin = static_cast<MyPlugin*>(plugin); my_plugin->printPluginMessage(); } } } return 1; } ``` </details>
3. [Compile](../../code/cpp/application.md#logic) и запустите приложение C++.


![](basic_plugin_output.png)

*The plugin was loaded successfully, both logics were initialized, and both the free function and the plugin method were called correctly.*


## Пример плагина движка


Когда вы создаёте плагин с помощью **Engine Plugin Template**, конфигурация проекта также добавляет пример плагина под названием ***NodeViewerPlugin*** в качестве эталонной реализации. Вы можете использовать его как отправную точку для разработки собственного плагина или удалить его, если он не требуется.


***NodeViewerPlugin*** позволяет просматривать иерархию узлов в мире, выбирать узлы правой кнопкой мыши и перемещать/вращать/масштабировать их с помощью манипуляторов (гизмо). Окно плагина можно включать и выключать клавишей *F10*.


![](engine_plugin_sample.png)

*Node Viewer Window*


Давайте быстро рассмотрим исходный код:


Реализация плагина находится в классе `NodeViewerPluginImpl`. Он наследуется как от *[Unigine::Plugin](../../api/library/common/class.plugin_cpp.md)*, так и от `NodeViewerPlugin`.


- Интерфейс `NodeViewerPlugin` - это часть, доступная пользовательскому коду. Он предоставляет простые методы для работы с плагином, например, проверку его инициализации или показ и скрытие окна.
- Интерфейс ***[Unigine::Plugin](../../api/library/common/class.plugin_cpp.md)*** используется самим движком. Через этот интерфейс движок регистрирует плагин, выполняет его инициализацию и вызывает его метод *update()* каждый кадр.


В данной конструкции весь публичный API предоставляется через интерфейс `NodeViewerPlugin`, в то время как его фактическая реализация скрыта внутри `NodeViewerPluginImpl`.


### Реализация паттерна Singleton


В большинстве случаев плагины проектируются как **синглтоны**. Это означает, что в движке существует **только один экземпляр** плагина, и он доступен из любого места в коде. Вместо создания новых объектов пользователь просто получает существующий экземпляр и использует его публичные методы.


Распространённый подход - предоставить статический метод *get()*, возвращающий указатель на текущий экземпляр плагина:


<details>
<summary>Singleton Plugin | Close</summary>

```cpp
UNIGINE_INLINE static NodeViewerPlugin *get()
{
	static NodeViewerPlugin *instance = nullptr;
	static Unigine::EventConnection connection;
	static Unigine::Mutex m;

	if (instance == nullptr)
	{
		Unigine::ScopedLock l(m);

		if (instance == nullptr)
		{
			if (!connection.isValid())
			{
				Unigine::Engine::get()->getEventPluginRemoved().connect(
					connection,
					[](const char *name) {
						if (Unigine::String::equal(name, "NodeViewerPlugin"))
						{
							connection.disconnect();
							instance = nullptr;
						}
					}
				);
			}

			instance = Unigine::Engine::get()->getPlugin<NodeViewerPlugin>("NodeViewerPlugin");
		}
	}
	return instance;
}

```

</details>


По умолчанию плагин предоставляет переключение окна с помощью клавиши **F10**. Чтобы получить доступ к экземпляру плагина и вызывать его методы напрямую (в данном случае - показывать или скрывать окно вручную), обычно делают следующее:


<details>
<summary>Accessing Plugin Instance | Close</summary>

```cpp
#include "AppWorldLogic.h"
#include "plugins/Unigine/NodeViewerPlugin/NodeViewerPlugin.h"

AppWorldLogic::AppWorldLogic()
{}

AppWorldLogic::~AppWorldLogic()
{}

int AppWorldLogic::init()
{
	// загружаем плагин по имени при инициализации WorldLogic
	// также можно использовать:
	// аргумент запуска "-extern_plugin" или
	// консольную команду "plugin_load" во время выполнения

	// при загрузке плагина необходимо указать его полное имя:
	// Vendor + PluginName
	Unigine::Engine::get()->addPlugin("UnigineNodeViewerPlugin");
	return 1;
}

int AppWorldLogic::update()
{
	// скрываем окно плагина по F8
	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_F8))
	{
		// плагины поддерживают горячую перезагрузку - они могут загружаться или перезагружаться во время выполнения

		// поэтому рекомендуется выполнять дополнительные проверки перед вызовом любых
		// методов плагина, чтобы избежать ошибок, когда плагин недоступен

		// здесь движок будет искать загруженный плагин, вызывая методы get_name()
		// см. исходный код NodeViewerPlugin для реализации
		bool is_plugin_loaded = Unigine::Engine::get()->findPlugin("NodeViewerPlugin") != -1;

		if (is_plugin_loaded && NodeViewerPlugin::get()->isInitialized())
		{
			NodeViewerPlugin::get()->setVisible(false);
		}
	}

	// показываем окно плагина по F9
	if (Unigine::Input::isKeyDown(Unigine::Input::KEY_F9))
	{
		// здесь применяется та же логика
		bool is_plugin_loaded = Unigine::Engine::get()->findPlugin("NodeViewerPlugin") != -1;

		if (is_plugin_loaded && NodeViewerPlugin::get()->isInitialized())
		{
			NodeViewerPlugin::get()->setVisible(true);
		}
	}

	return 1;
}

```

</details>


## Доступ к плагину C++ из проекта C#


Поскольку плагин собирается как нативная библиотека, его можно легко добавить и загрузить в проект C# [the same way as in C++ project](#step_4). Однако, если плагин предоставляет публичный API, который должен вызываться из C#, требуется дополнительный слой для связи нативного кода C++ и управляемого кода C#.


Для этой цели можно использовать Add-On **C# API Generator**, который автоматически генерирует как нативные обёртки (C++), так и слой управляемого API (C#) для ваших плагинов:


- **[C# API Generator](https://store.unigine.com/en/add-on/1f0734b4-b7f2-6c80-b381-950ea7ab9eab/description)** Add-On available in the *UNIGINE Add-On Store*
