// Пользовательский интерфейс для демонстрации преобразования clutter в cluster. Предоставляет интерактивные
// элементы управления для перегенерации процедурного размещения clutter и преобразования текущих
// экземпляров в статический кластер для повышения производительности во время выполнения.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

class ClutterConverter;

class ClutterSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ClutterSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Узел, содержащий компонент ClutterConverter для управления
	PROP_PARAM(Node, clutterConverter);

private:
	// Закэшированный указатель на компонент конвертера для callback-функций кнопок
	ClutterConverter *clutter_converter = nullptr;
	// Окно UI, содержащее элементы управления примера
	SampleDescriptionWindow sample_description_window;

private:
	void init();
	void shutdown();

	// Создаёт панель кнопок для операций генерации и преобразования
	void init_gui();

	// Запускает рандомизацию зерна clutter при нажатии кнопки Generate
	void generate_button_callback();
	// Запускает преобразование clutter в cluster при нажатии кнопки Convert
	void convert_button_callback();
};
