// Создаёт раскладку разделённого экрана с двумя видами камер, рендерящимися в текстуры.
// Верхний и нижний viewport'ы отображаются как виджеты на экране и
// на игровых объектах-дисплеях (TV) для гоночной игры.

#pragma once

#include <UnigineCamera.h>
#include <UnigineComponentSystem.h>
#include <UnigineViewport.h>
#include <UnigineWidgets.h>

class SplitScreenTexture : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SplitScreenTexture, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Камеры игроков для верхнего и нижнего видов
	PROP_PARAM(Node, camera_top, "", "", "", "filter=Player");
	PROP_PARAM(Node, camera_bottom, "", "", "", "filter=Player");
	// Игровые объекты-дисплеи для вида каждого игрока
	PROP_PARAM(Node, display_player1, "", "", "", "filter=ObjectMeshStatic");
	PROP_PARAM(Node, display_player2, "", "", "", "filter=ObjectMeshStatic");

private:
	void init();
	void update();
	void shutdown();
	// Обрабатывает события изменения размера окна
	void update_screen_size();
	// Создаёт текстуру рендер-таргета с текущими размерами экрана
	void create_texture_2D(Unigine::Texture &texture);
	void init_gui();
	void create_about();
	Unigine::WidgetLabelPtr setup_label(Unigine::GuiPtr gui, const char *text);
	void update_labels_pos();
	// Назначает отрендеренную текстуру материалу объекта-дисплея
	static void bind_texture(const Unigine::NodePtr &tv_display,
		const Unigine::TexturePtr &texture);

private:
	// Виджеты на экране, отображающие каждый viewport
	Unigine::WidgetSpritePtr widget_top;
	Unigine::WidgetSpritePtr widget_bottom;
	// Камеры, извлечённые из узлов игроков
	Unigine::CameraPtr cached_camera_top;
	Unigine::CameraPtr cached_camera_bottom;
	// Текстуры рендер-таргета для каждого вида
	Unigine::TexturePtr texture_top;
	Unigine::TexturePtr texture_bottom;
	// Viewport'ы для рендеринга вне экрана
	Unigine::ViewportPtr viewport_top;
	Unigine::ViewportPtr viewport_bottom;
	// Подписи с подсказками управления
	Unigine::WidgetLabelPtr wasd_label;
	Unigine::WidgetLabelPtr arrows_label;
	Unigine::WidgetVBoxPtr lay;
	// Закэшированные размеры окна для определения изменения размера
	int current_height;
	int current_width;
};
