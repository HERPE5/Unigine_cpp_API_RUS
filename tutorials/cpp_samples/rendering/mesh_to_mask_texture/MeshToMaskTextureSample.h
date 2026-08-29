// Рендерит силуэт меша в текстуру для целей маскирования или декалей.
// Демонстрирует два подхода к рендерингу: Renderer.RenderMesh (на основе камеры)
// и MeshRender.Render (ручная настройка параметров шейдера).

#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>
#include <UniginePlayers.h>
#include <UnigineViewport.h>
#include <UnigineWidgets.h>

// Рендерит меш в текстуру с использованием высокоуровневого или низкоуровневого API.
class MeshToMaskTextureSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(MeshToMaskTextureSample, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Исходный меш для рендеринга в виде силуэта
	PROP_PARAM(Node, mesh_node);
	// Плоскость отображения, показывающая отрендеренную текстуру
	PROP_PARAM(Node, object_view, "", "", "", "filter=Object");
	// Позиция камеры для рендеринга (перемещается через манипулятор)
	PROP_PARAM(Node, view_point);
	// Камера игрока, используемая в режиме Renderer.RenderMesh
	PROP_PARAM(Node, player_node);
	// Материал с пользовательским шейдером для рендеринга силуэта
	PROP_PARAM(Material, material);

private:
	void init();
	void init_gui();
	void update();
	void shutdown();

	// Параметры для ручного режима рендеринга (MeshRender.Render)
	struct RenderData
	{
		// Мировая трансформация меша
		Unigine::Math::Mat4 mesh_transform = Unigine::Math::Mat4_identity;
		// Позиция камеры для ортографической проекции
		Unigine::Math::Vec3 camera_position = Unigine::Math::Vec3_zero;
		// Границы ортографической камеры в мировых единицах
		Unigine::Math::ivec2 camera_size = Unigine::Math::ivec2(10, 10);
		// Ближняя/дальняя плоскости отсечения
		float zNear = 0.01f;
		float zFar = 25.0f;
		// Материал и проход рендеринга
		Unigine::MaterialPtr material = nullptr;
		const char *pass_name;
	};

	// Ручной режим: проекция и параметры шейдера настраиваются явно
	void renderMesh(const Unigine::MeshPtr mesh, Unigine::TexturePtr texture,
		const RenderData &data);
	// Режим камеры: использует Renderer.RenderMesh для более простой настройки
	void renderMesh(const Unigine::MeshPtr mesh, Unigine::TexturePtr texture,
		const Unigine::MaterialPtr material, const char *pass_name,
		const Unigine::Math::Mat4 mesh_transform, const Unigine::CameraPtr &camera);

private:
	// Загруженные данные меша для рендеринга
	Unigine::MeshPtr mesh_to_render;
	// Выходная текстура, отображаемая на плоскости обзора
	Unigine::TexturePtr texture;
	// Камера для режима Renderer.RenderMesh
	Unigine::PlayerDummyPtr player;
	Unigine::EventConnections ev_conns;
	// 3D-гизмо для перемещения позиции камеры
	Unigine::WidgetManipulatorTranslatorPtr manipulator;
	SampleDescriptionWindow window;
	// True = ручной режим (MeshRender.Render), False = режим камеры (Renderer.RenderMesh)
	bool is_manual = false;
};
