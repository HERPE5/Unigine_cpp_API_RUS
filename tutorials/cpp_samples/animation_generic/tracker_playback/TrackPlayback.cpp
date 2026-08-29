#include "TrackPlayback.h"
#include <UnigineFileSystem.h>
#include <UnigineEngine.h>
#include <UnigineGame.h>
#include "Tracker.h"

REGISTER_COMPONENT(TrackPlayback);

using namespace Unigine;
using namespace Math;

// Получаются ID треков и задаются начальные времена воспроизведения.
void TrackPlayback::init()
{
	if (!Tracker::isTrackerInitialized())
		return;

	// Обращаемся к треку по имени, затем кешируем ID для более быстрого доступа в update()
	if (Tracker::containsTrack("position_track"))
	{
		position_track_id = Tracker::getTrackID("position_track");
		position_track_time = Tracker::getMinTime(position_track_id);
	}

	// Альтернатива: обращение к треку только по имени (проще, но немного медленнее)
	if (Tracker::containsTrack("rotation_track"))
		rotation_track_time = Tracker::getMinTime("rotation_track");

	// Динамически добавляем трек во время выполнения (не предзагружен в компоненте Tracker)
	scale_track_id = Tracker::addTrack(scale_track_path);
	if (scale_track_id != -1)
		scale_track_time = Tracker::getMinTime(scale_track_id);
}

// Все треки продвигаются и вычисляются каждый кадр в цикле ручного воспроизведения.
void TrackPlayback::update()
{
	if (!Tracker::isTrackerInitialized())
		return;

	// Цикл ручного воспроизведения: продвигаем время, зацикливаем в конце, применяем к треку
	// Используем ID трека (кешированный в init) для более быстрого доступа
	if (position_track_id != -1)
	{
		float min_time = Tracker::getMinTime(position_track_id);
		float max_time = Tracker::getMaxTime(position_track_id);
		float unit_time = Tracker::getUnitTime(position_track_id);

		// Продвигаем время на основе времени кадра, масштабированного единицей времени трека
		position_track_time += Game::getIFps() / unit_time;
		if (position_track_time >= max_time)
			position_track_time = min_time;

		// setTime() вычисляет трек в заданный момент времени и применяет анимацию
		Tracker::setTime(position_track_id, position_track_time);
	}

	// Используем имя трека (поиск каждый кадр - проще, но медленнее)
	if (Tracker::containsTrack("rotation_track"))
	{
		float min_time = Tracker::getMinTime("rotation_track");
		float max_time = Tracker::getMaxTime("rotation_track");
		float unit_time = Tracker::getUnitTime("rotation_track");

		rotation_track_time += Game::getIFps() / unit_time;
		if (rotation_track_time >= max_time)
			rotation_track_time = min_time;

		Tracker::setTime("rotation_track", rotation_track_time);
	}

	// Трек масштаба (загружен динамически)
	if (scale_track_id != -1)
	{
		float min_time = Tracker::getMinTime(scale_track_id);
		float max_time = Tracker::getMaxTime(scale_track_id);
		float unit_time = Tracker::getUnitTime(scale_track_id);

		scale_track_time += Game::getIFps() / unit_time;
		if (scale_track_time >= max_time)
			scale_track_time = min_time;

		Tracker::setTime(scale_track_id, scale_track_time);
	}
}
