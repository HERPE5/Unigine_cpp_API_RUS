// Предоставляет элементы управления UI для примера DynamicTextureFieldHeight. Позволяет во время выполнения
// настраивать разрешение карты высот, амплитуду волн, частоту и скорость анимации.
// Отображает превью-спрайт, показывающий сгенерированную текстуру карты высот.

#include "DynamicTextureFieldHeightSample.h"
#include "UnigineGame.h"
#include "UnigineFields.h"
#include "DynamicTextureFieldHeight.h"

REGISTER_COMPONENT(DynamicTextureFieldHeightSample);

using namespace Unigine;
using namespace Math;

void DynamicTextureFieldHeightSample::init()
{
	description_window.createWindow();

	// Кнопки выбора разрешения текстуры карты высот
	// Более высокое разрешение = больше деталей, но выше затраты памяти и CPU
	WidgetButtonPtr button_size_1024 = WidgetButton::create();
	WidgetButtonPtr button_size_2048 = WidgetButton::create();
	WidgetButtonPtr button_size_4096 = WidgetButton::create();

	button_size_1024->setText("1024");
	button_size_2048->setText("2048");
	button_size_4096->setText("4096");

	// getComponent<T> получает компонент из узла по типу
	// Возвращает обычный указатель (не умный) для доступа к компоненту
	button_size_1024->getEventClicked().connect(*this, [this]() {
		DynamicTextureFieldHeight* component = getComponent<DynamicTextureFieldHeight>(field_height);
		if (component)
		{
			component->setImageSize(1024);
			size_map->setText("1024 X 1024");
		}
		});

	button_size_2048->getEventClicked().connect(*this, [this]() {
		DynamicTextureFieldHeight* component = getComponent<DynamicTextureFieldHeight>(field_height);
		if (component)
		{
			component->setImageSize(2048);
			size_map->setText("2048 X 2048");
		}
		});

	button_size_4096->getEventClicked().connect(*this, [this]() {
		DynamicTextureFieldHeight* component = getComponent<DynamicTextureFieldHeight>(field_height);
		if (component)
		{
			component->setImageSize(4096);
			size_map->setText("4096 X 4096");
		}
		});

	// Горизонтальная компоновка для кнопок разрешения
	WidgetHBoxPtr button_box = WidgetHBox::create();

	button_box->addChild(button_size_1024);
	button_box->addChild(button_size_2048);
	button_box->addChild(button_size_4096);

	// Размер поля определяет протяжённость изменения высоты в мировом пространстве
	description_window.addIntParameter("Size FieldHeight", "", 40, 25, 100, [this](int value) {
		FieldHeightPtr field = checked_ptr_cast<FieldHeight>(field_height.get());
		if (field)
		{
			// Равномерное масштабирование по всем осям
			field->setSize(vec3(float(value)));
		}
		});

	// Amplitude: интенсивность высоты волн (0 = плоско, 1 = максимум)
	description_window.addFloatParameter("Amplitude", "", 1.0f, 0.0f, 1.0f, [this](float value) {
		DynamicTextureFieldHeight* component = getComponent<DynamicTextureFieldHeight>(field_height);
		if (component)
		{
			component->setAmplitude(value);
		}
		});

	// Frequency: количество циклов волн по текстуре
	description_window.addFloatParameter("Frequency", "", 1.0f, 1.0f, 40.0f, [this](float value) {
		DynamicTextureFieldHeight* component = getComponent<DynamicTextureFieldHeight>(field_height);
		if (component)
		{
			component->setFrequency(value);
		}
		});

	// Speed: множитель скорости анимации
	description_window.addFloatParameter("Speed", "", 1.0f, 0.0f, 20.0f, [this](float value) {
		DynamicTextureFieldHeight* component = getComponent<DynamicTextureFieldHeight>(field_height);
		if (component)
		{
			component->setSpeed(value);
		}
		});

	// Метка, отображающая текущие размеры текстуры
	size_map = WidgetLabel::create();
	size_map->setText("1024 X 1024");
	size_map->setFontSize(20);
	DynamicTextureFieldHeight* component = getComponent<DynamicTextureFieldHeight>(field_height);

	// Создаём виджет-спрайт для превью текстуры карты высот
	// Спрайт получает обновления изображения из DynamicTextureFieldHeight::update()
	WidgetSpritePtr sprite = WidgetSprite::create();
	sprite->setHeight(200);
	sprite->setWidth(200);
	component->setWidgetSprite(sprite);


	description_window.addParameterSpacer();

	description_window.getParameterGroupBox()->addChild(button_box, Gui::ALIGN_LEFT);

	// Группа, содержащая метку разрешения и превью-спрайт
	WidgetGroupBoxPtr image_group = WidgetGroupBox::create();
	image_group->addChild(size_map);
	image_group->addChild(sprite);

	description_window.getParameterGroupBox()->addChild(button_box, Gui::ALIGN_TOP);
	description_window.getParameterGroupBox()->addChild(image_group, Gui::ALIGN_TOP);
}

void DynamicTextureFieldHeightSample::shutdown()
{
	description_window.shutdown();
}
