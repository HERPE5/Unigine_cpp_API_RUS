#include <UnigineEngine.h>
#include <UnigineLogic.h>
#include <UnigineWorld.h>
#include <UnigineAnimation.h>
#include <UniginePrimitives.h>
#include <UnigineComponentSystem.h>

#include "../../menu_ui/SampleDescriptionWindow.h"
#include "../../utils/Utils.h"

using namespace Unigine;
using namespace Math;

// Этот компонент демонстрирует слои анимации для комбинирования нескольких треков.
// Показаны два режима воспроизведения:
// - Combined: треки на разных слоях воспроизводятся одновременно (позиция + вращение + масштаб сразу)
// - Sequential: треки на одном слое воспроизводятся один за другим (позиция, затем вращение, затем масштаб)
// Один и тот же объект анимации может иметь разные привязки для каждого воспроизведения с помощью setPlaybackOverriddenBind().
class PlaybackLayersSample : public ComponentBase
{
public:
	COMPONENT_DEFINE(PlaybackLayersSample, ComponentBase);
	COMPONENT_INIT(init);
	COMPONENT_SHUTDOWN(shutdown);

private:
	// Создаются объекты анимации и запускаются оба режима воспроизведения.
	void init()
	{
		create_animations();

		// Создаём объекты для анимации
		NodePtr parent_0 = NodeDummy::create();
		NodePtr parent_1 = NodeDummy::create();

		NodePtr box_node_combined = Primitives::createBox(Math::vec3_one);
		box_node_combined->setName("box_node_combined");
		box_node_combined->setID(123);
		box_node_combined->setParent(parent_0);
		parent_0->setWorldPosition(Vec3(-2.0f, 0.0f, 1.75f));

		NodePtr box_node_sequential = Primitives::createBox(Math::vec3_one);
		box_node_sequential->setName("box_node_sequential");
		box_node_sequential->setID(456);
		box_node_sequential->setParent(parent_1);
		parent_1->setWorldPosition(Vec3(2.0f, 0.0f, 1.75f));

		playback_combined->play();
		playback_sequential->play();
	}

	// Оба воспроизведения останавливаются при уничтожении компонента.
	void shutdown()
	{
		playback_combined->stop();
		playback_sequential->stop();
	}

	// Создаются три отдельных трека и объединяются в двух разных режимах воспроизведения.
	void create_animations()
	{
		// Один объект анимации используется всеми треками
		AnimationObjectNodePtr anim_obj = AnimationObjectNode::create("box");

		// Трек 1: подпрыгивание по позиции Z
		AnimationTrackPtr position_track = AnimationTrack::create();
		position_track->addObject(anim_obj);

		auto position_modifier = AnimationModifierScalar::create("node.position_z");
		position_modifier->addValue(0.0f, 0.0f, AnimationCurve::KEY_TYPE_SMOOTH);
		position_modifier->addValue(3.0f, 2.0f, AnimationCurve::KEY_TYPE_SMOOTH);
		position_modifier->addValue(6.0f, 0.0f, AnimationCurve::KEY_TYPE_SMOOTH);
		position_track->addObjectModifier(anim_obj, position_modifier);

		// Трек 2: вращение по оси Z
		AnimationTrackPtr rotation_track = AnimationTrack::create();
		rotation_track->addObject(anim_obj);

		auto rotation_modifier = AnimationModifierQuat::create(AnimationModifierQuat::MODE_QUAT, "node.rotation");
		rotation_modifier->addQuatValue(0.0f, quat(0.0f, 0.0f, 0.0f));
		rotation_modifier->addQuatValue(3.0f, quat(0.0f, 0.f, 180.0f));
		rotation_modifier->addQuatValue(6.0f, quat(0.0f, 0.0f, 360.0f));
		rotation_track->addObjectModifier(anim_obj, rotation_modifier);

		// Трек 3: пульсация масштаба
		AnimationTrackPtr scale_track = AnimationTrack::create();
		scale_track->addObject(anim_obj);

		auto scale_modifier = AnimationModifierFVec3::create("node.scale");
		scale_modifier->addValue(0.0f, vec3(1.f, 1.f, 1.f), AnimationCurve::KEY_TYPE_SMOOTH);
		scale_modifier->addValue(3.0f, vec3(1.5f, 1.5f, 0.66f), AnimationCurve::KEY_TYPE_SMOOTH);
		scale_modifier->addValue(6.0f, vec3(1.f, 1.f, 1.f), AnimationCurve::KEY_TYPE_SMOOTH);
		scale_track->addObjectModifier(anim_obj, scale_modifier);

		// Combined-воспроизведение: все треки воспроизводятся одновременно на разных слоях
		{
			playback_combined = AnimationPlayback::create();
			playback_combined->setLoop(true);

			// addLayer() создаёт новый слой для каждого трека - они воспроизводятся параллельно
			playback_combined->setLayerTrack(0, 0, position_track);
			playback_combined->addLayer(rotation_track);	// Слой 1
			playback_combined->addLayer(scale_track);		// Слой 2

			// Переопределяем привязку для этого конкретного воспроизведения (левый куб)
			AnimationBindNodePtr bind = AnimationBindNode::create();
			bind->setNodeDescription(123, "box_node_combined");
			anim_obj->setPlaybackOverriddenBind(playback_combined, bind);
		}

		// Sequential-воспроизведение: треки воспроизводятся один за другим на одном слое
		{
			playback_sequential = AnimationPlayback::create();
			playback_sequential->setLoop(true);

			// addLayerTrack() добавляет треки на один и тот же слой - они воспроизводятся последовательно
			playback_sequential->setLayerTrack(0, 0, position_track);
			playback_sequential->addLayerTrack(0, rotation_track);
			playback_sequential->addLayerTrack(0, scale_track);

			// ApplyBefore/After гарантирует сохранение анимации между переключениями треков
			for (int i = 0; i < playback_sequential->getNumLayerTracks(0); i++)
			{
				playback_sequential->setLayerTrackApplyBefore(0, i, true);
				playback_sequential->setLayerTrackApplyAfter(0, i, true);
			}

			// Переопределяем привязку для этого конкретного воспроизведения (правый куб)
			AnimationBindNodePtr bind = AnimationBindNode::create();
			bind->setNodeDescription(456, "box_node_sequential");
			anim_obj->setPlaybackOverriddenBind(playback_sequential, bind);
		}
	}

	// ========================================================================================

	AnimationPlaybackPtr playback_combined;
	AnimationPlaybackPtr playback_sequential;
};

REGISTER_COMPONENT(PlaybackLayersSample);
