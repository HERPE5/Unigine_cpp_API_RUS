# Unigine::EngineWindowViewport Class (CPP)

**Header:** #include <UnigineWindowManager.h>

**Inherits from:** EngineWindow


Класс для создания и управления window viewport'ами: настройка камер, указание доступных инструментов движка (консоль, профилировщик, визуализатор и т.д.), добавление виджетов в клиентскую область.


Чтобы создать window viewport движка, используйте один из конструкторов класса:

```cpp
// создаём окно движка указанного размера с указанным именем
EngineWindowViewportPtr window = EngineWindowViewport::create("New window", 580, 300);


```


Затем можно задать поведение window viewport и добавить виджеты в его клиентскую область:

```cpp
// устанавливаем window viewport как главный
window->setMain(true);

// включаем консоль, профилировщик и визуализатор для window viewport
window->setConsoleUsage(true);
window->setProfilerUsage(true);
window->setVisualizerUsage(true);

// добавляем виджеты в клиентскую область
window->addChild(WidgetLabel::create(window->getSelfGui(), String::format("This is %s window.", window->getTitle())));
window->addChild(WidgetButton::create(window->getSelfGui(), window->getTitle()), Gui::ALIGN_CENTER);


```


## EngineWindowViewport Class

### Методы класса

## Ptr < Viewport > getViewport () const

Возвращает текущий window viewport.
### Возвращаемое значение

Текущий window viewport.
## void setCamera ( const Ptr < Camera >& camera )

Устанавливает новую камеру, изображение с которой отрисовывается в window viewport движка. Это значение имеет более высокий приоритет, чем [main camera flag](#setMain_int_void).
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Camera](../../../api/library/rendering/class.camera_cpp.md)>&* **camera** - Камера, изображение с которой отрисовывается в окне движка.

## Ptr < Camera > getCamera () const

Возвращает текущую камеру, изображение с которой отрисовывается в window viewport движка. Это значение имеет более высокий приоритет, чем [main camera flag](#setMain_int_void).
### Возвращаемое значение

Текущая камера, изображение с которой отрисовывается в окне движка.
## void setMain ( bool main )

Устанавливает новое значение, указывающее, установлено ли окно как главное, чтобы использовать его размер в логике, отрисовывать в него с главного игрока, захватывать управление и т.д.
> **Notice:** Может быть несколько окон, установленных как главные, либо ни одного главного окна.


### Аргументы

- *bool* **main** - Установите **true**, чтобы сделать окно главным; **false** — чтобы отключить это.

## bool isMain () const

Возвращает текущее значение, указывающее, установлено ли окно как главное, чтобы использовать его размер в логике, отрисовывать в него с главного игрока, захватывать управление и т.д.
> **Notice:** Может быть несколько окон, установленных как главные, либо ни одного главного окна.


### Возвращаемое значение

**true**, если окно является главным; иначе **false**.
## void setConsoleUsage ( bool usage )

Устанавливает новое значение, указывающее, отображается ли консоль для окна, находящегося в данный момент в фокусе.
### Аргументы

- *bool* **usage** - Установите **true**, чтобы включить отображение консоли для окна в фокусе; **false** — чтобы отключить его.

## bool isConsoleUsage () const

Возвращает текущее значение, указывающее, отображается ли консоль для окна, находящегося в данный момент в фокусе.
### Возвращаемое значение

**true**, если отображение консоли для окна в фокусе включено; иначе **false**.
## void setProfilerUsage ( bool usage )

Устанавливает новое значение, указывающее, отображается ли профилировщик для окна, находящегося в данный момент в фокусе.
### Аргументы

- *bool* **usage** - Установите **true**, чтобы включить отображение профилировщика для окна в фокусе; **false** — чтобы отключить его.

## bool isProfilerUsage () const

Возвращает текущее значение, указывающее, отображается ли профилировщик для окна, находящегося в данный момент в фокусе.
### Возвращаемое значение

**true**, если отображение профилировщика для окна в фокусе включено; иначе **false**.
## void setVisualizerUsage ( bool usage )

Устанавливает новое значение, указывающее, отображается ли визуализатор для окна, находящегося в данный момент в фокусе.
### Аргументы

- *bool* **usage** - Установите **true**, чтобы включить отображение визуализатора для окна в фокусе; **false** — чтобы отключить его.

## bool isVisualizerUsage () const

Возвращает текущее значение, указывающее, отображается ли визуализатор для окна, находящегося в данный момент в фокусе.
### Возвращаемое значение

**true**, если отображение визуализатора для окна в фокусе включено; иначе **false**.
## void setSkipRenderEngine ( bool engine )

Устанавливает новое значение, указывающее, отключена ли отрисовка движком для текущего окна (даже если установлен [main camera flag](#setMain_int_void) или [user camera](#setCamera_Camera_void)). Это не отключает экземпляр Gui, поэтому виджеты и консоль остаются доступными.
### Аргументы

- *bool* **engine** - true, чтобы отключить отрисовку движком; false, чтобы включить её.

## bool isSkipRenderEngine () const

Возвращает текущее значение, указывающее, отключена ли отрисовка движком для текущего окна (даже если установлен [main camera flag](#setMain_int_void) или [user camera](#setCamera_Camera_void)). Это не отключает экземпляр Gui, поэтому виджеты и консоль остаются доступными.
### Возвращаемое значение

true, чтобы отключить отрисовку движком; false, чтобы включить её.
## bool isFullscreen () const

Возвращает текущее значение, указывающее, находится ли окно движка в полноэкранном состоянии. Вложенное окно будет извлечено из группы, если для него включён полноэкранный режим.
### Возвращаемое значение

true, если окно движка находится в полноэкранном состоянии, false, если оно в оконном режиме.
## void setMouseGrab ( bool grab )

Устанавливает новое значение, указывающее, привязан ли указатель мыши к window viewport движка.
> **Notice:** Этот метод можно применять к отдельному или родительскому окну, использование этого метода для вложенного окна недопустимо (будет возвращено false).

### Аргументы

- *bool* **grab** - Установите **true**, чтобы указатель не мог покинуть window viewport движка; **false** — чтобы отключить это.

## bool isMouseGrab () const

Возвращает текущее значение, указывающее, привязан ли указатель мыши к window viewport движка.
> **Notice:** Этот метод можно применять к отдельному или родительскому окну, использование этого метода для вложенного окна недопустимо (будет возвращено false).

### Возвращаемое значение

**true**, если указатель не может покинуть window viewport движка; иначе **false**.
## int getNumChildren () const

Возвращает текущее общее количество дочерних виджетов окна движка.
### Возвращаемое значение

Текущее общее количество дочерних виджетов окна движка.
## Event<const Ptr < EngineWindowViewport > &> getEventCustomRender () const

Подписка на это событие заставляет движок прекратить отрисовку сцены в этот viewport — используя этот подход, можно реализовать собственную отрисовку в viewport. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<EngineWindowViewport> & **viewport**)*
### Возвращаемое значение

Ссылка на событие.
## void setAspectCorrection ( bool correction )

Устанавливает новое значение, указывающее, включена ли коррекция соотношения сторон для window viewport движка.
### Аргументы

- *bool* **correction** - Установите **true**, чтобы включить коррекцию соотношения сторон; **false** — чтобы отключить её.

## bool isAspectCorrection () const

Возвращает текущее значение, указывающее, включена ли коррекция соотношения сторон для window viewport движка.
### Возвращаемое значение

**true**, если коррекция соотношения сторон включена; иначе **false**.
---

## static EngineWindowViewportPtr create ( const Math:: ivec2 & size , int flags = 0 )

Конструктор. Создаёт window viewport указанного размера с указанными флагами.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Размер окна (ширина и высота).
- *int* **flags** - Маска, содержащая [flags](../../../api/library/gui/class.enginewindow_cpp.md#FLAGS_MAIN) окна.

## static EngineWindowViewportPtr create ( int width , int height , int flags = 0 )

Конструктор. Создаёт window viewport указанного размера с указанными флагами.
### Аргументы

- *int* **width** - Ширина окна.
- *int* **height** - Высота окна.
- *int* **flags** - Маска, содержащая [flags](../../../api/library/gui/class.enginewindow_cpp.md#FLAGS_MAIN) окна.

## static EngineWindowViewportPtr create ( const char * window_title , int width , int height , int flags = 0 )

Конструктор. Создаёт window viewport указанного размера с указанным заголовком и флагами.
### Аргументы

- *const char ** **window_title** - Заголовок окна в кодировке UTF-8.
- *int* **width** - Ширина окна.
- *int* **height** - Высота окна.
- *int* **flags** - Маска, содержащая [flags](../../../api/library/gui/class.enginewindow_cpp.md#FLAGS_MAIN) окна.

## void disableFullscreen ( )

Отключает полноэкранный режим для окна в полноэкранном режиме и устанавливает фокус на это окно. Состояния и позиции остальных окон восстанавливаются.
> **Notice:** Этот метод нельзя применять к вложенным окнам.


## bool enableFullscreen ( int display = -1 , int mode = -1 )

Включает указанный полноэкранный режим для указанного дисплея. Состояния других отображаемых окон сохраняются, чтобы восстановить их состояния и позиции при [disabled](#disableFullscreen_void) полноэкранного режима. Вложенное окно будет извлечено из группы, если для него включён полноэкранный режим.
### Аргументы

- *int* **display** - Индекс дисплея.
- *int* **mode** - Индекс режима, поддерживаемого дисплеем.

### Возвращаемое значение

true, если указанный полноэкранный режим успешно включён для указанного дисплея; иначе false.
## void addChild ( const Ptr < Widget > & widget , int flags = -1 )

Добавляет указанный виджет как дочерний в клиентскую область окна движка.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **widget** - Добавляемый дочерний виджет.
- *int* **flags** - Флаги виджета: одна из предопределённых переменных [ALIGN_*](../../../api/library/gui/class.gui_cpp.md#ALIGN_BACKGROUND). Это опциональный параметр.

## void removeChild ( const Ptr < Widget > & widget )

Удаляет указанный виджет из окна движка.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **widget** - Удаляемый дочерний виджет.

## Ptr < Widget > getChild ( int index )

Возвращает дочерний виджет по его индексу.
### Аргументы

- *int* **index** - Индекс виджета.

### Возвращаемое значение

Дочерний виджет.
## bool isChild ( const Ptr < Widget > & widget )

Проверяет, является ли указанный виджет дочерним для текущего window viewport.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **widget** - Виджет.

### Возвращаемое значение

true, если виджет является дочерним для текущего window viewport; иначе false.
