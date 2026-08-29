// Система манипулирования объектами с использованием виджетов WidgetManipulator. Объекты выбираются
// через пересечение луча от клика мыши и трансформируются с помощью виджетов перемещения, поворота
// и масштабирования. Горячие клавиши (W/E/R) переключают режимы манипулятора.

#pragma once

#include <UnigineComponentSystem.h>

// Обеспечивает интерактивное манипулирование объектами с виджетами перемещения, поворота и масштаба.
class Manipulators : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Manipulators, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component enables you to manipulate objects in the world using manipulators (WidgetManipulator)."
		"There should be only one property associated with this component used in the world."
		"This property should be assigned to a dedicated node used to control the logic of this component.");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Маска пересечения фильтрует, какие объекты можно выбрать с помощью трассировки луча
	PROP_PARAM(Mask, intersection_mask, 1, "Intersection mask", "Mask to define which objects can be selected.");
	// При включении трансформируется родительский узел вместо выбранного дочернего
	PROP_PARAM(Toggle, transform_parent, 1);

	// Управление осью поворота - включает/отключает ось X на виджете поворота
	void setXAxisRotation(bool value);
	bool isXAxisRotation() const
	{
		return is_x_axis_rotation;
	}
	// Управление осью поворота - включает/отключает ось Y на виджете поворота
	void setYAxisRotation(bool value);
	bool isYAxisRotation() const
	{
		return is_y_axis_rotation;
	}
	// Управление осью поворота - включает/отключает ось Z на виджете поворота
	void setZAxisRotation(bool value);
	bool isZAxisRotation() const
	{
		return is_z_axis_rotation;
	}
	// Устанавливает одинаковое состояние включения для всех осей поворота
	void setAxesRotation(bool value);

	// Управление осью перемещения - включает/отключает ось X на виджете перемещения
	void setXAxisTranslation(bool value);
	bool isXAxisTranslation()
	{
		return is_x_axis_translation;
	}
	// Управление осью перемещения - включает/отключает ось Y на виджете перемещения
	void setYAxisTranslation(bool value);
	bool isYAxisTranslation()
	{
		return is_y_axis_translation;
	}
	// Управление осью перемещения - включает/отключает ось Z на виджете перемещения
	void setZAxisTranslation(bool value);
	bool isZAxisTranslation()
	{
		return is_z_axis_translation;
	}
	// Устанавливает одинаковое состояние включения для всех осей перемещения
	void setAxesTranslation(bool value);

	// Управление осью масштаба - включает/отключает ось X на виджете масштаба
	void setXAxisScale(bool value);
	bool isXAxisScale()
	{
		return is_x_axis_scale;
	}
	// Управление осью масштаба - включает/отключает ось Y на виджете масштаба
	void setYAxisScale(bool value);
	bool isYAxisScale()
	{
		return is_y_axis_scale;
	}
	// Управление осью масштаба - включает/отключает ось Z на виджете масштаба
	void setZAxisScale(bool value);
	bool isZAxisScale()
	{
		return is_z_axis_scale;
	}
	// Устанавливает одинаковое состояние включения для всех осей масштаба
	void setAxesScale(bool value);

	// Переключает между локальным (объектным) и мировым базисом координат
	void setLocalBasis(bool value);
	bool isLocalBasis()
	{
		return is_local_basis;
	}

	// Возвращает true, когда объект в данный момент выбран для манипулирования
	bool isActive() const
	{
		return bool(obj);
	}
	// Синхронизирует трансформацию виджета манипулятора с выбранным объектом
	void updateManipulatorTransform();
	// Событие, вызываемое при изменении трансформации объекта через манипулятор
	Unigine::Event<Unigine::ObjectPtr>& getEventTransformChanged()
	{
		return transform_changed;
	}

protected:
	void init();
	void update();
	void shutdown();

private:
	// Применяет трансформацию виджета манипулятора к выбранному объекту
	void apply_transform();
	// Выполняет трассировку луча от камеры через позицию мыши для поиска объекта
	Unigine::ObjectPtr get_node_under_cursor();
	// Активирует указанный манипулятор и скрывает остальные
	void switch_manipulator(const Unigine::WidgetManipulatorPtr& currentManipulator);
	// Очищает выбор и скрывает все манипуляторы
	void unselect();
	// Обновляет базис манипулятора в соответствии с текущим режимом локальный/мировой
	void set_manipulators_basis();

	// Текущий выбранный объект, которым манипулируют
	Unigine::ObjectPtr obj;
	// Контекст GUI для создания виджетов
	Unigine::GuiPtr gui;
	// Текущий активный виджет манипулятора
	Unigine::WidgetManipulatorPtr current_object_manipulator;

	// Виджет манипуляции позицией (горячая клавиша W)
	Unigine::WidgetManipulatorTranslatorPtr object_translator;
	// Виджет манипуляции поворотом (горячая клавиша E)
	Unigine::WidgetManipulatorRotatorPtr object_rotator;
	// Виджет манипуляции масштабом (горячая клавиша R)
	Unigine::WidgetManipulatorScalerPtr object_scaler;

	// Флаги включения по осям для манипулятора поворота
	bool is_x_axis_rotation;
	bool is_y_axis_rotation;
	bool is_z_axis_rotation;
	// Флаги включения по осям для манипулятора перемещения
	bool is_x_axis_translation;
	bool is_y_axis_translation;
	bool is_z_axis_translation;
	// Флаги включения по осям для манипулятора масштаба
	bool is_x_axis_scale;
	bool is_y_axis_scale;
	bool is_z_axis_scale;

	// Флаг режима базиса (true = локальный базис объекта, false = мировой базис)
	bool is_local_basis;
	// Инициатор события для уведомлений об изменении трансформации
	Unigine::EventInvoker<Unigine::ObjectPtr> transform_changed;
};
