# Unigine::WidgetManipulatorTranslator Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetManipulator


Этот класс создаёт манипулятор перемещения вдоль трёх осей со стрелками на концах.


### См. также


- Пример использования: [Using Manipulators to Transform Objects](../../../code/usage/manipulator_component/index_cpp.md)
- Пример C++


## WidgetManipulatorTranslator Class

### Методы класса

---

## static WidgetManipulatorTranslatorPtr create ( const Ptr < Gui > & gui )

Конструктор. Создаёт манипулятор перемещения и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать translator.

## static WidgetManipulatorTranslatorPtr create ( )

Конструктор. Создаёт манипулятор перемещения и добавляет его в GUI движка.
