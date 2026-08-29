# Unigine.ImageConverter Class (CPP)

**Header:** #include <UnigineImage.h>


Этот класс используется для задания параметров преобразования, необходимых для изображения при [import](../../../editor2/assets_workflow/texture_import.md).


## ImageConverter Class

### Перечисления

## MIPMAPS_MODE

| Name | Description |
|---|---|
| **MIPMAPS_MODE_DISABLE** = 0 | Мипмапы не генерируются. |
| **MIPMAPS_MODE_POINT** = 1 | При генерации мипмапов используется метод точечной фильтрации. |
| **MIPMAPS_MODE_LINEAR** = 2 | При генерации мипмапов используется метод линейной фильтрации. |
| **MIPMAPS_MODE_BLUR** = 3 | При генерации мипмапов применяется размытие. |
| **MIPMAPS_MODE_SHARPEN** = 4 | При генерации мипмапов применяется повышение резкости. |
| **MIPMAPS_MODE_COMBINED** = 5 | Объединение загруженного 2D-изображения с наиболее детализированным изображением мипмапа. |
| **MIPMAPS_MODE_GGX** = 6 | Генерация мипмапов для кубических изображений ([IMAGE_CUBE](../../../api/library/common/class.image_cpp.md#IMAGE_CUBE) или [IMAGE_CUBE_ARRAY](../../../api/library/common/class.image_cpp.md#IMAGE_CUBE_ARRAY)) с использованием модели микрофасетов GGX BRDF. |

## RESOLUTION_MODE

| Name | Description |
|---|---|
| **RESOLUTION_MODE_AUTO** = 0 | Разрешение задаётся конвертером в зависимости от формата изображения (например, 2D-изображение преобразуется в 2D-массив / 3D-изображение). |
| **RESOLUTION_MODE_ORIGINAL** = 1 | Разрешение исходного изображения. |
| **RESOLUTION_MODE_MANUAL** = 2 | Разрешение, заданное вручную в конвертере. |

## COMPRESSION_QUALITY

| Name | Description |
|---|---|
| **COMPRESSION_QUALITY_LOW** = 0 | Низкое качество сжатия. |
| **COMPRESSION_QUALITY_HIGH** = 1 | Высокое качество сжатия. |

## RESIZE_FILTER

| Name | Description |
|---|---|
| **RESIZE_FILTER_POINT** = 0 | Метод точечной фильтрации, используемый для изменения размера. |
| **RESIZE_FILTER_LINEAR** = 1 | Метод линейной фильтрации, используемый для изменения размера. |
| **RESIZE_FILTER_MIN** = 2 | Минимизирующий метод фильтрации, используемый для изменения размера. |

## RANGE_MODE

| Name | Description |
|---|---|
| **RANGE_MODE_DISABLE** = 0 | Значения изображения не нормализуются. |
| **RANGE_MODE_NORMALIZE** = 1 | Значения во всех каналах изображения нормализуются в совокупности к значениям от 0 до 1 (т.е. общая яркость изображения). Рекомендуется использовать для цветов. |
| **RANGE_MODE_NORMALIZE_PER_CHANNEL** = 2 | Нормализация к значениям от 0 до 1 выполняется отдельно для каждого канала изображения. |
| **RANGE_MODE_MANUAL** = 3 | Выполняется нормализация к вручную заданным значениям. |

### Методы класса

## void setType ( int type )

Задаёт новый числовой код типа изображения.
### Аргументы

- *int* **type** - Числовой код типа изображения: 0 для 2D-изображения, 1 для 3D-изображения, 2 для кубического изображения, 3 для 2D-массива. См. [Unigine::Image:: IMAGE_* enumeration](../../../api/library/common/class.image_cpp.md#IMAGE_2D).

## int getType () const

Возвращает текущий числовой код типа изображения.
### Возвращаемое значение

Текущий числовой код типа изображения: 0 для 2D-изображения, 1 для 3D-изображения, 2 для кубического изображения, 3 для 2D-массива. См. [Unigine::Image:: IMAGE_* enumeration](../../../api/library/common/class.image_cpp.md#IMAGE_2D).
## void setFormat ( int format )

Задаёт новый числовой код формата изображения.
### Аргументы

- *int* **format** - Числовой код формата изображения. См. переменные [FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1).

## int getFormat () const

Возвращает текущий числовой код формата изображения.
### Возвращаемое значение

Текущий числовой код формата изображения. См. переменные [FORMAT_*](../../../api/library/common/class.image_cpp.md#FORMAT_ATI1).
## void setResolutionMode ( ImageConverter::RESOLUTION_MODE mode )

Задаёт новый режим разрешения, используемый для изображения.
### Аргументы

- *[ImageConverter::RESOLUTION_MODE](../../../api/library/common/class.imageconverter_cpp.md#RESOLUTION_MODE)* **mode** - Режим разрешения, используемый для изображения. Одно из значений *[RESOLUTION_MODE](#RESOLUTION_MODE_AUTO)*.

## ImageConverter::RESOLUTION_MODE getResolutionMode () const

Возвращает текущий режим разрешения, используемый для изображения.
### Возвращаемое значение

Текущий режим разрешения, используемый для изображения. Одно из значений *[RESOLUTION_MODE](#RESOLUTION_MODE_AUTO)*.
## void setResizeFilter ( ImageConverter::RESIZE_FILTER filter )

Задаёт новый фильтр изменения размера, используемый для изображения.
### Аргументы

- *[ImageConverter::RESIZE_FILTER](../../../api/library/common/class.imageconverter_cpp.md#RESIZE_FILTER)* **filter** - Фильтр изменения размера, используемый для изображения. Одно из значений *[RESIZE_FILTER](#RESIZE_FILTER_POINT)*.

## ImageConverter::RESIZE_FILTER getResizeFilter () const

Возвращает текущий фильтр изменения размера, используемый для изображения.
### Возвращаемое значение

Текущий фильтр изменения размера, используемый для изображения. Одно из значений *[RESIZE_FILTER](#RESIZE_FILTER_POINT)*.
## void setWidth ( int width )

Задаёт новую ширину изображения, в пикселях.
### Аргументы

- *int* **width** - Ширина изображения, в пикселях.

## int getWidth () const

Возвращает текущую ширину изображения, в пикселях.
### Возвращаемое значение

Текущая ширина изображения, в пикселях.
## void setHeight ( int height )

Задаёт новую высоту изображения, в пикселях.
### Аргументы

- *int* **height** - Высота изображения, в пикселях.

## int getHeight () const

Возвращает текущую высоту изображения, в пикселях.
### Возвращаемое значение

Текущая высота изображения, в пикселях.
## void setDepth ( int depth )

Задаёт новую глубину изображения, в пикселях.
### Аргументы

- *int* **depth** - Глубина изображения, в пикселях.

## int getDepth () const

Возвращает текущую глубину изображения, в пикселях.
### Возвращаемое значение

Текущая глубина изображения, в пикселях.
## void setFileCompression ( Image::FILE_COMPRESSION compression )

Задаёт новый тип сжатия файла изображения.
### Аргументы

- *[Image::FILE_COMPRESSION](../../../api/library/common/class.image_cpp.md#FILE_COMPRESSION)* **compression** - Тип сжатия файла, используемый для изображения. Одно из значений *[FILE_COMPRESSION_*](../../../api/library/common/class.image_cpp.md#FILE_COMPRESSION_LZ4_HIGH)*.

## Image::FILE_COMPRESSION getFileCompression () const

Возвращает текущий тип сжатия файла изображения.
### Возвращаемое значение

Текущий тип сжатия файла, используемый для изображения. Одно из значений *[FILE_COMPRESSION_*](../../../api/library/common/class.image_cpp.md#FILE_COMPRESSION_LZ4_HIGH)*.
## void setCompressionQuality ( ImageConverter::COMPRESSION_QUALITY quality )

Задаёт новое качество сжатия файла изображения.
### Аргументы

- *[ImageConverter::COMPRESSION_QUALITY](../../../api/library/common/class.imageconverter_cpp.md#COMPRESSION_QUALITY)* **quality** - Качество сжатия, используемое для изображения. Одно из значений *[COMPRESSION_QUALITY_*](#COMPRESSION_QUALITY_LOW)*.

## ImageConverter::COMPRESSION_QUALITY getCompressionQuality () const

Возвращает текущее качество сжатия файла изображения.
### Возвращаемое значение

Текущее качество сжатия, используемое для изображения. Одно из значений *[COMPRESSION_QUALITY_*](#COMPRESSION_QUALITY_LOW)*.
## void setGPUCompression ( bool gpucompression )

Задаёт новое значение, определяющее, используется ли сжатие на GPU при преобразовании изображения.
### Аргументы

- *bool* **gpucompression** - **true**, чтобы включить сжатие изображения на GPU; **false** - чтобы отключить его.

## bool isGPUCompression () const

Возвращает текущее значение, определяющее, используется ли сжатие на GPU при преобразовании изображения.
### Возвращаемое значение

**true**, если сжатие изображения на GPU включено; иначе **false**.
## void setMipmapsMode ( ImageConverter::MIPMAPS_MODE mode )

Задаёт новый тип фильтрации для мипмапов изображения.
### Аргументы

- *[ImageConverter::MIPMAPS_MODE](../../../api/library/common/class.imageconverter_cpp.md#MIPMAPS_MODE)* **mode** - Используемый режим мипмапов. Одно из значений *[MIPMAPS_MODE_*](#MIPMAPS_MODE_DISABLE)*.

## ImageConverter::MIPMAPS_MODE getMipmapsMode () const

Возвращает текущий тип фильтрации для мипмапов изображения.
### Возвращаемое значение

Текущий используемый режим мипмапов. Одно из значений *[MIPMAPS_MODE_*](#MIPMAPS_MODE_DISABLE)*.
## void setMipmapsGamma ( float gamma )

Задаёт новое значение гамма-коррекции, используемое для мипмапов.
### Аргументы

- *float* **gamma** - Значение гамма-коррекции, используемое для мипмапов.

## float getMipmapsGamma () const

Возвращает текущее значение гамма-коррекции, используемое для мипмапов.
### Возвращаемое значение

Текущее значение гамма-коррекции, используемое для мипмапов.
## void setMipmapsFilterRadius ( float radius )

Задаёт новый радиус, используемый для фильтрации мипмапов.
### Аргументы

- *float* **radius** - Значение радиуса фильтра.

## float getMipmapsFilterRadius () const

Возвращает текущий радиус, используемый для фильтрации мипмапов.
### Возвращаемое значение

Текущее значение радиуса фильтра.
## void setMipmapsFilterIntensity ( float intensity )

Задаёт новое значение интенсивности фильтра, используемое для мипмапов.
### Аргументы

- *float* **intensity** - Значение интенсивности фильтра, используемое для мипмапов.

## float getMipmapsFilterIntensity () const

Возвращает текущее значение интенсивности фильтра, используемое для мипмапов.
### Возвращаемое значение

Текущее значение интенсивности фильтра, используемое для мипмапов.
## void setMipmapsSharpOnlyLightness ( bool lightness )

Задаёт новое значение, определяющее, применяется ли резкость только к значению светлоты HSL мипмапа.
### Аргументы

- *bool* **lightness** - true, чтобы регулировать резкость только значения светлоты, **false**, чтобы повышать резкость всех значений HSL.

## bool isMipmapsSharpOnlyLightness () const

Возвращает текущее значение, определяющее, применяется ли резкость только к значению светлоты HSL мипмапа.
### Возвращаемое значение

true, чтобы регулировать резкость только значения светлоты, **false**, чтобы повышать резкость всех значений HSL.
## void setGGXMipmapsQuality ( Image::GGX_MIPMAPS_QUALITY quality )

Задаёт новое качество для мипмапов, генерируемых для кубических изображений с использованием модели микрофасетов GGX BRDF. Значение применяется, когда [mipmaps mode is set](#setMipmapsMode_int_void) в [GGX](#MIPMAPS_MODE_GGX).
### Аргументы

- *[Image::GGX_MIPMAPS_QUALITY](../../../api/library/common/class.image_cpp.md#GGX_MIPMAPS_QUALITY)* **quality** - Качество мипмапов GGX для кубического изображения. Одно из значений **[Image::GGX_MIPMAPS_QUALITY](../../../api/library/common/class.image_cpp.md#GGX_MIPMAPS_QUALITY)**.

## Image::GGX_MIPMAPS_QUALITY getGGXMipmapsQuality () const

Возвращает текущее качество для мипмапов, генерируемых для кубических изображений с использованием модели микрофасетов GGX BRDF. Значение применяется, когда [mipmaps mode is set](#setMipmapsMode_int_void) в [GGX](#MIPMAPS_MODE_GGX).
### Возвращаемое значение

Текущее качество мипмапов GGX для кубического изображения. Одно из значений **[Image::GGX_MIPMAPS_QUALITY](../../../api/library/common/class.image_cpp.md#GGX_MIPMAPS_QUALITY)**.
## void setRangeMode ( ImageConverter::RANGE_MODE mode )

Задаёт новый режим диапазона, применяемый при преобразовании изображения.
### Аргументы

- *[ImageConverter::RANGE_MODE](../../../api/library/common/class.imageconverter_cpp.md#RANGE_MODE)* **mode** - Режим диапазона, применяемый при преобразовании изображения. Одно из значений *[RANGE_MODE_*](#RANGE_MODE_DISABLE)*.

## ImageConverter::RANGE_MODE getRangeMode () const

Возвращает текущий режим диапазона, применяемый при преобразовании изображения.
### Возвращаемое значение

Текущий режим диапазона, применяемый при преобразовании изображения. Одно из значений *[RANGE_MODE_*](#RANGE_MODE_DISABLE)*.
## void setFlipX ( bool x )

Задаёт новое значение, определяющее, будет ли изображение отражено по горизонтали.
### Аргументы

- *bool* **x** - **true**, чтобы включить горизонтальное отражение изображения; **false** - чтобы отключить его.

## bool isFlipX () const

Возвращает текущее значение, определяющее, будет ли изображение отражено по горизонтали.
### Возвращаемое значение

**true**, если горизонтальное отражение изображения включено; иначе **false**.
## void setFlipY ( bool y )

Задаёт новое значение, определяющее, будет ли изображение отражено по вертикали.
### Аргументы

- *bool* **y** - **true**, чтобы включить вертикальное отражение изображения; **false** - чтобы отключить его.

## bool isFlipY () const

Возвращает текущее значение, определяющее, будет ли изображение отражено по вертикали.
### Возвращаемое значение

**true**, если вертикальное отражение изображения включено; иначе **false**.
## void setBlur ( int blur )

Задаёт новое значение размытия в пикселях.
### Аргументы

- *int* **blur** - Значение размытия в пикселях.

## int getBlur () const

Возвращает текущее значение размытия в пикселях.
### Возвращаемое значение

Текущее значение размытия в пикселях.
## void setRotate ( int rotate )

Задаёт новый угол поворота изображения.
### Аргументы

- *int* **rotate** - Угол поворота, по часовой стрелке.

## int getRotate () const

Возвращает текущий угол поворота изображения.
### Возвращаемое значение

Текущий угол поворота, по часовой стрелке.
---

## ImageConverter ( )

Конструктор по умолчанию. Создаётся пустой экземпляр с параметрами по умолчанию.
## ImageConverter ( const Ptr < ImageConverter > & imageconverter )

Конструктор. Создаёт конвертер изображений путём копирования указанного исходного конвертера изображений.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ImageConverter](../../../api/library/common/class.imageconverter_cpp.md)> &* **imageconverter** - Исходный конвертер изображений.

## void setRange ( int channel , const Math:: dvec4 & value )

Задаёт диапазон, применяемый при преобразовании изображения.
> **Notice:** Диапазон итогового изображения будет ограничен, если заданные значения диапазона превышают максимальные значения формата преобразования изображения.


### Аргументы

- *int* **channel** - Номер канала для инвертирования, в диапазоне от 0 до общего количества каналов.
- *const  Math::[dvec4](../../../api/library/math/class.dvec4_cpp.md) &* **value** - Значения диапазона: координаты x и y значения задают исходный диапазон, z и w задают диапазон, в который будет преобразовано изображение.

## Math:: dvec4 getRange ( int channel ) const

Возвращает диапазон, применяемый при преобразовании изображения.
### Аргументы

- *int* **channel** - Номер канала для инвертирования, в диапазоне от 0 до общего количества каналов.

### Возвращаемое значение

Значения диапазона: координаты x и y значения задают исходный диапазон, z и w задают диапазон, в который будет преобразовано изображение.
## bool getInvertChannel ( int channel )

Возвращает значение, указывающее, нужно ли инвертировать канал.
### Аргументы

- *int* **channel** - Номер канала для инвертирования, в диапазоне от 0 до общего количества каналов.

### Возвращаемое значение

**true**, если канал нужно инвертировать; иначе **false**.
## void setInvertChannel ( int channel , bool value )

Инвертирует значения, хранящиеся в указанном канале. Каналы изображений форматов half (*FORMAT_R16F* до *FORMAT_RGBA16F*) и float (*FORMAT_R32F* до *FORMAT_RGBA32F*) нельзя инвертировать.
### Аргументы

- *int* **channel** - Номер канала для инвертирования, в диапазоне от 0 до общего количества каналов.
- *bool* **value** - **true**, если канал нужно инвертировать; иначе **false**.

## void reset ( )

Устанавливает конвертер в значения по умолчанию.
## void copy ( Ptr < ImageConverter > & converter ) const

Копирует данные из указанного исходного конвертера.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[ImageConverter](../../../api/library/common/class.imageconverter_cpp.md)> &* **converter** - Исходный конвертер.

## Ptr < ImageConverter > clone ( ) const

Создаёт клон указанного исходного конвертера.
### Возвращаемое значение

Клонируемый конвертер.
## bool load ( const char * path )

Загружает настройки конвертера изображений с диска по указанному пути.
### Аргументы

- *const char ** **path** - Путь к файлу с настройками конвертера изображений.

### Возвращаемое значение

**true**, если настройки конвертера изображений успешно загружены; иначе **false**.
## void load ( const Ptr < Json > & json )

Загружает объект `.json` с настройками конвертера изображений.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Json](../../../api/library/common/class.json_cpp.md)> &* **json** - Объект с настройками конвертера изображений.

## bool save ( const char * path ) const

Сохраняет настройки конвертера изображений на диск в указанное место.
### Аргументы

- *const char ** **path** - Путь к файлу для хранения настроек конвертера изображений.

### Возвращаемое значение

**true**, если настройки конвертера изображений успешно сохранены; иначе **false**.
## void save ( const Ptr < Json > & json ) const

Сохраняет настройки конвертера изображений в указанный объект `.json`.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Json](../../../api/library/common/class.json_cpp.md)> &* **json** - Объект с настройками конвертера изображений.

## void updateParameters ( const Ptr < Image > & image )

Проверяет параметры конвертера изображений для указанного изображения. Этот метод позволяет проверить итоговые параметры перед преобразованием изображения.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Изображение для преобразования.

## bool runCPU ( Ptr < Image > & image )

Запускает конвертер изображений на CPU.
### Аргументы

- *[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Изображение для преобразования.

### Возвращаемое значение

true, если изображение успешно преобразовано; иначе false.
## bool run ( CallbackBase1 < Ptr < Image >> * on_converted , const Ptr < Image > & image )

Запускает конвертер изображений.
### Аргументы

- *[CallbackBase1](../../../api/library/common/callbacks/class.callbackbase1_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)>> ** **on_converted** - Callback, вызываемый после преобразования изображения.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Изображение для преобразования.

### Возвращаемое значение

true, если изображение успешно преобразовано; иначе false.
## bool adaptForSaving ( const Ptr < Image > & image , const char * extension )

Пытается адаптировать конвертер для сохранения указанного изображения с использованием одного из [supported file extensions](../../../api/library/common/class.image_cpp.md#intro).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Изображение для сохранения.
- *const char ** **extension** - Целевое расширение файла.

### Возвращаемое значение

true, если изображение допустимо, и подходящие формат и тип могли быть определены и установлены для сохранения; иначе false.
