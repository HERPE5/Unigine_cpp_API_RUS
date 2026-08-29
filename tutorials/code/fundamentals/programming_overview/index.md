# Programming Overview


Эта статья описывает способы создания проектов в Unigine.


Основная цель статьи - дать представление о настройке среды разработки и обзор программирования. Она содержит ссылки на другие статьи, помогающие подготовить среду разработки, выбрать язык программирования и так далее.


## Языки


Для создания собственного проекта на Unigine вы можете использовать следующие языки программирования:


- [UnigineScript](../../../code/uniginescript/index.md)
- C++, используя [C++ API](../../../api/index.md)
- C#, используя [C# API](../../../code/csharp/index.md)


UnigineScript можно легко расширить через API Unigine. Движок Unigine позволяет экспортировать код C++ и C# и наоборот. Вы можете написать некоторую функциональность на языке C++ или C# и экспортировать её в UnigineScript. Подробнее см. статьи с примерами использования *[C++ API](../../../code/cpp/usage/index.md)* и *[C# API](../../../code/csharp/usage/index.md)*.


## Платформы


Unigine поддерживает следующие платформы:


- Windows (10/11)
- Linux (ядро 4.19+)


Для разработки приложений с использованием UNIGINE 2 SDK требуется 64-битная система. Движок полностью и эффективно использует многоядерную архитектуру CPU.


С Unigine вы можете собирать приложения для этих платформ из единой кодовой базы.


Подробнее см. [Hardware Requirements](../../../start/requirements.md).


## Среды разработки


Вы можете использовать любую из этих ПК-платформ для написания вашего проекта на Unigine:


- Windows
- Linux


Помимо UNIGINE SDK, каждая платформа требует специфического программного обеспечения, которое нужно установить для начала разработки. Требования для каждой платформы вы можете найти здесь:


- [development for Windows](../../../code/environment/windows.md)
- [development for Linux](../../../code/environment/linux.md)


## Последовательность выполнения


[Application Logic System](../../../code/fundamentals/execution_sequence/app_logic_system.md) Unigine имеет три основных концепции логики:


- **System logic** - логика приложения. Вы можете реализовать свою логику, которая будет выполняться в течение жизненного цикла приложения. Пользовательскую логику можно разместить в файле [system script](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic) (*используя только UnigineScript API*), либо можно унаследовать [SystemLogic class](../../../api/library/common/logic/class.systemlogic_cpp.md) и реализовать свою логику (*C++ и C# API*). Системный файл скрипта UnigineScript `unigine.usc` создаётся автоматически в папке вашего проекта. При создании нового *проекта на C++ / C#* он уже наследует класс системной логики с реализованными методами, куда можно поместить код логики.
- **World logic** - логика мира - здесь следует размещать логику виртуальной [scene](../../../start/index.md#world). Логика вступает в силу при загрузке мира. Вы можете разместить свою логику в файле [world script](../../../code/fundamentals/execution_sequence/app_logic_system.md#world_logic) (*используя только UnigineScript API*), либо можно унаследовать [WorldLogic class](../../../api/library/common/logic/class.worldlogic_cpp.md) и реализовать свою логику (*C++ и C# API*). Файл скрипта мира `*.usc` автоматически создаётся вместе с новым миром и имеет имя вашего проекта. При создании нового *проекта на C++ / C#* он уже наследует класс логики мира с реализованными методами, куда можно поместить код логики.
- **Editor logic** - этот компонент используется в случае, если вам нужно реализовать собственный редактор. У него больше реализованных методов, дающих чёткое понимание текущих событий движка (узел был создан, свойство было удалено, материал был изменён и т.д.). Вы можете унаследовать [EditorLogic class](../../../api/library/common/logic/class.editorlogic_cpp.md) и реализовать свою логику на C++ или C#. Логика редактора по умолчанию на UnigineScript загружается из файла `editor2/editor.usc`, хранящегося внутри `editor2.ung`. Вы можете переопределить этот файл логики UnigineScript, создав папку с именем `editor2` в вашей папке `data` и поместив туда файл `editor.usc` со следующим кодом (вы можете изменять этот скрипт, но не удаляйте существующие строки *include*, так как они необходимы для работы редактора): <details> <summary>editor.usc | Close</summary> *editor.usc* ```text #include <editor2/editor_tracker.h> #include <editor2/editor_video_grabber.h> int init() { return 1; } int update() { return 1; } int shutdown() { return 1; } ``` </details>


> **Примечание:** В случае наследования классов `*Logic` (*C++ / C#*), реализованные методы будут вызваны сразу после соответствующих методов скриптов.


Внутренний код движка UNIGINE и логика приложения выполняются в заранее определённом порядке:


1. [**Initialization**](../../../code/fundamentals/execution_sequence/init.md). На этом этапе подготавливаются и инициализируются необходимые ресурсы. Как только эти ресурсы готовы к использованию, движок входит в главный цикл.
2. [**Main loop**](../../../code/fundamentals/execution_sequence/main_loop.md). Когда UNIGINE входит в главный цикл, все его действия можно разделить на три этапа, которые выполняются один за другим по циклу. Этот цикл повторяется каждый кадр, пока приложение работает.

  1. Этап [Update](../../../code/fundamentals/execution_sequence/main_loop.md#update), содержащий всю логику вашего приложения, выполняемую каждый кадр
  2. Этап [Rendering](../../../code/fundamentals/execution_sequence/main_loop.md#postUpdate), содержащий все операции, связанные с рендерингом, расчёты симуляции физики и поиск пути
  3. Этап [Swap](../../../code/fundamentals/execution_sequence/main_loop.md#swap), содержащий все операции синхронизации, выполняемые для переключения между буферами
3. [**Shutdown**](../../../code/fundamentals/execution_sequence/shutdown.md). Когда UNIGINE останавливает выполнение приложения, он выполняет операции, связанные с завершением работы приложения и очисткой ресурсов.


Прочитайте [this article](../../../code/fundamentals/execution_sequence/code_update.md), чтобы узнать, куда помещать код вашей логики.


Также прочитайте статьи [Execution Sequence](../../../code/fundamentals/execution_sequence/index.md) и [Logic System](../../../code/fundamentals/execution_sequence/app_logic_system.md), чтобы узнать подробный рабочий процесс движка Unigine.


## Применение логики к объектам


Чтобы объект удобно интегрировался в логику приложения, необходимо указать набор пользовательских параметров и способ, которым объект будет вести себя и взаимодействовать с другими объектами и окружением сцены.


В зависимости от языка программирования, выбранного в UNIGINE, вы также определяете способ применения логики к объектам:


- Путём назначения C# [**components**](../../../api/library/common/logic/component_system/cs/class.component.md), которые являются частью [**C# Component System**](../../../principles/component_system/component_system_cs/index.md) (.NET), включённой по умолчанию и интегрированной в UnigineEditor. Это самый простой способ реализовать логику вашего приложения: все параметры и логика добавляются в компоненты, которые можно назначить любому узлу для выполнения.
- Путём назначения [**properties**](../../../principles/world_structure/index.md#properties) (для C++). Свойства можно использовать самостоятельно для [**accessing nodes and files**](../../../code/fundamentals/file_access/index.md) или как неотъемлемую часть [**C++ Component System**](../../../principles/component_system/component_system_cpp/index.md) для расширения функциональности узлов. В то время как свойство представляет собой тег для логики и предоставляет набор пользовательских параметров, логический **компонент** объединяет узел, класс C++, содержащий реализацию логики, и свойство.


Чтобы узнать больше об использовании систем компонентов, см. следующие статьи с примерами использования:


- [**Using C# Component System**](../../../code/csharp/usage/using_cs_component_system/index.md)
- [**Using C++ Component System**](../../../code/usage/using_component_system/index.md)


## Примеры использования


Есть три раздела с примерами использования:


- [UnigineScript Sample](../../../code/uniginescript/application.md)
- [C++ Sample](../../../code/cpp/application.md)
- [C# Sample](../../../code/csharp/application.md)


Программный код одинаков для всех поддерживаемых платформ, разница только в компиляции.


Для всех этих примеров мы создаём новые проекты с помощью [SDK Browser](../../../sdk/projects/index_cpp.md#creation). Каждый мир содержит базовый набор контента, включая источник [World Light](../../../objects/lights/world/index.md), плоский меш и несколько объектов.
