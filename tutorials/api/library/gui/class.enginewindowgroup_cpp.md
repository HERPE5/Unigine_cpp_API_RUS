# Unigine::EngineWindowGroup Class (CPP)

**Header:** #include <UnigineWindowManager.h>

**Inherits from:** EngineWindow


Класс для создания и управления группами окон. Он позволяет объединять несколько окон группы во вкладки, задавать параметры элементов группы окон (такие как вкладки и разделители окон), а также определять пересечения с вложенными окнами. На изображении ниже показаны элементы группы окон:


![Window group elements](tab_bar_area.png)


Существует три типа групп окон:


- Вертикальный
- Горизонтальный
- Группа вкладок


Внутри группы все окна складываются в стек согласно одному из этих типов.


### Создание группы окон


Группу окон можно создать одним из следующих способов:


- Можно создать пустую группу с помощью одного из конструкторов класса *EngineWindowGroup*, а затем добавить в неё окна или другие группы.
- Можно складывать окна в стек с помощью функциональности класса *[WindowManager](../../../api/library/gui/class.windowmanager_cpp.md)*.


В этой статье мы рассмотрим только первый способ.


Следующие примеры демонстрируют, как создавать группы разных типов с помощью класса *EngineWindowGroup* и добавлять в них вложенные окна:


<details>
<summary>Horizontal Group</summary>

```cpp
// создаём отдельные окна, которые будут сгруппированы
EngineWindowViewportPtr horizontal_1 = EngineWindowViewport::create("Horizontal 1", 512, 256);
EngineWindowViewportPtr horizontal_2 = EngineWindowViewport::create("Horizontal 2", 512, 256);
EngineWindowViewportPtr horizontal_3 = EngineWindowViewport::create("Horizontal 3", 512, 256);

// создаём горизонтальную группу
auto horizontal_group = EngineWindowGroup::create(EngineWindowGroup::GROUP_TYPE_HORIZONTAL, "Horizontal Group", 565, 310);
// добавляем окна в группу
horizontal_group->add(horizontal_1);
horizontal_group->add(horizontal_2);
horizontal_group->add(horizontal_3);
// задаём позицию группы
horizontal_group->setPosition(Math::ivec2(50, 60));

// отрисовываем группу
horizontal_group->show();


```

</details>


<details>
<summary>Vertical Group</summary>

```cpp
// создаём отдельные окна, которые будут сгруппированы
EngineWindowViewportPtr vertical_1 = EngineWindowViewport::create("Vertical 1", 512, 256);
EngineWindowViewportPtr vertical_2 = EngineWindowViewport::create("Vertical 2", 512, 256);
EngineWindowViewportPtr vertical_3 = EngineWindowViewport::create("Vertical 3", 512, 256);

// создаём вертикальную группу
auto vertical_group = EngineWindowGroup::create(EngineWindowGroup::GROUP_TYPE_VERTICAL, "Vertical Group", 305, 670);
// добавляем окна в группу
vertical_group->add(vertical_1);
vertical_group->add(vertical_2);
vertical_group->add(vertical_3);
// задаём позицию группы
vertical_group->setPosition(Math::ivec2(665, 60));
// отрисовываем группу
vertical_group->show();


```

</details>


<details>
<summary>Group of Tabs</summary>

```cpp
// создаём отдельные окна, которые будут сгруппированы
EngineWindowViewportPtr tab_1 = EngineWindowViewport::create("Tab 1", 512, 256);
EngineWindowViewportPtr tab_2 = EngineWindowViewport::create("Tab 2", 512, 256);
EngineWindowViewportPtr tab_3 = EngineWindowViewport::create("Tab 3", 512, 256);

// создаём группу вкладок
auto tab_group = EngineWindowGroup::create(EngineWindowGroup::GROUP_TYPE_TAB, "Tab Group", 565, 310);
tab_group->add(tab_1);
tab_group->add(tab_2);
tab_group->add(tab_3);
// задаём позицию группы
tab_group->setPosition(Math::ivec2(50, 420));
// отрисовываем группу
tab_group->show();


```

</details>


### Редактирование группы окон


Редактирование группы окон включает изменение её элементов, таких как вкладки и разделители, добавление или удаление вложенных окон, задание режима автоматического удаления и т.д.


> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу получить доступ к его настройкам. Иначе можно получить некорректные результаты.


<details>
<summary>AppSystemLogic.cpp</summary>

```cpp
// создаём отдельные окна, которые будут сгруппированы
EngineWindowViewportPtr horizontal_1 = EngineWindowViewport::create("Horizontal 1", 512, 256);
EngineWindowViewportPtr horizontal_2 = EngineWindowViewport::create("Horizontal 2", 512, 256);
EngineWindowViewportPtr horizontal_3 = EngineWindowViewport::create("Horizontal 3", 512, 256);

// создаём горизонтальную группу
auto horizontal_group = EngineWindowGroup::create(EngineWindowGroup::GROUP_TYPE_HORIZONTAL, "Horizontal Group", 565, 310);
// добавляем окна в группу
horizontal_group->add(horizontal_1);
horizontal_group->add(horizontal_2);
horizontal_group->add(horizontal_3);
// задаём позицию группы
horizontal_group->setPosition(Math::ivec2(50, 60));

// обновляем иерархию в self gui группы
horizontal_group->updateGuiHierarchy();

int position_offset = 100;
float value_offset = 0.2f;

for (int i = 0; i < horizontal_group->getNumNestedWindows(); i++)
{
	// изменяем вкладку
	horizontal_group->setTabTitle(i, "New name " + String::itoa(i));
	if (i == 0) horizontal_group->setHorizontalTabWidth(i, position_offset);

	// изменяем разделитель
	horizontal_group->setSeparatorValue(i, horizontal_group->getSeparatorValue(i) + value_offset);
}

// отрисовываем группу
horizontal_group->show();


```

</details>


### Управление группами


Классы *EngineWindowGroup* и базовый *EngineWindow* предоставляют набор функций, позволяющих реализовать пользовательскую логику группировки и разгруппировки окон. Например, можно выполнить следующее:


- Управлять [whether the group can be modified](#isFixed_int) (т.е. можно ли добавлять новые окна и удалять вложенные окна).
- Проверять, можно ли [added to the group](../../../api/library/gui/class.enginewindow_cpp.md#isCanBeNested_int)
- [Access](#getNestedWindow_int_EngineWindow) к вложенным окнам
- Задавать [automatic deletion mode](#setAutoDeleteMode_int_void)


И многое другое, предоставляя гибкий контроль над логикой группировки.


### См. также


- Набор `примеров SDK`, демонстрирующих различные аспекты использования, включая:

  -
  -


## EngineWindowGroup Class

### Перечисления

## GROUP_TYPE

| Name | Description |
|---|---|
| **GROUP_TYPE_NONE** = 0 | Отдельное окно внутри группы. |
| **GROUP_TYPE_TAB** = 1 | Окна объединены в группу вкладок, где выбранное окно отображается поверх остальных в группе. |
| **GROUP_TYPE_HORIZONTAL** = 2 | Окна объединены в группу с горизонтальным расположением. |
| **GROUP_TYPE_VERTICAL** = 3 | Окна объединены в группу с вертикальным расположением. |

## AUTO_DELETE_MODE

| Name | Description |
|---|---|
| **AUTO_DELETE_MODE_NONE** = 0 | Автоматическое удаление окна отключено. |
| **AUTO_DELETE_MODE_EMPTY** = 1 | Группа окон удаляется автоматически, если она не содержит вложенных окон. |
| **AUTO_DELETE_MODE_SINGLE_WINDOW** = 2 | Группа удаляется автоматически, если в ней остаётся только одно окно. Если это была дочерняя группа, она автоматически преобразуется в дочернее окно. |

### Методы класса

---

## EngineWindowGroup ( EngineWindowGroup::GROUP_TYPE group_type , const Math:: ivec2 & size , int flags = 0 )

Конструктор. Создаёт группу окон указанного типа и размера с указанными флагами.
### Аргументы

- *[EngineWindowGroup::GROUP_TYPE](../../../api/library/gui/class.enginewindowgroup_cpp.md#GROUP_TYPE)* **group_type** - Тип группы.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **size** - Размер группы окон.
- *int* **flags** - Маска, содержащая [flags](../../../api/library/gui/class.enginewindow_cpp.md#FLAGS_MAIN) окна.

## EngineWindowGroup ( EngineWindowGroup::GROUP_TYPE group_type , int width , int height , int flags = 0 )

Конструктор. Создаёт группу окон указанного типа и размера с указанными флагами.
### Аргументы

- *[EngineWindowGroup::GROUP_TYPE](../../../api/library/gui/class.enginewindowgroup_cpp.md#GROUP_TYPE)* **group_type** - Тип группы.
- *int* **width** - Ширина окна.
- *int* **height** - Высота окна.
- *int* **flags** - Маска, содержащая [flags](../../../api/library/gui/class.enginewindow_cpp.md#FLAGS_MAIN) окна.

## EngineWindowGroup ( EngineWindowGroup::GROUP_TYPE group_type , const char * window_title , int width , int height , int flags = 0 )

Конструктор. Создаёт группу окон указанного типа и размера с указанным заголовком и флагами.
### Аргументы

- *[EngineWindowGroup::GROUP_TYPE](../../../api/library/gui/class.enginewindowgroup_cpp.md#GROUP_TYPE)* **group_type** - Тип группы.
- *const char ** **window_title** - Заголовок окна в кодировке UTF-8.
- *int* **width** - Ширина окна.
- *int* **height** - Высота окна.
- *int* **flags** - Маска, содержащая [flags](../../../api/library/gui/class.enginewindow_cpp.md#FLAGS_MAIN) окна.

## EngineWindowGroup::GROUP_TYPE getGroupType ( ) const

Возвращает тип группы окон, установленный в конструкторе — вертикальное, горизонтальное, вкладочное расположение окон, либо независимое окно внутри группы.
### Возвращаемое значение

Тип группы окон.
## void setFixed ( bool fixed )

Устанавливает значение, указывающее, можно ли добавлять окна в эту группу или удалять их из неё.
### Аргументы

- *bool* **fixed** - true, чтобы отключить добавление или удаление окон из этой группы, иначе false.

## bool isFixed ( ) const

Возвращает значение, указывающее, можно ли добавлять окна в эту группу или удалять их из неё.
### Возвращаемое значение

true, если добавление или удаление окон из этой группы отключено, иначе false.
## void setAutoDeleteMode ( EngineWindowGroup::AUTO_DELETE_MODE mode )

Устанавливает режим автоматического удаления окна.
### Аргументы

- *[EngineWindowGroup::AUTO_DELETE_MODE](../../../api/library/gui/class.enginewindowgroup_cpp.md#AUTO_DELETE_MODE)* **mode** - Режим автоматического удаления окна.

## EngineWindowGroup::AUTO_DELETE_MODE getAutoDeleteMode ( ) const

Возвращает режим автоматического удаления окна.
### Возвращаемое значение

Режим автоматического удаления окна.
## void add ( const Ptr < EngineWindow > & window , int target_index = -1 )

Добавляет окно по указанному индексу. Окно становится вложенным (т.е. его границы, стиль, панель заголовка и т.д. отключаются).
> **Notice:** Если группа [fixed](#isFixed_int), окно не будет добавлено в группу, и в консоли отобразится соответствующее предупреждение.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Добавляемое окно.
- *int* **target_index** - Порядок окна. Если индекс не указан, окно добавляется последним.

## void remove ( const Ptr < EngineWindow > & window )

Удаляет указанное окно из группы. Настройки окна становятся такими же, как до добавления в группу.
> **Notice:** Если группа [fixed](#isFixed_int), окно не будет удалено из группы, и в консоли отобразится соответствующее предупреждение.


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Удаляемое окно.

## void removeByIndex ( int index )

Удаляет окно по указанному индексу из группы. Настройки окна становятся такими же, как до добавления в группу.
> **Notice:** Если группа [fixed](#isFixed_int), окно не будет удалено из группы, и в консоли отобразится соответствующее предупреждение.


### Аргументы

- *int* **index** - Индекс удаляемого окна.

## int getNumNestedWindows ( ) const

Возвращает общее количество вложенных окон в группе.
### Возвращаемое значение

Общее количество вложенных окон в группе.
## Ptr < EngineWindow > getNestedWindow ( int index ) const

Возвращает вложенное окно движка по его индексу.
### Аргументы

- *int* **index** - Индекс вложенного окна.

### Возвращаемое значение

Вложенное окно движка.
## int getNestedWindowIndex ( const Ptr < EngineWindow > & window )

Возвращает индекс указанного вложенного окна движка.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Вложенное окно движка.

### Возвращаемое значение

Индекс вложенного окна.
## bool containsNestedWindow ( const Ptr < EngineWindow > & window ) const

Возвращает значение, указывающее, является ли указанное окно прямым дочерним для текущей группы.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Проверяемое окно.

### Возвращаемое значение

true, если указанное окно является прямым дочерним для текущего, иначе false.
## bool containsNestedWindowInHierarchy ( const Ptr < EngineWindow > & window ) const

Возвращает значение, указывающее, является ли указанное окно дочерним для текущей группы или любого из её потомков.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[EngineWindow](../../../api/library/gui/class.enginewindow_cpp.md)> &* **window** - Проверяемое окно.

### Возвращаемое значение

true, если указанное окно является дочерним для текущего, иначе false.
## void setTabTitle ( int index , const char * title )

Добавляет заголовок к указанной вкладке и самому окну.
### Аргументы

- *int* **index** - Индекс вкладки.
- *const char ** **title** - Добавляемый заголовок.

## void setTabIcon ( int index , const Ptr < Image > & image )

Добавляет изображение к указанной вкладке и самому окну.
### Аргументы

- *int* **index** - Индекс вкладки.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Добавляемое изображение.

## int setCurrentTab ( )

Устанавливает индекс текущей активной вкладки в группе вкладок.
### Возвращаемое значение

Индекс вкладки, устанавливаемой как текущая активная.
## int getCurrentTab ( ) const

Возвращает индекс текущей активной вкладки в группе вкладок.
### Возвращаемое значение

Индекс текущей активной вкладки.
## int getTabWidth ( int index ) const

Возвращает ширину вкладки. Доступно только для [horizontal](#GROUP_TYPE_HORIZONTAL) групп.
### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Ширина вкладки.
## int getTabHeight ( int index ) const

Возвращает высоту вкладки. Доступно только для [vertical](#GROUP_TYPE_VERTICAL) групп.
### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Высота вкладки.
## int getTabBarWidth ( int index ) const

Возвращает ширину панели вкладок.
### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Ширина панели вкладок.
## int getTabBarHeight ( int index ) const

Возвращает высоту панели вкладок.
### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Высота панели вкладок.
## Math:: ivec2 getTabLocalPosition ( int index ) const

Возвращает экранную позицию вкладки относительно родительской группы (глобального окна). Координаты представляют собой смещение от верхнего левого угла родительской группы (глобального окна).
### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Экранная позиция вкладки относительно родительской группы (глобального окна).
## Math:: ivec2 getTabBarLocalPosition ( int index ) const

Возвращает экранную позицию панели вкладок относительно родительской группы (глобального окна). Координаты представляют собой смещение от верхнего левого угла родительской группы (глобального окна).
### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Экранная позиция панели вкладок относительно родительской группы (глобального окна).
## void setHorizontalTabWidth ( int index , int width )

Устанавливает ширину вкладки в группе вкладок с горизонтальным расположением.
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу изменить ширину его вкладки. Иначе можно получить некорректные результаты.


### Аргументы

- *int* **index** - Индекс вкладки.
- *int* **width** - Ширина вкладки в группе вкладок с горизонтальным расположением.

## void setVerticalTabHeight ( int index , int height )

Устанавливает высоту вкладки в группе вкладок с вертикальным расположением.
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу изменить высоту его вкладки. Иначе можно получить некорректные результаты.


### Аргументы

- *int* **index** - Индекс вкладки.
- *int* **height** - Высота вкладки в группе вкладок с вертикальным расположением.

## int getSeparatorWidth ( ) const

Возвращает ширину вертикальной линии, отделяющей группу вкладок от остальной области.
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу получить доступ к его разделителю. Иначе можно получить некорректные результаты.


### Возвращаемое значение

Ширина разделительной линии, в пикселях.
## int getSeparatorHeight ( ) const

Возвращает высоту горизонтальной линии, отделяющей группу вкладок от остальной области.
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу получить доступ к его разделителю. Иначе можно получить некорректные результаты.


### Возвращаемое значение

Высота разделительной линии, в пикселях.
## void setSeparatorPosition ( int index , int pos )

Устанавливает позицию линии, отделяющей группу вкладок от остальной области. Линия разделителя может быть горизонтальной или вертикальной в зависимости от [group type](#getGroupType_int).
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу изменить его разделитель. Иначе можно получить некорректные результаты.


### Аргументы

- *int* **index** - Индекс вкладки.
- *int* **pos** - Позиция разделительной линии, в пикселях, от верхнего левого угла окна.

## int getSeparatorPosition ( int index ) const

Возвращает позицию линии, отделяющей группу вкладок от остальной области. Линия разделителя может быть горизонтальной или вертикальной в зависимости от [group type](#getGroupType_int).
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу получить доступ к его разделителю. Иначе можно получить некорректные результаты.


### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Позиция разделительной линии, в пикселях, от верхнего левого угла окна.
## void setSeparatorValue ( int index , float value )

Устанавливает относительную позицию разделителя вкладки.
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу изменить его разделитель. Иначе можно получить некорректные результаты.


### Аргументы

- *int* **index** - Индекс вкладки.
- *float* **value** - Позиция разделителя вкладки, значение от 0 до 1, пересчитываемое в пиксели.

## float getSeparatorValue ( int index ) const

Возвращает относительную позицию разделителя вкладки.
> **Notice:** Возможно, потребуется сначала вызвать [*updateGuiHierarchy()*](../../../api/library/gui/class.enginewindow_cpp.md#updateGuiHierarchy_void), если вы добавили новое окно в группу и хотите сразу получить доступ к его разделителю. Иначе можно получить некорректные результаты.


### Аргументы

- *int* **index** - Индекс вкладки.

### Возвращаемое значение

Позиция разделителя вкладки, значение от 0 до 1.
## void swapTabs ( int first , int second )

Меняет местами указанные вкладки.
> **Notice:** Если группа [fixed](#isFixed_int), вкладки не будут поменяны местами, и в консоли отобразится соответствующее предупреждение.


### Аргументы

- *int* **first** - Индекс первой вкладки.
- *int* **second** - Индекс второй вкладки.

## int getIntersectionTabBar ( const Math:: ivec2 & global_mouse_pos )

Возвращает значение, указывающее, находится ли курсор мыши над панелью вкладок окна.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **global_mouse_pos** - Глобальные экранные координаты мыши относительно главного дисплея.

### Возвращаемое значение

1, если курсор мыши находится над панелью вкладок окна, иначе 0.
## int getIntersectionTabBarArea ( const Math:: ivec2 & global_mouse_pos )

Возвращает значение, указывающее, находится ли курсор мыши над областью панели вкладок окна.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **global_mouse_pos** - Глобальные экранные координаты мыши относительно главного дисплея.

### Возвращаемое значение

1, если курсор мыши находится над областью панели вкладок окна, иначе 0.
## Math:: ivec2 getIntersectedItemPosition ( ) const

Возвращает позицию верхнего левого угла пересечённого элемента группы в экранных координатах. В случае нескольких дисплеев позиция задаётся относительно главного дисплея.
### Возвращаемое значение

Экранная позиция пересечённого элемента — координаты верхнего левого угла.
## Math:: ivec2 getIntersectedItemSize ( ) const

Возвращает размер пересечённого элемента.
### Возвращаемое значение

Размер пересечённого элемента, в пикселях.
