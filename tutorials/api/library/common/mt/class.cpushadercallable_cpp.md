# Unigine::CPUShaderCallable Class (CPP)

**Header:** #include <UnigineThread.h>

**Inherits from:** CPUShader


**CPUShaderCallable** — это шаблонный класс, предоставляющий упрощённый способ выполнения пользовательской многопоточной логики с использованием класса **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)**.


Обычно для использования **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)** необходимо унаследоваться от базового класса **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)** и вручную реализовать метод *process()*. Однако **CPUShaderCallable** позволяет передавать логику обработки и логику очистки напрямую в виде функциональных объектов, без написания пользовательского класса или управления наследованием.


Он также управляет внутренним разделяемым состоянием типа **State**, время жизни которого связано с шейдером — оно автоматически уничтожается с помощью предоставленной функции уничтожения при удалении шейдера.


Используйте вспомогательную функцию [makeCPUShader()](../../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUShader_State_Process_Destroy) для удобного создания экземпляров.


**Параметры шаблона**:


- **State** - пользовательский тип, хранящий разделяемое состояние.
- **Process** - функция, вызываемая для каждого потока. Сигнатура: *void(CPUShader *shader, int thread_num, int num_threads)*
- **Destroy** - функция, вызываемая один раз при уничтожении, после завершения всех потоков. Сигнатура: *void(State state)*


## CPUShaderCallable Class

### Методы класса

---

## CPUShaderCallable ( Process func_process_ , Destroy func_destroy_ , PoolType pool_ = PoolType::Auto , Priority priority_ = Priority::Normal , FrameSyncMode frame_sync_ = FrameSyncMode::Swap , WaitMode wait_mode_ = WaitMode::Auto )

Создаёт новый экземпляр CPUShaderCallable.
### Аргументы

- *Process* **func_process_** - Функция, выполняемая в каждом потоке.
- *Destroy* **func_destroy_** - Функция очистки, вызываемая при уничтожении.
- *[PoolType](#PoolType)* **pool_** - Целевой пул выполнения.
- *[Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[WaitMode](#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](../../../../api/library/common/mt/class.cpushader_cpp.md#wait_void).

## void process ( int thread_num , int num_threads )

Переопределено из **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)**. Вызывается один раз для каждого потока во время выполнения. Вызывает переданную функцию обработки, передавая указатель на шейдер в качестве первого аргумента.
### Аргументы

- *int* **thread_num** - Индекс текущего потока.
- *int* **num_threads** - Общее количество потоков, назначенных этой задаче.
