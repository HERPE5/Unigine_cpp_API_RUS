// Система частиц GPU с использованием вычислительных шейдеров. 1 млн частиц симулируется на
// GPU с позицией/скоростью, хранящейся в текстурах. Частицы перетекают между
// формами целевых мешей с использованием мировых позиций из UV-развёртки и пинг-понг буферов.

#pragma once

#include <UnigineComponentSystem.h>

// Симуляция частиц с ускорением GPU с целями морфинга мешей.
class ComputeShader : public Unigine::ComponentBase
{
	COMPONENT_DEFINE(ComputeShader, ComponentBase)

	// Материал с вычислительным шейдером для симуляции физики частиц
	PROP_PARAM(Material, particles_solver_material)
	// Материал для преобразования UV меша в мировые позиции
	PROP_PARAM(Material, uv_to_position_material)
	// Материал для рендеринга частиц (точечные спрайты)
	PROP_PARAM(Material, gpu_particles_material)

	// Ресурсы мешей, между которыми будут перетекать частицы
	PROP_ARRAY(File, meshes)
	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)

private:
	void init();
	void update();

	void create_resources();		// Создаёт GPU-текстуры, если ещё не выделены
	void init_particles_data();		// Заполняет текстуры начальными случайными позициями
	void destroy_resources();		// Освобождает GPU-ресурсы при завершении работы

private:
	float time{0.f};
	bool particles_initialized{false};

	// ObjectDynamic рендерит частицы как точечные примитивы
	Unigine::ObjectDynamicPtr dynamic;

	// Меши, используемые как цели морфинга для позиций частиц
	Unigine::Vector<Unigine::ObjectMeshStaticPtr> static_meshes;

	// Пинг-понг буферы: [0] = цель записи, [1] = источник чтения
	Unigine::VectorStack<Unigine::TexturePtr, 2> velocity_texture;
	Unigine::VectorStack<Unigine::TexturePtr, 2> position_texture;

	// Хранит мировые позиции из UV-развёртки меша
	Unigine::TexturePtr uv_position_texture;

	Unigine::RenderTargetPtr render_target;
};
