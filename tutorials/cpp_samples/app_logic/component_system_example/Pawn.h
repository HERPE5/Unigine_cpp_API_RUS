#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineControls.h>
#include <UnigineGame.h>

// Управляемая игроком сущность со здоровьем, движением и обратной связью при получении урона.
// Демонстрирует PROP_PARAM для предоставления переменных в редакторе,
// а также эффекты визуальной обратной связи (тряска экрана, вспышка цвета при уроне).
class Pawn : public Unigine::ComponentBase
{
public:
	// Макросы компонента
	COMPONENT(Pawn, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Имя свойства
	PROP_NAME("pawn");

	// Параметры
	PROP_PARAM(String, name, "Pawn1");    // отображаемое имя пешки
	PROP_PARAM(Int, health, 200);         // очки здоровья
	PROP_PARAM(Float, move_speed, 4.0f);  // скорость движения (метров/с)
	PROP_PARAM(Float, turn_speed, 90.0f); // скорость поворота (град/с)

	// Методы
	void hit(int damage); // применяет урон и запускает визуальную обратную связь

protected:
	// Главный цикл мира
	void init();
	void update();
	void shutdown();

private:
	Unigine::ControlsPtr controls;
	Unigine::PlayerPtr player;

	float damage_effect_timer;
	Unigine::Math::Mat4 default_model_view;

	void show_damage_effect();
};
