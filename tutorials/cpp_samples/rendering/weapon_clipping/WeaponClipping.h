// Предотвращает прохождение оружия от первого лица сквозь стены путём рендеринга
// его в отдельном проходе с собственной near-плоскостью отсечения. Использует
// выделенную камеру оружия, следующую за ориентацией основной камеры.

#pragma once
#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UniginePhysics.h>
#include <UniginePlayers.h>
#include <UnigineViewport.h>
#include <UnigineWidgets.h>

class WeaponClipping : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(WeaponClipping, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_POST_UPDATE(post_update);
	COMPONENT_SHUTDOWN(shutdown);

	// Основная камера сцены
	PROP_PARAM(Node, camera, "", "", "", "filter=Player");
	// Отдельная камера для рендеринга оружия с другим отсечением
	PROP_PARAM(Node, weapon_camera, "", "", "", "filter=Player");

	Unigine::ViewportPtr &getRenderViewport() {
		return viewport;
	}

private:
	void init();
	void update();
	void post_update();
	void shutdown();
	// Обрабатывает изменение размера окна для пересоздания текстуры
	void update_screen_size();
	// Создаёт текстуру рендер-таргета, соответствующую размерам экрана
	void create_texture_2D(Unigine::Texture &in_texture);

	// Callback для композитинга слоя оружия на основной рендер
	void render_callback();

private:
	Unigine::PlayerPtr player;
	// Игрок для прохода рендеринга только оружия
	Unigine::PlayerPtr weapon_player;
	// Viewport для рендеринга слоя оружия
	Unigine::ViewportPtr viewport;
	// Текстура, содержащая отрендеренный слой оружия
	Unigine::TexturePtr texture;

	// Закэшированные размеры экрана для определения изменения размера
	int current_width{ 0 };
	int current_height{ 0 };

	// Флаг для предотвращения рекурсивного рендеринга оружия
	bool is_rendering_weapon{false};
	// Сохранённый режим обработки мыши для восстановления
	Unigine::Input::MOUSE_HANDLE init_handle;
};
