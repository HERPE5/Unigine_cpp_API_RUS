// Демонстрация пересечения лучей с использованием World::getIntersection. Лазерный луч пускается
// каждый кадр, а чекбоксы маски пересечения управляют тем, какие объекты можно поразить.
// Визуализатор точки попадания выравнивается по нормали пересечения. Длина лазера подстраивается под расстояние.

#include "RayIntersection.h"

REGISTER_COMPONENT(RayIntersection)

using namespace Unigine;
using namespace Math;

// Создаётся объект пересечения, масштаб лазера кэшируется для динамической подстройки.
void RayIntersection::init()
{
	// Проверяем части лазера
	if (!laser_ray || !laser_hit)
	{
		Log::error("laser_ray or laser_hit is missing");
		return;
	}

	// Создаём объект пересечения для получения необходимой информации
	// о результате пересечения
	intersection = WorldIntersectionNormal::create();

	// Сохраняем исходный масштаб лазерного луча для изменения длины после пересечения
	laser_ray_scale = laser_ray->getWorldScale();

	init_gui();
}

// Луч пускается вдоль направления лазера; точка попадания и длина обновляются каждый кадр.
void RayIntersection::update()
{
	// Проверяем части лазера
	if (!laser_ray || !laser_hit)
		return;

	// Получаем точки для обнаружения пересечения на основе направления лазерного луча
	Vec3 first_point = laser_ray->getWorldPosition();
	Vec3 second_point = first_point + Vec3(laser_ray->getWorldDirection(AXIS_Y)) * laser_distance;

	// Выполняем проверку пересечения луча с текущим фильтром маски
	ObjectPtr hit_object = World::getIntersection(
		first_point, second_point, intersection_mask, intersection);
	if (hit_object && hit_object->getParent())
	{
		// Определяем индекс стены по порядку среди дочерних объектов и обновляем подпись с цветом
		int wall_idx = hit_object->getParent()->getChildIndex(hit_object);
		current_hit->setText(String::format(
			"Current Hit Object: <b><font color=\"%s\">%s</font></b>",
			colors[wall_idx], walls[wall_idx])
				.get());

		// Подстраиваем длину лазерного луча под расстояние до пересечения
		float length = (intersection->getPoint() - laser_ray->getWorldPosition()).length();
		laser_ray_scale.y = length;
		laser_ray->setWorldScale(laser_ray_scale);

		// Показываем индикатор попадания, если он был ранее скрыт
		if (!laser_hit->isEnabled())
			laser_hit->setEnabled(true);

		// Позиционируем индикатор попадания в точке пересечения, выровненной по нормали поверхности
		laser_hit->setWorldPosition(intersection->getPoint());
		laser_hit->setWorldDirection(intersection->getNormal(), vec3_up, AXIS_Y);
	}
	else
	{
		// Очищаем подпись попадания при отсутствии пересечения
		auto parameters = window.getParameterGroupBox();
		static_ptr_cast<WidgetLabel>(parameters->getChild(3))
			->setText(
				"Current Hit Object: <font color=\"#ffffff\">None</font>");

		// Растягиваем лазер до максимальной длины при отсутствии попадания
		laser_ray_scale.y = laser_distance;
		laser_ray->setWorldScale(laser_ray_scale);

		// Скрываем индикатор попадания
		laser_hit->setEnabled(false);
	}
}

// Ресурсы UI очищаются при уничтожении компонента.
void RayIntersection::shutdown()
{
	mask_text.deleteLater();
	window.shutdown();
}

// Строится UI с чекбоксами для каждого цвета стены и полем ввода бинарной маски.
void RayIntersection::init_gui()
{
	window.createWindow();

	auto parameters = window.getParameterGroupBox();

	int walls_size = walls.size();

	// Создаём сетку для чекбоксов стен и поля ввода бинарной маски
	auto grid = WidgetGridBox::create(4, 10, 10);
	auto hbox = WidgetHBox::create();
	auto line = WidgetEditLine::create();
	auto label = WidgetLabel::create("Laser Mask: ");
	current_hit = WidgetLabel::create("Current Hit Object: None");
	current_hit->setFontRich(true);
	// Настраиваем текстовое поле бинарной маски (8 бит для 8 стен)
	line->setWidth(100);
	line->setCapacity(8);
	line->setText("00000000");
	line->setValidator(Gui::VALIDATOR_UINT);
	hbox->addChild(label);
	hbox->addChild(line);
	hbox->setPadding(0, 0, 5, 5);

	parameters->addChild(grid);
	parameters->addChild(hbox, Gui::ALIGN_LEFT);
	parameters->addChild(current_hit, Gui::ALIGN_LEFT);

	// Убираем фокус по клавише Enter, чтобы применить изменения маски
	prev_text = line->getText();
	line->getEventKeyPressed().connect(
		*this, [](const WidgetPtr &check, int key) {
			if (key == Input::KEY_ENTER)
			{
				check->removeFocus();
			}
		});

	// Фильтруем ввод, разрешая только бинарные цифры (0 и 1)
	line->getEventChanged().connect(*this, [this](const WidgetPtr &edit_line) {
		auto temp = static_ptr_cast<WidgetEditLine>(edit_line);
		String text = temp->getText();
		if (prev_text == text)
			return;

		String new_text;
		for (int i = 0, some = text.size(); i < some; ++i)
		{
			if (text[i] == '0' || text[i] == '1')
			{
				new_text.append(text[i]);
			}
			else
			{
				temp->setCursor(i);
			}
		}
		prev_text = temp->getText();
		temp->setText(new_text);
	});
	// Синхронизируем чекбоксы с текстом маски, когда фокус покидает поле ввода
	line->getEventFocusOut().connect(
		*this, [this, grid](const WidgetPtr &edit_line) {
			auto temp = static_ptr_cast<WidgetEditLine>(edit_line);
			String text = temp->getText();
			// Дополняем до 8 цифр ведущими нулями
			if (text.size() < 8)
			{
				String new_text;
				for (int i = text.size(); i < 8; ++i)
				{
					new_text.append('0');
				}
				new_text = new_text + text;
				temp->setText(new_text);
				prev_text = new_text;
			}

			// Обновляем состояния чекбоксов из бинарной строки
			for (int i = 0; i < 8; ++i)
			{
				static_ptr_cast<WidgetCheckBox>(grid->getChild(7 - i))
					->setChecked(temp->getText()[i] - '0' > 0);
			}
		});

	// Создаём чекбокс для каждого цвета стены
	for (int i = 0; i < walls_size; ++i)
	{
		auto checkbox = WidgetCheckBox::create(walls[i]);
		int wall_intersection_mask = 1 << i;

		// Переключаем бит в маске и синхронизируем текстовое поле при изменении чекбокса
		int ind = walls_size - 1 - i;
		checkbox->getEventClicked().connect(
			*this, [this, wall_intersection_mask, ind, line](const WidgetPtr &check) {
				String new_text = line->getText();
				if (static_ptr_cast<WidgetCheckBox>(check)->isChecked())
				{
					new_text[ind] = '1';
					intersection_mask = intersection_mask | wall_intersection_mask;
				}
				else
				{
					new_text[ind] = '0';
					intersection_mask = intersection_mask & ~wall_intersection_mask;
				}
				line->setText(new_text);
			});

		// Инициализируем состояние чекбокса из текущей маски
		checkbox->setChecked((intersection_mask & wall_intersection_mask) > 0);

		grid->addChild(checkbox, Gui::ALIGN_LEFT);
	}
}
