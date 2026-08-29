// Демонстрирует WorldSplineGraph для размещения геометрии вдоль путей сплайнов в мире.
// В отличие от SplineGraph (только данные), WorldSplineGraph создаёт экземпляры исходных узлов вдоль
// каждого сегмента. Режим TILING повторяет исходную геометрию, а режим STRETCH масштабирует её.

#include <UnigineComponentSystem.h>
#include <UnigineVisualizer.h>
#include <UnigineWorlds.h>

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/Utils.h"

using namespace Unigine;
using namespace Math;

class WorldSplineGraphSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(WorldSplineGraphSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

	// Путь к файлу сплайна .spl, определяющему кривую
	PROP_PARAM(File, spline_file);
	// Файл узла для создания экземпляров вдоль сплайна (например, сегмент дороги)
	PROP_PARAM(File, segment_node);

private:
	void init()
	{
		Unigine::String spline_path = spline_file.get();
		if (spline_path.size() <= 0)
		{
			Unigine::Log::error("WorldSplineGraphSample::init(): Spline File param is empty!\n");
			return;
		}

		Unigine::String node_path = segment_node.get();
		if (node_path.size() <= 0)
		{
			Unigine::Log::error("WorldSplineGraphSample::init(): Segment File param is empty!\n");
			return;
		}

		// Создаём узел WorldSplineGraph, который будет генерировать геометрию
		world_spline_graph = WorldSplineGraph::create();

		// Загружаем данные сплайна из файла .spl
		world_spline_graph->load(spline_path);

		// Получаем все сегменты загруженного сплайна
		Vector<SplineSegmentPtr> segments;
		world_spline_graph->getSplineSegments(segments);

		// Настраиваем каждый сегмент для использования исходного узла
		for (int i = 0; i < segments.size(); i += 1)
		{
			SplineSegmentPtr &segment = segments[i];
			// Назначаем исходный узел и указываем ось направления (в данном случае X)
			segment->assignSource(node_path, SplineSegment::FORWARD_X);
			// Режим TILING повторяет геометрию, чтобы заполнить длину сегмента
			// Режим STRETCH масштабировал бы один экземпляр под нужный размер
			segment->setSegmentMode(node_path, SplineSegment::SEGMENT_TILING);
		}

		// Перегенерируем всю геометрию после изменения настроек
		// Это создаёт экземпляры исходных узлов вдоль каждого сегмента
		world_spline_graph->rebuild();

		visualizer_enabled = Visualizer::isEnabled();
		Visualizer::setEnabled(true);
	}

	void shutdown()
	{
		Visualizer::setEnabled(visualizer_enabled);
	}

	// ========================================================================================

	bool visualizer_enabled = false;
	// Узел WorldSplineGraph, генерирующий геометрию вдоль пути
	WorldSplineGraphPtr world_spline_graph;
};

REGISTER_COMPONENT(WorldSplineGraphSample);
