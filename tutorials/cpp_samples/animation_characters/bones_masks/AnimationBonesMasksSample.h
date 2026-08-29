#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineWidgets.h>

// Этот компонент демонстрирует маски костей для выборочного применения данных анимации.
// Маски определяют, какие компоненты трансформации (позиция, вращение, масштаб)
// применяются к конкретным костям, позволяя повторно использовать анимации для персонажей разного размера.
class AnimationBonesMasksSample : public Unigine::ComponentBase
{
public:
	COMPONENT_DEFINE(AnimationBonesMasksSample, ComponentBase);
	COMPONENT_INIT(init);

	// Ссылка на узел ObjectMeshSkinned, содержащий скелетный меш
	PROP_PARAM(Node, mesh_skinned_node);
	// Кости, которые будут получать только данные вращения (позиция и масштаб игнорируются).
	// Полезно для ретаргетинга анимаций между персонажами разных пропорций.
	PROP_ARRAY(String, rotation_only_bones);

private:
	void init();
};
