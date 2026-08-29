#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Демонстрирует композицию и декомпозицию вращения по углам Эйлера.
// Показывает все 6 последовательностей вращения (XYZ, XZY, YXZ, YZX, ZXY, ZYX) и то,
// как одно и то же вращение может быть представлено по-разному в зависимости от последовательности.
// Визуализирует оси вращения и кольца карданова подвеса в 3D-пространстве.
class EulerAnglesSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(EulerAnglesSample, Unigine::ComponentBase)
	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

	PROP_PARAM(Node, plane) // целевой узел для вращения

private:
	// Поддерживаемые последовательности вращения Эйлера
	enum ROTATION_SEQUENCE
	{
		XYZ,
		XZY,
		YXZ,
		YZX,
		ZXY,
		ZYX,
	};

	void init();
	void update();
	void shutdown();

	void init_gui(); // создаёт слайдеры и комбобоксы для управления углами/последовательностью

	void update_rotation();           // применяет углы Эйлера к узлу с использованием последовательности композиции
	void update_decomposition_angles(); // извлекает углы Эйлера из текущего вращения

	Unigine::Math::vec3 euler_angles = Unigine::Math::vec3_zero;        // входные углы (тангаж, крен, рыскание)
	Unigine::Math::vec3 decomposition_angles = Unigine::Math::vec3_zero; // углы, извлечённые из вращения
	ROTATION_SEQUENCE composition_sequence = XYZ;   // последовательность для построения вращения
	ROTATION_SEQUENCE decomposition_sequence = XYZ; // последовательность для извлечения углов
	SampleDescriptionWindow sample_description_window;
	Unigine::String status;
	bool visualizer_enabled = false; // исходное состояние визуализатора для восстановления при завершении
};
