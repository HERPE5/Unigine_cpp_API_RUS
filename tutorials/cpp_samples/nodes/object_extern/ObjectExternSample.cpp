// Демонстрирует ObjectExtern для создания пользовательских отрисовываемых объектов с пользовательской
// геометрией и рендерингом. В отличие от NodeExtern, ObjectExtern поддерживает поверхности, материалы
// и участвует в конвейере рендеринга. Пользовательские объекты могут определять собственную
// геометрию с помощью Fixed Function Pipeline (Ffp) или пользовательских шейдеров.

#include <UnigineComponentSystem.h>
#include <UnigineFfp.h>
#include <UnigineMathLib.h>
#include <UnigineObjects.h>
#include <UnigineVisualizer.h>
#include <UnigineGame.h>

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/Utils.h"

using namespace Unigine;
using namespace Math;

// Пользовательский отрисовываемый объект, наследуемый от ObjectExternBase
class MyObject : public ObjectExternBase
{
public:
	// Уникальный идентификатор этого типа объекта
	static constexpr int id = 2;

	// Конструктор по умолчанию для программного создания
	MyObject()
	{
		Log::message("MyObject::MyObject(): called\n");
	}

	// Конструктор фабрики, вызываемый ObjectExtern::create()
	MyObject(void *node): ObjectExternBase(node)
	{
		Log::message("MyObject::MyObject(void*): called\n");
	}

	~MyObject() override
	{
		Log::message("MyObject::~MyObject(): called\n");
	}

	int getClassID() override { return id; }

	// Интерфейс поверхности: определяет, сколько материалов можно назначить
	int getNumSurfaces() override { return 1; }
	const char *getSurfaceName(int surface) override { return "surface"; }

	// Ограничивающие объёмы для каждой поверхности для оптимизации отсечения
	const Math::BoundBox &getBoundBox(int surface) override { return bbox; }
	const Math::BoundSphere &getBoundSphere(int surface) override { return bsphere; }

	// Ограничивающие объёмы на уровне объекта (объединение всех поверхностей)
	const BoundBox &getBoundBox() override { return bbox; }
	const BoundSphere &getBoundSphere() override { return bsphere; }

	// Включаем рендеринг для этого объекта
	bool hasRender() override { return true; }

	// Пользовательский callback рендеринга, вызываемый в конвейере рендеринга
	void render(Render::PASS pass, int surface) override
	{
		// Рендерим только во время ambient-прохода (пропускаем тени, глубину и т.д.)
		if (pass != Render::PASS_AMBIENT)
			return;

		// Настраиваем состояние шейдера для этого объекта/поверхности
		ObjectPtr object = getObject();
		Renderer::setShaderParameters(pass, object, surface, false);

		// Устанавливаем пользовательский параметр шейдера (определён в материале)
		ShaderPtr shader = RenderState::getShader();
		shader->setParameterFloat4("extern_color", color);
		shader->flushParameters();

		// Строим геометрию куба с помощью Fixed Function Pipeline
		Ffp::beginTriangles();

		vec3 half_size = bbox.getSize() * .5f;

		// Определяем 8 вершин куба
		Ffp::addVertex(-half_size.x, -half_size.y, -half_size.z);
		Ffp::addVertex(half_size.x, -half_size.y, -half_size.z);
		Ffp::addVertex(-half_size.x, half_size.y, -half_size.z);
		Ffp::addVertex(half_size.x, half_size.y, -half_size.z);
		Ffp::addVertex(-half_size.x, -half_size.y, half_size.z);
		Ffp::addVertex(half_size.x, -half_size.y, half_size.z);
		Ffp::addVertex(-half_size.x, half_size.y, half_size.z);
		Ffp::addVertex(half_size.x, half_size.y, half_size.z);

		// Определяем 12 треугольников (по 2 на грань, 6 граней)
		// Нижняя грань
		Ffp::addIndices(0, 3, 1);
		Ffp::addIndices(3, 0, 2);
		// Верхняя грань
		Ffp::addIndices(6, 5, 7);
		Ffp::addIndices(5, 6, 4);
		// Задняя грань
		Ffp::addIndices(2, 7, 3);
		Ffp::addIndices(7, 2, 6);
		// Передняя грань
		Ffp::addIndices(1, 4, 0);
		Ffp::addIndices(4, 1, 5);
		// Правая грань
		Ffp::addIndices(3, 5, 1);
		Ffp::addIndices(5, 3, 7);
		// Левая грань
		Ffp::addIndices(0, 6, 2);
		Ffp::addIndices(6, 0, 4);

		Ffp::endTriangles();
	}

	// Пользовательский метод для установки цвета рендеринга
	void setColor(const vec4 &color)
	{
		this->color = color;
	}

private:
	// Ограничивающий объём единичного куба
	BoundBox bbox = BoundBox(vec3(-.5f), vec3(.5f));
	// Ограничивающая сфера для быстрого отсечения по фрустуму
	BoundSphere bsphere = BoundSphere(vec3(0.f), 1.f);
	// Цвет, передаваемый пользовательскому шейдеру
	vec4 color = vec4_white;
};

class ObjectExternSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(ObjectExternSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init()
	{
		// Регистрируем пользовательский тип объекта в фабрике
		ObjectExternBase::addClassID<MyObject>(MyObject::id);

		if (true)
		{
			// Создание через фабрику движка (рекомендуется)
			ObjectExternPtr object_extern = ObjectExtern::create(MyObject::id);
			ObjectExternBase *object_extern_base = object_extern->getObjectExtern();
			if (object_extern_base)
			{
				my_object = static_cast<MyObject *>(object_extern_base);
			}
		}

		else
		{
			// Прямое создание экземпляра (требует ручной очистки)
			my_object = new MyObject();
		}

		if (my_object)
		{
			// Доступ к стандартным методам Object через getObject()
			my_object->getObject()->setWorldPosition(Vec3(0.f, 0.f, 1.f));

			// Присоединяем физическое тело для физических взаимодействий
			{
				BodyRigidPtr body = BodyRigid::create();
				// Создаём коробчатую форму, соответствующую границам объекта
				ShapePtr shape = ShapeBox::create(my_object->getBoundBox().getSize());
				body->addShape(shape);
				my_object->getObject()->setBody(body);
			}

			// Назначаем пользовательский материал, определяющий параметр "extern_color"
			my_object->getObject()->setMaterialFilePath(joinPaths(getWorldRootPath(), "materials", "object_extern.basemat"), "surface");

			// Используем пользовательский метод для установки цвета рендеринга
			my_object->setColor(vec4_white);
		}

		visualizer_enabled = Visualizer::isEnabled();
		Visualizer::setEnabled(true);
	}

	void update()
	{
		// Рендеринг обрабатывается автоматически через callback render()
	}

	void shutdown()
	{
		Visualizer::setEnabled(visualizer_enabled);
	}

	// ========================================================================================

	bool visualizer_enabled = false;
	// Указатель на пользовательский объект (принадлежит ObjectExtern)
	MyObject *my_object = nullptr;
};

REGISTER_COMPONENT(ObjectExternSample);
