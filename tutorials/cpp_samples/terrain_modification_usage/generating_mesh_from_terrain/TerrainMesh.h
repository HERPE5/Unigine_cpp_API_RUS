// Генерирует динамический меш из данных высоты terrain с помощью асинхронного LandscapeFetch.
// Сетка позиций сэмплов запрашивается асинхронно с настраиваемым уровнем параллелизма.
// Полученные вершины меша содержат высоту terrain и цвет albedo из landscape.

#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineObjects.h>

// Запрашивает данные terrain и генерирует динамическое представление меша.
class TerrainMesh : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TerrainMesh, Unigine::ComponentBase);
	COMPONENT_UPDATE(update);

	PROP_PARAM(Material, material_prop, "Material");	// Материал, применяемый к сгенерированному мешу

	void setResolution(const Unigine::Math::ivec2 &in_resolution) { resolution = in_resolution; }	// Задаёт разрешение сетки вершин
	void setMaxFetchers(int in_max_fetchers) { max_fetchers = in_max_fetchers; }					// Задаёт лимит параллельных запросов

	void setDrawBoundingBox(bool in_draw_bounding_box) { draw_bounding_box = in_draw_bounding_box; }	// Включает визуализацию ограничивающего бокса
	void setDrawWireframe(bool in_draw_wireframe) { draw_wireframe = in_draw_wireframe; }			// Включает визуализацию каркаса

	int getTotalFetchPositions() const { return fetch_positions.size(); }		// Возвращает общее количество точек сэмплирования
	int getCompletedFetchPositions() const { return fishined_fetch_count; }		// Возвращает количество завершённых запросов

	void run();		// Запускает асинхронную операцию запроса terrain

	static constexpr int INVALID_FETCH_HEIGHT = -1000000000;	// Значение высоты, возвращаемое LandscapeFetch при отсутствии landscape

private:
	void update();
	void generate_mesh();		// Строит меш из запрошенных данных terrain

	Unigine::Math::ivec2 resolution{64, 64};	// Разрешение сетки по X и Y
	int max_fetchers{64};						// Максимум параллельных асинхронных запросов

	Unigine::Vector<Unigine::Math::Vec2> fetch_positions;	// Мировые позиции для сэмплирования
	int next_fetch_index{0};								// Индекс следующей позиции для запроса

	// Одиночный асинхронный запрос terrain с индексом вывода.
	struct Fetcher
	{
		Unigine::LandscapeFetchPtr landscape_fetch;		// Объект асинхронного запроса
		int out_data_index{0};							// Индекс вывода в массиве fetch_data
	};
	Unigine::Vector<Fetcher> fetchers;		// Пул параллельных запросов

	// Данные высоты и цвета, полученные из terrain.
	struct FetchData
	{
		float height;					// Высота terrain в точке сэмплирования
		Unigine::Math::vec4 albedo;		// Цвет albedo terrain в точке сэмплирования
	};
	Unigine::Vector<FetchData> fetch_data;	// Массив результатов для всех точек сэмплирования
	int fishined_fetch_count{0};			// Количество завершённых запросов

	Unigine::ObjectMeshDynamicPtr mesh_dynamic;		// Сгенерированный объект меша

	// Конечный автомат для асинхронной операции запроса.
	enum class State
	{
		IDLE,		// Готов к запуску нового запроса
		FETCHING	// Асинхронные запросы в процессе
	};
	State state{State::IDLE};

	bool draw_bounding_box{true};		// Флаг визуализации ограничивающего бокса
	bool draw_wireframe{false};			// Флаг визуализации каркаса
};
