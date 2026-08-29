// Пример прогноза погоды, демонстрирующий асинхронные HTTP-запросы.
// Использует API геокодирования и прогноза Open-Meteo для поиска городов и отображения
// текущих данных о погоде. Запросы выполняются в фоновых потоках через AsyncTask.

#pragma once

#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/AsyncTasks.h"
#include "../../utils/network/httplib.h"

// Демонстрирует асинхронные HTTP-запросы с интеграцией API геокодирования и погоды.
class SimpleHttpRequestSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SimpleHttpRequestSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	SampleDescriptionWindow sample_description_window;

private:
	void init();
	void update();
	void shutdown();

	void init_gui();

	Unigine::WidgetListBoxPtr w_list;						// Список результатов поиска городов
	Unigine::WidgetEditLinePtr w_search;					// Поле ввода названия города
	Unigine::Vector<std::unique_ptr<AsyncTask<httplib::Result>>> city_request;	// Ожидающие запросы геокодирования
	std::unique_ptr<AsyncTask<httplib::Result>> forecast_request;				// Ожидающий запрос прогноза
};
