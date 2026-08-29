# Unigine::Widget Class (CPP)

**Header:** #include <UnigineWidgets.h>


Этот базовый класс используется для создания виджетов [graphical user interface](../../../objects/objects/gui/index.md) разных типов. Класс Widget не предоставляет создание виджета: нужный виджет можно создать с помощью конструктора соответствующего класса, унаследованного от Widget.


Виджеты можно использовать по отдельности или объединять в иерархию.


### Работа с виджетами


Пример ниже демонстрирует, как создать отдельный виджет, иерархию виджетов и подписаться на событие виджета.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

`AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"
#include <UnigineWidgets.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

void on_button_click(const WidgetPtr& button, int mbuttons)
{
	Log::message("world button click\n");
}

int AppWorldLogic::init()
{
	// создаём отдельный виджет
	WidgetButtonPtr button = WidgetButton::create("WORLD_BUTTON");
	// подписываемся на событие Clicked
	button->getEventClicked().connect(econnections, on_button_click);
	// добавляем кнопку в WindowManager
	WindowManager::getMainWindow()->addChild(button);

	// создаём иерархию виджетов
	WidgetHBoxPtr hbox = WidgetHBox::create();
	hbox->setBackground(1);
	hbox->setBackgroundColor(Math::vec4_white);
	WindowManager::getMainWindow()->addChild(hbox, Gui::ALIGN_EXPAND);

	WidgetGroupBoxPtr group = WidgetGroupBox::create();
	group->setBackground(1);
	group->setText("Widgets Hierarchy");
	hbox->addChild(group);

	group->addChild(WidgetLabel::create("hierarchy_label_0"));
	group->addChild(WidgetLabel::create("hierarchy_label_1"));

	return 1;
}

int AppWorldLogic::shutdown()
{
	// удаляем все подписки на события где-то при завершении работы
	econnections.disconnectAll();

	return 1;
}

```

</details>


#### Жизненный цикл виджетов


По умолчанию жизненный цикл каждого нового виджета совпадает с жизненным циклом **[Engine](#LIFETIME_ENGINE)** (т.е. виджет будет удалён при завершении работы движка). Но можно выбрать, чем будет управляться жизненный цикл виджета:

- Отдельным **[window](#LIFETIME_WINDOW)** — в этом случае виджет удаляется автоматически при удалении окна.
- **[world](#LIFETIME_WORLD)** — в этом случае виджет удаляется при закрытии сцены.
- **[Manually](#LIFETIME_MANUAL)** — в этом случае виджет нужно удалять вручную.


Примеры ниже показывают, как работают разные типы управления жизненным циклом.


##### Управление жизненным циклом с помощью сцены


В этом примере виджеты появляются при загрузке сцены. При перезагрузке или выходе из сцены, либо при закрытии окна движка, виджеты удаляются, так как их жизненным циклом управляет *сцена*. Соответствующие сообщения будут показаны в консоли.


<details>
<summary>AppWorldLogic.cpp | Close</summary>

`AppWorldLogic.cpp`


```cpp
#include "AppWorldLogic.h"
#include <UnigineWidgets.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econn;

void on_button_click(const WidgetPtr &button, int mbuttons)
{
	Log::message("world button click\n");
}

void on_button_remove(const WidgetPtr &button)
{
	Log::message("world button removed\n");
}

void on_hbox_remove(const WidgetPtr &hbox)
{
	Log::message("world hbox hierarchy removed\n");
}

int AppWorldLogic::init()
{

	// отдельный виджет сцены
	WidgetButtonPtr button = WidgetButton::create("WORLD_BUTTON");
	button->setLifetime(Widget::LIFETIME_WORLD);
	button->getEventClicked().connect(econn, on_button_click);
	button->getEventRemove().connect(econn, on_button_remove);
	WindowManager::getMainWindow()->addChild(button);

	// иерархия сцены
	WidgetHBoxPtr hbox = WidgetHBox::create();
	hbox->setLifetime(Widget::LIFETIME_WORLD);
	hbox->getEventRemove().connect(econn, on_hbox_remove);
	hbox->setBackground(1);
	hbox->setBackgroundColor(Math::vec4_red);
	WindowManager::getMainWindow()->addChild(hbox, Gui::ALIGN_EXPAND);

	WidgetGroupBoxPtr group = WidgetGroupBox::create();
	group->setBackground(1);
	group->setText("World Hierarchy");
	hbox->addChild(group);

	group->addChild(WidgetLabel::create("hierarchy_world_label_0"));
	group->addChild(WidgetLabel::create("hierarchy_world_label_1"));

	return 1;
}

int AppWorldLogic::shutdown()
{
	// удаляем все подписки на события
	econn.disconnectAll();

	return 1;
}


```

</details>


##### Управление жизненным циклом с помощью окна


В этом примере виджеты появляются в отдельном окне. При закрытии окна виджеты удаляются, так как их жизненным циклом управляет это *окно*. Консоль показывает следующую информацию:

- Удалены ли окно, кнопка и иерархия hbox.
- Сработали ли обратные вызовы удаления.
- Сообщения от обратных вызовов удаления.


После закрытия окно можно пересоздать, нажав **T**.


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineWidgets.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

EngineWindowViewportPtr window;

WidgetButtonPtr button;
WidgetHBoxPtr hbox;

bool button_remove_handler = false;
bool hbox_remove_handler = false;

void on_window_button_click()
{
	Log::message("window button click\n");
}

void on_window_button_remove()
{
	Log::message("window button removed\n");
	button_remove_handler = true;
}

void on_window_hbox_remove()
{
	Log::message("window hbox hierarchy removed\n");
	hbox_remove_handler = true;
}

void create_window()
{

	button_remove_handler = false;
	hbox_remove_handler = false;

	window = EngineWindowViewport::create("Test", 512, 256, EngineWindow::FLAGS_SHOWN);

	// отдельный виджет окна
	button = WidgetButton::create("WINDOW_BUTTON");
	button->setLifetime(Widget::LIFETIME_WINDOW);
	button->getEventClicked().connect(econnections, on_window_button_click);
	button->getEventRemove().connect(econnections, on_window_button_remove);
	window->addChild(button);

	// иерархия окна
	hbox = WidgetHBox::create();
	hbox->setLifetime(Widget::LIFETIME_WINDOW);
	hbox->getEventRemove().connect(econnections, on_window_hbox_remove);
	hbox->setBackground(1);
	hbox->setBackgroundColor(Math::vec4_red);
	window->addChild(hbox, Gui::ALIGN_EXPAND);

	WidgetGroupBoxPtr group = WidgetGroupBox::create();
	group->setBackground(1);
	group->setText("Window Hierarchy");
	hbox->addChild(group);

	group->addChild(WidgetLabel::create("hierarchy_window_label_0"));
	group->addChild(WidgetLabel::create("hierarchy_window_label_1"));

}

int AppSystemLogic::init()
{

	create_window();

	return 1;
}

int AppSystemLogic::update()
{

	if (Input::isKeyDown(Input::KEY_T) && window.isDeleted())
		create_window();

	Log::message("window deleted: %d, button deleted: %d, hbox deleted: %d, button remove handler: %d, hbox remove handler: %d\n",
		window.isDeleted(), button.isDeleted(), hbox.isDeleted(), button_remove_handler, hbox_remove_handler);

	return 1;
}

int AppSystemLogic::shutdown()
{
	// удаляем все подписки на события
	econnections.disconnectAll();

	return 1;
}


```

</details>


##### Управление жизненным циклом с помощью движка


Виджеты создаются при инициализации движка, а затем добавляются в отдельное окно. Консоль показывает следующую информацию:


- Удалены ли окно, кнопка и иерархия hbox.
- Сработали ли обратные вызовы удаления.
- Сообщения от обратных вызовов удаления.


При закрытии окна оно будет удалено, и информация в консоли изменится. Все остальные виджеты удаляются только при завершении работы движка, так как их жизненным циклом управляет движок.


Если отдельное окно закрыто, нажмите **T**, чтобы пересоздать его.


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineWidgets.h>

using namespace Unigine;

// экземпляр класса EventConnections для управления подписками на события
EventConnections econnections;

EngineWindowViewportPtr engine_window;

WidgetButtonPtr engine_button;
WidgetHBoxPtr engine_hbox;

bool engine_button_remove_handler = false;
bool engine_hbox_remove_handler = false;

void on_engine_button_click(const WidgetPtr &button, int mbuttons)
{
	Log::message("engine button click\n");
}

void on_engine_button_remove(const WidgetPtr &button)
{
	Log::message("engine button removed\n");
	engine_button_remove_handler = true;
}

void on_engine_hbox_remove(const WidgetPtr &hbox)
{
	Log::message("engine hbox hierarchy removed\n");
	engine_hbox_remove_handler = true;
}

void create_engine_window()
{

	engine_window = EngineWindowViewport::create("Test", 512, 256, EngineWindow::FLAGS_SHOWN);

	engine_window->addChild(engine_button);
	engine_window->addChild(engine_hbox, Gui::ALIGN_EXPAND);

}

int AppSystemLogic::init()
{

	engine_button_remove_handler = false;
	engine_hbox_remove_handler = false;

	// single engine widget
	engine_button = WidgetButton::create("ENGINE_BUTTON");
	engine_button->setLifetime(Widget::LIFETIME_ENGINE);
	engine_button->getEventClicked().connect(econnections, on_engine_button_click);
	engine_button->getEventRemove().connect(econnections, on_engine_button_remove);

	// engine hierarchy
	engine_hbox = WidgetHBox::create();
	engine_hbox->setLifetime(Widget::LIFETIME_ENGINE);
	engine_hbox->getEventRemove().connect(econnections, on_engine_hbox_remove);
	engine_hbox->setBackground(1);
	engine_hbox->setBackgroundColor(Math::vec4_red);

	WidgetGroupBoxPtr engine_group = WidgetGroupBox::create();
	engine_group->setBackground(1);
	engine_group->setText("Engine Hierarchy");
	engine_hbox->addChild(engine_group);

	engine_group->addChild(WidgetLabel::create("hierarchy_engine_label_0"));
	engine_group->addChild(WidgetLabel::create("hierarchy_engine_label_1"));

	create_engine_window();

	return 1;
}

int AppSystemLogic::update()
{

	if (Input::isKeyDown(Input::KEY_T) && engine_window.isDeleted())
		create_engine_window();

	Log::message("engine window deleted: %d, engine button deleted: %d, engine hbox deleted: %d, engine button remove handler: %d, engine hbox remove handler: %d\n",
		engine_window.isDeleted(), engine_button.isDeleted(), engine_hbox.isDeleted(), engine_button_remove_handler, engine_hbox_remove_handler);

	return 1;
}

int AppSystemLogic::shutdown()
{
	// удаляем все подписки на события
	econnections.disconnectAll();

	return 1;
}


```

</details>


### See Also


- Пример C++
- Набор [UnigineScript samples](../../../code/uniginescript/samples/widgets.md), находящихся в папке `<UnigineSDK>/data/samples/widgets/`


## Widget Class

### Перечисления

## TYPE

| Name | Description |
|---|---|
| **WIDGET_VBOX** = 0 | [Vertical box](../../../code/gui/ui/ui_containers.md#vbox). См. также: [WidgetVBox](../../../api/library/gui/class.widgetvbox_cpp.md). |
| **WIDGET_HBOX** = 1 | [Horizontal box](../../../code/gui/ui/ui_containers.md#hbox). См. также: [WidgetHBox](../../../api/library/gui/class.widgethbox_cpp.md). |
| **WIDGET_GRID_BOX** = 2 | [Grid box](../../../code/gui/ui/ui_containers.md#gridbox). См. также: [WidgetGridBox](../../../api/library/gui/class.widgetgridbox_cpp.md). |
| **WIDGET_VPANED** = 3 | [Vertical box that allows resizing of its children](../../../code/gui/ui/ui_containers.md#vpaned). См. также: [WidgetVPaned](../../../api/library/gui/class.widgetvpaned_cpp.md). |
| **WIDGET_HPANED** = 4 | [Horizontal box that allows resizing of its children](../../../code/gui/ui/ui_containers.md#hpaned). См. также: [WidgetHPaned](../../../api/library/gui/class.widgethpaned_cpp.md). |
| **WIDGET_LABEL** = 5 | [Text label](../../../code/gui/ui/ui_widgets.md#label). См. также: [WidgetLabel](../../../api/library/gui/class.widgetlabel_cpp.md). |
| **WIDGET_BUTTON** = 6 | [Simple button](../../../code/gui/ui/ui_widgets.md#button). См. также: [WidgetButton](../../../api/library/gui/class.widgetbutton_cpp.md). |
| **WIDGET_EDIT_LINE** = 7 | [Text field](../../../code/gui/ui/ui_widgets.md#editline). См. также: [WidgetEditline](../../../api/library/gui/class.widgeteditline_cpp.md). |
| **WIDGET_EDIT_TEXT** = 8 | [Multiline text field](../../../code/gui/ui/ui_widgets.md#edittext). См. также: [WidgetEdittext](../../../api/library/gui/class.widgetedittext_cpp.md). |
| **WIDGET_CHECK_BOX** = 9 | [Checkbox](../../../code/gui/ui/ui_widgets.md#checkbox). См. также: [WidgetCheckbox](../../../api/library/gui/class.widgetcheckbox_cpp.md). |
| **WIDGET_COMBO_BOX** = 10 | [Combobox](../../../code/gui/ui/ui_widgets.md#combobox). См. также: [WidgetCombobox](../../../api/library/gui/class.widgetcombobox_cpp.md). |
| **WIDGET_CANVAS** = 11 | Виджет canvas для отрисовки текста, линий и полигонов. См. также: [WidgetCanvas](../../../api/library/gui/class.widgetcanvas_cpp.md). |
| **WIDGET_GROUP_BOX** = 12 | [Group box](../../../code/gui/ui/ui_containers.md#groupbox). См. также: [WidgetGroupBox](../../../api/library/gui/class.widgetgroupbox_cpp.md). |
| **WIDGET_LIST_BOX** = 13 | [List box](../../../code/gui/ui/ui_widgets.md#listbox). См. также: [WidgetListBox](../../../api/library/gui/class.widgetlistbox_cpp.md). |
| **WIDGET_TREE_BOX** = 14 | [Tree box](../../../code/gui/ui/ui_widgets.md#treebox). См. также: [WidgetTreeBox](../../../api/library/gui/class.widgettreebox_cpp.md). |
| **WIDGET_TAB_BOX** = 15 | [Tabbed box](../../../code/gui/ui/ui_containers.md#tabbox). См. также: [WidgetTabBox](../../../api/library/gui/class.widgettabbox_cpp.md). |
| **WIDGET_SCROLL** = 16 | Полоса прокрутки: [horizontal](../../../code/gui/ui/ui_widgets.md#hscroll) or [vertical](../../../code/gui/ui/ui_widgets.md#vscroll). См. также: [WidgetScroll](../../../api/library/gui/class.widgetscroll_cpp.md). |
| **WIDGET_SCROLL_BOX** = 17 | [Box with scrolling](../../../code/gui/ui/ui_containers.md#scrollbox). См. также: [WidgetScrollBox](../../../api/library/gui/class.widgetscrollbox_cpp.md). |
| **WIDGET_SPACER** = 18 | Разделитель: [horizontal](../../../code/gui/ui/ui_widgets.md#hspacer) or [vertical](../../../code/gui/ui/ui_widgets.md#vspacer). См. также: [WidgetSpacer](../../../api/library/gui/class.widgetspacer_cpp.md). |
| **WIDGET_SLIDER** = 19 | Слайдер: [horizontal](../../../code/gui/ui/ui_widgets.md#hslider) or [vertical](../../../code/gui/ui/ui_widgets.md#vslider). См. также: [WidgetSlider](../../../api/library/gui/class.widgetslider_cpp.md). |
| **WIDGET_SPIN_BOX** = 20 | [Spinbox](../../../code/gui/ui/ui_widgets.md#spinbox). См. также: [WidgetSpinBox](../../../api/library/gui/class.widgetspinbox_cpp.md). |
| **WIDGET_SPIN_BOX_DOUBLE** = 21 | [Spinbox](../../../code/gui/ui/ui_widgets.md#spinbox) со значениями типа double. См. также: [WidgetSpinBoxDouble](../../../api/library/gui/class.widgetspinboxdouble_cpp.md). |
| **WIDGET_ICON** = 22 | [Icon](../../../code/gui/ui/ui_widgets.md#icon). См. также: [WidgetIcon](../../../api/library/gui/class.widgeticon_cpp.md). |
| **WIDGET_SPRITE** = 23 | [Sprite](../../../code/gui/ui/ui_widgets.md#sprite). См. также: [WidgetSprite](../../../api/library/gui/class.widgetsprite_cpp.md). |
| **WIDGET_SPRITE_VIDEO** = 24 | Видео-спрайт. См. также: [WidgetSpriteVideo](../../../api/library/gui/class.widgetspritevideo_cpp.md). |
| **WIDGET_SPRITE_SHADER** = 25 | Шейдерный спрайт. См. также: [WidgetSpriteShader](../../../api/library/gui/class.widgetspriteshader_cpp.md). |
| **WIDGET_SPRITE_VIEWPORT** = 26 | Спрайт viewport. См. также: [WidgetSpriteViewport](../../../api/library/gui/class.widgetspriteviewport_cpp.md). |
| **WIDGET_SPRITE_NODE** = 27 | Спрайт узла. См. также: [WidgetSpriteNode](../../../api/library/gui/class.widgetspritenode_cpp.md). |
| **WIDGET_MENU_BAR** = 28 | [Menu bar](../../../code/gui/ui/ui_widgets.md#menubar). См. также: [WidgetMenuBar](../../../api/library/gui/class.widgetmenubar_cpp.md). |
| **WIDGET_MENU_BOX** = 29 | [Menu](../../../code/gui/ui/ui_widgets.md#menubox). См. также: [WidgetMenuBox](../../../api/library/gui/class.widgetmenubox_cpp.md). |
| **WIDGET_WINDOW** = 30 | [Window](../../../code/gui/ui/ui_containers.md#window). См. также: [WidgetWindow](../../../api/library/gui/class.widgetwindow_cpp.md). |
| **WIDGET_DIALOG** = 31 | [Dialog window](../../../code/gui/ui/ui_containers.md#dialog). См. также: [WidgetDialog](../../../api/library/gui/class.widgetdialog_cpp.md). |
| **WIDGET_DIALOG_MESSAGE** = 32 | Диалог сообщения. См. также: [WidgetDialogMessage](../../../api/library/gui/class.widgetdialogmessage_cpp.md). |
| **WIDGET_DIALOG_FILE** = 33 | Диалог выбора файла. См. также: [WidgetDialogFile](../../../api/library/gui/class.widgetdialogfile_cpp.md). |
| **WIDGET_DIALOG_COLOR** = 34 | Диалог выбора цвета. См. также: [WidgetDialogColor](../../../api/library/gui/class.widgetdialogcolor_cpp.md). |
| **WIDGET_DIALOG_IMAGE** = 35 | Диалог изображения. См. также: [WidgetDialogImage](../../../api/library/gui/class.widgetdialogimage_cpp.md). |
| **WIDGET_MANIPULATOR** = 36 | Виджет манипулятора. См. также: [WidgetManipulator](../../../api/library/gui/class.widgetmanipulator_cpp.md). |
| **WIDGET_MANIPULATOR_TRANSLATOR** = 37 | Манипулятор перемещения. См. также: [WidgetManipulatorTranslator](../../../api/library/gui/class.widgetmanipulatortranslator_cpp.md). |
| **WIDGET_MANIPULATOR_ROTATOR** = 38 | Манипулятор вращения. См. также: [WidgetManipulatorRotator](../../../api/library/gui/class.widgetmanipulatorrotator_cpp.md). |
| **WIDGET_MANIPULATOR_SCALER** = 39 | Манипулятор масштабирования. См. также: [WidgetManipulatorScaler](../../../api/library/gui/class.widgetmanipulatorscaler_cpp.md). |
| **WIDGET_EXTERN** = 40 | Внешний виджет. |
| **WIDGET_ENGINE** = 41 | Специфичный для движка виджет (манипулятор). См. также: [WidgetManipulator](../../../api/library/gui/class.widgetmanipulator_cpp.md). |
| **WIDGET_HIT_TEST_AREA** = 42 | Область hit-test. См. также: [WidgetHitTestArea](../../../api/library/gui/class.widgethittestarea_cpp.md). |
| **NUM_WIDGETS** = 43 | Общее количество типов виджетов. |

## LIFETIME

| Name | Description |
|---|---|
| **LIFETIME_WORLD** = 0 | Жизненным циклом виджета или пользовательского интерфейса управляет сцена. Виджет/пользовательский интерфейс будет автоматически удалён при закрытии сцены. |
| **LIFETIME_WINDOW** = 1 | Жизненным циклом виджета или пользовательского интерфейса управляет окно. Виджет/пользовательский интерфейс будет автоматически удалён при удалении окна. |
| **LIFETIME_ENGINE** = 2 | Жизненным циклом виджета или пользовательского интерфейса управляет движок. Виджет/пользовательский интерфейс будет автоматически удалён при завершении работы движка. > **Notice:** При использовании этого типа управления жизненным циклом экземпляр GUI для виджета может быть пустым: он будет назначен автоматически при добавлении виджета в окно. Для пользовательского интерфейса экземпляр Gui должен быть установлен через метод *[setGui()](../../../api/library/gui/class.userinterface_cpp.md#setGui_Gui_void)*. |
| **LIFETIME_MANUAL** = 3 | Жизненным циклом виджета или пользовательского интерфейса управляет пользователь. Виджет/пользовательский интерфейс следует удалять вручную. > **Notice:** При использовании этого типа управления жизненным циклом экземпляр GUI для виджета может быть пустым: он будет назначен автоматически при добавлении виджета в окно. Для пользовательского интерфейса экземпляр Gui должен быть установлен через метод *[setGui()](../../../api/library/gui/class.userinterface_cpp.md#setGui_Gui_void)*. |

### Методы класса

## int getNumChildren () const

Возвращает текущее количество дочерних виджетов.
### Возвращаемое значение

Текущее количество дочерних виджетов.
## void setFontWrap ( int wrap )

Устанавливает новое значение, указывающее, включён ли перенос текста по ширине виджета.
### Аргументы

- *int* **wrap** - Значение 1 для переноса текста; иначе 0.

## int getFontWrap () const

Возвращает текущее значение, указывающее, включён ли перенос текста по ширине виджета.
### Возвращаемое значение

Текущее значение 1 для переноса текста; иначе 0.
## void setFontRich ( int rich )

Устанавливает новое значение, указывающее, используется ли форматирование rich text.
### Аргументы

- *int* **rich** - Значение 1 для форматирования rich text; иначе 0.

## int getFontRich () const

Возвращает текущее значение, указывающее, используется ли форматирование rich text.
### Возвращаемое значение

Текущее значение 1 для форматирования rich text; иначе 0.
## void setFontOutline ( int outline )

Устанавливает новое значение, указывающее, отрисовывается ли текст виджета с тенью. Положительные или отрицательные значения определяют расстояние в пикселях, на которое смещается контур шрифта.
### Аргументы

- *int* **outline** - Положительное значение, если контур смещён в направлении нижнего правого угла, отрицательное значение, если контур смещён в направлении верхнего левого угла. 0, если контур не задан.

## int getFontOutline () const

Возвращает текущее значение, указывающее, отрисовывается ли текст виджета с тенью. Положительные или отрицательные значения определяют расстояние в пикселях, на которое смещается контур шрифта.
### Возвращаемое значение

Текущее положительное значение, если контур смещён в направлении нижнего правого угла, отрицательное значение, если контур смещён в направлении верхнего левого угла. 0, если контур не задан.
## void setFontVOffset ( int voffset )

Устанавливает новое вертикальное смещение шрифта, используемого виджетом.
### Аргументы

- *int* **voffset** - Значение вертикального смещения, в пикселях.

## int getFontVOffset () const

Возвращает текущее вертикальное смещение шрифта, используемого виджетом.
### Возвращаемое значение

Текущее значение вертикального смещения, в пикселях.
## void setFontHOffset ( int hoffset )

Устанавливает новое горизонтальное смещение шрифта, используемого виджетом.
### Аргументы

- *int* **hoffset** - Значение горизонтального смещения, в пикселях.

## int getFontHOffset () const

Возвращает текущее горизонтальное смещение шрифта, используемого виджетом.
### Возвращаемое значение

Текущее значение горизонтального смещения, в пикселях.
## void setFontVSpacing ( int vspacing )

Устанавливает новый интервал (в пикселях) между строками текста виджета.
### Аргументы

- *int* **vspacing** - Значение вертикального интервала, в пикселях.

## int getFontVSpacing () const

Возвращает текущий интервал (в пикселях) между строками текста виджета.
### Возвращаемое значение

Текущее значение вертикального интервала, в пикселях.
## void setFontHSpacing ( int hspacing )

Устанавливает новый интервал (в пикселях) между символами текста виджета.
### Аргументы

- *int* **hspacing** - Значение горизонтального интервала, в пикселях.

## int getFontHSpacing () const

Возвращает текущий интервал (в пикселях) между символами текста виджета.
### Возвращаемое значение

Текущее значение горизонтального интервала, в пикселях.
## void setFontPermanent ( int permanent )

Устанавливает новый флаг, указывающий, не изменяется ли цвет текста виджета (например, при переходе виджета в неактивное состояние или потере фокуса).
### Аргументы

- *int* **permanent** - Значение 1, чтобы цвет текста оставался неизменным; 0, чтобы он изменялся.

## int getFontPermanent () const

Возвращает текущий флаг, указывающий, не изменяется ли цвет текста виджета (например, при переходе виджета в неактивное состояние или потере фокуса).
### Возвращаемое значение

Текущее значение 1, чтобы цвет текста оставался неизменным; 0, чтобы он изменялся.
## void setFontColor ( const Math:: vec4 & color )

Устанавливает новый цвет шрифта, используемого виджетом.
### Аргументы

- *const  Math::[vec4](../../../api/library/math/class.vec4_cpp.md)&* **color** - Цвет шрифта.

## Math:: vec4 getFontColor () const

Возвращает текущий цвет шрифта, используемого виджетом.
### Возвращаемое значение

Текущий цвет шрифта.
## void setFontSize ( int size )

Устанавливает новый размер шрифта, используемого виджетом.
### Аргументы

- *int* **size** - Размер шрифта в пикселях.

## int getFontSize () const

Возвращает текущий размер шрифта, используемого виджетом.
### Возвращаемое значение

Текущий размер шрифта в пикселях.
## void setMouseCursor ( int cursor )

Устанавливает новый текущий указатель мыши.
### Аргументы

- *int* **cursor** - Указатель мыши. См. список доступных указателей с префиксом CURSOR_* в статье о функциях класса Gui.

## int getMouseCursor () const

Возвращает текущий указатель мыши.
### Возвращаемое значение

Текущий указатель мыши. См. список доступных указателей с префиксом CURSOR_* в статье о функциях класса Gui.
## int getMouseY () const

Возвращает текущую координату Y позиции указателя мыши в локальном пространстве виджета.
### Возвращаемое значение

Текущая координата Y позиции указателя мыши в локальном пространстве виджета.
## int getMouseX () const

Возвращает текущую координату X позиции указателя мыши в локальном пространстве виджета.
### Возвращаемое значение

Текущая координата X позиции указателя мыши в локальном пространстве виджета.
## void setHeight ( int height )

Устанавливает новую минимальную высоту виджета.
> **Notice:** Виджет не может быть меньше своего содержимого (текстуры, видео и т.д.). Виджет можно сделать только больше размера своего содержимого. Например, [WidgetButton](../../../api/library/gui/class.widgetbutton_cpp.md) можно сделать больше его текстуры, но нельзя сделать меньше размеров текстуры.


### Аргументы

- *int* **height** - Минимальная высота виджета, в [logical units](../../../principles/dpi/index.md). Если указано отрицательное значение, вместо него будет использовано 0.

## int getHeight () const

Возвращает текущую минимальную высоту виджета.
> **Notice:** Виджет не может быть меньше своего содержимого (текстуры, видео и т.д.). Виджет можно сделать только больше размера своего содержимого. Например, [WidgetButton](../../../api/library/gui/class.widgetbutton_cpp.md) можно сделать больше его текстуры, но нельзя сделать меньше размеров текстуры.


### Возвращаемое значение

Текущая минимальная высота виджета, в [logical units](../../../principles/dpi/index.md). Если указано отрицательное значение, вместо него будет использовано 0.
## void setWidth ( int width )

Устанавливает новую минимальную ширину виджета.
> **Notice:** Виджет не может быть меньше своего содержимого (текстуры, видео и т.д.). Виджет можно сделать только больше размера своего содержимого. Например, [WidgetButton](../../../api/library/gui/class.widgetbutton_cpp.md) можно сделать больше его текстуры, но нельзя сделать меньше размеров текстуры.


### Аргументы

- *int* **width** - Минимальная ширина виджета, в [logical units](../../../principles/dpi/index.md). Если указано отрицательное значение, вместо него будет использовано 0.

## int getWidth () const

Возвращает текущую минимальную ширину виджета.
> **Notice:** Виджет не может быть меньше своего содержимого (текстуры, видео и т.д.). Виджет можно сделать только больше размера своего содержимого. Например, [WidgetButton](../../../api/library/gui/class.widgetbutton_cpp.md) можно сделать больше его текстуры, но нельзя сделать меньше размеров текстуры.


### Возвращаемое значение

Текущая минимальная ширина виджета, в [logical units](../../../principles/dpi/index.md). Если указано отрицательное значение, вместо него будет использовано 0.
## int getScreenPositionY () const

Возвращает текущую экранную позицию виджета (его верхнего левого угла) на экране вдоль оси Y.
### Возвращаемое значение

Текущая экранная позиция вдоль оси Y в [logical units](../../../principles/dpi/index.md).
## int getScreenPositionX () const

Возвращает текущую экранную позицию виджета (его верхнего левого угла) на экране вдоль оси X.
### Возвращаемое значение

Текущая экранная позиция вдоль оси X в [logical units](../../../principles/dpi/index.md).
## void setPositionY ( int y )

Устанавливает новую координату Y позиции виджета относительно его родителя.
### Аргументы

- *int* **y** - Координата Y позиции виджета относительно его родителя.

## int getPositionY () const

Возвращает текущую координату Y позиции виджета относительно его родителя.
### Возвращаемое значение

Текущая координата Y позиции виджета относительно его родителя.
## void setPositionX ( int x )

Устанавливает новую координату X позиции виджета относительно его родителя.
### Аргументы

- *int* **x** - Координата X позиции виджета относительно его родителя.

## int getPositionX () const

Возвращает текущую координату X позиции виджета относительно его родителя.
### Возвращаемое значение

Текущая координата X позиции виджета относительно его родителя.
## void setNextFocus ( const Ptr < Widget >& focus )

Устанавливает новый виджет, который получит фокус следующим, если пользователь нажмёт **TAB**.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)>&* **focus** - Виджет, который получит фокус следующим, если пользователь нажмёт **TAB**.

## Ptr < Widget > getNextFocus () const

Возвращает текущий виджет, который получит фокус следующим, если пользователь нажмёт **TAB**.
### Возвращаемое значение

Текущий виджет, который получит фокус следующим, если пользователь нажмёт **TAB**.
## void setData ( const char * data )

Устанавливает новые пользовательские данные, связанные с виджетом.
### Аргументы

- *const char ** **data** - Пользовательские данные, связанные с виджетом. Данные могут быть строкой в формате xml.

## const char * getData () const

Возвращает текущие пользовательские данные, связанные с виджетом.
### Возвращаемое значение

Текущие пользовательские данные, связанные с виджетом. Данные могут быть строкой в формате xml.
## void setOrder ( int order )

Устанавливает новый порядок отрисовки (Z-order) для виджета. Чем выше значение, тем выше порядок виджета.
> **Notice:** Работает только для виджетов, добавленных в GUI через функцию [*Gui::addChild()*](../../../api/library/gui/class.gui_cpp.md#addChild_Widget_int_void) с указанным флагом [Gui::ALIGN_OVERLAP](../../../api/library/gui/class.gui_cpp.md#ALIGN_OVERLAP) (не должен быть [Gui::ALIGN_FIXED](../../../api/library/gui/class.gui_cpp.md#ALIGN_FIXED)).


```cpp
Unigine::Vector<Unigine::WidgetSpritePtr> sprites;

int AppWorldLogic::init()
{
	// создаём 3 квадрата разных цветов
	for (int i = 0; i < 3; i++)
	{
		WidgetSpritePtr &sprite = sprites.append();
		sprite = WidgetSprite::create(Gui::get(), "white.texture");
		sprite->setPosition(i * 40 + 50, i * 40 + 50);
		sprite->setWidth(100);
		sprite->setHeight(100);
		Gui::get()->addChild(sprite, Gui::ALIGN_OVERLAP);
	}

	sprites[0]->setColor(vec4(1, 0.3f, 0.3f, 1));
	sprites[1]->setColor(vec4(0.3f, 1, 0.3f, 1));
	sprites[2]->setColor(vec4(0.3f, 0.3f, 1, 1));

	return 1;
}

int AppWorldLogic::update()
{
	// нажмите клавишу пробел для случайной перестановки квадратов
	if (App::clearKeyState(' '))
	{
		for (int i = 0; i < 3; i++)
		{
			sprites[i]->setOrder(Game::getRandomInt(0, 10));

			Gui::get()->removeChild(sprites[i]);
			Gui::get()->addChild(sprites[i]);

			Log::message("%d ", sprites[i]->getOrder());
		}
		Log::message("\n");
	}
	return 1;
}

```


### Аргументы

- *int* **order** - Порядок отрисовки (z-order) для виджета, в диапазоне **[-128;127]**. (126 для профилировщика, 127 для консоли).

## int getOrder () const

Возвращает текущий порядок отрисовки (Z-order) для виджета. Чем выше значение, тем выше порядок виджета.
> **Notice:** Работает только для виджетов, добавленных в GUI через функцию [*Gui::addChild()*](../../../api/library/gui/class.gui_cpp.md#addChild_Widget_int_void) с указанным флагом [Gui::ALIGN_OVERLAP](../../../api/library/gui/class.gui_cpp.md#ALIGN_OVERLAP) (не должен быть [Gui::ALIGN_FIXED](../../../api/library/gui/class.gui_cpp.md#ALIGN_FIXED)).


```cpp
Unigine::Vector<Unigine::WidgetSpritePtr> sprites;

int AppWorldLogic::init()
{
	// создаём 3 квадрата разных цветов
	for (int i = 0; i < 3; i++)
	{
		WidgetSpritePtr &sprite = sprites.append();
		sprite = WidgetSprite::create(Gui::get(), "white.texture");
		sprite->setPosition(i * 40 + 50, i * 40 + 50);
		sprite->setWidth(100);
		sprite->setHeight(100);
		Gui::get()->addChild(sprite, Gui::ALIGN_OVERLAP);
	}

	sprites[0]->setColor(vec4(1, 0.3f, 0.3f, 1));
	sprites[1]->setColor(vec4(0.3f, 1, 0.3f, 1));
	sprites[2]->setColor(vec4(0.3f, 0.3f, 1, 1));

	return 1;
}

int AppWorldLogic::update()
{
	// нажмите клавишу пробел для случайной перестановки квадратов
	if (App::clearKeyState(' '))
	{
		for (int i = 0; i < 3; i++)
		{
			sprites[i]->setOrder(Game::getRandomInt(0, 10));

			Gui::get()->removeChild(sprites[i]);
			Gui::get()->addChild(sprites[i]);

			Log::message("%d ", sprites[i]->getOrder());
		}
		Log::message("\n");
	}
	return 1;
}

```


### Возвращаемое значение

Текущий порядок отрисовки (z-order) для виджета, в диапазоне **[-128;127]**. (126 для профилировщика, 127 для консоли).
## void setHidden ( bool hidden )

Устанавливает новое значение, указывающее, скрыт ли виджет.
### Аргументы

- *bool* **hidden** - Установите **true**, чтобы включить статус скрытости для виджета; **false** — чтобы отключить его.

## bool isHidden () const

Возвращает текущее значение, указывающее, скрыт ли виджет.
### Возвращаемое значение

**true**, если статус скрытости для виджета включён; иначе **false**.
## void setEnabled ( bool enabled )

Устанавливает новое значение, указывающее, включён ли виджет (может ли пользователь взаимодействовать с виджетом).
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить статус включённости (взаимодействия) для виджета; **false** — чтобы отключить его.

## bool isEnabled () const

Возвращает текущее значение, указывающее, включён ли виджет (может ли пользователь взаимодействовать с виджетом).
### Возвращаемое значение

**true**, если статус включённости (взаимодействия) для виджета включён; иначе **false**.
## void setIntersectionEnabled ( bool enabled )

Устанавливает новое значение, указывающее, включено ли обнаружение пересечения для виджета.
### Аргументы

- *bool* **enabled** - Установите **true**, чтобы включить обнаружение пересечения для виджета; **false** — чтобы отключить его.

## bool isIntersectionEnabled () const

Возвращает текущее значение, указывающее, включено ли обнаружение пересечения для виджета.
### Возвращаемое значение

**true**, если обнаружение пересечения для виджета включено; иначе **false**.
## void setFlags ( int flags )

Устанавливает новые флаги виджета.
### Аргументы

- *int* **flags** - Флаги виджета, предопределённые переменные [*ALIGN_**](../../../api/library/gui/class.gui_cpp.md#ALIGN_BACKGROUND).

## int getFlags () const

Возвращает текущие флаги виджета.
### Возвращаемое значение

Текущие флаги виджета, предопределённые переменные [*ALIGN_**](../../../api/library/gui/class.gui_cpp.md#ALIGN_BACKGROUND).
## void setParent ( const Ptr < Widget >& parent )

Устанавливает новый указатель на родительский виджет.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)>&* **parent** - Родительский виджет.

## Ptr < Widget > getParent () const

Возвращает текущий указатель на родительский виджет.
### Возвращаемое значение

Текущий родительский виджет.
## Ptr < Gui > getParentGui () const

Возвращает текущий экземпляр [Gui](../../../api/library/gui/class.gui_cpp.md), который в данный момент отрисовывает родителя виджета, если у виджета есть родитель. (Эту функцию можно использовать, если виджет создан и используется в двух разных GUI, например, в случае плагина Interface.)
### Возвращаемое значение

Текущий экземпляр GUI, используемый для родителя виджета.
## Ptr < Gui > getGui () const

Возвращает текущий экземпляр [Gui](../../../api/library/gui/class.gui_cpp.md), который отрисовывает виджет. (Эту функцию можно использовать, если виджет создан и используется в двух разных GUI, например, в случае плагина Interface.) Её можно вызывать только для корневых виджетов. Для дочерних виджетов см. *[getParentGui()](#getParentGui_Gui)*.
### Возвращаемое значение

Текущий экземпляр GUI, используемый для виджета.
## const char * getTypeName () const

Возвращает текущее имя типа виджета.
### Возвращаемое значение

Текущее имя типа виджета.
## Widget::TYPE getType () const

Возвращает текущий тип виджета.
### Возвращаемое значение

Текущий тип виджета.
## bool isLayout () const

Возвращает текущее значение, указывающее, является ли виджет layout.
### Возвращаемое значение

**true**, если виджет является layout; иначе **false**.
## bool isFixed () const

Возвращает текущее значение, указывающее, зафиксирован ли виджет.
### Возвращаемое значение

**true**, если виджет зафиксирован; иначе **false**.
## bool isBackground () const

Возвращает текущее значение, указывающее, является ли виджет фоновым.
### Возвращаемое значение

**true**, если виджет является фоновым; иначе **false**.
## bool isOverlapped () const

Возвращает текущее значение, указывающее, перекрыт ли виджет.
### Возвращаемое значение

**true**, если виджет перекрыт; иначе **false**.
## bool isExpanded () const

Возвращает текущее значение, указывающее, развёрнут ли виджет.
### Возвращаемое значение

**true**, если виджет развёрнут; иначе **false**.
## void setLifetime ( Widget::LIFETIME lifetime )

Устанавливает новый тип управления жизненным циклом для корня виджета, либо для самого виджета (если он не является дочерним для другого виджета).
> **Notice:** Жизненный цикл каждого виджета в иерархии определяется его корнем. Таким образом, тип управления жизненным циклом, установленный для дочернего виджета и отличающийся от установленного для корня, игнорируется.


### Аргументы

- *[Widget::LIFETIME](../../../api/library/gui/class.widget_cpp.md#LIFETIME)* **lifetime** - Тип управления жизненным циклом.

## Widget::LIFETIME getLifetime () const

Возвращает текущий тип управления жизненным циклом для корня виджета, либо для самого виджета (если он не является дочерним для другого виджета).
> **Notice:** Жизненный цикл каждого виджета в иерархии определяется его корнем. Таким образом, тип управления жизненным циклом, установленный для дочернего виджета и отличающийся от установленного для корня, игнорируется.


### Возвращаемое значение

Текущий тип управления жизненным циклом.
## float getDpiScale () const

Возвращает текущий DPI-масштаб, применяемый к виджету.
### Возвращаемое значение

Текущий DPI-масштаб, применяемый к виджету.
## int getRenderHeight () const

Возвращает текущую высоту рамки виджета в пикселях.
### Возвращаемое значение

Текущая высота рамки виджета в пикселях.
## int getRenderWidth () const

Возвращает текущую ширину рамки виджета в пикселях.
### Возвращаемое значение

Текущая ширина рамки виджета в пикселях.
## Event<const Ptr < Widget > &> getEventRemove () const

Событие, срабатывающее при удалении виджета. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Remove
void remove_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события Remove\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections remove_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventRemove().connect(remove_event_connections, remove_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventRemove().connect(remove_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Remove (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
remove_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection remove_event_connection;

// подписываемся на событие Remove с функцией-обработчиком, сохраняя соединение
publisher->getEventRemove().connect(remove_event_connection, remove_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
remove_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
remove_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Remove через соединение
remove_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Remove, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события Remove\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventRemove().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId remove_handler_id;

// подписываемся на событие Remove с лямбда-обработчиком, сохраняя идентификатор соединения
remove_handler_id = publisher->getEventRemove().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Remove (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventRemove().disconnect(remove_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Remove при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventRemove().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventRemove().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &, const Ptr < Widget > &> getEventDragDrop () const

Событие, срабатывающее при выполнении операции drag-and-drop с виджетом. Поддерживается всеми виджетами. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**, const Ptr<Widget> & **target_widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события DragDrop
void dragdrop_event_handler(const Ptr<Widget> & widget,  const Ptr<Widget> & target_widget)
{
	Log::message("\Обработка события DragDrop\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections dragdrop_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventDragDrop().connect(dragdrop_event_connections, dragdrop_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventDragDrop().connect(dragdrop_event_connections, [](const Ptr<Widget> & widget,  const Ptr<Widget> & target_widget) {
		Log::message("\Обработка события DragDrop (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
dragdrop_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection dragdrop_event_connection;

// подписываемся на событие DragDrop с функцией-обработчиком, сохраняя соединение
publisher->getEventDragDrop().connect(dragdrop_event_connection, dragdrop_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
dragdrop_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
dragdrop_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие DragDrop через соединение
dragdrop_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события DragDrop, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget,  const Ptr<Widget> & target_widget)
	{
		Log::message("\Обработка события DragDrop\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventDragDrop().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId dragdrop_handler_id;

// подписываемся на событие DragDrop с лямбда-обработчиком, сохраняя идентификатор соединения
dragdrop_handler_id = publisher->getEventDragDrop().connect(e_connections, [](const Ptr<Widget> & widget,  const Ptr<Widget> & target_widget) {
		Log::message("\Обработка события DragDrop (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventDragDrop().disconnect(dragdrop_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий DragDrop при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventDragDrop().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventDragDrop().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &, const Ptr < Widget > &> getEventDragMove () const

Событие, срабатывающее при перемещении виджета в фокусе. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**, const Ptr<Widget> & **underlying_widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события DragMove
void dragmove_event_handler(const Ptr<Widget> & widget,  const Ptr<Widget> & underlying_widget)
{
	Log::message("\Обработка события DragMove\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections dragmove_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventDragMove().connect(dragmove_event_connections, dragmove_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventDragMove().connect(dragmove_event_connections, [](const Ptr<Widget> & widget,  const Ptr<Widget> & underlying_widget) {
		Log::message("\Обработка события DragMove (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
dragmove_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection dragmove_event_connection;

// подписываемся на событие DragMove с функцией-обработчиком, сохраняя соединение
publisher->getEventDragMove().connect(dragmove_event_connection, dragmove_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
dragmove_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
dragmove_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие DragMove через соединение
dragmove_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события DragMove, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget,  const Ptr<Widget> & underlying_widget)
	{
		Log::message("\Обработка события DragMove\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventDragMove().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId dragmove_handler_id;

// подписываемся на событие DragMove с лямбда-обработчиком, сохраняя идентификатор соединения
dragmove_handler_id = publisher->getEventDragMove().connect(e_connections, [](const Ptr<Widget> & widget,  const Ptr<Widget> & underlying_widget) {
		Log::message("\Обработка события DragMove (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventDragMove().disconnect(dragmove_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий DragMove при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventDragMove().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventDragMove().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventLeave () const

Событие, срабатывающее, когда курсор мыши покидает виджет. Поддерживается всеми виджетами. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Leave
void leave_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события Leave\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections leave_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventLeave().connect(leave_event_connections, leave_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventLeave().connect(leave_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Leave (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
leave_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection leave_event_connection;

// подписываемся на событие Leave с функцией-обработчиком, сохраняя соединение
publisher->getEventLeave().connect(leave_event_connection, leave_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
leave_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
leave_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Leave через соединение
leave_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Leave, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события Leave\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventLeave().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId leave_handler_id;

// подписываемся на событие Leave с лямбда-обработчиком, сохраняя идентификатор соединения
leave_handler_id = publisher->getEventLeave().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Leave (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventLeave().disconnect(leave_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Leave при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventLeave().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventLeave().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventEnter () const

Событие, срабатывающее, когда курсор мыши входит в виджет. Поддерживается всеми виджетами. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Enter
void enter_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события Enter\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections enter_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventEnter().connect(enter_event_connections, enter_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventEnter().connect(enter_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Enter (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
enter_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection enter_event_connection;

// подписываемся на событие Enter с функцией-обработчиком, сохраняя соединение
publisher->getEventEnter().connect(enter_event_connection, enter_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
enter_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
enter_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Enter через соединение
enter_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Enter, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события Enter\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventEnter().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId enter_handler_id;

// подписываемся на событие Enter с лямбда-обработчиком, сохраняя идентификатор соединения
enter_handler_id = publisher->getEventEnter().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Enter (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventEnter().disconnect(enter_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Enter при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventEnter().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventEnter().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &, unsigned int> getEventTextPressed () const

Событие, срабатывающее при нажатии виртуальной клавиши, когда виджет находится в фокусе. Поддерживается следующими виджетами:
- [*WidgetEditLine*](../../../api/library/gui/class.widgeteditline_cpp.md)
- [*WidgetEditText*](../../../api/library/gui/class.widgetedittext_cpp.md)

 **Виртуальная клавиша** — это значение, в которое операционная система преобразует код сканирования (например, код сканирования **Q** будет соответствовать виртуальной клавише **Q** на клавиатуре *QWERTY*, тогда как на клавиатуре *AZERTY* — виртуальной клавише **A**; либо код сканирования **NUMPAD_DIGIT_7** может преобразовываться в виртуальную **NUMPAD_HOME** или **NUMPAD_DIGIT_7** в зависимости от текущего состояния *Num Lock*). Виртуальные клавиши используются, когда важно знать, что именно ввёл пользователь (не просто физическую кнопку, а именно букву).
 Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**, unsigned int **unicode**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TextPressed
void textpressed_event_handler(const Ptr<Widget> & widget,  unsigned int unicode)
{
	Log::message("\Обработка события TextPressed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections textpressed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventTextPressed().connect(textpressed_event_connections, textpressed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventTextPressed().connect(textpressed_event_connections, [](const Ptr<Widget> & widget,  unsigned int unicode) {
		Log::message("\Обработка события TextPressed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
textpressed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection textpressed_event_connection;

// подписываемся на событие TextPressed с функцией-обработчиком, сохраняя соединение
publisher->getEventTextPressed().connect(textpressed_event_connection, textpressed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
textpressed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
textpressed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TextPressed через соединение
textpressed_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события TextPressed, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget,  unsigned int unicode)
	{
		Log::message("\Обработка события TextPressed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventTextPressed().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId textpressed_handler_id;

// подписываемся на событие TextPressed с лямбда-обработчиком, сохраняя идентификатор соединения
textpressed_handler_id = publisher->getEventTextPressed().connect(e_connections, [](const Ptr<Widget> & widget,  unsigned int unicode) {
		Log::message("\Обработка события TextPressed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventTextPressed().disconnect(textpressed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TextPressed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventTextPressed().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventTextPressed().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &, int> getEventKeyPressed () const

Событие, срабатывающее при нажатии клавиши (по коду сканирования), когда виджет находится в фокусе. Поддерживается следующими виджетами:
- [*WidgetEditLine*](../../../api/library/gui/class.widgeteditline_cpp.md)
- [*WidgetEditText*](../../../api/library/gui/class.widgetedittext_cpp.md)

 **Scan code** - is a code assigned to avery key on the keyboard. Keyboard drivers use scan codes to detect which key is pressed. Scan codes are assigned to keys on the hardware level and are not affected by the states of modifiers like *Caps Lock*, *Num Lock*, *Scroll Lock*, *Shift*, *Alt*, and *Ctrl* making it possible to implement identical control on different types of keyboards (*uiQWERTY*, *AZERTY*, *QWERTC*, etc.). Scan codes are used when only a physical position of a key (a button) is important (e.g. in the *ControlsApp* class or Console key).
 Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**, int **key**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события KeyPressed
void keypressed_event_handler(const Ptr<Widget> & widget,  int key)
{
	Log::message("\Обработка события KeyPressed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections keypressed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventKeyPressed().connect(keypressed_event_connections, keypressed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventKeyPressed().connect(keypressed_event_connections, [](const Ptr<Widget> & widget,  int key) {
		Log::message("\Обработка события KeyPressed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
keypressed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection keypressed_event_connection;

// подписываемся на событие KeyPressed с функцией-обработчиком, сохраняя соединение
publisher->getEventKeyPressed().connect(keypressed_event_connection, keypressed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
keypressed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
keypressed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие KeyPressed через соединение
keypressed_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события KeyPressed, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget,  int key)
	{
		Log::message("\Обработка события KeyPressed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventKeyPressed().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId keypressed_handler_id;

// подписываемся на событие KeyPressed с лямбда-обработчиком, сохраняя идентификатор соединения
keypressed_handler_id = publisher->getEventKeyPressed().connect(e_connections, [](const Ptr<Widget> & widget,  int key) {
		Log::message("\Обработка события KeyPressed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventKeyPressed().disconnect(keypressed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий KeyPressed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventKeyPressed().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventKeyPressed().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &, int> getEventReleased () const

Событие, срабатывающее при отпускании кнопки мыши после клика где-либо на виджете. Поддерживается следующими виджетами:
- [*WidgetButton*](../../../api/library/gui/class.widgetbutton_cpp.md)
- [*WidgetGroupBox*](../../../api/library/gui/class.widgetgroupbox_cpp.md)
- [*WidgetIcon*](../../../api/library/gui/class.widgeticon_cpp.md)
- [*WidgetManipulatorRotator*](../../../api/library/gui/class.widgetmanipulatorrotator_cpp.md) (**mouse_buttons** is always 0)
- [*WidgetManipulatorScaler*](../../../api/library/gui/class.widgetmanipulatorscaler_cpp.md) (**mouse_buttons** is always 0)
- [*WidgetManipulatorTranslator*](../../../api/library/gui/class.widgetmanipulatortranslator_cpp.md) (**mouse_buttons** is always 0)
- [*WidgetSlider*](../../../api/library/gui/class.widgetslider_cpp.md)
- [*WidgetSpinBox*](../../../api/library/gui/class.widgetspinbox_cpp.md)
- [*WidgetSpinBoxDouble*](../../../api/library/gui/class.widgetspinboxdouble_cpp.md)
- [*WidgetWindow*](../../../api/library/gui/class.widgetwindow_cpp.md)
- [*EngineWindow*](../../../api/library/gui/class.enginewindow_cpp.md) (**mouse_buttons** is always 0)

 Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**, int **mouse_buttons**)*
- The `mouse_buttons` argument is a mask representing a combination of the following flags: *[Gui::MOUSE_MASK_LEFT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_LEFT) | [Gui::MOUSE_MASK_MIDDLE](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_MIDDLE) | [Gui::MOUSE_MASK_RIGHT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_RIGHT)*.


**Usage Example:**


```cpp
// auxiliary variable simplifying subscriptions management
EventConnections econn;

// ...

// creating a button widget
auto widget_button = WidgetButton::create(WindowManager::getMainWindow()->getGui(), "button");
WindowManager::getMainWindow()->getGui()->addChild(widget_button, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

// enabling Console onscreen overlay
Console::setOnscreen(true);

// subscribing to the Released event with a lambda-handler
widget_button->getEventReleased().connect(econn, [](WidgetPtr const& widget, int mouse_buttons) {
	int left = mouse_buttons & Gui::MOUSE_MASK_LEFT;
	int right = mouse_buttons & Gui::MOUSE_MASK_RIGHT;
	int middle = mouse_buttons & Gui::MOUSE_MASK_MIDDLE;

	// displaying information on the currently released mouse buttons
	Console::onscreenMessageLine(
		"getEventReleased(mouse_buttons: %s %s %s)",
		left ? "left" : "",
		right ? "right" : "",
		middle ? "middle" : ""
	);
});

```


<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Released
void released_event_handler(const Ptr<Widget> & widget,  int mouse_buttons)
{
	Log::message("\Обработка события Released\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections released_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventReleased().connect(released_event_connections, released_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventReleased().connect(released_event_connections, [](const Ptr<Widget> & widget,  int mouse_buttons) {
		Log::message("\Обработка события Released (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
released_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection released_event_connection;

// подписываемся на событие Released с функцией-обработчиком, сохраняя соединение
publisher->getEventReleased().connect(released_event_connection, released_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
released_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
released_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Released через соединение
released_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Released, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget,  int mouse_buttons)
	{
		Log::message("\Обработка события Released\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventReleased().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId released_handler_id;

// подписываемся на событие Released с лямбда-обработчиком, сохраняя идентификатор соединения
released_handler_id = publisher->getEventReleased().connect(e_connections, [](const Ptr<Widget> & widget,  int mouse_buttons) {
		Log::message("\Обработка события Released (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventReleased().disconnect(released_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Released при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventReleased().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventReleased().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &, int> getEventPressed () const

Событие, срабатывающее при нажатии кнопки мыши или клавиши **ENTER** (**RETURN**), когда курсор мыши находится где-либо на виджете. Поддерживается следующими виджетами:
- [*WidgetButton*](../../../api/library/gui/class.widgetbutton_cpp.md)
- [*WidgetCanvas*](../../../api/library/gui/class.widgetcanvas_cpp.md)
- [*WidgetEditLine*](../../../api/library/gui/class.widgeteditline_cpp.md)
- [*WidgetSlider*](../../../api/library/gui/class.widgetslider_cpp.md)
- [*WidgetIcon*](../../../api/library/gui/class.widgeticon_cpp.md)
- [*WidgetLabel*](../../../api/library/gui/class.widgetlabel_cpp.md)
- [*WidgetListBox*](../../../api/library/gui/class.widgetlistbox_cpp.md)
- [*WidgetSpinBox*](../../../api/library/gui/class.widgetspinbox_cpp.md)
- [*WidgetSprite*](../../../api/library/gui/class.widgetsprite_cpp.md)
- [*WidgetWindow*](../../../api/library/gui/class.widgetwindow_cpp.md)

 Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**, int **mouse_buttons**)*
- The `mouse_buttons` argument is a mask representing a combination of the following flags: *[Gui::MOUSE_MASK_LEFT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_LEFT) | [Gui::MOUSE_MASK_MIDDLE](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_MIDDLE) | [Gui::MOUSE_MASK_RIGHT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_RIGHT)*.


**Usage Example:**


```cpp
// auxiliary variable simplifying subscriptions management
EventConnections econn;

// ...

// creating a button widget
auto widget_button = WidgetButton::create(WindowManager::getMainWindow()->getGui(), "button");
WindowManager::getMainWindow()->getGui()->addChild(widget_button, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

// enabling Console onscreen overlay
Console::setOnscreen(true);

// subscribing to the Pressed event with a lambda-handler
widget_button->getEventPressed().connect(econn, [](WidgetPtr const& widget, int mouse_buttons) {
	int left = mouse_buttons & Gui::MOUSE_MASK_LEFT;
	int right = mouse_buttons & Gui::MOUSE_MASK_RIGHT;
	int middle = mouse_buttons & Gui::MOUSE_MASK_MIDDLE;

	// displaying information on the currently pressed mouse buttons
	Console::onscreenMessageLine(
		"getEventPressed(mouse_buttons: %s %s %s)",
		left ? "left" : "",
		right ? "right" : "",
		middle ? "middle" : ""
	);
});

```


<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Pressed
void pressed_event_handler(const Ptr<Widget> & widget,  int mouse_buttons)
{
	Log::message("\Обработка события Pressed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections pressed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventPressed().connect(pressed_event_connections, pressed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventPressed().connect(pressed_event_connections, [](const Ptr<Widget> & widget,  int mouse_buttons) {
		Log::message("\Обработка события Pressed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
pressed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection pressed_event_connection;

// подписываемся на событие Pressed с функцией-обработчиком, сохраняя соединение
publisher->getEventPressed().connect(pressed_event_connection, pressed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
pressed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
pressed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Pressed через соединение
pressed_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Pressed, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget,  int mouse_buttons)
	{
		Log::message("\Обработка события Pressed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventPressed().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId pressed_handler_id;

// подписываемся на событие Pressed с лямбда-обработчиком, сохраняя идентификатор соединения
pressed_handler_id = publisher->getEventPressed().connect(e_connections, [](const Ptr<Widget> & widget,  int mouse_buttons) {
		Log::message("\Обработка события Pressed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventPressed().disconnect(pressed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Pressed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventPressed().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventPressed().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventDoubleClicked () const

Событие, срабатывающее при двойном клике мыши где-либо на виджете. Поддерживается следующими виджетами:
- [*WidgetButton*](../../../api/library/gui/class.widgetbutton_cpp.md)
- [*WidgetCheckBox*](../../../api/library/gui/class.widgetcheckbox_cpp.md)
- [*WidgetComboBox*](../../../api/library/gui/class.widgetcombobox_cpp.md)
- [*WidgetEditLine*](../../../api/library/gui/class.widgeteditline_cpp.md)
- [*WidgetEditText*](../../../api/library/gui/class.widgetedittext_cpp.md)
- [*WidgetHPaned*](../../../api/library/gui/class.widgethpaned_cpp.md)
- [*WidgetIcon*](../../../api/library/gui/class.widgeticon_cpp.md)
- [*WidgetLabel*](../../../api/library/gui/class.widgetlabel_cpp.md)
- [*WidgetListBox*](../../../api/library/gui/class.widgetlistbox_cpp.md)
- [*WidgetManipulatorRotator*](../../../api/library/gui/class.widgetmanipulatorrotator_cpp.md)
- [*WidgetManipulatorScaler*](../../../api/library/gui/class.widgetmanipulatorscaler_cpp.md)
- [*WidgetManipulatorTranslator*](../../../api/library/gui/class.widgetmanipulatortranslator_cpp.md)
- [*WidgetScroll*](../../../api/library/gui/class.widgetscroll_cpp.md)
- [*WidgetSpinBox*](../../../api/library/gui/class.widgetspinbox_cpp.md)
- [*WidgetTreeBox*](../../../api/library/gui/class.widgettreebox_cpp.md)
- [*WidgetVPaned*](../../../api/library/gui/class.widgetvpaned_cpp.md)
- [*WidgetWindow*](../../../api/library/gui/class.widgetwindow_cpp.md)

 Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события DoubleClicked
void doubleclicked_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события DoubleClicked\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections doubleclicked_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventDoubleClicked().connect(doubleclicked_event_connections, doubleclicked_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventDoubleClicked().connect(doubleclicked_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события DoubleClicked (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
doubleclicked_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection doubleclicked_event_connection;

// подписываемся на событие DoubleClicked с функцией-обработчиком, сохраняя соединение
publisher->getEventDoubleClicked().connect(doubleclicked_event_connection, doubleclicked_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
doubleclicked_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
doubleclicked_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие DoubleClicked через соединение
doubleclicked_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события DoubleClicked, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события DoubleClicked\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventDoubleClicked().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId doubleclicked_handler_id;

// подписываемся на событие DoubleClicked с лямбда-обработчиком, сохраняя идентификатор соединения
doubleclicked_handler_id = publisher->getEventDoubleClicked().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события DoubleClicked (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventDoubleClicked().disconnect(doubleclicked_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий DoubleClicked при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventDoubleClicked().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventDoubleClicked().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &, int> getEventClicked () const

Событие, срабатывающее при клике мыши где-либо на виджете. Поддерживается следующими виджетами:
- [*WidgetButton*](../../../api/library/gui/class.widgetbutton_cpp.md)
- [*WidgetCheckBox*](../../../api/library/gui/class.widgetcheckbox_cpp.md)
- [*WidgetComboBox*](../../../api/library/gui/class.widgetcombobox_cpp.md)
- [*WidgetDialog*](../../../api/library/gui/class.widgetdialog_cpp.md)
- [*WidgetDialogFile*](../../../api/library/gui/class.widgetdialogfile_cpp.md)
- [*WidgetEditLine*](../../../api/library/gui/class.widgeteditline_cpp.md)
- [*WidgetEditText*](../../../api/library/gui/class.widgetedittext_cpp.md)
- [*WidgetHPaned*](../../../api/library/gui/class.widgethpaned_cpp.md)
- [*WidgetScroll*](../../../api/library/gui/class.widgetscroll_cpp.md)
- [*WidgetSlider*](../../../api/library/gui/class.widgetslider_cpp.md)
- [*WidgetIcon*](../../../api/library/gui/class.widgeticon_cpp.md)
- [*WidgetLabel*](../../../api/library/gui/class.widgetlabel_cpp.md)
- [*WidgetListBox*](../../../api/library/gui/class.widgetlistbox_cpp.md)
- [*WidgetManipulatorRotator*](../../../api/library/gui/class.widgetmanipulatorrotator_cpp.md)
- [*WidgetManipulatorScaler*](../../../api/library/gui/class.widgetmanipulatorscaler_cpp.md)
- [*WidgetManipulatorTranslator*](../../../api/library/gui/class.widgetmanipulatortranslator_cpp.md)
- [*WidgetMenuBox*](../../../api/library/gui/class.widgetmenubox_cpp.md)
- [*WidgetSpinBox*](../../../api/library/gui/class.widgetspinbox_cpp.md)
- [*WidgetSprite*](../../../api/library/gui/class.widgetsprite_cpp.md)
- [*WidgetTreeBox*](../../../api/library/gui/class.widgettreebox_cpp.md)
- [*WidgetVPaned*](../../../api/library/gui/class.widgetvpaned_cpp.md)

 Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**, int **mouse_buttons**)*
- The `mouse_buttons` argument is a mask representing a combination of the following flags: *[Gui::MOUSE_MASK_LEFT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_LEFT) | [Gui::MOUSE_MASK_MIDDLE](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_MIDDLE) | [Gui::MOUSE_MASK_RIGHT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_RIGHT)*.


**Usage Example:**


```cpp
// auxiliary variable simplifying subscriptions management
EventConnections econn;

// ...

// creating a button widget
auto widget_button = WidgetButton::create(WindowManager::getMainWindow()->getGui(), "button");
WindowManager::getMainWindow()->getGui()->addChild(widget_button, Gui::ALIGN_OVERLAP | Gui::ALIGN_FIXED);

// enabling Console onscreen overlay
Console::setOnscreen(true);

// subscribing to the Clicked event with a lambda-handler
widget_button->getEventClicked().connect(econn, [](WidgetPtr const& widget, int mouse_buttons) {
	int left = mouse_buttons & Gui::MOUSE_MASK_LEFT;
	int right = mouse_buttons & Gui::MOUSE_MASK_RIGHT;
	int middle = mouse_buttons & Gui::MOUSE_MASK_MIDDLE;

	// displaying information on the currently clicked mouse buttons
	Console::onscreenMessageLine(
		"getEventClicked(mouse_buttons: %s %s %s)",
		left ? "left" : "",
		right ? "right" : "",
		middle ? "middle" : ""
	);
});

```


<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Clicked
void clicked_event_handler(const Ptr<Widget> & widget,  int mouse_buttons)
{
	Log::message("\Обработка события Clicked\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections clicked_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventClicked().connect(clicked_event_connections, clicked_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventClicked().connect(clicked_event_connections, [](const Ptr<Widget> & widget,  int mouse_buttons) {
		Log::message("\Обработка события Clicked (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
clicked_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection clicked_event_connection;

// подписываемся на событие Clicked с функцией-обработчиком, сохраняя соединение
publisher->getEventClicked().connect(clicked_event_connection, clicked_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
clicked_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
clicked_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Clicked через соединение
clicked_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Clicked, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget,  int mouse_buttons)
	{
		Log::message("\Обработка события Clicked\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventClicked().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId clicked_handler_id;

// подписываемся на событие Clicked с лямбда-обработчиком, сохраняя идентификатор соединения
clicked_handler_id = publisher->getEventClicked().connect(e_connections, [](const Ptr<Widget> & widget,  int mouse_buttons) {
		Log::message("\Обработка события Clicked (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventClicked().disconnect(clicked_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Clicked при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventClicked().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventClicked().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventChanged () const

Событие, срабатывающее при изменении состояния виджета. Поддерживается следующими виджетами:
- [*WidgetButton*](../../../api/library/gui/class.widgetbutton_cpp.md)
- [*WidgetCheckBox*](../../../api/library/gui/class.widgetcheckbox_cpp.md)
- [*WidgetComboBox*](../../../api/library/gui/class.widgetcombobox_cpp.md)
- [*WidgetDialogColor*](../../../api/library/gui/class.widgetdialogcolor_cpp.md)
- [*WidgetEditLine*](../../../api/library/gui/class.widgeteditline_cpp.md)
- [*WidgetEditText*](../../../api/library/gui/class.widgetedittext_cpp.md)
- [*WidgetHPaned*](../../../api/library/gui/class.widgethpaned_cpp.md)
- [*WidgetScroll*](../../../api/library/gui/class.widgetscroll_cpp.md)
- [*WidgetScrollBox*](../../../api/library/gui/class.widgetscrollbox_cpp.md)
- [*WidgetSlider*](../../../api/library/gui/class.widgetslider_cpp.md)
- [*WidgetIcon*](../../../api/library/gui/class.widgeticon_cpp.md)
- [*WidgetLabel*](../../../api/library/gui/class.widgetlabel_cpp.md)
- [*WidgetListBox*](../../../api/library/gui/class.widgetlistbox_cpp.md)
- [*WidgetManipulator*](../../../api/library/gui/class.widgetmanipulator_cpp.md)
- [*WidgetManipulatorRotator*](../../../api/library/gui/class.widgetmanipulatorrotator_cpp.md)
- [*WidgetManipulatorScaler*](../../../api/library/gui/class.widgetmanipulatorscaler_cpp.md)
- [*WidgetManipulatorTranslator*](../../../api/library/gui/class.widgetmanipulatortranslator_cpp.md)
- [*WidgetSpinBox*](../../../api/library/gui/class.widgetspinbox_cpp.md)
- [*WidgetSpinBoxDouble*](../../../api/library/gui/class.widgetspinboxdouble_cpp.md)
- [*WidgetTabBox*](../../../api/library/gui/class.widgettabbox_cpp.md)
- [*WidgetTreeBox*](../../../api/library/gui/class.widgettreebox_cpp.md)
- [*WidgetVPaned*](../../../api/library/gui/class.widgetvpaned_cpp.md)

 Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Changed
void changed_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события Changed\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections changed_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventChanged().connect(changed_event_connections, changed_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventChanged().connect(changed_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Changed (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
changed_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection changed_event_connection;

// подписываемся на событие Changed с функцией-обработчиком, сохраняя соединение
publisher->getEventChanged().connect(changed_event_connection, changed_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
changed_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
changed_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Changed через соединение
changed_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Changed, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события Changed\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventChanged().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId changed_handler_id;

// подписываемся на событие Changed с лямбда-обработчиком, сохраняя идентификатор соединения
changed_handler_id = publisher->getEventChanged().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Changed (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventChanged().disconnect(changed_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Changed при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventChanged().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventChanged().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventFocusOut () const

Событие, срабатывающее при потере виджетом фокуса. Поддерживается всеми виджетами. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FocusOut
void focusout_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события FocusOut\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections focusout_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventFocusOut().connect(focusout_event_connections, focusout_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventFocusOut().connect(focusout_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события FocusOut (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
focusout_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection focusout_event_connection;

// подписываемся на событие FocusOut с функцией-обработчиком, сохраняя соединение
publisher->getEventFocusOut().connect(focusout_event_connection, focusout_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
focusout_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
focusout_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FocusOut через соединение
focusout_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события FocusOut, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события FocusOut\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventFocusOut().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId focusout_handler_id;

// подписываемся на событие FocusOut с лямбда-обработчиком, сохраняя идентификатор соединения
focusout_handler_id = publisher->getEventFocusOut().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события FocusOut (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventFocusOut().disconnect(focusout_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FocusOut при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventFocusOut().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventFocusOut().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventFocusIn () const

Событие, срабатывающее при получении виджетом фокуса. Поддерживается всеми виджетами. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события FocusIn
void focusin_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события FocusIn\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections focusin_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventFocusIn().connect(focusin_event_connections, focusin_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventFocusIn().connect(focusin_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события FocusIn (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
focusin_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection focusin_event_connection;

// подписываемся на событие FocusIn с функцией-обработчиком, сохраняя соединение
publisher->getEventFocusIn().connect(focusin_event_connection, focusin_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
focusin_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
focusin_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие FocusIn через соединение
focusin_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события FocusIn, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события FocusIn\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventFocusIn().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId focusin_handler_id;

// подписываемся на событие FocusIn с лямбда-обработчиком, сохраняя идентификатор соединения
focusin_handler_id = publisher->getEventFocusIn().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события FocusIn (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventFocusIn().disconnect(focusin_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий FocusIn при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventFocusIn().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventFocusIn().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventHide () const

Событие, срабатывающее при удалении виджета с помощью [*Gui::removeChild()*](../../../api/library/gui/class.gui_cpp.md#removeChild_Widget_void). Поддерживается всеми виджетами. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Hide
void hide_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события Hide\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections hide_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventHide().connect(hide_event_connections, hide_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventHide().connect(hide_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Hide (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
hide_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection hide_event_connection;

// подписываемся на событие Hide с функцией-обработчиком, сохраняя соединение
publisher->getEventHide().connect(hide_event_connection, hide_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
hide_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
hide_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Hide через соединение
hide_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Hide, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события Hide\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventHide().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId hide_handler_id;

// подписываемся на событие Hide с лямбда-обработчиком, сохраняя идентификатор соединения
hide_handler_id = publisher->getEventHide().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Hide (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventHide().disconnect(hide_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Hide при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventHide().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventHide().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## Event<const Ptr < Widget > &> getEventShow () const

Событие, срабатывающее при показе виджета. Поддерживается всеми виджетами. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<Widget> & **widget**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события Show
void show_event_handler(const Ptr<Widget> & widget)
{
	Log::message("\Обработка события Show\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections show_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
publisher->getEventShow().connect(show_event_connections, show_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
publisher->getEventShow().connect(show_event_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Show (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
show_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection show_event_connection;

// подписываемся на событие Show с функцией-обработчиком, сохраняя соединение
publisher->getEventShow().connect(show_event_connection, show_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
show_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
show_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие Show через соединение
show_event_connection.disconnect();

//////////////////////////////////////////////////////////////////////////////
//  3. Можно добавить экземпляр EventConnection/EventConnections как член класса,
//  обрабатывающего событие. В этом случае все связанные подписки будут
//  автоматически удалены при вызове деструктора класса
//////////////////////////////////////////////////////////////////////////////

// Класс, обрабатывающий событие
class SomeClass
{
public:
	// экземпляр класса EventConnections как член класса
	EventConnections e_connections;

	// Обработчик события Show, реализованный как член класса
	void event_handler(const Ptr<Widget> & widget)
	{
		Log::message("\Обработка события Show\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
publisher->getEventShow().connect(sc->e_connections, sc, &SomeClass::event_handler);

// ...

// экземпляр класса-обработчика удаляется, а все его подписки автоматически отменяются
delete sc;

//////////////////////////////////////////////////////////////////////////////
//   4. Подписка на событие с сохранением идентификатора соединения
//   и последующей отпиской по этому идентификатору
//////////////////////////////////////////////////////////////////////////////
// экземпляр класса EventConnections для управления соединениями событий
EventConnections e_connections;

// определяем идентификатор соединения, который будет использован для отписки позже
EventConnectionId show_handler_id;

// подписываемся на событие Show с лямбда-обработчиком, сохраняя идентификатор соединения
show_handler_id = publisher->getEventShow().connect(e_connections, [](const Ptr<Widget> & widget) {
		Log::message("\Обработка события Show (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
publisher->getEventShow().disconnect(show_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий Show при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
publisher->getEventShow().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
publisher->getEventShow().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## Ptr < Widget > getChild ( int num ) const

Возвращает дочерний виджет с указанным номером.
### Аргументы

- *int* **num** - Номер дочернего виджета.

### Возвращаемое значение

Указатель на дочерний виджет.
## int isChild ( const Ptr < Widget > & w ) const

Проверяет, является ли указанный виджет дочерним для текущего.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **w** - Проверяемый виджет.

### Возвращаемое значение

**1**, если рассматриваемый виджет является дочерним; иначе **0**.
## void setFocus ( )

Устанавливает фокус на виджет.
## int isFocused ( ) const

Возвращает значение, указывающее, находится ли виджет в данный момент в фокусе.
### Возвращаемое значение

1, если виджет в фокусе; иначе 0.
## void setFont ( const char * name )

Устанавливает TrueType-шрифт (*.ttf), который будет использоваться для отрисовки текста на виджете, по пути к файлу.
### Аргументы

- *const char ** **name** - Путь к файлу шрифта (`*.ttf`), хранящемуся в папке `data` вашего проекта.

## bool getIntersection ( int local_pos_x , int local_pos_y ) const

Проверяет пересечение указанной точки с границами виджета.
### Аргументы

- *int* **local_pos_x** - Локальная координата X.
- *int* **local_pos_y** - Локальная координата Y.

### Возвращаемое значение

true, если указанная координата находится внутри виджета; иначе false.
## Ptr < Widget > getHierarchyIntersection ( int screen_pos_x , int screen_pos_y )

Проверяет пересечение с виджетом, принадлежащим иерархии текущего виджета.
### Аргументы

- *int* **screen_pos_x** - Координата X экранной позиции.
- *int* **screen_pos_y** - Координата Y экранной позиции.

### Возвращаемое значение

Виджет, с которым найдено пересечение.
## int getKeyActivity ( unsigned int key ) const

Проверяет, имеет ли уже указанная клавиша особое назначение для виджета.
### Аргументы

- *unsigned int* **key** - ASCII-код клавиши: одно из значений *[Input::KEY_*](../../../api/library/controls/class.input_cpp.md#KEY_UNKNOWN)*.

### Возвращаемое значение

1, если клавишу нельзя использовать; иначе 0.
## void setPermanentFocus ( )

Устанавливает постоянный фокус на виджет (это означает, что виджет всегда находится в фокусе).
## void setPosition ( int x , int y )

Устанавливает позицию виджета относительно его родителя в [logical units](../../../principles/dpi/index.md).
### Аргументы

- *int* **x** - Координата X верхнего левого угла виджета в [logical units](../../../principles/dpi/index.md).
- *int* **y** - Координата Y верхнего левого угла виджета в [logical units](../../../principles/dpi/index.md).

## void setToolTip ( const char * str , int reset = 0 )

Устанавливает подсказку для виджета.
### Аргументы

- *const char ** **str** - Текст подсказки.
- *int* **reset** - **1**, чтобы пересчитать позицию подсказки, если курсор мыши был перемещён; иначе — **0** (по умолчанию).

## const char * getToolTip ( ) const

Возвращает текст подсказки виджета.
### Возвращаемое значение

Текст подсказки.
## void addAttach ( const Ptr < Widget > & w , const char * format = 0 , int multiplier = 1 , int flags = 0 )

Присоединяет указанный виджет к текущему. При применении к чекбоксам преобразует их в группу радиокнопок. Горизонтальный/вертикальный слайдер можно присоединить к метке или текстовому полю. Текстовое поле можно присоединить к любому из слайдеров.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **w** - Присоединяемый виджет.
- *const char ** **format** - Строка формата или значения, вводимые в присоединённый виджет. Если не указано, подразумевается "%d". Это опциональный параметр.
- *int* **multiplier** - Значение множителя, используемое для масштабирования значений, предоставляемых присоединённым виджетом. Это опциональный параметр.
- *int* **flags** - Флаги присоединения: одно из значений перечисления [Gui::](../../../api/library/gui/class.gui_cpp.md) с префиксом ATTACH_*. Это опциональный параметр.

## void addChild ( const Ptr < Widget > & w , int flags = 0 )

Добавляет дочерний элемент к виджету.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **w** - Дочерний виджет.
- *int* **flags** - Флаги виджета: одно из значений перечисления [Gui::](../../../api/library/gui/class.gui_cpp.md) с префиксом ALIGN_*. Это опциональный параметр.

## void arrange ( )

Перестраивает виджет и его дочерние элементы, чтобы аккуратно их разместить. Эта функция принудительно пересчитывает размер виджета и позволяет получить обновлённые данные компоновки GUI в текущем кадре. Если эта функция не вызывается, изменения виджета, сделанные в текущем *update()*, будут доступны только в следующем кадре (т.е. с задержкой в один кадр), так как GUI вычисляется и отрисовывается после выполнения функции скрипта *update()*.
## void raise ( const Ptr < Widget > & w )

Выносит указанный виджет наверх.
> **Notice:** Работает только для виджетов, добавленных в GUI через функцию [*Gui::addChild()*](../../../api/library/gui/class.gui_cpp.md#addChild_Widget_int_void) с указанным флагом [Gui::ALIGN_OVERLAP](../../../api/library/gui/class.gui_cpp.md#ALIGN_OVERLAP) (не должен быть [Gui::ALIGN_FIXED](../../../api/library/gui/class.gui_cpp.md#ALIGN_FIXED)).


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **w** - Виджет, который нужно вынести наверх.

## void removeAttach ( const Ptr < Widget > & w )

Отсоединяет указанный виджет от текущего.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **w** - Отсоединяемый виджет.

## void removeChild ( const Ptr < Widget > & w )

Удаляет дочерний виджет из списка дочерних элементов виджета.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **w** - Умный указатель на дочерний виджет.

## void removeFocus ( )

Снимает фокус с виджета.
## void replaceChild ( const Ptr < Widget > & w , const Ptr < Widget > & old_w , int flags = 0 )

Заменяет один дочерний виджет другим.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **w** - Умный указатель на новый дочерний виджет.
- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **old_w** - Заменяемый виджет.
- *int* **flags** - Флаги виджета: одно из значений перечисления [Gui::](../../../api/library/gui/class.gui_cpp.md) с префиксом ALIGN_*. Это опциональный параметр.

## Widget::LIFETIME getLifetimeSelf ( ) const

Возвращает тип управления жизненным циклом, установленный для виджета.
> **Notice:** Жизненный цикл каждого виджета в иерархии определяется его корнем. Установка типа управления жизненным циклом для дочернего виджета, отличающегося от установленного для корня, не имеет эффекта.


## int toRenderSize ( int unit_size )

Преобразует значение в единицах в значение в пикселях.
### Аргументы

- *int* **unit_size** - Размер в единицах.

### Возвращаемое значение

Размер в пикселях.
## int toUnitSize ( int render_size )

Преобразует значение в пикселях в значение в единицах.
### Аргументы

- *int* **render_size** - Размер в пикселях.

### Возвращаемое значение

Размер в единицах.
## Math:: ivec2 toRenderSize ( const Math:: ivec2 & unit_size )

Преобразует значение в единицах в значение в пикселях.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **unit_size** - Размер в единицах.

### Возвращаемое значение

Размер в пикселях.
## Math:: ivec2 toUnitSize ( const Math:: ivec2 & render_size )

Преобразует значение в пикселях в значение в единицах.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **render_size** - Размер в пикселях.

### Возвращаемое значение

Размер в единицах.
## Math:: ivec2 getTextRenderSize ( const char * OUT_text ) const

Возвращает размер (в пикселях) указанной текстовой строки при отрисовке на экране с учётом всех настроек вывода текста, таких как dpi, размер и стиль шрифта.
### Аргументы

- *const char ** **OUT_text** - Текстовая строка. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

Размер текста в пикселях.
## void runEventShow ( )

Эмулирует событие *[Show](#getEventShow_Event)*.
## void runEventHide ( )

Эмулирует событие *[Hide](#getEventHide_Event)*.
## void runEventFocusIn ( )

Эмулирует событие *[FocusIn](#getEventFocusIn_Event)*.
## void runEventFocusOut ( )

Эмулирует событие *[FocusOut](#getEventFocusOut_Event)*.
## void runEventChanged ( )

Эмулирует событие *[Changed](#getEventChanged_Event)*.
## void runEventClicked ( int mouse_buttons )

Эмулирует событие *[Clicked](#getEventClicked_Event)*.
### Аргументы

- *int* **mouse_buttons** - Кнопка мыши — маска, представляющая комбинацию следующих флагов: *[Gui.MOUSE_MASK_LEFT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_LEFT) | [Gui.MOUSE_MASK_MIDDLE](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_MIDDLE) | [Gui.MOUSE_MASK_RIGHT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_RIGHT)*.

## void runEventDoubleClicked ( )

Эмулирует событие *[DoubleClicked](#getEventDoubleClicked_Event)*.
## void runEventPressed ( int mouse_buttons )

Эмулирует событие *[Pressed](#getEventPressed_Event)*.
### Аргументы

- *int* **mouse_buttons** - Кнопка мыши — маска, представляющая комбинацию следующих флагов: *[Gui.MOUSE_MASK_LEFT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_LEFT) | [Gui.MOUSE_MASK_MIDDLE](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_MIDDLE) | [Gui.MOUSE_MASK_RIGHT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_RIGHT)*.

## void runEventReleased ( int mouse_buttons )

Эмулирует событие *[Released](#getEventReleased_Event)*.
### Аргументы

- *int* **mouse_buttons** - Кнопка мыши — маска, представляющая комбинацию следующих флагов: *[Gui.MOUSE_MASK_LEFT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_LEFT) | [Gui.MOUSE_MASK_MIDDLE](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_MIDDLE) | [Gui.MOUSE_MASK_RIGHT](../../../api/library/gui/class.gui_cpp.md#MOUSE_MASK_RIGHT)*.

## void runEventKeyPressed ( int key )

Эмулирует событие *[KeyPressed](#getEventKeyPressed_Event)*.
### Аргументы

- *int* **key** - Код сканирования клавиши.

## void runEventTextPressed ( unsigned int code )

Эмулирует событие *[TextPressed](#getEventTextPressed_Event)*.
### Аргументы

- *unsigned int* **code** - Виртуальная клавиша.

## void runEventEnter ( )

Эмулирует событие *[Enter](#getEventEnter_Event)*.
## void runEventLeave ( )

Эмулирует событие *[Leave](#getEventLeave_Event)*.
## void runEventDragMove ( const Ptr < Widget > & pointer )

Эмулирует событие *[DragMove](#getEventDragMove_Event)*.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **pointer** - Подложенный виджет.

## void runEventDragDrop ( const Ptr < Widget > & pointer )

Эмулирует событие *[DragDrop](#getEventDragDrop_Event)*.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Widget](../../../api/library/gui/class.widget_cpp.md)> &* **pointer** - Целевой виджет.

## Math:: ivec2 getTextUnitSize ( const char * text ) const

Возвращает размеры текста (ширину и высоту в логических единицах). Эта функция помогает оценить, насколько хорошо текст поместится в виджет перед отрисовкой.
### Аргументы

- *const char ** **text** - Текстовая строка.

### Возвращаемое значение

Размер текста в логических единицах (ширина, высота).
