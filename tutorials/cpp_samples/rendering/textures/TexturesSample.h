// Демонстрирует динамическое манипулирование текстурами с помощью API Image.
// Создаёт анимированные цветовые паттерны, напрямую изменяя данные пикселей
// и загружая результат в GPU-текстуры каждый кадр.

#pragma once

#include <UnigineComponentSystem.h>

class TexturesSample final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(TexturesSample, ComponentBase)

	// Объекты мешей, отображающие анимированные текстуры
	PROP_ARRAY(Node, meshes_param, "Meshes")

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)

private:
	void init();
	void update();

private:
	// Закэшированные объекты мешей для назначения текстур
	Unigine::VectorStack<Unigine::ObjectPtr, 4> meshes;
	// Базовые цвета для анимации каждой текстуры
	Unigine::VectorStack<Unigine::Math::ivec4, 4> colors;
	// Изображения на стороне CPU для манипуляции пикселями
	Unigine::VectorStack<Unigine::ImagePtr, 4> images;
};
