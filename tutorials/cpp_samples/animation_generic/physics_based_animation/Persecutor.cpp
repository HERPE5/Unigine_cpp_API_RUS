// Управляет анимированным персонажем кота (ObjectMeshSkinned) с двухслойным смешиванием
// анимации между состояниями ожидания и бега. Вращение использует экспоненциальное сглаживание
// для естественных поворотов, а скорость анимации бега соответствует фактической скорости движения.

#include "Persecutor.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(PersecutorSkinned);

using namespace Unigine;
using namespace Math;

// Узел приводится к ObjectMeshSkinned, настраиваются слои анимации.
void PersecutorSkinned::init()
{
	persecutor = static_ptr_cast<ObjectMeshSkinnedLegacy>(node);
	if (!persecutor)
		Log::error("Persecutor::init(): node is not ObjectMeshSkinned!\n");

	// Настраиваем два слоя анимации для смешивания: idle (слой 0) и run (слой 1).
	// Слои позволяют плавно переходить между состояниями анимации.
	persecutor->setNumLayers(2);
	persecutor->setLayerAnimationFilePath(0, persecutorIdleAnim);
	persecutor->setLayerAnimationFilePath(1, persecutorRunAnim);
}

// Возвращается мировая позиция скелетного меша.
Unigine::Math::Vec3 PersecutorSkinned::getPosition() const
{
	return persecutor->getWorldPosition();
}

// Возвращается мировое вращение скелетного меша.
Unigine::Math::quat PersecutorSkinned::getRotation() const
{
	return persecutor->getWorldRotation();
}

// Мировая позиция скелетного меша задаётся напрямую.
void PersecutorSkinned::setPosition(const Unigine::Math::Vec3 &new_pos)
{
	persecutor->setWorldPosition(new_pos);
}

// Вращение плавно интерполируется к целевому направлению.
void PersecutorSkinned::setRotation(const Unigine::Math::Vec3 &target_dir)
{
	// Строим вращение из вектора направления. Модель смотрит в сторону -X, поэтому применяем коррекцию на 90 градусов.
	quat target_rot = rotationFromDir(vec3(target_dir), vec3_up) * quat(0, 0, 1, -90.0f);

	// Экспоненциальное сглаживание вращения: создаёт естественное движение поворота
	// Чем выше turnRate, тем резче повороты, чем ниже - тем плавнее
	persecutor->setWorldRotation(slerp(persecutor->getWorldRotation(), target_rot,
		1.0f - Math::exp(-turnRate * Game::getIFps())));
}

// Слои анимации смешиваются в зависимости от состояния движения и скорости.
void PersecutorSkinned::setAnimation(float persecutor_speed, bool reached_target)
{
	// Смешиваем анимации ожидания и бега в зависимости от состояния движения.
	// Используется экспоненциальное скользящее среднее для плавных переходов весов.
	idle_anim_weight = lerp(idle_anim_weight, reached_target ? 1.0f : 0.0f,
		saturate(moveRate * Game::getIFps()));
	persecutor->setLayer(0, 1, idle_anim_weight);		// вес слоя ожидания
	persecutor->setLayer(1, 1, 1.0f - idle_anim_weight);	// вес слоя бега (обратный)

	// Продвигаем анимацию бега в зависимости от скорости движения (шаги синхронизированы со скоростью)
	run_anim_time += persecutor_speed * animationSpeed * Game::getIFps();
	persecutor->setLayerFrame(0, 0);		// ожидание остаётся на кадре 0
	persecutor->setLayerFrame(1, run_anim_time);	// бег продвигается вместе с движением
}
