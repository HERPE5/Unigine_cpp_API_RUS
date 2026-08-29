// Рендерит виджеты GUI в текстуру для внутримировых поверхностей отображения.
// Выполняет цикл обновления GUI вручную и захватывает вывод в текстуру,
// которую можно назначить в любой слот текстуры материала (albedo, emission и т.д.).

#pragma once

#include <UnigineComponentSystem.h>

// Захватывает рендеринг GUI в текстуру и назначает её в слоты текстур материала.
class GuiToTexture final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(GuiToTexture, Unigine::ComponentBase);

	// Поверхность, получающая текстуру GUI
	PROP_PARAM(String, surface_name);
	// Слоты текстур материала для назначения отрисованной текстуры GUI
	PROP_ARRAY(String, texture_slot_names);
	// Размеры выходной текстуры
	PROP_PARAM(IVec2, texture_resolution, Unigine::Math::ivec2(2048, 2048));

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

public:
	UNIGINE_INLINE Unigine::GuiPtr getGui() const { return gui; }
	UNIGINE_INLINE void setAutoUpdateEnabled(bool e) { auto_update_enabled = e; }
	void renderToTexture() const;
	UNIGINE_INLINE Unigine::Math::ivec2 getTextureResolution() const { return texture_resolution; }

private:
	void init();
	void update() const;

private:
	// Выходная текстура, содержащая отрисованный GUI
	Unigine::TexturePtr gui_texture;
	// Автономный экземпляр GUI (отдельный от основного экранного GUI)
	Unigine::GuiPtr gui;
	Unigine::WidgetCanvasPtr canvas;

	// Render target для захвата вывода GUI
	Unigine::RenderTargetPtr render_target;

	// Если включено, GUI перерисовывается в текстуру каждый кадр
	bool auto_update_enabled{true};
};
