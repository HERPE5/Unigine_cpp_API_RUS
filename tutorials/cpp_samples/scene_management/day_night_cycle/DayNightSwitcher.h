#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineLights.h>
#include "SunController.h"

// Переключает элементы сцены между состояниями дня и ночи.
// Два режима управления: угол зенита (положение солнца относительно горизонта)
// или явные временные границы (утренние/вечерние часы).
// Переключает видимость узлов и параметры эмиссии материалов при переходах.
class DayNightSwitcher : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(DayNightSwitcher, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component displays information about the day and night switching.");

	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Режим определения дня/ночи
	enum CONTROL_TYPE {
		Zenith = 0, // Использовать угол солнца от вертикали
		Time = 1,   // Использовать границы времени суток
	};

	// Сеттеры типа управления и порога
	void setControlType(CONTROL_TYPE type);
	void setZenithThreshold(float value);
	float getZenithThreshold() { return sun_zenit_threshold; };

	// Границы управления по времени (часы:минуты как ivec2)
	void setControlMorningTime(Unigine::Math::ivec2 time_morning);
	void setControlEveningTime(Unigine::Math::ivec2 time_evening);
	int getControlMorningTime() { return time_morning.get().x * 60 + time_morning.get().y; };
	int getControlEveningTime() { return time_evening.get().x * 60 + time_evening.get().y; };

private:
	// Параметры
	PROP_PARAM(Node, sun_node, "Sun node", "Sun node"); // Ссылка на солнце с SunController

	PROP_PARAM(Switch, selected_control_type, 0, "Zenith,Time"); // Селектор режима определения
	PROP_PARAM(Float, sun_zenit_threshold, 85.0f, nullptr, nullptr, nullptr, "selected_control_type=0"); // Пороговый угол для режима зенита
	PROP_PARAM(IVec2, time_morning, Unigine::Math::ivec2(7, 30), nullptr, nullptr, nullptr, "selected_control_type=1"); // Время начала дня
	PROP_PARAM(IVec2, time_evening, Unigine::Math::ivec2(19, 30), nullptr, nullptr, nullptr, "selected_control_type=1"); // Время конца дня

	PROP_PARAM(String, emission_material_parameter_name, "emission_scale"); // Параметр материала для переключения

	// Массивы объектов для переключения между состояниями дня/ночи
	PROP_ARRAY(Material, materials_day_enabled);   // Материалы с включённой эмиссией днём
	PROP_ARRAY(Material, materials_night_enabled); // Материалы с включённой эмиссией ночью
	PROP_ARRAY(Node, nodes_day_enabled);           // Узлы, видимые днём
	PROP_ARRAY(Node, nodes_night_enabled);         // Узлы, видимые ночью

	Unigine::HashMap<Unigine::UGUID, float> default_emission_scale;

	SunController* sun = nullptr;
	int is_day = -1; // Текущее состояние: 1=день, 0=ночь, -1=не инициализировано
	CONTROL_TYPE switch_control_type = CONTROL_TYPE::Zenith;

	void init();
	void shutdown();
	void onTimeChange();
	void switchNodes(bool day);
};

