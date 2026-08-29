#pragma once

#include <UnigineComponentSystem.h>
#include <UniginePlayers.h>

class CameraShiftController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(CameraShiftController, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component modifies the camera projection to enable two-point perspective, "
				"using a dummy player for rendering while keeping the original player for input and movement.")

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Включает или отключает режим двухточечной перспективы
	UNIGINE_INLINE void setModeShiftModeEnabled(bool enabled) { shift_enabled = enabled; }

private:
	void init();
	void update();
	void shutdown();

	// Управляемый игрок
	Unigine::PlayerSpectatorPtr player;
	// Фиктивный игрок, используемый для переопределения матрицы проекции, пока ввод остаётся на реальном игроке
	Unigine::PlayerDummyPtr dummy_player;

	void post_render_callback();
	void pre_render_callback();

	// Callback-функции рендеринга: подменяют игроков до и после рендеринга
	bool shift_enabled = false;
	bool need_reset_player = false;
};
