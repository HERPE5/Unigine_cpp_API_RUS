# Unigine.Texture Class (CPP)

**Header:** #include <UnigineTextures.h>


Интерфейс для работы с текстурами.


Текстуры хранятся на GPU.


Unigine предоставляет различные режимы фильтрации семплов текстур:


1. Точечная фильтрация (Point filtering)
2. Линейная фильтрация (Linear filtering)
3. Билинейная фильтрация (Bilinear filtering)
4. Трилинейная фильтрация (Trilinear filtering)
5. Анизотропная фильтрация (Anisotropic filtering)


Они упорядочены от наихудшего визуального качества к наилучшему, то есть от наименее затратной по производительности к наиболее затратной.


Текстура имеет два набора флагов: флаги сэмплера и флаги формата.


#### Флаги сэмплера


Флаги сэмплера могут динамически изменяться во время выполнения для [user](../../../content/materials/index.md#user_materials) материалов.


- SAMPLER_WRAP_CLAMP_X
- SAMPLER_WRAP_CLAMP_Y
- SAMPLER_WRAP_CLAMP_Z
- SAMPLER_WRAP_BORDER_X
- SAMPLER_WRAP_BORDER_Y
- SAMPLER_WRAP_BORDER_Z
- SAMPLER_WRAP_BORDER_ONE
- SAMPLER_WRAP_BORDER
- SAMPLER_WRAP_MASK
- SAMPLER_FILTER_POINT
- SAMPLER_FILTER_LINEAR
- SAMPLER_FILTER_BILINEAR
- SAMPLER_FILTER_TRILINEAR
- SAMPLER_FILTER_MASK
- SAMPLER_ANISOTROPY_1
- SAMPLER_ANISOTROPY_2
- SAMPLER_ANISOTROPY_4
- SAMPLER_ANISOTROPY_8
- SAMPLER_ANISOTROPY_16
- SAMPLER_ANISOTROPY_MASK
- SAMPLER_DEFAULT_FLAGS
- SAMPLER_FLAGS


#### Флаги формата


Изменения флагов формата требуют переинициализации текстуры, чтобы вступить в силу. Флаги формата доступны только для чтения (редактируются только для [base](../../../content/materials/index.md#base_materials) материалов).


- FORMAT_SRGB
- FORMAT_SIGNED
- FORMAT_INTEGER
- FORMAT_MIPMAPS
- FORMAT_MASK
- FORMAT_MULTISAMPLE_2
- FORMAT_MULTISAMPLE_4
- FORMAT_MULTISAMPLE_8
- FORMAT_MULTISAMPLE_16
- FORMAT_MULTISAMPLE_MASK
- FORMAT_USAGE_UNORDERED_ACCESS
- FORMAT_USAGE_RENDER
- FORMAT_USAGE_IMMUTABLE
- FORMAT_USAGE_DYNAMIC
- FORMAT_USAGE_STAGING
- FORMAT_USAGE_SHARED
- FORMAT_USAGE_MASK
- FORMAT_FLAGS


#### Хранение данных (уровни, слои, грани)


Хранилище текстуры содержит одно или несколько изображений определённых размеров. Каждый тип текстуры имеет специфическое расположение изображений в своём хранилище. Текстуры могут иметь **мип-карты (mipmaps)** - уменьшенные версии одного и того же изображения, используемые для помощи в сэмплировании и фильтрации текстур. Каждый уровень мип-карты имеет отдельный набор изображений.


Поскольку текстура хранит несколько изображений, важно иметь возможность идентифицировать конкретное изображение в текстуре. Каждое изображение в текстуре можно однозначно идентифицировать по следующим числам, в зависимости от типа текстуры:


- Для текстур, которые могут иметь мип-карты, - **уровень мип-карты**, содержащий изображение.
- Для массивов текстур (Array Textures) - **слой массива**, содержащий изображение.
- Для кубических текстур (Cubemap Textures) - **грань** внутри этого слоя массива и уровня мип-карты. > **Notice:** Для массивов кубических текстур (Cubemap Array Textures) слой и грань объединены в layer-faces.


Таким образом, текстуру можно представить как трёхмерный массив изображений. Первый индекс - это *уровень мип-карты*, второй - *слой массива*, а третий - *грань кубической карты*. Другой способ представить это - текстура имеет некоторое количество уровней мип-карты. Каждая мип-карта может иметь некоторое количество слоёв массива. И каждый слой массива имеет некоторое количество граней. **Таким образом, на каждое изображение текстуры можно однозначно сослаться по индексам грани, слоя и уровня.**


## Texture Class

### Методы класса

## int getAllFlags () const

Возвращает текущие флаги текстуры ([format](#format_flags) и [sampler](#sampler_flags)).
### Возвращаемое значение

Текущие флаги текстуры, комбинация переменных *[FORMAT_*](#FORMAT_SRGB)* и *[SAMPLER_*](#SAMPLER_WRAP_CLAMP_X)*.
## int getFormatFlags () const

Возвращает текущие [format_flags](#format_flags) текстуры.
### Возвращаемое значение

Текущие флаги формата, комбинация переменных *[FORMAT_*](#FORMAT_SRGB)*.
## void setSamplerFlags ( int flags )

Задаёт новые [sampler_flags](#sampler_flags) текстуры.
### Аргументы

- *int* **flags** - Флаги сэмплера, комбинация переменных *[SAMPLER_*](#SAMPLER_WRAP_CLAMP_X)*.

## int getSamplerFlags () const

Возвращает текущие [sampler_flags](#sampler_flags) текстуры.
### Возвращаемое значение

Текущие флаги сэмплера, комбинация переменных *[SAMPLER_*](#SAMPLER_WRAP_CLAMP_X)*.
## int getNumFaces () const

Возвращает текущее количество [faces](#anatomy) в текстуре.
### Возвращаемое значение

Текущее количество [faces](#anatomy) в текстуре.
## int getNumLayers () const

Возвращает текущее количество [layers](#anatomy) в текстуре.
### Возвращаемое значение

Текущее количество [layers](#anatomy) в текстуре.
## int getNumMipmaps () const

Возвращает текущее количество [mipmap](#anatomy) текстуры.
### Возвращаемое значение

Текущее количество [mipmap](#anatomy) текстуры.
## int getNumChannels () const

Возвращает текущее количество каналов.
### Возвращаемое значение

Текущее количество каналов.
## bool isDepthFormat () const

Возвращает текущее значение, указывающее, является ли текстура текстурой глубины.
### Возвращаемое значение

**true**, если текстура является текстурой глубины; иначе **false**.
## bool isColorFormat () const

Возвращает текущее значение, указывающее, является ли текстура текстурой цвета.
### Возвращаемое значение

**true**, если текстура является текстурой цвета; иначе **false**.
## bool isCompressedFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в сжатом формате (DXT1, DXT3, DXT5, ATI1, ATI2, ZLC1 или ZLC2).
### Возвращаемое значение

**true**, если текстура хранится в сжатом формате (DXT1, DXT3, DXT5, ATI1, ATI2, ZLC1 или ZLC2); иначе **false**.
## bool isCombinedFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в комбинированном формате (RGB565, RGBA4, RGB5A1 или RGB10A2).
### Возвращаемое значение

**true**, если текстура хранится в комбинированном формате (RGB565, RGBA4, RGB5A1 или RGB10A2); иначе **false**.
## bool isIntegerFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в целочисленном формате (unsigned char, unsigned short или unsigned int).
### Возвращаемое значение

**true**, если текстура хранится в целочисленном формате (unsigned char, unsigned short или unsigned int); иначе **false**.
## bool isFloatFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в формате с плавающей точкой (R32F, RG32F или RGBA32F).
### Возвращаемое значение

**true**, если текстура хранится в формате с плавающей точкой (R32F, RG32F или RGBA32F); иначе **false**.
## bool isHalfFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в формате half-float (R16F, RG16F или RGBA16F).
### Возвращаемое значение

**true**, если текстура хранится в формате half-float (R16F, RG16F или RGBA16F); иначе **false**.
## bool isUShortFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в формате unsigned short (R16, RG16 или RGBA16).
### Возвращаемое значение

**true**, если текстура хранится в формате unsigned short (R16, RG16 или RGBA16); иначе **false**.
## bool isUCharFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в формате unsigned char (R8, RG8, RGBA8, DXT1, DXT3, DXT5, ATI1 или ATI2).
### Возвращаемое значение

**true**, если текстура хранится в формате unsigned char (R8, RG8, RGBA8, DXT1, DXT3, DXT5, ATI1 или ATI2); иначе **false**.
## bool isUIntFormat () const

Возвращает текущее значение, указывающее, хранится ли текстура в формате unsigned integer (R32U, RG32U или RGBA32U).
### Возвращаемое значение

**true**, если текстура хранится в формате unsigned integer (R32U, RG32U или RGBA32U); иначе **false**.
## bool isRawFormat () const

Возвращает текущее значение, указывающее, является ли текстура несжатой (хранится в формате R8, RG8, RGBA8, R16, RG16, RGBA16, R16F, RG16F, RGBA16F, R32F, RG32F, RGBA32F, RGB565, RGBA4, RGB5A1, RGB10A2, D16, D24S8, D32F или D32FS8).
### Возвращаемое значение

**true**, если текстура несжатая (хранится в формате R8, RG8, RGBA8, R16, RG16, RGBA16, R16F, RG16F, RGBA16F, R32F, RG32F, RGBA32F, RGB565, RGBA4, RGB5A1, RGB10A2, D16, D24S8, D32F или D32FS8); иначе **false**.
## int getImageFormat () const

Возвращает текущий формат изображения, соответствующий текущему формату текстуры.
### Возвращаемое значение

Текущий идентификатор формата изображения (см. переменные [FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1)) или 0, если указанный формат текстуры неизвестен.
## const char * getFormatName () const

Возвращает текущее имя формата текстуры.
### Возвращаемое значение

Текущее имя формата текстуры.
## int getFormat () const

Возвращает текущий формат текстуры.
### Возвращаемое значение

Текущий формат текстуры.
## bool isArrayType () const

Возвращает текущее значение, указывающее, является ли текстура массивом текстур.
### Возвращаемое значение

**true**, если тип текстуры - массив; иначе **false**.
## bool isCubeType () const

Возвращает текущее значение, указывающее, является ли текстура кубической текстурой.
### Возвращаемое значение

**true**, если тип текстуры - кубическая текстура; иначе **false**.
## bool is3DType () const

Возвращает текущее значение, указывающее, является ли текстура 3D-текстурой.
### Возвращаемое значение

**true**, если тип текстуры - 3D-текстура; иначе **false**.
## bool is2DType () const

Возвращает текущее значение, указывающее, является ли текстура 2D-текстурой.
### Возвращаемое значение

**true**, если тип текстуры - 2D-текстура; иначе **false**.
## const char * getTypeName () const

Возвращает текущее имя типа текстуры.
### Возвращаемое значение

Текущее имя типа текстуры.
## int getType () const

Возвращает текущий тип текстуры.
### Возвращаемое значение

Текущий тип текстуры.
## void setDebugName ( const char * name )

Задаёт новое понятное имя для GPU-отладки (RenderDoc, NVIDIA Nsight). Оно может помочь определить, какой указатель интерфейса объекта вызвал утечку. Утечки памяти отображаются [debug software layer](https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-layers#debug-layer) путём вывода списка указателей интерфейсов объектов вместе с их понятными именами.
### Аргументы

- *const char ** **name** - Понятное имя текстуры, используемое для GPU-отладки (RenderDoc, NVIDIA Nsight).

## const char * getDebugName () const

Возвращает текущее понятное имя для GPU-отладки (RenderDoc, NVIDIA Nsight). Оно может помочь определить, какой указатель интерфейса объекта вызвал утечку. Утечки памяти отображаются [debug software layer](https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-layers#debug-layer) путём вывода списка указателей интерфейсов объектов вместе с их понятными именами.
### Возвращаемое значение

Текущее понятное имя текстуры, используемое для GPU-отладки (RenderDoc, NVIDIA Nsight).
## void setOwnership ( bool ownership )

Задаёт новый флаг владения, определяющий, управляется ли текстура автоматически движком. Если флаг установлен, движок заботится о текстуре так, как будто она была создана движком, в противном случае пользователь должен управлять текстурой вручную (уничтожать объект, выполнять всю необходимую очистку памяти).
### Аргументы

- *bool* **ownership** - **true**, чтобы включить автоматическое управление текстурой и временем жизни используемой памяти движком; **false** - чтобы отключить это.

## bool isOwnership () const

Возвращает текущий флаг владения, определяющий, управляется ли текстура автоматически движком. Если флаг установлен, движок заботится о текстуре так, как будто она была создана движком, в противном случае пользователь должен управлять текстурой вручную (уничтожать объект, выполнять всю необходимую очистку памяти).
### Возвращаемое значение

**true**, если автоматическое управление текстурой и временем жизни используемой памяти движком включено; иначе **false**.
## bool isUsageShared () const

Возвращает текущее значение, указывающее, включён ли для текстуры флаг [FORMAT_USAGE_SHARED](#FORMAT_USAGE_SHARED).
### Возвращаемое значение

**true**, если флаг [FORMAT_USAGE_SHARED](#FORMAT_USAGE_SHARED) для текстуры включён; иначе **false**.
## bool isUsageStaging () const

Возвращает текущее значение, указывающее, включён ли для текстуры флаг [FORMAT_USAGE_STAGING](#FORMAT_USAGE_STAGING).
### Возвращаемое значение

**true**, если флаг [FORMAT_USAGE_STAGING](#FORMAT_USAGE_STAGING) для текстуры включён; иначе **false**.
## bool isUsageDynamic () const

Возвращает текущее значение, указывающее, включён ли для текстуры флаг [FORMAT_USAGE_DYNAMIC](#FORMAT_USAGE_DYNAMIC).
### Возвращаемое значение

**true**, если флаг [FORMAT_USAGE_DYNAMIC](#FORMAT_USAGE_DYNAMIC) для текстуры включён; иначе **false**.
## bool isUsageImmutable () const

Возвращает текущее значение, указывающее, включён ли для текстуры флаг [FORMAT_USAGE_IMMUTABLE](#FORMAT_USAGE_IMMUTABLE).
### Возвращаемое значение

**true**, если флаг [FORMAT_USAGE_IMMUTABLE](#FORMAT_USAGE_IMMUTABLE) для текстуры включён; иначе **false**.
## bool isUsageRender () const

Возвращает текущее значение, указывающее, включён ли для текстуры флаг [FORMAT_USAGE_RENDER](#FORMAT_USAGE_RENDER).
### Возвращаемое значение

**true**, если флаг [FORMAT_USAGE_RENDER](#FORMAT_USAGE_RENDER) для текстуры включён; иначе **false**.
## bool isUsageUnorderedAccess () const

Возвращает текущее значение, указывающее, включён ли для текстуры флаг [FORMAT_USAGE_UNORDERED_ACCESS](#FORMAT_USAGE_UNORDERED_ACCESS).
### Возвращаемое значение

**true**, если флаг [FORMAT_USAGE_UNORDERED_ACCESS](#FORMAT_USAGE_UNORDERED_ACCESS) для текстуры включён; иначе **false**.
## size_t getVideoMemoryUsage () const

Возвращает текущий объём памяти, занимаемой текстурой.
### Возвращаемое значение

Текущий размер текстуры, в байтах.
---

## bool isAnisotropy ( ) const

Проверяет анизотропию текстуры.
### Возвращаемое значение

true, если фильтр текстуры - анизотропный, иначе false.
## bool isValid ( )

Возвращает значение, указывающее, действительна ли текстура (проверка на null-указатель).
### Возвращаемое значение

true, если текстура действительна; иначе false.
## int getDepth ( int level = 0 ) const

Возвращает глубину для заданного mip-уровня текстуры.
### Аргументы

- *int* **level** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](#getNumMipmaps_int).

### Возвращаемое значение

Глубина mip-уровня текстуры.
## int getHeight ( int level = 0 ) const

Возвращает высоту для указанного mip-уровня текстуры.
### Аргументы

- *int* **level** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](#getNumMipmaps_int).

### Возвращаемое значение

Высота mip-уровня текстуры.
## bool setImage ( const Ptr < Image > & image )

Задаёт данные текстуры, используя данные указанного исходного изображения.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Исходное изображение, используемое для задания данных текстуры.

### Возвращаемое значение

true, если данные успешно заданы; иначе false.
## bool setImage2D ( const Ptr < Image > & image , int offset_x , int offset_y , int texture_format = -1 )

Задаёт данные текстуры, используя данные указанного 2D-изображения или 2D-массива изображений.
> **Notice:** Должны быть выполнены следующие условия:
> - Тип текстуры и изображения должны быть либо оба **2D**, либо оба **2D_ARRAY**.
> - Разрешение текстуры должно быть больше или равно разрешению изображения.
> - Количество mip-уровней изображения и текстуры должно совпадать (то же самое для количества слоёв 2D-массивов).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Исходное изображение, используемое для задания данных текстуры.
- *int* **offset_x** - Смещение по оси X (в пикселях), начиная с которого берутся данные указанного изображения. Должно выполняться следующее условие: **offset_x < texture_width - image_width**.
- *int* **offset_y** - Смещение по оси Y (в пикселях), начиная с которого берутся данные указанного изображения. Должно выполняться следующее условие: **offset_y < texture_height - image_height**.
- *int* **texture_format** - Идентификатор формата текстуры (см. переменные [FORMAT_*](#FORMAT_ATI1)) или -1 - автоопределение.

### Возвращаемое значение

true, если данные успешно заданы; иначе false.
## bool setImageLayer ( const Ptr < Image > & image , int layer , int texture_format = -1 )

Задаёт данные указанного слоя массива 2D-текстур, используя данные указанного 2D-изображения.
> **Notice:** Должны быть выполнены следующие условия:
> - Текстура и изображение должны иметь одинаковое разрешение.
> - Количество mip-уровней изображения и текстуры должно совпадать (то же самое для количества слоёв 2D-массивов).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Исходное изображение, используемое для задания данных слоя массива 2D-текстур.
- *int* **layer** - Номер слоя массива 2D-текстур, для которого задаются данные.
- *int* **texture_format** - Идентификатор формата текстуры (см. переменные [FORMAT_*](#FORMAT_ATI1)) или -1 - автоопределение.

### Возвращаемое значение

true, если данные успешно заданы; иначе false.
## int getMultisample ( ) const

Возвращает количество сэмплов мультисэмплинга.
### Возвращаемое значение

Количество сэмплов мультисэмплинга.
## int getWidth ( int level = 0 ) const

Возвращает ширину для указанного mip-уровня текстуры.
### Аргументы

- *int* **level** - Номер mip-уровня в диапазоне от **0** до [total number of mipmaps](#getNumMipmaps_int).

### Возвращаемое значение

Ширина mip-уровня текстуры.
## void clear ( )

Очищает текстуру.
## bool copy2D ( int dest_x = 0 , int dest_y = 0 , int src_x = 0 , int src_y = 0 , int w = -1 , int h = -1 )

Копирует 2D-текстуру.
### Аргументы

- *int* **dest_x** - Смещение исходной текстуры по оси X.
- *int* **dest_y** - Смещение исходной текстуры по оси Y.
- *int* **src_x** - Смещение целевой текстуры по оси X.
- *int* **src_y** - Смещение целевой текстуры по оси Y.
- *int* **w** - Ширина целевой текстуры.
- *int* **h** - Высота целевой текстуры.

### Возвращаемое значение

true, если текстура скопирована; иначе false.
## bool copyCube ( int face , int dest_x = 0 , int dest_y = 0 , int src_x = 0 , int src_y = 0 , int w = -1 , int h = -1 )

Копирует кубическую текстуру.
### Аргументы

- *int* **face** - Грань куба.
- *int* **dest_x** - Смещение исходной текстуры по оси X.
- *int* **dest_y** - Смещение исходной текстуры по оси Y.
- *int* **src_x** - Смещение целевой текстуры по оси X.
- *int* **src_y** - Смещение целевой текстуры по оси Y.
- *int* **w** - Ширина целевой текстуры.
- *int* **h** - Высота целевой текстуры.

### Возвращаемое значение

true, если текстура скопирована; иначе false.
## static Ptr < Texture > TexturePtr create ( )

Конструктор текстуры.
### Возвращаемое значение

Указатель на созданную текстуру.
## bool create ( const Ptr < Image > & image , int flags = SAMPLER_FILTER_LINEAR , int skip_mipmaps = 0 , int format = -1 )

Конструктор текстуры. Создаёт новую текстуру с указанными параметрами.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Указатель на изображение.
- *int* **flags** - Флаги текстуры.
- *int* **skip_mipmaps**
- *int* **format** - Формат текстуры.

### Возвращаемое значение

true, если текстура успешно создана; иначе false.
## bool create2D ( int width , int height , int format , int flags = SAMPLER_FILTER_LINEAR )

Создаёт 2D-текстуру.
### Аргументы

- *int* **width** - Ширина текстуры.
- *int* **height** - Высота текстуры.
- *int* **format** - Формат текстуры.
- *int* **flags** - Флаги текстуры.

### Возвращаемое значение

true, если текстура успешно создана; иначе false.
## bool create2DArray ( int width , int height , int num_layers , int format , int flags = SAMPLER_FILTER_LINEAR )

Создаёт массив 2D-текстур.
### Аргументы

- *int* **width** - Ширина текстуры.
- *int* **height** - Высота текстуры.
- *int* **num_layers** - Слои текстуры.
- *int* **format** - Формат текстуры.
- *int* **flags** - Флаги текстуры.

### Возвращаемое значение

true, если массив 2D-текстур создан; иначе false.
## bool create3D ( int width , int height , int depth , int format , int flags = SAMPLER_FILTER_LINEAR )

Создаёт 3D-текстуру.
### Аргументы

- *int* **width** - Ширина текстуры.
- *int* **height** - Высота текстуры.
- *int* **depth** - Глубина текстуры.
- *int* **format** - Формат текстуры.
- *int* **flags** - Флаги текстуры.

### Возвращаемое значение

true, если 3D-текстура создана; иначе false.
## bool createCube ( int width , int height , int format , int flags = SAMPLER_FILTER_LINEAR )

Создаёт кубическую текстуру.
### Аргументы

- *int* **width** - Ширина текстуры.
- *int* **height** - Высота текстуры.
- *int* **format** - Формат текстуры.
- *int* **flags** - Флаги текстуры.

### Возвращаемое значение

true, если кубическая текстура создана; иначе false.
## bool createCubeArray ( int width , int height , int num_layers , int format , int flags = SAMPLER_FILTER_LINEAR )

Создаёт массив кубических текстур.
### Аргументы

- *int* **width** - Ширина текстуры.
- *int* **height** - Высота текстуры.
- *int* **num_layers** - Слои текстуры.
- *int* **format** - Формат текстуры.
- *int* **flags** - Флаги текстуры.

### Возвращаемое значение

true, если массив кубических текстур создан; иначе false.
## bool createMipmaps ( )

Создаёт стек мип-карт.
### Возвращаемое значение

true, если стек мип-карт создан; иначе false.
## void destroy ( )

Уничтожает текстуру.
## bool load ( const char * name , int flags = SAMPLER_FILTER_LINEAR )

Загружает текстуру из файла.
### Аргументы

- *const char ** **name** - Имя файла.
- *int* **flags** - Флаги текстуры.

### Возвращаемое значение

true, если текстура загружена; иначе false.
## void render2D ( float x0 = -1.0f , float y0 = -1.0f , float x1 = 1.0f , float y1 = 1.0f )

Рендерит 2D-текстуру. Эта функция создаёт 4 вершины (2 полигона), используя 2 X-координаты и 2 Y-координаты, и отправляет их на рендеринг.
### Аргументы

- *float* **x0** - Первая X-координата.
- *float* **y0** - Первая Y-координата.
- *float* **x1** - Вторая X-координата.
- *float* **y1** - Вторая Y-координата.

## void render2DArray ( int layer , float x0 = -1.0f , float y0 = -1.0f , float x1 = 1.0f , float y1 = 1.0f )

Рендерит массив 2D-текстур. Эта функция создаёт 4 вершины (2 полигона) слоя текстуры, используя 2 X-координаты и 2 Y-координаты, и отправляет их на рендеринг.
### Аргументы

- *int* **layer** - Номер слоя.
- *float* **x0** - Первая X-координата.
- *float* **y0** - Первая Y-координата.
- *float* **x1** - Вторая X-координата.
- *float* **y1** - Вторая Y-координата.

## void render2DScreen ( float x0 = -1.0f , float y0 = -1.0f , float x1 = 1.0f , float y1 = 1.0f )

Рендерит текстуру 2D Screen. Эта функция создаёт 3 вершины (1 полигон) и отправляет текстуру на рендеринг внутри полигона, чтобы избежать артефактов на границе 2 полигонов при использовании сглаживания.
### Аргументы

- *float* **x0** - Первая X-координата.
- *float* **y0** - Первая Y-координата.
- *float* **x1** - Вторая X-координата.
- *float* **y1** - Вторая Y-координата.

## void renderCube ( int face , float x0 = -1.0f , float y0 = -1.0f , float x1 = 1.0f , float y1 = 1.0f )

Рендерит кубическую текстуру. Эта функция создаёт 4 вершины (2 полигона) заданной грани кубической текстуры, используя 2 X-координаты и 2 Y-координаты, и отправляет их на рендеринг.
### Аргументы

- *int* **face** - Грань куба.
- *float* **x0** - Первая X-координата.
- *float* **y0** - Первая Y-координата.
- *float* **x1** - Вторая X-координата.
- *float* **y1** - Вторая Y-координата.

## void renderCubeArray ( int face , int layer , float x0 = -1.0f , float y0 = -1.0f , float x1 = 1.0f , float y1 = 1.0f )

Рендерит массив кубических текстур. Эта функция создаёт 4 вершины (2 полигона) заданной грани слоя кубической текстуры, используя 2 X-координаты и 2 Y-координаты, и отправляет их на рендеринг.
### Аргументы

- *int* **face** - Грань куба.
- *int* **layer** - Номер слоя.
- *float* **x0** - Первая X-координата.
- *float* **y0** - Первая Y-координата.
- *float* **x1** - Вторая X-координата.
- *float* **y1** - Вторая Y-координата.

## int formatImageToTexture ( int image_format , int flags )

Возвращает формат текстуры, соответствующий указанному формату изображения.
### Аргументы

- *int* **image_format** - Идентификатор формата изображения (см. переменные [FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1)) или 0, если указанный формат текстуры неизвестен.
- *int* **flags** - Флаг unsigned-формата. 1, чтобы интерпретировать целочисленный формат изображения как unsigned, 0 - как signed.

### Возвращаемое значение

Идентификатор формата текстуры (см. переменные [FORMAT_*](#FORMAT_ATI1)) или 0, если указанный формат изображения неизвестен.
## int formatTextureToImage ( int texture_format )

Возвращает формат изображения, соответствующий указанному формату текстуры.
### Аргументы

- *int* **texture_format** - Идентификатор формата текстуры (см. переменные [FORMAT_*](#FORMAT_ATI1)).

### Возвращаемое значение

Идентификатор формата изображения (см. переменные [FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1)) или 0, если указанный формат текстуры неизвестен.
## int typeTextureToImage ( int texture_type )

Возвращает тип изображения, соответствующий указанному типу текстуры.
### Аргументы

- *int* **texture_type** - Идентификатор типа текстуры (см. переменные [TEXTURE_*](#TEXTURE_2D)).

### Возвращаемое значение

Идентификатор типа изображения (см. переменные [IMAGE_*](../../../api/library/common/class.image_cpp.md#IMAGE_2D)) или 0, если указанный тип текстуры неизвестен.
## void clearBuffer ( )

Очищает все уровни изображения текстуры (заполняет все её элементы нулевыми значениями).
## void clearBuffer ( const Math:: vec4 & color )

Очищает все уровни изображения текстуры (заполняет все её элементы указанными значениями цвета).
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Цвет, используемый для заполнения буфера.

## void swap ( const Ptr < Texture > & texture )

Меняет местами данные текущей текстуры с исходной текстурой.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **texture** - Исходная текстура.

## bool copy ( const Ptr < Texture > & src )

Копирует данные исходной текстуры в текстуру.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **src** - Исходная текстура.

### Возвращаемое значение

true, если данные исходной текстуры успешно скопированы; иначе false.
## size_t getVideoMemoryUsage ( int width , int height , int format , int num_mipmaps , int flags , int num_faces , int num_layers , int depth )

Возвращает объём памяти, занимаемой текстурой с указанными параметрами.
### Аргументы

- *int* **width** - Ширина текстуры, в пикселях.
- *int* **height** - Высота текстуры, в пикселях.
- *int* **format** - Формат текстуры.
- *int* **num_mipmaps** - Количество mip-уровней в текстуре.
- *int* **flags** - Флаги текстуры.
- *int* **num_faces** - Количество граней в текстуре.
- *int* **num_layers** - Количество слоёв в текстуре.
- *int* **depth** - Глубина текстуры.

### Возвращаемое значение

Размер текстуры, в байтах.
## bool copyRegion ( const Ptr < Texture > & src , const Math:: ivec3 & src_coords , int src_level , const Math:: ivec3 & dest_coords , int dest_level , int width , int height , int depth )

Копирует указанную область из исходной текстуры.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Texture](../../../api/library/rendering/class.texture_cpp.md)> &* **src** - Исходная текстура, из которой копируются данные.
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **src_coords** - Координаты в исходной текстуре, начиная с которых берутся данные области.
- *int* **src_level** - Номер mip-уровня исходной текстуры в диапазоне от **0** до [total number of mipmaps](#getNumMipmaps_int).
- *const  Math::[ivec3](../../../api/library/math/class.ivec3_cpp.md) &* **dest_coords** - Координаты в текстуре, начиная с которых вставляются данные из исходной текстуры.
- *int* **dest_level** - Номер целевого mip-уровня в диапазоне от **0** до [total number of mipmaps](#getNumMipmaps_int).
- *int* **width** - Ширина копируемой области, в пикселях.
- *int* **height** - Высота копируемой области, в пикселях.
- *int* **depth** - Глубина копируемой области, в пикселях.

### Возвращаемое значение

true, если указанная область успешно скопирована из источника в приёмник; иначе false.
## bool setBlob ( const Ptr < Blob > & blob ) const

Задаёт данные текстуры из указанного исходного blob.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Blob](../../../api/library/common/class.blob_cpp.md)> &* **blob** - Исходный blob, содержащий данные текстуры.

### Возвращаемое значение

true, если данные успешно заданы; иначе false.
## const char * getTypeName ( int type )

Возвращает имя типа текстуры по индексу его типа.
### Аргументы

- *int* **type** - Индекс типа текстуры.

### Возвращаемое значение

Имя типа текстуры.
## Ptr < ResourceExternalMemory > getResourceExternalMemory ( ) const

Возвращает указатель на ресурс в видеопамяти. Если для ресурса не включён флаг [FORMAT_USAGE_SHARED](#FORMAT_USAGE_SHARED), этот метод возвращает nullptr.
### Возвращаемое значение

Указатель на ресурс в видеопамяти. Если для ресурса не включён флаг [FORMAT_USAGE_SHARED](#FORMAT_USAGE_SHARED), этот метод возвращает nullptr.
