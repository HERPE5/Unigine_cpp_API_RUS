# Unigine::WidgetExternBase Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** Base


Базовый класс, от которого наследуются [custom user-defined widgets](../../../api/library/gui/class.widgetextern_cpp.md).


### См. также


- Пример C++


## WidgetExternBase Class

### Методы класса

---

## template < class Type >

## static addClassID ( int class_id )

Регистрирует пользовательский класс виджета с уникальным ID класса.
```cpp
// регистрируем класс MyWidget
WidgetExternBase::addClassID<MyWidget>(1);

```


### Аргументы

- *int* **class_id** - Уникальный ID класса.

## int getClassID ( )

Возвращает уникальный ID класса.
### Возвращаемое значение

Уникальный ID класса.
## Ptr < Gui > getGui ( ) const

Возвращает умный указатель Gui.
### Возвращаемое значение

Умный указатель Gui.
## int getKeyActivity ( unsigned int key )

Проверяет клавишу клавиатуры.
### Аргументы

- *unsigned int* **key** - Код клавиши.

### Возвращаемое значение

Возвращает **1**, если клавиша используется виджетом.
## Ptr < Widget > getWidget ( ) const

Возвращает умный указатель Widget.
### Возвращаемое значение

Умный указатель Widget.
## Ptr < WidgetExtern > getWidgetExtern ( ) const

Возвращает умный указатель WidgetExtern.
### Возвращаемое значение

Умный указатель WidgetExtern.
## void arrange ( )

Вычисляет размер виджета.
## void checkCallbacks ( int x , int y )

Проверяет обратные вызовы виджета.
### Аргументы

- *int* **x** - Координата X мыши.
- *int* **y** - Координата Y мыши.

## void destroy ( )

Уничтожает ресурсы виджета.
## void expand ( int width , int height )

Расширяет размер виджета.
### Аргументы

- *int* **width** - Максимально доступная ширина.
- *int* **height** - Максимально доступная высота.

## void keyPress ( unsigned int key )

Событие нажатия клавиатуры (код сканирования).
### Аргументы

- *unsigned int* **key** - Код клавиши.

## void textPress ( unsigned int unicode )

Событие нажатия клавиатуры (виртуальная клавиша).
### Аргументы

- *unsigned int* **unicode** - Код виртуальной клавиши.

## void update ( float ifps )

Функция обновления виджета.
### Аргументы

- *float* **ifps** - Значение, обратное FPS.

## void preRender ( )

Функция предварительной отрисовки виджета, выполняемая после *update()* и перед функцией *render()*. Этот метод используется для выполнения необходимых подготовок к отрисовке (например, подготовки текстуры) после *update()* и вызывается автоматически для *[WidgetSpriteViewport](../../../api/library/gui/class.widgetspriteviewport_cpp.md)* и *[WidgetSpriteNode](../../../api/library/gui/class.widgetspriteviewport_cpp.md)*, чтобы обеспечить корректную отрисовку виджетов во время *render()*. Если вы реализуете пользовательский GUI или виджеты с помощью класса *WidgetExtern*, вам следует поместить все такие подготовки к отрисовке в этот метод и вызывать **[Gui::preRender()](../../../api/library/gui/class.gui_cpp.md#preRender_void)** *preRender()* вручную после *update()*.
## void render ( )

Отрисовывает виджет.
## void updatePositions ( )

Обновляет экранные координаты виджета. Эта функция вызывается после функций [arrange()](#arrange_void) и [expand()](#expand_int_int_void).
