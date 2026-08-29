#pragma once

#include <UnigineComponentSystem.h>

// Демонстрирует трассировку луча из экранных координат в мировое пространство.
// Преобразует позицию мыши в вектор направления через getDirectionFromMainWindow,
// затем выполняет World::getIntersection вдоль этого луча. Параметр маски пересечения
// фильтрует, какие объекты проверяются.
class IntersectionMouseRay : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(IntersectionMouseRay, Unigine::ComponentBase)
	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	PROP_PARAM(Float, distance, 100.0f);
	PROP_PARAM(Mask, mask, "intersection", 1);

private:
	void init();
	void update();
	void shutdown();

private:
	Unigine::Input::MOUSE_HANDLE init_handle;
	Unigine::WidgetLabelPtr current_hit_label{nullptr};
};
