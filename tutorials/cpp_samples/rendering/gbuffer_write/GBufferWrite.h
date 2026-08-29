// Демонстрирует изменение данных G-buffer после отложенного прохода.
// Применяет пользовательские свойства материала (цвет, эффект пластика) ко
// всему экрану, записывая в текстуры G-buffer.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>
#include "../../menu_ui/SampleDescriptionWindow.h"

// Изменяет содержимое G-buffer после отложенного прохода, применяя оттенок цвета
// и эффекты пластикового материала ко всему экрану с использованием рендеринга MRT.
class GBufferWrite : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(GBufferWrite, ComponentBase)

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	// Материал с шейдером, изменяющим данные G-buffer
	PROP_PARAM(Material, modify_buffer_material)

private:
	void init();
	void update();
	void shutdown();

	// Вызывается, когда G-buffer готов к изменению
	void g_buffers_ready_callback();

private:
	// Коэффициент смешивания эффекта (0 = нет эффекта, 1 = полный эффект)
	float influence{0.f};
	// Интенсивность эффекта пластикового материала
	float plastic{0.f};
	// Цвет оттенка, применяемый к albedo G-buffer
	Unigine::Math::vec4 color{Unigine::Math::vec4_one};

	SampleDescriptionWindow sample_description_window;

	// UI labels displaying current parameter values
	Unigine::WidgetLabelPtr plastic_label;
	Unigine::WidgetLabelPtr influence_label;
	Unigine::WidgetLabelPtr color_label;
};
