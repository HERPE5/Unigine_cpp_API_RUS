// Элемент управления "кнопка" с режимами переключения и удержания. Поддерживает анимированные переходы
// между состояниями вкл/выкл с настраиваемой длительностью. Если togglable, каждое нажатие переключает
// состояние; иначе кнопка возвращается к значению по умолчанию при отпускании.

#include "InteractableButtonComponent.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(InteractableButtonComponent);

using namespace Unigine;
using namespace Math;

// Позиции и повороты вкл/выкл вычисляются из исходной трансформации.
void InteractableButtonComponent::init()
{
	// По умолчанию используем узел компонента, если явная цель трансформации не задана
	if (!transformation_node)
	{
		transformation_node = node;
	}

	button_state = default_state;
	rotation_axis = normalize(rotation_axis.get());
	// Захватываем текущий поворот как состояние "выкл"
	rotation_off_quat = transformation_node->getRotation();
	rotation_on_quat = rotation_off_quat * quat(rotation_axis.get(), rotation_angle);

	// Захватываем текущую позицию как состояние "выкл"
	position_off = transformation_node->getPosition();
	position_on = transformation_node->getPosition() + (Vec3)position;

	// Начинаем анимацию с конца, если состояние по умолчанию — "вкл"
	if (default_state)
	{
		time = anim_duration;
	}
}

// Время анимации продвигается, трансформация интерполируется к целевому состоянию.
void InteractableButtonComponent::update()
{
	// Кнопки с удержанием возвращаются к значению по умолчанию при отпускании
	if (!togglable && !used_current_frame)
	{
		button_state = default_state;
	}

	// Продвигаем время анимации к цели в зависимости от состояния кнопки
	time = clamp((time - (Game::getIFps() * (button_state ? -1.0f : 1.0f))), 0.0f, anim_duration);

	// Вычисляем значение интерполяции для плавных переходов
	if (has_animation_time)
	{
		value = (time / anim_duration.get());
	}
	else
	{
		value = button_state ? 1.0f : 0.0f;
	}

	// Интерполируем позицию и поворот между состояниями выкл и вкл
	Vec3 new_position = static_cast<Vec3>(lerp(position_off, position_on, value));
	quat new_rotation = slerp(rotation_off_quat, rotation_on_quat, value);

	transformation_node->setTransform(
		static_cast<Mat4>(rotate(new_rotation)) * translate(new_position));

	used_last_frame = used_current_frame;
	used_current_frame = false;
}

// Состояние кнопки переключается или устанавливается в зависимости от режима взаимодействия.
void InteractableButtonComponent::use(PlayerPtr player, Unigine::Math::vec3 intersection_point)
{
	used_current_frame = true;
	if (togglable)
	{
		// Режим переключения: изменяем состояние только при первом нажатии
		if (!used_last_frame)
		{
			button_state = 1 - button_state;
		}
	}
	else
	{
		// Режим удержания: устанавливаем противоположное значению по умолчанию, пока удерживается
		if (used_last_frame)
		{
			button_state = 1 - default_state;
		}
	}
}

// Возвращается анимированное значение или дискретное состояние в зависимости от настройки.
float InteractableButtonComponent::getValue()
{
	if (has_animation_time)
	{
		return value;
	}
	else
	{
		return button_state ? 1.0f : 0.0f;
	}
}