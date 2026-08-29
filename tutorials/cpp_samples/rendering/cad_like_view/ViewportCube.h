// Интерактивный виджет 3D-куба ориентации для навигации камерой. Отображает
// кликабельный куб, вращающийся вместе с камерой; клик по граням/рёбрам/углам
// анимирует камеру к этой точке обзора. Поддерживает переключение орто/перспектива.

#pragma once

#include <UniginePlayers.h>
#include <UnigineWidgets.h>
#include <UnigineVector.h>

// Наложение куба ориентации для навигации по вьюпорту. Отрисовывает 3D-куб,
// отражающий ориентацию камеры. Клик по элементам куба запускает плавную анимацию
// вращения камеры. Также отображает навигационные стрелки при выравнивании по оси.
class ViewportCube final
{
public:
	ViewportCube(const Unigine::PlayerPtr &player, float ortho_width, float ortho_height);
	~ViewportCube();

	// Возвращает true, если мышь в данный момент находится над виджетом куба
	bool isHovered() const { return is_hovered; }

	// Позиция виджета куба в экранном пространстве
	void setViewcubePosition(const Unigine::Math::ivec2 &pos);
	Unigine::Math::ivec2 getViewcubePosition() const;

	// Включает/отключает переключатель проекции (орто/перспектива)
	void setChangeProjectionEnabled(bool enabled);
	bool getChangeProjectionEnabled() const;

	// Позиция центрирования камеры для анимации вращения
	void setCenteringPosition(const Unigine::Math::Vec3 &pos) { centering_position = pos; }
	Unigine::Math::Vec3 getCenteringPosition() const { return centering_position; }

	// Минимальная дистанция камеры, используемая во время анимации вращения
	void setMinimalDistance(Unigine::Math::Scalar dist) { min_distance = dist; }
	Unigine::Math::Scalar getMinimalDistance() const { return min_distance; }

	void update();

private:
	// Переключение между перспективной и ортографической проекцией
	void ortho_toggled();

	// Преобразует имя поверхности меша в позицию/вращение грани
	static Unigine::Math::vec3 get_polygon_pos(const char *name);
	static Unigine::Math::quat get_polygon_rot(const Unigine::Math::vec3 &pos);

	// Анимирует плавное вращение камеры к грани куба или стрелке
	void animate_rotation(const Unigine::Math::quat &rot);
	void update_rotation();

private:
	// Закэшированные вращения и позиции для каждой грани
	Unigine::Vector<Unigine::Math::quat> rotations;
	Unigine::Vector<Unigine::Math::vec3> positions;

	// Предварительно вычисленные трансформации для режимов орто и перспективы
	Unigine::Math::mat4 perspective_transform;
	Unigine::Math::mat4 ortho_transform;

	bool is_hovered = false;

	// Элементы UI
	Unigine::WidgetHBoxPtr main_widget;
	Unigine::WidgetHBoxPtr ortho_hbox;
	Unigine::WidgetIconPtr ortho_icon;
	Unigine::WidgetCanvasPtr cube_canvas;
	Unigine::WidgetCanvasPtr arrows_canvas;
	Unigine::EventConnection icon_connection;

	Unigine::PlayerPtr player;

	// Состояние центрирования камеры и анимации
	Unigine::Math::Vec3 centering_position;
	Unigine::Math::quat old_rotation;
	Unigine::Math::quat new_rotation;
	Unigine::Math::Vec3 old_position;
	Unigine::Math::Vec3 new_position;

	// Текстуры для состояний наведения и обычного
	Unigine::String viewcube_texture_touch_path;
	Unigine::String viewcube_texture_untouch_path;

	// Параметры проекции
	float ortho_width = 0;
	float ortho_height = 0;
	bool ortho_enabled = false;

	// Таймер анимации вращения камеры
	float timer_rotation = 0.0f;

	// Минимальная допустимая дистанция для анимации камеры
	Unigine::Math::Scalar min_distance = 0;
};
