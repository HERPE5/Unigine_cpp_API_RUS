# Unigine::UnixAPI::MutexPThread Class (CPP)

**Header:** #include <UnigineThread.h>


Реализация мьютекса, ***специфичная для Linux***, которая оборачивает объект *pthread_mutex_t*, используя принципы RAII (Resource Acquisition Is Initialization). Использует функции из пространства имён *Unigine::UnixAPI* и предназначена только для сборок под Linux.


> **Notice:** Подробнее о ***pthread_mutex_t*** можно узнать [here](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_lock.html).


## MutexPThread Class

### Методы класса

---

## MutexPThread ( )

Конструктор. Инициализирует внутренний ***pthread_mutex_t*** атрибутами по умолчанию.
## ~MutexPThread ( )

Деструктор. Уничтожает внутренний мьютекс. Не должен вызываться, пока мьютекс заблокирован.
## void lock ( )

Блокирует вызывающий поток, пока мьютекс не станет доступным, а затем блокирует его.
## bool tryLock ( )

Пытается заблокировать мьютекс без ожидания.
### Возвращаемое значение

Возвращает true, если мьютекс был успешно заблокирован, иначе false.
## void unlock ( )

Освобождает мьютекс, позволяя другим потокам захватить его.
