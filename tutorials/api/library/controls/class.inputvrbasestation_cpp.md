# Класс Unigine::InputVRBaseStation (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

**Наследуется от:** InputVRDevice


Этот класс обрабатывает ввод от VR-базовой станции.


> **Примечание:** UNIGINE поддерживает базовые станции, совместимые только с устройствами OpenVR и Varjo.


## Класс InputVRBaseStation

### Перечисления

## MODEL_TYPE

| Имя | Описание |
|---|---|
| **MODEL_TYPE_UNKNOWN** = 0 | Неизвестная базовая станция |
| **MODEL_TYPE_HTC_VIVE** = 1 | HTC Vive |
| **MODEL_TYPE_VALVE** = 2 | Valve Index |
| **NUM_MODEL_TYPES** = 3 | Общее количество моделей VR-базовых станций. |

### Методы класса

---

## InputVRBaseStation::MODEL_TYPE getModelType ( ) const

Возвращает тип модели VR-базовой станции.
### Возвращаемое значение

Тип модели базовой станции.
