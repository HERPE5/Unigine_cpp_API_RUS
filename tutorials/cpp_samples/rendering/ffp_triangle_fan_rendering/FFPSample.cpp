// Пример рендеринга Fixed Function Pipeline (FFP). Отрисовывает вращающийся цветной
// веер с помощью рендеринга треугольников в непосредственном режиме. FFP предоставляет простую 2D/3D
// отрисовку без пользовательских шейдеров, полезен для отладочной визуализации и UI.

#include "FFPSample.h"

#include <UnigineFfp.h>
#include <UnigineGame.h>

using namespace Unigine;
using namespace Unigine::Math;

REGISTER_COMPONENT(FFPSample)

// Подписывается на событие рендеринга после GUI, чтобы рисовать геометрию FFP после UI.
void FFPSample::init()
{
	// Подписываемся на событие "конец рендеринга GUI",
	// чтобы наша функция render() вызывалась после завершения рендеринга движком.
	Engine::get()->getEventEndPluginsGui().connect(*this, &FFPSample::render);
}

// Отрисовывает вращающийся цветной веер с помощью FFP. Настраивает ортографическую проекцию,
// создаёт веер из треугольников из 16 вершин с цветом для каждой вершины.
void FFPSample::render()
{
	Ffp::setTextureSample(1);
	const EngineWindowViewportPtr window = WindowManager::getMainWindow();
	const auto time = Game::getTime();

	// Размер экрана
	const int width = window->getClientRenderSize().x;
	const int height = window->getClientRenderSize().y;
	const float radius = height / 2.0f;

	Ffp::enable(Ffp::MODE_SOLID);
	Ffp::setOrtho(width, height);

	// Начинаем рендеринг треугольников
	// Примитивы и данные вершин нужно указывать между
	// beginTriangles() и endTriangles()
	Ffp::beginTriangles();

	// Цвета вершин
	constexpr unsigned int colors[] = {0xffff0000, 0xff00ff00, 0xff0000ff};

	// Создаём вершины
	constexpr int num_vertex = 16;
	for (int i = 0; i < num_vertex; i++)
	{
		const float angle = Consts::PI2 * i / (num_vertex - 1) - time;
		const float x = width / 2 + sinf(angle) * radius;
		const float y = height / 2 + cosf(angle) * radius;
		Ffp::addVertex(x, y);
		Ffp::setColor(colors[i % 3]);
	}

	// Создаём индексы
	for (int i = 1; i < num_vertex; i++)
	{
		Ffp::addIndex(0);
		Ffp::addIndex(i);
		Ffp::addIndex(i - 1);
	}

	// Завершаем рендеринг треугольников
	Ffp::endTriangles();

	// Отключаем рендеринг FFP
	Ffp::disable();
}
