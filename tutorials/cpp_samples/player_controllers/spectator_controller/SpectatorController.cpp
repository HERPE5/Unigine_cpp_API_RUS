// Свободнолетающая камера spectator с движением 6DOF и опциональными сферическими столкновениями.
// Использует симуляцию с фиксированным шагом времени для движения, независимого от частоты кадров. Поддерживает
// ускорение, затухание и режим спринта. Обрабатывает внешние изменения трансформации,
// синхронизируя внутреннее состояние с трансформацией узла.

#include "SpectatorController.h"
#include <UnigineGame.h>
#include <UnigineConsole.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(SpectatorController)

// Создаёт сферу столкновений, преобразует строковые имена клавиш в перечисления ввода,
// получает ссылку на игрока и инициализирует внутреннее состояние из трансформации узла.
void SpectatorController::init()
{
	// Создаём физическую форму
	p_shape_sphere = ShapeSphere::create(collision_radius.get());
	p_shape_sphere->setContinuous(0);

	// Назначаем клавиши ввода из строковых параметров
	_forward_key = Input::getKeyByName(forward_key.get());
	_backward_key = Input::getKeyByName(backward_key.get());
	_right_key = Input::getKeyByName(right_key.get());
	_left_key = Input::getKeyByName(left_key.get());
	_up_key = Input::getKeyByName(up_key.get());
	_down_key = Input::getKeyByName(down_key.get());
	_turn_up_key = Input::getKeyByName(turn_up_key.get());
	_turn_down_key = Input::getKeyByName(turn_down_key.get());
	_turn_left_key = Input::getKeyByName(turn_left_key.get());
	_turn_right_key = Input::getKeyByName(turn_right_key.get());
	_accelerate_key = Input::getKeyByName(accelerate_key.get());

	p_player = checked_ptr_cast<Player>(node);

	on_transform_changed();	// Получаем начальные параметры узла
}

// Обновление каждого кадра: обнаруживает внешние изменения трансформации, обрабатывает ввод,
// применяет движение и синхронизирует трансформацию обратно к узлу.
void SpectatorController::update()
{
	// Если кто-то изменил нашу позицию извне, обновляем все внутренние параметры
	if (transform != node->getTransform())
		on_transform_changed();

	updateControls();
	flushTransform();

	transform = node->getTransform();
}

// Очищает форму столкновений.
void SpectatorController::shutdown()
{
	p_shape_sphere.deleteLater();	// Удаляем созданную нами форму
}

// Обрабатывает пользовательский ввод и запускает обновления движения. Считывает дельту мыши для вращения,
// клавиатуру для импульса движения, затем выполняет физическую симуляцию с фиксированным шагом времени.
void SpectatorController::updateControls()
{
	vec3 up = p_player->getUp();

	vec3 impulse = vec3_zero;

	vec3 tangent, binormal;
	orthoBasis(p_player->getUp(), tangent, binormal);

	if (is_controlled.get() && !Console::isActive())
	{
		if (Input::isMouseCursorHide())
		{ 
			phi_angle += Input::getMouseDeltaPosition().x * mouse_sensitivity.get();
			theta_angle += Input::getMouseDeltaPosition().y * mouse_sensitivity.get();
		}

		theta_angle += turning * Game::getIFps() * (Input::isKeyPressed(_turn_down_key) - Input::isKeyPressed(_turn_up_key));
		theta_angle = clamp(theta_angle, min_theta_angle, max_theta_angle);

		phi_angle += turning * Game::getIFps() * (Input::isKeyPressed(_turn_right_key) - Input::isKeyPressed(_turn_left_key));

		vec3 x = (quat(up, -phi_angle) * quat(tangent, -theta_angle)) * binormal;
		vec3 y = normalizeValid(cross(up, x));
		vec3 z = normalizeValid(cross(x, y));

		direction = x;

		impulse += x * float(Input::isKeyPressed(_forward_key) - Input::isKeyPressed(_backward_key));
		impulse += y * float(Input::isKeyPressed(_left_key) - Input::isKeyPressed(_right_key));
		impulse += z * float(Input::isKeyPressed(_up_key) - Input::isKeyPressed(_down_key));

		impulse.normalizeValid();

		impulse *= Input::isKeyPressed(_accelerate_key) ? max_velocity.get() : min_velocity.get();
	}

	float time = Game::getIFps();

	float target_velocity = length(impulse);

	Vec3 player_velocity = Vec3(p_player->getVelocity());

	// Используем do-while, чтобы гарантировать обработку хотя бы одного обновления,
	// даже когда оставшееся время очень мало (например, при высоком FPS).
	do
	{
		// Ограничиваем шаг симуляции максимальным фиксированным интервалом времени (PLAYER_SPECTATOR_IFPS).
		// Это предотвращает нестабильность или большие скачки в движении и столкновениях при высоком времени кадра (например, при просадках FPS).
		float ifps = min(time, PLAYER_SPECTATOR_IFPS);
		time -= ifps;
		update_movement(impulse, ifps, target_velocity);
	} while (time > Consts::EPS);
}


// Применяет позицию и направление к трансформации узла, если они изменились с прошлого кадра.
void SpectatorController::flushTransform()
{
	vec3 up = p_player->getUp();

	if (last_position != position || last_direction != direction || last_up != up)
	{
		node->setWorldTransform(setTo(position, position + Vec3(direction), up));
		on_transform_changed(); // обновляем все внутренние параметры

		last_position = position;
		last_direction = direction;
		last_up = up;
	}
}

// Синхронизирует внутреннее состояние (позицию, направление, углы) из мировой трансформации узла.
// Вызывается при init и всякий раз, когда внешний код изменяет трансформацию.
void SpectatorController::on_transform_changed()
{
	vec3 up = p_player->getUp();

	vec3 tangent, binormal;
	orthoBasis(up, tangent, binormal);

	position = node->getWorldTransform().getColumn3(3);
	direction = normalizeValid(vec3(-node->getWorldTransform().getColumn3(2)));

	phi_angle = Math::atan2(dot(direction, tangent), dot(direction, binormal)) * Consts::RAD2DEG;
	theta_angle = Math::acos(clamp(dot(direction, up), -1.0f, 1.0f)) * Consts::RAD2DEG - 90.0f;
	theta_angle = clamp(theta_angle, min_theta_angle, max_theta_angle);
	direction = (quat(up, -phi_angle) * quat(tangent, -theta_angle)) * binormal;

	last_position = position;
	last_direction = direction;
	last_up = up;
}

// Применяет скорость с ускорением/затуханием и разрешает сферические столкновения.
// Вызывается в цикле с фиксированным шагом времени для обеспечения согласованного физического поведения.
void SpectatorController::update_movement(const vec3& impulse, float ifps, float target_velocity)
{
	float old_velocity = length(p_player->getVelocity());

	p_player->setVelocity(p_player->getVelocity() + impulse * acceleration.get() * ifps);

	float current_velocity = length(p_player->getVelocity());
	if (target_velocity < Consts::EPS || current_velocity > target_velocity)
		p_player->setVelocity(p_player->getVelocity() * Math::exp(-damping * ifps));

	current_velocity = length(p_player->getVelocity());
	if (current_velocity > old_velocity && current_velocity > target_velocity)
		p_player->setVelocity(p_player->getVelocity() * target_velocity / current_velocity);

	if (current_velocity < Consts::EPS)
		p_player->setVelocity(vec3_zero);

	position += Vec3(p_player->getVelocity() * ifps);

	contacts.clear();

	if (p_shape_sphere->isEnabled() && is_collided.get())
	{
		for (int i = 0; i < PLAYER_SPECTATOR_COLLISIONS; i++)
		{
			p_shape_sphere->setCenter(position);
			p_shape_sphere->getCollision(contacts, ifps);
			if (contacts.size() == 0)
				break;

			// Вычисляем обратную величину количества контактов, чтобы равномерно распределить общее выталкивание
			// Это предотвращает применение полной глубины для каждого контакта, что привело бы к перекомпенсации позиции
			float inum_contacts = 1.0f / Math::itof(contacts.size());
			for (int j = 0; j < contacts.size(); j++)
			{
				const ShapeContactPtr c = contacts[j];

				// Выталкиваем игрока вдоль нормали контакта, масштабированной глубиной проникновения и равномерно поделённой на количество контактов
				position += Vec3(c->getNormal() * (c->getDepth() * inum_contacts));

				// Убираем компонент скорости, направленный в поверхность контакта
				// Это предотвращает продолжение движения игрока в объект
				p_player->setVelocity(p_player->getVelocity() - c->getNormal() * dot(p_player->getVelocity(), c->getNormal()));
			}
		}
	}

	p_shape_sphere->setCenter(position);
}

// Задаёт горизонтальный угол вращения (рыскание) и обновляет направление взгляда.
void SpectatorController::setPhiAngle(float newAngle)
{
	newAngle = newAngle - phi_angle;
	direction = quat(p_player->getUp(), newAngle) * direction;
	phi_angle += newAngle;

	flushTransform();
}

// Задаёт вертикальный угол вращения (тангаж), ограниченный пределами min/max theta.
void SpectatorController::setThetaAngle(float newAngle)
{
	newAngle = clamp(newAngle, min_theta_angle.get(), max_theta_angle.get()) - theta_angle;
	direction = quat(cross(p_player->getUp(), direction), newAngle) * direction;
	theta_angle += newAngle;

	flushTransform();
}

// Задаёт направление взгляда из вектора, раскладывая на углы phi/theta.
void SpectatorController::setViewDirection(const vec3 &newView)
{
	direction = normalizeValid(newView);

	// Ортогональный базис
	vec3 tangent, binormal;
	orthoBasis(p_player->getUp(), tangent, binormal);

	// Раскладываем направление взгляда на сферические углы
	phi_angle = Math::atan2(dot(direction, tangent), dot(direction, binormal)) * Consts::RAD2DEG;
	theta_angle = Math::acos(clamp(dot(direction, p_player->getUp()), -1.0f, 1.0f)) * Consts::RAD2DEG - 90.0f;
	theta_angle = clamp(theta_angle, min_theta_angle.get(), max_theta_angle.get());

	flushTransform();
}

//////////////////////////////////////////////////////////////////////////
// Аксессоры контактов столкновений
//////////////////////////////////////////////////////////////////////////

// Возвращает полные данные контакта по указанному индексу.
const ShapeContactPtr SpectatorController::getContact(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerSpectator::getContact(): bad contact number");
	return contacts[num];
}

// Возвращает глубину проникновения в указанном контакте.
float SpectatorController::getContactDepth(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerSpectator::getContactDepth(): bad contact number");
	return contacts[num]->getDepth();
}

// Возвращает нормаль поверхности в указанном контакте.
vec3 SpectatorController::getContactNormal(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerSpectator::getContactNormal(): bad contact number");
	return contacts[num]->getNormal();
}

// Возвращает объект, с которым произошло столкновение в указанном контакте.
ObjectPtr SpectatorController::getContactObject(int num)
{
	assert(num >= 0 && num < getNumContacts() && "PlayerSpectator::getContactObject(): bad contact number");
	return contacts[num]->getObject();
}

// Возвращает мировую позицию указанного контакта.
Vec3 SpectatorController::getContactPoint(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerSpectator::getContactPoint(): bad contact number");
	return contacts[num]->getPoint();
}

// Возвращает форму столкновений, задействованную в указанном контакте.
ShapePtr SpectatorController::getContactShape(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerSpectator::getContactShape(): bad contact number");
	return contacts[num]->getShape0();
}

// Возвращает индекс поверхности объекта столкновения в указанном контакте.
int SpectatorController::getContactSurface(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerSpectator::getContactSurface(): bad contact number");
	return contacts[num]->getSurface();
}



