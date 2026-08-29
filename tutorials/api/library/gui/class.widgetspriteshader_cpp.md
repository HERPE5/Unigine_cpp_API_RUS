# Unigine::WidgetSpriteShader Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetSprite


Этот класс создаёт спрайт для отображения изображения с применённым пользовательским постпроцесс-материалом.


### См. также




## WidgetSpriteShader Class

### Методы класса

## void setMaterial ( const const Ptr < Material > && material )

Задаёт новый постпроцесс-материал для виджета.
### Аргументы

- *const const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Material](../../../api/library/rendering/class.material_cpp.md)> &&* **material** - Постпроцесс-материал.

## const Ptr < Material > & getMaterial () const

Возвращает текущий постпроцесс-материал виджета.
### Возвращаемое значение

Текущий постпроцесс-материал.
---

## static WidgetSpriteShaderPtr create ( const Ptr < Gui > & gui , const char * name = 0 )

Конструктор. Создаёт новый спрайт с указанной текстурой и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать спрайт.
- *const char ** **name** - Путь к текстуре. Это необязательный параметр.

## static WidgetSpriteShaderPtr create ( const char * name = 0 )

Конструктор. Создаёт новый спрайт с указанной текстурой и добавляет его в GUI движка.
### Аргументы

- *const char ** **name** - Путь к текстуре. Это необязательный параметр.
