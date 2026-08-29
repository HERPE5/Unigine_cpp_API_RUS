# Unigine::CPUShaderCallableStateless Class (CPP)

**Header:** #include <UnigineThread.h>

**Inherits from:** CPUShader


**CPUShaderCallableStateless** — это шаблонный класс, предоставляющий упрощённый способ выполнения пользовательской многопоточной логики с использованием класса **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)** без необходимости в разделяемом состоянии или функции уничтожения.


Обычно для использования **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)** необходимо унаследоваться от базового класса **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)** и вручную реализовать метод *process()*. Однако **CPUShaderCallableStateless** позволяет передавать логику обработки напрямую в виде функционального объекта, без написания пользовательского класса или управления наследованием.


В отличие от **[CPUShaderCallable](../../../../api/library/common/mt/class.cpushadercallable_cpp.md)**, этот вариант не управляет разделяемым состоянием или обратным вызовом уничтожения.


Используйте вспомогательные функции [makeCPUShaderStateless()](../../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUShaderStateless_Process), [makeScopeCPUShaderStateless()](../../../../api/library/common/class.unigine.namespace_cpp.md#makeScopeCPUShaderStateless_Process) или [runSyncMultiThreadFunc()](../../../../api/library/common/class.unigine.namespace_cpp.md#runSyncMultiThreadFunc_Process_int) для удобного создания и запуска экземпляров.


**Параметры шаблона**:


- **Process** - функция, вызываемая для каждого потока. Сигнатура: *void(CPUShader *shader, int thread_num, int num_threads)*


## CPUShaderCallableStateless Class

### Методы класса

---

## CPUShaderCallableStateless ( Process func_process_ , PoolType pool_ = PoolType::Auto , Priority priority_ = Priority::Normal , FrameSyncMode frame_sync_ = FrameSyncMode::Swap , WaitMode wait_mode_ = WaitMode::Auto )

Создаёт новый экземпляр CPUShaderCallableStateless.
### Аргументы

- *Process* **func_process_** - Функция, выполняемая в каждом потоке.
- *[PoolType](#PoolType)* **pool_** - Целевой пул выполнения.
- *[Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[WaitMode](#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](../../../../api/library/common/mt/class.cpushader_cpp.md#wait_void).

## void process ( int thread_num , int num_threads )

Переопределено из **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)**. Вызывается один раз для каждого потока во время выполнения. Вызывает переданную функцию обработки, передавая указатель на шейдер в качестве первого аргумента.
### Аргументы

- *int* **thread_num** - Индекс текущего потока.
- *int* **num_threads** - Общее количество потоков, назначенных этой задаче.
