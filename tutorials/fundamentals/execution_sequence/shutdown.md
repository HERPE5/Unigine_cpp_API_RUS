# Engine Shutdown


Эта статья подробно описывает шаги, выполняемые движком UNIGINE во время завершения работы.


Во время завершения работы движок последовательно завершает логику, останавливает рендеринг, выключает плагины и потоки, и освобождает ресурсы.


Для остальных шагов и общей информации о последовательности выполнения см. статью [Execution Sequence](../../../code/fundamentals/execution_sequence/index.md).


| Engine Shutdown |  |
|---|---|
| 1. | Вызывается метод *shutdown()* [Editor Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#editor_logic). - Вызывается метод скрипта редактора [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_shutdown). - Вызывается метод EditorLogic [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#editorlogic_shutdown). |
| 2. | Вызывается метод *shutdown()* [World Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#world_logic). - Вызывается метод скрипта мира [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_shutdown). - Вызывается метод WorldLogic [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#worldlogic_shutdown) (вызывается метод *shutdown()* компонентов. Порядок выполнения компонентов можно задать: см. описание класса компонента для *[C++](../../../api/library/common/logic/component_system/cpp/class.componentbase_cpp.md#methods_order)* или для *[C#](../../../api/library/common/logic/component_system/cs/class.component.md#methods)*). |
| 3. | Вызывается метод *shutdown()* [System Logics](../../../code/fundamentals/execution_sequence/app_logic_system.md#system_logic). - Вызывается метод системного скрипта [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_shutdown). - Вызывается метод SystemLogic [*shutdown()*](../../../code/fundamentals/execution_sequence/app_logic_system.md#systemlogic_shutdown). |
| 4. | Системы VR завершают работу, и их ресурсы освобождаются. |
| 5. | Завершает работу *[Memory profiler](../../../tools/profiling/profiler/index.md)*. |
| 6. | Вызывается метод плагинов *[shutdown()](../../../api/library/common/class.plugin_cpp.md#shutdown_int)*. Используйте *[get_order()](../../../api/library/common/class.plugin_cpp.md#get_order_int)*, чтобы задать приоритет завершения работы каждого плагина. |
| 7. | Процесс рендеринга останавливается и завершает работу. |
| 8. | Закрываются файлы ландшафта. |
| 9. | Сохраняется история консоли. |
| 10. | Завершаются все потоки движка. |
| 11. | Завершает работу звуковая система. |
| 12. | Завершает работу SystemProxy. |
| 13. | Очищаются и удаляются [Procedural mesh caches](../../../code/console/index.md#mesh_procedural_path). |
| 14. | Общее время завершения работы выводится в лог. |
| 15. | Освобождаются все ресурсы, выделенные UNIGINE. |
| 16. | Завершает работу [Memory Allocator](../../../principles/allocator/index.md). |
