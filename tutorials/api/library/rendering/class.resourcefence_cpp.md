# Unigine::ResourceFence Class (CPP)

**Header:** #include <UnigineResourceFence.h>


Этот класс позволяет управлять resource fence - объектом, обеспечивающим синхронизацию GPU-потока движка и внешнего GPU-потока.


> **Notice:** Синхронизация fence вызывается движком неявно, т.е. *ID3D12CommandQueue::Wait/ID3D12CommandQueue::Signal* (и аналогично для Vulkan с использованием timeline semaphores) вызывается в порядке **ID3D12CommandQueue::Wait - ID3D12CommandQueue::ExecuteCommandLists - ID3D12CommandQueue::Signal**.
>
>
> Для DX12 это вызывается во внутреннем потоке движка, тогда как реализация для Vulkan вызывает это из главного потока движка.
>
>
> Signal также увеличивает значения перед сигнализацией на GPU.


## ResourceFence Class

### Методы класса

---

## ResourceFence ( )

Конструктор ResourceFence. Resource fence создаётся включённым по умолчанию. Он создаётся в GPU-потоке движка и должен быть вручную импортирован во внешний графический API.
## void setEnabled ( bool enabled )

Включает и отключает resource fence.
### Аргументы

- *bool* **enabled** - true, чтобы включить resource fence, false, чтобы отключить его.

## bool isEnabled ( ) const

Возвращает значение, указывающее, включён ли resource fence.
### Возвращаемое значение

true, если resource fence включён, иначе false.
## void* getWin32Handle ( ) const

Возвращает указатель на переменную, получающую значение NT HANDLE для совместно используемого ресурса. Этот дескриптор можно использовать в вызовах для доступа к ресурсу.
### Возвращаемое значение

Win32-дескриптор. При вызове в Linux возвращает nullptr.
## int getFdHandle ( ) const

Возвращает файловый дескриптор, ссылающийся на содержимое объекта памяти устройства.
### Возвращаемое значение

Linux-дескриптор. При вызове в Windows возвращает -1.
## unsigned long long getValue ( ) const

Возвращает значение fence (значение сигнала и ожидания).
### Возвращаемое значение

Значение fence.
## unsigned long long incrementValue ( )

Увеличивает значение fence (значение сигнала и ожидания).
### Возвращаемое значение

Значение fence.
## void waitGPU ( )

Этот метод гарантирует завершение всех процессов в GPU-потоке движка.
## void closeHandle ( )

Закрывает дескриптор. Чтобы избежать утечек памяти, используйте этот метод, когда дескриптор ресурса больше не нужен (например, сразу после импорта объекта в другой графический API).
