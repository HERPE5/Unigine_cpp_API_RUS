#pragma once

#include <UnigineComponentSystem.h>

class ImagesSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(ImagesSample, ComponentBase)
	COMPONENT_DESCRIPTION("This component demonstrates creating and updating a 3D image in real time by "
							"writing raw pixel data and applying it as a texture to a volume object.")

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)

private:
	void init();
	void update();

	// Инициализирует и обновляет поля, генерирующие плотность вокселей
	void image_init();
	void image_update();


private:
	// Параметры симуляции
	float size{2.f};
	float velocity{1.f};
	float radius{0.5f};
	int num_fields{16};

	// Состояние движущихся полей
	Unigine::Vector<Unigine::Math::vec3> positions;
	Unigine::Vector<Unigine::Math::vec3> velocities;
	Unigine::Vector<float> radiuses;

	// Текстура и материал, используемые для визуализации
	Unigine::ImagePtr image;
	Unigine::MaterialPtr material;
};
