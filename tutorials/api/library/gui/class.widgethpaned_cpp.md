# Unigine::WidgetHPaned Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetVPaned


Этот класс создаёт [vertical movable bar](../../../code/gui/ui/ui_containers.md#hpaned), разделяющую окно на две панели с изменяемым размером.


Объект этого класса выглядит следующим образом:


![](../../../code/gui/ui/widgets/hpaned.png)


Этот виджет должен содержать ровно двух дочерних элементов. Если предоставлено меньше дочерних элементов, ничего не будет отрисовано; если больше — приложение может завершиться аварийно.


## WidgetHPaned Class

### Методы класса

---

## static WidgetHPanedPtr create ( const Ptr < Gui > & gui )

Конструктор. Создаёт новый горизонтальный box с возможностью изменения размера его дочерних элементов и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новый контейнер.

## static WidgetHPanedPtr create ( )

Конструктор. Создаёт новый горизонтальный box с возможностью изменения размера его дочерних элементов и добавляет его в GUI движка.
