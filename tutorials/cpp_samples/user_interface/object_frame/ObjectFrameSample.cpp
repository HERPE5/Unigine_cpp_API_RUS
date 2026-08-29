// UI примера для захвата скриншотов с рамками объектов. При клике по кнопке рамки временно
// скрываются, фреймбуфер захватывается через asyncTransferTextureToImage, и как скриншот
// (PNG), так и метаданные рамок (JSON) сохраняются с именами файлов, содержащими временную метку.

#include "ObjectFrameSample.h"
#include "ObjectFrame.h"

#include <UnigineConsole.h>
#include <ctime>

#include "../../utils/Utils.h"

REGISTER_COMPONENT(ObjectFrameSample);

using namespace Unigine;

// Создаётся UI, регистрируется callback конца рендеринга.
void ObjectFrameSample::init()
{
	sample_description_window.createWindow();

	// Создаём кнопку скриншота, запускающую захват на следующем кадре
	auto param_box = sample_description_window.getParameterGroupBox();
	param_box->setText("Controls");
	WidgetButtonPtr button = WidgetButton::create("Snap Screenshot");
	button->getEventClicked().connect(*this, [this]() {
		// Скрываем рамки перед захватом для чистого скриншота
		ObjectFrame::setObjectFramesEnabled(false);
		grab_flag = true;
	});
	param_box->addChild(button, Gui::ALIGN_EXPAND);

	// Подпись показывает имя файла последнего сохранённого скриншота
	label = WidgetLabel::create("");
	param_box->addChild(label, Gui::ALIGN_LEFT);

	// Регистрируем callback для захвата фреймбуфера после рендеринга
	window = WindowManager::getMainWindow();
	if (window)
		window->getEventFuncEndRender().connect(*this, this,
			&ObjectFrameSample::snap_screenshot);

	// Собираем все компоненты ObjectFrame для экспорта метаданных
	ComponentSystem::get()->getComponentsInWorld(frames, true);
}

// Ресурсы UI очищаются.
void ObjectFrameSample::shutdown()
{
	sample_description_window.shutdown();
}

// Фреймбуфер захватывается, метаданные JSON сохраняются, PNG экспортируется асинхронно.
void ObjectFrameSample::snap_screenshot()
{
	if (!grab_flag)
		return;
	grab_flag = false;

	// Копируем текущий фреймбуфер во временную текстуру
	TexturePtr temporary_texture = Render::getTemporaryTexture2D(window->getClientRenderSize().x,
		window->getClientRenderSize().y, Texture::FORMAT_RGBA8);
	temporary_texture->copy2D();
	// Снова включаем рамки, теперь когда фреймбуфер захвачен
	ObjectFrame::setObjectFramesEnabled(true);

	// Генерируем имя файла с временной меткой
	time_t now = time(0);
	std::strftime(time_str.getRaw(), time_str.getMemoryUsage(), "%Y-%m-%d %H_%M_%S",
		std::localtime(&now));

	// Строим JSON с метаданными для всех видимых рамок
	JsonPtr json = Json::create();
	auto array = json->addChild("entities");
	array->setArray();
	for (const auto &it : frames)
	{
		if (!it->isVisible() || !it->isEnabled())
			continue;
		auto info = it->getJsonMeta();
		array->addChild(info);
	}
	json->save(joinPaths(getWorldRootPath(), "frame_data", time_str + ".json"));

	// Асинхронно передаём текстуру в изображение и сохраняем PNG
	Render::asyncTransferTextureToImage(nullptr, MakeCallback([time_str = this->time_str, label = this->label](ImagePtr image) {
		// Переворачиваем изображение, если рендер ещё не перевёрнут
		if (!Render::isFlipped())
			image->flipY();

		Log::message("Saving \"%s.png\"\n", time_str.get());
		image->save(joinPaths(getWorldRootPath(), "screenshots", time_str + ".png"));

		// Обновляем подпись статуса
		String msg = String::format("Saved screenshot \"%s.png\"", time_str.get());
		if(label)
			label->setText(msg);
	}),
		temporary_texture);
	Render::releaseTemporaryTexture(temporary_texture);
}
