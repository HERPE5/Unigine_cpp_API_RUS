// Преобразует процедурный ObjectMeshClutter в статический ObjectMeshCluster. Clutter
// пересоздаёт экземпляры каждый кадр на основе зерна; Cluster хранит фиксированные трансформации
// для лучшей производительности во время выполнения, когда позиции экземпляров не должны меняться.

#include "ClutterConverter.h"

#include <UnigineObjects.h>

REGISTER_COMPONENT(ClutterConverter);

using namespace Unigine;
using namespace Math;

void ClutterConverter::init()
{
	// Приводим общую ссылку Node к ObjectMeshClutter для типобезопасного доступа
	clutter_mesh = checked_ptr_cast<ObjectMeshClutter>(clutterMesh.get());
}

void ClutterConverter::convertToCluster()
{
	// Удаляем любой ранее созданный кластер, чтобы избежать дубликатов
	remove_cluster();

	cluster_mesh = convert_mesh(clutter_mesh);
	if (cluster_mesh)
	{
		is_converted = true;
		// Переназначаем родителя кластера на указанный узел
		cluster_mesh->setParent(clusterParent.get());
	}
}

void ClutterConverter::generateClutter()
{
	// Новое зерно запускает пересчёт всех позиций экземпляров clutter
	clutter_mesh->setSeed(Math::Random::getRandom().get());
}

void ClutterConverter::remove_cluster()
{
	if (!is_converted)
		return;

	// deleteLater() безопасно удаляет узел в конце кадра
	cluster_mesh.deleteLater();
	is_converted = false;
}

ObjectMeshClusterPtr ClutterConverter::convert_mesh(const ObjectMeshClutterPtr &clutter)
{
	// Создаём кластер, используя тот же ресурс меша, что и исходный clutter
	auto cluster = ObjectMeshCluster::create(clutter->getMeshPath());
	String name(clutter->getName());
	cluster->setName(name.append("_Cluster"));

	// Сохраняем иерархию: кластер занимает место clutter в графе сцены
	cluster->setParent(clutter->getParent());
	// Копируем мировую трансформацию для сохранения пространственного позиционирования
	cluster->setWorldTransform(clutter->getWorldTransform());

	// Копируем настройки дистанции LOD для согласованного поведения видимости
	cluster->setVisibleDistance(clutter->getVisibleDistance());
	cluster->setFadeDistance(clutter->getFadeDistance());

	// Проходим по всем поверхностям, чтобы скопировать их настройки рендеринга и физики
	const int suf_num = clutter->getNumSurfaces();
	for (int suf_index = 0; suf_index < suf_num; ++suf_index)
	{
		// Настройки видимости и рендеринга
		cluster->setEnabled(clutter->isEnabled(suf_index), suf_index);
		cluster->setViewportMask(clutter->getViewportMask(suf_index), suf_index);

		// Настройка отбрасывания теней
		cluster->setShadowMask(clutter->getShadowMask(suf_index), suf_index);
		cluster->setCastShadow(clutter->getCastShadow(suf_index), suf_index);
		cluster->setCastWorldShadow(clutter->getCastWorldShadow(suf_index), suf_index);

		// Настройки глобального освещения и зондов окружения
		cluster->setBakeToEnvProbe(clutter->getBakeToEnvProbe(suf_index), suf_index);
		cluster->setBakeToGI(clutter->getBakeToGI(suf_index), suf_index);
		cluster->setCastEnvProbeShadow(clutter->getCastEnvProbeShadow(suf_index), suf_index);
		cluster->setShadowMode(clutter->getShadowMode(suf_index), suf_index);

		// Переопределения дистанции LOD для каждой поверхности
		cluster->setMinVisibleDistance(clutter->getMinVisibleDistance(suf_index), suf_index);
		cluster->setMaxVisibleDistance(clutter->getMaxVisibleDistance(suf_index), suf_index);
		cluster->setMinFadeDistance(clutter->getMinFadeDistance(suf_index), suf_index);
		cluster->setMaxFadeDistance(clutter->getMaxFadeDistance(suf_index), suf_index);
		cluster->setMinParent(clutter->getMinParent(suf_index), suf_index);
		cluster->setMaxParent(clutter->getMaxParent(suf_index), suf_index);

		// Настройки пересечения лучей для выбора и запросов видимости
		cluster->setIntersection(clutter->getIntersection(suf_index), suf_index);
		cluster->setIntersectionMask(clutter->getIntersectionMask(suf_index), suf_index);

		// Настройки определения столкновений
		cluster->setCollision(clutter->getCollision(suf_index), suf_index);
		cluster->setCollisionMask(clutter->getCollisionMask(suf_index), suf_index);

		// Трассировка лучей физики (отдельно от пересечения рендеринга)
		cluster->setPhysicsIntersection(clutter->getPhysicsIntersection(suf_index), suf_index);
		cluster->setPhysicsIntersectionMask(clutter->getPhysicsIntersectionMask(suf_index),
			suf_index);

		// Звуковая окклюзия для распространения звука
		cluster->setSoundOcclusion(clutter->getSoundOcclusion(suf_index), suf_index);
		cluster->setSoundOcclusionMask(clutter->getSoundOcclusionMask(suf_index), suf_index);

		// Свойства физического материала
		cluster->setPhysicsFriction(clutter->getPhysicsFriction(suf_index), suf_index);
		cluster->setPhysicsRestitution(clutter->getPhysicsRestitution(suf_index), suf_index);

		// Копируем ссылки на материал и свойство поверхности
		cluster->setMaterial(clutter->getMaterial(suf_index), suf_index);
		cluster->setSurfaceProperty(clutter->getSurfaceProperty(suf_index), suf_index);
	}

	// Извлекаем текущие трансформации экземпляров из процедурного clutter
	Vector<Mat4> transforms;
	// Заставляем clutter вычислить текущие позиции экземпляров
	clutter->createClutterTransforms();
	if (!clutter->getClutterWorldTransforms(transforms))
	{
		Log::warning("ClutterConverter::convert_mesh(): empty set of transforms\n");
		return ObjectMeshClusterPtr{};
	}

	// Создаём экземпляры кластера из извлечённых мировых трансформаций
	cluster->createMeshes(transforms);
	return cluster;
}
