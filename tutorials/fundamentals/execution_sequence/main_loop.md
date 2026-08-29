# Engine Main Loop


Эта статья подробно описывает шаги, выполняемые движком UNIGINE каждый кадр: **Update**, **Render** и **Swap**.


Почти на каждом этапе выполнения движок **генерирует события**. Вы можете подписаться на эти события и выполнять собственный код при их возникновении, что даёт гибкую настройку логики приложения за пределами стандартных методов жизненного цикла.


Общее время, затраченное главным циклом, отображается счётчиком ***Total*** в [Performance Profiler](../../../tools/profiling/profiler/index.md).


Для остальных шагов и общей информации о последовательности выполнения см. статью [Execution Sequence](../../../code/fundamentals/execution_sequence/index.md).


## Этап Update


**Update Stage** - это этап подготовки к рендерингу следующего кадра и основной этап, на котором выполняется логика приложения.


На этом этапе движок:


<details>
<summary>Update Steps</summary>

| Update Prepare | Related Event |
|---|---|
| 1. Приоритет процесса в операционной системе корректируется. |  |
| 2. Обновляется [Input](../../../api/library/controls/class.input_cpp.md), включая стандартный и VR. | *[EventBeginInputUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginInputUpdate_Event) [EventEndInputUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndInputUpdate_Event)* |
| 3. Движок пробуждает рабочие потоки в [thread pools](../../../code/fundamentals/thread_system/index.md#thread_pools) для обработки ожидающих задач. |  |
| 4. Если мир был выгружен в предыдущем кадре и должен быть загружен новый мир, движок загружает его со всеми применёнными настройками. |  |
| 5. Обновляется [Console](../../../code/console/index.md). Выполняются все ожидающие консольные команды, вызванные в течение предыдущего кадра. Команды выполняются в начале этапа Update, но до обновления скриптов, так как иначе они могут нарушить текущий процесс рендеринга или физических расчётов. |  |
| 6. Движок готовится к рендерингу следующего кадра. |  |
| Main Update | *[EventBeginUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginUpdate_Event)* |
| 1. Движок обновляет [properties](../../../principles/properties/index.md). Этот шаг независим от системы компонентов и обрабатывает такие случаи, как смена родителя свойства. | *[EventBeginPropertiesUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginPropertiesUpdate_Event) [EventEndPropertiesUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndPropertiesUpdate_Event)* |
| 2. Обновляются [Controls](../../../api/library/controls/class.controls_cpp.md). | *[EventBeginControlsUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginControlsUpdate_Event) [EventEndControlsUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndControlsUpdate_Event)* |
| 3. Обновляется World Manager, отвечающий за потоковую передачу ресурсов изображений и мешей. | *[EventBeginWorldManagerUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginWorldManagerUpdate_Event) [EventEndWorldManagerUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndWorldManagerUpdate_Event)* |
| 4. Обновляется Sound Manager, отвечающий за потоковую передачу звуковых ресурсов. | *[EventBeginSoundManagerUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginSoundManagerUpdate_Event) [EventEndSoundManagerUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndSoundManagerUpdate_Event)* |
| 5. Движок обновляет состояние класса *[Game](../../../api/library/engine/class.game_cpp.md)* и пересчитывает [Time](../../../api/library/engine/class.game_cpp.md#getTime_float). | *[EventBeginGameUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginGameUpdate_Event) [EventEndGameUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndGameUpdate_Event)* |
| 6. Обновляется класс *[Render](../../../api/library/rendering/class.render_cpp.md)*. Это включает запекание освещения, тайминг анимации, материалы и позиции камер. | *[EventBeginRenderUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginRenderUpdate_Event) [EventEndRenderUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndRenderUpdate_Event)* |
| 7. Движок обновляет [Expressions](../../../api/library/common/class.expression_cpp.md) и устанавливает новое игровое время для корректной работы ГПСЧ. | *[EventBeginExpressionUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginExpressionUpdate_Event) [EventEndExpressionUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndExpressionUpdate_Event)* |
| 8. Обновляется [Sound](../../../api/library/engine/class.sound_cpp.md), и всё потоковое аудио начинает воспроизводиться. | *[EventBeginSoundsUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginSoundsUpdate_Event) [EventEndSoundsUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndSoundsUpdate_Event)* |
| 9. Инициализируются [World Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic) и [Editor Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic). Это означает, что если был загружен новый мир (либо при запуске приложения, либо при переключении миров), его скрипт мира и логика инициализируются здесь. Метод [*init()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_init) всех ваших компонентов также вызывается, так как система компонентов наследуется от WorldLogic. Это включает как компоненты, которые уже существовали в мире, так и те, что были добавлены во время выполнения - все они получают вызов *init()* на этом этапе. - Вызывается метод скрипта мира [*init()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_init). - Вызывается метод WorldLogic [*init()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_init) (вызывается метод *init()* компонентов. Порядок инициализации компонентов можно задать: см. описание класса компонента для *[C++](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#methods_order)* или для *[C#](../../../api/library/common/logic/component_system/cs/class.component.md#methods)*). - Вызывается метод скрипта редактора [*worldInit()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_worldInit). - Вызывается метод EditorLogic [*worldInit()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_worldInit). |  |
| 10. Обновляются [Plugins](../../../api/library/common/class.plugin_cpp.md). Вызывается метод *[update()](../../../api/library/common/class.plugin_cpp.md#update_void)* всех плагинов. Используйте *[get_order()](../../../api/library/common/class.plugin_cpp.md#get_order_int)*, чтобы задать приоритет обновления каждого плагина. | *[EventBeginPluginsUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginPluginsUpdate_Event)* *[EventEndPluginsUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndPluginsUpdate_Event)* |
| 11. Обновляется [VR](../../../api/library/vr/class.vr_cpp.md), настраивая внутренние параметры рендеринга и применяя разобранные консольные команды. | *[EventBeginVRUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginVRUpdate_Event)* *[EventEndVRUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndVRUpdate_Event)* |
| 12. Обновляются [Editor Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic). - Вызывается метод скрипта редактора *[update()](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_update)*. - Вызывается метод EditorLogic *[update()](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_update)*. | *[EventBeginEditorUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginEditorUpdate_Event)* *[EventEndEditorUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndEditorUpdate_Event)* |
| 13. Обновляются [System Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic). - Вызывается метод системного скрипта [*update()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_update). - Вызывается метод SystemLogic [*update()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_update). | *[EventBeginSystemScriptUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginSystemScriptUpdate_Event)* *[EventEndSystemScriptUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndSystemScriptUpdate_Event)* *[EventBeginSystemLogicUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginSystemLogicUpdate_Event)* *[EventEndSystemScriptUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndSystemScriptUpdate_Event)* |
| 14. Обновляются [World Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#world_logic). - Выполняются [World Expressions](../../../objects/worlds/world_expression/index.md). - [Node References](../../../objects/nodes/reference/index.md) планируются к загрузке. - Вызывается World Logic [*updateAsyncThread()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_updateAsyncThread) (вызывается метод *updateAsyncThread()* компонентов. Порядок выполнения компонентов можно задать: см. описание класса компонента для *[C++](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#methods_order)* или для *[C#](../../../api/library/common/logic/component_system/cs/class.component.md#methods)*) - Вызывается World Logic [*updateSyncThread()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_updateSyncThread) (вызывается метод *updateSyncThread()* компонентов) - Вызывается метод скрипта мира [*update()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_update). - Вызывается World Logic [*update()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_update) (вызывается метод *update()* компонентов) - Обновляется состояние узлов, существующих в мире (в основном для видимых узлов): проигрывается скелетная анимация, системы частиц порождают новые частицы, игроки перемещаются и т.д. - Узлы предварительно рендерятся - Обновляются (или порождаются при необходимости) [World Clutters](../../../objects/worlds/world_clutter/index.md) - Вызываются события [Node Trigger](../../../objects/nodes/trigger/index.md) (см. класс [NodeTrigger](../../../api/library/nodes/class.nodetrigger_cpp.md)) - Вызываются события [World Trigger](../../../objects/worlds/world_trigger/index.md) (см. класс [WorldTrigger](../../../api/library/worlds/class.worldtrigger_cpp.md)) | *[EventBeginWorldUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginWorldUpdate_Event)* *[EventEndWorldUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndWorldUpdate_Event)* |
| 15. Обновляются [Animations](../../../principles/animations/index.md) на основе нового времени. | *[EventBeginAnimationManagerUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginAnimationManagerUpdate_Event)* *[EventEndAnimationManagerUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndAnimationManagerUpdate_Event)* |
| 16. Обновляется GUI движка. |  |
| PostUpdate Stage |  |
| 1. Выполняется постобновление [World Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#world_logic). - Вызывается метод скрипта мира [*postUpdate()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_postUpdate). - Вызывается метод WorldLogic [*postUpdate()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_postUpdate) (вызывается метод *postUpdate()* компонентов. Порядок выполнения компонентов можно задать: см. описание класса компонента для *[C++](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#methods_order)* или для *[C#](../../../api/library/common/logic/component_system/cs/class.component.md#methods)*). - Рендерится пространственное дерево мира. | *[EventBeginWorldPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginWorldPostUpdate_Event)* *[EventEndWorldPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndWorldPostUpdate_Event)* |
| 2. Выполняется постобновление [System Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic). - Вызывается метод системного скрипта [*postUpdate()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_postUpdate). - Вызывается метод SystemLogic [*postUpdate()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_postUpdate). | *[EventBeginSystemScriptPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginSystemScriptPostUpdate_Event)* *[EventEndSystemScriptPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndSystemScriptPostUpdate_Event)* *[EventBeginSystemLogicPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginSystemLogicPostUpdate_Event)* *[EventEndSystemLogicPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndSystemLogicPostUpdate_Event)* |
| 3. Выполняется постобновление [Editor Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic). - Вызывается метод скрипта редактора [*postUpdate()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_postUpdate). - Вызывается метод EditorLogic [*postUpdate()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_postUpdate). | *[EventBeginEditorPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginEditorPostUpdate_Event)* *[EventEndEditorPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndEditorPostUpdate_Event)* |
| 4. Выполняется постобновление [Plugins](../../../api/library/common/class.plugin_cpp.md). Вызывается метод *[postUpdate()](../../../api/library/common/class.plugin_cpp.md#postUpdate_void)* всех плагинов. Используйте *[get_order()](../../../api/library/common/class.plugin_cpp.md#get_order_int)*, чтобы задать приоритет постобновления каждого плагина. | *[EventBeginPluginsPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginPluginsPostUpdate_Event)* *[EventEndPluginsPostUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndPluginsPostUpdate_Event)* |
| 5. Обрабатывается [File System](../../../principles/filesystem/index_cpp.md), вызывая соответствующие события (см. класс *[FileSystem](../../../api/library/filesystem/class.filesystem_cpp.md)*) | *[EventBeginFilesystemUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginFilesystemUpdate_Event)* *[EventEndFilesystemUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndFilesystemUpdate_Event)* |
| 6. Обновляется внутренняя очередь асинхронных задач движка. Добавляются новые задачи для последующего выполнения, такие как задачи [data streaming](../../../principles/data_streaming/index.md). |  |
| 7. Пакет асинхронных задач выполняется в отдельных потоках, взятых из внутреннего пула потоков движка: - Планируется обновление World Spatial Tree. - Обновляются буферы, используемые для частиц (только для Vulkan API). - Выполняется загрузка файлов/мешей/узлов по требованию через AsyncQueue. - Выполняются асинхронные операции ландшафта. - Выполняются асинхронные задачи, обновлённые на шаге **6**. - Выгружаются неиспользуемые скелетные меши. | *[EventBeginSpatialUpdate](../../../api/library/engine/class.engine_cpp.md#getEventBeginSpatialUpdate_Event)* |
| 8. Обновляются операции и текстуры [Landscape](../../../api/library/objects/landscape_terrain/class.landscape_cpp.md) для корректного выполнения. |  |
| 9. Обновляются [Mesh Decals](../../../objects/decals/mesh/index.md). |  |
| 10. Обновляется WindowManager (обновляется GUI). |  |
| 11. Теперь движок ждёт, пока все задачи, запущенные на шаге **7**, не завершатся. |  |
| 12. Выполняется поток поиска пути (Pathfinding). | *[EventBeginPathfinding](../../../api/library/engine/class.engine_cpp.md#getEventBeginPathfinding_Event)* *[EventEndSpatialUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndSpatialUpdate_Event)* |
| 13. Если режим обновления физики настроен на выполнение перед рендерингом, движок запускает **[physics simulation](#physics)** и ждёт её завершения. | *[EventEndUpdate](../../../api/library/engine/class.engine_cpp.md#getEventEndUpdate_Event)* |

</details>


## Этап Render


Этап Render - это фаза главного цикла, на которой отрисовывается текущий мир и подготавливается финальное изображение для показа.


Этот этап выполняет конвейер рендеринга, обновляет визуальные ресурсы и создаёт кадр, который будет отображён на экране.


Рендеринг выполняется по-разному в зависимости от режима приложения. Если VR включён, сначала выполняется предварительный проход рендеринга для VR-устройства. Этот проход включает следующие шаги:


<details>
<summary>VR Rendering Steps</summary>

| VR Render Stage | Related Event |
|---|---|
| 1.Камера игрока обновляется в соответствии с положением HMD в реальном мире, включая позицию, ориентацию и специфичные для VR параметры |  |
| 2. Рендеринг подготавливается со специфичными для API задачами: настройка или переиспользование VR swapchain'ов и настройка видовых окон и матриц проекции для каждого глаза. | *[EventBeginVRRender](../../../api/library/engine/class.engine_cpp.md#getEventBeginVRRender_Event)* |
| 3. Сцена рендерится отдельно для каждого глаза в соответствующие буферы swapchain, используя параметры вида и проекции VR. |  |
| 4. Применяются зависящие от устройства шаги (например, Motion Prediction). |  |
| 5. Компонуются дополнительные оверлейные или quad-слои (если есть), и завершённые кадры отправляются в VR-рантайм. |  |
| 6. Этап VR-рендеринга завершён. | *[EventEndVRRender](../../../api/library/engine/class.engine_cpp.md#getEventEndVRRender_Event)* |

</details>


После завершения VR-рендеринга (или если VR-режим отключён) движок выполняет основную последовательность рендеринга для окна приложения. Подробное описание конвейера рендеринга выходит за рамки этой статьи и приведено в статье **[Rendering Sequence](../../../principles/render/sequence/index.md)**.


<details>
<summary>Regular Rendering Steps</summary>

| Regular Render Stage | Related Event |
|---|---|
| 1. Настраиваются окна для рендеринга | *[EventBeginRender](../../../api/library/engine/class.engine_cpp.md#getEventBeginRender_Event)* |
| 2. При необходимости рендерятся элементы GUI. |  |
| 3. UNIGINE рендерит графическую сцену (мир). Графическая сцена отправляется на GPU. Как только CPU завершает подготовку данных и передаёт команды рендеринга на GPU, GPU занимается рендерингом кадра. Общее время [rendering stage](../../../principles/render/sequence/index.md) отображается счётчиком Render CPU в Performance Profiler. После этого CPU свободен, поэтому мы можем загрузить его нужными нам расчётами. | *[EventBeginRenderWorld](../../../api/library/engine/class.engine_cpp.md#getEventBeginRenderWorld_Event)* *[EventEndRenderWorld](../../../api/library/engine/class.engine_cpp.md#getEventEndRenderWorld_Event)* |
| 4. Вызывается метод *render()* [Editor Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic). - Вызывается метод скрипта редактора [*render()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_render). - Вызывается метод EditorLogic [*render()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_render). | *[EventBeginEditorRender](../../../api/library/engine/class.engine_cpp.md#getEventBeginEditorRender_Event)* *[EventEndEditorRender](../../../api/library/engine/class.engine_cpp.md#getEventEndEditorRender_Event)* |
| 5. Вызывается метод плагинов *[render()](../../../api/library/common/class.plugin_cpp.md#render_const_EngineWindowViewportPtr_ref_void)*. Используйте *[get_order()](../../../api/library/common/class.plugin_cpp.md#get_order_int)*, чтобы задать приоритет рендеринга каждого плагина. | *[EventBeginPluginsRender](../../../api/library/engine/class.engine_cpp.md#getEventBeginPluginsRender_Event)* *[EventEndPluginsRender](../../../api/library/engine/class.engine_cpp.md#getEventEndPluginsRender_Event)* |
| 6. Вызывается метод плагинов *[gui()](../../../api/library/common/class.plugin_cpp.md#gui_const_EngineWindowViewportPtr_ref_void)*. Используйте *[get_order()](../../../api/library/common/class.plugin_cpp.md#get_order_int)*, чтобы задать приоритет gui каждого плагина. | *[EventBeginPluginsGui](../../../api/library/engine/class.engine_cpp.md#getEventBeginPluginsGui_Event)* *[EventEndPluginsGui](../../../api/library/engine/class.engine_cpp.md#getEventEndPluginsGui_Event)* |
| 7. Рендерится [Visualizer](../../../api/library/engine/class.visualizer_cpp.md). | *[EventBeginPostRender](../../../api/library/engine/class.engine_cpp.md#getEventBeginPostRender_Event)* *[EventEndPostRender](../../../api/library/engine/class.engine_cpp.md#getEventEndPostRender_Event)* |
| 8. Этап рендеринга завершён. | *[EventEndRender](../../../api/library/engine/class.engine_cpp.md#getEventEndRender_Event)* |

</details>


## Этап Swap


Этап Swap - это финальная фаза главного цикла.


Здесь движок завершает все ожидающие задачи для текущего кадра, выполняет очистку ресурсов, вызывает методы *swap()* пользовательской логики и плагинов, и финализирует состояние перед началом следующего цикла обновления.


<details>
<summary>Swap Steps</summary>

| Swap Stage | Related Event |
|---|---|
| Начинается этап Swap. | *[EventBeginSwap](../../../api/library/engine/class.engine_cpp.md#getEventBeginSwap_Event)* |
| 1. Если режим обновления физики настроен на асинхронное обновление вместе с рендерингом, движок приостанавливает выполнение до завершения симуляции физики. (В отличие от [the end of the Post-Update stage](#physics_before), где физика выполняется синхронно перед рендерингом). |  |
| 2. Движок приостанавливает выполнение до завершения потока поиска пути. | *[EventEndPathfinding](../../../api/library/engine/class.engine_cpp.md#getEventEndPathfinding_Event)* |
| 3. На этом шаге движок завершает рендеринг текущего кадра. Освобождаются временные текстуры, очищаются внутренние состояния и т.д. |  |
| 4. Движок выполняет [frame synchronization](../../../code/fundamentals/thread_system/index.md#frame_sync): все задачи с *FrameSyncMode::Swap* должны завершиться до продолжения кадра. На этом этапе движок также ожидает завершения метода [*updateAsyncThread()*](#world_update) (он выполняется во внутреннем пуле потоков). |  |
| 5. Диспетчеризуются события GUI (если есть), и освобождаются ресурсы GUI. Полный список связанных событий приведён в классе *[Widget](../../../api/library/gui/class.widget_cpp.md)*. |  |
| 6. Вызывается swap() [World Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#world_logic): - Вызывается метод WorldLogic [*swap()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_swap) (вызывается метод *swap()* компонентов. Порядок выполнения компонентов можно задать: см. описание класса компонента для *[C++](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#methods_order)* или для *[C#](../../../api/library/common/logic/component_system/cs/class.component.md#methods)*). | *[EventEndPathfinding](../../../api/library/engine/class.engine_cpp.md#getEventEndPathfinding_Event)* |
| 7. Вызывается метод плагинов *[swap()](../../../api/library/common/class.plugin_cpp.md#swap_void)*. Используйте *[get_order()](../../../api/library/common/class.plugin_cpp.md#get_order_int)*, чтобы задать приоритет swap каждого плагина. | *[EventBeginPluginsSwap](../../../api/library/engine/class.engine_cpp.md#getEventBeginPluginsSwap_Event)* *[EventEndPluginsSwap](../../../api/library/engine/class.engine_cpp.md#getEventEndPluginsSwap_Event)* |
| 8. Если вы запросили у движка завершение текущего мира или загрузку другого мира (например, через [*world_quit*](../../../code/console/index.md#world_quit)) в течение текущего кадра, движок сделает это здесь, включая: - Вызывается метод скрипта редактора [*worldShutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_worldShutdown). - Вызывается метод EditorLogic [*worldShutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_worldShutdown). - Вызывается метод скрипта мира [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_shutdown). - Вызывается метод WorldLogic [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_shutdown) (вызывается метод *shutdown()* компонентов. Порядок выполнения компонентов можно задать: см. описание класса компонента для *[C++](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#methods_order)* или для *[C#](../../../api/library/common/logic/component_system/cs/class.component.md#methods)*). |  |
| 9. Обновляются все [Profiling Metrics](../../../tools/profiling/profiler/index.md). |  |
| 10. Выполняются задачи асинхронной потоковой передачи данных. |  |
| 11. Если синхронизация FPS между движком и физикой включена, движок задерживает кадр, чтобы соответствовать частоте обновления физики. |  |
| 12. Удаляются все объекты, помеченные для удаления через *[deleteLater()](../../../code/fundamentals/smartpointers.md#delete)*. | *[EventBeginDeleteObjects](../../../api/library/engine/class.engine_cpp.md#getEventBeginDeleteObjects_Event)* *[EventEndDeleteObjects](../../../api/library/engine/class.engine_cpp.md#getEventEndDeleteObjects_Event)* |
| 13. Синхронизируются CPU и GPU. Подробнее см. *[Waiting GPU](../../../code/fundamentals/execution_sequence/index.md#waiting_gpu)*. |  |
| 14. *[Microprofiler](../../../tools/profiling/microprofile/index_cpp.md)* записывает значения для этого кадра. |  |
| 15. Обновляется частота кадров приложения. |  |
| 16. Движок обновляет статистику кадра и переходит к [Update Stage](#update). | *[EventEndSwap](../../../api/library/engine/class.engine_cpp.md#getEventEndSwap_Event)* |

</details>


## Обновление физики


В зависимости от [selected settings](../../../editor2/settings/physics_global/index.md), физика может обновляться либо синхронно [at the end of the Update stage](#physics_before), либо асинхронно [during the Render stage](#physics_async).


Также обратите внимание, что физика не обязательно обновляется каждый кадр вместе с основным циклом update-render-swap, так как у неё своя частота кадров.


Подробности о настройке и режимах выполнения см.: **[Simulation of Physics](../../../principles/physics/simulation.md)**


Независимо от выбранного режима, цикл обновления физики остаётся тем же и включает следующие шаги:


<details>
<summary>Physics Update Steps</summary>

| Physics Update | Related Event |  |
|---|---|---|
| 1. | Устанавливается таймер для хранения времени симуляции физики. | *[EventSyncBeginFramePhysics](../../../api/library/engine/class.engine_cpp.md#getEventSyncBeginFramePhysics_Event)* |
| 2. | Вызывается *[updatePhysics()](../../../api/library/common/class.plugin_cpp.md#updatePhysics_void)* плагинов. |  |
| 3. | Вызывается updatePhysics() [World Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#world_logic). - Вызывается метод скрипта мира [*updatePhysics()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_updatePhysics). - Вызывается метод WorldLogic [*updatePhysics()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_updatePhysics) (вызывается метод *updatePhysics()* компонентов. Порядок выполнения компонентов можно задать: см. описание класса компонента для *[C++](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#methods_order)* или для *[C#](../../../api/library/common/logic/component_system/cs/class.component.md#methods)*). |  |
| 4. | Сбрасывается пространственное дерево для применения всех ожидающих изменений физики. |  |
| 6. | Выполняется этап обнаружения столкновений. Во время этапа обнаружения столкновений движок находит активные тела, строит острова, обнаруживает контакты и готовит данные для разрешения столкновений. | *[EventAsyncBeginFramePhysics](../../../api/library/engine/class.engine_cpp.md#getEventAsyncBeginFramePhysics_Event)* |
| 7. | Выполняется этап симуляции. Во время этапа симуляции движок вычисляет реакции на столкновения и ограничения сочленений, накапливает результаты и применяет новые скорости и позиции к телам. |  |
| 8. | Обновляется сцена физики. | *[EventAsyncEndFramePhysics](../../../api/library/engine/class.engine_cpp.md#getEventAsyncEndFramePhysics_Event)* |
| 9. | Вызываются события, связанные с [bodies and joints](../../../code/fundamentals/events/index_cpp.md#physics) и [physical triggers](../../../objects/effects/physicals/physical_trigger/index.md). |  |
| 10. | Таймер обновления физики останавливается, и результат записывается для отображения в профилировщике. | *[EventSyncEndFramePhysics](../../../api/library/engine/class.engine_cpp.md#getEventSyncEndFramePhysics_Event)* |

</details>
