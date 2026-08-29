// Изменяет содержимое G-buffer после отложенного прохода с использованием MRT (Multiple Render
// Targets). Рендерит во временные текстуры, применяет эффекты цвета/пластика через
// пользовательский шейдер, затем возвращает обратно в G-buffer для освещения.

#include "GBufferWrite.h"

#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(GBufferWrite)

// Текстуры G-buffer изменяются на месте с использованием временных текстур и пользовательского шейдера.
void GBufferWrite::g_buffers_ready_callback()
{
	// Получаем шейдер из материала, чтобы задать параметры и привязать его в нужный нам момент времени.
	// Используем getShaderForce, чтобы получить его мгновенно, и если шейдер не скомпилирован, движок скомпилирует
	// его, и мы сможем использовать его сразу же.
	ShaderPtr shader = modify_buffer_material->getShaderForce(Render::PASS_POST);
	if (!shader)
	{
		return;
	}

	RenderTargetPtr render_target = Renderer::getPostRenderTarget();

	// Поскольку этот callback вызывается после того, как текстуры G-buffer готовы,
	// мы можем свободно их получить
	TexturePtr albedo = Renderer::getTextureGBufferAlbedo();
	TexturePtr normal = Renderer::getTextureGBufferNormal();
	TexturePtr shading = Renderer::getTextureGBufferShading();

	// Движок выделит новую текстуру или просто использует одну из своего внутреннего пула,
	// поэтому лучше использовать этот метод, чем создавать новые текстуры,
	// но нам нужно освобождать эти текстуры явно самим
	TexturePtr albedo_temp = Render::getTemporaryTexture(albedo);
	TexturePtr normal_temp = Render::getTemporaryTexture(normal);
	TexturePtr shading_temp = Render::getTemporaryTexture(shading);


	RenderState::saveState();
	RenderState::clearStates();

	// Задаём текстуры с флагом BIND_FRAGMENT, чтобы эти текстуры были доступны только из фрагментного
	// шейдера. Эти текстуры соответствуют этому коду шейдера в нашем материале STRUCT_FRAG_BEGIN
	// 	INIT_MRT(float4, OUT_ALBEDO)
	// 	INIT_MRT(float4, OUT_NORMAL)
	// 	INIT_MRT(float4, OUT_SHADING)
	// STRUCT_FRAG_END
	// MRT означает Multiple Render Target, и мы используем его для рендеринга нескольких текстур за один
	// вызов отрисовки
	render_target->bindColorTexture(0, albedo_temp);
	render_target->bindColorTexture(1, normal_temp);
	render_target->bindColorTexture(2, shading_temp);
	render_target->enable();
	{
		// Привязываем шейдер и задаём его параметры (посмотрите в modify_buffers_post.basemat,
		// чтобы узнать, как использовать эти параметры в шейдере)
		shader->bind();
		// Эти параметры соответствуют этим строкам в шейдере
		// CBUFFER(parameters)
		//	UNIFORM float ss_influence;
		//	UNIFORM float ss_plastic;
		//	UNIFORM float4 ss_color;
		// END
		shader->setParameterFloat("ss_influence", influence);
		shader->setParameterFloat("ss_plastic", plastic);
		shader->setParameterFloat4("ss_color", color);
		shader->flushParameters();

		// Здесь мы привязываем текстуры к шейдеру, чтобы можно было из них читать.
		// Эти строки соответствуют строкам шейдера
		// INIT_TEXTURE(0, TEX_ALBEDO)
		// INIT_TEXTURE(1, TEX_NORMAL)
		// INIT_TEXTURE(2, TEX_SHADING)
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 0, albedo);
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 1, normal);
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 2, shading);

		// Теперь мы можем начать наш рендер
		modify_buffer_material->renderScreen(Render::PASS_POST);
	}
	render_target->disable();
	render_target->unbindColorTextures();
	RenderState::restoreState();

	// Здесь мы устанавливаем новые текстуры G-buffer
	albedo_temp->swap(albedo);
	normal_temp->swap(normal);
	shading_temp->swap(shading);

	// Освобождаем временные текстуры
	Render::releaseTemporaryTexture(albedo_temp);
	Render::releaseTemporaryTexture(normal_temp);
	Render::releaseTemporaryTexture(shading_temp);
}

// Регистрируется callback изменения G-buffer; создаются метки UI для отображения параметров.
void GBufferWrite::init()
{
	Render::getEventEndOpacityGBuffer().connect(this, &GBufferWrite::g_buffers_ready_callback);

	sample_description_window.createWindow();

	color_label = sample_description_window.addLabel("Color: ");
	plastic_label = sample_description_window.addLabel("Plastic: ");
	influence_label = sample_description_window.addLabel("Influence: ");
}

// Параметры эффекта (color, plastic, influence) анимируются со временем для визуальной демонстрации.
void GBufferWrite::update()
{
	const VectorStack<vec4> colors = {vec4(1.0f, 1.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f),
		vec4(0.0f, 1.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f)};

	const float time = Game::getTime();
	const float ifps = Game::getIFps();

	influence = saturate(Math::sin(time / 2.0f) + 1.0f);
	plastic = (Math::cos(time / 5.0f) + 1.0f) / 2.0f;

	int color_index = static_cast<int>(time / 4.0f) % colors.size();

	color = lerp(color, colors[color_index], 0.2f * ifps);

	color_label->setText(
		String::format("Color: %0.2f %0.2f %0.2f %0.2f", color.x, color.y, color.z, color.w));
	influence_label->setText(String::format("Influence: %0.2f", influence));
	plastic_label->setText(String::format("Plastic: %0.2f", plastic));
}

// Окно UI очищается при уничтожении компонента.
void GBufferWrite::shutdown()
{
	sample_description_window.shutdown();
}
