#pragma once
#include "Alalba_6160/core/Scene.h"

namespace Alalba
{
	class PhysicsSys
	{
	public:
		static void Init(Scene& scene);
		static void OnUpdate(Scene& scene, float t);
		static void AddEntity(Entity& e);

		static void AddImpluse(Entity& e, glm::vec3 r, glm::vec3 p);
		static void testPh();
	private:
		static	Entity m_Entities[20];
		static int nEntities;
	// Graphics *graphics;
	// vector<Constraint *> constraints;
	// vector<Constraint *> constantConstraints;
	};
}