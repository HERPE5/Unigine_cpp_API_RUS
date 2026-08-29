// Симулирует расширяющийся сферический взрыв, прикладывающий направленные наружу силы к
// близлежащим твёрдым телам и запускающий разрушение разрушаемых объектов.
// Сила уменьшается по мере роста радиуса (обратное затухание от центра).

#pragma once

#include <UnigineComponentSystem.h>

class BodyFractureExplosion
	: public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(BodyFractureExplosion, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	// Обновление физики для согласованного приложения силы независимо от частоты кадров
	COMPONENT_UPDATE_PHYSICS(updatePhysics);
	COMPONENT_SHUTDOWN(shutdown);

	// Включает отладочную отрисовку сферы взрыва визуализатором
	PROP_PARAM(Toggle, debug, true);
	// Максимальный радиус расширения перед сбросом взрыва
	PROP_PARAM(Float, max_radius, 10.0f);
	// Скорость расширения в единицах в секунду
	PROP_PARAM(Float, speed, 100.0f);
	// Базовая величина силы, приложенной в центре взрыва
	PROP_PARAM(Float, power, 100.0f);

	// Запускает взрыв из текущей позиции
	void explode();

private:
	void init();
	void updatePhysics();
	void shutdown();

private:
	// Текущий радиус взрыва (расширяется от 0 до max_radius)
	float radius;
	// Флаг активного состояния взрыва
	bool isExploding;
	// Исходное состояние визуализатора для восстановления
	bool visualizer_enabled;
};
