# Unigine::WidgetSpacer Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Этот класс создаёт [line spacer](../../../code/gui/ui/ui_widgets.md#hspacer): [horizontal](../../../code/gui/ui/ui_widgets.md#hspacer) или [vertical](../../../code/gui/ui/ui_widgets.md#vspacer).


Объект этого класса может выглядеть следующим образом:


![Horizontal spacer](../../../code/gui/ui/widgets/hspacer.png)

*Горизонтальный разделитель*


![Vertical spacer](../../../code/gui/ui/widgets/vspacer.png)

*Вертикальный разделитель*


## WidgetSpacer Class

### Методы класса

---

## static WidgetSpacerPtr create ( const Ptr < Gui > & gui )

Конструктор. Создаёт разделитель и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать разделитель.

## static WidgetSpacerPtr create ( )

Конструктор. Создаёт разделитель и добавляет его в GUI движка.
## void setOrientation ( int orientation )

Задаёт ориентацию разделителя: горизонтальная (по умолчанию) или вертикальная.
### Аргументы

- *int* **orientation** - Положительное значение устанавливает горизонтальную ориентацию; 0 устанавливает вертикальную.

## int getOrientation ( ) const

Возвращает текущую ориентацию разделителя: горизонтальная или вертикальная.
### Возвращаемое значение

Положительное число, если ориентация вертикальная; 0, если горизонтальная.
