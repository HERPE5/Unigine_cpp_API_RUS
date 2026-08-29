# Unigine.VRMixedReality Class (CPP)

**Header:** #include <UnigineVRMixedReality.h>

> **Notice:** Этот класс является синглтоном.


Класс используется для управления смешанной реальностью на совместимых шлемах виртуальной реальности (HMD), поддерживающих смешанную реальность и работающих на бэкендах **Varjo** или **OpenXR**.


При использовании бэкенда **Varjo** доступны все возможности этого класса. Под **OpenXR** поддержка смешанной реальности ограничена. Используйте методы *[hasFeature...()](../../...md#hasFeatureAlphaBlend_int)*, чтобы проверить, какие возможности и соответствующие методы этого класса поддерживаются конкретно для вашего устройства и конфигурации бэкенда.


## VRMixedReality Class

### Перечисления

## BLEND_MASKING_MODE

| Name | Description |
|---|---|
| **BLEND_MASKING_MODE_BEGIN** = 0 | Первый элемент, используемый для итерации. |
| **BLEND_MASKING_MODE_DISABLED** = 0 | Режим маскирования отключён. |
| **BLEND_MASKING_MODE_RESTRICT_VIDEO_TO_MASK** = 1 | Показывать сквозное видеоизображение (VST) в маске. Можно использовать с хромакеем. |
| **BLEND_MASKING_MODE_RESTRICT_VR_TO_MASK** = 2 | Показывать VR в маске. Можно использовать с хромакеем. |
| **BLEND_MASKING_MODE_RESTRICT_VR_TO_CHROMAKEY_REDUCED_BY_MASK** = 3 | Показывать VR в маске, а хромакей - в остальных местах. Требует хромакей. |
| **BLEND_MASKING_MODE_END** = 3 | Последний элемент, используемый для итерации. |

## CAMERA_PROPERTY_MODE

| Name | Description |
|---|---|
| **CAMERA_PROPERTY_MODE_DISABLED** = 0 | Настройка свойств камеры отключена. |
| **CAMERA_PROPERTY_MODE_AUTO** = 1 | Автоматическая настройка свойств камеры. |
| **CAMERA_PROPERTY_MODE_MANUAL** = 2 | Ручная настройка свойств камеры. В этом режиме можно вручную задавать желаемые значения свойств (коррекция времени экспозиции, коррекция баланса белого, ISO) с помощью соответствующих методов. |

## CAMERA_EXPOSURE_TIME

| Name | Description |
|---|---|
| **CAMERA_EXPOSURE_TIME_UNKNOWN** = 0 | Время экспозиции камеры не указано. |
| **CAMERA_EXPOSURE_TIME_BEGIN** = 1 | Первый элемент, используемый для итерации. |
| **CAMERA_EXPOSURE_TIME_VALUE_91_MS** = 1 | Значение времени экспозиции камеры равно 91 К. |
| **CAMERA_EXPOSURE_TIME_VALUE_125_MS** = 2 | Значение времени экспозиции камеры равно 125 К. |
| **CAMERA_EXPOSURE_TIME_VALUE_250_MS** = 3 | Значение времени экспозиции камеры равно 250 К. |
| **CAMERA_EXPOSURE_TIME_VALUE_500_MS** = 4 | Значение времени экспозиции камеры равно 500 К. |
| **CAMERA_EXPOSURE_TIME_VALUE_1000_MS** = 5 | Значение времени экспозиции камеры равно 1000 К. |
| **CAMERA_EXPOSURE_TIME_VALUE_2000_MS** = 6 | Значение времени экспозиции камеры равно 2000 К. |
| **CAMERA_EXPOSURE_TIME_VALUE_4000_MS** = 7 | Значение времени экспозиции камеры равно 4000 К. |
| **CAMERA_EXPOSURE_TIME_VALUE_8000_MS** = 8 | Значение времени экспозиции камеры равно 8000 К. |
| **CAMERA_EXPOSURE_TIME_END** = 8 | Последний элемент, используемый для итерации. |

## CAMERA_WHITE_BALANCE

| Name | Description |
|---|---|
| **CAMERA_WHITE_BALANCE_UNKNOWN** = 0 | Значение баланса белого камеры не указано. |
| **CAMERA_WHITE_BALANCE_BEGIN** = 1 | Первый элемент, используемый для итерации. |
| **CAMERA_WHITE_BALANCE_VALUE_2000_K** = 1 | Значение баланса белого камеры равно 2000 К. |
| **CAMERA_WHITE_BALANCE_VALUE_3000_K** = 2 | Значение баланса белого камеры равно 3000 К. |
| **CAMERA_WHITE_BALANCE_VALUE_3500_K** = 3 | Значение баланса белого камеры равно 3500 К. |
| **CAMERA_WHITE_BALANCE_VALUE_4200_K** = 4 | Значение баланса белого камеры равно 4200 К. |
| **CAMERA_WHITE_BALANCE_VALUE_5000_K** = 5 | Значение баланса белого камеры равно 5000 К. |
| **CAMERA_WHITE_BALANCE_VALUE_5400_K** = 6 | Значение баланса белого камеры равно 5400 К. |
| **CAMERA_WHITE_BALANCE_VALUE_6500_K** = 7 | Значение баланса белого камеры равно 6500 К. |
| **CAMERA_WHITE_BALANCE_VALUE_8000_K** = 8 | Значение баланса белого камеры равно 8000 К. |
| **CAMERA_WHITE_BALANCE_VALUE_12000_K** = 9 | Значение баланса белого камеры равно 12000 К. |
| **CAMERA_WHITE_BALANCE_END** = 9 | Последний элемент, используемый для итерации. |

## CAMERA_ISO

| Name | Description |
|---|---|
| **CAMERA_ISO_UNKNOWN** = 0 | Значение ISO камеры не указано. |
| **CAMERA_ISO_BEGIN** = 1 | Первый элемент, используемый для итерации. |
| **CAMERA_ISO_GAIN_100** = 1 | Значение ISO камеры равно 100. |
| **CAMERA_ISO_GAIN_200** = 2 | Значение ISO камеры равно 200. |
| **CAMERA_ISO_GAIN_400** = 3 | Значение ISO камеры равно 400. |
| **CAMERA_ISO_GAIN_800** = 4 | Значение ISO камеры равно 800. |
| **CAMERA_ISO_GAIN_1600** = 5 | Значение ISO камеры равно 1600. |
| **CAMERA_ISO_GAIN_3200** = 6 | Значение ISO камеры равно 3200. |
| **CAMERA_ISO_GAIN_6400** = 7 | Значение ISO камеры равно 6400. |
| **CAMERA_ISO_END** = 7 | Последний элемент, используемый для итерации. |

## CAMERA_FLICKER_COMPENSATION

| Name | Description |
|---|---|
| **CAMERA_FLICKER_COMPENSATION_UNKNOWN** = 0 | Значение компенсации мерцания камеры не указано. |
| **CAMERA_FLICKER_COMPENSATION_BEGIN** = 1 | Первый элемент, используемый для итерации. |
| **CAMERA_FLICKER_COMPENSATION_FREQ_50_HZ** = 1 | Значение компенсации мерцания камеры равно 50 Гц. |
| **CAMERA_FLICKER_COMPENSATION_FREQ_60_HZ** = 2 | Значение компенсации мерцания камеры равно 60 Гц. |
| **CAMERA_FLICKER_COMPENSATION_END** = 2 | Последний элемент, используемый для итерации. |

## CUBEMAP_MODE

| Name | Description |
|---|---|
| **CUBEMAP_MODE_BEGIN** = 0 | Первый элемент, используемый для итерации. |
| **CUBEMAP_MODE_DISABLED** = 0 | Потоковая передача кубической текстуры от AR-камер отключена. |
| **CUBEMAP_MODE_ENVIRONMENT_OVERLAP** = 1 | Текстура окружения замещает небо. |
| **CUBEMAP_MODE_ENVIRONMENT_PRESET_0** = 2 | Первый [environment preset](../../../editor2/settings/render_settings/environment/index.md#presets) определяет способ задания AR-текстуры для окружения. |
| **CUBEMAP_MODE_ENVIRONMENT_PRESET_1** = 3 | Второй [environment preset](../../../editor2/settings/render_settings/environment/index.md#presets) определяет способ задания AR-текстуры для окружения. |
| **CUBEMAP_MODE_ENVIRONMENT_PRESET_2** = 4 | Третий [environment preset](../../../editor2/settings/render_settings/environment/index.md#presets) определяет способ задания AR-текстуры для окружения. |
| **CUBEMAP_MODE_END** = 4 | Последний элемент, используемый для итерации. |

## OVERRIDE_COLOR_CORRECTION_MODE

| Name | Description |
|---|---|
| **OVERRIDE_COLOR_CORRECTION_MODE_BEGIN** = 0 | Первый элемент, используемый для итерации. |
| **OVERRIDE_COLOR_CORRECTION_MODE_DISABLED** = 0 | Цветокоррекция отключена. |
| **OVERRIDE_COLOR_CORRECTION_MODE_EXPOSURE** = 1 | Коррекция экспозиции для потока с AR-камер. |
| **OVERRIDE_COLOR_CORRECTION_MODE_EXPOSURE_WHITE_BALANCE** = 2 | Коррекция экспозиции и баланса белого для потока. |
| **OVERRIDE_COLOR_CORRECTION_MODE_END** = 2 | Последний элемент, используемый для итерации. |

### Методы класса

## bool isAvailable () const

Возвращает текущее значение, указывающее, доступна ли смешанная реальность на активном VR-устройстве и поддерживается ли она во время выполнения.
### Возвращаемое значение

**true**, если смешанная реальность доступна; иначе **false**.
## void setChromaKeyEnabled ( bool enabled = 0 )

***Консоль*:**`vr_mixed_reality_chroma_key_enabled`Задаёт новое значение, указывающее, включён ли хромакей. [VST capturing](#isVideoEnabled_int) с камер HMD должен быть включён.
### Аргументы

- *bool* **enabled** - **true**, чтобы включить хромакей; **false** - чтобы отключить его. Значение по умолчанию - **false**.

## bool isChromaKeyEnabled () const

***Консоль*:**`vr_mixed_reality_chroma_key_enabled`Возвращает текущее значение, указывающее, включён ли хромакей. [VST capturing](#isVideoEnabled_int) с камер HMD должен быть включён.
### Возвращаемое значение

**true**, если хромакей включён; иначе **false**. Значение по умолчанию - **false**.
## void setDepthTestEnabled ( bool enabled = 0 )

***Консоль*:**`vr_mixed_reality_depth_test_enabled`Задаёт новое значение, указывающее, включена ли передача буфера глубины. [VST capturing](#isVideoEnabled_int) с камер HMD должен быть включён.
### Аргументы

- *bool* **enabled** - **true**, чтобы включить тест глубины; **false** - чтобы отключить его. Значение по умолчанию - **false**.

## bool isDepthTestEnabled () const

***Консоль*:**`vr_mixed_reality_depth_test_enabled`Возвращает текущее значение, указывающее, включена ли передача буфера глубины. [VST capturing](#isVideoEnabled_int) с камер HMD должен быть включён.
### Возвращаемое значение

**true**, если тест глубины включён; иначе **false**. Значение по умолчанию - **false**.
## void setAlphaBlendEnabled ( bool enabled = 0 )

***Консоль*:**`vr_mixed_reality_alpha_blend_enabled`Задаёт новое значение, указывающее, включено ли альфа-смешение. Эта опция используется для смешения изображений VR и AR с помощью альфа-канала. [VST capturing](#isVideoEnabled_int) с камер HMD должен быть включён, а [screen precision](../../../api/library/rendering/class.render_cpp.md#isScreenPrecision_int) должна быть равна 1.
### Аргументы

- *bool* **enabled** - **true**, чтобы включить альфа-смешение; **false** - чтобы отключить его. Значение по умолчанию - **false**.

## bool isAlphaBlendEnabled () const

***Консоль*:**`vr_mixed_reality_alpha_blend_enabled`Возвращает текущее значение, указывающее, включено ли альфа-смешение. Эта опция используется для смешения изображений VR и AR с помощью альфа-канала. [VST capturing](#isVideoEnabled_int) с камер HMD должен быть включён, а [screen precision](../../../api/library/rendering/class.render_cpp.md#isScreenPrecision_int) должна быть равна 1.
### Возвращаемое значение

**true**, если альфа-смешение включено; иначе **false**. Значение по умолчанию - **false**.
## void setVideoEnabled ( bool enabled = 0 )

***Консоль*:**`vr_mixed_reality_video_enabled`Задаёт новое значение, указывающее, включён ли видеосигнал с изображением реального мира с передних камер HMD. Изображение реального мира используется для объединения виртуальных и реальных элементов для создания эффекта погружения в смешанной реальности.
### Аргументы

- *bool* **enabled** - **true**, чтобы включить изображение реального мира с передних камер HMD; **false** - чтобы отключить его. Значение по умолчанию - **false**.

## bool isVideoEnabled () const

***Консоль*:**`vr_mixed_reality_video_enabled`Возвращает текущее значение, указывающее, включён ли видеосигнал с изображением реального мира с передних камер HMD. Изображение реального мира используется для объединения виртуальных и реальных элементов для создания эффекта погружения в смешанной реальности.
### Возвращаемое значение

**true**, если изображение реального мира с передних камер HMD включено; иначе **false**. Значение по умолчанию - **false**.
## void setDepthTestRangeEnabled ( bool enabled = 0 )

***Консоль*:**`vr_mixed_reality_depth_test_range_enabled`Задаёт новое значение, указывающее, включено ли использование диапазона теста глубины. Используйте [depth test range](#getDepthTestRange_vec2) (*Depth Test Near Z*, *Depth Test Far Z*) для управления диапазоном, для которого выполняется тест глубины.
### Аргументы

- *bool* **enabled** - **true**, чтобы включить диапазон теста глубины; **false** - чтобы отключить его. Значение по умолчанию - **false**.

## bool isDepthTestRangeEnabled () const

***Консоль*:**`vr_mixed_reality_depth_test_range_enabled`Возвращает текущее значение, указывающее, включено ли использование диапазона теста глубины. Используйте [depth test range](#getDepthTestRange_vec2) (*Depth Test Near Z*, *Depth Test Far Z*) для управления диапазоном, для которого выполняется тест глубины.
### Возвращаемое значение

**true**, если диапазон теста глубины включён; иначе **false**. Значение по умолчанию - **false**.
## void setDepthTestRange ( const Math:: vec2 & range )

***Консоль*:**`vr_mixed_reality_depth_test_range`Задаёт новый диапазон теста глубины в виде двухкомпонентного вектора (ближняя и дальняя плоскости). [depth test range usage](#isDepthTestRangeEnabled_int) должно быть включено.
### Аргументы

- *const  Math::[vec2](../../../api/library/math/class.vec2_cpp.md)&* **range** - Диапазон теста глубины. **vec2(0.0f, 1.0f)** - значение по умолчанию

## Math:: vec2 getDepthTestRange () const

***Консоль*:**`vr_mixed_reality_depth_test_range`Возвращает текущий диапазон теста глубины в виде двухкомпонентного вектора (ближняя и дальняя плоскости). [depth test range usage](#isDepthTestRangeEnabled_int) должно быть включено.
### Возвращаемое значение

Текущий диапазон теста глубины.
**vec2(0.0f, 1.0f)** - значение по умолчанию
## int getChromaKeyConfigNum () const

Возвращает текущее количество поддерживаемых индексов конфигурации хромакея. Максимальный индекс будет count-1.
### Возвращаемое значение

Текущее количество индексов конфигурации хромакея.
## void setBlendMaskingMode ( VRMixedReality::BLEND_MASKING_MODE mode = 0 )

***Консоль*:**`vr_mixed_reality_blend_masking_mode`Задаёт новый режим *Blend Control Mask*, который можно использовать для расширения или ограничения маски хромакея, или для управления тестом глубины относительно оценённой глубины видео.
### Аргументы

- *[VRMixedReality::BLEND_MASKING_MODE](../../../api/library/vr/class.vrmixedreality_cpp.md#BLEND_MASKING_MODE)* **mode** - Режим маскирования. Одно из следующих значений:

  - **0** - Disabled (режим маскирования отключён). (по умолчанию)
  - **1** - Restrict Video to Mask (показывать сквозное видеоизображение (VST) в маске; можно использовать с хромакеем)
  - **2** - Restrict VR to Mask (показывать VR в маске; можно использовать с хромакеем)
  - **3** - Restrict VR to Chromakey reduced by Mask (показывать VR в маске, а хромакей - в остальных местах; требует хромакей)

## VRMixedReality::BLEND_MASKING_MODE getBlendMaskingMode () const

***Консоль*:**`vr_mixed_reality_blend_masking_mode`Возвращает текущий режим *Blend Control Mask*, который можно использовать для расширения или ограничения маски хромакея, или для управления тестом глубины относительно оценённой глубины видео.
### Возвращаемое значение

Текущий режим маскирования. Одно из следующих значений:
- **0** - Disabled (режим маскирования отключён). (по умолчанию)
- **1** - Restrict Video to Mask (показывать сквозное видеоизображение (VST) в маске; можно использовать с хромакеем)
- **2** - Restrict VR to Mask (показывать VR в маске; можно использовать с хромакеем)
- **3** - Restrict VR to Chromakey reduced by Mask (показывать VR в маске, а хромакей - в остальных местах; требует хромакей)

## void setBlendMaskingDebugEnabled ( bool enabled = 0 )

***Консоль*:**`vr_mixed_reality_blend_masking_debug_enabled`Задаёт новое значение, указывающее, включена ли отладочная визуализация маскирования смешения. [blend masking mode](#getBlendMaskingMode_int) должен быть включён.
### Аргументы

- *bool* **enabled** - **true**, чтобы включить отладочную визуализацию маскирования смешения; **false** - чтобы отключить её. Значение по умолчанию - **false**.

## bool isBlendMaskingDebugEnabled () const

***Консоль*:**`vr_mixed_reality_blend_masking_debug_enabled`Возвращает текущее значение, указывающее, включена ли отладочная визуализация маскирования смешения. [blend masking mode](#getBlendMaskingMode_int) должен быть включён.
### Возвращаемое значение

**true**, если отладочная визуализация маскирования смешения включена; иначе **false**. Значение по умолчанию - **false**.
## bool isBlendMaskingUsed () const

Возвращает текущее значение, указывающее, используется ли *Blend Control Mask* для расширения или ограничения маски хромакея, или для управления тестом глубины относительно оценённой глубины видео.
### Возвращаемое значение

**true**, если маска смешения используется; иначе **false**.
## Ptr < Texture > getCurrentBlendMaskColorBuffer () const

Возвращает текущее изображение, представляющее текущий буфер цвета *Blend Control Mask*.
### Возвращаемое значение

Текущий буфер цвета.
## void setCameraExposureTimeRaw ( double raw )

Задаёт новое значение времени экспозиции для камеры.
### Аргументы

- *double* **raw** - Время экспозиции, в кадрах в секунду (например, 90.0 -> ~11 мс).

## double getCameraExposureTimeRaw () const

Возвращает текущее значение времени экспозиции для камеры.
### Возвращаемое значение

Текущее время экспозиции, в кадрах в секунду (например, 90.0 -> ~11 мс).
## void setCameraExposureTime ( VRMixedReality::CAMERA_EXPOSURE_TIME time )

***Консоль*:**`vr_mixed_reality_camera_exposure_time`Задаёт новое значение времени экспозиции, допустимое для подключённого устройства.
### Аргументы

- *[VRMixedReality::CAMERA_EXPOSURE_TIME](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_EXPOSURE_TIME)* **time** - Допустимое значение времени экспозиции для подключённого устройства.

## VRMixedReality::CAMERA_EXPOSURE_TIME getCameraExposureTime () const

***Консоль*:**`vr_mixed_reality_camera_exposure_time`Возвращает текущее значение времени экспозиции, допустимое для подключённого устройства.
### Возвращаемое значение

Текущее допустимое значение времени экспозиции для подключённого устройства.

## void setCameraExposureTimeMode ( VRMixedReality::CAMERA_PROPERTY_MODE mode = 1 )

***Консоль*:**`vr_mixed_reality_camera_exposure_time_mode`Задаёт новый режим настройки экспозиции для камеры.
### Аргументы

- *[VRMixedReality::CAMERA_PROPERTY_MODE](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_PROPERTY_MODE)* **mode** - Режим настройки экспозиции. Одно из следующих значений:

  - **0** - настройка экспозиции отключена
  - **1** - автоматическая настройка экспозиции (по умолчанию)
  - **2** - ручная настройка экспозиции

## VRMixedReality::CAMERA_PROPERTY_MODE getCameraExposureTimeMode () const

***Консоль*:**`vr_mixed_reality_camera_exposure_time_mode`Возвращает текущий режим настройки экспозиции для камеры.
### Возвращаемое значение

Текущий режим настройки экспозиции. Одно из следующих значений:
- **0** - настройка экспозиции отключена
- **1** - автоматическая настройка экспозиции (по умолчанию)
- **2** - ручная настройка экспозиции

## void setCameraWhiteBalanceRaw ( int raw )

Задаёт новое значение коррекции баланса белого, допустимое для подключённого устройства.
### Аргументы

- *int* **raw** - Значение цветовой температуры.

## int getCameraWhiteBalanceRaw () const

Возвращает текущее значение коррекции баланса белого, допустимое для подключённого устройства.
### Возвращаемое значение

Текущее значение цветовой температуры.
## void setCameraWhiteBalance ( VRMixedReality::CAMERA_WHITE_BALANCE balance )

***Консоль*:**`vr_mixed_reality_camera_white_balance`Задаёт новое значение коррекции баланса белого, допустимое для подключённого устройства.
### Аргументы

- *[VRMixedReality::CAMERA_WHITE_BALANCE](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_WHITE_BALANCE)* **balance** - Значение цветовой температуры.

## VRMixedReality::CAMERA_WHITE_BALANCE getCameraWhiteBalance () const

***Консоль*:**`vr_mixed_reality_camera_white_balance`Возвращает текущее значение коррекции баланса белого, допустимое для подключённого устройства.
### Возвращаемое значение

Текущее значение цветовой температуры.

## void setCameraWhiteBalanceMode ( VRMixedReality::CAMERA_PROPERTY_MODE mode = 1 )

***Консоль*:**`vr_mixed_reality_camera_white_balance_mode`Задаёт новый режим настройки баланса белого для камеры.
### Аргументы

- *[VRMixedReality::CAMERA_PROPERTY_MODE](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_PROPERTY_MODE)* **mode** - Режим настройки баланса белого. Одно из следующих значений:

  - **0** - настройка баланса белого отключена
  - **1** - автоматическая настройка баланса белого (по умолчанию)
  - **2** - ручная настройка баланса белого

## VRMixedReality::CAMERA_PROPERTY_MODE getCameraWhiteBalanceMode () const

***Консоль*:**`vr_mixed_reality_camera_white_balance_mode`Возвращает текущий режим настройки баланса белого для камеры.
### Возвращаемое значение

Текущий режим настройки баланса белого. Одно из следующих значений:
- **0** - настройка баланса белого отключена
- **1** - автоматическая настройка баланса белого (по умолчанию)
- **2** - ручная настройка баланса белого

## void setCameraISORaw ( int isoraw )

Задаёт новое значение ISO, допустимое для подключённого устройства.
### Аргументы

- *int* **isoraw** - Значение ISO (например, "200" -> ISO200).

## int getCameraISORaw () const

Возвращает текущее значение ISO, допустимое для подключённого устройства.
### Возвращаемое значение

Текущее значение ISO (например, "200" -> ISO200).
## void setCameraISO ( VRMixedReality::CAMERA_ISO iso )

***Консоль*:**`vr_mixed_reality_camera_iso`Задаёт новое значение ISO для камеры.
### Аргументы

- *[VRMixedReality::CAMERA_ISO](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_ISO)* **iso** - Значение ISO.

## VRMixedReality::CAMERA_ISO getCameraISO () const

***Консоль*:**`vr_mixed_reality_camera_iso`Возвращает текущее значение ISO для камеры.
### Возвращаемое значение

Текущее значение ISO.

## void setCameraISOMode ( VRMixedReality::CAMERA_PROPERTY_MODE isomode = 1 )

***Консоль*:**`vr_mixed_reality_camera_iso_mode`Задаёт новый режим настройки ISO для камеры.
### Аргументы

- *[VRMixedReality::CAMERA_PROPERTY_MODE](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_PROPERTY_MODE)* **isomode** - Режим настройки ISO. Одно из следующих значений:

  - **0** - настройка ISO отключена
  - **1** - автоматическая настройка ISO (по умолчанию)
  - **2** - ручная настройка ISO

## VRMixedReality::CAMERA_PROPERTY_MODE getCameraISOMode () const

***Консоль*:**`vr_mixed_reality_camera_iso_mode`Возвращает текущий режим настройки ISO для камеры.
### Возвращаемое значение

Текущий режим настройки ISO. Одно из следующих значений:
- **0** - настройка ISO отключена
- **1** - автоматическая настройка ISO (по умолчанию)
- **2** - ручная настройка ISO

## void setCameraFlickerCompensationRaw ( int raw )

Задаёт новое значение компенсации мерцания для камеры. Это полезно при использовании HMD в помещении с преимущественно искусственным освещением, которое мерцает с частотой 50 Гц или 60 Гц и может вызывать визуальные артефакты мерцания на сквозном видеоизображении. Правильная настройка зависит от частоты используемой электросети. Например, в большинстве регионов Африки/Азии/Австралии/Европы частота составляет 50 Гц, а в большинстве регионов Северной и Южной Америки - 60 Гц.
### Аргументы

- *int* **raw** - Компенсация мерцания, в Гц.

## int getCameraFlickerCompensationRaw () const

Возвращает текущее значение компенсации мерцания для камеры. Это полезно при использовании HMD в помещении с преимущественно искусственным освещением, которое мерцает с частотой 50 Гц или 60 Гц и может вызывать визуальные артефакты мерцания на сквозном видеоизображении. Правильная настройка зависит от частоты используемой электросети. Например, в большинстве регионов Африки/Азии/Австралии/Европы частота составляет 50 Гц, а в большинстве регионов Северной и Южной Америки - 60 Гц.
### Возвращаемое значение

Текущая компенсация мерцания, в Гц.
## void setCameraFlickerCompensation ( VRMixedReality::CAMERA_FLICKER_COMPENSATION compensation )

***Консоль*:**`vr_mixed_reality_camera_flicker_compensation`Задаёт новое значение компенсации мерцания для камеры. Это полезно при использовании HMD в помещении с преимущественно искусственным освещением, которое мерцает с частотой 50 Гц или 60 Гц и может вызывать визуальные артефакты мерцания на сквозном видеоизображении. Правильная настройка зависит от частоты используемой электросети. Например, в большинстве регионов Африки/Азии/Австралии/Европы частота составляет 50 Гц, а в большинстве регионов Северной и Южной Америки - 60 Гц.
### Аргументы

- *[VRMixedReality::CAMERA_FLICKER_COMPENSATION](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_FLICKER_COMPENSATION)* **compensation** - Компенсация мерцания.

## VRMixedReality::CAMERA_FLICKER_COMPENSATION getCameraFlickerCompensation () const

***Консоль*:**`vr_mixed_reality_camera_flicker_compensation`Возвращает текущее значение компенсации мерцания для камеры. Это полезно при использовании HMD в помещении с преимущественно искусственным освещением, которое мерцает с частотой 50 Гц или 60 Гц и может вызывать визуальные артефакты мерцания на сквозном видеоизображении. Правильная настройка зависит от частоты используемой электросети. Например, в большинстве регионов Африки/Азии/Австралии/Европы частота составляет 50 Гц, а в большинстве регионов Северной и Южной Америки - 60 Гц.
### Возвращаемое значение

Текущая компенсация мерцания.

## int getCameraMinSharpness () const

Возвращает текущее минимальное возможное значение для [camera sharpness](#CameraSharpness).
### Возвращаемое значение

Текущее минимальное возможное значение резкости камеры.
## int getCameraMaxSharpness () const

Возвращает текущее максимальное возможное значение для [camera sharpness](#CameraSharpness).
### Возвращаемое значение

Текущее максимальное возможное значение резкости камеры.
## void setCameraSharpness ( int sharpness = 0 )

***Консоль*:**`vr_mixed_reality_camera_sharpness`Задаёт новое значение силы фильтра резкости для камеры.
### Аргументы

- *int* **sharpness** - Значение силы фильтра резкости: наименьшее значение соответствует малому объёму фильтрации, а наибольшее - максимальному объёму фильтрации. Диапазон значений: **[0, 10]**. Значение по умолчанию: **0**.

## int getCameraSharpness () const

***Консоль*:**`vr_mixed_reality_camera_sharpness`Возвращает текущее значение силы фильтра резкости для камеры.
### Возвращаемое значение

Текущее значение силы фильтра резкости: наименьшее значение соответствует малому объёму фильтрации, а наибольшее - максимальному объёму фильтрации.
Диапазон значений: **[0, 10]**. Значение по умолчанию: **0**.
## void setViewOffset ( float offset = 0.0 )

***Консоль*:**`vr_mixed_reality_view_offset`Задаёт новое [view offset](https://developer.varjo.com/docs/apidocs/_varjo__mr_8h.html#a0aa1772b02020977c3c5b1c974848f75) глаз (где должна располагаться камера глаза при использовании Mixed Reality):
- **0** для физической позиции глаза
- **1** для позиции камеры VST


### Аргументы

- *float* **offset** - Смещение вида. Диапазон значений: **[0.0, 1.0]**. Значение по умолчанию: **0.0**.

## float getViewOffset () const

***Консоль*:**`vr_mixed_reality_view_offset`Возвращает текущее [view offset](https://developer.varjo.com/docs/apidocs/_varjo__mr_8h.html#a0aa1772b02020977c3c5b1c974848f75) глаз (где должна располагаться камера глаза при использовании Mixed Reality):
- **0** для физической позиции глаза
- **1** для позиции камеры VST


### Возвращаемое значение

Текущее смещение вида.
Диапазон значений: **[0.0, 1.0]**. Значение по умолчанию: **0.0**.
## void setMarkerTrackingEnabled ( bool enabled = 0 )

***Консоль*:**`vr_mixed_reality_marker_tracking_enabled`Задаёт новое значение, указывающее, включено ли отслеживание маркеров.
### Аргументы

- *bool* **enabled** - **true**, чтобы включить отслеживание маркеров; **false** - чтобы отключить его. Значение по умолчанию - **false**.

## bool isMarkerTrackingEnabled () const

***Консоль*:**`vr_mixed_reality_marker_tracking_enabled`Возвращает текущее значение, указывающее, включено ли отслеживание маркеров.
### Возвращаемое значение

**true**, если отслеживание маркеров включено; иначе **false**. Значение по умолчанию - **false**.
## short getNumMarkerObjectVisible () const

Возвращает текущее количество видимых объектов маркеров.
### Возвращаемое значение

Текущее количество видимых объектов маркеров.
## void setCubemapMode ( VRMixedReality::CUBEMAP_MODE mode = 2 )

***Консоль*:**`vr_mixed_reality_cubemap_mode`Задаёт новый режим, определяющий способ задания AR-текстуры для окружения.
### Аргументы

- *[VRMixedReality::CUBEMAP_MODE](../../../api/library/vr/class.vrmixedreality_cpp.md#CUBEMAP_MODE)* **mode** - Режим кубической текстуры. Одно из следующих значений:

  - **0** - потоковая передача кубической текстуры от AR-камер отключена.
  - **1** - текстура окружения замещает небо.
  - **2** - первый пресет окружения определяет способ задания AR-текстуры для окружения. (по умолчанию)
  - **3** - второй пресет окружения определяет способ задания AR-текстуры для окружения.
  - **4** - третий пресет окружения определяет способ задания AR-текстуры для окружения.

## VRMixedReality::CUBEMAP_MODE getCubemapMode () const

***Консоль*:**`vr_mixed_reality_cubemap_mode`Возвращает текущий режим, определяющий способ задания AR-текстуры для окружения.
### Возвращаемое значение

Текущий режим кубической текстуры. Одно из следующих значений:
- **0** - потоковая передача кубической текстуры от AR-камер отключена.
- **1** - текстура окружения замещает небо.
- **2** - первый пресет окружения определяет способ задания AR-текстуры для окружения. (по умолчанию)
- **3** - второй пресет окружения определяет способ задания AR-текстуры для окружения.
- **4** - третий пресет окружения определяет способ задания AR-текстуры для окружения.

## void setCubemapGGXQuality ( Render::GGX_MIPMAPS_QUALITY ggxquality = 1 )

***Консоль*:**`vr_mixed_reality_cubemap_ggx_quality`Задаёт новое качество генерируемых GGX-мипов для AR-кубической текстуры.
### Аргументы

- *[Render::GGX_MIPMAPS_QUALITY](../../../api/library/rendering/class.render_cpp.md#GGX_MIPMAPS_QUALITY)* **ggxquality** - Качество GGX-мипкарт. Одно из следующих значений:

  - **0** - низкое
  - **1** - среднее (по умолчанию)
  - **2** - высокое
  - **3** - ультра

## Render::GGX_MIPMAPS_QUALITY getCubemapGGXQuality () const

***Консоль*:**`vr_mixed_reality_cubemap_ggx_quality`Возвращает текущее качество генерируемых GGX-мипов для AR-кубической текстуры.
### Возвращаемое значение

Текущее качество GGX-мипкарт. Одно из следующих значений:
- **0** - низкое
- **1** - среднее (по умолчанию)
- **2** - высокое
- **3** - ультра

## void setOverrideColorCorrectionMode ( VRMixedReality::OVERRIDE_COLOR_CORRECTION_MODE mode = 0 )

***Консоль*:**`vr_mixed_reality_override_color_correction_mode`Задаёт новый режим цветокоррекции для потока с AR-камер.
### Аргументы

- *[VRMixedReality::OVERRIDE_COLOR_CORRECTION_MODE](../../../api/library/vr/class.vrmixedreality_cpp.md#OVERRIDE_COLOR_CORRECTION_MODE)* **mode** - Режим цветокоррекции. Одно из следующих значений:

  - **0** - коррекция отключена. (по умолчанию)
  - **1** - коррекция экспозиции для потока с AR-камер.
  - **2** - коррекция экспозиции и баланса белого для потока.

## VRMixedReality::OVERRIDE_COLOR_CORRECTION_MODE getOverrideColorCorrectionMode () const

***Консоль*:**`vr_mixed_reality_override_color_correction_mode`Возвращает текущий режим цветокоррекции для потока с AR-камер.
### Возвращаемое значение

Текущий режим цветокоррекции. Одно из следующих значений:
- **0** - коррекция отключена. (по умолчанию)
- **1** - коррекция экспозиции для потока с AR-камер.
- **2** - коррекция экспозиции и баланса белого для потока.

## static Event<> getEventCameraPropertyUpdateSharpness () const

Событие, генерируемое при изменении значения резкости камеры в Varjo Base. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CameraPropertyUpdateSharpness
void camerapropertyupdatesharpness_event_handler()
{
	Log::message("\Обработка события CameraPropertyUpdateSharpness\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections camerapropertyupdatesharpness_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventCameraPropertyUpdateSharpness().connect(camerapropertyupdatesharpness_event_connections, camerapropertyupdatesharpness_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventCameraPropertyUpdateSharpness().connect(camerapropertyupdatesharpness_event_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateSharpness (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
camerapropertyupdatesharpness_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection camerapropertyupdatesharpness_event_connection;

// подписываемся на событие CameraPropertyUpdateSharpness с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventCameraPropertyUpdateSharpness().connect(camerapropertyupdatesharpness_event_connection, camerapropertyupdatesharpness_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
camerapropertyupdatesharpness_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
camerapropertyupdatesharpness_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CameraPropertyUpdateSharpness через соединение
camerapropertyupdatesharpness_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события CameraPropertyUpdateSharpness, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события CameraPropertyUpdateSharpness\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventCameraPropertyUpdateSharpness().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId camerapropertyupdatesharpness_handler_id;

// подписываемся на событие CameraPropertyUpdateSharpness с лямбда-обработчиком, сохраняя идентификатор соединения
camerapropertyupdatesharpness_handler_id = VRMixedReality::getEventCameraPropertyUpdateSharpness().connect(e_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateSharpness (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventCameraPropertyUpdateSharpness().disconnect(camerapropertyupdatesharpness_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CameraPropertyUpdateSharpness при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventCameraPropertyUpdateSharpness().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventCameraPropertyUpdateSharpness().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventCameraPropertyUpdateFlickerCompensation () const

Событие, генерируемое при изменении значения компенсации мерцания камеры в Varjo Base. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CameraPropertyUpdateFlickerCompensation
void camerapropertyupdateflickercompensation_event_handler()
{
	Log::message("\Обработка события CameraPropertyUpdateFlickerCompensation\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections camerapropertyupdateflickercompensation_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().connect(camerapropertyupdateflickercompensation_event_connections, camerapropertyupdateflickercompensation_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().connect(camerapropertyupdateflickercompensation_event_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateFlickerCompensation (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
camerapropertyupdateflickercompensation_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection camerapropertyupdateflickercompensation_event_connection;

// подписываемся на событие CameraPropertyUpdateFlickerCompensation с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().connect(camerapropertyupdateflickercompensation_event_connection, camerapropertyupdateflickercompensation_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
camerapropertyupdateflickercompensation_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
camerapropertyupdateflickercompensation_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CameraPropertyUpdateFlickerCompensation через соединение
camerapropertyupdateflickercompensation_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события CameraPropertyUpdateFlickerCompensation, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события CameraPropertyUpdateFlickerCompensation\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId camerapropertyupdateflickercompensation_handler_id;

// подписываемся на событие CameraPropertyUpdateFlickerCompensation с лямбда-обработчиком, сохраняя идентификатор соединения
camerapropertyupdateflickercompensation_handler_id = VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().connect(e_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateFlickerCompensation (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().disconnect(camerapropertyupdateflickercompensation_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CameraPropertyUpdateFlickerCompensation при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventCameraPropertyUpdateFlickerCompensation().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventCameraPropertyUpdateISO () const

Событие, генерируемое при изменении значения ISO камеры и/или режима настройки ISO в Varjo Base. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CameraPropertyUpdateISO
void camerapropertyupdateiso_event_handler()
{
	Log::message("\Обработка события CameraPropertyUpdateISO\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections camerapropertyupdateiso_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventCameraPropertyUpdateISO().connect(camerapropertyupdateiso_event_connections, camerapropertyupdateiso_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventCameraPropertyUpdateISO().connect(camerapropertyupdateiso_event_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateISO (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
camerapropertyupdateiso_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection camerapropertyupdateiso_event_connection;

// подписываемся на событие CameraPropertyUpdateISO с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventCameraPropertyUpdateISO().connect(camerapropertyupdateiso_event_connection, camerapropertyupdateiso_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
camerapropertyupdateiso_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
camerapropertyupdateiso_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CameraPropertyUpdateISO через соединение
camerapropertyupdateiso_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события CameraPropertyUpdateISO, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события CameraPropertyUpdateISO\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventCameraPropertyUpdateISO().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId camerapropertyupdateiso_handler_id;

// подписываемся на событие CameraPropertyUpdateISO с лямбда-обработчиком, сохраняя идентификатор соединения
camerapropertyupdateiso_handler_id = VRMixedReality::getEventCameraPropertyUpdateISO().connect(e_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateISO (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventCameraPropertyUpdateISO().disconnect(camerapropertyupdateiso_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CameraPropertyUpdateISO при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventCameraPropertyUpdateISO().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventCameraPropertyUpdateISO().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventCameraPropertyUpdateWhiteBalance () const

Событие, генерируемое при изменении значения коррекции баланса белого камеры и/или режима настройки баланса белого в Varjo Base. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CameraPropertyUpdateWhiteBalance
void camerapropertyupdatewhitebalance_event_handler()
{
	Log::message("\Обработка события CameraPropertyUpdateWhiteBalance\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections camerapropertyupdatewhitebalance_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().connect(camerapropertyupdatewhitebalance_event_connections, camerapropertyupdatewhitebalance_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().connect(camerapropertyupdatewhitebalance_event_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateWhiteBalance (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
camerapropertyupdatewhitebalance_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection camerapropertyupdatewhitebalance_event_connection;

// подписываемся на событие CameraPropertyUpdateWhiteBalance с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().connect(camerapropertyupdatewhitebalance_event_connection, camerapropertyupdatewhitebalance_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
camerapropertyupdatewhitebalance_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
camerapropertyupdatewhitebalance_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CameraPropertyUpdateWhiteBalance через соединение
camerapropertyupdatewhitebalance_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события CameraPropertyUpdateWhiteBalance, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события CameraPropertyUpdateWhiteBalance\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId camerapropertyupdatewhitebalance_handler_id;

// подписываемся на событие CameraPropertyUpdateWhiteBalance с лямбда-обработчиком, сохраняя идентификатор соединения
camerapropertyupdatewhitebalance_handler_id = VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().connect(e_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateWhiteBalance (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().disconnect(camerapropertyupdatewhitebalance_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CameraPropertyUpdateWhiteBalance при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventCameraPropertyUpdateWhiteBalance().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventCameraPropertyUpdateExposureTime () const

Событие, генерируемое при изменении значения времени экспозиции камеры и/или режима настройки экспозиции в Varjo Base. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CameraPropertyUpdateExposureTime
void camerapropertyupdateexposuretime_event_handler()
{
	Log::message("\Обработка события CameraPropertyUpdateExposureTime\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections camerapropertyupdateexposuretime_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventCameraPropertyUpdateExposureTime().connect(camerapropertyupdateexposuretime_event_connections, camerapropertyupdateexposuretime_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventCameraPropertyUpdateExposureTime().connect(camerapropertyupdateexposuretime_event_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateExposureTime (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
camerapropertyupdateexposuretime_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection camerapropertyupdateexposuretime_event_connection;

// подписываемся на событие CameraPropertyUpdateExposureTime с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventCameraPropertyUpdateExposureTime().connect(camerapropertyupdateexposuretime_event_connection, camerapropertyupdateexposuretime_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
camerapropertyupdateexposuretime_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
camerapropertyupdateexposuretime_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CameraPropertyUpdateExposureTime через соединение
camerapropertyupdateexposuretime_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события CameraPropertyUpdateExposureTime, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события CameraPropertyUpdateExposureTime\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventCameraPropertyUpdateExposureTime().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId camerapropertyupdateexposuretime_handler_id;

// подписываемся на событие CameraPropertyUpdateExposureTime с лямбда-обработчиком, сохраняя идентификатор соединения
camerapropertyupdateexposuretime_handler_id = VRMixedReality::getEventCameraPropertyUpdateExposureTime().connect(e_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateExposureTime (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventCameraPropertyUpdateExposureTime().disconnect(camerapropertyupdateexposuretime_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CameraPropertyUpdateExposureTime при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventCameraPropertyUpdateExposureTime().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventCameraPropertyUpdateExposureTime().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventChromakeyUpdate () const

Событие, генерируемое при изменении настроек хромакея в Varjo Base. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ChromakeyUpdate
void chromakeyupdate_event_handler()
{
	Log::message("\Обработка события ChromakeyUpdate\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections chromakeyupdate_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventChromakeyUpdate().connect(chromakeyupdate_event_connections, chromakeyupdate_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventChromakeyUpdate().connect(chromakeyupdate_event_connections, []() {
		Log::message("\Обработка события ChromakeyUpdate (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
chromakeyupdate_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection chromakeyupdate_event_connection;

// подписываемся на событие ChromakeyUpdate с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventChromakeyUpdate().connect(chromakeyupdate_event_connection, chromakeyupdate_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
chromakeyupdate_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
chromakeyupdate_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ChromakeyUpdate через соединение
chromakeyupdate_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события ChromakeyUpdate, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события ChromakeyUpdate\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventChromakeyUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId chromakeyupdate_handler_id;

// подписываемся на событие ChromakeyUpdate с лямбда-обработчиком, сохраняя идентификатор соединения
chromakeyupdate_handler_id = VRMixedReality::getEventChromakeyUpdate().connect(e_connections, []() {
		Log::message("\Обработка события ChromakeyUpdate (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventChromakeyUpdate().disconnect(chromakeyupdate_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ChromakeyUpdate при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventChromakeyUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventChromakeyUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventDeviceDisconnected () const

Событие, генерируемое при отключении устройства Varjo. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события DeviceDisconnected
void devicedisconnected_event_handler()
{
	Log::message("\Обработка события DeviceDisconnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections devicedisconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventDeviceDisconnected().connect(devicedisconnected_event_connections, devicedisconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventDeviceDisconnected().connect(devicedisconnected_event_connections, []() {
		Log::message("\Обработка события DeviceDisconnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
devicedisconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection devicedisconnected_event_connection;

// подписываемся на событие DeviceDisconnected с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventDeviceDisconnected().connect(devicedisconnected_event_connection, devicedisconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
devicedisconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
devicedisconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие DeviceDisconnected через соединение
devicedisconnected_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события DeviceDisconnected, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события DeviceDisconnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventDeviceDisconnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId devicedisconnected_handler_id;

// подписываемся на событие DeviceDisconnected с лямбда-обработчиком, сохраняя идентификатор соединения
devicedisconnected_handler_id = VRMixedReality::getEventDeviceDisconnected().connect(e_connections, []() {
		Log::message("\Обработка события DeviceDisconnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventDeviceDisconnected().disconnect(devicedisconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий DeviceDisconnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventDeviceDisconnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventDeviceDisconnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventDeviceConnected () const

Событие, генерируемое при подключении устройства Varjo. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события DeviceConnected
void deviceconnected_event_handler()
{
	Log::message("\Обработка события DeviceConnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections deviceconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventDeviceConnected().connect(deviceconnected_event_connections, deviceconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventDeviceConnected().connect(deviceconnected_event_connections, []() {
		Log::message("\Обработка события DeviceConnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
deviceconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection deviceconnected_event_connection;

// подписываемся на событие DeviceConnected с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventDeviceConnected().connect(deviceconnected_event_connection, deviceconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
deviceconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
deviceconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие DeviceConnected через соединение
deviceconnected_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события DeviceConnected, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события DeviceConnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventDeviceConnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId deviceconnected_handler_id;

// подписываемся на событие DeviceConnected с лямбда-обработчиком, сохраняя идентификатор соединения
deviceconnected_handler_id = VRMixedReality::getEventDeviceConnected().connect(e_connections, []() {
		Log::message("\Обработка события DeviceConnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventDeviceConnected().disconnect(deviceconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий DeviceConnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventDeviceConnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventDeviceConnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<> getEventCameraPropertyUpdateVSTReprojection () const

Событие, генерируемое при обновлении свойства репроекции VST камеры. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события CameraPropertyUpdateVSTReprojection
void camerapropertyupdatevstreprojection_event_handler()
{
	Log::message("\Обработка события CameraPropertyUpdateVSTReprojection\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections camerapropertyupdatevstreprojection_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().connect(camerapropertyupdatevstreprojection_event_connections, camerapropertyupdatevstreprojection_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().connect(camerapropertyupdatevstreprojection_event_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateVSTReprojection (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
camerapropertyupdatevstreprojection_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection camerapropertyupdatevstreprojection_event_connection;

// подписываемся на событие CameraPropertyUpdateVSTReprojection с функцией-обработчиком, сохраняя соединение
VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().connect(camerapropertyupdatevstreprojection_event_connection, camerapropertyupdatevstreprojection_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
camerapropertyupdatevstreprojection_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
camerapropertyupdatevstreprojection_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие CameraPropertyUpdateVSTReprojection через соединение
camerapropertyupdatevstreprojection_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события CameraPropertyUpdateVSTReprojection, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события CameraPropertyUpdateVSTReprojection\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId camerapropertyupdatevstreprojection_handler_id;

// подписываемся на событие CameraPropertyUpdateVSTReprojection с лямбда-обработчиком, сохраняя идентификатор соединения
camerapropertyupdatevstreprojection_handler_id = VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().connect(e_connections, []() {
		Log::message("\Обработка события CameraPropertyUpdateVSTReprojection (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().disconnect(camerapropertyupdatevstreprojection_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий CameraPropertyUpdateVSTReprojection при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
VRMixedReality::getEventCameraPropertyUpdateVSTReprojection().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## void setCameraVSTReprojectionMode ( VRMixedReality::CAMERA_PROPERTY_MODE mode = 0 )

***Консоль*:**`vr_mixed_reality_camera_vst_reprojection_mode`Задаёт новый режим репроекции VST.
### Аргументы

- *[VRMixedReality::CAMERA_PROPERTY_MODE](../../../api/library/vr/class.vrmixedreality_cpp.md#CAMERA_PROPERTY_MODE)* **mode** - Режим репроекции VST. Одно из следующих значений:

  - **0** - репроекция VST отключена (по умолчанию). (по умолчанию)
  - **1** - автоматический режим репроекции VST (для репроекции используется буфер глубины)
  - **2** - ручной режим репроекции VST

## VRMixedReality::CAMERA_PROPERTY_MODE getCameraVSTReprojectionMode () const

***Консоль*:**`vr_mixed_reality_camera_vst_reprojection_mode`Возвращает текущий режим репроекции VST.
### Возвращаемое значение

Текущий режим репроекции VST. Одно из следующих значений:
- **0** - репроекция VST отключена (по умолчанию). (по умолчанию)
- **1** - автоматический режим репроекции VST (для репроекции используется буфер глубины)
- **2** - ручной режим репроекции VST

## void setCameraVSTReprojectionDistance ( float distance = 0.0f )

***Консоль*:**`vr_mixed_reality_camera_vst_reprojection_distance`Задаёт новое статическое расстояние в метрах, используемое для сдвига всего изображения. Настраивается только если [VST reprojection mode](#CameraVSTReprojectionMode) установлен в [Manual](#CAMERA_PROPERTY_MODE_MANUAL).
### Аргументы

- *float* **distance** - Статическое расстояние в метрах, используемое для управления репроекцией VST. Диапазон значений: **[0.0f, 1000.0f]**. Значение по умолчанию: **0.0f**.

## float getCameraVSTReprojectionDistance () const

***Консоль*:**`vr_mixed_reality_camera_vst_reprojection_distance`Возвращает текущее статическое расстояние в метрах, используемое для сдвига всего изображения. Настраивается только если [VST reprojection mode](#CameraVSTReprojectionMode) установлен в [Manual](#CAMERA_PROPERTY_MODE_MANUAL).
### Возвращаемое значение

Текущее статическое расстояние в метрах, используемое для управления репроекцией VST.
Диапазон значений: **[0.0f, 1000.0f]**. Значение по умолчанию: **0.0f**.
---

## void applySettings ( )

Обновляет настройки смешанной реальности до текущих настроек.
## bool isChromaKeyConfigEnabled ( int index ) const

Возвращает текущее значение, указывающее, включена ли конфигурация хромакея с указанным индексом.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.

### Возвращаемое значение

1, если конфигурация хромакея включена; иначе 0.
## void setChromaKeyConfigEnabled ( int index , bool enabled )

Задаёт новое значение, указывающее, включена ли конфигурация хромакея с указанным индексом.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.
- *bool* **enabled** - 1, чтобы включить конфигурацию хромакея; 0, чтобы отключить её.

## Math:: vec3 getChromaKeyConfigFalloff ( int index ) const

Возвращает текущие значения спада допуска для компонентов HSV целевого цвета хромакея.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.

### Возвращаемое значение

Текущие значения спада допуска для компонентов HSV целевого цвета хромакея. Диапазон для каждого компонента - [0.0; 1.0].
## void setChromaKeyConfigFalloff ( int index , const Math:: vec3 & falloff )

Задаёт новые значения спада допуска для компонентов HSV целевого цвета хромакея.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **falloff** - Новые значения спада допуска для компонентов HSV целевого цвета хромакея. Диапазон для каждого компонента - [0.0; 1.0].

## Math:: vec3 getChromaKeyConfigTargetColor ( int index ) const

Возвращает текущий целевой цвет хромакея в цветовой модели HSV.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.

### Возвращаемое значение

Текущий целевой цвет хромакея в цветовой модели HSV. Диапазон для каждого компонента - [0.0; 1.0].
## void setChromaKeyConfigTargetColor ( int index , const Math:: vec3 & target_color )

Задаёт новый целевой цвет хромакея в цветовой модели HSV.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **target_color** - Новый целевой цвет хромакея в цветовой модели HSV. Диапазон для каждого компонента - [0.0; 1.0].

## Math:: vec3 getChromaKeyConfigTolerance ( int index ) const

Возвращает текущие значения допуска для компонентов HSV целевого цвета хромакея.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.

### Возвращаемое значение

Текущие значения допуска для компонентов HSV целевого цвета хромакея. Диапазон для каждого компонента - [0.0; 1.0].
## void setChromaKeyConfigTolerance ( int index , const Math:: vec3 & tolerance )

Задаёт новые значения допуска для компонентов HSV целевого цвета хромакея.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.
- *const  Math::[vec3](../../../api/library/math/class.vec3_cpp.md) &* **tolerance** - Новые значения допуска для компонентов HSV целевого цвета хромакея. Диапазон для каждого компонента - [0.0; 1.0].

## void applyChromaKeySettings ( int index ) const

Обновляет настройки конфигурации хромакея с указанным индексом до текущих настроек.
### Аргументы

- *int* **index** - Индекс конфигурации хромакея в диапазоне от 0 до [config count](#ChromaKeyConfigNum) - 1.

## Vector <double> getCameraSupportedRawExposureTimes ( ) const

Возвращает вектор, содержащий значения времени экспозиции, заданные как допустимые для подключённого устройства.
### Возвращаемое значение

Вектор, содержащий значения времени экспозиции.
## Vector <int> getCameraSupportedRawWhiteBalances ( ) const

Возвращает вектор, содержащий значения баланса белого, заданные как допустимые для подключённого устройства.
### Возвращаемое значение

Вектор, содержащий значения баланса белого.
## Vector <int> getCameraSupportedRawISO ( ) const

Возвращает вектор, содержащий значения ISO, заданные как допустимые для подключённого устройства.
### Возвращаемое значение

Вектор, содержащий значения ISO.
## Vector <int> getCameraSupportedRawFlickerCompensations ( ) const

Возвращает вектор, содержащий значения компенсации мерцания, заданные как допустимые для подключённого устройства.
### Возвращаемое значение

Вектор, содержащий значения компенсации мерцания.
## Ptr < VRMarkerObject > getMarkerObject ( short index ) const

Возвращает объект маркера с указанным индексом.
### Аргументы

- *short* **index** - Индекс объекта маркера.

### Возвращаемое значение

Объект маркера.
## Ptr < VRMarkerObject > getMarkerObjectByID ( short marker_id ) const

Возвращает объект маркера с указанным ID.
### Аргументы

- *short* **marker_id** - ID объекта маркера.

### Возвращаемое значение

Объект маркера.
## bool cameraConfigLock ( ) const

Возвращает значение, указывающее, была ли успешна попытка заблокировать конфигурацию камеры.
### Возвращаемое значение

**true**, если конфигурация камеры успешно заблокирована или уже была заблокирована; иначе **false**.
## void cameraConfigUnlock ( ) const

Разблокирует ранее заблокированную конфигурацию камеры.
## bool hasFeatureChromakey ( ) const

Возвращает значение, указывающее, доступно ли смешение по хромакею для композиции смешанной реальности.
### Возвращаемое значение

true, если смешение по хромакею доступно; иначе false.
## bool hasFeatureAlphaBlend ( ) const

Возвращает значение, указывающее, поддерживается ли альфа-смешение для смешивания реальных и виртуальных изображений.
### Возвращаемое значение

true, если альфа-смешение поддерживается; иначе false.
## bool hasFeatureDepthTest ( ) const

Возвращает значение, указывающее, доступен ли тест глубины для смешивания реального и виртуального контента на основе перекрытия по глубине.
### Возвращаемое значение

true, если тест глубины доступен; иначе false.
## bool hasFeatureDepthTestRange ( ) const

Возвращает значение, указывающее, поддерживается ли настраиваемый диапазон теста глубины.
### Возвращаемое значение

true, если настраиваемый диапазон теста глубины поддерживается; иначе false.
## bool hasFeatureBlendmasking ( ) const

Возвращает значение, указывающее, поддерживается ли маскирование смешения в смешанной реальности.
### Возвращаемое значение

true, если маскирование смешения поддерживается; иначе false.
## bool hasFeatureCameraProperties ( ) const

Возвращает значение, указывающее, поддерживается ли доступ к свойствам камеры реального мира (например, баланс белого, ISO, выдержка и т.д.).
### Возвращаемое значение

true, если доступ к свойствам камеры реального мира поддерживается; иначе false.
## bool hasFeatureMarkerTracking ( ) const

Возвращает значение, указывающее, поддерживается ли пространственное отслеживание на основе маркеров.
### Возвращаемое значение

true, если пространственное отслеживание на основе маркеров поддерживается; иначе false.
## bool hasFeatureViewOffset ( ) const

Возвращает значение, указывающее, поддерживается ли смещение вида для каждого глаза для ручного совмещения виртуального контента со сквозным изображением.
### Возвращаемое значение

true, если смещение вида для каждого глаза поддерживается; иначе false.
## bool hasFeatureColorCorrection ( ) const

Возвращает значение, указывающее, поддерживается ли функция цветокоррекции.
### Возвращаемое значение

true, если функция цветокоррекции поддерживается; иначе false.
## bool hasFeatureEnvironmentCubemap ( ) const

Возвращает значение, указывающее, поддерживается ли функция кубической текстуры окружения.
### Возвращаемое значение

true, если функция кубической текстуры окружения поддерживается; иначе false.
