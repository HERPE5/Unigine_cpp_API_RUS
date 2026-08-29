// Пользовательский интерфейс для демонстрации преобразования clutter в cluster. Предоставляет интерактивные
// элементы управления для перегенерации процедурного размещения clutter и преобразования текущих
// экземпляров в статический кластер для повышения производительности во время выполнения.

#include "ClutterSample.h"

#include "ClutterConverter.h"

#include <UnigineWidgets.h>

REGISTER_COMPONENT(ClutterSample);

using namespace Unigine;
using namespace Math;

void ClutterSample::init()
{
	// Получаем компонент ClutterConverter из указанного узла
	clutter_converter = getComponent<ClutterConverter>(clutterConverter.get());
	if (!clutter_converter)
		Log::error("ClutterSample::init(): cannot find ClutterConverter component!\n");
	init_gui();
}

void ClutterSample::shutdown()
{
	// Очищаем ресурсы виджетов при уничтожении компонента
	sample_description_window.shutdown();
}

void ClutterSample::init_gui()
{
	// Создаём основной контейнер окна примера
	sample_description_window.createWindow();

	// Получаем область параметров, где размещаются интерактивные элементы управления
	const WidgetGroupBoxPtr &group_box = sample_description_window.getParameterGroupBox();

	// Создаём горизонтальную компоновку для кнопок в ряд
	auto hbox = WidgetHBox::create(5);
	group_box->addChild(hbox, Gui::ALIGN_CENTER);

	// Кнопка для рандомизации позиций экземпляров clutter
	auto button = WidgetButton::create("Generate Clutter");
	button->getEventClicked().connect(this, &ClutterSample::generate_button_callback);
	hbox->addChild(button, Gui::ALIGN_LEFT);

	// Кнопка для фиксации текущих позиций в статический кластер
	button = WidgetButton::create("Convert to Cluster");
	button->getEventClicked().connect(this, &ClutterSample::convert_button_callback);
	hbox->addChild(button, Gui::ALIGN_LEFT);
}

void ClutterSample::generate_button_callback()
{
	// Делегируем конвертеру: назначает новое случайное зерно clutter
	clutter_converter->generateClutter();
}

void ClutterSample::convert_button_callback()
{
	// Делегируем конвертеру: создаёт кластер из текущего состояния clutter
	clutter_converter->convertToCluster();
}
