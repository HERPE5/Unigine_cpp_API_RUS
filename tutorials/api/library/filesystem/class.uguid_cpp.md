# Unigine::UGUID Class (CPP)

**Header:** #include <UnigineGUID.h>


Этот класс представляет глобально уникальный идентификатор (40-байтное хэш-значение). Для генерации хэша используется алгоритм [SHA1](http://www.faqs.org/rfcs/rfc3174.html).


## UGUID Class

### Методы класса

---

## UGUID ( )

Конструктор по умолчанию. Создаёт пустой UGUID, заполненный нулями.
## UGUID ( const char * str )

Конструктор. Создаёт UGUID из указанной исходной строки. UGUID генерируется с помощью алгоритма [SHA1](http://www.faqs.org/rfcs/rfc3174.html).
### Аргументы

- *const char ** **str** - Исходная строка.

## UGUID ( unsigned char(& value_ )[VALUE_SIZE] )

Конструктор. Создаёт UGUID из указанного исходного значения. UGUID генерируется с помощью алгоритма [SHA1](http://www.faqs.org/rfcs/rfc3174.html).
### Аргументы

## UGUID ( unsigned int(& value_ )[NUM_VALUE_INT] )

Конструктор. Создаёт UGUID из указанного исходного значения. UGUID генерируется с помощью алгоритма [SHA1](http://www.faqs.org/rfcs/rfc3174.html).
### Аргументы

## UGUID ( const String & str )

Конструктор. Создаёт UGUID из указанной исходной строки. UGUID генерируется с помощью алгоритма [SHA1](http://www.faqs.org/rfcs/rfc3174.html).
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md) &* **str** - Исходная строка.

## UGUID ( const UGUID & guid )

Конструктор копирования. Создаёт UGUID путём копирования исходного UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - Исходный UGUID.

## void generate ( )

Генерирует новое случайное значение UGUID.
## void generate ( const char * str )

Генерирует значение UGUID из указанной исходной строки с помощью алгоритма [SHA1](http://www.faqs.org/rfcs/rfc3174.html).
### Аргументы

- *const char ** **str** - Исходная строка.

## void generate ( int& seed_ )

Генерирует случайное значение UGUID с использованием начального значения (seed).
### Аргументы

- *int&* **seed_** - Начальное значение (seed).

## void generate ( const void* data , int size )

Генерирует значение UGUID из указанного исходного массива байтов заданного размера с помощью алгоритма [SHA1](http://www.faqs.org/rfcs/rfc3174.html).
### Аргументы

- *const void** **data** - Исходный массив байтов.
- *int* **size** - Количество байтов, взятых из массива байтов для генерации UGUID.

## unsigned int hash ( )

Возвращает хэш для значения UGUID.
### Возвращаемое значение

Хэш, сгенерированный для значения UGUID.
## void clear ( )

Очищает значение UGUID. Все 40 байтов устанавливаются в 0.
## bool isEmpty ( ) const

Возвращает значение, указывающее, является ли UGUID пустым (все 40 байтов равны 0).
### Возвращаемое значение

**true**, если UGUID пуст; иначе false.
## bool isValid ( ) const

Возвращает значение, указывающее, имеет ли UGUID корректное значение.
### Возвращаемое значение

**true**, если значение корректно; иначе false.
## void setString ( const char * str )

Устанавливает значение UGUID равным указанной 40-символьной шестнадцатеричной строке.
### Аргументы

- *const char ** **str** - 40-символьная шестнадцатеричная строка, представляющая значение UGUID.

## UGUID & operator= ( const char * str )

Выполняет присваивание UGUID. Значение целевого UGUID устанавливается равным исходной шестнадцатеричной строке.
### Аргументы

- *const char ** **str** - Исходная строка. A 40-character hexadecimal string representing the UGUID value.

### Возвращаемое значение

Результат.
## UGUID & operator= ( const String & str )

Выполняет присваивание UGUID. Значение целевого UGUID устанавливается равным исходной строке.
### Аргументы

- *const [String](../../../api/library/common/class.string_cpp.md) &* **str** - Исходная строка.

### Возвращаемое значение

Результат.
## UGUID & operator= ( const UGUID & g )

Выполняет присваивание UGUID. Целевой UGUID = Исходный UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Исходный UGUID.

### Возвращаемое значение

Результат.
## int operator> ( const UGUID & g )

Указывает, больше ли значение UGUID, чем значение исходного UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Исходный UGUID.

### Возвращаемое значение

**1**, если значение UGUID больше значения исходного UGUID; иначе 0.
## int operator>= ( const UGUID & g )

Указывает, больше ли значение UGUID или равно значению исходного UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Исходный UGUID.

### Возвращаемое значение

**1**, если значение UGUID больше или равно значению исходного UGUID; иначе 0.
## int operator< ( const UGUID & g )

Указывает, меньше ли значение UGUID, чем значение исходного UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Исходный UGUID.

### Возвращаемое значение

**1**, если значение UGUID меньше или равно значению исходного UGUID; иначе 0.
## int operator<= ( const UGUID & g )

Указывает, меньше ли значение UGUID или равно значению исходного UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Исходный UGUID.

### Возвращаемое значение

**1**, если значение UGUID меньше или равно значению исходного UGUID; иначе 0.
## int operator== ( const UGUID & g )

Равенство. Указывает, равно ли значение UGUID значению исходного UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Исходный UGUID.

### Возвращаемое значение

**1**, если значение UGUID равно значению исходного UGUID; иначе 0.
## int operator!= ( const UGUID & g )

Неравенство. Указывает, не равно ли значение UGUID значению исходного UGUID.
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **g** - Исходный UGUID.

### Возвращаемое значение

**1**, если значение UGUID не равно значению исходного UGUID; иначе 0.
## const char * get ( )

Возвращает значение UGUID в виде строки.
### Возвращаемое значение

Строка.
## char & get ( int index )

Возвращает символ UGUID по индексу.
### Аргументы

- *int* **index** - Индекс символа

### Возвращаемое значение

Символ UGUID
## char get ( int index )

Константный доступ к массиву.
### Аргументы

- *int* **index** - Индекс элемента массива

### Возвращаемое значение

Элемент массива
## const unsigned char * getValue ( ) const

Возвращает указатель на внутренний буфер данных.
### Возвращаемое значение

Указатель на внутренний буфер данных.
## char & operator[] ( int index )

Доступ к массиву.
### Аргументы

- *int* **index** - Индекс элемента массива

### Возвращаемое значение

Элемент массива
## char operator[] ( int index )

Доступ к элементу по индексу.
### Аргументы

- *int* **index** - Индекс элемента массива

### Возвращаемое значение

Элемент массива
## const char * operator const char * ( )

Возвращает указатель на текущую строку.
### Возвращаемое значение

Указатель на текущую строку
## const void * operator const void * ( )

Возвращает указатель на текущую строку.
## GUIDString makeString ( ) const

Создаёт 40-символьную шестнадцатеричную строку, представляющую значение GUID.
### Возвращаемое значение

40-символьная шестнадцатеричная строка, представляющая значение GUID.
