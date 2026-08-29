// Демонстрирует WidgetIcon как переключаемую кнопку-изображение. При клике иконка
// переключается между состояниями вкл/выкл и отображает текущее состояние в оверлее
// консоли через callback EventClicked.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт кликабельный виджет иконки с функциональностью переключения.
class Icon : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Icon, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(500, 450));
	// Размеры иконки в пикселях
	PROP_PARAM(Vec2, size, Unigine::Math::vec2(32, 32));
	// Файл изображения для текстуры иконки
	PROP_PARAM(File, icon_image);

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета иконки
	Unigine::WidgetIconPtr widget_icon;
};
