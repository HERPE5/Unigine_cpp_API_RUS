# Unigine::StringStack class (CPP)

**Header:** #include <UnigineString.h>


Строка, хранящаяся в стеке. По умолчанию переменная StringStack резервирует 256 байт в стеке. Память выделяется динамически только тогда, когда размер данных превышает указанную *[capacity](#StringStacktmplargs_StringStacktmplargs_rvref_void)*.


> **Notice:** Если вы заранее знаете, что размер данных будет большим (например, при чтении текста из файла), используйте вместо этого [String](../../../api/library/common/class.string_cpp.md).


Такие строки обычно используются в следующих случаях:


- Когда строка создаётся и используется только один раз. ```cpp #include "AppWorldLogic.h" #include <UnigineString.h> #include <UnigineVector.h> #include <UnigineFileSystem.h> using namespace Unigine; StringStack<> AppWorldLogic::get_first_string() { return "This is a "; } StringStack<> AppWorldLogic::get_second_string() { return "string"; } void AppWorldLogic::my_file_write(FilePtr file, const char *s) { file->writeString("Sample Text\n"); file->writeString(s); } int AppWorldLogic::init() { // получаем строку StringStack<> str = get_first_string(); // строим строку str += get_second_string(); // используем построенную строку каким-либо образом FilePtr file = File::create(); file->open("file.txt", "wb"); if (file->isOpened()) { my_file_write(file, str); file->close(); } return 1; } ```
- Когда выполняются операции над строками, результаты всегда сохраняются в стеке. ```cpp const char *one = "one"; const String two = get_second_string(); // добавляем одну строку к другой StringStack<> s0 = one + two; StringStack<> s1 = two + two; const String file_name = file->getName(); // получаем расширение, если оно есть StringStack<> ext = file_name.extension(); ``` > **Notice:** Обращайте внимание на тип результата операции для его оптимального использования и во избежание проблем.


## StringStack Class

### Методы класса

---

## static StringStackPtr create ( )

Конструктор по умолчанию, создающий пустую строку размера по умолчанию (256 символов).
## static StringStackPtr create ( const String & s )

Конструктор копирования. Создаёт строку, хранящую указанную строку.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md) &* **s** - Копируемая строка.

## static StringStackPtr create ( const StringStack <Capacity> & s )

Конструктор копирования.
### Аргументы

- *const [StringStack](../../../api/library/common/class.stringstack_cpp.md)<Capacity> &* **s** - Стек строк указанного размера.

## static StringStackPtr create ( const char * s )

Конструктор копирования.
### Аргументы

- *const char ** **s** - Указатель на строку с завершающим нулём.

## void destroy ( )

Уничтожает строку.
## void StringStack<Capacity> ( StringStack <OtherCapacity> && s )

Копирует указанную строку в текущую строку.
### Аргументы

- *[StringStack](../../../api/library/common/class.stringstack_cpp.md)<OtherCapacity> &&* **s** - Копируемая строка указанного размера.

## StringStack <Capacity> & operator= ( const StringStack <Capacity> & s )

Оператор присваивания для строки.
### Аргументы

- *const [StringStack](../../../api/library/common/class.stringstack_cpp.md)<Capacity> &* **s** - Строка.

## StringStack <Capacity> & operator= ( const char * s )

Оператор присваивания для строки.
### Аргументы

- *const char ** **s** - Указатель на строку с завершающим нулём.

## StringStack <Capacity> & operator= ( StringStack <OtherCapacity> && s )

Оператор присваивания для строки.
### Аргументы

- *[StringStack](../../../api/library/common/class.stringstack_cpp.md)<OtherCapacity> &&* **s** - Строка указанного размера.

## StringStack <Capacity> & operator= ( const String & s )

Оператор присваивания для строки.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md) &* **s** - Строка.
