// Выполняет нарезку высоты (height slicing) на GPU для данных landscape terrain. Читает высоту
// из исходного LandscapeLayerMap и записывает изменённую высоту/albedo в целевой слой.
// Использует callback'и асинхронного рисования текстуры и конечный автомат для многокадровой обработки.

#include "HeightSlicer.h"

#include <UnigineMaterials.h>


REGISTER_COMPONENT(HeightSlicer);

using namespace Unigine;
using namespace Math;

void HeightSlicer::enable()
{
	// Подключаемся к событию рисования текстуры Landscape
	// Callback вызывается по завершении asyncTextureDraw
	Landscape::getEventTextureDraw().connect(this, &HeightSlicer::texture_draw_callback);
}

void HeightSlicer::disable()
{
	// Удаляет все соединения событий для этого объекта
	disconnectAll();
}

void HeightSlicer::setSourceLmap(
	const Unigine::LandscapeLayerMapPtr &in_source_lmap)
{
	maps.clear();
	source_lmap = in_source_lmap;
	// Вектор maps используется Landscape::render для пакетной обработки
	maps.push_back(source_lmap);
}

void HeightSlicer::run()
{
	// Игнорируем, если уже выполняется обработка
	if (state != State::IDLE)
		return;

	// Начинаем многокадровую операцию нарезки
	state = State::BEGIN_FETCH_HEIGHT;
}

void HeightSlicer::init()
{
	// Разрешаем частичный путь в полный GUID для поиска материала
	auto guid = FileSystem::getGUID(FileSystem::resolvePartialVirtualPath(
		"landscape_height_slice.basemat"));

	if (guid.isValid())
		// inherit() создаёт изменяемый экземпляр базового материала
		slice_material = Materials::findMaterialByFileGUID(guid)->inherit();
	else
		Log::warning(
			"HeightSlicer::init(): can not find \"landscape_height_slice.basemat\""
			"material\n");
}

void HeightSlicer::update()
{
	switch (state)
	{
		case State::IDLE:
			break;
		case State::BEGIN_FETCH_HEIGHT:
		{
			// Пропускаем, если у исходного слоя нет корректного разрешения
			if (source_lmap->getResolution().x == 0 || source_lmap->getResolution().y == 0)
				return;

			// Создаём промежуточный буфер для операций с текстурами landscape
			if (!buffers)
			{
				buffers = LandscapeTextures::create(source_lmap->getResolution());
			}

			// Создаём текстуру для хранения отрендеренных данных высоты
			if (!source_lmap_height)
			{
				source_lmap_height = Texture::create();
				// R32F = 32-битный float для высокой точности значений высоты
				// Несколько флагов включают: фильтрацию, использование как рендер-таргет, доступ compute
				source_lmap_height->create2D(source_lmap->getResolution().x, source_lmap->getResolution().y,
					Texture::FORMAT_R32F,
					Texture::SAMPLER_FILTER_LINEAR | Texture::FORMAT_USAGE_RENDER | Texture::SAMPLER_FILTER_BILINEAR | Texture::FORMAT_USAGE_UNORDERED_ACCESS | Texture::SAMPLER_WRAP_MASK);
			}

			// Landscape::render возвращает true, когда рендеринг завершён
			// Mat4_identity = без трансформации, размер тексела из исходного слоя
			if (!buffers_rendered && Landscape::render(maps, buffers, Mat4_identity, source_lmap->getTexelSize().x, 0))
			{
				// Копируем данные высоты из буфера в нашу текстуру
				source_lmap_height->copy(buffers->getHeight());
				buffers_rendered = true;
			} else if (buffers_rendered)
			{
				state = State::BEGIN_DRAW;
			}
			break;
		}
		case State::BEGIN_DRAW:
		{
			state = State::DRAWING;
			// Ставим в очередь операцию асинхронного рисования на целевом слое
			// Callback будет вызван, когда GPU будет готов
			Landscape::asyncTextureDraw(target_lmap->getGUID(), {0, 0},
				target_lmap->getResolution());
			break;
		}
		default:
			break;
	}
}

void HeightSlicer::texture_draw_callback(const Unigine::UGUID &guid, int id,
	const Unigine::LandscapeTexturesPtr &buffer, const Unigine::Math::ivec2 &coord, int data_mask)
{
	// Получаем временный рендер-таргет из пула
	auto render_target = Render::getTemporaryRenderTarget();

	// Сохраняем текущее состояние рендеринга для восстановления после нашего рендеринга
	RenderState::saveState();
	RenderState::clearStates();

	// Привязываем выходные текстуры: albedo в слот 0, высота в слот 1
	render_target->bindColorTexture(0, buffer->getAlbedo());
	render_target->bindColorTexture(1, buffer->getHeight());

	render_target->enable();
	{
		// Устанавливаем параметры шейдера для материала нарезки
		slice_material->setTexture("source_height", source_lmap_height);
		// Преобразуем нормализованное slice_height в реальные мировые единицы
		slice_material->setParameterFloat("slice_height", toFloat(slice_height * source_lmap->getExtremumHeight().y));
		// Передаём диапазон высоты для нормализации в шейдере
		slice_material->setParameterFloat("min_height", toFloat(source_lmap->getExtremumHeight().x));
		slice_material->setParameterFloat("max_height", toFloat(source_lmap->getExtremumHeight().y));

		// Выполняем полноэкранный проход шейдера нарезки
		slice_material->renderScreen("landscape_height_slice");
	}
	render_target->disable();
	// Отвязываем текстуры в обратном порядке
	render_target->unbindColorTexture(1);
	render_target->unbindColorTexture(0);

	// Восстанавливаем предыдущее состояние рендеринга
	RenderState::restoreState();
	// Возвращаем рендер-таргет в пул для повторного использования
	Render::releaseTemporaryRenderTarget(render_target);

	// Операция завершена, возвращаемся в состояние ожидания
	state = State::IDLE;
}
