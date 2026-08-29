// Реализации движения по траектории для плавного следования по пути.
// Предоставляет линейную интерполяцию, сплайн Catmull-Rom и воспроизведение файла .path.
// Все варианты циклически проходят через путевые точки с настраиваемой скоростью.

#pragma once

#include "UnigineComponentSystem.h"
#include "UnigineVector.h"

#include <UniginePath.h>
#include <UnigineWorlds.h>

// Перемещает узел по путевым точкам с линейной интерполяцией позиции и slerp-интерполяцией поворота.
class SimpleTrajectoryMovement : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SimpleTrajectoryMovement, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Родительский узел, содержащий дочерние путевые точки
	PROP_PARAM(Node, path_node);
	// Скорость движения в единицах в секунду
	PROP_PARAM(Float, velocity, 10.0f);
	// Включает визуализацию пути в режиме отладки
	PROP_PARAM(Toggle, debug);

private:
	void init();
	void update();
	void visualize_path();
	// Продвигает время интерполяции на основе скорости и длины сегмента
	void update_time();

	// Закэшированные позиции и повороты путевых точек
	Unigine::Vector<Unigine::Math::Vec3> points_pos;
	Unigine::Vector<Unigine::Math::quat> points_rot;
	// Конечная точка предыдущего сегмента для интерполяции
	Unigine::Math::Vec3 prev_point;
	Unigine::Math::quat prev_rot;
	// Индекс текущей целевой путевой точки
	int points_index = 0;
	// Прогресс интерполяции (от 0 до 1) внутри текущего сегмента
	float time = 0.0f;
};

// Перемещает узел по путевым точкам с помощью сплайна Catmull-Rom с SQUAD-поворотом.
class SplineTrajectoryMovement : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SplineTrajectoryMovement, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Родительский узел, содержащий дочерние путевые точки
	PROP_PARAM(Node, pathNode);
	// Скорость движения в единицах в секунду
	PROP_PARAM(Float, velocity, 10.0f);
	// Количество подразделений сплайна для вычисления длины
	PROP_PARAM(Int, quality, 25);
	// Включает визуализацию пути в режиме отладки
	PROP_PARAM(Toggle, debug);

private:
	void init();
	void update();
	void visualize_path();
	// Продвигает время с помощью предварительно вычисленных длин сегментов для постоянной скорости
	void update_time(float speed);

	// Возвращает четыре контрольные точки для текущего сегмента сплайна
	Unigine::VectorStack<Unigine::Math::Vec3, 4> get_current_points() const;
	// Возвращает четыре контрольных поворота для текущего сегмента сплайна
	Unigine::VectorStack<Unigine::Math::quat, 4> get_current_quats() const;

	// Предварительно вычисленные длины сегментов для нормализации скорости
	Unigine::Vector<Unigine::Vector<float>> lengths;
	Unigine::Vector<Unigine::Math::Vec3> points_pos;
	Unigine::Vector<Unigine::Math::quat> points_rot;
	int points_index = 0;
	float time = 0.0f;
};

// Преобразует путевые точки в формат файла UNIGINE .path с использованием сплайновой интерполяции.
class PathTrajectorySaver : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(PathTrajectorySaver, ComponentBase);
	COMPONENT_INIT(init, -1);

	// Путь к выходному файлу .path
	PROP_PARAM(File, path_file);
	// Родительский узел, содержащий дочерние путевые точки
	PROP_PARAM(Node, path_node);
	// Количество подразделений сплайна на сегмент
	PROP_PARAM(Int, quality, 25);
	// Автоматически сохраняет файл пути при инициализации
	PROP_PARAM(Toggle, autosave, 1);

private:
	void init();
	// Генерирует файл .path из путевых точек со сплайновой интерполяцией
	void save();
};

// Воспроизводит заранее сохранённые файлы .path с помощью WorldTransformPath для плавного движения.
class SavedPathTrajectory : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(SavedPathTrajectory, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	// Путь к файлу .path, содержащему данные траектории
	PROP_PARAM(File, trajectory_file_path);
	// Множитель скорости воспроизведения
	PROP_PARAM(Float, velocity, 10.0f);
	// Включает визуализацию пути в режиме отладки
	PROP_PARAM(Toggle, debug);

private:
	void init();
	void update();
	void visualize_path();

	// Встроенный обработчик воспроизведения пути
	Unigine::WorldTransformPathPtr transform_path;
};
