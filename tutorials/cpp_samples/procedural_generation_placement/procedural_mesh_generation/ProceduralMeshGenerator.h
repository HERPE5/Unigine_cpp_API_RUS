#pragma once

#include "../../menu_ui/SampleDescriptionWindow.h"

#include <UnigineComponentSystem.h>

// Демонстрирует асинхронную процедурную генерацию мешей для больших сеток объектов.
// Объекты создаются массово с помощью runGenerateMeshProceduralAsync, который строит
// данные меша в фоновых потоках. Сравнивает три процедурных режима (Dynamic, File, Blob)
// и отслеживает использование RAM/VRAM через атомарные счётчики для потокобезопасной статистики.
class ProceduralMeshGenerator : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ProceduralMeshGenerator, Unigine::ComponentBase);
	COMPONENT_DESCRIPTION("This component demonstrates procedural mesh generation and object management with async updates");

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void shutdown();

	void create_objects();
	void create_mesh(Unigine::MeshPtr mesh);
	void create_done(Unigine::ObjectMeshStaticPtr obj);

	void clear_objects();

	void update_stats();

	void init_gui();
	void shutdown_gui();

	void set_gui_enabled(bool enabled);
	void on_generate_button();
	void on_clear_button();

private:
	// Размер сетки и количество объектов
	int size = 128;
	int new_size;
	int num_objects;

	// Расстояние между объектами
	float offset = 0.5f;

	// Используем атомарные переменные, так как эти параметры
	// изменяются несколькими асинхронными потоками
	Unigine::AtomicInt64 dynamic_ram = 0;
	Unigine::AtomicInt64 dynamic_vram = 0;
	Unigine::AtomicInt64 num_created_objects = 0;

	// Состояние генерации
	bool is_creating_objects = false;
	bool is_deleting_done = false;

	// Сгенерированные объекты
	Unigine::Vector<Unigine::ObjectMeshStaticPtr> box_objects;

	// Процедурный режим и флаг использования MeshRender
	Unigine::ObjectMeshStatic::PROCEDURAL_MODE current_mode;
	Unigine::ObjectMeshStatic::PROCEDURAL_MODE last_mode;
	int current_mesh_render_flag;

	// UI примера с описанием и элементами управления
	SampleDescriptionWindow sample_description_window;

	Unigine::Map<Unigine::String, Unigine::ObjectMeshStatic::PROCEDURAL_MODE> modes_map;
	Unigine::Map<Unigine::String, int> flags_map;

	Unigine::WidgetComboBoxPtr mode_combo;
	Unigine::WidgetComboBoxPtr flags_combo;

	Unigine::WidgetEditLinePtr editline;
	Unigine::WidgetSpinBoxPtr spinbox;

	Unigine::WidgetButtonPtr generate_button;
	Unigine::WidgetButtonPtr clear_button;
};
