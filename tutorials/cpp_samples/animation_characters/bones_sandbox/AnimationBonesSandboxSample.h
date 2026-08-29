#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

#include "BonesSandbox.h"

// Интерактивная песочница для экспериментов с возможностями скелетной анимации.
// Предоставляет UI-редакторы для настройки IK-цепочек, LookAt-цепочек и ограничений костей
// в реальном времени, позволяя визуализировать и тестировать все доступные параметры.
class AnimationBonesSandboxSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesSandboxSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел ObjectMeshSkinned, содержащий скелетный меш
	PROP_PARAM(Node, mesh_skinned_node);

private:
	void init();
	void shutdown();

private:
	Unigine::ObjectMeshSkinnedLegacyPtr skinned;

	// Отдельное окно, содержащее все панели редакторов
	Unigine::EngineWindowViewportPtr editors_window;

	Unigine::WidgetHBoxPtr main_hbox;
	Unigine::WidgetVBoxPtr main_vbox;

	// UI-компоненты для различных функций анимации
	BoneSelection bone_selection;       // Дерево иерархии костей для выбора костей
	LookAtEditor look_at_editor;        // Редактор настройки LookAt-цепочки
	IKEditor ik_editor;                 // Редактор настройки IK-цепочки
	ConstraintEditor constraint_editor; // Редактор ограничений вращения костей
};
