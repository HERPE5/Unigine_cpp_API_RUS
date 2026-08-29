// Камера вида сверху в стиле RTS с масштабированием, вращением, прокруткой у краёв экрана и
// панорамированием средней кнопкой мыши. Использует сферические координаты (phi/theta) для угла
// обзора, с theta, связанной с дистанцией, для более выраженного вида сверху при отдалении.
// Поддерживает плавную интерполяцию к целевой позиции/углу.

#include "TopDownController.h"
#include "Selection.h"
#include <UnigineConsole.h>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(TopDownController);

using namespace Unigine;
using namespace Math;

// Мгновенно размещает опорную точку камеры в указанной позиции.
void TopDownController::setPosition(const Unigine::Math::Vec3& pos)
{
	camera_pivot_position = pos;
	camera_pivot_position.z = 2.0f;
	current_camera_pivot_position = camera_pivot_position;
}

// Задаёт целевую позицию, к которой камера плавно приближается.
void TopDownController::setTargetPosition(const Unigine::Math::Vec3& pos)
{
	camera_pivot_position = pos;
	camera_pivot_position.z = 2.0f;
}

// Мгновенно задаёт дистанцию и пересчитывает угол theta.
void TopDownController::setDistance(float dist)
{
	distance = dist;

	distance = clamp(distance, min_distance, max_distance);
	theta = clamp(min_theta + (distance - min_distance) * degrees_per_unit, min_theta, max_theta);

	current_distance = distance;
	current_theta = theta;
}

// Задаёт целевую дистанцию для плавной анимации масштабирования.
void TopDownController::setTargetDistance(float dist)
{
	distance = dist;

	distance = clamp(distance, min_distance, max_distance);
	theta = clamp(min_theta + (distance - min_distance) * degrees_per_unit, min_theta, max_theta);
}

// Инициализирует параметры камеры из свойств, вычисляет соотношение degrees_per_unit,
// настраивает обработку мыши и создаёт компонент Selection для выбора юнитов.
void TopDownController::init()
{
	// Устанавливаем значения по умолчанию из свойств
	phi = phiProp.get();
	current_phi = phi;
	theta = thetaProp.get();
	current_theta = theta;
	min_theta = thetaMinMax.get().x;
	max_theta = thetaMinMax.get().y;

	distance = Distance.get();
	current_distance = distance;
	min_distance = distanceMinMax.get().x;
	max_distance = distanceMinMax.get().y;

	interpolation_factor = zoomSpeed.get();

	if (max_distance != min_distance)
		degrees_per_unit = (max_theta - min_theta) / (max_distance - min_distance);
	else
		degrees_per_unit = 0.0f;

	// Настраиваем камеру
	camera = checked_ptr_cast<Player>(node);
	if (!camera)
	{
		Log::error("TopDownController::init(): camera is not valid\n");
		return;
	}

	camera_pivot_position = node->getPosition();
	camera_pivot_position.z = 2.0f;
	current_camera_pivot_position = camera_pivot_position;

	// Настраиваем обработку ввода, мышь не будет захвачена
	Input::setMouseHandle(Input::MOUSE_HANDLE_USER);

	// Устанавливаем камеру в начальную позицию
	vec3 cameraViewDirection = quat(vec3_up, current_phi) * vec3_forward;
	cameraViewDirection = quat(cross(vec3_up, cameraViewDirection), -current_theta) * cameraViewDirection * -1;
	cameraViewDirection.normalize();

	camera->setViewDirection(cameraViewDirection);
	camera->setWorldPosition(current_camera_pivot_position - Vec3(cameraViewDirection) * current_distance);

	// Создаём логический узел и назначаем ему компонент Selection
	NodeDummyPtr logic = NodeDummy::create();
	selection = ComponentSystem::get()->addComponent<Selection>(logic);
}

// Обрабатывает ввод для масштабирования, вращения, панорамирования, фокуса и прокрутки у краёв.
// Обновляет целевые значения, к которым будет выполняться интерполяция в postUpdate.
void TopDownController::update()
{
	if (!camera)
		return;

	// Обработка ввода только когда консоль неактивна
	if (!Console::isActive())
	{
		// При нажатии средней кнопки мыши сохраняем начальный вектор для панорамирования
		if (Input::isMouseButtonDown(Input::MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE))
		{
			auto object = World::getIntersection(camera->getWorldPosition(), camera->getWorldPosition() + Vec3(camera->getDirectionFromMainWindow(Input::getMousePosition().x, Input::getMousePosition().y) * 10000), ~0, intersection);
			if (object)
			{
				is_previous_hooked = true;
				previous_mouse_to_intersection_point_vector = intersection->getPoint() - camera->getWorldPosition();
			}
			else
			{
				is_previous_hooked = false;
			}
		}

		// Обрабатываем ввод для масштабирования (колесо мыши)
		int mouseAxis = Input::getMouseWheel();
		if (mouseAxis != 0)
		{
			distance = clamp(distance - mouseAxis, min_distance, max_distance);
			theta = clamp(theta - mouseAxis * degrees_per_unit, min_theta, max_theta);
		}

		// Обрабатываем ввод для вращения вокруг оси Z (клавиши Q/E)
		if (Input::isKeyPressed(Input::KEY_Q))
			phi -= 50.0f * Game::getIFps();
		if (Input::isKeyPressed(Input::KEY_E))
			phi += 50.0f * Game::getIFps();

		// При нажатии клавиши F и наличии выбранного объекта фокусируем камеру на выборе
		if (Input::isKeyPressed(Input::KEY_F) && selection->hasSelection())
		{
			distance = selection->getBoundRadius();
			camera_pivot_position = selection->getCenter();
			camera_pivot_position.z = 2.0f;

			distance = clamp(distance, min_distance, max_distance);
			theta = clamp(min_theta + (distance - min_distance) * degrees_per_unit, min_theta, max_theta);
		}

		// Если средняя кнопка удерживается, обновляем вектор пересечения для перемещения камеры
		if (Input::isMouseButtonPressed(Input::MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE) && is_previous_hooked)
		{
			current_mouse_to_intersection_point_vector = Vec3(camera->getDirectionFromMainWindow(Input::getMousePosition().x, Input::getMousePosition().y));
			current_mouse_to_intersection_point_vector *= previous_mouse_to_intersection_point_vector.z / current_mouse_to_intersection_point_vector.z;

			Vec3 displacement = current_mouse_to_intersection_point_vector - previous_mouse_to_intersection_point_vector;

			camera_pivot_position -= displacement;
			current_camera_pivot_position -= displacement;
			previous_mouse_to_intersection_point_vector = current_mouse_to_intersection_point_vector;
		}
		// Разрешаем прокрутку у краёв только когда средняя кнопка отпущена
		else
		{
			Vec3 forward = quat(vec3_up, phi) * Vec3_forward * -1;
			forward.normalize();
			Vec3 right = quat(vec3_up, phi) * Vec3_right * -1;
			right.normalize();
			ivec2 mousePosition = Input::getMousePosition();
			auto windowPos = WindowManager::getMainWindow()->getPosition();
			auto windowSize = WindowManager::getMainWindow()->getRenderSize();

			if (mousePosition.x < windowPos.x + 10)
				camera_pivot_position -= right * 10.0f * Game::getIFps();

			if (mousePosition.y < windowPos.y + 10)
				camera_pivot_position += forward * 10.0f * Game::getIFps();

			if (mousePosition.x > windowPos.x + windowSize.x - 10)
				camera_pivot_position += right * 10.0f * Game::getIFps();

			if (mousePosition.y > windowPos.y + windowSize.y - 10)
				camera_pivot_position -= forward * 10.0f * Game::getIFps();
		}
	}

	// Плавное движение и вращение камеры к целевым значениям
	current_phi = lerp(current_phi, phi, interpolation_factor * Game::getIFps());
	current_theta = lerp(current_theta, theta, interpolation_factor * Game::getIFps());
	current_distance = lerp(current_distance, distance, interpolation_factor * Game::getIFps());
	current_camera_pivot_position = lerp(current_camera_pivot_position, camera_pivot_position, interpolation_factor * Game::getIFps());
}

// Применяет интерполированную позицию и ориентацию камеры после всех обновлений.
void TopDownController::postUpdate()
{
	// После всех вычислений перемещаем камеру в вычисленную позицию
	vec3 cameraViewDirection = quat(vec3_up, current_phi) * vec3_forward;
	cameraViewDirection = quat(cross(vec3_up, cameraViewDirection), -current_theta) * cameraViewDirection * -1;
	cameraViewDirection.normalize();

	camera->setViewDirection(cameraViewDirection);
	camera->setPosition(current_camera_pivot_position - Vec3(cameraViewDirection) * current_distance);
}

// Восстанавливает режим обработки мыши и отключает визуализатор.
void TopDownController::shutdown()
{
	// Позволяем мыши снова быть захваченной
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);
	Visualizer::setEnabled(false);
}
