// Демонстрирует использование структурированного буфера GPU для сжатия текстур DXT.
// Использует compute-шейдер для сжатия исходной текстуры в формат DXT
// через структурированный буфер, показывая обработку данных на стороне GPU.

#pragma once

#include <UnigineComponentSystem.h>

// Сжимает текстуру в формат DXT1 с помощью compute-шейдера GPU и структурированного буфера.
class StructuredBufferSample : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(StructuredBufferSample, ComponentBase)

	COMPONENT_INIT(init)

	// Материал с compute-шейдером для сжатия DXT
	PROP_PARAM(Material, dxt_compute_material)
	// Исходная текстура для сжатия
	PROP_PARAM(File, source_texture_param, "Source Texture")

private:
	void init();
};
