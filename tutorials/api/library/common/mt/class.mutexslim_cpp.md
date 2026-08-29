# Unigine::WinAPI::MutexSlim Class (CPP)

**Header:** #include <UnigineThread.h>


Реализация мьютекса, ***специфичная для Windows***, которая оборачивает объект *Slim Reader/Writer Lock*, используя принципы RAII (Resource Acquisition Is Initialization). Использует функции из пространства имён *Unigine::WinAPI* и предназначена только для сборок под Windows.


> **Notice:** Подробнее о ***SRW Locks*** можно узнать [here](https://learn.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks).


## MutexSlim Class

### Методы класса

---

## MutexSlim ( )

Конструктор. Инициализирует внутренний **SRWLOCK**, вызывая *WinAPI::InitializeSRWLock*.
## ~MutexSlim ( )

Деструктор. Проверяет утверждением (assert), что блокировка не удерживается во время уничтожения.
## void lock ( )

Захватывает slim-блокировку в эксклюзивном (write) режиме. Блокирует вызывающий поток, если блокировка уже удерживается.
## bool tryLock ( )

Пытается захватить slim-блокировку в эксклюзивном режиме без ожидания.
### Возвращаемое значение

Возвращает true, если мьютекс был успешно заблокирован, иначе false.
## void unlock ( )

Освобождает эксклюзивную slim-блокировку.
