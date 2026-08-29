// Преобразует значения высоты terrain в цвета albedo с помощью текстуры градиента.
// Диапазон высоты отображается на координаты градиента для колоризации.
// Работает со всей landscape layer map, используя асинхронное рисование текстуры.

#include "LandscapeHeightToAlbedo.h"

#include <UnigineMaterials.h>

REGISTER_COMPONENT(LandscapeHeightToAlbedo);

using namespace Unigine;
using namespace Math;

// Callback рисования текстуры подключается к системе событий landscape.
void LandscapeHeightToAlbedo::enable()
{
	// Предотвращаем дублирующиеся подключения
	if (callback_handle.isValid())
		return;

	Landscape::getEventTextureDraw().connect(callback_handle, this, &LandscapeHeightToAlbedo::texture_draw_callback);
}

// Callback рисования текстуры отключается от системы событий landscape.
void LandscapeHeightToAlbedo::disable()
{
	// Пропускаем отключение, если не подключено
	if (!callback_handle.isValid())
		return;

	callback_handle.disconnect();
}

// Запускается асинхронное преобразование высоты в albedo для всего landscape.
void LandscapeHeightToAlbedo::run()
{
	// Генерируется уникальный ID операции для отслеживания
	auto id = Landscape::generateOperationID();

	// Текущие параметры захватываются для асинхронного callback
	per_operation_draw_data.insert(id, DrawData{
		gradient,
		min_height,
		max_height
	});

	// Запрашивается полное разрешение landscape с данными albedo и высоты
	Landscape::asyncTextureDraw(id, landscape_layer_map->getGUID(), { 0, 0 },
		landscape_layer_map->getResolution(), Landscape::FLAGS_DATA_ALBEDO | Landscape::FLAGS_DATA_HEIGHT);
}

// Загружается и создаётся экземпляр шейдерного материала для преобразования высоты в albedo.
void LandscapeHeightToAlbedo::init()
{
	// GUID материала разрешается из частичного виртуального пути
	auto guid = FileSystem::getGUID(FileSystem::resolvePartialVirtualPath("landscape_height_to_albedo.basemat"));
	if (!guid.isValid())
	{
		Log::warning("LandscapeHeightToAlbedo::init(): can not find \"landscape_height_to_albedo.basemat\" material\n");
		return;
	}

	// Создаётся уникальный экземпляр материала для этого компонента
	material = Materials::findMaterialByFileGUID(guid)->inherit();
}

// Шейдер преобразования высоты в albedo выполняется, когда буфер асинхронного рисования готов.
void LandscapeHeightToAlbedo::texture_draw_callback(const Unigine::UGUID &guid, int id, const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coord, int data_mask)
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

	// Буфер albedo привязывается как рендер-таргет для вывода
	render_target->bindColorTexture(0, buffer->getAlbedo());
	render_target->enable();
	{
		// Входные данные шейдера настраиваются данными высоты и отображением градиента
		material->setTexture("height", buffer->getHeight());
		material->setTexture("gradient", it->data.gradient);
		material->setParameterFloat("min_height", it->data.min_height);
		material->setParameterFloat("max_height", it->data.max_height);

		// Выполняется полноэкранный проход шейдера
		material->renderScreen("landscape_height_to_albedo");

	}
	render_target->disable();
	render_target->unbindColorTexture(0);

	// Состояние рендеринга восстанавливается до предыдущей конфигурации
	RenderState::restoreState();

	// Временный рендер-таргет возвращается в пул
	Render::releaseTemporaryRenderTarget(render_target);

	// Данные завершённой операции удаляются из отслеживания
	per_operation_draw_data.erase(it);
}
