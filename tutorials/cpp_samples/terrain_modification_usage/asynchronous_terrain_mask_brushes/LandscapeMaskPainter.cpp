// Реализует рисование масок terrain с настраиваемыми параметрами кисти.
// Мазки кисти применяются к каналам маски LandscapeLayerMap через асинхронное рисование текстуры.
// Поддерживает настройку текстуры кисти, непрозрачности, поворота, интервала и цвета.

#include "LandscapeMaskPainter.h"

#include <UnigineMaterials.h>

REGISTER_COMPONENT(LandscapeMaskPainter);

using namespace Unigine;
using namespace Math;

// Callback рисования текстуры подключается для получения событий завершения асинхронного рисования.
void LandscapeMaskPainter::enable()
{
	// Предотвращается дублирующееся подключение
	if (callback_handle.isValid())
	{
		return;
	}

	// Callback регистрируется для завершения асинхронного рисования текстуры
	Landscape::getEventTextureDraw().connect(callback_handle, this,
		&LandscapeMaskPainter::texture_draw_callback);
}

// Callback рисования текстуры отключается, чтобы прекратить получение событий рисования.
void LandscapeMaskPainter::disable()
{
	// Обрабатывается уже отключённое состояние
	if (!callback_handle.isValid())
	{
		return;
	}

	callback_handle.disconnect();
}

// Мазок кисти применяется в мировой позиции; интервал управляет плотностью мазков.
void LandscapeMaskPainter::paintAt(const Unigine::Math::Vec3 &world_position)
{
	// Мазок пропускается, если слишком близко к предыдущему мазку (на основе интервала)
	auto distance = (world_position - last_paint_position).length();
	if (distance < brush_spacing * brush_size)
	{
		return;
	}

	last_paint_position = world_position;

	// Мировая позиция преобразуется в локальное пространство landscape
	Vec3 brush_local_position = landscape_layer_map->getIWorldTransform() * world_position;
	quat brush_world_rotation = quat(vec3_up, brush_angle);
	quat brush_local_rotation = brush_world_rotation
		* inverse(landscape_layer_map->getWorldRotation());
	float half_size = brush_size / 2.0f;

	// Четыре угла повёрнутого квада кисти вычисляются в локальном пространстве
	Vec3 brush_local_corners[4]
		= {brush_local_position + brush_local_rotation * Vec3(-half_size, -half_size, 0.0),
			brush_local_position + brush_local_rotation * Vec3(half_size, -half_size, 0.0),
			brush_local_position + brush_local_rotation * Vec3(-half_size, half_size, 0.0),
			brush_local_position + brush_local_rotation * Vec3(half_size, half_size, 0.0)};

	// Ограничивающий бокс, выровненный по осям, вычисляется из повёрнутых углов
	auto brush_local_bbox_min = Vec2{min(min(brush_local_corners[0].x, brush_local_corners[1].x),
										 min(brush_local_corners[2].x, brush_local_corners[3].x)),
		min(min(brush_local_corners[0].y, brush_local_corners[1].y),
			min(brush_local_corners[2].y, brush_local_corners[3].y))};
	auto brush_local_bbox_max = Vec2{max(max(brush_local_corners[0].x, brush_local_corners[1].x),
										 max(brush_local_corners[2].x, brush_local_corners[3].x)),
		max(max(brush_local_corners[0].y, brush_local_corners[1].y),
			max(brush_local_corners[2].y, brush_local_corners[3].y))};

	// Локальные координаты преобразуются в координаты пикселей
	auto pixels_per_unit = Vec2{landscape_layer_map->getResolution()}
		/ Vec2{landscape_layer_map->getSize()};
	auto drawing_region_coord = ivec2{pixels_per_unit * brush_local_bbox_min};
	auto drawing_region_resolution = ivec2{
		pixels_per_unit * (brush_local_bbox_max - brush_local_bbox_min)};
	auto local_brush_angle = brush_local_rotation.getAngle(vec3_up);

	// Операция рисования ставится в очередь с текущими параметрами кисти
	auto id = Landscape::generateOperationID();
	per_operation_draw_data.insert(id,
		DrawData{brush_texture, brush_mask, local_brush_angle, brush_opacity, brush_color});

	// Запрашивается асинхронное рисование текстуры для канала маски 0 с непрозрачностью
	Landscape::asyncTextureDraw(id, landscape_layer_map->getGUID(), drawing_region_coord,
		drawing_region_resolution,
		static_cast<int>(Landscape::FLAGS_DATA_MASK_0)
			| static_cast<int>(Landscape::FLAGS_FILE_DATA_OPACITY_MASK_0));
}

// Материал кисти загружается и наследуется; ссылка на clutter проверяется.
void LandscapeMaskPainter::init()
{
	// Шейдерный материал кисти загружается из файла
	auto guid = FileSystem::getGUID(
		FileSystem::resolvePartialVirtualPath("landscape_mask_brush.basemat"));
	if (!guid.isValid())
	{
		Log::error(
			"LandscapePainter::init(): can not find \"landscape_mask_brush.basemat\" material");
		return;
	}
	brush_material = Materials::findMaterialByFileGUID(guid)->inherit();

	// Ссылка на узел clutter проверяется для инвалидации на основе маски
	if (!clutter_param.get())
	{
		Log::error("LandscapePainter::init(): attached node is not clutter");
		return;
	}

	clutter = checked_ptr_cast<ObjectMeshClutter>(clutter_param.get());
}

// Шейдер кисти выполняется, когда буфер асинхронного рисования текстуры готов.
void LandscapeMaskPainter::texture_draw_callback(const Unigine::UGUID &guid, int id,
	const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coord, int data_mask)
{
	// Данные рисования для этой операции извлекаются из карты ожидающих
	auto it = per_operation_draw_data.find(id);
	if (it == per_operation_draw_data.end())
	{
		return;
	}

	// Временный рендер-таргет получается для выполнения шейдера
	auto render_target = Render::getTemporaryRenderTarget();

	// Состояние рендеринга сохраняется для восстановления после прохода шейдера
	RenderState::saveState();
	RenderState::clearStates();

	// Текстуры маски и непрозрачности привязываются как неупорядоченный доступ для compute-шейдера
	render_target->bindUnorderedAccessTexture(0, buffer->getMask(0));
	render_target->bindUnorderedAccessTexture(1, buffer->getOpacityMask(0));
	render_target->enable();
	{
		// Параметры кисти передаются в материал шейдера
		brush_material->setTexture("brush_texture", it->data.brush_texture);
		brush_material->setTexture("brush_mask", it->data.brush_mask);
		brush_material->setParameterFloat("brush_angle", it->data.brush_angle);
		brush_material->setParameterFloat("brush_opacity", it->data.brush_opacity);
		brush_material->setParameterFloat4("brush_color", it->data.brush_color);

		// Выполняется полноэкранный проход шейдера кисти
		brush_material->renderScreen("landscape_mask_brush");
	}
	render_target->disable();
	render_target->unbindUnorderedAccessTexture(0);
	render_target->unbindUnorderedAccessTexture(1);

	// Восстанавливается предыдущее состояние рендеринга
	RenderState::restoreState();

	// Временные ресурсы освобождаются; данные операции очищаются
	Render::releaseTemporaryRenderTarget(render_target);
	per_operation_draw_data.erase(it);

	// Clutter инвалидируется для регенерации экземпляров на основе новой маски
	if (clutter_param.get())
	{
		clutter->invalidate();
	}
}
