// Демонстрирует управление временем жизни объектов при смене миров. Узлы и виджеты
// можно установить в LIFETIME_WORLD (уничтожаются при смене мира) или LIFETIME_ENGINE/WINDOW
// (сохраняются до завершения работы движка). Статические указатели отслеживают объекты между перезагрузками.

#include "LifetimeSample.h"

REGISTER_COMPONENT(LifetimeSample);

using namespace Unigine;

Unigine::NodePtr LifetimeSample::spawned_node;
Unigine::WidgetPtr LifetimeSample::spawned_widget;

void LifetimeSample::init()
{
	// Статические указатели сохраняются между перезагрузками миров, чтобы продемонстрировать поведение времени жизни.
	// При первом запуске создаются и виджет, и узел. При последующих загрузках миров
	// их существование зависит от настройки времени жизни на момент смены мира.

	if (!spawned_widget)
	{
		// LIFETIME_WORLD: виджет уничтожается при смене или перезагрузке мира.
		// LIFETIME_WINDOW: виджет сохраняется до закрытия окна.
		WidgetButtonPtr button = WidgetButton::create("WIDGET FROM LIFETIME SAMPLE!");
		button->setFontSize(18);
		button->setLifetime(Widget::LIFETIME_WORLD);
		spawned_widget = button;
		Gui::getCurrent()->addChild(spawned_widget, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

		Log::message("New widget created!\n");
	}
	if (!spawned_node)
	{
		// LIFETIME_WORLD: узел уничтожается при смене мира.
		// LIFETIME_ENGINE: узел сохраняется на всю сессию движка.
		spawned_node = World::loadNode(node_to_spawn);
		spawned_node->setWorldTransform(node->getWorldTransform());
		spawned_node->setLifetime(Node::LIFETIME_WORLD);

		Log::message("New node created!\n");
	}

	description_window.createWindow(Gui::ALIGN_RIGHT);

	int widget_cb_current = 0;
	switch (spawned_widget->getLifetime())
	{
	case Widget::LIFETIME_WORLD:
		widget_cb_current = 0;
		break;
	case Widget::LIFETIME_WINDOW:
		widget_cb_current = 1;
		break;
	default:
		break;
	}

	description_window.addSwitchParameter("Widget lifetime", "Widget lifetime", widget_cb_current, {"World", "Window"},
		[](int v) {
			spawned_widget->setLifetime(v == 0 ? Widget::LIFETIME_WORLD : Widget::LIFETIME_WINDOW);
		});

	int node_cb_current = 0;
	switch (spawned_node->getLifetime())
	{
	case Node::LIFETIME_WORLD:
		node_cb_current = 0;
		break;
	case Node::LIFETIME_ENGINE:
		node_cb_current = 1;
		break;
	default:
		break;
	}

	description_window.addSwitchParameter("Node lifetime", "Node lifetime", node_cb_current, {"World", "Engine"},
		[](int v) {
			spawned_node->setLifetime(v == 0 ? Node::LIFETIME_WORLD : Node::LIFETIME_ENGINE);
		});
}

void LifetimeSample::shutdown()
{
	description_window.shutdown();
}
