// Рисует значения высоты на terrain с помощью настраиваемых мазков кисти.
// Поддерживает альфа- и аддитивный режимы смешивания для скульптинга terrain.
// Мазки кисти применяются через асинхронное рисование текстуры с GPU-шейдером.

#include "LandscapeHeightPainter.h"

#include <UnigineMaterials.h>

REGISTER_COMPONENT(LandscapeHeightPainter);

using namespace Unigine;
using namespace Math;

// Callback рисования текстуры подключается к системе событий landscape.
void LandscapeHeightPainter::enable()
{
	// Предотвращаем дублирующиеся подключения
	if (callback_handle.isValid())
		return;

	Landscape::getEventTextureDraw().connect(callback_handle, this, &LandscapeHeightPainter::texture_draw_callback);
}

// Callback рисования текстуры отключается от системы событий landscape.
void LandscapeHeightPainter::disable()
{
	// Пропускаем отключение, если не подключено
	if (!callback_handle.isValid())
		return;

	callback_handle.disconnect();
}

// Мазок кисти применяется в мировой позиции, если порог интервала соблюдён.
void LandscapeHeightPainter::paintAt(const Unigine::Math::Vec3 & world_position)
{
	// Пропускаем мазок, если слишком близко к предыдущей позиции
	auto distance = (world_position - last_paint_position).length();
	if (distance < brush_spacing * brush_size)
		return;
	last_paint_position = world_position;

	// Мировая позиция преобразуется в локальное пространство landscape
	Vec3 brush_local_position = landscape_layer_map->getIWorldTransform() * world_position;

	// Поворот кисти вычисляется относительно ориентации landscape
	quat brush_world_rotation = quat(vec3_up, brush_angle);
	quat brush_local_rotation = brush_world_rotation * inverse(landscape_layer_map->getWorldRotation());

	// Повёрнутые углы кисти вычисляются в локальном пространстве
	float half_size = brush_size / 2.0f;
	Vec3 brush_local_corners[4] = {
		brush_local_position + brush_local_rotation * Vec3(-half_size, -half_size, 0.0),
		brush_local_position + brush_local_rotation * Vec3( half_size, -half_size, 0.0),
		brush_local_position + brush_local_rotation * Vec3(-half_size,  half_size, 0.0),
		brush_local_position + brush_local_rotation * Vec3( half_size,  half_size, 0.0)
	};

	// Ограничивающий бокс, выровненный по осям, вычисляется из повёрнутых углов
	auto brush_local_bbox_min = Vec2{
		min(min(brush_local_corners[0].x, brush_local_corners[1].x), min(brush_local_corners[2].x, brush_local_corners[3].x)),
		min(min(brush_local_corners[0].y, brush_local_corners[1].y), min(brush_local_corners[2].y, brush_local_corners[3].y))
	};
	auto brush_local_bbox_max = Vec2{
		max(max(brush_local_corners[0].x, brush_local_corners[1].x), max(brush_local_corners[2].x, brush_local_corners[3].x)),
		max(max(brush_local_corners[0].y, brush_local_corners[1].y), max(brush_local_corners[2].y, brush_local_corners[3].y))
	};

	// Координаты и разрешение в пикселях вычисляются из мировых единиц
	auto pixels_per_unit = Vec2{ landscape_layer_map->getResolution() } / Vec2{ landscape_layer_map->getSize() };
	auto drawing_region_coord = ivec2{ pixels_per_unit * brush_local_bbox_min };
	auto drawing_region_resolution = ivec2{ pixels_per_unit * (brush_local_bbox_max - brush_local_bbox_min) };
	auto local_brush_angle = brush_local_rotation.getAngle(vec3_up);

	// Генерируется уникальный ID операции для отслеживания
	auto id = Landscape::generateOperationID();

	// Текущие параметры кисти захватываются для асинхронного callback
	per_operation_draw_data.insert(id, DrawData{
		blend_mode,
		brush_texture,
		brush_mask,
		local_brush_angle,
		brush_opacity,
		brush_height,
		brush_height_scale
	});

	// Асинхронное рисование текстуры ставится в очередь для изменения данных высоты
	Landscape::asyncTextureDraw(id, landscape_layer_map->getGUID(), drawing_region_coord,
		drawing_region_resolution, Landscape::FLAGS_DATA_HEIGHT);
}

// Загружается и создаётся экземпляр шейдерного материала кисти.
void LandscapeHeightPainter::init()
{
	// GUID материала разрешается из частичного виртуального пути
	auto guid = FileSystem::getGUID(FileSystem::resolvePartialVirtualPath("landscape_height_brush.basemat"));
	if (!guid.isValid())
	{
		Log::warning("LandscapeHeightPainter::init(): can not find \"landscape_height_brush.basemat\" material\n");
		return;
	}

	// Создаётся уникальный экземпляр материала для этого компонента
	brush_material = Materials::findMaterialByFileGUID(guid)->inherit();
}

// Шейдер кисти выполняется, когда буфер асинхронного рисования готов.
void LandscapeHeightPainter::texture_draw_callback(const UGUID &guid, int id, const LandscapeTexturesPtr &buffer, const ivec2 &coord, int data_mask)
{
	// Проверяем, что операция принадлежит этому компоненту
	auto it = per_operation_draw_data.find(id);
	if (it == per_operation_draw_data.end())
		return;

	// Получаем временный рендер-таргет для прохода шейдера
	auto render_target = Render::getTemporaryRenderTarget();

	// Сохраняем состояние рендеринга для восстановления после выполнения шейдера
	RenderState::saveState();
	RenderState::clearStates();

	// Буфер высоты привязывается как текстура неупорядоченного доступа для чтения-записи
	render_target->bindUnorderedAccessTexture(0, buffer->getHeight());
	render_target->enable();
	{
		// Состояние режима смешивания определяет альфа или аддитивное смешивание
		brush_material->setState("blend_mode", static_cast<int>(it->data.blend_mode));

		// Параметры кисти передаются в шейдер
		brush_material->setTexture("brush_texture", it->data.brush_texture);
		brush_material->setTexture("brush_mask", it->data.brush_mask);
		brush_material->setParameterFloat("brush_angle", it->data.brush_angle);
		brush_material->setParameterFloat("brush_opacity", it->data.brush_opacity);
		brush_material->setParameterFloat("brush_height", it->data.brush_height);
		brush_material->setParameterFloat("brush_height_scale", it->data.brush_height_scale);

		// Выполняется полноэкранный проход шейдера
		brush_material->renderScreen("landscape_height_brush");

	}
	render_target->disable();
	render_target->unbindUnorderedAccessTexture(0);

	// Состояние рендеринга восстанавливается до предыдущей конфигурации
	RenderState::restoreState();

	// Временный рендер-таргет возвращается в пул
	Render::releaseTemporaryRenderTarget(render_target);

	// Данные завершённой операции удаляются из отслеживания
	per_operation_draw_data.erase(it);
}
