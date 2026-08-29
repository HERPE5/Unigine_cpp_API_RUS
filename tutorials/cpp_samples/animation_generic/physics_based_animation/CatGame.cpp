// Реализует простую игру, в которой игрок должен держать лазерную указку подальше от кота.
// Сложность увеличивается со временем за счёт наращивания жёсткости и демпфирования пружины,
// делая кота быстрее и отзывчивее. Игра заканчивается, когда кот ловит лазер.

#include "CatGame.h"

#include "Laser.h"
#include "SpringRegular.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(CatGame);

using namespace Unigine;
using namespace Math;

// Создаются элементы GUI игрового режима и добавляются в окно примера.
void CatGame::initGUI(const Unigine::WidgetWindowPtr &window)
{
	game_box = WidgetGroupBox::create("Game", 8, 4);
	game_label = WidgetLabel::create(
		String::format("Don't let the cat catch the laser pointer!\nTime: %.2f", timer));
	game_label->setFontVSpacing(4);
	game_box->addChild(game_label, Gui::ALIGN_LEFT);
	window->addChild(game_box, Gui::ALIGN_LEFT);
}

// Ссылки на компоненты Laser и SpringRegular получаются из свойств-узлов.
void CatGame::init()
{
	laser_component = ComponentSystem::get()->getComponent<Laser>(laserNode.get());
	if (!laser_component)
		Log::error("CatGame::init(): cannot find Laser component!\n");
	cat_mode = ComponentSystem::get()->getComponent<SpringRegular>(catMode.get());
	if (!cat_mode)
		Log::error("CatGame::init(): cannot find SpringRegular component!\n");
}

// Вызывается при активации игрового режима. Состояние игры сбрасывается, движение кота включается.
void CatGame::on_enable()
{
	catched = false;
	cat_mode->setEnabled(1);
	timer = 0;
	game_box->setHidden(false);
}

// Вызывается при деактивации игрового режима. Движение кота отключается, управление лазером восстанавливается.
void CatGame::on_disable()
{
	cat_mode->setEnabled(0);
	laser_component->setEnabled(1);
	game_box->setHidden(true);
}

// Обновляется состояние игры: обрабатывается либо активный геймплей, либо экран завершения игры.
void CatGame::update()
{
	catched ? update_gameover() : update_game();
}

// Обрабатывается активный геймплей: увеличивается сложность и проверяется условие поимки.
void CatGame::update_game()
{
	timer += Game::getIFps();

	// Увеличиваем сложность со временем: кот становится быстрее и отзывчивее.
	// Жёсткость определяет, насколько быстро пружина стремится к цели.
	// Демпфирование определяет затухание колебаний (выше = меньше "пружинистости").
	cat_mode->setStiffness(cat_mode->getStiffness() + Game::getIFps() * 2.0f);
	cat_mode->setDamping(cat_mode->getDamping() + Game::getIFps() * 0.25f);

	// Проверяем, поймал ли кот лазер (пружина закончила колебания у цели)
	catched = cat_mode->getFinished();
	if (catched)
		laser_component->setEnabled(0);

	game_label->setText(
		String::format("Don't let the cat catch the laser pointer!\nTime: %.2f", timer));
}

// Обрабатывается состояние завершения игры. Перезапуск доступен по клавише Enter.
void CatGame::update_gameover()
{
	// Игра перезапускается при нажатии клавиши Enter
	if (Input::isKeyDown(Input::KEY_ENTER))
	{
		catched = false;
		timer = 0;
		cat_mode->RefreshSpring();
		laser_component->setEnabled(1);
	}

	game_label->setText(String::format("GAME OVER! Press Enter to restart\nTime: %.2f", timer));
}

void CatGame::shutdown()
{
	shutdown_gui();
}

// Виджеты GUI освобождаются через deleteLater для безопасного отложенного уничтожения.
void CatGame::shutdown_gui()
{
	game_label.deleteLater();
	game_box.deleteLater();
}