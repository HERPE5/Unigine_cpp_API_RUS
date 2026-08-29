// Элементы управления UI для компонента Manipulators. Чекбоксы включают/отключают отдельные
// оси для операций перемещения, поворота и масштабирования. Кнопки-переключатели меняют
// мировой и локальный базис координат для виджетов манипулятора.

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

class Manipulators;

// Панель управления для настройки масок осей WidgetManipulator и режима базиса.
class ManipulatorsSample: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ManipulatorsSample, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component displays information about the sample, and demonstrates how to use the methods of the WidgetManipulators class.");

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

	// Ссылка на управляемый компонент Manipulators
	Manipulators* component = nullptr;

	// Callback-функции для чекбоксов осей поворота
	void x_axis_rotation_check_box_callback();
	void y_axis_rotation_check_box_callback();
	void z_axis_rotation_check_box_callback();
	// Callback-функции для чекбоксов осей перемещения
	void x_axis_translation_check_box_callback();
	void y_axis_translation_check_box_callback();
	void z_axis_translation_check_box_callback();
	// Callback-функции для чекбоксов осей масштаба
	void x_axis_scale_check_box_callback();
	void y_axis_scale_check_box_callback();
	void z_axis_scale_check_box_callback();

	// Callback-функции для кнопок-переключателей режима базиса
	void local_basis_button_callback();
	void world_basis_button_callback();

	// Чекбоксы включения/отключения осей поворота
	Unigine::WidgetCheckBoxPtr x_axis_rotation_check_box;
	Unigine::WidgetCheckBoxPtr y_axis_rotation_check_box;
	Unigine::WidgetCheckBoxPtr z_axis_rotation_check_box;
	// Чекбоксы включения/отключения осей перемещения
	Unigine::WidgetCheckBoxPtr x_axis_translation_check_box;
	Unigine::WidgetCheckBoxPtr y_axis_translation_check_box;
	Unigine::WidgetCheckBoxPtr z_axis_translation_check_box;
	// Чекбоксы включения/отключения осей масштаба
	Unigine::WidgetCheckBoxPtr x_axis_scale_check_box;
	Unigine::WidgetCheckBoxPtr y_axis_scale_check_box;
	Unigine::WidgetCheckBoxPtr z_axis_scale_check_box;
	// Кнопки-переключатели для смены локального и мирового базиса
	Unigine::WidgetButtonPtr local_basis_button;
	Unigine::WidgetButtonPtr world_basis_button;

	// Текущее состояние режима базиса (true = локальный, false = мировой)
	bool is_local_basis;
	// Вспомогательный класс для UI описания примера
	SampleDescriptionWindow sample_description_window;
	// Сохранённый дескриптор мыши для восстановления при завершении
	Unigine::Input::MOUSE_HANDLE previous_handle;
};