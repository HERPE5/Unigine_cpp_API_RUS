// Интерактивная демонстрация навигационных секторов с несколькими агентами Seeker. Использует области
// NavigationSector в форме прямоугольника вместо геометрии NavigationMesh. Перекрывающиеся секторы
// соединяются автоматически; Seeker-агенты плавно перемещаются через границы.

#include <UnigineVisualizer.h>
#include <UnigineConsole.h>
#include <UnigineComponentSystem.h>
#include <UniginePathFinding.h>
#include <UnigineGame.h>

#include "../../user_interface/widget_manipulators/Manipulators.h"
#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/navigation/Seeker.h"

class NavigationSectorsDemoLogic : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NavigationSectorsDemoLogic, Unigine::ComponentBase);
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

REGISTER_COMPONENT(NavigationSectorsDemoLogic);

using namespace Unigine;
using namespace Unigine::Math;

// Визуализатор включается, манипуляторы настраиваются, UI инициализируется.
void NavigationSectorsDemoLogic::init()
{
	Visualizer::setEnabled(true);
	Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);

	// Манипуляторы настраиваются с отключённым масштабированием
	widget_manipulator = getComponent<Manipulators>(node);
	if (widget_manipulator)
	{
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
			2.f,
			[this](float radius) { setSeekersRouteRadius(radius); }
		);
	}
}

// Управление игроком переключается в зависимости от состояния манипулятора; навигационные секторы визуализируются.
void NavigationSectorsDemoLogic::update()
{
	// Управление игроком отключается при перетаскивании манипуляторов
	Game::getPlayer()->setControlled(!widget_manipulator->isActive());

	// Границы навигационных секторов отрисовываются для отладки
	if (navigation)
		navigation->renderVisualizer();
}

// Визуализатор отключается, мышь восстанавливается, UI очищается.
void NavigationSectorsDemoLogic::shutdown()
{
	Visualizer::setEnabled(false);
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
	sample_description_window.shutdown();
}

// Радиус маршрута передаётся всем дочерним компонентам Seeker.
void NavigationSectorsDemoLogic::setSeekersRouteRadius(float radius)
{
	if (seekers)
	{
		for (int i = 0; i < seekers->getNumChildren(); i += 1)
		{
			auto seeker_component = getComponent<Seeker>(seekers->getChild(i));
			if (seeker_component)
				seeker_component->setRouteRadius(radius);
		}
	}
}
