# Unigine.BakeLighting Class (CPP)

**Header:** #include <UnigineRender.h>

> **Notice:** This class is a singleton.


Этот класс позволяет [bake lighting](../../../editor2/lighting/gi/bake_lighting/index.md).


> **Warning:** **Обратная совместимость для этого класса не гарантируется!** Хотя он доступен в публичном API, он в основном предназначен для внутреннего использования (внутри UnigineEditor). Используя его, вы делаете это на свой страх и риск.


## BakeLighting Class

### Перечисления

## LIGHTMAP_QUALITY

Пресет качества запекания освещения.
| Имя | Описание |
|---|---|
| **LIGHTMAP_QUALITY_DRAFT** = 0 | Черновое качество запекания. Обеспечивает наивысшую итеративность при самом низком качестве сэмплирования и количестве лучей. |
| **LIGHTMAP_QUALITY_LOW** = 1 | Низкое качество запекания. Обеспечивает низкое качество сэмплирования и количество лучей света. |
| **LIGHTMAP_QUALITY_MEDIUM** = 2 | Среднее качество запекания. Соответствует стабильному уровню качества, подходящему для большинства случаев. |
| **LIGHTMAP_QUALITY_HIGH** = 3 | Высокое качество запекания. Соответствует высокому качеству сэмплирования и количеству симулируемых лучей света, предназначенному для релизного продакшена. |
| **LIGHTMAP_QUALITY_ULTRA** = 4 | Максимальное качество запекания. Может быть полезно для устранения даже небольших несоответствий. Предназначено для релизного продакшена. |

### Методы класса

---

## void bake ( const Vector < Ptr < LightVoxelProbe > > & voxel_lights , const Vector < Ptr < LightEnvironmentProbe > > & env_lights , const Vector < Ptr < Light > > & shadow_lights , const Vector < Ptr < ObjectMeshStatic > > & objects , const Vector < int > & surfaces )

Запускает процесс запекания освещения для всех воксельных и environment проб, запекания теней для источников света в статическом режиме освещения и запекания лайтмапов для поверхностей объектов Mesh Static в заданном списке.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../api/library/common/class.ptr_cpp.md)<[LightVoxelProbe](../../../api/library/lights/class.lightvoxelprobe_cpp.md)> > &* **voxel_lights** - Список воксельных проб, для которых должен быть выполнен процесс запекания освещения. Порядок добавления узлов для запекания не важен.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../api/library/common/class.ptr_cpp.md)<[LightEnvironmentProbe](../../../api/library/lights/class.lightenvironmentprobe_cpp.md)> > &* **env_lights** - Список environment проб, для которых должен быть выполнен процесс запекания освещения. Порядок добавления узлов для запекания не важен.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Light](../../../api/library/lights/class.light_cpp.md)> > &* **shadow_lights** - Список источников света в статическом режиме освещения, для которых должен быть выполнен процесс запекания теней. Порядок добавления источников света для запекания не важен.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< [Ptr](../../../api/library/common/class.ptr_cpp.md)<[ObjectMeshStatic](../../../api/library/objects/class.objectmeshstatic_cpp.md)> > &* **objects** - Список объектов Mesh Static, для которых должен быть выполнен процесс запекания лайтмапов.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)< int > &* **surfaces** - Список поверхностей объектов Mesh Static **objects**, для которых должен быть выполнен процесс запекания лайтмапов. > **Notice:** Количество добавленных для запекания **objects** и **surfaces** должно совпадать.

## void bakeAll ( bool voxel_probes = true , bool env_probes = true , bool shadow = true , bool lightmap = true )

Запускает процесс запекания освещения для всех включённых воксельных и environment проб, запекания теней для включённых источников света в статическом режиме освещения и запекания лайтмапов для включённых поверхностей объектов Mesh Static в сцене.
### Аргументы

- *bool* **voxel_probes** - true включает запекание освещения для воксельных проб; иначе false.
- *bool* **env_probes** - true включает запекание освещения для environment проб; иначе false.
- *bool* **shadow** - true включает запекание теней для источников света в статическом режиме освещения; иначе false.
- *bool* **lightmap** - true включает запекание лайтмапов для поверхностей объектов Mesh Static; иначе false.

## bool isBaking ( ) const

Возвращает значение, указывающее, выполняется ли процесс запекания в данный момент.
### Возвращаемое значение

true, если освещение запекается; иначе - false.
## int getCurrentBounce ( ) const

Возвращает отскок, вычисляемый в данный момент.
> **Notice:** Если процесс запекания не выполняется в данный момент, возвращается 1.


### Возвращаемое значение

Номер отскока.
## int getBounces ( ) const

***Консоль*:**`bake_lighting_bounces`Возвращает количество всех отскоков.
### Возвращаемое значение

Количество отскоков.
## int getProgress ( ) const

Возвращает общий прогресс запекания освещения.
> **Notice:** Если процесс запекания не выполняется в данный момент, возвращается 0.


### Возвращаемое значение

Общий прогресс запекания, в процентах.
## int getProgressBounce ( ) const

Возвращает значение, показывающее прогресс вычисления текущего отскока.
### Возвращаемое значение

Прогресс вычисления отскока, в процентах.
## float getVoxelSizeMultiplier ( ) const

***Консоль*:**`bake_lighting_voxel_size_multiplier`Возвращает значение параметра множителя размера вокселя. По умолчанию равно 1.0f.
### Возвращаемое значение

Множитель размера вокселя.
## void setBounces ( int bounces )

Задаёт количество отскоков.
### Аргументы

- *int* **bounces** - Количество отскоков в диапазоне [1, 32]. Значение по умолчанию - 1.

## int getProgressLight ( ) const

Возвращает прогресс запекания освещения для текущей [LightVoxelProbe](../../../api/library/lights/class.lightvoxelprobe_cpp.md) в данный момент.
### Возвращаемое значение

Прогресс LightVoxelProbe, в процентах.
## float getTimer ( ) const

Возвращает время, прошедшее с начала процесса запекания.
### Возвращаемое значение

Прошедшее время, в секундах.
## void setVoxelSizeMultiplier ( float multiplier )

***Консоль*:**`bake_lighting_voxel_size_multiplier`Задаёт значение параметра множителя размера вокселя.
### Аргументы

- *float* **multiplier** - Множитель размера вокселя в диапазоне [0.0f, 8.0f]. Значение по умолчанию - 1.

## void stop ( bool save_results = false )

***Консоль*:**`bake_lighting_stop`Прерывает процесс запекания освещения, если он выполняется.
### Аргументы

- *bool* **save_results** - true сохраняет полученный результат; false восстанавливает предыдущее содержимое.

## Ptr < Light > getCurrentLight ( ) const

Возвращает экземпляр [LightVoxelProbe](../../../api/library/lights/class.lightvoxelprobe_cpp.md), вычисляемый в данный момент.
### Возвращаемое значение

Текущая LightVoxelProbe.
## void addReadOnlyTexture ( const UGUID & guid )

Добавляет текстуру только для чтения с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID добавляемой текстуры только для чтения.

## void removeReadOnlyTexture ( const UGUID & guid )

Удаляет текстуру только для чтения с указанным [GUID](../../../api/library/filesystem/class.uguid_cpp.md).
### Аргументы

- *const [UGUID](../../../api/library/filesystem/class.uguid_cpp.md) &* **guid** - GUID удаляемой текстуры только для чтения.

## void setSamplesPerFrame ( int frame )

***Консоль*:**`bake_lighting_samples_per_frame`Задаёт количество вокселей для воксельных проб и сэмплов для environment проб, источников света и поверхностей, вычисляемых и визуализируемых за один кадр.
### Аргументы

- *int* **frame** - Количество сэмплов за кадр в диапазоне [1, 500]. Значение по умолчанию - 1. > **Notice:** Высокие значения приводят к более долгому отклику пользовательского интерфейса.

## int getSamplesPerFrame ( ) const

Возвращает количество вокселей для воксельных проб и сэмплов для environment проб, источников света и поверхностей, вычисляемых и визуализируемых за один кадр.
### Возвращаемое значение

Количество сэмплов.
## void setLightmapQuality ( BakeLighting::LIGHTMAP_QUALITY quality )

***Консоль*:**`bake_lightmap_quality`Задаёт глобальное качество запекания для лайтмапов.
### Аргументы

- *[BakeLighting::LIGHTMAP_QUALITY](../../../api/library/lights/class.bakelighting_cpp.md#LIGHTMAP_QUALITY)* **quality** - Одно из значений [LIGHTMAP_QUALITY](#LIGHTMAP_QUALITY).

## BakeLighting::LIGHTMAP_QUALITY getLightmapQuality ( ) const

***Консоль*:**`bake_lightmap_quality`Возвращает текущее глобальное качество запекания для лайтмапов.
### Возвращаемое значение

Пресет [LIGHTMAP_QUALITY](#LIGHTMAP_QUALITY).
## void setLightmapViewportMask ( int mask )

***Консоль*:**`bake_lightmap_viewport_mask`Задаёт [viewport mask](../../../editor2/lighting/gi/bake_lighting/index.md#lightmaps) для lightmapper. Чтобы источник света или поверхность вносили вклад в статическое GI, их маски viewport должны совпадать с [viewport mask](../../../principles/bit_masking/index.md#viewport) запекания.
### Аргументы

- *int* **mask** - Маска viewport (целое число, каждый бит которого используется для представления маски).

## int getLightmapViewportMask ( ) const

Возвращает текущую [viewport mask](../../../editor2/lighting/gi/bake_lighting/index.md#lightmaps), заданную для lightmapper.
### Возвращаемое значение

Маска viewport (целое число, каждый бит которого используется для представления маски).
## void setLightmapZFar ( float zfar )

***Консоль*:**`bake_lightmap_zfar`Задаёт дальнюю границу отсечения для лучей света, используемую при запекании лайтмапов.
### Аргументы

- *float* **zfar** - Дальняя граница отсечения.

## float getLightmapZFar ( ) const

***Консоль*:**`bake_lightmap_zfar`Возвращает дальнюю границу отсечения для лучей света.
### Возвращаемое значение

Дальняя граница отсечения.
## void setCacheDir ( const char * dir )

Задаёт путь к директории, хранящей временные кэш-текстуры во время процесса запекания лайтмапов. По умолчанию задана папка проекта `bin/unigine_bake_lighting_cache`.
> **Notice:** Рекомендуется указывать путь к несуществующей папке во избежание потери файлов.

### Аргументы

- *const char ** **dir** - Абсолютный путь или относительный путь к папке `bin`.

## const char * getCacheDir ( ) const

Возвращает текущий путь, заданный для директории, хранящей временные кэш-текстуры во время процесса запекания лайтмапов. По умолчанию задана папка проекта `bin/unigine_bake_lighting_cache`.
### Возвращаемое значение

Путь к папке кэша.
## Ptr < Object > getCurrentObject ( ) const

Возвращает объект, обрабатываемый в данный момент при запекании лайтмапов.
### Возвращаемое значение

Указатель на объект во время запекания лайтмапов; иначе nullptr.
## int getCurrentSurface ( ) const

Возвращает индекс поверхности, обрабатываемой в данный момент при запекании лайтмапов.
### Возвращаемое значение

Индекс поверхности во время запекания лайтмапов; иначе -1.
