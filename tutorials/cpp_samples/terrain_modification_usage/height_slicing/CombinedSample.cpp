// Демонстрирует нарезку высоты terrain с помощью LandscapeLayerMap. Компонент HeightSlicer
// копирует данные высоты из исходного слоя terrain и применяет пороговое отсечение,
// изменяя albedo и высоту целевого слоя в зависимости от уровня нарезки.

#include "CombinedSample.h"

#include <UnigineInput.h>

REGISTER_COMPONENT(CombinedSample);

using namespace Unigine;
using namespace Math;

void CombinedSample::init()
{
	init_gui();

	// static_ptr_cast преобразует NodePtr в конкретный тип (LandscapeLayerMapPtr)
	// Используется, когда тип известен во время компиляции (быстрее, чем dynamic cast)
	source_lmap = static_ptr_cast<LandscapeLayerMap>(source_lmap_param.get());
	target_lmap = static_ptr_cast<LandscapeLayerMap>(target_lmap_param.get());

	// Получаем компонент HeightSlicer из связанного узла
	height_slicer = getComponent<HeightSlicer>(height_slicer_param);
	height_slicer->setSourceLmap(source_lmap);
	height_slicer->setTargetLmap(target_lmap);
	// Подключаем callback рисования текстуры для асинхронного рендеринга
	height_slicer->enable();

	// Применяем начальную высоту нарезки и запускаем операцию нарезки
	height_slicer->setSliceHeight(slice_height);
	height_slicer->run();
}

void CombinedSample::shutdown()
{
	shutdown_gui();
	// Отключаем callback'и, чтобы избежать висячих ссылок
	height_slicer->disable();
}

void CombinedSample::init_gui()
{
	sample_description_window.createWindow();

	auto window = sample_description_window.getWindow();

	// Ползунок настраивает порог высоты для нарезки terrain
	// Значения ниже порога отсекаются, открывая целевой слой
	sample_description_window.addFloatParameter("Slice height", "slice height", 1.f, 0.0f, 1.f,
		[this](float v) {
			height_slicer->setSliceHeight(v);
			// Запускаем пересчёт с новым порогом
			height_slicer->run();
		});
}

void CombinedSample::shutdown_gui()
{
	sample_description_window.shutdown();
}
