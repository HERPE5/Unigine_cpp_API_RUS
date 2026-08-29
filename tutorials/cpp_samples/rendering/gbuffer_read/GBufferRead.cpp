// Извлекает компоненты G-buffer (albedo, нормаль, металличность, шероховатость, глубина)
// в отдельные текстуры после отложенного прохода. Подключается к концу рендеринга
// G-buffer для копирования данных перед вычислениями освещения.

#include "GBufferRead.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(GBufferRead)

using namespace Unigine;
using namespace Math;

constexpr int TEXTURE_WIDTH = 1024;
constexpr int TEXTURE_HEIGHT = 1024;

// Создаются вьюпорт и выходные текстуры; регистрируются callback-функции событий для обоих режимов.
void GBufferRead::init()
{
	viewport = Viewport::create();

	// Поскольку финальное изображение нас не интересует, мы можем остановить
	// рендеринг, когда текстуры G-buffer готовы
	viewport->setRenderMode(Viewport::RENDER_DEPTH_GBUFFER);
	viewport->getEventEndOpacityGBuffer().connect(on_viewport_g_buffer_ready_connection, this,
		&GBufferRead::g_buffers_ready_callback);

	Render::getEventEndOpacityGBuffer().connect(on_render_g_buffer_ready_connection, this,
		&GBufferRead::g_buffers_ready_callback);

	// Создаём все текстуры
	// Используем Texture::FORMAT_USAGE_RENDER, чтобы текстуру можно было использовать в операциях рендеринга
	albedo_texture = Texture::create();
	albedo_texture->create2D(TEXTURE_WIDTH, TEXTURE_HEIGHT, Texture::FORMAT_RGBA8,
		Texture::FORMAT_USAGE_RENDER);

	normal_texture = Texture::create();
	normal_texture->create2D(TEXTURE_WIDTH, TEXTURE_HEIGHT, Texture::FORMAT_RGBA8,
		Texture::FORMAT_USAGE_RENDER);

	metalness_texture = Texture::create();
	metalness_texture->create2D(TEXTURE_WIDTH, TEXTURE_HEIGHT, Texture::FORMAT_RGBA8,
		Texture::FORMAT_USAGE_RENDER);

	roughness_texture = Texture::create();
	roughness_texture->create2D(TEXTURE_WIDTH, TEXTURE_HEIGHT, Texture::FORMAT_RGBA8,
		Texture::FORMAT_USAGE_RENDER);

	depth_texture = Texture::create();
	depth_texture->create2D(TEXTURE_WIDTH, TEXTURE_HEIGHT, Texture::FORMAT_RGBA8,
		Texture::FORMAT_USAGE_RENDER);

	setMode(mode);
}

// Извлекает компоненты G-buffer в отдельные текстуры с помощью полноэкранного прохода шейдера.
void GBufferRead::g_buffers_ready_callback()
{
	RenderTargetPtr render_target = Renderer::getPostRenderTarget();

	// Сохраняем текущее состояние и помещаем его на вершину стека сохранённых состояний RenderState
	RenderState::saveState();
	// Очищаем текущее состояние рендеринга, чтобы наш рендер не зависел от текущих настроек рендеринга
	RenderState::clearStates();

	// Задаём текстуры, в которые будем рендерить
	render_target->bindColorTexture(0, depth_texture);
	render_target->bindColorTexture(1, albedo_texture);
	render_target->bindColorTexture(2, normal_texture);
	render_target->bindColorTexture(3, metalness_texture);
	render_target->bindColorTexture(4, roughness_texture);

	// Включаем render target
	render_target->enable();
	{
		// Привязываем уже отрендеренные текстуры GBuffer к шейдеру
		// Используем RenderState::BIND_FRAGMENT для привязки текстур только для фрагментного шейдера
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 0, Renderer::getTextureOpacityDepth());
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 1, Renderer::getTextureGBufferAlbedo());
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 2, Renderer::getTextureGBufferNormal());
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 3,
			Renderer::getTextureGBufferShading());

		// Этот материал содержит шейдер, который отрендерит текстуры, привязанные к RenderTarget.
		// Чтобы посмотреть код этого шейдера, перейдите в папку примера, затем в папку materials
		// и откройте fetch_buffers_post.basemat
		fetch_buffers_post_material->renderScreen(Render::PASS_POST);
	}
	render_target->disable();
	render_target->unbindColorTextures();

	// Получаем RenderState с вершины внутреннего стека RenderState
	RenderState::restoreState();

	depth_texture->createMipmaps();
	normal_texture->createMipmaps();
	roughness_texture->createMipmaps();
	metalness_texture->createMipmaps();
	albedo_texture->createMipmaps();
}

// Рендерит одиночный узел с использованием пользовательских матриц камеры и запускает извлечение G-buffer.
void GBufferRead::renderNode(const Mat4 &model_view, const Mat4 &projection,
	const NodePtr &to_render) const
{
	// Создаётся временная камера с предоставленными матрицами для рендеринга узла
	CameraPtr camera = Camera::create();
	camera->setProjection(mat4(projection));
	camera->setModelview(model_view);

	RenderState::saveState();
	RenderState::clearStates();
	RenderState::setViewport(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);
	{
		// Здесь g_buffers_ready_callback будет вызван после того, как все текстуры G-buffer готовы.
		// См. функцию init() для подписки на событие.
		viewport->renderNode(camera, to_render);
	}
	RenderState::restoreState();
}

// Переключает между режимами RenderNode (пользовательский вьюпорт) и RenderMainViewport (камера сцены).
void GBufferRead::setMode(GBufferRead::Mode in_mode)
{
	mode = in_mode;
	switch (mode)
	{
	case Mode::RenderNode:
		on_render_g_buffer_ready_connection.setEnabled(false);
		on_viewport_g_buffer_ready_connection.setEnabled(true);
		break;
	case Mode::RenderMainViewport:
		on_render_g_buffer_ready_connection.setEnabled(true);
		on_viewport_g_buffer_ready_connection.setEnabled(false);
		break;
	}
}
