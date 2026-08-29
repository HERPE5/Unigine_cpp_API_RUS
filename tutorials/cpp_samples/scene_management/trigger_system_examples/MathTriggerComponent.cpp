// Пользовательские компоненты-триггеры с проверкой границ математическим способом. WorldMathTrigger
// проверяет зарегистрированные объекты относительно границ сферы или бокса каждый кадр с помощью проверок
// "точка внутри". WorldIntersectionTrigger использует пространственные запросы World::getIntersection
// для обнаружения любых узлов, входящих в объём или покидающих его.

#include "MathTriggerComponent.h"

#include <UnigineConsole.h>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(WorldMathTrigger);

using namespace Unigine;
using namespace Math;

// Границы сферы и бокса инициализируются в мировой позиции компонента.
void WorldMathTrigger::init()
{
	Vec3 translation = node->getWorldTransform().getTranslate();
	Vec3 coordinates_for_bound_box_min = -Vec3(bound_box_size / 2.0f);
	Vec3 coordinates_for_bound_box_max = Vec3(bound_box_size / 2.0f);
	bound_box.set(vec3(coordinates_for_bound_box_min), vec3(coordinates_for_bound_box_max));
	bound_box.setTransform(node->getWorldTransform());

	bound_sphere.set(vec3(translation), bound_sphere_size.get() / 2.0f);
	bound_sphere.setTransform(node->getWorldTransform());
}


// Границы перепозиционируются, все объекты проверяются на события входа/выхода.
void WorldMathTrigger::update()
{
	replace_bounds();

	if (debug)
	{
		visualize_bounds();
	}
	check_entered();
	check_leave();
}


// Объекты, покинувшие объём, удаляются из списка entered, вызывается callback.
void WorldMathTrigger::check_leave()
{
	for (const auto &obj : objects)
	{
		if (!entered.contains(obj))
			continue;
		if (obj.isDeleted())
		{
			entered.removeOneFast(obj);
			continue;
		}
		bool is_inside = is_sphere ? check_sphere(obj) : check_box(obj);
		if (!is_inside)
		{
			entered.removeOneFast(obj);
			if (is_callback(CALLBACK_TRIGGER_LEAVE))
				run_callback(CALLBACK_TRIGGER_LEAVE, obj);
		}
	}
}

// Границы перепозиционируются, следуя за узлом компонента.
void WorldMathTrigger::replace_bounds()
{
	Vec3 translation = node->getWorldTransform().getTranslate();
	Vec3 coordinates_for_bound_box_min = -Vec3(bound_box_size / 2.0f) + translation;
	Vec3 coordinates_for_bound_box_max = Vec3(bound_box_size / 2.0f) + translation;
	bound_box.set(vec3(coordinates_for_bound_box_min), vec3(coordinates_for_bound_box_max));
	bound_sphere.set(vec3(translation), bound_sphere_size.get() / 2.0f);
}

// Отладочный каркас рендерится для активной формы границ.
void WorldMathTrigger::visualize_bounds()
{
	if (is_sphere)
		Visualizer::renderSphere(bound_sphere_size / 2.0f, node->getWorldTransform(), vec4_red);
	else
		Visualizer::renderBoundBox(bound_box, Mat4_identity, vec4_red);
}


// Объекты, вновь оказавшиеся внутри объёма, добавляются в список entered, вызывается callback.
void WorldMathTrigger::check_entered()
{
	for (const auto &obj : objects)
	{
		if (entered.contains(obj))
			continue;
		bool is_inside = is_sphere ? check_sphere(obj) : check_box(obj);
		if (is_inside)
		{
			entered.push_back(obj);
			if (is_callback(CALLBACK_TRIGGER_ENTER))
				run_callback(CALLBACK_TRIGGER_ENTER, obj);
		}
	}
}


// Проверяет, находится ли позиция объекта внутри границ бокса.
inline bool WorldMathTrigger::check_box(const NodePtr &obj) const
{
	return bound_box.insideValid(vec3(obj->getTransform().getTranslate()));
}


// Проверяет, находится ли позиция объекта внутри границ сферы.
inline bool WorldMathTrigger::check_sphere(const NodePtr &obj) const
{
	return bound_sphere.insideValid(vec3(obj->getTransform().getTranslate()));
}


void *WorldMathTrigger::addCallback(CALLBACK_TRIGGER callback, CallbackBase1<NodePtr> *func)
{
	return signal[callback].add(func);
}


bool WorldMathTrigger::removeCallback(CALLBACK_TRIGGER callback, void *id)
{
	return signal[callback].remove(id);
}


void WorldMathTrigger::clearCallbacks(CALLBACK_TRIGGER callback)
{
	signal[callback].clear();
}


inline bool WorldMathTrigger::is_callback(CALLBACK_TRIGGER callback) const
{
	return signal[callback].size() > 0 ? true : false;
}


inline void WorldMathTrigger::run_callback(CALLBACK_TRIGGER callback, const NodePtr &obj)
{
	signal[callback].invoke(obj);
}


// Все зарегистрированные callback очищаются при уничтожении компонента.
void WorldMathTrigger::shutdown()
{
	for (int i = 0; i < CALLBACK_TRIGGER_NUM; i++)
	{
		signal[i].clear();
	}
}

void WorldMathTrigger::addObject(const Unigine::NodePtr &obj)
{
	objects.push_back(obj);
}

void WorldMathTrigger::addObjects(const Unigine::Vector<Unigine::NodePtr> &input_objects)
{
	objects.append(input_objects);
	;
}

void WorldMathTrigger::removeObject(const Unigine::NodePtr &obj)
{
	auto it = objects.find(obj);
	if (it != objects.end())
		objects.remove(it);
}


// Компонент World Intersection Trigger

REGISTER_COMPONENT(WorldIntersectionTrigger);

// Границы сферы и бокса инициализируются в мировой позиции компонента.
void WorldIntersectionTrigger::init()
{
	Vec3 translation = node->getWorldTransform().getTranslate();
	Vec3 coordinates_for_bound_box_min = -Vec3(bound_box_size / 2.0f) + translation;
	Vec3 coordinates_for_bound_box_max = Vec3(bound_box_size / 2.0f) + translation;
	bound_box.set(vec3(coordinates_for_bound_box_min), vec3(coordinates_for_bound_box_max));
	bound_sphere.set(vec3(translation), bound_sphere_size.get() / 2.0f);
}

// Запрашивается мировое пересечение, вызываются callback входа/выхода.
void WorldIntersectionTrigger::update()
{
	replace_bounds();

	if (debug)
	{
		visualize_bounds();
	}

	get_inside_nodes();
	check_entered();
	check_leave();
}

// Все зарегистрированные callback очищаются при уничтожении компонента.
void WorldIntersectionTrigger::shutdown()
{
	for (int i = 0; i < CALLBACK_TRIGGER_NUM; i++)
	{
		signal[i].clear();
	}
}

// Узлы, найденные в текущем запросе, но не в списке entered, вызывают callback входа.
void WorldIntersectionTrigger::check_entered()
{
	for (const auto &it : inside)
	{
		if (entered.find(it) == entered.end())
		{
			entered.push_back(it);
			run_callback(CALLBACK_TRIGGER_ENTER, it);
		}
	}
}

// Узлы из entered, отсутствующие в текущем запросе, удаляются, вызывается callback выхода.
void WorldIntersectionTrigger::check_leave()
{
	// Обратная итерация: removeOneFast меняет местами с последним элементом, безопасно при движении назад
	for (int i = entered.size() - 1; i >= 0; i--)
	{
		if (entered[i].isDeleted())
		{
			entered.removeFast(i);
			continue;
		}

		if (inside.find(entered[i]) == inside.end())
		{
			run_callback(CALLBACK_TRIGGER_LEAVE, entered[i]);
			entered.removeFast(i);
		}
	}
}

// Границы перепозиционируются, следуя за узлом компонента.
void WorldIntersectionTrigger::replace_bounds()
{
	Vec3 translation = node->getWorldTransform().getTranslate();
	Vec3 coordinates_for_bound_box_min = -Vec3(bound_box_size / 2.0f) + translation;
	Vec3 coordinates_for_bound_box_max = Vec3(bound_box_size / 2.0f) + translation;
	bound_box.set(vec3(coordinates_for_bound_box_min), vec3(coordinates_for_bound_box_max));
	bound_sphere.set(vec3(translation), bound_sphere_size.get() / 2.0f);
}

// Отладочный каркас рендерится для активной формы границ.
void WorldIntersectionTrigger::visualize_bounds()
{
	if (is_sphere)
		Visualizer::renderSphere(bound_sphere_size / 2.0f, node->getWorldTransform(), vec4_red);
	else
		Visualizer::renderBoundBox(bound_box, Mat4_identity, vec4_red);
}

// Запрос мирового пересечения возвращает все узлы, находящиеся в данный момент внутри границ.
void WorldIntersectionTrigger::get_inside_nodes()
{
	if (is_sphere)
		World::getIntersection(bound_sphere, inside);
	else
		World::getIntersection(bound_box, inside);
}


void *WorldIntersectionTrigger::addCallback(CALLBACK_TRIGGER callback, CallbackBase1<NodePtr> *func)
{
	return signal[callback].add(func);
}


bool WorldIntersectionTrigger::removeCallback(CALLBACK_TRIGGER callback, void *id)
{
	return signal[callback].remove(id);
}


void WorldIntersectionTrigger::clearCallbacks(CALLBACK_TRIGGER callback)
{
	signal[callback].clear();
}


inline bool WorldIntersectionTrigger::is_callback(CALLBACK_TRIGGER callback) const
{
	return signal[callback].size() > 0 ? true : false;
}


inline void WorldIntersectionTrigger::run_callback(CALLBACK_TRIGGER callback, const NodePtr &obj)
{
	signal[callback].invoke(obj);
}
