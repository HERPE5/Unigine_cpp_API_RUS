# Unigine::WidgetExtern Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Widget


Интерфейс для работы с внешним виджетом. Он служит для создания внешних пользовательских виджетов или интеграции сторонних GUI-систем внутри движка через интерфейс Plugin.


#### См. также


- Пример C++


## WidgetExtern Class

### Методы класса

---

## static WidgetExternPtr create ( const Ptr < Gui > & gui , int class_id )

Конструктор. Создаёт пользовательский виджет и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - Экземпляр Gui, которому принадлежит виджет.
- *int* **class_id** - Уникальный ID класса.

## static WidgetExternPtr create ( int class_id )

Конструктор. Создаёт пользовательский виджет и добавляет его в GUI движка.
### Аргументы

- *int* **class_id** - Уникальный ID класса.

## int getClassID ( ) const

Возвращает уникальный ID класса.
### Возвращаемое значение

Уникальный ID класса, если виджет существует; иначе 0.
