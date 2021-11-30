#include "PhysicsSys.h"
#include "Alalba_6160/core/Components.h"
#include "Alalba_6160/core/Entities/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
namespace Alalba
{
	
	int PhysicsSys::nEntities = 0;
	Entity PhysicsSys::m_Entities[20];
	
	void PhysicsSys::Init(Scene& scene){
		std::cout<<"Physic system init"<<std::endl;
	}
	void PhysicsSys::AddEntity(Entity& e){
		m_Entities[nEntities] = e;
		nEntities++;
	}
	// r : the hiting point in the world coordinate
	void PhysicsSys::AddImpluse(Entity& e, glm::vec3 r, glm::vec3 p) {
		
		if(e.GetComponent<Rigidbody2DComponent>().Type == Rigidbody2DComponent::BodyType::Static) return;
		auto& tranform = e.GetComponent<TransformComponent>();
		auto rg2d = e.GetComponent<Rigidbody2DComponent>();
		tranform.CenterVelocity += p * (float)(1.0/rg2d.Mass);
		tranform.AngularVelocity += glm::cross((r - tranform.Translation),p) 
																* (float)(1.0/rg2d.MomentOfInertia);
	}

	void PhysicsSys::OnUpdate(Scene& scene,float t){
		
		auto view = scene.Reg().view<Rigidbody2DComponent>();
		// Apply Impulse caused by gravity
		for(auto e:view)
		{
			Entity entity = {e, &scene};
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
			AddImpluse(entity,transform.Translation, glm::vec3(0, 9.8, 0) * (float)(rb2d.Mass * t));
		}
		
		std::cout<<"Physic system update"<<std::endl;
	}
	void PhysicsSys::testPh(){
		std::cout<<"testPh"<<std::endl;
		
		for(int i=0;i<nEntities;i++)
		{
			std::cout<<m_Entities[i].GetComponent<TransformComponent>().CenterVelocity.y<<std::endl;
		}
	}
}