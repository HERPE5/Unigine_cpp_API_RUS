// UI примера для настроек прохождения оружия сквозь геометрию. Предоставляет переключатель
// пропуска рендеринга теней в слое оружия для оптимизации производительности.

#include "WeaponClippingSample.h"
#include "WeaponClipping.h"

using namespace Unigine;

REGISTER_COMPONENT(WeaponClippingSample);

// Создаётся чекбокс UI для переключения рендеринга теней в слое оружия.
void WeaponClippingSample::init()
{
	// Получаем ссылку на компонент WeaponClipping на связанном узле
	WeaponClipping* weapon_clipping_component = ComponentSystem::get()->getComponent<WeaponClipping>(weapon_clipping_node);

	if (!weapon_clipping_component)
		return;

	sample_description_window.createWindow();

	// Строим UI чекбокса для переключения пропуска теней
	auto parameters = sample_description_window.getParameterGroupBox();
	auto hbox = WidgetHBox::create();
	auto checkbox = WidgetCheckBox::create();

	// Переключаем флаг SKIP_SHADOWS на viewport оружия при изменении состояния чекбокса
	checkbox->getEventClicked().connect(*this, [weapon_clipping_component, this, checkbox]() {
		// Всегда пропускаем буфер скорости; опционально пропускаем тени для производительности
		int flags = Viewport::SKIP_VELOCITY_BUFFER;
		if (checkbox->isChecked())
			flags |= Viewport::SKIP_SHADOWS;

		weapon_clipping_component->getRenderViewport()->setSkipFlags(flags);
	});

	auto label = WidgetLabel::create("Skip shadows");

	hbox->addChild(label);
	hbox->addChild(checkbox);

	parameters->addChild(hbox, Gui::ALIGN_LEFT);
}

// Окно UI примера очищается при уничтожении компонента.
void WeaponClippingSample::shutdown()
{
	sample_description_window.shutdown();
}

