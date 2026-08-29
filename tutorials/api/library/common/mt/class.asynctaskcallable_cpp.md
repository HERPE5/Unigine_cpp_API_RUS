# Unigine::AsyncTaskCallable Class (CPP)

**Header:** #include <UnigineThread.h>

**Inherits from:** CPUTask


**AsyncTaskCallable** — это шаблонный класс, предоставляющий упрощённый способ выполнения пользовательской однопоточной логики задачи с использованием класса **[CPUTask](../../../../api/library/common/mt/class.cputask_cpp.md)**.


Обычно для использования **[CPUTask](../../../../api/library/common/mt/class.cputask_cpp.md)** необходимо унаследоваться от базового класса **[CPUTask](../../../../api/library/common/mt/class.cputask_cpp.md)** и вручную реализовать метод *process()*. Однако **AsyncTaskCallable** позволяет передавать логику обработки и логику очистки напрямую в виде функциональных объектов, без написания пользовательского класса или управления наследованием.


Используйте вспомогательную функцию [makeCPUTask()](../../../../api/library/common/class.unigine.namespace_cpp.md#makeCPUTask_Callable_Priority_FrameSyncMode) для удобного создания экземпляров.


**Параметры шаблона**:


- **Callable** - функция, вызываемая при выполнении задачи. Сигнатура: *void(CPUTask *task)*
- **Destroy** - функция, вызываемая один раз при уничтожении. Сигнатура: *void()*


## AsyncTaskCallable Class

### Методы класса

---

## AsyncTaskCallable ( Callable callable_ , Destroy destroy_ , Priority priority_ = Priority::Normal , FrameSyncMode frame_sync_ = FrameSyncMode::Disabled )

Создаёт новый экземпляр AsyncTaskCallable.
### Аргументы

- *Callable* **callable_** - Функция, выполняемая при запуске задачи.
- *Destroy* **destroy_** - Функция очистки, вызываемая при уничтожении.
- *[Priority](#Priority)* **priority_** - Приоритет задачи в очереди пула.
- *[FrameSyncMode](#FrameSyncMode)* **frame_sync_** - Режим синхронизации кадра.

## void process ( )

Переопределено из **[CPUTask](../../../../api/library/common/mt/class.cputask_cpp.md)**. Вызывает переданную функцию callable, передавая указатель на задачу в качестве аргумента.
