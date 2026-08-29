// Пример WidgetCanvas, демонстрирующий рендеринг 2D-векторной графики.
// Линии, закрашенные полигоны и текст рисуются процедурно с использованием полярных координат.
// 3D-перспективная трансформация создаёт эффект анимированного вращения каждый кадр.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Рендерит анимированную 2D-векторную графику с помощью примитивов WidgetCanvas.
class Canvas : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Canvas, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();

	// Создаёт ломаную линию из полярных координат с заданным количеством вершин
	int create_line(int order, float x, float y, float radius, int num, float angle);
	// Создаёт закрашенный полигон из полярных координат с заданным количеством вершин
	int create_polygon(int order, float x, float y, float radius, int num, float angle);
	// Создаёт текстовый элемент в заданной позиции экрана
	int create_text(int order, float x, float y, Unigine::String string);

	// Виджет canvas для рендеринга 2D-примитивов
	Unigine::WidgetCanvasPtr canvas;
};