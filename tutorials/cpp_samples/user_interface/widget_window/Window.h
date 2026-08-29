// Демонстрирует WidgetWindow как контейнер для дочерних виджетов. Создаётся
// изменяемое по размеру окно со строкой ввода и кнопкой, каждая из которых
// имеет callback-обработчики, логирующие взаимодействия пользователя в экранную консоль.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Создаёт простое окно со строкой ввода и кнопкой, демонстрирующее обработку событий.
class Window : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Window, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

	// Callback для события изменения текста строки ввода
	void editline_changed(const Unigine::WidgetPtr &widget);
	// Callback для события нажатия кнопки
	void button_pressed();

	// Главное окно-контейнер, содержащее дочерние виджеты
	Unigine::WidgetWindowPtr window;
};