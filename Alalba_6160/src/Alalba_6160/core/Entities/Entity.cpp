#include "alalbapch.h"
#include "Entity.h"

namespace Alalba {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
	void Entity::OnUpdate(float t)
	{
		if(this->HasComponent<TransformComponent>() && this->HasComponent<Rigidbody2DComponent>())
		{
			auto& transform = this->GetComponent<TransformComponent>();
			
			transform.CenterVelocity += transform.dV;
			transform.AngularVelocity += transform.dW;

			transform.CenterVelocity  = transform.CenterVelocity *(1.0f-0.0003f);
			transform.AngularVelocity  = transform.AngularVelocity *(1.0f-0.0003f);
			transform.Translation += transform.CenterVelocity * t; 
			transform.Rotation += transform.AngularVelocity * t;

			if(transform.Translation.x <15-7.5/2 || transform.Translation.x > 15+7.5/2 )
				{
					transform.CenterVelocity = glm::vec3{0,0,0};
					this->RemoveComponent<Rigidbody2DComponent>();
				}
			transform.dV = glm::vec3{0,0,0};
			transform.dW = glm::vec3{0,0,0};
		}
	}
}
