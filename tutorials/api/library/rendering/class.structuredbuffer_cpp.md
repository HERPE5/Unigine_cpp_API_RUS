# Unigine.StructuredBuffer Class (CPP)

**Header:** #include <UnigineTextures.h>


StructuredBuffer - это буфер для структур: он представляет собой однородный массив структур.


Ресурс StructuredBuffer может быть задан [via the following flags](../../../api/library/rendering/class.structuredbuffer_cpp.md#USAGE_RENDER).


### См. также


- Пример на C++ **StructuredBuffer**, входящий в состав раздела Samples (*Samples -> C++ -> Render*) SDK Browser UNIGINE.


## StructuredBuffer Class

### Методы класса

## void setDebugName ( const char * name )

Задаёт новое понятное имя структурированного буфера, используемое для GPU-отладки (RenderDoc, NVIDIA Nsight). Оно может помочь определить, какой указатель интерфейса объекта вызвал утечку. Утечки памяти отображаются [debug software layer](https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-layers#debug-layer) путём вывода списка указателей интерфейсов объектов вместе с их понятными именами.
### Аргументы

- *const char ** **name** - Понятное отладочное имя.

## const char * getDebugName () const

Возвращает текущее понятное имя структурированного буфера, используемое для GPU-отладки (RenderDoc, NVIDIA Nsight). Оно может помочь определить, какой указатель интерфейса объекта вызвал утечку. Утечки памяти отображаются [debug software layer](https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-layers#debug-layer) путём вывода списка указателей интерфейсов объектов вместе с их понятными именами.
### Возвращаемое значение

Текущее понятное отладочное имя.
## int getNumElements () const

Возвращает текущее количество элементов в структурированном буфере.
### Возвращаемое значение

Текущее количество элементов в структурированном буфере.
## bool isUsageShared () const

Возвращает текущее значение, указывающее, включён ли для ресурса флаг [USAGE_SHARED](#USAGE_SHARED).
### Возвращаемое значение

**true**, если флаг [USAGE_SHARED](#USAGE_SHARED) включён; иначе **false**.
## bool isUsageStaging () const

Возвращает текущее значение, указывающее, включён ли для ресурса флаг [USAGE_STAGING](#USAGE_STAGING).
### Возвращаемое значение

**true**, если флаг [USAGE_STAGING](#USAGE_STAGING) включён; иначе **false**.
## bool isUsageImmutable () const

Возвращает текущее значение, указывающее, включён ли для ресурса флаг [USAGE_IMMUTABLE](#USAGE_IMMUTABLE).
### Возвращаемое значение

**true**, если флаг [USAGE_IMMUTABLE](#USAGE_IMMUTABLE) включён; иначе **false**.
## bool isUsageRender () const

Возвращает текущее значение, указывающее, включён ли для ресурса флаг [USAGE_RENDER](#USAGE_RENDER).
### Возвращаемое значение

**true**, если флаг [USAGE_RENDER](#USAGE_RENDER) включён; иначе **false**.
---

## static StructuredBufferPtr create ( )

Конструктор. Создаёт новый структурированный буфер.
```cpp
StructuredBufferPtr input_buffer = StructuredBuffer::create();
```


## void clear ( )

Очищает умный указатель.
## int create ( int flags , const void * data , unsigned int structure_size , unsigned int num_elements )

Создаёт экземпляр StructuredBuffer с указанными параметрами.
```cpp
#define NUMBERS_COUNT 4096 * 8192

// Input data structure
struct InputDataStructure {
	vec4 vector0;
	vec4 vector1;
};

// Source data
InputDataStructure *source_data = new InputDataStructure[NUMBERS_COUNT];

// Create immutable structure buffer (gpu_read-only) and store initial values
StructuredBufferPtr input_buffer = StructuredBuffer::create();
input_buffer->create(StructuredBuffer::IMMUTABLE, source_data, sizeof(InputDataStructure), NUMBERS_COUNT);

```


### Аргументы

- *int* **flags** - [StructuredBuffer flag](#USAGE_RENDER).
- *const void ** **data** - Указатель на исходные данные.
- *unsigned int* **structure_size** - Размер структурированного буфера.
- *unsigned int* **num_elements** - Количество элементов в структурированном буфере.

### Возвращаемое значение

**1**, если StructuredBuffer успешно создан; иначе **0**.
## int create ( int flags , unsigned int structure_size , unsigned int num_elements )

Создаёт экземпляр StructuredBuffer с указанными параметрами.
### Аргументы

- *int* **flags** - [StructuredBuffer flag](#USAGE_RENDER).
- *unsigned int* **structure_size** - Размер структурированного буфера.
- *unsigned int* **num_elements** - Количество элементов в структурированном буфере.

### Возвращаемое значение

**1**, если StructuredBuffer успешно создан; иначе **0**.
## void destroy ( )

Уничтожает умный указатель.
## void clearBuffer ( )

Очищает структурированный буфер.
## void copy ( const Ptr < StructuredBuffer > & src )

Копирует данные из указанного исходного структурированного буфера.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[StructuredBuffer](../../../api/library/rendering/class.structuredbuffer_cpp.md)> &* **src** - Исходный структурированный буфер для копирования данных.

## Ptr < ResourceExternalMemory > getResourceExternalMemory ( ) const

Возвращает указатель на ресурс в видеопамяти. Если для ресурса не включён флаг [USAGE_SHARED](#USAGE_SHARED), этот метод возвращает nullptr.
### Возвращаемое значение

Указатель на ресурс в видеопамяти. Если для ресурса не включён флаг [USAGE_SHARED](#USAGE_SHARED), этот метод возвращает nullptr.
## size_t getVideoMemoryUsage ( )

Возвращает текущий объём видеопамяти, используемой структурированным буфером.
### Возвращаемое значение

Объём видеопамяти, используемой структурированным буфером, в байтах.
