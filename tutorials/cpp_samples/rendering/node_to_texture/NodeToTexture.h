// Рендерит одиночный узел в закадровую текстуру с использованием пользовательского вьюпорта.
// Узел рендерится с указанной позиции камеры, и результат
// применяется к материалу объекта для отображения в мире.

#pragma once

#include <UnigineComponentSystem.h>
#include <UniginePlayers.h>
#include <UnigineViewport.h>
#include <UnigineWidgets.h>

// Захватывает изолированный рендеринг узла в текстуру для превью или миниатюр.
class NodeToTexture : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(NodeToTexture, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Камера, используемая для рендеринга узла
	PROP_PARAM(Node, player_camera, "", "", "", "filter=Player");
	// Целевой узел для рендеринга в текстуру
	PROP_PARAM(Node, node_to_render);
	// Объект, который будет отображать отрендеренную текстуру
	PROP_PARAM(Node, object_view, "", "", "", "filter=Object");

private:
	void init();
	void update();

private:
	Unigine::PlayerPtr player;
	// Текстура render target, получающая изображение узла
	Unigine::TexturePtr texture;
	// Текстура окружения для отражений в закадровом рендере
	Unigine::TexturePtr env_texture;
	// Выделенный вьюпорт для рендеринга одиночного узла
	Unigine::ViewportPtr viewport;
};
