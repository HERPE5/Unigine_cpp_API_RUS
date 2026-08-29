# Unigine::WidgetSpriteVideo Class (CPP)

**Header:** #include <UnigineWidgets.h>

**Inherits from:** WidgetSprite


Этот класс используется для создания виртуального монитора, воспроизводящего видеофайл (в настоящее время поддерживаются только файлы *.OGV). Он может быть синхронизирован с воспроизведением ambient-звука или направленного источника звука.


В следующем примере показано, как воспроизвести видеофайл в системном GUI или на [GUI-объекте](../../../api/library/objects/class.objectgui_cpp.md) с помощью класса *WidgetSpriteVideo*.


[Create a C++ component](../../../principles/component_system/component_system_cpp/index.md#workflow) с именем `VideoSprite` и скопируйте приведённый ниже код в соответствующие файлы:


<details>
<summary>VideoSprite.h | Закрыть</summary>

```cpp
#pragma once
#include <UnigineComponentSystem.h>
class VideoSprite :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(VideoSprite, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	// путь к видеофайлу для воспроизведения (поддерживается только тип *.OGV)
	PROP_PARAM(File, file_name, "");

private:
	// виджеты sprite video
	Unigine::WidgetSpriteVideoPtr TVscreen;
	Unigine::WidgetSpriteVideoPtr MAINscreen;
	void init();

};


```

</details>


<details>
<summary>VideoSprite.cpp | Закрыть</summary>

```cpp
#include "VideoSprite.h"
#include <UnigineGui.h>
REGISTER_COMPONENT(VideoSprite);

using namespace Unigine;

void VideoSprite::init()
{
	// создание первого виджета sprite video, воспроизводящего видеофайл file_name в системном GUI
	MAINscreen = WidgetSpriteVideo::create(Gui::getCurrent(), file_name, 1);

	// установка размера и позиции второго виджета sprite video на экране
	MAINscreen->setPosition(100, 100);
	MAINscreen->setWidth(400);
	MAINscreen->setHeight(225);
	MAINscreen->arrange();

	// добавление виджета sprite video в системный GUI
	Gui::getCurrent()->addChild(MAINscreen, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	// установка режима зацикленного воспроизведения
	MAINscreen->setLoop(1);

	// запуск воспроизведения
	MAINscreen->play();

	// проверка, является ли узел, к которому назначен компонент, GUI Object
	if (node->getType() != Node::OBJECT_GUI)
	{
		Log::message("Node is not a GUI Object!\n");
		return;
	}
	ObjectGuiPtr GUIObject = checked_ptr_cast<ObjectGui>(node);

	// создание второго виджета sprite video, воспроизводящего видеофайл file_name на GUI-объекте
	TVscreen = WidgetSpriteVideo::create(GUIObject->getGui(), file_name, 1);

	// подгонка размера виджета под размер GUI-объекта
	TVscreen->setWidth(GUIObject->getScreenWidth());
	TVscreen->setHeight(GUIObject->getScreenHeight());

	// добавление виджета sprite video на GUI-объект
	GUIObject->getGui()->addChild(TVscreen, Gui::ALIGN_OVERLAP | Gui::ALIGN_BACKGROUND);

	// установка режима зацикленного воспроизведения
	TVscreen->setLoop(1);

	// запуск воспроизведения
	TVscreen->play();
}

```

</details>


### См. также



  -
  -
  -
  -


## WidgetSpriteVideo Class

### Методы класса

---

## static WidgetSpriteVideoPtr create ( const Ptr < Gui > & gui , const char * name = 0 , int mode = 1 )

Конструктор. Создаёт новый спрайт, воспроизводящий видео, и добавляет его в указанный GUI.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Gui](../../../api/library/gui/class.gui_cpp.md)> &* **gui** - [GUI](../../../api/library/gui/class.gui_cpp.md), которому будет принадлежать новый спрайт.
- *const char ** **name** - Путь к видеофайлу.
- *int* **mode** - Флаг YUV: **1**, если преобразование в RGB должно выполняться GPU, **0** - если CPU.

## static WidgetSpriteVideoPtr create ( const char * name = 0 , int mode = 1 )

Конструктор. Создаёт новый спрайт, воспроизводящий видео, и добавляет его в GUI движка.
### Аргументы

- *const char ** **name** - Путь к видеофайлу.
- *int* **mode** - Флаг YUV: **1**, если преобразование в RGB должно выполняться GPU, **0** - если CPU.

## void setAmbientSource ( const Ptr < AmbientSource > & source )

Синхронизирует воспроизведение видео с воспроизведением источника ambient-звука.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[AmbientSource](../../../api/library/sounds/class.ambientsource_cpp.md)> &* **source** - Источник ambient-звука, в соответствии с которым будет синхронизировано воспроизведение видео.

## Ptr < AmbientSource > getAmbientSource ( ) const

Возвращает источник ambient-звука, в соответствии с которым синхронизировано воспроизведение видео.
### Возвращаемое значение

Источник ambient-звука.
## void setLoop ( int loop )

Задаёт значение, указывающее, должно ли видео быть зациклено.
### Аргументы

- *int* **loop** - Положительное число зацикливает видео, **0** воспроизводит его только один раз.

## int getLoop ( ) const

Возвращает значение, указывающее, зациклено ли видео.
### Возвращаемое значение

Положительное число, если видео зациклено; иначе **0**.
## bool isPlaying ( ) const

Возвращает значение, указывающее, воспроизводится ли видео в данный момент.
### Возвращаемое значение

**1**, если видео воспроизводится; иначе **0**.
## void setSoundSource ( const Ptr < SoundSource > & source )

Синхронизирует воспроизведение видео с воспроизведением источника звука.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[SoundSource](../../../api/library/sounds/class.soundsource_cpp.md)> &* **source** - Источник звука, в соответствии с которым будет синхронизировано воспроизведение видео.

## Ptr < SoundSource > getSoundSource ( ) const

Возвращает источник звука, в соответствии с которым синхронизировано воспроизведение видео.
### Возвращаемое значение

Источник звука.
## bool isStopped ( ) const

Возвращает значение, указывающее, остановлено ли видео в данный момент.
### Возвращаемое значение

**1**, если видео остановлено; иначе **0**.
## void setVideoTime ( float time )

Перематывает видео назад или вперёд к заданному времени.
### Аргументы

- *float* **time** - Время в секундах.

## float getVideoTime ( ) const

Возвращает время текущего воспроизводимого кадра.
### Возвращаемое значение

Время в секундах.
## void setYUV ( int yuv )

Задаёт флаг для преобразования YUV.
### Аргументы

- *int* **yuv** - Флаг режима: **1**, если преобразование в RGB должно выполняться GPU, **0**, если CPU.

## int getYUV ( ) const

Возвращает флаг для преобразования YUV.
### Возвращаемое значение

**1**, если преобразование в RGB выполняется GPU, **0**, если CPU.
## void play ( )

Начинает воспроизведение видео.
## void stop ( )

Останавливает воспроизведение видео. Эта функция сохраняет позицию воспроизведения, чтобы воспроизведение файла можно было возобновить с той же точки.
