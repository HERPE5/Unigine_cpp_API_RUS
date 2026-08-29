# Unigine::WidgetSpinBoxDouble Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот класс создаёт [spin box](../../../code/gui/ui/ui_widgets.md#spinbox) со значениями типа double.


### Пример использования


В этом примере показано создание spin box с помощью кода.


```cpp
#include "AppWorldLogic.h"
#include <UnigineWidgets.h>
#include <UnigineGui.h>

using namespace Unigine;

WidgetSpinBoxDoublePtr spinbox;

// создаём экземпляр класса EventConnection
EventConnection connection;

// функция-обработчик события изменения значения spin box
void onSpinboxChanged(const Ptr<Widget> & widget) {
	WidgetSpinBoxDoublePtr sb = checked_ptr_cast<WidgetSpinBoxDouble>(widget);

	// вывод текущего значения spin box в консоль
	Log::message("Spinbox value changed: %d \n", sb->getValue());
}

// Метод, создающий spin box с указанными параметрами в указанной позиции
WidgetSpinBoxDoublePtr createSB(double x, double y, double min, double max, double value, double step)
{

	// получение указателя на системный GUI
	GuiPtr gui = Gui::getCurrent();

	// создание новой строки ввода и добавление её в GUI
	WidgetEditLinePtr new_el = WidgetEditLine::create(gui);
	gui->addChild(new_el, Gui::ALIGN_OVERLAP);

	// установка позиции виджета
	new_el->setPosition(x, y);

	// создание spin box с указанными параметрами и добавление его в GUI
	WidgetSpinBoxDoublePtr new_sb = WidgetSpinBoxDouble::create(gui, min, max, value, step);
	gui->addChild(new_sb, Gui::ALIGN_OVERLAP);

	// добавление колбэка, вызываемого при изменении значения spin box
	new_sb->getEventChanged().connect(connection, onSpinboxChanged);
	new_sb->setOrder(1);

	// прикрепление spin box к строке ввода
	new_el->addAttach(new_sb);

	// установка начального значения spin box
	new_sb->setValue(value);

	return new_sb;
}
// ...

int AppWorldLogic::init()
{
	// создание spin box со значениями в диапазоне [0, 10] (текущее - 5) в позиции (100, 100)
	spinbox = createSB(100, 100, 0.0, 10.0, 5.0, 1.0);

	return 1;
}

// ...

int AppWorldLogic::shutdown()
{
	// очистка
	spinbox.deleteLater();

	return 1;
}


```


## WidgetSpinBoxDouble Class

### Методы класса

---

## static WidgetSpinBoxDoublePtr create ( const Ptr < Gui > & gui , double min = 0.0 , double max = 100.0 , double value = 0.0 , double step = 1.0 )

Конструктор. Создаёт spin box с заданными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать spin box.
- *double* **min** - Минимальное значение.
- *double* **max** - Максимальное значение.
- *double* **value** - Начальное значение.
- *double* **step** - Начальный шаг.

## static WidgetSpinBoxDoublePtr create ( double min = 0.0 , double max = 100.0 , double value = 0.0 , double step = 1.0 )

Конструктор. Создаёт spin box с заданными параметрами и добавляет его в GUI движка.
### Аргументы

- *double* **min** - Минимальное значение.
- *double* **max** - Максимальное значение.
- *double* **value** - Начальное значение.
- *double* **step** - Начальный шаг.

## void setMaxExpand ( double expand )

Задаёт максимальное значение, до которого может быть расширен верхний предел диапазона значений spin box.
### Аргументы

- *double* **expand** - Максимальное значение, до которого может быть поднят верхний предел spin box.

## double getMaxExpand ( ) const

Возвращает текущее максимальное значение, до которого может быть расширен верхний предел диапазона значений spin box. Верхний предел spin box может быть расширен только если он прикреплён к editline с флагом Gui::ATTACH_MAX_EXPAND.
### Возвращаемое значение

Максимальное значение, до которого может быть поднят верхний предел spin box.
## void setMaxValue ( double value )

Задаёт максимальное значение spin box.
### Аргументы

- *double* **value** - Максимальное значение spin box.

## double getMaxValue ( ) const

Возвращает максимальное значение spin box.
### Возвращаемое значение

Максимальное значение spin box.
## void setMinExpand ( double expand )

Задаёт минимальное значение, до которого может быть расширен нижний предел диапазона значений spin box.
### Аргументы

- *double* **expand** - Минимальное значение, до которого может быть опущен нижний предел spin box.

## double getMinExpand ( ) const

Возвращает текущее минимальное значение, до которого может быть расширен нижний предел диапазона значений spin box. Нижний предел spin box может быть расширен только если он прикреплён к editline с флагом Gui::ATTACH_MIN_EXPAND.
### Возвращаемое значение

Минимальное значение, до которого может быть опущен нижний предел spin box.
## void setMinValue ( double value )

Задаёт минимальное значение spin box.
### Аргументы

- *double* **value** - Минимальное значение spin box.

## double getMinValue ( ) const

Возвращает минимальное значение spin box.
### Возвращаемое значение

Минимальное значение spin box.
## void setValue ( double value )

Обновляет текущее значение spin box.
### Аргументы

- *double* **value** - Новое значение spin box.

## double getValue ( ) const

Возвращает текущее значение spin box.
### Возвращаемое значение

Текущее значение spin box.
## void setStep ( double step )

Обновляет текущий шаг spin box.
### Аргументы

- *double* **step** - Новый шаг spin box.

## double getStep ( ) const

Возвращает текущий шаг spin box.
### Возвращаемое значение

Текущий шаг spin box.
## void setButtonColor ( const Math:: vec4 & color )

Задаёт цвет кнопки виджета.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md) &* **color** - Четырёхкомпонентный вектор, задающий цвет в формате RGBA.

## Math:: vec4 getButtonColor ( ) const

Возвращает текущий цвет кнопки виджета.
### Возвращаемое значение

Четырёхкомпонентный вектор, задающий цвет в формате RGBA.
