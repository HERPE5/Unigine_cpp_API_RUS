// Визуализирует последовательности композиции и декомпозиции вращения по углам Эйлера. Показывает, как
// разный порядок осей (XYZ, XZY, YXZ, YZX, ZXY, ZYX) даёт разные вращения
// из одних и тех же углов. Декомпозиция может давать разные углы из-за карданова замка.

#include "EulerAnglesSample.h"

#include "UnigineVisualizer.h"


REGISTER_COMPONENT(EulerAnglesSample);

using namespace Unigine;
using namespace Unigine::Math;



// GUI инициализируется, визуализатор включается для отладочного рендеринга.
void EulerAnglesSample::init()
{
	init_gui();
	update_decomposition_angles();

	visualizer_enabled = Visualizer::isEnabled();
	Visualizer::setEnabled(true);
}

// Локальные/глобальные оси и орбиты вращения визуализируются каждый кадр.
void EulerAnglesSample::update()
{
	Vec3 position = plane->getWorldPosition();
	vec3 direction_x = plane->getWorldDirection(Math::AXIS_X);
	vec3 direction_y = plane->getWorldDirection(Math::AXIS_Y);
	vec3 direction_z = plane->getWorldDirection(Math::AXIS_Z);

	// Отрисовываем локальные оси плоскости (вращаются вместе с объектом).
	// Они показывают текущую ориентацию объекта после применения вращения Эйлера.
	// Красный = X (ось тангажа), Зелёный = Y (ось крена), Синий = Z (ось рыскания).
	{
		Visualizer::renderVector(position, position + Vec3(direction_x) * 1.5f, vec4_red);
		Visualizer::renderVector(position, position + Vec3(direction_y) * 1.5f, vec4_green);
		Visualizer::renderVector(position, position + Vec3(direction_z) * 1.5f, vec4_blue);

		Visualizer::renderMessage3D(position + Vec3(direction_x) * 1.5f, vec3_zero, "X", vec4_black, 1);
		Visualizer::renderMessage3D(position + Vec3(direction_y) * 1.5f, vec3_zero, "Y", vec4_black, 1);
		Visualizer::renderMessage3D(position + Vec3(direction_z) * 1.5f, vec3_zero, "Z", vec4_black, 1);
	}

	// Отрисовываем глобальные (мировые) оси как ориентир.
	// Они никогда не вращаются - показывают фиксированную мировую систему координат.
	{
		Vec3 offset = { -2.0f, -2.0f, 0.2f };

		Visualizer::renderVector(offset, offset + Vec3_right * 2.0f, vec4_red);
		Visualizer::renderVector(offset, offset + Vec3_forward * 2.0f, vec4_green);
		Visualizer::renderVector(offset, offset + Vec3_up * 2.0f, vec4_blue);
	}


	// Отрисовываем кольца карданова подвеса (орбиты), показывающие оси вращения на каждом шаге.
	// Каждое кольцо представляет вращение по одной оси в последовательности.
	// Большее кольцо = применяется первым, меньшее кольцо = применяется последним.
	// Это визуализирует, как вращения Эйлера строятся пошагово.
	{
		Mat4 orbit_x_transform = Mat4_identity;
		Mat4 orbit_y_transform = Mat4_identity;
		Mat4 orbit_z_transform = Mat4_identity;
		vec3 radii = vec3_zero;

		// Вычисляем трансформацию для каждого кольца карданова подвеса на основе последовательности композиции.
		// Каждое кольцо показывает ориентацию оси ПОСЛЕ применения предыдущих вращений.
		{
			float x = euler_angles.x;
			float y = euler_angles.y;
			float z = euler_angles.z;

			float big_radius = 1.4f;
			float middle_radius = 1.3f;
			float small_radius = 1.2f;

			orbit_x_transform = Mat4 { rotate(quat{ euler_angles.x, 0.0f, 0.0f }) };
			orbit_y_transform = Mat4 { rotate(quat{ euler_angles.x, euler_angles.y, 0.0f }) };
			orbit_z_transform = Mat4 { rotate(quat{ euler_angles.x, euler_angles.y, euler_angles.z }) };
			radii = vec3 { big_radius, middle_radius, small_radius };

			// Для каждой последовательности кольца вычисляются инкрементально:
			// - Первая ось: без предшествующего вращения
			// - Вторая ось: повёрнута первой
			// - Третья ось: повёрнута первой и второй
			// Радиусы указывают порядок: большой = первая, средний = вторая, малый = третья.
			switch (composition_sequence)
			{
				case XYZ: // Вращаем X, затем Y, затем Z
					orbit_x_transform = Mat4 { composeRotationXYZ(vec3(x, 0.0f, 0.0f)) };
					orbit_y_transform = Mat4 { composeRotationXYZ(vec3(x, y, 0.0f)) };
					orbit_z_transform = Mat4 { composeRotationXYZ(vec3(x, y, z)) };
					radii = vec3(big_radius, middle_radius, small_radius);
					break;

				case XZY: // Вращаем X, затем Z, затем Y
					orbit_x_transform = Mat4 { composeRotationXZY(vec3(x, 0.0f, 0.0f)) };
					orbit_z_transform = Mat4 { composeRotationXZY(vec3(x, 0.0f, z)) };
					orbit_y_transform = Mat4 { composeRotationXZY(vec3(x, y, z)) };
					radii = vec3(big_radius, small_radius, middle_radius);
					break;

				case YXZ: // Вращаем Y, затем X, затем Z
					orbit_y_transform = Mat4 { composeRotationYXZ(vec3(0.0f, y, 0.0f)) };
					orbit_x_transform = Mat4 { composeRotationYXZ(vec3(x, y, 0.0f)) };
					orbit_z_transform = Mat4 { composeRotationYXZ(vec3(x, y, z)) };
					radii = vec3(middle_radius, big_radius, small_radius);
					break;

				case YZX: // Вращаем Y, затем Z, затем X
					orbit_y_transform = Mat4 { composeRotationYZX(vec3(0.0f, y, 0.0f)) };
					orbit_z_transform = Mat4 { composeRotationYZX(vec3(0.0f, y, z)) };
					orbit_x_transform = Mat4 { composeRotationYZX(vec3(x, y, z)) };
					radii = vec3(small_radius, big_radius, middle_radius);
					break;

				case ZXY: // Вращаем Z, затем X, затем Y
					orbit_z_transform = Mat4 { composeRotationZXY(vec3(0.0f, 0.0f, z)) };
					orbit_x_transform = Mat4 { composeRotationZXY(vec3(x, 0.0f, z)) };
					orbit_y_transform = Mat4 { composeRotationZXY(vec3(x, y, z)) };
					radii = vec3(middle_radius, small_radius, big_radius);
					break;

				case ZYX: // Вращаем Z, затем Y, затем X
					orbit_z_transform = Mat4 { composeRotationZYX(vec3(0.0f, 0.0f, z)) };
					orbit_y_transform = Mat4 { composeRotationZYX(vec3(0.0f, y, z)) };
					orbit_x_transform = Mat4 { composeRotationZYX(vec3(x, y, z)) };
					radii = vec3(small_radius, middle_radius, big_radius);
					break;
			}

			// Позиционируем кольца в положении объекта и ориентируем их перпендикулярно их оси вращения.
			// X-кольцо вращается вокруг X, поэтому лежит в плоскости YZ (повёрнуто на 90° вокруг Y).
			// Y-кольцо вращается вокруг Y, поэтому лежит в плоскости XZ (повёрнуто на 90° вокруг X).
			// Z-кольцо вращается вокруг Z, поэтому лежит в плоскости XY (без дополнительного вращения).
			orbit_x_transform = translate(position) * orbit_x_transform * Mat4 { rotate(quat{ 0, 90, 0 }) };
			orbit_y_transform = translate(position) * orbit_y_transform * Mat4 { rotate(quat{ 90, 0, 0 }) };
			orbit_z_transform = translate(position) * orbit_z_transform;
		}

		Visualizer::renderCircle(radii.x, orbit_x_transform, vec4_red);
		Visualizer::renderCircle(radii.y, orbit_y_transform, vec4_green);
		Visualizer::renderCircle(radii.z, orbit_z_transform, vec4_blue);

		// Отрисовываем маленькие стрелки на каждом кольце, указывающие направление вращения.
		{
			Vec3 arrow_start = position + orbit_x_transform.getAxisY() * radii.x;
			Vec3 arrow_finish = arrow_start + orbit_x_transform.getAxisY() * 0.1f;
			Visualizer::renderVector(arrow_start, arrow_finish, vec4_red, 1.0f);

			arrow_start = position + orbit_y_transform.getAxisY() * radii.y;
			arrow_finish = arrow_start + orbit_y_transform.getAxisY() * 0.1f;
			Visualizer::renderVector(arrow_start, arrow_finish, vec4_green, 1.0f);

			arrow_start = position + orbit_z_transform.getAxisY() * radii.z;
			arrow_finish = arrow_start + orbit_z_transform.getAxisY() * 0.1f;
			Visualizer::renderVector(arrow_start, arrow_finish, vec4_blue, 1.0f);
		}
	}
}

// UI освобождается, состояние визуализатора восстанавливается.
void EulerAnglesSample::shutdown()
{
	sample_description_window.shutdown();
	Visualizer::setEnabled(visualizer_enabled);
}


// Вращение составляется из углов Эйлера с использованием выбранной последовательности осей.
void EulerAnglesSample::update_rotation()
{
	// Составляем матрицу вращения из углов Эйлера с использованием выбранной последовательности.
	// Разные последовательности дают разные вращения из одних и тех же углов!
	mat4 rotation = mat4_identity;

	switch (composition_sequence)
	{
		case XYZ: rotation = composeRotationXYZ(euler_angles); break;
		case XZY: rotation = composeRotationXZY(euler_angles); break;
		case YXZ: rotation = composeRotationYXZ(euler_angles); break;
		case YZX: rotation = composeRotationYZX(euler_angles); break;
		case ZXY: rotation = composeRotationZXY(euler_angles); break;
		case ZYX: rotation = composeRotationZYX(euler_angles); break;
	}

	plane->setWorldRotation(quat{ rotation }, true);
}

// Текущее вращение раскладывается обратно в углы Эйлера с использованием выбранной последовательности.
void EulerAnglesSample::update_decomposition_angles()
{
	// Раскладываем матрицу вращения обратно в углы Эйлера.
	// Примечание: декомпозиция может давать другие углы, чем композиция,
	// из-за карданова замка и нескольких допустимых представлений.
	mat3 rotation = plane->getWorldRotation().getMat3();

	switch (decomposition_sequence)
	{
		case XYZ: decomposition_angles = decomposeRotationXYZ(rotation); break;
		case XZY: decomposition_angles = decomposeRotationXZY(rotation); break;
		case YXZ: decomposition_angles = decomposeRotationYXZ(rotation); break;
		case YZX: decomposition_angles = decomposeRotationYZX(rotation); break;
		case ZXY: decomposition_angles = decomposeRotationZXY(rotation); break;
		case ZYX: decomposition_angles = decomposeRotationZYX(rotation); break;
	}

	status = String::format("Decomposition angles:\nPitch (X):\t%.2f\nRoll (Y):\t%.2f\nYaw (Z):\t%.2f\n",
		decomposition_angles.x, decomposition_angles.y, decomposition_angles.z);
	sample_description_window.setStatus(status);
}

// Создаются слайдеры и комбобоксы UI для управления углами и последовательностью.
void EulerAnglesSample::init_gui()
{
	sample_description_window.createWindow();

	auto pitch_slider = sample_description_window.addIntParameter("Pitch (X)", "Pitch (X)", 0, -180, 180, [this](int value) {
		euler_angles.x = float(value);
		update_rotation();
		update_decomposition_angles();
	});

	auto roll_slider = sample_description_window.addIntParameter("Roll (Y)", "Roll (Y)", 0, -180, 180, [this](int value) {
		euler_angles.y = float(value);
		update_rotation();
		update_decomposition_angles();
	});

	auto yaw_slider = sample_description_window.addIntParameter("Yaw (Z)", "Yaw (Z)", 0, -180, 180, [this](int value) {
		euler_angles.z = float(value);
		update_rotation();
		update_decomposition_angles();
	});

	auto parameters = sample_description_window.getParameterGroupBox();

	WidgetComboBoxPtr composition_combo_box;
	WidgetComboBoxPtr decomposition_combo_box;

	{
		auto hbox = WidgetHBox::create();
		hbox->addChild(WidgetLabel::create("Composition sequence: "), Gui::ALIGN_LEFT);

		auto combo_box = WidgetComboBox::create();

		combo_box->addItem("XYZ");
		combo_box->addItem("XZY");
		combo_box->addItem("YXZ");
		combo_box->addItem("YZX");
		combo_box->addItem("ZXY");
		combo_box->addItem("ZYX");

		combo_box->getEventChanged().connect(*this, [this, combo_box] {
			composition_sequence = ROTATION_SEQUENCE(combo_box->getCurrentItem());
			update_rotation();
		});

		composition_combo_box = combo_box;

		hbox->addChild(combo_box);
		parameters->addChild(hbox, Gui::ALIGN_LEFT);
	};

	{
		auto hbox = WidgetHBox::create();
		hbox->addChild(WidgetLabel::create("Decomposition sequence: "), Gui::ALIGN_LEFT);

		auto combo_box = WidgetComboBox::create();

		combo_box->addItem("XYZ");
		combo_box->addItem("XZY");
		combo_box->addItem("YXZ");
		combo_box->addItem("YZX");
		combo_box->addItem("ZXY");
		combo_box->addItem("ZYX");

		combo_box->getEventChanged().connect(*this, [this, combo_box] {
			decomposition_sequence = ROTATION_SEQUENCE(combo_box->getCurrentItem());
			update_decomposition_angles();
		});

		decomposition_combo_box = combo_box;

		hbox->addChild(combo_box);
		parameters->addChild(hbox, Gui::ALIGN_LEFT);
	};

	auto reset_button = WidgetButton::create("Reset");
	reset_button->getEventClicked().connect(*this, [this, yaw_slider, roll_slider, pitch_slider, composition_combo_box, decomposition_combo_box] {
		euler_angles = vec3_zero;
		update_rotation();
		update_decomposition_angles();

		yaw_slider->setValue(0);
		pitch_slider->setValue(0);
		roll_slider->setValue(0);
		composition_combo_box->setCurrentItem(0);
		decomposition_combo_box->setCurrentItem(0);
	});

	parameters->addChild(reset_button, Gui::ALIGN_LEFT);
}
