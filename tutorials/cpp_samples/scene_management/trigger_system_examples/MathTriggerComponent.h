// Пользовательские компоненты-триггеры с проверкой границ математическим способом.
// WorldMathTrigger проверяет зарегистрированные объекты каждый кадр с помощью проверок "точка внутри".
// WorldIntersectionTrigger использует World::getIntersection для автоматического обнаружения.

#pragma once
#include <UnigineComponentSystem.h>
#include <UnigineCallback.h>
#include <UnigineMathLibBounds.h>
#include <UnigineSignal.h>

// Проверяет зарегистрированные объекты относительно границ сферы или бокса с помощью проверок "точка внутри".
class WorldMathTrigger :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(WorldMathTrigger, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Радиус сферы для обнаружения столкновений
	PROP_PARAM(Float, bound_sphere_size, 5.0f);
	// Размер бокса для обнаружения столкновений
	PROP_PARAM(Float, bound_box_size, 5.0f);
	// Если true, используется сфера, иначе бокс
	PROP_PARAM(Toggle, is_sphere, false);
	// Включает отладочный рендеринг границ
	PROP_PARAM(Toggle, debug, false);


public:
	// Управление объектами - узлы должны быть зарегистрированы для отслеживания
	void addObject(const Unigine::NodePtr& obj);
	void addObjects(const Unigine::Vector<Unigine::NodePtr>& input_objects);
	int getNumObjects() const { return objects.size(); }
	const Unigine::NodePtr& getObjectsByIndex(int index) const { return objects[index]; }
	void removeObject(const Unigine::NodePtr& obj);
	void removeObjectByIndex(int index) { objects.remove(index); }
	void clearObjects() { objects.clear(); }

	// Типы callback для событий входа/выхода
	enum CALLBACK_TRIGGER
	{
		CALLBACK_TRIGGER_ENTER,
		CALLBACK_TRIGGER_LEAVE,
		CALLBACK_TRIGGER_NUM
	};

	// Регистрация callback для событий входа/выхода
	void *addCallback(CALLBACK_TRIGGER callback, Unigine::CallbackBase1<Unigine::NodePtr> *func);
	bool removeCallback(CALLBACK_TRIGGER callback, void *id);
	void clearCallbacks(CALLBACK_TRIGGER callback);

private:
	void init();
	void update();
	void shutdown();

	// Вызывает callback входа для объектов, оказавшихся внутри
	void check_entered();
	// Вызывает callback выхода для покинувших объём объектов
	void check_leave();

	// Обновляет позицию границ в соответствии с трансформацией узла
	void replace_bounds();
	void visualize_bounds();

	// Проверки "точка внутри" для каждого типа формы
	bool check_sphere(const Unigine::NodePtr &obj) const;
	bool check_box(const Unigine::NodePtr &obj) const;

	inline bool is_callback(CALLBACK_TRIGGER callback) const;
	inline void run_callback(CALLBACK_TRIGGER callback,  const Unigine::NodePtr &obj);

private:
	// Зарегистрированные callback для событий входа/выхода
	Unigine::Signal signal[CALLBACK_TRIGGER_NUM];

	// Объекты, отслеживаемые для обнаружения триггера
	Unigine::Vector<Unigine::NodePtr> objects;
	// Объекты, находящиеся в данный момент внутри объёма триггера
	Unigine::Vector<Unigine::NodePtr> entered;

	Unigine::Math::BoundBox bound_box;
	Unigine::Math::BoundSphere bound_sphere;
};


// Использует World::getIntersection для обнаружения любых узлов, входящих в объём или покидающих его.
class WorldIntersectionTrigger :
	public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(WorldIntersectionTrigger, ComponentBase);

	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Радиус сферы для запросов пересечения
	PROP_PARAM(Float, bound_sphere_size, 5.0f);
	// Размер бокса для запросов пересечения
	PROP_PARAM(Float, bound_box_size, 5.0f);
	// Если true, используется сфера, иначе бокс
	PROP_PARAM(Toggle, is_sphere, false);
	// Включает отладочный рендеринг границ
	PROP_PARAM(Toggle, debug, false);

public:
	// Типы callback для событий входа/выхода
	enum CALLBACK_TRIGGER
	{
		CALLBACK_TRIGGER_ENTER,
		CALLBACK_TRIGGER_LEAVE,
		CALLBACK_TRIGGER_NUM
	};

	// Регистрация callback для событий входа/выхода
	void* addCallback(CALLBACK_TRIGGER callback, Unigine::CallbackBase1<Unigine::NodePtr>* func);
	bool removeCallback(CALLBACK_TRIGGER callback, void* id);
	void clearCallbacks(CALLBACK_TRIGGER callback);

private:
	void init();
	void update();
	void shutdown();

	// Вызывает callback входа для вновь обнаруженных узлов
	void check_entered();
	// Вызывает callback выхода для узлов, больше не находящихся в объёме
	void check_leave();

	// Обновляет позицию границ в соответствии с трансформацией узла
	void replace_bounds();
	void visualize_bounds();

	// Запрашивает у мира все узлы внутри границ
	void get_inside_nodes();

	inline bool is_callback(CALLBACK_TRIGGER callback) const;
	inline void run_callback(CALLBACK_TRIGGER callback, const Unigine::NodePtr& obj);

private:
	// Зарегистрированные callback для событий входа/выхода
	Unigine::Signal signal[CALLBACK_TRIGGER_NUM];

	// Узлы, отслеживаемые в данный момент как находящиеся внутри
	Unigine::Vector<Unigine::NodePtr> entered;
	// Узлы, найденные внутри при запросе текущего кадра
	Unigine::Vector<Unigine::NodePtr> inside;

	Unigine::Math::BoundBox bound_box;
	Unigine::Math::BoundSphere bound_sphere;

	// Узлы, исключённые из обнаружения
	Unigine::Vector<Unigine::NodePtr> exclude;

};

