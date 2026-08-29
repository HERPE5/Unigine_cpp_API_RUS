// Демонстрирует WidgetWindow как контейнер для дочерних виджетов. Создаётся
// изменяемое по размеру окно со строкой ввода и кнопкой, каждая из которых
// имеет callback-обработчики, логирующие взаимодействия пользователя в консоль.

#include "Window.h"

#include <UnigineConsole.h>

REGISTER_COMPONENT(Window);

using namespace Unigine;
using namespace Math;

// Создаётся изменяемое по размеру окно со строкой ввода и кнопкой, обе с обработчиками событий.
void Window::init()
{
	EngineWindowViewportPtr main_window = WindowManager::getMainWindow();

	GuiPtr gui = main_window->getGui();

	// Создаём окно с заголовком и отступом 4px
	window = WidgetWindow::create(gui, "Hello from C++", 4, 4);
	window->setWidth(320);
	// Разрешаем пользователю изменять размер окна
	window->setSizeable(1);

	// Строка ввода с текстом-заполнителем и callback изменения
	auto editline = WidgetEditLine::create(gui, "Edit me");
	window->addChild(editline, Gui::ALIGN_EXPAND);
	editline->getEventChanged().connect(this, &Window::editline_changed);
	editline->setFontSize(16);

	// Кнопка с callback клика
	auto button = WidgetButton::create(gui, "Press me");
	window->addChild(button, Gui::ALIGN_EXPAND);
	button->getEventClicked().connect(this, &Window::button_pressed);
	button->setFontSize(18);

	// Пересчитываем компоновку и отображаем по центру экрана
	window->arrange();
	main_window->addChild(window, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

	// Включаем экранную консоль для видимости сообщений лога
	Console::setOnscreen(true);
}

// Окно освобождается, экранная консоль отключается.
void Window::shutdown()
{
	window.deleteLater();

	Console::setOnscreen(false);
}

// Изменение текста строки ввода логируется для демонстрации callback события.
void Window::editline_changed(const Unigine::WidgetPtr &widget)
{
	// Приводим к WidgetEditLine для доступа к методу getText
	WidgetEditLinePtr editline = checked_ptr_cast<WidgetEditLine>(widget);
	Log::message("EditLine changed: %s\n", editline->getText());
}

// Нажатие кнопки логируется для демонстрации callback события.
void Window::button_pressed()
{
	Log::message("Button pressed\n");
}
