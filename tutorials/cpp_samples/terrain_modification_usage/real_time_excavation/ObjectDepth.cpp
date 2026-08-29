// Рендерит буфер глубины объекта с ортографического вида сверху. Текстура глубины
// используется системой раскопки для определения того, насколько глубоко объект врезается
// в terrain в каждой позиции текселя.

#include "ObjectDepth.h"
#include <Unigine.h>
#include <UnigineTextures.h>

using namespace Unigine;
using namespace Math;

ObjectDepth::ObjectDepth()
{
	camera = Camera::create();

	viewport = Viewport::create();
	// Отключаем коррекцию соотношения сторон для точного отображения пикселей
	viewport->setAspectCorrection(0);
	// Сохраняем временные ресурсы живыми 10 часов для переиспользования между рендерами
	viewport->setLifetime(60 * 60 * 10);
	// Пропускаем все пост-эффекты, тени и т.д., так как нужна только глубина
	viewport->setSkipFlags(~0);

	render_target = RenderTarget::create();

	// Режим RENDER_DEPTH выводит только буфер глубины, без цвета
	viewport->setRenderMode(Viewport::RENDER_DEPTH);

	// Подключаем callback, где проход шейдера преобразует глубину в мировую высоту
	viewport->getEventEndScreen().connect(on_end_screen_connection, this, &ObjectDepth::on_end_screen);

	auto guid = FileSystem::getGUID(FileSystem::resolvePartialVirtualPath("digging_tool.basemat"));
	if (guid.isValid())
		// inherit() создаёт изменяемый экземпляр материала
		digging_tool_mat = Materials::findMaterialByFileGUID(guid)->inherit();
	else
		Log::warning("ObjectDepth::ObjectDepth(): can not find \"digging_tool.basemat\" material\n");
}

void ObjectDepth::renderDepthTexture(
	TexturePtr &tex,
	const NodePtr &target,
	const Vec3 &pos,
	const Vec3 &size,
	const ivec2 &resolution
)
{
	if (!target)
		return;

	Vec3 center = pos + size * .5f;

	// Сохраняем параметры ограничивающего бокса для преобразования глубины в мировые координаты в шейдере
	// Шейдер отображает глубину clip-space [0,1] обратно в мировые координаты Z
	{
		bb_height = (float)size.z;
		bb_min_z = (float)pos.z;
	}

	// Настраиваем ортографическую камеру так, чтобы точно совпадать с размерами ограничивающего бокса
	{
		// Ортографическая проекция охватывает протяжённость XY ограничивающего бокса
		mat4 projection = ortho((float)(-size.x * 0.5f), (float)(size.x * 0.5f), (float)(-size.y * 0.5f), (float)(size.y * 0.5f), 0.0f, (float)size.z);
		// Камера расположена у дна бокса, смотрит вверх (повёрнута на 180 вокруг X)
		Mat4 transform = translate(Vec3(center.x, center.y, pos.z)) * Mat4(rotateX(-180.0f));

		camera->setProjection(projection);
		// Modelview = инверсия мировой трансформации
		camera->setModelview(inverse(transform));
	}

	// Рендерим объект в текстуру глубины
	{
		// Сохраняем и очищаем состояние рендеринга во избежание помех
		RenderState::saveState();
		RenderState::clearStates();
		RenderState::setViewport(0, 0, resolution.x, resolution.y);

		// Привязываем выходную текстуру как цветовое вложение (глубина преобразуется в цвет)
		render_target->bindColorTexture(0, tex);
		render_target->enable();

		{
			// renderNode рисует один узел с настроенной камерой
			viewport->renderNode(camera, target);
		}

		render_target->disable();
		render_target->unbindColorTexture(0);

		RenderState::restoreState();
	}
}

void ObjectDepth::on_end_screen()
{
	// Передаём текущий буфер глубины и информацию об ограничивающем боксе в шейдер
	digging_tool_mat->setTexture("depth", Renderer::getTextureCurrentDepth());
	digging_tool_mat->setParameterFloat("bb_height", bb_height);
	digging_tool_mat->setParameterFloat("bb_min_z", bb_min_z);
	// Выполняем полноэкранный проход для преобразования глубины в мировую высоту
	digging_tool_mat->renderScreen("object_depth");
}
