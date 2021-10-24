#pragma once

#include "Entity.h"
#include "Alalba_6160/core/Events/Event.h"
namespace Alalba {

	class Camera : public Entity
	{
	public:
		Camera() = default;
		Camera(entt::entity handle, Scene* scene)
			: Entity(handle, scene)
		{
		}
		Camera(const Camera& other) = default;

	public:
		virtual void OnEvent(Event& event){} ;
		virtual void OnUpdate(){} ;
	};
}