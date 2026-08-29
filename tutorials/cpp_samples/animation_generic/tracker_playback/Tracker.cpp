// Предоставляет интерфейс на C++ к системе Tracker через обёртку на UnigineScript.
// Треки - это файлы анимации (.track), которые можно загружать, опрашивать по тайминг-информации
// и вычислять в конкретные моменты времени. Скрипт-обёртка обрабатывает фактическое воспроизведение трека.

#include "Tracker.h"
#include <UnigineFileSystem.h>
#include <UnigineEngine.h>

REGISTER_COMPONENT(Tracker);

using namespace Unigine;
using namespace Math;

bool Tracker::is_wrapper_loaded = false;

// Имена функций для вызова обёртки TrackerWrapper на UnigineScript
const Variable Tracker::init_func = Variable("TrackerWrapper::init");
const Variable Tracker::shutdown_func = Variable("TrackerWrapper::shutdown");
const Variable Tracker::add_track_func = Variable("TrackerWrapper::addTrack");
const Variable Tracker::remove_track_func = Variable("TrackerWrapper::removeTrack");
const Variable Tracker::get_min_time_func = Variable("TrackerWrapper::getMinTime");
const Variable Tracker::get_max_time_func = Variable("TrackerWrapper::getMaxTime");
const Variable Tracker::get_unit_time_func = Variable("TrackerWrapper::getUnitTime");
const Variable Tracker::set_func = Variable("TrackerWrapper::set");

Map<String, int> Tracker::track_ids;

Variable Tracker::track_file_var = Variable("");
Variable Tracker::track_id_var = Variable(0);
Variable Tracker::time_var = Variable(0.0f);

bool Tracker::is_initialized = false;

// Загружает файл .track и возвращает его ID для последующих операций.
// Имя трека извлекается из имени файла для поиска в карте track_ids.
int Tracker::addTrack(const char *track_file)
{
	if (isTrackerInitialized() && FileSystem::isFileExist(track_file) &&
		!String::compare(FileSystem::getExtension(track_file), "track"))
	{
		// Извлекаем имя трека из пути: "folder/trackname.track" -> "trackname"
		auto track_name = String::split(track_file, ".")[0];
		auto parts = String::split(track_name, "/");
		track_name = parts[parts.size() - 1];

		if (!track_ids.contains(track_name))
		{
			// Вызываем скрипт-обёртку для загрузки трека и получения его ID
			track_file_var.setString(track_file);
			int track_id = Engine::get()->runWorldFunction(add_track_func, track_file_var).getInt();
			track_ids.insert(track_name, track_id);

			return track_id;
		}
		else
		{
			Log::warning("Tracker::addTrack: %s already added\n", track_file);
			return track_ids[track_name];
		}
	}

	return -1;
}

// Трек выгружается и удаляется из карты track_ids по ID.
void Tracker::removeTrack(int track_id)
{
	if (isTrackerInitialized())
	{
		auto it = track_ids.findData(track_id);
		if (it != track_ids.end())
		{
			track_id_var.setInt(track_id);
			Engine::get()->runWorldFunction(remove_track_func, track_id_var);

			track_ids.remove(it);
		}
	}
}

// Трек выгружается и удаляется из карты track_ids по имени.
void Tracker::removeTrack(const char* track_name)
{
	if (isTrackerInitialized() && track_ids.contains(track_name))
		removeTrack(track_ids[track_name]);
}

// Возвращает true, если трек с заданным именем загружен.
bool Tracker::containsTrack(const char* track_name)
{
	if (isTrackerInitialized())
		return track_ids.contains(track_name);

	return false;
}

// Возвращает ID трека для заданного имени, или -1, если не найден.
int Tracker::getTrackID(const char* track_name)
{
	if (isTrackerInitialized() && track_ids.contains(track_name))
		return track_ids[track_name];

	return -1;
}

// Возвращается минимальное время (первый ключевой кадр) трека.
float Tracker::getMinTime(int track_id)
{
	if (isTrackerInitialized())
	{
		track_id_var.setInt(track_id);
		return Engine::get()->runWorldFunction(get_min_time_func, track_id_var).getFloat();
	}

	return 0.0f;
}

// Минимальное время возвращается по имени трека.
float Tracker::getMinTime(const char* track_name)
{
	if (isTrackerInitialized() && track_ids.contains(track_name))
		return getMinTime(track_ids[track_name]);

	return 0.0f;
}

// Возвращается максимальное время (последний ключевой кадр) трека.
float Tracker::getMaxTime(int track_id)
{
	if (isTrackerInitialized())
	{
		track_id_var.setInt(track_id);
		return Engine::get()->runWorldFunction(get_max_time_func, track_id_var).getFloat();
	}

	return 0.0f;
}

// Максимальное время возвращается по имени трека.
float Tracker::getMaxTime(const char* track_name)
{
	if (isTrackerInitialized() && track_ids.contains(track_name))
		return getMaxTime(track_ids[track_name]);

	return 0.0f;
}

// Возвращается единица времени (масштаб времени, кадров в секунду) трека.
float Tracker::getUnitTime(int track_id)
{
	if (isTrackerInitialized())
	{
		track_id_var.setInt(track_id);
		return Engine::get()->runWorldFunction(get_unit_time_func, track_id_var).getFloat();
	}

	return 0.0f;
}

// Единица времени возвращается по имени трека.
float Tracker::getUnitTime(const char* track_name)
{
	if (isTrackerInitialized() && track_ids.contains(track_name))
		return getUnitTime(track_ids[track_name]);

	return 0.0f;
}

// Трек вычисляется в заданный момент времени, применяется анимация.
void Tracker::setTime(int track_id, float time)
{
	if (isTrackerInitialized())
	{
		time_var.setFloat(time);
		track_id_var.setInt(track_id);
		Engine::get()->runWorldFunction(set_func, track_id_var, time_var);
	}
}

// Время трека задаётся по имени трека.
void Tracker::setTime(const char* track_name, float time)
{
	if (isTrackerInitialized() && track_ids.contains(track_name))
		setTime(track_ids[track_name], time);
}

// Скрипт TrackerWrapper проверяется и инициализируется, затем загружаются треки.
void Tracker::init()
{
	// Проверяем, назначен ли скрипт TrackerWrapper в качестве логики мира
	String tracker_wrapper_guid = FileSystem::guidToPath(FileSystem::getGUID(tracker_wrapper_usc));
	is_wrapper_loaded = (String::compare(World::getScriptName(), tracker_wrapper_guid) == 0);

	// Если обёртка не загружена, назначаем её и перезагружаем мир для применения изменений
	if (!is_wrapper_loaded)
	{
		World::setScriptName(tracker_wrapper_guid);
		World::setScriptExecute(true);
		World::saveWorld();
		World::reloadWorld();
		return;
	}

	// Инициализируем систему tracker в скрипте-обёртке
	Engine::get()->runWorldFunction(init_func);
	is_initialized = true;

	// Загружаем все треки, указанные в массиве свойств компонента
	if (!track_files.nullCheck())
	{
		for (int i = 0; i < track_files.size(); i++)
			addTrack(track_files[i].get());
	}
}

// Система Tracker останавливается, все треки выгружаются.
void Tracker::shutdown()
{
	if (isTrackerInitialized())
	{
		Engine::get()->runWorldFunction(shutdown_func);

		track_ids.clear();
		is_wrapper_loaded = false;
		is_initialized = false;
	}
}
