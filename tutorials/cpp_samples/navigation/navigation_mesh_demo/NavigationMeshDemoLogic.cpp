// Интерактивная демонстрация навигационной сетки с несколькими агентами Seeker. Каждый Seeker использует
// PathRoute (create2D/create3D) для вычисления путей к целевому узлу. Радиус маршрута
// определяет минимальный зазор от препятствий. Агенты поворачиваются по направлению движения
// и проверяют позицию относительно навигационной области через проверки inside2D/inside3D.
// Когда Seeker достигает своей PathfindingTarget, цель перемещается в случайную
// позицию из предопределённого набора. Манипуляторы позволяют перетаскивать путевые точки в плоскости XY.

#include <UnigineVisualizer.h>
#include <UnigineConsole.h>
#include <UnigineComponentSystem.h>
#include <UniginePathFinding.h>
#include <UnigineGame.h>

#include "../../user_interface/widget_manipulators/Manipulators.h"
#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/navigation/Seeker.h"

class NavigationMeshDemoLogic : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NavigationMeshDemoLogic, Unigine::ComponentBase);
	COMPONENT_INIT(init, 2);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Float, route_radius, 0.15f);
	PROP_PARAM(Node, navigation);
	PROP_PARAM(Node, seekers);

	void setSeekersRouteRadius(float radius);

private:
	void init();
	void update();
	void shutdown();

	SampleDescriptionWindow sample_description_window;
	Manipulators *widget_manipulator;
};

REGISTER_COMPONENT(NavigationMeshDemoLogic);

using namespace Unigine;
using namespace Unigine::Math;

// Визуализатор включается, манипуляторы настраиваются для перемещения в плоскости XY, создаётся UI.
void NavigationMeshDemoLogic::init()
{
	Visualizer::setEnabled(true);
	Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);

	// Манипуляторы ограничены только перемещением по XY (Z определяется навигационной поверхностью)
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

	// Начальный радиус маршрута применяется ко всем агентам Seeker
	setSeekersRouteRadius(route_radius);

	{
		sample_description_window.createWindow();

		sample_description_window.addFloatParameter(
			"Route radius",
			"The radius required to move the point along the route inside the navigation area.",
			route_radius,
			0.f,
			1.f,
			[this](float radius) { setSeekersRouteRadius(radius); }
		);
	}
}

// Управление игроком переключается в зависимости от состояния манипулятора; навигационная сетка визуализируется.
void NavigationMeshDemoLogic::update()
{
	// Управление камерой отключается, пока пользователь перетаскивает манипулятор
	Game::getPlayer()->setControlled(!widget_manipulator->isActive());

	// Границы навигационной сетки и проходимые области отрисовываются для отладки
	if (navigation)
		navigation->renderVisualizer();
}

// Визуализатор отключается, мышь восстанавливается, UI очищается.
void NavigationMeshDemoLogic::shutdown()
{
	Visualizer::setEnabled(false);
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
	sample_description_window.shutdown();
}

// Радиус маршрута передаётся всем дочерним компонентам Seeker.
void NavigationMeshDemoLogic::setSeekersRouteRadius(float radius)
{
	if (seekers)
	{
		// Каждый дочерний узел с компонентом Seeker получает обновлённый радиус
		for (int i = 0; i < seekers->getNumChildren(); i += 1)
		{
			auto seeker_component = getComponent<Seeker>(seekers->getChild(i));
			if (seeker_component)
				seeker_component->setRouteRadius(radius);
		}

	}
}
