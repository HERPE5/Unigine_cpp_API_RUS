# Unigine::WinAPI::MutexCriticalSection Class (CPP)

**Header:** #include <UnigineThread.h>


Реализация мьютекса, ***специфичная для Windows***, которая оборачивает объект *CRITICAL_SECTION*, используя принципы RAII (Resource Acquisition Is Initialization). Использует функции из пространства имён *Unigine::WinAPI* и предназначена только для сборок под Windows.


> **Notice:** Подробнее об объекте ***CRITICAL_SECTION*** можно узнать [here](https://learn.microsoft.com/en-us/windows/win32/sync/critical-section-objects).


## MutexCriticalSection Class

### Методы класса

---

## MutexCriticalSection ( )

Конструктор. Инициализирует внутренний объект ***CRITICAL_SECTION***.
## ~MutexCriticalSection ( )

Деструктор. Уничтожает внутренний объект ***CRITICAL_SECTION***.
## void lock ( )

Захватывает критическую секцию, блокируя вызывающий поток при необходимости, пока блокировка не станет доступной.
## bool tryLock ( )

Пытается захватить критическую секцию без блокировки.
### Возвращаемое значение

Возвращает true, если блокировка была успешно захвачена; иначе false.
## void unlock ( )

Освобождает критическую секцию, позволяя другим потокам войти.
