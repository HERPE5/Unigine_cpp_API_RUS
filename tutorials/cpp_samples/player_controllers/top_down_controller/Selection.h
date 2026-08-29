// Обработчик прямоугольного выбора в стиле RTS. Поддерживает выбор перетаскиванием с визуальным прямоугольником,
// пространственный запрос объектов на основе фрустума и резервный вариант выбора одиночным кликом.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineGame.h>

// Обрабатывает выбор юнитов мышью: прямоугольник перетаскивания выбирает все юниты внутри
// фрустума, одиночный клик выбирает объект под курсором. Отслеживает выбранные объекты
// и вычисляет их совместную ограничивающую сферу для фокусировки камеры.
class Selection : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Selection, Unigine::ComponentBase);

	COMPONENT_UPDATE(update);

	Unigine::Math::Vec3 getCenter();	// Возвращает центр ограничивающей сферы выбранных объектов
	float getBoundRadius();				// Возвращает радиус ограничивающей сферы выбранных объектов

	bool hasSelection();	// Возвращает true, если выбраны какие-либо объекты

protected:
	void update();

private:
	void updateBoundShpere();	// Примечание: опечатка в имени метода - должно быть "updateBoundSphere"

	bool is_selection = false;	// True во время выбора перетаскиванием

	// Прямоугольник выбора в экранных координатах
	Unigine::Math::ivec2 selection_start_mouse_position;	// Позиция в пространстве окна в начале перетаскивания
	Unigine::Math::vec2 upper_left_selection_corner;		// Нормализованная [0,1] позиция угла прямоугольника
	Unigine::Math::vec2 bottom_right_selection_corner;		// Нормализованная [0,1] позиция угла прямоугольника

	Unigine::Math::WorldBoundFrustum frustum;			// Фрустум, построенный из прямоугольника выбора
	Unigine::Vector<Unigine::ObjectPtr> selected_objects;	// Текущие выбранные объекты

	// Совместная ограничивающая сфера всех выбранных объектов
	Unigine::Math::Vec3 selected_objects_bound_sphere_position;
	float selected_objects_bound_sphere_radius;
};