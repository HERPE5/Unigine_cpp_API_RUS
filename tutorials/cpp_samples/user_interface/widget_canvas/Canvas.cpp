// Демонстрирует WidgetCanvas для рендеринга 2D-векторной графики. Линии, полигоны и текст
// создаются процедурно с использованием полярных координат. 3D-перспективная трансформация применяется
// каждый кадр для создания эффекта вращения с помощью манипуляции матрицей проекции.

#include "Canvas.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(Canvas);

using namespace Unigine;
using namespace Math;

// Виджет canvas создаётся и заполняется различными геометрическими примитивами.
void Canvas::init()
{
	EngineWindowViewportPtr main_window = WindowManager::getMainWindow();
	GuiPtr gui = main_window->getGui();

	canvas = WidgetCanvas::create(gui);

	// Перекрывающиеся треугольная, квадратная и пятиугольная линейные фигуры в одной позиции
	canvas->setLineColor(create_line(0, 200.0f, 200.0f, 100.0f, 3, 360.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f));
	canvas->setLineColor(create_line(0, 200.0f, 200.0f, 100.0f, 4, 360.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f));
	canvas->setLineColor(create_line(0, 200.0f, 200.0f, 100.0f, 5, 360.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));

	// Спиральная линия создаётся с помощью угла > 360 градусов с большим количеством вершин
	canvas->setLineColor(create_line(0, 800.0f, 400.0f, 100.0f, 16, 360.0f * 9.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// Слоёные полигоны: треугольник поверх шестиугольника (порядок определяет приоритет рисования)
	canvas->setPolygonColor(create_polygon(0, 600.0f, 200.0f, 100.0f, 6, 360.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	canvas->setPolygonColor(create_polygon(1, 600.0f, 200.0f, 100.0f, 3, 360.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f));

	// Слоёные полигоны: квадрат поверх восьмиугольника
	canvas->setPolygonColor(create_polygon(0, 400.0f, 400.0f, 100.0f, 8, 360.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f));
	canvas->setPolygonColor(create_polygon(1, 400.0f, 400.0f, 100.0f, 4, 360.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));

	create_text(0, 200.0f - 64.0f, 200.0f - 30.0f, "This is C++ canvas text");

	main_window->addChild(canvas, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);
}

// Применяется 3D-перспективная трансформация для создания эффекта анимации вращения.
void Canvas::update()
{
	GuiPtr gui = WindowManager::getMainWindow()->getGui();

	float fov = 2.0f;
	float time = Game::getTime();
	float x = gui->getWidth() / 2.0f;
	float y = gui->getHeight() / 2.0f;
	// Цепочка трансформаций: перенос в центр, применение перспективы, поворот по осям Y и X, перенос обратно
	canvas->setTransform(translate(vec3(x, y, 0.0f)) * perspective(fov, 1.0f, 0.01f, 100.0f) * rotateY(sinf(time)) * rotateX(cosf(time * 0.5f)) * translate(vec3(-x, -y, -1.0f / tanf(fov * Consts::DEG2RAD * 0.5f))));
}

// Виджет canvas освобождается.
void Canvas::shutdown()
{
	canvas.deleteLater();
}

// Ломаная линия генерируется путём равномерного распределения точек вокруг центра с помощью полярной математики.
int Canvas::create_line(int order, float x, float y, float radius, int num, float angle)
{
	int line = canvas->addLine(order);
	for (int i = 0; i <= num; i++)
	{
		// Преобразуем полярные координаты в позицию на экране
		float s = Unigine::Math::sin(angle / num * Consts::DEG2RAD * i) * radius + x;
		float c = Unigine::Math::cos(angle / num * Consts::DEG2RAD * i) * radius + y;
		canvas->addLinePoint(line, vec3(s, c, 0.0f));
	}
	return line;
}

// Закрашенный полигон генерируется с использованием вершин правильного n-угольника, вычисленных из полярных координат.
int Canvas::create_polygon(int order, float x, float y, float radius, int num, float angle)
{
	int polygon = canvas->addPolygon(order);
	for (int i = 0; i < num; i++)
	{
		// Каждая вершина размещается через равные угловые интервалы
		float s = Unigine::Math::sin(angle / num * Consts::DEG2RAD * i) * radius + x;
		float c = Unigine::Math::cos(angle / num * Consts::DEG2RAD * i) * radius + y;
		canvas->addPolygonPoint(polygon, vec3(s, c, 0.0f));
	}
	return polygon;
}

// Текстовый элемент создаётся в заданной позиции с указанным содержимым строки.
int Canvas::create_text(int order, float x, float y, Unigine::String string)
{
	int text = canvas->addText(order);
	canvas->setTextPosition(text, vec2(x, y));
	canvas->setTextText(text, string.getRaw());
	return text;
}
