// Демонстрирует асинхронные HTTP-запросы с использованием библиотеки cpp-httplib.
// Использует API погоды для поиска городов и получения прогнозов.
// Запросы выполняются в фоновых потоках через AsyncTask, чтобы не блокировать рендеринг.

#include "SimpleHttpRequestSample.h"

#include <UnigineWidgets.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(SimpleHttpRequestSample);

using namespace Unigine;
using namespace Math;

// GUI создаётся, фоновая очередь потоков запускается.
void SimpleHttpRequestSample::init()
{
	init_gui();

	// Пул фоновых потоков запускается для асинхронных HTTP-запросов
	ThreadQueue::get().run();
}

// Ожидающие HTTP-запросы опрашиваются; ответы разбираются и отображаются.
void SimpleHttpRequestSample::update()
{
	// Завершение запроса поиска города проверяется (неблокирующий опрос)
	if (city_request.size() && city_request.last()->isCompleted())
	{
		w_list->clear();

		// Результат извлекается из завершённой асинхронной задачи
		if (httplib::Result &result = city_request.last()->get())
		{
			// JSON-ответ от API геокодирования разбирается
			JsonPtr json = Json::create();
			json->parse(result->body.c_str());
			Log::message("response:\n%s\n", json->getFormattedSubTree().get());
			auto arr = json->getChild("results");
			if (arr && arr->getNumChildren() != 0)
			{
				// Каждый результат города добавляется в список с координатами, сохранёнными как данные элемента
				for (int i = 0; i < arr->getNumChildren(); i++)
				{
					auto child = arr->getChild(i);
					if (!child->isChild("name") || !child->isChild("latitude") || !child->isChild("longitude"))
						continue;
					String name = child->getChild("name")->getString();
					if (child->isChild("country"))
						name += ", " + child->getChild("country")->getString();
					if (child->isChild("admin1"))
						name += ", " + child->getChild("admin1")->getString();

					int item = w_list->addItem(name);

					// Координаты сохраняются как параметры URL-запроса для запроса прогноза
					double lat = child->getChild("latitude")->getNumber();
					double lon = child->getChild("longitude")->getNumber();
					String data = String::format("latitude=%f&longitude=%f", lat, lon);

					w_list->setItemData(item, data);
				}
			} else
			{
				// Результаты не найдены - поле ввода подсвечивается красным
				w_search->setFontColor(vec4_red);
			}
		} else
		{
			// Ошибка HTTP-клиента логируется
			String error = httplib::to_string(result.error()).c_str();
			Log::error("%s\n", error.get());
		}
		city_request.clear();
	}

	// Завершение запроса прогноза проверяется
	if (forecast_request && forecast_request->isCompleted())
	{
		String res;

		if (httplib::Result &result = forecast_request->get())
		{
			// Данные о погоде извлекаются из JSON-ответа
			JsonPtr json = Json::create();
			json->parse(result->body.c_str());
			Log::message("response:\n%s\n", json->getFormattedSubTree().get());

			// Текущие значения погоды и единицы измерения форматируются для отображения
			auto current = json->getChild("current");
			auto current_units = json->getChild("current_units");
			if (!current || !current_units)
			{
				Log::error("SimpleHttpRequestSample: unexpected forecast JSON structure\n");
			} else
			{
				auto fmt = [&](const char *label, const char *key)
				{
					auto val = current->getChild(key);
					auto unit = current_units->getChild(key);
					if (val && unit)
						res += String(label) + String::ftoa(toFloat(val->getNumber()), 1) + unit->getString() + "\n";
				};
				fmt("Temperature: ", "temperature_2m");
				fmt("Humidity: ", "relative_humidity_2m");
				fmt("Precipitation: ", "precipitation");
				fmt("Wind Speed: ", "wind_speed_10m");
				fmt("Wind Direction: ", "wind_direction_10m");
			}
		} else
		{
			String error = httplib::to_string(result.error()).c_str();
			Log::error("%s\n", error.get());
		}
		// Информация о погоде отображается в области статуса
		sample_description_window.setStatus(res);

		forecast_request.reset();
	}
}

// Фоновая очередь потоков останавливается, UI очищается.
void SimpleHttpRequestSample::shutdown()
{
	ThreadQueue::get().stop();
	sample_description_window.shutdown();
}

// Поисковый интерфейс создаётся с полем ввода города и списком результатов.
void SimpleHttpRequestSample::init_gui()
{
	sample_description_window.createWindow();

	// Окно центрируется на экране
	sample_description_window.getWindow()->arrange();
	auto size = Gui::getCurrent()->getSize() / 2 - ivec2(sample_description_window.getWindow()->getWidth(), sample_description_window.getWindow()->getHeight()) / 2;
	sample_description_window.getWindow()->setPosition(size.x, size.y);

	auto gui = Gui::getCurrent();

	auto &parent = sample_description_window.getWindow();

	// Группа поиска содержит поле ввода и список результатов
	auto w_group_search = WidgetGroupBox::create("Search", 20, 10);
	parent->addChild(w_group_search, Gui::ALIGN_EXPAND);

	w_search = WidgetEditLine::create(gui);
	w_search->setToolTip("search city by name");
	w_group_search->addChild(w_search, Gui::ALIGN_EXPAND);

	// Нажатие клавиши запускает запрос к API геокодирования
	w_search->getEventKeyPressed().connect(*this, [this]()
		{
		w_search->setFontColor(vec4_white);
		String str = "/v1/search?name=";
		str += w_search->getText();

		// Новый асинхронный запрос создаётся и ставится в очередь для фонового выполнения
		// API: geocoding-api.open-meteo.com/v1/search?name=<city>
		city_request.push_back(std::make_unique<AsyncTask<httplib::Result>>([str]() -> httplib::Result {
				httplib::Client cli("geocoding-api.open-meteo.com");
				return cli.Get(str.get());
			})); });

	w_list = WidgetListBox::create(gui);
	w_group_search->addChild(w_list, Gui::ALIGN_LEFT);

	// Выбор города запускает запрос к API прогноза
	w_list->getEventChanged().connect(*this, [this]()
		{
			sample_description_window.setStatus("");
			if (w_list->getCurrentItem() != -1)
			{
				sample_description_window.setStatus("request...");
				// Запрос прогноза строится с использованием координат, сохранённых в данных элемента
				// API: api.open-meteo.com/v1/forecast?latitude=X&longitude=Y&current=...
				auto request_str = String::format("/v1/forecast?%s&current=temperature_2m,relative_humidity_2m,precipitation,wind_speed_10m,wind_direction_10m", w_list->getCurrentItemData());
				forecast_request = std::make_unique<AsyncTask<httplib::Result>>([request_str]() -> httplib::Result {
					httplib::Client cli("api.open-meteo.com");
					return cli.Get(request_str.get());
				});
			}
		});

	sample_description_window.setStatus("Type city name");
}
