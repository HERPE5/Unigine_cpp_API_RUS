// Индикатор цели за пределами экрана с использованием спрайтов стрелки и маркера.
// Когда цель видна на экране, точечный маркер выделяет её позицию.
// Когда цель вне экрана или за камерой, стрелка указывает направление.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

// Отображает направленный индикатор, указывающий на узел цели с точки зрения камеры.
class TargetMarker : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TargetMarker, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Изображение спрайта, отображаемое как направленная стрелка, когда цель вне экрана
	PROP_PARAM(File, arrowSprite);
	// Изображение спрайта, отображаемое как маркер, когда цель видна на экране
	PROP_PARAM(File, pointSprite);

	// Узел для отслеживания и указания направления на него
	PROP_PARAM(Node, targetNode);

	// Нормализованное смещение точки опоры для позиционирования точечного маркера (0.5, 0.5 = центр)
	PROP_PARAM(Vec2, pointPivot, Unigine::Math::vec2(0.5, 0.5));

protected:
	void init();
	void update();
	void shutdown();

private:
	// Вычисляет точку пересечения луча направления с прямоугольником границ экрана
	void getIntersectionWithRect(int& x, int& y, int vec_x, int vec_y, int half_width, int half_height);

	// Спрайт стрелки, показываемый, когда цель вне экрана
	Unigine::WidgetSpritePtr arrow;
	// Спрайт точечного маркера, показываемый, когда цель видна
	Unigine::WidgetSpritePtr point;

	// Закэшированная ссылка на отслеживаемый узел цели
	Unigine::NodePtr target;

	// Камера игрока, используемая для расчётов проекции на экран
	Unigine::PlayerPtr camera;

	// Закэшированные размеры спрайта точечного маркера
	int point_width;
	int point_height;
	// Закэшированные размеры спрайта стрелки
	int arrow_width;
	int arrow_half_width;
	int arrow_height;
	int arrow_half_height;

};