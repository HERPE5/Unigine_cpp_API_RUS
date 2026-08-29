// Рендеринг FFP с тестированием глубины. Отрисовывает 3D-линии с использованием буфера
// глубины сцены для правильного перекрытия. Демонстрирует ручную настройку проекции с
// обратной глубиной и смешиванием для наложений, учитывающих геометрию сцены.

#include "FFPDepth.h"

#include <UnigineFfp.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(FFPDepth)

// Callback регистрируется для события end-visualizer (после рендеринга сцены).
void FFPDepth::init()
{
	Render::getEventEndVisualizer().connect(this, &FFPDepth::render_lines_callback);
}

// Линии FFP отрисовываются с тестированием глубины, чтобы они перекрывались геометрией сцены.
void FFPDepth::render_lines_callback()
{
	RenderTargetPtr render_target = Renderer::getRenderTarget();
	TexturePtr texture = Renderer::getTextureColor();

	RenderState::saveState();
	RenderState::clearStates();

	// Буфер глубины уже привязан из прохода сцены
	render_target->bindColorTexture(0, texture);

	render_target->enable();
	{
		// GEQUAL для обратной глубины; альфа-смешивание для прозрачности наложения
		RenderState::setDepthFunc(RenderState::DEPTH_GEQUAL);
		RenderState::setBlendFunc(RenderState::BLEND_SRC_ALPHA, RenderState::BLEND_ONE_MINUS_SRC_ALPHA);
		RenderState::flushStates();

		Ffp::enable();

		// Белая текстура позволяет цвету вершин проходить без изменений
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 0, Render::getWhite2DTexture());

		// Проекция корректируется для обратной глубины и пространства отсечения [0..1]
		mat4 projection;
		const mat4 offset = translate(0.f, 0.f, 0.5f) * scale(1.f, 1.f, 0.5f);
		mul(projection, offset, reverseDepthProjection((Renderer::getProjectionWithoutTAA())));

		Ffp::setTransform(projection);

		auto model_view = Renderer::getModelview();

		const unsigned col_argb = 0xffff0000;	// Красная линия

		Ffp::beginLines();
		Ffp::addLines(1);

		Ffp::Vertex vert;

		// Конечные точки линии преобразуются из мирового пространства в пространство камеры
		vec3(model_view * vec3(-0.5f, -0.3f, 0.65f)).get(vert.xyz);
		Ffp::addVertex(vert);
		Ffp::setColor(col_argb);

		vec3(model_view * vec3(0.5f, -0.3f, 0.65f)).get(vert.xyz);
		Ffp::addVertex(vert);
		Ffp::setColor(col_argb);

		Ffp::endLines();
		Ffp::disable();
	}
	render_target->disable();
	render_target->unbindColorTextures();
	RenderState::restoreState();
}
