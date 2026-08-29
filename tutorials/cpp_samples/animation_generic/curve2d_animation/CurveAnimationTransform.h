#pragma once

#include "UnigineComponentSystem.h"

// Анимирует трансформацию узла с помощью Curve2D для каждой оси позиции, вращения и масштаба.
// Curve2D - это облегчённая альтернатива системе Animation, полезная для простых
// процедурных анимаций, где не требуется полная инфраструктура треков/воспроизведения.
// Каждая кривая вычисляется в текущий момент времени для построения итоговой матрицы трансформации.
class CurveAnimationTransform :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CurveAnimationTransform, ComponentBase);
	COMPONENT_UPDATE(update);

	// Тройка кривых для компонентов X, Y, Z
	struct Curves : Unigine::ComponentStruct
	{
		PROP_PARAM(Curve2d, x);
		PROP_PARAM(Curve2d, y);
		PROP_PARAM(Curve2d, z);
	};

	// Компоненты трансформации - у каждой оси своя кривая для полного контроля
	PROP_STRUCT(Curves, position);
	PROP_STRUCT(Curves, rotation);	// углы Эйлера в градусах
	PROP_STRUCT(Curves, scale_prop);

	PROP_PARAM(Float, speed, 1.0f);	// множитель скорости воспроизведения

private:
	void update();
	float time = 0;
};

// Анимирует float-параметры материала с помощью Curve2D.
// Каждая запись в массиве parameters сопоставляет кривую с параметром материала по имени.
// Полезно для анимации свечения, прозрачности или других параметров шейдера во времени.
class CurveAnimationMaterialParamFloat :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CurveAnimationMaterialParamFloat, ComponentBase);
	COMPONENT_UPDATE(update);

	// Определение одного анимируемого параметра
	struct Curves : Unigine::ComponentStruct
	{
		PROP_PARAM(Curve2d, curve);		// кривая анимации
		PROP_PARAM(String, name);		// имя параметра материала
		PROP_PARAM(Int, surface, 0);	// индекс поверхности, к которой применяется
	};

	PROP_ARRAY_STRUCT(Curves, parameters);	// список анимируемых параметров
	PROP_PARAM(Float, speed, 1.0f);

private:
	void update();
	float time = 0;
};
