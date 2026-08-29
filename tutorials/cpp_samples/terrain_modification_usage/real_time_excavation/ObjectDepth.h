// Рендерит буфер глубины объекта с ортографического вида сверху. Текстура глубины
// используется системой раскопки для определения того, насколько глубоко объект врезается
// в terrain в каждой позиции текселя.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>
#include <UnigineWidgets.h>
#include <UnigineViewport.h>

class ObjectDepth
{
public:
	ObjectDepth();
	// Некопируемый: ресурсы viewport и render target уникальны
	ObjectDepth(const ObjectDepth&) = delete;
	ObjectDepth& operator=(const ObjectDepth&) = delete;

	// Рендерит глубину целевого узла сверху в предоставленную текстуру
	// pos/size определяют ограничивающий бокс в мировом пространстве, resolution — размер текстуры
	void renderDepthTexture(
		Unigine::TexturePtr &tex,
		const Unigine::NodePtr &target,
		const Unigine::Math::Vec3 &pos,
		const Unigine::Math::Vec3 &size,
		const Unigine::Math::ivec2 &resolution
	);

private:
	// Callback, вызываемый в конце прохода рендеринга viewport
	void on_end_screen();

private:
	Unigine::RenderTargetPtr render_target;
	// Выделенный viewport с режимом рендеринга только глубины
	Unigine::ViewportPtr viewport;
	// Ортографическая камера, смотрящая вниз на объект
	Unigine::CameraPtr camera;

	// Высота ограничивающего бокса для нормализации глубины в шейдере
	float bb_height{ 0.0f };
	// Минимальный Z ограничивающего бокса для восстановления мирового пространства
	float bb_min_z{0.0f};

	Unigine::EventConnection on_end_screen_connection;
	// Материал, содержащий шейдер извлечения глубины
	Unigine::MaterialPtr digging_tool_mat;
};
