// Порождает узлы декалей следов через регулярные интервалы по мере движения родительского узла.
// Управляет пулом узлов следов, которые переиспользуются циклически.
// Интервал следов и максимальное количество настраиваются во время выполнения.

#pragma once

#include <UnigineComponentSystem.h>

// Размещает отметки следов вдоль пути движущегося узла.
class TrackSpawner : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(TrackSpawner, Unigine::ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_UPDATE(update);

	PROP_PARAM(File, track_node, "Track node")									// Файл узла для порождения как отметки следа
	PROP_PARAM(Float, min_distance_between_tracks_param, 1.0f, "Min distance between tracks");	// Минимальный интервал между следами
	PROP_PARAM(Int, max_number_of_tracks_param, 100, "Max number of tracks");	// Максимум следов в пуле

	void setMinDistanceBetweenTracks(float min_distance) { min_distance_between_tracks = min_distance; }	// Задаёт интервал следов
	void setMaxNumberOfTracks(int max_number);		// Очищает пул и задаёт новый максимум

private:
	void init();
	void update();

	float min_distance_between_tracks{0.1f};		// Текущий порог интервала
	int max_number_of_tracks{100};					// Текущий лимит размера пула

	Unigine::Math::Vec3 last_track_position = Unigine::Math::Vec3_inf;	// Позиция последнего порождённого следа

	Unigine::Vector<Unigine::NodePtr> active_tracks;	// Пул порождённых узлов следов
	int next_active_track_to_reuse = 0;					// Индекс для циклического переиспользования
};