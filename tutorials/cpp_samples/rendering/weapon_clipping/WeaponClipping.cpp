// Предотвращает прохождение оружия сквозь стены путём рендеринга с отдельной
// near-плоскостью камеры. Оружие рендерится в текстуру после основной сцены,
// затем композитится поверх во время post-materials. Использует настройку с двумя камерами,
// где камера оружия отслеживает трансформацию основной камеры.

#include "WeaponClipping.h"

#include <UnigineBase.h>
#include <UnigineMathLibVec4.h>
#include <UnigineRender.h>
#include <UnigineGame.h>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(WeaponClipping);

using namespace Unigine;
using namespace Math;

// Захватывается мышь; создаются viewport и текстура для рендеринга слоя оружия.
void WeaponClipping::init()
{
	// Сохраняем текущий режим мыши для восстановления при завершении работы
	init_handle = Input::getMouseHandle();
	Input::setMouseHandle(Input::MOUSE_HANDLE_GRAB);

	// Кэшируем размеры окна для расчёта размера текстуры
	ivec2 window_size = WindowManager::getMainWindow()->getSize();
	current_width = window_size.x;
	current_height = window_size.y;

	// Получаем ссылки на игроков из параметров компонента
	player = checked_ptr_cast<Player>(camera.get());
	weapon_player = checked_ptr_cast<Player>(weapon_camera.get());

	// Создаём выделенный viewport для рендеринга только оружия
	viewport = Viewport::create();
	// Включаем и узловое, и мировое освещение для правильного освещения оружия
	viewport->setNodeLightUsage(Viewport::USAGE_NODE_LIGHT | Viewport::USAGE_WORLD_LIGHT);
	// Пропускаем буфер скорости, поскольку слою оружия не нужны векторы движения
	viewport->setSkipFlags(Viewport::SKIP_VELOCITY_BUFFER);

	// Создаём текстуру для хранения отрендеренного слоя оружия
	texture = Texture::create();
	create_texture_2D(*texture);

	// Подписываемся на изменение размера окна для пересоздания текстуры
	WindowManager::getMainWindow()->getEventResized().connect(this,
		&WeaponClipping::update_screen_size);

	// Подписываемся на событие post-materials для композитинга оружия на сцену
	Render::getEventBeginPostMaterials().connect(this, &WeaponClipping::render_callback);
}

// Камера оружия синхронизируется с позицией и ориентацией основной камеры.
void WeaponClipping::update()
{
	// Инвертированный modelview даёт мировую трансформацию; камера оружия точно следует за основной камерой
	weapon_player->setTransform(player->getCamera()->getIModelview());
}

// Создаётся текстура рендер-таргета, соответствующая текущим размерам экрана.
void WeaponClipping::create_texture_2D(Unigine::Texture &in_texture)
{
	// RGBA8 с альфа-каналом для прозрачного фона вокруг оружия
	in_texture.create2D(current_width, current_height, Texture::FORMAT_RGBA8,
		Texture::SAMPLER_FILTER_LINEAR | Texture::SAMPLER_ANISOTROPY_16
			| Texture::FORMAT_USAGE_RENDER);
}

// Текстура пересоздаётся при изменении размеров окна.
void WeaponClipping::update_screen_size()
{
	ivec2 window_size = WindowManager::getMainWindow()->getSize();
	int app_width = window_size.x;
	int app_height = window_size.y;
	if (app_width != current_width || app_height != current_height)
	{
		current_width = app_width;
		current_height = app_height;
		// Пересоздаём текстуру для соответствия новому размеру экрана
		create_texture_2D(*texture);
	}
}

// Режим обработки мыши восстанавливается в исходное состояние.
void WeaponClipping::shutdown()
{
	Input::setMouseHandle(init_handle);
}

// Оружие рендерится в текстуру после завершения обновления основной сцены.
void WeaponClipping::post_update()
{
	// Рендерим оружие только для ожидаемой камеры игрока
	if (Game::getPlayer() != player)
		return;

	RenderState::saveState();
	RenderState::clearStates();
	RenderState::setViewport(0, 0, current_width, current_height);

	// Получаем временный рендер-таргет для слоя оружия
	auto target = Render::getTemporaryRenderTarget();
	target->bindColorTexture(0, texture);

	target->enable();
	{
		// Отключаем блики линз в слое оружия, чтобы избежать визуальных артефактов
		bool flare = Render::isLightsLensFlares();
		Render::setLightsLensFlares(false);

		// Очищаем в прозрачный чёрный, чтобы были видны только пиксели оружия
		RenderState::clearBuffer(RenderState::BUFFER_ALL, Math::vec4_zero);

		// Рендерим оружие с помощью выделенной камеры с собственной near-плоскостью отсечения
		if (texture)
		{
			// Флаг предотвращает рекурсивный рендеринг в render_callback
			is_rendering_weapon = true;
			viewport->renderTexture2D(weapon_player->getCamera(), texture);
			is_rendering_weapon = false;
		}

		Render::setLightsLensFlares(flare);
	}

	target->disable();

	target->unbindColorTexture(0);
	RenderState::restoreState();
}

// Текстура оружия композитится на основной рендер во время фазы post-materials.
void WeaponClipping::render_callback()
{
	// Композитим только для ожидаемой камеры игрока
	if (Game::getPlayer() != player)
		return;

	// Пропускаем композитинг во время рендеринга оружия, чтобы избежать бесконечной рекурсии
	if (is_rendering_weapon)
	{
		return;
	}

	RenderState::saveState();
	RenderState::clearStates();
	RenderState::setViewport(0, 0, current_width, current_height);

	// Привязываем основной цветовой буфер как целевой таргет вывода
	auto target = Render::getTemporaryRenderTarget();
	target->bindColorTexture(0, Renderer::getTextureColor());

	target->enable();
	{
		// Альфа-блендинг накладывает оружие на сцену; прозрачные области показывают сцену насквозь
		RenderState::setBlendFunc(RenderState::BLEND_SRC_ALPHA,
			RenderState::BLEND_ONE_MINUS_SRC_ALPHA);

		// Копируем текстуру оружия на основной рендер с помощью материала копирования
		if (texture)
			Render::renderScreenMaterial("Unigine::render_copy_2d", texture);
	}
	target->disable();

	target->unbindColorTexture(0);
	RenderState::restoreState();
	Render::releaseTemporaryRenderTarget(target);
}
