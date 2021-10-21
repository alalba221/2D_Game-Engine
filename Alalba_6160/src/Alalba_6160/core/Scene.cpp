#include "alalbapch.h"
#include "Scene.h"


// #include "Hazel/Renderer/Renderer2D.h"
#include "Base.h"
#include "Vec2.h"
#include "Entity.h"
#include "Player.h"
namespace Alalba {
	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();


		if (m_Registry.has<TransformComponent>(entity))
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);


		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif

	}

	Scene::~Scene()
	{
	}

	// entt::entity Scene::CreateEntity()
	// {
	// 	return m_Registry.create();
	// }
	Entity* Scene::CreateEntity(const std::string& name)
	{
		Entity* entity = new Entity{ m_Registry.create(), this };
		//entity.AddComponent<TransformComponent>();
		auto& tag = entity->AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		this->m_Entities.emplace_back(entity);
		return entity;
	}
	void Scene::Init()
	{
		Entity* mario = this->CreateEntity();
		int width = 72;
		mario->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
		mario->AddComponent<TransformComponent>(SNES_RESOLUTION_WIDTH/2-width/2-20,
																									SNES_RESOLUTION_HEIGHT/2-30,
																									TILE_SIZE,TILE_SIZE);
	
		Player* player = this->CreateEntity();
		player->AddComponent<PlayerComponent>();

		player->AddComponent<GravityComponent>();
		player->AddComponent<SolidComponent>();
		player->AddComponent<KineticComponent>();
		player->AddComponent<TextureComponent>(TextureId::MARIO_JUMP);
		player->AddComponent<TransformComponent>(40, 140, 
																						TILE_SIZE-4, 
																						SMALL_MARIO_COLLIDER_HEIGHT);
	}
	void Scene::OnUpdate()
	{
		

	}

}