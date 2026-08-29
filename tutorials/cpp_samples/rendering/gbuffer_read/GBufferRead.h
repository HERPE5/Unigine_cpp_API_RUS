// Извлекает компоненты G-buffer (albedo, нормаль, металличность, шероховатость, глубина)
// в отдельные текстуры после отложенного прохода. Подключается к концу рендеринга
// G-buffer для копирования данных перед вычислениями освещения.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineViewport.h>

// Извлекает данные G-buffer (albedo, нормали, глубину, металличность, шероховатость) в
// отдельные текстуры. Поддерживает извлечение из главного вьюпорта или рендеринга пользовательского узла.
class GBufferRead final : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(GBufferRead, ComponentBase)

	// Материал с полноэкранным шейдером для извлечения данных G-buffer
	PROP_PARAM(Material, fetch_buffers_post_material)

	COMPONENT_INIT(init)

	// Источник извлечения: одиночный узел или весь главный вьюпорт
	enum class Mode
	{
		RenderNode,
		RenderMainViewport
	};

	// Рендерит одиночный узел и извлекает его данные G-buffer
	void renderNode(const Unigine::Math::Mat4 &model_view, const Unigine::Math::Mat4 &projection,
		const Unigine::NodePtr &to_render) const;

	void setMode(Mode in_mode);
	UNIGINE_INLINE Mode getMode() const { return mode; }

	// Геттеры для извлечённых данных текстур
	UNIGINE_INLINE Unigine::TexturePtr getDepthTexture() const { return depth_texture; }
	UNIGINE_INLINE Unigine::TexturePtr getAlbedoTexture() const { return albedo_texture; }
	UNIGINE_INLINE Unigine::TexturePtr getNormalTexture() const { return normal_texture; }
	UNIGINE_INLINE Unigine::TexturePtr getRoughnessTexture() const { return roughness_texture; }
	UNIGINE_INLINE Unigine::TexturePtr getMetalnessTexture() const { return metalness_texture; }

private:
	void init();

	// Вызывается, когда G-buffer завершён, выполняет извлечение текстур
	void g_buffers_ready_callback();

private:
	Mode mode{Mode::RenderNode};

	// Извлечённые текстуры компонентов G-buffer
	Unigine::TexturePtr depth_texture;
	Unigine::TexturePtr albedo_texture;
	Unigine::TexturePtr normal_texture;
	Unigine::TexturePtr metalness_texture;
	Unigine::TexturePtr roughness_texture;

	// Соединения событий для обоих режимов рендеринга
	Unigine::EventConnection on_viewport_g_buffer_ready_connection;
	Unigine::EventConnection on_render_g_buffer_ready_connection;
	// Выделенный вьюпорт для режима RenderNode
	Unigine::ViewportPtr viewport;
};
