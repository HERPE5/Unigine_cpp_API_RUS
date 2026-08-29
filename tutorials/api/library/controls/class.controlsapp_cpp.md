# Unigine::ControlsApp Class (CPP)

**Header:** #include <UnigineControls.h>


> **Notice:** Этот класс устарел. Используйте вместо него класс *[Input](../../../api/library/controls/class.input_cpp.md)*.


## ControlsApp Class

### Members

## void setMouseDY ( float dy )

Задаёт новое изменение позиции указателя мыши на экране вдоль оси y за предыдущий кадр.
### Arguments

- *float* **dy** - Изменение позиции указателя мыши на экране вдоль оси y за предыдущий кадр.

## float getMouseDY () const

Возвращает текущее изменение позиции указателя мыши на экране вдоль оси y за предыдущий кадр.
### Return value

Текущее изменение позиции указателя мыши на экране вдоль оси y за предыдущий кадр.
## void setMouseDX ( float dx )

Задаёт новое изменение позиции указателя мыши на экране вдоль оси x за предыдущий кадр.
### Arguments

- *float* **dx** - Изменение позиции указателя мыши на экране вдоль оси x за предыдущий кадр.

## float getMouseDX () const

Возвращает текущее изменение позиции указателя мыши на экране вдоль оси x за предыдущий кадр.
### Return value

Текущее изменение позиции указателя мыши на экране вдоль оси x за предыдущий кадр.
## void setMouseSensitivity ( float sensitivity )

Задаёт новую чувствительность мыши, используемую для увеличения или уменьшения скорости движения мыши.
### Arguments

- *float* **sensitivity** - Чувствительность мыши, используемая для увеличения или уменьшения скорости движения мыши.

## float getMouseSensitivity () const

Возвращает текущую чувствительность мыши, используемую для увеличения или уменьшения скорости движения мыши.
### Return value

Текущая чувствительность мыши, используемая для увеличения или уменьшения скорости движения мыши.
## void setMouseInverse ( bool inverse )

Задаёт новое значение, указывающее, инвертированы ли движения мыши вперёд-назад (по оси y): когда мышь двигается вверх, камера смотрит вниз, а когда мышь двигается вниз, камера смотрит вверх. Этот режим доступен только для управления камерой.
### Arguments

- *bool* **inverse** - Установите **true**, чтобы включить инвертированное состояние мыши; **false** - чтобы отключить его.

## bool isMouseInverse () const

Возвращает текущее значение, указывающее, инвертированы ли движения мыши вперёд-назад (по оси y): когда мышь двигается вверх, камера смотрит вниз, а когда мышь двигается вниз, камера смотрит вверх. Этот режим доступен только для управления камерой.
### Return value

**true**, если инвертированное состояние мыши включено; иначе **false**.
## void setMouseRawInput ( bool input )

Задаёт новое значение, указывающее, какой тип данных мыши используется для управления камерой — необработанные ([Input::getMouseDeltaRaw()](../../../api/library/controls/class.input_cpp.md#getMouseDeltaRaw_ivec2)) или обработанные ОС ([Input::getMouseDeltaPosition()](../../../api/library/controls/class.input_cpp.md#getMouseDeltaPosition_ivec2)).
### Arguments

- *bool* **input** - Установите **true**, чтобы включить режим использования необработанных данных мыши для управления камерой; **false** - чтобы отключить его.

## bool isMouseRawInput () const

Возвращает текущее значение, указывающее, какой тип данных мыши используется для управления камерой — необработанные ([Input::getMouseDeltaRaw()](../../../api/library/controls/class.input_cpp.md#getMouseDeltaRaw_ivec2)) или обработанные ОС ([Input::getMouseDeltaPosition()](../../../api/library/controls/class.input_cpp.md#getMouseDeltaPosition_ivec2)).
### Return value

**true**, если режим использования необработанных данных мыши для управления камерой включён; иначе **false**.
## void setMouseEnabled ( bool enabled )

Задаёт новое значение, указывающее, включена ли мышь.
### Arguments

- *bool* **enabled** - Установите **true**, чтобы включить мышь; **false** - чтобы отключить её.

## bool isMouseEnabled () const

Возвращает текущее значение, указывающее, включена ли мышь.
### Return value

**true**, если мышь включена; иначе **false**.
## void setAlwaysRun ( int run = 0 )

Задаёт новое значение, указывающее, бежит ли игрок по умолчанию. Если игрок находится в этом режиме, элемент управления *Run* переключит его на ходьбу. Положительное целое число включает этот режим, 0 отключает его.
### Arguments

- *int* **run** - Положительное целое число, чтобы игрок бежал по умолчанию; иначе **0**.

## int getAlwaysRun () const

Возвращает текущее значение, указывающее, бежит ли игрок по умолчанию. Если игрок находится в этом режиме, элемент управления *Run* переключит его на ходьбу. Положительное целое число включает этот режим, 0 отключает его.
### Return value

Текущее положительное целое число, чтобы игрок бежал по умолчанию; иначе **0**.
## void setEnabled ( bool enabled )

Задаёт новое значение, указывающее, включена ли обработка ввода для текущего окна приложения.
### Arguments

- *bool* **enabled** - Установите **true**, чтобы включить обработку ввода для текущего окна приложения; **false** - чтобы отключить её.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включена ли обработка ввода для текущего окна приложения.
### Return value

**true**, если обработка ввода для текущего окна приложения включена; иначе **false**.
## void setMouseHandle ( Input::MOUSE_HANDLE handle )

Задаёт новый режим поведения мыши.
### Arguments

- *[Input::MOUSE_HANDLE](../../../api/library/controls/class.input_cpp.md#MOUSE_HANDLE)* **handle** - Режим поведения мыши, одно из значений [MOUSE_HANDLE_*](../../../api/library/controls/class.input_cpp.md#MOUSE_HANDLE).

## Input::MOUSE_HANDLE getMouseHandle () const

Возвращает текущий режим поведения мыши.
### Return value

Текущий режим поведения мыши, одно из значений [MOUSE_HANDLE_*](../../../api/library/controls/class.input_cpp.md#MOUSE_HANDLE).
## void setAutosave ( bool autosave )

Задаёт новое значение, указывающее, сохраняются ли текущие настройки конфигурации элементов управления автоматически в соответствующий файл конфигурации элементов управления (`configs/default.controls` по умолчанию) при загрузке, закрытии и сохранении мира, а также при завершении работы движка.
### Arguments

- *bool* **autosave** - Установите **true**, чтобы включить автоматическое сохранение текущих настроек конфигурации элементов управления; **false** - чтобы отключить его.

## bool isAutosave () const

Возвращает текущее значение, указывающее, сохраняются ли текущие настройки конфигурации элементов управления автоматически в соответствующий файл конфигурации элементов управления (`configs/default.controls` по умолчанию) при загрузке, закрытии и сохранении мира, а также при завершении работы движка.
### Return value

**true**, если автоматическое сохранение текущих настроек конфигурации элементов управления включено; иначе **false**.
## void setPath ( const char * path )

Задаёт новый путь к [controls configuration file](../../../code/configuration_file_cpp.md#controls) (по умолчанию: `configs/default.controls`). Путь может быть указан как абсолютный или относительно папки *[*-data_path*](../../../code/command_line.md#data_path)* или *<project_name>*, если задан *[*-project_name*](../../../code/command_line.md#project_name)*.
### Arguments

- *const char ** **path** - Путь к файлу конфигурации элементов управления.

## const char * getPath () const

Возвращает текущий путь к [controls configuration file](../../../code/configuration_file_cpp.md#controls) (по умолчанию: `configs/default.controls`). Путь может быть указан как абсолютный или относительно папки *[*-data_path*](../../../code/command_line.md#data_path)* или *<project_name>*, если задан *[*-project_name*](../../../code/command_line.md#project_name)*.
### Return value

Текущий путь к файлу конфигурации элементов управления.
---

## void setState ( int state , int value )

Обновляет состояние заданного элемента управления (включает или выключает его).
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.
- *int* **value** - Значение состояния: положительное значение, чтобы "нажать" элемент управления; 0, чтобы отпустить его.

## int getState ( int state )

Возвращает состояние заданного элемента управления.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.

### Return value

Значение состояния: положительное значение означает, что элемент управления "нажат"; 0 означает, что элемент управления отпущен.
## void setStateMouseButton ( int state , Input::MOUSE_BUTTON button )

Задаёт кнопку мыши, которая переключает заданное состояние (вкл/выкл). Этот параметр хранится в следующем файле конфигурации: **[*.controls](../../../code/configuration_file_cpp.md#controls)**.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.
- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Кнопка, переключающая состояние, один из предустановленных кодов [MOUSE_BUTTON_](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON).

## Input::MOUSE_BUTTON getStateMouseButton ( int state )

Возвращает кнопку мыши, которая переключает заданное состояние (вкл/выкл). Этот параметр хранится в следующем файле конфигурации: **[*.controls](../../../code/configuration_file_cpp.md#controls)**.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.

### Return value

Кнопка, переключающая состояние, один из предустановленных кодов [MOUSE_BUTTON_](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON).
## int isStateMouseButton ( Input::MOUSE_BUTTON button )

Возвращает значение, указывающее, назначена ли заданная кнопка состоянию.
### Arguments

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Кнопка, переключающая состояние, один из предустановленных кодов [MOUSE_BUTTON_](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON).

### Return value

**1**, если заданная кнопка назначена; иначе **0**.
## void getStateEvent ( int state )

Позволяет пользователю назначить клавишу или кнопку мыши заданному состоянию.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.

## int isStateEvent ( )

Возвращает значение, указывающее, успешно ли назначена клавиша или кнопка мыши состоянию.
### Return value

**1**, если клавиша или кнопка мыши уже назначена; иначе **0**.
## void setStateKey ( int state , Input::KEY key )

Задаёт клавишу, которая переключает заданное состояние (вкл/выкл). Этот параметр хранится в следующем файле конфигурации: **[*.controls](../../../code/configuration_file_cpp.md#controls)**.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.
- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Клавиша, переключающая состояние, один из предустановленных кодов [KEY_](../../../api/library/controls/class.input_cpp.md#KEY).

## Input::KEY getStateKey ( int state )

Возвращает клавишу, которая переключает заданное состояние (вкл/выкл). Этот параметр хранится в следующем файле конфигурации: **[*.controls](../../../code/configuration_file_cpp.md#controls)**.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.

### Return value

Клавиша, переключающая состояние, один из предустановленных кодов [KEY_](../../../api/library/controls/class.input_cpp.md#KEY).
## int isStateKey ( Input::KEY key )

Проверяет, действует ли уже заданная клавиша как элемент управления приложением. Это полезно, чтобы избежать конфликтов между элементами управления приложением и горячими клавишами.
### Arguments

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Клавиша, переключающая состояние, один из предустановленных кодов [KEY_](../../../api/library/controls/class.input_cpp.md#KEY).

### Return value

**1**, если клавиша назначена состоянию; иначе **0**.
## String getStateName ( int state )

Возвращает имя заданного состояния элемента управления.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.

### Return value

Имя заданного состояния элемента управления.
## String getStateInfo ( int state ) const

Возвращает информацию о заданном состоянии элемента управления.
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.

### Return value

Строка, содержащая информацию о заданном состоянии элемента управления.
## int clearState ( int state )

Возвращает состояние элемента управления и сбрасывает его в 0 (элемент управления не нажат).
### Arguments

- *int* **state** - Номер состояния элемента управления. Возможные значения находятся в диапазоне [ [STATE_FORWARD](../../../api/library/controls/class.controls_cpp.md#STATE_FORWARD);NUM_STATES]. Полный список доступных элементов управления см. в перечислении Unigine::Controls:: в конце статьи.

### Return value

**1**, если элемент управления нажат; иначе **0**.
## void setRemoveGrabKey ( Input::KEY key )

Задаёт новую клавишу, используемую для отключения [grab mode](../../../api/library/controls/class.input_cpp.md#setMouseGrab_int_void) указателя мыши (указатель мыши привязан к окну приложения). См. [этот пример](../../../code/usage/mouse_customization/index_cpp.md#defines) для получения дополнительной информации о режимах указателя мыши и их настройке.
### Arguments

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Клавиша, используемая для отключения [grab mode](../../../api/library/controls/class.input_cpp.md#setMouseGrab_int_void) указателя мыши, один из предустановленных кодов [KEY_](../../../api/library/controls/class.input_cpp.md#KEY).

## Input::KEY getRemoveGrabKey ( ) const

Возвращает клавишу, в данный момент используемую для отключения [grab mode](../../../api/library/controls/class.input_cpp.md#setMouseGrab_int_void) указателя мыши (указатель мыши привязан к окну приложения). См. [этот пример](../../../code/usage/mouse_customization/index_cpp.md#defines) для получения дополнительной информации о режимах указателя мыши и их настройке.
### Return value

Клавиша, используемая для отключения [grab mode](../../../api/library/controls/class.input_cpp.md#setMouseGrab_int_void) указателя мыши, один из предустановленных кодов [KEY_](../../../api/library/controls/class.input_cpp.md#KEY).
## int load ( )

***Console*:**`controls_config_load`Загружает настройки конфигурации элементов управления из [файла конфигурации элементов управления](../../../code/configuration_file_cpp.md) (`configs/default.controls` по умолчанию). Чтобы изменить путь к файлу конфигурации элементов управления, используйте метод [*setPath()*](#setPath_cstr_void).
### Return value

1, если настройки конфигурации элементов управления успешно загружены из файла; иначе 0.
## int save ( ) const

***Console*:**`controls_config_save`Сохраняет настройки конфигурации элементов управления в [файл конфигурации элементов управления](../../../code/configuration_file_cpp.md) (`configs/default.controls` по умолчанию). Чтобы изменить путь к файлу конфигурации элементов управления, используйте метод [*setPath()*](#setPath_cstr_void).
### Return value

1, если настройки конфигурации элементов управления успешно сохранены в файл; иначе 0.
