#include "PhysicsSys.h"
#include "Components.h"
#include "Entity.h"
namespace Alalba
{
	void PhysicsSys::OnUpdate(const Scene& scene){
	
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