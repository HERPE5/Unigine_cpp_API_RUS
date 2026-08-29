# Unigine::Checksum Class (CPP)

**Header:** #include <UnigineChecksum.h>


## Checksum Class

### Методы класса

---

## int CRC32 ( const void * data , int size , bool big_endian )

Вычисляет 32-битную контрольную сумму CRC.
### Аргументы

- *const void ** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

### Возвращаемое значение

32-битная контрольная сумма CRC.
## void MD5 ( unsigned int * value , const void * data , int size , bool big_endian )

Вычисляет 128-битную контрольную сумму MD5.
### Аргументы

- *unsigned int ** **value** - 128-битная контрольная сумма MD5 (массив из 4 элементов unsigned int).
- *const void ** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

## int MD5 ( const void * data , int size , bool big_endian )

Вычисляет 32-битную контрольную сумму MD5.
### Аргументы

- *const void ** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

### Возвращаемое значение

32-битная контрольная сумма MD5.
## unsigned long long MD5_64 ( const void* data , int size , bool big_endian )

Вычисляет 64-битную контрольную сумму MD5.
### Аргументы

- *const void** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

### Возвращаемое значение

64-битная контрольная сумма MD5.
## void SHA1 ( unsigned int * value , const void * data , int size , bool big_endian )

Вычисляет 160-битную контрольную сумму SHA1.
### Аргументы

- *unsigned int ** **value** - 160-битная контрольная сумма SHA1 (массив из 5 элементов unsigned int).
- *const void ** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

## int SHA1 ( const void * data , int size , bool big_endian )

Вычисляет 32-битную контрольную сумму SHA1.
### Аргументы

- *const void ** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

### Возвращаемое значение

32-битная контрольная сумма SHA1.
## void SHA256 ( unsigned int * value , const void * data , int size , bool big_endian )

Вычисляет 256-битную контрольную сумму SHA256.
### Аргументы

- *unsigned int ** **value** - 256-битная контрольная сумма SHA256 (массив из 8 элементов unsigned int).
- *const void ** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *bool* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

## bool SHA256 ( const void * data , int size , int big_endian )

Вычисляет 32-битную контрольную сумму SHA256.
### Аргументы

- *const void ** **data** - Указатель на входные данные.
- *int* **size** - Размер входных данных, в байтах.
- *int* **big_endian** - Флаг порядка байтов. true, если используется порядок big-endian; false, если используется порядок little-endian.

### Возвращаемое значение

32-битная контрольная сумма SHA256.
