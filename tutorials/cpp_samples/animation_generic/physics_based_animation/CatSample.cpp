// Основной контроллер примера с анимацией кота. Управляет двумя режимами: Demo
// (демонстрирует разные алгоритмы сглаживания) и Game (интерактивная игра в ловлю).
// Кнопки-переключатели позволяют переключаться между режимами через окно описания примера.

#include "CatSample.h"

#include "CatDemo.h"
#include "CatGame.h"

#include <UnigineWidgets.h>
#include <UnigineWindowManager.h>

#include "../../utils/Utils.h"

REGISTER_COMPONENT(CatSample);

using namespace Unigine;
using namespace Math;

// Пример инициализируется: настраивается дескриптор мыши, получаются контроллеры режимов.
void CatSample::init()
{
	// Оставляем курсор мыши видимым (режим SOFT показывает курсор, USER скрывает его)
	mouse_handle = Input::getMouseHandle();
	Input::setMouseHandle(Input::MOUSE_HANDLE_SOFT);

	// Получаем ссылки на контроллеры режимов demo и game
	game_manager = ComponentSystem::get()->getComponent<CatGame>(gameNode.get());
	if (!game_manager)
		Log::error("CatSample::init(): cannot find CatGame component!\n");

	demo_manager = ComponentSystem::get()->getComponent<CatDemo>(demoNode.get());
	if (!demo_manager)
		Log::error("CatSample::init(): cannot find CatDemo component!\n");

	init_gui();
	// Начинаем с обоих отключённых режимов, затем активируем режим demo
	demo_manager->setEnabled(0);
	game_manager->setEnabled(0);

	demo_button->setToggled(true);
}

// Создаётся GUI: инициализируются окно описания, кнопки переключения режимов и дочерние GUI.
void CatSample::init_gui()
{
	title_label = WidgetLabel::create("Move the pointer away from the cat");
	title_label->setTextAlign(Gui::ALIGN_CENTER);
	title_label->setFontSize(40);
	title_label->setFontOutline(1);
	Gui::getCurrent()->addChild(title_label, Gui::ALIGN_EXPAND);

	sample_description_window.createWindow();

	auto vbox = sample_description_window.getParameterGroupBox();

	auto hbox = WidgetHBox::create(5);
	vbox->addChild(hbox, Gui::ALIGN_BOTTOM);
	game_button = WidgetButton::create("Start Game");
	game_button->setToggleable(1);
	game_button->getEventClicked().connect(this, &CatSample::switch_to_game);
	hbox->addChild(game_button, Gui::ALIGN_LEFT);
	game_manager->initGUI(sample_description_window.getWindow());

	demo_button = WidgetButton::create("Animations Demo");
	demo_button->getEventClicked().connect(this, &CatSample::switch_to_demo);
	demo_button->setToggleable(1);
	hbox->addChild(demo_button, Gui::ALIGN_LEFT);
	demo_manager->initGUI(sample_description_window.getWindow());
}

// Режим demo отключается, режим game активируется.
void CatSample::switch_to_game()
{
	demo_manager->setEnabled(0);
	game_manager->setEnabled(1);

	// MUTE_EVENT временно отключает событие, чтобы предотвратить рекурсивный коллбэк
	// при программной установке состояния переключателя
	MUTE_EVENT(demo_button->getEventClicked());
	demo_button->setToggled(0);
}

// Режим game отключается, режим demo активируется.
void CatSample::switch_to_demo()
{
	game_manager->setEnabled(0);
	demo_manager->setEnabled(1);

	// Отключаем событие, чтобы избежать вызова switch_to_game при снятии переключения
	MUTE_EVENT(game_button->getEventClicked());
	game_button->setToggled(0);
}

// Дескриптор мыши восстанавливается, ресурсы GUI освобождаются.
void CatSample::shutdown()
{
	Input::setMouseHandle(mouse_handle);
	shutdown_gui();
}

// Виджеты GUI освобождаются через deleteLater для безопасного отложенного уничтожения.
void CatSample::shutdown_gui()
{
	title_label.deleteLater();
	demo_button.deleteLater();
	game_button.deleteLater();
	sample_description_window.shutdown();
}
