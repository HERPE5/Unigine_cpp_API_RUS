# Unigine::ScopedMutexWriterLock<MutexType> Class (CPP)

**Header:** #include <UnigineThread.h>


Шаблонный класс, реализующий паттерн RAII (Resource Acquisition Is Initialization) для управления блокировкой мьютекса в многопоточной среде. Этот класс гарантирует, что мьютекс автоматически блокируется для записи при создании и разблокируется при выходе объекта из области видимости.


Этот класс имеет следующие псевдонимы:


| Alias | Description | Type |
|---|---|---|
| **ScopedWriterSpinLock ScopedWriterLock** | Псевдоним для **ScopedMutexWriterLock**, использующий **[RWMutexSpin](../../../../api/library/common/mt/class.rwmutexspin_cpp.md)** в качестве базового мьютекса чтения-записи. Предоставляет блокировку записи в области видимости через спин-блокировку. | **[RWMutexSpin](../../../../api/library/common/mt/class.rwmutexspin_cpp.md)** |
| **ScopedWriterSlimLock** | Псевдоним для **ScopedMutexWriterLock**, использующий **[RWMutexSlim](../../../../api/library/common/mt/class.rwmutexslim_cpp.md)** в качестве базового мьютекса чтения-записи. Предоставляет эксклюзивную блокировку в стиле RAII в области видимости через Windows ***SRW Lock***. | **[RWMutexSlim](../../../../api/library/common/mt/class.rwmutexslim_cpp.md)** |


## ScopedMutexWriterLock<MutexType> Class

### Методы класса

---

## ScopedMutexWriterLock ( MutexType& m )

Конструктор, блокирующий переданный мьютекс для записи. Блокировка удерживается на протяжении всего времени жизни объекта **ScopedMutexWriterLock**.
### Аргументы

- *MutexType&* **m** - Ссылка на объект мьютекса, блокируемый для записи. Мьютекс должен предоставлять функции-члены *lockWrite()* и *unlockWrite()*.

## ~ScopedMutexWriterLock ( )

Деструктор, автоматически разблокирующий мьютекс при выходе объекта **ScopedMutexWriterLock** из области видимости.
