#pragma once
#include "Alalba_6160/core/Scene.h"
#include "Alalba_6160/core/Entities/Entity.h"
#include "Alalba_6160/core/Components.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
// test
#include <glm/gtx/string_cast.hpp>
namespace Alalba
{

	class Contact;
	struct  Delta {
		glm::vec3 deltaV;
		glm::vec3 deltaAV;
	};
	class PhysicsSys
	{
		friend Contact;
	public:
		static void Init(Scene& scene);
		static void OnUpdate(Scene& scene, float t);
		static void AddEntity(Entity& e);

		static void AddImpluse(Entity& e, glm::vec3 r, glm::vec3 p);
		static void testPh();
		
		static bool TestCircleCollision(Entity& a, Entity& b);
	//private:
		static	Entity m_Entities[20];
		static int nEntities;

		static std::vector<Contact*> m_Contact;
	// Graphics *graphics;
	// vector<Constraint *> constraints;
	// vector<Constraint *> constantConstraints;
	};

	class Contact {
			
	public:
		Entity A, B;
		glm::vec3 p, n;
		// double elasticConstant;
		float depth;
	private:
		glm::vec3 GetPointVelocity(const Entity& e, glm::vec3 point)
		{
			glm::vec3 center = e.GetComponent<TransformComponent>().Translation;
			glm::vec3 centerVelocity = e.GetComponent<TransformComponent>().CenterVelocity;
			glm::vec3 angularVelocity = e.GetComponent<TransformComponent>().AngularVelocity;;
			return centerVelocity + glm::cross(angularVelocity,point-center);
		}
	public:
		Contact(Entity& a, Entity& b, glm::vec3 _p, glm::vec3 _n, float _depth) : A(a), B(b), p(_p), n(_n), depth(_depth) {}
		
		void Process() {
			// b hit a 
			// v10: vb - va
			// n: b-a/||b-a||
			auto& transform_A = A.GetComponent<TransformComponent>();
			auto& rb2d_A = A.GetComponent<Rigidbody2DComponent>();
			
			auto& transform_B = B.GetComponent<TransformComponent>();
			auto& rb2d_B = B.GetComponent<Rigidbody2DComponent>();
			glm::vec3 v = GetPointVelocity(B,p) - GetPointVelocity(A,p) ;
			
			if(glm::dot(v,n)>0.0) return;
			// /// Matrix form
			// glm::vec3 vn = n*glm::dot(v,n);
			
			// glm::vec3 vt = v-vn;
			// glm:: vec3 tao = glm:;vec3{-n.y,n.x,n.z};
			
			// float mu_n = rb2d_A.Restitution;
			// float mu_t = rb2d_A.Friction;
			// // Coulomb's law
			// float alpha = std::max(float(1-mu_t*(1+mu_n)*glm::length(vn)/glm::length(vt)),0.0f);

			// glm::vec3 vn_new = vn * (-mu_n);
			// glm::vec3 vt_new = vt * alpha;

			// glm::vec3 v_new = vn_new + vt_new;
			// glm::vec3 r0 = p - transform_A.Translation, r1 = p - transform_B.Translation;
			
			// float K = 1.0/
			// 					( 1.0 / rb2d_A.Mass + 1.0 / rb2d_B.Mass +
			// 					(-1)*
			// 					glm::dot(glm::cross(glm::cross(r0,n) * (float(1.0/rb2d_A.MomentOfInertia)),r0),n)  +
			// 					(-1)*
			// 					glm::dot(glm::cross(glm::cross(r1,n) * (float(1.0/rb2d_B.MomentOfInertia)),r1),n)   );
			
			// glm::vec3 j = (v_new-v) * (float(1.0/K));
			
			// PhysicsSys::AddImpluse(A, p, -j);
			// PhysicsSys::AddImpluse(B, p, j);

			

//// 

			glm::vec3 r0 = p - transform_A.Translation, r1 = p - transform_B.Translation;
			// |Vn|
			
			glm::vec3 tao = glm::vec3{-n.y, n.x, n.z};
			if(glm::dot(tao,n)<0)
				tao = -tao;

			float vn = glm::dot(n,v);
			float vt = glm::dot(v,tao);			
			float mu_n = rb2d_A.Restitution;
			float mu_t = rb2d_A.Friction;
			// Coulomb's law
			float alpha = std::max(float(1-mu_t*(1+mu_n)*abs(vn)/abs(vt)),0.0f);
			
			float J = (-(1 + mu_n ) * vn) /
								( 1.0 / rb2d_A.Mass + 1.0 / rb2d_B.Mass +
								glm::dot(glm::cross(glm::cross(r0,n) * (float(1.0/rb2d_A.MomentOfInertia)),r0),n)  +
								glm::dot(glm::cross(glm::cross(r1,n) * (float(1.0/rb2d_B.MomentOfInertia)),r1),n)   );
	
			float j = (-alpha)* glm::dot(v,tao)/
								( 1.0 / rb2d_A.Mass + 1.0 / rb2d_B.Mass +
								glm::dot(glm::cross(glm::cross(r0,tao) * (float(1.0/rb2d_A.MomentOfInertia)),r0),tao)  +
								glm::dot(glm::cross(glm::cross(r1,tao) * (float(1.0/rb2d_B.MomentOfInertia)),r1),tao)   );


			glm::vec3 impluse = n * J + tao * j;

			PhysicsSys::AddImpluse(A, p, -impluse);
			PhysicsSys::AddImpluse(B, p, impluse);
		}
		// Constraint *Copy() {
		// 	return new Contact(*this);
		// }
	};
}