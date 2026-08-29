// Демонстрирует ObjectText для рендеринга 3D-текста в мире. Создаются три текстовых объекта:
// редактируемый пользователем текст с настраиваемыми свойствами шрифта, статический форматированный текст
// с HTML-подобной разметкой и динамический текст, циклически меняющий значения цвета каждый кадр.

#include "../../menu_ui/SampleDescriptionWindow.h"
#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

using namespace Unigine;
using namespace Unigine::Math;

// Creates and manages three ObjectText instances demonstrating different use cases.
class ObjectTextSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(ObjectTextSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Текст по умолчанию, отображаемый при пустом вводе пользователя
	PROP_PARAM(String, user_text_if_empty, "Here could be your text...");

	// Скорость изменения компонента цвета в секунду для динамического текста
	PROP_PARAM(Float, color_step, 1.0f);

private:
	// Создаются три экземпляра ObjectText с UI для редактирования первого из них.
	void init()
	{
		color = min_color;

		description_window.createWindow();

		auto &params = description_window.getParameterGridBox();

		// Параметры по умолчанию для редактируемого пользователем текстового объекта
		text_user_pos = Vec3(0, 12, 2);
		vec4 user_color = vec4_white;
		float user_wrap = 32;
		bool user_depth_test = false;
		int user_outline = 0;
		int user_vspacing = 0;
		int user_hspacing = 0;
		int user_resolution = 512;
		int user_size = 128;
		bool user_rich = false;

		// Элементы управления UI для настройки свойств текста с превью в реальном времени
		description_window.addFloatParameter("Wrap width", nullptr, user_wrap, 4, 64, [this](float v) {
			text_user->setTextWrapWidth(v);
			center_text(text_user, text_user_pos);
		});
		description_window.addBoolParameter("Depth test", nullptr, user_depth_test, [this](bool v) {
			text_user->setDepthTest(v);
			center_text(text_user, text_user_pos);
		});
		description_window.addIntParameter("Font outline", nullptr, user_outline, 0, 32, [this](int v) {
			text_user->setFontOutline(v);
			center_text(text_user, text_user_pos);
		});
		description_window.addIntParameter("Vertical spacing", nullptr, user_vspacing, 0, 32, [this](int v) {
			text_user->setFontVSpacing(v);
			center_text(text_user, text_user_pos);
		});
		description_window.addIntParameter("Horizontal spacing", nullptr, user_hspacing, 0, 32, [this](int v) {
			text_user->setFontHSpacing(v);
			center_text(text_user, text_user_pos);
		});
		description_window.addIntParameter("Font resolution", nullptr, user_resolution, 128, 1024, [this](int v) {
			text_user->setFontResolution(v);
			center_text(text_user, text_user_pos);
		});
		description_window.addIntParameter("Font size", nullptr, user_size, 32, 256, [this](int v) {
			text_user->setFontSize(v);
			center_text(text_user, text_user_pos);
		});
		description_window.addBoolParameter("Rich text", nullptr, user_rich, [this](bool v) {
			text_user->setFontRich(v);
			center_text(text_user, text_user_pos);
		});

		// Подпись и прокручиваемый контейнер для многострочного ввода текста
		auto label = WidgetLabel::create("Text");
		params->addChild(label);

		auto scroll_box = WidgetScrollBox::create();
		scroll_box->setWidth(200);
		scroll_box->setHeight(100);
		scroll_box->setVScrollEnabled(true);
		scroll_box->setHScrollEnabled(true);
		params->addChild(scroll_box);

		// Виджет ввода текста обновляет содержимое ObjectText в реальном времени
		auto edit_text = WidgetEditText::create();
		edit_text->setText(user_text_if_empty);
		edit_text->getEventChanged().connect(*this, [this, edit_text]() {
			// Текст-заполнитель отображается, когда ввод очищен
			if (edit_text->getText()[0] != '\0')
			{
				text_user->setText(edit_text->getText());
			}
			else
			{
				text_user->setText(user_text_if_empty);
			}

			center_text(text_user, text_user_pos);
		});
		scroll_box->addChild(edit_text, Gui::ALIGN_EXPAND);

		// Пустая подпись служит вертикальным разделителем
		params->addChild(WidgetLabel::create());

		// Редактируемый пользователем текстовый объект с настраиваемыми через UI свойствами
		text_user = ObjectText::create(font);
		text_user->setTextColor(user_color);
		text_user->setTextWrapWidth(user_wrap);
		text_user->setDepthTest(user_depth_test);
		text_user->setFontOutline(user_outline);
		text_user->setFontVSpacing(user_vspacing);
		text_user->setFontHSpacing(user_hspacing);
		text_user->setFontResolution(user_resolution);
		text_user->setFontSize(user_size);
		text_user->setFontRich(user_rich);
		text_user->setText(user_text_if_empty);
		// Поворот делает текст обращённым вверх для просмотра с плоскости земли
		text_user->setWorldRotation(quat(90, 0, 0));
		center_text(text_user, text_user_pos);

		// Статический форматированный текст, демонстрирующий HTML-подобную разметку
		text_static_rich = ObjectText::create(font);
		text_static_rich->setTextWrapWidth(5);
		text_static_rich->setFontSize(user_size);
		text_static_rich->setFontRich(true);
		text_static_rich->setText(R"(
<font size=62 color=#888888>— feed begins —</font><br/>

<p align=left>
<font color=#ff0000 size=78 outline=#000000><b>viewer2431234</b></font><br/>
<font size=70><b>It’s me—your only viewer.</b></font><br/>
<font size=66><i>For years I sustained the <b>illusion</b> that you had many viewers, but it was only me.</i></font><br/>
<font size=66>I’ll now send this message from all my accounts.</font>
</p>

<font color=#444444 size=66>—————————————</font><br/>

<p align=left>
<font color=#00ff00 size=78 outline=#000000><b>viewer4243553</b></font><br/>
<font size=70><b>It’s me—your only viewer.</b></font><br/>
<font size=66><i>For years I sustained the <b>illusion</b> that you had many viewers, but it was only me.</i></font><br/>
<font size=66>I’ll now send this message from all my accounts.</font>
</p>

<br/><font size=62 color=#888888>— feed ends —</font>
)");
		// Угловой поворот для визуального разнообразия в демонстрации
		text_static_rich->setWorldRotation(quat(90, 45, 0));
		center_text(text_static_rich, Vec3(-10, 12, 2));

		// Динамический текст, отображающий и циклически меняющий значения цвета
		text_dynamic_change = ObjectText::create(font);
		text_dynamic_change->setFontSize(user_size);
		text_dynamic_change->setTextColor(color);
		text_dynamic_change->setText(get_dynamic_text_color_str());
		text_dynamic_change->setWorldRotation(quat(90, -45, 0));
		center_text(text_dynamic_change, Vec3(10, 12, 2));
	}

	// Компонент цвета анимируется, текст обновляется каждый кадр.
	void update()
	{
		// Текущие границы компонента цвета для анимации
		auto min_comp = min_color.v[color_index];
		auto max_comp = max_color.v[color_index];
		auto &comp = color.v[color_index];

		// Интерполируем компонент цвета на основе прошедшего времени
		comp += color_mult * color_step * Game::getIFps();

		// Направление меняется на противоположное при достижении границ
		if (comp <= min_comp || comp >= max_comp)
		{
			comp = clamp(comp, min_comp, max_comp);
			// Случайный компонент выбирается для следующего цикла анимации
			if (color_index != 3 || comp >= max_comp)
			{
				color_index = randInt(0, 4);
			}
			color_mult = comp >= max_comp ? -1 : 1;
		}

		// Визуальная обратная связь показывает текущие значения цвета в реальном времени
		text_dynamic_change->setTextColor(color);
		text_dynamic_change->setText(get_dynamic_text_color_str());
	}

	// Все экземпляры ObjectText и ресурсы UI освобождаются.
	void shutdown()
	{
		text_dynamic_change.deleteLater();
		text_static_rich.deleteLater();
		text_user.deleteLater();
		description_window.shutdown();
	}

	// Возвращается форматированное строковое представление текущих значений цвета RGBA.
	String get_dynamic_text_color_str() const
	{
		return String::format("Current color: %.2f %.2f %.2f %.2f", color.x, color.y, color.z, color.w);
	}

	// Текстовый объект перепозиционируется так, чтобы его визуальный центр совпадал с точкой опоры.
	static void center_text(const ObjectTextPtr &text, const Vec3 &pivot)
	{
		// Локальные оси учитывают поворот текста в мировом пространстве
		auto right = text->getWorldDirection(AXIS_X);
		auto up = text->getWorldDirection(AXIS_NY);
		// Позиция смещается на половину размеров для достижения центрирования
		text->setWorldPosition(pivot - Vec3(right * (text->getTextWidth() / 2) + up * (text->getTextHeight() / 2)));
	}

private:
	// Окно UI для элементов управления параметрами
	SampleDescriptionWindow description_window;
	// Редактируемый пользователем текст с настраиваемыми свойствами шрифта
	ObjectTextPtr text_user;
	// Мировая позиция, используемая для центрирования пользовательского текста
	Vec3 text_user_pos;
	// Статический текст, демонстрирующий возможности форматирования
	ObjectTextPtr text_static_rich;
	// Динамический текст с анимированными значениями цвета
	ObjectTextPtr text_dynamic_change;

	// Файл шрифта, используемый для всех текстовых объектов
	const char *font = "font.ttf";
	// Текущий анимированный цвет для динамического текста
	vec4 color;
	// Нижняя граница для анимации компонента цвета
	vec4 min_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	// Верхняя граница для анимации компонента цвета
	vec4 max_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// Множитель направления анимации (1 = увеличение, -1 = уменьшение)
	float color_mult = 1;
	// Индекс анимируемого компонента цвета (0=R, 1=G, 2=B, 3=A)
	int color_index = 0;
};

REGISTER_COMPONENT(ObjectTextSample);
