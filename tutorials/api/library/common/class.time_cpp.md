# Unigine::Time Class (CPP)

**Header:** #include <UnigineTimer.h>


Этот класс используется для получения текущего системного времени и преобразования его в различные единицы измерения.


> **Notice:** **Этот класс не реализован в C# API движка**, поскольку доступны другие варианты:
>
>
> Метод **[Stopwatch.GetTimestamp()](https://learn.microsoft.com/en-us/dotnet/api/system.diagnostics.stopwatch.gettimestamp?view=net-8.0#system-diagnostics-stopwatch-gettimestamp)** (из стандартного модуля **System.Diagnostics**) — наиболее точный и близкий к времени по настенным часам. Он возвращает секунды с двойной точностью, позволяя работать с микросекундами/наносекундами. Он игнорирует скачки и зависания. Может использоваться для любых независимых от приложения вычислений времени.
>
>
> Если такая высокая точность времени не требуется, можно просто использовать стандартное и удобное свойство **[DateTime.Now](https://learn.microsoft.com/en-us/dotnet/api/system.datetime.now?view=net-8.0)**.


## Timer Class

### Методы класса

---

## static double microsecondsToNanoseconds ( long long microseconds )

Преобразует микросекунды в наносекунды.
### Аргументы

- *long long* **microseconds** - Микросекунды.

### Возвращаемое значение

Наносекунды.
## static double microsecondsToMilliseconds ( long long microseconds )

Преобразует микросекунды в миллисекунды.
### Аргументы

- *long long* **microseconds** - Микросекунды.

### Возвращаемое значение

Миллисекунды.
## static double microsecondsToSeconds ( long long microseconds )

Преобразует микросекунды в секунды.
### Аргументы

- *long long* **microseconds** - Микросекунды.

### Возвращаемое значение

Секунды.
## static double millisecondsToNanoseconds ( double milliseconds )

Преобразует миллисекунды в наносекунды.
### Аргументы

- *double* **milliseconds** - Миллисекунды.

### Возвращаемое значение

Наносекунды.
## static double millisecondsToMicroseconds ( double milliseconds )

Преобразует миллисекунды в микросекунды.
### Аргументы

- *double* **milliseconds** - Миллисекунды.

### Возвращаемое значение

Микросекунды.
## static double millisecondsToSeconds ( double milliseconds )

Преобразует миллисекунды в секунды.
### Аргументы

- *double* **milliseconds** - Миллисекунды.

### Возвращаемое значение

Секунды.
## static double secondsToNanoseconds ( double seconds )

Преобразует секунды в наносекунды.
### Аргументы

- *double* **seconds** - Секунды.

### Возвращаемое значение

Наносекунды.
## static double secondsToMicroseconds ( double seconds )

Преобразует секунды в микросекунды.
### Аргументы

- *double* **seconds** - Секунды.

### Возвращаемое значение

Микросекунды.
## static double secondsToMilliseconds ( double seconds )

Преобразует секунды в миллисекунды.
### Аргументы

- *double* **seconds** - Секунды.

### Возвращаемое значение

Миллисекунды.
## static double hertzToNanoseconds ( double hertz )

Преобразует частоту в герцах в наносекунды.
### Аргументы

- *double* **hertz** - Герцы.

### Возвращаемое значение

Наносекунды.
## static double hertzToMicroseconds ( double hertz )

Преобразует частоту в герцах в микросекунды.
### Аргументы

- *double* **hertz** - Герцы.

### Возвращаемое значение

Микросекунды.
## static double hertzToMilliseconds ( double hertz )

Преобразует частоту в герцах в миллисекунды.
### Аргументы

- *double* **hertz** - Герцы.

### Возвращаемое значение

Миллисекунды.
## static double hertzToSeconds ( double hertz )

Преобразует частоту в герцах в секунды.
### Аргументы

- *double* **hertz** - Герцы.

### Возвращаемое значение

Секунды.
## static long long getClock ( )

Возвращает счётчик тактов CPU.
### Возвращаемое значение

Счётчик тактов CPU.
## static long long get ( )

Возвращает время в микросекундах.
### Возвращаемое значение

Время в микросекундах.
## static double getSeconds ( )

Возвращает время в секундах.
### Возвращаемое значение

Время в секундах.
## static double getMilliseconds ( )

Возвращает время в миллисекундах.
### Возвращаемое значение

Время в миллисекундах.
