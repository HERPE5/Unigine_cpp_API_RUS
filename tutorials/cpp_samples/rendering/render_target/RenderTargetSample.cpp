// Демонстрирует рисование текстуры в стиле декалей. Клик по объекту рисует
// спрайты в точке UV-пересечения. Использует render target для компоновки
// спрайтов на постоянной текстуре, обновляющей albedo стены.

#include "RenderTargetSample.h"

#include <UnigineGame.h>

using namespace Unigine;
using namespace Math;

constexpr float DRAW_TIMEOUT = 0.5f;
const vec4 SPRITE_COLOR = {0.f, 0.f, 1.f, 0.7f, ConstexprTag{}};

REGISTER_COMPONENT(RenderTargetSample)

// Текстуры спрайтов загружаются; albedo стены копируется в текстуры render target.
void RenderTargetSample::init()
{
	// Загружаем все изображения спрайтов из путей к файлам в GPU-текстуры
	for (int i = 0; i < sprites.size(); i++)
	{
		String sprite_path = sprites[i].get();
		TexturePtr sprite_texture = Texture::create();
		sprite_texture->load(sprite_path);
		sprite_textures.push_back(std::move(sprite_texture));
	}

	// Получаем объект стены и наследуем его материал, чтобы изменения не влияли на другие экземпляры
	wall = checked_ptr_cast<Object>(wall_param.get());
	wall_material = wall->getMaterialInherit(0);

	// Загружаем исходную текстуру albedo как CPU-изображение (для размеров и сброса)
	wall_albedo = Image::create();
	wall_albedo->load(wall_material->getTexturePath(wall_material->findTexture("albedo")));

	countdown = DRAW_TIMEOUT;

	const int width = wall_albedo->getWidth();
	const int height = wall_albedo->getHeight();

	render_target = RenderTarget::create();

	// Фоновая текстура хранит накопленные спрайты (сохраняется между кадрами)
	background_texture = Texture::create();
	background_texture->create2D(width, height, Texture::FORMAT_RGBA8,
		Texture::FORMAT_USAGE_RENDER);

	// Преобразуем CPU-изображение в GPU-текстуру и копируем в фон
	const TexturePtr albedo_texture = Texture::create();
	albedo_texture->create(wall_albedo);
	copy_texture(background_texture, albedo_texture);

	// Результирующая текстура - это то, что фактически отображает стена (обновляется после каждой отрисовки спрайта)
	result_texture = Texture::create();
	result_texture->create2D(width, height, Texture::FORMAT_RGBA8, Texture::FORMAT_USAGE_RENDER);

	// Инициализируем результат содержимым фона и назначаем материалу стены
	copy_texture(result_texture, background_texture);
	wall_material->setTexture(wall_material->findTexture("albedo"), result_texture);
}

// Клики мыши рисуют спрайты в точке UV-пересечения; случайные спрайты добавляются периодически.
void RenderTargetSample::update()
{
	// Обрабатываем рисование по клику мыши
	if (Input::isMouseButtonDown(Input::MOUSE_BUTTON_LEFT))
	{
		// Выпускаем луч от камеры через позицию мыши
		Vec3 p0, p1;
		PlayerPtr player = Game::getPlayer();
		player->getDirectionFromMainWindow(p0, p1, Input::getMousePosition().x,
			Input::getMousePosition().y);

		// Преобразуем луч в локальное пространство стены для проверки пересечения
		Vec3 wall_p0 = wall->getIWorldTransform() * p0;
		Vec3 wall_p1 = wall->getIWorldTransform() * p1;

		// Проверяем, попадает ли луч в стену, и получаем UV-координаты в точке попадания
		ObjectIntersectionTexCoordPtr intersection = ObjectIntersectionTexCoord::create();
		if (wall->getIntersection(wall_p0, wall_p1, ~0, intersection, nullptr))
		{
			vec4 tex_coord = intersection->getTexCoord();
			draw_sprite(tex_coord.x, tex_coord.y);
		}
	}

	// Автоматически создаём спрайты в случайных позициях каждые DRAW_TIMEOUT секунд
	countdown -= Game::getIFps();
	if (countdown <= 0.0f)
	{
		float x = Game::getRandomFloat(0.0, 1.0f);
		float y = Game::getRandomFloat(0.0, 1.0f);
		draw_sprite(x, y);
		countdown = DRAW_TIMEOUT;
	}
}

// Render target и все созданные текстуры освобождаются.
void RenderTargetSample::shutdown()
{
	render_target->destroy();
	render_target.clear();

	for (int i = 0; i < sprite_textures.size(); i++)
	{
		if (sprite_textures[i])
		{
			sprite_textures[i]->destroy();
			sprite_textures[i].clear();
		}
	}

	background_texture->destroy();
	background_texture.clear();

	result_texture->destroy();
	result_texture.clear();
}

// Полноэкранный блит из источника в приёмник с использованием встроенного материала копирования.
void RenderTargetSample::copy_texture(const TexturePtr &dest, const TexturePtr &src) const
{
	// Сохраняем текущее состояние рендеринга для восстановления после нашей операции
	RenderState::saveState();
	RenderState::clearStates();

	// Устанавливаем текстуру назначения как вывод render target
	render_target->bindColorTexture(0, dest);
	render_target->enable();
	{
		// Используем встроенный шейдер копирования движка для простого блита текстуры
		MaterialPtr material = Materials::findManualMaterial("Unigine::render_copy_2d");
		if (material)
		{
			int color_id = material->findTexture("color");
			material->setTexture(color_id, src);
			// Полноэкранный квад рендерит исходную текстуру в приёмник
			material->renderScreen(Render::PASS_POST);
			material->setTexture(color_id, nullptr);
		}
	}
	render_target->disable();
	render_target->unbindColorTextures();
	RenderState::restoreState();
}

// Спрайт трансформируется в UV-позицию и смешивается на результирующей текстуре.
void RenderTargetSample::draw_sprite(float uv_x, float uv_y)
{
	// Принудительно компилируем шейдер при необходимости и получаем дескриптор шейдера
	ShaderPtr shader = draw_sprite_material->getShaderForce(Render::PASS_POST);
	if (!shader)
	{
		return;
	}

	// Выбираем случайный спрайт из загруженных текстур
	TexturePtr sprite_texture = sprite_textures[Game::getRandomInt(0, sprite_textures.size() - 1)];

	// Преобразуем UV [0..1] в пространство отсечения [-1..1], учитывая переворот по Y на некоторых платформах
	const float flip_sign = (Render::isFlipped() ? -1.0f : 1.0f);
	const float translate_x = 2.0f * uv_x - 1.0f;
	const float translate_y = flip_sign * (2.0f * uv_y - 1.0f);

	// Масштабируем спрайт для сохранения его размера в пикселях относительно фоновой текстуры
	const float scale_x = itof(sprite_texture->getWidth()) / itof(background_texture->getWidth());
	const float scale_y = itof(sprite_texture->getHeight()) / itof(background_texture->getHeight());

	// Строим матрицу трансформации: сначала масштаб, затем перемещение в UV-позицию
	const mat4 transform = translate(translate_x, translate_y, 0.0f)
		* scale(scale_x, scale_y, 1.0f);

	RenderState::saveState();
	RenderState::clearStates();

	// Рендерим в результирующую текстуру (спрайт компонуется поверх фона)
	render_target->bindColorTexture(0, result_texture);
	render_target->enable();
	{
		// Задаём параметры шейдера для позиционирования спрайта и цвета оттенка
		shader->bind();
		shader->setParameterFloat4x4("ss_transform", transform);
		shader->setParameterFloat4("ss_color", SPRITE_COLOR);
		shader->flushParameters();

		// Слот 0: фон для сохранения, Слот 1: спрайт для смешивания сверху
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 0, background_texture);
		RenderState::setTexture(RenderState::BIND_FRAGMENT, 1, sprite_texture);
		draw_sprite_material->renderScreen(Render::PASS_POST);
	}
	render_target->disable();
	render_target->unbindColorTextures();
	RenderState::restoreState();

	// Копируем результат обратно в фон, чтобы следующий спрайт рисовался поверх всех предыдущих
	copy_texture(background_texture, result_texture);

	// Генерируем мипмапы для правильной фильтрации на расстоянии
	result_texture->createMipmaps();
}
