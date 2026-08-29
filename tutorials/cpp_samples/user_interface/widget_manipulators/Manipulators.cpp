// Реализует манипулирование объектами с использованием виджетов WidgetManipulator (Translator, Rotator,
// Scaler). Объекты выбираются через пересечение луча по клику мыши и трансформируются
// с помощью горячих клавиш (W/E/R). Поддерживает режимы мирового и локального базиса с управлением по осям.

#include "Manipulators.h"
#include <UnigineGame.h>
#include <UniginePlayers.h>
#include <UnigineWidgets.h>
#include <UnigineWorld.h>

REGISTER_COMPONENT(Manipulators);

using namespace Unigine;
using namespace Math;

// Рекурсивно расширяет ограничивающую сферу, включая все меш-объекты в иерархии.
void get_mesh_bs(const NodePtr &node, WorldBoundSphere &bs)
{
	if (!node) return;

	// Включаем границы этого узла, если это объект
	if (node->isObject())
		bs.expand(node->getWorldBoundSphere());

	// Рекурсия в цели NodeReference
	if (node->getType() == Node::NODE_REFERENCE)
		get_mesh_bs(checked_ptr_cast<NodeReference>(node)->getReference(), bs);
	// Рекурсия по всем дочерним узлам
	for (int i = 0; i < node->getNumChildren(); i++)
		get_mesh_bs(node->getChild(i), bs);
}

// Синхронизирует позицию виджета манипулятора с текущей трансформацией объекта.
void Manipulators::updateManipulatorTransform()
{
	if (obj && current_object_manipulator)
	{
		NodePtr manipulate_node = obj;

		// Используем трансформацию родителя, если включён transform_parent
		if (transform_parent && manipulate_node->getParent())
			manipulate_node = manipulate_node->getParent();

		current_object_manipulator->setTransform(manipulate_node->getWorldTransform());
	}
}

// Все три виджета манипулятора создаются и добавляются в GUI, изначально скрыты.
void Manipulators::init()
{
	// По умолчанию все оси доступны для каждого манипулятора
	is_x_axis_rotation = true;
	is_y_axis_rotation = true;
	is_z_axis_rotation = true;
	is_x_axis_translation = true;
	is_y_axis_translation = true;
	is_z_axis_translation = true;
	is_x_axis_scale = true;
	is_y_axis_scale = true;
	is_z_axis_scale = true;

	// По умолчанию манипуляторы работают в мировом базисе
	is_local_basis = false;

	// Создаём виджеты перемещения (W), поворота (E) и масштаба (R)
	gui = Gui::getCurrent();
	object_translator = WidgetManipulatorTranslator::create(gui);
	object_rotator = WidgetManipulatorRotator::create(gui);
	object_scaler = WidgetManipulatorScaler::create(gui);

	gui->addChild(object_translator);
	gui->addChild(object_rotator);
	gui->addChild(object_scaler);

	// Все манипуляторы изначально скрыты, пока не выбран объект
	object_translator->setHidden(true);
	object_rotator->setHidden(true);
	object_scaler->setHidden(true);
	// Перемещение - режим манипулятора по умолчанию
	current_object_manipulator = object_translator;

	// Подключаем события изменения трансформации к callback apply_transform
	object_translator->getEventChanged().connect(this, &Manipulators::apply_transform);
	object_rotator->getEventChanged().connect(this, &Manipulators::apply_transform);
	object_scaler->getEventChanged().connect(this, &Manipulators::apply_transform);

	// Отключаем управление игроком, чтобы разрешить взаимодействие с манипулятором
	auto player = Game::getPlayer();
	player->setControlled(false);
}

// Обрабатывается ввод для выбора объекта, переключения манипулятора и фокуса камеры.
void Manipulators::update()
{
	auto player = Game::getPlayer();

	// Включаем управление игроком, когда мышь захвачена (отключает горячие клавиши манипулятора)
	if (Input::isMouseGrab())
		player->setControlled(true);

	// Синхронизируем проекцию/модельвид манипулятора с текущей камерой
	if (player)
	{
		object_translator->setProjection(player->getProjection());
		object_rotator->setProjection(player->getProjection());
		object_scaler->setProjection(player->getProjection());

		object_translator->setModelview(player->getCamera()->getModelview());
		object_rotator->setModelview(player->getCamera()->getModelview());
		object_scaler->setModelview(player->getCamera()->getModelview());
	}
	// Обрабатываем выбор объекта по клику левой кнопки мыши
	if (Input::isMouseButtonUp(Input::MOUSE_BUTTON::MOUSE_BUTTON_LEFT) && !Input::isMouseGrab())
	{
		auto hoveredWidget = Gui::getCurrent()->getUnderCursorWidget();
		// Трассируем луч только если клик не по виджету
		if (!hoveredWidget)
		{
			obj = get_node_under_cursor();
			if (obj)
			{
				switch_manipulator(current_object_manipulator);
			}
			else
			{
				unselect();
			}
		}
	}

	// Обрабатываем ввод только когда объект выбран
	if (obj)
	{
		// Обновляем позицию манипулятора после завершения операции перетаскивания
		if (Input::isMouseButtonUp(Input::MOUSE_BUTTON::MOUSE_BUTTON_LEFT))
		{
			switch_manipulator(current_object_manipulator);
		}

		// Обрабатываем горячие клавиши режима манипулятора, когда мышь не захвачена
		if (!Input::isMouseGrab())
		{
			if (Input::isKeyDown(Input::KEY::KEY_W))
				switch_manipulator(object_translator);

			if (Input::isKeyDown(Input::KEY::KEY_E))
				switch_manipulator(object_rotator);

			if (Input::isKeyDown(Input::KEY::KEY_R))
				switch_manipulator(object_scaler);
		}

		// Фокусируем камеру на выбранном объекте (клавиша F)
		if (Input::isKeyDown(Input::KEY::KEY_F))
		{
			vec3 inversePlayerViewDirection = -player->getViewDirection();
			WorldBoundSphere bs;
			get_mesh_bs(obj, bs);
			// Размещаем камеру на расстоянии 2х радиуса ограничивающей сферы
			player->setWorldPosition(bs.center + Vec3(inversePlayerViewDirection * ((float)bs.radius * 2.0f)));
		}

		// Снимаем выбор объекта (клавиша U или Escape)
		if (Input::isKeyDown(Input::KEY::KEY_U) || Input::isKeyDown(Input::KEY::KEY_ESC))
		{
			unselect();
		}
	}
}

// Все виджеты манипулятора освобождаются.
void Manipulators::shutdown()
{
	object_translator.deleteLater();
	object_rotator.deleteLater();
	object_scaler.deleteLater();
}

// Трансформация виджета манипулятора применяется к выбранному объекту.
void Manipulators::apply_transform()
{
	if (obj)
	{
		NodePtr manipulate_node = obj;

		// Применяем к родителю, если включён режим transform_parent
		if (transform_parent && manipulate_node->getParent())
			manipulate_node = manipulate_node->getParent();

		manipulate_node->setWorldTransform(current_object_manipulator->getTransform());
		// Уведомляем слушателей об изменении трансформации
		transform_changed.run(obj);
	}
}

// Трассирует луч от камеры через позицию мыши для поиска выбираемого объекта.
Unigine::ObjectPtr Manipulators::get_node_under_cursor()
{
	auto player = Game::getPlayer();
	ivec2 mouse = Input::getMousePosition();

	// Пускаем луч от камеры через позицию мыши, максимальная дистанция 10000 единиц
	return World::getIntersection(player->getWorldPosition(), player->getWorldPosition() + Vec3(player->getDirectionFromMainWindow(mouse.x, mouse.y) * 10000), intersection_mask.get());
}

// Активирует указанный манипулятор, скрывает остальные и синхронизирует трансформацию.
void Manipulators::switch_manipulator(const Unigine::WidgetManipulatorPtr &currentManipulator)
{
	if (obj)
	{
		// Применяем текущий режим базиса ко всем манипуляторам
		set_manipulators_basis();

		current_object_manipulator = currentManipulator;
		current_object_manipulator->setHidden(false);

		NodePtr manipulate_node = obj;

		if (transform_parent && manipulate_node->getParent())
			manipulate_node = manipulate_node->getParent();

		// Синхронизируем позицию манипулятора с объектом
		current_object_manipulator->setTransform(manipulate_node->getWorldTransform());

		// Скрываем все остальные манипуляторы (виден только один одновременно)
		if (object_translator != current_object_manipulator)
			object_translator->setHidden(true);
		if (object_rotator != current_object_manipulator)
			object_rotator->setHidden(true);
		if (object_scaler != current_object_manipulator)
			object_scaler->setHidden(true);
	}
}

// Выбор снимается, и все манипуляторы скрываются.
void Manipulators::unselect()
{
	obj = ObjectPtr();

	object_translator->setHidden(true);
	object_rotator->setHidden(true);
	object_scaler->setHidden(true);
}

// Базис координат манипулятора устанавливается в локальный или мировой режим.
void Manipulators::set_manipulators_basis()
{
	if (obj)
	{
		if (is_local_basis)
		{
			// Используем локальную систему координат объекта для ориентации осей
			object_rotator->setBasis(obj->getWorldTransform());
			object_translator->setBasis(obj->getWorldTransform());
			object_scaler->setBasis(obj->getWorldTransform());
		}
		else
		{
			// Используем мировую систему координат (единичная матрица)
			object_rotator->setBasis(Mat4_identity);
			object_translator->setBasis(Mat4_identity);
			object_scaler->setBasis(Mat4_identity);
		}
	}
}

// Включает или отключает соответствующую ось для каждого манипулятора
void Manipulators::setXAxisRotation(bool value)
{
	is_x_axis_rotation = value;
	if (is_x_axis_rotation)
		object_rotator->setMask(object_rotator->getMask() | WidgetManipulator::MASK_X);
	else
		object_rotator->setMask(object_rotator->getMask() & ~(WidgetManipulator::MASK_X));
}

void Manipulators::setYAxisRotation(bool value)
{
	is_y_axis_rotation = value;
	if (is_y_axis_rotation)
		object_rotator->setMask(object_rotator->getMask() | WidgetManipulator::MASK_Y);
	else
		object_rotator->setMask(object_rotator->getMask() & ~(WidgetManipulator::MASK_Y));
}

void Manipulators::setZAxisRotation(bool value)
{
	is_z_axis_rotation = value;
	if (is_z_axis_rotation)
		object_rotator->setMask(object_rotator->getMask() | WidgetManipulator::MASK_Z);
	else
		object_rotator->setMask(object_rotator->getMask() & ~(WidgetManipulator::MASK_Z));
}

void Manipulators::setAxesRotation(bool value)
{
	is_x_axis_rotation = value;
	is_y_axis_rotation = value;
	is_z_axis_rotation = value;
	if (is_x_axis_rotation)
		object_rotator->setMask(object_rotator->getMask() | WidgetManipulator::MASK_X);
	else
		object_rotator->setMask(object_rotator->getMask() & ~(WidgetManipulator::MASK_X));

	if (is_y_axis_rotation)
		object_rotator->setMask(object_rotator->getMask() | WidgetManipulator::MASK_Y);
	else
		object_rotator->setMask(object_rotator->getMask() & ~(WidgetManipulator::MASK_Y));

	if (is_z_axis_rotation)
		object_rotator->setMask(object_rotator->getMask() | WidgetManipulator::MASK_Z);
	else
		object_rotator->setMask(object_rotator->getMask() & ~(WidgetManipulator::MASK_Z));
}

void Manipulators::setXAxisTranslation(bool value)
{
	is_x_axis_translation = value;
	if (is_x_axis_translation)
		object_translator->setMask(object_translator->getMask() | WidgetManipulator::MASK_X);
	else
		object_translator->setMask(object_translator->getMask() & ~(WidgetManipulator::MASK_X));
}

void Manipulators::setYAxisTranslation(bool value)
{
	is_y_axis_translation = value;
	if (is_y_axis_translation)
		object_translator->setMask(object_translator->getMask() | WidgetManipulator::MASK_Y);
	else
		object_translator->setMask(object_translator->getMask() & ~(WidgetManipulator::MASK_Y));
}

void Manipulators::setZAxisTranslation(bool value)
{
	is_z_axis_translation = value;
	if (is_z_axis_translation)
		object_translator->setMask(object_translator->getMask() | WidgetManipulator::MASK_Z);
	else
		object_translator->setMask(object_translator->getMask() & ~(WidgetManipulator::MASK_Z));
}

void Manipulators::setAxesTranslation(bool value)
{
	is_x_axis_translation = value;
	is_y_axis_translation = value;
	is_z_axis_translation = value;
	if (is_x_axis_translation)
		object_translator->setMask(object_translator->getMask() | WidgetManipulator::MASK_X);
	else
		object_translator->setMask(object_translator->getMask() & ~(WidgetManipulator::MASK_X));

	if (is_y_axis_translation)
		object_translator->setMask(object_translator->getMask() | WidgetManipulator::MASK_Y);
	else
		object_translator->setMask(object_translator->getMask() & ~(WidgetManipulator::MASK_Y));

	if (is_z_axis_translation)
		object_translator->setMask(object_translator->getMask() | WidgetManipulator::MASK_Z);
	else
		object_translator->setMask(object_translator->getMask() & ~(WidgetManipulator::MASK_Z));
}

void Manipulators::setXAxisScale(bool value)
{
	is_x_axis_scale = value;
	if (is_x_axis_scale)
		object_scaler->setMask(object_scaler->getMask() | WidgetManipulator::MASK_X);
	else
		object_scaler->setMask(object_scaler->getMask() & ~(WidgetManipulator::MASK_X));
}

void Manipulators::setYAxisScale(bool value)
{
	is_y_axis_scale = value;
	if (is_y_axis_scale)
		object_scaler->setMask(object_scaler->getMask() | WidgetManipulator::MASK_Y);
	else
		object_scaler->setMask(object_scaler->getMask() & ~(WidgetManipulator::MASK_Y));
}

void Manipulators::setZAxisScale(bool value)
{
	is_z_axis_scale = value;
	if (is_z_axis_scale)
		object_scaler->setMask(object_scaler->getMask() | WidgetManipulator::MASK_Z);
	else
		object_scaler->setMask(object_scaler->getMask() & ~(WidgetManipulator::MASK_Z));
}

void Manipulators::setAxesScale(bool value)
{
	is_x_axis_scale = value;
	is_y_axis_scale = value;
	is_z_axis_scale = value;
	if (is_x_axis_scale)
		object_scaler->setMask(object_scaler->getMask() | WidgetManipulator::MASK_X);
	else
		object_scaler->setMask(object_scaler->getMask() & ~(WidgetManipulator::MASK_X));

	if (is_y_axis_scale)
		object_scaler->setMask(object_scaler->getMask() | WidgetManipulator::MASK_Y);
	else
		object_scaler->setMask(object_scaler->getMask() & ~(WidgetManipulator::MASK_Y));

	if (is_z_axis_scale)
		object_scaler->setMask(object_scaler->getMask() | WidgetManipulator::MASK_Z);
	else
		object_scaler->setMask(object_scaler->getMask() & ~(WidgetManipulator::MASK_Z));
}

// Переключает базис манипулятора между локальной (объектной) и мировой системами координат
void Manipulators::setLocalBasis(bool value)
{
	is_local_basis = value;
	set_manipulators_basis();
}
