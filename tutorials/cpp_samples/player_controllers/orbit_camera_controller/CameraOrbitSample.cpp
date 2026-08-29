// Реализует орбитальную камеру, вращающуюся вокруг целевого узла.
// Камера остаётся на настраиваемом расстоянии с ограничениями вертикального угла
// для предотвращения складывания карданного подвеса. Направление вычисляется из сферических
// координат (горизонтальный и вертикальный углы).

#include "../../utils/CameraControls.h"
#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

using namespace Unigine;
using namespace Unigine::Math;

// Орбитальная камера от третьего лица с масштабированием дистанции и ограничениями углов.
class CameraOrbitSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(CameraOrbitSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Node, controls_node);					// Узел с компонентом CameraControls
	PROP_PARAM(Float, angularSpeed, 90.0f)				// Скорость вращения в градусах в секунду
	PROP_PARAM(Float, zoomSpeed, 3.0f);					// Скорость масштабирования в единицах в секунду
	PROP_PARAM(Float, minDistance, 5.0f);				// Минимальное допустимое расстояние до цели
	PROP_PARAM(Float, maxDistance, 10.0f);				// Максимальное допустимое расстояние от цели
	PROP_PARAM(Float, minVerticalAngle, -89.9f);		// Нижний предел тангажа (около -90, чтобы избежать складывания подвеса)
	PROP_PARAM(Float, maxVerticalAngle, 89.9f);			// Верхний предел тангажа (около 90, чтобы избежать складывания подвеса)
	PROP_PARAM(Node, target);							// Узел, вокруг которого вращается камера

private:
	CameraControls *controls = nullptr;
	PlayerDummyPtr camera = nullptr;
	float horizontalAngle = 0.0f;	// Угол рыскания вокруг цели (сферический phi)
	float verticalAngle = 0.0f;		// Угол тангажа (сферический theta)
	float distance = 0.0f;			// Текущее расстояние от цели
	Input::MOUSE_HANDLE init_mouse_handle;	// Сохранённый режим мыши для восстановления при завершении работы

private:
	// Начальные углы извлекаются из текущего направления камера-цель.
	void init()
	{
		camera = static_ptr_cast<PlayerDummy>(node);
		if (!camera)
		{
			return;
		}

		if (!target)
		{
			return;
		}

		controls = getComponent<CameraControls>(controls_node);
		if (!controls)
		{
			return;
		}

		init_mouse_handle = Input::getMouseHandle();
		Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);

		// Направление от камеры к цели используется для вычисления начальных сферических углов
		vec3 direction(target->getWorldPosition() - camera->getWorldPosition());
		direction.normalize();

		// Горизонтальное направление (проекция XY) необходимо для разложения угла
		vec3 horizontalDirection = direction;
		horizontalDirection.z = 0;
		horizontalDirection.normalize();

		// Вертикальный угол: возвышение от горизонтальной плоскости
		verticalAngle = getAngle(direction, horizontalDirection);
		verticalAngle *= -sign(direction.z);
		verticalAngle = clamp(verticalAngle, minVerticalAngle, maxVerticalAngle);

		// Горизонтальный угол: вращение от оси вперёд
		horizontalAngle = getAngle(horizontalDirection, vec3_forward);
		horizontalAngle *= sign(direction.x);

		// Камера начинает со среднего расстояния, смотря на цель
		distance = minDistance + (maxDistance - minDistance) * 0.5f;
		camera->setWorldDirection(direction, vec3_up);
		camera->setWorldPosition(target->getWorldPosition() - Vec3(direction * distance));
	}

	// Сферические углы и расстояние обновляются из ввода, затем камера перепозиционируется.
	void update()
	{
		if (!camera || !target || !controls)
			return;

		// Тангаж ограничивается, чтобы предотвратить переворот через полюса
		verticalAngle -= controls->getTurnUp() * angularSpeed * Game::getIFps();
		verticalAngle += controls->getTurnDown() * angularSpeed * Game::getIFps();
		verticalAngle = clamp(verticalAngle, minVerticalAngle, maxVerticalAngle);

		horizontalAngle += controls->getTurnRight() * angularSpeed * Game::getIFps();
		horizontalAngle -= controls->getTurnLeft() * angularSpeed * Game::getIFps();

		// Рыскание закольцовывается на ±180 градусах
		if (horizontalAngle < -180 || 180 < horizontalAngle)
			horizontalAngle = clamp(-horizontalAngle, -180.0f, 180.0f);

		// Направление восстанавливается из сферических координат (сначала рыскание, затем тангаж)
		vec3 cameraDirection = vec3_forward * rotateZ(horizontalAngle);
		cameraDirection = cameraDirection * rotate(cross(cameraDirection, vec3_up), verticalAngle);

		distance -= controls->getZoomIn() * zoomSpeed * Game::getIFps();
		distance += controls->getZoomOut() * zoomSpeed * Game::getIFps();
		distance = clamp(distance, minDistance, maxDistance);

		// Камера размещается вдоль вектора направления на заданном расстоянии от цели
		camera->setWorldDirection(cameraDirection, vec3_up);
		camera->setWorldPosition(target->getWorldPosition() - Vec3(cameraDirection * distance));
	}

	// Восстанавливает исходный режим обработки мыши при уничтожении компонента.
	void shutdown()
	{
		Input::setMouseHandle(init_mouse_handle);
	}
};

REGISTER_COMPONENT(CameraOrbitSample);
