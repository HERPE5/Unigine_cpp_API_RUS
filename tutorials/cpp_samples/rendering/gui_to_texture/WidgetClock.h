// Виджет часов реального времени, отображаемый через рендеринг GUI-в-текстуру.
// Использует ручное обновление GUI (автообновление отключено) для перерисовки
// только когда отображаемое время действительно меняется, экономя ресурсы GPU.

#pragma once

#include <UnigineComponentSystem.h>

#include <ctime>

class GuiToTexture;

// Отображает системное время на текстуре, обновляясь только при изменении секунд.
class WidgetClock final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(WidgetClock, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	void setCenterPosition(const Unigine::Math::ivec2 &pos);

private:
	void init();
	void update();

	void adjust_screen_position() const;
	void set_time(const std::time_t &time) const;

private:
	// Виджет метки, показывающий формат HH:MM:SS
	Unigine::WidgetLabelPtr widget_timer{};
	// Закэшированное время для определения необходимости обновления
	std::time_t previous_time{};

	// Позиция центра виджета на текстуре
	Unigine::Math::ivec2 position;

	// Ссылка на рендерер GUI-в-текстуру
	GuiToTexture *gui_to_texture{};
};
