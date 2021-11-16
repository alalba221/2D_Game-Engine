#pragma once

#include "Alalba_6160/core/Scene.h"
#include "entt.hpp"
#include "Alalba_6160/core/Events/Event.h"
namespace Alalba {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		virtual ~Entity() = default;
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if(m_Scene->m_Registry.all_of<T>(m_EntityHandle))
				m_Scene->m_Registry.remove<T>(m_EntityHandle);
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			if(m_Scene->m_Registry.all_of<T>(m_EntityHandle))
				return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
		virtual void OnEvent(Event& event){};
		virtual void OnUpdate();
		operator bool() const { return m_EntityHandle != entt::null; }
	protected:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}