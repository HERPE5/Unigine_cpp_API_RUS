// Демонстрирует поиск пути по навигационной сетке с использованием PathRoute.
// Начальную и конечную точки можно перемещать через манипуляторы. Маршрут вычисляется
// с помощью create2D(), который находит кратчайший путь, ограниченный навигационной сеткой.
// Если действительного пути не существует, между точками рисуется красная линия.

#include <UnigineVisualizer.h>
#include <UnigineConsole.h>
#include <UnigineGame.h>
#include <UnigineComponentSystem.h>
#include <UniginePathFinding.h>

#include "../../user_interface/widget_manipulators/Manipulators.h"
#include "../../menu_ui/SampleDescriptionWindow.h"

class NavigationMeshLogic : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NavigationMeshLogic, Unigine::ComponentBase)
	COMPONENT_INIT(init, 2)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	PROP_PARAM(Node, path_start)
	PROP_PARAM(Node, path_end)
	PROP_PARAM(Node, navigation)
	PROP_PARAM(Float, route_radius, 0.15f)
	PROP_PARAM(Color, route_color, Unigine::Math::vec4_white)

private:
	void init();
	void update();
	void shutdown();

	Unigine::PathRoutePtr route;
	SampleDescriptionWindow sample_description_window;
	Manipulators *widget_manipulator;
};


REGISTER_COMPONENT(NavigationMeshLogic);

using namespace Unigine;
using namespace Unigine::Math;

// PathRoute создаётся, манипуляторы настраиваются, UI инициализируется.
void NavigationMeshLogic::init()
{
	Visualizer::setEnabled(true);
	Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);

	// Создаём объект PathRoute для вычисления путей по навигационной сетке.
	// Радиус определяет размер агента для расчёта зазора пути.
	route = PathRoute::create();
	route->setRadius(route_radius);

	// Настраиваем манипуляторы: ограничиваем движение только плоскостью XY
	// (Z ограничен поверхностью навигационной сетки), отключаем вращение и масштабирование
	widget_manipulator = getComponent<Manipulators>(node);
	if (widget_manipulator)
	{
		widget_manipulator->setZAxisTranslation(false);
		widget_manipulator->setXAxisRotation(false);
		widget_manipulator->setYAxisRotation(false);
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

// Маршрут пересчитывается каждый кадр; путь или линия ошибки визуализируются.
void NavigationMeshLogic::update()
{
	// Управление игроком отключается при перетаскивании манипуляторов
	Game::getPlayer()->setControlled(!widget_manipulator->isActive());

	// Отрисовываем каркас навигационной сетки для отладки
	if (navigation)
		navigation->renderVisualizer();

	if (path_start && path_end)
	{
		auto start = path_start->getWorldPosition();
		auto end = path_end->getWorldPosition();

		// Вычисляем 2D-путь (игнорируя различия по Z, проецируя на навигационную сетку)
		route->create2D(start, end);

		// Отрисовываем путь, если он достижим, иначе показываем красную линию "нет пути"
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
void NavigationMeshLogic::shutdown()
{
	Visualizer::setEnabled(false);
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
	sample_description_window.shutdown();
}
