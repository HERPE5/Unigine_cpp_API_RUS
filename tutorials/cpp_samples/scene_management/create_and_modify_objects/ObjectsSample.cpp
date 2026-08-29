// Демонстрирует создание и манипуляцию тремя разными типами объектов:
// ObjectMeshStatic (загружается из файла), ObjectMeshDynamic (процедурный тетраэдр)
// и ObjectParticles. Показывает изменение вершин во время выполнения, присоединение
// твёрдого тела и изменение параметров материала через систему наследования материалов.

#include <UnigineComponentSystem.h>
#include <UnigineFileSystem.h>
#include <UnigineMesh.h>
#include <UniginePhysics.h>
#include <UnigineVisualizer.h>
#include <UniginePrimitives.h>
#include <UnigineObjects.h>
#include <UnigineGame.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

using namespace Unigine;
using namespace Math;

namespace
{
	// Длина ребра для процедурной геометрии тетраэдра
	constexpr float tetrahedron_edge = 1.4f;
}

class ObjectsSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(ObjectsSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_UPDATE_PHYSICS(update_physics);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init()
	{
		// Создаём каждый тип объекта, чтобы продемонстрировать разные подходы создания мешей
		create_static_mesh();
		create_dynamic_mesh();
		create_particles_object();

		// Включаем визуализатор для отладочного рендеринга поверхностей и форм
		visualizer_enabled = Visualizer::isEnabled();
		Visualizer::setEnabled(true);
		gui.init(this);
	}

	void update()
	{
		// Рендерим отладочную визуализацию поверхностей и физических форм
		visualize_objects();
	}

	void update_physics()
	{
		// Применяем начальное вращение к тетраэдру на первом физическом кадре
		if (first_frame)
		{
			if (BodyRigidPtr body = dynamic_mesh->getBodyRigid())
			{
				// Угловой импульс масштабируется тензором инерции для постоянной скорости вращения
				body->addAngularImpulse(body->getInertia() * vec3(0.f, 0.f, .5f));
			}
		}

		first_frame = false;
	}

	void shutdown()
	{
		gui.shutdown();
		// Восстанавливаем исходное состояние визуализатора
		Visualizer::setEnabled(visualizer_enabled);
	}

	void create_static_mesh()
	{
		// ObjectMeshStatic: геометрия загружается из файла меша и не может изменяться во время выполнения
		static_mesh = ObjectMeshStatic::create();

		// resolvePartialVirtualPath() находит полный путь по частичному имени файла
		static_mesh->setMeshPath(FileSystem::resolvePartialVirtualPath("material_ball.mesh"));

		// Символ подстановки "*" назначает материал всем поверхностям меша
		static_mesh->setMaterialFilePath(FileSystem::resolvePartialVirtualPath("material_ball/fbx/material_ball_mat.mat"), "*");

		{
			// Создаём физическое тело с формой бокса, соответствующей границам меша
			BoundBox bbox = static_mesh->getBoundBox();

			BodyRigidPtr body = BodyRigid::create();
			ShapeBoxPtr shape = ShapeBox::create();

			// Размер формы соответствует размерам ограничивающего бокса меша
			shape->setSize(bbox.getSize());
			// Смещение формы позиционирует её в центре ограничивающего бокса
			body->addShape(shape, translate(bbox.getCenter()));

			// Присоединяем тело к объекту для физической симуляции
			static_mesh->setBody(body);
		}

		static_mesh->setWorldPosition(Vec3(-3.0f, 0.f, 1.1f));
		static_mesh->setWorldRotation(quat(0.f, 0.f, 270.f));
	}

	void create_dynamic_mesh()
	{
		// ObjectMeshDynamic: геометрия создаётся и может изменяться во время выполнения
		// Конструируем тетраэдр - простейшую 3D-форму с четырьмя вершинами

		// USAGE_IMMUTABLE_INDICES: связность треугольников не будет меняться
		// USAGE_DYNAMIC_VERTEX: позиции вершин будут изменяться во время выполнения
		dynamic_mesh = ObjectMeshDynamic::create(ObjectMeshDynamic::USAGE_IMMUTABLE_INDICES | ObjectMeshDynamic::USAGE_DYNAMIC_VERTEX);

		// Предварительно выделяем GPU-буферы: 4 треугольника (12 индексов) и 4 вершины
		dynamic_mesh->allocateIndices(3 * 4);
		dynamic_mesh->allocateVertex(4);

		{
			// Позиции вершин тетраэдра вычислены по формулам правильного тетраэдра
			// Вершины расположены на описанной сфере с центром в начале координат
			dynamic_mesh->addVertex(vec3(0.f, - sqrtf(8.f / 9.f), -1.f / 3.f) * tetrahedron_edge * 3.f / (2.f * sqrtf(6.f)));
			dynamic_mesh->addVertex(vec3(- sqrtf(2.f / 3.f), sqrtf(2.f / 9.f), -1.f / 3.f) * tetrahedron_edge * 3.f / (2.f * sqrtf(6.f)));
			dynamic_mesh->addVertex(vec3(+ sqrtf(2.f / 3.f), sqrtf(2.f / 9.f), -1.f / 3.f) * tetrahedron_edge * 3.f / (2.f * sqrtf(6.f)));
			dynamic_mesh->addVertex(vec3(0.f, 0.f, 1.f) * tetrahedron_edge * 3.f / (2.f * sqrtf(6.f)));
		}

		{
			// UV-координаты для наложения текстуры (vec4 содержит UV0 и UV1)
			dynamic_mesh->setTexCoord(0, vec4(vec2(0.f, 0.f), vec2_zero));
			dynamic_mesh->setTexCoord(1, vec4(vec2(.33f, 0.f), vec2_zero));
			dynamic_mesh->setTexCoord(2, vec4(vec2(.66f, 0.f), vec2_zero));
			dynamic_mesh->setTexCoord(3, vec4(vec2(.5f, 1.f), vec2_zero));
		}

		{
			// Определяем связность треугольников через буфер индексов
			// Порядок обхода против часовой стрелки определяет лицевые треугольники
			// (обратные грани отсекаются и не рендерятся)

			// Нижняя грань
			dynamic_mesh->addIndex(0);
			dynamic_mesh->addIndex(1);
			dynamic_mesh->addIndex(2);

			// Три боковые грани, соединяющие основание с вершиной
			dynamic_mesh->addIndex(1);
			dynamic_mesh->addIndex(0);
			dynamic_mesh->addIndex(3);

			dynamic_mesh->addIndex(3);
			dynamic_mesh->addIndex(0);
			dynamic_mesh->addIndex(2);

			dynamic_mesh->addIndex(2);
			dynamic_mesh->addIndex(1);
			dynamic_mesh->addIndex(3);

			// Группируем всю геометрию в именованную поверхность для назначения материала
			dynamic_mesh->addSurface("surface");
		}

		// Вычисляем векторы тангенса для normal mapping (требуется после изменения вершин)
		dynamic_mesh->updateTangents();
		// Пересчитываем ограничивающий бокс для отсечения (требуется после изменения вершин)
		dynamic_mesh->updateBounds();

		// Назначаем материал по имени поверхности, а не по индексу
		dynamic_mesh->setMaterialFilePath(FileSystem::resolvePartialVirtualPath("glass_mat.mgraph"), "surface");

		{
			// Создаём физическое тело со сферической аппроксимацией тетраэдра
			BodyRigidPtr body = BodyRigid::create(dynamic_mesh);
			// Радиус описанной сферы для тетраэдра
			ShapeSpherePtr shape = ShapeSphere::create(body, sqrtf(3.f / 8.f) * tetrahedron_edge);

			// Отключаем гравитацию для эффекта парения
			body->setGravity(false);
			// Используем явную массу/инерцию вместо вычисления из формы
			body->setShapeBased(false);
			body->setInertia(mat3_identity * 60.f);
			body->setMass(60.f);
		}

		dynamic_mesh->setWorldPosition(Vec3(0.f, 3.f, 1.2f));
		dynamic_mesh->setWorldRotation(quat(0.f, 0.f, 180.f));
	}

	void create_particles_object()
	{
		// ObjectParticles: динамический эмиттер частиц для эффектов
		particles = ObjectParticles::create();

		// Включаем столкновение частиц со всеми объектами
		particles->setCollisionEnabled(true);
		particles->setCollisionMask(~0);  // Все биты установлены = столкновение со всем

		// Включаем физическое пересечение для обнаружения частиц через raycast
		particles->setPhysicsIntersectionEnabled(true);
		particles->setPhysicsIntersectionMask(~0);

		// Настраиваем параметры эмиссии
		particles->setEmitterEnabled(1);
		particles->setSpawnRate(5.0f);        // Частиц в секунду
		particles->setLife(2.0f, 0.5f);       // Базовое время жизни с разбросом

		particles->setWorldPosition(Vec3(3.f, 0.f, 1.0f));
	}

	void visualize_objects()
	{
		// Вычисляем цвета визуализации (нулевая альфа = отключено)
		vec4 surface_color = visualize_surfaces ? vec4(vec3(1.f), .66f) : vec4_zero;
		vec4 shape_color = visualize_shapes ? vec4(.97f, .9f, .356f, 1.f) : vec4_zero;

		// Лямбда для рендеринга всех поверхностей объекта с оверлеем каркаса
		auto render_surfaces = [](const ObjectPtr &object, const vec4 &color)
		{
			for (int i = 0; i < object->getNumSurfaces(); i += 1)
				Visualizer::renderObjectSurface(object, i, color);
		};

		// Лямбда для рендеринга физических форм столкновения, присоединённых к телу объекта
		auto render_shapes = [](const ObjectPtr &object, const vec4 &color)
		{
			BodyPtr body = object->getBody();
			if (body)
			{
				// У каждого тела может быть несколько форм столкновения
				for (int i = 0; i < body->getNumShapes(); i += 1)
					body->getShape(i)->renderVisualizer(color);
			}
		};

		// Применяем визуализацию ко всем созданным объектам
		render_surfaces(dynamic_mesh, surface_color);
		render_surfaces(static_mesh, surface_color);
		render_surfaces(particles, surface_color);

		render_shapes(dynamic_mesh, shape_color);
		render_shapes(static_mesh, shape_color);
		render_shapes(particles, shape_color);
	}

	void set_tetrahedron_base_relative_height(float height)
	{
		// Деформируем тетраэдр, перемещая вершины основания и сохраняя вершину неподвижной
		// Это демонстрирует изменение вершин во время выполнения

		// Преобразуем относительную высоту (-1 до 1) в мировые единицы
		height = height * tetrahedron_edge * 3.f / (2.f * sqrtf(6.f));
		// Вычисляем радиус описанной сферы для ограничения
		float circumsphere_radius = tetrahedron_edge * sqrtf(3.f / 8.f);
		// Вершины основания остаются на описанной сфере: находим радиус XY при заданном Z
		float base_radius = sqrtf(circumsphere_radius * circumsphere_radius - height * height);

		// Размещаем три вершины основания равномерно вокруг оси Z на вычисленном радиусе
		dynamic_mesh->setVertex(0, rotateZ(0.f * 360.f) * vec3(0.f, -base_radius, height));
		dynamic_mesh->setVertex(1, rotateZ(1.f /3.f * 360.f) * vec3(0.f, -base_radius, height));
		dynamic_mesh->setVertex(2, rotateZ(2.f /3.f * 360.f) * vec3(0.f, -base_radius, height));

		// flushVertex() загружает изменённые данные вершин на GPU
		// Требуется после setVertex(), чтобы изменения вступили в силу визуально
		dynamic_mesh->flushVertex();
	}

	// ========================================================================================

	struct SampleGui : public EventConnections
	{
		void init(ObjectsSample *sample)
		{
			this->sample = sample;

			sample_description_window.createWindow();

			// Ползунок для изменения цвета albedo материала во время выполнения
			sample_description_window.addFloatParameter(
				"material ball albedo brightness",
				"",
				1.f,
				0.f,
				1.f,
				[sample](float value)
				{
					// getMaterialInherit() создаёт индивидуальную копию материала при первом вызове
					for (int i = 0; i < sample->static_mesh->getNumSurfaces(); i += 1)
						sample->static_mesh->getMaterialInherit(i)->setParameterFloat4("albedo_color", vec4(vec3(value), 1.f));
				}
			);

			// Ползунок для деформации геометрии тетраэдра в реальном времени
			sample_description_window.addFloatParameter(
				"tetrahedron base height",
				"",
				-1.f / 3.f,
				-1.f,
				1.f,
				[sample](float value) {
					sample->set_tetrahedron_base_relative_height(value);
				}
			);

			// Ползунок для настройки частоты эмиссии частиц
			sample_description_window.addFloatParameter(
				"particles spawn rate",
				"",
				5.f,
				0.f,
				50.f,
				[sample](float value) {
					sample->particles->setSpawnRate(value);
				}
			);

			// Переключатель визуализации каркаса поверхностей
			sample_description_window.addBoolParameter(
				"show object surfaces",
				"",
				true,
				[sample](bool value) {
					sample->visualize_surfaces = value;
				}
			);

			// Переключатель визуализации физических форм
			sample_description_window.addBoolParameter(
				"show object body shapes",
				"",
				false,
				[sample](bool value) {
					sample->visualize_shapes = value;
				}
			);
		}

		void shutdown()
		{
			sample_description_window.shutdown();
		}

		ObjectsSample *sample = nullptr;
		SampleDescriptionWindow sample_description_window;
	};

	// ========================================================================================

	// Процедурный меш с изменяемыми данными вершин
	ObjectMeshDynamicPtr dynamic_mesh;
	// Меш на основе файла с фиксированной геометрией
	ObjectMeshStaticPtr static_mesh;
	// Эмиттер эффекта частиц
	ObjectParticlesPtr particles;

	// Сохранённое состояние визуализатора для восстановления при завершении работы
	bool visualizer_enabled = false;
	// Управляемые через UI флаги отладочной визуализации
	bool visualize_surfaces = true;
	bool visualize_shapes = false;
	// Одноразовый флаг для начального физического импульса
	bool first_frame = true;

	SampleGui gui;
};

REGISTER_COMPONENT(ObjectsSample);
