// Порождает узлы декалей следов через регулярные интервалы по мере движения родительского узла.
// Управляет пулом узлов следов, которые переиспользуются циклически.
// Интервал следов и максимальное количество настраиваются во время выполнения.

#include "TrackSpawner.h"

#include <UnigineWorld.h>

REGISTER_COMPONENT(TrackSpawner);

using namespace Unigine;
using namespace Math;

// Пул следов очищается, задаётся новый максимум.
void TrackSpawner::setMaxNumberOfTracks(int max_number)
{
	// Существующие следы планируются к удалению
	for (const auto &track : active_tracks)
		track.deleteLater();
	active_tracks.clear();

	// Применяется новый лимит, индекс переиспользования сбрасывается
	max_number_of_tracks = max_number;
	next_active_track_to_reuse = 0;
}

// Параметры инициализируются из значений свойств.
void TrackSpawner::init()
{
	// Параметры времени выполнения устанавливаются из свойств редактора
	setMinDistanceBetweenTracks(min_distance_between_tracks_param.get());
	setMaxNumberOfTracks(max_number_of_tracks_param.get());
}

// След порождается или переиспользуется при превышении порога расстояния.
void TrackSpawner::update()
{
	// Следы не порождаются, если лимит равен нулю
	if (max_number_of_tracks == 0)
		return;

	// Квадрат расстояния вычисляется для эффективности
	auto world_position = node->getWorldPosition();
	auto distance2 = (last_track_position - world_position).length2();

	// След пропускается, если слишком близко к предыдущей позиции
	if (distance2 < min_distance_between_tracks * min_distance_between_tracks)
		return;

	// Текущая позиция сохраняется для следующей проверки расстояния
	last_track_position = world_position;

	NodePtr current_track;
	if (active_tracks.size() < max_number_of_tracks)
	{
		// Новый след загружается, когда в пуле есть место
		current_track = World::loadNode(track_node.get());
		active_tracks.push_back(current_track);
	}
	else
	{
		// Существующий след переиспользуется в циклическом порядке
		current_track = active_tracks[next_active_track_to_reuse];
		next_active_track_to_reuse = (next_active_track_to_reuse + 1) % active_tracks.size();
	}

	// След позиционируется в текущем местоположении спавнера
	current_track->setTransform(node->getWorldTransform());
}
