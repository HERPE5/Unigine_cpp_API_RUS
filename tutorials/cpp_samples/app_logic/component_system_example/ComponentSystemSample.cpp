// Демонстрирует использование Component System: создание узлов с компонентами во время выполнения,
// два способа прикрепления (C++ API против на основе свойств), взаимодействие между компонентами
// и корректное управление памятью (виджеты удаляются вручную, узлы удаляются автоматически).

#include "ComponentSystemSample.h"

#include "Pawn.h"
#include "Spinner.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(ComponentSystemSample);

using namespace Unigine;
using namespace Math;

// Сцена инициализируется: волчки, пешка и UI создаются и настраиваются.
void ComponentSystemSample::init()
{
	// Создаём объекты
	ObjectMeshDynamicPtr obj[4];
	obj[0] = create_box(translate(Vec3(-16.0f, 0.0f, 0.0f)), vec3(1.0f));
	obj[1] = create_box(translate(Vec3(16.0f, 0.0f, 0.0f)), vec3(1.0f));
	obj[2] = create_box(translate(Vec3(0.0f, -16.0f, 0.0f)), vec3(1.0f));
	obj[3] = create_box(translate(Vec3(0.0f, 16.0f, 0.0f)), vec3(1.0f));

	// Два способа прикрепить компоненты к узлам:
	// 1) C++ API: ComponentSystem::addComponent<T>() - типобезопасно, немедленно
	ComponentSystem::get()->addComponent<Spinner>(obj[0]);
	ComponentSystem::get()->addComponent<Spinner>(obj[1]);

	// 2) На основе свойств: добавление свойства по имени - используется для компонентов, созданных в редакторе
	obj[2]->addProperty("Spinner");
	obj[3]->setProperty(0, "Spinner");

	// Настраиваем волчки (задаём переменную "spawn_node")
	ObjectMeshDynamicPtr projectile_obj = create_box(Mat4_identity, vec3(0.15f));
	projectile_obj->setEnabled(0);
	for (int i = 0; i < 4; i++)
		ComponentSystem::get()->getComponent<Spinner>(obj[i])->spawn_node = projectile_obj;

	// Создаём игрока
	ObjectMeshDynamicPtr my_pawn_object = create_box(translate(Vec3(1.0f, 1.0f, 0.0f)),
		vec3(1.3f, 1.3f, 0.3f));
	my_pawn = ComponentSystem::get()->addComponent<Pawn>(my_pawn_object);
	my_pawn->setDestroyCallback(MakeCallback(this, &ComponentSystemSample::my_pawn_destroyed));
	time = 0;

	// Создаём информационную метку
	label = WidgetLabel::create(Gui::getCurrent());
	label->setPosition(10, 10);
	label->setFontSize(24);
	label->setFontOutline(1);
	Gui::getCurrent()->addChild(label, Gui::ALIGN_OVERLAP);
}

// Обновляется время выживания, статистика отображается в UI.
void ComponentSystemSample::update()
{
	// Увеличиваем время, пока игрок жив
	if (my_pawn)
		time += Game::getIFps();

	// Показываем информацию
	label->setText(String::format("Player:\n"
								  "Health Points: %d\n"
								  "Time: %.1f sec\n"
								  "\n"
								  "Statisics:\n"
								  "Components: %d",
		(my_pawn ? my_pawn->health.get() : 0), time, ComponentSystem::get()->getNumComponents())
			.get());
}

// Виджеты GUI освобождаются вручную (узлы удаляются автоматически при завершении работы мира).
void ComponentSystemSample::shutdown()
{
	// Узлы будут удалены автоматически при завершении работы мира,
	// но виджеты могут существовать вне мира. Их нужно удалять вручную.
	label.deleteLater();
}

// Создаёт box-меш с заданной трансформацией и размером.
Unigine::ObjectMeshDynamicPtr ComponentSystemSample::create_box(
	const Unigine::Math::Mat4 &transform, const Unigine::Math::vec3 &size)
{
	MeshPtr mesh = Mesh::create();
	mesh->addBoxSurface("box", size);

	ObjectMeshDynamicPtr object = ObjectMeshDynamic::create(1);
	object->setMesh(mesh);
	object->setWorldTransform(transform);

	return object;
}
