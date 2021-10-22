#include "PhysicsSys.h"
#include "Components.h"
#include "Entity.h"
namespace Alalba
{
// 		Direction checkCollisionY(Entity* solid, TransformComponent* transform, KineticComponent* kinetic) {
//     auto& solidTransform = solid->GetComponent<TransformComponent>();
//     auto direction = Direction::NONE;

//     if (kinetic->speedY >= 0.0f) {
// 			// Falling
// 			if (AABBCollision(
// 				transform->x + TILE_ROUNDNESS / 2,    // Check previous x position
// 				transform->y + kinetic->speedY,
// 				transform->w - TILE_ROUNDNESS,
// 				transform->h,
// 				solidTransform)) {

// 				float distanceTop = abs(solidTransform->top() - (transform->bottom() + kinetic->speedY));
// 				float distanceBottom = abs((transform->top() + kinetic->speedY) - solidTransform->bottom());
// 				if (distanceTop < distanceBottom) {
// 					transform->setBottom(solidTransform->top());
// 					solid->assign<TopCollisionComponent>();
// 					direction = Direction::BOTTOM;
// 				}
// 			}
//     } else {
//         // Jumping
// 			if (AABBCollision(
// 				transform->x + TILE_ROUNDNESS,    // Check previous x position
// 				transform->y + kinetic->speedY,
// 				transform->w - (TILE_ROUNDNESS * 2),
// 				transform->h,
// 				solidTransform)) {

// 				float distanceTop = abs(solidTransform->top() - (transform->bottom() + kinetic->speedY));
// 				float distanceBottom = abs((transform->top() + kinetic->speedY) - solidTransform->bottom());
// 				if (distanceTop > distanceBottom) {
// 					transform->setTop(solidTransform->bottom());
// 					solid->assign<BottomCollisionComponent>();
// 					direction = Direction::TOP;
// 				}
// 			}
//     }
//   return direction;
// }

// Direction checkCollisionX(Entity* solid, TransformComponent* transform, KineticComponent* kinetic) {
// 	auto& solidTransform = solid->GetComponent<TransformComponent>();
// 	auto direction = Direction::NONE;

//     // X-AXIS CHECK
// 	if (AABBCollision(
// 		transform->x + kinetic->speedX,
// 		transform->y + kinetic->speedY + 2,   // Check with updated y position
// 		transform->w,
// 		transform->h - 8, //Ideally should be -4, but this favours Mario ending up on TOP of a tile.
// 		solidTransform)) {

// 		float distanceLeft = abs((transform->left() + kinetic->speedX) - solidTransform->right());
// 		float distanceRight = abs((transform->right() + kinetic->speedX) - solidTransform->left());
		
// 		if (distanceLeft < distanceRight) {
// 			if (transform->left() < solidTransform->right()) {
// 				//item is inside block, push out
// 				transform->x += std::min(.5f, solidTransform->right() - transform->left());
// 			} else {
// 				//item about to get inside the block
// 				transform->setLeft(solidTransform->right());
// 			}
// 			solid->AddComponent<RightCollisionComponent>();
// 			direction = Direction::LEFT;
// 		} else {
// 			if (transform->right() > solidTransform->left()) {
// 				//item is inside block, push out
// 				transform->x -= std::min(.5f, transform->right() - solidTransform->left());
// 			} else {
// 				//item about to get inside the block
// 				transform->setRight(solidTransform->left());
// 			}

// 			solid->AddComponent<LeftCollisionComponent>();
// 			direction = Direction::RIGHT;
// 		}
// 	}
// 	return direction;
// }



	void PhysicsSys::OnUpdate(Scene& scene){
	
		auto entities = scene.GetEntities();
	
		for(auto entity: entities)
		{
			if(entity->HasComponent<GravityComponent>() && entity->HasComponent<KineticComponent>())
			{
				entity->GetComponent<KineticComponent>().accY += GRAVITY;
			}

			// Apply force
			if(entity->HasComponent<TransformComponent>() && entity->HasComponent<KineticComponent>())
			{
				auto& transform = entity->GetComponent<TransformComponent>();
        auto& kinematic = entity->GetComponent<KineticComponent>();
        transform.x += kinematic.speedX;
        transform.y += kinematic.speedY;
        kinematic.speedX += kinematic.accX;
        kinematic.speedY += kinematic.accY;
        if (std::abs(kinematic.speedY) < MARIO_ACCELERATION_X) kinematic.speedY = 0;
        if (std::abs(kinematic.speedX) < MARIO_ACCELERATION_X) kinematic.speedX = 0;
        kinematic.speedY *= FRICTION;
        kinematic.speedX *= FRICTION;

        if (kinematic.speedY > MAX_SPEED_Y) kinematic.speedY = MAX_SPEED_Y;
        if (kinematic.speedX > MAX_SPEED_X) kinematic.speedX = MAX_SPEED_X;

        if (kinematic.speedY < -MAX_SPEED_Y) kinematic.speedY = -MAX_SPEED_Y;
        if (kinematic.speedX < -MAX_SPEED_X) kinematic.speedX = -MAX_SPEED_X;
			}
		}
	}

}