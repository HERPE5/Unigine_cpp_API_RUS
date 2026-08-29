// Полная демонстрация триггеров. Показывает PhysicalTrigger (физические тела),
// WorldTrigger (узлы), WorldMathTrigger (пользовательская проверка точки в границах), WorldIntersectionTrigger
// (пространственные запросы) и NodeTrigger (события включения/позиции). Каждый тип триггера
// меняет цвет материала постамента, когда цель входит в его границы или покидает их.

#include "TriggerSample.h"

#include "MathTriggerComponent.h"

#include <UnigineConsole.h>
#include <UnigineVisualizer.h>
#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(TriggerSample);


// Ищем пересечения только с material ball
namespace
{
constexpr int MATERIAL_BALL_INTERSECTION_MASK = 0x7;
} // анонимное пространство имён

// Настраиваются все типы триггеров, подключаются callback входа/выхода.
void TriggerSample::init()
{
	// Включаем визуализатор с тестом глубины для отображения границ триггеров
	Visualizer::setEnabled(true);
	visualizer_mode = Visualizer::getMode();
	Visualizer::setMode(Visualizer::MODE_ENABLED_DEPTH_TEST_ENABLED);

	// Приводим узлы триггеров к PhysicalTrigger для обнаружения на основе физики
	physical_trigger_sphere = checked_ptr_cast<PhysicalTrigger>(trigger_physics_sphere_node.get());
	physical_trigger_capsule = checked_ptr_cast<PhysicalTrigger>(trigger_physics_capsule_node.get());
	physical_trigger_cylinder = checked_ptr_cast<PhysicalTrigger>(trigger_physics_cylinder_node.get());
	physical_trigger_box = checked_ptr_cast<PhysicalTrigger>(trigger_physics_box_node.get());

	// Получаем пользовательские компоненты-триггеры на основе математики
	WorldMathTrigger *math_trigger_box = getComponent<WorldMathTrigger>(
		trigger_math_box_node.get());
	WorldMathTrigger *math_trigger_sphere = getComponent<WorldMathTrigger>(
		trigger_math_sphere_node.get());
	world_trigger = checked_ptr_cast<WorldTrigger>(trigger_world_node.get());

	// Получаем компоненты-триггеры на основе пересечения
	WorldIntersectionTrigger *world_intersections_trigger_sphere
		= getComponent<WorldIntersectionTrigger>(trigger_intersection_node_sphere.get());
	WorldIntersectionTrigger *world_intersectons_trigger_box
		= getComponent<WorldIntersectionTrigger>(trigger_intersection_node_box.get());

	// Регистрируем целевой объект в математических триггерах для отслеживания
	math_trigger_box->addObject(target_to_check);
	math_trigger_sphere->addObject(target_to_check);

	NodeTriggerPtr node_trigger = checked_ptr_cast<NodeTrigger>(trigger_node_node.get());

	// Callback'и PhysicalTrigger - обнаруживают физические тела, входящие в формы триггеров или покидающие их.
	// У каждого типа формы (сфера, капсула, цилиндр, бокс) свой триггер и постамент.

	// Sphere PhysicalTrigger: подсвечивает постамент сферы, когда тело входит
	physical_trigger_sphere->getEventEnter().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_sphere.get());
			obj->setMaterial(postament_mat_triggered, 0);
		});

	// Sphere PhysicalTrigger: восстанавливает постамент сферы, когда тело выходит
	physical_trigger_sphere->getEventLeave().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_sphere.get());
			obj->setMaterial(postament_mat, 0);
		});

	// Capsule PhysicalTrigger: подсвечивает постамент капсулы, когда тело входит
	physical_trigger_capsule->getEventEnter().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_capsule.get());
			obj->setMaterial(postament_mat_triggered, 0);
		});

	// Capsule PhysicalTrigger: восстанавливает постамент капсулы, когда тело выходит
	physical_trigger_capsule->getEventLeave().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_capsule.get());
			obj->setMaterial(postament_mat, 0);
		});

	// Cylinder PhysicalTrigger: подсвечивает постамент цилиндра, когда тело входит
	physical_trigger_cylinder->getEventEnter().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_cylinder.get());
			obj->setMaterial(postament_mat_triggered, 0);
		});

	// Cylinder PhysicalTrigger: восстанавливает постамент цилиндра, когда тело выходит
	physical_trigger_cylinder->getEventLeave().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_cylinder.get());
			obj->setMaterial(postament_mat, 0);
		});

	// Box PhysicalTrigger: подсвечивает постамент бокса, когда тело входит
	physical_trigger_box->getEventEnter().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_box.get());
			obj->setMaterial(postament_mat_triggered, 0);
		});

	// Box PhysicalTrigger: восстанавливает постамент бокса, когда тело выходит
	physical_trigger_box->getEventLeave().connect(*this, [this](const BodyPtr &body_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_physics_box.get());
			obj->setMaterial(postament_mat, 0);
		});

	// Callback'и WorldTrigger - обнаруживают узлы, входящие в объём бокса, выровненного по осям, или покидающие его.
	// В отличие от PhysicalTrigger, работает с любым узлом (не только физическими телами).

	// WorldTrigger: подсвечивает мировой постамент, когда узел входит в AABB
	world_trigger->getEventEnter().connect(*this, [this](const NodePtr &node_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_world.get());
			obj->setMaterial(postament_mat_triggered, 0);
		});

	// WorldTrigger: восстанавливает мировой постамент, когда узел покидает AABB
	world_trigger->getEventLeave().connect(*this, [this](const NodePtr &node_trigger)
		{
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_world.get());
			obj->setMaterial(postament_mat, 0);
		});

	// Callback'и WorldMathTrigger - пользовательский компонент с проверками "точка в границах".
	// Требует ручной регистрации объекта через addObject(); проверяет позицию каждый кадр.

	// Триггер математической сферы: подсвечивает постамент math_sphere, когда зарегистрированный узел входит
	math_trigger_sphere->addCallback(WorldMathTrigger::CALLBACK_TRIGGER_ENTER,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(
				postament_math_sphere.get());
			obj->setMaterial(postament_mat_triggered, 0);
		}));

	// Триггер математической сферы: восстанавливает постамент math_sphere, когда зарегистрированный узел выходит
	math_trigger_sphere->addCallback(WorldMathTrigger::CALLBACK_TRIGGER_LEAVE,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(
				postament_math_sphere.get());
			obj->setMaterial(postament_mat, 0);
		}));

	// Callback'и WorldIntersectionTrigger - используют пространственные запросы World::getIntersection.
	// Автоматически обнаруживает любой узел в границах; фильтрует по маске пересечения.

	// Триггер пересечения сферы: подсвечивает постамент intersection_sphere для подходящих объектов
	world_intersections_trigger_sphere->addCallback(
		WorldIntersectionTrigger::CALLBACK_TRIGGER_ENTER,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectPtr obj = checked_ptr_cast<Object>(node_trigger);
			if (obj && (obj->getIntersectionMask(0) == MATERIAL_BALL_INTERSECTION_MASK))
			{
				ObjectMeshStaticPtr postament = checked_ptr_cast<ObjectMeshStatic>(
					postament_intersection_sphere.get());
				postament->setMaterial(postament_mat_triggered, 0);
			}
		}));

	// Триггер пересечения сферы: восстанавливает постамент intersection_sphere, когда объект выходит
	world_intersections_trigger_sphere->addCallback(
		WorldIntersectionTrigger::CALLBACK_TRIGGER_LEAVE,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectPtr obj = checked_ptr_cast<Object>(node_trigger);
			if (obj && (obj->getIntersectionMask(0) == MATERIAL_BALL_INTERSECTION_MASK))
			{
				ObjectMeshStaticPtr postament = checked_ptr_cast<ObjectMeshStatic>(
					postament_intersection_sphere.get());
				postament->setMaterial(postament_mat, 0);
			}
		}));

	// Триггер математического бокса: подсвечивает постамент math_box, когда зарегистрированный узел входит
	math_trigger_box->addCallback(WorldMathTrigger::CALLBACK_TRIGGER_ENTER,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_math_box.get());
			obj->setMaterial(postament_mat_triggered, 0);
		}));

	// Триггер математического бокса: восстанавливает постамент math_box, когда зарегистрированный узел выходит
	math_trigger_box->addCallback(WorldMathTrigger::CALLBACK_TRIGGER_LEAVE,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectMeshStaticPtr obj = checked_ptr_cast<ObjectMeshStatic>(postament_math_box.get());
			obj->setMaterial(postament_mat, 0);
		}));

	// Триггер пересечения бокса: подсвечивает постамент intersection_box для подходящих объектов
	world_intersectons_trigger_box->addCallback(WorldIntersectionTrigger::CALLBACK_TRIGGER_ENTER,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectPtr obj = checked_ptr_cast<Object>(node_trigger);
			if (obj && (obj->getIntersectionMask(0) == MATERIAL_BALL_INTERSECTION_MASK))
			{
				ObjectMeshStaticPtr postament = checked_ptr_cast<ObjectMeshStatic>(
					postament_intersection_box.get());
				postament->setMaterial(postament_mat_triggered, 0);
			}
		}));

	// Триггер пересечения бокса: восстанавливает постамент intersection_box, когда объект выходит
	world_intersectons_trigger_box->addCallback(WorldIntersectionTrigger::CALLBACK_TRIGGER_LEAVE,
		MakeCallback([this](const NodePtr &node_trigger) {
			ObjectPtr obj = checked_ptr_cast<Object>(node_trigger);
			if (obj && obj->getIntersectionMask(0) == MATERIAL_BALL_INTERSECTION_MASK)
			{
				ObjectMeshStaticPtr postament = checked_ptr_cast<ObjectMeshStatic>(
					postament_intersection_box.get());
				postament->setMaterial(postament_mat, 0);
			}
		}));

	// Callback'и NodeTrigger - срабатывают при включении/отключении или перемещении узла

	// Обновляет цвет текста в зависимости от состояния включения триггера
	node_trigger->getEventEnabled().connect(*this, [this](const NodeTriggerPtr &trigger)
		{
			auto object_text = checked_ptr_cast<ObjectText>(trigger_node_text.get());
			if(trigger->isEnabled())
				object_text->setTextColor(vec4_white);
			else
				object_text->setTextColor(vec4_red);
		});

	// Анимирует цвет материала родителя при изменении позиции триггера
	node_trigger->getEventPosition().connect(*this, [](const NodeTriggerPtr &trigger)
		{
			ObjectPtr parent = checked_ptr_cast<Object>(trigger->getParent());
			MaterialPtr material = parent->getMaterialInherit(0);
			vec4 color = material->getParameterFloat4("albedo_color");
			color.z += Game::getIFps();
			if (color.z > 1.0f)
				color.z = 0.0f;
			material->setParameterFloat4("albedo_color", color);
		});

	// Настройка UI

	sample_description_window.createWindow();
	WidgetGroupBoxPtr parameters = sample_description_window.getParameterGroupBox();
	auto node_trigger_checkbox = WidgetCheckBox::create("Cube Active");
	parameters->addChild(node_trigger_checkbox, Gui::ALIGN_LEFT);
	// Чекбокс переключает состояние включения родительского узла NodeTrigger
	node_trigger_checkbox->getEventChanged().connect(*this, [this, node_trigger_checkbox]()
		{
			trigger_node_parent_node.get()->setEnabled(node_trigger_checkbox->isChecked());
		});
	node_trigger_checkbox->setChecked(true);
}

// Границы триггеров визуализируются каждый кадр для отладочной наглядности.
void TriggerSample::update()
{
	Visualizer::renderBoundBox(world_trigger->getBoundBox(),
		trigger_world_node.get()->getWorldTransform(), vec4_red);

	physical_trigger_sphere->renderVisualizer();
	physical_trigger_capsule->renderVisualizer();
	physical_trigger_cylinder->renderVisualizer();
	physical_trigger_box->renderVisualizer();
}

// Режим визуализатора восстанавливается, UI очищается.
void TriggerSample::shutdown()
{
	Visualizer::setMode(visualizer_mode);
	Visualizer::setEnabled(false);

	sample_description_window.shutdown();
}
