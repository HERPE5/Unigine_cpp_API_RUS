// Демонстрирует поведение переключателя (radio button) с использованием WidgetCheckBox и addAttach.
// Присоединение чекбоксов создаёт взаимное исключение, так что можно выбрать только один
// одновременно. Изменения выбора отображаются в оверлее консоли.

#include "RadioButtons.h"
#include <UnigineConsole.h>

REGISTER_COMPONENT(RadioButtons)

using namespace Unigine;

// Переключатели создаются как присоединённые чекбоксы в вертикальной компоновке с callback изменения.
void RadioButtons::init()
{
	auto gui = WindowManager::getMainWindow()->getGui();

	p_vertical_layout = WidgetVBox::create(horizontal_layout_space.get(), vertical_layout_space.get());

	gui->addChild(p_vertical_layout, Gui::ALIGN_OVERLAP);

	p_vertical_layout->setPosition(widget_position.get().x, widget_position.get().y);
	p_vertical_layout->setBackground(1);

	// Создаём первый переключатель и делаем его изначально выбранным
	p_first_rbutton = WidgetCheckBox::create(first_rbutton_text.get());
	p_first_rbutton->setChecked(true);

	p_vertical_layout->addChild(p_first_rbutton, Gui::ALIGN_LEFT);

	p_first_rbutton->setFontSize(font_size.get());

	// Callback-лямбда отображает сообщение выбора для первого варианта
	p_first_rbutton->getEventChanged().connect(*this, [this]() {
		if (p_first_rbutton->isChecked())
			Console::onscreenMessageLine("Radio buttons: first option");
	});

	// Создаём второй переключатель
	p_second_rbutton = WidgetCheckBox::create(second_rbutton_text.get());

	p_vertical_layout->addChild(p_second_rbutton, Gui::ALIGN_LEFT);
	// Присоединяем второй чекбокс к первому для взаимного исключения
	p_first_rbutton->addAttach(p_second_rbutton);

	p_second_rbutton->setFontSize(font_size.get());

	// Callback-лямбда отображает сообщение выбора для второго варианта
	p_second_rbutton->getEventChanged().connect(*this, [this]() {
		if (p_second_rbutton->isChecked())
			Console::onscreenMessageLine("Radio buttons: second option");
	});


	Console::setOnscreen(true);
}

// Контейнер компоновки и дочерние виджеты освобождаются.
void RadioButtons::shutdown()
{
	p_vertical_layout.deleteLater();
	Console::setOnscreen(false);
}
