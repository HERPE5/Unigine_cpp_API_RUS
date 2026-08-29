// Камера от третьего лица, следующая за целевым узлом с использованием сферических координат.
// Поддерживает фиксированный (привязанный к вращению цели) и свободный орбитальные режимы, с
// определением столкновений для предотвращения прохождения камеры сквозь геометрию.
// Использует сферическую форму для запросов столкновений и итеративной коррекции позиции.

#include "PlayerPersecutorComponent.h"
#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(PlayerPersecutorComponent);

// Создаёт сферу столкновений и инициализирует систему сферических координат.
// Должен быть прикреплён к узлу PlayerDummy.
void PlayerPersecutorComponent::init()
{
	camera = checked_ptr_cast<PlayerDummy>(node);

	// Сфера столкновений для обнаружения препятствий между камерой и целью
	shape = Unigine::ShapeSphere::create();
	shape->setContinuous(0);
	shape->setCenter(node->getWorldPosition());

	// Инициализируем состояние сферических координат
	direction = vec3_right;
	distance = 4.0f;
	phi_direction = vec3_right;
	theta_angle = 0.0f;

	// Применяем параметры редактора
	setFixed(fixed);
	setCollision(collision);
	setCollisionMask(collision_mask);
	setCollisionRadius(0.5f);

	setAnchor(anchor);
	setMinDistance(min_distance);
	setMaxDistance(max_distance);
	setMinThetaAngle(min_theta_angle);
	setMaxThetaAngle(max_theta_angle);
	setTurning(90.0f);
}

// Обновление каждого кадра: считывает ввод мыши, применяет вращение адаптивными шагами,
// итеративно разрешает столкновения и обновляет трансформацию камеры.
void PlayerPersecutorComponent::update()
{
	if (!target_node || !camera)
		return;

	// Вычисляем точку привязки цели в мировом пространстве
	target = target_node->getWorldTransform() * Vec3(anchor);

	// Согласовываем скорость камеры со скоростью цели для плавного движения
	BodyRigidPtr body = target_node->getObjectBodyRigid();
	if (body)
		camera->setVelocity(body->getLinearVelocity());
	else
		camera->setVelocity(vec3_zero);

	// Считываем ввод вращения с мыши
	float phi = 0.0f;
	float theta = 0.0f;

	if (controlled && camera->isMainPlayer() && Input::isMouseCursorHide())
	{
		phi = Input::getMouseDeltaPosition().x;
		theta = Input::getMouseDeltaPosition().y;
	}

	float old_min_theta_angle = getMinThetaAngle();
	float old_max_theta_angle = getMaxThetaAngle();

	// Фиксированные углы: привязываем theta к вращению цели
	if (isFixed())
	{
		theta_angle += theta;
		theta_angle = clamp(theta_angle, min_theta_angle, max_theta_angle);
		theta += theta_angle - getThetaAngle();

		setMinThetaAngle(theta_angle);
		setMaxThetaAngle(theta_angle);
	}

	// Адаптивная корректировка вращения с учётом столкновений
	do
	{
		// Адаптивный размер шага на основе радиуса столкновений и дистанции
		float max_distance = max(getCollisionRadius(), getDistance());
		float min_distance = min(getCollisionRadius(), getDistance());

		float angle = max(Math::atan(max_distance / min_distance) * Consts::RAD2DEG * 0.5f, Consts::EPS);
		float p = clamp(phi, -angle, angle);
		float t = clamp(theta, -angle, angle);
		phi -= p;
		theta -= t;

		Vector<ShapeContactPtr> contacts;
		shape->getCollision(contacts, Game::getIFps());

		// Обновляем ограничения
		update_distance();
		update_angles(p, t);

		// Столкновение с миром: итеративно разрешаем проникновения
		contacts.clear();
		if (getCollision())
		{
			for (int i = 0; i < PLAYER_PERSECUTOR_COLLISIONS; i++)
			{
				shape->setCenter(position);
				shape->getCollision(contacts, 0.0f);
				if (contacts.size() == 0)
					break;
				float inum_contacts = 1.0f / Math::itof(contacts.size());
				for (int j = 0; j < contacts.size(); j++)
				{
					const ShapeContact& c = *contacts[j].get();
					position += Vec3(c.getNormal() * (c.getDepth() * inum_contacts));
				}
				update_distance();
				if (isFixed())
					update_angles(-getPhiAngle(), 0.0f);
				else
					update_angles(0.0f, 0.0f);
			}
		}

		// Позиция формы: синхронизируем форму столкновений с камерой
		shape->setCenter(position);
	} while (Math::abs(phi) > Consts::EPS || Math::abs(theta) > Consts::EPS);

	setMinThetaAngle(old_min_theta_angle);
	setMaxThetaAngle(old_max_theta_angle);

	// Применяем трансформацию
	flushTransform();
}

// Очищает форму столкновений.
void PlayerPersecutorComponent::shutdown()
{
	shape.deleteLater();
}

//////////////////////////////////////////////////////////////////////////
// Параметры - сеттеры, обновляющие внутреннее состояние трансформации
//////////////////////////////////////////////////////////////////////////

// Переключает между фиксированным (привязанным к цели) и свободным орбитальными режимами.
void PlayerPersecutorComponent::setFixed(int f)
{
	fixed = f;
	update_transform();
}

// Задаёт целевой узел для слежения.
void PlayerPersecutorComponent::setTarget(NodePtr n)
{
	target_node = n;
	update_transform();
}

// Задаёт смещение точки привязки на целевом узле.
void PlayerPersecutorComponent::setAnchor(const vec3& a)
{
	anchor = a;
	update_transform();
}

//////////////////////////////////////////////////////////////////////////
// Dynamic - манипуляция сферическими координатами во время выполнения
//////////////////////////////////////////////////////////////////////////

// Задаёт расстояние камеры от цели (ограничено min/max).
void PlayerPersecutorComponent::setDistance(float d)
{
	distance = clamp(d, min_distance, max_distance);
	position = target - Vec3(direction * distance);

	flushTransform();
}

// Задаёт горизонтальный угол орбиты (phi) вокруг цели.
void PlayerPersecutorComponent::setPhiAngle(float angle)
{
	if (!target_node)
		return;

	float phi = angle - getPhiAngle();

	
	vec3 up = camera->getUp();

	quat transform = quat(target_node->getWorldTransform());
	phi_direction = (inverse(transform) * quat(up, phi) * transform) * phi_direction;

	direction = quat(up, -phi) * direction;
	position = target - Vec3(direction * distance);

	flushTransform();
}

// Возвращает горизонтальный угол орбиты. В фиксированном режиме возвращает угол относительно
// ориентации цели; в свободном режиме возвращает абсолютный мировой угол.
float PlayerPersecutorComponent::getPhiAngle() const
{
	if (!target_node)
		return 0.0f;

	vec3 up = camera->getUp();

	if (isFixed())
	{
		// Вычисляем угол между опорным направлением и текущим направлением
		vec3 d0 = rotation(target_node.get()->getWorldTransform()) * phi_direction;
		vec3 d1 = direction;
		d0 = normalize(d0 - up * dot(up, d0));
		d1 = normalize(d1 - up * dot(up, d1));

		return Math::acos(clamp(dot(d0, d1), -1.0f, 1.0f)) * Math::sign(dot(up, cross(d0, d1))) * Consts::RAD2DEG;
	}
	else
	{
		// Вычисляем абсолютный угол в мировом пространстве
		vec3 tangent, binormal;
		orthoBasis(up, tangent, binormal);

		return Math::atan2(dot(direction, tangent), dot(direction, binormal)) * Consts::RAD2DEG;
	}
}

// Задаёт вертикальный угол орбиты (theta) - возвышение над/под целью.
void PlayerPersecutorComponent::setThetaAngle(float angle)
{
	theta_angle = clamp(angle, min_theta_angle, max_theta_angle);
	float theta = theta_angle - getThetaAngle();

	direction = quat(cross(camera->getUp(), direction), theta) * direction;
	position = target - Vec3(direction * distance);

	flushTransform();
}

// Возвращает вертикальный угол возвышения (-90 = ниже цели, +90 = выше).
float PlayerPersecutorComponent::getThetaAngle() const
{
	return Math::acos(clamp(dot(direction, camera->getUp()), -1.0f, 1.0f)) * Consts::RAD2DEG - 90.0f;
}

void PlayerPersecutorComponent::setViewDirection(const vec3& view)
{
	direction = normalize(view);
	theta_angle = getThetaAngle();
	flushTransform();
}

void PlayerPersecutorComponent::setView(const vec3& view)
{
	direction = normalize(view);

	theta_angle = getThetaAngle();

	flushTransform();
}


//////////////////////////////////////////////////////////////////////////
// Contacts
//////////////////////////////////////////////////////////////////////////


const ShapeContactPtr& PlayerPersecutorComponent::getContact(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerPersecutor::getContact(): bad contact number");
	return contacts[num];
}

float PlayerPersecutorComponent::getContactDepth(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerPersecutor::getContactDepth(): bad contact number");
	return contacts[num]->getDepth();
}

vec3 PlayerPersecutorComponent::getContactNormal(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerPersecutor::getContactNormal(): bad contact number");
	return contacts[num]->getNormal();
}

ObjectPtr PlayerPersecutorComponent::getContactObject(int num)
{
	assert(num >= 0 && num < getNumContacts() && "PlayerPersecutor::getContactObject(): bad contact number");
	return contacts[num]->getObject();
}

Vec3 PlayerPersecutorComponent::getContactPoint(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerPersecutor::getContactPoint(): bad contact number");
	return contacts[num]->getPoint();
}

ShapePtr PlayerPersecutorComponent::getContactShape(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerPersecutor::getContactShape(): bad contact number");
	return checked_ptr_cast<Shape>(contacts[num]->getShape1());
}

int PlayerPersecutorComponent::getContactSurface(int num) const
{
	assert(num >= 0 && num < getNumContacts() && "PlayerPersecutor::getContactSurface(): bad contact number");
	return contacts[num]->getSurface();
}

//////////////////////////////////////////////////////////////////////////
// Update - методы пересчёта внутреннего состояния
//////////////////////////////////////////////////////////////////////////

// Пересчитывает направление и дистанцию из текущих позиций, применяет ограничение.
void PlayerPersecutorComponent::update_distance()
{
	vec3 tangent, binormal;
	orthoBasis(camera->getUp(), tangent, binormal);

	// Вычисляем направление от позиции к цели
	direction = vec3(target - position);
	distance = length(direction);
	if (length(vec2(direction)) > Consts::EPS)
		direction /= distance;
	else
		direction = binormal;

	// Применяем ограничения дистанции
	distance = clamp(distance, min_distance, max_distance);

	// Пересчитываем позицию из ограниченной дистанции
	position = target - Vec3(direction * distance);
}

// Применяет дельты вращения phi (горизонтальный) и theta (вертикальный) с ограничением.
void PlayerPersecutorComponent::update_angles(float phi, float theta)
{
	vec3 up = camera->getUp();

	// Угол theta: вычисляем новый вертикальный угол
	float theta_angle = getThetaAngle() + theta;

	// Ограничиваем угол theta заданными пределами
	if (theta_angle < min_theta_angle)
		theta += min_theta_angle - theta_angle;
	else if (theta_angle > max_theta_angle)
		theta += max_theta_angle - theta_angle;

	// Фиксированные углы: обновляем опорное направление в локальном пространстве цели
	if (isFixed())
	{
		quat transform = quat(target_node->getWorldTransform());
		phi_direction = normalize(inverse(transform) * quat(up, -phi) * transform) * phi_direction;
		phi = getPhiAngle();
	}

	// Обновляем трансформацию: применяем вращение к направлению и пересчитываем позицию
	direction = (quat(up, -phi) * quat(cross(up, direction), theta)) * direction;
	position = target - Vec3(direction * distance);
}

//////////////////////////////////////////////////////////////////////////
// Transformation - синхронизация между узлом и внутренним состоянием
//////////////////////////////////////////////////////////////////////////

// Извлекает сферические координаты из текущей трансформации узла.
// Вызывается при изменении цели/точки привязки для реинициализации внутреннего состояния.
void PlayerPersecutorComponent::update_transform()
{
	// Предотвращаем рекурсивные обновления во время flushTransform
	if (flush == 0 && target_node)
	{
		target = target_node->getWorldTransform() * Vec3(anchor);

		// Извлекаем текущую позицию из узла
		position = node->getWorldTransform().getColumn3(3);

		update_distance();

		// Сохраняем опорное направление в локальном пространстве цели (для фиксированного режима)
		phi_direction = rotation(target_node->getIWorldTransform()) * direction;

		update_angles(0.0f, 0.0f);
		theta_angle = getThetaAngle();
	}
}

// Применяет внутреннее состояние к трансформации узла. Использует setTo() для взгляда из
// позиции на цель, сохраняя вектор "вверх" камеры.
void PlayerPersecutorComponent::flushTransform()
{
	flush = 1;
	node->setWorldTransform(setTo(position, position + Vec3(direction), camera->getUp()));
	flush = 0;
}
