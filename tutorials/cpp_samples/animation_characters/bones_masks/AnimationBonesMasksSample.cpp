#include "AnimationBonesMasksSample.h"

#include <UnigineGui.h>

REGISTER_COMPONENT(AnimationBonesMasksSample);

using namespace Unigine;

void AnimationBonesMasksSample::init()
{
	ObjectMeshSkinnedLegacyPtr skinned = checked_ptr_cast<ObjectMeshSkinnedLegacy>(mesh_skinned_node.get());
	if (skinned.isValid() == false)
	{
		Log::error("AnimationBonesMasksSample::init(): skinned is null\n");
		return;
	}

	// Включаем покостное использование кадров (маски) на слое 0.
	// Это позволяет указать, какие компоненты трансформации получает каждая кость.
	skinned->setLayerFrameUsesEnabled(0, true);

	// Применяем маску "только вращение" к указанным костям.
	// ANIM_FRAME_USES_ROTATION означает, что из анимации берутся только данные вращения,
	// а позиция и масштаб остаются неизменными (сохраняя исходные пропорции кости).
	for (int i = 0; i < rotation_only_bones.size(); i++)
	{
		int bone = skinned->findBone(rotation_only_bones[i]);
		if (bone != -1)
			skinned->setLayerBoneFrameUses(0, bone, ObjectMeshSkinnedLegacy::ANIM_FRAME_USES_ROTATION);
	}
}
