# Класс Unigine::InputVRTracker (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputVRDevice


Этот класс обрабатывает ввод от VR-трекера.


> **Примечание:** VR-трекер должен иметь [world transformation](../../../api/library/controls/class.inputvrdevice_cpp.md#getWorldTransform_int_Mat4). Так вы можете, например, прикрепить трекер к камере или игроку для отслеживания его позиции в виртуальном мире.


> **Примечание:** UNIGINE поддерживает базовые станции, совместимые только с устройствами OpenVR и Varjo.


## Класс InputVRTracker

### Перечисления

## MODEL_TYPE

| Имя | Описание |
|---|---|
| **MODEL_TYPE_UNKNOWN** = 0 | Неизвестный VR-трекер. |
| **MODEL_TYPE_HTC_VIVE** = 1 | HTC Vive |
| **NUM_MODEL_TYPES** = 2 | Общее количество моделей VR-трекеров. |

### Методы класса

---

## InputVRTracker::MODEL_TYPE getModelType ( ) const

Возвращает тип модели VR-трекера.
### Возвращаемое значение

Тип модели трекера.
