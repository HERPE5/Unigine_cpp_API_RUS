# Unigine::Plugins::Weather::Manager Class (CPP)

**Header:** #include <plugins/Unigine/Weather/UnigineWeather.h>


Этот класс представляет интерфейс Weather Manager.

> **Notice:** Плагин Weather должен быть загружен.


## Weather::Manager Class

### Методы класса

---

## void saveState ( const Ptr < Stream > & blob ) const

Сохраняет состояние Weather Manager в бинарный поток.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **blob** - Поток для сохранения данных погоды.

## void restoreState ( const Ptr < Stream > & blob )

Восстанавливает состояние Weather Manager из бинарного потока.
### Аргументы

- *const [Ptr](../../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../../api/library/common/class.stream_cpp.md)> &* **blob** - Поток, хранящий данные погоды.
