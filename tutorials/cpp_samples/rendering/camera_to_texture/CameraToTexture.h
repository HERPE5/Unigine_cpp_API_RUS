// Рендерит сцену из отдельной камеры в закадровую текстуру.
// Камера игрока рендерится каждый кадр с использованием выделенного вьюпорта,
// и результирующую текстуру можно применить к любому материалу.

#pragma once

#include <UnigineComponentSystem.h>
#include <UniginePlayers.h>
#include <UnigineViewport.h>
#include <UnigineWidgets.h>

// Захватывает обзор камеры игрока в отрисовываемую текстуру каждый кадр
// и назначает её текстурой albedo материала прикреплённого объекта.
class CameraToTexture : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CameraToTexture, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Игрок, чей обзор камеры рендерится в текстуру
	PROP_PARAM(Node, player_camera, "", "", "", "filter=Player");

private:
	void init();
	void update();

private:
	Unigine::PlayerPtr player;
	// Текстура render target, получающая вывод камеры
	Unigine::TexturePtr texture;
	// Выделенный вьюпорт для закадрового рендеринга
	Unigine::ViewportPtr viewport;
};
