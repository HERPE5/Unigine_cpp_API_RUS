# Класс Unigine::CustomSystemProxy (CPP)

**Заголовочный файл:** #include <UnigineCustomSystemProxy.h>


Этот класс используется для интеграции со сторонними системами (например, *Qt, SDL, WPF*). Большинство его функций виртуальные, поэтому вам нужно переопределить их при реализации своего приложения.


В общем случае рабочий процесс на основе *CustomSystemProxy* выглядит следующим образом:


1. Подключите заголовочный файл `UnigineCustomSystemProxy.h` в исходный код.
2. Создайте пользовательский класс и унаследуйте его от класса *Unigine::CustomSystemProxy*.
3. Переопределите все виртуальные функции, указанные в файле `include/UnigineCustomSystemProxy.h`.
4. Определите поддерживаемые функции через конструктор прокси (переменные *[SYSTEM_PROXY_*](../../../api/library/engine/class.customsystemproxy_cpp.md#SYSTEM_PROXY_WINDOWS)*).
5. Реализуйте функции в соответствии со списком поддерживаемых возможностей, включая [event handling](../../../code/cpp/usage/unigine_app/proxy.md#event_handling) и [rendering into an external window](../../../code/cpp/usage/unigine_app/proxy.md#external_window), если требуется.


> **Примечание:** Полнофункциональный пример интеграции движка UNIGINE в фреймворк QT можно найти в папке `source/apps/main_qt` (`SystemProxyQt.h`, `SystemProxyQt.cpp`).


Следующий код является частью примера *SystemProxyQt*:


<details>
<summary>SystemProxyQt.h | Close</summary>

```cpp
// подключаем заголовочный файл
#include <UnigineCustomSystemProxy.h>
#include <UnigineVector.h>

...

// создаём пользовательский класс и наследуем его от CustomSystemProxy
class SystemProxyQt final : public Unigine::CustomSystemProxy
{

public:

	SystemProxyQt();
	~SystemProxyQt() override;

// переопределяем необходимые виртуальные функции
protected:

	// главный поток
	bool isEngineActive() override;
	void mainUpdate() override {}

	// окна (проверяем поддержку только создания и удаления)
	Unigine::WIN_HANDLE createWindow(int width, int height) override;
	void removeWindow(Unigine::WIN_HANDLE win_handle) override;
	void setWindowTitle(Unigine::WIN_HANDLE win_handle, const char *title) override;
	void setWindowIcon(Unigine::WIN_HANDLE win_handle, const Unigine::ImagePtr &image) override;

	...

	// дисплеи
	int getDisplayDefaultSystemDPI() const override;
	int getNumDisplays() const override;

	...

	// джойстики
	void getConnectedJoysticks(Unigine::Vector<int32_t> &connected_ids) override {}
	int getJoystickPlayerIndex(int32_t joy_id) const override { return -1; }
	int getJoystickDeviceType(int32_t joy_id) const override { return -1; }

	...

	// геймпады
	void getConnectedGamepads(Unigine::Vector<int32_t> &connected_ids) override {}

	...

	// прочее
	bool hasClipboardText() const override;

	...
}

```

</details>


<details>
<summary>SystemProxyQt.cpp | Close</summary>

```cpp
// ...

using namespace Unigine;

// создаём прокси, который может работать с мышью и клавиатурой и создавать окна
SystemProxyQt::SystemProxyQt()
	: CustomSystemProxy(SYSTEM_PROXY_WINDOWS | SYSTEM_PROXY_MOUSE | SYSTEM_PROXY_KEYBOARD)
{
	timestamp_timer_.begin();
}

SystemProxyQt::~SystemProxyQt()
{
	assert(external_windows_.empty());
	assert(window_by_id_.empty());
	window_by_id_.clear();
}

// реализация функций (создание окна, обработка событий, рендеринг во внешнее окно и т.д.)
// ...

```

</details>


### См. также


- Статья [Integrating with Frameworks](../../../code/cpp/usage/unigine_app/proxy.md)


## Класс CustomSystemProxy

### Методы класса

---

## CustomSystemProxy ( int features )

Конструктор. Создаёт экземпляр класса CustomSystemProxy и указывает [supported features](#SYSTEM_PROXY_WINDOWS) (мышь, клавиатура, джойстик и т.д.).
### Аргументы

- *int* **features** - Поддерживаемые функции.

## CustomSystemProxy * get ( )

Возвращает экземпляр CustomSystemProxy.
### Возвращаемое значение

Экземпляр CustomSystemProxy.
## int getFeatures ( ) const

Возвращает набор функций, которые может выполнять CustomSystemProxy.
### Возвращаемое значение

Маска, задающая набор функций [SYSTEM_PROXY_*](#SYSTEM_PROXY_WINDOWS), которые может выполнять CustomSystemProxy.
## bool isWindowsSupported ( ) const

Возвращает значение, указывающее, поддерживает ли CustomSystemProxy создание окон.
### Возвращаемое значение

true, если CustomSystemProxy поддерживает создание окон, иначе false.
## bool isMouseSupported ( ) const

Возвращает значение, указывающее, поддерживает ли CustomSystemProxy работу с мышью.
### Возвращаемое значение

true, если CustomSystemProxy поддерживает работу с мышью, иначе false.
## bool isKeyboardSupported ( ) const

Возвращает значение, указывающее, поддерживает ли CustomSystemProxy работу с клавиатурой.
### Возвращаемое значение

true, если CustomSystemProxy поддерживает работу с клавиатурой, иначе false.
## bool isTouchesSupported ( ) const

Возвращает значение, указывающее, поддерживает ли CustomSystemProxy работу с сенсорным вводом.
### Возвращаемое значение

true, если CustomSystemProxy поддерживает работу с сенсорным вводом, иначе false.
## bool isDisplaysSupported ( ) const

Возвращает значение, указывающее, может ли CustomSystemProxy предоставлять информацию о дисплеях.
### Возвращаемое значение

true, если CustomSystemProxy может предоставлять информацию о дисплеях, иначе false.
## bool isJoysticksSupported ( ) const

Возвращает значение, указывающее, поддерживает ли CustomSystemProxy работу с вводом от джойстика.
### Возвращаемое значение

true, если CustomSystemProxy поддерживает работу с вводом от джойстика, иначе false.
## bool isGamepadsSupported ( ) const

Возвращает значение, указывающее, поддерживает ли CustomSystemProxy работу с вводом от геймпада.
### Возвращаемое значение

true, если CustomSystemProxy поддерживает работу с вводом от геймпада, иначе false.
## bool initExternalWindowBuffers ( WIN_HANDLE win_handle , const ivec2& size )

Инициализация ресурсов для рендеринга во внешнее окно.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна.
- *const ivec2&* **size** - Размер окна.

### Возвращаемое значение

true, если операция выполнена успешно, иначе false.
## bool resizeExternalWindowBuffers ( WIN_HANDLE win_handle , const ivec2& size )

Изменение размера внешнего окна для обновления внутренних текстур.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна.
- *const ivec2&* **size** - Размер окна.

### Возвращаемое значение

true, если операция выполнена успешно, иначе false.
## bool shutdownExternalWindowBuffers ( WIN_HANDLE win_handle )

Завершение работы всех ресурсов, необходимых для рендеринга во внешнее окно, при закрытии окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна.

### Возвращаемое значение

true, если операция выполнена успешно, иначе false.
## void onExternalWindowRender ( WIN_HANDLE win_handle )

Рендеринг в указанное внешнее окно.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна, в которое рендерится изображение.

## void invokeWindowEvent ( WindowEvent Ptr e )

Передаёт событие окна в Window Manager.
### Аргументы

- *[WindowEvent](../../../api/library/gui/class.windowevent_cpp.md)Ptr* **e** - Событие окна.

## void invokeInputEvent ( InputEvent Ptr e )

Передаёт событие ввода в Window Manager.
### Аргументы

- *[InputEvent](../../../api/library/controls/class.inputevent_cpp.md)Ptr* **e** - Событие ввода.

## void mainUpdate ( )

Обратный вызов из главного потока перед обновлением.
## WIN_HANDLE createWindow ( int width , int height )

Возвращает хендл движка для созданного окна.
### Аргументы

- *int* **width** - Ширина окна.
- *int* **height** - Высота окна.

### Возвращаемое значение

Хендл окна движка.
## void removeWindow ( WIN_HANDLE win_handle )

Уничтожает окно по его хендлу.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## void setWindowTitle ( WIN_HANDLE win_handle , const char* title )

Устанавливает заголовок окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *const char** **title** - Заголовок окна.

## void setWindowIcon ( WIN_HANDLE win_handle , const ImagePtr& image )

Устанавливает иконку окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *const ImagePtr&* **image** - Изображение, используемое в качестве иконки.

## void setWindowSize ( WIN_HANDLE win_handle , const ivec2& size )

Устанавливает размер окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *const ivec2&* **size** - Размер окна (ширина и высота).

## void setWindowMinSize ( WIN_HANDLE win_handle , const ivec2& size )

Устанавливает минимально возможный размер окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *const ivec2&* **size** - Размер окна (ширина и высота).

## void setWindowMaxSize ( WIN_HANDLE win_handle , const ivec2& size )

Устанавливает максимально возможный размер окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *const ivec2&* **size** - Размер окна (ширина и высота).

## void setWindowPosition ( WIN_HANDLE win_handle , const ivec2& pos )

Устанавливает позицию окна (верхний левый угол) в экранных координатах.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *const ivec2&* **pos** - Позиция окна.

## void showWindow ( WIN_HANDLE win_handle )

Отображает окно.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## void hideWindow ( WIN_HANDLE win_handle )

Скрывает окно.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## void setWindowFocus ( WIN_HANDLE win_handle )

Устанавливает фокус на окно движка.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## void setWindowMouseGrab ( WIN_HANDLE win_handle , bool state )

Устанавливает значение, указывающее, привязан ли указатель мыши к окну.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *bool* **state** - true, если мышь не может покинуть окно; иначе **false**.

## void setWindowResizable ( WIN_HANDLE win_handle , bool state )

Устанавливает значение, указывающее, можно ли изменять размер окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *bool* **state** - true, если размер окна можно изменять; иначе **false**.

## void setWindowBordered ( WIN_HANDLE win_handle , bool state )

Устанавливает значение, указывающее, имеет ли окно границы.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *bool* **state** - true, если окно имеет границы; иначе **false**.

## void disableWindowFullscreen ( WIN_HANDLE win_handle )

Отключает полноэкранный режим для окна с указанным хендлом и возвращает его в оконный режим.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## bool enableWindowFullscreen ( WIN_HANDLE win_handle , int display , int mode )

Разворачивает окно с указанным хендлом в полноэкранный режим на указанном дисплее с указанным режимом.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *int* **display** - Индекс дисплея.
- *int* **mode** - Индекс режима.

### Возвращаемое значение

true, если окно с указанным хендлом успешно развёрнуто в полноэкранный режим на указанном дисплее с указанным режимом; иначе false.
## void minimizeWindow ( WIN_HANDLE win_handle )

Сворачивает окно в трей.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## void maximizeWindow ( WIN_HANDLE win_handle )

Разворачивает окно на весь экран.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## void restoreWindow ( WIN_HANDLE win_handle )

Восстанавливает окно из свёрнутого или развёрнутого состояния.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## void setWindowOpacity ( WIN_HANDLE win_handle , float opacity )

Устанавливает непрозрачность окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.
- *float* **opacity** - Непрозрачность окна.

## int getWindowDisplayIndex ( WIN_HANDLE win_handle ) const

Возвращает индекс дисплея, на котором рендерится окно.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

### Возвращаемое значение

Индекс дисплея.
## ivec4 getWindowSystemBorderSize ( WIN_HANDLE win_handle )

Возвращает размер системных границ окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

### Возвращаемое значение

Размер системных границ окна.
## int getHitTestAreaIntersection ( uint64_t win_handle , int global_pos_x , int global_pos_y )

Возвращает значение, указывающее, обнаружено ли пересечение курсора с областью перетаскивания окна.
### Аргументы

- *uint64_t* **win_handle** - Хендл окна движка.
- *int* **global_pos_x** - Координата X курсора в глобальных координатах.
- *int* **global_pos_y** - Координата Y курсора в глобальных координатах.

### Возвращаемое значение

1, если пересечение обнаружено; иначе 0.
## void setGlobalMousePosition ( const ivec2& pos )

Устанавливает позицию мыши в глобальных координатах относительно главного системного дисплея.
### Аргументы

- *const ivec2&* **pos** - Позиция мыши в глобальных координатах.

## ivec2 getGlobalMousePosition ( ) const

Возвращает позицию мыши в глобальных координатах относительно главного системного дисплея.
### Возвращаемое значение

Позиция мыши в глобальных координатах.
## void showCursor ( bool state )

Устанавливает значение, указывающее, отображается ли курсор.
### Аргументы

- *bool* **state** - true, чтобы показать курсор, false, чтобы скрыть его.

## void showMouseCursorSystemArrow ( )

Устанавливает системную стрелку в качестве курсора мыши.
## void setMouseCursorSkinCustom ( const ImagePtr& mouse_skin )

Устанавливает указанное [skin image](../../../code/gui/skin/index.md#gui_mouse_layout) в качестве курсора мыши.
### Аргументы

- *const ImagePtr&* **mouse_skin** - [Image](../../../code/gui/skin/index.md#gui_mouse_layout), содержащее формы указателя, устанавливаемые для курсора мыши (например, выбор, перемещение, изменение размера и т.д.).

## void setMouseCursorSkinSystem ( )

Устанавливает текущий системный скин курсора ОС (формы указателя, такие как выбор, перемещение, изменение размера и т.д.).
## void setMouseCursorCustom ( const ImagePtr& image , int x , int y )

Устанавливает пользовательское изображение для системного курсора мыши ОС. Изображение должно иметь квадратный размер и формат *RGBA8*. Этот способ установки курсора имеет приоритет над другими способами. Изображение, установленное этим методом, можно очистить только с помощью метода [clearMouseCursorCustom()](#clearMouseCursorCustom_void).
### Аргументы

- *const ImagePtr&* **image** - [Image](../../../code/gui/skin/index.md#gui_mouse_layout), содержащее формы указателя, устанавливаемые для курсора мыши (например, выбор, перемещение, изменение размера и т.д.).
- *int* **x** - Координата X горячей точки курсора.
- *int* **y** - Координата Y горячей точки курсора.

## void clearMouseCursorCustom ( )

Очищает пользовательский курсор мыши, установленный методом [setMouseCursorCustom()](#setMouseCursorCustom_const_ImagePtr_ref_int_int_void).
## void changeMouseCursorSkinNumber ( int number )

Изменяет скин курсора с помощью [skin number](../../../code/gui/skin/index.md#gui_mouse_layout).
### Аргументы

- *int* **number** - Номер скина курсора, одна из предопределённых переменных [CURSOR_*](../../../api/library/gui/class.gui_cpp.md#CURSOR_ARROW).

## int getDisplayDefaultSystemDPI ( ) const

Возвращает значение точек/пикселей на дюйм по умолчанию для системы.
### Возвращаемое значение

Значение точек/пикселей на дюйм.
## int getNumDisplays ( ) const

Возвращает общее количество дисплеев.
### Возвращаемое значение

Количество дисплеев.
## ivec2 getDisplayPosition ( int display_index ) const

Возвращает позицию указанного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Позиция дисплея.
## ivec2 getDisplayResolution ( int display_index ) const

Возвращает разрешение указанного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Разрешение дисплея.
## int getDisplayDPI ( int display_index ) const

Возвращает DPI указанного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

DPI дисплея.
## int getMainDisplay ( ) const

Возвращает индекс главного дисплея.
### Возвращаемое значение

Индекс дисплея.
## int getDisplayNumModes ( int display_index ) const

Возвращает общее количество доступных режимов дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Количество доступных режимов дисплея.
## ivec2 getDisplayModeResolution ( int display_index , int mode_index ) const

Возвращает DPI указанного режима для выбранного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.
- *int* **mode_index** - Индекс режима дисплея.

### Возвращаемое значение

DPI дисплея.
## int getDisplayModeRefreshRate ( int display_index , int mode_index ) const

Возвращает частоту обновления указанного режима дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.
- *int* **mode_index** - Индекс режима дисплея.

### Возвращаемое значение

Частота обновления указанного режима дисплея.
## const char * getDisplayName ( int display_index ) const

Возвращает системное имя указанного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Имя дисплея.
## bool hasClipboardText ( ) const

Возвращает значение, показывающее, содержит ли буфер обмена что-либо.
### Возвращаемое значение

true, если в буфере обмена есть текст, иначе false.
## void setClipboardText ( const char* str )

Обновляет содержимое системного буфера обмена.
### Аргументы

- *const char** **str** - Устанавливаемое содержимое.

## const char* getClipboardText ( )

Извлекает содержимое системного буфера обмена.
### Возвращаемое значение

Содержимое системного буфера обмена.
## bool showDialogMessage ( const char* title , const char* message , WIN_HANDLE parent_window_handle )

Отображает диалоговое окно сообщения с указанным заголовком и текстом.
### Аргументы

- *const char** **title** - Заголовок окна сообщения.
- *const char** **message** - Текст сообщения.
- *WIN_HANDLE* **parent_window_handle** - Хендл родительского окна.

### Возвращаемое значение

true, если диалоговое окно сообщения отображено успешно, иначе false.
## bool showDialogWarning ( const char* title , const char* warning , WIN_HANDLE parent_window_handle )

Отображает диалоговое окно предупреждения с указанным заголовком и текстом.
### Аргументы

- *const char** **title** - Заголовок окна предупреждения.
- *const char** **warning** - Текст предупреждения.
- *WIN_HANDLE* **parent_window_handle** - Хендл родительского окна.

### Возвращаемое значение

true, если диалоговое окно предупреждения отображено успешно, иначе false.
## bool showDialogError ( const char* title , const char* error , WIN_HANDLE parent_window_handle )

Отображает диалоговое окно ошибки с указанным заголовком и текстом.
### Аргументы

- *const char** **title** - Заголовок окна ошибки.
- *const char** **error** - Текст ошибки.
- *WIN_HANDLE* **parent_window_handle** - Хендл родительского окна.

### Возвращаемое значение

true, если диалоговое окно ошибки отображено успешно, иначе false.
## bool needRenderExternalWindow ( WIN_HANDLE win_handle )

Проверяет рендеринг внешнего окна. Если окно свёрнуто, перекрыто другими окнами и т.д., эту информацию можно передать движку (например, чтобы остановить рендеринг).
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл внешнего окна, в которое рендерится изображение.

### Возвращаемое значение

true, если окно рендерится, иначе false.
## void setWindowModal ( WIN_HANDLE win_handle , WIN_HANDLE parent_handle )

Устанавливает окно как модальное для родительского окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Окно, устанавливаемое как модальное.
- *WIN_HANDLE* **parent_handle** - Родительское окно для модального окна.

## void setWindowAlwaysOnTop ( WIN_HANDLE win_handle , bool state )

Размещает окно поверх всех остальных окон. Окно сохраняет верхнюю позицию, даже когда деактивировано.
### Аргументы

- *WIN_HANDLE* **win_handle** - Окно, устанавливаемое как модальное.
- *bool* **state** - true, чтобы сделать окно движка верхним; false, чтобы установить поведение окна движка по умолчанию.

## void getConnectedJoysticks ( Vector <int32_t>& connected_ids )

Возвращает идентификаторы всех подключённых джойстиков.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int32_t>&* **connected_ids** - Вектор идентификаторов.

## int getJoystickPlayerIndex ( int32_t joy_id ) const

Возвращает индекс игрока джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Индекс игрока.
## int getJoystickDeviceType ( int32_t joy_id ) const

Возвращает тип джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Тип джойстика.
## int getJoystickVendor ( int32_t joy_id ) const

Возвращает идентификатор производителя джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Идентификатор производителя джойстика.
## int getJoystickProduct ( int32_t joy_id ) const

Возвращает идентификатор продукта джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Идентификатор продукта джойстика.
## int getJoystickProductVersion ( int32_t joy_id ) const

Возвращает версию продукта джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Версия продукта джойстика.
## const char * getJoystickName ( int32_t joy_id ) const

Возвращает имя джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Имя джойстика.
## const char * getJoystickModelGUID ( int32_t joy_id ) const

Возвращает имя джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

GUID модели джойстика.
## int getJoystickNumButtons ( int32_t joy_id ) const

Возвращает количество кнопок джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Количество кнопок.
## int getJoystickNumAxes ( int32_t joy_id ) const

Возвращает количество осей джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Количество осей.
## int getJoystickNumPovs ( int32_t joy_id ) const

Возвращает количество POV-переключателей джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.

### Возвращаемое значение

Количество POV-переключателей.
## float getJoystickAxisInitValue ( int32_t joy_id , int axis ) const

Возвращает начальное значение оси джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *int* **axis** - Индекс оси.

### Возвращаемое значение

Начальное значение оси.
## const char * getJoystickButtonName ( int32_t joy_id , int button )

Возвращает имя кнопки джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *int* **button** - Индекс кнопки.

### Возвращаемое значение

Имя кнопки.
## const char * getJoystickAxisName ( int32_t joy_id , int axis )

Возвращает имя оси джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *int* **axis** - Индекс оси.

### Возвращаемое значение

Имя оси.
## const char * getJoystickPovName ( int32_t joy_id , int pov )

Возвращает имя POV-переключателя джойстика.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *int* **pov** - Индекс POV-переключателя.

### Возвращаемое значение

Имя POV-переключателя.
## void getConnectedGamepads ( Vector <int32_t>& connected_ids )

Возвращает идентификаторы всех подключённых геймпадов.
### Аргументы

- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<int32_t>&* **connected_ids** - Вектор идентификаторов.

## int getGamepadPlayerIndex ( int32_t pad_id ) const

Возвращает индекс игрока геймпада.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.

### Возвращаемое значение

Индекс игрока.
## int getGamepadDeviceType ( int32_t pad_id ) const

Возвращает тип геймпада.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.

### Возвращаемое значение

Тип геймпада.
## int getGamepadModelType ( int32_t pad_id ) const

Возвращает тип модели джойстика.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.

### Возвращаемое значение

Тип модели.
## const char * getGamepadName ( int32_t pad_id ) const

Возвращает имя геймпада.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.

### Возвращаемое значение

Имя геймпада.
## const char * getGamepadModelGUID ( int32_t pad_id ) const

Возвращает GUID модели геймпада.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.

### Возвращаемое значение

GUID модели.
## void setGamepadVibration ( int32_t pad_id , float low_frequency , float high_frequency , float duration_ms )

Запускает вибрацию геймпада.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.
- *float* **low_frequency** - Скорость низкочастотного (левого) мотора.
- *float* **high_frequency** - Скорость высокочастотного (правого) мотора.
- *float* **duration_ms** - Продолжительность вибрации, в миллисекундах.

## int getGamepadNumTouches ( int32_t pad_id ) const

Возвращает общее количество сенсорных панелей для указанного геймпада.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.

### Возвращаемое значение

Общее количество сенсорных панелей для указанного геймпада.
## int getGamepadNumTouchFingers ( int32_t pad_id , int touch ) const

Возвращает общее количество пальцев, поддерживаемых указанной сенсорной панелью геймпада.
### Аргументы

- *int32_t* **pad_id** - Идентификатор геймпада.
- *int* **touch** - Индекс сенсорной панели геймпада, число от 0 до общего количества сенсорных панелей.

### Возвращаемое значение

Общее количество пальцев, поддерживаемых указанной сенсорной панелью геймпада.
## int getDisplayRefreshRate ( int display_index ) const

Возвращает частоту обновления дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Частота обновления.
## int getDisplayCurrentMode ( int display_index ) const

Возвращает номер текущего режима дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Номер текущего режима дисплея.
## int getDisplayDesktopMode ( int display_index ) const

Возвращает номер режима дисплея рабочего стола.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Номер режима дисплея рабочего стола.
## int getDisplayOrientation ( int display_index ) const

Возвращает ориентацию дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Ориентация дисплея.
## bool isDpiAwarenessSupported ( int32_t mode ) const

Возвращает значение, указывающее, поддерживается ли указанный режим осведомлённости о DPI.
### Аргументы

- *int32_t* **mode** - Режим осведомлённости о DPI, значение, указывающее, как приложение обрабатывает масштабирование DPI.

### Возвращаемое значение

true, если указанный режим осведомлённости о DPI поддерживается; иначе false.
## bool isKeyboardModifierEnabled ( int modifier ) const

Возвращает значение, указывающее, включён ли указанный модификатор клавиатуры.
### Аргументы

- *int* **modifier** - Модификатор клавиатуры (одна из переменных *[Input::MODIFIER_*](../../../api/library/controls/class.input_cpp.md#MODIFIER)*).

### Возвращаемое значение

true, если модификатор клавиатуры включён; иначе false.
## unsigned int keyToUnicode ( unsigned int key ) const

Возвращает заданную клавишу, преобразованную в Unicode.
### Аргументы

- *unsigned int* **key** - Клавиша (одна из переменных *[Input::KEY_*](../../../api/library/controls/class.input_cpp.md#KEY)*).

### Возвращаемое значение

Символ Unicode.
## unsigned int unicodeToKey ( unsigned int unicode ) const

Возвращает клавишу, преобразованную из указанного символа Unicode.
### Аргументы

- *unsigned int* **unicode** - Символ Unicode.

### Возвращаемое значение

Клавиша (одна из переменных *[Input::KEY_*](../../../api/library/controls/class.input_cpp.md#KEY)*).
## bool isFocus ( )

Возвращает значение, указывающее, установлен ли фокус на окне.
### Возвращаемое значение

true, если фокус установлен на окне; иначе false.
## void focusGained ( )

Фокус установлен на окне.
## void focusLost ( )

Фокус снят с окна.
## void updateWindowOrders ( )

Обновляет Z-порядок всех окон.
> **Notice:** Рекомендуется использовать этот метод только при необходимости, так как он очень медленный.

## int getWindowOrder ( WIN_HANDLE win_handle ) const

Возвращает Z-порядок окна.
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

### Возвращаемое значение

Порядок окна (меньшее значение означает, что окно ближе к наблюдателю).
## void windowToTop ( WIN_HANDLE win_handle )

Выводит окно с указанным хендлом наверх (поверх всех остальных окон).
### Аргументы

- *WIN_HANDLE* **win_handle** - Хендл окна движка.

## WIN_HANDLE getWindowIntersection ( const ivec2& global_pos , const Vector <WIN_HANDLE>& excludes )

Возвращает хендл окна, пересечение с которым обнаружено.
### Аргументы

- *const ivec2&* **global_pos** - Координаты точки пересечения в глобальных координатах.
- *const [Vector](../../../api/library/containers/vector/class.vector_cpp.md)<WIN_HANDLE>&* **excludes** - Окна, исключаемые из обнаружения пересечения.

### Возвращаемое значение

Хендл окна, пересечение с которым обнаружено.
## bool isJoystickForceFeedbackEffectSupported ( int32_t joy_id , int effect )

Возвращает значение, указывающее, поддерживается ли указанный тип эффекта силовой обратной связи джойстиком с заданным идентификатором.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *int* **effect** - Тип эффекта силовой обратной связи.

### Возвращаемое значение

true, если указанный тип эффекта силовой обратной связи поддерживается джойстиком с заданным идентификатором; иначе false.
## void playJoystickForceFeedbackEffectConstant ( int32_t joy_id , float force )

Применяет к джойстику с заданным идентификатором эффект постоянной силовой обратной связи с указанными параметрами. Сила применяется на постоянном уровне в течение всей продолжительности эффекта.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Величина силы, применяемой эффектом силовой обратной связи. Значение в диапазоне [-1, 1]. Отрицательные значения означают, что начальное направление эффекта силовой обратной связи — влево, положительные значения — вправо.

## void playJoystickForceFeedbackEffectRamp ( int32_t joy_id , float force , unsigned long duration_us )

Применяет к джойстику с заданным идентификатором эффект силовой обратной связи типа "рампа" с указанными параметрами. Сила применяется постепенно, увеличиваясь или уменьшаясь в течение продолжительности эффекта.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Величина силы, применяемой эффектом силовой обратной связи. Значение в диапазоне [-1, 1]. Отрицательные значения означают, что начальное направление эффекта силовой обратной связи — влево, положительные значения — вправо.
- *unsigned long* **duration_us** - Продолжительность эффекта силовой обратной связи, в микросекундах.

## void playJoystickForceFeedbackEffectSineWave ( int32_t joy_id , float force , float attack_force , float fade_force , int phase , unsigned int period_ms , unsigned int attack_length_ms , unsigned int fade_length_ms , unsigned int effect_duration_ms )

Применяет к джойстику с заданным идентификатором синусоидальный эффект силовой обратной связи с указанными параметрами. Сила применяется по синусоидальному шаблону.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Значение поддержания — значение силы в середине эффекта силовой обратной связи в диапазоне [-1, 1]. Отрицательные значения означают, что начальное направление эффекта силовой обратной связи — влево, положительные значения — вправо.
- *float* **attack_force** - Значение в начале атаки, в диапазоне [0, 1].
- *float* **fade_force** - Значение в конце затухания, в диапазоне [0, 1].
- *int* **phase** - Положительный сдвиг фазы, в градусах в диапазоне [0, 360].
- *unsigned int* **period_ms** - Период волны, в мс.
- *unsigned int* **attack_length_ms** - Продолжительность атаки — период времени в мс, определяющий, сколько времени требуется для достижения значения силы (значения в середине эффекта).
- *unsigned int* **fade_length_ms** - Продолжительность затухания — период времени в мс, определяющий, сколько времени требуется, чтобы спасть от значения силы (значения в середине эффекта).
- *unsigned int* **effect_duration_ms** - Продолжительность эффекта, в мс.

## void playJoystickForceFeedbackEffectSquareWave ( int32_t joy_id , float force , float attack_force , float fade_force , int phase , unsigned int period_ms , unsigned int attack_length_ms , unsigned int fade_length_ms , unsigned int effect_duration_ms )

Применяет к джойстику с заданным идентификатором прямоугольный эффект силовой обратной связи с указанными параметрами. Сила применяется по прямоугольному шаблону.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Значение поддержания — значение силы в середине эффекта силовой обратной связи в диапазоне [-1, 1]. Отрицательные значения означают, что начальное направление эффекта силовой обратной связи — влево, положительные значения — вправо.
- *float* **attack_force** - Значение в начале атаки, в диапазоне [0, 1].
- *float* **fade_force** - Значение в конце затухания, в диапазоне [0, 1].
- *int* **phase** - Положительный сдвиг фазы, в градусах в диапазоне [0, 360].
- *unsigned int* **period_ms** - Период волны, в мс.
- *unsigned int* **attack_length_ms** - Продолжительность атаки — период времени в мс, определяющий, сколько времени требуется для достижения значения силы (значения в середине эффекта).
- *unsigned int* **fade_length_ms** - Продолжительность затухания — период времени в мс, определяющий, сколько времени требуется, чтобы спасть от значения силы (значения в середине эффекта).
- *unsigned int* **effect_duration_ms** - Продолжительность эффекта, в мс.

## void playJoystickForceFeedbackEffectTriangleWave ( int32_t joy_id , float force , float attack_force , float fade_force , int phase , unsigned int period_ms , unsigned int attack_length_ms , unsigned int fade_length_ms , unsigned int effect_duration_ms )

Применяет к джойстику с заданным идентификатором треугольный эффект силовой обратной связи с указанными параметрами. Сила применяется по треугольному шаблону.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Значение поддержания — значение силы в середине эффекта силовой обратной связи в диапазоне [-1, 1]. Отрицательные значения означают, что начальное направление эффекта силовой обратной связи — влево, положительные значения — вправо.
- *float* **attack_force** - Значение в начале атаки. Значение в диапазоне [0, 1].
- *float* **fade_force** - Значение в конце затухания. Значение в диапазоне [0, 1].
- *int* **phase** - Положительный сдвиг фазы, в градусах в диапазоне [0, 360].
- *unsigned int* **period_ms** - Период волны, в мс.
- *unsigned int* **attack_length_ms** - Продолжительность атаки — период времени в мс, определяющий, сколько времени требуется для достижения значения силы (значения в середине эффекта).
- *unsigned int* **fade_length_ms** - Продолжительность затухания — период времени в мс, определяющий, сколько времени требуется, чтобы спасть от значения силы (значения в середине эффекта).
- *unsigned int* **effect_duration_ms** - Продолжительность эффекта, в мс.

## void playJoystickForceFeedbackEffectSawtoothUpWave ( int32_t joy_id , float force , float attack_force , float fade_force , int phase , unsigned int period_ms , unsigned int attack_length_ms , unsigned int fade_length_ms , unsigned int effect_duration_ms )

Применяет к джойстику с заданным идентификатором восходящий пилообразный эффект силовой обратной связи с указанными параметрами. Сила применяется по восходящему пилообразному шаблону.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Значение поддержания — значение силы в середине эффекта силовой обратной связи в диапазоне [-1, 1]. Отрицательные значения означают, что начальное направление эффекта силовой обратной связи — влево, положительные значения — вправо.
- *float* **attack_force** - Значение в начале атаки. Значение в диапазоне [0, 1].
- *float* **fade_force** - Значение в конце затухания. Значение в диапазоне [0, 1].
- *int* **phase** - Положительный сдвиг фазы, в градусах в диапазоне [0, 360].
- *unsigned int* **period_ms** - Период волны, в мс.
- *unsigned int* **attack_length_ms** - Продолжительность атаки — период времени в мс, определяющий, сколько времени требуется для достижения значения силы (значения в середине эффекта).
- *unsigned int* **fade_length_ms** - Продолжительность затухания — период времени в мс, определяющий, сколько времени требуется, чтобы спасть от значения силы (значения в середине эффекта).
- *unsigned int* **effect_duration_ms** - Продолжительность эффекта, в мс.

## void playJoystickForceFeedbackEffectSawtoothDownWave ( int32_t joy_id , float force , float attack_force , float fade_force , int phase , unsigned int period_ms , unsigned int attack_length_ms , unsigned int fade_length_ms , unsigned int effect_duration_ms )

Применяет к джойстику с заданным идентификатором нисходящий пилообразный эффект силовой обратной связи с указанными параметрами. Сила применяется по нисходящему пилообразному шаблону.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Значение поддержания — значение силы в середине эффекта силовой обратной связи в диапазоне [-1, 1]. Отрицательные значения означают, что начальное направление эффекта силовой обратной связи — влево, положительные значения — вправо.
- *float* **attack_force** - Значение в начале атаки. Значение в диапазоне [0, 1].
- *float* **fade_force** - Значение в конце затухания. Значение в диапазоне [0, 1].
- *int* **phase** - Положительный сдвиг фазы, в градусах в диапазоне [0, 360].
- *unsigned int* **period_ms** - Период волны, в мс.
- *unsigned int* **attack_length_ms** - Продолжительность атаки — период времени в мс, определяющий, сколько времени требуется для достижения значения силы (значения в середине эффекта).
- *unsigned int* **fade_length_ms** - Продолжительность затухания — период времени в мс, определяющий, сколько времени требуется, чтобы спасть от значения силы (значения в середине эффекта).
- *unsigned int* **effect_duration_ms** - Продолжительность эффекта, в мс.

## void playJoystickForceFeedbackEffectSpring ( int32_t joy_id , float left_force , float left_saturation , float right_force , float right_saturation , float offset , float deadband )

Применяет к джойстику с заданным идентификатором пружинный эффект силовой обратной связи с указанными параметрами. Сила применяется в противодействие заданному состоянию.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **left_force** - Сила эффекта силовой обратной связи, возникающего при повороте влево. Значение в диапазоне [0, 1].
- *float* **left_saturation** - Максимально возможная сила для эффекта силовой обратной связи при повороте влево. Значение в диапазоне [0, 1]. Не все устройства поддерживают насыщение.
- *float* **right_force** - Сила эффекта силовой обратной связи, возникающего при повороте вправо. Значение в диапазоне [0, 1].
- *float* **right_saturation** - Максимально возможная сила для эффекта силовой обратной связи при повороте вправо. Значение в диапазоне [0, 1]. Не все устройства поддерживают насыщение.
- *float* **offset** - Смещение от нулевого показания соответствующего значения датчика, при котором начинает применяться условие. Для пружинного эффекта нейтральная точка — то есть точка на оси, в которой пружина считалась бы в состоянии покоя — определяется смещением для условия.
- *float* **deadband** - Зона вокруг смещения оси, в которой условие не активно. В случае пружины, находящейся в состоянии покоя в середине оси, мёртвая зона увеличивает эту область покоя. Не все устройства поддерживают мёртвую зону.

## void playJoystickForceFeedbackEffectFriction ( int32_t joy_id , float left_force , float left_saturation , float right_force , float right_saturation )

Применяет к джойстику с заданным идентификатором эффект силовой обратной связи типа "трение" с указанными параметрами. Сила применяется для имитации трения.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **left_force** - Сила эффекта силовой обратной связи, возникающего при повороте влево. Значение в диапазоне [0, 1].
- *float* **left_saturation** - Максимально возможная сила для эффекта силовой обратной связи при повороте влево. Значение в диапазоне [0, 1]. Не все устройства поддерживают насыщение.
- *float* **right_force** - Сила эффекта силовой обратной связи, возникающего при повороте вправо. Значение в диапазоне [0, 1].
- *float* **right_saturation** - Максимально возможная сила для эффекта силовой обратной связи при повороте вправо. Значение в диапазоне [0, 1]. Не все устройства поддерживают насыщение.

## void playJoystickForceFeedbackEffectDamper ( int32_t joy_id , float left_force , float left_saturation , float right_force , float right_saturation )

Применяет к джойстику с заданным идентификатором демпферный эффект силовой обратной связи с указанными параметрами. Сила применяется для имитации эффекта демпфера.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **left_force** - Сила эффекта силовой обратной связи, возникающего при повороте влево. Значение в диапазоне [0, 1].
- *float* **left_saturation** - Максимально возможная сила для эффекта силовой обратной связи при повороте влево. Значение в диапазоне [0, 1]. Не все устройства поддерживают насыщение.
- *float* **right_force** - Сила эффекта силовой обратной связи, возникающего при повороте вправо. Значение в диапазоне [0, 1].
- *float* **right_saturation** - Максимально возможная сила для эффекта силовой обратной связи при повороте вправо. Значение в диапазоне [0, 1]. Не все устройства поддерживают насыщение.

## void playJoystickForceFeedbackEffectInertia ( int32_t joy_id , float force )

Применяет к джойстику с заданным идентификатором инерционный эффект силовой обратной связи с указанными параметрами. Сила применяется для имитации эффекта инерции.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *float* **force** - Величина силы, применяемой эффектом силовой обратной связи. Значение в диапазоне [0, 1].

## void stopJoystickForceFeedbackEffect ( int32_t joy_id , int effect )

Останавливает применение указанного типа эффекта силовой обратной связи к джойстику с заданным идентификатором.
### Аргументы

- *int32_t* **joy_id** - Идентификатор джойстика.
- *int* **effect** - Тип эффекта силовой обратной связи.
