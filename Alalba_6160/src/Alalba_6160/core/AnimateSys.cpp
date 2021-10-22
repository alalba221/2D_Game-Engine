#include "AnimateSys.h"
#include "Components.h"
#include "Entity.h"
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

	// 	world->find<AnimationComponent, TextureComponent>([&](Entity* entity) {
	// 		auto animation = entity->get<AnimationComponent>();
	// 		auto texture = entity->get<TextureComponent>();
	// 		animation->counter++;
	// 		if (animation->counter >= animation->duration) {
	// 			if (animation->flipH) texture->flipH = !texture->flipH;
	// 			if (animation->flipV) texture->flipV = !texture->flipV;
	// 			animation->counter = 0;
	// 			animation->currentTexture = (animation->currentTexture + 1) % animation->textures.size();
	// 			texture->id = animation->textures[animation->currentTexture];
	// 			if (!animation->loop && animation->currentTexture == animation->textures.size() - 1) {
	// 				entity->remove<AnimationComponent>();
	// 			}
	// 		}
  //   });
	// }
}