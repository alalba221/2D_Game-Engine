#include "alalbapch.h"
#include "Scene.h"


// #include "Hazel/Renderer/Renderer2D.h"
#include "Base.h"
#include "Vec2.h"
#include "Entity.h"
#include "Player.h"
#include "Camera.h"
namespace Alalba {
	Scene::Scene()
	{
		m_Entities.clear();
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

	void Scene::AddEntity(Entity* entity,const std::string& name)
	{
		this->m_Entities.emplace_back(entity);
		auto& tag = entity->AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
	}
	void Scene::Init()
	{
		// player
		Player* player = new Player(m_Registry.create(),this);
		AddEntity(player,"Player");

		player->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
		
		player->AddComponent<PlayerComponent>();
		player->AddComponent<GravityComponent>();
		player->AddComponent<SolidComponent>();
		player->AddComponent<KineticComponent>();
		player->AddComponent<TransformComponent>(40, 140, 
																						TILE_SIZE-4, 
																						SMALL_MARIO_COLLIDER_HEIGHT);

		// camera
		Camera* camera = new Camera(m_Registry.create(),this);
		AddEntity(camera, "Camera");
		camera->AddComponent<CameraComponent>(SNES_RESOLUTION_WIDTH / 2,
                                    SNES_RESOLUTION_WIDTH / 2,
                                    SNES_RESOLUTION_WIDTH,
                                    SNES_RESOLUTION_WIDTH);
	}
	void Scene::OnUpdate()
	{
		auto entities = this->GetEntities();
	
		for(auto entity: entities)
		{
			entity->OnUpdate();	
		}

	}

}