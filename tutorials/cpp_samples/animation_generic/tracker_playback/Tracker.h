#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineInterpreter.h>
#include <UnigineMap.h>

// Обёртка на C++ для системы анимации Tracker (реализованной на UnigineScript).
// Предоставляет статический API для загрузки, управления и воспроизведения треков анимации, созданных
// в инструменте редактора Tracker. Треки - это файлы .track, содержащие анимации с ключевыми кадрами.
// Этот компонент инициализирует скрипт TrackerWrapper и управляет регистрацией треков.
class Tracker : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(Tracker, Unigine::ComponentBase);
	COMPONENT_INIT(init, INT_MIN);		// ранняя инициализация, чтобы быть готовым для других компонентов
	COMPONENT_SHUTDOWN(shutdown, INT_MAX);	// поздняя остановка после других компонентов

	// путь к скрипту TrackerWrapper.usc, реализующему фактическую логику Tracker
	PROP_PARAM(File, tracker_wrapper_usc);
	// файлы треков для загрузки при инициализации
	PROP_ARRAY(File, track_files);

	static bool isTrackerInitialized() { return is_initialized; }

	// управление треками: загрузка/выгрузка файлов .track
	static int addTrack(const char *track_file);
	static void removeTrack(int track_id);
	static void removeTrack(const char *track_name);
	static bool containsTrack(const char *track_name);
	static int getTrackID(const char *track_name);

	// тайминг трека: получение мин/макс диапазона кадров и масштаба времени
	static float getMinTime(int track_id);
	static float getMinTime(const char *track_name);
	static float getMaxTime(int track_id);
	static float getMaxTime(const char* track_name);
	static float getUnitTime(int track_id);	// масштаб времени (кадров в секунду)
	static float getUnitTime(const char* track_name);
	// задаёт текущее время воспроизведения - это вычисляет трек и применяет анимацию
	static void setTime(int track_id, float time);
	static void setTime(const char* track_name, float time);

private:
	void init();
	void shutdown();

	static bool is_wrapper_loaded;

	static const Unigine::Variable init_func;
	static const Unigine::Variable shutdown_func;
	static const Unigine::Variable add_track_func;
	static const Unigine::Variable remove_track_func;
	static const Unigine::Variable get_min_time_func;
	static const Unigine::Variable get_max_time_func;
	static const Unigine::Variable get_unit_time_func;
	static const Unigine::Variable set_func;

	static Unigine::Map<Unigine::String, int> track_ids;

	static Unigine::Variable track_file_var;
	static Unigine::Variable track_id_var;
	static Unigine::Variable time_var;

	static bool is_initialized;
};