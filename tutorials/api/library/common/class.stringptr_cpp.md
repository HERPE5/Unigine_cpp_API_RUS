# Unigine::StringPtr class (CPP)

**Header:** #include <UnigineString.h>


## StringPtr Class

### Методы класса

---

## static StringPtrPtr create ( )

Конструктор по умолчанию, создающий строку.
## static StringPtrPtr create ( const String & s )

Конструктор копирования.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md) &* **s** - Копируемая строка.

## static StringPtrPtr create ( const String Ptr & s )

Конструктор копирования.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md)Ptr &* **s** - Копируемая строка.

## static StringPtrPtr create ( const char * s )

Конструктор копирования.
### Аргументы

- *const char ** **s** - Копируемая строка.

## String Ptr & operator= ( const String Ptr & s )

Оператор присваивания для строки.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md)Ptr &* **s** - Значение строки.

## String Ptr & operator= ( const char * s )

Оператор присваивания для строки.
### Аргументы

- *const char ** **s** - Значение строки.

## String Ptr & operator= ( const String & s )

Оператор присваивания для строки.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md) &* **s** - Значение строки.

## void clear ( )

Очищает указатель на строку.
## int empty ( )

Возвращает флаг пустоты.
### Возвращаемое значение

1, если строка пуста; иначе 0.
## int size ( )

Возвращает размер строки.
### Возвращаемое значение

Размер строки.
## String Ptr & operator+= ( const String & s )

Сложение строк.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md) &* **s** - Вторая строка.

## String Ptr & operator+= ( const char * s )

Сложение строк.
### Аргументы

- *const char ** **s** - Символ.

## void swap ( String Ptr & s )

Меняет местами содержимое текущей строки и указанной.
### Аргументы

- *[String](../../../api/library/common/class.string_cpp.md)Ptr &* **s** - Вторая строка.

## const char * get ( )

Возвращает указатель на строку с завершающим нулём.
### Возвращаемое значение

Строка с завершающим нулём.
## const void * operator const void * ( )

Возвращает указатель на текущую строку.
### Возвращаемое значение

Указатель на строку.
## const char * operator const char * ( )

Возвращает указатель на текущую строку.
### Возвращаемое значение

Указатель на строку.
## const String & getString ( )

Возвращает строку.
### Возвращаемое значение

Строка.
