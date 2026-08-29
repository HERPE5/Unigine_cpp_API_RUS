// Демонстрирует WidgetSprite для отображения 2D-изображений в UI. Спрайт
// загружается из файла изображения, указанного через свойство компонента, с настраиваемой
// позицией и размерами.

#pragma once
#include <UnigineComponentSystem.h>

// Создаёт виджет спрайта для отображения 2D-изображений.
class Sprite : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Sprite, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Позиция на экране в пикселях
	PROP_PARAM(Vec2, position, Unigine::Math::vec2(275, 450));
	// Размеры виджета в пикселях
	PROP_PARAM(Vec2, size, Unigine::Math::vec2(100, 50));
	// Путь к файлу изображения для спрайта
	PROP_PARAM(File, sprite_image);

private:
	void init();
	void shutdown();

	// Контекст GUI для создания виджета
	Unigine::GuiPtr gui;
	// Экземпляр виджета спрайта
	Unigine::WidgetSpritePtr widget_sprite;
};