# Класс Unigine::Input (CPP)

**Заголовочный файл:** #include <UnigineInput.h>

> **Примечание:** Этот класс является одиночкой (singleton).


Класс Input содержит функции для простой ручной обработки пользовательского ввода с клавиатуры, мыши или геймпада.


### См. также


- Набор примеров на C++ (`<SAMPLES_PROJECT_PATH>/source/input_controls/`)


### Примеры использования


Следующий пример показывает способ перемещения и вращения узла с помощью класса Input:


```cpp
#include "AppWorldLogic.h"
#include <UnigineInput.h>

#include <UnigineConsole.h>

#include <UnigineGame.h>
#include <UniginePrimitives.h>

using namespace Unigine;

using namespace Math;

NodePtr box;

float move_speed = 1.0f;
float turn_speed = 30.0f;

int AppWorldLogic::init()
{

	box = Primitives::createBox(vec3_one);

	return 1;
}

int AppWorldLogic::update()
{

	if (Console::isActive())
		return 1;

	if (Input::isKeyPressed(Input::KEY_UP) || Input::isKeyPressed(Input::KEY_W))
		box->translate(Vec3_forward * move_speed * Game::getIFps());

	if (Input::isKeyPressed(Input::KEY_DOWN) || Input::isKeyPressed(Input::KEY_S))
		box->translate(Vec3_back * move_speed * Game::getIFps());

	if (Input::isKeyPressed(Input::KEY_LEFT) || Input::isKeyPressed(Input::KEY_A))
		box->rotate(0.0f, 0.0f, turn_speed * Game::getIFps());

	if (Input::isKeyPressed(Input::KEY_RIGHT) || Input::isKeyPressed(Input::KEY_D))
		box->rotate(0.0f, 0.0f, -turn_speed * Game::getIFps());

	return 1;
}

```


Следующий код демонстрирует, как получить событие, изменившее состояние кнопки, с помощью [isKeyDown()](#isKeyDown_int_int), [isKeyUp()](#isKeyUp_int_int). Такой код также можно использовать для кнопок мыши и сенсорного экрана.


```cpp
#include "AppWorldLogic.h"
#include <UnigineInput.h>

#include <UnigineConsole.h>

using namespace Unigine;

int AppWorldLogic::update()
{

	if (Input::isKeyDown(Input::KEY_T) || Input::isKeyUp(Input::KEY_T))
	{
		InputEventKeyboardPtr e = Input::getKeyEvent(Input::KEY_T);
		Console::messageLine("%s %d time = %lld frame = %lld", Input::getKeyName(e->getKey()), e->getAction(), e->getTimestamp(), e->getFrame());
	}

	return 1;
}

```


Следующий код иллюстрирует получение немедленного ввода (immediate input) — пользователь получает уведомление о событии сразу после фильтрации:


```cpp
#include "AppWorldLogic.h"
#include <UnigineInput.h>

#include <UnigineConsole.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	Input::getEventImmediateInput().connect(on_immediate_input);

	return 1;
}

```


Следующий код иллюстрирует работу фильтра событий. Нажатие кнопки "W" и движения мыши будут отклонены, т.е. эти события не будут восприняты как ввод:


```cpp
#include "AppWorldLogic.h"
#include <UnigineInput.h>

using namespace Unigine;

int event_filter(InputEventPtr& e)
{
	switch (e->getType())
	{
	case InputEvent::INPUT_EVENT_KEYBOARD:
	{
		// пропускаем повторные события клавиши 'W'
		InputEventKeyboardPtr k = checked_ptr_cast<InputEventKeyboard>(e);
		if (k->getKey() == Input::KEY_W && k->getAction() == InputEventKeyboard::ACTION_REPEAT)
			return 1;
		break;
	}

	case InputEvent::INPUT_EVENT_MOUSE_MOTION:
	{
		// пропускаем все события движения мыши
		return 1;
	}

	default: break;
	}

	return 0;
}

int AppWorldLogic::init()
{

	Input::setEventsFilter(event_filter);

	return 1;
}

```


Следующий код — пример создания событий ввода. Мы имитируем ввод консольной команды `show_profiler 1`, как если бы это было событие с клавиатуры.


```cpp
#include "AppWorldLogic.h"
#include <UnigineInput.h>

using namespace Unigine;

enum
{
	STATE_OPEN_CONSOLE = 0,
	STATE_TYPING_COMMAND,
	STATE_APPLY_COMMAND,
	STATE_FINISH,
};

int state = STATE_OPEN_CONSOLE;

void emulate_key_input(Input::KEY key)
{
	InputEventKeyboardPtr key_down = InputEventKeyboard::create();
	key_down->setAction(InputEventKeyboard::ACTION_DOWN);
	key_down->setKey(key);

	InputEventKeyboardPtr key_repeat = InputEventKeyboard::create();
	key_repeat->setAction(InputEventKeyboard::ACTION_REPEAT);
	key_repeat->setKey(key);

	InputEventKeyboardPtr key_up = InputEventKeyboard::create();
	key_up->setAction(InputEventKeyboard::ACTION_UP);
	key_up->setKey(key);

	Input::sendEvent(key_down);
	Input::sendEvent(key_repeat);
	Input::sendEvent(key_up);
}

void emulate_text_input(const char *text)
{
	int size = strlen(text);
	for (int i = 0; i < size; i++)
	{
		InputEventTextPtr text_input = InputEventText::create();
		text_input->setUnicode(text[i]);
		Input::sendEvent(text_input);
	}
}

int AppWorldLogic::update()
{

	switch (state)
	{
		case STATE_OPEN_CONSOLE:
		{
			emulate_key_input(Input::KEY_BACK_QUOTE);
			state = STATE_TYPING_COMMAND;
			break;
		}

		case STATE_TYPING_COMMAND:
		{
			emulate_text_input("show_profiler 1");
			state = STATE_APPLY_COMMAND;
			break;
		}

		case STATE_APPLY_COMMAND:
		{
			emulate_key_input(Input::KEY_ENTER);
			state = STATE_FINISH;
			break;
		}

		default: break;
	}

	return 1;
}

```


Следующий код демонстрирует, как получить различные имена кнопок с помощью методов [getKeyName()](#getKeyName_int_cstr), [keyToUnicode()](#keyToUnicode_int_uint) и [getKeyLocalName()](#getKeyLocalName_int_cstr):


```cpp
#include "AppWorldLogic.h"
#include <UnigineInput.h>

#include <UnigineConsole.h>

using namespace Unigine;

int AppWorldLogic::init()
{

	Console::setOnscreen(true);

	return 1;
}

int AppWorldLogic::update()
{

	auto print_info = [](const char* state, Input::KEY key)
	{
		unsigned int unicode = Input::keyToUnicode(key);
		Console::message("%s: (key='%s', unicode='%s', local_name='%s') ",
			state,
			Input::getKeyName(key),
			String::unicodeToUtf8(unicode).get(),
			Input::getKeyLocalName(key));
	};

	print_info("Up", Input::KEY_W);
	print_info("Jump", Input::KEY_SPACE);
	print_info("Run", Input::KEY_RIGHT_SHIFT);
	Console::message("\n");

	return 1;
}

```


## Класс Input

### Перечисления

## MOUSE_HANDLE

| Имя | Описание |
|---|---|
| **MOUSE_HANDLE_GRAB** = 0 | Мышь захватывается при клике (курсор исчезает, движение камеры управляется мышью). |
| **MOUSE_HANDLE_SOFT** = 1 | Курсор мыши исчезает после короткого периода бездействия. |
| **MOUSE_HANDLE_USER** = 2 | Мышь не обрабатывается системой (позволяет обрабатывать ввод пользовательскому модулю). |

## MOUSE_BUTTON

| Имя | Описание |
|---|---|
| **MOUSE_BUTTON_UNKNOWN** = 0 | Неизвестная кнопка мыши. |
| **MOUSE_BUTTON_LEFT** = 1 | Левая кнопка мыши. |
| **MOUSE_BUTTON_MIDDLE** = 2 | Средняя кнопка мыши. |
| **MOUSE_BUTTON_RIGHT** = 3 | Правая кнопка мыши. |
| **MOUSE_BUTTON_DCLICK** = 4 | Двойной клик левой кнопкой мыши. |
| **MOUSE_BUTTON_AUX_0** = 5 | Дополнительная кнопка мыши. |
| **MOUSE_BUTTON_AUX_1** = 6 | Дополнительная кнопка мыши. |
| **MOUSE_BUTTON_AUX_2** = 7 | Дополнительная кнопка мыши. |
| **MOUSE_BUTTON_AUX_3** = 8 | Дополнительная кнопка мыши. |
| **MOUSE_NUM_BUTTONS** = 9 | Количество кнопок мыши. |

## MODIFIER

| Имя | Описание |
|---|---|
| **MODIFIER_LEFT_SHIFT** = 0 | Левая клавиша *Shift* в качестве модификатора. |
| **MODIFIER_RIGHT_SHIFT** = 1 | Правая клавиша *Shift* в качестве модификатора. |
| **MODIFIER_LEFT_CTRL** = 2 | Левая клавиша *Ctrl* в качестве модификатора. |
| **MODIFIER_RIGHT_CTRL** = 3 | Правая клавиша *Ctrl* в качестве модификатора. |
| **MODIFIER_LEFT_ALT** = 4 | Левая клавиша *Alt* в качестве модификатора. |
| **MODIFIER_RIGHT_ALT** = 5 | Правая клавиша *Alt* в качестве модификатора. |
| **MODIFIER_LEFT_CMD** = 6 | Левая клавиша Command в качестве модификатора. |
| **MODIFIER_RIGHT_CMD** = 7 | Правая клавиша Command в качестве модификатора. |
| **MODIFIER_NUM_LOCK** = 8 | Клавиша *Num Lock* в качестве модификатора. |
| **MODIFIER_CAPS_LOCK** = 9 | Клавиша *Caps Lock* в качестве модификатора. |
| **MODIFIER_SCROLL_LOCK** = 10 | Клавиша *Scroll Lock* в качестве модификатора. |
| **MODIFIER_ALT_GR** = 11 | Клавиша *Alt Gr* в качестве модификатора. |
| **MODIFIER_ANY_SHIFT** = 12 | Любая клавиша *Shift* в качестве модификатора. |
| **MODIFIER_ANY_CTRL** = 13 | Любая клавиша *Ctrl* в качестве модификатора. |
| **MODIFIER_ANY_ALT** = 14 | Любая клавиша *Alt* в качестве модификатора. |
| **MODIFIER_ANY_CMD** = 15 | Любая клавиша Command в качестве модификатора. |
| **MODIFIER_NONE** = 16 | Модификатор не указан. |
| **NUM_MODIFIERS** = 17 | Общее количество модификаторов. |

## KEY

| Имя | Описание |
|---|---|
| **KEY_UNKNOWN** = 0 | Неизвестная клавиша |
| **KEY_ESC** = 1 | Клавиша *Escape* |
| **KEY_F1** = 2 | Клавиша **F1** |
| **KEY_F2** = 3 | Клавиша **F2** |
| **KEY_F3** = 4 | Клавиша **F3** |
| **KEY_F4** = 5 | Клавиша **F4** |
| **KEY_F5** = 6 | Клавиша **F5** |
| **KEY_F6** = 7 | Клавиша **F6** |
| **KEY_F7** = 8 | Клавиша **F7** |
| **KEY_F8** = 9 | Клавиша **F8** |
| **KEY_F9** = 10 | Клавиша **F9** |
| **KEY_F10** = 11 | Клавиша **F10** |
| **KEY_F11** = 12 | Клавиша **F11** |
| **KEY_F12** = 13 | Клавиша **F12** |
| **KEY_PRINTSCREEN** = 14 | Клавиша *Print Screen* |
| **KEY_SCROLL_LOCK** = 15 | Клавиша *Scroll Lock* |
| **KEY_PAUSE** = 16 | Клавиша *Pause* |
| **KEY_BACK_QUOTE** = 17 | Клавиша обратного апострофа |
| **KEY_DIGIT_1** = 18 | Клавиша **1** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_2** = 19 | Клавиша **2** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_3** = 20 | Клавиша **3** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_4** = 21 | Клавиша **4** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_5** = 22 | Клавиша **5** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_6** = 23 | Клавиша **6** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_7** = 24 | Клавиша **7** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_8** = 25 | Клавиша **8** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_9** = 26 | Клавиша **9** буквенно-цифровой клавиатуры |
| **KEY_DIGIT_0** = 27 | Клавиша **0** буквенно-цифровой клавиатуры |
| **KEY_MINUS** = 28 | Клавиша минуса |
| **KEY_EQUALS** = 29 | Клавиша равенства |
| **KEY_BACKSPACE** = 30 | Клавиша Backspace |
| **KEY_TAB** = 31 | Клавиша *Tab* |
| **KEY_Q** = 32 | Клавиша *Q* |
| **KEY_W** = 33 | Клавиша *W* |
| **KEY_E** = 34 | Клавиша *E* |
| **KEY_R** = 35 | Клавиша *R* |
| **KEY_T** = 36 | Клавиша *T* |
| **KEY_Y** = 37 | Клавиша *Y* |
| **KEY_U** = 38 | Клавиша *U* |
| **KEY_I** = 39 | Клавиша *I* |
| **KEY_O** = 40 | Клавиша *O* |
| **KEY_P** = 41 | Клавиша *P* |
| **KEY_LEFT_BRACKET** = 42 | Клавиша левой квадратной скобки |
| **KEY_RIGHT_BRACKET** = 43 | Клавиша правой квадратной скобки |
| **KEY_ENTER** = 44 | Клавиша *Enter* |
| **KEY_CAPS_LOCK** = 45 | Клавиша *Caps Lock* |
| **KEY_A** = 46 | Клавиша *A* |
| **KEY_S** = 47 | Клавиша *S* |
| **KEY_D** = 48 | Клавиша *D* |
| **KEY_F** = 49 | Клавиша *F* |
| **KEY_G** = 50 | Клавиша *G* |
| **KEY_H** = 51 | Клавиша *H* |
| **KEY_J** = 52 | Клавиша *J* |
| **KEY_K** = 53 | Клавиша *K* |
| **KEY_L** = 54 | Клавиша *L* |
| **KEY_SEMICOLON** = 55 | Клавиша точки с запятой |
| **KEY_QUOTE** = 56 | Клавиша апострофа |
| **KEY_BACK_SLASH** = 57 | Клавиша обратной косой черты |
| **KEY_LEFT_SHIFT** = 58 | Левая клавиша *Shift* |
| **KEY_LESS** = 59 | Клавиша "меньше" |
| **KEY_Z** = 60 | Клавиша **Z** |
| **KEY_X** = 61 | Клавиша **X** |
| **KEY_C** = 62 | Клавиша **C** |
| **KEY_V** = 63 | Клавиша **V** |
| **KEY_B** = 64 | Клавиша **B** |
| **KEY_N** = 65 | Клавиша **N** |
| **KEY_M** = 66 | Клавиша **M** |
| **KEY_COMMA** = 67 | Клавиша запятой |
| **KEY_DOT** = 68 | Клавиша точки |
| **KEY_SLASH** = 69 | Клавиша слэша |
| **KEY_RIGHT_SHIFT** = 70 | Правая клавиша *Shift* |
| **KEY_LEFT_CTRL** = 71 | Левая клавиша *Ctrl* |
| **KEY_LEFT_CMD** = 72 | Левая клавиша Command |
| **KEY_LEFT_ALT** = 73 | Левая клавиша *Alt* |
| **KEY_SPACE** = 74 | Клавиша пробела |
| **KEY_RIGHT_ALT** = 75 | Правая клавиша *Alt* |
| **KEY_RIGHT_CMD** = 76 | Правая клавиша Command |
| **KEY_MENU** = 77 | Клавиша меню |
| **KEY_RIGHT_CTRL** = 78 | Правая клавиша *Ctrl* |
| **KEY_INSERT** = 79 | Клавиша *Insert* |
| **KEY_DELETE** = 80 | Клавиша *Delete* |
| **KEY_HOME** = 81 | Клавиша *Home* |
| **KEY_END** = 82 | Клавиша *End* |
| **KEY_PGUP** = 83 | Клавиша Page Up |
| **KEY_PGDOWN** = 84 | Клавиша Page Down |
| **KEY_UP** = 85 | Клавиша стрелки вверх |
| **KEY_LEFT** = 86 | Клавиша стрелки влево |
| **KEY_DOWN** = 87 | Клавиша стрелки вниз |
| **KEY_RIGHT** = 88 | Клавиша стрелки вправо |
| **KEY_NUM_LOCK** = 89 | Клавиша *Num Lock* |
| **KEY_NUMPAD_DIVIDE** = 90 | Клавиша деления на цифровой клавиатуре |
| **KEY_NUMPAD_MULTIPLY** = 91 | Клавиша умножения на цифровой клавиатуре |
| **KEY_NUMPAD_MINUS** = 92 | Клавиша минуса на цифровой клавиатуре |
| **KEY_NUMPAD_DIGIT_7** = 93 | Клавиша **7** цифровой клавиатуры |
| **KEY_NUMPAD_DIGIT_8** = 94 | Клавиша **8** цифровой клавиатуры |
| **KEY_NUMPAD_DIGIT_9** = 95 | Клавиша **9** цифровой клавиатуры |
| **KEY_NUMPAD_PLUS** = 96 | Клавиша плюса на цифровой клавиатуре |
| **KEY_NUMPAD_DIGIT_4** = 97 | Клавиша **4** цифровой клавиатуры |
| **KEY_NUMPAD_DIGIT_5** = 98 | Клавиша **5** цифровой клавиатуры |
| **KEY_NUMPAD_DIGIT_6** = 99 | Клавиша **6** цифровой клавиатуры |
| **KEY_NUMPAD_DIGIT_1** = 100 | Клавиша **1** цифровой клавиатуры |
| **KEY_NUMPAD_DIGIT_2** = 101 | Клавиша **2** цифровой клавиатуры |
| **KEY_NUMPAD_DIGIT_3** = 102 | Клавиша **3** цифровой клавиатуры |
| **KEY_NUMPAD_ENTER** = 103 | Клавиша *Enter* на цифровой клавиатуре |
| **KEY_NUMPAD_DIGIT_0** = 104 | Клавиша **0** цифровой клавиатуры |
| **KEY_NUMPAD_DOT** = 105 | Клавиша точки на цифровой клавиатуре |
| **KEY_ANY_SHIFT** = 106 | Любая клавиша *Shift* |
| **KEY_ANY_CTRL** = 107 | Любая клавиша *Ctrl* |
| **KEY_ANY_ALT** = 108 | Любая клавиша *Alt* |
| **KEY_ANY_CMD** = 109 | Любая клавиша Command |
| **KEY_ANY_UP** = 110 | Любая клавиша стрелки вверх |
| **KEY_ANY_LEFT** = 111 | Любая клавиша стрелки влево |
| **KEY_ANY_DOWN** = 112 | Любая клавиша стрелки вниз |
| **KEY_ANY_RIGHT** = 113 | Любая клавиша стрелки вправо |
| **KEY_ANY_ENTER** = 114 | Любая клавиша Enter |
| **KEY_ANY_DELETE** = 115 | Любая клавиша *Delete* |
| **KEY_ANY_INSERT** = 116 | Любая клавиша *Insert* |
| **KEY_ANY_HOME** = 117 | Любая клавиша *Home* |
| **KEY_ANY_END** = 118 | Любая клавиша *End* |
| **KEY_ANY_PGUP** = 119 | Любая клавиша Page Up |
| **KEY_ANY_PGDOWN** = 120 | Любая клавиша Page Down |
| **KEY_ANY_DIGIT_1** = 121 | Клавиша **1** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_2** = 122 | Клавиша **2** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_3** = 123 | Клавиша **3** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_4** = 124 | Клавиша **4** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_5** = 125 | Клавиша **5** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_6** = 126 | Клавиша **6** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_7** = 127 | Клавиша **7** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_8** = 128 | Клавиша **8** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_9** = 129 | Клавиша **9** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_DIGIT_0** = 130 | Клавиша **0** буквенно-цифровой либо цифровой клавиатуры |
| **KEY_ANY_MINUS** = 131 | Любая клавиша минуса |
| **KEY_ANY_EQUALS** = 132 | Любая клавиша равенства |
| **KEY_ANY_DOT** = 133 | Любая клавиша точки |
| **NUM_KEYS** = 134 | Количество клавиш. |

## DEVICE

| Имя | Описание |
|---|---|
| **DEVICE_UNKNOWN** = 0 | Неизвестное устройство. |
| **DEVICE_GAME_CONTROLLER** = 1 | Игровой контроллер. |
| **DEVICE_WHEEL** = 2 | Руль. |
| **DEVICE_ARCADE_STICK** = 3 | Аркадный джойстик. |
| **DEVICE_FLIGHT_STICK** = 4 | Джойстик для авиасимуляторов. |
| **DEVICE_DANCE_PAD** = 5 | Танцевальная платформа. |
| **DEVICE_GUITAR** = 6 | Гитара. |
| **DEVICE_DRUM_KIT** = 7 | Барабанная установка. |
| **DEVICE_VR** = 8 | VR-устройство. |

## GAMEPAD_BUTTON

Кнопки геймпада.
| Имя | Описание |
|---|---|
| **GAMEPAD_BUTTON_A** = 0 | Кнопка A геймпада. |
| **GAMEPAD_BUTTON_B** = 1 | Кнопка B геймпада. |
| **GAMEPAD_BUTTON_X** = 2 | Кнопка X геймпада. |
| **GAMEPAD_BUTTON_Y** = 3 | Кнопка Y геймпада. |
| **GAMEPAD_BUTTON_BACK** = 4 | Кнопка "Back" геймпада. |
| **GAMEPAD_BUTTON_START** = 5 | Кнопка "Start" геймпада. |
| **GAMEPAD_BUTTON_DPAD_UP** = 6 | Кнопка "Up" геймпада. |
| **GAMEPAD_BUTTON_DPAD_DOWN** = 7 | Кнопка "Down" геймпада. |
| **GAMEPAD_BUTTON_DPAD_LEFT** = 8 | Кнопка "Left" геймпада. |
| **GAMEPAD_BUTTON_DPAD_RIGHT** = 9 | Кнопка "Right" геймпада. |
| **GAMEPAD_BUTTON_THUMB_LEFT** = 10 | Кнопка левого стика геймпада. |
| **GAMEPAD_BUTTON_THUMB_RIGHT** = 11 | Кнопка правого стика геймпада. |
| **GAMEPAD_BUTTON_SHOULDER_LEFT** = 12 | Левая кнопка плеча (бампер) геймпада. |
| **GAMEPAD_BUTTON_SHOULDER_RIGHT** = 13 | Правая кнопка плеча (бампер) геймпада. |
| **GAMEPAD_BUTTON_GUIDE** = 14 | Кнопка "Guide" геймпада. |
| **GAMEPAD_BUTTON_MISC1** = 15 | Дополнительная кнопка геймпада. |
| **GAMEPAD_BUTTON_TOUCHPAD** = 16 | Тачпад геймпада. |
| **NUM_GAMEPAD_BUTTONS** = 17 | Количество кнопок геймпада. |

## GAMEPAD_AXIS

| Имя | Описание |
|---|---|
| **GAMEPAD_AXIS_LEFT_X** = 0 | Ось X левого стика геймпада. |
| **GAMEPAD_AXIS_LEFT_Y** = 1 | Ось Y левого стика геймпада. |
| **GAMEPAD_AXIS_RIGHT_X** = 2 | Ось X правого стика геймпада. |
| **GAMEPAD_AXIS_RIGHT_Y** = 3 | Ось Y правого стика геймпада. |
| **GAMEPAD_AXIS_LEFT_TRIGGER** = 4 | Левый триггер геймпада. |
| **GAMEPAD_AXIS_RIGHT_TRIGGER** = 5 | Правый триггер геймпада. |
| **NUM_GAMEPAD_AXES** = 6 | Количество осей геймпада. |

## JOYSTICK_POV

Состояния переключателя POV (Point-of-View) или D-Pad.
| Имя | Описание |
|---|---|
| **JOYSTICK_POV_NOT_PRESSED** = 0 | Переключатель POV (Point-of-View) или кнопка D-Pad (крестовина) не нажата. |
| **JOYSTICK_POV_UP** = 1 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в верхнем положении. |
| **JOYSTICK_POV_UP_RIGHT** = 2 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в верхне-правом положении. |
| **JOYSTICK_POV_RIGHT** = 3 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в правом положении. |
| **JOYSTICK_POV_DOWN_RIGHT** = 4 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в нижне-правом положении. |
| **JOYSTICK_POV_DOWN** = 5 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в нижнем положении. |
| **JOYSTICK_POV_DOWN_LEFT** = 6 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в нижне-левом положении. |
| **JOYSTICK_POV_LEFT** = 7 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в левом положении. |
| **JOYSTICK_POV_UP_LEFT** = 8 | Переключатель POV (Point-of-View) или D-Pad (крестовина) в верхне-левом положении. |

## VR_BUTTON

| Имя | Описание |
|---|---|
| **VR_BUTTON_SYSTEM** = 0 | Системная кнопка. |
| **VR_BUTTON_START** = 1 | Кнопка Start. |
| **VR_BUTTON_HOME** = 2 | Кнопка Home. |
| **VR_BUTTON_END** = 3 | Кнопка End. |
| **VR_BUTTON_SELECT** = 4 | Кнопка Select. |
| **VR_BUTTON_VOLUME_UP** = 5 | Кнопка увеличения громкости. |
| **VR_BUTTON_VOLUME_DOWN** = 6 | Кнопка уменьшения громкости. |
| **VR_BUTTON_MUTE_MIC** = 7 | Кнопка отключения микрофона. |
| **VR_BUTTON_PLAY_PAUSE** = 8 | Кнопка Play/Pause. |
| **VR_BUTTON_MENU** = 9 | Кнопка меню. |
| **VR_BUTTON_VIEW** = 10 | Кнопка View. |
| **VR_BUTTON_BACK** = 11 | Кнопка Back. |
| **VR_BUTTON_X** = 12 | Кнопка X, зарезервированная для контроллера. |
| **VR_BUTTON_Y** = 13 | Кнопка Y, зарезервированная для контроллера. |
| **VR_BUTTON_SHOULDER** = 14 | Кнопка плеча, зарезервированная для контроллера. |
| **VR_BUTTON_GRIP** = 15 | Кнопка захвата (grip), зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_0** = 16 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_1** = 17 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_2** = 18 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_3** = 19 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_4** = 20 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_5** = 21 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_6** = 22 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_7** = 23 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_8** = 24 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_9** = 25 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_10** = 26 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_11** = 27 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_12** = 28 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_13** = 29 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_14** = 30 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_AXIS_15** = 31 | Ось, зарезервированная для контроллера. |
| **VR_BUTTON_DPAD_UP** = 32 | Кнопка "вверх" сенсорной панели. |
| **VR_BUTTON_DPAD_DOWN** = 33 | Кнопка "вниз" сенсорной панели. |
| **VR_BUTTON_DPAD_LEFT** = 34 | Кнопка "влево" сенсорной панели. |
| **VR_BUTTON_DPAD_RIGHT** = 35 | Кнопка "вправо" сенсорной панели. |
| **VR_BUTTON_DPAD_CENTER** = 36 | Центральная кнопка сенсорной панели. |
| **VR_BUTTON_THUMBREST** = 37 | Место для отдыха большого пальца. |
| **VR_BUTTON_THUMB_RESTING_SURFACES** = 38 | Поверхности для отдыха большого пальца — любые поверхности, на которых большой палец может естественным образом располагаться. Это могут быть, среди прочего, лицевые кнопки, стик и место для отдыха большого пальца. |
| **VR_BUTTON_PROXIMITY_SENSOR** = 39 | Датчик приближения. |
| **VR_BUTTON_APPLICATION** = 40 | Кнопка меню приложения. |
| **NUM_VR_BUTTONS** = 41 | Общее количество VR-кнопок и осей. |

## JOYSTICK_FORCE_FEEDBACK_EFFECT

| Имя | Описание |
|---|---|
| **JOYSTICK_FORCE_FEEDBACK_CONSTANT** = 0 | Постоянная сила в одном направлении. |
| **JOYSTICK_FORCE_FEEDBACK_RAMP** = 1 | Сила, равномерно увеличивающаяся или уменьшающаяся по величине. |
| **JOYSTICK_FORCE_FEEDBACK_SINEWAVE** = 2 | Сила пульсирует периодически по синусоидальной волновой форме. |
| **JOYSTICK_FORCE_FEEDBACK_SQUAREWAVE** = 3 | Сила пульсирует периодически по прямоугольной волновой форме. |
| **JOYSTICK_FORCE_FEEDBACK_TRIANGLEWAVE** = 4 | Сила пульсирует периодически по треугольной волновой форме. |
| **JOYSTICK_FORCE_FEEDBACK_SAWTOOTHUPWAVE** = 5 | Сила пульсирует периодически по возрастающей (прямой) пилообразной форме. |
| **JOYSTICK_FORCE_FEEDBACK_SAWTOOTHDOWNWAVE** = 6 | Сила пульсирует периодически по убывающей (обратной) пилообразной форме. |
| **JOYSTICK_FORCE_FEEDBACK_SPRING** = 7 | Сила увеличивается пропорционально расстоянию оси от заданной нейтральной точки. |
| **JOYSTICK_FORCE_FEEDBACK_FRICTION** = 8 | Сила применяется при перемещении оси и зависит от заданного коэффициента трения. |
| **JOYSTICK_FORCE_FEEDBACK_DAMPER** = 9 | Сила увеличивается пропорционально скорости, с которой пользователь перемещает ось. |
| **JOYSTICK_FORCE_FEEDBACK_INERTIA** = 10 | Сила увеличивается пропорционально ускорению оси. |
| **NUM_JOYSTICK_FORCE_FEEDBACKS** = 11 | Общее количество эффектов силовой обратной связи джойстика. |

### Методы класса

## int getNumJoysticks () const

Возвращает текущее количество джойстиков.
### Возвращаемое значение

Текущее количество джойстиков.
## int getNumGamePads () const

Возвращает текущее количество всех геймпадов.
### Возвращаемое значение

Текущее количество всех геймпадов.
## int getMouseWheelHorizontal () const

Возвращает текущее значение горизонтальной прокрутки мыши.
### Возвращаемое значение

Текущее значение горизонтальной прокрутки мыши в диапазоне [-1;1].
## int getMouseWheel () const

Возвращает текущее значение вертикальной прокрутки мыши.
### Возвращаемое значение

Текущее значение прокрутки мыши. Отрицательные значения соответствуют прокрутке вниз; положительные — прокрутке вверх; значение равно нулю, если колесо мыши не прокручивается.
## Math:: ivec2 getMouseDeltaPosition () const

Возвращает текущий вектор, содержащий дельта-значения позиции курсора мыши.
### Возвращаемое значение

Текущий вектор, содержащий изменение экранной позиции указателя мыши по осям X и Y — разницу между значениями в предыдущем и текущем кадрах.
## void setMousePosition ( const Math:: ivec2 & position )

Устанавливает новый вектор, содержащий целочисленные значения позиции курсора мыши.
### Аргументы

- *const  Math::[ivec2](../../../api/library/math/class.ivec2_cpp.md)&* **position** - Возвращает вектор, содержащий глобальные координаты курсора мыши. В случае события кнопки мыши возвращается позиция курсора на момент обработки события. При отсутствии такого события возвращается позиция мыши на начало кадра. Чтобы получить позицию курсора во время события другого типа, получите это событие (например, с помощью [getKeyEvent()](#getKeyEvent_int_InputEventKeyboard)) и извлеките позицию курсора, хранящуюся внутри него.

## Math:: ivec2 getMousePosition () const

Возвращает текущий вектор, содержащий целочисленные значения позиции курсора мыши.
### Возвращаемое значение

Текущий вектор, содержащий глобальные координаты курсора мыши. В случае события кнопки мыши возвращается позиция курсора на момент обработки события. При отсутствии такого события возвращается позиция мыши на начало кадра. Чтобы получить позицию курсора во время события другого типа, получите это событие (например, с помощью [getKeyEvent()](#getKeyEvent_int_InputEventKeyboard)) и извлеките позицию курсора, хранящуюся внутри него.
## void setMouseHandle ( Input::MOUSE_HANDLE handle )

Устанавливает новый режим поведения мыши — одно из значений [MOUSE_HANDLE](#MOUSE_HANDLE).
### Аргументы

- *[Input::MOUSE_HANDLE](../../../api/library/controls/class.input_cpp.md#MOUSE_HANDLE)* **handle** - Режим поведения мыши — одно из значений [MOUSE_HANDLE](#MOUSE_HANDLE).

## Input::MOUSE_HANDLE getMouseHandle () const

Возвращает текущий режим поведения мыши — одно из значений [MOUSE_HANDLE](#MOUSE_HANDLE).
### Возвращаемое значение

Текущий режим поведения мыши — одно из значений [MOUSE_HANDLE](#MOUSE_HANDLE).
## void setMouseCursorNeedUpdate ( bool update )

Устанавливает новое значение, указывающее, что курсор был изменён (показан, скрыт, изменён на системный или иным образом) и его необходимо обновить. Предположим, что курсор был изменён, например, плагином *Interface*. После закрытия окна плагина курсор не вернётся в предыдущее состояние, поскольку SDL даже не знает об изменениях. Вы можете использовать этот флаг, чтобы сигнализировать о необходимости обновления курсора мыши.
### Аргументы

- *bool* **update** - **true** — включить признак того, что курсор был изменён (показан, скрыт, изменён на системный или иным образом) и его необходимо обновить; **false** — отключить.

## bool isMouseCursorNeedUpdate () const

Возвращает текущее значение, указывающее, что курсор был изменён (показан, скрыт, изменён на системный или иным образом) и его необходимо обновить. Предположим, что курсор был изменён, например, плагином *Interface*. После закрытия окна плагина курсор не вернётся в предыдущее состояние, поскольку SDL даже не знает об изменениях. Вы можете использовать этот флаг, чтобы сигнализировать о необходимости обновления курсора мыши.
### Возвращаемое значение

**true**, если курсор был изменён (показан, скрыт, изменён на системный или иным образом) и его необходимо обновить; иначе **false**.
## void setMouseCursorSystem ( bool system )

Устанавливает новое значение, указывающее, отображается ли системный указатель мыши ОС.
### Аргументы

- *bool* **system** - **true** — включить признак того, что отображается системный указатель мыши ОС; **false** — отключить.

## bool isMouseCursorSystem () const

Возвращает текущее значение, указывающее, отображается ли системный указатель мыши ОС.
### Возвращаемое значение

**true**, если отображается системный указатель мыши ОС; иначе **false**.
## void setMouseCursorHide ( bool hide )

Устанавливает новое значение, указывающее, скрыт ли курсор мыши в текущем кадре.
### Аргументы

- *bool* **hide** - **true** — включить признак того, что курсор мыши скрыт в текущем кадре; **false** — отключить.

## bool isMouseCursorHide () const

Возвращает текущее значение, указывающее, скрыт ли курсор мыши в текущем кадре.
### Возвращаемое значение

**true**, если курсор мыши скрыт в текущем кадре; иначе **false**.
## void setMouseGrab ( bool grab )

Устанавливает новое значение, указывающее, привязан ли указатель мыши к окну приложения (не может покинуть его).
### Аргументы

- *bool* **grab** - **true** — включить признак того, что указатель мыши привязан к окну приложения; **false** — отключить.

## bool isMouseGrab () const

Возвращает текущее значение, указывающее, привязан ли указатель мыши к окну приложения (не может покинуть его).
### Возвращаемое значение

**true**, если указатель мыши привязан к окну приложения; иначе **false**.
## void setClipboard ( const char * clipboard )

Устанавливает новое содержимое системного буфера обмена.
### Аргументы

- *const char ** **clipboard** - Содержимое системного буфера обмена.

## const char * getClipboard () const

Возвращает текущее содержимое системного буфера обмена.
### Возвращаемое значение

Текущее содержимое системного буфера обмена.
## bool isEmptyClipboard () const

Возвращает текущее значение, указывающее, пуст ли буфер обмена.
### Возвращаемое значение

**true**, если буфер обмена пуст; иначе **false**.
## Math:: ivec2 getMouseDeltaRaw () const

Возвращает текущее изменение абсолютной позиции мыши (не экранного курсора) в точках на дюйм.
### Возвращаемое значение

Текущее изменение абсолютной позиции мыши (не экранного курсора) в точках на дюйм.
## Ptr < InputVRController > getVRControllerTreadmill () const

Возвращает текущий VR-контроллер беговой дорожки.
### Возвращаемое значение

Текущий VR-контроллер беговой дорожки.
## Ptr < InputVRController > getVRControllerRight () const

Возвращает текущий правый VR-контроллер.
### Возвращаемое значение

Текущий правый VR-контроллер.
## Ptr < InputVRController > getVRControllerLeft () const

Возвращает текущий левый VR-контроллер.
### Возвращаемое значение

Текущий левый VR-контроллер.
## Ptr < InputVRHead > getVRHead () const

Возвращает текущий VR-контроллер головы.
### Возвращаемое значение

Текущий VR-контроллер головы.
## int getNumVRDevices () const

Возвращает текущее количество всех VR-устройств.
### Возвращаемое значение

Текущее количество всех VR-устройств.
## static Event<const Ptr < InputEvent > &> getEventImmediateInput () const

Событие, срабатывающее немедленно при получении ввода от прокси, до его обработки движком. Это событие может срабатывать в разных потоках в зависимости от реализации прокси. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(const Ptr<InputEvent> & **event**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события ImmediateInput
void immediateinput_event_handler(const Ptr<InputEvent> & event)
{
	Log::message("\Обработка события ImmediateInput\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections immediateinput_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventImmediateInput().connect(immediateinput_event_connections, immediateinput_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventImmediateInput().connect(immediateinput_event_connections, [](const Ptr<InputEvent> & event) {
		Log::message("\Обработка события ImmediateInput (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
immediateinput_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection immediateinput_event_connection;

// подписываемся на событие ImmediateInput с функцией-обработчиком, сохраняя соединение
Input::getEventImmediateInput().connect(immediateinput_event_connection, immediateinput_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
immediateinput_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
immediateinput_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие ImmediateInput через соединение
immediateinput_event_connection.disconnect();

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

	// Обработчик события ImmediateInput, реализованный как член класса
	void event_handler(const Ptr<InputEvent> & event)
	{
		Log::message("\Обработка события ImmediateInput\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventImmediateInput().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId immediateinput_handler_id;

// подписываемся на событие ImmediateInput с лямбда-обработчиком, сохраняя идентификатор соединения
immediateinput_handler_id = Input::getEventImmediateInput().connect(e_connections, [](const Ptr<InputEvent> & event) {
		Log::message("\Обработка события ImmediateInput (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventImmediateInput().disconnect(immediateinput_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий ImmediateInput при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventImmediateInput().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventImmediateInput().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int> getEventJoyPovMotion () const

Событие, срабатывающее при изменении значения состояния POV джойстика. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **joystick_id**, int **pov_index**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события JoyPovMotion
void joypovmotion_event_handler(int joystick_id,  int pov_index)
{
	Log::message("\Обработка события JoyPovMotion\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections joypovmotion_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventJoyPovMotion().connect(joypovmotion_event_connections, joypovmotion_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventJoyPovMotion().connect(joypovmotion_event_connections, [](int joystick_id,  int pov_index) {
		Log::message("\Обработка события JoyPovMotion (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
joypovmotion_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection joypovmotion_event_connection;

// подписываемся на событие JoyPovMotion с функцией-обработчиком, сохраняя соединение
Input::getEventJoyPovMotion().connect(joypovmotion_event_connection, joypovmotion_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
joypovmotion_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
joypovmotion_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие JoyPovMotion через соединение
joypovmotion_event_connection.disconnect();

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

	// Обработчик события JoyPovMotion, реализованный как член класса
	void event_handler(int joystick_id,  int pov_index)
	{
		Log::message("\Обработка события JoyPovMotion\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventJoyPovMotion().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId joypovmotion_handler_id;

// подписываемся на событие JoyPovMotion с лямбда-обработчиком, сохраняя идентификатор соединения
joypovmotion_handler_id = Input::getEventJoyPovMotion().connect(e_connections, [](int joystick_id,  int pov_index) {
		Log::message("\Обработка события JoyPovMotion (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventJoyPovMotion().disconnect(joypovmotion_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий JoyPovMotion при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventJoyPovMotion().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventJoyPovMotion().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int> getEventJoyAxisMotion () const

Событие, срабатывающее при изменении значения состояния оси джойстика. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**joystick_id**, int **axis**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события JoyAxisMotion
void joyaxismotion_event_handler(joystick_id,  int axis)
{
	Log::message("\Обработка события JoyAxisMotion\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections joyaxismotion_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventJoyAxisMotion().connect(joyaxismotion_event_connections, joyaxismotion_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventJoyAxisMotion().connect(joyaxismotion_event_connections, [](joystick_id,  int axis) {
		Log::message("\Обработка события JoyAxisMotion (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
joyaxismotion_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection joyaxismotion_event_connection;

// подписываемся на событие JoyAxisMotion с функцией-обработчиком, сохраняя соединение
Input::getEventJoyAxisMotion().connect(joyaxismotion_event_connection, joyaxismotion_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
joyaxismotion_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
joyaxismotion_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие JoyAxisMotion через соединение
joyaxismotion_event_connection.disconnect();

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

	// Обработчик события JoyAxisMotion, реализованный как член класса
	void event_handler(joystick_id,  int axis)
	{
		Log::message("\Обработка события JoyAxisMotion\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventJoyAxisMotion().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId joyaxismotion_handler_id;

// подписываемся на событие JoyAxisMotion с лямбда-обработчиком, сохраняя идентификатор соединения
joyaxismotion_handler_id = Input::getEventJoyAxisMotion().connect(e_connections, [](joystick_id,  int axis) {
		Log::message("\Обработка события JoyAxisMotion (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventJoyAxisMotion().disconnect(joyaxismotion_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий JoyAxisMotion при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventJoyAxisMotion().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventJoyAxisMotion().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int> getEventJoyButtonUp () const

Событие, срабатывающее при отпускании кнопки джойстика. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**joystick_id**, int **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события JoyButtonUp
void joybuttonup_event_handler(joystick_id,  int button)
{
	Log::message("\Обработка события JoyButtonUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections joybuttonup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventJoyButtonUp().connect(joybuttonup_event_connections, joybuttonup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventJoyButtonUp().connect(joybuttonup_event_connections, [](joystick_id,  int button) {
		Log::message("\Обработка события JoyButtonUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
joybuttonup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection joybuttonup_event_connection;

// подписываемся на событие JoyButtonUp с функцией-обработчиком, сохраняя соединение
Input::getEventJoyButtonUp().connect(joybuttonup_event_connection, joybuttonup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
joybuttonup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
joybuttonup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие JoyButtonUp через соединение
joybuttonup_event_connection.disconnect();

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

	// Обработчик события JoyButtonUp, реализованный как член класса
	void event_handler(joystick_id,  int button)
	{
		Log::message("\Обработка события JoyButtonUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventJoyButtonUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId joybuttonup_handler_id;

// подписываемся на событие JoyButtonUp с лямбда-обработчиком, сохраняя идентификатор соединения
joybuttonup_handler_id = Input::getEventJoyButtonUp().connect(e_connections, [](joystick_id,  int button) {
		Log::message("\Обработка события JoyButtonUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventJoyButtonUp().disconnect(joybuttonup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий JoyButtonUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventJoyButtonUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventJoyButtonUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int> getEventJoyButtonDown () const

Событие, срабатывающее при нажатии кнопки джойстика. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**joystick_id**, int **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события JoyButtonDown
void joybuttondown_event_handler(joystick_id,  int button)
{
	Log::message("\Обработка события JoyButtonDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections joybuttondown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventJoyButtonDown().connect(joybuttondown_event_connections, joybuttondown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventJoyButtonDown().connect(joybuttondown_event_connections, [](joystick_id,  int button) {
		Log::message("\Обработка события JoyButtonDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
joybuttondown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection joybuttondown_event_connection;

// подписываемся на событие JoyButtonDown с функцией-обработчиком, сохраняя соединение
Input::getEventJoyButtonDown().connect(joybuttondown_event_connection, joybuttondown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
joybuttondown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
joybuttondown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие JoyButtonDown через соединение
joybuttondown_event_connection.disconnect();

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

	// Обработчик события JoyButtonDown, реализованный как член класса
	void event_handler(joystick_id,  int button)
	{
		Log::message("\Обработка события JoyButtonDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventJoyButtonDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId joybuttondown_handler_id;

// подписываемся на событие JoyButtonDown с лямбда-обработчиком, сохраняя идентификатор соединения
joybuttondown_handler_id = Input::getEventJoyButtonDown().connect(e_connections, [](joystick_id,  int button) {
		Log::message("\Обработка события JoyButtonDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventJoyButtonDown().disconnect(joybuttondown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий JoyButtonDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventJoyButtonDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventJoyButtonDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventJoyDisconnected () const

Событие, срабатывающее при отключении джойстика. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**joystick_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события JoyDisconnected
void joydisconnected_event_handler(joystick_id)
{
	Log::message("\Обработка события JoyDisconnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections joydisconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventJoyDisconnected().connect(joydisconnected_event_connections, joydisconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventJoyDisconnected().connect(joydisconnected_event_connections, [](joystick_id) {
		Log::message("\Обработка события JoyDisconnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
joydisconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection joydisconnected_event_connection;

// подписываемся на событие JoyDisconnected с функцией-обработчиком, сохраняя соединение
Input::getEventJoyDisconnected().connect(joydisconnected_event_connection, joydisconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
joydisconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
joydisconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие JoyDisconnected через соединение
joydisconnected_event_connection.disconnect();

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

	// Обработчик события JoyDisconnected, реализованный как член класса
	void event_handler(joystick_id)
	{
		Log::message("\Обработка события JoyDisconnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventJoyDisconnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId joydisconnected_handler_id;

// подписываемся на событие JoyDisconnected с лямбда-обработчиком, сохраняя идентификатор соединения
joydisconnected_handler_id = Input::getEventJoyDisconnected().connect(e_connections, [](joystick_id) {
		Log::message("\Обработка события JoyDisconnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventJoyDisconnected().disconnect(joydisconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий JoyDisconnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventJoyDisconnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventJoyDisconnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventJoyConnected () const

Событие, срабатывающее при подключении джойстика. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**joystick_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события JoyConnected
void joyconnected_event_handler(joystick_id)
{
	Log::message("\Обработка события JoyConnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections joyconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventJoyConnected().connect(joyconnected_event_connections, joyconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventJoyConnected().connect(joyconnected_event_connections, [](joystick_id) {
		Log::message("\Обработка события JoyConnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
joyconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection joyconnected_event_connection;

// подписываемся на событие JoyConnected с функцией-обработчиком, сохраняя соединение
Input::getEventJoyConnected().connect(joyconnected_event_connection, joyconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
joyconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
joyconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие JoyConnected через соединение
joyconnected_event_connection.disconnect();

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

	// Обработчик события JoyConnected, реализованный как член класса
	void event_handler(joystick_id)
	{
		Log::message("\Обработка события JoyConnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventJoyConnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId joyconnected_handler_id;

// подписываемся на событие JoyConnected с лямбда-обработчиком, сохраняя идентификатор соединения
joyconnected_handler_id = Input::getEventJoyConnected().connect(e_connections, [](joystick_id) {
		Log::message("\Обработка события JoyConnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventJoyConnected().disconnect(joyconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий JoyConnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventJoyConnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventJoyConnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int> getEventVrDeviceAxisMotion () const

Событие, срабатывающее при изменении значения состояния оси VR-устройства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**device_id**, int **axis**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события VrDeviceAxisMotion
void vrdeviceaxismotion_event_handler(device_id,  int axis)
{
	Log::message("\Обработка события VrDeviceAxisMotion\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections vrdeviceaxismotion_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventVrDeviceAxisMotion().connect(vrdeviceaxismotion_event_connections, vrdeviceaxismotion_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventVrDeviceAxisMotion().connect(vrdeviceaxismotion_event_connections, [](device_id,  int axis) {
		Log::message("\Обработка события VrDeviceAxisMotion (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
vrdeviceaxismotion_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection vrdeviceaxismotion_event_connection;

// подписываемся на событие VrDeviceAxisMotion с функцией-обработчиком, сохраняя соединение
Input::getEventVrDeviceAxisMotion().connect(vrdeviceaxismotion_event_connection, vrdeviceaxismotion_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
vrdeviceaxismotion_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
vrdeviceaxismotion_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие VrDeviceAxisMotion через соединение
vrdeviceaxismotion_event_connection.disconnect();

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

	// Обработчик события VrDeviceAxisMotion, реализованный как член класса
	void event_handler(device_id,  int axis)
	{
		Log::message("\Обработка события VrDeviceAxisMotion\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventVrDeviceAxisMotion().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId vrdeviceaxismotion_handler_id;

// подписываемся на событие VrDeviceAxisMotion с лямбда-обработчиком, сохраняя идентификатор соединения
vrdeviceaxismotion_handler_id = Input::getEventVrDeviceAxisMotion().connect(e_connections, [](device_id,  int axis) {
		Log::message("\Обработка события VrDeviceAxisMotion (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventVrDeviceAxisMotion().disconnect(vrdeviceaxismotion_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий VrDeviceAxisMotion при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventVrDeviceAxisMotion().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventVrDeviceAxisMotion().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, Input::VR_BUTTON > getEventVrDeviceButtonTouchUp () const

Событие, срабатывающее при отведении пальца от кнопки VR-устройства. Если палец отпускает кнопку, которая была нажата, это событие срабатывает вместе с [EventVrDeviceButtonUp](#EventVrDeviceButtonUp). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **device_id**, Input::VR_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события VrDeviceButtonTouchUp
void vrdevicebuttontouchup_event_handler(int device_id,  Input::VR_BUTTON button)
{
	Log::message("\Обработка события VrDeviceButtonTouchUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections vrdevicebuttontouchup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventVrDeviceButtonTouchUp().connect(vrdevicebuttontouchup_event_connections, vrdevicebuttontouchup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventVrDeviceButtonTouchUp().connect(vrdevicebuttontouchup_event_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonTouchUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
vrdevicebuttontouchup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection vrdevicebuttontouchup_event_connection;

// подписываемся на событие VrDeviceButtonTouchUp с функцией-обработчиком, сохраняя соединение
Input::getEventVrDeviceButtonTouchUp().connect(vrdevicebuttontouchup_event_connection, vrdevicebuttontouchup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
vrdevicebuttontouchup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
vrdevicebuttontouchup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие VrDeviceButtonTouchUp через соединение
vrdevicebuttontouchup_event_connection.disconnect();

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

	// Обработчик события VrDeviceButtonTouchUp, реализованный как член класса
	void event_handler(int device_id,  Input::VR_BUTTON button)
	{
		Log::message("\Обработка события VrDeviceButtonTouchUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventVrDeviceButtonTouchUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId vrdevicebuttontouchup_handler_id;

// подписываемся на событие VrDeviceButtonTouchUp с лямбда-обработчиком, сохраняя идентификатор соединения
vrdevicebuttontouchup_handler_id = Input::getEventVrDeviceButtonTouchUp().connect(e_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonTouchUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventVrDeviceButtonTouchUp().disconnect(vrdevicebuttontouchup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий VrDeviceButtonTouchUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventVrDeviceButtonTouchUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventVrDeviceButtonTouchUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, Input::VR_BUTTON > getEventVrDeviceButtonTouchDown () const

Событие, срабатывающее при касании кнопки VR-устройства. Если кнопка была затронута и нажата, вместе с этим событием срабатывает [EventVrDeviceButtonDown](#EventVrDeviceButtonDown). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **device_id**, Input::VR_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события VrDeviceButtonTouchDown
void vrdevicebuttontouchdown_event_handler(int device_id,  Input::VR_BUTTON button)
{
	Log::message("\Обработка события VrDeviceButtonTouchDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections vrdevicebuttontouchdown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventVrDeviceButtonTouchDown().connect(vrdevicebuttontouchdown_event_connections, vrdevicebuttontouchdown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventVrDeviceButtonTouchDown().connect(vrdevicebuttontouchdown_event_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonTouchDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
vrdevicebuttontouchdown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection vrdevicebuttontouchdown_event_connection;

// подписываемся на событие VrDeviceButtonTouchDown с функцией-обработчиком, сохраняя соединение
Input::getEventVrDeviceButtonTouchDown().connect(vrdevicebuttontouchdown_event_connection, vrdevicebuttontouchdown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
vrdevicebuttontouchdown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
vrdevicebuttontouchdown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие VrDeviceButtonTouchDown через соединение
vrdevicebuttontouchdown_event_connection.disconnect();

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

	// Обработчик события VrDeviceButtonTouchDown, реализованный как член класса
	void event_handler(int device_id,  Input::VR_BUTTON button)
	{
		Log::message("\Обработка события VrDeviceButtonTouchDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventVrDeviceButtonTouchDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId vrdevicebuttontouchdown_handler_id;

// подписываемся на событие VrDeviceButtonTouchDown с лямбда-обработчиком, сохраняя идентификатор соединения
vrdevicebuttontouchdown_handler_id = Input::getEventVrDeviceButtonTouchDown().connect(e_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonTouchDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventVrDeviceButtonTouchDown().disconnect(vrdevicebuttontouchdown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий VrDeviceButtonTouchDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventVrDeviceButtonTouchDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventVrDeviceButtonTouchDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, Input::VR_BUTTON > getEventVrDeviceButtonUp () const

Событие, срабатывающее при отпускании кнопки VR-устройства. Если палец отводится от кнопки, которая была нажата, вместе с этим событием срабатывает [EventVrDeviceButtonTouchUp](#EventVrDeviceButtonTouchUp). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **device_id**, Input::VR_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события VrDeviceButtonUp
void vrdevicebuttonup_event_handler(int device_id,  Input::VR_BUTTON button)
{
	Log::message("\Обработка события VrDeviceButtonUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections vrdevicebuttonup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventVrDeviceButtonUp().connect(vrdevicebuttonup_event_connections, vrdevicebuttonup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventVrDeviceButtonUp().connect(vrdevicebuttonup_event_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
vrdevicebuttonup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection vrdevicebuttonup_event_connection;

// подписываемся на событие VrDeviceButtonUp с функцией-обработчиком, сохраняя соединение
Input::getEventVrDeviceButtonUp().connect(vrdevicebuttonup_event_connection, vrdevicebuttonup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
vrdevicebuttonup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
vrdevicebuttonup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие VrDeviceButtonUp через соединение
vrdevicebuttonup_event_connection.disconnect();

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

	// Обработчик события VrDeviceButtonUp, реализованный как член класса
	void event_handler(int device_id,  Input::VR_BUTTON button)
	{
		Log::message("\Обработка события VrDeviceButtonUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventVrDeviceButtonUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId vrdevicebuttonup_handler_id;

// подписываемся на событие VrDeviceButtonUp с лямбда-обработчиком, сохраняя идентификатор соединения
vrdevicebuttonup_handler_id = Input::getEventVrDeviceButtonUp().connect(e_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventVrDeviceButtonUp().disconnect(vrdevicebuttonup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий VrDeviceButtonUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventVrDeviceButtonUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventVrDeviceButtonUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, Input::VR_BUTTON > getEventVrDeviceButtonDown () const

Событие, срабатывающее при нажатии кнопки VR-устройства. Если кнопка ранее не была затронута, вместе с этим событием срабатывает [EventVrDeviceButtonTouchDown](#EventVrDeviceButtonTouchDown). Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **device_id**, Input::VR_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события VrDeviceButtonDown
void vrdevicebuttondown_event_handler(int device_id,  Input::VR_BUTTON button)
{
	Log::message("\Обработка события VrDeviceButtonDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections vrdevicebuttondown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventVrDeviceButtonDown().connect(vrdevicebuttondown_event_connections, vrdevicebuttondown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventVrDeviceButtonDown().connect(vrdevicebuttondown_event_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
vrdevicebuttondown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection vrdevicebuttondown_event_connection;

// подписываемся на событие VrDeviceButtonDown с функцией-обработчиком, сохраняя соединение
Input::getEventVrDeviceButtonDown().connect(vrdevicebuttondown_event_connection, vrdevicebuttondown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
vrdevicebuttondown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
vrdevicebuttondown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие VrDeviceButtonDown через соединение
vrdevicebuttondown_event_connection.disconnect();

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

	// Обработчик события VrDeviceButtonDown, реализованный как член класса
	void event_handler(int device_id,  Input::VR_BUTTON button)
	{
		Log::message("\Обработка события VrDeviceButtonDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventVrDeviceButtonDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId vrdevicebuttondown_handler_id;

// подписываемся на событие VrDeviceButtonDown с лямбда-обработчиком, сохраняя идентификатор соединения
vrdevicebuttondown_handler_id = Input::getEventVrDeviceButtonDown().connect(e_connections, [](int device_id,  Input::VR_BUTTON button) {
		Log::message("\Обработка события VrDeviceButtonDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventVrDeviceButtonDown().disconnect(vrdevicebuttondown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий VrDeviceButtonDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventVrDeviceButtonDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventVrDeviceButtonDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventVrDeviceDisconnected () const

Событие, срабатывающее при отключении VR-устройства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**device_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события VrDeviceDisconnected
void vrdevicedisconnected_event_handler(device_id)
{
	Log::message("\Обработка события VrDeviceDisconnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections vrdevicedisconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventVrDeviceDisconnected().connect(vrdevicedisconnected_event_connections, vrdevicedisconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventVrDeviceDisconnected().connect(vrdevicedisconnected_event_connections, [](device_id) {
		Log::message("\Обработка события VrDeviceDisconnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
vrdevicedisconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection vrdevicedisconnected_event_connection;

// подписываемся на событие VrDeviceDisconnected с функцией-обработчиком, сохраняя соединение
Input::getEventVrDeviceDisconnected().connect(vrdevicedisconnected_event_connection, vrdevicedisconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
vrdevicedisconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
vrdevicedisconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие VrDeviceDisconnected через соединение
vrdevicedisconnected_event_connection.disconnect();

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

	// Обработчик события VrDeviceDisconnected, реализованный как член класса
	void event_handler(device_id)
	{
		Log::message("\Обработка события VrDeviceDisconnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventVrDeviceDisconnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId vrdevicedisconnected_handler_id;

// подписываемся на событие VrDeviceDisconnected с лямбда-обработчиком, сохраняя идентификатор соединения
vrdevicedisconnected_handler_id = Input::getEventVrDeviceDisconnected().connect(e_connections, [](device_id) {
		Log::message("\Обработка события VrDeviceDisconnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventVrDeviceDisconnected().disconnect(vrdevicedisconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий VrDeviceDisconnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventVrDeviceDisconnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventVrDeviceDisconnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventVrDeviceConnected () const

Событие, срабатывающее при подключении VR-устройства. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**device_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события VrDeviceConnected
void vrdeviceconnected_event_handler(device_id)
{
	Log::message("\Обработка события VrDeviceConnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections vrdeviceconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventVrDeviceConnected().connect(vrdeviceconnected_event_connections, vrdeviceconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventVrDeviceConnected().connect(vrdeviceconnected_event_connections, [](device_id) {
		Log::message("\Обработка события VrDeviceConnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
vrdeviceconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection vrdeviceconnected_event_connection;

// подписываемся на событие VrDeviceConnected с функцией-обработчиком, сохраняя соединение
Input::getEventVrDeviceConnected().connect(vrdeviceconnected_event_connection, vrdeviceconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
vrdeviceconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
vrdeviceconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие VrDeviceConnected через соединение
vrdeviceconnected_event_connection.disconnect();

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

	// Обработчик события VrDeviceConnected, реализованный как член класса
	void event_handler(device_id)
	{
		Log::message("\Обработка события VrDeviceConnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventVrDeviceConnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId vrdeviceconnected_handler_id;

// подписываемся на событие VrDeviceConnected с лямбда-обработчиком, сохраняя идентификатор соединения
vrdeviceconnected_handler_id = Input::getEventVrDeviceConnected().connect(e_connections, [](device_id) {
		Log::message("\Обработка события VrDeviceConnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventVrDeviceConnected().disconnect(vrdeviceconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий VrDeviceConnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventVrDeviceConnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventVrDeviceConnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int, int> getEventGamepadTouchMotion () const

Событие, срабатывающее при перемещении пальца по сенсорной панели геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**gamepad_id**, int **touch_id**, int **finger**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadTouchMotion
void gamepadtouchmotion_event_handler(gamepad_id,  int touch_id,  int finger)
{
	Log::message("\Обработка события GamepadTouchMotion\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepadtouchmotion_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadTouchMotion().connect(gamepadtouchmotion_event_connections, gamepadtouchmotion_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadTouchMotion().connect(gamepadtouchmotion_event_connections, [](gamepad_id,  int touch_id,  int finger) {
		Log::message("\Обработка события GamepadTouchMotion (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepadtouchmotion_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepadtouchmotion_event_connection;

// подписываемся на событие GamepadTouchMotion с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadTouchMotion().connect(gamepadtouchmotion_event_connection, gamepadtouchmotion_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepadtouchmotion_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepadtouchmotion_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadTouchMotion через соединение
gamepadtouchmotion_event_connection.disconnect();

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

	// Обработчик события GamepadTouchMotion, реализованный как член класса
	void event_handler(gamepad_id,  int touch_id,  int finger)
	{
		Log::message("\Обработка события GamepadTouchMotion\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadTouchMotion().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepadtouchmotion_handler_id;

// подписываемся на событие GamepadTouchMotion с лямбда-обработчиком, сохраняя идентификатор соединения
gamepadtouchmotion_handler_id = Input::getEventGamepadTouchMotion().connect(e_connections, [](gamepad_id,  int touch_id,  int finger) {
		Log::message("\Обработка события GamepadTouchMotion (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadTouchMotion().disconnect(gamepadtouchmotion_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadTouchMotion при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadTouchMotion().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadTouchMotion().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int, int> getEventGamepadTouchUp () const

Событие, срабатывающее при снятии касания с сенсорной панели геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**gamepad_id**, int **touch_id**, int **finger**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadTouchUp
void gamepadtouchup_event_handler(gamepad_id,  int touch_id,  int finger)
{
	Log::message("\Обработка события GamepadTouchUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepadtouchup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadTouchUp().connect(gamepadtouchup_event_connections, gamepadtouchup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadTouchUp().connect(gamepadtouchup_event_connections, [](gamepad_id,  int touch_id,  int finger) {
		Log::message("\Обработка события GamepadTouchUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepadtouchup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepadtouchup_event_connection;

// подписываемся на событие GamepadTouchUp с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadTouchUp().connect(gamepadtouchup_event_connection, gamepadtouchup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepadtouchup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepadtouchup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadTouchUp через соединение
gamepadtouchup_event_connection.disconnect();

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

	// Обработчик события GamepadTouchUp, реализованный как член класса
	void event_handler(gamepad_id,  int touch_id,  int finger)
	{
		Log::message("\Обработка события GamepadTouchUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadTouchUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepadtouchup_handler_id;

// подписываемся на событие GamepadTouchUp с лямбда-обработчиком, сохраняя идентификатор соединения
gamepadtouchup_handler_id = Input::getEventGamepadTouchUp().connect(e_connections, [](gamepad_id,  int touch_id,  int finger) {
		Log::message("\Обработка события GamepadTouchUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadTouchUp().disconnect(gamepadtouchup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadTouchUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadTouchUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadTouchUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int, int> getEventGamepadTouchDown () const

Событие, срабатывающее при касании сенсорной панели геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**gamepad_id**, int **touch_id**, int **finger**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadTouchDown
void gamepadtouchdown_event_handler(gamepad_id,  int touch_id,  int finger)
{
	Log::message("\Обработка события GamepadTouchDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepadtouchdown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadTouchDown().connect(gamepadtouchdown_event_connections, gamepadtouchdown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadTouchDown().connect(gamepadtouchdown_event_connections, [](gamepad_id,  int touch_id,  int finger) {
		Log::message("\Обработка события GamepadTouchDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepadtouchdown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepadtouchdown_event_connection;

// подписываемся на событие GamepadTouchDown с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadTouchDown().connect(gamepadtouchdown_event_connection, gamepadtouchdown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepadtouchdown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepadtouchdown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadTouchDown через соединение
gamepadtouchdown_event_connection.disconnect();

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

	// Обработчик события GamepadTouchDown, реализованный как член класса
	void event_handler(gamepad_id,  int touch_id,  int finger)
	{
		Log::message("\Обработка события GamepadTouchDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadTouchDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepadtouchdown_handler_id;

// подписываемся на событие GamepadTouchDown с лямбда-обработчиком, сохраняя идентификатор соединения
gamepadtouchdown_handler_id = Input::getEventGamepadTouchDown().connect(e_connections, [](gamepad_id,  int touch_id,  int finger) {
		Log::message("\Обработка события GamepadTouchDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadTouchDown().disconnect(gamepadtouchdown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadTouchDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadTouchDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadTouchDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, Input::GAMEPAD_AXIS > getEventGamepadAxisMotion () const

Событие, срабатывающее при изменении значения состояния оси геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **gamepad_id**, Input::GAMEPAD_AXIS **axis**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadAxisMotion
void gamepadaxismotion_event_handler(int gamepad_id,  Input::GAMEPAD_AXIS axis)
{
	Log::message("\Обработка события GamepadAxisMotion\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepadaxismotion_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadAxisMotion().connect(gamepadaxismotion_event_connections, gamepadaxismotion_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadAxisMotion().connect(gamepadaxismotion_event_connections, [](int gamepad_id,  Input::GAMEPAD_AXIS axis) {
		Log::message("\Обработка события GamepadAxisMotion (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepadaxismotion_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepadaxismotion_event_connection;

// подписываемся на событие GamepadAxisMotion с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadAxisMotion().connect(gamepadaxismotion_event_connection, gamepadaxismotion_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepadaxismotion_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepadaxismotion_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadAxisMotion через соединение
gamepadaxismotion_event_connection.disconnect();

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

	// Обработчик события GamepadAxisMotion, реализованный как член класса
	void event_handler(int gamepad_id,  Input::GAMEPAD_AXIS axis)
	{
		Log::message("\Обработка события GamepadAxisMotion\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadAxisMotion().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepadaxismotion_handler_id;

// подписываемся на событие GamepadAxisMotion с лямбда-обработчиком, сохраняя идентификатор соединения
gamepadaxismotion_handler_id = Input::getEventGamepadAxisMotion().connect(e_connections, [](int gamepad_id,  Input::GAMEPAD_AXIS axis) {
		Log::message("\Обработка события GamepadAxisMotion (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadAxisMotion().disconnect(gamepadaxismotion_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadAxisMotion при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadAxisMotion().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadAxisMotion().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, Input::GAMEPAD_BUTTON > getEventGamepadButtonUp () const

Событие, срабатывающее при отпускании кнопки геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **gamepad_id**, Input::GAMEPAD_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadButtonUp
void gamepadbuttonup_event_handler(int gamepad_id,  Input::GAMEPAD_BUTTON button)
{
	Log::message("\Обработка события GamepadButtonUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepadbuttonup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadButtonUp().connect(gamepadbuttonup_event_connections, gamepadbuttonup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadButtonUp().connect(gamepadbuttonup_event_connections, [](int gamepad_id,  Input::GAMEPAD_BUTTON button) {
		Log::message("\Обработка события GamepadButtonUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepadbuttonup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepadbuttonup_event_connection;

// подписываемся на событие GamepadButtonUp с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadButtonUp().connect(gamepadbuttonup_event_connection, gamepadbuttonup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepadbuttonup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepadbuttonup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadButtonUp через соединение
gamepadbuttonup_event_connection.disconnect();

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

	// Обработчик события GamepadButtonUp, реализованный как член класса
	void event_handler(int gamepad_id,  Input::GAMEPAD_BUTTON button)
	{
		Log::message("\Обработка события GamepadButtonUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadButtonUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepadbuttonup_handler_id;

// подписываемся на событие GamepadButtonUp с лямбда-обработчиком, сохраняя идентификатор соединения
gamepadbuttonup_handler_id = Input::getEventGamepadButtonUp().connect(e_connections, [](int gamepad_id,  Input::GAMEPAD_BUTTON button) {
		Log::message("\Обработка события GamepadButtonUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadButtonUp().disconnect(gamepadbuttonup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadButtonUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadButtonUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadButtonUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, Input::GAMEPAD_BUTTON > getEventGamepadButtonDown () const

Событие, срабатывающее при нажатии кнопки геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(int **gamepad_id**, Input::GAMEPAD_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadButtonDown
void gamepadbuttondown_event_handler(int gamepad_id,  Input::GAMEPAD_BUTTON button)
{
	Log::message("\Обработка события GamepadButtonDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepadbuttondown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadButtonDown().connect(gamepadbuttondown_event_connections, gamepadbuttondown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadButtonDown().connect(gamepadbuttondown_event_connections, [](int gamepad_id,  Input::GAMEPAD_BUTTON button) {
		Log::message("\Обработка события GamepadButtonDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepadbuttondown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepadbuttondown_event_connection;

// подписываемся на событие GamepadButtonDown с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadButtonDown().connect(gamepadbuttondown_event_connection, gamepadbuttondown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepadbuttondown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepadbuttondown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadButtonDown через соединение
gamepadbuttondown_event_connection.disconnect();

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

	// Обработчик события GamepadButtonDown, реализованный как член класса
	void event_handler(int gamepad_id,  Input::GAMEPAD_BUTTON button)
	{
		Log::message("\Обработка события GamepadButtonDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadButtonDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepadbuttondown_handler_id;

// подписываемся на событие GamepadButtonDown с лямбда-обработчиком, сохраняя идентификатор соединения
gamepadbuttondown_handler_id = Input::getEventGamepadButtonDown().connect(e_connections, [](int gamepad_id,  Input::GAMEPAD_BUTTON button) {
		Log::message("\Обработка события GamepadButtonDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadButtonDown().disconnect(gamepadbuttondown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadButtonDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadButtonDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadButtonDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventGamepadDisconnected () const

Событие, срабатывающее при отключении геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**gamepad_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadDisconnected
void gamepaddisconnected_event_handler(gamepad_id)
{
	Log::message("\Обработка события GamepadDisconnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepaddisconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadDisconnected().connect(gamepaddisconnected_event_connections, gamepaddisconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadDisconnected().connect(gamepaddisconnected_event_connections, [](gamepad_id) {
		Log::message("\Обработка события GamepadDisconnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepaddisconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepaddisconnected_event_connection;

// подписываемся на событие GamepadDisconnected с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadDisconnected().connect(gamepaddisconnected_event_connection, gamepaddisconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepaddisconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepaddisconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadDisconnected через соединение
gamepaddisconnected_event_connection.disconnect();

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

	// Обработчик события GamepadDisconnected, реализованный как член класса
	void event_handler(gamepad_id)
	{
		Log::message("\Обработка события GamepadDisconnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadDisconnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepaddisconnected_handler_id;

// подписываемся на событие GamepadDisconnected с лямбда-обработчиком, сохраняя идентификатор соединения
gamepaddisconnected_handler_id = Input::getEventGamepadDisconnected().connect(e_connections, [](gamepad_id) {
		Log::message("\Обработка события GamepadDisconnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadDisconnected().disconnect(gamepaddisconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadDisconnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadDisconnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadDisconnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventGamepadConnected () const

Событие, срабатывающее при подключении геймпада. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**gamepad_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события GamepadConnected
void gamepadconnected_event_handler(gamepad_id)
{
	Log::message("\Обработка события GamepadConnected\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections gamepadconnected_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventGamepadConnected().connect(gamepadconnected_event_connections, gamepadconnected_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventGamepadConnected().connect(gamepadconnected_event_connections, [](gamepad_id) {
		Log::message("\Обработка события GamepadConnected (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
gamepadconnected_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection gamepadconnected_event_connection;

// подписываемся на событие GamepadConnected с функцией-обработчиком, сохраняя соединение
Input::getEventGamepadConnected().connect(gamepadconnected_event_connection, gamepadconnected_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
gamepadconnected_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
gamepadconnected_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие GamepadConnected через соединение
gamepadconnected_event_connection.disconnect();

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

	// Обработчик события GamepadConnected, реализованный как член класса
	void event_handler(gamepad_id)
	{
		Log::message("\Обработка события GamepadConnected\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventGamepadConnected().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId gamepadconnected_handler_id;

// подписываемся на событие GamepadConnected с лямбда-обработчиком, сохраняя идентификатор соединения
gamepadconnected_handler_id = Input::getEventGamepadConnected().connect(e_connections, [](gamepad_id) {
		Log::message("\Обработка события GamepadConnected (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventGamepadConnected().disconnect(gamepadconnected_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий GamepadConnected при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventGamepadConnected().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventGamepadConnected().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventTouchMotion () const

Событие, срабатывающее при перемещении касания. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**touch_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TouchMotion
void touchmotion_event_handler(touch_id)
{
	Log::message("\Обработка события TouchMotion\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections touchmotion_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventTouchMotion().connect(touchmotion_event_connections, touchmotion_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventTouchMotion().connect(touchmotion_event_connections, [](touch_id) {
		Log::message("\Обработка события TouchMotion (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
touchmotion_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection touchmotion_event_connection;

// подписываемся на событие TouchMotion с функцией-обработчиком, сохраняя соединение
Input::getEventTouchMotion().connect(touchmotion_event_connection, touchmotion_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
touchmotion_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
touchmotion_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TouchMotion через соединение
touchmotion_event_connection.disconnect();

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

	// Обработчик события TouchMotion, реализованный как член класса
	void event_handler(touch_id)
	{
		Log::message("\Обработка события TouchMotion\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventTouchMotion().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId touchmotion_handler_id;

// подписываемся на событие TouchMotion с лямбда-обработчиком, сохраняя идентификатор соединения
touchmotion_handler_id = Input::getEventTouchMotion().connect(e_connections, [](touch_id) {
		Log::message("\Обработка события TouchMotion (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventTouchMotion().disconnect(touchmotion_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TouchMotion при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventTouchMotion().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventTouchMotion().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventTouchUp () const

Событие, срабатывающее при снятии касания. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**touch_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TouchUp
void touchup_event_handler(touch_id)
{
	Log::message("\Обработка события TouchUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections touchup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventTouchUp().connect(touchup_event_connections, touchup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventTouchUp().connect(touchup_event_connections, [](touch_id) {
		Log::message("\Обработка события TouchUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
touchup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection touchup_event_connection;

// подписываемся на событие TouchUp с функцией-обработчиком, сохраняя соединение
Input::getEventTouchUp().connect(touchup_event_connection, touchup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
touchup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
touchup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TouchUp через соединение
touchup_event_connection.disconnect();

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

	// Обработчик события TouchUp, реализованный как член класса
	void event_handler(touch_id)
	{
		Log::message("\Обработка события TouchUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventTouchUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId touchup_handler_id;

// подписываемся на событие TouchUp с лямбда-обработчиком, сохраняя идентификатор соединения
touchup_handler_id = Input::getEventTouchUp().connect(e_connections, [](touch_id) {
		Log::message("\Обработка события TouchUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventTouchUp().disconnect(touchup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TouchUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventTouchUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventTouchUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventTouchDown () const

Событие, срабатывающее при касании. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**touch_id**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TouchDown
void touchdown_event_handler(touch_id)
{
	Log::message("\Обработка события TouchDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections touchdown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventTouchDown().connect(touchdown_event_connections, touchdown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventTouchDown().connect(touchdown_event_connections, [](touch_id) {
		Log::message("\Обработка события TouchDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
touchdown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection touchdown_event_connection;

// подписываемся на событие TouchDown с функцией-обработчиком, сохраняя соединение
Input::getEventTouchDown().connect(touchdown_event_connection, touchdown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
touchdown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
touchdown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TouchDown через соединение
touchdown_event_connection.disconnect();

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

	// Обработчик события TouchDown, реализованный как член класса
	void event_handler(touch_id)
	{
		Log::message("\Обработка события TouchDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventTouchDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId touchdown_handler_id;

// подписываемся на событие TouchDown с лямбда-обработчиком, сохраняя идентификатор соединения
touchdown_handler_id = Input::getEventTouchDown().connect(e_connections, [](touch_id) {
		Log::message("\Обработка события TouchDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventTouchDown().disconnect(touchdown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TouchDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventTouchDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventTouchDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<unsigned int> getEventTextPress () const

Событие, срабатывающее при нажатии клавиши, имеющей соответствующий печатаемый символ. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(unsigned int **unicode**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события TextPress
void textpress_event_handler(unsigned int unicode)
{
	Log::message("\Обработка события TextPress\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections textpress_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventTextPress().connect(textpress_event_connections, textpress_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventTextPress().connect(textpress_event_connections, [](unsigned int unicode) {
		Log::message("\Обработка события TextPress (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
textpress_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection textpress_event_connection;

// подписываемся на событие TextPress с функцией-обработчиком, сохраняя соединение
Input::getEventTextPress().connect(textpress_event_connection, textpress_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
textpress_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
textpress_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие TextPress через соединение
textpress_event_connection.disconnect();

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

	// Обработчик события TextPress, реализованный как член класса
	void event_handler(unsigned int unicode)
	{
		Log::message("\Обработка события TextPress\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventTextPress().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId textpress_handler_id;

// подписываемся на событие TextPress с лямбда-обработчиком, сохраняя идентификатор соединения
textpress_handler_id = Input::getEventTextPress().connect(e_connections, [](unsigned int unicode) {
		Log::message("\Обработка события TextPress (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventTextPress().disconnect(textpress_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий TextPress при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventTextPress().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventTextPress().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<unsigned int> getEventKeyRepeat () const

Событие, срабатывающее при повторном нажатии клавиши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(unsigned int **unicode**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события KeyRepeat
void keyrepeat_event_handler(unsigned int unicode)
{
	Log::message("\Обработка события KeyRepeat\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections keyrepeat_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventKeyRepeat().connect(keyrepeat_event_connections, keyrepeat_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventKeyRepeat().connect(keyrepeat_event_connections, [](unsigned int unicode) {
		Log::message("\Обработка события KeyRepeat (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
keyrepeat_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection keyrepeat_event_connection;

// подписываемся на событие KeyRepeat с функцией-обработчиком, сохраняя соединение
Input::getEventKeyRepeat().connect(keyrepeat_event_connection, keyrepeat_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
keyrepeat_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
keyrepeat_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие KeyRepeat через соединение
keyrepeat_event_connection.disconnect();

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

	// Обработчик события KeyRepeat, реализованный как член класса
	void event_handler(unsigned int unicode)
	{
		Log::message("\Обработка события KeyRepeat\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventKeyRepeat().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId keyrepeat_handler_id;

// подписываемся на событие KeyRepeat с лямбда-обработчиком, сохраняя идентификатор соединения
keyrepeat_handler_id = Input::getEventKeyRepeat().connect(e_connections, [](unsigned int unicode) {
		Log::message("\Обработка события KeyRepeat (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventKeyRepeat().disconnect(keyrepeat_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий KeyRepeat при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventKeyRepeat().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventKeyRepeat().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event< Input::KEY > getEventKeyUp () const

Событие, срабатывающее при отпускании клавиши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(Input::KEY **key**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события KeyUp
void keyup_event_handler(Input::KEY key)
{
	Log::message("\Обработка события KeyUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections keyup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventKeyUp().connect(keyup_event_connections, keyup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventKeyUp().connect(keyup_event_connections, [](Input::KEY key) {
		Log::message("\Обработка события KeyUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
keyup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection keyup_event_connection;

// подписываемся на событие KeyUp с функцией-обработчиком, сохраняя соединение
Input::getEventKeyUp().connect(keyup_event_connection, keyup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
keyup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
keyup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие KeyUp через соединение
keyup_event_connection.disconnect();

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

	// Обработчик события KeyUp, реализованный как член класса
	void event_handler(Input::KEY key)
	{
		Log::message("\Обработка события KeyUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventKeyUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId keyup_handler_id;

// подписываемся на событие KeyUp с лямбда-обработчиком, сохраняя идентификатор соединения
keyup_handler_id = Input::getEventKeyUp().connect(e_connections, [](Input::KEY key) {
		Log::message("\Обработка события KeyUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventKeyUp().disconnect(keyup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий KeyUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventKeyUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventKeyUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event< Input::KEY > getEventKeyDown () const

Событие, срабатывающее при нажатии и удержании клавиши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(Input::KEY **key**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события KeyDown
void keydown_event_handler(Input::KEY key)
{
	Log::message("\Обработка события KeyDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections keydown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventKeyDown().connect(keydown_event_connections, keydown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventKeyDown().connect(keydown_event_connections, [](Input::KEY key) {
		Log::message("\Обработка события KeyDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
keydown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection keydown_event_connection;

// подписываемся на событие KeyDown с функцией-обработчиком, сохраняя соединение
Input::getEventKeyDown().connect(keydown_event_connection, keydown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
keydown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
keydown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие KeyDown через соединение
keydown_event_connection.disconnect();

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

	// Обработчик события KeyDown, реализованный как член класса
	void event_handler(Input::KEY key)
	{
		Log::message("\Обработка события KeyDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventKeyDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId keydown_handler_id;

// подписываемся на событие KeyDown с лямбда-обработчиком, сохраняя идентификатор соединения
keydown_handler_id = Input::getEventKeyDown().connect(e_connections, [](Input::KEY key) {
		Log::message("\Обработка события KeyDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventKeyDown().disconnect(keydown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий KeyDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventKeyDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventKeyDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int, int> getEventMouseMotion () const

Событие, срабатывающее при перемещении мыши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**coord_x**, int **coord_y**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события MouseMotion
void mousemotion_event_handler(coord_x, int coord_y)
{
	Log::message("\Обработка события MouseMotion\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections mousemotion_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventMouseMotion().connect(mousemotion_event_connections, mousemotion_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventMouseMotion().connect(mousemotion_event_connections, [](coord_x, int coord_y) {
		Log::message("\Обработка события MouseMotion (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
mousemotion_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection mousemotion_event_connection;

// подписываемся на событие MouseMotion с функцией-обработчиком, сохраняя соединение
Input::getEventMouseMotion().connect(mousemotion_event_connection, mousemotion_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
mousemotion_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
mousemotion_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие MouseMotion через соединение
mousemotion_event_connection.disconnect();

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

	// Обработчик события MouseMotion, реализованный как член класса
	void event_handler(coord_x, int coord_y)
	{
		Log::message("\Обработка события MouseMotion\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventMouseMotion().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId mousemotion_handler_id;

// подписываемся на событие MouseMotion с лямбда-обработчиком, сохраняя идентификатор соединения
mousemotion_handler_id = Input::getEventMouseMotion().connect(e_connections, [](coord_x, int coord_y) {
		Log::message("\Обработка события MouseMotion (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventMouseMotion().disconnect(mousemotion_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий MouseMotion при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventMouseMotion().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventMouseMotion().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventMouseWheelHorizontal () const

Событие, срабатывающее при горизонтальной прокрутке колеса мыши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**delta_horizontal**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события MouseWheelHorizontal
void mousewheelhorizontal_event_handler(delta_horizontal)
{
	Log::message("\Обработка события MouseWheelHorizontal\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections mousewheelhorizontal_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventMouseWheelHorizontal().connect(mousewheelhorizontal_event_connections, mousewheelhorizontal_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventMouseWheelHorizontal().connect(mousewheelhorizontal_event_connections, [](delta_horizontal) {
		Log::message("\Обработка события MouseWheelHorizontal (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
mousewheelhorizontal_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection mousewheelhorizontal_event_connection;

// подписываемся на событие MouseWheelHorizontal с функцией-обработчиком, сохраняя соединение
Input::getEventMouseWheelHorizontal().connect(mousewheelhorizontal_event_connection, mousewheelhorizontal_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
mousewheelhorizontal_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
mousewheelhorizontal_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие MouseWheelHorizontal через соединение
mousewheelhorizontal_event_connection.disconnect();

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

	// Обработчик события MouseWheelHorizontal, реализованный как член класса
	void event_handler(delta_horizontal)
	{
		Log::message("\Обработка события MouseWheelHorizontal\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventMouseWheelHorizontal().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId mousewheelhorizontal_handler_id;

// подписываемся на событие MouseWheelHorizontal с лямбда-обработчиком, сохраняя идентификатор соединения
mousewheelhorizontal_handler_id = Input::getEventMouseWheelHorizontal().connect(e_connections, [](delta_horizontal) {
		Log::message("\Обработка события MouseWheelHorizontal (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventMouseWheelHorizontal().disconnect(mousewheelhorizontal_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий MouseWheelHorizontal при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventMouseWheelHorizontal().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventMouseWheelHorizontal().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event<int> getEventMouseWheel () const

Событие, срабатывающее при прокрутке колеса мыши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(**delta_vertical**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события MouseWheel
void mousewheel_event_handler(delta_vertical)
{
	Log::message("\Обработка события MouseWheel\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections mousewheel_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventMouseWheel().connect(mousewheel_event_connections, mousewheel_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventMouseWheel().connect(mousewheel_event_connections, [](delta_vertical) {
		Log::message("\Обработка события MouseWheel (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
mousewheel_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection mousewheel_event_connection;

// подписываемся на событие MouseWheel с функцией-обработчиком, сохраняя соединение
Input::getEventMouseWheel().connect(mousewheel_event_connection, mousewheel_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
mousewheel_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
mousewheel_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие MouseWheel через соединение
mousewheel_event_connection.disconnect();

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

	// Обработчик события MouseWheel, реализованный как член класса
	void event_handler(delta_vertical)
	{
		Log::message("\Обработка события MouseWheel\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventMouseWheel().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId mousewheel_handler_id;

// подписываемся на событие MouseWheel с лямбда-обработчиком, сохраняя идентификатор соединения
mousewheel_handler_id = Input::getEventMouseWheel().connect(e_connections, [](delta_vertical) {
		Log::message("\Обработка события MouseWheel (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventMouseWheel().disconnect(mousewheel_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий MouseWheel при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventMouseWheel().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventMouseWheel().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event< Input::MOUSE_BUTTON > getEventMouseUp () const

Событие, срабатывающее при отпускании кнопки мыши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(Input::MOUSE_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события MouseUp
void mouseup_event_handler(Input::MOUSE_BUTTON button)
{
	Log::message("\Обработка события MouseUp\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections mouseup_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventMouseUp().connect(mouseup_event_connections, mouseup_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventMouseUp().connect(mouseup_event_connections, [](Input::MOUSE_BUTTON button) {
		Log::message("\Обработка события MouseUp (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
mouseup_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection mouseup_event_connection;

// подписываемся на событие MouseUp с функцией-обработчиком, сохраняя соединение
Input::getEventMouseUp().connect(mouseup_event_connection, mouseup_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
mouseup_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
mouseup_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие MouseUp через соединение
mouseup_event_connection.disconnect();

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

	// Обработчик события MouseUp, реализованный как член класса
	void event_handler(Input::MOUSE_BUTTON button)
	{
		Log::message("\Обработка события MouseUp\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventMouseUp().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId mouseup_handler_id;

// подписываемся на событие MouseUp с лямбда-обработчиком, сохраняя идентификатор соединения
mouseup_handler_id = Input::getEventMouseUp().connect(e_connections, [](Input::MOUSE_BUTTON button) {
		Log::message("\Обработка события MouseUp (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventMouseUp().disconnect(mouseup_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий MouseUp при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventMouseUp().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventMouseUp().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
## static Event< Input::MOUSE_BUTTON > getEventMouseDown () const

Событие, срабатывающее при нажатии кнопки мыши. Вы можете подписываться на события через *connect()* и отписываться через *disconnect()*. Также для удобства можно использовать классы *[EventConnection](../../../api/library/common/events/class.eventconnection_cpp.md)* и *[EventConnections](../../../api/library/common/events/class.eventconnections_cpp.md)* (см. примеры ниже).

> **Notice:** Подробнее см. статью [Event Handling](../../../code/fundamentals/events/index_cpp.md).

 Сигнатура обработчика события выглядит следующим образом: *myhandler(Input::MOUSE_BUTTON **button**)*
<details>
<summary>Показать пример | Скрыть</summary>

**Пример использования**

```cpp
// реализация обработчика события MouseDown
void mousedown_event_handler(Input::MOUSE_BUTTON button)
{
	Log::message("\Обработка события MouseDown\n");
}

//////////////////////////////////////////////////////////////////////////////
//  1. Несколько подписок можно связать с экземпляром класса EventConnections,
//  который затем можно использовать для отмены всех этих подписок сразу
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnections
EventConnections mousedown_event_connections;

// связываем с этим экземпляром при подписке на событие (можно связывать подписки на разные события)
Input::getEventMouseDown().connect(mousedown_event_connections, mousedown_event_handler);

// другие подписки также связаны с этим экземпляром EventConnections
// (например, можно подписываться с помощью лямбда-функций)
Input::getEventMouseDown().connect(mousedown_event_connections, [](Input::MOUSE_BUTTON button) {
		Log::message("\Обработка события MouseDown (лямбда).\n");
	}
);

// ...

// позже все эти связанные подписки можно удалить одной строкой
mousedown_event_connections.disconnectAll();

//////////////////////////////////////////////////////////////////////////////
//  2. Можно подписываться и отписываться через экземпляр класса EventConnection.
//  А также включать и отключать это конкретное соединение при необходимости.
//////////////////////////////////////////////////////////////////////////////

// создаём экземпляр класса EventConnection
EventConnection mousedown_event_connection;

// подписываемся на событие MouseDown с функцией-обработчиком, сохраняя соединение
Input::getEventMouseDown().connect(mousedown_event_connection, mousedown_event_handler);

// ...

// можно временно отключить конкретное соединение события для выполнения определённых действий
mousedown_event_connection.setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
mousedown_event_connection.setEnabled(true);

// ...

// удаляем подписку на событие MouseDown через соединение
mousedown_event_connection.disconnect();

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

	// Обработчик события MouseDown, реализованный как член класса
	void event_handler(Input::MOUSE_BUTTON button)
	{
		Log::message("\Обработка события MouseDown\n");
		// ...
	}
};

SomeClass *sc = new SomeClass();

// ...

// указываем экземпляр класса, если метод-обработчик принадлежит какому-либо классу
Input::getEventMouseDown().connect(sc->e_connections, sc, &SomeClass::event_handler);

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
EventConnectionId mousedown_handler_id;

// подписываемся на событие MouseDown с лямбда-обработчиком, сохраняя идентификатор соединения
mousedown_handler_id = Input::getEventMouseDown().connect(e_connections, [](Input::MOUSE_BUTTON button) {
		Log::message("\Обработка события MouseDown (лямбда).\n");
	}
);

// удаляем подписку позже, используя идентификатор
Input::getEventMouseDown().disconnect(mousedown_handler_id);

//////////////////////////////////////////////////////////////////////////////
//   5. Игнорирование всех событий MouseDown при необходимости
//////////////////////////////////////////////////////////////////////////////

// можно временно отключить событие для выполнения определённых действий без его срабатывания
Input::getEventMouseDown().setEnabled(false);

// ... выполняемые действия

// и снова включить его при необходимости
Input::getEventMouseDown().setEnabled(true);

```

</details>

### Возвращаемое значение

Ссылка на событие.
---

## Ptr < InputGamePad > getGamePad ( int num ) const

Возвращает геймпад с заданным индексом.
### Аргументы

- *int* **num** - Индекс геймпада.

### Возвращаемое значение

Объект [InputGamepad](../../../api/library/controls/class.inputgamepad_cpp.md).
## Ptr < InputJoystick > getJoystick ( int num ) const

Возвращает джойстик с заданным индексом.
### Аргументы

- *int* **num** - Индекс джойстика.

### Возвращаемое значение

Объект [InputJoystick](../../../api/library/controls/class.inputjoystick_cpp.md).
## bool isKeyPressed ( Input::KEY key ) const

Возвращает значение, указывающее, нажата ли заданная клавиша. Проверяйте это значение для выполнения непрерывных действий.
```cpp
if (Input::isKeyPressed(Input::KEY_ENTER)) {
	Log::message("the Enter key is held down\n");
}

```


### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

true, если клавиша нажата; иначе false.
## bool isKeyDown ( Input::KEY key ) const

Возвращает значение, указывающее, была ли заданная клавиша нажата в течение текущего кадра. Проверяйте это значение для выполнения одноразовых действий при нажатии клавиши.
```cpp
if (Input::isKeyDown(Input::KEY_SPACE)) {
	Log::message("the Space key was pressed\n");
}

```


### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

1 в течение первого кадра, когда клавиша была нажата, 0 в последующих кадрах, пока она не будет отпущена и нажата снова.
## bool isKeyUp ( Input::KEY key ) const

Возвращает значение, указывающее, была ли заданная клавиша отпущена в течение текущего кадра. Проверяйте это значение для выполнения одноразовых действий при отпускании клавиши.
```cpp
if (Input::isKeyUp(Input::KEY_F)) {
	Log::message("the F key was released\n");
}

```


### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

true в течение первого кадра, когда клавиша была отпущена; иначе false.
## bool isMouseButtonPressed ( Input::MOUSE_BUTTON button ) const

Возвращает значение, указывающее, нажата ли заданная кнопка мыши. Проверяйте это значение для выполнения непрерывных действий.
```cpp
if (Input::isMouseButtonPressed(Input::MOUSE_BUTTON_LEFT)) {
	Log::message("the left mouse button is held down\n");
}

```


### Аргументы

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Один из предустановленных кодов [MOUSE_BUTTON_](#MOUSE_BUTTON).

### Возвращаемое значение

1, если кнопка мыши нажата; иначе 0.
## bool isMouseButtonDown ( Input::MOUSE_BUTTON button ) const

Возвращает значение, указывающее, была ли заданная кнопка мыши нажата в течение текущего кадра. Проверяйте это значение для выполнения одноразовых действий при нажатии кнопки мыши.
```cpp
if (Input::isMouseButtonDown(Input::MOUSE_BUTTON_LEFT)) {
	Log::message("the left mouse button was pressed\n");
}

```


### Аргументы

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Один из предустановленных кодов [MOUSE_BUTTON_](#MOUSE_BUTTON).

### Возвращаемое значение

1 в течение первого кадра, когда кнопка мыши была нажата; иначе 0.
## bool isMouseButtonUp ( Input::MOUSE_BUTTON button ) const

Возвращает значение, указывающее, была ли заданная кнопка мыши отпущена в течение текущего кадра. Проверяйте это значение для выполнения одноразовых действий при отпускании кнопки мыши.
```cpp
if (Input::isMouseButtonUp(Input::MOUSE_BUTTON_LEFT)) {
	Log::message("the left mouse button was released\n");
}

```


### Аргументы

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Один из предустановленных кодов [MOUSE_BUTTON_](#MOUSE_BUTTON).

### Возвращаемое значение

1 в течение первого кадра, когда кнопка мыши была отпущена; иначе 0.
## bool isTouchPressed ( int index ) const

Возвращает значение, указывающее, нажат ли сенсорный экран пальцем.
### Аргументы

- *int* **index** - Индекс сенсорного ввода.

### Возвращаемое значение

true, если сенсорный экран нажат; иначе false.
## bool isTouchDown ( int index ) const

Возвращает значение, указывающее, было ли заданное касание нажато в течение текущего кадра.
### Аргументы

- *int* **index** - Индекс сенсорного ввода.

### Возвращаемое значение

true, если сенсорный экран нажат в течение текущего кадра; иначе false.
## bool isTouchUp ( int index ) const

Возвращает значение, указывающее, было ли заданное касание отпущено.
### Аргументы

- *int* **index** - Индекс сенсорного ввода.

### Возвращаемое значение

true в течение первого кадра, когда касание было отпущено; иначе false.
## Math:: ivec2 getTouchPosition ( int index ) const

Возвращает вектор, содержащий целочисленные значения позиции касания.
### Аргументы

- *int* **index** - Индекс сенсорного ввода.

### Возвращаемое значение

Позиция касания.
## Math:: ivec2 getTouchDelta ( int index ) const

Возвращает вектор, содержащий изменение экранной позиции касания по осям X и Y — разницу между значениями в предыдущем и текущем кадрах.
### Аргументы

- *int* **index** - Индекс сенсорного ввода.

### Возвращаемое значение

Изменение позиции касания.
## Ptr < InputEventTouch > getTouchEvent ( int index )

Возвращает действие, приведённое к событию касания.
### Аргументы

- *int* **index** - Индекс сенсорного ввода.

### Возвращаемое значение

Событие сенсорного ввода.
## int getTouchEvents ( int index , Vector < Ptr < InputEventTouch >> & OUT_events )

Возвращает действия, приведённые к событию касания.
### Аргументы

- *int* **index** - Индекс сенсорного ввода.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEventTouch](../../../api/library/controls/class.inputeventtouch_cpp.md)>> &* **OUT_events** - Буфер с событиями сенсорного ввода. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

Количество событий сенсорного ввода.
## Ptr < InputEventKeyboard > getKeyEvent ( Input::KEY key )

Возвращает текущее обрабатываемое событие ввода с клавиатуры.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

Событие ввода с клавиатуры, или nullptr, если для указанной клавиши нет событий в текущем кадре.
## int getKeyEvents ( Input::KEY key , Vector < Ptr < InputEventKeyboard >> & OUT_events )

Возвращает буфер с событиями для указанной клавиши.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEventKeyboard](../../../api/library/controls/class.inputeventkeyboard_cpp.md)>> &* **OUT_events** - Буфер с событиями ввода. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## const char * getKeyName ( Input::KEY key ) const

Возвращает имя указанной клавиши.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

Имя клавиши.
## Input::KEY getKeyByName ( const char * name ) const

Возвращает клавишу по её имени.
### Аргументы

- *const char ** **name** - Имя клавиши.

### Возвращаемое значение

Один из предустановленных кодов [KEY_](#KEY).
## Ptr < InputEventMouseButton > getMouseButtonEvent ( Input::MOUSE_BUTTON button )

Возвращает событие движения мыши для указанной кнопки.
### Аргументы

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Один из предустановленных кодов [MOUSE_BUTTON_](#MOUSE_BUTTON).

### Возвращаемое значение

Событие движения мыши.
## const char * getMouseButtonName ( Input::MOUSE_BUTTON button ) const

Возвращает имя кнопки мыши.
### Аргументы

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Один из предустановленных кодов [MOUSE_BUTTON_](#MOUSE_BUTTON).

### Возвращаемое значение

Имя кнопки мыши.
## Input::MOUSE_BUTTON getMouseButtonByName ( const char * name ) const

Возвращает кнопку мыши по её имени.
### Аргументы

- *const char ** **name** - Имя кнопки мыши.

### Возвращаемое значение

Один из предустановленных кодов [MOUSE_BUTTON_](#MOUSE_BUTTON).
## int getEventsBuffer ( int frame , Vector < Ptr < InputEvent >> & OUT_events ) const

Возвращает буфер с событиями ввода для указанного кадра.
### Аргументы

- *int* **frame** - Номер кадра, для которого требуется получить буфер событий ввода. События ввода хранятся за последние 60 кадров. 0 — текущий кадр, 1 — предыдущий кадр и т.д.
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEvent](../../../api/library/controls/class.inputevent_cpp.md)>> &* **OUT_events** - Буфер с событиями ввода. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

## void sendEvent ( const Ptr < InputEvent > & e )

Создаёт пользовательское событие и передаёт его движку.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEvent](../../../api/library/controls/class.inputevent_cpp.md)> &* **e** - Событие ввода.

## void setEventsFilter ( int (*)(const Ptr < InputEvent > &) func )

Устанавливает функцию обратного вызова, выполняемую при получении событий ввода. Этот фильтр событий ввода позволяет отклонять определённые события ввода для движка и получать необходимую информацию обо всех событиях ввода.
### Аргументы

- *int (*)(const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEvent](../../../api/library/controls/class.inputevent_cpp.md)> &)* **func** - Функция обратного вызова для события ввода.

## bool isModifierEnabled ( Input::MODIFIER modifier ) const

Возвращает значение, указывающее, включён ли заданный модификатор.
### Аргументы

- *[Input::MODIFIER](../../../api/library/controls/class.input_cpp.md#MODIFIER)* **modifier** - Один из предустановленных кодов [MODIFIER_](#MODIFIER_LEFT_SHIFT).

### Возвращаемое значение

true, если модификатор включён; иначе false.
## unsigned int keyToUnicode ( Input::KEY key ) const

Возвращает заданную клавишу, преобразованную в unicode.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

Символ unicode.
## Input::KEY unicodeToKey ( unsigned int unicode ) const

Возвращает заданную клавишу, преобразованную в unicode.
### Аргументы

- *unsigned int* **unicode** - Символ unicode.

### Возвращаемое значение

Один из предустановленных кодов [KEY_](#KEY).
## void setMouseCursorSkinCustom ( const Ptr < Image > & image )

Устанавливает пользовательское изображение для курсора мыши.
### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Изображение, содержащее формы указателя, устанавливаемые для курсора мыши (например, выбор, перемещение, изменение размера и т.д.).

## void setMouseCursorSkinSystem ( )

Устанавливает текущий системный скин курсора ОС (формы указателя, такие как выбор, перемещение, изменение размера и т.д.).
## void setMouseCursorSkinDefault ( )

Устанавливает скин курсора движка по умолчанию (формы указателя, такие как выбор, перемещение, изменение размера и т.д.).
## void setMouseCursorCustom ( const Ptr < Image > & image , int x = 0 , int y = 0 )

Устанавливает пользовательское изображение для системного курсора мыши. Изображение должно иметь квадратный размер и формат *RGBA8*.
```cpp
// create an instance of the Image class
ImagePtr cursor = Image::create("textures/my_cursor.png");
// set the image as the mouse cursor
Input::setMouseCursorCustom(cursor);
// show the OS mouse pointer
Input::setMouseCursorSystem(1);

```


### Аргументы

- *const [Ptr](../../../api/library/common/class.ptr_cpp.md)<[Image](../../../api/library/common/class.image_cpp.md)> &* **image** - Устанавливаемое изображение курсора.
- *int* **x** - Координата X горячей точки курсора.
- *int* **y** - Координата Y горячей точки курсора.

## void clearMouseCursorCustom ( )

Очищает пользовательский курсор мыши, установленный методом [setMouseCursorCustom()](#setMouseCursorCustom_Image_int_int_void).
## void updateMouseCursor ( )

Обновляет курсор мыши. Этот метод следует вызывать после внесения изменений в курсор мыши, чтобы применить их все вместе. После вызова этого метода курсор будет обновлён в следующем кадре.
## const char * getKeyLocalName ( Input::KEY key ) const

Возвращает имя заданной клавиши, взятое из текущей выбранной раскладки клавиатуры.
> **Notice:** На возвращаемое значение влияет модификатор, такой как Shift.


### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

Локализованное имя заданной клавиши.
## int getMouseButtonEvents ( Input::MOUSE_BUTTON button , Vector < Ptr < InputEventMouseButton >> & OUT_events )

Возвращает количество событий ввода для указанной кнопки мыши и помещает события в указанный выходной буфер.
### Аргументы

- *[Input::MOUSE_BUTTON](../../../api/library/controls/class.input_cpp.md#MOUSE_BUTTON)* **button** - Один из предустановленных кодов [MOUSE_BUTTON_](#MOUSE_BUTTON).
- *[Vector](../../../api/library/containers/vector/class.vector_cpp.md)<[Ptr](../../../api/library/common/class.ptr_cpp.md)<[InputEventMouseButton](../../../api/library/controls/class.inputeventmousebutton_cpp.md)>> &* **OUT_events** - Буфер с событиями ввода. > **Notice:** Этот выходной буфер должен быть заполнен движком в результате выполнения метода.

### Возвращаемое значение

Количество событий ввода для указанной кнопки мыши.
## Math:: ivec2 getForceMousePosition ( )

Возвращает абсолютную позицию мыши, полученную от ОС.
### Возвращаемое значение

Абсолютная позиция мыши.
## bool isKeyText ( Input::KEY key ) const

Возвращает значение, указывающее, имеет ли заданная клавиша соответствующий печатаемый символ (учитывается текущее состояние Num Lock). Например, нажатие 2 на цифровой клавиатуре с включённым *Num Lock* даёт "2", а с выключенным *Num Lock* та же клавиша действует как стрелка вниз. Клавиши вроде *Esc, PrintScreen, BackSpace* вообще не производят печатаемого символа.
### Аргументы

- *[Input::KEY](../../../api/library/controls/class.input_cpp.md#KEY)* **key** - Один из предустановленных кодов [KEY_](#KEY).

### Возвращаемое значение

true, если значение клавиши является символом; иначе false.
## const char * getModifierName ( Input::MODIFIER modifier ) const

Возвращает имя модификатора клавиши по его скан-коду.
### Аргументы

- *[Input::MODIFIER](../../../api/library/controls/class.input_cpp.md#MODIFIER)* **modifier** - Скан-код модификатора.

### Возвращаемое значение

Имя модификатора клавиши.
## Input::MODIFIER getModifierByName ( const char * name ) const

Возвращает скан-код модификатора клавиши по его имени.
### Аргументы

- *const char ** **name** - Имя модификатора клавиши.

### Возвращаемое значение

Скан-код модификатора.
## Ptr < InputVRDevice > getVRDevice ( int num ) const

Возвращает VR-устройство по его номеру.
### Аргументы

- *int* **num** - Номер VR-устройства.

### Возвращаемое значение

VR-устройство.
