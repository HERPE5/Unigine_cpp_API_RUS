# Unigine::Gui Class (CPP)

**Header:** #include <UnigineGui.h>


Создаёт GUI. Различные типы виджетов GUI могут быть добавлены в один из следующих контейнеров:

- В системный GUI (пользовательский интерфейс Unigine), который отрисовывается поверх окна приложения.
- В [GUI object](../../../api/library/objects/class.objectgui_cpp.md), размещённый в сцене. В этом случае можно применять любой постобработочный фильтр.

Значения по умолчанию, возвращаемые следующими методами, можно переопределить через [RC-файлы](../../../code/gui/rc.md), задающие пользовательский GUI.
## Gui Class

### Методы класса

## int getNumChildren () const

Возвращает текущее количество виджетов в GUI.
### Возвращаемое значение

Текущее количество виджетов в GUI.
## void setMouseGrab ( int grab )

Устанавливает новое значение, указывающее, привязан ли указатель мыши к GUI.
### Аргументы

- *int* **grab** - Значение, указывающее, привязан ли указатель мыши к GUI: 1, если указатель мыши не может покинуть GUI; иначе 0.

## int getMouseGrab () const

Возвращает текущее значение, указывающее, привязан ли указатель мыши к GUI.
### Возвращаемое значение

Текущее значение, указывающее, привязан ли указатель мыши к GUI: 1, если указатель мыши не может покинуть GUI; иначе 0.
## void setMouseCursor ( int cursor )

Устанавливает новое значение курсора мыши, одну из предопределённых переменных *CURSOR_**.
### Аргументы

- *int* **cursor** - Значение курсора мыши, одна из предопределённых переменных *CURSOR_**.

## int getMouseCursor () const

Возвращает текущее значение курсора мыши, одну из предопределённых переменных *CURSOR_**.
### Возвращаемое значение

Текущее значение курсора мыши, одна из предопределённых переменных *CURSOR_**.
## void setMouseSprite ( const Ptr < WidgetSprite >& sprite )

Устанавливает новый используемый пользовательский указатель мыши.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[WidgetSprite](../../../api/library/gui/class.widgetsprite_cpp.md)>&* **sprite** - Спрайт с пользовательским указателем мыши, либо NULL, если используется стандартный указатель мыши.

## Ptr < WidgetSprite > getMouseSprite () const

Возвращает текущий используемый пользовательский указатель мыши.
### Возвращаемое значение

Текущий спрайт с пользовательским указателем мыши, либо NULL, если используется стандартный указатель мыши.
## void setMouseEnabled ( bool enabled )

Устанавливает новое значение, указывающее, отрисовывается ли курсор мыши.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отрисовку курсора мыши; **false** — чтобы отключить её.

## bool isMouseEnabled () const

Возвращает текущее значение, указывающее, отрисовывается ли курсор мыши.
### Возвращаемое значение

**true**, если отрисовка курсора мыши включена; иначе **false**.
## void setToolTipTime ( float time )

Устанавливает новую задержку перед появлением подсказки.
### Аргументы

- *float* **time** - Задержка перед появлением подсказки, в циклах в секунду.

## float getToolTipTime () const

Возвращает текущую задержку перед появлением подсказки.
### Возвращаемое значение

Текущая задержка перед появлением подсказки, в циклах в секунду.
## void setToolTipAlpha ( float alpha )

Устанавливает новое значение альфа-канала подсказки.
### Аргументы

- *float* **alpha** - Значение альфа-канала подсказки.

## float getToolTipAlpha () const

Возвращает текущее значение альфа-канала подсказки.
### Возвращаемое значение

Текущее значение альфа-канала подсказки.
## void setToolTipColor ( const Math:: vec4 & color )

Устанавливает новый цвет шрифта подсказки.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет шрифта подсказки. Значение по умолчанию эквивалентно **#000000** (чёрный).

## Math:: vec4 getToolTipColor () const

Возвращает текущий цвет шрифта подсказки.
### Возвращаемое значение

Текущий цвет шрифта подсказки. Значение по умолчанию эквивалентно **#000000** (чёрный).
## void setToolTipWidth ( int width )

Устанавливает новую ширину подсказки.
### Аргументы

- *int* **width** - Ширина подсказки.

## int getToolTipWidth () const

Возвращает текущую ширину подсказки.
### Возвращаемое значение

Текущая ширина подсказки.
## void setToolTipSize ( int size )

Устанавливает новый размер шрифта подсказки.
### Аргументы

- *int* **size** - Размер шрифта подсказки.

## int getToolTipSize () const

Возвращает текущий размер шрифта подсказки.
### Возвращаемое значение

Текущий размер шрифта подсказки.
## void setToolTipEnabled ( bool enabled )

Устанавливает новое значение, указывающее, доступны ли подсказки.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отображение подсказок; **false** — чтобы отключить его.

## bool isToolTipEnabled () const

Возвращает текущее значение, указывающее, доступны ли подсказки.
### Возвращаемое значение

**true**, если отображение подсказок включено; иначе **false**.
## void setTransparentAlpha ( )

Устанавливает новое значение альфа-канала прозрачного виджета. Виджет является прозрачным, если он использует смешивание (blending).
### Аргументы

- **alpha** - Значение альфа-канала прозрачного виджета. **0** означает полную прозрачность.

## getTransparentAlpha () const

Возвращает текущее значение альфа-канала прозрачного виджета. Виджет является прозрачным, если он использует смешивание (blending).
### Возвращаемое значение

Текущее значение альфа-канала прозрачного виджета. **0** означает полную прозрачность.
## void setTransparentColor ( const Math:: vec4 & color )

Устанавливает новый цвет шрифта прозрачного виджета. Виджет является прозрачным, если он использует смешивание (blending).
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет шрифта прозрачного виджета. Значение по умолчанию эквивалентно **#869caa** (светло-голубоватый).

## Math:: vec4 getTransparentColor () const

Возвращает текущий цвет шрифта прозрачного виджета. Виджет является прозрачным, если он использует смешивание (blending).
### Возвращаемое значение

Текущий цвет шрифта прозрачного виджета. Значение по умолчанию эквивалентно **#869caa** (светло-голубоватый).
## void setTransparentEnabled ( bool enabled )

Устанавливает новое значение, указывающее, может ли виджет при необходимости отрисовываться как [transparent](../../../code/gui/rc.md#transparent) (т.е. соответствующим образом менять цвет). Например, это может указывать, является ли выпадающий список combobox прозрачным или нет.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отрисовку виджета как прозрачного; **false** — чтобы отключить её.

## bool isTransparentEnabled () const

Возвращает текущее значение, указывающее, может ли виджет при необходимости отрисовываться как [transparent](../../../code/gui/rc.md#transparent) (т.е. соответствующим образом менять цвет). Например, это может указывать, является ли выпадающий список combobox прозрачным или нет.
### Возвращаемое значение

**true**, если отрисовка виджета как прозрачного включена; иначе **false**.
## void setDisabledAlpha ( float alpha )

Устанавливает новое значение альфа-канала отключённого виджета.
### Аргументы

- *float* **alpha** - Значение альфа-канала отключённого виджета. **0** означает полную прозрачность.

## float getDisabledAlpha () const

Возвращает текущее значение альфа-канала отключённого виджета.
### Возвращаемое значение

Текущее значение альфа-канала отключённого виджета. **0** означает полную прозрачность.
## void setDisabledColor ( const Math:: vec4 & color )

Устанавливает новый цвет шрифта отключённого виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет шрифта отключённого виджета. Значение по умолчанию эквивалентно **#869caa** (светло-голубоватый).

## Math:: vec4 getDisabledColor () const

Возвращает текущий цвет шрифта отключённого виджета.
### Возвращаемое значение

Текущий цвет шрифта отключённого виджета. Значение по умолчанию эквивалентно **#869caa** (светло-голубоватый).
## void setDisabledEnabled ( bool enabled )

Устанавливает новое значение, указывающее, может ли виджет при необходимости отрисовываться как [disabled](../../../code/gui/rc.md#disabled) (т.е. соответствующим образом менять цвет).
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отрисовку виджета как отключённого; **false** — чтобы отключить её.

## bool isDisabledEnabled () const

Возвращает текущее значение, указывающее, может ли виджет при необходимости отрисовываться как [disabled](../../../code/gui/rc.md#disabled) (т.е. соответствующим образом менять цвет).
### Возвращаемое значение

**true**, если отрисовка виджета как отключённого включена; иначе **false**.
## void setFocusedAlpha ( float alpha )

Устанавливает новое значение альфа-канала виджета в фокусе.
### Аргументы

- *float* **alpha** - Значение альфа-канала виджета в фокусе. **0** означает полную прозрачность.

## float getFocusedAlpha () const

Возвращает текущее значение альфа-канала виджета в фокусе.
### Возвращаемое значение

Текущее значение альфа-канала виджета в фокусе. **0** означает полную прозрачность.
## void setFocusedColor ( const Math:: vec4 & color )

Устанавливает новый цвет шрифта виджета в фокусе.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет шрифта виджета в фокусе. Значение по умолчанию эквивалентно **#ffffff** (белый).

## Math:: vec4 getFocusedColor () const

Возвращает текущий цвет шрифта виджета в фокусе.
### Возвращаемое значение

Текущий цвет шрифта виджета в фокусе. Значение по умолчанию эквивалентно **#ffffff** (белый).
## void setFocusedEnabled ( bool enabled )

Устанавливает новое значение, указывающее, может ли виджет при необходимости отрисовываться как [focused](../../../code/gui/rc.md#focused) (т.е. соответствующим образом менять цвет).
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить отрисовку виджета как находящегося в фокусе; **false** — чтобы отключить её.

## bool isFocusedEnabled () const

Возвращает текущее значение, указывающее, может ли виджет при необходимости отрисовываться как [focused](../../../code/gui/rc.md#focused) (т.е. соответствующим образом менять цвет).
### Возвращаемое значение

**true**, если отрисовка виджета как находящегося в фокусе включена; иначе **false**.
## void setDefaultAlpha ( float alpha )

Устанавливает новое стандартное значение альфа-канала виджета.
### Аргументы

- *float* **alpha** - Стандартное значение альфа-канала виджета. **0** означает полную прозрачность.

## float getDefaultAlpha () const

Возвращает текущее стандартное значение альфа-канала виджета.
### Возвращаемое значение

Текущее стандартное значение альфа-канала виджета. **0** означает полную прозрачность.
## void setDefaultColor ( const Math:: vec4 & color )

Устанавливает новый стандартный цвет шрифта виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Стандартный цвет шрифта виджета. Значение по умолчанию эквивалентно **#ddddff** (сине-белый).

## Math:: vec4 getDefaultColor () const

Возвращает текущий стандартный цвет шрифта виджета.
### Возвращаемое значение

Текущий стандартный цвет шрифта виджета. Значение по умолчанию эквивалентно **#ddddff** (сине-белый).
## void setDefaultSize ( int size )

Устанавливает новый стандартный размер шрифта виджета.
### Аргументы

- *int* **size** - Стандартный размер шрифта виджета.

## int getDefaultSize () const

Возвращает текущий стандартный размер шрифта виджета.
### Возвращаемое значение

Текущий стандартный размер шрифта виджета.
## void setFadeOutSpeed ( float speed )

Устанавливает новую продолжительность анимации затухания, воспроизводимой при потере виджетом фокуса.
### Аргументы

- *float* **speed** - Продолжительность в циклах в секунду, например, **4** означает, что продолжительность составляет **1/4** секунды.

## float getFadeOutSpeed () const

Возвращает текущую продолжительность анимации затухания, воспроизводимой при потере виджетом фокуса.
### Возвращаемое значение

Текущая продолжительность в циклах в секунду, например, **4** означает, что продолжительность составляет **1/4** секунды.
## void setFadeInSpeed ( float speed )

Устанавливает новую продолжительность анимации появления, воспроизводимой при получении виджетом фокуса.
### Аргументы

- *float* **speed** - Продолжительность в циклах в секунду, например, **8** означает, что продолжительность составляет **1/8** секунды.

## float getFadeInSpeed () const

Возвращает текущую продолжительность анимации появления, воспроизводимой при получении виджетом фокуса.
### Возвращаемое значение

Текущая продолжительность в циклах в секунду, например, **8** означает, что продолжительность составляет **1/8** секунды.
## void setExposeSpeed ( float speed = 1024 )

Устанавливает новую продолжительность анимации, воспроизводимой при появлении виджета.
### Аргументы

- *float* **speed** - Продолжительность в циклах в секунду. Например, **6** означает, что продолжительность составляет **1/6** секунды. Значение меньше или равное 0 означает, что плавные анимации не применяются.

## float getExposeSpeed () const

Возвращает текущую продолжительность анимации, воспроизводимой при появлении виджета.
### Возвращаемое значение

Текущая продолжительность в циклах в секунду. Например, **6** означает, что продолжительность составляет **1/6** секунды. Значение меньше или равное 0 означает, что плавные анимации не применяются.
## void setTransform ( const Math:: mat4 & transform )

Устанавливает новую глобальную матрицу трансформации GUI. Эту 2D-матрицу можно наклонять, вращать, перемещать или изменять множеством способов в 3D-пространстве.
### Аргументы

- *const  Math::[mat4](../../../api/library/math/class.mat4_cpp.md)&* **transform** - Глобальная матрица трансформации GUI.

## Math:: mat4 getTransform () const

Возвращает текущую глобальную матрицу трансформации GUI. Эту 2D-матрицу можно наклонять, вращать, перемещать или изменять множеством способов в 3D-пространстве.
### Возвращаемое значение

Текущая глобальная матрица трансформации GUI.
## void setColor ( const Math:: vec4 & color )

Устанавливает новый цвет глобального цветового множителя.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет глобального цветового множителя. Значение по умолчанию эквивалентно #ffffff (белый).

## Math:: vec4 getColor () const

Возвращает текущий цвет глобального цветового множителя.
### Возвращаемое значение

Текущий цвет глобального цветового множителя. Значение по умолчанию эквивалентно #ffffff (белый).
## int getHeight () const

Возвращает текущую высоту экрана.
### Возвращаемое значение

Текущая высота экрана, в [logical units](../../../principles/dpi/index.md).
## int getWidth () const

Возвращает текущую ширину экрана.
### Возвращаемое значение

Текущая ширина экрана, в [logical units](../../../principles/dpi/index.md).
## void setHidden ( bool hidden )

Устанавливает новое значение, указывающее, отрисовывается ли виджет видимым.
### Аргументы

- *bool* **hidden** - Установите **true**, чтобы включить отрисовку виджета как видимого; **false** — чтобы отключить её.

## bool isHidden () const

Возвращает текущее значение, указывающее, отрисовывается ли виджет видимым.
### Возвращаемое значение

**true**, если отрисовка виджета как видимого включена; иначе **false**.
## void setEnabled ( bool enabled )

Устанавливает новое значение, указывающее, включён ли GUI.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить GUI; **false** — чтобы отключить его.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включён ли GUI.
### Возвращаемое значение

**true**, если GUI включён; иначе **false**.
## bool isActive () const

Возвращает текущее значение, указывающее, находится ли какой-либо виджет в GUI в фокусе.
### Возвращаемое значение

**true**, если какой-либо виджет в GUI находится в фокусе; иначе **false**.
## Ptr < WidgetVBox > getVBox () const

Возвращает текущий корневой виджет GUI.
### Возвращаемое значение

Текущий корневой виджет GUI.
## Ptr < Widget > getPermanentFocus () const

Возвращает текущий виджет, который всегда находится в фокусе.
### Возвращаемое значение

Текущий виджет, который всегда находится в фокусе.
## Ptr < Widget > getOverlappedFocus () const

Возвращает текущий виджет, расположенный под виджетом, находящимся в фокусе в данный момент.
### Возвращаемое значение

Текущий перекрытый виджет.
## Ptr < Widget > getFocus () const

Возвращает текущий виджет, находящийся в данный момент в фокусе.
### Возвращаемое значение

Текущий виджет, находящийся в данный момент в фокусе.
## int getMouseDY () const

Возвращает текущую разницу между предыдущей позицией указателя мыши и текущей вдоль оси Y в [logical units](../../../principles/dpi/index.md).
### Возвращаемое значение

Текущая разница между предыдущей позицией указателя мыши и текущей вдоль оси Y в [logical units](../../../principles/dpi/index.md).
## int getMouseDX () const

Возвращает текущую разницу между предыдущей позицией указателя мыши и текущей вдоль оси X в [logical units](../../../principles/dpi/index.md).
### Возвращаемое значение

Текущая разница между предыдущей позицией указателя мыши и текущей вдоль оси X в [logical units](../../../principles/dpi/index.md).
## int getMouseY () const

Возвращает текущую координату Y указателя мыши в системе координат окна приложения в [logical units](../../../principles/dpi/index.md).
### Возвращаемое значение

Текущая координата Y указателя мыши в системе координат окна приложения в [logical units](../../../principles/dpi/index.md).
## int getMouseX () const

Возвращает текущую координату X указателя мыши в системе координат окна приложения в [logical units](../../../principles/dpi/index.md).
### Возвращаемое значение

Текущая координата X указателя мыши в системе координат окна приложения в [logical units](../../../principles/dpi/index.md).
## void setToolTipY ( int y )

Устанавливает новую позицию подсказки вдоль оси Y.
### Аргументы

- *int* **y** - Позиция подсказки вдоль оси Y.

## int getToolTipY () const

Возвращает текущую позицию подсказки вдоль оси Y.
### Возвращаемое значение

Текущая позиция подсказки вдоль оси Y.
## void setToolTipX ( int x )

Устанавливает новую позицию подсказки вдоль оси X.
### Аргументы

- *int* **x** - Позиция подсказки вдоль оси X.

## int getToolTipX () const

Возвращает текущую позицию подсказки вдоль оси X.
### Возвращаемое значение

Текущая позиция подсказки вдоль оси X.
## void setToolTipText ( const char * text )

Устанавливает новый текст подсказки GUI.
### Аргументы

- *const char ** **text** - Текст подсказки GUI.

## const char * getToolTipText () const

Возвращает текущий текст подсказки GUI.
### Возвращаемое значение

Текущий текст подсказки GUI.
## bool isUnderCursor () const

Возвращает текущее значение, указывающее, находится ли объект GUI под курсором.
### Возвращаемое значение

**true**, если объект GUI находится под курсором; иначе **false**.
## int getMouseWheelHorizontal () const

Возвращает текущее значение горизонтальной прокрутки мыши.
### Возвращаемое значение

Текущее значение горизонтальной прокрутки мыши в диапазоне [-1;1].
## int getMouseWheel () const

Возвращает текущее значение прокрутки мыши. Отрицательные значения соответствуют прокрутке вниз; положительные значения соответствуют прокрутке вверх; значение равно нулю, если колесо мыши не прокручивается.
### Возвращаемое значение

Текущее значение прокрутки мыши в диапазоне [-1;1].
## void setMouseShow ( bool show )

Устанавливает новое значение, указывающее, отображается ли системный указатель мыши ОС, либо используется только курсор приложения.
### Аргументы

- *bool* **show** - Установите **true**, чтобы включить отображение системного указателя мыши ОС; **false** — чтобы отключить его.

## bool isMouseShow () const

Возвращает текущее значение, указывающее, отображается ли системный указатель мыши ОС, либо используется только курсор приложения.
### Возвращаемое значение

**true**, если отображение системного указателя мыши ОС включено; иначе **false**.
## void setMouseButtons ( int buttons )

Устанавливает новые кнопки мыши, ввод от которых принимается.
### Аргументы

- *int* **buttons** - *[Input::MOUSE_BUTTON_LEFT](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON_LEFT)*, или *[Input::MOUSE_BUTTON_RIGHT](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON_RIGHT)*, или *[Input::MOUSE_BUTTON_MIDDLE](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON_MIDDLE)*.

## int getMouseButtons () const

Возвращает текущие кнопки мыши, ввод от которых принимается.
### Возвращаемое значение

Текущий *[Input::MOUSE_BUTTON_LEFT](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON_LEFT)*, или *[Input::MOUSE_BUTTON_RIGHT](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON_RIGHT)*, или *[Input::MOUSE_BUTTON_MIDDLE](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON_MIDDLE)*.
## void setWorldObject ( bool object )

Устанавливает новое значение, указывающее, доступен ли объект GUI в иерархии и отрисовывается ли он как объект сцены, либо он должен иметь дескриптор окна.
### Аргументы

- *bool* **object** - Установите **true**, чтобы объект GUI был доступен в иерархии и отрисовывался как объект сцены; **false** — чтобы отключить это.

## bool isWorldObject () const

Возвращает текущее значение, указывающее, доступен ли объект GUI в иерархии и отрисовывается ли он как объект сцены, либо он должен иметь дескриптор окна.
### Возвращаемое значение

**true**, если объект GUI доступен в иерархии и отрисовывается как объект сцены; иначе **false**.
## void setWinHandle ( unsigned long long handle )

Устанавливает новый дескриптор окна движка.
### Аргументы

- *unsigned long long* **handle** - Дескриптор окна.

## unsigned long long getWinHandle () const

Возвращает текущий дескриптор окна движка.
### Возвращаемое значение

Текущий дескриптор окна.
## void setPosition ( const Math:: ivec2 & position )

Устанавливает новую позицию объекта GUI (верхний левый угол) в экранных координатах.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)&* **position** - Позиция объекта GUI (верхний левый угол) в экранных координатах.

## Math:: ivec2 getPosition () const

Возвращает текущую позицию объекта GUI (верхний левый угол) в экранных координатах.
### Возвращаемое значение

Текущая позиция объекта GUI (верхний левый угол) в экранных координатах.
## void setSize ( const Math:: ivec2 & size )

Устанавливает новый размер объекта GUI в [logical units](../../../principles/dpi/index.md).
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)&* **size** - Размер объекта GUI (ширина и высота) в [logical units](../../../principles/dpi/index.md).

## Math:: ivec2 getSize () const

Возвращает текущий размер объекта GUI в [logical units](../../../principles/dpi/index.md).
### Возвращаемое значение

Текущий размер объекта GUI (ширина и высота) в [logical units](../../../principles/dpi/index.md).
## void setDpiScale ( float scale )

Устанавливает новый DPI-масштаб, применяемый к GUI.
### Аргументы

- *float* **scale** - DPI-масштаб, применяемый к GUI.

## float getDpiScale () const

Возвращает текущий DPI-масштаб, применяемый к GUI.
### Возвращаемое значение

Текущий DPI-масштаб, применяемый к GUI.
## Event<> getEventUpdate () const

Событие, срабатывающее при обновлении GUI. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler()*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Update
void update_event_handler()
{
	Log::message("\Обработка события Update\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections update_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventUpdate().connect(update_event_connections, update_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventUpdate().connect(update_event_connections, []() {
		Log::message("\Обработка события Update (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
update_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection update_event_connection;

// подписываемся на событие Update с функцией-обработчиком, сохраняя соединение
publisher->getEventUpdate().connect(update_event_connection, update_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
update_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
update_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Update через соединение
update_event_connection.disconnect();

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

	// Обработчик события Update, реализованный как член класса
	void event_handler()
	{
		Log::message("\Обработка события Update\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventUpdate().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId update_handler_id;

// подписываемся на событие Update с лямбда-обработчиком, сохраняя идентификатор соединения
update_handler_id = publisher->getEventUpdate().connect(e_connections, []() {
		Log::message("\Обработка события Update (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventUpdate().disconnect(update_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Update при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventUpdate().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventUpdate().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## Ptr < Gui > getCurrent ( )

Returns the current GUI instance.
### Возвращаемое значение

Current GUI instance.
## Ptr < Widget > getChild ( int num ) const

Returns a child widget with a given number.
### Аргументы

- *int* **num** - Child widget number.

### Возвращаемое значение

Child widget.
## int isChild ( const Ptr < Widget > & widget ) const

Checks if a given widget belongs to the GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **widget** - Widget to check.

### Возвращаемое значение

true if the widget belongs to the GUI; otherwise, false.
## void setFocusedPermanent ( bool permanent )

Changes the permanent color of the focused widget.
### Аргументы

- *bool* **permanent** - true - a font color is overridden with the global GUI focused color; false - a font color is unchanged.

## bool isFocusedPermanent ( ) const

Returns a value indicating if the permanent color of the focused widget is changed.
### Возвращаемое значение

true if the font color is overridden with the global GUI focused color; false if the font color is unchanged.
## int getKeyActivity ( unsigned int key ) const

Checks if a given key already has a special purpose for the widget in focus.
### Аргументы

- *unsigned int* **key** - One of the standard ASCII control codes or one of the *[KEY_*](../../../api/library/controls/class.input_cpp.md#KEY_UNKNOWN)* pre-defined variables.

### Возвращаемое значение

**1** if the key cannot be used; otherwise, **0**.
## bool setResource ( const char * name )

Changes the resource skin file used in the system GUI.
### Аргументы

- *const char ** **name** - Path to the rc file.

### Возвращаемое значение

true if the resource file is successfully changed; otherwise, false.
## void setToolTip ( int x , int y , const char * str )

Sets a tooltip.
### Аргументы

- *int* **x** - X coordinate of the tooltip position.
- *int* **y** - Y coordinate of the tooltip position.
- *const char ** **str** - ToolTip text.

## int getToolTipHeight ( const char * str ) const

Returns a height of the given tooltip.
> **Notice:** Height of a single-line tooltip is equal to 21 pixels.


### Аргументы

- *const char ** **str** - A tooltip text.

### Возвращаемое значение

Height of the given tooltip (in pixels).
## int getToolTipWidth ( const char * str ) const

Возвращает текущую ширину подсказки.
### Аргументы

- *const char ** **str** - A tooltip text.

### Возвращаемое значение

Width of the tooltip.
## void addChild ( const Ptr < Widget > & widget , int flags = 0 )

Adds a given widget to the GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **widget** - Widget to add.
- *int* **flags** - One of the ALIGN_* pre-defined variables. This is an optional parameter.

## bool addDictionary ( const char * name , const char * language = 0 )

Adds a new dictionary with localized interface strings. Dictionaries cannot be modified in run-time.
### Аргументы

- *const char ** **name** - Path to the dictionary file.
- *const char ** **language** - Name of the dictionary language.

### Возвращаемое значение

Returns **1** if the dictionary is added successfully; otherwise, **0**.
## void clearDictionaries ( )

Clears all dictionaries.
## bool clearTexture ( const char * name )

Clears the specified GUI texture file cache.
### Аргументы

- *const char ** **name** - Texture name.

### Возвращаемое значение

1 if the texture is successfully cleared; otherwise, 0.
## Ptr&lt;Gui&gt; create ( const char * name = 0 )

GUI constructor.
### Аргументы

- *const char ** **name** - GUI skin name.

### Возвращаемое значение

Pointer to the created GUI.
## void destroy ( )

Destroys all GUI resources.
## void disable ( )

Disables GUI rendering.
## void enable ( )

Enables GUI rendering.
## bool hasTranslation ( const char * arg1 ) const

Returns a value indicating if there is translation for a given string in the localization dictionary.
### Аргументы

- *const char ** **arg1** - Проверяемая строка.

### Возвращаемое значение

true, если для указанной строки есть перевод; иначе false.
## Math:: vec4 parseColor ( const char * str ) const

Преобразует строку цвета в веб-формате (RRGGBB / #RRGGBB или RRGGBBAA / #RRGGBBAA) в её эквивалент *vec4*.
### Аргументы

- *const char ** **str** - Строка цвета в веб-формате.

### Возвращаемое значение

Значение цвета в виде вектора *vec4* (R, G, B, A).
## void removeChild ( const Ptr < Widget > & widget )

Удаляет указанный виджет из GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **widget** - Удаляемый дочерний виджет.

## void removeFocus ( )

Снимает фокус с GUI.
## void replaceChild ( const Ptr < Widget > & widget , const Ptr < Widget > & old_widget , int flags = 0 )

Заменяет указанный виджет в GUI другим виджетом.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **widget** - Заменяющий виджет.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **old_widget** - Заменяемый виджет.
- *int* **flags** - Одна из предопределённых переменных *ALIGN_**. Это опциональный параметр.

## bool saveDictionary ( const char * name , const char * language = 0 )

Сохраняет текущий словарь на диске. Эта функция может использоваться для сохранения текущего загруженного словаря в другой файл.
### Аргументы

- *const char ** **name** - Имя языка словаря.
- *const char ** **language** - Имя языка словаря.

### Возвращаемое значение

true, если словарь успешно сохранён; иначе false.
## const char * translate ( const char * str )

Возвращает исходную строку, переведённую с помощью словаря.
### Аргументы

- *const char ** **str** - Переводимая строка (исходная).

### Возвращаемое значение

Целевая (переведённая) строка, если она найдена в словаре локализации; иначе исходная строка.
## void update ( )

Обновляет GUI.
## void preRender ( )

Метод, выполняемый после *update()* и перед функцией *render()*. Этот метод используется для выполнения необходимых подготовок к отрисовке (например, подготовки текстуры) после *update()* и вызывается автоматически для *[WidgetSpriteViewport](../../../api/library/gui/class.widgetspriteviewport_cpp.md)* и *[WidgetSpriteNode](../../../api/library/gui/class.widgetspriteviewport_cpp.md)*, чтобы обеспечить корректную отрисовку виджетов во время *render()*. Если вы реализуете пользовательский GUI или виджеты с помощью класса *[WidgetExtern](../../../api/library/gui/class.widgetextern_cpp.md)*, вам следует поместить все такие подготовки к отрисовке в **[WidgetExternBase::preRender()](../../../api/library/gui/class.widgetexternbase_cpp.md#preRender_void)** и вызывать *preRender()* для GUI вручную после *update()*.
## void render ( )

Отрисовывает GUI.
## void render ( int custom_mouse_buttons )

Отрисовывает GUI.
### Аргументы

- *int* **custom_mouse_buttons** - Нажатая кнопка мыши.

## void updateHierarchy ( )

Обновляет иерархию для всех виджетов — виджеты выравниваются, расширяются до необходимых размеров, а затем обновляются их позиции. Обновление иерархии может потребоваться, например, для получения экранной позиции сразу после добавления виджета в иерархию.
## bool isRenderingBootScreen ( )

Возвращает значение, указывающее, отрисовывает ли GUI в данный момент [boot screen](../../../code/gui/screens/index.md#boot).
### Возвращаемое значение

true, если GUI в данный момент отрисовывает [boot screen](../../../code/gui/screens/index.md#boot); иначе false.
## bool isRenderingSplashScreen ( )

Возвращает значение, указывающее, отрисовывает ли GUI в данный момент [splash screen](../../../code/gui/screens/index.md#splash).
### Возвращаемое значение

true, если GUI в данный момент отрисовывает [splash screen](../../../code/gui/screens/index.md#splash); иначе false.
## bool isRenderingLoadingScreen ( )

Возвращает значение, указывающее, отрисовывает ли GUI в данный момент [loading screen](../../../code/gui/screens/index.md#loading).
### Возвращаемое значение

true, если GUI в данный момент отрисовывает [loading screen](../../../code/gui/screens/index.md#loading); иначе false.
## void focusGained ( )

Фокус устанавливается на объект GUI.
## void focusLost ( )

Фокус снимается с GUI.
## bool isHover ( int global_pos_x , int global_pos_y ) const

Возвращает значение, указывающее, находится ли курсор над объектом GUI.
### Аргументы

- *int* **global_pos_x** - Координата X курсора в глобальных координатах.
- *int* **global_pos_y** - Координата Y курсора в глобальных координатах.

### Возвращаемое значение

true, если курсор находится над объектом GUI; иначе false.
## Ptr < Widget > getWidgetIntersection ( int global_pos_x , int global_pos_y )

Возвращает пересечённый виджет, который визуально воспринимаем (не пустой, не прозрачный).
### Аргументы

- *int* **global_pos_x** - Координата X [cursor in global coordinates](../../../api/library/controls/class.input_cpp.md#getMousePosition_ivec2).
- *int* **global_pos_y** - Координата Y [cursor in global coordinates](../../../api/library/controls/class.input_cpp.md#getMousePosition_ivec2).

### Возвращаемое значение

Пересечённый виджет, который визуально воспринимаем.
## Ptr < Widget > getUnderCursorWidget ( )

Возвращает визуально воспринимаемый виджет, над которым в данный момент находится курсор.
### Возвращаемое значение

Виджет, над которым в данный момент находится курсор.
## Ptr < Gui > getFocusGui ( )

Возвращает объект GUI, находящийся в данный момент в фокусе.
### Возвращаемое значение

Объект GUI, находящийся в данный момент в фокусе.
## Ptr < Gui > getGuiIntersection ( int global_pos_x , int global_pos_y )

Возвращает пересечённый объект GUI.
> **Notice:** Этот метод учитывает Z-порядок: если объект GUI перекрыт каким-либо другим окном, метод возвращает nullptr.

### Аргументы

- *int* **global_pos_x** - Координата X точки пересечения в глобальных координатах.
- *int* **global_pos_y** - Координата Y точки пересечения в глобальных координатах.

### Возвращаемое значение

Пересечённый объект GUI.
## Ptr < Gui > getUnderCursorGui ( )

Возвращает объект GUI, находящийся в данный момент под курсором.
> **Notice:** В случае перетаскивания или изменения размера окна этот метод возвращает nullptr. Чтобы получить пересечённый GUI в таком случае, используйте [getGuiIntersection()](#getGuiIntersection_int_int_Gui).

### Возвращаемое значение

Объект GUI, находящийся в данный момент под курсором.
## void getWorldGuiInstances ( Vector < Ptr < Gui >> & OUT_ret_instances )

Возвращает все экземпляры GUI, доступные в иерархии сцены и отрисовываемые как объекты сцены.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)>> &* **OUT_ret_instances** - Все экземпляры GUI, доступные в иерархии сцены и отрисовываемые как объекты сцены. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## int getAndClearMouseWheel ( )

Возвращает значение прокрутки мыши и очищает информацию о состоянии прокрутки мыши.
### Возвращаемое значение

Значение прокрутки мыши в диапазоне [-1;1].
## void forceSetMouseWheel ( int value )

Устанавливает значение прокрутки мыши.
### Аргументы

- *int* **value** - Значение прокрутки мыши в диапазоне [-1;1].

## int getAndClearMouseWheelHorizontal ( )

Возвращает значение горизонтальной прокрутки мыши и очищает информацию о состоянии прокрутки мыши.
### Возвращаемое значение

Значение горизонтальной прокрутки мыши в диапазоне [-1;1].
## void forceSetMouseWheelHorizontal ( int value )

Устанавливает значение вертикальной прокрутки мыши.
### Аргументы

- *int* **value** - Значение горизонтальной прокрутки мыши в диапазоне [-1;1].

## bool getKey ( Input::KEY key )

Возвращает значение, указывающее, нажата ли указанная клавиша.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из стандартных управляющих кодов ASCII или одна из предопределённых переменных *[KEY_*](../../../api/library/controls/class.input_cpp.md#KEY_UNKNOWN)*.

### Возвращаемое значение

true, если клавиша нажата; иначе false.
## bool getAndClearKey ( Input::KEY key )

Возвращает значение, указывающее, нажата ли указанная клавиша, и очищает информацию о состоянии клавиши.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из стандартных управляющих кодов ASCII или одна из предопределённых переменных *[KEY_*](../../../api/library/controls/class.input_cpp.md#KEY_UNKNOWN)*.

### Возвращаемое значение

true, если клавиша нажата; иначе false.
## int toRenderSize ( int unit_size ) const

Преобразует значение в единицах в значение в пикселях.
### Аргументы

- *int* **unit_size** - Размер в единицах.

### Возвращаемое значение

Размер в пикселях.
## int toUnitSize ( int render_size ) const

Преобразует значение в пикселях в значение в единицах.
### Аргументы

- *int* **render_size** - Размер в пикселях.

### Возвращаемое значение

Размер в единицах.
## bool setFontPath ( const char * path )

Изменяет обычный шрифт, используемый в системном GUI.
### Аргументы

- *const char ** **path** - Путь к файлу шрифта.

### Возвращаемое значение

true, если шрифт успешно установлен, иначе false.
## const char * getFontPath ( ) const

Возвращает путь к обычному шрифту, используемому в данный момент в системном GUI.
### Возвращаемое значение

Путь к файлу шрифта.
## bool setFontPaths ( const char * normal_path , const char * bold_path , const char * italic_path , const char * bold_italic_path )

Изменяет набор шрифтов — обычный, полужирный, курсив и полужирный курсив — используемых в системном GUI.
### Аргументы

- *const char ** **normal_path** - Путь к файлу обычного шрифта.
- *const char ** **bold_path** - Путь к файлу полужирного шрифта.
- *const char ** **italic_path** - Путь к файлу курсивного шрифта.
- *const char ** **bold_italic_path** - Путь к файлу полужирного курсивного шрифта.

### Возвращаемое значение

true, если шрифты успешно установлены, иначе false.
## bool setFontRichBoldPath ( const char * path )

Изменяет полужирный шрифт, используемый в системном GUI.
### Аргументы

- *const char ** **path** - Путь к файлу полужирного шрифта.

### Возвращаемое значение

true, если шрифты успешно установлены, иначе false.
## const char * getFontRichBoldPath ( ) const

Возвращает путь к полужирному шрифту, используемому в данный момент в системном GUI.
### Возвращаемое значение

Путь к файлу полужирного шрифта.
## bool setFontRichItalicPath ( const char * path )

Изменяет курсивный шрифт, используемый в системном GUI.
### Аргументы

- *const char ** **path** - Путь к файлу курсивного шрифта.

### Возвращаемое значение

true, если шрифт успешно установлен, иначе false.
## const char * getFontRichItalicPath ( ) const

Возвращает путь к курсивному шрифту, используемому в данный момент в системном GUI.
### Возвращаемое значение

Путь к файлу курсивного шрифта.
## bool setFontRichBoldItalicPath ( const char * path )

Изменяет полужирный курсивный шрифт, используемый в системном GUI.
### Аргументы

- *const char ** **path** - Путь к файлу полужирного курсивного шрифта.

### Возвращаемое значение

true, если шрифт успешно установлен, иначе false.
## const char * getFontRichBoldItalicPath ( ) const

Возвращает путь к полужирному курсивному шрифту, используемому в данный момент в системном GUI.
### Возвращаемое значение

Путь к файлу полужирного курсивного шрифта.
## bool setSkinPath ( const char * path )

Изменяет скин GUI, используемый в системном GUI.
### Аргументы

- *const char ** **path** - Путь к каталогу, в котором хранятся файлы скина ([RC-файл](../../../code/gui/rc.md) и текстуры).

### Возвращаемое значение

true, если скин успешно установлен, иначе false.
## const char * getSkinPath ( ) const

Возвращает путь к текущему скину GUI.
### Возвращаемое значение

Путь к каталогу, в котором хранятся файлы скина ([RC-файл](../../../code/gui/rc.md) и текстуры).
## Ptr < Gui > get ( )

Возвращает указатель на текущий GUI.
### Возвращаемое значение

Указатель на GUI.
## void setGlobalFontFallback ( const Vector < String > & fallbacks )

Устанавливает глобальный список резервных шрифтов. Если символ не найден в текущем шрифте, система ищет его в этих шрифтах по порядку. Глобальные резервные шрифты применяются ко всем шрифтам.
### Аргументы

- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **fallbacks** - Список путей к файлам резервных шрифтов.

## void getGlobalFontFallback ( Vector < String > & OUT_ret )

Возвращает глобальный список резервных шрифтов.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_ret** - Массив для хранения путей к файлам глобальных резервных шрифтов. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void setFontFallback ( const char * font , const Vector < String > & fallbacks )

Устанавливает список резервных шрифтов для конкретного шрифта. Если символ не найден в указанном шрифте, система сначала ищет его в этих шрифтах, затем в глобальных резервных шрифтах.
### Аргументы

- *const char ** **font** - Путь к файлу шрифта, для которого задаются резервные шрифты.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **fallbacks** - Список путей к файлам резервных шрифтов.

## void getFontFallback ( const char * font , Vector < String > & OUT_ret )

Возвращает список резервных шрифтов для конкретного шрифта.
### Аргументы

- *const char ** **font** - Путь к файлу шрифта, для которого нужно получить резервные шрифты.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[String](../../../api/library/common/class.string_cpp.md)> &* **OUT_ret** - Массив для хранения путей к файлам резервных шрифтов для указанного шрифта. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.
