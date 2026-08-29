#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует размещение стоп на неровных поверхностях с помощью IK-цепочек.
// Для определения контакта с землёй используется трассировка лучей: в каждом кадре луч
// отправляется вниз от каждой стопы для поиска поверхности. Позиция и вращение стопы затем
// корректируются в соответствии с высотой и нормалью поверхности.
class AnimationBonesSimpleFootPlacementSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesSimpleFootPlacementSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Ссылка на узел ObjectMeshSkinned, содержащий скелетный меш
	PROP_PARAM(Node, mesh_skinned_node);
	// Цепочка костей для левой ноги (например, бедро -> голень -> стопа)
	PROP_ARRAY(String, left_leg_bones);
	// Цепочка костей для правой ноги
	PROP_ARRAY(String, right_leg_bones);
	// Смещение по высоте от земли до опорной точки стопы
	PROP_PARAM(Float, foot_height, 0.1f);
	// Опциональная подвижная платформа/препятствие для тестирования размещения стоп
	PROP_PARAM(Node, obstacle);

private:
	enum FOOT
	{
		FOOT_LEFT = 0,
		FOOT_RIGHT,
		FOOT_NUM,
	};

private:
	void init();
	void update();
	void shutdown();

	// Вызывается перед решением IK для обновления целей стоп на основе результатов трассировки лучей
	void on_begin_ik_solvers();

private:
	// Манипуляторы для перемещения/вращения платформы-препятствия
	Unigine::WidgetManipulatorTranslatorPtr translator;
	Unigine::WidgetManipulatorRotatorPtr rotator;

	Unigine::ObjectMeshSkinnedLegacyPtr skinned;
	int chain_ids[FOOT_NUM];
	// Последняя кость в каждой цепочке (кость стопы, используемая как конечный эффектор)
	int effector_bones[FOOT_NUM];
};
