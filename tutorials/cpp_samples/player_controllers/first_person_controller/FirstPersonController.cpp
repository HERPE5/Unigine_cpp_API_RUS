// Полнофункциональный контроллер персонажа от первого лица с коллизией капсулы,
// ходьбой/бегом/приседанием, прыжками, автоматическим преодолением ступеней,
// обработкой наклонных поверхностей и взаимодействием с физическими объектами.
// Использует собственную обработку коллизий для передвижения, независимого
// от частоты кадров, и стабильного определения земли.

#include "FirstPersonController.h"
#include <UnigineGame.h>
#include <UnigineVisualizer.h>
#include <UnigineProfiler.h>
#include <UnigineConsole.h>
#include <UnigineInput.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(FirstPersonController)

// Устанавливает трансформацию игрока из внешнего источника (например, при телепортации).
// Ограничивает ориентацию вертикалью (без наклона), извлекает углы камеры из матрицы.
void FirstPersonController::setWorldTransform(const Unigine::Math::Mat4 &t)
{
	// Выравниваем ось Y по горизонтальной плоскости - игрок должен оставаться вертикальным
	Vec3 axis_y = t.getAxisY();
	axis_y.z = 0;
	axis_y = (axis_y.length2() > Consts::EPS ? axis_y.normalize() : Vec3_forward);
	node->setWorldTransform(setTo(t.getTranslate(), t.getTranslate() + axis_y, vec3_up, AXIS_Y));

	// Извлекаем тангаж и рыскание из матрицы трансформации и применяем к камере
	if (camera && camera_mode != CameraMode::NONE)
	{
		// Вертикальный угол: вычисляется из наклона оси Z относительно вектора "вниз"
		camera_vertical_angle = getAngle(vec3_down, static_cast<vec3>(-t.getAxisZ()));
		camera_vertical_angle = clamp(camera_vertical_angle, min_vertical_angle + 90.0f, max_vertical_angle + 90.0f);

		// Горизонтальный угол: поворот вокруг оси "вверх"
		camera_horizontal_angle = node->getWorldRotation().getAngle(vec3_up);

		// Восстанавливаем направление камеры из сферических углов
		vec3 camera_direction = vec3_forward * rotateZ(-camera_horizontal_angle);
		camera_direction = camera_direction * rotate(cross(camera_direction, vec3_up), 90.0f - camera_vertical_angle);
		camera_direction.normalize();
		camera->setWorldDirection(camera_direction, vec3_up);
	}
}

// Инициализирует контроллер: создаёт/проверяет физическое тело и форму, настраивает камеру,
// предварительно вычисляет косинусы углов и определяет геймпад. Компонент должен быть прикреплён к Object.
void FirstPersonController::init()
{
	// Компоненту требуется узел Object (не просто Node) для крепления физического тела
	ObjectPtr obj = checked_ptr_cast<Object>(node);
	if (!obj)
	{
		Log::error("FirstPersonController: can't cast node to Object\n");
		return;
	}

	// Принудительно устанавливаем вертикальную ориентацию: выравниваем ось Y по горизонтальной плоскости.
	// Это предотвращает наклонённых персонажей и обеспечивает согласованное поведение при передвижении.
	Vec3 axis_y = obj->getWorldTransform().getAxisY();
	axis_y.z = 0;
	axis_y = (axis_y.length2() > Consts::EPS ? axis_y.normalize() : Vec3_forward);
	obj->setWorldTransform(setTo(node->getWorldPosition(), node->getWorldPosition() + axis_y, vec3_up, AXIS_Y));

	// BodyDummy используется для ручной обработки коллизий (а не для физической симуляции).
	// Если use_object_body истинно, пытаемся использовать существующее тело из редактора.
	if (use_object_body)
	{
		body = checked_ptr_cast<BodyDummy>(obj->getBody());
		if (!body)
			Log::warning("FirstPersonController: object doesn't contain BodyDummy, it was created automatically\n");
	}

	if (!body)
	{
		body = BodyDummy::create(obj);
		body->setTransform(obj->getWorldTransform());
	}

	// Форма капсулы идеальна для коллизии персонажа: закруглённые концы предотвращают
	// застревание на кромках, цилиндрическое тело обеспечивает плавное скольжение вдоль стен.
	if (use_object_body)
	{
		// Ищем капсулу среди существующих форм
		if (body->getNumShapes() > 0)
		{
			for (int i = 0; i < body->getNumShapes(); i++)
				if (!shape)
					shape = checked_ptr_cast<ShapeCapsule>(body->getShape(i));

			if (!shape)
				Log::warning("FirstPersonController: body doesn't contain ShapeCapsule, it was created automatically\n");
		}
		else
			Log::warning("FirstPersonController: body doesn't contain shapes, it was created automatically\n");
	}

	// Создаём капсулу по умолчанию, если она не найдена
	if (!shape)
	{
		shape = ShapeCapsule::create(body, capsule_radius, capsule_height);
		// Располагаем капсулу так, чтобы её низ касался земли в точке начала координат игрока
		body->setShapeTransform(body->getNumShapes() - 1, translate(vec3_up * (capsule_radius + 0.5f * capsule_height)));

		shape->setPhysicsIntersectionMask(physics_intersection_mask);
		shape->setCollisionMask(collision_mask);
		shape->setExclusionMask(exclusion_mask);
	}

	// Кэшируем фактические размеры капсулы (могут отличаться от параметров при использовании собственной формы)
	capsule_height = shape->getHeight();
	// Высота приседания должна быть не меньше диаметра (двух полусфер) и не больше полной высоты стояния
	crouch_height = clamp(crouch_height, 2.0f * shape->getRadius(), shape->getHeight() + 2.0f * shape->getRadius());
	// Инициализируем конечный автомат приседания на высоте стояния
	crouch_state.current_height = shape->getHeight() + 2.0f * shape->getRadius();
	crouch_state.start_height = crouch_state.current_height;
	crouch_state.end_height = crouch_height.get();

	// Камера может быть: NONE (без управления), CREATE_AUTOMATICALLY (дочерний PlayerDummy),
	// или USE_EXTERNAL (назначенный в редакторе узел камеры)
	camera = checked_ptr_cast<PlayerDummy>(camera_editor_node.get());

	if (camera_mode == CameraMode::USE_EXTERNAL && !camera)
		Log::warning("FirstPersonController: camera is null, it was created automatically\n");

	if (!camera || camera_mode == CameraMode::CREATE_AUTOMATICALLY)
	{
		camera = PlayerDummy::create();
		camera->setParent(obj);
		camera->setFov(fov);
		camera->setZNear(near_clipping);
		camera->setZFar(far_clipping);

		camera->setWorldPosition(obj->getWorldTransform() * Vec3(camera_position_offset));
		camera->setWorldDirection(vec3(axis_y), vec3_up);

		camera->setMainPlayer(true);
	}

	if (camera && camera_mode != CameraMode::NONE)
	{
		camera_vertical_angle = getAngle(vec3_down, camera->getWorldDirection());
		camera_vertical_angle = clamp(camera_vertical_angle, min_vertical_angle + 90.0f, max_vertical_angle + 90.0f);

		camera_horizontal_angle = node->getWorldRotation().getAngle(vec3_up);
		camera_position_offset = vec3(node->getIWorldTransform() * camera->getWorldPosition());

		vec3 camera_direction = vec3_forward * rotateZ(-camera_horizontal_angle);
		camera_direction = camera_direction * rotate(cross(camera_direction, vec3_up), 90.0f - camera_vertical_angle);
		camera_direction.normalize();
		camera->setWorldDirection(camera_direction, vec3_up);
	}

	// Форма-цилиндр для обнаружения твёрдых тел, которые нужно толкать. Немного больше капсулы,
	// чтобы гарантировать обнаружение контакта даже при неидеальном выравнивании.
	if (use_objects_interaction)
	{
		interaction_shape = ShapeCylinder::create();
		interaction_shape->setEnabled(false);
	}

	// Предварительно вычисляем косинусы один раз для быстрого сравнения углов при проверке коллизий.
	// Сравнение косинусов быстрее, чем вычисление углов каждый кадр.
	player_ifps = 1.0f / player_fps;
	crouch_transition_time = max(crouch_transition_time, Consts::EPS);

	cos_ground_angle = Math::cos(max_ground_angle * Math::Consts::DEG2RAD);
	cos_ceiling_angle = Math::cos(max_ceiling_angle * Math::Consts::DEG2RAD);
	cos_stair_angle = Math::cos(max_stair_angle * Math::Consts::DEG2RAD);
	cos_stairs_detection_angle = Math::cos(stairs_detection_angle * Math::Consts::DEG2RAD + Math::Consts::PI05);
	cos_wall_stop_sliding_angle = Math::cos(wall_stop_sliding_angle * Math::Consts::DEG2RAD);

	// Многократно используемый объект результата пересечения (избегает выделения памяти каждый кадр)
	normal_intersection = WorldIntersectionNormal::create();

#if DEBUG
	max_pass_contacts = contacts_buffer_size;
#endif

	world_transform = obj->getWorldTransform();

	// Ищем первый доступный геймпад для альтернативного ввода
	for (int i = 0; i < Input::getNumGamePads(); i++)
	{
		if (Input::getGamePad(i)->isAvailable())
		{
			game_pad = Input::getGamePad(i);
			break;
		}
	}

	is_initialized = true;

#if DEBUG
	init_debug();
#endif
}

// Основной цикл обновления: считывает ввод, обновляет физику подшагами, обрабатывает приседание.
// Вызывается каждый кадр рендера. Использует адаптивный шаг по времени для стабильной физики
// независимо от частоты кадров (разбивает время кадра на части по player_ifps).
void FirstPersonController::update()
{
	if (!is_initialized)
		return;

	world_transform = node->getWorldTransform();

	// Масштабируем время кадра масштабом физики для поддержки замедленной съёмки
	float ifps = Game::getIFps() * Physics::getScale();

	update_move_directions(ifps);
	check_move_and_stair();

	// Если движение заблокировано и есть контакты с землёй, полностью останавливаемся,
	// чтобы предотвратить дрожание при упоре в стены
	if (!is_available_side_move)
	{
		if (has_bottom_contacts)
		{
			horizontal_velocity = Vec3_zero;
			horizontal_move_direction = vec2_zero;
		}
	}

	// Разбиваем кадр на шаги фиксированного размера для стабильного поведения физики.
	// Длинные кадры делятся на несколько итераций, чтобы предотвратить проваливание
	// сквозь геометрию и обеспечить стабильную обработку коллизий.
	float update_time = ifps;
	has_bottom_contacts = false;
	while (update_time > 0.0f)
	{
		float adaptive_time_step = min(update_time, player_ifps);
		update_time -= adaptive_time_step;

		update_velocity(adaptive_time_step, adaptive_time_step / ifps);
		// Применяем скорость к трансформации, затем обрабатываем коллизии
		mul(world_transform, translate((horizontal_velocity + Vec3_up * vertical_velocity) * adaptive_time_step), world_transform);
		update_collisions(adaptive_time_step);
	}

	update_crouch(ifps);

	// Применяем итоговую трансформацию игрока
	node->setWorldTransform(world_transform);
	body->setTransform(node->getWorldTransform());
	if (is_crouch)
		shape->setTransform(world_transform * translate(Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f)));

	update_camera();

#if DEBUG
	update_debug();
#endif
}

// Такт физики: применяет импульсы к твёрдым телам, которых касается игрок.
// Выполняется с фиксированной частотой физики (не частотой рендера) для стабильного толкания объектов.
void FirstPersonController::update_physics()
{
	if (!is_initialized)
		return;

	if (use_objects_interaction)
	{
		// Форма-цилиндр немного больше капсулы, чтобы улавливать объекты,
		// которые могут проскользнуть через зазоры, особенно у ног игрока
		interaction_shape->setEnabled(true);
		interaction_shape->setRadius(shape->getRadius() + check_move_ray_offset + skin_width_offset);
		interaction_shape->setHeight(shape->getHeight() + 2.0f * (shape->getRadius() + check_move_ray_offset - skin_width_offset));
		interaction_shape->setTransform(translate(world_transform.getTranslate() + Vec3_up * (0.5f * interaction_shape->getHeight() + skin_width_offset)));

		interaction_shape->getCollision(contacts);
		int contacts_count = min(contacts_buffer_size, contacts.size());

		Scalar speed = horizontal_velocity.length() + Math::abs(vertical_velocity);
		speed = max(speed, static_cast<Scalar>(1.0f));

		// Вычисляем силу импульса на основе массы и скорости игрока.
		// Делим на количество контактов, чтобы равномерно распределить силу по всем задетым объектам.
		float k = player_mass * impulse_multiplier * 0.5f;
		if (contacts_count > 0)
			k /= contacts_count;

		// Применяем импульсы к каждому задетому твёрдому телу
		float top_cap_z = shape->getTopCap().z;
		for (int i = 0; i < contacts_count; i++)
		{
			const ShapeContactPtr &c = contacts[i];
			if (auto contact_object = c->getObject())
			{
				if (auto rb = contact_object->getBodyRigid())
				{
					Vec3 point = c->getPoint();
					if (ignore_top_contacts && point.z > top_cap_z)
						continue;

					rb->setFrozen(false);
					rb->addWorldImpulse(point, -c->getNormal() * k * speed);
				}
			}
		}

		interaction_shape->setEnabled(false);
	}
}

// Считывает ввод с клавиатуры/геймпада и преобразует его в векторы направления движения.
// Стик геймпада перекрывает клавиатуру, если величина его ввода больше.
void FirstPersonController::update_move_directions(float ifps)
{
	// Очищаем ввод предыдущего кадра
	horizontal_move_direction = vec2_zero;
	vertical_move_direction = 0.0f;

	// Обрабатываем ввод только когда мышь захвачена (у игры есть фокус)
	if (!Input::isMouseGrab())
		return;

	// Строим вектор направления по клавишам WASD (нормализованное диагональное движение)
	if (Input::isKeyPressed(static_cast<Input::KEY>(forward_key.get())))
		horizontal_move_direction += forward;

	if (Input::isKeyPressed(static_cast<Input::KEY>(backward_key.get())))
		horizontal_move_direction -= forward;

	if (Input::isKeyPressed(static_cast<Input::KEY>(right_key.get())))
		horizontal_move_direction += right;

	if (Input::isKeyPressed(static_cast<Input::KEY>(left_key.get())))
		horizontal_move_direction -= right;

	horizontal_move_direction.normalize();

	if (game_pad)
	{
		vec2 moveValue = (move_stick == GamepadStickSide::LEFT ? game_pad->getAxesLeft() : game_pad->getAxesRight());
		if (moveValue.length() > sticks_dead_zone && moveValue.length2() > horizontal_move_direction.length2())
			horizontal_move_direction = moveValue;
	}

	// Обновляем вертикальное направление (импульс прыжка при нахождении на земле)
	if (use_jump && is_ground && (Input::isKeyDown(static_cast<Input::KEY>(jump_key.get())) ||
		game_pad && game_pad->isButtonDown(static_cast<Input::GAMEPAD_BUTTON>(jump_button.get()))))
	{
		vertical_move_direction = (is_crouch ? crouch_jump_power : jump_power) / ifps;
	}
}

// Трассирует лучи впереди игрока для обнаружения проходимых поверхностей и ступеней.
// Устанавливает is_available_side_move, если направление движения ведёт на допустимую землю,
// и is_available_stair, если следует попытаться выполнить автоступень.
void FirstPersonController::check_move_and_stair()
{
	is_available_side_move = false;
	is_available_stair = false;

	vec3 horizontal_direction = world_transform.getRotate() * vec3(horizontal_move_direction);
	horizontal_move_direction.normalize();

	// Трассируем луч вниз впереди игрока, чтобы проверить проходимость поверхности
	if (horizontal_move_direction.length2() > 0.0f)
	{
		Vec3 p2 = world_transform.getTranslate() + Vec3(horizontal_direction) * (static_cast<Scalar>(shape->getRadius()) + check_move_ray_offset) + Vec3_down * Scalar(check_move_ray_offset.get());
		Vec3 p1 = p2 + Vec3_up * (max(shape->getRadius(), max_step_height) + check_move_ray_offset);

		auto hitObj = World::getIntersection(p1, p2, check_move_mask, normal_intersection);
		if (hitObj)
		{
			if (dot(vec3_up, normal_intersection->getNormal()) > cos_ground_angle)
				is_available_side_move = true;

			// Разрешаем движение при приближении к другой наклонной поверхности - это позволяет
			// подниматься по пандусам и переходить между поверхностями с разными углами
			Scalar cos = dot(slope_normal, Vec3(normal_intersection->getNormal()));
			if (cos < large_epsilon)
				is_available_side_move = true;
		}
		else
		{
			// Разрешаем движение в воздухе (поверхность не обнаружена)
			is_available_side_move = true;
		}

	#if DEBUG
		if (debug_visualizer.get().enabled && debug_visualizer.get().check_move_ray)
		{
			if (is_available_side_move)
				Visualizer::renderVector(p1, p2, vec4_green);
			else
				Visualizer::renderVector(p1, p2, vec4_red);
		}
	#endif
	}

	// Проверяем угол поверхности ступени для автоступеней
	if (use_auto_stepping && horizontal_move_direction.length2() > 0.0f)
	{
		Vec3 p2 = world_transform.getTranslate() + Vec3(horizontal_direction)
			* static_cast<Scalar>(shape->getRadius() + check_stair_ray_offset)
			+ Vec3_up * static_cast<Scalar>(min_step_height);
		Vec3 p1 = p2 + Vec3(vec3_up)
			* static_cast<Scalar>(max_step_height.get() - min_step_height.get() + check_stair_ray_offset.get());

		auto hitObj = World::getIntersection(p1, p2, stair_detection_mask, normal_intersection);
		if (hitObj)
		{
			if (dot(vec3_up, normal_intersection->getNormal()) > cos_stair_angle)
				is_available_stair = true;
		}

	#if DEBUG
		if (debug_visualizer.get().enabled && debug_visualizer.get().stair_detection_ray)
		{
			if (is_available_stair)
				Visualizer::renderVector(p1, p2, vec4_green);
			else
				Visualizer::renderVector(p1, p2, vec4_red);
		}
	#endif
	}
}

// Обновляет скорость игрока на основе ввода, наклона поверхности, поворота и физики.
// Строит локальную систему координат, выровненную по текущей наклонной поверхности, для естественного движения.
// На земле смена направления мгновенная; в воздухе движение обладает инерцией.
void FirstPersonController::update_velocity(float ifps, float update_part)
{
	// Строим систему координат, выровненную по наклонной поверхности. Необходимо проверять коллинеарность,
	// так как векторное произведение параллельных векторов равно нулю (вырожденный случай на ровной земле)
	Scalar cos_angle = dot(Vec3(world_transform.getAxisY()), slope_normal);
	if (compare(Math::abs(cos_angle), static_cast<Scalar>(1.0f)) == 0)
	{
		slope_axis_x = cross(Vec3(world_transform.getAxisY()), slope_normal).normalize();
		slope_axis_y = cross(slope_normal, slope_axis_x).normalize();
	}
	else
	{
		slope_axis_y = cross(Vec3(world_transform.getAxisX()) * sign(cos_angle), slope_normal).normalize();
		slope_axis_x = cross(slope_axis_y, slope_normal).normalize();
	}

	// Раскладываем скорость в базис наклонной поверхности для мгновенной смены направления на земле
	Vec3 horizontal_velocity_decomposition = Vec3_zero;
	if (is_ground)
	{
		horizontal_velocity_decomposition.x = dot(slope_axis_x, horizontal_velocity);
		horizontal_velocity_decomposition.y = dot(slope_axis_y, horizontal_velocity);
		horizontal_velocity_decomposition.z = dot(slope_normal, horizontal_velocity);
	}

	// Поворот игрока по вводу мыши/геймпада
	if (Input::isMouseGrab())
	{
		world_transform *= Mat4(rotate(quat(vec3_up, -Input::getMouseDeltaPosition().x * mouse_sensitivity * update_part)));

		float delta = -Input::getMouseDeltaPosition().x * mouse_sensitivity;
		if (game_pad)
		{
			vec2 rotate_value = (camera_stick == GamepadStickSide::LEFT ? game_pad->getAxesLeft() : game_pad->getAxesRight());
			if (rotate_value.length() > sticks_dead_zone && Math::abs(rotate_value.x * camera_stick_sensitivity) > Math::abs(delta))
				delta = -rotate_value.x * camera_stick_sensitivity;
		}

		camera_horizontal_angle += delta * update_part;
		if (camera_horizontal_angle < -180.0f || 180.0f < camera_horizontal_angle)
			camera_horizontal_angle -= sign(camera_horizontal_angle) * 360.0f;

		Vec3 position = world_transform.getTranslate();
		world_transform.setRotate(Vec3_up, camera_horizontal_angle);
		world_transform.setColumn3(3, position);
	}

	// На земле меняем направление скорости мгновенно (без инерции)
	if (is_ground)
	{
		// Пересчитываем базис наклонной поверхности после поворота
		cos_angle = dot(Vec3(world_transform.getAxisY()), slope_normal);
		if (compare(Math::abs(cos_angle), static_cast<Scalar>(1.0f)) == 0)
		{
			slope_axis_x = cross(Vec3(world_transform.getAxisY()), slope_normal).normalize();
			slope_axis_y = cross(slope_normal, slope_axis_x).normalize();
		}
		else
		{
			slope_axis_y = cross(Vec3(world_transform.getAxisX()) * sign(cos_angle), slope_normal).normalize();
			slope_axis_x = cross(slope_axis_y, slope_normal).normalize();
		}

		// Восстанавливаем скорость в новом базисе наклонной поверхности
		horizontal_velocity = slope_axis_x * horizontal_velocity_decomposition.x +
			slope_axis_y * horizontal_velocity_decomposition.y +
			slope_normal * horizontal_velocity_decomposition.z;
	}

	// Добавляем горизонтальную скорость в базисе наклонной поверхности
	float acceleration = (is_ground ? ground_acceleration : air_acceleration);
	horizontal_velocity += slope_axis_x * horizontal_move_direction.x * acceleration * ifps;
	horizontal_velocity += slope_axis_y * horizontal_move_direction.y * acceleration * ifps;

	// Обновляем вертикальную скорость (прыжок + гравитация)
	vertical_velocity += vertical_move_direction * ifps;
	if (!is_ground)
		vertical_velocity += Physics::getGravity().z * ifps;

	// Получаем текущую максимальную скорость на основе режима передвижения
	float max_speed = max_air_speed;
	if (is_ground)
	{
		max_speed = (use_run && use_run_default) ? run_speed : walk_speed;

		if (use_run && (Input::isKeyPressed(static_cast<Input::KEY>(run_key.get())) ||
			game_pad && game_pad->isButtonPressed(static_cast<Input::GAMEPAD_BUTTON>(run_button.get()))))
		{
			max_speed = use_run_default ? walk_speed : run_speed;
		}

		if (is_ground && is_crouch)
			max_speed = crouch_speed;

		max_air_speed = max_speed;
	}

	// Применяем затухание, когда скорость превышает целевую или ввод отсутствует
	vec2 targetSpeed = horizontal_move_direction * max_speed;
	if (targetSpeed.length() < Consts::EPS || targetSpeed.length() < horizontal_velocity.length())
		horizontal_velocity *= Math::exp((is_ground ? -ground_damping : -air_damping) * ifps);

	// Ограничиваем горизонтальную скорость максимальным значением
	if (horizontal_velocity.length() > max_speed)
		horizontal_velocity = horizontal_velocity.normalize() * max_speed;

	// Проверяем состояние заморозки (предотвращает скольжение по наклонной поверхности при почти неподвижном состоянии)
	is_horizontal_frozen = is_ground && (horizontal_velocity.length() < Physics::getFrozenLinearVelocity());
}

// Основной цикл обработки коллизий. Выполняет несколько итераций для обработки сложных
// сценариев контактов (углы, клинья). Каждая итерация может автоматически подниматься над препятствиями,
// обрабатывать горизонтальные контакты, а затем опускаться для поиска земли.
void FirstPersonController::update_collisions(float ifps)
{
	// Сбрасываем состояние коллизий для этого кадра
	is_ground = false;
	is_ceiling = false;
	slope_normal = Vec3_up;

	is_heavy_contacts = false;

	// Обрабатываем коллизии итеративно
	for (int j = 0; j < collision_iterations; j++)
	{
		if (use_auto_stepping)
		{
		#if DEBUG
			auto_stepping_applied = false;
		#endif
			if (is_available_stair)
				try_move_up(ifps);
		}

		move_side(ifps);

		if (use_auto_stepping && used_auto_stepping && is_available_stair)
		{
		#if DEBUG
			auto_stepping_applied = true;
		#endif
			try_move_down(ifps);
		}

		if (is_heavy_contacts)
			break;
	}
}

// Автоступени, фаза 1: поднимает игрока над препятствием. Анализирует контакты,
// чтобы найти самую высокую ступень в направлении движения, затем поднимает игрока над ней.
// Активируется только при движении вперёд, отсутствии заморозки и падении (не прыжке).
void FirstPersonController::try_move_up(float ifps)
{
	used_auto_stepping = false;
	last_step_height = 0.0f;

	// Поднимаемся только при горизонтальном движении и отсутствии прыжка вверх
	if (horizontal_move_direction.length2() > 0.0f && !is_horizontal_frozen && vertical_velocity < 0.0f)
	{
		body->setTransform(world_transform);
		if (is_crouch)
			shape->setTransform(world_transform * translate(Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f)));

		// Запрашиваем все контакты в текущей позиции
		shape->getCollision(contacts);
		if (contacts.size() == 0)
			return;

		if (contacts.size() > heavy_contacts_count)
			is_heavy_contacts = true;

		int contacts_count = min(contacts_buffer_size, contacts.size());

		// Ищем максимальную высоту ступени по контактам в направлении движения
		Vec2 velocity_xy = Vec2(horizontal_velocity);
		if (velocity_xy.length2() < auto_stepping_speed_threshold)
		{
			// Задаём минимальную скорость для подъёма
			velocity_xy = Vec2(world_transform.getRotate() * Vec3(Vec2(horizontal_move_direction)));
			velocity_xy.normalize();
			horizontal_velocity = Vec3(velocity_xy * static_cast<Scalar>(walk_speed));
		}

		for (int i = 0; i < contacts_count; i++)
		{
			const ShapeContactPtr &c = contacts[i];

			Vec2 normalXY = Vec2(Vec3(c->getNormal()));

			// Пропускаем контакты, противоположные направлению движения
			if (dot(normalXY, velocity_xy) > cos_stairs_detection_angle)
				continue;

			Scalar step = dot(c->getPoint() - world_transform.getTranslate(), Vec3_up);
			if (last_step_height < step)
				last_step_height = step;
		}

		// Применяем автоступень, если высота ступени в допустимом диапазоне
		if (min_step_height < last_step_height && last_step_height < max_step_height)
		{
			world_transform.setColumn3(3, world_transform.getTranslate() + Vec3(vec3_up) * last_step_height);

			// Проверяем контакты после подъёма; отменяем ступень, если заблокировано
			body->setTransform(world_transform);
			if (is_crouch)
				shape->setTransform(world_transform * translate(Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f)));

			shape->getCollision(contacts);
			if (contacts.size() == 0)
				used_auto_stepping = true;
			else
				world_transform.setColumn3(3, world_transform.getTranslate() + Vec3(vec3_down) * last_step_height);
		}

	#if DEBUG
		if (debug_visualizer.get().enabled && debug_visualizer.get().up_pass_contacts)
		{
			for (const auto &c : contacts)
				Visualizer::renderVector(c->getPoint(), c->getPoint() + Vec3(c->getNormal()), debug_colors.get().up_pass_contacts);
		}

		if (debug_profiler.get().enabled && debug_profiler.get().up_pass_contact)
			Profiler::setValue("Up Pass Contacts ", "", contacts.size(), max_pass_contacts, debug_colors.get().array_up_pass_contacts);
	#endif
	}
}

// Основной проход обработки коллизий: устраняет проникновения в геометрию мира.
// Выталкивает игрока из контактов, гасит скорость, направленную в поверхности, определяет
// состояния земли/потолка и отслеживает нормаль наклонной поверхности для направления движения.
void FirstPersonController::move_side(float ifps)
{
	// Синхронизируем физическое тело с текущей мировой трансформацией
	body->setTransform(world_transform);
	if (is_crouch)
		shape->setTransform(world_transform * translate(Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f)));

	// Получаем контакты в новой позиции и обрабатываем их
	shape->getCollision(contacts);
	if (contacts.size() == 0)
		return;

	if (contacts.size() > heavy_contacts_count)
		is_heavy_contacts = true;

	int contacts_count = min(contacts_buffer_size, contacts.size());

	// Суммарное смещение позиции, накопленное по глубинам всех контактов
	auto position_offset = vec3_zero;

	// Отслеживаем максимальный угол наклона под игроком
	float max_cos_angle = 1.0f;

	float inum = 1.0f / contacts_count;
	for (int i = 0; i < contacts_count; i++)
	{
		const ShapeContactPtr &c = contacts[i];

		// При заморозке двигаемся только по вертикали, чтобы предотвратить скольжение по наклонной поверхности;
		// иначе обрабатываем во всех направлениях
		if (is_horizontal_frozen)
		{
			float depth = dot(vec3_up, c->getNormal()) * (c->getDepth() - Consts::EPS);
			position_offset += vec3_up * depth * inum;
		}
		else
		{
			position_offset += c->getNormal() * (c->getDepth() - Consts::EPS) * inum;

			// Убираем компонент скорости, спроецированный на нормаль контакта
			Scalar normal_speed = dot(Vec3(c->getNormal()), horizontal_velocity);
			horizontal_velocity -= Vec3(c->getNormal()) * normal_speed;
		}

		// Останавливаем скольжение при почти лобовом ударе о стену
		if ((c->getObject() && !c->getObject()->getBodyRigid()) && shape->getBottomCap().z < c->getPoint().z && c->getPoint().z < shape->getTopCap().z)
		{
			float cos = dot(world_transform.getRotate() * vec3(horizontal_move_direction), -c->getNormal());
			if (cos > cos_wall_stop_sliding_angle)
				horizontal_velocity = Vec3_zero;
		}

		// Проверяем состояние земли: контакт на нижней полусфере + угол поверхности в допустимом пределе
		if (dot(c->getPoint() - shape->getBottomCap(), Vec3_up) < 0.0f)
		{
			has_bottom_contacts = true;
			if (dot(c->getNormal(), vec3_up) > cos_ground_angle)
			{
				vertical_velocity = Physics::getGravity().z * ifps;
				is_ground = true;
			}

			// Отслеживаем самую крутую нормаль поверхности под игроком
			float cos_angle = dot(vec3_up, c->getNormal());
			if (compare(cos_angle, 0.0f, 0.01f) == 0 && cos_angle < max_cos_angle)
			{
				slope_normal = Vec3(contacts[i]->getNormal());
				max_cos_angle = cos_angle;
			}
		}

		// Проверяем состояние потолка: контакт на верхней полусфере + угол поверхности в допустимом пределе
		if (dot(contacts[i]->getNormal(), vec3_down) > cos_ceiling_angle && dot(contacts[i]->getPoint() - shape->getTopCap(), Vec3_down) < 0.0f)
		{
			is_ceiling = true;

			// Останавливаем движение вверх при ударе о потолок
			vertical_velocity = 0.0f;
		}
	}

	// Применяем накопленное смещение позиции
	world_transform.setColumn3(3, world_transform.getTranslate() + Vec3(position_offset));

#if DEBUG
	if (debug_visualizer.get().enabled && debug_visualizer.get().side_pass_contacts)
	{
		for (const auto &c : contacts)
			Visualizer::renderVector(c->getPoint(), c->getPoint() + Vec3(c->getNormal()), debug_colors.get().side_pass_contacts);
	}

	if (debug_profiler.get().enabled && debug_profiler.get().side_pass_contact)
		Profiler::setValue("Side Pass Contacts ", "", contacts.size(), max_pass_contacts, debug_colors.get().array_side_pass_contacts);
#endif
}

// Автоступени, фаза 2: опускает игрока обратно после подъёма.
// После того как try_move_up поднял игрока над препятствием, эта функция находит
// фактический уровень земли и привязывает игрока к нему для плавного прохождения лестниц.
void FirstPersonController::try_move_down(float ifps)
{
	// Большие ступени вызывают дрожание, так как игрок многократно проскакивает и
	// корректируется. Ограничение радиусом капсулы обеспечивает плавное движение на больших лестницах.
	if (last_step_height > shape->getRadius())
		last_step_height = shape->getRadius() - Physics::getPenetrationTolerance();

	// Опускаем игрока на высоту ступени, на которую подняли в try_move_up
	world_transform.setColumn3(3, world_transform.getTranslate() - Vec3(vec3_up) * last_step_height);

	body->setTransform(world_transform);
	if (is_crouch)
		shape->setTransform(world_transform * translate(Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f)));

	// Ищем коллизии капсулы
	shape->getCollision(contacts);
	if (contacts.size() == 0)
		return;

	if (contacts.size() > heavy_contacts_count)
		is_heavy_contacts = true;

	int contacts_count = min(contacts_buffer_size, contacts.size());

	// Обрабатываем контакты, чтобы найти землю
	float inum_contacts = 1.0f / itof(contacts_count);
	for (int i = 0; i < contacts_count; i++)
	{
		const ShapeContactPtr &c = contacts[i];

		float depth = dot(vec3_up, c->getNormal()) * c->getDepth();
		world_transform.setColumn3(3, world_transform.getTranslate()
			+ Vec3(vec3_up) * static_cast<Scalar>(depth) * static_cast<Scalar>(inum_contacts));

		if (dot(c->getNormal(), vec3_up) > cos_ground_angle && dot(c->getPoint() - shape->getBottomCap(), Vec3_up) < 0.0f)
		{
			is_ground = true;
			vertical_velocity = Physics::getGravity().z * ifps;
		}
	}

#if DEBUG
	if (debug_visualizer.get().enabled && debug_visualizer.get().down_pass_contacts)
	{
		for(const auto &c : contacts)
			Visualizer::renderVector(c->getPoint(), c->getPoint() + Vec3(c->getNormal()), debug_colors.get().down_pass_contacts);
	}

	if (debug_profiler.get().enabled && debug_profiler.get().down_pass_contact)
		Profiler::setValue("Down Pass Contacts ", "", contacts.size(), max_pass_contacts, debug_colors.get().array_down_pass_contacts);
#endif
}

// Конечный автомат для плавных переходов приседания. Обрабатывает четыре фазы:
// STAND (полная высота), MOVE_DOWN (уменьшение), CROUCH (присед), MOVE_UP (увеличение).
// Проверяет свободное пространство сверху перед вставанием, чтобы предотвратить проваливание сквозь потолок.
void FirstPersonController::update_crouch(float ifps)
{
	if (!use_crouch)
		return;

	// Считываем ввод приседания с клавиатуры или геймпада
	bool is_key = (Input::isKeyPressed(static_cast<Input::KEY>(crouch_key.get())) ||
				  game_pad && game_pad->isButtonPressed(static_cast<Input::GAMEPAD_BUTTON>(crouch_button.get())));

	// Конечный автомат: определяем поведение на основе текущей фазы приседания
	switch (crouch_state.phase)
	{
		case CrouchPhase::STAND:
			if (is_key)
			{
				// Начинаем плавный переход в присед
				crouch_state.phase = CrouchPhase::MOVE_DOWN;
				swap_interpolation_direction(capsule_height + 2.0f * shape->getRadius(), crouch_height);
				is_crouch = true;
			}
			break;

		case CrouchPhase::MOVE_DOWN:
		case CrouchPhase::CROUCH:
			if (!is_key)
			{
				// Пытаемся встать: проверяем, есть ли место сверху
				bool can_stand_up = true;

				// Временно устанавливаем форму для стояния (уже, чтобы избежать ложных контактов со стенами)
				float radius = shape->getRadius();
				shape->setRadius(radius - skin_width_offset);
				update_player_height(capsule_height + 2.0f * skin_width_offset);

				// Проверяем препятствия сверху
				shape->getCollision(contacts);

				Scalar top_point = world_transform.getTranslate().z + crouch_height;
				for (int i = 0; i < contacts.size(); i++)
					if (contacts[i]->getPoint().z > top_point)
					{
						// Заблокировано препятствием сверху
						can_stand_up = false;
						break;
					}

				// Восстанавливаем текущие параметры формы
				shape->setRadius(radius);
				update_player_height(crouch_state.current_height - 2.0f * shape->getRadius());

				if (can_stand_up)
				{
					// Начинаем плавный переход в положение стоя
					crouch_state.phase = CrouchPhase::MOVE_UP;
					swap_interpolation_direction(crouch_height, capsule_height + 2.0f * shape->getRadius());
				}
			}
			break;

		case CrouchPhase::MOVE_UP:
			if (is_ceiling || is_key)
			{
				// Удар о потолок или нажата клавиша: возвращаемся в присед
				crouch_state.phase = CrouchPhase::MOVE_DOWN;
				swap_interpolation_direction(capsule_height + 2.0f * shape->getRadius(), crouch_height);
			}
			break;

		default: break;
	}

	// Обрабатываем плавную интерполяцию высоты
	if (crouch_state.current_time > 0.0f)
	{
		// Вычисляем коэффициент интерполяции на основе оставшегося времени перехода
		float t = 1.0f;
		if (compare(crouch_transition_time, Consts::EPS) == 0)
			t = saturate(1.0f - crouch_state.current_time / crouch_transition_time);

		// Обновляем высоту капсулы
		crouch_state.current_height = lerp(crouch_state.start_height, crouch_state.end_height, static_cast<Scalar>(t));
		update_player_height(crouch_state.current_height - 2.0f * shape->getRadius());

		crouch_state.current_time -= ifps;

		// Завершаем переход по истечении времени
		if (crouch_state.current_time <= 0.0f)
		{
			// Устанавливаем финальное время и высоту
			crouch_state.current_time = 0.0f;
			crouch_state.current_height = crouch_state.end_height;

			switch (crouch_state.phase)
			{
				case CrouchPhase::MOVE_DOWN:
					// Переход завершён: входим в состояние приседа
					update_player_height(crouch_state.current_height - 2.0f * shape->getRadius());
					crouch_state.phase = CrouchPhase::CROUCH;
					break;

				case CrouchPhase::MOVE_UP:
					// Переход завершён: входим в состояние стояния
					update_player_height(crouch_state.current_height - 2.0f * shape->getRadius());
					crouch_state.phase = CrouchPhase::STAND;
					is_crouch = false;
					break;

				default: break;
			}
		}
	}
}

// Обновляет позицию и ориентацию камеры. Применяет вертикальный угол по вводу мыши,
// объединяет все смещения позиции (базовое, приседания, дополнительное) и
// строит направление обзора из сферических координат (рыскание + тангаж).
void FirstPersonController::update_camera()
{
	if (!camera || camera_mode == CameraMode::NONE)
		return;

	if (Input::isMouseGrab())
	{
		// Считываем вертикальный взгляд с мыши или геймпада (в зависимости от того, где дельта больше)
		camera_vertical_angle -= Input::getMouseDeltaPosition().y * mouse_sensitivity;

		float delta = -Input::getMouseDeltaPosition().y * mouse_sensitivity;
		if (game_pad)
		{
			vec2 rotate_value = (camera_stick == GamepadStickSide::LEFT ? game_pad->getAxesLeft() : game_pad->getAxesRight());
			if (rotate_value.length() > sticks_dead_zone && Math::abs(rotate_value.y * camera_stick_sensitivity) > Math::abs(delta))
				delta = rotate_value.y * camera_stick_sensitivity;
		}

		camera_vertical_angle += delta;
		camera_vertical_angle = clamp(camera_vertical_angle, min_vertical_angle + 90.0f, max_vertical_angle + 90.0f);
	}

	// Применяем позицию камеры со всеми смещениями (базовое + присед + дополнительное)
	camera->setWorldPosition(world_transform * (Vec3(camera_position_offset.get()) + Vec3(camera_crouch_offset) + Vec3(additional_camera_offset)));

	vec3 camera_direction = vec3_forward * rotateZ(-camera_horizontal_angle);
	camera_direction = camera_direction * rotate(cross(camera_direction, vec3_up), 90.0f - camera_vertical_angle);
	camera_direction = additional_camera_rotation * camera_direction;
	camera_direction.normalize();
	camera->setWorldDirection(camera_direction, vec3_up);
}

// Меняет направление перехода приседания в середине интерполяции. Используется, когда игрок
// отпускает клавишу приседания во время перехода вниз, или ударяется о потолок во время
// перехода вверх. Сохраняет плавность движения за счёт использования оставшегося времени.
void FirstPersonController::swap_interpolation_direction(Scalar start_height, Scalar end_height)
{
	// Оставшееся время перехода становится новой длительностью (плавный разворот)
	crouch_state.current_time = max(Consts::EPS, crouch_transition_time - crouch_state.current_time);
	crouch_state.start_height = start_height;
	crouch_state.end_height = end_height;
}

// Изменяет размер капсулы коллизии и корректирует смещение камеры под новую высоту.
// Вызывается во время переходов приседания для плавной анимации высоты игрока.
void FirstPersonController::update_player_height(Scalar height)
{
	shape->setHeight((float)height);
	// Смещение камеры - это разница между текущей высотой и высотой стояния
	camera_crouch_offset = vec3_up * (height - capsule_height);
	// Заново центрируем форму капсулы относительно точки начала координат игрока
	shape->setTransform(world_transform * translate(Vec3_up * (shape->getRadius() + height * 0.5f)));
}

#if DEBUG

// Инициализирует системы отладочной визуализации: камеру от третьего лица для наблюдения
// за игроком снаружи, визуализатор для отображения данных коллизий и профилировщик
// для отображения метрик в реальном времени на экране.
void FirstPersonController::init_debug()
{
	if (!is_initialized)
		return;

	// Создаём вращающуюся отладочную камеру, которая смотрит на игрока снаружи
	if (debug_camera.get().enabled)
	{
		debug_camera.get().camera = PlayerDummy::create();
		debug_camera.get().angular_speed = 90.0f;
		debug_camera.get().zoom_speed = 3.0f;
		debug_camera.get().max_distance = 10.0f;
		debug_camera.get().horizontal_angle = 0.0f;
		debug_camera.get().vertical_angle = 0.0f;
		debug_camera.get().distance = debug_camera.get().max_distance * 0.5f;

		Game::setPlayer(debug_camera.get().camera);

		debug_camera.get().camera->setWorldDirection(vec3_forward, vec3_up);
		debug_camera.get().camera->setWorldPosition((world_transform.getTranslate() + Vec3(vec3_up)
			* static_cast<Scalar>(shape->getRadius() + shape->getHeight() * 0.5f)) - Vec3(vec3_forward)
			* static_cast<Scalar>(debug_camera.get().distance));
	}

	// Включаем визуализатор для отладочного рендеринга
	String command;

	Visualizer::setEnabled(debug_visualizer.get().enabled != 0);
	if (debug_visualizer.get().enabled)
	{
		Render::setShowTriangles(debug_visualizer.get().triangles ? 1 : 0);

		int showShapes = (debug_visualizer.get().shapes ? 1 : 0);
		command = "physics_show_shapes " + String::itoa(showShapes);
		Console::run(command);
	}

	// Включаем профилировщик для метрик производительности
	int show_profiler = (debug_profiler.get().enabled ? 1 : 0);
	command = "show_profiler " + String::itoa(show_profiler);
	Console::run(command);
	if (debug_profiler.get().enabled)
	{
		// Инициализируем массивы цветов профилировщика для каждой метрики
		max_applied_horizontal_speed = max(crouch_speed, walk_speed);
		max_applied_horizontal_speed = max(max_applied_horizontal_speed, run_speed);
		max_applied_horizontal_speed *= 1.1f;

		debug_colors.get().array_applied_horizontal_velocity[0] = debug_colors.get().applied_horizontal_velocity.get().x;
		debug_colors.get().array_applied_horizontal_velocity[1] = debug_colors.get().applied_horizontal_velocity.get().y;
		debug_colors.get().array_applied_horizontal_velocity[2] = debug_colors.get().applied_horizontal_velocity.get().z;
		debug_colors.get().array_applied_horizontal_velocity[3] = debug_colors.get().applied_horizontal_velocity.get().w;

		// применяемая вертикальная скорость
		debug_colors.get().array_applied_vertical_velocity[0] = debug_colors.get().applied_vertical_velocity.get().x;
		debug_colors.get().array_applied_vertical_velocity[1] = debug_colors.get().applied_vertical_velocity.get().y;
		debug_colors.get().array_applied_vertical_velocity[2] = debug_colors.get().applied_vertical_velocity.get().z;
		debug_colors.get().array_applied_vertical_velocity[3] = debug_colors.get().applied_vertical_velocity.get().w;

		// контакты верхнего прохода
		debug_colors.get().array_up_pass_contacts[0] = debug_colors.get().up_pass_contacts.get().x;
		debug_colors.get().array_up_pass_contacts[1] = debug_colors.get().up_pass_contacts.get().y;
		debug_colors.get().array_up_pass_contacts[2] = debug_colors.get().up_pass_contacts.get().z;
		debug_colors.get().array_up_pass_contacts[3] = debug_colors.get().up_pass_contacts.get().w;

		// контакты бокового прохода
		debug_colors.get().array_side_pass_contacts[0] = debug_colors.get().side_pass_contacts.get().x;
		debug_colors.get().array_side_pass_contacts[1] = debug_colors.get().side_pass_contacts.get().y;
		debug_colors.get().array_side_pass_contacts[2] = debug_colors.get().side_pass_contacts.get().z;
		debug_colors.get().array_side_pass_contacts[3] = debug_colors.get().side_pass_contacts.get().w;

		// контакты нижнего прохода
		debug_colors.get().array_down_pass_contacts[0] = debug_colors.get().down_pass_contacts.get().x;
		debug_colors.get().array_down_pass_contacts[1] = debug_colors.get().down_pass_contacts.get().y;
		debug_colors.get().array_down_pass_contacts[2] = debug_colors.get().down_pass_contacts.get().z;
		debug_colors.get().array_down_pass_contacts[3] = debug_colors.get().down_pass_contacts.get().w;

		// на земле
		debug_colors.get().array_is_ground[0] = debug_colors.get().is_ground.get().x;
		debug_colors.get().array_is_ground[1] = debug_colors.get().is_ground.get().y;
		debug_colors.get().array_is_ground[2] = debug_colors.get().is_ground.get().z;
		debug_colors.get().array_is_ground[3] = debug_colors.get().is_ground.get().w;

		// у потолка
		debug_colors.get().array_is_ceiling[0] = debug_colors.get().is_ceiling.get().x;
		debug_colors.get().array_is_ceiling[1] = debug_colors.get().is_ceiling.get().y;
		debug_colors.get().array_is_ceiling[2] = debug_colors.get().is_ceiling.get().z;
		debug_colors.get().array_is_ceiling[3] = debug_colors.get().is_ceiling.get().w;

		// в приседе
		debug_colors.get().array_is_crouch[0] = debug_colors.get().is_crouch.get().x;
		debug_colors.get().array_is_crouch[1] = debug_colors.get().is_crouch.get().y;
		debug_colors.get().array_is_crouch[2] = debug_colors.get().is_crouch.get().z;
		debug_colors.get().array_is_crouch[3] = debug_colors.get().is_crouch.get().w;

		// средняя скорость
		debug_colors.get().array_average_speed[0] = debug_colors.get().average_speed.get().x;
		debug_colors.get().array_average_speed[1] = debug_colors.get().average_speed.get().y;
		debug_colors.get().array_average_speed[2] = debug_colors.get().average_speed.get().z;
		debug_colors.get().array_average_speed[3] = debug_colors.get().average_speed.get().w;

		// профилирование автоступеней
		debug_colors.get().array_auto_stepping[0] = debug_colors.get().auto_stepping.get().x;
		debug_colors.get().array_auto_stepping[1] = debug_colors.get().auto_stepping.get().y;
		debug_colors.get().array_auto_stepping[2] = debug_colors.get().auto_stepping.get().z;
		debug_colors.get().array_auto_stepping[3] = debug_colors.get().auto_stepping.get().w;
	}

	last_player_position = world_transform.getTranslate();
}

// Отладочное обновление в каждом кадре: управляет вращением отладочной камеры стрелками,
// отрисовывает визуализации (форму, скорости, контакты) и обновляет
// метрики профилировщика (скорости, состояния, количество контактов).
void FirstPersonController::update_debug()
{
	if (!is_initialized)
		return;

	// Стрелки вращают отладочную камеру вокруг игрока, +/- приближение/отдаление
	if (debug_camera.get().enabled)
	{
		if (!debug_camera.get().use_fixed_angles)
		{
			if (Input::isKeyPressed(Input::KEY_UP))
				debug_camera.get().vertical_angle += debug_camera.get().angular_speed * Game::getIFps();
			if (Input::isKeyPressed(Input::KEY_DOWN))
				debug_camera.get().vertical_angle -= debug_camera.get().angular_speed * Game::getIFps();

			debug_camera.get().vertical_angle = clamp(debug_camera.get().vertical_angle, -89.9f, 89.9f);

			if (Input::isKeyPressed(Input::KEY_RIGHT))
				debug_camera.get().horizontal_angle -= debug_camera.get().angular_speed * Game::getIFps();
			if (Input::isKeyPressed(Input::KEY_LEFT))
				debug_camera.get().horizontal_angle += debug_camera.get().angular_speed * Game::getIFps();

			if (debug_camera.get().horizontal_angle < -180.0f || 180.0f < debug_camera.get().horizontal_angle)
				debug_camera.get().horizontal_angle -= sign(debug_camera.get().horizontal_angle) * 360.0f;
		}

		if (Input::isKeyPressed(Input::KEY_EQUALS))
			debug_camera.get().distance -= debug_camera.get().zoom_speed * Game::getIFps();
		if (Input::isKeyPressed(Input::KEY_MINUS))
			debug_camera.get().distance += debug_camera.get().zoom_speed * Game::getIFps();

		debug_camera.get().distance = clamp(debug_camera.get().distance, 0.0f, debug_camera.get().max_distance);

		vec3 camera_direction = debug_camera.get().camera->getDirection();
		if (debug_camera.get().use_fixed_angles && camera)
		{
			if (dot(camera->getDirection(), vec3_down) < 1.0f)
				camera_direction = camera->getWorldDirection();
		} else
		{
			camera_direction = vec3_forward * rotateZ(debug_camera.get().horizontal_angle);
			camera_direction = camera_direction * rotate(cross(camera_direction, vec3_up), debug_camera.get().vertical_angle);
		}

		debug_camera.get().camera->setWorldDirection(camera_direction, vec3_up);
	debug_camera.get().camera->setWorldPosition((world_transform.getTranslate() + Vec3(vec3_up)
		* static_cast<Scalar>(shape->getRadius() + shape->getHeight() * 0.5f)) - Vec3(camera_direction)
		* static_cast<Scalar>(debug_camera.get().distance));
	}

	// Рендерим отладочные визуализации
	if (debug_visualizer.get().enabled)
	{
		if (debug_visualizer.get().player_shape)
			shape->renderVisualizer(debug_colors.get().player_shape);

		if (debug_visualizer.get().player_direction)
		{
			Vec3 p0 = world_transform.getTranslate() + Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f);
			Vec3 p1 = p0 + Vec3(world_transform.getAxisY());
			Visualizer::renderVector(p0, p1, debug_colors.get().player_direction);
		}

		if (debug_visualizer.get().camera && camera)
		{
			Vec3 p0 = camera->getWorldPosition();
			Vec3 p1 = p0 + Vec3(camera->getWorldDirection());
			Visualizer::renderVector(p0, p1, debug_colors.get().camera_color);

			camera->renderVisualizer();
		}

		if (debug_visualizer.get().slope_basis)
		{
			Vec3 p0 = world_transform.getTranslate();
			Visualizer::renderVector(p0, p0 + slope_axis_x, vec4_red);
			Visualizer::renderVector(p0, p0 + slope_axis_y, vec4_green);
			Visualizer::renderVector(p0, p0 + slope_normal, vec4_blue);
		}

		if (debug_visualizer.get().applied_horizontal_velocity)
		{
			Vec3 p0 = world_transform.getTranslate() + Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f);
			Vec3 p1 = p0 + horizontal_velocity;
			Visualizer::renderVector(p0, p1, debug_colors.get().applied_horizontal_velocity);
		}

		if (debug_visualizer.get().applied_vertical_velocity)
		{
			Vec3 p0 = world_transform.getTranslate() + Vec3_up * (shape->getRadius() + shape->getHeight() * 0.5f);
			Vec3 p1 = p0 + Vec3(vec3_up) * static_cast<Scalar>(vertical_velocity);
			Visualizer::renderVector(p0, p1, debug_colors.get().applied_vertical_velocity);
		}
	}

	// Обновляем метрики профайлера
	if (debug_profiler.get().enabled)
	{
		if (debug_profiler.get().applied_horizontal_speed)
			Profiler::setValue("Applied Horizontal Speed", "m/s", (float)horizontal_velocity.length(), max_applied_horizontal_speed, debug_colors.get().array_applied_horizontal_velocity);

		if (debug_profiler.get().applied_vertical_speed)
			Profiler::setValue("|Applied Vertical Speed|", "m/s", Math::abs(vertical_velocity), max_applied_vertical_speed, debug_colors.get().array_applied_vertical_velocity);

		if (debug_profiler.get().is_ground)
			Profiler::setValue("Is Ground", "", (is_ground ? 1.0f : 0.0f), max_flag_value, debug_colors.get().array_is_ground);

		if (debug_profiler.get().is_ceiling)
			Profiler::setValue("Is Ceiling", "", (is_ceiling ? 1.0f : 0.0f), max_flag_value, debug_colors.get().array_is_ceiling);

		if (debug_profiler.get().is_crouch)
			Profiler::setValue("Is Crouch", "", (is_crouch ? 1.0f : 0.0f), max_flag_value, debug_colors.get().array_is_crouch);

		if (debug_profiler.get().average_speed)
		{
			for (int i = 0; i < speeds_buffer_size - 1; i++)
				speeds_buffer[i] = speeds_buffer[i + 1];

			speeds_buffer[speeds_buffer_size - 1] = (float)(world_transform.getTranslate() - last_player_position).length() / Game::getIFps();
			last_player_position = world_transform.getTranslate();

			float avg_speed = 0.0f;
			for (int i = 0; i < speeds_buffer_size; i++)
				avg_speed += speeds_buffer[i];

			avg_speed /= (float)speeds_buffer_size;

			Profiler::setValue("Avg Speed", "m/s", avg_speed, max_applied_horizontal_speed * 1.75f, debug_colors.get().array_average_speed);
		}

		if (debug_profiler.get().auto_stepping)
			Profiler::setValue("Auto Stepping", "", (auto_stepping_applied ? 1.0f : 0.0f), max_flag_value, debug_colors.get().array_auto_stepping);
	}
}

#endif