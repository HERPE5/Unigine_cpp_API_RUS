# Класс Unigine::InputVRHead (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputVRDevice


Этот класс обрабатывает ввод от шлема виртуальной реальности (HMD).


## Класс InputVRHead

### Перечисления

## MODEL_TYPE

| Имя | Описание |
|---|---|
| **MODEL_TYPE_UNKNOWN** = 0 | Неизвестный HMD. |
| **MODEL_TYPE_OCULUS_BEGIN** = 1 | Первый элемент для перебора типов моделей HMD Oculus Rift. |
| **MODEL_TYPE_OCULUS_DK2** = 1 | Oculus Rift DK2 |
| **MODEL_TYPE_OCULUS_CB** = 2 | Oculus Rift CB |
| **MODEL_TYPE_OCULUS_OTHER** = 3 | Другая модель HMD Oculus Rift. |
| **MODEL_TYPE_OCULUS_E3_2015** = 4 | Oculus Rift E3 2015 |
| **MODEL_TYPE_OCULUS_ES06** = 5 | Oculus Rift ES06 |
| **MODEL_TYPE_OCULUS_ES09** = 6 | Oculus Rift ES09 |
| **MODEL_TYPE_OCULUS_ES11** = 7 | Oculus Rift ES11 |
| **MODEL_TYPE_OCULUS_RIFT** = 8 | Oculus Rift CV1 |
| **MODEL_TYPE_OCULUS_RIFT_S** = 9 | Oculus Rift Rift S |
| **MODEL_TYPE_OCULUS_END** = 9 | Последний элемент для перебора типов моделей HMD Oculus Rift. |
| **MODEL_TYPE_VARJO_BEGIN** = 10 | Первый элемент для перебора типов моделей HMD Varjo. |
| **MODEL_TYPE_VARJO_VR_1** = 10 | Varjo VR-1 |
| **MODEL_TYPE_VARJO_XR_1** = 11 | Varjo XR-1 |
| **MODEL_TYPE_VARJO_VR_2** = 12 | Varjo VR-2 |
| **MODEL_TYPE_VARJO_VR_2_PRO** = 13 | Varjo VR-2 Pro |
| **MODEL_TYPE_VARJO_VR_3** = 14 | Varjo VR-3 |
| **MODEL_TYPE_VARJO_XR_3** = 15 | Varjo XR-3 |
| **MODEL_TYPE_VARJO_AERO** = 16 | Varjo AERO |
| **MODEL_TYPE_VARJO_END** = 16 | Последний элемент для перебора типов моделей HMD Varjo. |
| **MODEL_TYPE_OPENVR_BEGIN** = 17 | Первый элемент для перебора типов моделей HMD. |
| **MODEL_TYPE_OPENVR_HTC_VIVE** = 17 | HTC Vive |
| **MODEL_TYPE_OPENVR_HTC_VIVE_PRO** = 18 | HTC Vive Pro MV |
| **MODEL_TYPE_OPENVR_HTC_FOCUS** = 19 | HTC Vive Focus |
| **MODEL_TYPE_OPENVR_VALVE_INDEX** = 20 | Valve Index |
| **MODEL_TYPE_OPENVR_END** = 20 | Последний элемент для перебора типов моделей HMD. |
| **NUM_MODEL_TYPES** = 21 | Общее количество типов моделей HMD. |

### Методы класса

---

## InputVRHead::MODEL_TYPE getModelType ( ) const

Возвращает тип модели HMD.
### Возвращаемое значение

Тип модели HMD.
## bool hasButtons ( ) const

Возвращает значение, указывающее, есть ли у HMD кнопки.
### Возвращаемое значение

true, если кнопки есть; иначе false.
## Vector <float> getSupportedRefreshRates ( ) const

Возвращает массив поддерживаемых частот обновления дисплея, в Гц, с как минимум одной поддерживаемой частотой обновления.
### Возвращаемое значение

Вектор поддерживаемых частот обновления дисплея, в Гц.
## void setRefreshRate ( float rate )

Устанавливает частоту обновления дисплея, если поддерживается.
### Аргументы

- *float* **rate** - Частота обновления дисплея, в Гц.

## float getRefreshRate ( ) const

Возвращает текущую частоту обновления дисплея, в Гц.
### Возвращаемое значение

Частота обновления дисплея, в Гц.
## void setTrackingPositionEnabled ( bool enabled )

Устанавливает значение, указывающее, включено ли отслеживание позиции головы.
### Аргументы

- *bool* **enabled** - true, чтобы включить отслеживание позиции; false, чтобы отключить.

## bool isTrackingPositionEnabled ( ) const

Возвращает значение, указывающее, включено ли отслеживание позиции головы.
### Возвращаемое значение

true, если отслеживание позиции включено; иначе false.
## void setTrackingRotationEnabled ( bool enabled )

Устанавливает значение, указывающее, включено ли отслеживание вращения головы.
### Аргументы

- *bool* **enabled** - true, чтобы включить отслеживание вращения; false, чтобы отключить.

## bool isTrackingRotationEnabled ( ) const

Возвращает значение, указывающее, включено ли отслеживание вращения головы.
### Возвращаемое значение

true, если отслеживание вращения включено; иначе false.
## bool isButtonPressed ( Input::VR_BUTTON button ) const

Возвращает значение, указывающее, нажата ли заданная кнопка. Проверяйте это значение для выполнения непрерывных действий.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.

### Возвращаемое значение

true, если кнопка нажата; иначе false.
## bool isButtonDown ( Input::VR_BUTTON button ) const

Возвращает значение, указывающее, была ли заданная кнопка нажата в течение текущего кадра.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.

### Возвращаемое значение

true, если кнопка была нажата; иначе false.
## bool isButtonUp ( Input::VR_BUTTON button ) const

Возвращает значение, указывающее, была ли заданная кнопка отпущена в течение текущего кадра.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.

### Возвращаемое значение

true, если кнопка была отпущена; иначе false.
## Ptr < InputEventVRButton > getButtonEvent ( Input::VR_BUTTON button ) const

Возвращает текущее обрабатываемое событие ввода кнопки HMD.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.

### Возвращаемое значение

Событие ввода кнопки HMD, или nullptr, если для указанной кнопки нет событий в текущем кадре.
## int getButtonEvents ( Input::VR_BUTTON button , Vector < Ptr < InputEventVRButton >> & OUT_events )

Возвращает количество событий ввода для указанной кнопки HMD и помещает события в указанный выходной буфер.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEventVRButton](../../../api/library/controls/class.inputeventvrbutton_cpp.md)>> &* **OUT_events** - Буфер с событиями ввода кнопок HMD. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

Количество событий ввода для указанной кнопки HMD.
