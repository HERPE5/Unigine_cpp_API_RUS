// Реализации движения по траектории. Предоставлены четыре варианта:
// - SimpleTrajectoryMovement: линейная интерполяция между путевыми точками
// - SplineTrajectoryMovement: плавная сплайновая интерполяция Catmull-Rom с SQUAD-поворотом
// - PathTrajectorySaver: преобразует путевые точки в формат файла .path
// - SavedPathTrajectory: воспроизводит файлы .path с помощью WorldTransformPath

#include "TrajectoryMovement.h"

#include "../../utils/Math.h"
#include "UnigineGame.h"
#include "UnigineVisualizer.h"

#include <UniginePrimitives.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(SimpleTrajectoryMovement);
REGISTER_COMPONENT(SplineTrajectoryMovement);
REGISTER_COMPONENT(PathTrajectorySaver);
REGISTER_COMPONENT(SavedPathTrajectory);

// Позиции и повороты путевых точек кэшируются из дочерних узлов.
void SimpleTrajectoryMovement::init()
{
	UNIGINE_ASSERT(!path_node.nullCheck());

	// Кэшируем трансформации путевых точек из дочерних узлов пути
	int num_childs = path_node->getNumChildren();
	for (int i = 0; i < num_childs; i++)
	{
		NodePtr nc = path_node->getChild(i);
		points_pos.emplace_back(nc->getWorldPosition());
		points_rot.emplace_back(nc->getWorldRotation());
	}
	prev_point = node->getWorldPosition();
}

// Позиция и поворот линейно интерполируются каждый кадр.
void SimpleTrajectoryMovement::update()
{
	update_time();

	// Lerp для позиции, slerp для поворота между конечными точками текущего сегмента
	node->setWorldPosition(lerp(prev_point, points_pos[points_index], time));
	node->setWorldRotation(slerp(prev_rot, points_rot[points_index], time));

	if (debug.get())
		visualize_path();
}

// Рисует линии, соединяющие путевые точки в замкнутый цикл.
void SimpleTrajectoryMovement::visualize_path()
{
	for (int i = 0; i < points_pos.size(); i++)
	{
		int next = (i + 1) % points_pos.size();
		Visualizer::renderLine3D(points_pos[i], points_pos[next], vec4_white);
	}
}

// Время продвигается на основе скорости и длины сегмента для постоянной скорости.
void SimpleTrajectoryMovement::update_time()
{
	float len = (float)length(points_pos[points_index] - prev_point);

	// Обновляем время интерполяции, нормализованное по длине сегмента
	time += velocity / len * Game::getIFps();
	if (time >= 1.0f)
	{
		// Кэшируем текущую точку как начало сегмента для следующей интерполяции
		prev_point = points_pos[points_index];
		prev_rot = points_rot[points_index];

		// Переходим к следующей путевой точке с зацикливанием
		points_index = (points_index + ftoi(time)) % points_pos.size();
		time = Math::frac(time);
	}
}

// Путевые точки кэшируются, длины сегментов предварительно вычисляются для постоянной скорости.
void SplineTrajectoryMovement::init()
{
	UNIGINE_ASSERT(!pathNode.nullCheck());

	// Кэшируем трансформации путевых точек из дочерних узлов пути
	int num_childs = pathNode->getNumChildren();
	for (int i = 0; i < num_childs; i++)
	{
		NodePtr nc = pathNode->getChild(i);
		points_pos.emplace_back(nc->getWorldPosition());
		points_rot.emplace_back(nc->getWorldRotation());
	}

	// Предварительно вычисляем длины дуг сегментов для движения с постоянной скоростью
	lengths.clear();
	int points_count = points_pos.size();
	for (int j = 0; j < points_count; j++)
	{
		int j_prev = (j - 1 < 0) ? (points_count - 1) : j - 1;
		int j_cur = j;
		int j_next = (j + 1) % points_count;
		int j_next_next = (j + 2) % points_count;

		const Vec3& p0 = points_pos[j_prev];
		const Vec3& p1 = points_pos[j_cur];
		const Vec3& p2 = points_pos[j_next];
		const Vec3& p3 = points_pos[j_next_next];

		lengths.append(Utils::getLengthCatmullRomCentripetal(p0, p1, p2, p3, quality));
	}
}

// Позиция на сплайне и SQUAD-поворот вычисляются каждый кадр.
void SplineTrajectoryMovement::update()
{
	// Вычисляем скорость с помощью предварительно вычисленной длины сегмента для постоянной скорости
	float speed = velocity / (lengths[points_index][int(time * (quality - 1))] * quality);
	update_time(speed);

	// Собираем четыре контрольные точки для вычисления сплайна Catmull-Rom
	VectorStack<Vec3, 4> p = get_current_points();
	VectorStack<quat, 4> q = get_current_quats();

	// Вычисляем позицию на сплайне Catmull-Rom и поворот с помощью SQUAD
	Vec3 pos = Utils::catmullRomCentripetal(p[0], p[1], p[2], p[3], time);
	quat rot = Utils::squad(q[0], q[1], q[2], q[3], time);

	// Применяем интерполированную трансформацию к узлу
	node->setWorldPosition(pos);
	node->setWorldRotation(rot, true);

	if (debug.get())
		visualize_path();
}

// Рисует плавные сплайновые кривые между всеми путевыми точками.
void SplineTrajectoryMovement::visualize_path()
{
	int points_count = points_pos.size();
	for (int j = 0; j < points_count; j++)
	{
		int j_prev = (j - 1 < 0) ? (points_count - 1) : j - 1;
		int j_cur = j;
		int j_next = (j + 1) % points_count;
		int j_next_next = (j + 2) % points_count;

		const Vec3& p0 = points_pos[j_prev];
		const Vec3& p1 = points_pos[j_cur];
		const Vec3& p2 = points_pos[j_next];
		const Vec3& p3 = points_pos[j_next_next];

		// Рисуем сегмент сплайна как соединённые отрезки линий
		Vec3 start = Utils::catmullRomCentripetal(p0, p1, p2, p3, 0);
		int quality = 10;
		for (int i = 1; i < quality; i++)
		{
			Vec3 end = Utils::catmullRomCentripetal(p0, p1, p2, p3, float(i) / (quality - 1));
			Visualizer::renderLine3D(start, end, vec4_white);
			start = end;
		}
	}
}

// Время интерполяции продвигается; переходит к следующему сегменту по завершении.
void SplineTrajectoryMovement::update_time(float speed)
{
	time += speed * Game::getIFps();
	if (time >= 1.0f)
	{
		// Переходим к следующему сегменту с зацикливанием
		points_index = (points_index + ftoi(time)) % points_pos.size();
		time = Math::frac(time);
	}
}

// Собирает четыре окружающие контрольные точки позиции для вычисления сплайна.
VectorStack<Vec3, 4> SplineTrajectoryMovement::get_current_points() const
{
	int points_count = points_pos.size();
	int i_prev = (points_index - 1 < 0) ? (points_count - 1) : points_index - 1;
	int i_cur = points_index;
	int i_next = (points_index + 1) % points_count;
	int i_next_next = (points_index + 2) % points_count;

	VectorStack<Vec3, 4> result;
	result.append(points_pos[i_prev]);
	result.append(points_pos[i_cur]);
	result.append(points_pos[i_next]);
	result.append(points_pos[i_next_next]);
	return result;
}

// Собирает четыре окружающих контрольных поворота для вычисления SQUAD.
VectorStack<quat, 4> SplineTrajectoryMovement::get_current_quats() const
{
	int points_count = points_pos.size();
	int i_prev = (points_index - 1 < 0) ? (points_count - 1) : points_index - 1;
	int i_cur = points_index;
	int i_next = (points_index + 1) % points_count;
	int i_next_next = (points_index + 2) % points_count;

	VectorStack<quat, 4> result;
	result.append(points_rot[i_prev]);
	result.append(points_rot[i_cur]);
	result.append(points_rot[i_next]);
	result.append(points_rot[i_next_next]);
	return result;
}


// Файл пути генерируется автоматически, если включён autosave.
void PathTrajectorySaver::init()
{
	UNIGINE_ASSERT(!path_file.nullCheck());
	UNIGINE_ASSERT(!path_node.nullCheck());

	// Генерируем файл .path при инициализации компонента, если включено
	if (autosave.get())
		save();
}

// Сплайн вычисляется и данные кадров записываются в файл .path.
void PathTrajectorySaver::save()
{
	PathPtr path = Path::create();
	path->clear();

	int points_count = path_node->getNumChildren();
	double frame_time = 0;
	for (int j = 0; j < points_count; j++)
	{
		int j_prev = (j - 1 < 0) ? (points_count - 1) : j - 1;
		int j_cur = j;
		int j_next = (j + 1) % points_count;
		int j_next_next = (j + 2) % points_count;

		// Собираем четыре контрольные точки для вычисления Catmull-Rom
		const Vec3 p0 = path_node->getChild(j_prev)->getWorldPosition();
		const Vec3 p1 = path_node->getChild(j_cur)->getWorldPosition();
		const Vec3 p2 = path_node->getChild(j_next)->getWorldPosition();
		const Vec3 p3 = path_node->getChild(j_next_next)->getWorldPosition();

		const quat q0 = path_node->getChild(j_prev)->getWorldRotation();
		const quat q1 = path_node->getChild(j_cur)->getWorldRotation();
		const quat q2 = path_node->getChild(j_next)->getWorldRotation();
		const quat q3 = path_node->getChild(j_next_next)->getWorldRotation();

		// Сэмплируем сплайн через интервалы quality для генерации кадров пути
		Vec3 start = Utils::catmullRomCentripetal(p0, p1, p2, p3, 0);
		for (int i = 1; i < quality; i++)
		{
			path->addFrame();

			float time = float(i) / (quality - 1);

			// Вычисляем позицию на сплайне и SQUAD-поворот при текущем t
			Vec3 end = Utils::catmullRomCentripetal(p0, p1, p2, p3, time);
			quat rot = Utils::squad(q0, q1, q2, q3, time);

			// Накапливаем длину дуги для тайминга кадров (обеспечивает воспроизведение с постоянной скоростью)
			double len = length(start - end);
			frame_time += len;

			path->setFramePosition(path->getNumFrames() - 1, end);
			path->setFrameRotation(path->getNumFrames() - 1, rot);
			path->setFrameTime(path->getNumFrames() - 1, static_cast<float>(frame_time));

			start = end;
		}
	}

	// Сохраняем в файл
	path->save(path_file.get());
}

// Создаётся WorldTransformPath, узел присоединяется для автоматической анимации.
void SavedPathTrajectory::init()
{
	node->setWorldPosition(Vec3(0, 0, 0));

	transform_path = WorldTransformPath::create(trajectory_file_path);
	transform_path->setLoop(1);
	transform_path->setTime(0.0f);
	transform_path->setSpeed(velocity);
	transform_path->play();
	transform_path->addChild(node);
}

// Скорость воспроизведения обновляется, путь визуализируется, если включён debug.
void SavedPathTrajectory::update()
{
	transform_path->setSpeed(velocity);

	if (debug.get())
		visualize_path();
}

// Рисует линии, соединяющие все кадры в загруженном пути.
void SavedPathTrajectory::visualize_path()
{
	PathPtr path = transform_path->getPath();
	int num_frames = path->getNumFrames();
	for (int i = 0; i < num_frames; i++)
	{
		Vec3 curr_point = path->getFramePosition(i);
		Vec3 next_point = path->getFramePosition((i + 1) % num_frames);

		Visualizer::renderLine3D(curr_point, next_point, vec4_white);
	}
}
