// Менеджер раскладки вьюпортов 2x2 в стиле CAD. Отображает четыре синхронизированных обзора
// одной сцены: сверху, сбоку, спереди (ортографические) и перспективный.
// Каждый вьюпорт имеет куб ориентации для навигации камерой.

#pragma once

#include <UnigineCamera.h>
#include <UnigineComponentSystem.h>
#include <UniginePlayers.h>
#include <UnigineWidgets.h>

#include <memory>

class ViewportCube;

// Создаёт и управляет четырьмя виджетами вьюпортов в раскладке сетки 2x2.
// Обрабатывает настройку камеры, ортографическую проекцию, ввод перетаскивания-панорамирования,
// изменение размера вьюпорта и позиционирование куба обзора.
class CADLikeView : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CADLikeView, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component creates a CAD-style 2x2 viewport layout with top, perspective, side, and front views, "
							"manages cameras and input, and attaches orientation viewcubes.")

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Игроки, представляющие каждый вьюпорт (задаются в редакторе)
	PROP_PARAM(Node, player_top, "", "", "", "filter=Player");
	PROP_PARAM(Node, player_perspective, "", "", "", "filter=Player");
	PROP_PARAM(Node, player_side, "", "", "", "filter=Player");
	PROP_PARAM(Node, player_front, "", "", "", "filter=Player");

	// Размер ортографической проекции (задаётся в редакторе)
	PROP_PARAM(Float, ortho_width, 3);
	PROP_PARAM(Float, ortho_height, 3);

	// Объект сцены для центрирования кубов обзора (задаётся в редакторе)
	PROP_PARAM(Node, figure);

private:
	void create_viewcubes();
	void init();
	void update();
	void shutdown();

	void update_screen_size();
	void set_dragged_player();
	void set_ortho_projection(float width, float height);
	void update_input();
	void create_viewports();
	void update_viewcubes_position();

private:
	// Виджеты вьюпортов для каждого обзора
	Unigine::WidgetSpriteViewportPtr viewport_top;
	Unigine::WidgetSpriteViewportPtr viewport_perspective;
	Unigine::WidgetSpriteViewportPtr viewport_side;
	Unigine::WidgetSpriteViewportPtr viewport_front;

	// Камеры, соответствующие каждому игроку
	Unigine::CameraPtr camera_top;
	Unigine::CameraPtr camera_perspective;
	Unigine::CameraPtr camera_side;
	Unigine::CameraPtr camera_front;

	// Наложения куба обзора для ориентации
	std::unique_ptr<ViewportCube> viewcube_top;
	std::unique_ptr<ViewportCube> viewcube_perspective;
	std::unique_ptr<ViewportCube> viewcube_side;
	std::unique_ptr<ViewportCube> viewcube_front;

	// Текущий перетаскиваемый игрок для интерактивного перемещения
	Unigine::PlayerPtr dragged_player;

	// Контейнер раскладки для вьюпортов
	Unigine::WidgetGridBoxPtr lay;

	// Закэшированные размеры окна для обработки изменения размера
	int current_width;
	int current_height;

	Unigine::Input::MOUSE_HANDLE last_handle;
};
