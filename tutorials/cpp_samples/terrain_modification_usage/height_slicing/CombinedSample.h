// Демонстрирует нарезку высоты terrain с помощью LandscapeLayerMap. Компонент HeightSlicer
// копирует данные высоты из исходного слоя terrain и применяет пороговое отсечение,
// изменяя albedo и высоту целевого слоя в зависимости от уровня нарезки.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "HeightSlicer.h"

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>

class CombinedSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CombinedSample, Unigine::ComponentBase);
	// Порядок инициализации 1 гарантирует, что это выполняется после компонента HeightSlicer
	COMPONENT_INIT(init, 1);
	COMPONENT_SHUTDOWN(shutdown);

	// Узел, содержащий компонент HeightSlicer
	PROP_PARAM(Node, height_slicer_param, "Height Slicer");

	// Исходный слой предоставляет данные высоты для чтения
	PROP_PARAM(Node, source_lmap_param, "Source Lmap");
	// Целевой слой получает результат нарезки
	PROP_PARAM(Node, target_lmap_param, "Target Lmap");


private:
	void init();
	void shutdown();

	HeightSlicer *height_slicer{nullptr};
	// Нормализованный порог нарезки (0.0 = основание, 1.0 = максимальная высота)
	float slice_height{1.0f};

	Unigine::LandscapeLayerMapPtr source_lmap;
	Unigine::LandscapeLayerMapPtr target_lmap;

	bool flag{false};

	// UI (интерфейс)
	void init_gui();
	void shutdown_gui();

private:
	SampleDescriptionWindow sample_description_window;
	Unigine::WidgetSliderPtr slider;
};
