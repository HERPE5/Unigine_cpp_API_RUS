// Предоставляет элементы управления UI для примера DynamicTextureFieldHeight. Позволяет во время выполнения
// настраивать разрешение карты высот, амплитуду волн, частоту и скорость анимации.
// Отображает превью-спрайт, показывающий сгенерированную текстуру карты высот.

#pragma once
#include <UnigineComponentSystem.h>
#include "../../menu_ui/SampleDescriptionWindow.h"

using namespace Unigine;
using namespace Math;

class DynamicTextureFieldHeightSample final : public Unigine::ComponentBase {
	COMPONENT_DEFINE(DynamicTextureFieldHeightSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел FieldHeight с компонентом DynamicTextureFieldHeight
	// Фильтр гарантирует, что в редакторе можно назначить только узлы FieldHeight
	PROP_PARAM(Node, field_height, "", "", "", "filter=FieldHeight");

private:
	void init();
	void shutdown();

private:

	SampleDescriptionWindow description_window;

	// Метка, показывающая текущее разрешение текстуры (например, "1024 X 1024")
	Unigine::WidgetLabelPtr size_map;
};
