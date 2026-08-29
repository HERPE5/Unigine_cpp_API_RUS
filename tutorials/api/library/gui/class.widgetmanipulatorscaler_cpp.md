# Unigine::WidgetManipulatorScaler Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetManipulator


Этот класс создаёт манипулятор масштабирования вдоль трёх осей в форме треугольника.


### См. также


- Пример использования: [Using Manipulators to Transform Objects](../../../code/usage/manipulator_component/index_cpp.md)
- Пример C++


## WidgetManipulatorScaler Class

### Методы класса

---

## static WidgetManipulatorScalerPtr create ( const Ptr < Gui > & gui )

Конструктор. Создаёт манипулятор масштабирования и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать scaler.

## static WidgetManipulatorScalerPtr create ( )

Конструктор. Создаёт манипулятор масштабирования и добавляет его в GUI движка.
