#include "PhysicsSys.h"

namespace Alalba
{
	
	int PhysicsSys::nEntities = 0;
	Entity PhysicsSys::m_Entities[20];
	std::vector<Contact*> PhysicsSys::m_Contact;
	
	void PhysicsSys::Init(Scene& scene){
		std::cout<<"Physic system init"<<std::endl;
	}
	void PhysicsSys::AddEntity(Entity& e){
		m_Entities[nEntities] = e;
		nEntities++;
	}
	// r : the hiting point in the world coordinate
	void PhysicsSys::AddImpluse(Entity& e, glm::vec3 r, glm::vec3 p) {
		if(e.GetComponent<TagComponent>().Tag == "Ground")
			e.GetComponent<Rigidbody2DComponent>().Type = Rigidbody2DComponent::BodyType::Static;
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

			if(entity.GetComponent<TagComponent>().Tag == "Player")
				AddImpluse(entity,transform.Translation, glm::vec3(0, 9.8, 0) * (float)(rb2d.Mass * t));
		}


		for (int i = 0; i < nEntities; i++)
			for (int j = i + 1; j < nEntities; j++)
				TestCircleCollision(m_Entities[i], m_Entities[j]);
		// for (int K = 0; K < 2; K++)
		
		for (int i = 0; i < (int)m_Contact.size(); i++)
		{
			m_Contact[i]->Process();
			std::cout<<i<<" "<<glm::to_string(m_Contact[i]->p)<<std::endl;
		}
		
		for (; !m_Contact.empty(); ) {
			delete m_Contact.back();
			m_Contact.pop_back();
		}
	}

	bool PhysicsSys::TestCircleCollision(Entity& a, Entity& b) {
		
		auto& transform_a = a.GetComponent<TransformComponent>();
		auto& rb2d_a = a.GetComponent<Rigidbody2DComponent>();
		
		auto& transform_b = b.GetComponent<TransformComponent>();
		auto& rb2d_b = b.GetComponent<Rigidbody2DComponent>();

		glm::vec3 n = transform_b.Translation - transform_a.Translation;
		float depth = rb2d_a.CircleRadius + rb2d_b.CircleRadius - glm::length(n);
		
		if (depth < 0.0) return false;
		
		glm::vec3 norm = glm::normalize(n);
		m_Contact.push_back(new Contact(a, b, transform_a.Translation + norm * rb2d_a.CircleRadius, norm, depth));
		return true;
	}
	void PhysicsSys::testPh(){
		std::cout<<"testPh"<<std::endl;
		
		for(int i=0;i<nEntities;i++)
		{
			std::cout<<m_Entities[i].GetComponent<TransformComponent>().CenterVelocity.y<<std::endl;
		}
	}
}