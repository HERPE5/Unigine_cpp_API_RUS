# Integrating with Frameworks


Чтобы интегрировать движок UNIGINE с другой системой (например, Qt, SDL, WPF, WinForms и т.д.), можно использовать класс *[Unigine::CustomSystemProxy](../../../../api/library/engine/class.customsystemproxy_cpp.md)*. Его концепция включает определение доступных функций (создание и управление окнами, управление вводом, дополнительную функциональность, такую как диалоги, буфер обмена и т.д.) вместе со всеми необходимыми переопределениями.


Функциональность некоторых подсистем движка определяется в зависимости от набора функций, предоставленных пользователем. Этот класс формирует основу для работы *[WindowManager](../../../../api/library/gui/class.windowmanager_cpp.md), [Input](../../../../api/library/controls/class.input_cpp.md), [GUI](../../../../api/library/gui/class.gui_cpp.md), [Displays](../../../../api/library/gui/class.displays_cpp.md)* и т.д.


Рабочий процесс на основе *CustomSystemProxy* позволяет:


- Создавать окно без использования платформозависимого кода
- Создавать отдельное окно рендеринга без каких-либо плагинов
- Реализовывать функциональность создания окон, общую для всех приложений
- Получать информацию о физической конфигурации дисплеев
- Предоставлять полную функциональность главного окна другим окнам (*GUI, Input* и т.д.)


> **Notice:** Для каждой среды интеграции требуется отдельная реализация прокси (*SystemProxySDL, SystemProxyQt* и т.д.).


## Рабочий процесс интеграции


Чтобы правильно использовать класс *CustomSystemProxy*, необходимо выполнить следующее:


1. Подключите файл заголовка `UnigineCustomSystemProxy.h` в исходный код.
2. Создайте пользовательский класс и унаследуйте его от класса *[Unigine::CustomSystemProxy](../../../../api/library/engine/class.customsystemproxy_cpp.md)*.
3. Переопределите все виртуальные функции, указанные в файле `include/UnigineCustomSystemProxy.h`.
4. Определите поддерживаемые функции через конструктор прокси (переменные *[SYSTEM_PROXY_*](../../../../api/library/engine/class.customsystemproxy_cpp.md#SYSTEM_PROXY_WINDOWS)*).
5. Реализуйте функции в соответствии со списком поддерживаемых возможностей, включая обработку событий и рендеринг во внешнее окно, если это требуется.


> **Notice:** Полнофункциональный пример интеграции движка UNIGINE во фреймворк QT можно найти в папке `source/apps/main_qt` (`SystemProxyQt.h`, `SystemProxyQt.cpp`).


<details>
<summary>SystemProxyQt.h | Close</summary>

```cpp
// подключаем файл заголовка
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


### Создание системного прокси


При создании системного прокси можно указать поддерживаемые им функции: передайте необходимые переменные *[SYSTEM_PROXY_*](../../../../api/library/engine/class.customsystemproxy_cpp.md#SYSTEM_PROXY_WINDOWS)* в конструктор. Например:


<details>
<summary>SystemProxyQt.cpp | Close</summary>

```cpp
// создаём прокси, способный работать с мышью и клавиатурой и создавать окна
SystemProxyQt::SystemProxyQt()
: CustomSystemProxy(SYSTEM_PROXY_WINDOWS | SYSTEM_PROXY_MOUSE | SYSTEM_PROXY_KEYBOARD)
{
}

```

</details>


Вы можете проверить, поддерживается ли функция, с помощью [corresponding function](../../../../api/library/engine/class.customsystemproxy_cpp.md#isWindowsSupported_bool). Также можно получить поддерживаемые функции через *[getFeatures()](../../../../api/library/engine/class.customsystemproxy_cpp.md#getFeatures_int)*.


<details>
<summary>SystemProxyQt.cpp | Close</summary>

```cpp
WIN_HANDLE SystemProxyQt::createWindow(int width, int height)
{
	// проверяем, поддерживается ли создание окна
	if (0 == isWindowsSupported())
	{
		return WIN_HANDLE();
	}

	WIN_HANDLE result;

	// реализация createWindow()
	...
}

```

</details>


### Обработка событий


Информация о вводе данных или взаимодействии с окном передаётся движку с помощью *событий*. Существуют:


- **[Input events](../../../../api/library/controls/class.inputevent_cpp.md)** для мыши, клавиатуры, текста, ввода с датчиков, джойстиков, геймпадов и системных событий (*[InputEventMouseButton](../../../../api/library/controls/class.inputeventmousebutton_cpp.md), [InputEventKeyboard](../../../../api/library/controls/class.inputeventkeyboard_cpp.md)* и т.д.).
- **[Window events](../../../../api/library/gui/class.windowevent_cpp.md)** для окон (*[WindowEventGeneric](../../../../api/library/gui/class.windoweventgeneric_cpp.md), [WindowEventDrop](../../../../api/library/gui/class.windoweventdrop_cpp.md)*).


После создания события их можно передать движку с помощью методов *[invokeWindowEvent()](../../../../api/library/engine/class.customsystemproxy_cpp.md#invokeWindowEvent_WindowEventPtr_void)* и *[invokeInputEvent()](../../../../api/library/engine/class.customsystemproxy_cpp.md#invokeInputEvent_InputEventPtr_void)* класса CustomSystemProxy.


<details>
<summary>SystemProxyQt.cpp | Close</summary>

```cpp
bool SystemProxyQt::invoke_input_event(const QEvent *q_event)
{
	...
	switch (q_event->type())
	{
	case QEvent::Wheel:
	{
		auto e = static_cast<const QWheelEvent *>(q_event);

		const QPoint delta = e->angleDelta() / 120;
		const Math::ivec2 scroll(delta.x(), delta.y());
		const auto timestamp = get_timestamp();
		const Math::ivec2 mouse_pos(e->globalX(), e->globalY());

		// создаём событие ввода прокрутки колеса мыши
		auto wheel_event = InputEventMouseWheel::create(timestamp, mouse_pos, scroll);
		// передаём событие ввода в WindowManager
		invokeInputEvent(wheel_event);
	}
	break;
	...
	// обрабатываем остальные события
}

```

</details>


### Рендеринг во внешнее окно


UNIGINE позволяет **регистрировать** любое внешнее окно для рендеринга с помощью следующих методов:


- *[initExternalWindowBuffers()](../../../../api/library/engine/class.customsystemproxy_cpp.md#initExternalWindowBuffers_WIN_HANDLE_const_ivec2_ref_bool)* инициализирует необходимые ресурсы в движке для рендеринга во внешнее окно.
- *[resizeExternalWindowBuffers()](../../../../api/library/engine/class.customsystemproxy_cpp.md#resizeExternalWindowBuffers_WIN_HANDLE_const_ivec2_ref_bool)* передаёт движку новые размеры окна после его изменения, чтобы движок мог обновить ресурсы рендеринга.
- *[shutdownExternalWindowBuffers()](../../../../api/library/engine/class.customsystemproxy_cpp.md#shutdownExternalWindowBuffers_WIN_HANDLE_bool)* удаляет все ресурсы, используемые для рендеринга во внешнее окно, при закрытии окна (или когда рендеринг в окно больше не требуется).


**Рендеринг** во внешнее окно выполняется с помощью следующих виртуальных методов:


- *[needRenderExternalWindow()](../../../../api/library/engine/class.customsystemproxy_cpp.md#needRenderExternalWindow_WIN_HANDLE_bool)* проверяет рендеринг внешнего окна. Если окно свёрнуто, перекрыто другими окнами и т.п., эту информацию можно передать движку (например, чтобы остановить рендеринг).
- *[onExternalWindowRender()](../../../../api/library/engine/class.customsystemproxy_cpp.md#onExternalWindowRender_WIN_HANDLE_void)* — функция обратного вызова, вызываемая при рендеринге внешнего окна. Она получает дескриптор окна, и в этой точке можно выполнить рендеринг в окно.


> **Notice:** Поскольку эти методы являются виртуальными, их необходимо переопределить.


<details>
<summary>SystemProxyQt.h | Close</summary>

```cpp
...

// внешнее окно, в которое выполняется рендеринг
class ExternalWindow
{
public:
	virtual ~ExternalWindow() = default;

	virtual void doRender() {}
	virtual void doUpdate() {}
	virtual void doSwap() {}
	virtual bool isRendering() const { return true; }
};

// класс на основе CustomSystemProxy
class SystemProxyQt final : public Unigine::CustomSystemProxy
{
public:
	...
	// переопределяем виртуальные функции
	int needRenderExternalWindow(Unigine::WIN_HANDLE win_handle) override;
	void onExternalWindowRender(Unigine::WIN_HANDLE win_handle) override;
	...

private:
	// объявляем необходимые переменные
	Unigine::HashMap<uint64_t, ExternalWindow *> external_id_to_window_;
	...
}

```

</details>


<details>
<summary>SystemProxyQt.cpp | Close</summary>

```cpp
...

// проверяем, рендерится ли внешнее окно
int SystemProxyQt::needRenderExternalWindow(WIN_HANDLE win_handle)
{
	const auto it = external_id_to_window_.find(win_handle.win_id);
	if (it != external_id_to_window_.end())
	{
		return it->data->isRendering();
	}

	return 0;
}

// реализуем логику, которая будет выполняться при рендеринге внешнего окна
void SystemProxyQt::onExternalWindowRender(WIN_HANDLE win_handle)
{
	const auto it = external_id_to_window_.find(win_handle.win_id);
	if (it != external_id_to_window_.end())
	{
		it->data->doRender();
	}
}

...

```

</details>
