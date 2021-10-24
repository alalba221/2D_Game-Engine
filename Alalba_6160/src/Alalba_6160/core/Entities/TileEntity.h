#pragma once

#include "Entity.h"
#include "Alalba_6160/core/Events/Event.h"
namespace Alalba {

	class TileEntity : public Entity
	{
	public:
		TileEntity() = default;
		TileEntity(entt::entity handle, Scene* scene);
		TileEntity(const TileEntity& other) = default;

	public:
		virtual void OnEvent(Event& event) override;
		virtual void OnUpdate() override;
	};
}