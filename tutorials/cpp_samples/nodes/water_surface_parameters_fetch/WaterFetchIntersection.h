// Демонстрирует два метода запроса состояния поверхности воды: fetch (прямая выборка
// высоты) и intersection (пересечение луча с водой). Fetch быстрее, но менее точен
// при запросах под углом; intersection обрабатывает наклонные лучи с настраиваемой точностью.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>

class WaterFetchIntersection : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(WaterFetchIntersection, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел ObjectWaterGlobal для запроса
	PROP_PARAM(Node, water_node, "", "", "", "filter=ObjectWaterGlobal");

private:
	void init();
	void update();
	void shutdown();

	void init_gui();
	void shutdown_gui();
	Unigine::WidgetWindowPtr window;

	// Количество точек запроса для визуализации (sqrt даёт размеры сетки)
	int num_intersection = 100;
	// Размер отрисовываемых точек пересечения
	float intersect_point_size = 0.2f;
	// Угол луча для запросов пересечения (градусы от вертикали)
	float intersection_angle = 0.f;
	// Переключатель режима: true = fetch (выборка высоты), false = intersection (трассировка луча)
	bool fetch = true;
	SampleDescriptionWindow sample_description_window;
	// Флажок для переключения визуализации векторов нормалей
	Unigine::WidgetCheckBoxPtr normal_cb;
	// Закэшированный указатель на объект воды
	Unigine::ObjectWaterGlobalPtr water;
};
