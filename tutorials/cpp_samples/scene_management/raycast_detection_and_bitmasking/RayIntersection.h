// Демонстрирует проверку пересечений на основе лучей с фильтрацией по маске.
// Лазерный луч пускается каждый кадр, а цветные стены можно выборочно
// включать или исключать с помощью чекбоксов маски пересечения.

#pragma once

#include <UnigineComponentSystem.h>
#include "../../menu_ui/SampleDescriptionWindow.h"

// Пускает лазерный луч и визуализирует попадания с UI фильтрации на основе маски.
class RayIntersection : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(RayIntersection, Unigine::ComponentBase)
	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	// Визуальный лазерный луч, растягивающийся до точки попадания
	PROP_PARAM(Node, laser_ray, nullptr);
	// Индикатор точки попадания, позиционируемый в месте пересечения
	PROP_PARAM(Node, laser_hit, nullptr);
	// Максимальная длина луча при отсутствии пересечения
	PROP_PARAM(Float, laser_distance, 25.0f);
	// Битовая маска, определяющая, какие объекты могут быть поражены
	PROP_PARAM(Mask, intersection_mask, "intersection", 1);

private:
	// Хранит точку пересечения и нормаль для визуализации попадания
	Unigine::WorldIntersectionNormalPtr intersection;
	// Исходный масштаб, закэшированный для динамической подстройки длины
	Unigine::Math::vec3 laser_ray_scale = Unigine::Math::vec3_one;

	// Состояние GUI для валидации бинарного ввода маски
	Unigine::String prev_text = "";
	Unigine::ObjectGuiPtr mask_text = nullptr;
	SampleDescriptionWindow window;
	Unigine::WidgetLabelPtr current_hit;
	// Имена стен для каждой позиции бита в маске
	Unigine::Vector<const char *> walls{
		"RED", "GREEN", "BLUE", "BLACK", "WHITE", "YELLOW", "GRAY", "ORANGE"};
	// HTML-цвета для отображения форматированного текста
	Unigine::Vector<const char *> colors{
		"#FF4D4D", // RED — ярко-красный
		"#00ff7f", // GREEN — ярко-зелёный (весенне-зелёный)
		"#3399ff", // BLUE — светло-синий
		"#000000", // BLACK — чистый чёрный
		"#ffffff", // WHITE — чистый белый
		"#ffff66", // YELLOW — светло-жёлтый (лимонный)
		"#cccccc", // GRAY — светло-серый
		"#ff9933"  // ORANGE — ярко-оранжевый
	};

	void init_gui();
	
	void init();
	void update();
	void shutdown();

	Unigine::String current_node;
};