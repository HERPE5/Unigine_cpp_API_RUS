// Демонстрирует использование RenderTarget для компоновки спрайтов на текстуре.
// Периодически рисует случайные спрайты на фоновой текстуре, которая
// затем применяется к объекту стены в сцене.

#pragma once

#include <UnigineComponentSystem.h>

// Компонует спрайты на текстуре стены через операции render target.
class RenderTargetSample final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(RenderTargetSample, Unigine::ComponentBase)

	// Материал с шейдером для отрисовки спрайтов
	PROP_PARAM(Material, draw_sprite_material)
	// Массив файлов изображений спрайтов
	PROP_ARRAY(File, sprites)
	// Объект стены для отображения скомпонованной текстуры
	PROP_PARAM(Node, wall_param, "Wall Node")

	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_SHUTDOWN(shutdown)

private:
	void init();
	void update();
	void shutdown();

	// Копирует исходную текстуру в целевую с использованием render target
	void copy_texture(const Unigine::TexturePtr &dest, const Unigine::TexturePtr &src) const;
	// Рисует спрайт в указанных UV-координатах
	void draw_sprite(float uv_x, float uv_y);

private:
	Unigine::RenderTargetPtr render_target;
	// Загруженные текстуры спрайтов для случайного выбора
	Unigine::Vector<Unigine::TexturePtr> sprite_textures;
	// Базовая текстура, на которой компонуются спрайты
	Unigine::TexturePtr background_texture;
	// Финальная скомпонованная текстура, применённая к стене
	Unigine::TexturePtr result_texture;

	Unigine::ObjectPtr wall;
	Unigine::MaterialPtr wall_material;
	// Исходный albedo стены для сброса фона
	Unigine::ImagePtr wall_albedo;

	// Таймер для периодического появления спрайтов
	float countdown{0.f};
};
