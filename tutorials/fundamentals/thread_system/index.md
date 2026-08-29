# Thread System in UNIGINE


Движок выполняет тысячи операций каждую секунду - от рендеринга кадров до обновления физики и управления ресурсами. Код вашего собственного проекта добавляет ещё больше задач в этот рабочий процесс.


Если бы все эти операции выполнялись строго одна за другой, время обработки резко возросло бы, и приложение быстро стало бы слишком медленным для плавной работы.


Чтобы предотвратить это, большинство задач движка выполняются параллельно на разных потоках, организованных в **thread pools**. Вы также можете отправлять свои собственные задачи в эти пулы.


В этой статье мы рассмотрим, как работают потоки и пулы, как запускать собственные параллельные задачи и как профилировать их производительность.


> **Примечание:** Для повседневной разработки - написания компонентов, игровой логики и скриптов - вам вообще не нужно думать о потоках. Движок обрабатывает параллелизм внутренне. Эта статья предназначена для продвинутых сценариев, когда вы хотите запускать свои собственные параллельные задачи на пулах потоков движка или точно настраивать производительность многопоточности.


## Потоки


Поток - это лёгкая единица выполнения, которая может работать независимо от других частей кода. Каждый поток в движке представлен классом **[Thread](../../../api/library/common/mt/class.thread_cpp.md)**. Вы можете создавать собственные потоки, наследуясь от него и переопределяя метод *process()*. Класс предоставляет управление жизненным циклом (*[run()](../../../api/library/common/mt/class.thread_cpp.md#run_size_t_bool)*, *[stop()](../../../api/library/common/mt/class.thread_cpp.md#stop_bool)*, *[shutdown()](../../../api/library/common/mt/class.thread_cpp.md#shutdown_bool)*), режим сна и сигнализацию (*[sleep()](../../../api/library/common/mt/class.thread_cpp.md#sleep_uint_void)*, *[signal()](../../../api/library/common/mt/class.thread_cpp.md#signal_void)*), а также управление приоритетом на уровне ОС.


### Тип потока


У каждого потока есть *[Type](../../../api/library/common/mt/class.thread_cpp.md#Type)* - пресет, предоставляющий значения по умолчанию для **имени** потока (отображается в отладчике и [Microprofile](../../../tools/profiling/microprofile/index_cpp.md)), **приоритета ОС** и **порядка отображения** в [Microprofile](../../../tools/profiling/microprofile/index_cpp.md). Все эти значения можно переопределить индивидуально. Тип не привязывает поток к пулу и не меняет его поведение.


Движок использует около 20 встроенных типов внутренне (рабочие пула, звук, ввод, сеть и т.д.). Тип по умолчанию для новых пользовательских потоков - *Unknown*.


### Главный поток


**Main** поток - это место, где происходит вся инициализация движка, загрузка мира, callback-функции игровой логики и главный цикл. Некоторые методы API можно вызывать только из главного потока.


> **Примечание:** Подробнее о потокобезопасном использовании API см. в статье [Thread Safety in API](../../../code/fundamentals/thread_safety/index.md).


Однако создание и управление потоками вручную требуется редко. Для большинства параллельных нагрузок движок предоставляет систему более высокого уровня: **thread pools** и **jobs**.


## Пулы потоков


Пул потоков - это группа заранее созданных рабочих потоков, управляемых движком. Вместо создания и уничтожения потоков каждый раз, когда нужно выполнить задачу, пул поддерживает набор активных потоков, готовых немедленно выполнить работу.


Когда вы или движок отправляете задачу в пул потоков, она помещается в общую очередь. Первый доступный рабочий поток берёт задачу и выполняет её. По завершении поток снова становится свободным и может взять следующую задачу из очереди.


Всеми пулами потоков управляет класс **[ThreadsPool](../../../api/library/common/mt/class.threadspool_cpp.md)**.


### Почему раздельные пулы?


Если бы все параллельные задачи использовали общий пул потоков, всплеск тяжёлой асинхронной работы мог бы занять **все** доступные рабочие потоки, не оставив места для небольших, но критичных по времени синхронных задач. Чувствительные к кадрам системы, такие как физика и рендеринг, застопорились бы в ожидании свободного потока - фактически работая однопоточно и вызывая падения частоты кадров.


Чтобы предотвратить это, движок разделяет рабочие потоки на выделенные пулы - каждый со своими потоками, приоритетом и назначением - так что один тип работы не может "заморить" другой.


Следующая диаграмма показывает все пулы, создаваемые при запуске движка, их очереди и то, как задачи проходят через систему:


![](thread_pool_architecture_unigine.svg)


Каждый пул содержит две очереди: **Frame-Bound** (для задач, которые должны завершиться в течение текущего кадра) и **Independent** (для задач, которые могут занимать несколько кадров). Внутри каждой очереди задачи организованы по [priority](#task_priority) - задачи с более высоким приоритетом всегда забираются первыми. Подробности этих настроек рассмотрены в [Running Custom Jobs](#custom_tasks).


### Подробности о пулах


| Pool | Thread Count | Description |
|---|---|---|
| **Sync Pool** | Ядра CPU - 1 | Пул для синхронизированных с кадром задач. Используется движком для распределения работы, которая должна завершиться в течение текущего кадра. Главный поток также участвует в работе Sync Pool во время синхронного выполнения, поэтому эффективное количество потоков на единицу больше числа выделенных потоков пула. |
| **Async Pool** | Ядра CPU | Асинхронный пул общего назначения, используемый движком для задач вроде предзагрузки, обновлений ландшафта, потоковой передачи данных и других фоновых операций. Чрезмерное использование этого пула может задержать основные системы движка. |
| **Critical Pool** | 1 | Пул для самых важных задач, которые должны быть завершены как можно быстрее. Имеет выделенный поток, который исключительно обрабатывает Critical задачи. Лучше всего подходит для небольших, срочных операций (например, принудительный запрос пересечения с ландшафтом). Избегайте отправки тяжёлой или долго выполняющейся работы в этот пул, так как это может заблокировать другие критические задачи. |
| **Common Pool** | 1 | Вспомогательный пул общего назначения. В отличие от других пулов, рабочий поток Common Pool всегда активен (spin-waiting) и может выполнять задачи из очередей Sync, Async и Common, выступая гибким помощником, который помогает там, где есть работа. |
| **Background Pool** | 1 | Пул с низким приоритетом. Редко используется самим движком, в основном предназначен для пользовательских процедурных операций, таких как модификация геометрии. Безопасен для долго выполняющихся фоновых задач, так как не мешает потоковой передаче или другим критическим системам движка. |
| **File Stream Pool** | 1 | Выделенный пул для операций ввода-вывода файлов. Отделён от Async Pool для снижения конкуренции между работой CPU и доступом к диску. Подходит для загрузки/сохранения геометрии, потоковой передачи данных с диска или обработки тяжёлого ввода-вывода. Перегрузка этого пула может повлиять на производительность потоковой передачи. |
| **GPU Stream Pool** | 1 | Специализированный пул с выделенной командной очередью для передачи данных из RAM в VRAM. Используется для асинхронного создания GPU-ресурсов (например, Texture, MeshRender) из соответствующих объектов RAM (Image, Mesh). Идеален для реализации пользовательских систем потоковой передачи данных или динамических обновлений данных GPU. |
| **Render Flush Pool** | 1 | Пул для сброса команд GPU. |


> **Примечание:** Количество потоков в каждом пуле можно настроить при запуске через [command-line options](../../../code/command_line.md#multithreading).


### Кросс-пуловое выполнение


Потоки каждого пула обычно выполняют только задачи из своей собственной очереди. Пул **Common** является исключением - его рабочий поток может забирать задачи из очередей **Sync**, **Async** и **Common**, выступая гибким помощником, который помогает там, где есть работа.


В отличие от других потоков пулов, рабочий поток Common Pool всегда активен (*spin-waiting*), а не спит, поэтому он реагирует на новую работу немедленно.


**Главный поток** также помогает системе пулов: он участвует как рабочий поток Sync Pool во время вызовов *[runSync()](../../../api/library/common/mt/class.cpushader_cpp.md#runSync_int_void)*, обрабатывает задачи, отправленные через *[CPUTask::runMainThread()](../../../api/library/common/mt/class.cputask_cpp.md#runMainThread_void)*, и помогает опустошать привязанные к кадру очереди всех пулов на этапе *[Engine::swap()](../../../code/fundamentals/execution_sequence/main_loop.md#swap)*.


## Приоритет потока


**Приоритет потока** - это настройка на уровне ОС, которая указывает операционной системе, как распределять время CPU между потоками. Поток с более высоким приоритетом получает больше времени CPU при загрузке системы. Устанавливается через *[Thread::setPriority()](../../../api/library/common/mt/class.thread_cpp.md#setPriority_int_int)*. Каждому типу потока при создании назначается приоритет ОС по умолчанию:


| Value | Level | Thread Types |
|---|---|---|
| 1 | Above Normal | PoolSync, PoolAsync, PoolCritical, PoolCommon |
| 0 | Normal | Main, PoolRenderFlush, GenericUser, USC, Unknown |
| -1 | Below Normal | Monitor, Ultraleap, Network |
| -2 | Lowest | PoolBackground, PoolFileStream, PoolGPUStream, Sound, Input, Dump |
| -3 | Idle | WakeUp |


> **Примечание:** Полный диапазон, принимаемый *[Thread::setPriority()](../../../api/library/common/mt/class.thread_cpp.md#setPriority_int_int)*, составляет от -3 до 3, где 2 соответствует **Highest**, а 3 - **Time Critical**. Эти более высокие уровни не используются по умолчанию, но могут быть установлены вручную при необходимости.


В большинстве случаев вам не нужно менять приоритет потока - значения по умолчанию тщательно настроены. Если вы всё же его меняете, эффект зависит от общей загрузки системы: на слабо загруженной системе все потоки получают достаточно времени независимо от приоритета.


## Запуск пользовательских задач


UNIGINE предоставляет несколько способов запуска вашего собственного кода на потоках движка. Два основных механизма - **[CPUShader](../../../api/library/common/mt/class.cpushader_cpp.md)** и **[CPUTask](../../../api/library/common/mt/class.cputask_cpp.md)**. Оба позволяют отправлять работу в пулы потоков, но различаются способом её распределения:


- **[CPUShader](../../../api/library/common/mt/class.cpushader_cpp.md)** - распределяет работу по **нескольким потокам** параллельно. Каждый поток получает свой индекс и общее количество потоков, так что можно разделить нагрузку между ними.
- **[CPUTask](../../../api/library/common/mt/class.cputask_cpp.md)** - выполняется на **одном потоке** в выбранном пуле. Задача выполняется один раз на назначенном рабочем потоке.


Вот сравнение этих двух классов:


|  | **CPUShader** | **CPUTask** |
|---|---|---|
| **Pool** | *[PoolType](../../../api/library/common/mt/class.cpushader_cpp.md#PoolType)*, задаваемый в конструкторе (Auto, Sync, Async и т.д.). | Выбирается вызовом соответствующего метода *[run*Thread()](../../../api/library/common/mt/class.cputask_cpp.md#run_PoolThread_void)* (по одному на пул + Main). |
| **Execution** | Выполняется на **нескольких потоках** параллельно. *[runSync()](../../../api/library/common/mt/class.cpushader_cpp.md#runSync_int_void)* блокирует вызывающий поток, *[runAsync()](../../../api/library/common/mt/class.cpushader_cpp.md#runAsync_int_void)* возвращает управление немедленно. | Выполняется на **одном потоке**. Всегда неблокирующий. |
| **[Frame Sync](#frame_sync)** | По умолчанию ожидается на [swap stage](../../../code/fundamentals/execution_sequence/main_loop.md#swap). | По умолчанию не ожидается на [swap stage](../../../code/fundamentals/execution_sequence/main_loop.md#swap). |
| **[Priority](#task_priority)** | 8 уровней (Critical .. Idle). По умолчанию: *Normal*. |  |
| **Wait Mode** | Что делает вызывающий поток, пока заблокирован: *Auto* (spin-wait) или *Full* (помогает пулу, выполняя другие задачи). По умолчанию: *Auto*. | Н/Д (всегда неблокирующий). |


### Приоритет задачи


И **CPUShader**, и **CPUTask** принимают значение *Priority*, определяющее порядок, в котором задачи забираются в рамках одного пула. Есть 8 уровней приоритета:


| Priority | Value |
|---|---|
| Critical | 0 (highest) |
| Highest | 1 |
| AboveNormal | 2 |
| Normal | 3 (default) |
| BelowNormal | 4 |
| Lowest | 5 |
| Background | 6 |
| Idle | 7 (lowest) |


> **Примечание:** **Приоритет задачи** не зависит от **[thread priority](#thread_priority)**. Приоритет потока влияет на то, сколько времени CPU ОС выделяет потоку; приоритет задачи влияет на порядок задач в очереди.
>
>
> Задача с приоритетом *Critical* в Background Pool будет забрана раньше других Background задач - но она всё равно выполняется на низкоприоритетном потоке. Если вам нужны и быстрый захват, и быстрое выполнение, отправьте задачу в пул с [high thread priority](#thread_priority).


### Синхронизация кадров


И **CPUShader**, и **CPUTask** поддерживают настройку *FrameSyncMode*, которая контролирует, ждёт ли движок завершения задачи перед завершением текущего кадра:


- *FrameSyncMode::Disabled* - задача выполняется независимо от цикла кадра. Движок не ждёт её ни в одной точке синхронизации. Это значение по умолчанию для **CPUTask**.
- *FrameSyncMode::Swap* - задача привязана к текущему кадру. *[Swap stage](../../../code/fundamentals/execution_sequence/main_loop.md#swap)* будет блокироваться до завершения всех синхронизированных с кадром задач. Это значение по умолчанию для **CPUShader**.


Используйте *FrameSyncMode::Swap*, когда результаты задачи должны быть доступны до начала следующего кадра (например, расчёты физики, обновления видимости). Используйте *FrameSyncMode::Disabled* для задач по принципу "запустил и забыл", которые могут занимать несколько кадров.


Каждый пул поддерживает две внутренние очереди на основе этих режимов. Рабочий поток проходит по [priority levels](#task_priority) от высшего к низшему. На каждом уровне он сначала проверяет очередь, привязанную к кадру, затем независимую очередь, прежде чем перейти к следующему уровню. Это означает, что независимая задача с высоким приоритетом будет забрана раньше, чем привязанная к кадру задача с низким приоритетом - приоритет всегда важнее.


Следующая диаграмма показывает, как задачи организованы внутри одного пула и в каком порядке они становятся доступны рабочим потокам:


![](job_queue.svg)

*CPUTasks выполняются до CPUShaders*


### CPUShader: многопоточные задачи


Используйте **[CPUShader](../../../api/library/common/mt/class.cpushader_cpp.md)**, когда вам нужно распределить работу по нескольким потокам параллельно. Ваша функция обработки получает индекс потока и общее количество потоков, так что вы можете разделить работу между ними.


#### Быстрый старт с помощниками


Самый простой способ запустить параллельную работу - использовать шаблонные вспомогательные функции - без необходимости наследования:


<details>
<summary>Details</summary>

```cpp
#include <UnigineThread.h>
using namespace Unigine;

// Проще всего: синхронная параллельная работа (блокирует до завершения)
runSyncMultiThreadFunc([](CPUShader *shader, int thread_num, int num_threads)
{
	// Разделяем работу, используя thread_num / num_threads
});

// Асинхронно: возвращает указатель, который вы запускаете и которым управляете сами
CPUShader *shader = makeCPUShaderStateless(
	[](CPUShader *shader, int thread_num, int num_threads)
	{
		// Ваша параллельная работа здесь
	}
);
shader->runAsync(-1);
// ... выполняем другую работу ...
shader->wait();
delete shader;

```

</details>


Доступные помощники:


- *[runSyncMultiThreadFunc()](../../../api/library/common/class.unigine.namespace_cpp.md#runSyncMultiThreadFunc_Process_int)* - самый простой вариант. Выполняет работу синхронно на нескольких потоках и блокирует до завершения всех.
- *[makeCPUShaderStateless()](../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUShaderStateless_Process)* - создаёт выделенный в куче шейдер без общего состояния. Возвращает указатель, который можно запустить асинхронно. Должен быть удалён вручную.
- *[makeScopeCPUShaderStateless()](../../../api/library/common/class.unigine.namespace_cpp.md#makeScopeCPUShaderStateless_Process)* - то же самое, но выделенный на стеке. Автоматически очищается при выходе из области видимости.
- *[makeCPUShader<State>(process, ...)](../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUShader_State_Process)* - создаёт шейдер с общим состоянием указанного типа. Должен быть удалён вручную.
- *[makeCPUShader<State>(process, destroy, ...)](../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUShader_State_Process_Destroy)* - то же самое, но с callback-функцией destroy для очистки состояния.


Все помощники принимают опциональные параметры для [pool](#thread_pools), [priority](#task_priority), [frame sync](#frame_sync) и режима ожидания - значения по умолчанию подходят для большинства случаев.


Вызовите *[runSync()](../../../api/library/common/mt/class.cpushader_cpp.md#runSync_int_void)*, чтобы блокировать выполнение до завершения всех рабочих потоков, или *[runAsync()](../../../api/library/common/mt/class.cpushader_cpp.md#runAsync_int_void)*, чтобы вернуть управление немедленно и вызвать *[wait()](../../../api/library/common/mt/class.cpushader_cpp.md#wait_void)* позже.


> **Примечание:** При вызове из потока, не являющегося главным, работа всегда направляется в Async Pool - даже если явно указан *PoolType::Sync*.


#### Ручное наследование


Для полного контроля - пользовательских callback-функций *[done()](../../../api/library/common/mt/class.cpushader_cpp.md#done_void)*, переиспользуемых шейдеров или сложного управления состоянием - наследуйтесь от **CPUShader** напрямую:


<details>
<summary>Details</summary>

```cpp
#include <UnigineThread.h>
using namespace Unigine;

class MyShader : public CPUShader
{
public:
	MyShader()
		: CPUShader(PoolType::Async, Priority::Normal, FrameSyncMode::Swap)
	{}

	void process(int thread_num, int num_threads) override
	{
		int chunk_size = total_items / num_threads;
		int start = thread_num * chunk_size;
		int end = (thread_num == num_threads - 1) ? total_items : start + chunk_size;

		for (int i = start; i < end; i++)
		{
			// Обрабатываем элемент i
		}
	}

	void done() override
	{
		// Вызывается на потоке, завершившем работу последним - размещайте здесь последующую работу
	}

private:
	int total_items = 1000;
};

// Использование:
MyShader shader;
shader.runAsync(4);  // Запускаем на 4 потоках
shader.wait();       // Ждём завершения

```

</details>


Когда все потоки завершают работу, виртуальный callback *[done()](../../../api/library/common/mt/class.cpushader_cpp.md#done_void)* срабатывает на последнем потоке, позволяя вам продолжить цепочку работы без возврата в главный поток.


### CPUTask: однопоточные задачи


Используйте **[CPUTask](../../../api/library/common/mt/class.cputask_cpp.md)**, когда ваша работа должна выполняться на одном рабочем потоке в определённом пуле.


#### Быстрый старт с помощниками


Самый простой способ создать задачу - использовать помощник *[makeCPUTask()](../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUTask_Callable_Priority_FrameSyncMode)*:


<details>
<summary>Details</summary>

```cpp
#include <UnigineThread.h>
using namespace Unigine;

CPUTask *task = makeCPUTask([](CPUTask *t)
{
	// Ваша работа здесь
});
task->runAsyncThread();   // Отправляем в Async Pool

```

</details>


Опциональный callback destroy можно передать вторым аргументом для очистки при удалении задачи. Оба варианта принимают опциональные параметры [priority](#task_priority) и [frame sync](#frame_sync).


У каждого [pool](#thread_pools) есть соответствующий метод *run*Thread()* (например, *[runAsyncThread()](../../../api/library/common/mt/class.cputask_cpp.md#runAsyncThread_void)*, *[runSyncThread()](../../../api/library/common/mt/class.cputask_cpp.md#runSyncThread_void)*). Используйте *[runMainThread()](../../../api/library/common/mt/class.cputask_cpp.md#runMainThread_void)*, чтобы поставить задачу в очередь для главного потока. Полный список см. в **[CPUTask](../../../api/library/common/mt/class.cputask_cpp.md)**.


> **Примечание:** Все вызовы *run*Thread()* неблокирующие - они помещают задачу в очередь пула и немедленно возвращают управление.


#### Ручное наследование


Для переиспользуемых задач или сложной логики наследуйтесь от **CPUTask** напрямую:


<details>
<summary>Details</summary>

```cpp
#include <UnigineThread.h>
using namespace Unigine;

class MyTask : public CPUTask
{
public:
	void process() override
	{
		// Ваша работа здесь
	}
};

// Использование:
MyTask *task = new MyTask();
task->runAsyncThread();

```

</details>


### Совместная обработка задач


Внутри долго выполняющейся задачи вы можете добровольно помочь пулу обработать другие ожидающие задачи с помощью двух статических методов **[ThreadsPool](../../../api/library/common/mt/class.threadspool_cpp.md)**:


- *[yield()](../../../api/library/common/mt/class.threadspool_cpp.md#yield_int_int_bool_bool)* - забирает и выполняет одну ожидающую задачу из собственного пула вызывающего потока. Безопасен для использования где угодно - поток Sync возьмёт только работу Sync, поток Background - только работу Background, и так далее.
- *[runProcess()](../../../api/library/common/mt/class.threadspool_cpp.md#runProcess_int_int_bool_bool)* - вариант более низкого уровня, где вы явно указываете, из каких пулов и уровней приоритета забирать работу.


Вызывайте *[yield()](../../../api/library/common/mt/class.threadspool_cpp.md#yield_int_int_bool_bool)* внутри долго выполняющихся задач, чтобы помочь движку обработать другую работу, пока вы ждёте чего-то. Это делает поток полезным вместо простаивания в блокировке.


### Управление памятью


Ни **CPUShader**, ни **CPUTask** не удаляются автоматически после выполнения. То, как вы обрабатываете очистку, зависит от того, как был создан объект:


- *[runSyncMultiThreadFunc()](../../../api/library/common/class.unigine.namespace_cpp.md#runSyncMultiThreadFunc_Process_int)* и *[makeScopeCPUShaderStateless()](../../../api/library/common/class.unigine.namespace_cpp.md#makeScopeCPUShaderStateless_Process)* - выделяются на стеке, очистка не требуется.
- *[makeCPUShaderStateless()](../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUShaderStateless_Process)*, *[makeCPUShader()](../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUShader_State_Process)*, *[makeCPUTask()](../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUTask_Callable_Priority_FrameSyncMode)* - выделяются в куче, вызывайте *delete* по завершении.
- Для **CPUTask** вы также можете вызвать *[destroy()](../../../api/library/common/mt/class.cputask_cpp.md#destroy_void)* вместо *delete*, чтобы запланировать асинхронное удаление через внутреннюю очередь удаления движка.


> **Примечание:** Деструктор **CPUShader** внутренне вызывает *[wait()](../../../api/library/common/mt/class.cpushader_cpp.md#wait_void)*, поэтому вызов *delete* для выполняющегося шейдера безопасен - он заблокирует выполнение до завершения всех потоков.


При наследовании от **CPUShader** можно установить *protected* поле *auto_destroy = true*, чтобы шейдер удалял себя сам после завершения всех потоков (паттерн "запустил и забыл"). Проверить текущее состояние можно с помощью *[isAutoDestroy()](../../../api/library/common/mt/class.cpushader_cpp.md#isAutoDestroy_bool)*.


### Автономные потоки


Если вам нужно выполнить произвольный код в полностью отдельном потоке (не привязанном ни к одному пулу), используйте *[ThreadsPool::runNewThread()](../../../api/library/common/mt/class.threadspool_cpp.md#runNewThread_CallbackBase_ptr_int_void)*. Это создаёт новый поток **GenericUser**, выполняет ваш callback и автоматически очищается:


```cpp
#include <UnigineThread.h>
#include <UnigineCallback.h>
using namespace Unigine;

void myFunction()
{
	// Долго выполняющаяся работа в отдельном потоке
}

// Создаём новый поток и запускаем callback
ThreadsPool::runNewThread(MakeCallback(myFunction));

```


Этот подход лучше всего подходит для изолированных, долго выполняющихся операций, которым не нужно взаимодействовать с планированием пулов движка.


### AsyncQueue (C# / UnigineScript)


Класс **[AsyncQueue](../../../api/library/filesystem/class.asyncqueue_cpp.md)** - основной способ запуска пользовательских задач на пулах потоков из **C#** и **UnigineScript**. Его многопоточные методы создают экземпляры **[CPUShader](../../../api/library/common/mt/class.cpushader_cpp.md)**, а однопоточные методы создают экземпляры **[CPUTask](../../../api/library/common/mt/class.cputask_cpp.md)** - те же примитивы, описанные выше, но доступные через единый межъязыковой интерфейс.


**AsyncQueue** также предоставляет асинхронную загрузку ресурсов (изображений, мешей, узлов) с собственной очередью загрузки.


> **Примечание:** Не путайте **AsyncQueue** (утилиту загрузки ресурсов, использующую поток **GenericUser**) с **Async Pool** (пулом потоков общего назначения для задач движка). Это отдельные системы.


Полные подробности см. в документации класса [AsyncQueue](../../../api/library/filesystem/class.asyncqueue_cpp.md).


## Профилирование с помощью Microprofile


[Microprofile](../../../tools/profiling/microprofile/index_cpp.md) - это встроенный инструмент профилирования, позволяющий визуализировать временную шкалу выполнения всех потоков и видеть, куда тратится время. Каждый поток движка отображается в Microprofile под своим именем - если пользовательское имя было задано через конструктор **[Thread](../../../api/library/common/mt/class.thread_cpp.md)**, отображается это имя; в противном случае отображается тип потока.


Чтобы отметить участки вашего кода в Microprofile, используйте следующие макросы и вызовы API:


```cpp
#include <UnigineProfiler.h>

void myFunction()
{
	// Автоматически профилирует всю функцию
	UNIGINE_PROFILER_FUNCTION;

	// Или профилируем определённый участок вручную
	int id = Profiler::beginMicro("my_section_name");
	// ... работа ...
	Profiler::endMicro(id);
}

```


Например, следующий код запускает **[CPUShader](../../../api/library/common/mt/class.cpushader_cpp.md)** на 4 потоках с пользовательским маркером [Microprofile](../../../tools/profiling/microprofile/index_cpp.md):


```cpp
auto shader = makeScopeCPUShaderStateless(
	[](CPUShader* self, int thread_num, int num_threads)
	{
		int id = Profiler::beginMicro("MyCustomJob");
		Thread::sleep(200);
		Profiler::endMicro(id);
	},
	CPUShader::PoolType::Sync
);
shader.runSync(4);

```


![](cpu_shader_in_microprofile.png)


На скриншоте *[Microprofile](../../../tools/profiling/microprofile/index_cpp.md)* выше: пользовательская задача ("**MyCustomJob**"), отправленная в пул Sync через *runSync(4)*, выполняется на 4 потоках:

- **2 Pool Sync Threads** - рабочие потоки из целевого пула.
- **Main Thread** - *runSync()* выполняет один фрагмент на вызывающем потоке.
- **Pool Common Thread** - забрал фрагмент через [cross-pool execution](#cross_pool).


## См. также


- [Thread Safety in API](../../../code/fundamentals/thread_safety/index.md)
- [Thread Class](../../../api/library/common/mt/class.thread_cpp.md)
- [ThreadsPool Class](../../../api/library/common/mt/class.threadspool_cpp.md)
- [CPUShader Class](../../../api/library/common/mt/class.cpushader_cpp.md)
- [CPUTask Class](../../../api/library/common/mt/class.cputask_cpp.md)
- [Engine Main Loop](../../../code/fundamentals/execution_sequence/main_loop.md)
- [Microprofile](../../../tools/profiling/microprofile/index_cpp.md)
