# Unigine::WidgetSpinBox Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот класс создаёт [spin box](../../../code/gui/ui/ui_widgets.md#spinbox).


Объект этого класса выглядит следующим образом:


![](../../../code/gui/ui/widgets/spinbox.png)


#### См. также


- C++ sample


### Пример использования


В этом примере показано создание spin box с помощью кода.


```cpp
#include "AppWorldLogic.h"
#include <UnigineWidgets.h>
#include <UnigineGui.h>

using namespace Unigine;

WidgetSpinBoxPtr spinbox;

// создаём экземпляр класса EventConnection
EventConnection connection;

// функция-обработчик события изменения значения spin box
void onSpinboxChanged(const Ptr<Widget> & widget) {
	WidgetSpinBoxPtr sb = checked_ptr_cast<WidgetSpinBox>(widget);

	// вывод текущего значения spin box в консоль
	Log::message("Spinbox value changed: %d \n", sb->getValue());
}

// Метод, создающий spin box с указанными параметрами в указанной позиции
WidgetSpinBoxPtr createSB(int x, int y, int min, int max, int value, int step)
{

	// получение указателя на системный GUI
	GuiPtr gui = Gui::getCurrent();

	// создание новой строки ввода и добавление её в GUI
	WidgetEditLinePtr new_el = WidgetEditLine::create(gui);
	gui->addChild(new_el, Gui::ALIGN_OVERLAP);

	// установка позиции виджета
	new_el->setPosition(x, y);

	// создание spin box с указанными параметрами и добавление его в GUI
	WidgetSpinBoxPtr new_sb = WidgetSpinBox::create(gui, min, max, value, step);
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
	spinbox = createSB(100, 100, 0, 10, 5, 1);

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


## WidgetSpinBox Class

### Методы класса

---

## static WidgetSpinBoxPtr create ( const Ptr < Gui > & gui , int min = 0 , int max = 100 , int value = 0 , int step = 1 )

Конструктор. Создаёт spin box с заданными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать spin box.
- *int* **min** - Минимальное значение.
- *int* **max** - Максимальное значение.
- *int* **value** - Начальное значение.
- *int* **step** - Начальный шаг.

## static WidgetSpinBoxPtr create ( int min = 0 , int max = 100 , int value = 0 , int step = 1 )

Конструктор. Создаёт spin box с заданными параметрами и добавляет его в GUI движка.
### Аргументы

- *int* **min** - Минимальное значение.
- *int* **max** - Максимальное значение.
- *int* **value** - Начальное значение.
- *int* **step** - Начальный шаг.

## void setMaxExpand ( int expand )

Задаёт максимальное значение, до которого может быть расширен верхний предел диапазона значений spin box.
### Аргументы

- *int* **expand** - Максимальное значение, до которого может быть поднят верхний предел spin box.

## int getMaxExpand ( ) const

Возвращает текущее максимальное значение, до которого может быть расширен верхний предел диапазона значений spin box. Верхний предел spin box может быть расширен только если он прикреплён к editline с флагом Gui::ATTACH_MAX_EXPAND.
### Возвращаемое значение

Максимальное значение, до которого может быть поднят верхний предел spin box.
## void setMaxValue ( int value )

Задаёт максимальное значение spin box.
### Аргументы

- *int* **value** - Максимальное значение spin box.

## int getMaxValue ( ) const

Возвращает максимальное значение spin box.
### Возвращаемое значение

Максимальное значение spin box.
## void setMinExpand ( int expand )

Задаёт минимальное значение, до которого может быть расширен нижний предел диапазона значений spin box.
### Аргументы

- *int* **expand** - Минимальное значение, до которого может быть опущен нижний предел spin box.

## int getMinExpand ( ) const

Возвращает текущее минимальное значение, до которого может быть расширен нижний предел диапазона значений spin box. Нижний предел spin box может быть расширен только если он прикреплён к editline с флагом Gui::ATTACH_MIN_EXPAND.
### Возвращаемое значение

Минимальное значение, до которого может быть опущен нижний предел spin box.
## void setMinValue ( int value )

Задаёт минимальное значение spin box.
### Аргументы

- *int* **value** - Минимальное значение spin box.

## int getMinValue ( ) const

Возвращает минимальное значение spin box.
### Возвращаемое значение

Минимальное значение spin box.
## void setValue ( int value )

Обновляет текущее значение spin box.
### Аргументы

- *int* **value** - Новое значение spin box.

## int getValue ( ) const

Возвращает текущее значение spin box.
### Возвращаемое значение

Текущее значение spin box.
## void setStep ( int step )

Обновляет текущий шаг spin box.
### Аргументы

- *int* **step** - Новый шаг spin box.

## int getStep ( ) const

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
