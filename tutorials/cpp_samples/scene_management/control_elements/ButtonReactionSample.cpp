// Демонстрирует реакцию на состояние интерактивного элемента управления. Трансформация узла
// интерполируется между начальной и конечной позициями/поворотами на основе
// нормализованного значения интерактивного элемента (0-1).

#include "ButtonReactionSample.h"

REGISTER_COMPONENT(ButtonReactionSample);

using namespace Unigine;
using namespace Math;

// Захватывается исходная трансформация и разрешается ссылка на интерактивный элемент.
void ButtonReactionSample::init()
{
	// Ищем интерфейс интерактивного элемента на связанном узле
	interactable_comp = ComponentSystem::get()->getComponent<Interactable>(interatable_node);

	// Захватываем начальную трансформацию как базу для интерполяции
	initial_position = node->getPosition();
	initial_rotation = node->getRotation();

	// Вычисляем целевой поворот, применяя настроенные смещения по углам Эйлера
	final_rotation = initial_rotation * quat(rotation.get().x, rotation.get().y, rotation.get().z);
}

// Трансформация узла интерполируется на основе текущего значения интерактивного элемента.
void ButtonReactionSample::update()
{
	if (!interactable_comp) return;

	// Читаем нормализованное состояние из связанного интерактивного элемента
	float value = interactable_comp->getValue();

	// Интерполируем поворот и позицию на основе значения интерактивного элемента
	quat new_rotation = slerp(initial_rotation, final_rotation, value);
	Vec3 new_position = lerp(initial_position, initial_position + (Vec3)position, value);

	node->setTransform(translate(new_position) * (Mat4)rotate(new_rotation));
}
