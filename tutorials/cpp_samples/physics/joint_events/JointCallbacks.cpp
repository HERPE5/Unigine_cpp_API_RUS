// Демонстрирует события разрушения соединений. Мост строится из сегментов твёрдых тел,
// соединённых шарнирными соединениями с ограничениями силы/крутящего момента. Когда нагрузка
// превышает пределы, соединения разрушаются и запускают callback-функции, изменяющие материалы.

#include "JointCallbacks.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(JointCallbacks)

// Строится разрушаемый мост с ломающимися шарнирными соединениями.
void JointCallbacks::init()
{
	auto file_path = mesh_file.get();
	if (String::isEmpty(file_path))
	{
		Log::error("JointCallbacks::init(): Mesh File parameter is empty!\n");
		return;
	}

	broken_mat = broken_materal.get();
	if (!broken_mat)
	{
		Log::error("JointCallbacks::init(): Broken Matreial parameter is empty!\n");
		return;
	}

	joint_mat = joint_materal.get();
	if (!joint_mat)
	{
		Log::error("JointCallbacks::init(): Joint Matreial parameter is empty!\n");
		return;
	}

	// Более низкие пороги позволяют телам замораживаться раньше, снижая нагрузку на CPU
	Physics::setFrozenLinearVelocity(0.1f);
	Physics::setFrozenAngularVelocity(0.1f);

	ObjectMeshStaticPtr orig_object = ObjectMeshStatic::create(file_path);

	// Тяжёлые грузы с высокой плотностью (80) упадут на мост, чтобы проверить прочность соединений
	BodyRigidPtr body = BodyRigid::create(orig_object);
	ShapeBoxPtr shape = ShapeBox::create(body, vec3(1.f));
	shape->setDensity(80.0f);
	for (int i = 0; i < 3; i++)
	{
		auto object = static_ptr_cast<ObjectMeshStatic>(orig_object->clone());
		object->setWorldTransform(translate(Vec3(3.0f * (i - 1), 0.f, 12.0f)));
		objects.append(object);
	}

	// Шаблон сбрасывается для секций моста (без тела, другой материал)
	orig_object->setBody(nullptr);
	body.deleteLater();
	orig_object->setMaterial(joint_mat, "*");
	BodyPtr b0, b1;
	for (int i = 0; i < bridge_sections; i++)
	{
		auto object = static_ptr_cast<ObjectMeshStatic>(orig_object->clone());
		float pos = space * (i - (bridge_sections - 1) / 2.f);
		object->setWorldTransform(translate(Vec3(pos, 0.f, 8.f)));

		// Крайние сегменты используют BodyDummy (неподвижные якоря), средние - BodyRigid
		if (i == 0 || i == bridge_sections - 1)
			b1 = BodyDummy::create(object);
		else
			b1 = BodyRigid::create(object);
		ShapeBoxPtr shape2 = ShapeBox::create(b1, vec3(1.f));
		objects.append(object);

		// Шарнирные соединения допускают вращение только вокруг оси X (как в настоящей цепи моста)
		if (b0)
		{
			JointHingePtr joint = JointHinge::create(b0, b1, Vec3(pos - space, 0.f, 8.f),
				vec3_right);
			joint->setAngularDamping(8.f);
			joint->setNumIterations(4);
			joint->setLinearRestitution(0.02f);
			joint->setAngularRestitution(0.02f);
			// Ограничения силы/крутящего момента определяют, когда соединение разрушается под нагрузкой
			joint->setMaxForce(1000.f);
			joint->setMaxTorque(16000.f);
			joint->getEventBroken().connect(joint_connections, this,
				&JointCallbacks::broken_callback);
		}

		b0 = b1;
	}

	orig_object.deleteLater();
}

void JointCallbacks::shutdown()
{
	joint_connections.disconnectAll();
	objects.clear();
}

// Визуальная обратная связь: оба сегмента, соединённых разрушенным соединением, меняют внешний вид.
void JointCallbacks::broken_callback(const Unigine::JointPtr &joint)
{
	joint->getBody0()->getObject()->setMaterial(broken_mat, "*");
	joint->getBody1()->getObject()->setMaterial(broken_mat, "*");
}
