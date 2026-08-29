// Пример загрузки изображений по HTTP с асинхронной загрузкой текстур.
// HttpImageRequestSample управляет жизненным циклом фоновой очереди потоков.
// HttpImageToTexture скачивает изображение по указанному URL и применяет
// его к слоту текстуры материала по завершении.

#pragma once

#include <UnigineComponentSystem.h>
#include "../../utils/AsyncTasks.h"
#include "../../utils/network/httplib.h"

// Управляет фоновой очередью потоков для асинхронных HTTP-операций.
class HttpImageRequestSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(HttpImageRequestSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();
};

// Скачивает изображение по HTTP и применяет его к слоту текстуры материала.
// Запрос выполняется асинхронно; текстура обновляется по завершении загрузки.
class HttpImageToTexture: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(HttpImageToTexture, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	PROP_PARAM(String, host, "eu.httpbin.org");	// Имя хоста HTTP-сервера
	PROP_PARAM(String, args, "/image/");		// Путь запроса (эндпоинт)
	PROP_PARAM(Int, surface, 0);				// Индекс поверхности материала на объекте
	PROP_PARAM(String, texture, "albedo");		// Имя слота текстуры в материале

private:
	void init();
	void update();

	Unigine::ImagePtr image;								// Скачанные данные изображения
	std::unique_ptr<AsyncTask<httplib::Result>> request;	// Дескриптор асинхронного HTTP-запроса
};
