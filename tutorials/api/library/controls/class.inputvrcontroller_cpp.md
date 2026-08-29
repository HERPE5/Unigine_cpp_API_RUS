# Класс Unigine::InputVRController (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputVRDevice


Этот класс управляет вводом с VR-контроллера, служа основным интерфейсом для VR-ввода.


> **Примечание:** Каждый экземпляр класса InputVRController содержит собственный набор значений, считанных с контроллера.


Существует *три* типа VR-контроллеров: *левосторонний*, *правосторонний* контроллеры и *беговая дорожка*. Чтобы получить тип VR-контроллера, вы можете использовать функцию *[getControllerType()](#getControllerType_int)*.


Класс предоставляет доступ к следующему вводу:


- **Кнопки** VR-контроллера, включая кнопки *касания*. Они могут быть либо нажаты, либо отпущены в текущем кадре, либо непрерывно нажаты или затронуты в течение нескольких кадров подряд, включая текущий.
- **Оси** VR-контроллера, определяющие одномерное движение элемента управления. В зависимости от типа VR-контроллера количество осей может отличаться. Обычно их *3* или *4*. Ось может быть привязана к элементу управления одного из поддерживаемых типов, также называемому [*типом оси*](../../../api/library/controls/class.inputvrcontroller_cpp.md#AXIS_TYPE). Чтобы определить поддерживаемые оси, вызовите *[getNumAxes()](../../../api/library/controls/class.inputvrcontroller_cpp.md#getNumAxes_int)*. Кроме того, вы можете получить тип оси с помощью *[getAxisType()](../../../api/library/controls/class.inputvrcontroller_cpp.md#getAxisType_int_int)*, найти индекс оси по её типу через *[findAxisByType()](../../../api/library/controls/class.inputvrcontroller_cpp.md#findAxisByType_int_int)* или получить значение состояния оси через *[getAxisByType()](../../../api/library/controls/class.inputvrcontroller_cpp.md#getAxisByType_int_float)*.


> **Примечание:** Статья о системе VR-ввода содержит несколько [examples of inputs](../../../vr_development/vr_input_cpp.md#openvr_input) для различных типов контроллеров, поддерживаемых OpenVR, и информацию о сопоставлении кнопок и осей в UNIGINE.


## Класс InputVRController

### Перечисления

## MODEL_TYPE

| Имя | Описание |
|---|---|
| **MODEL_TYPE_UNKNOWN** = 0 | Неизвестный контроллер. |
| **MODEL_TYPE_HTC_VIVE** = 1 | HTC Vive |
| **MODEL_TYPE_OCULUS_RIFT** = 2 | Oculus Rift |
| **MODEL_TYPE_VALVE_KNUCKLES** = 3 | Valve Index Knuckles |
| **NUM_MODEL_TYPES** = 4 | Общее количество моделей VR-контроллеров. |

## CONTROLLER_TYPE

| Имя | Описание |
|---|---|
| **CONTROLLER_TYPE_UNKNOWN** = 0 | Неизвестный тип контроллера |
| **CONTROLLER_TYPE_HAND_LEFT** = 1 | Контроллер левой руки |
| **CONTROLLER_TYPE_HAND_RIGHT** = 2 | Контроллер правой руки |
| **CONTROLLER_TYPE_TREADMILL** = 3 | Беговая дорожка |
| **NUM_CONTROLLER_TYPES** = 4 | Общее количество типов контроллеров |

## AXIS_TYPE

| Имя | Описание |
|---|---|
| **AXIS_TYPE_NONE** = 0 | Не указано |
| **AXIS_TYPE_TRACKPAD_X** = 1 | Ось X трекпада. Диапазон оси [-1;1]. |
| **AXIS_TYPE_TRACKPAD_Y** = 2 | Ось Y трекпада. Диапазон оси [-1;1]. |
| **AXIS_TYPE_TRACKPAD_FORCE** = 3 | Ось трекпада, учитывающая значение силы нажатия пальца. Диапазон оси [0;1]. |
| **AXIS_TYPE_JOYSTICK_X** = 4 | Ось X джойстика. Диапазон оси [-1;1]. |
| **AXIS_TYPE_JOYSTICK_Y** = 5 | Ось Y джойстика. Диапазон оси [-1;1]. |
| **AXIS_TYPE_JOYSTICK_FORCE** = 6 | Ось джойстика, учитывающая значение силы нажатия пальца. Диапазон оси [0;1]. |
| **AXIS_TYPE_GRIP_VALUE** = 7 | Ось захвата (grip), принимающая значение от 0 до 1. |
| **AXIS_TYPE_GRIP_FORCE** = 8 | Ось захвата, учитывающая значение силы нажатия пальца, превышающее 1. |
| **AXIS_TYPE_TRIGGER_VALUE** = 9 | Ось триггера, принимающая значение от 0 до 1. |
| **AXIS_TYPE_TRIGGER_FORCE** = 10 | Ось триггера, учитывающая значение силы нажатия пальца, превышающее 1. |
| **AXIS_TYPE_TRIGGER_CURL_VALUE** = 11 | Ось сгиба триггера, принимающая значение от 0 до 1. |
| **AXIS_TYPE_TRIGGER_CURL_FORCE** = 12 | Ось сгиба триггера, учитывающая значение силы нажатия пальца, превышающее 1. |
| **AXIS_TYPE_TRIGGER_SLIDE_VALUE** = 13 | Ось скольжения триггера, принимающая значение от 0 до 1. |
| **AXIS_TYPE_TRIGGER_SLIDE_FORCE** = 14 | Ось скольжения триггера, учитывающая значение силы нажатия пальца, превышающее 1. |
| **AXIS_TYPE_PINCH_VALUE** = 15 | Одномерный аналоговый компонент ввода, указывающий степень сведения пальца и большого пальца пользователем для выполнения жеста щипка (поддерживается WMR). |
| **AXIS_TYPE_GRASP_VALUE** = 16 | Одномерный аналоговый компонент ввода, указывающий, что пользователь сжимает кулак (поддерживается WMR). |
| **AXIS_TYPE_AIM_ACTIVATE_VALUE** = 17 | Одномерный аналоговый компонент ввода, указывающий, что пользователь активировал действие над целью, на которую он указывает позой прицеливания (поддерживается WMR). |
| **NUM_AXIS_TYPES** = 18 | Общее количество типов осей. |

### Методы класса

## InputVRController::MODEL_TYPE getModelType () const

Возвращает текущий тип модели VR-контроллера.
### Возвращаемое значение

Текущий тип модели контроллера.
## void setFilter ( float filter )

Устанавливает новое значение фильтра, используемое для коррекции текущего состояния аналоговой оси относительно предыдущего. Состояния осей интерполируются для стиков и триггеров.
### Аргументы

- *float* **filter** - Значение фильтра для интерполяции между состояниями осей. Указанное значение ограничивается диапазоном [0.0;1.0].

  - Значение фильтра 0.0 означает отсутствие интерполяции — текущее значение не корректируется.
  - Значение фильтра 1.0 означает, что вместо текущего состояния используется предыдущее.

## float getFilter () const

Возвращает текущее значение фильтра, используемое для коррекции текущего состояния аналоговой оси относительно предыдущего. Состояния осей интерполируются для стиков и триггеров.
### Возвращаемое значение

Текущее значение фильтра для интерполяции между состояниями осей. Указанное значение ограничивается диапазоном [0.0;1.0].
- Значение фильтра 0.0 означает отсутствие интерполяции — текущее значение не корректируется.
- Значение фильтра 1.0 означает, что вместо текущего состояния используется предыдущее.


## InputVRController::CONTROLLER_TYPE getControllerType () const

Возвращает текущий тип VR-контроллера.
### Возвращаемое значение

Текущий тип контроллера.
## int getNumAxes () const

Возвращает текущее количество осей, поддерживаемых VR-контроллером.
### Возвращаемое значение

Текущее количество осей.
## unsigned long long getSupportedButtonsMask () const

Возвращает текущие поддерживаемые кнопки для контроллера. Например, вы можете получить поддерживаемые кнопки и проверить доступность конкретной кнопки:
```cpp
InputVRControllerPtr device = Input::getVRControllerLeft();

// check if there is the X button on the controller
if (device->getSupportedButtonsMask() & (1ull << uint64_t(Input::VR_BUTTON_X)))
	return device->isButtonPressed(Input::VR_BUTTON_X);

```


### Возвращаемое значение

Текущая маска поддерживаемых кнопок.
## bool isUsingHandTracking () const

Возвращает текущее значение, указывающее, использует ли контроллер отслеживание рук, т.е. руки не держат контроллеры, и их движения могут отслеживаться.
> **Примечание:** Для устройств OpenXR.


### Возвращаемое значение

**true**, если используется отслеживание рук (контроллеры не удерживаются в руках); иначе **false**.
---

## InputVRController::AXIS_TYPE getAxisType ( int axis ) const

Возвращает тип заданной оси.
### Аргументы

- *int* **axis** - Номер оси.

### Возвращаемое значение

Тип оси.
## float getAxis ( int axis ) const

Возвращает значение состояния для заданной оси. Оно включает позицию VR-контроллера вдоль следующих осей: X, Y (двухосный контроллер) и Z (трёхосный контроллер). Когда VR-контроллер находится в центральном положении, значения осей X и Y равны нулю. Отрицательные значения означают влево или вниз; положительные значения означают вправо или вверх.
### Аргументы

- *int* **axis** - Номер оси.

### Возвращаемое значение

Значение в диапазоне [-1.0f; 1.0f].
## float getAxisDelta ( int axis ) const

Возвращает дельту оси — разницу между новым и текущим состоянием заданной оси.
### Аргументы

- *int* **axis** - Номер оси.

### Возвращаемое значение

Значение в диапазоне [-1.0f; 1.0f].
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
## bool isButtonTouchPressed ( Input::VR_BUTTON touch ) const

Возвращает значение, указывающее, затронута ли заданная кнопка.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **touch** - Кнопка.

### Возвращаемое значение

true, если кнопка затронута; иначе false.
## bool isButtonTouchDown ( Input::VR_BUTTON touch ) const

Возвращает значение, указывающее, была ли заданная кнопка касания "нажата" в текущем кадре.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **touch** -

### Возвращаемое значение

true, если кнопка касания была "нажата"; иначе false.
## bool isButtonTouchUp ( Input::VR_BUTTON touch ) const

Возвращает значение, указывающее, была ли заданная кнопка касания "отпущена" в текущем кадре.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **touch** -

### Возвращаемое значение

true, если кнопка касания была "отпущена"; иначе false.
## Ptr < InputEventVRButton > getButtonEvent ( Input::VR_BUTTON button ) const

Возвращает текущее обрабатываемое событие ввода кнопки VR-контроллера.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.

### Возвращаемое значение

Событие ввода кнопки VR-контроллера, или nullptr, если для указанной кнопки нет событий в текущем кадре.
## int getButtonEvents ( Input::VR_BUTTON button , Vector < Ptr < InputEventVRButton >> & OUT_events )

Возвращает количество событий ввода для указанной кнопки VR-контроллера и помещает события в указанный выходной буфер.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEventVRButton](../../../api/library/controls/class.inputeventvrbutton_cpp.md)>> &* **OUT_events** - Буфер с событиями ввода кнопок. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

Количество событий ввода для указанной кнопки VR-контроллера.
## Ptr < InputEventVRButtonTouch > getButtonTouchEvent ( Input::VR_BUTTON button ) const

Возвращает текущее обрабатываемое событие касания кнопки VR-контроллера.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.

### Возвращаемое значение

Событие касания кнопки VR-контроллера, или nullptr, если для указанной кнопки касания нет событий в текущем кадре.
## int getButtonTouchEvents ( Input::VR_BUTTON button , Vector < Ptr < InputEventVRButtonTouch >> & OUT_events )

Возвращает количество событий касания для указанной кнопки касания VR-контроллера и помещает события в указанный выходной буфер.
### Аргументы

- *[Input::VR_BUTTON](../../../api/library/controls/class.input_cpp.md#VR_BUTTON)* **button** - Кнопка.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEventVRButtonTouch](../../../api/library/controls/class.inputeventvrbuttontouch_cpp.md)>> &* **OUT_events** - Буфер с событиями касания кнопок. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

Количество событий ввода для указанной кнопки касания VR-контроллера.
## void stopHaptic ( )

Останавливает вибрационную обратную связь.
## void applyHaptic ( float amplitude = -1 , double duration_ms = -1 , float frequency_hz = -1 )

Применяет вибрационную обратную связь с указанными параметрами амплитуды, продолжительности и частоты.
### Аргументы

- *float* **amplitude** - Амплитуда вибрации в диапазоне от 0.0 до 1.0.
- *double* **duration_ms** - Продолжительность вибрации, в миллисекундах.
- *float* **frequency_hz** - Частота вибрации в Гц.

## float getAxisByType ( InputVRController::AXIS_TYPE axis_type ) const

Возвращает значение состояния для оси заданного типа. Оно включает позицию VR-контроллера вдоль осей X и Y (двухосный контроллер). Возвращаемое значение зависит от [axis type](#AXIS_TYPE).
### Аргументы

- *[InputVRController::AXIS_TYPE](../../../api/library/controls/class.inputvrcontroller_cpp.md#AXIS_TYPE)* **axis_type** - Тип оси.

### Возвращаемое значение

Значение в диапазоне [-1.0f;1.0f].
## int findAxisByType ( InputVRController::AXIS_TYPE axis_type ) const

Возвращает индекс оси по её типу.
### Аргументы

- *[InputVRController::AXIS_TYPE](../../../api/library/controls/class.inputvrcontroller_cpp.md#AXIS_TYPE)* **axis_type** - Тип оси.

### Возвращаемое значение

Индекс оси.
