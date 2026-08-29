// Реализует раскопку terrain с помощью проекции глубины объекта. Форма роющего объекта
// проецируется на поверхность terrain, изменяя данные высоты и маски
// в базовом LandscapeLayerMap с помощью операций асинхронного рисования текстуры.

#include "DiggingTool.h"

#include <Unigine.h>
#include <UnigineTextures.h>

REGISTER_COMPONENT(DiggingTool);

using namespace Unigine;
using namespace Math;

// Получаются ссылки на layer map и роющий объект; создаётся материал.
void DiggingTool::init()
{
	// Ссылки на узлы проверяются и приводятся к нужным типам
	{
		layer_map = checked_ptr_cast<LandscapeLayerMap>(lmap_node.get());
		if (!layer_map)
		{
			Log::error("DiggingTool: can't cast node to lmap\n");
			return;
		}

		digging_object = checked_ptr_cast<Object>(digging_object_node.get());
		if (!digging_object)
		{
			Log::error("DiggingTool: digging object is null\n");
			return;
		}

		// Материал раскопки загружается и наследуется для изменения во время выполнения
		auto guid = FileSystem::getGUID(FileSystem::resolvePartialVirtualPath("digging_tool.basemat"));
		if (auto mat = Materials::findMaterialByFileGUID(guid))
		{
			digging_tool_mat = mat->inherit();
			if (!digging_tool_mat)
			{
				Log::error("DiggingTool: can't create digging tool material\n");
				return;
			}
		}
		else
		{
			Log::error("DiggingTool: can't create digging tool material\n");
			return;
		}
	}

	// Подключается callback асинхронного рисования текстуры; предыдущие изменения очищаются
	{
		Landscape::getEventTextureDraw().connect(texture_draw_connection, this, &DiggingTool::on_texture_draw);
		reset_modifications();
	}

	// Инициализируется обработка мыши и манипуляторы GUI
	{
		Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);
		target_transform = digging_object->getWorldTransform();
		gui.init(this);
	}
}

// Роющий объект интерполируется; terrain обновляется при значительном перемещении объекта.
void DiggingTool::update()
{
	update_digging_object();

	// Клавиша C сбрасывает все изменения terrain
	if (Input::isKeyDown(Input::KEY_C))
		reset_modifications();

	// Обновление terrain ставится в очередь только при достаточном изменении позиции/поворота
	if (should_update_terrain())
		enqueue_terrain_update();

	gui.update();
}

// Соединение события удаляется; ожидающие операции очищаются.
void DiggingTool::shutdown()
{
	texture_draw_connection.disconnect();
	reset_modifications();

	// Ожидающие текстуры глубины уничтожаются
	for (auto &it: per_operation_draw_data)
		it.data.object_depth_texture->destroy();

	per_operation_draw_data.clear();

	gui.shutdown();
}

// =======================================================================================

// Роющий объект плавно интерполируется к целевой трансформации от манипулятора.
void DiggingTool::update_digging_object()
{
	float ifps = Game::getIFps();

	// Ограничивающая сфера используется для получения квадратного ограничивающего бокса для стабильного выделения текстуры
	digging_object_wbb = WorldBoundBox { digging_object->getWorldBoundSphere() };

	float position_lerp_rate = 5.f;
	float rotation_lerp_rate = 2.f;

	Mat4 transform = digging_object->getWorldTransform();

	Vec3 position = transform.getTranslate();

	// Позиция и поворот интерполируются к цели
	Vec3 new_position = lerp(position, target_transform.getTranslate(), position_lerp_rate * ifps);
	quat new_rotation = slerp(transform.getRotate(), target_transform.getRotate(), rotation_lerp_rate * ifps);

	{
		// Перемещение ограничивается, чтобы избежать разрывов в изменении terrain,
		// когда объект движется быстрее, чем скорость обновления terrain

		float max_delta = position_spacing;

		Vec3 delta = new_position - position;
		Vec3 direction = normalize(delta);
		float magnitude = length(delta);

		magnitude = min(magnitude, max_delta);
		new_position = position + direction * magnitude;
	}

	digging_object->setWorldTransform(Mat4 { new_rotation, new_position });
}

// Возвращает true, если объект достаточно переместился/повернулся для обновления terrain.
bool DiggingTool::should_update_terrain()
{
	// Terrain обновляется только если возникнет видимая разница
	// (определяется порогами position_spacing и rotation_spacing)

	Vec3 position = digging_object->getWorldPosition();
	vec3 rotation = decomposeRotationXYZ(mat3(digging_object->getWorldTransform()));

	// compare возвращает true, если значения в пределах допуска (обновление не требуется)
	if (compare(position, prev_position, position_spacing) && compare(rotation, prev_rotation, rotation_spacing))
		return false;

	prev_position = position;
	prev_rotation = rotation;

	return true;
}

// Текстура глубины рендерится, асинхронное изменение terrain ставится в очередь.
void DiggingTool::enqueue_terrain_update()
{
	// Лямбды преобразуют между мировыми координатами и координатами текселей landscape
	auto world_to_texel = [this](const Vec3 &world_pos, bool is_max) -> ivec2 {
		Vec2 coord = world_pos.xy / layer_map->getTexelSize();
		return ivec2(is_max ? ceil(coord) : floor(coord));
	};

	auto texel_to_world = [this](const ivec2 &texel_pos) -> Vec2 {
		return Vec2(texel_pos) * layer_map->getTexelSize();
	};

	TexturePtr object_depth_texture;

	// Ограничивающий бокс преобразуется в координаты текселей
	ivec2 coord = world_to_texel(digging_object_wbb.minimum, true);
	ivec2 coord_max = world_to_texel(digging_object_wbb.maximum, false);
	ivec2 resolution = coord_max - coord;

	// Разрешение проверяется и выравнивается для оптимизации переиспользования текстур
	{
		if (resolution.x <= 0 || resolution.y <= 0)
			return;

		// Выравнивание до 64 помогает аллокатору ресурсов переиспользовать текстуры
		resolution = align(resolution, 64);
	}

	// Создаётся текстура глубины для хранения глубины силуэта объекта
	{
		object_depth_texture = Texture::create();

		// 32-битный float R-канал хранит значения глубины
		int texture_format = Texture::FORMAT_R32F;

		int texture_flags = {
			Texture::SAMPLER_FILTER_LINEAR |
			Texture::SAMPLER_FILTER_BILINEAR |
			Texture::SAMPLER_WRAP_MASK |
			Texture::FORMAT_USAGE_RENDER |	// Требуется для рендеринга в текстуру
			0
		};

		object_depth_texture->create2D(resolution.x, resolution.y, texture_format, texture_flags);
	}

	// Глубина объекта рендерится сверху в текстуру
	{
		Vec3 position { texel_to_world(coord), digging_object_wbb.minimum.z };
		Vec3 size { texel_to_world(resolution), digging_object_wbb.getSize().z };

		object_depth.renderDepthTexture(object_depth_texture, digging_object, position, size, resolution);
	}

	// Операция асинхронного рисования текстуры ставится в очередь системы landscape
	{
		int id = Landscape::generateOperationID();

		DrawData draw_data;
		draw_data.resolution = resolution;
		draw_data.object_depth_texture = object_depth_texture;

		per_operation_draw_data.append(id, draw_data);

		// Флаги указывают, какие слои данных terrain изменять
		int flags_file_data = {
			Landscape::FLAGS_DATA_HEIGHT |		// Изменить карту высот
			Landscape::FLAGS_FILE_DATA_MASK_4 |	// Изменить маску 4 (пример)
			0
		};

		Landscape::asyncTextureDraw(id, layer_map->getGUID(), coord, draw_data.resolution, flags_file_data);
	}
}

// =======================================================================================

// Callback, вызываемый, когда асинхронное рисование текстуры готово; проход шейдера изменяет данные terrain.
void DiggingTool::on_texture_draw(const UGUID &guid, int operation_id, const LandscapeTexturesPtr &buffer, const ivec2 &coords, int data_mask)
{
	// Данные рисования для этой операции извлекаются из карты ожидающих
	auto it = per_operation_draw_data.find(operation_id);
	if (it == per_operation_draw_data.end())
		return;

	// Буферы terrain и текстура глубины привязываются к материалу для прохода шейдера
	digging_tool_mat->setTexture("bind_height", buffer->getHeight());
	digging_tool_mat->setTexture("bind_mask", buffer->getMask(4));
	digging_tool_mat->setTexture("object_depth", it->data.object_depth_texture);

	// Шейдерное выражение изменяет высоту и маску terrain на основе глубины объекта
	digging_tool_mat->runExpression("draw_object", it->data.resolution.x, it->data.resolution.y);

	// Текстуры отвязываются после выполнения шейдера
	digging_tool_mat->setTexture("bind_height", nullptr);
	digging_tool_mat->setTexture("bind_mask", nullptr);
	digging_tool_mat->setTexture("object_depth", nullptr);

	// Текстура глубины очищается после использования
	it->data.object_depth_texture->destroy();
	per_operation_draw_data.remove(it);
}

// Все изменения terrain, сделанные этим инструментом, откатываются в исходное состояние.
void DiggingTool::reset_modifications()
{
	Landscape::asyncResetModifications(layer_map->getGUID());
}

// =======================================================================================
// РЕАЛИЗАЦИЯ GUI
// =======================================================================================

// Создаются манипуляторы переноса и поворота для интерактивного управления объектом.
void DiggingTool::Gui::init(DiggingTool *sample)
{
	this->sample = sample;

	auto gui = Unigine::Gui::getCurrent();

	// Лямбда инициализирует общие свойства манипулятора
	auto init_manipulator = [this, gui](auto manipulator)
	{
		manipulator->setBasis(this->sample->target_transform);
		manipulator->setTransform(this->sample->target_transform);
		manipulator->setMask(WidgetManipulator::MASK_XYZ);
		manipulator->setRenderGui(gui);
		manipulator->setHidden(true);
		gui->addChild(manipulator);
	};

	translator = WidgetManipulatorTranslator::create(gui);
	rotator = WidgetManipulatorRotator::create(gui);

	init_manipulator(translator);
	init_manipulator(rotator);

	// По умолчанию активен транслятор
	set_manipulator(translator);
}

// Манипулятор обновляется матрицами камеры; клавиатура переключает режим инструмента.
void DiggingTool::Gui::update()
{
	PlayerPtr player = Game::getPlayer();

	if (!player || !active)
		return;

	// Матрицы камеры передаются манипулятору для корректного 3D-рендеринга
	active->setModelview(player->getCamera()->getModelview());
	active->setProjection(player->getProjection());
	active->setBasis(basis == LOCAL ? active->getTransform() : Mat4_identity);

	// Клавиатурные сокращения переключают инструменты и системы координат
	if (!Input::isMouseGrab() && !Console::isActive())
	{
		if (Input::isKeyDown(Input::KEY_T))
			set_manipulator(translator);	// T = режим переноса

		if (Input::isKeyDown(Input::KEY_R))
			set_manipulator(rotator);		// R = режим поворота

		if (Input::isKeyDown(Input::KEY_G))
			basis = (basis == LOCAL) ? WORLD : LOCAL;	// G = переключение локальный/мировой
	}

	// Целевая трансформация обновляется из позиции манипулятора
	sample->target_transform = active->getTransform();
}

// Активный манипулятор переключается; трансформация сохраняется между инструментами.
void DiggingTool::Gui::set_manipulator(WidgetManipulatorPtr manipulator)
{
	WidgetManipulatorPtr previous = active;
	active = manipulator;

	// Трансформация передаётся от предыдущего манипулятора
	if (previous)
	{
		previous->setHidden(true);
		active->setTransform(previous->getTransform());
	}

	active->setHidden(false);
}

// Виджеты манипулятора планируются к удалению.
void DiggingTool::Gui::shutdown()
{
	translator.deleteLater();
	rotator.deleteLater();
}
