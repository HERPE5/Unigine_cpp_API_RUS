// Демонстрирует запросы пространственного пересечения с использованием объёмов
// усечённой пирамиды, сферы и бокса. У объектов, пересекающих каждый объём,
// изменяется материал. Использует типы WorldBound для совместимости с двойной точностью.

#include "BoundIntersection.h"
#include "UnigineComponentSystem.h"
#include "UnigineMaterial.h"
#include "UnigineMathLib.h"
#include "UnigineMathLibBounds.h"
#include "UnigineMathLibMat4.h"
#include "UnigineMathLibVec4.h"
#include "UnigineObjects.h"
#include "UniginePtr.h"
#include "UnigineVisualizer.h"
#include "UnigineWidgets.h"
#include "../../utils/Rotator.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(BoundIntersection)

// Ограничивающие объёмы строятся из параметров компонента; визуализатор включается.
void BoundIntersection::init()
{
	Visualizer::setEnabled(true);

	// Строим усечённую пирамиду из view-матрицы look-at и матрицы перспективной проекции
	frustum_view_matrix =
		Mat4(lookAt(bound_frustum->eye_position, bound_frustum->target_position, bound_frustum->up_direction, bound_frustum->forward_axis));
	float view_aspect = static_cast<float>(bound_frustum->view_width) / bound_frustum->view_height;
	frustum_projection_matrix =
		perspective(bound_frustum->view_fov, view_aspect, bound_frustum->view_distance_min, bound_frustum->view_distance_max);

	// Типы WorldBound обеспечивают корректное поведение в сборках с двойной точностью
	frustum = WorldBoundFrustum(frustum_projection_matrix, frustum_view_matrix);
	sphere = WorldBoundSphere(Vec3(bound_sphere->position), bound_sphere->radius);
	box = WorldBoundBox(Vec3(bound_box->minimum), Vec3(bound_box->maximum));

	init_ui();
	// Получаем ссылку на Rotator для управления скоростью вращения через UI
	rotator_component = ComponentSystem::get()->getComponentInWorld<Rotator>();
}

// Каждый тип объёма проверяется на пересечения; совпадающие объекты подсвечиваются.
void BoundIntersection::update()
{
	// Переиспользуется для каждого запроса пересечения (автоматически очищается getIntersection)
	Vector<NodePtr> found;

	// Проверяем пересечение с усечённой пирамидой и применяем зелёный материал
	World::getIntersection(frustum, found);
	change_color(found, bound_frustum->intersection_material);

	// Проверяем пересечение со сферой и применяем красный материал
	World::getIntersection(sphere, found);
	change_color(found, bound_sphere->intersection_material);

	// Проверяем пересечение с боксом и применяем синий материал
	World::getIntersection(box, found);
	change_color(found, bound_box->intersection_material);

	render_all_bounds();
}

// Окно UI закрывается; визуализатор отключается.
void BoundIntersection::shutdown()
{
	window.shutdown();
	Visualizer::setEnabled(false);
}

// Исходные материалы восстанавливаются в конце кадра, чтобы подсветка длилась только один кадр.
void BoundIntersection::swap()
{
	for (auto &it : changed)
	{
		it.key->setMaterial(it.data, 0);
	}
	changed.clear();
}

// У пересекающихся объектов материал временно заменяется на цвет подсветки.
void BoundIntersection::change_color(const Vector<NodePtr> &found, const MaterialPtr &new_material)
{
	for (int i = 0, found_size = found.size(); i < found_size; ++i)
	{
		if (found[i].isDeleted())
			continue;

		// Обрабатываем только объекты-меши (пропускаем источники света, игроков и т.д.)
		if (ObjectMeshStaticPtr mesh = checked_ptr_cast<ObjectMeshStatic>(found[i]))
		{
			// Сохраняем исходный материал для восстановления в swap()
			changed.append(mesh, mesh->getMaterial(0));
			mesh->setMaterial(new_material, 0);
		}
	}
}

// Отладочная визуализация всех ограничивающих объёмов и боксов объектов.
void BoundIntersection::render_all_bounds() const
{
	// Рисуем тестовые объёмы в соответствующих цветах подсветки
	Visualizer::renderFrustum(frustum_projection_matrix, inverse(frustum_view_matrix), vec4_green);
	Visualizer::renderBoundSphere(sphere, Mat4_identity, vec4_red);
	Visualizer::renderBoundBox(box, Mat4_identity, vec4_blue);

	// Рисуем ограничивающие боксы всех тестовых примитивов
	NodePtr primitives = World::getNodeByName("primitives");
	if (!primitives)
		return;

	for (int i = 0; i < primitives->getNumChildren(); ++i)
		Visualizer::renderNodeBoundBox(primitives->getChild(i), vec4_white);
}

// Создаётся окно UI с ползунком скорости вращения.
void BoundIntersection::init_ui()
{
	window.createWindow();

	auto parameters = window.getParameterGroupBox();
	WidgetVBoxPtr vbox = WidgetVBox::create();
	window.addFloatParameter("Rotation Speed", "Adjusts the rotation speed of the figures", 25.0f, 0.0f, 50.0f,
		[this](float new_z) { rotator_component->angular_velocity = vec3(0, 0, new_z); });
}
