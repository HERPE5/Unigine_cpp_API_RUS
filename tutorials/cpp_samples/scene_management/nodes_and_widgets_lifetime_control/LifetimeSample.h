#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"
#include <UnigineComponentSystem.h>

// Демонстрирует режимы управления временем жизни объектов для узлов и виджетов.
// LIFETIME_WORLD привязывает объекты к текущему миру (уничтожаются при смене мира),
// в то время как LIFETIME_ENGINE/LIFETIME_WINDOW сохраняет их между переходами миров.
// Статические указатели сохраняют ссылки между загрузками миров, чтобы показать поведение сохранности.
class LifetimeSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(LifetimeSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(File, node_to_spawn);

private:
	void init();
	void shutdown();

private:
	SampleDescriptionWindow description_window;

	static Unigine::NodePtr spawned_node;
	static Unigine::WidgetPtr spawned_widget;
};
