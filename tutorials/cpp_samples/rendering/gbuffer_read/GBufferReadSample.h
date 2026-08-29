// UI примера для демонстрации извлечения G-buffer.
// Рендерит вращающийся узел и отображает извлечённые компоненты G-buffer
// (albedo, нормаль, глубину, шероховатость, металличность) на отдельных дисплеях.

#pragma once

#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

class GBufferRead;

// Демонстрирует извлечение G-buffer, рендеря вращающийся узел и отображая
// извлечённые компоненты буфера (albedo, нормаль, глубину, шероховатость, металличность) на экране.
class GBufferReadSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(GBufferReadSample, ComponentBase)

	// Более высокий порядок init гарантирует, что GBufferRead инициализируется первым
	COMPONENT_INIT(init, 10)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	// Узел, который рендерится для извлечения данных G-buffer
	PROP_PARAM(Node, node_to_render)

	// Узлы отображения для каждого компонента G-buffer
	PROP_PARAM(Node, roughness_node_param, "Roughness Display")
	PROP_PARAM(Node, metallness_node_param, "Metalness Display")
	PROP_PARAM(Node, albedo_node_param, "Albedo Display")
	PROP_PARAM(Node, normal_node_param, "Normal Display")
	PROP_PARAM(Node, depth_node_param, "Depth Display")

private:
	void init();
	void update();
	void shutdown();

	// Назначает извлечённую текстуру материалу узла отображения
	static void init_display(const Unigine::NodePtr &display_node, const Unigine::TexturePtr &texture);

private:
	// Угол вращения для рендеринга анимированного узла
	float phi{0.f};
	// Фиксированный угол тангажа для позиционирования камеры
	const float THETA{20.f};

	GBufferRead *g_buffer_read_component;

	SampleDescriptionWindow sample_description_window;

	// Хранит исходное состояние визуализатора для восстановления
	bool visualizer_enabled;
};
