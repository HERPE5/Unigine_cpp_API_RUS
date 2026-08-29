# Класс Unigine::InputEvent (CPP)

**Заголовочный файл:** #include <UnigineInput.h>


Этот класс обрабатывает информацию о событии ввода.


## Класс InputEvent

### Перечисления

## TYPE

| Имя | Описание |
|---|---|
| **INPUT_EVENT** = 0 | Базовый тип. Не может быть создан. |
| **INPUT_EVENT_MOUSE_BUTTON** = 1 | Была нажата кнопка мыши. |
| **INPUT_EVENT_MOUSE_WHEEL** = 2 | Было прокручено колесо мыши. |
| **INPUT_EVENT_MOUSE_MOTION** = 3 | Мышь была перемещена. |
| **INPUT_EVENT_KEYBOARD** = 4 | Была нажата клавиша клавиатуры. |
| **INPUT_EVENT_TEXT** = 5 | Был введён текст. |
| **INPUT_EVENT_TOUCH** = 6 | Было выполнено касание сенсорного устройства. |
| **INPUT_EVENT_JOY_DEVICE** = 7 | Джойстик был подключён или отключён. |
| **INPUT_EVENT_JOY_BUTTON** = 8 | Была нажата кнопка джойстика. |
| **INPUT_EVENT_JOY_AXIS_MOTION** = 9 | Была изменена ось джойстика. |
| **INPUT_EVENT_JOY_POV_MOTION** = 10 | Был перемещён POV-переключатель джойстика. |
| **INPUT_EVENT_PAD_DEVICE** = 11 | Геймпад был подключён или отключён. |
| **INPUT_EVENT_PAD_BUTTON** = 12 | Была нажата кнопка геймпада. |
| **INPUT_EVENT_PAD_AXIS_MOTION** = 13 | Была изменена ось геймпада. |
| **INPUT_EVENT_PAD_TOUCH_MOTION** = 14 | Была выполнена сенсорная панель. |
| **INPUT_EVENT_VR_DEVICE** = 15 | VR-устройство было подключено или отключено. |
| **INPUT_EVENT_VR_BUTTON** = 16 | Была нажата кнопка VR-устройства. |
| **INPUT_EVENT_VR_BUTTON_TOUCH** = 17 | Было выполнено касание кнопки VR-устройства. |
| **INPUT_EVENT_VR_AXIS_MOTION** = 18 | Была изменена ось VR-устройства. |
| **INPUT_EVENT_SYSTEM** = 19 | Произошло системное событие (изменена раскладка клавиатуры или язык ввода). |
| **NUM_INPUT_EVENTS** = 20 | Счётчик событий ввода. |

### Методы класса

---

## InputEvent::TYPE getType ( ) const

Возвращает тип события ввода.
### Возвращаемое значение

Тип события ввода, одно из значений [TYPE.INPUT_EVENT](#TYPE).
## const char * getTypeName ( ) const

Возвращает имя типа события ввода.
### Возвращаемое значение

Имя типа события ввода.
## void setTimestamp ( unsigned int timestamp )

Устанавливает временную метку события.
### Аргументы

- *unsigned int* **timestamp** - Временная метка события, в миллисекундах.

## unsigned int getTimestamp ( ) const

Возвращает временную метку события.
### Возвращаемое значение

Временная метка события, в миллисекундах.
## void setMousePosition ( const Math:: ivec2 & pos )

Устанавливает позицию мыши для события.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **pos** - Позиция мыши.

## Math:: ivec2 getMousePosition ( ) const

Возвращает позицию мыши для события.
### Возвращаемое значение

Позиция мыши.
## unsigned long long getFrame ( ) const

Возвращает кадр движка, во время которого событие было отправлено от прокси в Input.
### Возвращаемое значение

Кадр движка, во время которого событие было отправлено от прокси в Input.
