// Демонстрирует два метода запроса состояния поверхности воды: fetch (прямая выборка
// высоты) и intersection (пересечение луча с водой). Fetch быстрее, но менее точен
// при запросах под углом; intersection обрабатывает наклонные лучи с настраиваемой точностью.

#include "WaterFetchIntersection.h"

#include <UnigineVisualizer.h>

#include <functional>

REGISTER_COMPONENT(WaterFetchIntersection);

using namespace Unigine;
using namespace Math;

void WaterFetchIntersection::init()
{
	// Приводим ссылку на узел к ObjectWaterGlobal
	water = checked_ptr_cast<ObjectWaterGlobal>(water_node.get());

	Visualizer::setEnabled(true);
	init_gui();
}

void WaterFetchIntersection::shutdown()
{
	Visualizer::setEnabled(false);
	shutdown_gui();
}

void WaterFetchIntersection::init_gui()
{
	sample_description_window.createWindow();

	auto parameters = sample_description_window.getParameterGroupBox();

	// Создаём переключаемые кнопки для выбора режима запроса
	auto hbox_request_type = WidgetHBox::create();
	auto request_type_label = WidgetLabel::create("Request type: ");
	auto fetch_button = WidgetButton::create("Fetch");
	auto intersection_button = WidgetButton::create("Intersection");
	normal_cb = WidgetCheckBox::create("Show normals");

	fetch_button->setToggleable(true);
	intersection_button->setToggleable(true);

	// По умолчанию режим intersection
	intersection_button->setToggled(true);
	fetch = false;

	hbox_request_type->addChild(request_type_label);
	hbox_request_type->addChild(fetch_button);

	hbox_request_type->addChild(intersection_button);
	hbox_request_type->addChild(normal_cb);

	parameters->addChild(hbox_request_type, Gui::ALIGN_LEFT);

	// Поведение радиокнопок: переключение одной снимает переключение другой
	fetch_button->getEventChanged().connect(*this, [this, fetch_button, intersection_button]() {
			fetch = fetch_button->isToggled();
			intersection_button->setToggled(!fetch);
		});

	intersection_button->getEventChanged().connect(*this, [this, fetch_button, intersection_button]() {
			fetch = !intersection_button->isToggled();
			fetch_button->setToggled(fetch);
		});

	// Общие параметры
	sample_description_window.addIntParameter("Number of requests", "num request", num_intersection, 1, 10000,
		[this](int v) { num_intersection = v; });

	sample_description_window.addFloatParameter("Point size", "Point size", intersect_point_size, 0.1f, 1.f,
		[this](float v) { intersect_point_size = v; });

	// Шкала Beaufort управляет интенсивностью волн (0 = штиль, 12 = ураган)
	sample_description_window.addFloatParameter("Beaufort", "beaufort", 0.f, 0.f, 12.f,
		[this](float v) { water->setBeaufort(v); });

	sample_description_window.addParameterSpacer();

	// Параметры, специфичные для Fetch
	// Порог амплитуды: волны ниже этой высоты игнорируются для fetch
	sample_description_window.addFloatParameter("Fetch Amplitude Threshold", "fetch amplitude threshold",
		water->getFetchAmplitudeThreshold(), 0.001f, 0.5f,
		[this](float v) { water->setFetchAmplitudeThreshold(v); });

	// Качество крутизны: выше = точнее, но медленнее fetch
	sample_description_window.addIntParameter("Fetch Steepness Quality", "fetch steepness quality",
		water->getFetchSteepnessQuality(), 0, 4, [this](int v) {
			water->setFetchSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY(v));
		});

	sample_description_window.addParameterSpacer();

	// Параметры, специфичные для Intersection
	sample_description_window.addFloatParameter("Intersection Amplitude Threshold",
		"intersection amplitude threshold", water->getIntersectionAmplitudeThreshold(), 0.001f,
		0.5f, [this](float v) { water->setIntersectionAmplitudeThreshold(v); });

	sample_description_window.addIntParameter("Intersection Steepness Quality",
		"intersection steepness quality", static_cast<int>(water->getIntersectionSteepnessQuality()), 0, 4,
		[this](int v) {
			water->setIntersectionSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY(v));
		});

	// Точность: пороговое расстояние для признания пересечения найденным
	sample_description_window.addFloatParameter("Intersection Precision", "intersection precision",
		water->getIntersectionPrecision(), 0.001f, 2.0f,
		[this](float v) { water->setIntersectionPrecision(v); });

	// Угол луча для тестов пересечения
	sample_description_window.addFloatParameter("Intersection Angle", "intersection angle", 5.f,
		-30.f, 30.f, [this](float v) { water->setIntersectionPrecision(v); });
}

void WaterFetchIntersection::shutdown_gui()
{
	sample_description_window.shutdown();
}

void WaterFetchIntersection::update()
{
	bool normal_show = normal_cb->isChecked();
	// Создаём квадратную сетку точек запроса
	int count = (int)Math::sqrtFast((float)num_intersection);

	// Заранее создаём объекты результата пересечения (переиспользуются для эффективности)
	ObjectIntersectionPtr oi = ObjectIntersection::create();
	ObjectIntersectionNormalPtr oin = ObjectIntersectionNormal::create();

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			// Позиция сетки на уровне воды (z=0)
			Vec3 pos = Vec3((float)i, (float)j, 0);

			if (fetch)
			{
				// Режим Fetch: прямая выборка высоты в позиции XY
				float v = water->fetchHeight(pos);
				pos.z += v;
				Visualizer::renderPoint3D(pos, intersect_point_size, vec4_blue);

				if (normal_show)
				{
					// Выбираем нормаль поверхности в этой позиции
					vec3 n = water->fetchNormal(pos);
					Visualizer::renderVector(pos, pos + Vec3(n), vec4_white);
				}
			}
			else
			{
				// Режим Intersection: выпускаем луч для поиска поверхности воды
				// Направление луча на основе параметра угла пересечения
				Vec3 dir(Math::sin(intersection_angle * Consts::DEG2RAD), 0,
					Math::cos(intersection_angle * Consts::DEG2RAD));

				if (normal_show)
				{
					// Используем ObjectIntersectionNormal, чтобы также получить нормаль поверхности
					if (water->getIntersection(pos + dir * 100, pos - dir * 100, oin, 0))
					{
						Visualizer::renderPoint3D(oin->getPoint(), intersect_point_size,
							vec4_green);
						Visualizer::renderVector(oin->getPoint(),
							oin->getPoint() + Vec3(oin->getNormal()), vec4_white);
						// Отрисовываем направление луча
						Visualizer::renderVector(oin->getPoint() + dir * 2.f, oin->getPoint(),
							vec4_blue);
					}
				}
				else
				{
					// Используем ObjectIntersection (без нормали, немного быстрее)
					if (water->getIntersection(pos + dir * 100, pos - dir * 100, oi, 0))
					{
						Visualizer::renderPoint3D(oi->getPoint(), intersect_point_size, vec4_green);
						Visualizer::renderVector(oi->getPoint() + dir * 2.f, oi->getPoint(),
							vec4_blue);
					}
				}
			}
		}
	}
}
