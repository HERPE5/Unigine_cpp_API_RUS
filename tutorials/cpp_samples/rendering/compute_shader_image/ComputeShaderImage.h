// Демонстрирует использование вычислительного шейдера для динамической генерации текстуры.
// Запускает вычислительный шейдер, записывающий напрямую в текстуру с использованием
// unordered-доступа, которая затем отображается на целевом материале.

#pragma once

#include <UnigineComponentSystem.h>

// Генерирует процедурную текстуру через вычислительный шейдер и отображает её на материале.
class ComputeShaderImage : public Unigine::ComponentBase {
	COMPONENT_DEFINE(ComputeShaderImage, ComponentBase)

	// Материал, содержащий вычислительный шейдер
	PROP_PARAM(Material, compute_material)
	// Материал, отображающий сгенерированную текстуру
	PROP_PARAM(Material, target_material)

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

private:
	void init();
	void update();
	void shutdown();

private:
	// Текстура, в которую пишет вычислительный шейдер
	Unigine::TexturePtr dynamic_texture;
	// Render target для диспетчеризации вычислений
	Unigine::RenderTargetPtr render_target;
};
