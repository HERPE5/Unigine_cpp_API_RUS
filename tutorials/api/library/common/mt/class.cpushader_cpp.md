# Unigine::CPUShader Class (CPP)

**Header:** #include <UnigineThread.h>


Этот класс используется для создания пользовательского CPU-шейдера, например, для реализации многопоточного обновления кластеров мешей. Ваш пользовательский CPU-шейдер должен быть унаследован от этого класса. Пример включён в SDK.


Кадро-синхронизированные шейдеры ([FrameSyncMode::Swap](../../../../api/library/common/mt/class.threadspool_cpp.md#FrameSyncMode_Swap)) вычерпываются на этапе завершения кадра через [ThreadsPool::frameSync()](../../../../api/library/common/mt/class.threadspool_cpp.md#frameSync_void), поэтому движок ожидает их завершения перед переходом к следующему кадру.


Вот пример реализации пользовательского CPU-шейдера:


```cpp
struct UpdateClustersCPUShader: public CPUShader
{
	UpdateClustersCPUShader() {}
	virtual ~UpdateClustersCPUShader()
	{
		// ожидание завершения всех асинхронных операций
		wait();
	}

	Vector<AsyncCluster> clusters;

	volatile int counter{0};

	// переопределение метода process для выполнения наших вычислений
	void process(int thread_num, int threads_count) override
	{
		UNIGINE_PROFILER_FUNCTION;

		while (true)
		{
			int num = AtomicAdd(&counter, 1);
			if (num >= clusters.size())
				break;
			clusters[num].update();
		}
	}

	void run()
	{
		for (auto &c : clusters)
			c.swap();

		counter = 0;

		// запуск кода шейдера в асинхронном режиме
		runAsync();
	}
};

```


## CPUShader Class

### Перечисления

## PoolType

| Name | Description |
|---|---|
| **Auto** = 0 | Автоматический выбор пула: [Sync](#PoolType_Sync) при вызове из главного потока, [Async](#PoolType_Async) в остальных случаях. |
| **Async** = 1 | Пул асинхронных рабочих потоков. |
| **Sync** = 2 | Пул синхронных рабочих потоков. |
| **Critical** = 3 | Пул критических рабочих потоков. |
| **Common** = 4 | Общий пул рабочих потоков. |
| **Background** = 5 | Фоновый пул рабочих потоков. |
| **RenderFlush** = 6 | Пул рабочих потоков сброса рендеринга. |
| **FileStream** = 7 | Пул рабочих потоков потоковой передачи файлов. |
| **GPUStream** = 8 | Пул рабочих потоков потоковой передачи GPU. |

## WaitMode

| Name | Description |
|---|---|
| **Auto** = 0 | Простое активное ожидание до завершения шейдера. |
| **Full** = 1 | Активно обрабатывает другие задачи из того же пула во время ожидания завершения шейдера. |

### Методы класса

---

## CPUShader ( )

Создаёт новый экземпляр CPUShader.
## CPUShader ( PoolType pool_ , Priority priority_ , FrameSyncMode frame_sync_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[PoolType](/api/library/common/mt/class.cpushader#PoolType)* **pool_** - Целевой пул выполнения.
- *[Priority](#priority)* **priority_** - Приоритет задачи в очереди пула.
- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.

## CPUShader ( PoolType pool_ , Priority priority_ , FrameSyncMode frame_sync_ , WaitMode wait_mode_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[PoolType](/api/library/common/mt/class.cpushader#PoolType)* **pool_** - Целевой пул выполнения.
- *[Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.
- *[WaitMode](/api/library/common/mt/class.cpushader#WaitMode)* **wait_mode_** - Стратегия ожидания для [wait()](#wait_void).

## CPUShader ( Priority priority_ , FrameSyncMode frame_sync_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.

## CPUShader ( PoolType pool_ , FrameSyncMode frame_sync_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[PoolType](/api/library/common/mt/class.cpushader#PoolType)* **pool_** - Целевой пул выполнения.
- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.

## CPUShader ( PoolType pool_ , Priority priority_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[PoolType](/api/library/common/mt/class.cpushader#PoolType)* **pool_** - Целевой пул выполнения.
- *[Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.

## CPUShader ( FrameSyncMode frame_sync_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.

## CPUShader ( PoolType pool_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[PoolType](/api/library/common/mt/class.cpushader#PoolType)* **pool_** - Целевой пул выполнения.

## CPUShader ( Priority priority_ )

Создаёт новый экземпляр CPUShader.
### Аргументы

- *[Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.

## void runSync ( int num_threads_ = -1 )

Направляет шейдер в пул [Sync](#PoolType_Sync) и блокирует выполнение до завершения всех потоков. Один блок обрабатывается в вызывающем потоке, остальные — в рабочих потоках пула.
### Аргументы

- *int* **num_threads_** - Количество используемых потоков. Значение -1 означает использование количества потоков пула по умолчанию.

## void runAsync ( int num_threads_ = -1 )

Направляет шейдер в пул [Async](#PoolType_Async) и немедленно возвращает управление. Вызовите [wait()](#wait_void), чтобы блокировать выполнение до завершения обработки.
### Аргументы

- *int* **num_threads_** - Количество используемых потоков. Значение -1 означает использование количества потоков пула по умолчанию.

## void wait ( )

Блокирует выполнение до завершения работы шейдера. Сначала пытается помочь, обрабатывая оставшиеся элементы работы ([doProcess()](#doProcess_void)), затем ожидает в соответствии с текущим [WaitMode](#WaitMode).
## bool isRunning ( ) const

Возвращает значение, указывающее, выполняется ли в данный момент код CPU-шейдера.
### Возвращаемое значение

true, если код шейдера в данный момент выполняется; иначе false.
## int getNumThreads ( ) const

Возвращает текущее используемое количество потоков.
### Возвращаемое значение

Количество используемых в данный момент потоков.
## virtual void process ( int thread_num , int num_threads )

Переопределите этот метод для реализации вычислений.
### Аргументы

- *int* **thread_num** - Номер текущего потока. Это число не является ID потока, это просто виртуальный номер.
- *int* **num_threads** - Количество используемых потоков.

## void doProcess ( )

Пытается обработать оставшиеся элементы работы шейдера из текущего потока. Используется внутренне во время [wait()](#wait_void) для более быстрого завершения работы шейдера.
## virtual void done ( )

Виртуальный обратный вызов, вызываемый в последнем потоке, завершающем обработку. Переопределите этот метод, чтобы связать задачи CPUShader в цепочку без возврата в главный поток.
## bool isAutoDestroy ( ) const

Возвращает значение, указывающее, будет ли шейдер автоматически уничтожен после завершения обработки всеми потоками.
### Возвращаемое значение

true, если автоматическое уничтожение включено; иначе false.
## CPUShader::PoolType getPool ( ) const

Возвращает тип пула, к которому назначен этот шейдер.
### Возвращаемое значение

Текущий тип пула.
## void setPool ( PoolType p )

Задаёт тип пула. Если шейдер в данный момент выполняется, ожидает завершения перед изменением пула.
### Аргументы

- *[PoolType](/api/library/common/mt/class.cpushader#PoolType)* **p** - Устанавливаемый тип пула.

## Priority getPriority ( ) const

Возвращает приоритет шейдера в очереди пула.
### Возвращаемое значение

Текущий приоритет.
## void setPriority ( Priority p )

Задаёт приоритет шейдера. Если шейдер в данный момент выполняется, ожидает завершения перед изменением приоритета.
### Аргументы

- *[Priority](#Priority)* **p** - Устанавливаемый приоритет.

## FrameSyncMode getFrameSync ( ) const

Возвращает режим синхронизации кадра.
### Возвращаемое значение

Текущий режим синхронизации кадра.
## void setFrameSync ( FrameSyncMode f )

Задаёт режим синхронизации кадра. Если шейдер в данный момент выполняется, ожидает завершения перед изменением режима.
### Аргументы

- *[FrameSyncMode](#FrameSyncMode)* **f** - Устанавливаемый режим синхронизации кадра.

## WaitMode getWaitMode ( ) const

Возвращает режим ожидания, используемый [wait()](#wait_void).
### Возвращаемое значение

Текущий режим ожидания.
## void setWaitMode ( WaitMode f )

Задаёт режим ожидания. [WaitMode::Auto](#WaitMode_Auto) использует простое активное ожидание. [WaitMode::Full](#WaitMode_Full) активно обрабатывает другие задачи из того же пула во время ожидания.
### Аргументы

- *[WaitMode](/api/library/common/mt/class.cpushader#WaitMode)* **f** - Устанавливаемый режим ожидания.

## bool isDone ( ) const

Возвращает значение, указывающее, завершено ли выполнение CPU-шейдера.
### Возвращаемое значение

true, если шейдер завершил выполнение; иначе false.
