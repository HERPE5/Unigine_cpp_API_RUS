// Захватывает скриншот асинхронно в конце рендеринга кадра.
// Копирует цветовой буфер во временную текстуру, передаёт в Image в
// потоке GPU и сохраняет в файл. Обрабатывает переворот по Y для неперевёрнутых контекстов.

#include "Screenshot.h"

using namespace Unigine;
using namespace Math;

// Регистрирует callback рендеринга на указанном окне; отключается от предыдущего окна.
void Screenshot::setWindow(const Unigine::EngineWindowPtr &window)
{
	// Удаляем все существующие соединения перед переключением окон
	disconnectAll();
	if (!window)
		return;

	window_ = window;
	// Подписываемся на событие конца рендеринга, когда кадр завершён, но ещё не представлен
	window_->getEventFuncEndRender().connect(this, &Screenshot::render);
}

// Вызывается в конце каждого кадра; захватывает скриншот, когда установлен флаг grab.
void Screenshot::render()
{
	// Пропускаем захват, если grab() не был вызван
	if (!grab_flag)
	{
		return;
	}
	grab_flag = false;

	// Получаем временную текстуру, соответствующую размерам окна, для захвата
	TexturePtr temporary_texture = Render::getTemporaryTexture2D(window_->getClientSize().x,
		window_->getClientSize().y, Texture::FORMAT_RGBA8, 0);

	// Копируем содержимое текущего цветового буфера в нашу временную текстуру
	temporary_texture->copy2D();

	// Передаём данные текстуры в CPU-изображение асинхронно (неблокирующе)
	Render::asyncTransferTextureToImage(nullptr, MakeCallback([](ImagePtr image) {
		// Некоторые графические API рендерят перевёрнуто; переворачиваем при необходимости для правильной ориентации
		if (!Render::isFlipped())
		{
			image->flipY();
		}
		image->save("screenshot.dds");
		Log::message("Screenshot saved to \"data/screenshot.dds\"\n");
	}),
		temporary_texture);

	// Возвращаем текстуру в пул для повторного использования
	Render::releaseTemporaryTexture(temporary_texture);
}
