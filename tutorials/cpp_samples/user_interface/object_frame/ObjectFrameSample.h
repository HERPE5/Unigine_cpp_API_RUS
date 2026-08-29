// Контроллер примера для функции захвата скриншотов с рамками объектов.
// Захватывает фреймбуфер и сохраняет скриншот PNG вместе с файлом метаданных JSON.
// Временно скрывает рамки во время захвата для чистого скриншота.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

class ObjectFrame;

// Захватывает скриншоты с метаданными рамок для наборов данных обнаружения объектов.
class ObjectFrameSample final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(ObjectFrameSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

	void snap_screenshot();

	SampleDescriptionWindow sample_description_window;
	// Главное окно для захвата кадра
	Unigine::EngineWindowPtr window;
	// Подпись статуса, показывающая имя последнего сохранённого файла
	Unigine::WidgetLabelPtr label;

	// Все компоненты ObjectFrame в сцене
	Unigine::Vector<ObjectFrame *> frames;
	// Флаг, устанавливаемый при ожидании захвата скриншота
	bool grab_flag{false};
	// Буфер временной метки для имён файлов
	Unigine::String time_str{"yyyy-mm-dd hh_mm_ss"};
};
