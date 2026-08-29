// Рендерит 2D-рамки выделения вокруг 3D-объектов с помощью WidgetCanvas. Ограничивающий бокс
// проецируется в экранное пространство, видимость проверяется через пересечение луча, рамки
// рисуются с настраиваемыми границами и подписями. Поддерживает отсечение по расстоянию.

#include "ObjectFrame.h"

#include <UnigineGame.h>
#include <UnigineViewport.h>

REGISTER_COMPONENT(ObjectFrame)


using namespace Unigine;
using namespace Math;

// Статические члены, общие для всех экземпляров ObjectFrame
Unigine::WidgetCanvasPtr ObjectFrame::canvas;
bool ObjectFrame::canvas_clean;
int ObjectFrame::components_count = 0;

// Собирается ограничивающий бокс, при необходимости создаётся общий canvas.
void ObjectFrame::init()
{
	components_count++;
	// Временно сбрасываем трансформацию для вычисления бокса в локальном пространстве
	auto init_transform = node->getWorldTransform();
	node->setWorldTransform(Mat4(Math::scale(node->getScale())));
	collect_mesh_bound_box(node);

	// Извлекаем восемь угловых точек из ограничивающего бокса
	points.resize(8);
	bound_box.getPoints(points.get(), 8);

	local_center = bound_box.getCenter();
	node->setWorldTransform(init_transform);

	// Создаём общий canvas при инициализации первого компонента
	if (!canvas)
	{
		auto gui = Gui::getCurrent();
		canvas = WidgetCanvas::create(gui);
		gui->addChild(canvas, Gui::ALIGN_OVERLAP | Gui::ALIGN_EXPAND);
		canvas_clean = false;
	}

	// Предварительно вычисляем квадрат расстояния для более быстрого сравнения
	max_visibility_distance = visibility_distance * visibility_distance;
}

// Ограничивающий бокс проецируется, проверяется видимость, рисуется рамка.
void ObjectFrame::update()
{
	auto window = WindowManager::getMainWindow();
	auto player = Game::getPlayer();
	if (!window || !player)
		return;

	is_frame_rendered = false;
	// Очищаем canvas один раз за кадр (первый обновляющийся компонент его очищает)
	if (!canvas_clean)
	{
		canvas_clean = true;
		canvas->clear();
	}
	// Ранний выход, если объект слишком далеко от игрока
	float distance = (node->getWorldPosition() - player->getWorldPosition()).length2();
	if (distance > max_visibility_distance)
		return;

	// Инициализируем экранные границы для расширения спроецированными точками
	auto screen_size = window->getClientSize();
	min_point = {screen_size.x, screen_size.y};
	max_point = {0, 0};

	// Проецируем все восемь углов ограничивающего бокса в экранное пространство
	int x, y;
	bool visible = false;
	auto transform = node->getWorldTransform();
	for (const auto &point : points)
	{
		visible |= get_screen_position(x, y, Vec3(transform * point), player, screen_size);
		min_point.x = Math::min(min_point.x, x);
		min_point.y = Math::min(min_point.y, y);
		max_point.x = Math::max(max_point.x, x);
		max_point.y = Math::max(max_point.y, y);
	}

	// Пропускаем, если все точки за камерой или рамка вне экрана
	if (!visible || !is_rectangle_on_screen(screen_size, min_point, max_point))
		return;

	// Трассировка луча для проверки, не заслонён ли объект другой геометрией
	auto world_center = transform * local_center;
	auto obj = World::getIntersection(player->getWorldPosition(), Vec3(world_center), ~0);
	if (!obj || !is_child(obj))
		return;

	// Порядок рисования на основе расстояния (более близкие объекты рисуются поверх)
	int order = int(-distance * 100);
	ivec2 minmax_point = ivec2{min_point.x, max_point.y};
	ivec2 maxmin_point = ivec2{max_point.x, min_point.y};

	// Рисуем четыре прямоугольника границы (слева, сверху, справа, снизу)
	draw_rectangle(order, minmax_point, min_point - ivec2{border_size});
	draw_rectangle(order, min_point, maxmin_point + ivec2{1, -1} * border_size);
	draw_rectangle(order, maxmin_point, max_point + ivec2{border_size});
	draw_rectangle(order, max_point, minmax_point + ivec2{-1, 1} * border_size);

	// Рисуем заголовок подписи над рамкой
	int text_id = canvas->addText(order + 1);
	canvas->setFontSize(label_text_size);
	ivec2 text_size = canvas->toUnitSize(canvas->getTextRenderSize(label_text));

	auto header_point_min = min_point - ivec2{border_size};
	auto header_point_max = header_point_min + ivec2{text_size.x, -text_size.y}
		+ ivec2{2, -1} * border_size;
	draw_rectangle(order, header_point_min, header_point_max);

	// Настраиваем и позиционируем текст подписи
	canvas->setTextPosition(text_id, vec2(min_point.x, header_point_max.y));
	canvas->setTextText(text_id, label_text);
	canvas->setTextSize(text_id, label_text_size);
	canvas->setTextAlign(text_id, Gui::ALIGN_LEFT | Gui::ALIGN_BOTTOM | Gui::ALIGN_BACKGROUND);
	canvas->setTextColor(text_id, label_text_color);
	canvas->setTextOutline(text_id, label_text_outline);

	is_frame_rendered = true;
}

// Флаг очистки canvas сбрасывается после обновления всех компонентов.
void ObjectFrame::post_update()
{
	if (canvas_clean)
		canvas_clean = false;
}

// Общий canvas уничтожается при завершении работы последнего компонента.
void ObjectFrame::shutdown()
{
	components_count--;
	if (components_count == 0 && (canvas || !canvas.isDeleted()))
	{
		canvas.deleteLater();
		canvas = nullptr;
	}
}

// Рекурсивно собирает ограничивающие боксы из всех дочерних мешей.
void ObjectFrame::collect_mesh_bound_box(const NodePtr &n)
{
	if (!n)
		return;

	int type = n->getType();
	// Следуем по NodeReference к узлу-ссылке
	if (type == Node::NODE_REFERENCE)
		collect_mesh_bound_box(static_ptr_cast<NodeReference>(n)->getReference());
	// Расширяем ограничивающий бокс для типов мешей
	else if (type == Node::OBJECT_MESH_STATIC || type == Node::OBJECT_MESH_SKINNED
		|| type == Node::OBJECT_MESH_DYNAMIC)
	{
		bound_box.expand(n->getBoundBox());
	}

	// Рекурсивно обрабатываем дочерние узлы
	for (int i = 0; i < n->getNumChildren(); i++)
		collect_mesh_bound_box(n->getChild(i));
}

// Проецирует мировую точку в экранные координаты, возвращает true, если перед камерой.
bool ObjectFrame::get_screen_position(int &x, int &y, const Vec3 &world_point,
	const Unigine::PlayerPtr &player, const Unigine::Math::ivec2 &screen_size)
{
	float width = itof(screen_size.x);
	float height = itof(screen_size.y);

	// Применяем матрицы проекции и modelview
	mat4 projection = player->getProjection();
	mat4 modelview = mat4(player->getCamera()->getModelview());
	projection.m00 *= height / width;

	Vec4 p = projection * Vec4(modelview * Vec4(world_point, 1));
	if (p.w > 0)
	{
		// Точка перед камерой - вычисляем позицию на экране
		x = (static_cast<float>(width * (0.5f + p.x * 0.5f / p.w)));
		y = (static_cast<float>(height - height * (0.5f + p.y * 0.5f / p.w)));
		return true;
	}
	else
	{
		// Точка за камерой - зеркалируем координаты
		x = (width - static_cast<float>(width * (0.5f + p.x * 0.5f / p.w)));
		y = (height - static_cast<float>(height - height * (0.5f + p.y * 0.5f / p.w)));
		return false;
	}
}

// Рисует закрашенный прямоугольный полигон на canvas.
int ObjectFrame::draw_rectangle(int order, const ivec2 &p1, const ivec2 &p2)
{
	int id = canvas->addPolygon(order);

	// Определяем четыре угла прямоугольника
	canvas->addPolygonPoint(id, vec3(p1.x, p1.y, 0));
	canvas->addPolygonPoint(id, vec3(p1.x, p2.y, 0));
	canvas->addPolygonPoint(id, vec3(p2.x, p2.y, 0));
	canvas->addPolygonPoint(id, vec3(p2.x, p1.y, 0));
	// Определяем два треугольника для заполнения прямоугольника
	canvas->addPolygonIndex(id, 0);
	canvas->addPolygonIndex(id, 1);
	canvas->addPolygonIndex(id, 2);
	canvas->addPolygonIndex(id, 2);
	canvas->addPolygonIndex(id, 3);
	canvas->addPolygonIndex(id, 0);

	canvas->setPolygonColor(id, border_color);
	return id;
}

// Возвращает true, если прямоугольник перекрывает видимую область экрана.
bool ObjectFrame::is_rectangle_on_screen(const Unigine::Math::ivec2 &screen_size, const ivec2 &min,
	const ivec2 &max)
{
	// Проверяем, находится ли прямоугольник полностью за пределами какого-либо края экрана
	if ((min.x <= 0 && max.x <= 0) || (min.x >= screen_size.x && max.x >= screen_size.x)
		|| (min.y <= 0 && max.y <= 0) || (min.y >= screen_size.y && max.y >= screen_size.y))
		return false;
	return true;
}

// Рекурсивно проверяет, является ли узел узлом этого компонента или его дочерним.
bool ObjectFrame::is_child(const Unigine::NodePtr &n)
{
	if (n == node)
		return true;
	auto parent = n->getParent();
	// Проверяем possessor для узлов внутри NodeReference
	if (!parent)
		parent = n->getPossessor();
	return parent ? is_child(parent) : false;
}

// Глобально показывает или скрывает все рамки объектов, добавляя/удаляя canvas из GUI.
void ObjectFrame::setObjectFramesEnabled(bool enabled)
{
	if (!canvas)
		return;

	auto gui = Gui::getCurrent();
	if (enabled)
		gui->addChild(canvas, Gui::ALIGN_OVERLAP | Gui::ALIGN_EXPAND | Gui::ALIGN_BACKGROUND);
	else
		gui->removeChild(canvas);
}

// Возвращает объект JSON, содержащий метаданные узла и экранные границы.
JsonPtr ObjectFrame::getJsonMeta() const
{
	JsonPtr json = Json::create();
	json->setObject();
	json->addChild("node_id", node->getID());
	json->addChild("node_name", node->getName());

	// Добавляем мировую позицию
	auto pos = node->getWorldPosition();
	auto pos_json = json->addChild("position");
	pos_json->setObject();
	pos_json->addChild("x", pos.x);
	pos_json->addChild("y", pos.y);
	pos_json->addChild("z", pos.z);

	// Добавляем углы мирового поворота
	auto rot = node->getWorldRotation();
	auto rot_json = json->addChild("rotation");
	rot_json->setObject();
	rot_json->addChild("x", rot.getAngle(vec3_right));
	rot_json->addChild("y", rot.getAngle(vec3_forward));
	rot_json->addChild("z", rot.getAngle(vec3_up));

	// Добавляем границы рамки в экранном пространстве
	auto min_frame_json = json->addChild("screen_position");
	min_frame_json->setObject();
	min_frame_json->addChild("min_x", min_point.x);
	min_frame_json->addChild("min_y", min_point.y);
	min_frame_json->addChild("max_x", max_point.x);
	min_frame_json->addChild("max_y", max_point.y);

	return json;
}
