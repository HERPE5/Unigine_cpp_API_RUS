#pragma once

#include "Persecutor.h"

#include <UnigineComponentSystem.h>

// Базовый класс для стратегий интерполяции движения.
// Каждый производный класс реализует свой подход к сглаживанию/физике:
// - LinearMotion: движение с постоянной скоростью
// - EaseInMotion: постепенное ускорение
// - EaseOutMotion: постепенное замедление
// - EaseOutBounceMotion: эффект отскока у цели
// - семейство SpringMotion: симуляция физики пружины
class MotionMode : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(MotionMode, Unigine::ComponentBase);
	COMPONENT_INIT(init);

	PROP_PARAM(Node, targetNode)		// лазерная указка, за которой идёт погоня
	PROP_PARAM(Node, persecutorNode)	// кот, который преследует

protected:
	PersecutorBase *persecutor = nullptr;

protected:
	void init();
};