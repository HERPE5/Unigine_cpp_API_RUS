# ObjectWaterGlobal Class (CPP)

**Header:** #include <UnigineObjects.h>

**Inherits from:** Object


Интерфейс для работы с объектом **[Global Water](../../../objects/objects/water/water_object.md)**. Этот объект воды представляет бесконечно распространённую воду с авто-тесселяцией (каркас объекта воды не масштабируется — независимо от позиции камеры он остаётся неизменным) и режимом «под водой». Этот тип подходит для представления безбрежного океана без чрезмерной нагрузки на GPU.


Однако ему нельзя назначить тело, и поэтому он не обеспечивает корректного физического взаимодействия с объектами сцены. Если вам нужно симулировать физику плавучести, следует использовать **[Physical Water](../../../objects/effects/physicals/physical_water/index.md)**. Также он ограничен единым уровнем воды. Это означает, что уровень заполнения воды всегда остаётся неизменным. Поэтому, если вам нужно создать, например, горные озёра или водные потоки с перепадом высот, следует использовать **[Water Mesh](../../../objects/objects/water/water_mesh.md)**.


Существует три варианта создания волн:


- **Режим Layer (слои)** — вы создаёте слои, на которых волны будут генерироваться случайным образом в заданном диапазоне параметров волн. Все слои складываются вместе. > **Notice:** Слои волн обычно создаются через UnigineEditor, но их также можно создавать и редактировать через код.
- **Режим Manual (ручной)** — вы создаёте собственные отдельные волны и полностью контролируете их. Этот режим можно задать только через код, в UnigineEditor это сделать нельзя. > **Notice:** В **режиме Manual** будьте осторожны с параметром *Steepness* — при высоком значении волны будут выворачиваться.
- **Режим Beauforts** — волны генерируются на основе пресетов, воспроизводящих состояние моря согласно шкале силы ветра Бофорта (0 - штиль, 12 - ураган). В этом режиме параметры, определяющие основную геометрию волн, недоступны для редактирования через код.


Для всех режимов частота волны вычисляется на основе длины волны по формуле:

 sqrt (*Gravity* * 2 * PI / *Wavelength*)
 где *Gravity* = 9.81 м/с2.
При включении **режима Manual** список сгенерированных волн очищается, и вы можете задать собственные волны.


При сохранении мира слои будут сохранены, а пользовательские волны — нет, так как они создаются через код.


Максимальное общее количество волн — **256**. Для лучшей производительности рекомендуется использовать около **100**.


Вот как можно изменить файл *AppWorldLogic.cpp* для создания волн в **режиме Manual**:


<details>
<summary>AppWorldLogic.cpp | Закрыть</summary>

```cpp
#include "AppWorldLogic.h"
#include <UnigineWorld.h>

using namespace Unigine;

ObjectWaterGlobalPtr water = nullptr;

/* ... */

int AppWorldLogic::init()
{
	// Здесь напишите код, который должен вызываться при инициализации мира: инициализируйте ресурсы для вашей сцены мира во время старта мира.

	// Меняем пресет на custom (4) и настраиваем параметры тесселяции
	Render::setWaterGeometryPreset(4);
	Render::setWaterGeometryPolygonSize(0.01f);
	Render::setWaterGeometryProgression(1.0f);
	Render::setWaterGeometrySubpixelReduction(6.0f);

	water = static_ptr_cast<ObjectWaterGlobal>(World::getNodeByType(Node::OBJECT_WATER_GLOBAL));
	if (!water)
	{
		water = ObjectWaterGlobal::create();
	}

	// Каждую волну можно задать только в режиме Manual
	water->setWavesMode(ObjectWaterGlobal::WAVES_MODE_MANUAL);

	// Добавляем волны
	// addWave(длина волны, амплитуда, крутизна, угол направления[0.0; 360.0], смещение фазы[0.0; 2*PI])

	water->addWave(8.0f, 0.05f, 2.0f, 270.0f, 0.0f);
	water->addWave(8.0f, 0.015f, 1.0f, 150.0f, 1.0f);
	water->addWave(8.0f, 0.02f, 6.0f, 75.0f, 0.0f);
	water->addWave(16.0f, 0.05f, 2.0f, 270.0f, 3.0f);
	water->addWave(16.0f, 0.05f, 7.0f, 45.0f, 0.5f);
	water->addWave(32.0f, 0.1f, 2.0f, 120.0f, 2.0f);
	water->addWave(64.0f, 0.2f, 1.0f, -90.0f, 0.1f);

	// Меняем амплитуду и длину для второй волны
	water->setWaveAmplitude(1, 0.03f);
	water->setWaveLength(1, 10.0f);

	return 1;

	/* ... */

}


```

</details>


### Получение уровня воды и нормали поверхности


Для обеспечения правильного размещения и ориентации объектов относительно поверхности воды необходимо получить уровень воды (высоту) и ориентацию нормали в заданной точке. Это можно сделать с помощью следующих методов:


- *[fetchHeight()](#fetchHeight_Vec3_float)*
- *[fetchNormal()](#fetchNormal_Vec3_vec3)*


По умолчанию качество (точность) вычисления высот и нормалей задано для оптимизации производительности, но в случае более высоких уровней Бофорта (приводящих к значительной крутизне волн и перепадам высот на поверхности воды) результаты вычислений могут отличаться от визуального представления (например, вычисленный уровень воды может быть больше фактического значения). Это может, например, привести к некорректному заданию позиции и ориентации корабля относительно поверхности воды. Чтобы избежать таких случаев, можно повысить качество вычислений для запросов получения высоты/нормали через следующие параметры, доступные через API:


- **Steepness Quality** *[setFetchSteepnessQuality](../../...md#setFetchSteepnessQuality_int_void)* - точность вычисления крутизны волн, используемая при вычислении уровня воды (высоты) и ориентации нормали в заданной точке. Этот параметр используется для улучшения результатов вычислений в случае высокой крутизны волн (более высокие уровни Бофорта). Низкого качества обычно достаточно для спокойной воды (*high* обеспечивает хорошие результаты для 6-7 баллов Бофорта, а *ultra* рекомендуется для 8-10 баллов).
- **Amplitude Threshold** *[setFetchAmplitudeThreshold](../../...md#setFetchAmplitudeThreshold_float_void)* - минимальный порог амплитуды, при котором волны учитываются при вычислении высоты и нормали (волны с меньшей амплитудой будут игнорироваться).


> **Notice:** Использование более высокого качества влияет на производительность, поэтому рекомендуется повышать его только при необходимости (при высоких уровнях Бофорта) и возвращать к значению по умолчанию, когда поверхность воды становится относительно спокойной.


Таким образом, в случае более высоких уровней Бофорта можно скорректировать качество вычисления пересечений с помощью следующих строк:


```cpp
water->setFetchSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY_ULTRA);
water->setFetchAmplitudeThreshold(0.01f);


```


### Поиск точек пересечения


Пересечения используются для множества целей, например, можно найти точку пересечения снаряда с поверхностью воды для создания брызг. По умолчанию качество (точность) вычисления точек пересечения задано для оптимизации производительности, но в случае более высоких уровней Бофорта (приводящих к значительной крутизне волн и перепадам высот на поверхности воды) результаты вычислений могут отличаться от визуального представления (например, точка пересечения обнаруживается на некотором расстоянии от поверхности воды). Это может, например, привести к созданию систем частиц, представляющих брызги, в неправильной позиции. Чтобы избежать таких случаев, можно повысить качество вычислений для определения пересечений через следующие параметры, доступные через API:


- **Precision** *[setIntersectionPrecision](../../...md#setIntersectionPrecision_float_void)* - допустимая погрешность между вычисленной и реальной точкой пересечения с водой.
- **Steepness Quality** *[setIntersectionSteepnessQuality](../../...md#setIntersectionSteepnessQuality_int_void)* - точность вычисления крутизны волн, используемая при вычислении пересечений. Этот параметр используется для улучшения вычисления пересечений в случае высокой крутизны волн (более высокие уровни Бофорта). Низкого качества обычно достаточно для спокойной воды (*high* обеспечивает хорошие результаты для 6-7 баллов Бофорта, а *ultra* рекомендуется для 8-10 баллов).
- **Amplitude Threshold** *[setIntersectionAmplitudeThreshold](../../...md#setIntersectionAmplitudeThreshold_float_void)* - минимальный порог амплитуды, при котором волны учитываются при вычислении пересечений (волны с меньшей амплитудой будут игнорироваться).


> **Notice:** Использование более высокого качества влияет на производительность, поэтому рекомендуется повышать его только при необходимости (при высоких уровнях Бофорта) и возвращать к значению по умолчанию, когда поверхность воды становится относительно спокойной.


Таким образом, в случае более высоких уровней Бофорта можно скорректировать качество вычисления пересечений с помощью следующих строк:


```cpp
water->setFetchSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY_ULTRA);
water->setFetchAmplitudeThreshold(0.01f);


```


### Пример использования


Этот пример демонстрирует влияние параметров **[Steepness Quality](#setFetchSteepnessQuality_int_void), [Amplitude Threshold](#setFetchAmplitudeThreshold_float_void)** и **[Precision](#setIntersectionPrecision_float_void)** на точность запросов получения данных и пересечений для объекта *Global Water* на различных уровнях Бофорта.


[Create a new C++ component](../../../code/usage/using_component_system/index.md#create_class) с именем **WaterFetchIntersection** и скопируйте приведённый ниже код в соответствующие файлы:


<details>
<summary>WaterFetchIntersection.h | Закрыть</summary>

`WaterFetchIntersection.h`


```cpp
#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>

class WaterFetchIntersection : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(WaterFetchIntersection, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// параметр для назначения объекта Global Water
	PROP_PARAM(Node, water_node, "", "", "", "filter=ObjectWaterGlobal");

private:
	void init();
	void update();
	void shutdown();

	void init_gui();
	void shutdown_gui();
	Unigine::WidgetWindowPtr window;

	int num_intersection = 100;
	float intersect_point_size = 0.2f;
	bool fetch = true;

	Unigine::WidgetSliderPtr slider_num_requests;
	Unigine::WidgetSliderPtr slider_beaufort;
	Unigine::WidgetSliderPtr slider_fetch_amplitude;
	Unigine::WidgetSliderPtr slider_fetch_stepness;
	Unigine::WidgetSliderPtr slider_intersection_amplitude;
	Unigine::WidgetSliderPtr slider_intersection_stepness;
	Unigine::WidgetSliderPtr slider_precision;

	// указатель на объект Global Water
	Unigine::ObjectWaterGlobalPtr water;
};

```

</details>


<details>
<summary>WaterFetchIntersection.cpp | Закрыть</summary>

`WaterFetchIntersection.cpp`


```cpp
#include "WaterFetchIntersection.h"
#include <functional>
#include <UnigineVisualizer.h>

REGISTER_COMPONENT(WaterFetchIntersection);

using namespace Unigine;
using namespace Math;

void WaterFetchIntersection::init()
{
	water = checked_ptr_cast<ObjectWaterGlobal>(water_node.get());

	Visualizer::setEnabled(1);
	init_gui();
}

void WaterFetchIntersection::shutdown()
{
	shutdown_gui();
}

// построение UI для параметров
void WaterFetchIntersection::init_gui()
{
	window = WidgetWindow::create("Fetch and Intersection Water Parameters");
	Gui::getCurrent()->addChild(window, Gui::ALIGN_OVERLAP);

	auto group_box = WidgetGroupBox::create("Parameters", 8, 8);
	window->addChild(group_box, Gui::ALIGN_LEFT);

	WidgetHBoxPtr hbox = WidgetHBox::create();
	group_box->addChild(hbox, Gui::ALIGN_LEFT);
	auto label = WidgetLabel::create("Request Type");
	label->setWidth(180);
	hbox->addChild(label, Gui::ALIGN_LEFT);

	auto fetch_b = WidgetButton::create("Fetch");
	hbox->addChild(fetch_b, Gui::ALIGN_LEFT);
	fetch_b->setToggleable(true);
	fetch_b->setToggled(fetch);
	auto intersection_b = WidgetButton::create("Intersection");
	hbox->addChild(intersection_b, Gui::ALIGN_LEFT);
	intersection_b->setToggleable(true);
	intersection_b->setToggled(!fetch);

	fetch_b->getEventChanged().connect(*this, [this, fetch_b, intersection_b]() {
		fetch = fetch_b->isToggled();
		intersection_b->setToggled(!fetch);
	});

	intersection_b->getEventChanged().connect(*this, [this, fetch_b, intersection_b]() {
		fetch = !intersection_b->isToggled();
		fetch_b->setToggled(fetch);
		});

	auto grid = WidgetGridBox::create(3);
	group_box->addChild(grid);

	// функция, создающая параметр и добавляющая соответствующий элемент UI
	auto create_param = [this](const WidgetPtr& parent, const char* name, float default_value, float min_value, float max_value, std::function<void(float)> f, bool floating) -> WidgetSliderPtr {
		auto label = WidgetLabel::create(name);
		label->setWidth(100);
		parent->addChild(label, Gui::ALIGN_LEFT);

		auto slider = WidgetSlider::create();
		slider->setMinValue(min_value * (floating ? 1000 : 1));
		slider->setMaxValue(max_value * (floating ? 1000 : 1));
		slider->setValue(default_value * (floating ? 1000 : 1));

		slider->setWidth(200);
		slider->setButtonWidth(20);
		slider->setButtonHeight(20);
		parent->addChild(slider, Gui::ALIGN_LEFT);

		label = WidgetLabel::create(String::ftoa(default_value, (floating ? 3 : 0)));
		label->setWidth(20);
		parent->addChild(label);

		slider->getEventChanged().connect(*this, [this, label, slider, f, floating]() {
			float v = slider->getValue() / (floating ? 1000.0f : 1.0f);
			label->setText(String::ftoa(v, (floating ? 3 : 0)));
			f(v);
		});

		return slider;
	};
	// слайдер количества запросов fetch/intersection
	slider_num_requests = create_param(grid, "Request Count", num_intersection, 100, 10000, [this](float v) { num_intersection = v; }, false);

	// слайдер уровня Бофорта
	slider_beaufort = create_param(grid, "Beaufort", 0, 0, 13, [this](float v) { water->setBeaufort(v); }, true);

	for (int i = 0; i < 3; i++)
	{
		auto s = WidgetSpacer::create();
		grid->addChild(s);
		s->setOrientation(1);
	}

	// слайдеры, управляющие параметрами качества для запросов fetch
	slider_fetch_amplitude = create_param(grid, "Fetch Amplitude Threshold", water->getFetchAmplitudeThreshold(), 0.001f, 0.5f, [this](float v) { water->setFetchAmplitudeThreshold(v); }, true);
	slider_fetch_stepness = create_param(grid, "Fetch Steepness Quality", int(water->getFetchSteepnessQuality()), 0, 4, [this](float v) { water->setFetchSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY(Math::roundFast(v))); }, false);

	for (int i = 0; i < 3; i++)
	{
		auto s = WidgetSpacer::create();
		grid->addChild(s);
		s->setOrientation(1);
	}
	// слайдеры, управляющие параметрами качества и точности для запросов intersection
	slider_intersection_amplitude = create_param(grid, "Intersection Amplitude Threshold", water->getIntersectionAmplitudeThreshold(), 0.001f, 0.5f, [this](float v) { water->setIntersectionAmplitudeThreshold(v); }, true);
	slider_intersection_stepness = create_param(grid, "Intersection Steepness Quality", int(water->getIntersectionSteepnessQuality()), 0, 4, [this](float v) { water->setIntersectionSteepnessQuality(ObjectWaterGlobal::STEEPNESS_QUALITY(Math::roundFast(v))); }, false);
	slider_precision = create_param(grid, "Intersection Precision", water->getIntersectionPrecision(), 0.01f, 2.0f, [this](float v) { water->setIntersectionPrecision(v); }, true);

	window->arrange();
}

void WaterFetchIntersection::shutdown_gui()
{
	window.deleteLater();
}

void WaterFetchIntersection::update()
{
	// вычисляем количество точек fetch/intersection вдоль осей X и Y
	int count = Math::sqrtFast(num_intersection);

	// создаём объект для хранения данных пересечения
	ObjectIntersectionNormalPtr oin = ObjectIntersectionNormal::create();

	// перебираем все точки для выполнения запросов fetch/intersection с текущими настройками
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			Vec3 pos = Vec3(i, j, 0);
			if (fetch)
			{
				// получаем данные о высоте Global Water и точку, отображаем их
				float v = water->fetchHeight(pos);
				pos.z += v;
				Visualizer::renderPoint3D(pos, intersect_point_size, vec4_blue);

				// получаем и отображаем нормали в точках fetch
				vec3 n = water->fetchNormal(pos);
				Visualizer::renderVector(pos, pos + Vec3(n), vec4_white);
			}
			else
			{
				// получаем и отображаем нормали в точках пересечения
				if (water->getIntersection(pos + Vec3_up * 100, pos - Vec3_up * 100, oin, 0))
				{
					Visualizer::renderPoint3D(oin->getPoint(), intersect_point_size, vec4_green);
					Visualizer::renderVector(oin->getPoint(), oin->getPoint() + Vec3(oin->getNormal()), vec4_white);
				}

			}
		}
	}
}


```

</details>


### См. также


- C++ samples:

  -
  -
  -
  -
  -
- C# samples:

  -
  -
  -


## ObjectWaterGlobal Class

### Перечисления

## WAVES_MODE

| Name | Description |
|---|---|
| **WAVES_MODE_MANUAL** = 0 | Ручной режим генерации волн. |
| **WAVES_MODE_LAYERS** = 1 | Слоевой режим генерации волн. |
| **WAVES_MODE_BEAUFORTS** = 2 | Режим генерации волн по шкале Бофорта. |

## STEEPNESS_QUALITY

Точность вычисления крутизны, используемая при вычислении пересечений, а также при получении уровня воды (высоты) и ориентации нормали в заданной точке. Этот параметр используется для улучшения результатов вычислений в случае высокой крутизны волн (более высокие уровни Бофорта). Низкого качества обычно достаточно для спокойной воды (*high* обеспечивает хорошие результаты для 6-7 баллов Бофорта, а *ultra* рекомендуется для 8-10 баллов; если результат всё ещё не устраивает, можно использовать *extreme*).
| Name | Description |
|---|---|
| **STEEPNESS_QUALITY_LOW** = 0 | По умолчанию. Низкое качество вычисления крутизны волн. |
| **STEEPNESS_QUALITY_MEDIUM** = 1 | Среднее качество вычисления крутизны волн. |
| **STEEPNESS_QUALITY_HIGH** = 2 | Высокое качество вычисления крутизны волн. |
| **STEEPNESS_QUALITY_ULTRA** = 3 | Ультра качество вычисления крутизны волн. |
| **STEEPNESS_QUALITY_EXTREME** = 4 | Экстремальное качество вычисления крутизны волн. Значительно влияет на производительность. |

## PLANAR_REFLECTION_SIZE

| Name | Description |
|---|---|
| **PLANAR_REFLECTION_SIZE_RESOLUTION_128** = 0 | Изображение отражения с разрешением 128x128. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_256** = 1 | Изображение отражения с разрешением 256x256. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_512** = 2 | Изображение отражения с разрешением 512x512. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_1024** = 3 | Изображение отражения с разрешением 1024x1024. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_2048** = 4 | Изображение отражения с разрешением 2048x2048. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_4096** = 5 | Изображение отражения с разрешением 4096x4096. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_HEIGHT_QUART** = 6 | Изображение отражения с разрешением *height/4* x *height/4*, где height — высота окна приложения. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_HEIGHT_HALF** = 7 | Изображение отражения с разрешением *height/2* x *height/2*, где height — высота окна приложения. |
| **PLANAR_REFLECTION_SIZE_RESOLUTION_HEIGHT** = 8 | Изображение отражения с разрешением *height* x *height*, где height — высота окна приложения. |

### Методы класса

---

## static ObjectWaterGlobalPtr create ( )

Конструктор. Создаёт новый объект глобальной воды.
## int getPhysicsFieldMask ( ) const

Возвращает физическую маску FieldHeight назначенного материала на Global Water.
### Возвращаемое значение

Физическая маска FieldHeight.
## int getVisualFieldMask ( ) const

Возвращает визуальную маску FieldHeight назначенного материала на Global Water.
### Возвращаемое значение

Визуальная маска FieldHeight.
## float getMeanLevel ( ) const

Возвращает среднюю координату Z объекта воды.
### Возвращаемое значение

Значение координаты Z.
## void setAnimationTime ( float time )


Задаёт значение времени анимации воды для синхронизации воды. Используется для эффектов, таких как нормали, каустика и пена.


### Аргументы

- *float* **time** - Значение времени анимации воды.

## float getAnimationTime ( ) const

Возвращает значение времени анимации воды для синхронизации воды.
### Возвращаемое значение

Значение времени анимации воды.
## void setLayerName ( int layer , const char * value )

Задаёт новое имя слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя
- *const char ** **value** - Имя слоя.

## const char * getLayerName ( int layer ) const

Возвращает имя слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

### Возвращаемое значение

Имя слоя
## void setLayerWeight ( int layer , float value )

Задаёт вес для указанного слоя волн. Это значение определяет, насколько данный слой влияет на итоговую форму волны. Может использоваться для плавных переходов между состояниями воды. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя
- *float* **value** - Вес слоя

## float getLayerWeight ( int layer ) const

Возвращает текущий вес слоя волн. Это значение определяет, насколько данный слой влияет на итоговую форму волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

### Возвращаемое значение

Вес слоя.
## void setLayerDirectionAngleVariance ( int layer , float value )

Задаёт значение разброса угла направления волны для указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя
- *float* **value** - Значение разброса.

## float getLayerDirectionAngleVariance ( int layer ) const

Возвращает текущее значение разброса угла направления волны для указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

### Возвращаемое значение

Значение разброса.
## void setLayerSteepnessScale ( int layer , float value )

Задаёт значение [steepness scale](../../../objects/objects/water/water_object.md#steepness_scale) для указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя
- *float* **value** - Значение масштаба крутизны.

## float getLayerSteepnessScale ( int layer ) const

Возвращает текущее значение [steepness scale](../../../objects/objects/water/water_object.md#steepness_scale) для указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

### Возвращаемое значение

Значение масштаба крутизны.
## void setLayerAmplitudeRange ( int layer , const Math::vec2& value )

Задаёт диапазон амплитуд волн для указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя.
- *const  Math::vec2&* **value** - Диапазон амплитуд.

## Math:: vec2 getLayerAmplitudeRange ( int layer ) const

Возвращает текущий диапазон амплитуд волн указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя.

### Возвращаемое значение

Диапазон амплитуд.
## void setLayerLengthRange ( int layer , const Math::vec2& value )

Задаёт диапазон длин волн для указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя
- *const  Math::vec2&* **value** - Диапазон длин.

## Math:: vec2 getLayerLengthRange ( int layer ) const

Возвращает текущий диапазон длин волн указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

### Возвращаемое значение

Диапазон длин.
## void setLayerNumWaves ( int layer , int num )

Задаёт количество волн для указанного слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя
- *int* **num** - Количество волн.

## int getLayerNumWaves ( int layer ) const

Возвращает количество волн на указанном слое волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

### Возвращаемое значение

Количество волн.
## bool isLayerEnabled ( int layer ) const

Возвращает значение, указывающее, включён ли указанный слой волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

### Возвращаемое значение

true, если слой включён; иначе false.
## void setLayerEnabled ( int layer , bool enabled )

Включает или отключает указанный слой волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя
- *bool* **enabled** - true для включения слоя, false для отключения.

## void swapLayer ( int num_0 , int num_1 )

Меняет местами два указанных слоя волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **num_0** - Номер слоя 1.
- *int* **num_1** - Номер слоя 2.

## int getNumLayers ( ) const

Возвращает текущее количество слоёв волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Возвращаемое значение

Количество слоёв волн.
## void removeLayer ( int layer )

Удаляет указанный слой волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Аргументы

- *int* **layer** - Номер слоя

## int addLayer ( )

Добавляет новый слой волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Layers*.
### Возвращаемое значение

Номер нового добавленного слоя.
## void setWavePhaseOffset ( int index , float value )

Задаёт параметр смещения фазы для указанной волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.
- *float* **value** - Значение параметра смещения фазы, в радианах, в диапазоне [0; 2pi].

## float getWavePhaseOffset ( int index ) const

Возвращает значение параметра Phase Offset волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.

### Возвращаемое значение

Значение параметра смещения фазы, в радианах, в диапазоне [0; 2pi].
## void setWaveDirectionAngle ( int index , float value )

Задаёт направление (угол распространения) для указанной волны:
- Если указано 0, волна распространяется вдоль оси Y и параллельна оси X.
- Если указано положительное значение, направление волны наклонено против часовой стрелки относительно исходного распространения.
- Если указано отрицательное значение, волна поворачивается по часовой стрелке.


Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.


### Аргументы

- *int* **index** - Номер волны.
- *float* **value** - Угол, в градусах. Допустимы как положительные, так и отрицательные значения.

## float getWaveDirectionAngle ( int index ) const

Возвращает направление (угол распространения) указанной волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.

### Возвращаемое значение

Угол, в градусах.
## void setWaveSteepness ( int index , float value )

Задаёт значение крутизны для указанной волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.
- *float* **value** - Значение крутизны.

## float getWaveSteepness ( int index ) const

Возвращает текущее значение крутизны указанной волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.

### Возвращаемое значение

Значение крутизны.
## void setWaveAmplitude ( int index , float value )

Задаёт расстояние между наивысшим и наинизшим пиками для указанной волны. Задаёт форму волны вместе с функцией [setWaveLength()](#setWaveLength_int_float_void). Чем выше значение, тем выше волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.
- *float* **value** - Амплитуда, в единицах.

## float getWaveAmplitude ( int index ) const

Возвращает расстояние между наивысшим и наинизшим пиками указанной волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.

### Возвращаемое значение

Амплитуда, в единицах.
## void setWaveLength ( int index , float value )

Задаёт расстояние между последовательными гребнями для указанной волны. Чем больше значение длины, тем шире волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.
- *float* **value** - Длина, в единицах.

## float getWaveLength ( int index ) const

Возвращает расстояние между последовательными гребнями указанной волны. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.

### Возвращаемое значение

Длина, в единицах.
## int getNumWaves ( ) const

Возвращает текущее количество симулируемых волн. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Возвращаемое значение

Количество волн.
## void removeWave ( int index )

Удаляет волну с указанным номером. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *int* **index** - Номер волны.

## int addWave ( float length , float amplitude , float steepness , float direction_angle , float phase )

Добавляет волну, если [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Manual*.
### Аргументы

- *float* **length** - Длина волны.
- *float* **amplitude** - Амплитуда волны.
- *float* **steepness** - Крутизна волны.
- *float* **direction_angle** - Угол направления волны, в градусах. При угле 0 волна будет направлена вдоль оси X.
- *float* **phase** - Смещение фазы волны, в радианах (от 0 до 2pi).

### Возвращаемое значение

Номер добавленной волны.
## float getWindAffect ( ) const

Возвращает текущее значение, определяющее, насколько направление ветра влияет на волны.
### Возвращаемое значение

Значение влияния ветра в диапазоне [0;1].
## void setWindAffect ( float affect )

Задаёт, насколько направление ветра влияет на волны.
### Аргументы

- *float* **affect** - Влияние ветра в диапазоне [0;1]. При значении 1 все волны будут направлены вдоль направления ветра.

## float getWindDirectionAngle ( ) const

Возвращает угол, определяющий направление ветра.
### Возвращаемое значение

Угол, в градусах.
## void setWindDirectionAngle ( float angle )

Задаёт угол, определяющий направление ветра.
### Аргументы

- *float* **angle** - Угол направления ветра, в градусах.

## static int type ( )

Возвращает тип узла.
### Возвращаемое значение

Идентификатор типа [Object](../../../api/library/objects/class.object_cpp.md).
## void setActiveWater ( bool water )

Задаёт значение, указывающее, является ли объект глобальной воды активным. Если в сцене несколько узлов глобальной воды, будет отрисован только активный.
### Аргументы

- *bool* **water** - true, чтобы сделать объект глобальной воды активным; false — неактивным.

## bool isActiveWater ( ) const

Возвращает значение, указывающее, является ли объект глобальной воды активным.
### Возвращаемое значение

true, если объект глобальной воды активен; false — если неактивен.
## float fetchHeight ( const Math:: Vec3 & position ) const

Возвращает смещение высоты указанной точки относительно текущего уровня воды, вычисленного для этой точки. Например, если указанная точка (0, 0, -3), а текущий уровень воды, вычисленный для этой точки, равен 5, функция вернёт 8.


![](fetch.png)


> **Notice:** В случае более высоких уровней Бофорта (приводящих к значительной крутизне волн и перепадам высот на поверхности воды) результаты вычислений могут отличаться от визуального представления (например, вычисленный уровень воды может быть больше фактического значения). Чтобы избежать этого и повысить точность, [adjust calculation quality](#fetch).

### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Координаты позиции точки.

### Возвращаемое значение

Смещение высоты указанной точки относительно текущего уровня воды, вычисленного для этой точки, в метрах.
## Math:: vec3 fetchNormal ( const Math:: Vec3 & position ) const

Возвращает вектор нормали к поверхности воды в указанной точке (для ориентации объектов вдоль нормалей волн).
> **Notice:** В случае более высоких уровней Бофорта (приводящих к значительной крутизне волн и перепадам высот на поверхности воды) результаты вычислений могут отличаться от визуального представления (например, вычисленный уровень воды может быть больше фактического значения). Чтобы избежать этого и повысить точность, [adjust calculation quality](#fetch).

### Аргументы

- *const  Math::[Vec3](../../../api/library/math/class.vec3_cpp.md) &* **position** - Координаты позиции точки.

### Возвращаемое значение

Вектор нормали.
## void setFetchAmplitudeThreshold ( float threshold )

Задаёт порог значений амплитуды, которые не будут участвовать в [height and normal calculations](#fetch). Чем больше вы отсекаете, тем менее точное значение высоты вы получаете, но тем быстрее выполняются вычисления.
### Аргументы

- *float* **threshold** - Порог амплитуды. Значение по умолчанию: 0.1f.

## float getFetchAmplitudeThreshold ( ) const

Возвращает текущий порог значений амплитуды, которые не будут участвовать в [height and normal calculations](#fetch).
### Возвращаемое значение

Порог амплитуды.
## void setFetchSteepnessQuality ( ObjectWaterGlobal::STEEPNESS_QUALITY quality )

Задаёт качество вычисления крутизны волн, используемое при [height and normal calculations](#fetch). Низкого качества обычно достаточно для спокойной воды и крупных плавающих объектов. Если волны большие или вы хотите симулировать небольшие плавающие объекты, может потребоваться повысить качество. Более высокое качество даёт более точный результат, но влияет на производительность.
### Аргументы

- *[ObjectWaterGlobal::STEEPNESS_QUALITY](../../../api/library/objects/class.objectwaterglobal_cpp.md#STEEPNESS_QUALITY)* **quality** - Значение качества.

## ObjectWaterGlobal::STEEPNESS_QUALITY getFetchSteepnessQuality ( ) const

Возвращает качество вычисления крутизны волн, используемое при [height and normal calculations](#fetch).
### Возвращаемое значение

Качество крутизны. Значение по умолчанию: [STEEPNESS_QUALITY_LOW](../../../api/library/objects/class.objectwaterglobal_cpp.md#STEEPNESS_QUALITY_LOW).
## float getIntersectionAmplitudeThreshold ( ) const

Возвращает текущий порог значений амплитуды, которые не будут участвовать в [intersection calculations](#intersections).
### Возвращаемое значение

Порог амплитуды.
## void setIntersectionAmplitudeThreshold ( float threshold )

Задаёт порог значений амплитуды, которые не будут участвовать в [intersection calculations](#intersections). Значение по умолчанию: 0.1f.
### Аргументы

- *float* **threshold** - Порог амплитуды.

## void setIntersectionPrecision ( float precision )

Задаёт точность пересечения, представляющую погрешность между реальным значением точки пересечения с водой и вычисленным значением. Значение по умолчанию: 0.25.
### Аргументы

- *float* **precision** - Точность определения пересечения.

## float getIntersectionPrecision ( ) const

Возвращает текущую точность пересечения, представляющую погрешность между реальным значением точки пересечения с водой и вычисленным значением.
### Возвращаемое значение

Точность определения пересечения.
## void setIntersectionSteepnessQuality ( ObjectWaterGlobal::STEEPNESS_QUALITY quality )

Задаёт качество вычисления крутизны волн, используемое при [intersection calculations](#intersections). Низкого качества обычно достаточно для спокойной воды и крупных плавающих объектов. Если волны большие или вы хотите симулировать небольшие плавающие объекты, может потребоваться повысить качество. Более высокое качество даёт более точный результат, но влияет на производительность.
### Аргументы

- *[ObjectWaterGlobal::STEEPNESS_QUALITY](../../../api/library/objects/class.objectwaterglobal_cpp.md#STEEPNESS_QUALITY)* **quality** - Качество крутизны. Значение по умолчанию: [STEEPNESS_QUALITY_LOW](../../../api/library/objects/class.objectwaterglobal_cpp.md#STEEPNESS_QUALITY_LOW).

## ObjectWaterGlobal::STEEPNESS_QUALITY getIntersectionSteepnessQuality ( ) const

Возвращает качество вычисления крутизны волн, используемое при [intersection calculations](#intersections). Низкого качества обычно достаточно для спокойной воды и крупных плавающих объектов. Если волны большие или вы хотите симулировать небольшие плавающие объекты, может потребоваться повысить качество. Более высокое качество даёт более точный результат, но влияет на производительность.
### Возвращаемое значение

Качество крутизны.
## void setSoftInteraction ( float intersection )

Задаёт мягкое пересечение воды с береговой линией и поверхностями объектов.
### Аргументы

- *float* **intersection** - Значение мягкого пересечения.

## float getSoftInteraction ( ) const

Возвращает текущее мягкое пересечение воды с береговой линией и поверхностями объектов.
### Возвращаемое значение

Значение мягкого пересечения.
## void takeSyncData ( const Ptr < Stream > & stream )

Записывает данные синхронизации волн в указанный поток.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток, в который записываются данные синхронизации волн.

## void applySyncData ( const Ptr < Stream > & stream )

Считывает данные синхронизации волн из указанного потока и применяет их к системе волн.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Stream](../../../api/library/common/class.stream_cpp.md)> &* **stream** - Поток с данными синхронизации волн, которые нужно применить.

## void setWavesMode ( ObjectWaterGlobal::WAVES_MODE mode )

Задаёт [wave generation mode](../../../objects/objects/water/water_object.md#creating_waves).
### Аргументы

- *[ObjectWaterGlobal::WAVES_MODE](../../../api/library/objects/class.objectwaterglobal_cpp.md#WAVES_MODE)* **mode** - Требуемый режим волн.

## ObjectWaterGlobal::WAVES_MODE getWavesMode ( ) const

Возвращает текущий [wave generation mode](../../../objects/objects/water/water_object.md#creating_waves).
### Возвращаемое значение

Режим волн.
## void setBeaufort ( float beaufort )

Задаёт значение шкалы силы ветра Бофорта.
### Аргументы

- *float* **beaufort** - Значение Бофорта от 0 (штиль) до 12 (ураган). Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Beauforts*.

## float getBeaufort ( ) const

Возвращает текущее значение шкалы силы ветра Бофорта. Доступно, когда [is set](../../../api/library/objects/class.objectwaterglobal_cpp.md#setWavesMode_int_void) режим *Beauforts*.
### Возвращаемое значение

Значение Бофорта.
## void setGeometryNormalIntensity ( float intensity )

Задаёт интенсивность нормалей волн.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getGeometryNormalIntensity ( ) const

Возвращает текущую интенсивность нормалей волн.
### Возвращаемое значение

Значение интенсивности.
## void setTextureNormalBlur ( float blur )

Задаёт коэффициент размытия для процедурно генерируемых нормалей. Этот параметр позволяет уменьшить пикселизацию карты нормалей и сделать её менее выраженной. При необходимости коррекции рекомендуется использовать небольшие значения. Влияет на нормали, генерируемые для [Field Height](../../../objects/effects/fields/field_height/index.md) и [Field Shoreline](../../../objects/effects/fields/field_shoreline/index.md).
### Аргументы

- *float* **blur** - Значение размытия нормали.

## float getTextureNormalBlur ( ) const

Возвращает текущий коэффициент размытия для процедурно генерируемых нормалей. Этот параметр позволяет уменьшить пикселизацию карты нормалей и сделать её менее выраженной. При необходимости коррекции рекомендуется использовать небольшие значения. Влияет на нормали, генерируемые для [Field Height](../../../objects/effects/fields/field_height/index.md) и [Field Shoreline](../../../objects/effects/fields/field_shoreline/index.md).
### Возвращаемое значение

Значение размытия нормали.
## void setTextureNormalIntensity ( float intensity )

Задаёт интенсивность процедурно генерируемых нормалей. Влияет на нормали, генерируемые для [Field Height](../../../objects/effects/fields/field_height/index.md) и [Field Shoreline](../../../objects/effects/fields/field_shoreline/index.md).
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getTextureNormalIntensity ( ) const

Возвращает текущую интенсивность процедурно генерируемых нормалей. Влияет на нормали, генерируемые для [Field Height](../../../objects/effects/fields/field_height/index.md) и [Field Shoreline](../../../objects/effects/fields/field_shoreline/index.md).
### Возвращаемое значение

Значение интенсивности.
## void setDetailTexturePath ( const char * path )

Задаёт путь к расположению [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Аргументы

- *const char ** **path** - Путь к детализирующей текстуре.

## const char * getDetailTexturePath ( ) const

Возвращает текущий путь к расположению [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Возвращаемое значение

Путь к детализирующей текстуре.
## void setDetail0UVSize ( const Math::vec2& size )

Задаёт размер первого сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Аргументы

- *const  Math::vec2&* **size** - Значение размера.

## Math:: vec2 getDetail0UVSize ( ) const

Возвращает текущий размер первого сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Возвращаемое значение

Значение размера.
## void setDetail0UVSpeed ( const Math::vec2& speed )

Задаёт скорость первого сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Аргументы

- *const  Math::vec2&* **speed** - Значение скорости.

## Math:: vec2 getDetail0UVSpeed ( ) const

Возвращает текущую скорость первого сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Возвращаемое значение

Значение скорости.
## void setDetail0Intensity ( float intensity )

Задаёт интенсивность первого сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getDetail0Intensity ( ) const

Возвращает текущую интенсивность первого сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Возвращаемое значение

Значение интенсивности.
## void setDetail1UVSize ( const Math::vec2& size )

Задаёт размер второго сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Аргументы

- *const  Math::vec2&* **size** - Значение размера.

## Math:: vec2 getDetail1UVSize ( ) const

Возвращает текущий размер второго сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Возвращаемое значение

Значение размера.
## void setDetail1UVSpeed ( const Math::vec2& speed )

Задаёт скорость второго сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Аргументы

- *const  Math::vec2&* **speed** - Скорость детализирующей текстуры.

## Math:: vec2 getDetail1UVSpeed ( ) const

Возвращает текущую скорость второго сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Возвращаемое значение

Значение скорости.
## void setDetail1Intensity ( float intensity )

Задаёт интенсивность второго сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getDetail1Intensity ( ) const

Возвращает текущую интенсивность первого сэмпла [normal detail texture](../../../objects/objects/water/water_object.md#detail_normal_map).
### Возвращаемое значение

Значение интенсивности.
## void setDistantWavesTexturePath ( const char * path )

Задаёт путь к [normal map](../../../objects/objects/water/water_object.md#distant_waves_normal_map) [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Аргументы

- *const char ** **path** - Путь к [normal map](../../../objects/objects/water/water_object.md#distant_waves_normal_map).

## const char * getDistantWavesTexturePath ( ) const

Возвращает текущий путь к [normal map](../../../objects/objects/water/water_object.md#distant_waves_normal_map) [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Возвращаемое значение

Путь к [normal map](../../../objects/objects/water/water_object.md#distant_waves_normal_map).
## void setDistantWavesUVTransform ( const Math::vec4& transform )

Задаёт UV-трансформацию для карты нормалей [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Аргументы

- *const  Math::vec4&* **transform** - Первые два значения (x, y) представляют масштаб текстурных координат по осям X и Y. Третье и четвёртое значения (z, w) задают скорость анимации движения.

## Math:: vec4 getDistantWavesUVTransform ( ) const

Возвращает текущую UV-трансформацию для карты нормалей [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Возвращаемое значение

Первые два значения (x, y) представляют масштаб текстурных координат по осям X и Y. Третье и четвёртое значения (z, w) задают скорость анимации движения.
## void setDistantWavesIntensity ( float scale )

Задаёт интенсивность для [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
> **Notice:** Недоступно для режимов со смешиванием уровней Бофорта.

### Аргументы

- *float* **scale** - Значение интенсивности.

## float getDistantWavesIntensity ( ) const

Возвращает текущее значение интенсивности для [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
> **Notice:** Недоступно для режимов со смешиванием уровней Бофорта.

### Возвращаемое значение

Значение интенсивности.
## void setDistantWavesBlendDistanceStart ( float start )

Задаёт начальную дистанцию проявления (fade-in) для [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Аргументы

- *float* **start** - Начальная дистанция проявления.

## float getDistantWavesBlendDistanceStart ( ) const

Возвращает текущую начальную дистанцию проявления (fade-in) для [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Возвращаемое значение

Начальная дистанция проявления.
## void setDistantWavesBlendDistanceEnd ( float end )

Задаёт конечную дистанцию проявления (fade-in) для [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Аргументы

- *float* **end** - Конечная дистанция проявления.

## float getDistantWavesBlendDistanceEnd ( ) const

Возвращает текущую конечную дистанцию проявления (fade-in) для [distant waves](../../../objects/objects/water/water_object.md#distant_waves).
### Возвращаемое значение

Конечная дистанция затухания.
## void setDistantWavesBlendMax ( float value )

Задаёт значение, представляющее максимальную долю [distant waves](../../../objects/objects/water/water_object.md#distant_waves) в зоне перекрёстного затухания, где основные геометрические волны исчезают, а дальние волны проявляются.
### Аргументы

- *float* **value** - Значение, представляющее максимальную долю дальних волн. Диапазон: [0; 1], значение по умолчанию: 0.

## float getDistantWavesBlendMax ( ) const

Возвращает текущее значение, представляющее максимальную долю [distant waves](../../../objects/objects/water/water_object.md#distant_waves) в зоне перекрёстного затухания, где основные геометрические волны исчезают, а дальние волны проявляются.
### Возвращаемое значение

Значение, представляющее максимальную долю дальних волн.
## void setDistantWavesBlendMin ( float value )

Задаёт значение, представляющее минимальную долю [distant waves](../../../objects/objects/water/water_object.md#distant_waves) в зоне перекрёстного затухания, где основные геометрические волны исчезают, а дальние волны проявляются.
### Аргументы

- *float* **value** - Значение, представляющее минимальную долю дальних волн. Диапазон: [0; 1], значение по умолчанию: 0.

## float getDistantWavesBlendMin ( ) const

Возвращает текущее значение, представляющее минимальную долю [distant waves](../../../objects/objects/water/water_object.md#distant_waves) в зоне перекрёстного затухания, где основные геометрические волны исчезают, а дальние волны проявляются.
### Возвращаемое значение

Значение, представляющее минимальную долю дальних волн.
## void setFoamTexturePath ( const char * path )

Задаёт путь к [foam texture](../../../objects/objects/water/water_object.md#texture).
### Аргументы

- *const char ** **path** - Путь к текстуре пены.

## const char * getFoamTexturePath ( ) const

Возвращает текущий путь к [foam texture](../../../objects/objects/water/water_object.md#texture).
### Возвращаемое значение

Путь к текстуре пены.
## void setFoam0UVScale ( float scale )

Задаёт UV-масштаб для первого сэмпла текстуры пены.
### Аргументы

- *float* **scale** - Значение масштаба.

## float getFoam0UVScale ( ) const

Возвращает текущий UV-масштаб для первого сэмпла текстуры пены.
### Возвращаемое значение

Значение масштаба.
## void setFoam0UVSpeed ( float speed )

Задаёт скорость первого сэмпла текстуры пены.
### Аргументы

- *float* **speed** - Значение скорости.

## float getFoam0UVSpeed ( ) const

Возвращает текущую скорость первого сэмпла текстуры пены.
### Возвращаемое значение

Значение скорости.
## void setFoam1UVScale ( float scale )

Задаёт UV-масштаб для второго сэмпла текстуры пены.
### Аргументы

- *float* **scale** - Значение масштаба.

## float getFoam1UVScale ( ) const

Возвращает текущий UV-масштаб для второго сэмпла текстуры пены.
### Возвращаемое значение

Значение масштаба.
## void setFoam1UVSpeed ( float speed )

Задаёт скорость второго сэмпла текстуры пены.
### Аргументы

- *float* **speed** - Значение скорости.

## float getFoam1UVSpeed ( ) const

Возвращает текущую скорость второго сэмпла текстуры пены.
### Возвращаемое значение

Значение скорости.
## void setFoamPeakContrast ( float contrast )

Задаёт контраст пены на гребнях волн.
### Аргументы

- *float* **contrast** - Значение контраста.

## float getFoamPeakContrast ( ) const

Возвращает текущий контраст пены на гребнях волн.
### Возвращаемое значение

Значение контраста.
## void setFoamPeakIntensity ( float intensity )

Задаёт интенсивность пены на гребнях волн.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getFoamPeakIntensity ( ) const

Возвращает текущую интенсивность пены на гребнях волн.
### Возвращаемое значение

Значение интенсивности.
## void setFoamWhitecapContrast ( float contrast )

Задаёт контраст пены на белых барашках.
### Аргументы

- *float* **contrast** - Значение контраста.

## float getFoamWhitecapContrast ( ) const

Возвращает текущий контраст пены на белых барашках.
### Возвращаемое значение

Значение контраста.
## void setFoamWhitecapIntensity ( float intensity )

Задаёт интенсивность пены на белых барашках.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getFoamWhitecapIntensity ( ) const

Возвращает текущую интенсивность пены на белых барашках.
### Возвращаемое значение

Значение интенсивности.
## void setFoamWindContrast ( float contrast )

Задаёт контраст пены, генерируемой на основе направления ветра.
### Аргументы

- *float* **contrast** - Значение контраста.

## float getFoamWindContrast ( ) const

Возвращает текущий контраст пены, генерируемой на основе направления ветра.
### Возвращаемое значение

Значение контраста.
## void setFoamWindIntensity ( float intensity )

Задаёт интенсивность пены, генерируемой на основе направления ветра.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getFoamWindIntensity ( ) const

Возвращает текущую интенсивность пены, генерируемой на основе направления ветра.
### Возвращаемое значение

Значение интенсивности.
## void setFieldHeightFoamContrast ( float contrast )

Задаёт контраст пены, генерируемой объектами [FieldHeight](../../../objects/effects/fields/field_height/index.md), размещёнными в Global Water.
### Аргументы

- *float* **contrast** - Значение контраста.

## float getFieldHeightFoamContrast ( ) const

Возвращает текущий контраст пены, генерируемой объектами [FieldHeight](../../../objects/effects/fields/field_height/index.md), размещёнными в Global Water.
### Возвращаемое значение

Значение контраста.
## void setFieldHeightFoamIntensity ( float intensity )

Задаёт интенсивность пены, генерируемой объектами [FieldHeight](../../../objects/effects/fields/field_height/index.md), размещёнными в Global Water.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getFieldHeightFoamIntensity ( ) const

Возвращает текущую интенсивность пены, генерируемой объектами [FieldHeight](../../../objects/effects/fields/field_height/index.md), размещёнными в Global Water.
### Возвращаемое значение

Значение интенсивности.
## void setFoamContactIntensity ( float intensity )

Задаёт интенсивность пены вблизи берегов или различных объектов в воде.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getFoamContactIntensity ( ) const

Возвращает текущую интенсивность пены вблизи берегов или различных объектов в воде.
### Возвращаемое значение

Значение интенсивности.
## void setFoamTextureAffect ( float affect )

Задаёт видимость текстуры пены. Может использоваться для создания дополнительных эффектов, например, пузырьков пены.
### Аргументы

- *float* **affect** - Значение влияния текстуры.

## float getFoamTextureAffect ( ) const

Возвращает видимость текстуры пены.
### Возвращаемое значение

Значение влияния текстуры.
## void setSubsurfaceColor ( const Math::vec4& color )

Задаёт [water subsurface scattering (SSS) color](../../../objects/objects/water/water_object.md#color).
### Аргументы

- *const  Math::vec4&* **color** - Значение цвета.

## Math:: vec4 getSubsurfaceColor ( ) const

Возвращает текущий [water subsurface scattering (SSS) color](../../../objects/objects/water/water_object.md#color).
### Возвращаемое значение

Значение цвета.
## void setSubsurfaceAmbientIntensity ( float intensity )

Задаёт [intensity of subsurface scattering](../../../objects/objects/water/water_object.md#ambient_intensity) для окружающего освещения.
### Аргументы

- *float* **intensity** - Значение интенсивности. Чем ниже значение, тем быстрее световые лучи рассеиваются в воде.

## float getSubsurfaceAmbientIntensity ( ) const

Возвращает текущую [intensity of subsurface scattering](../../../objects/objects/water/water_object.md#ambient_intensity) для окружающего освещения.
### Возвращаемое значение

Значение интенсивности.
## void setSubsurfaceWaveIntensity ( float intensity )

Задаёт интенсивность [light rays passing through waves](../../../objects/objects/water/water_object.md#intensity_through_waves).
### Аргументы

- *float* **intensity** - Значение интенсивности. Чем ниже значение, тем быстрее световые лучи рассеиваются в воде.

## float getSubsurfaceWaveIntensity ( ) const

Возвращает текущую интенсивность [light rays passing through waves](../../../objects/objects/water/water_object.md#intensity_through_waves).
### Возвращаемое значение

Значение интенсивности.
## void setSubsurfaceWaveFoamIntensity ( float intensity )

Задаёт интенсивность [subsurface scattering near the foam areas](../../../objects/objects/water/water_object.md#intensity_around_foam).
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getSubsurfaceWaveFoamIntensity ( ) const

Возвращает текущую интенсивность подповерхностного рассеивания вблизи областей пены.
### Возвращаемое значение

Значение интенсивности.
## void setSubsurfaceDecalsIntensity ( float intensity )

Задаёт интенсивность подповерхностного рассеивания диффузного освещения для декалей.
### Аргументы

- *float* **intensity** - Новое значение интенсивности подповерхностного рассеивания, которое нужно задать.

## float getSubsurfaceDecalsIntensity ( ) const

Возвращает текущую интенсивность подповерхностного рассеивания диффузного освещения для декалей.
### Возвращаемое значение

Текущее значение интенсивности подповерхностного рассеивания.
## void setDepthLUTTexturePath ( const char * path )

Задаёт путь к [LUT texture](../../../objects/objects/water/water_object.md#depth_lut), отображающей цвет дна.
### Аргументы

- *const char ** **path** - Путь к текстуре.

## const char * getDepthLUTTexturePath ( ) const

Возвращает текущий путь к [LUT texture](../../../objects/objects/water/water_object.md#depth_lut), отображающей цвет дна.
### Возвращаемое значение

Путь к текстуре.
## void setUnderwaterFogColor ( const Math::vec4& color )

Задаёт [underwater fog color](../../../objects/objects/water/water_object.md#fog_color). Освещение от Sun и Environment влияет на этот параметр для создания итогового цвета подводного тумана.
### Аргументы

- *const  Math::vec4&* **color** - Значение цвета.

## Math:: vec4 getUnderwaterFogColor ( ) const

Возвращает текущий [underwater fog color](../../../objects/objects/water/water_object.md#fog_color).
### Возвращаемое значение

Значение цвета.
## void setUnderwaterFogTransparency ( float transparency )

Задаёт [transparency of the underwater fog](../../../objects/objects/water/water_object.md#fog_transparency).
### Аргументы

- *float* **transparency** - Значение прозрачности. Чем выше значение, тем прозрачнее подводный туман.

## float getUnderwaterFogTransparency ( ) const

Возвращает текущую [transparency of the underwater fog](../../../objects/objects/water/water_object.md#fog_transparency).
### Возвращаемое значение

Значение прозрачности.
## void setUnderwaterFogDepth ( float depth )

Задаёт [distance from the water surface](../../../objects/objects/water/water_object.md#fog_lighting_depth), до которого свет влияет на подводный цвет.
### Аргументы

- *float* **depth** - Значение глубины, в единицах.

## float getUnderwaterFogDepth ( ) const

Возвращает текущее [distance from the water surface](../../../objects/objects/water/water_object.md#fog_lighting_depth), до которого свет влияет на подводный цвет.
### Возвращаемое значение

Значение глубины, в единицах.
## void setUnderwaterFogOffset ( float offset )

Задаёт смещение по высоте для освещения.
### Аргументы

- *float* **offset** - Значение смещения.

## float getUnderwaterFogOffset ( ) const

Возвращает текущее смещение по высоте для освещения.
### Возвращаемое значение

Значение смещения.
## void setUnderwaterFogEnvironmentInfluence ( float influence )

Задаёт степень влияния окружающего освещения на итоговый подводный цвет.
### Аргументы

- *float* **influence** - Значение влияния.

## float getUnderwaterFogEnvironmentInfluence ( ) const

Возвращает текущую степень влияния окружающего освещения на итоговый подводный цвет.
### Возвращаемое значение

Значение влияния.
## void setUnderwaterFogSunInfluence ( float influence )

Задаёт степень влияния солнечного освещения на итоговый подводный цвет.
### Аргументы

- *float* **influence** - Значение влияния.

## float getUnderwaterFogSunInfluence ( ) const

Возвращает текущую степень влияния солнечного освещения на итоговый подводный цвет.
### Возвращаемое значение

Значение влияния.
## void setUnderwaterShaftIntensity ( float intensity )

Задаёт интенсивность подводных световых лучей солнца.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getUnderwaterShaftIntensity ( ) const

Возвращает текущую интенсивность подводных световых лучей солнца.
### Возвращаемое значение

Значение интенсивности.
## void setWaterlineSize ( float size )

Задаёт [size of the borderline](../../../objects/objects/water/water_object.md#waterline_size) между надводной и подводной средой.
### Аргументы

- *float* **size** - Размер линии воды.

## float getWaterlineSize ( ) const

Возвращает текущий [size of the borderline](../../../objects/objects/water/water_object.md#waterline_size) между надводной и подводной средой.
### Возвращаемое значение

Размер линии воды.
## void setUnderwaterDofDistance ( float distance )

Задаёт фокусное расстояние для [underwater DOF effect](../../../objects/objects/water/water_object.md#underwater_dof).
### Аргументы

- *float* **distance** - Фокусное расстояние.

## float getUnderwaterDofDistance ( ) const

Возвращает текущее фокусное расстояние для [underwater DOF effect](../../../objects/objects/water/water_object.md#underwater_dof).
### Возвращаемое значение

Фокусное расстояние.
## void setPlanarReflectionDistance ( float distance )

Задаёт расстояние от камеры области просмотра отражения до отражаемого объекта. Это расстояние равно сумме расстояния от камеры до отражающей поверхности и расстояния от объекта до отражающей поверхности.
### Аргументы

- *float* **distance** - Расстояние, в единицах.

## float getPlanarReflectionDistance ( ) const

Возвращает текущее расстояние от камеры области просмотра отражения до отражаемого объекта. Это расстояние равно сумме расстояния от камеры до отражающей поверхности и расстояния от объекта до отражающей поверхности.
### Возвращаемое значение

Расстояние, в единицах.
## void setPlanarReflectionPivotOffset ( const Math::vec3& offset )

Задаёт позицию опорной точки отражения.
### Аргументы

- *const  Math::vec3&* **offset** - Смещение опорной точки.

## Math:: vec3 getPlanarReflectionPivotOffset ( ) const

Возвращает текущую позицию опорной точки отражения.
### Возвращаемое значение

Смещение опорной точки.
## void setReflectionRoughness ( float roughness )

Задаёт [reflection roughness](../../../objects/objects/water/water_object.md#roughness) окружения на поверхности воды. Этот параметр помогает настраивать отражения на поверхности воды относительно окружения.
### Аргументы

- *float* **roughness** - Значение шероховатости.

## float getReflectionRoughness ( ) const

Возвращает текущую [reflection roughness](../../../objects/objects/water/water_object.md#roughness) окружения на поверхности воды. Этот параметр помогает настраивать отражения на поверхности воды относительно окружения.
### Возвращаемое значение

Значение шероховатости.
## void setReflectionOcclusion ( float occlusion )

Задаёт [occlusion factor for environment reflections](../../../objects/objects/water/water_object.md#occlusion) на участках поверхности воды с отрицательными нормалями. Использование этого параметра позволяет симулировать отражение волн на поверхности воды, устраняя слишком яркие области на волнах вблизи горизонта.
### Аргументы

- *float* **occlusion** - Значение окклюзии. Минимальное значение — 0 (без окклюзии). При более высоких значениях окклюзия применяется к отражениям на участках поверхности воды с отрицательными нормалями, имеющими определённый наклон. Чем выше значение, тем менее интенсивны отражения на участках поверхности с отрицательными нормалями.

## float getReflectionOcclusion ( ) const

Возвращает текущий [occlusion factor for environment reflections](../../../objects/objects/water/water_object.md#occlusion) на участках поверхности воды с отрицательными нормалями. Использование этого параметра позволяет симулировать отражение волн на поверхности воды, устраняя слишком яркие области на волнах вблизи горизонта.
### Возвращаемое значение

Значение окклюзии.
## void setReflectionOcclusionSlope ( float slope )

Задаёт наклон отрицательных нормалей поверхности воды, при котором выполняется окклюзия для отражений волн.
### Аргументы

- *float* **slope** - Значение наклона.

## float getReflectionOcclusionSlope ( ) const

Возвращает текущий наклон отрицательных нормалей поверхности воды, при котором выполняется окклюзия для отражений волн.
### Возвращаемое значение

Значение наклона.
## void setCausticsTexturePath ( const char * path )

Задаёт путь к [3D Caustic texture](../../../objects/objects/water/water_object.md#caustics_texture), определяющей [pattern of light rays](../../../objects/objects/water/water_object.md#enable_caustics), преломлённых поверхностью воды. Текстура одноканальная: значение *R* определяет узор каустики.
### Аргументы

- *const char ** **path** - Путь к текстуре.

## const char * getCausticsTexturePath ( ) const

Возвращает текущий путь к [3D Caustic texture](../../../objects/objects/water/water_object.md#caustics_texture), определяющей [pattern of light rays](../../../objects/objects/water/water_object.md#enable_caustics), преломлённых поверхностью воды.
### Возвращаемое значение

Путь к текстуре.
## void setCausticUVTransform ( const Math::vec4& transform )

Задаёт координаты [UV Transform](../../../objects/objects/water/water_object.md#caustics_uv_transform) для текстуры каустики.
### Аргументы

- *const  Math::vec4&* **transform** - Координаты трансформации.

## Math:: vec4 getCausticUVTransform ( ) const

Возвращает текущие координаты [UV Transform](../../../objects/objects/water/water_object.md#caustics_uv_transform) для текстуры каустики.
### Возвращаемое значение

Координаты трансформации.
## void setCausticDistanceFade ( float fade )

Задаёт [distance from the water surface](../../../objects/objects/water/water_object.md#caustics_distance_fade) вниз, на котором световые узоры затухают.
### Аргументы

- *float* **fade** - Расстояние, в единицах.

## float getCausticDistanceFade ( ) const

Возвращает текущее [distance from the water surface](../../../objects/objects/water/water_object.md#caustics_distance_fade) вниз, на котором световые узоры затухают.
### Возвращаемое значение

Расстояние, в единицах.
## void setCausticAnimationSpeed ( float speed )

Задаёт скорость движения световых узоров.
### Аргументы

- *float* **speed** - Значение скорости.

## float getCausticAnimationSpeed ( ) const

Возвращает текущую скорость движения световых узоров.
### Возвращаемое значение

Значение скорости.
## void setCausticBrightness ( float brightness )

Задаёт яркость световых узоров.
### Аргументы

- *float* **brightness** - Значение яркости.

## float getCausticBrightness ( ) const

Возвращает текущую яркость световых узоров.
### Возвращаемое значение

Значение яркости.
## void setFieldShorelineLUTTexturePath ( const char * path )

Задаёт путь к LUT-текстуре, используемой для эффекта влажности береговой линии.
### Аргументы

- *const char ** **path** - Путь к текстуре.

## const char * getFieldShorelineLUTTexturePath ( ) const

Возвращает текущий путь к LUT-текстуре, используемой для эффекта влажности береговой линии.
### Возвращаемое значение

Путь к текстуре.
## void setFieldShorelineWaveSpeed ( float speed )

Задаёт скорость приливных волн.
### Аргументы

- *float* **speed** - Значение скорости волн.

## float getFieldShorelineWaveSpeed ( ) const

Возвращает текущую скорость приливных волн.
### Возвращаемое значение

Значение скорости волн.
## void setFieldShorelineWaveTiling ( float tiling )

Задаёт частоту приливных волн.
### Аргументы

- *float* **tiling** - Значение частоты повторения.

## float getFieldShorelineWaveTiling ( ) const

Возвращает текущую частоту приливных волн.
### Возвращаемое значение

Значение частоты повторения.
## void setFieldShorelineWaveHeight ( float height )

Задаёт высоту набегающих приливных волн.
### Аргументы

- *float* **height** - Значение высоты.

## float getFieldShorelineWaveHeight ( ) const

Возвращает текущую высоту набегающих приливных волн.
### Возвращаемое значение

Значение высоты.
## void setFieldShorelineWaveFalloff ( float falloff )

Задаёт градиент видимости волн, набегающих с моря на берег.
### Аргументы

- *float* **falloff** - Значение затухания.

## float getFieldShorelineWaveFalloff ( ) const

Возвращает текущий градиент видимости волн, набегающих с моря на берег.
### Возвращаемое значение

Значение затухания.
## void setFieldShorelineWaveExponent ( float exponent )

Задаёт нелинейность частоты и скорости движения приливных волн в зависимости от их расстояния от береговой линии.
### Аргументы

- *float* **exponent** - Значение показателя степени.

## float getFieldShorelineWaveExponent ( ) const

Возвращает текущую нелинейность частоты и скорости движения приливных волн.
### Возвращаемое значение

Значение показателя степени.
## void setFieldShorelineWaveFrontExponent ( float exponent )

Задаёт полупрозрачность пены под углом к направлению ветра. Позволяет делать пену видимой только с наветренной стороны.
### Аргументы

- *float* **exponent** - Значение показателя степени.

## float getFieldShorelineWaveFrontExponent ( ) const

Возвращает текущую полупрозрачность пены под углом к направлению ветра. Позволяет делать пену видимой только с наветренной стороны.
### Возвращаемое значение

Значение показателя степени.
## void setFieldShorelineFoamStretching ( float stretching )

Задаёт ширину LUT-текстуры Shoreline, создающей приливную волну.
### Аргументы

- *float* **stretching** - Значение растяжения.

## float getFieldShorelineFoamStretching ( ) const

Возвращает текущую ширину LUT-текстуры Shoreline, создающей приливную волну.
### Возвращаемое значение

Значение растяжения.
## void setFieldShorelineFoamIntensity ( float intensity )

Задаёт степень интенсивности пены вдоль береговой линии.
### Аргументы

- *float* **intensity** - Значение интенсивности.

## float getFieldShorelineFoamIntensity ( ) const

Возвращает текущую степень интенсивности пены вдоль береговой линии.
### Возвращаемое значение

Значение интенсивности.
## void setFieldShorelineFoamExponent ( float exponent )

Задаёт видимость узора текстуры пены.
### Аргументы

- *float* **exponent** - Значение показателя степени.

## float getFieldShorelineFoamExponent ( ) const

Возвращает текущую видимость узора текстуры пены.
### Возвращаемое значение

Значение показателя степени.
## void setFieldShorelineMaskTiling ( float tiling )

Задаёт размер процедурного узора пены, используемого для уменьшения эффекта повторения пены при виде сверху.
### Аргументы

- *float* **tiling** - Значение частоты повторения.

## float getFieldShorelineMaskTiling ( ) const

Возвращает текущий размер процедурного узора пены, используемого для уменьшения эффекта повторения пены.
### Возвращаемое значение

Значение частоты повторения.
## void setFieldShorelineBeaufortFalloff ( float falloff )

Задаёт значение затухания Бофорта, обеспечивающее контроль высоты основных геометрических волн вблизи береговой линии.
### Аргументы

- *float* **falloff** - Значение затухания.

## float getFieldShorelineBeaufortFalloff ( ) const

Возвращает текущее значение затухания Бофорта, обеспечивающее контроль высоты основных геометрических волн вблизи береговой линии.
### Возвращаемое значение

Значение затухания.
## void setShorelineWetnessIntensity ( float intensity )

Задаёт интенсивность эффекта влажности вдоль береговой линии.
### Аргументы

- *float* **intensity** - Значение интенсивности влажности.

## float getShorelineWetnessIntensity ( ) const

Возвращает текущую интенсивность эффекта влажности вдоль береговой линии.
### Возвращаемое значение

Значение интенсивности влажности.
## void setShorelineWetnessDistance ( float distance )

Задаёт распространение области влажности вдоль береговой линии.
### Аргументы

- *float* **distance** - Значение расстояния влажности, в единицах.

## float getShorelineWetnessDistance ( ) const

Возвращает текущее распространение области влажности вдоль береговой линии.
### Возвращаемое значение

Значение расстояния влажности, в единицах.
## void setShorelineWetnessOffset ( float offset )

Задаёт смещение области влажности от воды.
### Аргументы

- *float* **offset** - Значение смещения влажности, в единицах.

## float getShorelineWetnessOffset ( ) const

Возвращает текущее смещение области влажности от воды.
### Возвращаемое значение

Значение смещения влажности, в единицах.
## void setAuxiliaryColor ( const Math::vec4& color )

Задаёт цвет, записываемый во вспомогательный буфер. *Alpha* — коэффициент смешивания.
### Аргументы

- *const  Math::vec4&* **color** - Вспомогательный цвет.

## Math:: vec4 getAuxiliaryColor ( ) const

Возвращает текущий цвет, записываемый во вспомогательный буфер.
### Возвращаемое значение

Вспомогательный цвет.
## void setRefractionScale ( float scale )

Задаёт масштаб [water refraction](../../../objects/objects/water/water_object.md#refraction_scale).
### Аргументы

- *float* **scale** - Значение масштаба преломления.

## float getRefractionScale ( ) const

Возвращает текущий масштаб [water refraction](../../../objects/objects/water/water_object.md#refraction_scale).
### Возвращаемое значение

Значение масштаба преломления.
## void setDecalsDistortion ( float distortion )

Искажение [decals](../../../objects/decals/index.md), проецируемых на воду.
### Аргументы

- *float* **distortion** - Значение искажения.

## float getDecalsDistortion ( ) const

Возвращает текущее искажение [decals](../../../objects/decals/index.md), проецируемых на воду.
### Возвращаемое значение

Значение искажения.
## void setDecalsSoftInteraction ( float interaction )

Задаёт новое мягкое пересечение воды с декалями.
### Аргументы

- *float* **interaction** - Значение мягкого пересечения.

## float getDecalsSoftInteraction ( ) const

Возвращает текущее мягкое пересечение воды с декалями.
### Возвращаемое значение

Значение мягкого пересечения.
## void setFieldHeightSteepness ( float steepness )

Задаёт резкость гребней волн, генерируемых объектами [FieldHeight](../../../objects/effects/fields/field_height/index.md), размещёнными в Global Water.
### Аргументы

- *float* **steepness** - Значение крутизны.

## float getFieldHeightSteepness ( ) const

Возвращает текущую резкость гребней волн, генерируемых объектами [FieldHeight](../../../objects/effects/fields/field_height/index.md), размещёнными в Global Water.
### Возвращаемое значение

Значение крутизны.
## void setUnderwaterDOF ( bool underwaterdof )

Включает/отключает эффект [underwater DOF](../../../objects/objects/water/water_object.md#underwater_dof).
### Аргументы

- *bool* **underwaterdof** - true для включения эффекта underwater DOF, false для отключения.

## bool isUnderwaterDOF ( ) const

Возвращает значение, указывающее, включён ли эффект [underwater DOF](../../../objects/objects/water/water_object.md#underwater_dof).
### Возвращаемое значение

true, если эффект underwater DOF включён; иначе false.
## void setPlanarReflection ( bool reflection )

Включает/отключает использование плоских отражений (planar reflections) на поверхности воды вместо SSR. Эту опцию лучше использовать для спокойной воды (0-2 балла Бофорта). Включение этой опции активирует параметры [Planar Reflection MapSize](../../../api/library/objects/class.objectwaterglobal_cpp.md#setPlanarReflectionMapSizeType_int_void) и Planar Reflection.
### Аргументы

- *bool* **reflection** - true для включения плоских отражений, false для отключения.

## bool isPlanarReflection ( ) const

Возвращает значение, указывающее, включена ли опция плоских отражений.
### Возвращаемое значение

true, если опция плоских отражений включена; иначе false.
## void setPlanarReflectionMapSizeType ( ObjectWaterGlobal::PLANAR_REFLECTION_SIZE type )

Задаёт размер карты плоских отражений. Чем выше значение, тем лучше качество.
### Аргументы

- *[ObjectWaterGlobal::PLANAR_REFLECTION_SIZE](../../../api/library/objects/class.objectwaterglobal_cpp.md#PLANAR_REFLECTION_SIZE)* **type** - Размер карты плоских отражений.

## ObjectWaterGlobal::PLANAR_REFLECTION_SIZE getPlanarReflectionMapSizeType ( ) const

Возвращает текущий размер карты плоских отражений.
### Возвращаемое значение

Размер карты плоских отражений.
## void setPlanarReflectionViewportMask ( int mask )

Задаёт [mask](../../../principles/bit_masking/index.md#viewport) камеры отражения. Отражение поверхности рендерится, если её маска области просмотра и маска области просмотра её материала совпадают с этой маской.
### Аргументы

- *int* **mask** - Маска области просмотра.

## int getPlanarReflectionViewportMask ( ) const

Возвращает текущую [mask](../../../principles/bit_masking/index.md#viewport) камеры отражения. Отражение поверхности рендерится, если её маска области просмотра и маска области просмотра её материала совпадают с этой маской.
### Возвращаемое значение

Маска области просмотра.
## void setCaustics ( bool caustics )

Включает/отключает эффект [light rays refraction](../../../objects/objects/water/water_object.md#enable_caustics) поверхностью воды.
### Аргументы

- *bool* **caustics** - true для включения каустики, false для отключения.

## bool isCaustics ( ) const

Возвращает значение, указывающее, включён ли [caustics effect](../../../objects/objects/water/water_object.md#enable_caustics).
### Возвращаемое значение

true, если эффект каустики включён; иначе false.
## void setCausticsDistortion ( bool distortion )

Включает/отключает опцию [caustics distortion](../../../objects/objects/water/water_object.md#caustics_distortion). Этот эффект устраняет пикселизацию и делает каустику более плавной. Когда сглаживание не требуется, эту опцию можно отключить для повышения производительности.
### Аргументы

- *bool* **distortion** - true для включения искажения каустики, false для отключения.

## bool isCausticsDistortion ( ) const

Возвращает значение, указывающее, включён ли эффект [caustics distortion](../../../objects/objects/water/water_object.md#caustics_distortion).
### Возвращаемое значение

true, если искажение каустики включено; иначе false.
## void setFieldShorelineEnabled ( bool enabled )

Включает/отключает эффект объекта [FieldShoreline](../../../objects/effects/fields/field_shoreline/index.md) на объекте Global Water. Включение этой опции делает доступной группу состояний Field Shoreline.
### Аргументы

- *bool* **enabled** - true для включения FieldShoreline, false для отключения.

## bool isFieldShorelineEnabled ( ) const

Проверяет, включена ли опция взаимодействия [FieldShoreline](../../../objects/effects/fields/field_shoreline/index.md) для материала, назначенного объекту Global Water.
### Возвращаемое значение

**true**, если опция взаимодействия FieldShoreline включена; иначе **false**.
## void setFieldShorelineHighPrecision ( bool precision )

Включает/отключает [improved interpolation](../../../objects/objects/water/water_object.md#high_precision) между соседними пикселями текстуры береговой линии для уменьшения артефактов ступенчатости. Это заметно при взгляде на линию воды, разделяющую надводную и подводную части. Эту опцию следует использовать только когда включены состояния [geometry](../../../api/library/objects/class.objectwaterglobal_cpp.md#setFieldShorelineGeometry_int_void) и/или [normal](../../../api/library/objects/class.objectwaterglobal_cpp.md#setFieldShorelineNormal_int_void).
### Аргументы

- *bool* **precision** - true для включения высокой точности, false для отключения.

## bool isFieldShorelineHighPrecision ( ) const

Возвращает значение, указывающее, включена ли [high precision](../../../objects/objects/water/water_object.md#high_precision) береговой линии. При включении эта опция улучшает интерполяцию между соседними пикселями текстуры береговой линии для уменьшения артефактов ступенчатости.
### Возвращаемое значение

true, если высокая точность включена; иначе false.
## void setFieldShorelineNormal ( bool normal )

Включает/отключает вычисление нормалей для геометрии прибрежных волн. Эта опция значительно снижает производительность и может использоваться в случаях, когда требуются действительно крупные волны. В большинстве случаев достаточно включить только состояние [geometry](../../../api/library/objects/class.objectwaterglobal_cpp.md#setFieldShorelineGeometry_int_void) для симуляции искажения поверхности воды прибрежной волной.
### Аргументы

- *bool* **normal** - true для включения, false для отключения.

## bool isFieldShorelineNormal ( ) const

Возвращает значение, указывающее, включено ли вычисление нормалей для геометрии прибрежных волн.
### Возвращаемое значение

true, если включено; иначе false.
## void setFieldShorelineGeometry ( bool geometry )

Включает/отключает [rendering of wave geometry](../../../objects/objects/water/water_object.md#fieldshoreline_geometry) для прибрежных волн. При отключении поверхность воды остаётся плоской. Отключение этой опции в случаях, когда геометрия волн едва заметна (например, авиасимулятор), даёт прирост производительности.
### Аргументы

- *bool* **geometry** - true для включения, false для отключения.

## bool isFieldShorelineGeometry ( ) const

Возвращает значение, указывающее, включён ли [rendering of wave geometry](../../../objects/objects/water/water_object.md#fieldshoreline_geometry) для прибрежных волн.
### Возвращаемое значение

true, если включено; иначе false.
## void setFieldShorelineFoam ( bool foam )

Включает/отключает [rendering of foam](../../../objects/objects/water/water_object.md#fieldshoreline_foam) для прибрежных зон.
### Аргументы

- *bool* **foam** - true для включения, false для отключения.

## bool isFieldShorelineFoam ( ) const

Возвращает значение, указывающее, включён ли [rendering of foam](../../../objects/objects/water/water_object.md#fieldshoreline_foam) для прибрежных зон.
### Возвращаемое значение

true, если включено; иначе false.
## void setAuxiliary ( bool auxiliary )

Включает/отключает [auxiliary rendering pass](../../../objects/objects/water/water_object.md#auxiliary) для материала. Может использоваться для пользовательских постэффектов, таких как тепловизор, ночное видение и т.д. Включение этой опции активирует параметр [Auxiliary Color](../../../api/library/objects/class.objectwaterglobal_cpp.md#setAuxiliaryColor_vec4_void).
### Аргументы

- *bool* **auxiliary** - true для включения, false для отключения.

## bool isAuxiliary ( ) const

Возвращает значение, указывающее, включён ли вспомогательный проход рендеринга для материала.
### Возвращаемое значение

true, если включено; иначе false.
## void setFieldHeightEnabled ( bool enabled )

Включает/отключает эффект объекта [FieldHeight](../../../objects/effects/fields/field_height/index.md) на объекте Global Water.
### Аргументы

- *bool* **enabled** - true для включения, false для отключения.

## bool isFieldHeightEnabled ( ) const

Проверяет, включена ли опция взаимодействия [FieldHeight](../../../objects/effects/fields/field_height/index.md) для материала, назначенного объекту Global Water.
### Возвращаемое значение

**true**, если опция взаимодействия FieldHeight включена; иначе **false**.
## void setFieldSpacerEnabled ( bool enabled )

Включает/отключает эффект объекта [FieldSpacer](../../../objects/effects/fields/field_spacer/index.md) на объекте Global Water.
### Аргументы

- *bool* **enabled** - true для включения, false для отключения.

## bool isFieldSpacerEnabled ( ) const

Возвращает значение, указывающее, включён ли эффект объекта [FieldSpacer](../../../objects/effects/fields/field_spacer/index.md) на объекте Global Water.
### Возвращаемое значение

true, если включено; иначе false.
## void setWavesSpeedScale ( float scale )

Задаёт значение масштаба, влияющее на скорость всех волн. Итоговая скорость волны вычисляется как ***sqrt(gravity * 2 * pi / wave_length) * waves_speed_scale***, где *gravity* = 9.81 м/с2.
### Аргументы

- *float* **scale** - Значение масштаба.

## float getWavesSpeedScale ( ) const

Возвращает текущее значение масштаба, влияющее на скорость всех волн.
### Возвращаемое значение

Scale value.
