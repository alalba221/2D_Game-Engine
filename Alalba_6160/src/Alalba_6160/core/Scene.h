#pragma once
#include "entt.hpp"
#include "Alalba_6160/core/Components.h"
namespace Alalba
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::registry& Reg() { return m_Registry; }

		// Entity* CreateEntity(const std::string& name = std::string());
		void Init();
		void Init_Start();
		void OnUpdate(float t);
		std::list<Entity*> GetEntities(){return m_Entities;}
		void AddEntity(Entity* entity,const std::string& name = std::string());
		Entity* redDictator[4];
		Entity* blueDictator[4];
		void dictateScreen(int s);
		int getScreen();
		void clearEntities();
	private:
		entt::registry m_Registry;
		std::list<Entity*> m_Entities;
		friend class Entity;
		int screenNum = 0;
		//0 is start, 1 is playing, 2 is end.



		// physics
	};
}