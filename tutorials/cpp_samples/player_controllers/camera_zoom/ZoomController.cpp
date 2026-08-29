// Реализует масштабирование камеры, синхронно регулируя FOV, масштаб дистанции рендеринга и
// чувствительность мыши. Более сильное увеличение сужает FOV, расширяя дистанции LOD
// и снижая чувствительность для стабильного прицеливания на большой дистанции.

#include "ZoomController.h"

#include "UnigineConsole.h"
#include "UnigineGame.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ZoomController);

// Значения по умолчанию захватываются из текущих настроек игрока и рендеринга.
void ZoomController::init()
{
	player = checked_ptr_cast<Player>(node);
	if (!player)
	{
		Log::error("ZoomSample::init cannot cast node to player!\n");
	}

	default_FOV = player->getFov();
	default_distance_scale = Render::getDistanceScale();
	default_sensivity = ControlsApp::getMouseSensitivity();

	// Скорость поворота доступна только для типов игрока Spectator и Actor
	if (node->getType() == Node::PLAYER_SPECTATOR)
	{
		PlayerSpectatorPtr player_spectator = checked_ptr_cast<PlayerSpectator>(node);
		default_player_turning = player_spectator->getTurning();
	}
	if (node->getType() == Node::PLAYER_ACTOR)
	{
		PlayerActorPtr player_spectator = checked_ptr_cast<PlayerActor>(node);
		default_player_turning = player_spectator->getTurning();
	}
}

// Глобальные настройки рендеринга/ввода восстанавливаются, чтобы не влиять на другие примеры.
void ZoomController::shutdown()
{
	Render::setDistanceScale(default_distance_scale);
	ControlsApp::setMouseSensitivity(default_sensivity);
}

// Направление камеры устанавливается на целевой узел.
void ZoomController::focus_on_target(NodePtr target)
{
	vec3 dir = vec3(target->getWorldPosition() - node->getWorldPosition());
	dir.normalize();
	player->setViewDirection(dir);
}

// Все зависящие от масштабирования параметры масштабируются пропорционально.
void ZoomController::udpate_zoom_factor(float zoom_factor)
{
	// FOV сужается, LOD расширяется, чувствительность снижается для стабильного прицеливания на дальней дистанции
	player->setFov(default_FOV / zoom_factor);
	Render::setDistanceScale(default_distance_scale * zoom_factor);
	ControlsApp::setMouseSensitivity(default_sensivity / zoom_factor);

	if (node->getType() == Node::PLAYER_SPECTATOR|| node->getType() == Node::PLAYER_ACTOR)
	{
		update_turning(zoom_factor);
	}
}

// Скорость поворота масштабируется для Spectator/Actor (недоступна на базовом Player).
// Проверка типа необходима, так как свойство Turning отличается в разных классах игрока.
void ZoomController::update_turning(float zoom_factor)
{
	if (node->getType() == Node::PLAYER_SPECTATOR)
	{
		PlayerSpectatorPtr player_spectator = checked_ptr_cast<PlayerSpectator>(node);
		player_spectator->setTurning(default_player_turning / zoom_factor);
	}
	if (node->getType() == Node::PLAYER_ACTOR)
	{
		PlayerActorPtr player_actor = checked_ptr_cast<PlayerActor>(node);
		player_actor->setTurning(default_player_turning / zoom_factor);
	}
}

void ZoomController::reset()
{
	udpate_zoom_factor(1);
}
