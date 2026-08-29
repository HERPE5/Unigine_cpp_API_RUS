# Unigine::WidgetHBox Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetVBox


Этот класс создаёт контейнер [single horizontal row](../../../code/gui/ui/ui_containers.md#hbox).


Объект этого класса выглядит следующим образом:


![](../../../code/gui/ui/widgets/hbox.png)


## WidgetHBox Class

---

## static WidgetHBoxPtr create ( const Ptr < Gui > & gui , int x = 0 , int y = 0 )

Конструктор. Создаёт горизонтальный box с указанными параметрами и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новый box.
- *int* **x** - Горизонтальное расстояние между виджетами в box и между ними и границей box. Это опциональный параметр.
- *int* **y** - Вертикальное расстояние между виджетами в box и между ними и границей box. Это опциональный параметр.

## static WidgetHBoxPtr create ( int x = 0 , int y = 0 )

Конструктор. Создаёт горизонтальный box с указанными параметрами и добавляет его в GUI движка.
### Аргументы

- *int* **x** - Горизонтальное расстояние между виджетами в box и между ними и границей box. Это опциональный параметр.
- *int* **y** - Вертикальное расстояние между виджетами в box и между ними и границей box. Это опциональный параметр.
