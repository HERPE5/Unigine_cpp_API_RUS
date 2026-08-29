# Unigine::Displays Class (CPP)

**Header:** #include <UnigineDisplays.h>

> **Notice:** This class is a singleton.


Класс *Displays* позволяет получать информацию о подключённых дисплеях, такую как количество экранных дисплеев и индекс главного из них, их позицию и размер в пикселях. Он предоставляет доступ к имени и текущему dpi. Этот класс также позволяет получать общее количество доступных режимов для дисплеев и получать разрешение и частоту обновления по индексу режима.


<details>
<summary>AppSystemLogic.h | Close</summary>

`AppSystemLogic.h`


```cpp
#include <UnigineLogic.h>

class AppSystemLogic : public Unigine::SystemLogic
{
public:
	AppSystemLogic();
	~AppSystemLogic() override;

	int init() override;

	int update() override;
	int postUpdate() override;

	int shutdown() override;

	int showDisplayInfo(int current_display);

};


```

</details>


<details>
<summary>AppSystemLogic.cpp | Close</summary>

`AppSystemLogic.cpp`


```cpp
#include "AppSystemLogic.h"
#include <UnigineDisplays.h>

using namespace Unigine;
using namespace Math;

EngineWindowViewportPtr window_0;
int current_display;

int AppSystemLogic::init()
{

	// получаем главное окно
	window_0 = WindowManager::getMainWindow();
	// задаём его позицию и размер
	window_0->setPosition(Math::ivec2(60, 60));
	window_0->setSize(Math::ivec2(960, 600));
	// отрисовываем окно
	window_0->show();

	// получаем текущий дисплей
	current_display = Displays::getCurrent();
	// показываем информацию о текущем дисплее в главном окне
	showDisplayInfo(current_display);

	return 1;
}

int AppSystemLogic::update()
{
	// проверяем, был ли курсор перемещён на другой дисплей
	if (current_display != Displays::getCurrent())
	{
		// удаляем информацию о предыдущем дисплее
		for (int i = 0; i < window_0->getNumChildren(); i++) window_0->removeChild(window_0->getChild(i));
		// показываем информацию о дисплее, над которым сейчас находится курсор
		showDisplayInfo(current_display);
	}

	return 1;
}

int AppSystemLogic::showDisplayInfo(int i)
{
	ivec2 resolution;

	if (i == Displays::getMain()) window_0->addChild(WidgetLabel::create(window_0->getSelfGui(), String::format("Main display")));
	// имя дисплея
	window_0->addChild(WidgetLabel::create(window_0->getSelfGui(), String::format("The display name: %s \n", Displays::getName(i))));
	// разрешение дисплея
	resolution = Displays::getResolution(i);
	window_0->addChild(WidgetLabel::create(window_0->getSelfGui(), String::format("The display resolution: %d %d", resolution.x, resolution.y)));
	// dpi дисплея
	window_0->addChild(WidgetLabel::create(window_0->getSelfGui(), String::format("The display DPI: %d \n", Displays::getDPI(i))));
	// количество режимов дисплея
	window_0->addChild(WidgetLabel::create(window_0->getSelfGui(), String::format("The num display modes: %d \n", Displays::getNumModes(i))));
	// текущий режим дисплея
	window_0->addChild(WidgetLabel::create(window_0->getSelfGui(), String::format("The current display mode: %d", Displays::getCurrentMode(i))));

	return 1;
}


```

</details>


## Displays Class

### Перечисления

## ORIENTATION

| Name | Description |
|---|---|
| **ORIENTATION_UNKNOWN** = -1 | Другой неопределённый тип ориентации. |
| **ORIENTATION_LANDSCAPE** = 0 | Альбомная ориентация. |
| **ORIENTATION_LANDSCAPE_FLIPPED** = 1 | Альбомная ориентация, перевёрнутая вверх ногами. |
| **ORIENTATION_PORTRAIT** = 2 | Книжная ориентация. |
| **ORIENTATION_PORTRAIT_FLIPPED** = 3 | Книжная ориентация, перевёрнутая вверх ногами. |

### Методы класса

---

## int getMain ( ) const

Возвращает индекс главного системного дисплея.
### Возвращаемое значение

Индекс главного системного дисплея.
## int getDefaultSystemDPI ( ) const

Возвращает системное значение точек/пикселей на дюйм по умолчанию.
### Возвращаемое значение

Значение точек/пикселей на дюйм.
## int getNum ( ) const

Возвращает количество доступных видеодисплеев.
### Возвращаемое значение

Количество доступных видеодисплеев.
## Math:: ivec2 getPosition ( int display_index ) const

Возвращает позицию дисплея по его индексу.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Позиция дисплея.
## Math:: ivec2 getResolution ( int display_index ) const

Возвращает разрешение дисплея по его индексу.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Разрешение дисплея.
## int getDPI ( int display_index ) const

Возвращает DPI дисплея по его индексу.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

DPI дисплея.
## int getNumModes ( int display_index ) const

Возвращает общее количество доступных режимов дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Количество доступных режимов дисплея.
## Math:: ivec2 getModeResolution ( int display_index , int mode_index ) const

Возвращает разрешение выбранного режима для выбранного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.
- *int* **mode_index** - Индекс режима дисплея в диапазоне от 0 до [total number of available display modes](#getNumModes_int_int).

### Возвращаемое значение

Разрешение.
## int getModeRefreshRate ( int display_index , int mode_index ) const

Возвращает частоту обновления указанного режима дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.
- *int* **mode_index** - Индекс режима дисплея в диапазоне от 0 до [total number of available display modes](#getNumModes_int_int).

### Возвращаемое значение

Частота обновления указанного режима дисплея.
## const char * getName ( int display_index ) const

Возвращает системное имя дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Системное имя дисплея.
## int getCurrent ( ) const

Возвращает индекс дисплея, над которым сейчас находится курсор.
### Возвращаемое значение

Индекс дисплея, над которым сейчас находится курсор.
## int getRefreshRate ( int display_index ) const

Возвращает текущую частоту обновления указанного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Частота обновления указанного дисплея.
## int getCurrentMode ( int display_index ) const

Возвращает текущий режим дисплея для указанного дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Индекс режима дисплея в диапазоне от 0 до [total number of available display modes](#getNumModes_int_int).
## int getDesktopMode ( int display_index ) const

Возвращает информацию о режиме дисплея рабочего стола. Есть разница между этой функцией и [getCurrentMode()](#getCurrentMode_int_int), когда приложение работает в полноэкранном режиме и изменило разрешение. В таком случае эта функция вернёт предыдущий нативный режим дисплея, а не текущий режим дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Индекс режима дисплея в диапазоне от 0 до [total number of available display modes](#getNumModes_int_int).
## Displays::ORIENTATION getOrientation ( int display_index ) const

Возвращает ориентацию дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Ориентация, одно из значений [ORIENTATION_*](#ORIENTATION_UNKNOWN).
## int getUniqueID ( int display_index ) const

Возвращает уникальный ID дисплея.
### Аргументы

- *int* **display_index** - Индекс дисплея.

### Возвращаемое значение

Уникальный ID дисплея.
## int findDisplay ( const char * name ) const

Возвращает индекс дисплея по его имени.
### Аргументы

- *const char ** **name** - Имя дисплея.

### Возвращаемое значение

Индекс дисплея.
## int findDisplay ( int unique_id ) const

Возвращает индекс дисплея по его уникальному ID.
### Аргументы

- *int* **unique_id** - Уникальный ID дисплея.

### Возвращаемое значение

Индекс дисплея, либо -1, если дисплей не найден.
## int findMode ( int display_index , const Math:: ivec2 & resolution ) const

Возвращает индекс режима дисплея по индексу дисплея и разрешению.
### Аргументы

- *int* **display_index** - Индекс дисплея.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение дисплея.

### Возвращаемое значение

Индекс режима дисплея в диапазоне от 0 до [total number of available display modes](#getNumModes_int_int), либо -1, если режим не найден.
## int findMode ( int display_index , const Math:: ivec2 & resolution , int refresh_rate ) const

Возвращает индекс режима дисплея по индексу дисплея, разрешению и частоте обновления.
### Аргументы

- *int* **display_index** - Индекс дисплея.
- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **resolution** - Разрешение дисплея.
- *int* **refresh_rate** - Частота обновления.

### Возвращаемое значение

Индекс режима дисплея в диапазоне от 0 до [total number of available display modes](#getNumModes_int_int), либо -1, если режим не найден.
## int getByPoint ( const Math:: ivec2 & point ) const

Возвращает индекс дисплея, расположенного в указанной точке. Например, можно передать координаты мыши как аргумент, чтобы получить индекс дисплея, над которым находится курсор.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md) &* **point** - Позиция точки в глобальных координатах.

### Возвращаемое значение

Индекс дисплея, расположенного в указанной точке.
