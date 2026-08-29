# Unigine::WinAPI::RWMutexSlim Class (CPP)

**Header:** #include <UnigineThread.h>


Реализация мьютекса чтения-записи, ***специфичная для Windows***, которая оборачивает объект *Slim Reader/Writer Lock*, используя принципы RAII (Resource Acquisition Is Initialization). Использует функции из пространства имён *Unigine::WinAPI* и предназначена только для сборок под Windows.


Этот класс позволяет конкурентный разделяемый (чтение) доступ и эксклюзивный (запись) доступ.


> **Notice:** Подробнее о ***SRW Locks*** можно узнать [here](https://learn.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks).


## RWMutexSlim Class

### Методы класса

---

## RWMutexSlim ( )

Конструктор. Инициализирует внутренний **SRWLOCK**, вызывая *WinAPI::InitializeSRWLock*.
## ~RWMutexSlim ( )

Деструктор. Проверяет утверждением (assert), что блокировка не удерживается во время уничтожения.
## void lockRead ( )

Захватывает разделяемую (read) блокировку. Несколько потоков могут удерживать блокировку чтения одновременно.
## bool tryLockRead ( )

Пытается захватить разделяемую (read) блокировку без ожидания.
## void unlockRead ( )

Освобождает ранее захваченную разделяемую (read) блокировку.
## void lockWrite ( )

Захватывает эксклюзивную (write) блокировку. Блокирует выполнение, пока ни один другой поток не удерживает блокировку чтения или записи.
## bool tryLockWrite ( )

Пытается захватить эксклюзивную (write) блокировку без ожидания.
## void unlockWrite ( )

Освобождает ранее захваченную эксклюзивную (write) блокировку.
## void lock ( )

Псевдоним для *[lockWrite()](#lockWrite_void)*. Позволяет использовать ***RWMutexSlim*** в обобщённых интерфейсах блокировки.
## bool tryLock ( )

Псевдоним для *[tryLockWrite()](#tryLockWrite_bool)*. Позволяет использовать ***RWMutexSlim*** в обобщённых интерфейсах блокировки.
## void unlock ( )

Псевдоним для *[unlockWrite()](#unlockWrite_void)*. Позволяет использовать ***RWMutexSlim*** в обобщённых интерфейсах блокировки.
