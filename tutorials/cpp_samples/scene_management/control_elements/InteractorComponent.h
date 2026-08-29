// Контроллер взаимодействия игрока, выполняющий трассировку лучей для поиска интерактивных объектов.
// Нажатие F инициирует взаимодействие; удержание F продолжает его каждый кадр.
// Прикрепляется к узлу Player для использования направления взгляда при трассировке.

#pragma once
#include "Interactable.h"

#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

// Выполняет трассировку луча от позиции игрока и вызывает use() на пересечённых интерактивных объектах.
class InteractorComponent : public Unigine::ComponentBase
{
public:
	COMPONENT(InteractorComponent, Unigine::ComponentBase);
	PROP_NAME("Interactor");
	// Битовая маска, фильтрующая объекты, с которыми возможно взаимодействие
	PROP_PARAM(Mask, interactable_intersection_mask, 4);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_POST_UPDATE(post_update);
	COMPONENT_SHUTDOWN(shutdown);

private:
	void init();
	void update();
	void post_update();
	void shutdown();

	// Ссылка на игрока для направления взгляда и позиции
	Unigine::PlayerPtr player;
	// Переиспользуемый результат пересечения во избежание аллокаций
	Unigine::WorldIntersectionPtr intersection = Unigine::WorldIntersection::create();
	// Текущая заблокированная цель взаимодействия
	Unigine::ObjectPtr obj;
	// Закэшированный интерактивный компонент целевого объекта
	Interactable *comp_interactable = nullptr;

	// Сохранённый режим мыши, восстанавливаемый при завершении работы
	Unigine::Input::MOUSE_HANDLE mouse_handle;
};
