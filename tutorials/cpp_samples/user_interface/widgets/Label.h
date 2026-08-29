// Демонстрирует WidgetLabel для отображения статического текста. Метка позиционируется
// и оформляется через свойства компонента, обработка событий для этого
// неинтерактивного типа виджета не требуется.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт виджет статической текстовой метки для отображения информации.
class Label : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Label, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(800, 150));
	// Текстовое содержимое для отображения
	PROP_PARAM(String, text, "Label");
	// Размер шрифта для текста метки
	PROP_PARAM(Int, font_size, 16)

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета метки
	Unigine::WidgetLabelPtr widget_label;
};