#pragma once
#include "DayNightSwitcher.h"
#include <UnigineConsole.h>


using namespace Unigine;
using namespace Math;

// Переключает элементы сцены между состояниями день/ночь на основе позиции солнца. Два режима:
// пороговый угол зенита (проверяет угол солнца от вертикали) или по времени (утренние/вечерние
// границы). Переключает видимость узлов и параметры эмиссии материалов.

REGISTER_COMPONENT(DayNightSwitcher);

// Получается SunController, подписывается событие, кэшируются значения эмиссии по умолчанию.
void DayNightSwitcher::init()
{
	sun = getComponent<SunController>(sun_node.get());
	if (!sun)
	{
		Log::error("DayNightSwitchSample::init can't find SunController component on the sun node!\n");
	}
	sun->getEventOnTimeChanged().connect(this, &DayNightSwitcher::onTimeChange);
	switch_control_type = static_cast<CONTROL_TYPE>(selected_control_type.get());


	for (int i = 0; i < materials_day_enabled.size(); i++)
	{
		MaterialPtr mat = materials_day_enabled.get(i).get();

		if (mat)
		{
			int param = mat->findParameter(emission_material_parameter_name.get());
			if (param == -1)
			{
				Log::error("DayNightSwitchSample::init materials_day_enabled got wrong material without emission!\n");
			}
			default_emission_scale.append(mat->getGUID(), mat->getParameterFloat(param));
		}
	}
	for (int i = 0; i < materials_night_enabled.size(); i++)
	{
		MaterialPtr mat = materials_night_enabled.get(i).get();

		if (mat)
		{
			int param = mat->findParameter(emission_material_parameter_name.get());
			if (param == -1)
			{
				Log::error("DayNightSwitchSample::init materials_night_enabled got wrong material without emission!\n");
			}
			default_emission_scale.append(mat->getGUID(), mat->getParameterFloat(param));
		}
	}
	onTimeChange();
}

// Событие отписывается, кэшированные данные очищаются.
void DayNightSwitcher::shutdown()
{
	default_emission_scale.clear();
	sun->getEventOnTimeChanged().disconnect(this, &DayNightSwitcher::onTimeChange);
	sun = nullptr;
}

// Состояние дня/ночи оценивается, узлы переключаются при изменении состояния.
void DayNightSwitcher::onTimeChange()
{
	switch (switch_control_type)
	{
	case 0: {// Угол зенита
		// Проверяем, день ли, после поворота солнца
		bool day = true;
		if (sun_node)
		{
			float current_angle = getAngle(vec3_up, sun_node->getWorldDirection(AXIS_Z));
			day = current_angle < sun_zenit_threshold;
		}

		// Начальное значение is_day равно -1, поэтому узлы всегда переключаются при первом вызове
		if ((day ? 1 : 0) != is_day)
		{
			switchNodes(day);
			is_day = day;
		}
		break;
	}
	case 1: {// Управление по времени
		int time = sun->getTime()/60;
		// Проверяем, находится ли текущее время в границах дня (от утра до вечера)
		bool day = time > (time_morning.get().x * 60 + time_morning.get().y)
				&& time < (time_evening.get().x * 60 + time_evening.get().y);
		// Начальное значение is_day равно -1, поэтому узлы всегда переключаются при первом вызове
		if ((day ? 1 : 0) != is_day)
		{
			switchNodes(day);
			is_day = day;
		}
		break;
	}
	default:
		break;
	}

}

// Видимость узлов и эмиссия материалов переключаются в зависимости от состояния дня/ночи.
void DayNightSwitcher::switchNodes(bool day)
{
	// Материалы
	for (size_t i = 0; i < materials_day_enabled.size(); i++)
	{
		MaterialPtr mat = materials_day_enabled.get(i).get();
		if (mat)
		{
			mat->setParameterFloat(emission_material_parameter_name.get(), day ? default_emission_scale[mat->getGUID()] : 0);
		}
		else
		{
			Log::warning("DayNightSwitcher::on_time_changed: materials_day_enabled  wrong day material %d\n", i);
		}

	}

	for (size_t i = 0; i < materials_night_enabled.size(); i++)
	{
		MaterialPtr mat = materials_night_enabled.get(i).get();
		if (mat)
		{
			mat->setParameterFloat(emission_material_parameter_name.get(), !day ? default_emission_scale[mat->getGUID()] : 0);
		}
		else
		{
			Log::warning("DayNightSwitcher::on_time_changed: materials_night_enabled wrong day material %d\n", i);
		}

	}

	// Узлы
	for (size_t i = 0; i < nodes_day_enabled.size(); i++)
	{
		NodePtr node = nodes_day_enabled.get(i).get();
		if (node)
		{
			node->setEnabled(day);
		}
		else
		{
			Log::warning("DayNightSwitcher::on_time_changed: wrong node %d\n", i);
		}
	}

	for (size_t i = 0; i < nodes_night_enabled.size(); i++)
	{
		NodePtr node = nodes_night_enabled.get(i).get();
		if (node)
		{
			node->setEnabled(!day);
		}
		else
		{
			Log::warning("DayNightSwitcher::on_time_changed: wrong node %d\n", i);
		}
	}
}

// Тип управления изменяется, состояние дня/ночи немедленно переоценивается.
void DayNightSwitcher::setControlType(CONTROL_TYPE type)
{
	switch_control_type = type;
	// Применяем новый порог немедленно
	onTimeChange();
}

// Порог зенита ограничивается и применяется, состояние дня/ночи переоценивается.
void DayNightSwitcher::setZenithThreshold(float value)
{
	value = clamp(value, 0.0f, 180.0f);
	sun_zenit_threshold = value;
	// Применяем новый порог немедленно
	onTimeChange();
}

// Устанавливается утренняя граница времени, состояние дня/ночи переоценивается.
void DayNightSwitcher::setControlMorningTime(Unigine::Math::ivec2 time_morning)
{
	this->time_morning = time_morning;
	// Применяем изменение немедленно
	onTimeChange();
}
// Устанавливается вечерняя граница времени, состояние дня/ночи переоценивается.
void DayNightSwitcher::setControlEveningTime(Unigine::Math::ivec2 time_evening)
{
	this->time_evening = time_evening;
	// Применяем изменение немедленно
	onTimeChange();
}