// Управляемая игроком пешка со здоровьем и движением. Использует состояния Controls для ввода
// (работает с клавиатурой, геймпадом или пользовательскими привязками). Урон запускает визуальную обратную связь:
// красный оверлей экрана через Render::setFadeColor и тряску камеры через матрицу Modelview.

#include "Pawn.h"

#include <UnigineConsole.h>
#include <UnigineRender.h>

REGISTER_COMPONENT(Pawn);

#define DAMAGE_EFFECT_TIME 0.5f

using namespace Unigine;
using namespace Math;

// Ссылка на игрока и controls кешируются, эффект урона инициализируется.
void Pawn::init()
{
	player = Game::getPlayer();
	controls = player->getControls();

	default_model_view = player->getCamera()->getModelview();
	damage_effect_timer = 0;
	show_damage_effect();

	Log::message("PAWN: INIT \"%s\"\n", name.get());
}

// Движение обрабатывается на основе состояний управления, эффект урона обновляется.
void Pawn::update()
{
	// Получаем время между кадрами
	float ifps = Game::getIFps();

	// Показываем эффект урона
	if (damage_effect_timer > 0)
	{
		damage_effect_timer = Math::clamp(damage_effect_timer - ifps, 0.0f, DAMAGE_EFFECT_TIME);
		show_damage_effect();
	}

	// Если консоль открыта, всё управление отключено
	if (Console::isActive())
		return;

	// Получаем вектор направления меша из второго столбца (ось Y) матрицы
	// трансформации
	Vec3 direction = node->getWorldTransform().getColumn3(1);

	// Проверяем состояния управления и изменяем позицию и вращение пешки
	if (controls->getState(Controls::STATE_FORWARD) || controls->getState(Controls::STATE_TURN_UP))
		node->setWorldPosition(node->getWorldPosition() + direction * move_speed * ifps);

	if (controls->getState(Controls::STATE_BACKWARD)
		|| controls->getState(Controls::STATE_TURN_DOWN))
		node->setWorldPosition(node->getWorldPosition() - direction * move_speed * ifps);

	if (controls->getState(Controls::STATE_MOVE_LEFT)
		|| controls->getState(Controls::STATE_TURN_LEFT))
		node->setWorldRotation(node->getWorldRotation() * quat(0.0f, 0.0f, turn_speed * ifps));

	if (controls->getState(Controls::STATE_MOVE_RIGHT)
		|| controls->getState(Controls::STATE_TURN_RIGHT))
		node->setWorldRotation(node->getWorldRotation() * quat(0.0f, 0.0f, -turn_speed * ifps));
}

// Уничтожение пешки логируется.
void Pawn::shutdown()
{
	Log::message("PAWN: DEAD!\n");
}

// Урон применяется к здоровью, запускается визуальный эффект, узел уничтожается при обнулении здоровья.
void Pawn::hit(int damage)
{
	// Получаем урон
	health = health - damage;

	// Показываем эффект
	damage_effect_timer = DAMAGE_EFFECT_TIME;
	show_damage_effect();

	// Уничтожаем
	if (health <= 0)
		node.deleteLater();

	Log::message("PAWN: damage taken (%d) - HP left (%d)\n", damage, health.get());
}

// Красный оверлей и тряска камеры применяются на основе оставшегося таймера эффекта.
void Pawn::show_damage_effect()
{
	// Визуальная обратная связь урона: красный оверлей экрана + тряска камеры.
	// Сила эффекта уменьшается со временем (damage_effect_timer отсчитывает вниз).
	float strength = damage_effect_timer / DAMAGE_EFFECT_TIME;
	Render::setFadeColor(vec4(0.5f, 0, 0, saturate(strength - 0.5f)));
	// Применяем случайное вращение к камере для эффекта тряски
	player->getCamera()->setModelview(default_model_view
		* Mat4(rotateX(Game::getRandomFloat(-5, 5) * strength)
			* rotateY(Game::getRandomFloat(-5, 5) * strength)));
}
