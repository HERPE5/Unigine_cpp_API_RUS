// Демонстрирует создание пользовательского виджета через наследование от WidgetExternBase. MyWidget
// рендерит анимированный текст с 3D-трансформацией поворота. Показаны два способа создания:
// прямая конструкция и фабрика через регистрацию ID класса.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Пользовательский виджет, рендерящий текст с анимированным эффектом 3D-поворота.
class MyWidget : public Unigine::WidgetExternBase
{
private:
	// Прошедшее время для вычисления фазы анимации
	float time;
	// Текстовое содержимое, отображаемое виджетом
	Unigine::String text;
	// Цвет RGBA, применяемый к отрендеренному тексту
	Unigine::Math::vec4 color;

public:
	// Конструирует виджет с контекстом GUI и начальным текстом
	MyWidget(Unigine::GuiPtr gui, const char *str);
	// Конструирует из существующего указателя на виджет (используется фабрикой)
	MyWidget(void *widget);
	~MyWidget() override;

	// Возвращает уникальный ID класса для регистрации фабрики
	int getClassID() override;

	// Продвигает время анимации каждый кадр
	void update(float ifps) override;

	// Обрабатывает события callback по умолчанию и при нажатии
	void checkCallbacks(int x, int y) override;

	// Вычисляет размер виджета на основе размеров текста
	void arrange() override;
	// Расширяет ширину, чтобы соответствовать родительскому контейнеру
	void expand(int width, int height) override;
	// Рисует текст с анимированной трансформацией 3D-поворота
	void render() override;

	// Задаёт смещение времени анимации
	void setTime(float t);
	// Задаёт текстовое содержимое для отображения
	void setText(const char *str);
	// Задаёт цвет рендеринга текста
	void setColor(const Unigine::Math::vec4 &c);
};

// Компонент, создающий и управляющий пользовательскими экземплярами MyWidget в окне.
class ExternWidget : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ExternWidget, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void shutdown();

	// Виджет, созданный через прямой конструктор
	MyWidget *my_widget_0 = nullptr;
	// Виджет, созданный через фабрику WidgetExtern
	MyWidget *my_widget_1 = nullptr;
	// Окно-контейнер для пользовательских виджетов
	Unigine::WidgetWindowPtr window;
};