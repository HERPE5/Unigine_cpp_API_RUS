// Деформация террейна в реальном времени с использованием алгоритма Marching Cubes.
// Позволяет копать и заполнять кликами мыши. Воксельное поле хранится
// в 3D-текстуре; генерация меша выполняется асинхронно.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWorld.h>

#include "../../menu_ui/SampleDescriptionWindow.h"

class AsyncMarchingCubes;

// Обрабатывает пользовательский ввод и делегирует генерацию меша AsyncMarchingCubes.
class MeshDigger : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(MeshDigger, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);
	COMPONENT_SHUTDOWN(shutdown);

	// Количество вокселей вдоль каждой оси 3D-поля
	PROP_PARAM(Int, field_size, 64, nullptr, "Number of marching cubes along one side of the field");
	// Размер каждого воксельного куба в мировом пространстве
	PROP_PARAM(Float, marching_cube_size, 0.2f, nullptr, "Marching Cube edge length");
	// Размер кисти для операций копания/заполнения в воксельных единицах
	PROP_PARAM(Float, digging_radius, 2.f);
	// Материал, применяемый к сгенерированному мешу террейна
	PROP_PARAM(Material, mat, "Ground material");

private:
	void init();
	void update();
	void shutdown();

private:
	// Управляет воксельным полем и генерацией меша
	AsyncMarchingCubes *marching_cubes;
	// Ссылка на сгенерированный меш для проверок пересечений
	Unigine::ObjectPtr ground_object;
	// Закэшированная обратная трансформация для преобразования мир-локальные координаты
	Unigine::Math::Mat4 ground_itransform;
	// Переиспользуемый объект результата пересечения
	Unigine::WorldIntersectionPtr intersection = Unigine::WorldIntersection::create();

	SampleDescriptionWindow samples_description_window;
};


// Генерирует меш террейна из воксельного поля с использованием алгоритма Marching Cubes.
// Обновления меша выполняются асинхронно во избежание задержек кадра.
class AsyncMarchingCubes
{
public:
	AsyncMarchingCubes(int num_cubes, float cube_edge = 0.2f);
	~AsyncMarchingCubes() { destroy(); }

	void create(int num_cubes, float cube_edge = 0.2f);
	void destroy();

	void update();

	// Сферическая кисть для изменения воксельного поля
	struct BrushSphere
	{
		Unigine::Math::vec3 pos{};	 // Позиция центра в воксельных координатах
		float radius{6};			 // Радиус кисти в вокселях
		float k{2};					 // Сила: положительная заполняет, отрицательная копает
	};
	// Ставит операцию кисти в очередь для следующего обновления меша
	void addBrush(const BrushSphere &a) { actions.append(a); }

	Unigine::ObjectPtr getObject() const { return object; }
	void setMaterial(const Unigine::MaterialPtr &mat) { material = mat; }

private:
	// Запускает асинхронную генерацию меша, если она ещё не выполняется
	void run(bool force = false);
	// Генерирует начальное воксельное поле на основе карты высот с использованием шума
	void create_field();
	// Генерирует треугольники из воксельного поля с использованием таблиц поиска
	void marching_cubes(Unigine::MeshPtr mesh) const;
	// Применяет все поставленные в очередь операции кисти к воксельному полю
	void brush_field();
	// Изменяет значения вокселей в пределах радиуса сферы
	void add_sphere(Unigine::Math::vec3 pos, float radius, float k);
	// Асинхронный callback: применяет кисти и пересоздаёт меш
	void update_ram(Unigine::MeshPtr mesh);
	// Асинхронный callback: включает столкновения после обновления меша
	void update_ram_done();

private:
	// Сгенерированный объект меша террейна
	Unigine::ObjectMeshStaticPtr object;
	// 3D-текстура, хранящая значения плотности вокселей
	Unigine::ImagePtr field;

	int size{0};	  // Размер воксельной сетки по каждой оси
	int size2{0};	  // size * size (закэшировано для индексации)
	float cube_edge_length{0.2f};

	// Генератор шума Перлина для начального террейна
	Unigine::Math::Noise noise;

	// Ожидающие операции кисти (основной поток)
	Unigine::Vector<BrushSphere> actions;
	// Операции кисти, обрабатываемые (асинхронный поток)
	Unigine::Vector<BrushSphere> async_actions;

	Unigine::MaterialPtr material;

	// Предотвращает одновременную генерацию меша
	Unigine::AtomicBool is_running{false};
	// Флаг безопасности для уничтожения во время асинхронной операции
	bool is_deleted = false;

	// Таблицы поиска Marching Cubes
	static const short marching_cubes_edges[];
	static const char marching_cubes_triangles[];
	// Позиции углов единичного куба
	static const Unigine::Math::vec3 cell_0;
	static const Unigine::Math::vec3 cell_1;
	static const Unigine::Math::vec3 cell_2;
	static const Unigine::Math::vec3 cell_3;
	static const Unigine::Math::vec3 cell_4;
	static const Unigine::Math::vec3 cell_5;
	static const Unigine::Math::vec3 cell_6;
	static const Unigine::Math::vec3 cell_7;
};
