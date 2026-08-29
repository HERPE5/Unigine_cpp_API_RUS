# Unigine::ScopedSpinLockInteger<Type> Class (CPP)

**Header:** #include <UnigineThread.h>


Шаблонный класс, реализующий паттерн управления блокировками с использованием спин-блокировок для синхронизации доступа к разделяемым данным в многопоточной среде. Этот класс используется для захвата и освобождения блокировки на протяжении времени жизни объекта, гарантируя автоматическое освобождение блокировки при выходе объекта из области видимости.


```cpp
volatile int lock = 0;									// Блокируемая переменная

// Определение области видимости
{
	ScopedSpinLockInteger<int> lock_guard(lock);		// Блокировка захватывается здесь

	Log::message("Critical section accessed!");			// Некоторые действия в критической секции

}														// Блокировка автоматически освобождается здесь

```


Этот класс имеет следующие псевдонимы:


| Alias | Description | Type |
|---|---|---|
| **ScopedSpinLockChar** **ScopedSpinLock8** | Псевдоним для **ScopedSpinLockInteger** с использованием типа char (8-бит) | char |
| **ScopedSpinLockShort** **ScopedSpinLock16** | Псевдоним для **ScopedSpinLockInteger** с использованием типа short (16-бит) | short |
| **ScopedSpinLockInt** **ScopedSpinLock32** | Псевдоним для **ScopedSpinLockInteger** с использованием типа int (32-бит) | int |
| **ScopedSpinLockLongLong** **ScopedSpinLock64** | Псевдоним для **ScopedSpinLockInteger** с использованием типа long long (64-бит) | long long |


## ScopedSpinLockInteger<Type> Class

### Методы класса

---

## ScopedSpinLockInteger ( volatile Type& m )

Конструктор, захватывающий спин-блокировку для переданного объекта мьютекса. Вызывает функцию *[MutexSpinLock](../../../../api/library/common/class.unigine.namespace_cpp.md#MutexSpinLock_volatiletmpl_void)* для захвата блокировки. Блокировка останется активной, пока объект **ScopedSpinLockInteger** не выйдет из области видимости.
### Аргументы

- *volatile Type&* **m** - Ссылка на объект типа *volatile Type*, представляющий блокируемую переменную.

## ~ScopedSpinLockInteger ( )

Деструктор, освобождающий спин-блокировку путём вызова функции *[MutexSpinUnlock](../../../../api/library/common/class.unigine.namespace_cpp.md#MutexSpinUnlock_volatiletmpl_void)*.
