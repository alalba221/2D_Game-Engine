#include "AnimateSys.h"
#include "Alalba_6160/core/Components.h"
#include "Alalba_6160/core/Entities/Entity.h"
namespace Alalba
{
	void AnimateSys::OnUpdate(Scene& scene){
	
		auto entities = scene.GetEntities();
		
		for(auto entity: entities)
		{
			if(entity->HasComponent<AnimationComponent>())
			{
				auto& animation = entity->GetComponent<AnimationComponent>();
				auto& texture = entity->GetComponent<TextureComponent>();
				animation.counter++;
				if (animation.counter >= animation.duration) {
					if (animation.flipH) texture.flipH = !texture.flipH;
					if (animation.flipV) texture.flipV = !texture.flipV;
					animation.counter = 0;
					animation.currentTexture = (animation.currentTexture + 1) % animation.textures.size();
					texture.id = animation.textures[animation.currentTexture];
					if (!animation.loop && animation.currentTexture == animation.textures.size() - 1) {
						entity->RemoveComponent<AnimationComponent>();
					}
				}
			}
		}
	}
}