# Unigine.RenderTarget Class (CPP)

**Header:** #include <UnigineTextures.h>


Контейнер, в который рендерится изображение (абстракция [framebuffer](https://en.wikipedia.org/wiki/Framebuffer)).


## RenderTarget Class

### Методы класса

---

## static RenderTargetPtr create ( )

Конструктор. Создаёт новый рендер-таргет.
## void destroy ( )

Уничтожает рендер-таргет.
## void enable ( )

Включает рендер-таргет.
## void enableCompute ( )

Включает рендер-таргет с использованием вывода вычислительного шейдера.
## void disable ( )

Отключает рендер-таргет.
## void flush ( )

Выполняет flush рендер-таргета.
## Ptr < Texture > getColorTexture ( int slot ) const

Возвращает текстуру цвета по указанному слоту.
### Аргументы

- *int* **slot** - Слот текстуры.

### Возвращаемое значение

Текстура цвета, если она существует, иначе nullptr.
## void bindColorTexture ( int slot , const Ptr < Texture > & texture )

Привязывает все слои и грани (если поддерживается типом текстуры) текстуры на 0-м mip-уровне к указанному слоту в качестве рендер-таргета.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Текстура цвета для привязки.

## void bindColorTexture2D ( int slot , const Ptr < Texture > & texture , int mip = 0 )

Привязывает указанный слот 2D-текстуры на указанном mip-уровне к указанному слоту в качестве рендер-таргета.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - 2D-текстура цвета для привязки.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindColorTexture2DArray ( int slot , const Ptr < Texture > & texture , int layer = -1 , int mip = 0 )

Привязывает указанный слот и слой массива 2D-текстур на указанном mip-уровне к указанному слоту в качестве рендер-таргета.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Массив 2D-текстур цвета для привязки.
- *int* **layer** - Номер слоя массива 2D-текстур. При значении по умолчанию -1 привязываются все слои текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindColorTextureCube ( int slot , const Ptr < Texture > & texture , int face = -1 , int mip = 0 )

Привязывает указанный слот и грань кубической текстуры на указанном mip-уровне к указанному слоту в качестве рендер-таргета.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Кубическая текстура цвета для привязки.
- *int* **face** - Грань куба. При значении по умолчанию -1 привязываются все грани текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindColorTextureCubeArray ( int slot , const Ptr < Texture > & texture , int layer = -1 , int face = -1 , int mip = 0 )

Привязывает указанный слой и грань массива кубических текстур на указанном mip-уровне к указанному слоту в качестве рендер-таргета.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Массив кубических текстур цвета для привязки.
- *int* **layer** - Номер слоя массива кубических текстур. При значении по умолчанию -1 привязываются все слои текстуры на указанном mip-уровне.
- *int* **face** - Грань куба. При значении по умолчанию -1 привязываются все грани текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindColorTexture3D ( int slot , const Ptr < Texture > & texture , int depth = -1 , int mip = 0 )

Привязывает указанный слой глубины 3D-текстуры на указанном mip-уровне к указанному слоту в качестве рендер-таргета.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - 3D-текстура цвета для привязки.
- *int* **depth** - Слой глубины 3D-текстуры. При значении по умолчанию -1 привязываются все слои глубины текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void unbindColorTexture ( int slot )

Отвязывает текстуру рендер-таргета от указанного слота.
### Аргументы

- *int* **slot** - Слот текстуры.

## void unbindColorTextures ( )

Отвязывает все текстуры рендер-таргета от рендер-таргета.
## Ptr < Texture > getDepthTexture ( ) const

Возвращает текстуру глубины.
### Возвращаемое значение

Текстура глубины, если она существует, иначе nullptr.
## void bindDepthTexture ( const Ptr < Texture > & texture )

Привязывает все слои и грани (если поддерживается типом текстуры) текстуры на 0-м mip-уровне к указанному слоту в качестве таргета глубины.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Текстура глубины для привязки.

## void bindDepthTextureReadOnly ( const Ptr < Texture > & texture )

Привязывает текстуру глубины как таргет глубины только для чтения (например, для теста глубины), и одновременно позволяет использовать эту текстуру как ресурс шейдера внутри шейдера.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Текстура глубины для привязки.

## void bindDepthTexture2D ( const Ptr < Texture > & texture , int mip = 0 )

Привязывает 2D-текстуру глубины на указанном mip-уровне в качестве таргета глубины.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - 2D-текстура глубины для привязки.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindDepthTexture2DArray ( const Ptr < Texture > & texture , int layer = -1 , int mip = 0 )

Привязывает указанный слой текстуры глубины на указанном mip-уровне в качестве таргета глубины.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Массив 2D-текстур глубины для привязки.
- *int* **layer** - Номер слоя массива 2D-текстур глубины. При значении по умолчанию -1 привязываются все слои текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindDepthTextureCube ( const Ptr < Texture > & texture , int face = -1 , int mip = 0 )

Привязывает указанную грань кубической текстуры глубины на указанном mip-уровне в качестве таргета глубины.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Кубическая текстура глубины для привязки.
- *int* **face** - Грань куба. При значении по умолчанию -1 привязываются все грани текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindDepthTextureCubeArray ( const Ptr < Texture > & texture , int layer = -1 , int face = -1 , int mip = 0 )

Привязывает указанный слой и грань массива кубических текстур глубины на указанном mip-уровне в качестве таргета глубины.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Массив кубических текстур глубины для привязки.
- *int* **layer** - Номер слоя массива кубических текстур. При значении по умолчанию -1 привязываются все слои текстуры на указанном mip-уровне.
- *int* **face** - Грань куба. При значении по умолчанию -1 привязываются все грани текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void unbindDepthTexture ( )

Отвязывает текстуру глубины от таргета глубины.
## Ptr < Texture > getUnorderedAccessTexture ( int slot ) const

Возвращает текстуру unordered access по указанному слоту.
### Аргументы

- *int* **slot** - Слот текстуры.

### Возвращаемое значение

Текстура unordered access, если она существует, иначе nullptr.
## void bindUnorderedAccessTexture ( int slot , const Ptr < Texture > & texture , bool writeonly = false , bool atomic = false )

Привязывает все слои и грани (если поддерживается типом текстуры) текстуры на 0-м mip-уровне к указанному слоту для unordered access.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Текстура unordered access для привязки.
- *bool* **writeonly** - Флаг доступа. true, чтобы использовать текстуру только для записи, иначе false.
- *bool* **atomic** - true, чтобы привязать текстуру с форматом *GL_32UI*; иначе — false. Этот флаг следует устанавливать только для Vulkan.

## void bindUnorderedAccessTexture2D ( int slot , const Ptr < Texture > & texture , bool writeonly = false , bool atomic = false , int mip = 0 )

Привязывает 2D-текстуру на указанном mip-уровне к указанному слоту для unordered access.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - 2D-текстура unordered access для привязки.
- *bool* **writeonly** - Флаг доступа. true, чтобы использовать текстуру только для записи, иначе false.
- *bool* **atomic** - true, чтобы привязать текстуру с форматом *GL_32UI*; иначе — false. Этот флаг следует устанавливать только для Vulkan.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindUnorderedAccessTexture2DArray ( int slot , const Ptr < Texture > & texture , bool writeonly = false , bool atomic = false , int layer = -1 , int mip = 0 )

Привязывает указанный слой массива 2D-текстур на указанном mip-уровне к указанному слоту для unordered access.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Массив 2D-текстур unordered access для привязки.
- *bool* **writeonly** - Флаг доступа. true, чтобы использовать текстуру только для записи, иначе false.
- *bool* **atomic** - true, чтобы привязать текстуру с форматом *GL_32UI*; иначе — false. Этот флаг следует устанавливать только для Vulkan.
- *int* **layer** - Номер слоя массива 2D-текстур. При значении по умолчанию -1 привязываются все слои текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindUnorderedAccessTextureCube ( int slot , const Ptr < Texture > & texture , bool writeonly = false , bool atomic = false , int face = -1 , int mip = 0 )

Привязывает указанную грань кубической текстуры на указанном mip-уровне к указанному слоту для unordered access.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Кубическая текстура unordered access для привязки.
- *bool* **writeonly** - Флаг доступа. true, чтобы использовать текстуру только для записи, иначе false.
- *bool* **atomic** - true, чтобы привязать текстуру с форматом *GL_32UI*; иначе — false. Этот флаг следует устанавливать только для Vulkan.
- *int* **face** - Грань куба. При значении по умолчанию -1 привязываются все грани текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindUnorderedAccessTextureCubeArray ( int slot , const Ptr < Texture > & texture , bool writeonly = false , bool atomic = false , int layer = -1 , int face = -1 , int mip = 0 )

Привязывает указанный слой и грань кубической текстуры на указанном mip-уровне к указанному слоту для unordered access.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Массив кубических текстур unordered access для привязки.
- *bool* **writeonly** - Флаг доступа. true, чтобы использовать текстуру только для записи, иначе false.
- *bool* **atomic** - true, чтобы привязать текстуру с форматом *GL_32UI*; иначе — false. Этот флаг следует устанавливать только для Vulkan.
- *int* **layer** - Номер слоя массива кубических текстур.
- *int* **face** - Грань куба. При значении по умолчанию -1 привязываются все грани текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void bindUnorderedAccessTexture3D ( int slot , const Ptr < Texture > & texture , bool writeonly = false , bool atomic = false , int depth = -1 , int mip = 0 )

Привязывает указанный слой 3D-текстуры на указанном mip-уровне к указанному слоту для unordered access.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - 3D-текстура unordered access для привязки.
- *bool* **writeonly** - Флаг доступа. true, чтобы использовать текстуру только для записи, иначе false.
- *bool* **atomic** - true, чтобы привязать текстуру с форматом *GL_32UI*; иначе — false. Этот флаг следует устанавливать только для Vulkan.
- *int* **depth** - Слой глубины 3D-текстуры. При значении по умолчанию -1 привязываются все слои глубины текстуры на указанном mip-уровне.
- *int* **mip** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](../../../api/library/rendering/class.texture_cpp.md#getNumMipmaps_int).

## void unbindUnorderedAccessTexture ( int slot )

Отвязывает текстуру unordered access от указанного слота.
### Аргументы

- *int* **slot** - Слот текстуры.

## void unbindUnorderedAccessTextures ( )

Отвязывает все текстуры unordered access для ресурсов unordered access.
## Ptr < StructuredBuffer > getStructuredBuffer ( int slot ) const

Возвращает структурированный буфер по указанному слоту.
### Аргументы

- *int* **slot** - Слот текстуры.

### Возвращаемое значение

[Structured buffer](../../../api/library/rendering/class.structuredbuffer_cpp.md), если он существует, иначе nullptr.
## void bindStructuredBuffer ( int slot , const Ptr < StructuredBuffer > & buffer )

Привязывает структурированный буфер к устройству по указанному слоту.
### Аргументы

- *int* **slot** - Слот текстуры.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[StructuredBuffer](../../../api/library/rendering/class.structuredbuffer_cpp.md)> &* **buffer** - [Structured buffer](../../../api/library/rendering/class.structuredbuffer_cpp.md) для привязки.

## void unbindStructuredBuffer ( int slot )

Отвязывает структурированный буфер для ресурсов unordered access.
### Аргументы

- *int* **slot** - Слот текстуры.

## void unbindStructuredBuffers ( )

Отвязывает все структурированные буферы для ресурсов unordered access.
## bool isEnabled ( ) const

Возвращает значение, указывающее, включён ли рендер-таргет.
### Возвращаемое значение

true, если рендер-таргет включён, иначе false.
## bool isCompleted ( ) const

Возвращает значение, указывающее, завершён ли рендер-таргет.
### Возвращаемое значение

true, если рендер-таргет завершён, иначе false.
## void unbindAll ( )

Отвязывает все текстуры цвета, глубины и unordered access, а также структурированные буферы.
