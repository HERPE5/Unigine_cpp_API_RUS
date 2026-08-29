// Демонстрирует WidgetSprite для отображения 2D-изображений в UI. Спрайт
// загружается из файла изображения, указанного через свойство компонента, с настраиваемой
// позицией и размерами.

#include "Sprite.h"

REGISTER_COMPONENT(Sprite);

using namespace Unigine;
using namespace Math;

// Виджет спрайта создаётся из указанного файла изображения с настроенными размерами.
void Sprite::init()
{
	gui = WindowManager::getMainWindow()->getGui();

	// Создаём спрайт из файла изображения
	widget_sprite = WidgetSprite::create(gui, sprite_image.get());

	gui->addChild(widget_sprite, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	widget_sprite->setPosition(position.get().x, position.get().y);
	widget_sprite->setWidth(size.get().x);
	widget_sprite->setHeight(size.get().y);
}

// Виджет удаляется из GUI, ресурсы освобождаются.
void Sprite::shutdown()
{
	if (gui)
	{
		gui->removeChild(widget_sprite);

		widget_sprite.deleteLater();
	}
}
