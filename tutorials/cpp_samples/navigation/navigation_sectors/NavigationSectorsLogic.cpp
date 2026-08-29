// Демонстрирует поиск пути через несколько связанных навигационных секторов.
// NavigationSector определяет проходимую область в форме прямоугольника (в отличие от NavigationMesh,
// которая использует произвольную геометрию). Перекрывающиеся или соседние секторы
// соединяются автоматически; PathRoute::create2D() находит пути через них.

#include <UnigineVisualizer.h>
#include <UnigineConsole.h>
#include <UnigineGame.h>
#include <UnigineComponentSystem.h>
#include <UniginePathFinding.h>

#include "../../user_interface/widget_manipulators/Manipulators.h"
#include "../../menu_ui/SampleDescriptionWindow.h"

class NavigationSectorsLogic : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NavigationSectorsLogic, Unigine::ComponentBase);
	COMPONENT_INIT(init, 2);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);
	
	PROP_PARAM(Node, path_start);
	PROP_PARAM(Node, path_end);
	PROP_PARAM(Node, navigation);
	PROP_PARAM(Float, route_radius, 0.12f);
	PROP_PARAM(Color, route_color, Unigine::Math::vec4_white);
	
private:
	void init();
	void update();
	void shutdown();
	
	Unigine::PathRoutePtr route;
	SampleDescriptionWindow sample_description_window;
	Manipulators *widget_manipulator;
};

REGISTER_COMPONENT(NavigationSectorsLogic);

using namespace Unigine;
using namespace Unigine::Math;

// PathRoute создаётся, манипуляторы настраиваются, UI инициализируется.
void NavigationSectorsLogic::init()
{
	Visualizer::setEnabled(true);
	Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);

	// PathRoute создаётся для поиска пути через несколько секторов
	route = PathRoute::create();
	route->setRadius(route_radius);

	// Манипуляторы настраиваются с отключённым масштабированием
	widget_manipulator = getComponent<Manipulators>(node);
	if (widget_manipulator)
	{
		widget_manipulator->setXAxisScale(false);
		widget_manipulator->setYAxisScale(false);
		widget_manipulator->setZAxisScale(false);
	}
	
	{
		sample_description_window.createWindow();
		
		sample_description_window.addFloatParameter(
			"Route radius",
			"The radius required to move the point along the route inside the navigation area.",
			route_radius,
			0.f,
			1.f,
			[this](float value) {
				route->setRadius(value);
			}
		);
	}
}

// Маршрут пересчитывается; все секторы и путь визуализируются.
void NavigationSectorsLogic::update()
{
	// Управление игроком отключается при перетаскивании манипуляторов
	Game::getPlayer()->setControlled(!widget_manipulator->isActive());

	// Каждый навигационный сектор рендерится отдельно (секторы являются дочерними узлами узла навигации)
	if (navigation)
	{
		for (int i = 0; i < navigation->getNumChildren(); i += 1)
			navigation->getChild(i)->renderVisualizer();
	}

	if (path_start && path_end)
	{
		auto start = path_start->getWorldPosition();
		auto end = path_end->getWorldPosition();

		// Поиск пути автоматически пересекает границы секторов, когда секторы перекрываются
		route->create2D(start, end);

		if (route->isReached())
			route->renderVisualizer(route_color);

		else
			Visualizer::renderLine3D(start, end, vec4_red, Game::getIFps());
	}
	
	{
		auto status = String::format(
			"Route length: %.2f\n"
			"Route points: %d\n",
			route->getDistance(),
			route->getNumPoints()
		);
		
		sample_description_window.setStatus(status);
	}
}

// Визуализатор отключается, мышь восстанавливается, UI очищается.
void NavigationSectorsLogic::shutdown()
{
	Visualizer::setEnabled(false);
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
	sample_description_window.shutdown();
}
