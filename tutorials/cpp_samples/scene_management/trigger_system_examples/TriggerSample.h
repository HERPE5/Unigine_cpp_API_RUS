// Полная демонстрация триггеров, показывающая несколько типов триггеров.
// Постаменты меняют цвет, когда цель входит в границы каждого триггера.
// Охватывает PhysicalTrigger, WorldTrigger, пользовательские математические триггеры и NodeTrigger.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>
#include <UnigineWorlds.h>
#include <UniginePhysicals.h>
#include <UnigineVisualizer.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

// Настраивает все типы триггеров и подключает callback входа/выхода к изменениям материалов.
class TriggerSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TriggerSample, ComponentBase);

	// Целевой объект, входящий в объёмы триггеров
	PROP_PARAM(Node, target_to_check);
	// Визуальные индикаторы, меняющие цвет при срабатывании
	PROP_PARAM(Node, postament_physics_sphere);
	PROP_PARAM(Node, postament_physics_capsule);
	PROP_PARAM(Node, postament_physics_cylinder);
	PROP_PARAM(Node, postament_physics_box);
	PROP_PARAM(Node, postament_world);
	PROP_PARAM(Node, postament_math_sphere);
	PROP_PARAM(Node, postament_math_box);
	PROP_PARAM(Node, postament_intersection_box);
	PROP_PARAM(Node, postament_intersection_sphere);

	// Узлы триггеров для демонстрации каждого типа триггера
	PROP_PARAM(Node, trigger_physics_sphere_node);
	PROP_PARAM(Node, trigger_physics_capsule_node);
	PROP_PARAM(Node, trigger_physics_cylinder_node);
	PROP_PARAM(Node, trigger_physics_box_node);
	PROP_PARAM(Node, trigger_world_node);
	PROP_PARAM(Node, trigger_math_box_node);
	PROP_PARAM(Node, trigger_math_sphere_node);
	PROP_PARAM(Node, trigger_intersection_node_box);
	PROP_PARAM(Node, trigger_intersection_node_sphere);
	PROP_PARAM(Node, trigger_node_node);
	PROP_PARAM(Node, trigger_node_parent_node);
	PROP_PARAM(Node, trigger_node_text);

	// Материалы, переключаемые на постаментах для индикации состояния триггера
	PROP_PARAM(Material, postament_mat);
	PROP_PARAM(Material, postament_mat_triggered);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();

private:
	// Экземпляр WorldTrigger для обнаружения на основе узлов
	Unigine::WorldTriggerPtr world_trigger;

	// Экземпляры PhysicalTrigger для обнаружения физических тел
	Unigine::PhysicalTriggerPtr physical_trigger_sphere;
	Unigine::PhysicalTriggerPtr physical_trigger_capsule;
	Unigine::PhysicalTriggerPtr physical_trigger_cylinder;
	Unigine::PhysicalTriggerPtr physical_trigger_box;

	// Сохранённый режим визуализатора, восстанавливаемый при завершении работы
	Unigine::Visualizer::MODE visualizer_mode;

	SampleDescriptionWindow sample_description_window;
};
