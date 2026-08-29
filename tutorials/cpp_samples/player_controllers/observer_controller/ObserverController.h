// Контроллер свободной камеры в стиле редактора, воспроизводящий поведение камеры UnigineEditor.
// Поддерживает несколько режимов движения: spectator (свободный полёт), panning, rail (движение по
// направлению обзора) и фокусировку на объекте. Использует конечный автомат для переходов.

#pragma once

#include <UnigineComponentSystem.h>

// Свободнолетающая камера с управлением в стиле редактора: режим spectator, панорамирование, rail-масштабирование,
// фокусировка на объекте, передачи скорости (1-3) и экранное меню позиции/скорости.
class ObserverController : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(ObserverController, Unigine::ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	PROP_GROUP("Input")
	PROP_PARAM(String, focus_key, "F", "Focusing Key", "Key to focus the camera on the object, zooming in for a closer view.");
	PROP_PARAM(String, toggle_camera_menu, "F3", "Toggle Camera Menu", "Key to toggle the visibility of the camera menu.");
	PROP_PARAM(String, alt_camera_mode, "ANY_ALT", "Camera Control Modifier", "Modifier key for switching between different camera control modes.");
	PROP_PARAM(String, acceleration_key, "ANY_SHIFT", "Acceleration Key", "Key to activate acceleration mode, typically used for faster movement.");
	PROP_PARAM(String, spectator_mode, "RIGHT", "Spectator Mode Mouse Button", "Mouse button to toggle spectator mode.");
	PROP_PARAM(String, rail_mode, "RIGHT", "Rail Mode Mouse Button", "Mouse button to activate rail mode.");
	PROP_PARAM(String, panning_mode, "MIDDLE", "Panning Mode Mouse Button", "Mouse button to initiate panning mode.");
	PROP_PARAM(Float, panning_rail_scale, 0.01f, "Panning Mode Mouse Button", "Mouse button to initiate panning mode.");

	PROP_GROUP("Velocity")
	PROP_PARAM(String, first_gear_key, "DIGIT_1", "First Gear Key", "Key to activate the first gear (low speed).");
	PROP_PARAM(Float, first_gear_velocity, 5.0f, "First Gear Speed", "Velocity for the first gear.");
	PROP_PARAM(String, second_gear_key, "DIGIT_2", "Second Gear Key", "Key to activate the second gear (medium speed).");
	PROP_PARAM(Float, second_gear_velocity, 50.0f, "Second Gear Speed", "Velocity for the second gear.");
	PROP_PARAM(String, third_gear_key, "DIGIT_3", "Third Gear Key", "Key to activate the third gear (high speed).");
	PROP_PARAM(Float, third_gear_velocity, 500.0f, "Third Gear Speed", "Velocity for the third gear.");
	PROP_PARAM(Float, accelearation_multiplier, 2.0f, "Acceleration Multiplier", "Multiplier for acceleration when the assigned key is held.");

private:
	const float DEFAULT_VELOCITY = 5.0f;		// Резервная скорость, если поле пустое
	const float DEFAULT_POSITION_VALUE = 0;		// Резервная позиция, если поле пустое

	bool edit_text = false;				// True при редактировании текстового поля (отключает ввод камеры)
	bool try_end_focusing = false;		// Сигнализирует о завершении анимации фокусировки
	bool enter_mouse_grab_mode = false;	// Исходное состояние захвата мыши для восстановления

	// Виджеты GUI для меню скорости/позиции
	Unigine::WidgetHBoxPtr menu_layout = nullptr;
	Unigine::WidgetCheckBoxPtr first_gear_checkbox = nullptr;
	Unigine::WidgetCheckBoxPtr second_gear_checkbox = nullptr;
	Unigine::WidgetCheckBoxPtr third_gear_checkbox = nullptr;

	Unigine::Vector<Unigine::WidgetEditLinePtr> edit_lines;	// [0]=скорость, [1-3]=позиция XYZ

	Unigine::Math::Vec3 target_point;	// Цель для анимации фокусировки

	Unigine::Input::KEY _toggle_camera_menu = Unigine::Input::KEY::KEY_UNKNOWN;
	Unigine::Input::KEY _focus_key = Unigine::Input::KEY::KEY_UNKNOWN;
	Unigine::Input::KEY _acceleration_key = Unigine::Input::KEY::KEY_UNKNOWN;
	Unigine::Input::KEY _first_gear_key = Unigine::Input::KEY::KEY_UNKNOWN;
	Unigine::Input::KEY _second_gear_key = Unigine::Input::KEY::KEY_UNKNOWN;
	Unigine::Input::KEY _third_gear_key = Unigine::Input::KEY::KEY_UNKNOWN;

	Unigine::Input::MOUSE_BUTTON _spectator_mode = Unigine::Input::MOUSE_BUTTON::MOUSE_BUTTON_UNKNOWN;
	Unigine::Input::MOUSE_BUTTON _rail_mode = Unigine::Input::MOUSE_BUTTON::MOUSE_BUTTON_UNKNOWN;
	Unigine::Input::MOUSE_BUTTON _panning_mode = Unigine::Input::MOUSE_BUTTON::MOUSE_BUTTON_UNKNOWN;

	Unigine::Input::MODIFIER _alt_camera_mode = Unigine::Input::MODIFIER::MODIFIER_NONE;

	Unigine::PlayerSpectatorPtr player_camera = nullptr;	// Управляемая камера

	// Режимы движения камеры
	enum PlayerMovementState
	{
		IDLE,		// Нет активного движения, ожидание ввода
		SPECTATOR,	// Свободный полёт с обзором мышью (удержание ПКМ)
		RAIL,		// Движение вдоль направления обзора (Alt+ПКМ)
		FOCUSING,	// Анимированное перемещение к выбранному объекту
		PANNING		// Смещение перпендикулярно обзору (Alt+СКМ)
	};

	PlayerMovementState player_state = IDLE;

	// Пресеты скорости, выбираемые цифровыми клавишами 1-3
	enum VelocityGear
	{
		GEAR_FIRST = 1,		// Медленная скорость
		GEAR_SECOND,		// Средняя скорость
		GEAR_THIRD			// Высокая скорость
	};

	VelocityGear velocity_gear = GEAR_FIRST;

	// Условие и цель для переходов конечного автомата
	struct StateTransition
	{
		std::function<bool()> condition;	// Предикат, проверяемый каждый кадр
		PlayerMovementState target_state;	// Состояние для перехода, если условие истинно
	};

	// Определение состояния с callback-функциями жизненного цикла
	struct MovementState
	{
		Unigine::Vector<StateTransition> transitions;	// Возможные выходы из этого состояния
		std::function<void()> on_enter;		// Вызывается один раз при входе в состояние
		std::function<void()> on_exit;		// Вызывается один раз при выходе из состояния
		std::function<void()> on_update;	// Вызывается каждый кадр, пока в состоянии
	};

	Unigine::Map<PlayerMovementState, MovementState> state_map;	// Определение конечного автомата

	// Вспомогательные функции условий переходов состояний
	inline bool try_focusing() const { return Unigine::Input::isKeyDown(_focus_key); }
	inline bool try_exit_rail_mode() const { return Unigine::Input::isMouseButtonUp(_rail_mode); }
	inline bool try_exit_panning_mode() const { return Unigine::Input::isMouseButtonUp(_panning_mode); }
	inline bool try_enter_spectator_mode() const
	{
		// Spectator требует ПКМ без модификатора Alt
		return !Unigine::Input::isModifierEnabled(_alt_camera_mode) && Unigine::Input::isMouseButtonPressed(_spectator_mode);
	}
	inline bool try_enter_rail_mode() const
	{
		// Режим rail требует Alt + ПКМ
		return Unigine::Input::isModifierEnabled(_alt_camera_mode) && Unigine::Input::isMouseButtonPressed(_rail_mode);
	}
	inline bool try_enter_panning_mode() const
	{
		// Панорамирование требует Alt + СКМ
		return Unigine::Input::isModifierEnabled(_alt_camera_mode) && Unigine::Input::isMouseButtonPressed(_panning_mode);
	}


private:
	// Методы жизненного цикла
	void init();
	void update();
	void shutdown();

	// Инициализация, специфичная для состояния
	void init_spectator();	// Включает управление PlayerSpectator
	void init_panning();	// Захватывает мышь для режима панорамирования
	void init_focusing();	// Трассирует луч для поиска цели фокусировки
	void init_menu();		// Создаёт виджеты GUI скорости/позиции

	// Обновления каждого кадра для каждого состояния
	void update_state();		// Проверяет переходы, вызывает обновление текущего состояния
	void update_spectator();	// Скрывает курсор во время свободного полёта
	void update_rail();			// Перемещает камеру вдоль направления обзора
	void update_panning();		// Перемещает камеру перпендикулярно обзору
	void update_focusing();		// Плавно перемещает камеру к целевой точке
	void update_menu();			// Синхронизирует поля позиции с камерой
	void update_edit_field_submission();	// Обрабатывает клавишу Enter в текстовых полях

	// Очистка, специфичная для состояния
	void end_spectator();	// Отключает управление PlayerSpectator
	void end_panning();		// Освобождает захват мыши
	void end_focusing();	// Сбрасывает флаг завершения фокусировки

	// Управление передачами скорости
	void update_gear(VelocityGear new_gear);	// Применяет скорость передачи к камере
	void update_velocity_gear();				// Проверяет клавиши 1-3 для переключения передачи
	void change_gear_text_field(VelocityGear target_gear);	// Обновляет чекбокс GUI
	void set_velocity(VelocityGear target_gear, float velocity);	// Сохраняет пользовательскую скорость

	// Конечный автомат
	void create_state_map();	// Определяет все состояния и переходы
	void switch_state(PlayerMovementState target_state);	// Обрабатывает callback-функции входа/выхода

	void assign_inputs();	// Преобразует строковые имена клавиш в перечисления

	float get_velocity() const;				// Возвращает базовую скорость текущей передачи
	float get_velocity_acceleration() const;	// Возвращает ускоренную скорость (с множителем)
};
