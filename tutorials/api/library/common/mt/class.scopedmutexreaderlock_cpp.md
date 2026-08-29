# Unigine::ScopedMutexReaderLock<MutexType> Class (CPP)

**Header:** #include <UnigineThread.h>


Шаблонный класс, реализующий паттерн RAII (Resource Acquisition Is Initialization) для управления блокировкой мьютекса в многопоточной среде. Этот класс гарантирует, что мьютекс автоматически блокируется для чтения при создании и разблокируется при выходе объекта из области видимости.


Этот класс имеет следующие псевдонимы:


| Alias | Description | Type |
|---|---|---|
| **ScopedReaderSpinLock ScopedReaderLock** | Псевдоним для **ScopedMutexReaderLock**, использующий **[RWMutexSpin](../../../../api/library/common/mt/class.rwmutexspin_cpp.md)** в качестве базового мьютекса чтения-записи. Предоставляет блокировку чтения в области видимости через спин-блокировку. | **[RWMutexSpin](../../../../api/library/common/mt/class.rwmutexspin_cpp.md)** |
| **ScopedReaderSlimLock** | Псевдоним для **ScopedMutexReaderLock**, использующий **[RWMutexSlim](../../../../api/library/common/mt/class.rwmutexslim_cpp.md)** в качестве базового мьютекса чтения-записи. Предоставляет разделяемую блокировку в стиле RAII в области видимости через Windows ***SRW Lock***. | **[RWMutexSlim](../../../../api/library/common/mt/class.rwmutexslim_cpp.md)** |


## ScopedMutexReaderLock<MutexType> Class

### Методы класса

---

## ScopedMutexReaderLock ( MutexType& m )

Конструктор, блокирующий переданный мьютекс для чтения. Блокировка удерживается на протяжении всего времени жизни объекта **ScopedMutexReaderLock**.
### Аргументы

- *MutexType&* **m** - Ссылка на объект мьютекса, блокируемый для чтения. Мьютекс должен предоставлять функции-члены *lockRead()* и *unlockRead()*.

## ~ScopedMutexReaderLock ( )

Деструктор, автоматически разблокирующий мьютекс при выходе объекта **ScopedMutexReaderLock** из области видимости.
