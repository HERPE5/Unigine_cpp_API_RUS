// Скачивает изображения по HTTP и применяет их как текстуры на объектах сцены.
// Использует AsyncTask для неблокирующих запросов в фоновых потоках. Изображение
// загружается из тела ответа и назначается в слот текстуры материала.

#include "HttpImageRequestSample.h"

#include <UnigineWidgets.h>
#include <UnigineGame.h>

REGISTER_COMPONENT(HttpImageRequestSample);
REGISTER_COMPONENT(HttpImageToTexture);

using namespace Unigine;
using namespace Math;

// Фоновая очередь потоков запускается для асинхронных HTTP-операций.
void HttpImageRequestSample::init()
{
	ThreadQueue::get().run();
}

// Фоновая очередь потоков останавливается для корректного завершения.
void HttpImageRequestSample::shutdown()
{
	ThreadQueue::get().stop();
}

// HTTP GET-запрос создаётся и ставится в очередь для фонового выполнения.
void HttpImageToTexture::init()
{
	// Параметры захватываются по значению для потокобезопасного выполнения лямбды
	String host_str = host.get();
	String args_str = args.get();
	request = std::make_unique<AsyncTask<httplib::Result>>([host_str, args_str]() -> httplib::Result {
		httplib::Client cli(host_str.get());
		return cli.Get(args_str.get());
	});
}

// Завершение запроса опрашивается; скачанное изображение применяется к текстуре материала.
void HttpImageToTexture::update()
{
	// Асинхронный запрос проверяется на завершение каждый кадр
	if (request && request->isCompleted())
	{
		if (httplib::Result &result = request->get())
		{
			// HTTP 200 indicates successful download
			if (result->status == 200)
			{
				unsigned char *data = (unsigned char *)result->body.data();

				// Изображение создаётся из необработанного тела HTTP-ответа
				image = Image::create();
				bool loaded = image->load(data, toInt(result->body.size()));
				if (!loaded)
				{
					// Данные неудавшегося изображения сохраняются в файл для отладки
					Log::error("HttpImageToTexture can not load image\n");
					FilePtr file = File::create("wrong_image", "wb");
					file->write(data, result->body.size());
					file->close();
					Log::error("HttpImageToTexture save loaded image to 'data/wrong_image' file\n");
				}

				// Узел приводится к Object для доступа к поверхностям материала
				ObjectPtr object = checked_ptr_cast<Object>(node);
				if (!object)
				{
					Log::error("HttpImageToTexture can be assigned only to Objects: %s(%d) is %s\n", node->getName(), node->getID(), node->getTypeName());
					return;
				}

				// Унаследованный материал получается для возможности изменения для конкретного экземпляра
				auto mat = object->getMaterialInherit(surface.get());
				if (!mat)
				{
					Log::error("HttpImageToTexture can not find any material on %d surface of %s(%d)\n", surface.get(), node->getName(), node->getID());
					return;
				}

				// Индекс слота текстуры ищется по имени
				int slot = mat->findTexture(texture.get());
				if (slot == -1)
				{
					Log::error("HttpImageToTexture can not find texture slot '%s' in material on %d surface of %s(%d)\n", texture.get(), surface.get(), node->getName(), node->getID());
					return;
				}

				// Скачанное изображение назначается в слот текстуры материала
				mat->setTextureImage(slot, image);
			} else
				// Non-200 HTTP status is logged as informational message
				Log::message("%d %s\n", result->status, result->reason.c_str());

		} else
		{
			// Ошибка HTTP-клиента логируется (не удалось подключиться, таймаут и т.д.)
			String error = httplib::to_string(result.error()).c_str();
			Log::error("%s\n", error.get());
		}

		// Дескриптор запроса освобождается после обработки
		request.reset();
	}
}
