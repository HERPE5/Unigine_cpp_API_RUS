// Демонстрирует создание пользовательских виджетов через наследование от WidgetExternBase. MyWidget рендерит
// текст с эффектом 3D-поворота, применяемым через setTransform. Показаны два способа создания:
// прямая конструкция и фабрика через регистрацию ID класса WidgetExtern.

#include "ExternWidget.h"

REGISTER_COMPONENT(ExternWidget);

using namespace Unigine;
using namespace Math;

// Виджет инициализируется с контекстом GUI, текстовым содержимым и белым цветом по умолчанию.
MyWidget::MyWidget(GuiPtr gui, const char *str)
	: WidgetExternBase(gui)
{
	setTime(0.0f);
	setText(str);
	setColor(vec4(1.0f));
}

// Фабричный конструктор оборачивает существующий виджет; текст задаётся отдельно через setText.
MyWidget::MyWidget(void *widget)
	: WidgetExternBase(widget)
{
	setTime(0.0f);
	setColor(vec4(1.0f));
}

MyWidget::~MyWidget()
{}

// ID класса 1 используется для регистрации фабрики через addClassID<MyWidget>(1).
int MyWidget::getClassID()
{
	return 1;
}


// Время анимации накапливается каждый кадр для вычисления поворота.
void MyWidget::update(float ifps)
{
	time += ifps;
	WidgetExternBase::update(ifps);
}

// Обрабатываются оба типа callback - по умолчанию и при нажатии - для обработки ввода.
void MyWidget::checkCallbacks(int x, int y)
{
	check_default_callbacks(x, y);
	check_pressed_callbacks(x, y);
}

// Размер виджета вычисляется из размеров текста, с учётом минимальных значений по умолчанию.
void MyWidget::arrange()
{
	int width = 0;
	int height = 0;
	// Измеряем текстовую строку для определения требуемого размера
	get_text_unit_size(text.get(), width, height);
	set_width(max(get_default_width(), width));
	set_height(max(get_default_height(), height));
}

// Ширина расширяется, чтобы соответствовать контейнеру; высота остаётся неизменной.
void MyWidget::expand(int width, int height)
{
	set_width(max(width, get_width()));
}

// Текст рендерится с колеблющимся поворотом по оси Y вокруг центра виджета.
void MyWidget::render()
{
	push_transform();
	set_translate(get_position_x(), get_position_y());

	// Точка опоры поворота размещается в горизонтальном центре виджета
	float offset = get_width() / 2.0f;
	// Трансформация: перенос к точке опоры, поворот на основе времени, перенос обратно
	set_transform(translate(vec3(offset, 0.0f, -10.0f)) * rotateY((float)Unigine::Math::sin(time * 2.0f) * 45.0f) * translate(vec3(-offset, 0.0f, 10.0f)));

	render_text(0, 0, color, text.get(), 0, 0);

	pop_transform();
}

// Задаёт смещение фазы анимации для разнесённой во времени анимации между экземплярами.
void MyWidget::setTime(float t)
{
	time = t;
}

// Обновляет отображаемое текстовое содержимое.
void MyWidget::setText(const char *str)
{
	text = str;
}

// Задаёт цвет RGBA для рендеринга текста.
void MyWidget::setColor(const vec4 &c)
{
	color = c;
}

// Создаются два пользовательских виджета: один через прямую конструкцию, один через фабрику.
void ExternWidget::init()
{
	// Регистрируем конструктор класса MyWidget для создания через фабрику
	WidgetExternBase::addClassID<MyWidget>(1);

	EngineWindowViewportPtr main_window = WindowManager::getMainWindow();

	GuiPtr gui = main_window->getGui();

	window = WidgetWindow::create(gui, "WidgetWindow", 4, 4);

	// Способ 1: прямая конструкция с параметром текста
	my_widget_0 = new MyWidget(gui, "My Widget 0");
	window->addChild(my_widget_0->getWidget(), Gui::ALIGN_EXPAND);
	WidgetPtr widget_0 = my_widget_0->getWidget();
	widget_0->setFontSize(48);

	// Способ 2: конструкция через фабрику WidgetExtern с использованием ID класса
	WidgetExternPtr widget_1 = WidgetExtern::create(gui, 1);
	my_widget_1 = static_cast<MyWidget *>(widget_1->getWidgetExtern());
	// Смещение фазы анимации создаёт визуальное отличие между экземплярами
	my_widget_1->setTime(2.0f);
	my_widget_1->setText("My Widget 1");
	// Жёлтый цвет отличает экземпляр, созданный фабрикой
	my_widget_1->setColor(vec4(1.0f, 1.0f, 0.0f, 1.0f));
	widget_1->setFontSize(48);
	window->addChild(widget_1, Gui::ALIGN_EXPAND);

	window->arrange();

	main_window->addChild(window, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);
}

// Пользовательские виджеты удаляются вручную; окно использует очистку через умный указатель.
void ExternWidget::shutdown()
{
	if (my_widget_0)
		delete my_widget_0;

	if (my_widget_1)
		delete my_widget_1;

	window.deleteLater();
}
