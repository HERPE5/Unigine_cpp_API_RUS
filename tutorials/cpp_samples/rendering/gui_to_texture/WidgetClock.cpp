// Виджет часов реального времени, рендерящийся в текстуру. Обновляется только при изменении
// секунд, чтобы избежать лишних перерисовок. Демонстрирует ручное управление обновлением
// GUI с отключённым автообновлением GuiToTexture.

#include "WidgetClock.h"

#include "GuiToTexture.h"

REGISTER_COMPONENT(WidgetClock);

using namespace Unigine;

// Сохраняет новую позицию и немедленно перепозиционирует виджет.
void WidgetClock::setCenterPosition(const Math::ivec2 &pos)
{
	position = pos;
	adjust_screen_position();
}

// Виджет таймера создаётся и центрируется; автообновление отключается для ручного управления.
void WidgetClock::init()
{
	gui_to_texture = ComponentSystem::get()->getComponent<GuiToTexture>(node);
	// Автообновление отключено, так как перерисовка нужна только при изменении времени
	gui_to_texture->setAutoUpdateEnabled(false);

	// Получаем наш пользовательский GUI
	const GuiPtr gui = gui_to_texture->getGui();


	widget_timer = WidgetLabel::create(gui);
	widget_timer->setFontSize(150);

	// Добавляем виджет как дочерний в GUI
	gui->addChild(widget_timer, Gui::ALIGN_OVERLAP);

	setCenterPosition(gui_to_texture->getTextureResolution() / 2);

	previous_time = std::time(nullptr);
	// Задаём время и обновляем GUI
	set_time(previous_time);
}

// Время проверяется каждый кадр; текстура перерисовывается только при изменении секунд.
void WidgetClock::update()
{
	auto clock_equal = [](std::time_t left, std::time_t right) {
		return Math::abs(difftime(left, right)) < 1.;
	};

	const std::time_t now = std::time(nullptr);
	if (clock_equal(now, previous_time))
	{
		return;
	}

	set_time(now);
	previous_time = now;
}

// Виджет перепозиционируется, чтобы текст оставался центрированным относительно целевой позиции.
void WidgetClock::adjust_screen_position() const
{
	Math::ivec2 widget_size;
	widget_size.y = widget_timer->getTextRenderSize(widget_timer->getText()).y;
	widget_size.x = widget_timer->getTextRenderSize(widget_timer->getText()).x;
	widget_timer->setPositionX(position.x - widget_size.x / 2);
	widget_timer->setPositionY(position.y - widget_size.y / 2);
}

// Текст метки форматируется, текстура перерисовывается с обновлённым временем.
void WidgetClock::set_time(const std::time_t &time) const
{
	tm tstruct = *localtime(&time);
	widget_timer->setText(String::format("%02d:%02d:%02d", tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec));
	adjust_screen_position();
	gui_to_texture->renderToTexture();
}