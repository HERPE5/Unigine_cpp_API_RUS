// Контроллер камеры вида сверху в стиле RTS с использованием сферических координат (phi/theta).
// Поддерживает масштабирование, вращение, прокрутку у краёв экрана, панорамирование средней кнопкой мыши и фокус на выборе.
// Угол theta связан с дистанцией для более выраженного вида сверху при отдалении.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

class Selection;

// Камера вида сверху для геймплея RTS/тактики. Вращается вокруг опорной точки с использованием
// сферических координат с плавной интерполяцией к целевым значениям.
class TopDownController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TopDownController, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_POST_UPDATE(postUpdate);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_PARAM(Float, phiProp, 180.0f, "Phi", "The angle by which the camera will be rotated around the Z axis at the beginning", "Angles");
	PROP_PARAM(Float, thetaProp, 40.0f, "Theta", "The angle by which the camera will be rotated around the Y axis at the beginning", "Angles", "min=0.0f;max=89.9f");

	PROP_PARAM(Vec2, thetaMinMax, Unigine::Math::vec2(10.0f, 70.0f), nullptr, "Lower and upper angle limits", "Angles");

	PROP_PARAM(Float, Distance, 25.0f, nullptr, "Distance at which the camera will be at the beginning", "Distance", "min=0.1f;max=300.0f");
	PROP_PARAM(Vec2, distanceMinMax, Unigine::Math::vec2(5.0f, 45.0f), nullptr, "Lower and upper distance limits", "Distance");

	PROP_PARAM(Float, zoomSpeed, 5.0f, nullptr, "The speed at which transformations will occur", "Speed", "min=0.5f;max=10.0f");

	void setPosition(const Unigine::Math::Vec3& pos);		// Мгновенно перемещает опорную точку камеры в позицию
	void setTargetPosition(const Unigine::Math::Vec3& pos);	// Задаёт целевую позицию для плавного движения

	void setDistance(float dist);		// Мгновенно задаёт дистанцию камеры от опорной точки
	void setTargetDistance(float dist);	// Задаёт целевую дистанцию для плавного масштабирования

protected:
	void init();
	void update();
	void postUpdate();
	void shutdown();

private:
	Unigine::PlayerPtr camera;		// Управляемый узел камеры

	// Состояние панорамирования средней кнопкой мыши: трассировка луча к плоскости земли для движения перетаскиванием
	Unigine::WorldIntersectionPtr intersection = Unigine::WorldIntersection::create();
	Unigine::Math::Vec3 previous_mouse_to_intersection_point_vector;	// Вектор от камеры к земле в начале перетаскивания
	Unigine::Math::Vec3 current_mouse_to_intersection_point_vector;		// Вектор от камеры к земле в текущей позиции мыши
	bool is_previous_hooked = false;	// True, если начальная трассировка луча попала в землю

	// Угол горизонтального вращения (рыскание) - текущий и целевой для интерполяции
	float current_phi = 180.0f;
	float phi = 180.0f;

	// Угол вертикального вращения (тангаж) - связан с дистанцией для эффекта вида сверху
	float current_theta = 40.0f;
	float theta = 40.0f;
	float max_theta = 70.0f;
	float min_theta = 10.0f;

	// Дистанция от опорной точки - текущая и целевая для интерполяции
	float current_distance = 25.0f;
	float distance = 25.0f;
	float max_distance = 45.0f;
	float min_distance = 5.0f;

	float interpolation_factor = 1.0f;	// Скорость плавной интерполяции

	// Позиция опорной точки - камера вращается вокруг этой точки
	Unigine::Math::Vec3 current_camera_pivot_position;
	Unigine::Math::Vec3 camera_pivot_position;

	float degrees_per_unit = 1.0f;		// Изменение theta на единицу изменения дистанции

	Selection *selection = nullptr;		// Обработчик выбора для функции фокуса на выборе
};