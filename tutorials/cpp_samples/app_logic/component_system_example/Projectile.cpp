// Движущийся снаряд, наносящий урон Pawn при столкновении. Использует updateSyncThread() для
// потокобезопасного обновления трансформации и update() для игровой логики. Запрос ограничивающего объёма
// определяет столкновения; VectorStack используется для результатов, размещённых на стеке.

#include "Projectile.h"

#include "Pawn.h"

#include <UnigineGame.h>

REGISTER_COMPONENT(Projectile);

using namespace Unigine;
using namespace Math;

// Позиция обновляется вдоль направления движения, время жизни уменьшается (потокобезопасно).
void Projectile::updateSyncThread()
{
	// UpdateSyncThread выполняется в потоке обновления, безопасен для изменения трансформации.
	// Используйте это для обновлений физического типа, изменяющих позиции узлов.
	float ifps = Game::getIFps();

	// Извлекаем направление движения из матрицы трансформации (ось Y = столбец 1)
	Vec3 direction = node->getWorldTransform().getColumn3(1);

	node->setWorldPosition(node->getWorldPosition() + direction * speed * ifps);

	lifetime = lifetime - ifps;
}

// Проверяется время жизни, определяется столкновение с Pawn, при попадании наносится урон.
void Projectile::update()
{
	// Обработка времени жизни
	if (lifetime < 0)
	{
		// Уничтожаем текущий узел вместе с его свойствами и компонентами
		node.deleteLater();
		return;
	}

	// Запрос пересечения ограничивающего объёма для определения столкновений.
	// VectorStack размещается на стеке (быстрее, чем Vector в куче, но фиксированная ёмкость).
	VectorStack<NodePtr> nodes;
	World::getIntersection(node->getWorldBoundBox(), nodes);
	if (nodes.size() > 1)	// сам узел всегда в списке, поэтому проверяем > 1
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			Pawn *pawn = getComponent<Pawn>(nodes[i]);
			if (pawn)
			{
				// Попадание в игрока!
				pawn->hit(damage);

				// ...и уничтожаем текущий узел
				node.deleteLater();
				return;
			}
		}
	}
}

// Материал применяется ко всем поверхностям меша снаряда.
void Projectile::setMaterial(const MaterialPtr &mat)
{
	checked_ptr_cast<Object>(node)->setMaterial(mat, "*");
}
