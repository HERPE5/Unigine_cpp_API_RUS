// Элемент управления "кнопка" с режимами переключения и удержания.
// Анимированные переходы между состояниями вкл/выкл с настраиваемой длительностью.
// Если togglable, каждое нажатие переключает состояние; иначе возврат к значению по умолчанию при отпускании.

#pragma once
#include "Interactable.h"

#include <UnigineComponentSystem.h>

// Анимирует между позициями и поворотами вкл/выкл в зависимости от состояния кнопки.
class InteractableButtonComponent
	: public Interactable
	, public Unigine::ComponentBase
{

public:
	COMPONENT(InteractableButtonComponent, ComponentBase);
	PROP_NAME("InteractableButtonComponent");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update, Interactable::interactable_update_priority);

	// Остаётся ли кнопка в нажатом состоянии или возвращается при отпускании
	PROP_PARAM(Toggle, togglable, true);
	// Начальное состояние кнопки (вкл/выкл)
	PROP_PARAM(Toggle, default_state, false);
	// Должен ли переход анимироваться во времени
	PROP_PARAM(Toggle, has_animation_time, true);
	// Длительность анимации нажатия/отпускания в секундах
	PROP_PARAM(Float, anim_duration, 0.2f);
	// Смещение позиции, когда кнопка в нажатом состоянии
	PROP_PARAM(Vec3, position);
	// Ось, вокруг которой кнопка вращается при нажатии
	PROP_PARAM(Vec3, rotation_axis, Unigine::Math::vec3(1, 0, 0));
	// Угол поворота в градусах при нажатии кнопки
	PROP_PARAM(Float, rotation_angle, 0.0f);
	// Узел, получающий трансформацию позиции/поворота
	PROP_PARAM(Node, transformation_node);

	void use(Unigine::PlayerPtr player, Unigine::Math::vec3 intersection_point) override;
	float getValue() override;

private:
	// Текущее состояние кнопки (0 = выкл, 1 = вкл)
	int button_state = false;
	void init();
	void update();

	// Кватернион поворота для нажатого состояния
	Unigine::Math::quat rotation_on_quat;
	// Кватернион поворота для отпущенного состояния
	Unigine::Math::quat rotation_off_quat;

	// Позиция, когда кнопка отпущена
	Unigine::Math::Vec3 position_off;
	// Позиция, когда кнопка нажата
	Unigine::Math::Vec3 position_on;

	// Текущее значение интерполяции (0-1) для анимации
	float value = 0.0f;
	// Текущий аккумулятор времени анимации
	float time = 0.0f;

	// Отслеживает, была ли кнопка нажата в предыдущем кадре
	bool used_last_frame = false;
	// Отслеживает, нажата ли кнопка в текущем кадре
	bool used_current_frame = false;
};
