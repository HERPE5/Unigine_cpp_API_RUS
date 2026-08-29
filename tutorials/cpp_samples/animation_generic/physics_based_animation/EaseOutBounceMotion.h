#pragma once

#include "SpringRegular.h"

#include <UnigineComponentSystem.h>

// Расширяет пружинное движение эффектом отскока при приближении к цели.
// Когда преследователь входит в радиус отскока и движется к цели,
// скорость реверсируется для создания эффекта "отскока от стены".
// Полезно для игривой или преувеличенной эстетики движения.
class EaseOutBounceMotion : public SpringRegular

{
public:
	COMPONENT_DEFINE(EaseOutBounceMotion, SpringRegular);

	PROP_PARAM(Float, bounceRadius, 3.f);

private:
	// промежуточные динамические переменные позиции
	Unigine::Math::Vec3 new_position;
	// нормаль отскока
	Unigine::Math::Vec3 wall_normal;

private:
	Unigine::Math::Vec3 update_physics(const Unigine::Math::Vec3 &src, // исходная точка
		const Unigine::Math::Vec3 &dst,                                // целевая точка
		bool &out_finished,                                            // движение остановлено
		Unigine::Math::Vec3 &out_dir) override; // направление от исходной точки к целевой

	void on_enable() override;
};