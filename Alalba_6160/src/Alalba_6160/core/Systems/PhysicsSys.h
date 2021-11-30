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
	private:
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
			//glm::vec3 v10 = shapeB->PointVelocity(p) - shapeA->PointVelocity(p);
			glm::vec3 r0 = p - transform_A.Translation, r1 = p - transform_B.Translation;
			// |Vn|
			glm::vec3 tao = glm::vec3{-n.y, n.x, n.z};

			float vn = -glm::dot(n,v);
			//std::cout<<vn<<std::endl;
			float vt = glm::dot(v,tao);
			//glm::vec3 vn = n * glm::dot(v10,n);
			//glm::vec3 vt = v - vn;
			
			float mu_n = rb2d_A.Restitution;
			float mu_t = rb2d_A.Friction;
			// Coulomb's law
			float alpha = std::max(float(1-mu_t*(1+mu_n)*abs(vn)/abs(vt)),0.0f);

			float J = ((1 ) * vn) /
								( 1.0 / rb2d_A.Mass + 
								1.0 / rb2d_B.Mass +
								glm::cross(r0,n).z * glm::cross(r0,n).z/ rb2d_A.MomentOfInertia + 
								glm::cross(r1,n).z * glm::cross(r1,n).z/ rb2d_B.MomentOfInertia );

			float j = (-1)* glm::dot(v,tao)/
								( 1.0 / rb2d_A.Mass + 
								1.0 / rb2d_B.Mass +
								glm::cross(r0,tao).z * glm::cross(r0,tao).z/ rb2d_A.MomentOfInertia + 
								glm::cross(r1,tao).z * glm::cross(r1,tao).z/ rb2d_B.MomentOfInertia );
			glm::vec3 impluse = n * J + tao * j;

			//std::cout<<glm::to_string(transform_B.CenterVelocity)<<std::endl;
			// glm::vec3 vn_new = vn * (-mu_n);			
			// glm::vec3 vt_new = vt * alpha;

			
			// //double J = (0.4 / timeInterval * max(0., depth - 0.1) + (1 + 0) * v0) / 
			// double J = ((1 + 0.5) * v0) / 
			// 	(1 / shapeA->mass + 1 / shapeB->mass + sqr(r0 % n) / shapeA->momentOfInertia + sqr(r1 % n) / shapeB->momentOfInertia);
			// if (J < 0) return;
			// // Should consider the Coulomb's law
			// double j = -0.2*(v10 * tao) / (1 / shapeA->mass + 1 / shapeB->mass + sqr(r0 % tao) / shapeA->momentOfInertia + sqr(r1 % tao) / shapeB->momentOfInertia);
			
			// //j = max(min(j, mu * J), -mu * J);
			// Vector2D impluse = J * n + j * tao;
			PhysicsSys::AddImpluse(A, p, -impluse);
			PhysicsSys::AddImpluse(B, p, impluse);
		}
		// Constraint *Copy() {
		// 	return new Contact(*this);
		// }
	};
}