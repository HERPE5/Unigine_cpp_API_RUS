// Демонстрирует процедурное создание мешей с помощью методов Mesh::add*Surface().
// Каждый тип примитива (box, sphere, cylinder, capsule, prism, plane) создаётся
// добавлением соответствующей поверхности в Mesh, а затем оборачиванием в ObjectMeshDynamic.

#include <UnigineComponentSystem.h>

using namespace Unigine;

class CreatePrimitivesSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(CreatePrimitivesSample, ComponentBase);
	COMPONENT_INIT(init);

private:
	void init()
	{
		// Создаём все типы примитивов, расставленные вдоль оси X
		create_box();
		create_sphere();
		create_cylinder();
		create_capsule();
		create_prism();
		create_plane();
	}

	void create_box()
	{
		// Объект Mesh хранит данные геометрии до того, как станет узлом сцены
		auto box_mesh = Mesh::create();

		// addBoxSurface() генерирует шестигранный бокс с заданными размерами
		// Имя поверхности используется для назначения материала
		box_mesh->addBoxSurface("box_surface", Math::vec3(1.0f, 1.0f, 1.0f));

		// ObjectMeshDynamic копирует данные меша и становится рендерящимся узлом
		auto box = ObjectMeshDynamic::create(box_mesh);
		box->setWorldPosition(Math::Vec3(-5.0f, 0.0f, 1.5f));

		// Очищаем временный Mesh; у ObjectMeshDynamic есть собственная копия
		box_mesh.clear();
	}

	void create_sphere()
	{
		auto sphere_mesh = Mesh::create();
		// Параметры: радиус, stacks (деления по широте), slices (деления по долготе)
		sphere_mesh->addSphereSurface("sphere_surface", 0.5f, 16, 16);

		auto sphere = ObjectMeshDynamic::create(sphere_mesh);
		sphere->setWorldPosition(Math::Vec3(-3.0f, 0.0f, 1.5f));

		sphere_mesh.clear();
	}

	void create_cylinder()
	{
		auto cylinderMesh = Mesh::create();
		// Параметры: радиус, высота, stacks (деления по высоте), slices (радиальные деления)
		cylinderMesh->addCylinderSurface("cylinder_surface", 0.5f, 1.0f, 16, 16);

		auto cylinder = ObjectMeshDynamic::create(cylinderMesh);
		cylinder->setWorldPosition(Math::Vec3(-1.0f, 0.0f, 1.5f));

		cylinderMesh.clear();
	}

	void create_capsule()
	{
		auto capsuleMesh = Mesh::create();
		// Капсула: цилиндр с полусферическими крышками на обоих концах
		// Параметры: радиус, высота (цилиндрической части), stacks, slices
		capsuleMesh->addCapsuleSurface("capsule_surface", 0.5f, 1.0f, 16, 16);

		auto capsule = ObjectMeshDynamic::create(capsuleMesh);
		capsule->setWorldPosition(Math::Vec3(1.0f, 0.0f, 1.5f));

		capsuleMesh.clear();
	}

	void create_prism()
	{
		auto prismMesh = Mesh::create();
		// Призма: конический цилиндр с настраиваемыми верхним/нижним радиусами
		// Параметры: нижний радиус, высота, верхний радиус, количество граней
		prismMesh->addPrismSurface("prism_surface", 0.5f, 1.0f, 0.5f, 5);

		auto prism = ObjectMeshDynamic::create(prismMesh);
		prism->setWorldPosition(Math::Vec3(3.0f, 0.0f, 1.5f));

		prismMesh.clear();
	}

	void create_plane()
	{
		auto planeMesh = Mesh::create();
		// Параметры: ширина, высота, количество подразделений по каждой оси
		// Одно подразделение создаёт простой квад
		planeMesh->addPlaneSurface("plane_surface", 1.0f, 1.0f, 1);

		auto plane = ObjectMeshDynamic::create(planeMesh);
		plane->setWorldPosition(Math::Vec3(5.0f, 0.0f, 1.5f));

		planeMesh.clear();
	}
};

REGISTER_COMPONENT(CreatePrimitivesSample);
