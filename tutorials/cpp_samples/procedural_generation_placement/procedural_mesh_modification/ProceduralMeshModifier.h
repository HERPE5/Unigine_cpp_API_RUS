#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Демонстрирует изменение процедурного меша в реальном времени с корректными обновлениями RAM/VRAM.
// Анимированная волновая поверхность перегенерируется каждый кадр с использованием фоновых потоков через AsyncQueue.
// Поддерживает несколько стратегий обновления: режимы применения async/force, семантику copy/move
// и опциональное ручное создание MeshRender. Синхронизация потоков осуществляется через Mutex
// и AtomicBool для безопасной координации обновлений меша между несколькими потоками.
class ProceduralMeshModifier : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ProceduralMeshModifier, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates procedural mesh generation and proper async RAM/VRAM updates");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();

	// Строит данные меша
	void update_mesh(Unigine::MeshPtr mesh);

	// Обновляет CPU-сторону меша (RAM)
	void update_ram();
	void async_update_ram();

	// Обновляет GPU-сторону MeshRender (VRAM)
	void update_vram();
	void async_update_vram();

	// Применяет обновлённый меш к объекту (учитывает режимы async/force и copy/move)
	void apply_data();

	// UI примера с описанием и элементами управления
	void init_gui();
	void shutdown_gui();

private:
	// Разрешение сетки для генерируемой геометрии.
	int size = 128;
	float isize;

	// Объект сцены и контейнеры меша
	Unigine::ObjectMeshStaticPtr object;	// Объект, получающий процедурный меш
	Unigine::MeshPtr mesh_ram;				// Данные меша на стороне CPU
	Unigine::MeshRenderPtr mesh_vram;		// Данные меша на стороне GPU

	// Параметры для координации разных потоков
	Unigine::Mutex mesh_lock;
	Unigine::AtomicBool is_deleted;

	// Текущий процедурный режим и флаги использования MeshRender
	Unigine::ObjectMeshStatic::PROCEDURAL_MODE current_mode;
	int current_mesh_render_flag;

	// Параметры, определяющие способ выполнения обновлений
	bool is_collision_enabled = false;				// Включает создание CollisionData (пространственное дерево/рёбра)
	bool is_thread_async = true;					// Включает создание данных меша в асинхронном потоке
	bool is_async_mode = true;						// Включает apply*Async вместо apply*Force
	bool is_copy_mode = true;						// Включает applyCopy* вместо applyMove*
	Unigine::AtomicBool is_meshvram_manual = false;	// Создаёт MeshRender вручную вместо использования перегрузки applyMove*
	bool updated_meshvram_manual;					// Блокирует состояние mesh_vram, чтобы предотвратить изменения во время обновлений в других потоках.

	// Предотвращает запуск нового обновления, пока выполняется предыдущее
	bool is_running = false;

	// UI примера с описанием и элементами управления
	SampleDescriptionWindow sample_description_window;

	Unigine::WidgetComboBoxPtr thread_combo;
	Unigine::WidgetComboBoxPtr async_combo;
	Unigine::WidgetComboBoxPtr move_combo;

	Unigine::Map<Unigine::String, Unigine::ObjectMeshStatic::PROCEDURAL_MODE> modes_map;
	Unigine::Map<Unigine::String, int> usage_map;
	Unigine::WidgetComboBoxPtr mode_combo;
	Unigine::WidgetComboBoxPtr usage_combo;

	Unigine::WidgetCheckBoxPtr meshvram_checkbox;

	Unigine::WidgetLabelPtr warning_label;
};
