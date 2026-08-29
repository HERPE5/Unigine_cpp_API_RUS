# Unigine::PathWildcards Class (CPP)

**Header:** #include <UniginePathWildcards.h>


Этот класс представляет собой контейнер шаблонов путей (***wildcards***), который можно использовать для проверки того, соответствует ли заданный путь какому-либо из хранимых шаблонов. Обычно используется для фильтрации файлов и директорий на основе сопоставления с шаблоном.


> **Примечание:** Подробное руководство по синтаксису wildcard-шаблонов см. в статье **[Path Wildcards](../../../principles/filesystem/wildcards.md)**.


Поддерживаемые символы-шаблоны:


- `*` — соответствует любой последовательности символов, кроме `/`.
- `**` — соответствует любой последовательности директорий (включая отсутствие таковых), позволяя шаблонам охватывать несколько уровней директорий.
- `?` — соответствует ровно одному символу, кроме `/` (только ASCII).
- `[...]` — соответствует ровно одному символу из набора или диапазона (например, `[a-z0-9]`, `[abc]`). Также поддерживает POSIX-классы символов: `[:alnum:]`, `[:alpha:]`, `[:digit:]`, `[:lower:]`, `[:upper:]`, `[:space:]`, `[:punct:]`, `[:xdigit:]`.
- `[!...]` или `[^...]` — соответствует ровно одному символу, НЕ входящему в набор (например, `[!0-9]`).


Правила сопоставления шаблонов:


- Разделителем директорий является прямой слеш `/`.
- Если разделитель директорий стоит в начале или середине шаблона, шаблон считается относительным к корню пути данных. В противном случае шаблон может соответствовать на любом уровне директорий.
- Завершающий слеш `/` в шаблоне означает «соответствует этой директории и всему её содержимому».
- Используйте обратный слеш для экранирования символов `[` или `]` в шаблонах (например, `file\[1\].txt` соответствует `file[1].txt`).
- Символы-шаблоны `*` и `?` нельзя экранировать, так как эти символы запрещены в именах файлов в Windows.
- Шаблоны чувствительны к регистру.


> **Примечание:** Символ-шаблон `?` и диапазоны символов `[...]` некорректно работают с не-ASCII символами (например, Unicode). Используйте `*` для сопоставления не-ASCII символов.


Следующий фрагмент кода демонстрирует пример использования:


<details>
<summary>PathWildcards Usage Example</summary>

```cpp
#include <UniginePathWildcards.h>
#include <UnigineLog.h>
#include <UnigineVector.h>

// Создаём фильтр с несколькими шаблонами, используя Vector
Vector<String> patterns = {
	"*.tmp",          // Игнорировать все файлы .tmp
	"*.bak",          // Игнорировать все файлы .bak
	"build/",         // Игнорировать папку "build" и её содержимое
	"**/cache/",      // Игнорировать папку "cache" на любой глубине
	"log_??.txt",     // Игнорировать log_XX.txt (ровно 2 символа)
	"data[0-9].csv",  // Игнорировать data0.csv по data9.csv
	"[._]*"           // Игнорировать файлы, начинающиеся с . или _
};
PathWildcards ignore_patterns(patterns);

// Проверяем состояние фильтра
Log::message("Filter is empty: %d\n", ignore_patterns.empty());   // 0 (false)
Log::message("Number of patterns: %d\n", ignore_patterns.size()); // 7

// Перебираем все шаблоны по индексу
for (int i = 0; i < ignore_patterns.size(); i++)
{
	Log::message("Pattern[%d]: %s\n", i, ignore_patterns.getPattern(i));
}

// Получаем все шаблоны в виде вектора (два эквивалентных способа)
Vector<String> all_patterns = ignore_patterns.get();
// или: ignore_patterns.get(all_patterns);

// Проверяем пути файлов относительно фильтра
Vector<String> files = {
	"src/main.cpp",        // [OK] - ни один шаблон не совпал
	"build/output.exe",    // [SKIP] - совпадает с "build/"
	"data/cache/temp.dat", // [SKIP] - совпадает с "**/cache/"
	"backup.bak",          // [SKIP] - совпадает с "*.bak"
	"log_01.txt",          // [SKIP] - совпадает с "log_??.txt" (один ? = один символ)
	"log_1.txt",           // [OK] - не совпадает (после _ только один символ)
	"data5.csv",           // [SKIP] - совпадает с "data[0-9].csv"
	"dataX.csv",           // [OK] - не совпадает (X не входит в 0-9)
	".gitignore",          // [SKIP] - совпадает с "[._]*" (начинается с .)
	"_temp_file",          // [SKIP] - совпадает с "[._]*" (начинается с _)
	"readme.txt"           // [OK] - ни один шаблон не совпал
};

for (const String& file : files)
{
	if (ignore_patterns.matchPath(file))
		Log::message("[SKIP] %s\n", file.get());
	else
		Log::message("[OK] %s\n", file.get());
}

// Заменяем все шаблоны одним новым
ignore_patterns.set("*.log");
Log::message("After set(): %d patterns\n", ignore_patterns.size()); // 1

// Удаляем все шаблоны из фильтра
ignore_patterns.clear();
Log::message("After clear(): empty = %d\n", ignore_patterns.empty()); // 1 (true)

// Нормализуем строку шаблона (удаляет дублирующиеся слеши, преобразует обратные слеши)
StringStack<> normalized = PathWildcards::normalizePattern("folder\\\\subfolder//file.txt");
Log::message("Normalized: %s\n", normalized.get()); // "folder/subfolder/file.txt"

```

</details>


## PathWildcards Class

### Members

---

## PathWildcards ( )

Конструктор по умолчанию. Создаёт пустой экземпляр **PathWildcards** без шаблонов.
## PathWildcards ( const char* pattern )

Конструктор. Создаёт экземпляр **PathWildcards** и добавляет указанный шаблон.
### Arguments

- *const char** **pattern** - Начальный шаблон для добавления.

## PathWildcards ( const Vector < String >& patterns )

Конструктор. Создаёт экземпляр **PathWildcards** и добавляет все шаблоны из указанного вектора.
### Arguments

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)>&* **patterns** - Вектор шаблонов для добавления.

## bool empty ( ) const

Возвращает значение, указывающее, не содержит ли экземпляр **PathWildcards** шаблонов.
### Return value

true, если хранимых шаблонов нет; в противном случае false.
## int size ( ) const

Возвращает количество шаблонов, хранящихся в экземпляре **PathWildcards**.
### Return value

Количество шаблонов.
## void clear ( )

Удаляет все шаблоны из экземпляра **PathWildcards**.
## void add ( const char* pattern )

Добавляет один шаблон в экземпляр **PathWildcards**. Шаблон нормализуется внутренне (дублирующиеся слеши удаляются, обратные слеши преобразуются в прямые, кроме случаев экранирования скобок).
### Arguments

- *const char** **pattern** - Добавляемый шаблон.

## void add ( const Vector < String >& patterns )

Добавляет несколько шаблонов из указанного вектора в экземпляр **PathWildcards**.
### Arguments

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)>&* **patterns** - Вектор шаблонов для добавления.

## void set ( const char* pattern )

Очищает все существующие шаблоны и задаёт один новый шаблон.
### Arguments

- *const char** **pattern** - Устанавливаемый шаблон.

## void set ( const Vector < String >& patterns )

Очищает все существующие шаблоны и задаёт новые шаблоны из указанного вектора.
### Arguments

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)>&* **patterns** - Вектор устанавливаемых шаблонов.

## void get ( Vector < String >& patterns ) const

Добавляет все хранимые шаблоны в указанный вектор.
### Arguments

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)>&* **patterns** - Выходной вектор для получения шаблонов. Шаблоны добавляются в этот вектор.

## Vector < String > get ( ) const

Возвращает вектор, содержащий все хранимые шаблоны.
### Return value

Вектор, содержащий все хранимые шаблоны.
## const char* getPattern ( int i ) const

Возвращает шаблон по указанному индексу.
### Arguments

- *int* **i** - Индекс запрашиваемого шаблона. Должен находиться в диапазоне [0, size()).

### Return value

Шаблон по указанному индексу.
## bool matchPath ( const char* path ) const

Проверяет, соответствует ли указанный путь какому-либо из хранимых шаблонов. Путь нормализуется внутренне перед сопоставлением.
### Arguments

- *const char** **path** - Проверяемый путь.

### Return value

true, если путь соответствует какому-либо из хранимых шаблонов; в противном случае false.
## bool matchNormalizedPath ( const char* normalized_path ) const

Проверяет, соответствует ли указанный предварительно нормализованный путь какому-либо из хранимых шаблонов. Используйте этот метод для повышения производительности, если путь уже нормализован.
### Arguments

- *const char** **normalized_path** - Нормализованный путь для проверки. Путь должен быть предварительно нормализован с помощью *[String::normalizePath()](../../../api/library/common/class.string_cpp.md#normalizePath_const_char_ptr_StringStacktmplargs)* или *[String::normalizeDirPath()](../../../api/library/common/class.string_cpp.md#normalizeDirPath_const_char_ptr_StringStacktmplargs)*.

### Return value

true, если путь соответствует какому-либо из хранимых шаблонов; в противном случае false.
## static StringStack <> normalizePattern ( const char* pattern )

Нормализует шаблон, удаляя дублирующиеся слеши и преобразуя обратные слеши в прямые (кроме случаев экранирования символов скобок). Это статический служебный метод.
### Arguments

- *const char** **pattern** - Нормализуемый шаблон.

### Return value

Нормализованный шаблон.
