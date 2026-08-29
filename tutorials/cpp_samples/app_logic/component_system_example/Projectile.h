#pragma once
#include <UnigineComponentSystem.h>

// Движущийся снаряд с временем жизни и определением столкновений.
// Демонстрирует COMPONENT_UPDATE_SYNC_THREAD для потокобезопасного обновления позиции
// и World::getIntersection для запросов столкновений ограничивающих объёмов.
class Projectile : public Unigine::ComponentBase
{
public:
	// Макросы компонента
	COMPONENT(Projectile, Unigine::ComponentBase);
	COMPONENT_UPDATE_SYNC_THREAD(updateSyncThread);
	COMPONENT_UPDATE(update);

	// Имя свойства
	PROP_NAME("Projectile");

	// Параметры
	PROP_PARAM(Float, speed, 5.0f);
	PROP_PARAM(Float, lifetime, 5.0f); // время жизни в секундах (есть значение по умолчанию)
	PROP_PARAM(Int, damage); // урон, наносимый при попадании (нет значения по умолчанию)

	// Методы
	void setMaterial(const Unigine::MaterialPtr &mat);

protected:
	// Главный цикл мира
	void updateSyncThread();
	void update();
};
