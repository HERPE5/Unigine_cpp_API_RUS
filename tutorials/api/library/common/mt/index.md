# Функциональность многопоточности


Функциональность многопоточности UNIGINE предоставляет кроссплатформенные, низко- и высокоуровневые абстракции для построения эффективных многопоточных систем.


Она включает управление потоками, примитивы взаимного исключения (мьютексы), обёртки блокировок в области видимости и полный набор атомарных операций и классов.


### Управление потоками


Класс **[Thread](../../../../api/library/common/mt/class.thread_cpp.md)** является базовым классом для создания и управления потоками. Унаследуйтесь от него и реализуйте метод *process()*, чтобы определить логику вашего пользовательского потока.


Класс **[ThreadsPool](../../../../api/library/common/mt/class.threadspool_cpp.md)** — это планировщик работы CPU движка, распределяющий задачи **[CPUTask](../../../../api/library/common/mt/class.cputask_cpp.md)** и **[CPUShader](../../../../api/library/common/mt/class.cpushader_cpp.md)** между выделенными рабочими пулами (sync, async, critical, common, background, render-flush, file-stream, GPU-stream) и главным потоком.


**[ProcessTask](../../../../api/library/common/mt/class.processtask_cpp.md)** — это удобный базовый класс для повторяющихся задач — он оборачивает **CPUTask** циклом и защитой мьютексом, поэтому вам нужно реализовать только шаг работы и проверку продолжения.


### Мьютексы и блокировки


**Мьютексы** (взаимные исключения) — это основной инструмент для предотвращения одновременного доступа к разделяемым ресурсам. UNIGINE предоставляет различные типы мьютексов, оптимизированные для спин-блокировок, нативных системных API и повторно входимого поведения.


В большинстве случаев вам понадобится лишь ограниченный набор высокоуровневых классов и псевдонимов, обеспечивающих эффективную и безопасную синхронизацию из коробки:


- *[Mutex](../../../../api/library/common/mt/class.mutexspin_cpp.md)* - тип мьютекса по умолчанию, использующий спин-блокировку.
- *[ScopedLock](../../../../api/library/common/mt/class.scopedmutexlock_cpp.md)* - блокировка в области видимости для *Mutex*.
- *[ReentrantMutex](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md)* - повторно входимый мьютекс на основе спин-блокировки.
- *[ScopedReentrantLock](../../../../api/library/common/mt/class.scopedmutexlock_cpp.md)* - блокировка в области видимости для *ReentrantMutex*.
- *[RWMutex](../../../../api/library/common/mt/class.rwmutexspin_cpp.md)* - мьютекс чтения-записи по умолчанию на основе спин-блокировки.
- *[ScopedReaderLock](../../../../api/library/common/mt/class.scopedmutexreaderlock_cpp.md)* - блокировка чтения в области видимости для *RWMutex*.
- *[ScopedWriterLock](../../../../api/library/common/mt/class.scopedmutexwriterlock_cpp.md)* - блокировка записи в области видимости для *RWMutex*.


Если вам требуется больше контроля, специфичная для платформы интеграция или более низкоуровневая настройка производительности, библиотека также предоставляет мьютексы на основе спин-блокировок, обёртки для нативных системных API, шаблоны блокировок в области видимости и продвинутые типы мьютексов с отслеживанием состояния блокировки.


Для нативных реализаций мьютексов, специфичных для платформы, следующие псевдонимы разрешаются в **[MutexSlim](../../../../api/library/common/mt/class.mutexslim_cpp.md)** (SRW Lock) на Windows и **[MutexPThread](../../../../api/library/common/mt/class.mutexpthread_cpp.md)** (pthread_mutex_t) на Linux:


| Native Alias | Windows | Linux |
|---|---|---|
| **MutexNative** | MutexSlim | MutexPThread |
| **ScopedNativeLock** | ScopedSlimLock | ScopedPThreadLock |
| **MutexNativeAdvance** | MutexSlimAdvance | MutexPThreadAdvance |
| **ScopedNativeAdvanceLock** | ScopedSlimAdvanceLock | ScopedPThreadAdvanceLock |
| **ReentrantMutexNative** | ReentrantMutexSlim | ReentrantMutexPThread |
| **ScopedReentrantNativeLock** | ScopedReentrantSlimLock | ScopedReentrantPThreadLock |
| **RWMutexNative** | RWMutexSlim | RWMutex (RWMutexSpin) |
| **ScopedReaderNativeLock** | ScopedReaderSlimLock | ScopedReaderLock |
| **ScopedWriterNativeLock** | ScopedWriterSlimLock | ScopedWriterLock |


### Атомарные операции


Атомарные типы необходимы для построения безопасных и производительных многопоточных приложений. Они позволяют получать доступ к разделяемым данным и изменять их конкурентно без возникновения состояний гонки.


Эта атомарная система предоставляет универсальный шаблон **Atomic<Type>**, автоматически выбирающий наиболее подходящую базовую реализацию: ***lock-free*** или ***на основе мьютекса***, в зависимости от размера и типа переданного ***Type***. Этот выбор полностью разрешается на этапе компиляции.


> **Notice:** Используйте обобщённый шаблон ***Atomic<T>*** как выбор по умолчанию. Он автоматически выбирает наиболее эффективную реализацию (lock-free или на основе мьютекса) на основе типа во время компиляции.


Шаблон **Atomic<Type>** выбирает между несколькими внутренними реализациями, используя типовые признаки (type traits) и оценку размера. Логика принятия решения основана как на категории типа (целое число, указатель и т. д.), так и на размере данных, с конкретными проверками для 8-битных, 16-битных, 32-битных и 64-битных размеров. На основе этого выбирается подходящий необработанный тип хранения:


- **[AtomicInteger<Type>](../../../../api/library/common/mt/class.atomicinteger_cpp.md)** Используется для стандартных целочисленных типов размером до 64 бит (таких как int, short, long long и т. д.), кроме bool. Этот тип поддерживает атомарные арифметические и побитовые операции и всегда является lock-free.
- **[AtomicPointer<Type>](../../../../api/library/common/mt/class.atomicpointer_cpp.md)** Специализирован для типов указателей. Поддерживает атомарную арифметику указателей и операции CAS. Также lock-free и учитывает размер.
- **AtomicLockFree<Type>** Для всех остальных тривиально копируемых типов размером до 64 бит:

  - **[AtomicLockFreeRaw<Type>](../../../../api/library/common/mt/class.atomiclockfreeraw_cpp.md)** используется, если размер точно совпадает с необработанным типом.
  - **[AtomicLockFreeAlign<Type>](../../../../api/library/common/mt/class.atomiclockfreealign_cpp.md)** используется, когда для соответствия размеру требуется приведение типов с помощью объединений (union).
- **[AtomicWithMutex<Type>](../../../../api/library/common/mt/class.atomicwithmutex_cpp.md)** Резервный вариант для типов размером более 64 бит или не являющихся тривиально копируемыми. Эта версия не является lock-free, но поддерживает любой тип.


Для упрощения использования предоставляются следующие псевдонимы:


```cpp
// Boolean
using AtomicBool = Atomic<bool>;

// Signed integers
using AtomicInt8   = Atomic<char>;
using AtomicInt16  = Atomic<short>;
using AtomicInt32  = Atomic<int>;
using AtomicInt64  = Atomic<long long>;

// Unsigned integers
using AtomicUInt8  = Atomic<unsigned char>;
using AtomicUInt16 = Atomic<unsigned short>;
using AtomicUInt32 = Atomic<unsigned int>;
using AtomicUInt64 = Atomic<unsigned long long>;

// Floating point
using AtomicFloat  = Atomic<float>;
using AtomicDouble = Atomic<double>;

```


## Статьи в этом разделе

- [Thread Class (CPP)](../../../../api/library/common/mt/class.thread_cpp.md)

- [ThreadsPool Class (CPP)](../../../../api/library/common/mt/class.threadspool_cpp.md)

- [CPUShader Class (CPP)](../../../../api/library/common/mt/class.cpushader_cpp.md)

- [CPUShaderCallable Class (CPP)](../../../../api/library/common/mt/class.cpushadercallable_cpp.md)

- [CPUShaderCallableStateless Class (CPP)](../../../../api/library/common/mt/class.cpushadercallablestateless_cpp.md)



- [CPUTask Class (CPP)](../../../../api/library/common/mt/class.cputask_cpp.md)

- [ProcessTask Class (CPP)](../../../../api/library/common/mt/class.processtask_cpp.md)

- [AsyncTaskCallable Class (CPP)](../../../../api/library/common/mt/class.asynctaskcallable_cpp.md)

- [AtomicInteger<Type> Struct (CPP)](../../../../api/library/common/mt/class.atomicinteger_cpp.md)

- [AtomicPointer<Type> Struct (CPP)](../../../../api/library/common/mt/class.atomicpointer_cpp.md)

- [AtomicLockFreeAlign<Type> Struct (CPP)](../../../../api/library/common/mt/class.atomiclockfreealign_cpp.md)

- [AtomicLockFreeRaw<Type> Struct (CPP)](../../../../api/library/common/mt/class.atomiclockfreeraw_cpp.md)

- [AtomicWithMutex<Type, MutexType> Struct (CPP)](../../../../api/library/common/mt/class.atomicwithmutex_cpp.md)

- [MutexSlim Class (CPP)](../../../../api/library/common/mt/class.mutexslim_cpp.md)

- [MutexCriticalSection Class (CPP)](../../../../api/library/common/mt/class.mutexcriticalsection_cpp.md)

- [MutexSpin Class (CPP)](../../../../api/library/common/mt/class.mutexspin_cpp.md)

- [MutexPThread Class (CPP)](../../../../api/library/common/mt/class.mutexpthread_cpp.md)

- [MutexAdvance<MutexType> Class (CPP)](../../../../api/library/common/mt/class.mutexadvance_cpp.md)

- [ReentrantMutexBase<MutexType> Class (CPP)](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md)

- [RWMutexSlim Class (CPP)](../../../../api/library/common/mt/class.rwmutexslim_cpp.md)

- [RWMutexSpin Class (CPP)](../../../../api/library/common/mt/class.rwmutexspin_cpp.md)

- [ScopedMutexLock<MutexType> Class (CPP)](../../../../api/library/common/mt/class.scopedmutexlock_cpp.md)

- [ScopedMutexReaderLock<MutexType> Class (CPP)](../../../../api/library/common/mt/class.scopedmutexreaderlock_cpp.md)

- [ScopedMutexWriterLock<MutexType> Class (CPP)](../../../../api/library/common/mt/class.scopedmutexwriterlock_cpp.md)

- [ScopedSpinLockInteger<Type> Class (CPP)](../../../../api/library/common/mt/class.scopedspinlockinteger_cpp.md)

- [BackoffSpinner Class (CPP)](../../../../api/library/common/mt/class.backoffspinner_cpp.md)
