# Unigine::ScopedMutexLock<MutexType> Class (CPP)

**Header:** #include <UnigineThread.h>


Шаблонный класс, реализующий паттерн RAII (Resource Acquisition Is Initialization) для управления блокировкой мьютекса в многопоточной среде. Этот класс гарантирует, что мьютекс автоматически блокируется при создании и разблокируется при выходе объекта из области видимости.


Этот класс имеет следующие псевдонимы:


| Alias | Description | Type |
|---|---|---|
| **ScopedSpinLock ScopedLock** | Псевдоним для **ScopedMutexLock**, использующий класс **[MutexSpin](../../../../api/library/common/mt/class.mutexspin_cpp.md)** для блокировки на основе спин-блокировки в области видимости. Гарантирует захват спин-блокировки при создании и её освобождение при уничтожении. | **[MutexSpin](../../../../api/library/common/mt/class.mutexspin_cpp.md)** |
| **ScopedReentrantSpinLock ScopedReentrantLock** | Псевдоним для **ScopedMutexLock**, использующий **[ReentrantMutexSpin](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md)**, обеспечивающий блокировку повторно входимых спин-блокировок в области видимости. | **[ReentrantMutexSpin](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md)** |
| **ScopedCriticalSectionLock** | Псевдоним для **ScopedMutexLock**, использующий **[MutexCriticalSection](../../../../api/library/common/mt/class.mutexcriticalsection_cpp.md)**. Предоставляет блокировку в стиле RAII в области видимости с использованием Windows ***CRITICAL_SECTION***. | **[MutexCriticalSection](../../../../api/library/common/mt/class.mutexcriticalsection_cpp.md)** |
| **ScopedSlimLock** | Псевдоним для **ScopedMutexLock**, использующий **[MutexSlim](../../../../api/library/common/mt/class.mutexslim_cpp.md)**. Предоставляет блокировку в стиле RAII в области видимости с использованием Windows ***SRW Lock***. | **[MutexSlim](../../../../api/library/common/mt/class.mutexslim_cpp.md)** |
| **ScopedReentrantSlimLock** | Псевдоним для **ScopedMutexLock**, использующий **[ReentrantMutexSlim](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md#reentrant_mutex_slim)**. Предоставляет блокировку в стиле RAII в области видимости с поддержкой повторной входимости с использованием Windows ***SRW Lock***. | **[ReentrantMutexSlim](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md#reentrant_mutex_slim)** |
| **ScopedSlimAdvanceLock** | Псевдоним для **ScopedMutexLock**, использующий **[MutexSlimAdvance](../../../../api/library/common/mt/class.mutexadvance_cpp.md#mutex_slim_advance)**. Предоставляет блокировку в стиле RAII в области видимости с возможностью проверки, удерживается ли блокировка в данный момент, с использованием Windows ***SRW Lock***. | **[MutexSlimAdvance](../../../../api/library/common/mt/class.mutexadvance_cpp.md#mutex_slim_advance)** |
| **ScopedCriticalSectionAdvanceLock** | Псевдоним для **ScopedMutexLock**, использующий **[MutexCriticalSectionAdvance](../../../../api/library/common/mt/class.mutexadvance_cpp.md#mutex_critical_section_advance)**. Предоставляет блокировку в стиле RAII в области видимости с возможностью проверки, удерживается ли блокировка в данный момент, с использованием Windows ***CRITICAL_SECTION***. | **[MutexCriticalSectionAdvance](../../../../api/library/common/mt/class.mutexadvance_cpp.md#mutex_critical_section_advance)** |
| **ScopedPThreadLock** | Псевдоним для **ScopedMutexLock**, использующий **[MutexPThread](../../../../api/library/common/mt/class.mutexpthread_cpp.md)**. Предоставляет блокировку в стиле RAII в области видимости через мьютекс Linux ***pthread_mutex_t***. | **[MutexPThread](../../../../api/library/common/mt/class.mutexpthread_cpp.md)** |
| **ScopedReentrantPThreadLock** | Псевдоним для **ScopedMutexLock**, использующий **[ReentrantMutexPThread](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md#reentrant_mutex_pthread)**. Предоставляет блокировку в области видимости с повторной входимостью через мьютекс Linux ***pthread_mutex_t***. | **[ReentrantMutexPThread](../../../../api/library/common/mt/class.reentrantmutexbase_cpp.md#reentrant_mutex_pthread)** |
| **ScopedPThreadAdvanceLock** | Псевдоним для **ScopedMutexLock**, использующий **[MutexPThreadAdvance](../../../../api/library/common/mt/class.mutexadvance_cpp.md#mutex_pthread_advance)**. Предоставляет блокировку в области видимости с отслеживанием внутреннего состояния через мьютекс Linux ***pthread_mutex_t***. | **[MutexPThreadAdvance](../../../../api/library/common/mt/class.mutexadvance_cpp.md#mutex_pthread_advance)** |


## ScopedMutexLock<MutexType> Class

### Методы класса

---

## ScopedMutexLock ( MutexType& m )

Конструктор, блокирующий переданный мьютекс. Блокировка удерживается на протяжении всего времени жизни объекта **ScopedMutexLock**.
### Аргументы

- *MutexType&* **m** - Ссылка на объект мьютекса для блокировки. Мьютекс должен предоставлять функции-члены *lock()* и *unlock()*.

## ~ScopedMutexLock ( )

Деструктор, автоматически разблокирующий мьютекс при выходе объекта **ScopedMutexLock** из области видимости.
