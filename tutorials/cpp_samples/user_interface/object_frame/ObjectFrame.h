// Рендерит 2D-рамки выделения вокруг 3D-объектов с помощью WidgetCanvas.
// Углы ограничивающего бокса проецируются в экранное пространство с отсечением по видимости.
// Поддерживает настраиваемый стиль рамки, текст подписи и видимость на основе расстояния.

#pragma once

#include "UnigineComponentSystem.h"

#include <UnigineNode.h>
#include <UnigineVisualizer.h>

// Проецирует границы 3D-объекта на экран и рисует прямоугольную рамку выделения.
class ObjectFrame : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(ObjectFrame, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update, 2);
	COMPONENT_POST_UPDATE(post_update);
	COMPONENT_SHUTDOWN(shutdown);

	// Толщина рамки в пикселях
	PROP_PARAM(Int, border_size, 3);
	// Цвет рамки
	PROP_PARAM(Color, border_color, Unigine::Math::vec4_blue);

	// Текст, отображаемый над рамкой
	PROP_PARAM(String, label_text, "Name");
	// Размер шрифта для подписи
	PROP_PARAM(Int, label_text_size, 15);
	// Толщина обводки текста подписи
	PROP_PARAM(Int, label_text_outline, 1);
	// Цвет текста подписи
	PROP_PARAM(Color, label_text_color, Unigine::Math::vec4_white);

	// Максимальное расстояние, на котором рендерится рамка
	PROP_PARAM(Float, visibility_distance, 40.f);

public:
	// Глобально включает/выключает все рамки объектов
	static void setObjectFramesEnabled(bool enabled);
	// Возвращает, была ли рамка отрендерена в этом кадре
	bool isVisible() const { return is_frame_rendered; }
	// Возвращает JSON с позицией, поворотом узла и экранными границами
	Unigine::JsonPtr getJsonMeta() const;

private:
	void init();
	void update();
	void post_update();
	void shutdown();

	void collect_mesh_bound_box(const Unigine::NodePtr &n);
	bool get_screen_position(int &x, int &y, const Unigine::Math::Vec3 &world_point,
		const Unigine::PlayerPtr &player, const Unigine::Math::ivec2 &screen_size);
	int draw_rectangle(int order, const Unigine::Math::ivec2 &p1, const Unigine::Math::ivec2 &p2);
	bool is_rectangle_on_screen(const Unigine::Math::ivec2 &screen_size,
		const Unigine::Math::ivec2 &min, const Unigine::Math::ivec2 &max);
	bool is_child(const Unigine::NodePtr &n);

private:
	// Общий canvas для всех экземпляров ObjectFrame
	static Unigine::WidgetCanvasPtr canvas;
	// Флаг отслеживания, был ли canvas очищен в этом кадре
	static bool canvas_clean;
	// Счётчик ссылок для управления временем жизни общего canvas
	static int components_count;

	// Объединённый ограничивающий бокс всех дочерних мешей
	Unigine::Math::BoundBox bound_box;
	// Восемь углов ограничивающего бокса
	Unigine::VectorStack<Unigine::Math::vec3, 8> points;
	// Центральная точка ограничивающего бокса в локальном пространстве
	Unigine::Math::vec3 local_center;

	// Квадрат расстояния видимости для быстрого сравнения
	float max_visibility_distance;

	// Была ли рамка успешно отрендерена в этом кадре
	bool is_frame_rendered;
	// Границы отрендеренной рамки в экранном пространстве
	Unigine::Math::ivec2 min_point;
	Unigine::Math::ivec2 max_point;
};
