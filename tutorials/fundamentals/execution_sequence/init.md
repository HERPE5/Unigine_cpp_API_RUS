# Engine Initialization


Эта статья подробно описывает шаги, выполняемые движком UNIGINE во время **инициализации**.


На этом этапе движок подготавливает все основные подсистемы, необходимые для запуска приложения и дальнейшего выполнения. Это включает разбор аргументов командной строки, инициализацию аппаратных интерфейсов и API, настройку файлов конфигурации, путей к логам и данным, создание внутренних потоков и подключение к графической, звуковой системам и системе ввода.


После завершения всех шагов инициализации движок полностью готов к запуску **[main loop](../../../code/fundamentals/execution_sequence/main_loop.md)**.


> **Примечание:** Шаги инициализации сопровождаются сообщениями в лог. Например, при открытии редактора эти сообщения можно наблюдать на вкладке *Console*, а при запуске приложения они отображаются во внутриигровой консоли (открывается по умолчанию клавишей **~**).
>
>
> Файлы логов также создаются по умолчанию в папке `/bin` вашего проекта.


**Первый кадр** обрабатывается особым образом, так как он завершает настройку основных систем и скриптов. По этой причине его шаги также перечислены в этой статье и считаются частью процесса инициализации.


Для остальных шагов и общей информации о последовательности выполнения см. статью [Execution Sequence](../../../code/fundamentals/execution_sequence/index.md).


## Шаги инициализации


| Engine Initialization |  |
|---|---|
| 1. | Основной поток приложения определяется и сохраняется для обеспечения [thread safety](../../../code/fundamentals/thread_safety/index.md) для операций, которые должны выполняться только в главном потоке. |
| 2. | **[Command-line options](../../../code/command_line.md)**, переданные при запуске, разбираются и сохраняются для последующей конфигурации. > **Примечание:** Значения из командной строки переопределяют значения по умолчанию и значения, указанные в [configuration files](../../../code/configuration_file_cpp.md). |
| 3. | Инициализируется **[System Info](../../../api/library/engine/class.systeminfo_cpp.md)** для предоставления доступа к информации о текущей аппаратной конфигурации. |
| 4. | Инициализируется API UNIGINE. |
| 5. | Определяются домашняя директория и директория приложения. Путь к папке, куда по умолчанию будут сохраняться все данные приложения: - Если вы передаёте [*project name*](../../../code/command_line.md#project_name) через командную строку или при инициализации движка, все данные (такие как файлы логов, кэш и файлы конфигурации) сохраняются в домашней директории пользователя следующим образом: - В Windows - в папке `C:/Users/<username>/<project_name>/` - В Linux - в папке `/home/<username>/.<project_name>/` - В противном случае данные сохраняются в папке приложения (`<PROJECT_DIRECTORY>/bin/` вместе с исполняемым бинарным файлом). |
| 6. | Восстанавливается история *[Console](../../../code/console/index.md)*. |
| 7. | [Third-Party Notices](../../../third_party.md) записываются в лог. |
| 8. | Загружаются и обрабатываются [configuration files](../../../code/configuration_file_cpp.md) и дополнительные зависимости (аргументы командной строки имеют более высокий приоритет); в лог записывается соответствующее сообщение: ```text ---- Configs ---- Loading boot config "D:/UNIGINE/UNIGINE Projects/MyProject/data/configs/editor.boot"... Loading user config "D:/UNIGINE/UNIGINE Projects/MyProject/data/configs/default.user"... Using config file "configs/default.config" Using boot config file "configs/editor.boot" Using user config file "configs/default.user" Using controls config file "configs/default.controls" Loading "dxgi.dll"... ``` |
| 9. | Разбираются оставшиеся **[command-line options](../../../code/command_line.md)** (те, что не были разобраны [previously](#cli_paths)). Эти опции задают базовые настройки видео, такие как графический API, используемый для рендеринга (DirectX или Vulkan; графический API также можно отключить), размер окна приложения и т.д. Вы также можете передать через командную строку любые внешние директивы *[#define](../../../code/command_line.md#extern_define)* и [console variables](../../../code/console/index.md#operation). > **Примечание:** Значения из командной строки переопределяют значения по умолчанию и значения, указанные в [configuration files](../../../code/configuration_file_cpp.md). |
| 10. | Инициализируется пользовательский [Memory Allocator](../../../principles/allocator/index.md) UNIGINE для более быстрого и оптимального выделения памяти по сравнению со стандартным системным аллокатором. В коде движка он задаётся через директиву *USE_MEMORY*. |
| 11. | Инициализируется GPU, и полная информация о текущем оборудовании [is written to the log](../../../api/library/engine/class.systeminfo_cpp.md#logInfo_void) (информация о движке, ОС, CPU и GPU). |
| 12. | Инициализируются [Microprofile](../../../tools/profiling/microprofile/index_cpp.md) и [Memory Profiler](../../../tools/profiling/profiler/index.md). Статус веб-сервера микропрофилировщика записывается в лог (если включено): ```text ---- Engine Microprofile ---- Microprofile initialization (Time: 0.6ms, Memory: 1.4KB) MicroProfile: Web server started on port 1338 ``` |
| 13. | Инициализируются [general-purpose thread pools](../../../code/fundamentals/thread_system/index.md#thread_pools). |
| 14. | Инициализируются внутренние потоки движка для специализированных задач. Подробности см. в статье [Threading](../../../code/fundamentals/thread_system/index.md). |
| 15. | Инициализируется [System Proxy](../../../api/library/engine/class.customsystemproxy_cpp.md) по умолчанию. Движок подключается к графической подсистеме, аудиоустройствам и системам ввода. В лог записывается соответствующее сообщение: ```text ---- System Proxy ---- SystemProxy initialization (Time: 0.0ms, Memory: 0B) ``` |
| 16. | Инициализируется [VR API](../../../code/command_line.md#vr_app). В лог записывается соответствующее сообщение: ```text ---- VR ---- VR initialization (Time: 0.0ms, Memory: 896B) ``` |
| 17. | Инициализируется [Rendering API](../../../code/command_line.md#video_app). В лог записывается соответствующее сообщение: ```text ---- Render ---- Renderer API: Direct3D 12.0 Maximum texture size: 16384 Maximum texture units: 16 DLSS is supported DLSS Streamline version: 2.8.12 FSR is supported FSR Version: 3.1.3 FSR Max Contexts: 8 Render initialization (Time: 5.2s, Memory: 25.6MB) ``` |
| 18. | Инициализируется Window Manager (подробности см. в классе [WindowManager](../../../api/library/gui/class.windowmanager_cpp.md)). |
| 19. | Инициализируется система ввода. |
| 20. | Инициализируются дисплеи (подробности см. в классе [Displays](../../../api/library/gui/class.displays_cpp.md)). |
| 21. | Инициализируются VR-подсистемы. В лог записывается соответствующее сообщение: ```text ---- VR Subsystems ---- VR Subsystems initialization (Time: 0.1ms, Memory: 17.4KB) ``` |
| 22. | Отображается [Boot screen](../../../code/gui/screens/index.md#boot) на основе [configuration file](../../../code/configuration_file_cpp.md) `default.boot`. |
| 23. | Инициализируется [File System](../../../principles/filesystem/index_cpp.md). В лог записывается соответствующее сообщение: ```text ---- Filesystem begin ---- App path:  D:/UNIGINE/UNIGINE Projects/MyProject/bin/ Data path: D:/UNIGINE/UNIGINE Projects/MyProject/data/ Save path: D:/UNIGINE/UNIGINE Projects/MyProject/bin/ Runtimes loaded: 7 (Time: 13.3ms, Memory: 245.8KB) Filesystem initialization (Time: 422.4ms, Memory: 1.6MB) ``` |
| 24. | Загружаются пресеты рендеринга, включая стандартные (Low, Medium, High и т.д.), а также любые пользовательские пресеты. |
| 25. | Загружаются шрифты консоли и профилировщика. |
| 27. | Инициализируется звуковая система. В лог записывается соответствующее сообщение: ```text ---- Sound ---- Loading "openal32.dll"... Renderer: OpenAL Soft on Realtek Digital Output (2- Realtek(R) Audio) OpenAL vendor: OpenAL Community ... Sound: openal Sound initialization (Time: 110.6ms, Memory: 6.9KB) ``` |
| 28. | Создаётся набор внутренних менеджеров (например, *[Game](../../../api/library/engine/class.game_cpp.md)*, *[Physics](../../../api/library/physics/class.physics_cpp.md)*, *[Materials](../../../api/library/rendering/class.materials_cpp.md)*, *[Properties](../../../api/library/engine/class.properties_cpp.md)*, *[Animations](../../../api/library/animations/class.animations_cpp.md)* и т.д.). Каждый из этих классов существует как единственный глобальный экземпляр (синглтон). |
| 29. | Запускается [asynchronous data streaming](../../../principles/data_streaming/index.md). |
| 30. | Загружаются меши, материалы и свойства. Если в файле конфигурации запуска движка указаны консольные переменные, связанные с предзагрузкой, PSO, шейдеры и материалы компилируются и кэшируются. ```text ---- Materials begin---- ---- MeshManager begin ---- Initialization meshes (Time: 18.7ms, Memory: 580.4KB) Total resources: 28 ---- MeshManager end ---- ---- Properties begin ---- Properties loaded: 2/2 (Time: 0.7ms, Memory: 36.0KB) ---- Properties end ---- Base materials loaded: 196/196 Materials loaded: 88/88 Load Materials (Time: 145.4ms, Memory: 3.6MB) Preload materials loaded: 81 (Time: 8.5ms, Memory: 768.1KB) Shaders compiled: 54 (Time: 71.9ms, Memory: 797.4KB) Total materials loaded: 365 (Time: 225.9ms, Memory: 5.1MB) ---- Materials end ---- ``` |
| 31. | Загружаются [Animations](../../../api/library/animations/class.animations_cpp.md). |
| 32. | Устанавливается [Loading screen](../../../code/gui/screens/index.md#loading). |
| 33. | Инициализируется и надлежащим образом настраивается главное окно приложения. |
| 34. | Статистика инициализации движка записывается в логи: ```text Engine initialization (Time: 4.4s, Memory: 587.1MB) ``` |
| 35. | Плагины загружаются из [plugin_path](../../../code/command_line.md#plugin_path) (по умолчанию папка `/bin/plugins` папки вашего проекта). Метод *[init()](../../../api/library/common/class.plugin_cpp.md#init_int)* всех плагинов вызывается после загрузки. В лог записывается соответствующее сообщение: ```text ---- Plugins ---- EnginePlugins: "UnigineFbxImporter" plugin is initialized EnginePlugins: "UnigineGLTFImporter" plugin is initialized EnginePlugins: "UnigineFbxExporter" plugin is initialized EnginePlugins: "UnigineUsdExchanger" plugin is initialized Plugins initialization (Time: 318.0ms, Memory: 9.0KB) ``` |
| First Frame |  |
| 1. | Инициализируется [Interpreter](../../../api/library/common/class.interpreter_cpp.md). |
| 2. | Выполняются консольные команды, переданные как аргументы командной строки. |
| 3. | Загружается [System Script](../../../code/fundamentals/execution_sequence/app_logic_system.md#usc_system_logic). |
| 4. | Инициализируются [System Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_init). - Вызывается метод системного скрипта [*init()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_init). - Вызывается метод SystemLogic [*init()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_init). |
| 5. | Очередь консольных команд сбрасывается, чтобы гарантировать обработку всех ожидающих команд. |
