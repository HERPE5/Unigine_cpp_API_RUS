// Демонстрирует callback-функции событий физического тела: frozen, position и contact.
// Создаётся башня из твёрдых тел; каждое тело меняет материал в зависимости от состояния.
// Замороженные тела становятся серыми (спящие), движущиеся подсвечиваются,
// а точки контакта визуализируются при соприкосновении тел.

#include "BodyCallbacks.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(BodyCallbacks)

// Создаётся башня из твёрдых тел с подключёнными callback-функциями событий.
void BodyCallbacks::init()
{
	// Проверяется параметр файла меша
	auto file_path = mesh_file.get();
	if (String::isEmpty(file_path))
	{
		Log::error("BodyCallbacks::init(): Mesh File parameter is empty!\n");
		return;
	}

	// Материал состояния frozen извлекается и проверяется
	frozen_mat = frozen_materal.get();
	if (!frozen_mat)
	{
		Log::error("BodyCallbacks::init(): Frozen Matreial parameter is empty!\n");
		return;
	}

	// Материал состояния движения извлекается и проверяется
	position_mat = position_materal.get();
	if (!position_mat)
	{
		Log::error("BodyCallbacks::init(): Position Matreial parameter is empty!\n");
		return;
	}

	// Настраиваются пороги заморозки физики
	Physics::setFrozenLinearVelocity(0.1f);
	Physics::setFrozenAngularVelocity(0.1f);
	Physics::setNumIterations(4);

	// Создаётся шаблонный объект с твёрдым телом и коробчатой формой
	ObjectMeshStaticPtr object = ObjectMeshStatic::create(file_path);
	BodyRigidPtr body = BodyRigid::create(object);
	ShapeBoxPtr shape = ShapeBox::create(body, vec3(1));
	object->setMaterial(position_mat, "*");

	// Пирамидальная башня строится клонированием шаблона
	for (int i = 0; i < tower_level; i++)
		for (int j = 0; j < tower_level - i; j++)
		{
			// Объект клонируется и позиционируется в форме пирамиды
			auto cloned_object = static_ptr_cast<ObjectMeshStatic>(object->clone());
			cloned_object->setWorldTransform(
				translate(Vec3(0.0f, j - 0.5f * (tower_level - i) + 0.5f, i + 0.5f) * space));

			// Callback-функции событий подключаются к клонированному телу
			body = cloned_object->getBodyRigid();
			body->getEventFrozen().connect(body_connections, this, &BodyCallbacks::frozen_callback);
			body->getEventPosition().connect(body_connections, this,
				&BodyCallbacks::position_callback);
			body->getEventContactEnter().connect(body_connections, this,
				&BodyCallbacks::contact_callback);

			// Объект сохраняется для последующей очистки
			objects.append(cloned_object);
		}

	// Шаблонный объект удаляется
	object.deleteLater();
}

// Соединения событий удаляются, объекты очищаются.
void BodyCallbacks::shutdown()
{
	// Все callback-функции событий тела отключаются
	body_connections.disconnectAll();

	// Ссылки на объекты очищаются
	objects.clear();
}

// Материал frozen применяется при переходе тела в спящее состояние.
void BodyCallbacks::frozen_callback(const Unigine::BodyPtr &body)
{
	// Серый материал применяется для обозначения замороженного состояния
	body->getObject()->setMaterial(frozen_mat, "*");
}

// Активный материал применяется, когда тело движется.
void BodyCallbacks::position_callback(const Unigine::BodyPtr &body)
{
	// Подсвеченный материал применяется для обозначения движения
	body->getObject()->setMaterial(position_mat, "*");
}

// Точки контакта визуализируются при обнаружении столкновения.
void BodyCallbacks::contact_callback(const Unigine::BodyPtr &body)
{
	// Точки контакта отрисовываются для отладки
	body->renderContacts();
}
